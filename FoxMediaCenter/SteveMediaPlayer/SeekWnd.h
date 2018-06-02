#if !defined(AFX_SEEKWND_H__0B1470B6_2B39_4EAD_9764_D9EE98B24065__INCLUDED_)
#define AFX_SEEKWND_H__0B1470B6_2B39_4EAD_9764_D9EE98B24065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SeekWnd.h : header file
//
#include "MySeekSliderWnd.h"
class CSteveMediaPlayerCtrl;
/////////////////////////////////////////////////////////////////////////////
// CSeekWnd window

class CSeekWnd : public CWnd
{
// Construction
public:
	CSeekWnd();

// Attributes
public:
	CMySeekSliderWnd	m_wndSlider;
	CSteveMediaPlayerCtrl* m_pMain;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeekWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Init();
	void UpdatePosition(DWORD dwPos);
	DWORD GetMin();
	DWORD GetMax();
	DWORD GetPosition();
	void SetPosition(DWORD dwPos);
	virtual ~CSeekWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSeekWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEEKWND_H__0B1470B6_2B39_4EAD_9764_D9EE98B24065__INCLUDED_)
