// PingJob.h: interface for the CPingJob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PINGJOB_H__E885C058_602A_4071_AFDC_3F72504F0456__INCLUDED_)
#define AFX_PINGJOB_H__E885C058_602A_4071_AFDC_3F72504F0456__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PingSocket.h"

class CPingJob : public CObject  
{
public:
	HWND m_pwndReply;
	CPingJob();
	CPingJob(CString strParams);
	virtual ~CPingJob();

	BOOL ContinueJob();
	void StopJob();
	// attributes
	CString m_strParams;

protected:
	// attributes
	CPingSocket* m_pPostSock;

};

#endif // !defined(AFX_PINGJOB_H__E885C058_602A_4071_AFDC_3F72504F0456__INCLUDED_)
