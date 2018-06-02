#include "StdAfx.h"
#include "mytoolbars.h"
#include "resource.h"
#include "IEFTPPlugin.h"
#include ".\mytoolbars.h"
#include "helpers.h"
#include "AddressBookDlg.h"
#include "EnterRegCode.h"
#include "aboutdlg.h"
#include "ChangeDirToDlg.h"

CMyToolbars::CMyToolbars(void)
{
	m_pParent = NULL;
}

CMyToolbars::~CMyToolbars(void)
{
}

LRESULT CMyToolbars::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	int nX1 = 5;
	int nY1 = 1;
	int nYSize = 20;
	int nSize = 43;

	HWND wnd = NULL;
	wnd = m_buttonFTP.Create(m_hWnd,CRect(nX1,nY1,nX1+nSize,nYSize+nY1),NULL,WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,0,ID_FTP_BUTTON);
	m_buttonFTP.SetBitmaps(m_bmFTP2.LoadBitmap(IDB_FTP2),RGB(0,255,0),m_bmFTP1.LoadBitmap(IDB_FTP1),RGB(0,255,0));

	m_buttonFTP.CreateToolTip(_T("FTP server connections and options."));

	return S_OK;
}

LRESULT CMyToolbars::OnDrawItem(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
{
	LPDRAWITEMSTRUCT lpDrawItemStruct = (LPDRAWITEMSTRUCT)lParam;
	switch (lpDrawItemStruct->CtlID)
	{
		case ID_FTP_BUTTON:
			m_buttonFTP.OnDrawItem(lpDrawItemStruct);
			break;
	} 
	bHandled = false; 
	return S_OK;
}

LRESULT CMyToolbars::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	CRect rect;
	GetClientRect(rect);
	CPaintDC dc(m_hWnd);
	// paint HDC
	COLORREF col = GetSysColor(COLOR_BTNFACE);
	dc.FillSolidRect(rect,col);

	int nX1 = 50;
	int nX2 = nX1 + 50;
	CRect rectText(nX1,0,nX2,rect.bottom);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(0);
	CFont font;
	font.CreatePointFont(80,_T("Arial"));
	HFONT fOld = dc.SelectFont(font);
	dc.DrawText(_T("FTP"),3,rectText,DT_VCENTER|DT_LEFT|DT_SINGLELINE);
	dc.SelectFont(fOld);

	bHandled = true;
	return S_OK;
}

// popup menu
LRESULT CMyToolbars::OnMainMenu(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CMenu menu;
	menu.LoadMenu(IDR_MENU_POPUP);
	CRect rect(0,20,40,40);
	ClientToScreen(rect);
	// if not registered add registration menu's
	if(!IsRegistered())
	{
		menu.GetSubMenu(0).AppendMenu(MF_SEPARATOR);
		menu.GetSubMenu(0).AppendMenu(MF_STRING,ID_REGISTER,"Enter registration code");
		menu.GetSubMenu(0).AppendMenu(MF_STRING,ID_REGISTER_ONLINE,"Purchase registration code");
	}
	menu.GetSubMenu(0).AppendMenu(MF_SEPARATOR);
	// if connected add disconnect menu
	if(!m_pParent->m_strCurrentURL.IsEmpty() && m_pParent->m_strCurrentURL != _T("about:blank"))
		menu.GetSubMenu(0).AppendMenu(MF_STRING,ID_DISCONNECT,"Disconnect");
	// insert last server
	CString strLastServer = MyGetProfileString("LastServer","");
	if(!strLastServer.IsEmpty())
		menu.GetSubMenu(0).AppendMenu(MF_STRING,ID_FTP_CONNECT_TO_LAST_SERVER,"Connect (last used): " + strLastServer);
	// insert all servers in sub menu
	if(MyGetProfileInt("ShowMenuAllServers",1) == 1)
	{
		HMENU popupMenu = ::CreatePopupMenu();
		::InsertMenu(menu.GetSubMenu(0).m_hMenu,2,MF_STRING|MF_POPUP,(UINT)popupMenu,"Connect (all servers):");

		CAddressBookDlg dlg;
		dlg.LoadEntries();	
		for(int n=0;n<dlg.m_straEntries.GetSize();n++)
		{			
			CString strName = ParseXML("Name",dlg.m_straEntries[n]);
			::AppendMenu(popupMenu,MF_STRING,ID_BASE_MENU_UID + n,strName);
		}

		// check option for pop up windows explorer
		UINT nOptions = MF_STRING;
		if(MyGetProfileInt("PopupWinExplorer",1) == 1)
			nOptions |= MF_CHECKED;
		else
			nOptions |= MF_UNCHECKED;
		menu.GetSubMenu(0).AppendMenu(nOptions,ID_MYMENU_POPUP_WIN_EXPLORER,"Popup Windows Explorer");
	}
	::TrackPopupMenu(menu.GetSubMenu(0), TPM_CENTERALIGN|TPM_LEFTBUTTON, rect.left, rect.top, 0, *this, NULL);		

	bHandled = false;
	return S_OK;
}

LRESULT CMyToolbars::OnClickAddressBook(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CAddressBookDlg dlg;
	dlg.m_pParent = this;
	if(dlg.DoModal(m_hWnd) == IDOK)
	{
		if(m_pParent->m_bHasExpired)
		{
			m_pParent->m_nTimer = m_pParent->SetTimer(ID_NAG,300);
			return 0;
		}
		if(m_pParent)
			m_pParent->LoadURL(dlg.m_strURL,dlg.m_strName,dlg.m_strLocalPath);
	}

	return 0L;
}

LRESULT CMyToolbars::OnClickRegister(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_pParent)
		m_pParent->LoadURL(GetRegisterURL());
	return 0L;
}

LRESULT CMyToolbars::OnClickEnterRegistrationCode(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CEnterRegCode dlg;
	if(dlg.DoModal() == IDOK)
		if(IsRegistered())
			m_pParent->m_bHasExpired = false;
	return 0;
}

LRESULT CMyToolbars::OnClickAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CAboutDlg dlg;
	if(dlg.DoModal() == IDYES && m_pParent)
		m_pParent->LoadURL(GetRegisterURL());
	return 0L;
}

LRESULT CMyToolbars::OnClickPopupWinExplorer(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(MyGetProfileInt("PopupWinExplorer",1) == 1)
		MyWriteProfileInt("PopupWinExplorer",0);
	else
		MyWriteProfileInt("PopupWinExplorer",1);
	return 0;
}


LRESULT CMyToolbars::OnClickConnectLastServer(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_pParent->m_bHasExpired)
	{
		m_pParent->m_nTimer = m_pParent->SetTimer(ID_NAG,300);
		return 0;
	}
	CString strLastServer = MyGetProfileString("LastServer","");
	CAddressBookDlg dlg;
	dlg.LoadEntries();
	CString strData = dlg.LookUpDataForName(strLastServer);
	if(!strData.IsEmpty())
	{
		if(dlg.LoadURLData(strData) && m_pParent)
			m_pParent->LoadURL(dlg.m_strURL,dlg.m_strName,dlg.m_strLocalPath);
	}
	else
		MessageBox("There is no address book entry for " + strLastServer, "Error");
	return 0;
}

LRESULT CMyToolbars::OnClickConnectToServer(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_pParent->m_bHasExpired)
	{
		m_pParent->m_nTimer = m_pParent->SetTimer(ID_NAG,300);
		return 0;
	}
	int nPos = wID - ID_BASE_MENU_UID;
	CAddressBookDlg dlg;
	dlg.LoadEntries();	
	if(nPos < dlg.m_straEntries.GetSize())
	{	
		CString strName = ParseXML("Name",dlg.m_straEntries[nPos]);
		CString strData = dlg.LookUpDataForName(strName);
		if(!strData.IsEmpty())
		{
			if(dlg.LoadURLData(strData) && m_pParent)
				m_pParent->LoadURL(dlg.m_strURL,dlg.m_strName,dlg.m_strLocalPath);
		}		
	}
	return 0;
}

// manually change directory
LRESULT CMyToolbars::OnClickChangeDirectoryTo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_pParent == NULL)
		return S_FALSE;
	if(m_pParent->m_strCurrentURL.IsEmpty())
	{
		MessageBox("Please connect to an FTP server first.",APP_NAME,MB_OK);
	}
	else
	{
		CChangeDirToDlg dlg;
		if(dlg.DoModal() == IDOK)
		{
			m_pParent->ChangeFTPDir(dlg.m_strDir);
		}
	}
	return S_OK;
}

// disconnect from FTP site
LRESULT CMyToolbars::OnDisconnect(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_pParent == NULL)
		return S_FALSE;
	if(m_pParent->m_strCurrentURL.IsEmpty())
	{
		MessageBox(_T("Please connect to an FTP server first."),APP_NAME,MB_OK);
	}
	else
	{
		m_pParent->LoadURL(_T("about:blank"));
	}
	return S_OK;
}
