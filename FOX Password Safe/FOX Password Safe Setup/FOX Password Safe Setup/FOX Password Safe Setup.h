// FOX Password Safe Setup.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CFOXPasswordSafeSetupApp:
// See FOX Password Safe Setup.cpp for the implementation of this class
//

class CFOXPasswordSafeSetupApp : public CWinApp
{
public:
	CFOXPasswordSafeSetupApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFOXPasswordSafeSetupApp theApp;