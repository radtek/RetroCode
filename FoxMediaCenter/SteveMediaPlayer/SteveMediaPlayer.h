#if !defined(AFX_STEVEMEDIAPLAYER_H__8D59B6AD_4A0E_4018_8512_DFF55B85A0C5__INCLUDED_)
#define AFX_STEVEMEDIAPLAYER_H__8D59B6AD_4A0E_4018_8512_DFF55B85A0C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SteveMediaPlayer.h : main header file for STEVEMEDIAPLAYER.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSteveMediaPlayerApp : See SteveMediaPlayer.cpp for implementation.

class CSteveMediaPlayerApp : public COleControlModule
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

#endif // !defined(AFX_STEVEMEDIAPLAYER_H__8D59B6AD_4A0E_4018_8512_DFF55B85A0C5__INCLUDED)
