// FOX Password Safe.h : main header file for the FOX Password Safe application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CFOXPasswordSafeApp:
// See FOX Password Safe.cpp for the implementation of this class
//

class CFOXPasswordSafeApp : public CWinApp
{
public:
	CFOXPasswordSafeApp();

// Overrides
public:
	virtual BOOL InitInstance();
	void SetPortraitPrintMode();
// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFOXPasswordSafeApp theApp;