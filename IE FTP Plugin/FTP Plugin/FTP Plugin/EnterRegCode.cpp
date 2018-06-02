// EnterRegCode.cpp : Implementation of CEnterRegCode

#include "stdafx.h"
#include "EnterRegCode.h"


// CEnterRegCode

LRESULT CEnterRegCode::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CRect rect;
	GetClientRect(rect);
	CPaintDC dc(m_hWnd);
	// paint HDC
	COLORREF col = GetSysColor(COLOR_BTNFACE);
	dc.FillSolidRect(rect,col);

	return 0;
}
