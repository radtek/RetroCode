#if !defined(AFX_MYTREECTRL_H__8BE5CF20_A9EE_41D7_8240_DC48322F976F__INCLUDED_)
#define AFX_MYTREECTRL_H__8BE5CF20_A9EE_41D7_8240_DC48322F976F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl window

class CMyTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CMyTreeCtrl();

// Attributes
public:

// Operations
public:
	void AddRootItem(CString strName,BOOL bSelect);
	void SwapPositions();
	BOOL Init();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL IsSelectedRoot();
	CStringArray* GetChildPlayListItems(CString strRoot);
	CStringArray* GetRootPlayLists();
	CString GetSelectPlayList();
	CString GetSelectedFile();
	CStringArray m_straFullPathLists;
	HTREEITEM AddNewFile(CString strFile,HTREEITEM item,BOOL bExpand=false,BOOL bInsertFirst=false);
	virtual ~CMyTreeCtrl();

	CWnd*		m_pDropWnd;
	HTREEITEM	m_nDragIndex;
	HTREEITEM	m_nDropIndex;
	CImageList* m_pDragImage;
	BOOL		m_bDragging;
	CImageList	m_Image;

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTreeCtrl)
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREECTRL_H__8BE5CF20_A9EE_41D7_8240_DC48322F976F__INCLUDED_)
