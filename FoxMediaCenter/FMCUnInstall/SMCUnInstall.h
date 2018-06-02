// SMCUnInstall.h : main header file for the SMCUNINSTALL application
//

#if !defined(AFX_SMCUNINSTALL_H__6D63C71D_418C_43E7_8B44_256A7C6BE70F__INCLUDED_)
#define AFX_SMCUNINSTALL_H__6D63C71D_418C_43E7_8B44_256A7C6BE70F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSMCUnInstallApp:
// See SMCUnInstall.cpp for the implementation of this class
//

class CSMCUnInstallApp : public CWinApp
{
public:
	CSMCUnInstallApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMCUnInstallApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSMCUnInstallApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMCUNINSTALL_H__6D63C71D_418C_43E7_8B44_256A7C6BE70F__INCLUDED_)
