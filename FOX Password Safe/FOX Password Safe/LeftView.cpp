// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "FOX Password Safe.h"

#include "FOX Password SafeDoc.h"
#include "LeftView.h"
#include ".\leftview.h"
#include "MainFrm.h"
#include "helpers.h"
#include "PrintSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	// Standard printing commands
	ON_COMMAND(ID_MY_FILE_PRINT, OnMyFilePrint)
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnMyFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnMyFilePrintPreview)
	ON_WM_TIMER()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnTvnSelchanged)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnTvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CLeftView construction/destruction
CLeftView::CLeftView()
: m_TimerUpdate(0)
, m_bIsActivated(false)
{
	m_bDragging = false;
	m_itemDrag = NULL;
	m_hCursorOld = NULL;
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnDraw(CDC* /*pDC*/)
{
	CFOXPasswordSafeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	if(!m_bIsActivated)
	{
		m_bIsActivated = true;
		CTreeCtrl& treeCtrl = GetTreeCtrl();
		LONG lStyles = ::GetWindowLong(treeCtrl.m_hWnd, GWL_STYLE);
		lStyles |= (TVS_SHOWSELALWAYS | TVS_HASBUTTONS | TVS_LINESATROOT);
		::SetWindowLong(treeCtrl.m_hWnd, GWL_STYLE, lStyles);

		m_ImageList.Create(16, 16, ILC_MASK|ILC_COLOR16, 0, 4);
		CBitmap bm;
		bm.LoadBitmap(IDB_IMAGELIST2);
		m_ImageList.Add(&bm,RGB(0,128,128));
		treeCtrl.SetImageList(&m_ImageList,TVSIL_NORMAL); 

		CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
		pMain->PostMessage(WM_STARTUP);
	}
}

// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CFOXPasswordSafeDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFOXPasswordSafeDoc)));
	return (CFOXPasswordSafeDoc*)m_pDocument;
}
#endif //_DEBUG

// empty tree view list
void CLeftView::ClearList(void)
{
	GetTreeCtrl().DeleteAllItems();
}

void CLeftView::OnTimer(UINT nIDEvent)
{
	CTreeView::OnTimer(nIDEvent);	
}

// insert a header into the tree view
HTREEITEM CLeftView::InsertHeader(CString strHeaderText,BOOL bHasExpired,long lArrayPos)
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	HTREEITEM hItem = treeCtrl.GetNextItem(TVI_ROOT, TVGN_CHILD);
	while(hItem)
	{
		CString strText = treeCtrl.GetItemText(hItem);
		if(strHeaderText.CompareNoCase(strText) == 0)
		{
			if(bHasExpired)
				treeCtrl.SetItemImage(hItem,3,12);
			return hItem;
		}
		hItem = treeCtrl.GetNextItem(hItem, TVGN_NEXT);
	}
	TVINSERTSTRUCT tvIns;
	ZeroMemory(&tvIns,sizeof(TVINSERTSTRUCT));
	tvIns.hParent = NULL;
	tvIns.hInsertAfter = TVI_LAST;
	tvIns.itemex.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
	tvIns.itemex.pszText = (LPSTR)strHeaderText.GetBuffer(strHeaderText.GetLength());
	tvIns.itemex.iImage = bHasExpired?3:0;
	tvIns.itemex.iSelectedImage = bHasExpired?12:1;
	tvIns.itemex.lParam = lArrayPos;

	hItem = treeCtrl.InsertItem(&tvIns);
	strHeaderText.ReleaseBuffer();

	return hItem;
}

// insert a header into the tree view
BOOL CLeftView::InsertHeader(CString strHeaderText,HTREEITEM& hItem,BOOL bHasExpired,long lArrayPos)
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	hItem = treeCtrl.GetNextItem(TVI_ROOT, TVGN_CHILD);
	while(hItem)
	{
		CString strText = treeCtrl.GetItemText(hItem);
		if(strHeaderText.CompareNoCase(strText) == 0)
		{
			if(bHasExpired)
				treeCtrl.SetItemImage(hItem,3,12);
			return false;
		}
		hItem = treeCtrl.GetNextItem(hItem, TVGN_NEXT);
	}
	TVINSERTSTRUCT tvIns;
	ZeroMemory(&tvIns,sizeof(TVINSERTSTRUCT));
	tvIns.hParent = NULL;
	tvIns.hInsertAfter = TVI_LAST;
	tvIns.itemex.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
	tvIns.itemex.pszText = (LPSTR)strHeaderText.GetBuffer(strHeaderText.GetLength());
	tvIns.itemex.iImage = bHasExpired?3:0;
	tvIns.itemex.iSelectedImage = bHasExpired?12:1;
	tvIns.itemex.lParam = lArrayPos;

	hItem = treeCtrl.InsertItem(&tvIns);
	strHeaderText.ReleaseBuffer();

	return true;
}

// insert password entry into parent tree node
BOOL CLeftView::InsertChildItem(CString strParams,HTREEITEM hItemParent,BOOL bHasExpired,long lArrayPos)
{
	CString strName = ParseXML("Description",strParams);
	if(strName.IsEmpty())
		return false;

	CTreeCtrl& treeCtrl = GetTreeCtrl();
	TVINSERTSTRUCT tvIns;
	ZeroMemory(&tvIns,sizeof(TVINSERTSTRUCT));
	tvIns.hParent = hItemParent;
	tvIns.hInsertAfter = TVI_LAST;
	tvIns.itemex.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
	tvIns.itemex.pszText = (LPSTR)strName.GetBuffer(strName.GetLength());
	// check if encrypted file
	if(IsEncryptedFileEntry(strParams))
	{
		BOOL bEnc = IsFileEncrypted(strParams);
		tvIns.itemex.iImage = bEnc?15:14;
		tvIns.itemex.iSelectedImage = bEnc?15:14;
	}
	else
	{
		tvIns.itemex.iImage = bHasExpired?13:5;
		tvIns.itemex.iSelectedImage = bHasExpired?13:5;
	}
	tvIns.itemex.lParam = lArrayPos;

	HTREEITEM hItem = treeCtrl.InsertItem(&tvIns);
	strName.ReleaseBuffer();	
	return true;
}

// return the selected tree array position 
long CLeftView::GetSelectedArrayPos(void)
{
	long lArrayPos = -1;
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	HTREEITEM hItem = treeCtrl.GetSelectedItem();
	if(hItem != NULL)
	{
		lArrayPos = (long)treeCtrl.GetItemData(hItem);
	}
	return lArrayPos;
}

// CLeftView printing
BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	m_CustomPrint.OnPreparePrinting(pInfo);
	BOOL bOK = DoPreparePrinting(pInfo);
	return bOK;
}

void CLeftView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	m_CustomPrint.OnBeginPrinting(pDC, pInfo);
}

void CLeftView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	m_CustomPrint.OnEndPrinting(pDC, pInfo);
}

void CLeftView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	m_CustomPrint.OnPrint(pDC, pInfo);
}

void CLeftView::OnMyFilePrint()
{
	CPrintSelectDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
		// clear entries from array
		m_CustomPrint.ClearArray();

		m_CustomPrint.m_pCtrlWnd = this;
		m_CustomPrint.m_PrintDatabasePassword = dlg.m_PrintDatabasePassword;
		m_CustomPrint.m_bCategory = dlg.m_bCategory;
		m_CustomPrint.m_bDescription = dlg.m_bDescription;
		m_CustomPrint.m_bPrintUserID = dlg.m_bUsername;
		m_CustomPrint.m_bPrintPass = dlg.m_bPassword;
		m_CustomPrint.m_bPrintURL = dlg.m_bWebSite;
		m_CustomPrint.m_bPrintNotes = false;

		// load array with entries selected
		if(dlg.m_bPrintSingleItem == 0) // 0 = selected
		{
			if(!pMain->GetSingleSelectedItemData((LPVOID)&m_CustomPrint))
				return;
		}
		else if(dlg.m_bPrintAll == 0)
		{
			if(!pMain->GetAllItemData((LPVOID)&m_CustomPrint))
				return;
		}
		else if(!pMain->GetSelectedItemData((LPVOID)&m_CustomPrint))
		{
			return;
		}
		// work out largest text size
		m_CustomPrint.SetLargestColumnSize();

		CTreeView::OnFilePrint();
	}
}

void CLeftView::OnMyFilePrintPreview()
{
	CPrintSelectDlg dlg;
	if(dlg.DoModal() == IDOK)
	{		
		CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
		// clear entries from array
		m_CustomPrint.ClearArray();

		m_CustomPrint.m_pCtrlWnd = this;
		m_CustomPrint.m_PrintDatabasePassword = dlg.m_PrintDatabasePassword;
		m_CustomPrint.m_bCategory = dlg.m_bCategory;
		m_CustomPrint.m_bDescription = dlg.m_bDescription;
		m_CustomPrint.m_bPrintUserID = dlg.m_bUsername;
		m_CustomPrint.m_bPrintPass = dlg.m_bPassword;
		m_CustomPrint.m_bPrintURL = dlg.m_bWebSite;
		m_CustomPrint.m_bPrintNotes = false;

		// load array with entries selected
		if(dlg.m_bPrintSingleItem == 0) // 0 = selected
		{
			if(!pMain->GetSingleSelectedItemData((LPVOID)&m_CustomPrint))
				return;
		}
		else if(dlg.m_bPrintAll == 0)
		{
			if(!pMain->GetAllItemData((LPVOID)&m_CustomPrint))
				return;
		}
		else if(!pMain->GetSelectedItemData((LPVOID)&m_CustomPrint))
		{
			return;
		}
		// work out largest text size
		m_CustomPrint.SetLargestColumnSize();

		CTreeView::OnFilePrintPreview();
	}
}

void CLeftView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CTreeView::OnRButtonDown(nFlags, point);
	
	ClientToScreen(&point);
	CMenu menu;
	BOOL bOK = menu.CreatePopupMenu();

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	long lArrayPos = GetSelectedArrayPos();
	CString strEntry = pMain->GetStringEntry(lArrayPos);
	if(IsEncryptedFileEntry(strEntry))
	{
		if(IsFileEncrypted(strEntry))
			bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_UNENCRYPTFILEENTRY, "Unencrypt file entry");
		else
			bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_ENCRYPTFILEENTRY, "Encrypt file entry");
		bOK = menu.AppendMenu(MF_SEPARATOR, NULL, "");
		bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_EDITSELECTEDENTRY, "Edit Selected Entry");
		bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_DELETESELECTEDCATEGORY, "Delete Selected Item");
	}
	else
	{
		bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_COPY, "Copy Username to Clipboard");
		bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_COPYPASSWORDTOCLIPBOARD, "Copy Password to Clipboard");
		bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_EMPTYPASSWORDFROMCLIPBOARD, "Empty Password from Clipboard");
		bOK = menu.AppendMenu(MF_SEPARATOR, NULL, "");
		bOK = menu.AppendMenu(MF_POPUP, ID_FILE_ADDNEWCATEGORY, "Create New Category");
		bOK = menu.AppendMenu(MF_POPUP, ID_FILE_ADDNEWENTRY, "Create New Entry");
		bOK = menu.AppendMenu(MF_SEPARATOR, NULL, "");
		bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_EDITSELECTEDCATEGORY, "Edit Selected Category");
		bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_EDITSELECTEDENTRY, "Edit Selected Entry");
		bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_DELETESELECTEDCATEGORY, "Delete Selected Item");
	}
	::TrackPopupMenu(menu.m_hMenu,TPM_CENTERALIGN|TPM_RIGHTBUTTON, point.x, point.y,NULL,AfxGetMainWnd()->m_hWnd,NULL);
}

// open tree view to this selection
void CLeftView::SetCurrentSelection(CString strHeader,CString strDescription)
{
	// root item
	if(strHeader.IsEmpty())
	{
		strHeader = strDescription;
		strDescription = "";
	}
	// Look at all of the root-level items
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	HTREEITEM hCurrent = treeCtrl.GetRootItem();
	HTREEITEM hRoot = NULL;
	while (hCurrent != NULL)
	{
		TVITEM item;
		TCHAR szText[1024];
		item.hItem = hCurrent;
		item.mask = TVIF_TEXT | TVIF_HANDLE;
		item.pszText = szText;
		item.cchTextMax = 1024;
		treeCtrl.GetItem(&item);
		if(strHeader == item.pszText)
		{
			hRoot = item.hItem;
			treeCtrl.SelectItem(item.hItem);
			break;	
		}
		hCurrent = treeCtrl.GetNextItem(hCurrent, TVGN_NEXT);
	}
	// look at all child items to select
	if(!strDescription.IsEmpty())
	{
		hCurrent = treeCtrl.GetChildItem(hRoot);
		while(hCurrent != NULL)
		{
			TVITEM item;
			TCHAR szText[1024];
			item.hItem = hCurrent;
			item.mask = TVIF_TEXT | TVIF_HANDLE;
			item.pszText = szText;
			item.cchTextMax = 1024;
			treeCtrl.GetItem(&item);
			if(strDescription == item.pszText)
			{
				treeCtrl.SelectItem(item.hItem);
				treeCtrl.EnsureVisible(item.hItem);
				break;	
			}
			hCurrent = treeCtrl.GetNextItem(hCurrent, TVGN_NEXT);
		}
	}
}

void CLeftView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;
	
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();

	long lArrayPos = (long)treeCtrl.GetItemData(hItem);
	if(treeCtrl.GetParentItem(hItem) == NULL)
		pMain->ShowSelectedHeader(lArrayPos);
	else
		pMain->ShowSelectedEntry(lArrayPos);
}

// open item double clicked on
void CLeftView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CTreeView::OnLButtonDblClk(nFlags, point);
	// auto load item on double click
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	pMain->LoadFileAssociation(false);
}

void CLeftView::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;

	HTREEITEM htiTarget;  // handle to target item 
	TVHITTESTINFO tvht;  // hit test information 
    tvht.pt.x = pNMTreeView->ptDrag.x; 
    tvht.pt.y = pNMTreeView->ptDrag.y; 
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	if ((htiTarget = TreeView_HitTest(treeCtrl.m_hWnd, &tvht)) != NULL) 
    { 
		// don't drag main items
		if(treeCtrl.GetParentItem(htiTarget) != NULL)
		{
			SetCapture();
			m_bDragging = true;
			m_itemDrag = htiTarget;
			m_hCursorOld = SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_DRAG));
		}
    } 	
}

void CLeftView::OnMouseMove(UINT nFlags, CPoint point)
{
	CTreeView::OnMouseMove(nFlags, point);
    if(m_bDragging) 
    { 
		HTREEITEM htiTarget;  // handle to target item 
	    TVHITTESTINFO tvht;  // hit test information 
        tvht.pt.x = point.x; 
        tvht.pt.y = point.y; 
		CTreeCtrl& treeCtrl = GetTreeCtrl();
        if ((htiTarget = TreeView_HitTest(treeCtrl.m_hWnd, &tvht)) != NULL) 
        { 
            TreeView_SelectDropTarget(treeCtrl.m_hWnd, htiTarget); 
        } 
    } 
}

void CLeftView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CTreeView::OnLButtonUp(nFlags, point);

	if(m_bDragging)
	{
		CTreeCtrl& treeCtrl = GetTreeCtrl();

		m_bDragging = false;
		ReleaseCapture();
		SetCursor(m_hCursorOld);

		HTREEITEM htiTarget;  // handle to target item 
		TVHITTESTINFO tvht;  // hit test information 
        tvht.pt.x = point.x; 
        tvht.pt.y = point.y; 
        if ((htiTarget = TreeView_HitTest(treeCtrl.m_hWnd, &tvht)) != NULL) 
            MoveTreeItem(m_itemDrag, htiTarget); 
		else
			TreeView_Select(treeCtrl.m_hWnd,NULL,TVGN_DROPHILITE);
	}
}

// move item to new location
void CLeftView::MoveTreeItem(HTREEITEM htiSource,HTREEITEM htiTarget)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	if(MessageBox("Are you sure you want to move this item?","Confirm move",MB_YESNO) == IDYES)
	{
		HTREEITEM hParent = treeCtrl.GetParentItem(htiTarget);
		if(hParent)
			htiTarget = hParent;		
		// source
		long lArrayPosSource = (long)treeCtrl.GetItemData(htiSource);
		// target
		long lArrayPosTarget= (long)treeCtrl.GetItemData(htiTarget);
		pMain->MoveTreeItem(lArrayPosSource,lArrayPosTarget);		
	}
	else
	{
		TreeView_Select(treeCtrl.m_hWnd,NULL,TVGN_DROPHILITE);
		pMain->SetLastViewSelection();
	}
}

// set encrypted item image
void CLeftView::SetItemImageEncrypted(BOOL bEncrypted)
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	HTREEITEM hItem = treeCtrl.GetSelectedItem();
	treeCtrl.SetItemImage(hItem,bEncrypted?15:14,bEncrypted?15:14);
}

