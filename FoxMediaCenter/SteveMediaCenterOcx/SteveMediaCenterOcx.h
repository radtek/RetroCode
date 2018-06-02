#if !defined(AFX_STEVEMEDIACENTEROCX_H__F277D3DF_687A_4163_8FE8_45670C03373E__INCLUDED_)
#define AFX_STEVEMEDIACENTEROCX_H__F277D3DF_687A_4163_8FE8_45670C03373E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SteveMediaCenterOcx.h : main header file for STEVEMEDIACENTEROCX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterOcxApp : See SteveMediaCenterOcx.cpp for implementation.

class CSteveMediaCenterOcxApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEVEMEDIACENTEROCX_H__F277D3DF_687A_4163_8FE8_45670C03373E__INCLUDED)
