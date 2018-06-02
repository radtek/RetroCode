// MyPrintListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "MyPrintListCtrl.h"
#include ".\myprintlistctrl.h"


// CMyPrintListCtrl

IMPLEMENT_DYNAMIC(CMyPrintListCtrl, CListCtrl)
CMyPrintListCtrl::CMyPrintListCtrl()
{
}

CMyPrintListCtrl::~CMyPrintListCtrl()
{
}

BEGIN_MESSAGE_MAP(CMyPrintListCtrl, CListCtrl)	
END_MESSAGE_MAP()

void CMyPrintListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    CRect rcItem(lpDrawItemStruct->rcItem);
    int nItem = lpDrawItemStruct->itemID;
    CImageList* pImageList;
    
    // Save dc state
    int nSavedDC = pDC->SaveDC();
    
    // Get item image and state info
    LV_ITEM lvi;
    lvi.mask = LVIF_IMAGE | LVIF_STATE;
    lvi.iItem = nItem;
    lvi.iSubItem = 0;
    lvi.stateMask = 0xFFFF;     // get all state flags
    GetItem(&lvi);
    
    // Should the item be highlighted
    BOOL bHighlight =((lvi.state & LVIS_DROPHILITED) || ( (lvi.state & LVIS_SELECTED)
        && ((GetFocus() == this) || (GetStyle() & LVS_SHOWSELALWAYS))));
    
    // Get rectangles for drawing
    CRect rcBounds, rcLabel, rcIcon;
    GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
    GetItemRect(nItem, rcLabel, LVIR_LABEL);
    GetItemRect(nItem, rcIcon, LVIR_ICON);
    CRect rcCol( rcBounds ); 
    
    CString sLabel = GetItemText( nItem, 0 );
    
    // Labels are offset by a certain amount  
    // This offset is related to the width of a space character
    int offset = pDC->GetTextExtent(_T(" "), 1 ).cx*2;
    
    CRect rcHighlight;
    CRect rcWnd;
    rcHighlight = rcBounds;
    rcHighlight.left = rcLabel.left;
       
    // Draw the background color
    if( bHighlight )
    {
        pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
        pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
        
        pDC->FillRect(rcHighlight, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
    }
    else
        pDC->FillRect(rcHighlight, &CBrush(::GetSysColor(COLOR_WINDOW)));
    
    // Set clip region
    rcCol.right = rcCol.left + GetColumnWidth(0);
    CRgn rgn;
    rgn.CreateRectRgnIndirect(&rcCol);
    pDC->SelectClipRgn(&rgn);
    rgn.DeleteObject();
    
    // Draw state icon
    if (lvi.state & LVIS_STATEIMAGEMASK)
    {
        int nImage = ((lvi.state & LVIS_STATEIMAGEMASK)>>12) - 1;
        pImageList = GetImageList(LVSIL_STATE);
        if (pImageList)
        {
            pImageList->Draw(pDC, nImage, CPoint(rcCol.left, rcCol.top), ILD_TRANSPARENT);
        }
    }
    // Draw normal and overlay icon
    pImageList = GetImageList(LVSIL_NORMAL);
    if (pImageList)
    {
        UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
        pImageList->Draw(pDC, lvi.iImage, 
            CPoint(rcIcon.left, rcIcon.top),
            (bHighlight?ILD_BLEND50:0) | ILD_TRANSPARENT | nOvlImageMask );
    }
    
    // Draw item label - Column 0
    rcLabel.left += offset/2 + 20;
    rcLabel.right -= offset;
    
    pDC->DrawText(sLabel,-1,rcLabel,
        DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP |
        DT_VCENTER | DT_END_ELLIPSIS);
    
    // Draw labels for remaining columns
    LV_COLUMN lvc;
    lvc.mask = LVCF_FMT | LVCF_WIDTH;
  
    rcBounds.right = rcHighlight.right > rcBounds.right ? rcHighlight.right :
    rcBounds.right;
    rgn.CreateRectRgnIndirect(&rcBounds);
    pDC->SelectClipRgn(&rgn);
    
    for(int nColumn = 1; GetColumn(nColumn, &lvc); nColumn++)
    {
        rcCol.left = rcCol.right;
        rcCol.right += lvc.cx;
        
        sLabel = GetItemText(nItem, nColumn);
        if (sLabel.GetLength() == 0)
            continue;
        
        rcLabel = rcCol;
        rcLabel.left += offset;
        rcLabel.right -= offset;
        
        pDC->DrawText(sLabel, -1, rcLabel, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS);
    }
    
    // Draw focus rectangle if item has focus
    if (lvi.state & LVIS_FOCUSED && (GetFocus() == this))
        pDC->DrawFocusRect(rcHighlight);
    
    // Restore dc
    pDC->RestoreDC( nSavedDC );
}

