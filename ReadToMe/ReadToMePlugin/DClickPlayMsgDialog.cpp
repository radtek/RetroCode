// DClickPlayMsgDialog.cpp : Implementation of CDClickPlayMsgDialog

#include "stdafx.h"
#include "DClickPlayMsgDialog.h"


// CDClickPlayMsgDialog

LRESULT CDClickPlayMsgDialog::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rect;
	GetClientRect(rect);

	int nHeight = 64;
	CPaintDC dc(m_hWnd);
	CBrush br;
	br.CreateSolidBrush(RGB(255,255,255));
	HBRUSH bOld = dc.SelectBrush(br);
	dc.FillRect(CRect(0,0,rect.right,nHeight),br);
	dc.SelectBrush(bOld);
	HFONT fOld = dc.SelectFont(m_Font);

	CString strText = _T("IMPORTANT HINT");
	dc.DrawText(strText,strText.GetLength(),CRect(0,20,rect.right,nHeight),DT_CENTER|DT_VCENTER); 
	dc.SelectFont(fOld);

	return S_OK;
}