// JobManager.h: interface for the CJobManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JOBMANAGER_H__77B1AB94_590C_4631_87AE_1B391994DBCD__INCLUDED_)
#define AFX_JOBMANAGER_H__77B1AB94_590C_4631_87AE_1B391994DBCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Job.h"
class CAppendClass;

class CJobManager  
{
public:
	void ExecuteJob(CJob* pJob);
	BOOL VerfifyJobOK(CJob *pJob);
	void Save();
	BOOL GetUpdateFile(CString strParams);
	void DeleteJobWithURL(CString strFileURL);
	void DeleteAnyJobsWithFileURL(CString );
	BOOL AreAnyJobsDownloading();
	BOOL DownloadFile(CString strParams);
	void ContinueAnyCurrentJobs(BOOL bPolite = FALSE);
	void StopAllJobs(CString strShowID="");
	void DeleteJob(CJob *pJob,BOOL bRemoveFromList=TRUE);
	void ContinueJob(CJob* pJob);
	CObArray m_obaJobs;
	BOOL NewJob(CString strParams,BOOL bContinueDownloads=TRUE,BOOL bDontCheck=FALSE);
	CJobManager();
	void Serialize(CArchive& ar); 
	virtual ~CJobManager();

};

#endif // !defined(AFX_JOBMANAGER_H__77B1AB94_590C_4631_87AE_1B391994DBCD__INCLUDED_)
