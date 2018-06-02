// PingSocket.cpp: implementation of the CPingSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PingJob.h"
#include "PingSocket.h"
#include "..\helpers.h"
#include "..\SteveMediaCenter.h"
#include "..\MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPingSocket::CPingSocket()
{
	m_hRequest = NULL;
	m_nTries = 0;
	m_bIsUsingProxy = FALSE;
	CRect rect(1,1,5,5);
	if(!m_MsgWnd.Create(NULL, "PostMsgWnd",
			WS_BORDER, rect, AfxGetMainWnd(), 71))
		DebugMessage("Error, failed to create PostMsgWnd Window");
	m_MsgWnd.m_pParent = this;
}

CPingSocket::~CPingSocket()
{
	CancelAsyncLookup();
	if(m_hSocket!=INVALID_SOCKET)
	{
		AsyncSelect(0);
		Close();
	}
	if(IsWindow(m_MsgWnd.m_hWnd))
	{
		::KillTimer(m_MsgWnd.m_hWnd,m_MsgWnd.m_TimerConnect);
		::KillTimer(m_MsgWnd.m_hWnd,m_MsgWnd.m_TimerRead);
		m_MsgWnd.DestroyWindow();
	}
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CPingSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CPingSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CPingSocket member functions

BOOL CPingSocket::StartDownload()
{
	m_nTries = 1;

	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();

	// connect string
	CString strHost = m_strURL.Mid(7);
	strHost = strHost.Left(strHost.Find("/"));
	CString strPath = m_strURL.Mid(7);
	strPath = strPath.Mid(strPath.Find("/"));

	// proxy connect here
	m_bIsUsingProxy = pApp->GetProfileInt("Settings","UseProxy",0);
	CString strPort = pApp->GetProfileString("Settings","HttpPort","80");
	CString strURL = pApp->GetProfileString("Settings","HttpProxyUrl","");
	
	m_strConnect = strHost;
	if(m_strConnect.IsEmpty())
	{
		DebugMessage("CPingSocket::StartDownload = m_strConnect.IsEmpty()");
		return FALSE;
	}

	if(m_bIsUsingProxy)
	{	// proxy connect
		m_strConnect = strURL;  
	}
	else
	{
		strPort = "80";
	}

	m_nPort = atoi(strPort);
	
	RemoveSpaces();
	ResetStrings();

	ConnectAsync();
	
	return TRUE;
}

void CPingSocket::Retry(BOOL bRetryMsg)
{
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();

	if(bRetryMsg)
	{
		DebugMessage("TimeStamp");
		DebugMessage("CPingSocket::Retry " + m_strURL + " IP address = " + m_MsgWnd.m_strIPAddress);
	}

	if(bRetryMsg)
		m_nTries ++;
	ResetStrings();

	if(m_hSocket != INVALID_SOCKET)
	{
		AsyncSelect(0);
	}
	Close();
	Create();

	if(m_nTries > 2)
	{
		CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
		BOOL bIsStat = (ParseXML("JobType",m_pParent->m_strParams) == "Stats");
		
		if(m_pParent->m_pwndReply && IsWindow(m_pParent->m_pwndReply))
			::PostMessage(m_pParent->m_pwndReply,bIsStat?WM_RETRYLATER_JOB:WM_DELETE_JOB,1,(LPARAM)m_pParent);
		else
			pMain->PostMessage(bIsStat?WM_RETRYLATER_JOB:WM_DELETE_JOB,1,(LPARAM)m_pParent);
		
		return;
	}

	AsyncSelect(FD_CONNECT);
	ConnectAsync();	
}

void CPingSocket::CancelAsyncLookup()
{
	if(m_hRequest != NULL)
	{
		int nRes = WSACancelAsyncRequest(m_hRequest);
		m_hRequest = NULL;
	}
}

void CPingSocket::ConnectAsync()
{
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	CString strParams = m_pParent->m_strParams;

	int nTimeout = atoi(pApp->GetProfileString("Settings","Timeout","20"));
	if(IsWindow(m_MsgWnd.m_hWnd))
	{
		m_MsgWnd.KillTimer(m_MsgWnd.m_TimerConnect);
		m_MsgWnd.m_TimerConnect = m_MsgWnd.SetTimer(ID_CONNECT,nTimeout*1000,NULL);
	}

	HOSTENT* lphost = NULL;
	DWORD dwAddr;
	dwAddr = inet_addr(m_strConnect);
	if((dwAddr != INADDR_NONE) || !IsWindow(m_MsgWnd.m_hWnd))
	{ 
		if( !IsWindow(m_MsgWnd.m_hWnd))
			DebugMessage("CHttpSock::ConnectAsync Message window is not valid");

		Close();
		Create();
		AsyncSelect(FD_CONNECT);
		Connect(m_strConnect,m_nPort);
	}
	else
	{	
		if(!IsWindow(m_MsgWnd.m_hWnd))
			return;
		m_hRequest = WSAAsyncGetHostByName(m_MsgWnd.m_hWnd, WM_HOSTNAME,m_strConnect,
			m_MsgWnd.m_buf,MAXGETHOSTSTRUCT);	
	}
}

void CPingSocket::OnConnect(int nErrorCode) 
{
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	if(IsWindow(m_MsgWnd.m_hWnd))
	{
		int nTimeout = atoi(pApp->GetProfileString("Settings","Timeout","20"));
		m_MsgWnd.KillTimer(m_MsgWnd.m_TimerConnect);
		m_MsgWnd.m_TimerConnect = m_MsgWnd.SetTimer(ID_CONNECT,nTimeout*1000,NULL);
	}
	// send string
	CString strHost = m_strURL.Mid(7);
	strHost = strHost.Left(strHost.Find("/"));
	m_strSend = "GET " + m_strURL + " HTTP/1.0\r\n";
	m_strSend += "Host: " + strHost + "\r\n";
	m_strSend += "User-Agent: Mozilla/5.0 (compatible; SteveFox 1.0; " + GetOSTypeLong() + ";)\r\n";
	// check for username password
	if(m_bIsUsingProxy)
	{
		if(UsingProxyPassword())
			m_strSend += GetProxyPasswordString();
	}

	m_strSend += "Pragma: no-cache\r\n";
	m_strSend += "Accept: */*\r\n\r\n";

	m_lSent = 0;
	AsyncSelect(FD_WRITE);
	return;
}

void CPingSocket::OnSend(int nErrorCode) 
{
	CString strSend;
	if((m_lSent >0) && (m_lSent < m_strSend.GetLength()))
		strSend = m_strSend.Mid(m_lSent+1);
	else
		strSend = m_strSend;
	int nLength = strSend.GetLength();

	m_lSent += Send(strSend,nLength);
	strSend.ReleaseBuffer();

	if(m_lSent < nLength)
	{
		AsyncSelect(FD_WRITE);
	}
	else
	{
		m_lReceived = 0;
		m_strSend.Empty();
		m_strRecData.Empty();
		if(IsWindow(m_MsgWnd.m_hWnd))
			m_MsgWnd.m_TimerRead = m_MsgWnd.SetTimer(ID_READ_TIMER,READ_WAIT_TIME,NULL);
		else
			AsyncSelect(FD_READ);
	}
}

void CPingSocket::OnReceive(int nErrorCode)
{
	if(nErrorCode == WSAENETDOWN)
	{
		if(IsWindow(m_MsgWnd.m_hWnd))
			m_MsgWnd.KillTimer(m_MsgWnd.m_TimerConnect);
		m_MsgWnd.m_TimerConnect = m_MsgWnd.SetTimer(ID_CONNECT,10000,NULL); // 10 second delay for retry
		return;
	}	

	char ch[4025];
	memset(&ch,0,4024);
	int lLen;
	lLen = Receive(&ch,4024);

	if(lLen == SOCKET_ERROR)
	{
		if(IsWindow(m_MsgWnd.m_hWnd))
			m_MsgWnd.KillTimer(m_MsgWnd.m_TimerConnect);
		m_MsgWnd.m_TimerConnect = m_MsgWnd.SetTimer(ID_CONNECT,10000,NULL); // 10 second delay for retry
		return;
	}
	// no data try again
	if(lLen == 0)
	{
		if(IsWindow(m_MsgWnd.m_hWnd))
			m_MsgWnd.m_TimerRead = m_MsgWnd.SetTimer(ID_READ_TIMER,READ_WAIT_TIME,NULL);
		else
			AsyncSelect(FD_READ);
		return;
	}

	ch[lLen] = '\0';
	CString strTemp = ch;	

	strTemp = ParseServerTags(strTemp); // get rid of "&lt;" chars etc.

	if(m_bStartRec) // ! found \r\n\r\n
	{
		m_strRecData += strTemp;

		if(m_strRecData.Find(_T("\r\n\r\n")) == -1) // not past header yet
		{
			if(IsWindow(m_MsgWnd.m_hWnd))
				m_MsgWnd.m_TimerRead = m_MsgWnd.SetTimer(ID_READ_TIMER,READ_WAIT_TIME,NULL);
			else
				AsyncSelect(FD_READ);
		}
		else  //found \r\n\r\n
		{
			int nReply = CheckHTTPResponce(m_strRecData);

			// check if its a redirect
			if(nReply == 301 || nReply == 302)
			{
				CString strPost = m_strURL.Mid(7);
				if(strPost.Find("/") != -1)
					strPost = strPost.Mid(strPost.Find("/")+1);
				CString strNewURL = GetServerTag("Location:",m_strRecData);
				// make path relative
				if(!IsKnownType(strNewURL))
				{
					BOOL bIsRoot = (strNewURL.Left(1) == '/');
					CString strHost = m_strURL.Mid(7);
					if(strHost.Find("/") != -1)
					{
						if(bIsRoot)
							strHost = strHost.Left(strHost.Find('/'));
						else
							strHost = strHost.Left(strHost.ReverseFind('/')+1);
					}					
					strNewURL = "http://" + strHost + strNewURL;
				}

				if(strNewURL == m_strURL)
				{
					DebugMessage("Redirection to same URL. Server must not like my request");		
					DebugMessage("\r\n");	
					Retry();
					return;
				}
				m_strURL = strNewURL;
				m_pParent->m_strParams = ReplaceXML(m_strURL,"FileURL",m_pParent->m_strParams);
		
				if(!m_bIsUsingProxy)
				{
					// get new host
					CString strHost = m_strURL.Mid(7);
					if(strHost.Find("/") != -1)
						strHost = strHost.Left(strHost.Find("/"));
					m_strConnect = strHost;
				
					// look for :port number
					CString strPort;
					if(m_strConnect.Find(':') != -1)
					{
						strPort = m_strConnect.Mid(m_strConnect.Find(':') +1);
						m_strConnect = m_strConnect.Left(m_strConnect.Find(':'));
					}
					else
						strPort = "80";
					m_nPort = atoi(strPort);
				}
	
				Retry(FALSE);
				return;
			}
			else if(nReply >= 400) // error from server
			{
				CString strError;
				strError.Format("Http error > 400 Fatal: %s Error = %d",m_strURL,nReply);
				DebugMessage("TimeStamp");
				DebugMessage(strError);

				AsyncSelect(0);
				Close();
				if(IsWindow(m_MsgWnd.m_hWnd))
				{
					::KillTimer(m_MsgWnd.m_hWnd,m_MsgWnd.m_TimerConnect);
					::KillTimer(m_MsgWnd.m_hWnd,m_MsgWnd.m_TimerRead);
				}

				if(m_pParent->m_pwndReply && IsWindow(m_pParent->m_pwndReply))
					::PostMessage(m_pParent->m_pwndReply,WM_RETRYLATER_JOB,1,(LPARAM)m_pParent);
				else					
					AfxGetMainWnd()->PostMessage(WM_RETRYLATER_JOB,1,(LPARAM)m_pParent);
				return;							   					
			}			
			// get file size of reply data
			m_lURLFileSize = GetFileSize(m_strRecData);

			// Remove <head> data from size of recv
			int nPos = m_strRecData.Find(_T("\r\n\r\n"));
			nPos += strlen(_T("\r\n\r\n"));
			lLen -= nPos;
			
			m_strRecData = m_strRecData.Mid(m_strRecData.Find(_T("\r\n\r\n")) + strlen(_T("\r\n\r\n")));
			m_bStartRec = FALSE;
		}
	}
	else  // save more data
	{
		m_strRecData += strTemp;
	}

	m_lBytesReceived += lLen;

	BOOL bEOF = FALSE;
	// if filesize of download is zero look for closing </html> tag
	if(m_lURLFileSize > 0)
		bEOF = m_lURLFileSize > 0 && m_lBytesReceived >= m_lURLFileSize;
	else
		bEOF = (m_strRecData.Find(_T("</html>")) != -1 || m_strRecData.Find(_T("</HTML>")) != -1 ||
				m_strRecData.Find(_T("</Html>")) != -1);
	

	if(bEOF)  // finished pinging server
	{
		Finished();	
		return;
	}
	else
	{
		if(IsWindow(m_MsgWnd.m_hWnd))
		{
			CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
			int nTimeout = atoi(pApp->GetProfileString("Settings","Timeout","20"));
			::KillTimer(m_MsgWnd.m_hWnd,m_MsgWnd.m_TimerConnect);
			m_MsgWnd.m_TimerConnect = m_MsgWnd.SetTimer(ID_CONNECT,nTimeout*1000,NULL);

			m_MsgWnd.m_TimerRead = m_MsgWnd.SetTimer(ID_READ_TIMER,READ_WAIT_TIME,NULL);
		}
		else
			AsyncSelect(FD_READ);
	}
}

void CPingSocket::ResetStrings()
{
	m_lBytesReceived = 0;
	m_strRecData = _T("");
	m_lURLFileSize = 0;
	m_bStartRec = TRUE;
}

void CPingSocket::Finished()
{
	AsyncSelect(0);
	Close();
	if(IsWindow(m_MsgWnd.m_hWnd))
	{
		::KillTimer(m_MsgWnd.m_hWnd,m_MsgWnd.m_TimerConnect);
		::KillTimer(m_MsgWnd.m_hWnd,m_MsgWnd.m_TimerRead);
	}
	m_pParent->m_strParams = ReplaceXML("Finished","Status",m_pParent->m_strParams);
	m_pParent->m_strParams = ReplaceXML(m_strRecData,"PingReply",m_pParent->m_strParams);

	if(m_pParent->m_pwndReply && IsWindow(m_pParent->m_pwndReply))
		::PostMessage(m_pParent->m_pwndReply,WM_FINISHED_JOB,1,(LPARAM)m_pParent);
	else
		AfxGetMainWnd()->PostMessage(WM_FINISHED_JOB,1,(LPARAM)m_pParent);
}

void CPingSocket::RemoveSpaces()
{
	int nPos = 0;
	while((nPos=m_strURL.Find(' '))!=-1)
	{
		m_strURL.SetAt(nPos,'+');
	}
}

void CPingSocket::OnClose(int nErrorCode) 
{
	DebugMessage("CPingSocket::OnClose");
	
	CAsyncSocket::OnClose(nErrorCode);
}

void CPingSocket::Send302Retry()
{
	// send string
	CString strURL = m_strURL.Mid(7);
	CString strHost,strPath;
	if(strURL.Find("/") != -1)
	{
		strPath = strURL.Mid(strURL.Find("/"));
		strHost = strURL.Left(strURL.Find("/"));
	}
	else 
	{
		strHost = strURL;
		strPath = "/";
	}
	// proxy uses full path
	if(m_bIsUsingProxy)
	{
		strPath = m_strURL;
	}

	m_strSend = "GET " + strPath + " HTTP/1.1\r\n";
	m_strSend += "Accept: */*\r\n";
	m_strSend += "Accept-Language: en-us\r\n";
	m_strSend += "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; " + GetOSTypeLong() + " 5.0; Vodexa)\r\n";
	m_strSend += "Connection: Keep-Alive\r\n";
	m_strSend += "Host: " + strHost + "\r\n";
	// check for username password
	if(m_bIsUsingProxy)
	{
		if(UsingProxyPassword())
			m_strSend += GetProxyPasswordString();
	}
	m_strSend += "\r\n";
	m_lSent = 0;
	AsyncSelect(FD_WRITE);
}
