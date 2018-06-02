#if !defined(AFX_FULLSCREENWND_H__54C3D7F7_FB19_4D39_80A9_DCB80FFA9EEA__INCLUDED_)
#define AFX_FULLSCREENWND_H__54C3D7F7_FB19_4D39_80A9_DCB80FFA9EEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FullScreenWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFullScreenWnd window

class CFullScreenWnd : public CWnd
{
// Construction
public:
	CFullScreenWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFullScreenWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFullScreenWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFullScreenWnd)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FULLSCREENWND_H__54C3D7F7_FB19_4D39_80A9_DCB80FFA9EEA__INCLUDED_)
