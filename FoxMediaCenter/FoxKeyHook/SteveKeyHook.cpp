// SteveKeyHook.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include "stevekeyhook.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

// keyboard hook for stop play etc
LRESULT CALLBACK MyKeyboardProc(int code,
			WPARAM wParam,  // virtual-key code
			LPARAM lParam)   // keystroke-message information
{
	if(code >= 0)
	{
		
		if(GetKeyState(VK_SHIFT) & 0x80000000)
		{
			if(wParam >= 112 && wParam <= 123)
			{
				SendMessageMainWnd(wParam,lParam);
				return 1;
			}
		}
	}
	// Call the next hook in sequence
    return CallNextHookEx(NULL, code, wParam, lParam);
}

BOOL SendMessageMainWnd(WPARAM wParam,LPARAM lParam)
{
	HWND handle = FindWindow(APP_EXE_CLASSNAME,NULL);
	if(handle)
	{
		::SendMessage(handle,WM_KEYBOARD_HOOK_MSG,wParam,lParam);
		return true;
	}
	else
		return false;
}