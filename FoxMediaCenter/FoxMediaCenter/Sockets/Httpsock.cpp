// HttpSock.cpp : implementation file
//

#include "stdafx.h"
#include "job.h"
#include "HttpSock.h"
#include "..\Helpers.h"
#include "..\SteveMediaCenter.h"
#include "..\MainFrm.h"
#include "JobManager.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHttpSock

CHttpSock::CHttpSock()
{
	m_hRequest = NULL;
	m_nTries = 0;
	m_bIsUsingProxy = FALSE;
	CRect rect(1,1,5,5);
	if(!m_MsgWnd.Create(NULL, "HttpMsgWnd",
			WS_BORDER, rect, AfxGetMainWnd(), 68))
		DebugMessage("Error, failed to create HttpMsgWnd Window");
	m_MsgWnd.m_pParent = this;
	
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	m_nTimeOut = atoi(pApp->GetProfileString("Settings","Timeout","10"));
	m_lTotalSize = 0;
}

CHttpSock::~CHttpSock()
{
	CancelAsyncLookup();
	if(m_hSocket!=INVALID_SOCKET)
	{
		AsyncSelect(0);
		Close();
	}
	if(m_fileSave.m_hFile != -1)
	{
		m_fileSave.Close();
		m_fileSave.m_hFile = -1;
	}

	if(IsWindow(m_MsgWnd.m_hWnd))
	{
		::KillTimer(m_MsgWnd.m_hWnd,m_MsgWnd.m_TimerConnect);
		::KillTimer(m_MsgWnd.m_hWnd,m_MsgWnd.m_TimerRead);
		::KillTimer(m_MsgWnd.m_hWnd,m_nTimerCalcSpeed);
		m_MsgWnd.DestroyWindow();
	}
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CHttpSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CHttpSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CHttpSock member functions

BOOL CHttpSock::StartDownload()
{
	if(m_fileSave.m_hFile != -1)
	{
		m_fileSave.Close();
		m_fileSave.m_hFile = -1;
	}

	m_nTries ++;
	m_nHTTPStatus = 0;

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
		DebugMessage("CHttpSock::StartDownload = m_strConnect.IsEmpty()");
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
	ConnectAsync();
	
	return TRUE;
}

void CHttpSock::Retry()
{
	if(m_fileSave.m_hFile != -1)
	{
		m_fileSave.Close();
		m_fileSave.m_hFile = -1;
	}

	DebugMessage("CHttpSock::Retry " + m_strDownloadPath + " IP address = " + m_MsgWnd.m_strIPAddress);
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	SECFileSystem fp;

	CString strDir = m_strDownloadPath.Left(m_strDownloadPath.ReverseFind('\\'));
	if(!fp.DirectoryExists(strDir))
		fp.MakePath(strDir);

	// check CRC TRIES
	CString strParams = m_pParent->m_strParams;
	int nTries = atoi(ParseXML("CRCReTries",strParams));
	CString strShowID = ParseXML("ShowID",strParams);
	if(nTries > 1 && strShowID.IsEmpty())
	{
		fp.DeleteFile(m_strDownloadPath);
		AfxGetMainWnd()->PostMessage(WM_RETRYLATER_JOB,0,(LPARAM)m_pParent);
		return;
	}

	int nMax = atoi(pApp->GetProfileString("Settings","Retries","5"));
	m_nTimeOut = atoi(pApp->GetProfileString("Settings","Timeout","10"));

	m_nTries ++;
	m_nHTTPStatus = 0;
	ResetStrings();

	if(m_hSocket != INVALID_SOCKET)
	{
		AsyncSelect(0);
	}
	Close();
	Create();

	AsyncSelect(FD_CONNECT);
	ConnectAsync();	
}

void CHttpSock::CancelAsyncLookup()
{
	if(m_hRequest != NULL)
	{
		int nRes = WSACancelAsyncRequest(m_hRequest);
		m_hRequest = NULL;
	}
}

void CHttpSock::ConnectAsync()
{
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	m_bDoResume = FALSE;
	CString strParams = m_pParent->m_strParams;

	int nTimeout = m_nTimeOut;
	if(IsWindow(m_MsgWnd.m_hWnd))
	{
		m_MsgWnd.KillTimer(m_MsgWnd.m_TimerConnect);
		m_MsgWnd.m_TimerConnect = m_MsgWnd.SetTimer(ID_CONNECT,nTimeout*1000,NULL);

		m_MsgWnd.KillTimer(m_nTimerCalcSpeed);
		m_nTimerCalcSpeed = m_MsgWnd.SetTimer(ID_CALC_SPEED_TIMER,1000,NULL);
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

void CHttpSock::ResetStrings()
{
	m_strSend = "";
	m_strReply = "";
	m_lSent = 0;
	m_lReceived = 0;
}

void CHttpSock::OnConnect(int nErrorCode) 
{
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	if(IsWindow(m_MsgWnd.m_hWnd))
	{
		int nTimeout = m_nTimeOut;
		m_MsgWnd.KillTimer(m_MsgWnd.m_TimerConnect);
		m_MsgWnd.m_TimerConnect = m_MsgWnd.SetTimer(ID_CONNECT,nTimeout*1000,NULL);
	}

	m_startTime = CTime::GetCurrentTime();

	if(m_nHTTPStatus == 0)
	{
		m_nHTTPStatus = 1;
		CFileStatus status;
		
		// look for job starting pos for accelerated
		long lStartPos = atol(ParseXML("StartPos",m_pParent->m_strParams));

		if(CFile::GetStatus(m_strDownloadPath,status))
			m_lBytesStart = status.m_size;
		else
			m_lBytesStart = 0;
		
		m_lBytesStart += lStartPos;
		m_bDoResume = (m_lBytesStart > 0);

		// send string
		CString strHost = m_strURL.Mid(7);
		strHost = strHost.Left(strHost.Find("/"));
		CString strPath;
		strPath = m_strURL;
		m_strSend = "GET " + strPath + " HTTP/1.0\r\n";
		m_strSend += "Host: " + strHost + "\r\n";
		m_strSend += "User-Agent: Mozilla/5.0 (compatible; Vodexa 1.0; " + GetOSTypeLong() + ";)\r\n";
		// check for username password
		if(m_bIsUsingProxy)
		{
			if(UsingProxyPassword())
				m_strSend += GetProxyPasswordString();
		}

		m_strSend += "Pragma: no-cache\r\n";
		m_strSend += "Accept: */*\r\n\r\n";
		
		m_bSaveFile = FALSE;

		m_lSent = 0;
		AsyncSelect(FD_WRITE);
		return;
	}
	else 
	{
		m_lSent = 0;
		AsyncSelect(FD_WRITE);
		return;
	}	
}

void CHttpSock::OnSend(int nErrorCode) 
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
		m_strReply.Empty();
		if(IsWindow(m_MsgWnd.m_hWnd))
			m_MsgWnd.m_TimerRead = m_MsgWnd.SetTimer(ID_READ_TIMER,READ_WAIT_TIME,NULL);
		else
			AsyncSelect(FD_READ);
	}
}

void CHttpSock::OnReceive(int nErrorCode) 
{
	if(!this)
		return;

	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	const int nPacketSize = 4096;

	if(nErrorCode == WSAENETDOWN)
	{
		DebugMessage("OnReceive nErrorCode == WSAENETDOWN");
		if(IsWindow(m_MsgWnd.m_hWnd))
			m_MsgWnd.KillTimer(m_MsgWnd.m_TimerConnect);
		m_MsgWnd.m_TimerConnect = m_MsgWnd.SetTimer(ID_CONNECT,10000,NULL); // 10 second delay for retry
		return;
	}	
	if(m_nHTTPStatus == 1)  // start of download
	{		
		char chRec[nPacketSize+1];
		memset(&chRec,0,nPacketSize);
		CString strRec;
		CString strPath;

		// see if we need whole 4096 rec
		long nRecNeeded = nPacketSize;
		if(m_lReceived > 0)
		{
			nRecNeeded = (m_lTotalSize - (m_lBytesStart + m_lReceived));
			if(nRecNeeded > (nPacketSize-1))
				nRecNeeded = nPacketSize;
		}
		long lRec = Receive(chRec,nRecNeeded);
		if(lRec == SOCKET_ERROR)
		{
			DebugMessage("OnReceive lRec == SOCKET_ERROR");
			if(IsWindow(m_MsgWnd.m_hWnd))
				m_MsgWnd.KillTimer(m_MsgWnd.m_TimerConnect);
			m_MsgWnd.m_TimerConnect = m_MsgWnd.SetTimer(ID_CONNECT,5000,NULL); // 5 second delay for retry
			return;
		}
		// no data try again
		if(lRec == 0)
		{
			if(IsWindow(m_MsgWnd.m_hWnd))
				m_MsgWnd.m_TimerRead = m_MsgWnd.SetTimer(ID_READ_TIMER,pApp->m_nREAD_WAIT_TIME,NULL);
			else
				AsyncSelect(FD_READ);
			return;
		}

		if(!m_bSaveFile) // ! found \r\n\r\n
		{
			chRec[lRec] = '\0';
			m_strReply += chRec;
			if(m_strReply.Find("\r\n\r\n") == -1) // not finished
			{
				if(IsWindow(m_MsgWnd.m_hWnd))
					m_MsgWnd.m_TimerRead = m_MsgWnd.SetTimer(ID_READ_TIMER,pApp->m_nREAD_WAIT_TIME,NULL);
				else
					AsyncSelect(FD_READ);
			}
			else
			{
				int nReply = CheckHTTPResponce(m_strReply);

				// need username password autheticate
				if(nReply == 407) // Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==
				{
					DebugMessage("OnReceive nReply == 407");

					if(!pApp->m_bCheckingProxyName)
						if(CheckProxyUsernamePassword())
							m_nTries = 0;
					m_MsgWnd.m_TimerConnect = m_MsgWnd.SetTimer(ID_CONNECT,10000,NULL); // 10 second delay for retry
					return;
				}
				if(nReply == 302)  // redirect
				{
				}
				// fatal error, job deleted 
				if(nReply >= 400)
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
					if(nReply == 404)
					{
						AfxGetMainWnd()->PostMessage(WM_DELETE_JOB,0,(LPARAM)m_pParent);		
						return;
					}
					AfxGetMainWnd()->PostMessage(WM_RETRYLATER_JOB,0,(LPARAM)m_pParent);
					return;							   					
				}

				m_bSaveFile = TRUE;
				// look for filesize if job
				m_lTotalSize = atol(ParseXML("EndPos",m_pParent->m_strParams));
				if(m_lTotalSize == 0)
					m_lTotalSize = GetFileSize(m_strReply);
				// Empty file error
				if(m_lTotalSize== 0)
				{
					CString strError;
					strError.Format("Zero file size: %s",m_strURL);
					DebugMessage("TimeStamp");
					DebugMessage(strError);
					
					AfxGetMainWnd()->PostMessage(WM_DELETE_JOB,0,(LPARAM)m_pParent);
					return;
				}
		
				// see if enough disk space free
				double ldNeeded = m_lTotalSize - m_lBytesStart;
				SECFileSystem fp;
				double lSize = GetDiskSpaceFree();
				lSize = lSize * 1000;
				lSize = lSize * 1024;
				double lSizeTest = ldNeeded; 
				if((lSize < lSizeTest) && (lSize !=0) && (lSize > 0) && (lSizeTest > 0))
				{
					lSize = lSize/1024;
					lSizeTest = lSizeTest /1024;
					CString strMsg;
					strMsg.Format("You have %u Kb Free on drive %s. You need to have free %u Kb before you continue to download.",lSize,strPath.Left(1),lSizeTest);
					DebugMessage(strMsg);
					return;
				}
				if(m_bDoResume)  // resume partial file
				{
					if(m_lBytesStart == m_lTotalSize)  // allready downloaded, check OK
					{
						Finished();
						return;							   					
					}

					AsyncSelect(0);
					Close();
					Create();
					
					m_bSaveFile = FALSE;
					ResetStrings();
					m_bDoResume = FALSE;

					CString strHost = m_strURL.Mid(7);
					strHost = strHost.Left(strHost.Find("/"));
					CString strPath;
					strPath = m_strURL;

					m_strSend = "GET " + strPath + " HTTP/1.0\r\n";
					m_strSend += "User-Agent: Mozilla/5.0 (compatible; Vodexa 1.0; " + GetOSTypeLong() + ";)\r\n";
					m_strSend += "Host: " + strHost + "\r\n";
					if(m_bIsUsingProxy)
					{
						if(UsingProxyPassword())
							m_strSend += GetProxyPasswordString();
					}
					m_strSend += "Pragma: no-cache\r\n";
					m_strSend += "Accept: */*\r\n";

					CString str; 
					str.Format("Range: bytes=%u-%u\r\n\r\n",m_lBytesStart,m_lTotalSize-1);
					m_strSend += str;

					m_nHTTPStatus = 4;

					ConnectAsync();
					return;
				}

				int nPos = m_strReply.Find("\r\n\r\n");
				if((nPos+4) < lRec) // save some data
				{
					char ch[4097];
					for(int n=0;n< (lRec -(nPos+4));n++)
						ch[n] = chRec[(nPos+4)+n];
					m_strReply = m_strReply.Left(nPos);
					SaveBytes(ch,(lRec -(nPos+4)),FALSE);						
				}
				if(m_hSocket != INVALID_SOCKET)
				{
					if(IsWindow(m_MsgWnd.m_hWnd))
						m_MsgWnd.m_TimerRead = m_MsgWnd.SetTimer(ID_READ_TIMER,pApp->m_nREAD_WAIT_TIME,NULL);
					else
						AsyncSelect(FD_READ);
				}
			}
		}
		else
		{
			SaveBytes(chRec,lRec);	
		}
		if((m_lBytesStart + m_lReceived >= m_lTotalSize))
		{
			Finished();	
			return;
		}
	}
	if(m_nHTTPStatus == 4)    // save data
	{
		char chRec[nPacketSize+1];
		CString strRec;
		CString strPath;
		long lRec = Receive(chRec,nPacketSize);
		if(lRec == SOCKET_ERROR)
		{
			DebugMessage("OnReceive m_nHTTPStatus == 4");

			if(IsWindow(m_MsgWnd.m_hWnd))
				m_MsgWnd.KillTimer(m_MsgWnd.m_TimerConnect);
			m_MsgWnd.m_TimerConnect = m_MsgWnd.SetTimer(ID_CONNECT,10000,NULL); // 10 second delay for retry
			return;
		}
		// no data try again
		if(lRec == 0)
		{
			if(IsWindow(m_MsgWnd.m_hWnd))
				m_MsgWnd.m_TimerRead = m_MsgWnd.SetTimer(ID_READ_TIMER,pApp->m_nREAD_WAIT_TIME,NULL);
			else
				AsyncSelect(FD_READ);
			return;
		}

		if(!m_bSaveFile) // ! found \r\n\r\n
		{
			chRec[lRec] = '\0';
			m_strReply += chRec;
			if(m_strReply.Find("\r\n\r\n") == -1) // not finished
			{
				if(IsWindow(m_MsgWnd.m_hWnd))
					m_MsgWnd.m_TimerRead = m_MsgWnd.SetTimer(ID_READ_TIMER,pApp->m_nREAD_WAIT_TIME,NULL);
				else
					AsyncSelect(FD_READ);
			}
			else
			{
				int nPos = m_strReply.Find("\r\n\r\n");
				if((nPos+4) < lRec) // save some data
				{
					char ch[4097];
					for(int n=0;n< (lRec -(nPos+4));n++)
						ch[n] = chRec[(nPos+4)+n];
					m_strReply = m_strReply.Left(nPos);

					SaveBytes(ch,(lRec -(nPos+4)));
				}
				m_bSaveFile = TRUE;
			}
		}
		else
		{
			SaveBytes(chRec,lRec);	
		}
		if((m_lBytesStart + m_lReceived >= m_lTotalSize) && m_lTotalSize >0)
		{
			Finished();	
			return;
		}
	}	
}

void CHttpSock::OnClose(int nErrorCode) 
{
	DebugMessage("CHttpSock::OnClose");
	CAsyncSocket::OnClose(nErrorCode);
}

BOOL CHttpSock::SaveBytes(char* pChar,int nLen,BOOL bTimer)
{
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();

	if(IsWindow(m_MsgWnd.m_hWnd))
	{
		::KillTimer(m_MsgWnd.m_hWnd,m_MsgWnd.m_TimerConnect);
		m_MsgWnd.m_TimerConnect = m_MsgWnd.SetTimer(ID_CONNECT,m_nTimeOut*1000,NULL);
	}
	AsyncSelect(0);

	if(nLen <= 0)
	{
		return FALSE;
	}
	m_lReceived += nLen;

	// save file
	TRY
	{
		if(m_fileSave.m_hFile == -1)
		{
			if(!m_fileSave.Open(m_strDownloadPath, CFile::modeCreate 
						| CFile::modeWrite | CFile::modeNoTruncate))
			{
				DebugMessage("CHttpSock::SaveBytes File could not be opened");
				Close();
				if(m_fileSave.m_hFile != -1)
				{
					m_fileSave.Close();
					m_fileSave.m_hFile = -1;
				}
				Retry();
				return FALSE;
			}
		}
		m_fileSave.SeekToEnd();
		m_fileSave.Write(pChar,nLen);
	}
	CATCH( CFileException, e)
	{
		DebugMessage("CHttpSock::SaveBytes File could not be opened");
		Close();
		if(m_fileSave.m_hFile != -1)
		{
			m_fileSave.Close();
			m_fileSave.m_hFile = -1;
		}
		Retry();
		return FALSE;
	}
	END_CATCH
	
	if(bTimer)
	{
		if(IsWindow(m_MsgWnd.m_hWnd))
			m_MsgWnd.m_TimerRead = m_MsgWnd.SetTimer(ID_READ_TIMER,pApp->m_nREAD_WAIT_TIME,NULL);
		else
			AsyncSelect(FD_READ);
	}

	return TRUE;
}

void CHttpSock::Finished()
{
	if(m_hSocket!=INVALID_SOCKET)
	{
		AsyncSelect(0);
		Close();
	}
	if(IsWindow(m_MsgWnd.m_hWnd))
	{
		::KillTimer(m_MsgWnd.m_hWnd,m_MsgWnd.m_TimerConnect);
		::KillTimer(m_MsgWnd.m_hWnd,m_MsgWnd.m_TimerRead);
		::KillTimer(m_MsgWnd.m_hWnd,m_nTimerCalcSpeed);
	}
	if(m_fileSave.m_hFile != -1)
	{
		m_fileSave.Close();
		m_fileSave.m_hFile = -1;
	}
	BOOL bStreaming = (ParseXML("Streaming",m_pParent->m_strParams) == "TRUE");
	if(!bStreaming)
		CalculateSpeed();

	AfxGetMainWnd()->PostMessage(WM_FINISHED_JOB,0,(LPARAM)m_pParent);
}

void CHttpSock::CalculateSpeed()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if(m_lTotalSize == 0)
		return;

	long lStartPos = atol(ParseXML("StartPos",m_pParent->m_strParams));

	long lTot = m_lTotalSize - lStartPos;
	if(lTot > 1024)
		lTot = lTot / 1024;
	else 
		lTot = 1;
	long lRec = m_lBytesStart + m_lReceived - lStartPos;
	if(lRec > 1024)
		lRec = lRec / 1024;
	else 
		lRec = 1;
	if(lRec > lTot) 
		lRec = lTot;

	// work out job speed after 10 Kb
	float nSpeed = 0;
	if(m_lReceived > 10000)
	{
		CTime tm = CTime::GetCurrentTime();
		CTimeSpan tmSpan = tm - m_startTime;
		long lSecs = tmSpan.GetTotalSeconds();
		if(lSecs > 0)
		{
			double dRes = (double)m_lReceived / 1024;
			nSpeed = dRes / lSecs;
		}
	}
}

void CHttpSock::FailedCRCCheck()
{
	DebugMessage("Bad CRC on file " + m_strDownloadPath);
	SECFileSystem fp;
	CString strDestination;
	strDestination = m_strDownloadPath.Left(m_strDownloadPath.ReverseFind('\\'));
	if(!fp.DirectoryExists(strDestination))
	{
		if(!fp.MakePath(strDestination))
		{
			DebugMessage("Error creating directory, please try closing windows file explorer");
		}
	}
	CString strPath = m_strDownloadPath.Left(m_strDownloadPath.ReverseFind('.')+1);
	fp.DeleteFiles(strPath + "*");

	CString strParams = m_pParent->m_strParams;
	int nTries = atoi(ParseXML("CRCReTries",strParams));
	nTries ++;
	CString strTries;
	strTries.Format("%d",nTries);
	m_pParent->m_strParams = ReplaceXML(strTries,"CRCReTries",strParams);
	Retry();
}
