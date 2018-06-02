#include "StdAfx.h"
#include "ReadToMe.h"
#include "mytoolbars.h"
#include "resource.h"
#include "helpers.h"
#include ".\mytoolbars.h"
#include "EnterRegCode.h"
#include "AboutDlg.h"

CMyToolbars::CMyToolbars(void)
{
	m_pParent = NULL;
}

CMyToolbars::~CMyToolbars(void)
{
}

LRESULT CMyToolbars::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	int nX1 = 0;
	int nY1 = 1;
	int nXSize = 20;
	int nYSize = 20;
	int nSize = 40;

	HWND wnd = NULL;
	wnd = m_buttonReadToMe.Create(m_hWnd,CRect(nX1,nY1,nX1+nSize,nYSize+nY1),NULL,WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,0,ID_READTOME);
	wnd = m_buttonPlay.Create(m_hWnd,CRect(nX1+nSize,nY1,nX1+nSize+nXSize,nYSize+nY1),NULL,WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,0,ID_PLAY);
	wnd = m_buttonPause.Create(m_hWnd,CRect(nX1+nSize+nXSize,nY1,nX1+nSize+nXSize*2,nYSize+nY1),NULL,WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,0,ID_PAUSE);
	wnd = m_buttonStop.Create(m_hWnd,CRect(nX1+nSize+nXSize*2,nY1,nX1+nSize+nXSize*3,nYSize+nY1),NULL,WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,0,ID_STOP);

	m_buttonReadToMe.SetBitmaps(m_bmReadToMe2.LoadBitmap(IDB_READTOMEDOWN),RGB(0,255,0),m_bmReadToMe.LoadBitmap(IDB_READTOMEUP),RGB(0,255,0));
	m_buttonPlay.SetBitmaps(m_bmPlay2.LoadBitmap(IDB_BITMAP_PLAY2),RGB(0,255,0),m_bmPlay.LoadBitmap(IDB_BITMAP_PLAY1),RGB(0,255,0));
	m_buttonPause.SetBitmaps(m_bmPause2.LoadBitmap(IDB_BITMAP_PAUSE1),RGB(0,255,0),m_bmPause.LoadBitmap(IDB_BITMAP_PAUSE),RGB(0,255,0));
	m_buttonStop.SetBitmaps(m_bmStop2.LoadBitmap(IDB_BITMAP_STOP1),RGB(0,255,0),m_bmStop.LoadBitmap(IDB_BITMAP_STOP),RGB(0,255,0));

	if(MyGetProfileInt("ShowToolTips",1) == 1)
	{
		m_buttonReadToMe.CreateToolTip(_T("ReadToMe main menu."));
		m_buttonPlay.CreateToolTip(_T("Speak selected or all text."));
		m_buttonPause.CreateToolTip(_T("Pause speaking."));
		m_buttonStop.CreateToolTip(_T("Stop speaking."));
	}

	return S_OK;
}

LRESULT CMyToolbars::OnDrawItem(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
{
	LPDRAWITEMSTRUCT lpDrawItemStruct = (LPDRAWITEMSTRUCT)lParam;
	switch (lpDrawItemStruct->CtlID)
	{
		case ID_READTOME:
			m_buttonReadToMe.OnDrawItem(lpDrawItemStruct);
			break;
		case ID_PLAY:
			m_buttonPlay.OnDrawItem(lpDrawItemStruct);
			break;
		case ID_PAUSE:
			m_buttonPause.OnDrawItem(lpDrawItemStruct);
			break;
		case ID_STOP:
			m_buttonStop.OnDrawItem(lpDrawItemStruct);
			break;
	}
	bHandled = false;
	return S_OK;
}

LRESULT CMyToolbars::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(IsWindow())
	{
		CRect rect;
		GetClientRect(rect);
		CWindow myWindow;
		myWindow.Attach(m_hWnd);
		PAINTSTRUCT ps;
		HDC hDC  = myWindow.BeginPaint(&ps);
		// paint HDC
		COLORREF col = GetSysColor(COLOR_BTNFACE);
		HBRUSH br = CreateSolidBrush(col);
		HBRUSH brOld = (HBRUSH)SelectObject(hDC,br);
		FillRect(hDC,rect,br);
		SelectObject(hDC,brOld);
		
		DeleteObject(br);
		myWindow.EndPaint(&ps);
		myWindow.Detach();
	}
	return S_OK;
}

// OnPlay speech
LRESULT CMyToolbars::OnPlay(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_pParent)
		m_pParent->OnPlay(wNotifyCode, wID, hWndCtl, bHandled);
	bHandled = false;
	return S_OK;
}

// OnStop speech
LRESULT CMyToolbars::OnStop(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_pParent)
		m_pParent->OnStop(wNotifyCode, wID, hWndCtl, bHandled);
	bHandled = false;
	return S_OK;
}

// OnPause speech
LRESULT CMyToolbars::OnPause(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_pParent)
		m_pParent->OnPause(wNotifyCode, wID, hWndCtl, bHandled);
	bHandled = false;
	return S_OK;
}

// update tooltips
void CMyToolbars::UpdateToolTips(int nShowToolsTips)
{
	if(nShowToolsTips == 1)
	{
		m_buttonReadToMe.CreateToolTip(_T("ReadToMe main menu."));
		m_buttonPlay.CreateToolTip(_T("Speak selected or all text."));
		m_buttonPause.CreateToolTip(_T("Pause speaking."));
		m_buttonStop.CreateToolTip(_T("Stop speaking."));
	}
	else
	{
		m_buttonReadToMe.DestroyToolTip();
		m_buttonPlay.DestroyToolTip();
		m_buttonPause.DestroyToolTip();
		m_buttonStop.DestroyToolTip();
	}
}

// OnSettings
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
	::TrackPopupMenu(menu.GetSubMenu(0), TPM_CENTERALIGN|TPM_LEFTBUTTON, rect.left, rect.top, 0, *this, NULL);		

	bHandled = false;
	return S_OK;
}

// load registration site
LRESULT CMyToolbars::OnClickRegister(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_pParent)
		m_pParent->LoadURL(GetRegisterURL());
	return 0L;
}

// enter reg code
LRESULT CMyToolbars::OnClickEnterRegistrationCode(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CEnterRegCode dlg;
	if(dlg.DoModal() == IDOK)
	{
		if(IsRegistered())
		{
			if(m_pParent)
				m_pParent->m_bHasExpired = false;
		}
	}
	return 0;
}

// Show settings
LRESULT CMyToolbars::OnSettings(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_pParent)
		m_pParent->OnSettings();
	return S_OK;
}

// rewind
LRESULT CMyToolbars::OnRewind(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_pParent)
		m_pParent->OnRewind();
	return S_OK;
}

// fast rewind
LRESULT CMyToolbars::OnFastRewind(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_pParent)
		m_pParent->OnFastRewind();
	return S_OK;
}

// forward
LRESULT CMyToolbars::OnForward(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_pParent)
		m_pParent->OnForward();
	return S_OK;
}

// fast forward
LRESULT CMyToolbars::OnFastForward(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_pParent)
		m_pParent->OnFastForward();
	return S_OK;
}

// show about dialog
LRESULT CMyToolbars::OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CAboutDlg dlg;
	if(dlg.DoModal() == IDYES && m_pParent)
		m_pParent->LoadURL(GetRegisterURL());
	return S_OK;
}

