#if !defined(AFX_MYLISTCTRL_H__7DB35A77_5A9D_4B13_B5A8_A3CD4D86F684__INCLUDED_)
#define AFX_MYLISTCTRL_H__7DB35A77_5A9D_4B13_B5A8_A3CD4D86F684__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window

class CMyListCtrl : public CListCtrl
{
// Construction
public:
	CMyListCtrl();

// Attributes
public:
	LRESULT MySubClassProc( UINT message, WPARAM wParam, LPARAM lParam );
// Operations
public:
	void SwapPositions();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetNormalIconAll();
	void SendListUpdateToApp();
	CString GetPlaySelectedList();
	BOOL m_bDrawIcons;
	int m_nAlignText;
	BOOL m_bDrawBKSelected;
	DWORD m_dwTextColor;
	DWORD m_dwSelectTextColor;
	DWORD m_dwSelectBKColor;
	DWORD m_dwBKColor;

	long m_nJpgBKOriginY;
	long m_nJpgBKOriginX;
	void LoadImage();
	CString m_strImageBK;
	SECJpeg* m_pJpegBK;

	DWORD MakeSelectedString(CString strName,BOOL bSetPlayIcon=false);
	void SetPlayingIcon(DWORD nPos,BOOL bSelect=true);
	void SetNormalIcon(DWORD nPos);
	int GetImageTypeNumber(CString strFile);
	DWORD GetSelectedItem();
	CStringArray* GetSelectedList();

	CWnd*		m_pDropWnd;
	int			m_nDragIndex;
	int			m_nDropIndex;
	CImageList* m_pDragImage;
	BOOL		m_bDragging;
	CImageList	m_Image;

	CStringArray m_straPlayList;
	void ClearPlayList();
	void AddNewFile(CString strFile,BOOL bUpdateApp=true);
	virtual ~CMyListCtrl();

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrl)
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnInsertitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__7DB35A77_5A9D_4B13_B5A8_A3CD4D86F684__INCLUDED_)
