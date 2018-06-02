// NagDlg.cpp : Implementation of CNagDlg

#include "stdafx.h"
#include "NagDlg.h"
#include "EnterRegCode.h"

// CNagDlg


LRESULT CNagDlg::OnClickedButton_enter_number(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CEnterRegCode dlg;
	dlg.DoModal();	
	EndDialog(IDOK);
	return 0;
}

LRESULT CNagDlg::OnClickedButton_register(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(IDYES);
	return 0;
}

LRESULT CNagDlg::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CRect rect;
	GetClientRect(rect);
	CPaintDC dc(m_hWnd);
	// paint HDC
	COLORREF col = GetSysColor(COLOR_BTNFACE);
	dc.FillSolidRect(rect,col);
	return 0;
}

LRESULT CNagDlg::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	EndDialog(IDCANCEL);
	return 0;
}
