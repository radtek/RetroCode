// MyTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "MyTreeCtrl.h"
#include "PlayListManager.h"
#include "helpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl

CMyTreeCtrl::CMyTreeCtrl()
{
	m_pDragImage = new CImageList;
	m_bDragging = FALSE;
}

CMyTreeCtrl::~CMyTreeCtrl()
{
	if(m_pDragImage)
		delete m_pDragImage;
}


BEGIN_MESSAGE_MAP(CMyTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CMyTreeCtrl)
	ON_WM_DROPFILES()
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, OnKeydown)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl message handlers

int CMyTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CMyTreeCtrl::Init()
{
	BOOL bOK = m_pDragImage->Create(16, 13, TRUE, 3, 1);
	CBitmap bm;
	bm.LoadBitmap (IDB_DRAG);
	m_pDragImage->Add(&bm, RGB (255, 0, 255));
	SetImageList(m_pDragImage, TVSIL_NORMAL);

	return true;
}

void CMyTreeCtrl::OnDropFiles(HDROP hDropInfo) 
{
	UINT nFiles = DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);

	CPoint pt;
	DragQueryPoint(hDropInfo,&pt);
	UINT nFlags;
	HTREEITEM item = HitTest(pt,&nFlags);
	if(item == NULL)
		item = GetSelectedItem();

	CString strFile;
    for(UINT n=0;n<nFiles;n++)
    {
        DragQueryFile(hDropInfo,n,strFile.GetBuffer(MAX_PATH),MAX_PATH);
		strFile.ReleaseBuffer();
		AddNewFile(strFile,item,true);
    }
	
	CTreeCtrl::OnDropFiles(hDropInfo);
}

HTREEITEM CMyTreeCtrl::AddNewFile(CString strFile, HTREEITEM item,BOOL bExpand,BOOL bInsertFirst)
{
	HTREEITEM hNew = NULL;
	HTREEITEM iParent = GetParentItem(item);
	CString strName = strFile.Mid(strFile.ReverseFind('\\')+1);

	m_straFullPathLists.Add(strFile);
	long nPos = m_straFullPathLists.GetSize() -1;

	// not root item
	if(iParent)
	{
		hNew = InsertItem(TVIF_IMAGE|TVIF_TEXT|TVIF_STATE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
				strName.GetBuffer(strName.GetLength()),
				1,1, 0, 0, nPos, iParent,bInsertFirst?TVI_FIRST:item);
			strName.ReleaseBuffer();		

	}
	else // root item 
	{
		hNew = InsertItem(TVIF_IMAGE|TVIF_TEXT|TVIF_STATE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
				strName.GetBuffer(strName.GetLength()),
				1,1, 0, 0, nPos, item,NULL);
			strName.ReleaseBuffer();		
	}

	if(bExpand)
		Expand(iParent?iParent:item,TVE_EXPAND);

	return hNew;
}

void CMyTreeCtrl::AddRootItem(CString strName,BOOL bSelect)
{
	if(strName.IsEmpty())
		return;

	TVINSERTSTRUCT insert;
	ZeroMemory(&insert,sizeof(TVINSERTSTRUCT));
	insert.hParent = TVI_ROOT;
	insert.hInsertAfter = TVI_LAST;
	TVITEMEX itemx;
	ZeroMemory(&itemx,sizeof(TVITEMEX));
	itemx.mask = TVIF_IMAGE|TVIF_TEXT|TVIF_STATE|TVIF_CHILDREN|TVIF_SELECTEDIMAGE;
	itemx.pszText = strName.GetBuffer(strName.GetLength());
	itemx.iImage = 0;
	itemx.iSelectedImage = 0;
	itemx.cChildren = 1;
	
	insert.itemex = itemx;
	HTREEITEM iParent = InsertItem(&insert);
	strName.ReleaseBuffer();

	CPlayListManager list;
	CStringArray* pstra = list.GetEntriesForName(strName,true);
	HTREEITEM item;
	for(int n=0;n<pstra->GetSize();n++)
	{
		CString strTemp = pstra->GetAt(n);
		CString strEntry;
		if(strTemp == RANDOM_ENTRY_NAME)
		{
			strEntry = strTemp;
		}
		else
		{
			m_straFullPathLists.Add(ParseXML("FullPath",strTemp));
			strEntry = ParseXML("Name",strTemp);
		}
		item = InsertItem(TVIF_IMAGE|TVIF_TEXT|TVIF_STATE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
				strEntry.GetBuffer(strEntry.GetLength()),
				1,1, 0, 0, (LPARAM)m_straFullPathLists.GetSize()-1, iParent,TVI_LAST);
			strEntry.ReleaseBuffer();		
	}
	delete pstra;

	if(bSelect)
	{
		SelectItem(iParent);
		Expand(iParent,TVE_EXPAND);
		EnsureVisible(iParent);
	} 
}

void CMyTreeCtrl::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	*pResult = 0;

	WORD wKey = pLVKeyDow->wVKey;
	// 46 delete
	if(wKey==46)
	{
		HTREEITEM hItem = GetSelectedItem();
		HTREEITEM hParent = GetParentItem(hItem);

		CString strPlayList = hParent?GetItemText(hParent):GetItemText(hItem);
		DeleteItem(hItem);
	}
}

void CMyTreeCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	m_nDragIndex = pNMTreeView->itemNew.hItem;

	// create a drag image
	BOOL bOK = m_pDragImage->BeginDrag(1, CPoint (8, 8));
	m_pDragImage->DragEnter(GetDesktopWindow(), pNMTreeView->ptDrag);
	// set dragging flag
	m_bDragging = TRUE;
	m_nDropIndex = NULL;
	m_pDropWnd = this;
	// capture all mouse messages
	SetCapture ();

	*pResult = 0;}

void CMyTreeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bDragging)
	{
		CPoint pt (point);
		ClientToScreen (&pt);
		// move the drag image
		VERIFY (m_pDragImage->DragMove(pt));
		// unlock window updates
		VERIFY (m_pDragImage->DragShowNolock (FALSE));
		// get the CWnd pointer of the window that is under the mouse cursor
		CWnd* pDropWnd = WindowFromPoint (pt);
		ASSERT (pDropWnd);
		// if we drag outside current window
		if (pDropWnd != m_pDropWnd)
		{
			// turn off hilight for drop target in list control
			if(m_nDropIndex)
			{
				CTreeCtrl* pList = (CTreeCtrl*)m_pDropWnd;
				VERIFY (pList->SetItemState (m_nDropIndex, 0, LVIS_DROPHILITED));
				// redraw item
				//pList->InvalidateRect(NULL);
				pList->UpdateWindow ();
				m_nDropIndex = NULL;
			}
		}
		// save current window pointer
		m_pDropWnd = pDropWnd;

		// convert from screen coordinates to drop target client coordinates
		pDropWnd->ScreenToClient (&pt);

		if (pDropWnd->IsKindOf (RUNTIME_CLASS (CTreeCtrl)))
		{			
			UINT uFlags;
			CTreeCtrl* pList = (CTreeCtrl*)pDropWnd;

			// turn off hilight for previous drop target
			pList->SetItemState (m_nDropIndex, 0, LVIS_DROPHILITED);
		
			// get the item that is below cursor
			m_nDropIndex = ((CTreeCtrl*)pDropWnd)->HitTest (pt, &uFlags);
			// highlight it
			pList->SetItemState (m_nDropIndex, LVIS_DROPHILITED, LVIS_DROPHILITED);
			// redraw item
			//pList->InvalidateRect(NULL);
			pList->UpdateWindow ();
		}
		// lock window updates
		VERIFY (m_pDragImage->DragShowNolock (TRUE));
	}
	CTreeCtrl::OnMouseMove(nFlags, point);
}

void CMyTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bDragging)
	{
		// release mouse capture
		VERIFY (::ReleaseCapture());
		m_bDragging = FALSE;
		// end dragging
		VERIFY (m_pDragImage->DragLeave(GetDesktopWindow()));
		m_pDragImage->EndDrag();

		CPoint pt (point);
		ClientToScreen (&pt);
		// get the CWnd pointer of the window that is under the mouse cursor
		CWnd* pDropWnd = WindowFromPoint(pt);
		ASSERT (pDropWnd);
		// if window is this
		if(pDropWnd == this)
		{
			SwapPositions();
		}
	}
	CTreeCtrl::OnLButtonUp(nFlags, point);
}

void CMyTreeCtrl::SwapPositions()
{
	BOOL bGood = true;
	
	if(!m_nDragIndex || !m_nDropIndex)
		bGood = false;
	if(m_nDragIndex == m_nDropIndex)
		bGood = false;
	if(!GetParentItem(m_nDragIndex))
		bGood = false;

	if(!bGood)
	{
		SetItemState(m_nDragIndex, 0, LVIS_DROPHILITED);
		SetItemState(m_nDragIndex, 0, LVIS_SELECTED);	
		SetItemState(m_nDropIndex, 0, LVIS_DROPHILITED);
		SetItemState(m_nDropIndex, 0, LVIS_SELECTED);
		return;
	}

	SetItemState(m_nDragIndex, 0, LVIS_DROPHILITED);
	SetItemState(m_nDragIndex, 0, LVIS_SELECTED);	

	// move item
	CString strFile = m_straFullPathLists.GetAt(GetItemData(m_nDragIndex));
	HTREEITEM hTree = GetPrevSiblingItem(m_nDropIndex);
	if(!GetParentItem(m_nDropIndex))
		hTree = NULL;

	HTREEITEM hNew = AddNewFile(strFile,hTree ? hTree:m_nDropIndex,hTree?false:true);

	DeleteItem(m_nDragIndex);
	m_nDragIndex = NULL;

	SetItemState(m_nDropIndex, 0, LVIS_DROPHILITED);

	SelectItem(hNew);
	EnsureVisible(hNew);
}

CString CMyTreeCtrl::GetSelectPlayList()
{
	HTREEITEM hTree = GetSelectedItem();
	if(GetParentItem(hTree))
		hTree = GetParentItem(hTree);
	CString strName = GetItemText(hTree);

	return strName;
}

CString CMyTreeCtrl::GetSelectedFile()
{
	HTREEITEM hTree = GetSelectedItem();
	if(!GetParentItem(hTree))
		hTree = GetChildItem(hTree);
	CString strName = GetItemText(hTree);

	return strName;
}

CStringArray* CMyTreeCtrl::GetRootPlayLists()
{
	CStringArray* pstra = new CStringArray;
	HTREEITEM hTree = GetRootItem();
	CString strName = GetItemText(hTree);
	pstra->Add(strName);
	while((hTree = GetNextSiblingItem(hTree)) != NULL)	
	{
		strName = GetItemText(hTree);
		pstra->Add(strName);
	}

	return pstra;
}

CStringArray* CMyTreeCtrl::GetChildPlayListItems(CString strRoot)
{
	CStringArray* pstra = new CStringArray;

	HTREEITEM hTree = GetRootItem();
	CString strName = GetItemText(hTree);
	BOOL bFound = (strRoot == strName);

	while(!bFound && (hTree = GetNextSiblingItem(hTree)) != NULL)	
	{
		strName = GetItemText(hTree);
		bFound = (strRoot == strName);		
	}
	if(bFound)
	{
		HTREEITEM hChildItem = GetChildItem(hTree);
		while(hChildItem != NULL)
		{
			DWORD dwPos = GetItemData(hChildItem);
			if(dwPos < m_straFullPathLists.GetSize())
				pstra->Add(m_straFullPathLists.GetAt(dwPos));
			hChildItem = GetNextItem(hChildItem, TVGN_NEXT);
		}
	}
	return pstra;
}

void CMyTreeCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	GetParent()->PostMessage(WM_PLAY_SELECTED);
}

BOOL CMyTreeCtrl::IsSelectedRoot()
{
	HTREEITEM hTree = GetSelectedItem();
	return (!GetParentItem(hTree));
}
