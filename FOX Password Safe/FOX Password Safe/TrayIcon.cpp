
#include "stdafx.h"
#include "trayicon.h"
#include ".\trayicon.h"
#include "helpers.h"
#include "resource.h"

#define PACKVERSION(major,minor) MAKELONG(minor,major)

#ifndef _DLL_VERSION_H_
#define _DLL_VERSION_H_


#endif //_DLL_VERSION_H_

typedef struct _MYNOTIFYICONDATA_V5 {
        DWORD cbSize;
        HWND hWnd;
        UINT uID;
        UINT uFlags;
        UINT uCallbackMessage;
        HICON hIcon;
        CHAR   szTip[128];
        DWORD dwState;
        DWORD dwStateMask;
        CHAR   szInfo[256];
        union {
            UINT  uTimeout;
            UINT  uVersion;
        } DUMMYUNIONNAME;
        CHAR   szInfoTitle[64];
        DWORD dwInfoFlags;
} MYNOTIFYICONDATA_V5;

#define     NOTIFYICON_VERSION 3
#define NIS_HIDDEN              0x00000001
#define NIS_SHAREDICON          0x00000002

typedef struct _MYNOTIFYICONDATA_V4 {
        DWORD cbSize;
        HWND hWnd;
        UINT uID;
        UINT uFlags;
        UINT uCallbackMessage;
        HICON hIcon;
        CHAR   szTip[64];
} MYNOTIFYICONDATA_V4;

CTrayIcon::CTrayIcon()
: m_bIsVersion5(FALSE)
{
	m_nTrayID = 1;
	m_hWndParent = NULL;
	m_bIsVersion5 = IsVersion5();

	m_pMenu = NULL;
	m_pSubMenu = NULL;
}

CTrayIcon::~CTrayIcon()
{
	if(m_hWndParent)
	{
		NOTIFYICONDATA notifyicon;
		ZeroMemory(&notifyicon,sizeof(NOTIFYICONDATA));
		notifyicon.cbSize = NOTIFYICONDATA_V1_SIZE;
		notifyicon.hWnd = m_hWndParent;
		notifyicon.uID = m_nTrayID;

		Shell_NotifyIcon(NIM_DELETE, &notifyicon);
	}
	if(m_pMenu)
	{
		delete m_pMenu;
		m_pMenu = NULL;
	}
	if(m_pSubMenu)
	{
		delete m_pSubMenu;
		m_pSubMenu = NULL;
	}
	for(int n=0;n<m_obDynamicMenus.GetSize();n++)
	{
		CMenu* pMenu = (CMenu*)m_obDynamicMenus.GetAt(n);
		delete pMenu;
	}
	m_obDynamicMenus.RemoveAll();
}

// create task tray icon
BOOL CTrayIcon::Create(CWnd* pParent,UINT nNotifyMsg,HICON hIcon,CString strToolTip,UINT nIconID)
{
	ASSERT(pParent);

	if(nIconID != 0)
		m_nTrayID = nIconID;
	m_hWndParent = pParent->m_hWnd;
	NOTIFYICONDATA* pnotifyicon = NULL;
	// version 5 DLL
	if(m_bIsVersion5)
	{
		MYNOTIFYICONDATA_V5 notifyicon5;
		ZeroMemory(&notifyicon5,sizeof(MYNOTIFYICONDATA_V5));
		notifyicon5.cbSize = sizeof(MYNOTIFYICONDATA_V5);
		notifyicon5.uVersion = NOTIFYICON_VERSION;
		notifyicon5.dwState = NIS_SHAREDICON;
		notifyicon5.dwStateMask = NIS_SHAREDICON|NIS_HIDDEN;
		notifyicon5.hWnd = m_hWndParent;
		notifyicon5.uID = m_nTrayID;
		notifyicon5.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
		notifyicon5.uCallbackMessage = nNotifyMsg;
		notifyicon5.hIcon = hIcon;
		int nTextSize = strToolTip.GetLength();
		if(nTextSize > 63)
		{
			strToolTip = strToolTip.Left(63);	
			nTextSize = 63;
		}
		strncpy(notifyicon5.szTip,strToolTip.GetBuffer(nTextSize),nTextSize);
		strToolTip.ReleaseBuffer();
		pnotifyicon = (NOTIFYICONDATA*)&notifyicon5;
	}
	else // version 4
	{
		MYNOTIFYICONDATA_V4 notifyicon4;
		notifyicon4.cbSize = sizeof(MYNOTIFYICONDATA_V4);
		notifyicon4.hWnd = m_hWndParent;
		notifyicon4.uID = m_nTrayID;
		notifyicon4.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
		notifyicon4.uCallbackMessage = nNotifyMsg;
		notifyicon4.hIcon = hIcon;
		int nTextSize = strToolTip.GetLength();
		if(nTextSize > 63)
		{
			strToolTip = strToolTip.Left(63);	
			nTextSize = 63;
		}
		strncpy(notifyicon4.szTip,strToolTip.GetBuffer(nTextSize),nTextSize);
		strToolTip.ReleaseBuffer();
		pnotifyicon = (NOTIFYICONDATA*)&notifyicon4;
	}

	return Shell_NotifyIcon(NIM_ADD, pnotifyicon);
}

// set current tool tip
void CTrayIcon::SetTip(CString strTip)
{
	NOTIFYICONDATA notifyicon;
	ZeroMemory(&notifyicon,sizeof(NOTIFYICONDATA));
	notifyicon.cbSize = NOTIFYICONDATA_V1_SIZE;

	notifyicon.hWnd = m_hWndParent;
	notifyicon.uID = m_nTrayID;
	notifyicon.uFlags = NIF_TIP;
	int nTextSize = strTip.GetLength();
	if(nTextSize > 63)
	{
		strTip = strTip.Left(63);	
		nTextSize = 63;
	}
	strncpy(notifyicon.szTip,strTip.GetBuffer(nTextSize),nTextSize);
	strTip.ReleaseBuffer();

	Shell_NotifyIcon(NIM_MODIFY, &notifyicon);
}

// Set current icon
void CTrayIcon::SetIcon(HICON hIcon)
{
	ASSERT(hIcon);

	NOTIFYICONDATA notifyicon;
	ZeroMemory(&notifyicon,sizeof(NOTIFYICONDATA));
	notifyicon.cbSize = NOTIFYICONDATA_V1_SIZE;

	notifyicon.hWnd = m_hWndParent;
	notifyicon.uID = m_nTrayID;
	notifyicon.uFlags = NIF_ICON;
	notifyicon.hIcon = hIcon;

	Shell_NotifyIcon(NIM_MODIFY, &notifyicon);
}

// get version of windows shell
DWORD CTrayIcon::GetShellVersion(LPCTSTR lpszDllName)
{
    HINSTANCE hinstDll;
    DWORD dwVersion = 0;

    /* For security purposes, LoadLibrary should be provided with a 
       fully-qualified path to the DLL. The lpszDllName variable should be
       tested to ensure that it is a fully qualified path before it is used. */
    hinstDll = LoadLibrary(lpszDllName);
	
    if(hinstDll)
    {
        DLLGETVERSIONPROC pDllGetVersion;
        pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hinstDll, 
                          "DllGetVersion");

        /* Because some DLLs might not implement this function, you
        must test for it explicitly. Depending on the particular 
        DLL, the lack of a DllGetVersion function can be a useful
        indicator of the version. */

        if(pDllGetVersion)
        {
            DLLVERSIONINFO dvi;
            HRESULT hr;

            ZeroMemory(&dvi, sizeof(dvi));
            dvi.cbSize = sizeof(dvi);

            hr = (*pDllGetVersion)(&dvi);

            if(SUCCEEDED(hr))
            {
               dwVersion = PACKVERSION(dvi.dwMajorVersion, dvi.dwMinorVersion);
            }
        }
        FreeLibrary(hinstDll);
    }
    return dwVersion;
}

// check if using version 5 or better shell
BOOL CTrayIcon::IsVersion5(void)
{
	DWORD dwVersion = GetShellVersion(TEXT("shell32.dll"));
	BOOL bIsVer5 = (dwVersion >= PACKVERSION(5,00));
	return bIsVer5;
}

// load a menu resource and create menu
BOOL CTrayIcon::LoadMenu(UINT nMenuResourceID)
{
	if(m_pMenu)
	{
		delete m_pMenu;
		m_pMenu = NULL;
	}
	m_pMenu = new CMenu();
	return m_pMenu->LoadMenu(nMenuResourceID);
}

// load dynamic menu items
BOOL CTrayIcon::LoadDynamicMenuItems(UINT nResourceID, CStringArray* pstraItems)
{
	// clear any previous menu
	if(m_pMenu)
	{
		delete m_pMenu;
		m_pMenu = NULL;
	}
	if(m_pSubMenu)
	{
		delete m_pSubMenu;
		m_pSubMenu = NULL;
	}
	for(int n=0;n<m_obDynamicMenus.GetSize();n++)
	{
		CMenu* pMenu = (CMenu*)m_obDynamicMenus.GetAt(n);
		delete pMenu;
	}
	m_obDynamicMenus.RemoveAll();
	
	// create menus
	m_pMenu = new CMenu();
	m_pMenu->LoadMenu(nResourceID);
	CMenu* pmenuItem = m_pMenu->GetSubMenu(0);

	m_pSubMenu = new CMenu();
	m_pSubMenu->CreatePopupMenu();

	// load URL's menu's
	int nCount = 0;
	for(int n=0;n<pstraItems->GetSize();n++)
	{			
		CString strHeader = ParseXML("Header",pstraItems->GetAt(n));
		CString strName = ParseXML("Description",pstraItems->GetAt(n));
		CString strURL = ParseXML("URL",pstraItems->GetAt(n));
		// add new entry
		if(!strName.IsEmpty() && !strURL.IsEmpty())
		{
			// if has header insert header and menu text
			if(!strHeader.IsEmpty())
			{
				BOOL bFound = false;
				// look for existing sub menu to insert into
				CString strMenuText;
				int nMenus = m_pSubMenu->GetMenuItemCount();
				for(int x=0;x<nMenus;x++)
				{
					m_pSubMenu->GetMenuString(x,strMenuText,MF_BYPOSITION);
					if(strMenuText == strHeader)
					{
						CMenu* pNewSubMenu = m_pSubMenu->GetSubMenu(x);
						bFound = true;
						pNewSubMenu->AppendMenu(MF_STRING,ID_BASE_MENU_UID + nCount,strName);
					}
				}
				if(!bFound)
				{
					CMenu* pNewSubMenu = new CMenu();
					pNewSubMenu->CreatePopupMenu();	
					pNewSubMenu->AppendMenu(MF_STRING,ID_BASE_MENU_UID + nCount,strName);
					m_obDynamicMenus.Add(pNewSubMenu);
					m_pSubMenu->AppendMenu(MF_STRING|MF_POPUP,(UINT_PTR)pNewSubMenu->m_hMenu,strHeader);
				}
			}
			// insert in root submenu
			else
			{
				m_pSubMenu->AppendMenu(MF_STRING,ID_BASE_MENU_UID + nCount,strName);
			}
			nCount ++;
		}
	}
	// only load menu if there are web entries
	if(nCount > 0)
		pmenuItem->ModifyMenu(1,MF_BYPOSITION|MF_STRING|MF_POPUP,(UINT_PTR)m_pSubMenu->m_hMenu,"Load web site:");		

	return 0;
}
