// MyLockDown.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "MyLockDown.h"
#include ".\mylockdown.h"
#include "helpers.h"
#include <atlbase.h>

// CMyLockDown
LRESULT CALLBACK DebugProc(int nCode,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK LowLevelKeyboardProc(int nCode,WPARAM wParam,LPARAM lParam);

// handle to system hook
HHOOK glHandleHook = NULL;

IMPLEMENT_DYNAMIC(CMyLockDown, CWnd)
CMyLockDown::CMyLockDown()
{
	m_TimerUnlockBrowser = NULL;
	m_hinstHookDLL = NULL;
}

CMyLockDown::~CMyLockDown()
{
}


BEGIN_MESSAGE_MAP(CMyLockDown, CWnd)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// start lock down measures
void CMyLockDown::StartLockDown(BOOL bAutoEndLockdown)
{
	CString strReturn = "";
	CRegKey reg;
	BOOL bOK = false;
	// get disable browser helpers
	if(reg.Open(HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\Main", KEY_READ) == ERROR_SUCCESS)
	{
		 DWORD ulChars = 4024;
		 bOK = (reg.QueryStringValue("Enable Browser Extensions",strReturn.GetBuffer(ulChars),&ulChars) == ERROR_SUCCESS);
		 strReturn.ReleaseBuffer();
		 if(!bOK)
		 {
			 TRACE("Failed to read registry error: %d\r\n",GetLastError());		
			 strReturn = "";
		 }
		 reg.Close();
	}  
	CString strDefault = MyGetProfileString("CurrentBHOEnabled","");
	if(strDefault.IsEmpty())
		MyWriteProfileString("CurrentBHOEnabled",strReturn);
	// disable browser helpers
	if(strReturn == "yes")
	{
		if(reg.Create(HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\Main") == ERROR_SUCCESS)
		{
			bOK = (reg.SetStringValue("Enable Browser Extensions","no") == ERROR_SUCCESS);
			reg.Close();
		}  
	}

	// auto unlock browser after time period
	if(bAutoEndLockdown && MyGetProfileInt("AutoUnlockBrowser",1) == 1)
	{
		// time period for auto unlock browser
		DWORD nSecs = MyGetProfileInt("AutoUnlockBrowserTimeMins",DEFAULT_AUTO_UNLOCK_BROWSER_SECS);
		m_TimerUnlockBrowser = (UINT)SetTimer(ID_UNLOCK_BROWSER,nSecs*1000,NULL);	
	}
}

// end lock down
void CMyLockDown::EndLockdown(void)
{
	CString strBHO = MyGetProfileString("CurrentBHOEnabled","");
	CRegKey reg;
	if(!strBHO.IsEmpty())
	{
		if(reg.Create(HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\Main") == ERROR_SUCCESS)
		{
			BOOL bOK = (reg.SetStringValue("Enable Browser Extensions",strBHO) == ERROR_SUCCESS);
			reg.Close();
		}
	}	
}

void CMyLockDown::OnTimer(UINT nIDEvent)
{
	CWnd::OnTimer(nIDEvent);

	if(ID_UNLOCK_BROWSER == nIDEvent)
	{
		KillTimer(m_TimerUnlockBrowser);
		m_TimerUnlockBrowser = NULL;
		EndLockdown();
	}	
}

//===============================================================================================
// VERSION 2 search and disable hooks
//===============================================================================================

/*
// start hooking messages
void CMyLockDown::StartHook(void)
{
	//glHandleHook = SetWindowsHookEx(WH_DEBUG,DebugProc,NULL,0);
	//glHandleHook = SetWindowsHookEx(WH_KEYBOARD_LL,LowLevelKeyboardProc,NULL,0);

	HOOKPROC hkprcSysMsg = NULL; 
	m_hinstHookDLL = LoadLibrary((LPCTSTR) "D:\\MyAppdev\\Shareware\\FOX Password Safe\\FoxNoLog1\\FoxNoLog1\\Debug\\FoxNoLog1.dll");
	hkprcSysMsg = (HOOKPROC)GetProcAddress(m_hinstHookDLL, "LowLevelKeyboardProc"); 
	glHandleHook = SetWindowsHookEx(WH_KEYBOARD_LL,hkprcSysMsg,m_hinstHookDLL,0); 

	if(glHandleHook == NULL)
	{
		TRACE("SetWindowsHookEx failed, error:%u",GetLastError());
	}
}

// end hooking functions
void CMyLockDown::EndHook(void)
{
	if(glHandleHook != NULL)
		UnhookWindowsHookEx(glHandleHook);
	if(m_hinstHookDLL)
		FreeLibrary(m_hinstHookDLL);
}


LRESULT CALLBACK DebugProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	CString strBuf;
    static int c = 0; 
 
    if (nCode < 0)  // do not process message 
        return CallNextHookEx(glHandleHook, nCode, wParam, lParam); 
 
    switch (nCode) 
    { 
        case HC_ACTION:
			
			strBuf.Format("DEBUG - nCode: %d, tsk: %ld, %d times   ", 
                nCode,wParam, c++);
			TRACE("%s\r\n",strBuf);
            break; 
 
        default: 
            break; 
    } 

    return CallNextHookEx(glHandleHook, nCode, wParam, lParam); 
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	CString strBuf;
    static int c = 0; 
 
    if (nCode < 0)  // do not process message 
        return CallNextHookEx(glHandleHook, nCode, wParam, lParam); 
 
    switch (nCode) 
    { 
        case HC_ACTION:
			
			strBuf.Format("DEBUG - nCode: %d, tsk: %ld, %d times   ", nCode,wParam, c++);
			TRACE(strBuf);
            break; 
 
        default: 
            break; 
    } 

    return CallNextHookEx(glHandleHook, nCode, wParam, lParam); 
}

*/
