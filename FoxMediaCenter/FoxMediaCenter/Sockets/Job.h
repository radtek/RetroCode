// Job.h: interface for the CJob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JOB_H__2F394322_0301_4B33_8620_F2FA77AD9AE1__INCLUDED_)
#define AFX_JOB_H__2F394322_0301_4B33_8620_F2FA77AD9AE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "HttpSock.h"

class CJob : public CObject 
{
public:
	void UpdateTime();
	DWORD GetSecsToDownload();
	DWORD GetFileSize();
	CTime m_Time;
	BOOL ContinueJob();
	void StopJob();
	// attributes
	CString m_strParams;
	
	// methods
	CJob();
	CJob(CString strParams);
	virtual ~CJob();

protected:
	// attributes
	CHttpSock* m_pHttpSock;

	friend class CJobManager;
};

#endif // !defined(AFX_JOB_H__2F394322_0301_4B33_8620_F2FA77AD9AE1__INCLUDED_)
