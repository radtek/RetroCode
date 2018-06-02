#if !defined(AFX_MYBITMAPBUTTON_H__C14B4121_77EF_11D3_BAD1_0060082DB2A6__INCLUDED_)
#define AFX_MYBITMAPBUTTON_H__C14B4121_77EF_11D3_BAD1_0060082DB2A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyBitMapButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyBitMapButton window


class CMyBitMapButton : public CButton
{
// Construction
public:
	CMyBitMapButton();
	CBitmap* m_pImg;
	CBitmap* m_pImg2;
	CBitmap* m_pImg3;

	CToolTipCtrl m_ToolTip;
	HCURSOR m_hCursor;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyBitMapButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bDontShowHand;
	void SetToolTip(UINT nText);
	void LoadImage(UINT nIDResource);
	void LoadImageDown(UINT nIDResource);
	void LoadImageGhost(UINT nIDResource);


	virtual ~CMyBitMapButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyBitMapButton)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBITMAPBUTTON_H__C14B4121_77EF_11D3_BAD1_0060082DB2A6__INCLUDED_)
