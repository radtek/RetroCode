#pragma once

#include "Picture.h"
// CMyButton

class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)

public:
	CMyButton();
	virtual ~CMyButton();

protected:
	CFont m_font;
	CBitmap m_Image;
	CBitmap m_ImageDown;
	CToolTipCtrl m_ToolTip;

	DECLARE_MESSAGE_MAP()
public:
	BOOL LoadImage(UINT nResourceID);
	BOOL m_bImageLoaded;
	BOOL m_bImageDownLoaded;
	BOOL LoadImageDown(UINT nResourceID);

	// text color
	COLORREF m_crTextColor;
	// custom button color
	COLORREF m_crCustomColor;
	BOOL m_bUseCustColor;
	void SetRGBCustomColor(COLORREF rgb);
	// use gradient color fill
	BOOL m_bUseGradientFill;

	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// set tool tip for this button
	void SetToolTip(CString strText);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


