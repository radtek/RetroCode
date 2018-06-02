#if !defined(AFX_MYSEEKSLIDERWND_H__935E9C39_44BF_4432_8D56_1F8F8CE533BA__INCLUDED_)
#define AFX_MYSEEKSLIDERWND_H__935E9C39_44BF_4432_8D56_1F8F8CE533BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySeekSliderWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMySeekSliderWnd window
class CSeekWnd;

class CMySeekSliderWnd : public CWnd
{
// Construction
public:
	CMySeekSliderWnd();

// Attributes
public:
	CSeekWnd* m_pParent;

	void SetPos(ULONG lPos,BOOL bSeek=true);
	ULONG GetPos();

	DWORD m_dwMax;
	DWORD m_dwMin;

// Operations
public:
	CString m_strText;
	DWORD m_dwLineColor;
	DWORD m_dwBkColor;
	void Init();
	int m_nVol_Start;
	int m_nVold_Width;
	long m_lSliderPos;
	BOOL m_bMouseDown;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySeekSliderWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_strMin;
	CString m_strMax;
	void UpdatePosition(DWORD dwSecs);
	virtual ~CMySeekSliderWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMySeekSliderWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSEEKSLIDERWND_H__935E9C39_44BF_4432_8D56_1F8F8CE533BA__INCLUDED_)
