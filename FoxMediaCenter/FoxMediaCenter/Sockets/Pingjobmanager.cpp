// PingJobManager.cpp: implementation of the CPingJobManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\SteveMediaCenter.h"
#include "PingJobManager.h"
#include "..\helpers.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPingJobManager::CPingJobManager()
{
	m_nTimerRetry5Mins = 0;

	CString strJobFile;
	// install dir
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\'));
	strJobFile = strDestination + "\\datafile.dat";
	// serialize
	TRY
	{
		SECCryptoFile fp;
		if(fp.Open(strJobFile,"duyb783slp", CFile::modeCreate|CFile::modeNoTruncate|CFile::modeRead, SECCryptoFile::ECB))
		{
			CArchive ar( &fp, CArchive::load);
			Serialize(ar);
			ar.Close();
			fp.Close();
		}
	}
	CATCH(CFileException,e)
	{
		DebugMessage("Error while trying to load jobs file");
	}
	END_CATCH
}

CPingJobManager::~CPingJobManager()
{
	Save();

	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		CPingJob* pJob = (CPingJob*)m_obaJobs.GetAt(n);
		if(pJob)
			delete pJob;
	}
	m_obaJobs.RemoveAll();
}

void CPingJobManager::Save()
{
	CString strJobFile;
	// install dir
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\'));
	strJobFile = strDestination + "\\datafile.dat";
	// serialize
	TRY
	{
		SECCryptoFile fp;
		if(fp.Open(strJobFile,"duyb783slp", CFile::modeCreate|CFile::modeWrite, SECCryptoFile::ECB))
		{
			CArchive ar( &fp, CArchive::store);
			Serialize(ar);
			ar.Close();
			fp.Close();
		}
	}
	CATCH(CFileException,e)
	{
		DebugMessage("Error while trying to save jobs file");
	}
	END_CATCH
}

void CPingJobManager::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{
		for(int n=0;n<m_obaJobs.GetSize();n++)
		{
			CPingJob* pJob = (CPingJob*)m_obaJobs.GetAt(n);
			CString strParams = pJob->m_strParams;
			if(ParseXML("Status",strParams) != "Finished")
			{				
				TRY
				{
					ar << strParams;
				}
				CATCH(CArchiveException,e)
				{
					DebugMessage("CPingJobManager::Serialize store exception");
				}
				END_CATCH
			}
		}
	}
	else
	{	
		m_obaJobs.RemoveAll();
		BOOL bLoad = TRUE;
		while(bLoad)
		{
			CString strParams;
			TRY
			{
				ar >> strParams;
				if(ParseXML("Status",strParams) != "Finished")
				{
					CPingJob* pJob = new CPingJob(strParams);
					m_obaJobs.Add(pJob);
				}
			}
			CATCH(CArchiveException,e)
			{
				bLoad = FALSE;
			}
			END_CATCH
		}
	}
}

BOOL CPingJobManager::NewJob(CString strParams,BOOL bCanDiscardOnUrlAlone)
{
	// look for any existing job, means download started already, not vaid for testing for same job
	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		CPingJob* pJob = (CPingJob*)m_obaJobs.GetAt(n);
		// test for same job
		CString strJobTest = pJob->m_strParams;
		CString strNewTest = strParams;	
		if(bCanDiscardOnUrlAlone)
		{
			strJobTest = ParseXML("FileURL",strJobTest);
			int nFind = -1;
			if((nFind = strJobTest.Find("?")) != -1)
				strJobTest = strJobTest.Left(nFind);
			strNewTest = ParseXML("FileURL",strNewTest);
			if((nFind = strNewTest.Find("?")) != -1)
				strNewTest = strNewTest.Left(nFind);
		}
		else
		{
			strJobTest = ReplaceXML("","Status",strJobTest);
			strNewTest = ReplaceXML("","Status",strNewTest);

			strJobTest = ReplaceXML("","RetryTime",strJobTest);
			strNewTest = ReplaceXML("","RetryTime",strNewTest);
		}
		if(strJobTest == strNewTest)
		{
			ContinueAnyCurrentJobs(TRUE);
			return FALSE;
		}
	}
	
	CString strURL = ParseXML("FileURL",strParams);
	strURL.MakeLower();
	if(strURL.Find("http://127.0.0.1") != -1)
		DebugMessage("WARNING local host used in url " + strURL);


	strParams = ReplaceXML("Started","Status",strParams);
	CPingJob* pJob = new CPingJob(strParams);
	m_obaJobs.Add(pJob);
	
	ContinueAnyCurrentJobs();

	Save();

	return TRUE;
}

void CPingJobManager::ContinueJob(CPingJob* pJob)
{
	if(!pJob->ContinueJob())
		DeleteJob(pJob);
}

void CPingJobManager::DeleteJob(CPingJob *pJob)
{
	BOOL bJobVerified = FALSE;
	CObArray obTemp;
	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		if(pJob != m_obaJobs.GetAt(n))
			obTemp.Add(m_obaJobs.GetAt(n));
		else
			bJobVerified = TRUE;
	}

	if(pJob && bJobVerified)
	{
		pJob->StopJob();
		m_obaJobs.RemoveAll();
		m_obaJobs.Copy(obTemp);
		delete pJob;
		pJob = NULL;
	}
}

void CPingJobManager::StopAllJobs()
{
	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		((CPingJob*)m_obaJobs.GetAt(n))->StopJob();
	}
}

void CPingJobManager::ContinueAnyCurrentJobs(BOOL bIgnoreRetryTime)
{
	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		CPingJob* pJob = (CPingJob*)m_obaJobs.GetAt(n);
		CString strStatus = ParseXML("Status",pJob->m_strParams);
		if(strStatus == "none" || strStatus == "Started")
		{
			// look for a retry time in params
			CString strTime = ParseXML("RetryTime",pJob->m_strParams);
			BOOL bOK = TRUE;
			if(!bIgnoreRetryTime && !strTime.IsEmpty())
			{
				CTime tmOld(atol(strTime));
				CTime tmNow = CTime::GetCurrentTime();
				CTimeSpan span = tmNow - tmOld;
				if(span.GetTotalMinutes() < 5)
					bOK = FALSE;
			}
			if(bOK)
			{
				pJob->StopJob();   // maybe only continue none job, and change stopped job to none
				pJob->ContinueJob();
				return;
			}
		}
	}
	// set retry Timer
	if(m_obaJobs.GetSize() > 0 && !m_nTimerRetry5Mins)
	{
		int nMins = AfxGetApp()->GetProfileInt("Settings","RetryTimeMins",30);
		m_nTimerRetry5Mins = AfxGetMainWnd()->SetTimer(ID_5MIN_PING_RETRY,nMins * ONE_MINUTE,NULL);
	}
}

void CPingJobManager::RetryJobLater(CPingJob *pJob)
{
	CTime tm = CTime::GetCurrentTime();
	CString str;
	str.Format("%u",tm.GetTime());
	
	pJob->StopJob();
	pJob->m_strParams = ReplaceXML(str,"RetryTime",pJob->m_strParams);

	if(!m_nTimerRetry5Mins)
	{
		int nMins = AfxGetApp()->GetProfileInt("Settings","RetryTimeMins",30);
		m_nTimerRetry5Mins = AfxGetMainWnd()->SetTimer(ID_5MIN_PING_RETRY,nMins * ONE_MINUTE,NULL);
	}
}
