#pragma once


// CMyIconEdit
#include "MyEdit.h"


class CMyIconEdit : public CWnd
{
	DECLARE_DYNAMIC(CMyIconEdit)

public:
	CMyIconEdit();
	virtual ~CMyIconEdit();

	// show an icon button at the end of the text
	void ShowButton(UINT imageDown, UINT imageUp, int nImageLength, int nImageHeight, UINT buttonFunction, CRect* pRectPos = NULL);
	CMyEdit m_Edit;
protected:
	DECLARE_MESSAGE_MAP()

	CMyButton* m_pButtonIcon;
	int m_nButtonFunction;

	afx_msg void OnButtonClick();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// custom create function
	BOOL MyCreate(DWORD style, CRect rect, CWnd* pParent);
	// get width size of text and icon 
	int GetSizeX(void);
	// set edit text
	void SetText(CString);
	// left position of icon
	int m_nIconXPos;
	void SetPasswordChar(char nChar);
	// hides icon from window
	void HideIconButton(void);
	// set buttons tool tip
	void SetToolTip(CString strText);
	// get max text
	CString GetCompactText(CString strText) { return m_Edit.GetCompactText(strText); }
};


