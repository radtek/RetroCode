// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenterOcx.h"
#include "MyListCtrl.h"
#include "helpers.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
	m_pDragImage = new CImageList;
	m_bDragging = FALSE;
	m_pJpegBK = NULL;
	m_nJpgBKOriginX = 0;
	m_nJpgBKOriginY = 0;

	m_dwBKColor = 0;
	m_dwTextColor = 0;
	m_dwSelectTextColor = 0;
	m_dwSelectBKColor = 0;

	m_bDrawBKSelected = false;
	m_nAlignText = 0;
	m_bDrawIcons = true;
}

CMyListCtrl::~CMyListCtrl()
{
	if(m_pDragImage)
		delete m_pDragImage;
	if(m_pJpegBK)
		delete m_pJpegBK;
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	ON_WM_DROPFILES()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_NOTIFY_REFLECT(LVN_INSERTITEM, OnInsertitem)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_WM_DRAWITEM()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers

int CMyListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(rect);
	InsertColumn(0,"File Name",LVCFMT_LEFT,rect.Width());

	m_pDragImage->Create(16, 13, ILC_COLORDDB, 3, 1);
	CBitmap bm;
	bm.LoadBitmap (IDB_DRAG);
	m_pDragImage->Add(&bm, RGB(255, 0, 255));
	SetImageList(m_pDragImage, LVSIL_SMALL);

	return 0;
}

void CMyListCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CListCtrl::OnSize(nType, cx, cy);
	SetColumnWidth(0,cx);	
}

void CMyListCtrl::OnDropFiles(HDROP hDropInfo) 
{
	UINT nFiles = DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);

	CString strFile;
    for(UINT n=0;n<nFiles;n++)
    {
        DragQueryFile(hDropInfo,n,strFile.GetBuffer(MAX_PATH),MAX_PATH);
		strFile.ReleaseBuffer();
        
		AddNewFile(strFile);
    }

	CListCtrl::OnDropFiles(hDropInfo);
}

void CMyListCtrl::AddNewFile(CString strFile, BOOL bUpdateApp)
{
	CString strParams = "<FullPath>" + strFile + "</FullPath>";
	CString strName = strFile.Mid(strFile.ReverseFind('\\')+1);
	strParams += "<Name>" + strName + "</Name>";

	m_straPlayList.Add(strParams);
	
	LVITEM item;
	ZeroMemory(&item,sizeof(LVITEM));
	item.mask = LVIF_TEXT|LVIF_PARAM|LVIF_IMAGE|LVIF_STATE;
	item.iItem = GetItemCount();
	item.iSubItem = 0;
	int nLen = strName.GetLength();
	item.pszText = strName.GetBuffer(nLen);
	item.cchTextMax = nLen;
	item.iImage = GetImageTypeNumber(strFile);
	item.lParam = 0;
	item.state = 0;
	InsertItem(&item);
	strName.ReleaseBuffer();

	if(bUpdateApp)
		SendListUpdateToApp();
}

void CMyListCtrl::ClearPlayList()
{
	m_straPlayList.RemoveAll();
	DeleteAllItems();
}

void CMyListCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	
	int nItem = pDispInfo->item.iItem;
	CString strNewText = pDispInfo->item.pszText;
	
	CString strName = ParseXML("Name",m_straPlayList.GetAt(nItem));
	if(strName != strNewText)
	{
		CString strFullPath = ParseXML("FullPath",m_straPlayList.GetAt(nItem));
		CString strNewFullPath = strFullPath.Left(strFullPath.ReverseFind('\\')+1);
		strNewFullPath += strNewText;
		
		SECFileSystem fp;
		BOOL bOK = fp.RenameFile(strFullPath,strNewFullPath);
		if(bOK)
		{
			SetItemText(nItem,0,strNewText);
			
			m_straPlayList.SetAt(nItem,ReplaceXML(strNewText,"Name",m_straPlayList.GetAt(nItem)));
			m_straPlayList.SetAt(nItem,ReplaceXML(strNewFullPath,"FullPath",m_straPlayList.GetAt(nItem)));
		}
	}
	*pResult = 0;
}

void CMyListCtrl::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	*pResult = 0;

	WORD wKey = pLVKeyDow->wVKey;
	// 46 delete
	if(wKey==46)
	{
		int nSelectPos = 0;
		CStringArray straTemp;
		for(int n=0;n<GetItemCount();n++)
		{
			BOOL bSelected = (GetItemState(n,LVIS_SELECTED) & LVIS_SELECTED);
			if(bSelected)
			{
				nSelectPos = n;
				m_straPlayList.RemoveAt(nSelectPos);
				DeleteItem(nSelectPos);
				break;
			}
		}

		if(nSelectPos < GetItemCount())
		{
			SetItemState(nSelectPos,LVIS_SELECTED,LVIS_SELECTED);
			EnsureVisible(nSelectPos,false);
		}
		else if(GetItemCount() > 0)
		{
			SetItemState(GetItemCount()-1,LVIS_SELECTED,LVIS_SELECTED);	
			EnsureVisible(GetItemCount()-1,false);
		}
		SendListUpdateToApp();
	}
}

void CMyListCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_nDragIndex = ((NM_LISTVIEW *)pNMListView)->iItem;
	POINT pt;
	pt.x = 8;
	pt.y = 8;
	// create a drag image
	BOOL bOK = m_pDragImage->BeginDrag (1, CPoint (8, 8));
	m_pDragImage->DragEnter (GetDesktopWindow (), ((NM_LISTVIEW *)pNMListView)->ptAction);
	// set dragging flag
	m_bDragging = TRUE;
	m_nDropIndex = -1;
	m_pDropWnd = this;
	// capture all mouse messages
	SetCapture ();

	*pResult = 0;
}

void CMyListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
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
			if (m_nDropIndex != -1)
			{
				CListCtrl* pList = (CListCtrl*)m_pDropWnd;
				VERIFY (pList->SetItemState (m_nDropIndex, 0, LVIS_DROPHILITED));
				// redraw item
				VERIFY (pList->RedrawItems (m_nDropIndex, m_nDropIndex));
				pList->UpdateWindow ();
				m_nDropIndex = -1;
			}
		}
		// save current window pointer
		m_pDropWnd = pDropWnd;

		// convert from screen coordinates to drop target client coordinates
		pDropWnd->ScreenToClient (&pt);

		if (pDropWnd->IsKindOf (RUNTIME_CLASS (CListCtrl)))
		{			
			UINT uFlags;
			CListCtrl* pList = (CListCtrl*)pDropWnd;

			// turn off hilight for previous drop target
			pList->SetItemState (m_nDropIndex, 0, LVIS_DROPHILITED);
			// redraw previous item
			pList->RedrawItems(m_nDropIndex, m_nDropIndex);
			
			// get the item that is below cursor
			m_nDropIndex = ((CListCtrl*)pDropWnd)->HitTest (pt, &uFlags);
			// highlight it
			pList->SetItemState (m_nDropIndex, LVIS_DROPHILITED, LVIS_DROPHILITED);
			// redraw item
			pList->RedrawItems(m_nDropIndex, m_nDropIndex);
			pList->UpdateWindow();
		}
		// lock window updates
		VERIFY (m_pDragImage->DragShowNolock (TRUE));
	}
	
	CListCtrl::OnMouseMove(nFlags, point);
}

void CMyListCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
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
	
	CListCtrl::OnLButtonUp(nFlags, point);
}

void CMyListCtrl::SwapPositions()
{
	if(m_nDragIndex < 0 || m_nDragIndex > m_straPlayList.GetSize())
		return;
	if(m_nDropIndex < 0 || m_nDropIndex > m_straPlayList.GetSize())
		return;
	if(m_nDragIndex == m_nDropIndex)
		return;

	SetNormalIcon(m_nDragIndex);
	SetNormalIcon(m_nDropIndex);

	// Dragged from
	CString strItemText0 = GetItemText(m_nDropIndex,0);
	CString strTemp = m_straPlayList.GetAt(m_nDropIndex);

	// swap from to strings
	SetItemText(m_nDropIndex,0,GetItemText(m_nDragIndex,0));
	m_straPlayList.SetAt(m_nDropIndex,m_straPlayList.GetAt(m_nDragIndex));

	// delete dragged pos
	m_straPlayList.RemoveAt(m_nDragIndex);
	DeleteItem(m_nDragIndex);

	if(m_nDragIndex < m_nDropIndex)
		m_nDropIndex -- ;
	
	// insert below swap pos
	LVITEM item;
	ZeroMemory(&item,sizeof(LVITEM));
	item.mask = LVIF_TEXT|LVIF_PARAM|LVIF_IMAGE|LVIF_STATE;
	item.iItem = m_nDropIndex+1;
	item.iSubItem = 0;
	int nLen = strItemText0.GetLength();
	item.pszText = strItemText0.GetBuffer(nLen);
	item.cchTextMax = nLen;
	item.iImage = GetImageTypeNumber(ParseXML("FullPath",strTemp));
	item.lParam = 0;
	item.state = 0;
	InsertItem(&item);
	strItemText0.ReleaseBuffer();

	m_straPlayList.InsertAt(m_nDropIndex+1,strTemp);

	SetItemState(m_nDragIndex, 0, LVIS_DROPHILITED);
	SetItemState(m_nDragIndex, 0, LVIS_SELECTED);
	SetItemState(m_nDropIndex, 0, LVIS_DROPHILITED);
	SetItemState(m_nDropIndex, LVIS_SELECTED, LVIS_SELECTED);	

	SendListUpdateToApp();
}

CStringArray* CMyListCtrl::GetSelectedList()
{
	CStringArray* pStra = new CStringArray;
	
	for(int n=0;n<GetItemCount();n++)
	{
		BOOL bSelected = (GetItemState(n,LVIS_SELECTED) & LVIS_SELECTED);
		if(bSelected)
		{
			pStra->Add(m_straPlayList.GetAt(n));
		}
	}
	return pStra;
}

void CMyListCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	for(int n=0;n<GetItemCount();n++)
		SetNormalIcon(n);

	GetParent()->PostMessage(WM_PLAY_ALL_FROM_SELECTED);
		
	*pResult = 0;
}

DWORD CMyListCtrl::GetSelectedItem()
{
	DWORD nItem = 0;
	POSITION pos = GetFirstSelectedItemPosition();
	if (pos != NULL)
		nItem = GetNextSelectedItem(pos);

	return nItem;
}

int CMyListCtrl::GetImageTypeNumber(CString strFile)
{
	EnumFileType myType = GetMediaFileType(strFile);
	if(myType == WMP_AUDIO)
		return 1;
	else
		return 0;
}

void CMyListCtrl::SetNormalIconAll()
{
	for(int n=0;n<GetItemCount();n++)
		SetNormalIcon(n);
}

void CMyListCtrl::SetNormalIcon(DWORD nPos)
{
	if(nPos >= GetItemCount())
		return;
	LVITEM item;
	ZeroMemory(&item,sizeof(LVITEM));
	item.mask = LVIF_IMAGE;
	item.iItem = nPos;
	item.iImage = GetImageTypeNumber(ParseXML("FullPath",m_straPlayList.GetAt(nPos)));
	SetItem(&item);
}

void CMyListCtrl::SetPlayingIcon(DWORD nPos,BOOL bSelect)
{
	if(nPos >= GetItemCount())
		return;

	LVITEM item;
	ZeroMemory(&item,sizeof(LVITEM));
	item.mask = LVIF_IMAGE;
	item.iItem = nPos;
	item.iImage = 2;
	SetItem(&item);

	if(bSelect)
	{
		EnsureVisible(nPos,false);
		DWORD dwOld = GetSelectedItem();
		SetItemState(dwOld,0, LVIS_SELECTED);
		SetItemState(nPos, LVIS_SELECTED, LVIS_SELECTED);	
	}
}

DWORD CMyListCtrl::MakeSelectedString(CString strName,BOOL bSetPlayIcon)
{
	for(int n=0;n<GetItemCount();n++)
	{
		CString strTest = GetItemText(n,0);
		if(strName == strTest)
		{
			SetItemState(n, LVIS_SELECTED, LVIS_SELECTED);
			if(bSetPlayIcon)
				SetPlayingIcon(n);
			return n;
		}
	}
	return 0;
}

void CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    DWORD dwItem = lpDrawItemStruct->itemID;
	CString strText = GetItemText(dwItem,0);

	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	
	CRect rectItem(lpDrawItemStruct->rcItem);
	BOOL bSelected = (GetItemState(dwItem,LVIS_SELECTED) & LVIS_SELECTED);

	if(m_bDrawIcons)
	{
		LVITEM item;
		ZeroMemory(&item,sizeof(LVITEM));
		item.mask = LVIF_IMAGE; 
		item.iItem = dwItem;
		GetItem(&item);		
	    int iImage = item.iImage;
		CImageList* pImageList = GetImageList(LVSIL_SMALL);
		pImageList->DrawIndirect(&dc,iImage,CPoint(0,rectItem.top),CSize(16,12),CPoint(0,0));
		
		rectItem.left += 20;
	}
	if(bSelected)
	{
		CRect rectNeeded(rectItem);
		dc.DrawText(strText,&rectNeeded,m_nAlignText|DT_VCENTER|DT_CALCRECT);
		if(m_bDrawBKSelected)
		{
			CBrush brush;
			brush.CreateSolidBrush(m_dwSelectBKColor);	
			// center
			if(m_nAlignText == 1)
			{
				int nWidth = rectNeeded.Width();
				rectNeeded.left = (rectItem.Width() / 2) - (rectNeeded.Width() / 2);
				rectNeeded.right = rectNeeded.left + nWidth;
			}
			// right align
			else if(m_nAlignText == 2)
			{
				int nWidth = rectNeeded.Width();
				rectNeeded.right = rectItem.right;
				rectNeeded.left = rectNeeded.right - nWidth;				
			}
			dc.FillRect(rectNeeded,&brush);
		}
		dc.SetTextColor(m_dwSelectTextColor);
		dc.DrawText(strText,rectItem,m_nAlignText|DT_VCENTER);      
	}
	else
	{
		dc.SetTextColor(m_dwTextColor);
		dc.DrawText(strText,rectItem,m_nAlignText|DT_VCENTER);      
	}

	dc.Detach();
}

BOOL CMyListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	if(m_pJpegBK)
	{
		CRect rect;
		GetClientRect(rect);

		CDC dcMem;
		dcMem.CreateCompatibleDC(pDC);
		CBitmap bmMem; 
		bmMem.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
		CBitmap* pBm = dcMem.SelectObject(&bmMem);

		int rx = rect.Width();
		int ry = rect.Height();

		SECJpeg copyImage;
		copyImage.CopyImage(m_pJpegBK);
		SECImage* pImage = &copyImage;
		pImage->m_bUseHalftone = false;		

		// crop to size
		if(pImage->m_dwWidth > rx && pImage->m_dwHeight > ry)
		{
			pImage->Crop(rect.left + m_nJpgBKOriginX ,rect.top + m_nJpgBKOriginY,rx,ry);
			if(rx > 0)
			{
				pImage->StretchDIBits(&dcMem,0,0,rx,ry,
					0,0,rx,ry,
					pImage->m_lpSrcBits,pImage->m_lpBMI,DIB_RGB_COLORS,SRCCOPY); 
			}
		}
		else  // stretch
		{
			if(rx > 0)
			{
				if(pImage->m_dwWidth > rx)
					pImage->Crop(rect.left + m_nJpgBKOriginX,0,rx,pImage->m_dwHeight);
				pImage->StretchDIBits(&dcMem,0,0,rx,ry,
					0,0,pImage->m_dwWidth,pImage->m_dwHeight,
					pImage->m_lpSrcBits,pImage->m_lpBMI,DIB_RGB_COLORS,SRCCOPY); 
			}
		}
		pDC->BitBlt(rect.left,rect.top,rx,ry,&dcMem,0,0,SRCCOPY);
		dcMem.SelectObject(pBm);
		dcMem.DeleteDC();	
	}
	else
	{
		CRect rect;
		GetClientRect(rect);
		CBrush brush;
		brush.CreateSolidBrush(m_dwBKColor);
		pDC->FillRect(rect,&brush);
	}
	return true;
}

void CMyListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(m_pJpegBK)
		InvalidateRect(NULL);	

	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMyListCtrl::OnInsertitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	if(m_pJpegBK)
		InvalidateRect(NULL);
	
	*pResult = 0;
}

void CMyListCtrl::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if(m_pJpegBK)
		InvalidateRect(NULL);
	
	*pResult = 0;
}

BOOL CMyListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if(m_pJpegBK)
		InvalidateRect(NULL);

	BOOL bOK = CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
	return bOK;
}

void CMyListCtrl::LoadImage()
{
	if(!m_strImageBK.IsEmpty() && !m_pJpegBK)
	{
		SECFileSystem fp;
		if(!fp.FileExists(m_strImageBK))
			return;
		m_pJpegBK = new SECJpeg;
		m_pJpegBK->LoadImage(m_strImageBK);
		m_pJpegBK->m_bUseHalftone = false;
		
		if(IsWindow(m_hWnd))
			InvalidateRect(NULL);
	}
}

CString CMyListCtrl::GetPlaySelectedList()
{
	CString strData = "<Message>PlaySelectedList</Message>";

	CStringArray* pstra = GetSelectedList();
	for(int n=0;n<pstra->GetSize();n++)
	{
		strData += "<PlayListEntry>" + pstra->GetAt(n) + "</PlayListEntry>";
	}

	return strData;
}

void CMyListCtrl::SendListUpdateToApp()
{
	CString strData = "<Message>CurrentFileListXML</Message>";
	for(int n=0;n<m_straPlayList.GetSize();n++)
	{
		strData += "<PlayListEntry>" + m_straPlayList.GetAt(n) + "</PlayListEntry>";
	}

	SendMessageToInstanseOfApp(strData);
}

