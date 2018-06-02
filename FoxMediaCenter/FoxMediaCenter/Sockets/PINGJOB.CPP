// PingJob.cpp: implementation of the CPingJob class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\SteveMediaCenter.h"
#include "PingJob.h"
#include "..\helpers.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPingJob::CPingJob()
{
	m_pPostSock = NULL;
	m_pwndReply = NULL;
}

CPingJob::~CPingJob()
{
	StopJob();
}

CPingJob::CPingJob(CString strParams)
{
	m_strParams = strParams;
	m_pPostSock = NULL;
	m_pwndReply = NULL;
}

void CPingJob::StopJob()
{
	if(m_pPostSock)
	{
		m_pPostSock->CancelAsyncLookup();
		if(m_pPostSock->m_hSocket!=INVALID_SOCKET)
			m_pPostSock->AsyncSelect(0);
		if(IsWindow(m_pPostSock->m_MsgWnd.m_hWnd))
			m_pPostSock->m_MsgWnd.DestroyWindow();
		delete m_pPostSock;
		m_pPostSock = NULL;
	}
}

BOOL CPingJob::ContinueJob()
{
	StopJob();
	CString strURL = ParseXML("FileURL",m_strParams);
	CString strTest = strURL.Left(7);
	strTest.MakeLower();
	// bad request
	if(strTest != "http://")
	{
		DebugMessage("Bad URL request " + strURL);
		return FALSE;
	}
	
	m_pPostSock = new CPingSocket();
	m_pPostSock->m_pParent = this;
	m_pPostSock->m_strURL = strURL;
	if(!m_pPostSock->StartDownload())
		return FALSE;

	return TRUE;
}
