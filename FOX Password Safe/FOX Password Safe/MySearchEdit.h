#pragma once


// CMySearchEdit

class CMySearchEdit : public CEdit
{
	DECLARE_DYNAMIC(CMySearchEdit)

public:
	CMySearchEdit();
	virtual ~CMySearchEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


