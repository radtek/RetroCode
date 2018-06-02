// LeftView.h : interface of the CLeftView class
//


#pragma once

class CFOXPasswordSafeDoc;
#include "CustomPrint.h"

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CFOXPasswordSafeDoc* GetDocument();

// Operations
public:

// Overrides
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	virtual void OnInitialUpdate(); // called first time after construct

	afx_msg void OnMyFilePrint();
	afx_msg void OnMyFilePrintPreview();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CImageList m_ImageList;
	CCustomPrint m_CustomPrint;
	// drag and drop operation
	BOOL m_bDragging;
	// item being dragged
	HTREEITEM	m_itemDrag;
	// handle default cursor
	HCURSOR		m_hCursorOld;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	// insert a header into the tree view
	BOOL InsertHeader(CString strHeader,HTREEITEM& hTree,BOOL bHasExpired, long lArrayPos);
	// empty tree view list
	void ClearList(void);
	// timer to update initial view
	UINT_PTR m_TimerUpdate;
	// insert password entry into parent tree node
	BOOL InsertChildItem(CString strParams,HTREEITEM hItemParent,BOOL bHasExpired,long lArrayPos);
	HTREEITEM InsertHeader(CString strHeaderText,BOOL bHasExpired,long lArrayPos);
	// return the selected tree array position 
	long GetSelectedArrayPos(void);
	bool m_bIsActivated;
protected:
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	// move item to new location
	void MoveTreeItem(HTREEITEM htiSource,HTREEITEM htiTarget);
public:	
	// open tree view to this selection
	void SetCurrentSelection(CString strHeader,CString strDescription);
	// set encrypted item image
	void SetItemImageEncrypted(BOOL bEncrypted);
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CFOXPasswordSafeDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CFOXPasswordSafeDoc*>(m_pDocument); }
#endif

