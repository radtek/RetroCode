#pragma once

// CMyEdit
#include "MyButton.h"
#include "shlwapi.h"

class CMyEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyEdit)

public:
	CMyEdit();
	virtual ~CMyEdit();

protected:
	DECLARE_MESSAGE_MAP()
	CBrush m_brush;
	CFont* m_pfont;
public:
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	// create font for this control
	void SetFont(CString strTypeFace="Times New Roman", int nSize=12, bool bBold=false);

	CString GetCompactText(CString strText) 
	{
		CRect rect;
		GetClientRect(rect);
		CDC* pDC = GetDC();
		PathCompactPath(pDC->GetSafeHdc(),strText.GetBuffer(strText.GetLength()),rect.Width());
		strText.ReleaseBuffer();
		ReleaseDC(pDC);
		return strText;
	}
};


