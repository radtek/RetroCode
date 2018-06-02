#pragma once
#include "mybutton.h"


// CMyDlgBar

class CMyDlgBar : public CDialogBar
{
	DECLARE_DYNAMIC(CMyDlgBar)

public:
	CMyDlgBar();
	virtual ~CMyDlgBar();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	CMyButton m_butNew;
	CMyButton m_butOpen;
	CMyButton m_butLoadURL;
	CMyButton m_butCopyUser;
	CMyButton m_butCopyPass;
	CMyButton m_butClearClip;
};


