#if !defined(AFX_MYMESSAGEWND_H__9D4C89EC_D849_42D6_A277_BDA150E33173__INCLUDED_)
#define AFX_MYMESSAGEWND_H__9D4C89EC_D849_42D6_A277_BDA150E33173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyMessageWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyMessageWnd window


class CMyMessageWnd : public CWnd
{
// Construction
public:
	CMyMessageWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMessageWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	CWnd* m_pParent;
	virtual ~CMyMessageWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyMessageWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMESSAGEWND_H__9D4C89EC_D849_42D6_A277_BDA150E33173__INCLUDED_)
