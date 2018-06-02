
// CTrayIcon class
// trayicon.h header file copyright 2004 Steve Foxover

#pragma once

#include <shellapi.h>

class CTrayIcon
{
public:
	// constructors
	CTrayIcon();
	~CTrayIcon();

	// create task tray icon
	BOOL Create(CWnd* pParent,UINT nNotifyMsg=NULL,HICON hIcon=NULL,CString strToolTip="",UINT nIconID=1);
	// set current tool tip
	void SetTip(CString strTip);
	// Set current icon
	void SetIcon(HICON hIcon);
	// Tray icon ID
	UINT m_nTrayID;
	// parent window handle
	HWND m_hWndParent;
	// get version of windows shell
	DWORD GetShellVersion(LPCTSTR lpszDllName);
	// check if using version 5 or better shell
	BOOL IsVersion5(void);
	// version 5 or better shell
	BOOL m_bIsVersion5;
	// dynamic menu items
	CMenu* m_pMenu;
	CMenu* m_pSubMenu;
	CObArray m_obDynamicMenus;

	// load a menu resource and create menu
	BOOL LoadMenu(UINT nMenuResourceID);
	// load dynamic menu items
	BOOL LoadDynamicMenuItems(UINT nResourceID, CStringArray* pstraItems);
};
