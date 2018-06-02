#if !defined(AFX_MYSTATIC_H__4A47C3B1_7B15_4D12_9E77_4B957F2B214F__INCLUDED_)
#define AFX_MYSTATIC_H__4A47C3B1_7B15_4D12_9E77_4B957F2B214F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyStatic window

class CMyStatic : public CStatic
{
// Construction
public:
	CMyStatic();

// Attributes
public:
	void SetColor(DWORD dwColor);
	CBrush m_brush;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD m_dwTextColor;
	virtual ~CMyStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATIC_H__4A47C3B1_7B15_4D12_9E77_4B957F2B214F__INCLUDED_)
