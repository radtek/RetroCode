#pragma once

#include "MyBmButton.h"
#include "MySearchEdit.h"
// CSearchBarWnd

class CSearchBarWnd : public CWnd
{
	DECLARE_DYNAMIC(CSearchBarWnd)

public:
	CSearchBarWnd();
	virtual ~CSearchBarWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();

	CMyBmButton m_ctlSearch;
	CBitmap		m_bmSearch1;
	CBitmap		m_bmSearch2;

	CMyBmButton m_ctlShowAll;
	CBitmap		m_bmShowAll1;
	CBitmap		m_bmShowAll2;

	CMySearchEdit		m_ctlEdit;
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	CString GetSearchText(void);
	void SetEditFocus(void);
};


