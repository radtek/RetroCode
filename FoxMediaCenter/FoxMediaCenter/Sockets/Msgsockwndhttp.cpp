// MsgSockWndHTTP.cpp : implementation file
//

#include "stdafx.h"
#include "..\SteveMediaCenter.h"

#include "HttpSock.h"
#include "MsgSockWndHTTP.h"
#include "..\Helpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgSockWndHTTP

CMsgSockWndHTTP::CMsgSockWndHTTP()
{
	m_TimerRead = 0;
}

CMsgSockWndHTTP::~CMsgSockWndHTTP()
{
}


BEGIN_MESSAGE_MAP(CMsgSockWndHTTP, CWnd)
	//{{AFX_MSG_MAP(CMsgSockWndHTTP)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_HOSTNAME,OnHostName)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMsgSockWndHTTP message handlers

void CMsgSockWndHTTP::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == ID_READ_TIMER)
	{
		if(IsWindow(m_hWnd))
			KillTimer(m_TimerRead);
		if(m_pParent->m_hSocket != INVALID_SOCKET)
			m_pParent->AsyncSelect(FD_READ);
	}
	if(nIDEvent == ID_CONNECT)
	{
		DebugMessage("TimeStamp");
		DebugMessage("CMsgSockWndHTTP ID_CONNECT Retry()");
		m_pParent->Retry();
	}
	if(nIDEvent == ID_CALC_SPEED_TIMER)
	{
		m_pParent->CalculateSpeed();
	}
}

LONG CMsgSockWndHTTP::OnHostName(UINT wParam, LONG lParam) 
{
	if(!m_pParent)
	{
		DebugMessage("CMsgSockWndHTTP::OnHostName !m_pParent");
		return 1;
	}
	m_pParent->m_hRequest = NULL;

	UINT uError = WSAGETASYNCERROR(lParam);
	if(uError != 0)
	{
		DebugMessage("Error resolving DNS lookup.");
		return 1;
	}

	LPHOSTENT lphost = (LPHOSTENT)m_buf; 	
	SOCKADDR_IN socAddr;
	memset(&socAddr,0,sizeof(socAddr));
	socAddr.sin_family = AF_INET;
	socAddr.sin_port = m_pParent->m_nPort;
	memcpy(&socAddr.sin_addr,lphost->h_addr_list[0],sizeof(lphost->h_addr_list[0]));
	CString str;
	str.Format("%d.%d.%d.%d",
				socAddr.sin_addr.S_un.S_un_b.s_b1,
				socAddr.sin_addr.S_un.S_un_b.s_b2,
				socAddr.sin_addr.S_un.S_un_b.s_b3,
				socAddr.sin_addr.S_un.S_un_b.s_b4);

	m_strIPAddress = str;

	if(m_pParent)
	{
		if(m_pParent->m_hSocket != INVALID_SOCKET)
		{
			m_pParent->AsyncSelect(0);
			m_pParent->Close();
		}
		m_pParent->Create();
		m_pParent->AsyncSelect(FD_CONNECT);
		m_pParent->Connect(str,m_pParent->m_nPort);
	}

	return 1;
}

