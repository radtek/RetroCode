// SteveMediaCenter.h : main header file for the STEVEMEDIACENTER application
//

#if !defined(AFX_STEVEMEDIACENTER_H__CC9FF730_F4AA_4587_9F97_DB10806DA7B2__INCLUDED_)
#define AFX_STEVEMEDIACENTER_H__CC9FF730_F4AA_4587_9F97_DB10806DA7B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterApp:
// See SteveMediaCenter.cpp for the implementation of this class
//

class CSteveMediaCenterApp : public CWinApp
{
public:
	CSteveMediaCenterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSteveMediaCenterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	int m_nREAD_WAIT_TIME;
	BOOL m_bIsAutoDialOn;
	BOOL m_bCheckingProxyName;
	CString m_strProxyPassword;
	BOOL m_bHasCheckedForProxyPasswordFromFile;
	CString m_strProxyUserName;
	//{{AFX_MSG(CSteveMediaCenterApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEVEMEDIACENTER_H__CC9FF730_F4AA_4587_9F97_DB10806DA7B2__INCLUDED_)
