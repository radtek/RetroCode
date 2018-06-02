// SMCSetup.h : main header file for the SMCSETUP application
//

#if !defined(AFX_SMCSETUP_H__BED5B0E9_A75A_46A8_ADDB_6ED6F3A5E190__INCLUDED_)
#define AFX_SMCSETUP_H__BED5B0E9_A75A_46A8_ADDB_6ED6F3A5E190__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSMCSetupApp:
// See SMCSetup.cpp for the implementation of this class
//

class CSMCSetupApp : public CWinApp
{
public:
	CSMCSetupApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMCSetupApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSMCSetupApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMCSETUP_H__BED5B0E9_A75A_46A8_ADDB_6ED6F3A5E190__INCLUDED_)
