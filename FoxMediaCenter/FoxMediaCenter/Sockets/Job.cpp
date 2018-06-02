// Job.cpp: implementation of the CJob class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\SteveMediaCenter.h"
#include "PingJob.h"
#include "Job.h"
#include "..\helpers.h"
#include "..\MainFrm.h"
#include "JobManager.h"
#include "PingJobManager.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CJob::CJob()
{
	m_pHttpSock = NULL;
	m_Time = NULL;
}

CJob::CJob(CString strParams)
{
	m_strParams = strParams;
	m_pHttpSock = NULL;
}

CJob::~CJob()
{
	StopJob();
}

void CJob::StopJob()
{
	if(m_pHttpSock)
	{
		m_pHttpSock->CancelAsyncLookup();
		if(m_pHttpSock->m_hSocket!=INVALID_SOCKET)
			m_pHttpSock->AsyncSelect(0);
		if(IsWindow(m_pHttpSock->m_MsgWnd.m_hWnd))
			m_pHttpSock->m_MsgWnd.DestroyWindow();
		delete m_pHttpSock;
		m_pHttpSock = NULL;
	}
	if(ParseXML("Status",m_strParams) == "Downloading")
	{
		m_strParams = ReplaceXML("Started","Status",m_strParams);
		UpdateTime();
	}
}

DWORD CJob::GetFileSize()
{
	DWORD dwSize = 0;
	CString str;
	str = ParseXML("ClipSize",m_strParams);
	dwSize = atol(str);
	
	return dwSize;
}

DWORD CJob::GetSecsToDownload()
{
	DWORD dwSize = 0;
	CString str;
	str = ParseXML("SecsToDownload",m_strParams);
	dwSize = atol(str);
	
	return dwSize;
}

void CJob::UpdateTime()
{
	// add download time
	if(m_Time != NULL)
	{
		CTime tm = CTime::GetCurrentTime();
		CTimeSpan tSpan = tm - m_Time;
		long lSecs = tSpan.GetTotalSeconds();
		if(lSecs > 0)
		{
			CString strSecs = ParseXML("SecsToDownload",m_strParams);
			long lSecsToDownload = atol(strSecs);
			lSecsToDownload += lSecs;
			strSecs.Format("%u",lSecsToDownload);
			m_strParams = ReplaceXML(strSecs,"SecsToDownload",m_strParams);
			m_Time = NULL;
		}
	}
}

BOOL CJob::ContinueJob()
{
	StopJob();

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();

	CString strURL = ParseXML("FileURL",m_strParams);
	CString strTest = strURL.Left(7);
	strTest.MakeLower();
	// bad request
	if(strTest != "http://")
	{
		DebugMessage("Bad URL request " + strURL);
		return FALSE;
	}
	m_pHttpSock = new CHttpSock();
	m_pHttpSock->m_pParent = this;
	// url
	m_pHttpSock->m_strURL = strURL;
	// local path
	m_pHttpSock->m_strDownloadPath = ParseXML("DownloadPath",m_strParams);

	// measure download time accurately
	m_Time = CTime::GetCurrentTime();
	m_strParams = ReplaceXML("Downloading","Status",m_strParams);

	if(!m_pHttpSock->StartDownload())
		return FALSE;

	return TRUE;
}


