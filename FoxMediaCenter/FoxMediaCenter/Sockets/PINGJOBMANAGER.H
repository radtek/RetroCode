// PingJobManager.h: interface for the CPingJobManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PINGJOBMANAGER_H__6CAD74DD_E3AA_4100_A1C5_1F0CD975D9C6__INCLUDED_)
#define AFX_PINGJOBMANAGER_H__6CAD74DD_E3AA_4100_A1C5_1F0CD975D9C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "pingJob.h"

class CPingJobManager  
{
public:
	void Save();
	UINT m_nTimerRetry5Mins;
	void RetryJobLater(CPingJob* pJob);
	void ContinueAnyCurrentJobs(BOOL bIgnoreRetryTime=FALSE);
	CPingJobManager();
	virtual ~CPingJobManager();

	void StopAllJobs();
	void DeleteJob(CPingJob *pJob);
	void ContinueJob(CPingJob* pJob);
	CObArray m_obaJobs;
	BOOL NewJob(CString strParams,BOOL bCanDiscardOnUrlAlone=true);
	void Serialize(CArchive& ar); 

};

#endif // !defined(AFX_PINGJOBMANAGER_H__6CAD74DD_E3AA_4100_A1C5_1F0CD975D9C6__INCLUDED_)
