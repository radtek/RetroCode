
#include "StdAfx.h"
#include ".\mybmbutton.h"

CMyBmButton::CMyBmButton(void)
{
	m_bIsPressed = false;
	m_bIsFocused = false;
	m_bIsDisabled = false;
	m_bIsFlat = true;
	m_bDrawBorder = true;
	m_bMouseOnButton = false;
	m_bDrawFlatFocus = false;
	m_bIsDefault = false;
	m_bAlwaysTrack = false;
	// By default icon is aligned horizontally
	m_byAlign = ST_ALIGN_HORIZ; 
	m_ptImageOrg.x = 3;
	m_ptImageOrg.y = 3;
	SetPressedStyle(BTNST_PRESSED_LEFTRIGHT, FALSE);

	SetDefaultColors(false);
}

CMyBmButton::~CMyBmButton(void)
{
	FreeResources();
}

LRESULT CMyBmButton::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	return S_OK;
}

void CMyBmButton::OnDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	m_bIsPressed = (lpDrawItemStruct->itemState & ODS_SELECTED);
	if(m_bIsPressed)
		int n = 1;
	m_bIsFocused  = (lpDrawItemStruct->itemState & ODS_FOCUS);
	m_bIsDisabled = (lpDrawItemStruct->itemState & ODS_DISABLED);

	CRect itemRect = lpDrawItemStruct->rcItem;
	dc.SetBkMode(TRANSPARENT);
	OnDrawBackground(&dc,&itemRect);

	// Draw button border
	OnDrawBorder(&dc, &itemRect);

	CRect captionRect = lpDrawItemStruct->rcItem;
	if(m_csBitmaps[0].hBitmap)
	{
		dc.SetBkColor(RGB(255,255,255));
		DrawTheBitmap(&dc, false, &lpDrawItemStruct->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);
	} 	
	if(m_bIsFlat == FALSE || (m_bIsFlat && m_bDrawFlatFocus))
	{
		// Draw the focus rect
		if(m_bIsFocused)
		{
			CRect focusRect = itemRect;
			focusRect.DeflateRect(3,3);
			dc.DrawFocusRect(&focusRect);
		} 
	} 
	dc.Detach();
}

void CMyBmButton::FreeResources(BOOL bCheckForNULL)
{
	if(bCheckForNULL)
	{
		// Destroy bitmaps
		if (m_csBitmaps[0].hBitmap)	::DeleteObject(m_csBitmaps[0].hBitmap);
		if (m_csBitmaps[1].hBitmap)	::DeleteObject(m_csBitmaps[1].hBitmap);
		// Destroy mask bitmaps
		if (m_csBitmaps[0].hMask)	::DeleteObject(m_csBitmaps[0].hMask);
		if (m_csBitmaps[1].hMask)	::DeleteObject(m_csBitmaps[1].hMask);
	} 
	::ZeroMemory(&m_csBitmaps, sizeof(m_csBitmaps));
} 

void CMyBmButton::OnDrawBackground(CDC* pDC, CRect* pRect)
{
	COLORREF	crColor;
	if(m_bIsFlat == FALSE)
	{
		if(m_bIsFocused || m_bIsDefault)
		{
			CBrush br(RGB(0,0,0));  
			pDC->FrameRect(pRect, br);
			pRect->DeflateRect(1, 1);
		} 
	} 
	if(m_bMouseOnButton || m_bIsPressed)
		crColor = m_crColors[BTNST_COLOR_BK_IN];
	else
	{
		if (m_bIsFocused)
			crColor = m_crColors[BTNST_COLOR_BK_FOCUS];
		else
			crColor = m_crColors[BTNST_COLOR_BK_OUT];
	} // else
	CBrush	brBackground;
	brBackground.CreateSolidBrush(crColor);
	pDC->FillRect(pRect, brBackground);
} 

void CMyBmButton::OnDrawBorder(CDC* pDC, CRect* pRect)
{
	// Draw pressed button
	if(m_bIsPressed)
	{
		if(m_bIsFlat)
		{
			if (m_bDrawBorder)
				pDC->Draw3dRect(pRect, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHILIGHT));
		}
		else    
		{
			CBrush brBtnShadow;
			brBtnShadow.CreateSolidBrush(GetSysColor(COLOR_BTNSHADOW));
			pDC->FrameRect(pRect, brBtnShadow);
		}
	}
	else // ...else draw non pressed button
	{
		CPen penBtnHiLight;
		penBtnHiLight.CreatePen(PS_SOLID, 0, GetSysColor(COLOR_BTNHILIGHT)); // White
		CPen pen3DLight;
		pen3DLight.CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DLIGHT));       // Light gray
		CPen penBtnShadow;
		penBtnShadow.CreatePen(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));   // Dark gray
		CPen pen3DDKShadow;
		pen3DDKShadow.CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DDKSHADOW)); // Black

		if (m_bIsFlat)
		{
			if (m_bMouseOnButton && m_bDrawBorder)
				pDC->Draw3dRect(pRect, ::GetSysColor(COLOR_BTNHILIGHT), ::GetSysColor(COLOR_BTNSHADOW));
		}
		else
		{
			// Draw top-left borders
			// White line
			HPEN pOldPen = pDC->SelectPen(penBtnHiLight);
			pDC->MoveTo(pRect->left, pRect->bottom-1);
			pDC->LineTo(pRect->left, pRect->top);
			pDC->LineTo(pRect->right, pRect->top);
			// Light gray line
			pDC->SelectPen(pen3DLight);
			pDC->MoveTo(pRect->left+1, pRect->bottom-1);
			pDC->LineTo(pRect->left+1, pRect->top+1);
			pDC->LineTo(pRect->right, pRect->top+1);
			// Draw bottom-right borders
			// Black line
			pDC->SelectPen(pen3DDKShadow);
			pDC->MoveTo(pRect->left, pRect->bottom-1);
			pDC->LineTo(pRect->right-1, pRect->bottom-1);
			pDC->LineTo(pRect->right-1, pRect->top-1);
			// Dark gray line
			pDC->SelectPen(penBtnShadow);
			pDC->MoveTo(pRect->left+1, pRect->bottom-2);
			pDC->LineTo(pRect->right-2, pRect->bottom-2);
			pDC->LineTo(pRect->right-2, pRect->top);
			//
			pDC->SelectPen(pOldPen);
		} 
	} 
} 

void CMyBmButton::DrawTheBitmap(CDC* pDC, BOOL bHasTitle, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed, BOOL bIsDisabled)
{
	HDC			hdcBmpMem	= NULL;
	HBITMAP		hbmOldBmp	= NULL;
	HDC			hdcMem		= NULL;
	HBITMAP		hbmT		= NULL;
	BYTE		byIndex		= 0;
	// Select the bitmap to use
	if(bIsPressed || m_bMouseOnButton)
		byIndex = 0;
	else
		byIndex = (m_csBitmaps[1].hBitmap == NULL ? 0 : 1);

	CRect	rImage;
	PrepareImageRect(bHasTitle, rpItem, rpCaption, bIsPressed, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight, &rImage);

	hdcBmpMem = ::CreateCompatibleDC(pDC->m_hDC);

	hbmOldBmp = (HBITMAP)::SelectObject(hdcBmpMem, m_csBitmaps[byIndex].hBitmap);

	hdcMem = ::CreateCompatibleDC(NULL);

	hbmT = (HBITMAP)::SelectObject(hdcMem, m_csBitmaps[byIndex].hMask);

	if (bIsDisabled)
	{
		HDC		hDC = NULL;
		HBITMAP	hBitmap = NULL;

		hDC = ::CreateCompatibleDC(pDC->m_hDC);
		hBitmap = ::CreateCompatibleBitmap(pDC->m_hDC, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight);
		HBITMAP	hOldBmp2 = (HBITMAP)::SelectObject(hDC, hBitmap);

		RECT	rRect;
		rRect.left = 0;
		rRect.top = 0;
		rRect.right = rImage.right + 1;
		rRect.bottom = rImage.bottom + 1;
		::FillRect(hDC, &rRect, (HBRUSH)RGB(255, 255, 255));

		COLORREF crOldColor = ::SetBkColor(hDC, RGB(255,255,255));

		::BitBlt(hDC, 0, 0, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight, hdcMem, 0, 0, SRCAND);
		::BitBlt(hDC, 0, 0, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight, hdcBmpMem, 0, 0, SRCPAINT);

		::SetBkColor(hDC, crOldColor);
		::SelectObject(hDC, hOldBmp2);
		::DeleteDC(hDC);

		pDC->DrawState(	CPoint(rImage.left/*+1*/, rImage.top), 
						CSize(m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight), 
						hBitmap, DST_BITMAP | DSS_DISABLED);

		::DeleteObject(hBitmap);
	} // if
	else
	{
		::BitBlt(pDC->m_hDC, rImage.left, rImage.top, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight, hdcMem, 0, 0, SRCAND);

		::BitBlt(pDC->m_hDC, rImage.left, rImage.top, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight, hdcBmpMem, 0, 0, SRCPAINT);
	} // else

	::SelectObject(hdcMem, hbmT);
	::DeleteDC(hdcMem);

	::SelectObject(hdcBmpMem, hbmOldBmp);
	::DeleteDC(hdcBmpMem);
} 

void CMyBmButton::SetDefaultColors(BOOL bRepaint)
{
	m_crColors[BTNST_COLOR_BK_IN]		= ::GetSysColor(COLOR_BTNFACE);
	m_crColors[BTNST_COLOR_FG_IN]		= ::GetSysColor(COLOR_BTNTEXT);
	m_crColors[BTNST_COLOR_BK_OUT]		= ::GetSysColor(COLOR_BTNFACE);
	m_crColors[BTNST_COLOR_FG_OUT]		= ::GetSysColor(COLOR_BTNTEXT);
	m_crColors[BTNST_COLOR_BK_FOCUS]	= ::GetSysColor(COLOR_BTNFACE);
	m_crColors[BTNST_COLOR_FG_FOCUS]	= ::GetSysColor(COLOR_BTNTEXT);
	if(bRepaint)
		Invalidate();
} 

void CMyBmButton::PrepareImageRect(BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, DWORD dwWidth, DWORD dwHeight, CRect* rpImage)
{
	CRect rBtn;
	rpImage->CopyRect(rpItem);

	switch (m_byAlign)
	{
		case ST_ALIGN_HORIZ:
			if (bHasTitle == FALSE)
			{
				// Center image horizontally
				rpImage->left += ((rpImage->Width() - (long)dwWidth)/2);
			}
			else
			{
				// Image must be placed just inside the focus rect
				rpImage->left += m_ptImageOrg.x;  
				rpTitle->left += dwWidth + m_ptImageOrg.x;
			}
			// Center image vertically
			rpImage->top += ((rpImage->Height() - (long)dwHeight)/2);
			break;

		case ST_ALIGN_HORIZ_RIGHT:
			GetClientRect(&rBtn);
			if (bHasTitle == FALSE)
			{
				// Center image horizontally
				rpImage->left += ((rpImage->Width() - (long)dwWidth)/2);
			}
			else
			{
				// Image must be placed just inside the focus rect
				rpTitle->right = rpTitle->Width() - dwWidth - m_ptImageOrg.x;
				rpTitle->left = m_ptImageOrg.x;
				rpImage->left = rBtn.right - dwWidth - m_ptImageOrg.x;
				// Center image vertically
				rpImage->top += ((rpImage->Height() - (long)dwHeight)/2);
			}
			break;
		
		case ST_ALIGN_VERT:
			// Center image horizontally
			rpImage->left += ((rpImage->Width() - (long)dwWidth)/2);
			if (bHasTitle == FALSE)
			{
				// Center image vertically
				rpImage->top += ((rpImage->Height() - (long)dwHeight)/2);           
			}
			else
			{
				rpImage->top = m_ptImageOrg.y;
				rpTitle->top += dwHeight;
			}
			break;

		case ST_ALIGN_OVERLAP:
			break;
	} // switch
    
	// If button is pressed then press image also
	if (bIsPressed)
		rpImage->OffsetRect(m_ptPressedOffset.x, m_ptPressedOffset.y);
} 

void CMyBmButton::SetPressedStyle(BYTE byStyle, BOOL bRepaint)
{
	switch (byStyle)
	{
		case BTNST_PRESSED_LEFTRIGHT:
			m_ptPressedOffset.x = 1;
			m_ptPressedOffset.y = 1;
			break;
		case BTNST_PRESSED_TOPBOTTOM:
			m_ptPressedOffset.x = 0;
			m_ptPressedOffset.y = 2;
			break;
	} // switch
	if (bRepaint)	
		Invalidate();
} 

void CMyBmButton::SetBitmaps(HBITMAP hBitmapIn, COLORREF crTransColorIn, HBITMAP hBitmapOut, COLORREF crTransColorOut,ULONG ulBitOutDefault)
{
	int		nRetValue = 0;
	BITMAP	csBitmapSize;

	// Free any loaded resource
	FreeResources();

	if (hBitmapIn)
	{
		m_csBitmaps[0].hBitmap = hBitmapIn;
		m_csBitmaps[0].crTransparent = crTransColorIn;
		// Get bitmap size
		nRetValue = ::GetObject(hBitmapIn, sizeof(csBitmapSize), &csBitmapSize);
		if (nRetValue == 0)
		{
			FreeResources();
			return;
		} // if
		m_csBitmaps[0].dwWidth = (DWORD)csBitmapSize.bmWidth;
		m_csBitmaps[0].dwHeight = (DWORD)csBitmapSize.bmHeight;

		// Create grayscale/darker bitmap BEFORE mask (of hBitmapIn)
		if(ulBitOutDefault == BTNST_AUTO_GRAY)
		{			
			hBitmapOut = CreateGrayscaleBitmap(hBitmapIn, m_csBitmaps[0].dwWidth, m_csBitmaps[0].dwHeight, crTransColorIn);
			m_csBitmaps[1].hBitmap = hBitmapOut;
			crTransColorOut = crTransColorIn;
		}
		else if(ulBitOutDefault == BTNST_AUTO_DARKER)
		{
			hBitmapOut = CreateDarkerBitmap(hBitmapIn, m_csBitmaps[0].dwWidth, m_csBitmaps[0].dwHeight, crTransColorIn);
			m_csBitmaps[1].hBitmap = hBitmapOut;
			crTransColorOut = crTransColorIn;
		} 
		// Create mask for bitmap In
		m_csBitmaps[0].hMask = CreateBitmapMask(hBitmapIn, m_csBitmaps[0].dwWidth, m_csBitmaps[0].dwHeight, crTransColorIn);
		if (m_csBitmaps[0].hMask == NULL)
		{
			FreeResources();
			return;
		} // if

		if (!ulBitOutDefault && hBitmapOut)
		{
			m_csBitmaps[1].hBitmap = hBitmapOut;
			m_csBitmaps[1].crTransparent = crTransColorOut;
			// Get bitmap size
			nRetValue = ::GetObject(hBitmapOut, sizeof(csBitmapSize), &csBitmapSize);
			if (nRetValue == 0)
			{
				FreeResources();
				return;
			} // if
			m_csBitmaps[1].dwWidth = (DWORD)csBitmapSize.bmWidth;
			m_csBitmaps[1].dwHeight = (DWORD)csBitmapSize.bmHeight;

			// Create mask for bitmap Out
			m_csBitmaps[1].hMask = CreateBitmapMask(hBitmapOut, m_csBitmaps[1].dwWidth, m_csBitmaps[1].dwHeight, crTransColorOut);
			if (m_csBitmaps[1].hMask == NULL)
			{
				FreeResources();
				return;
			} // if
		} // if
	} // if
	Invalidate();
} 

HBITMAP CMyBmButton::CreateGrayscaleBitmap(HBITMAP hBitmap, DWORD dwWidth, DWORD dwHeight, COLORREF crTrans)
{
	HBITMAP		hGrayBitmap = NULL;
	HDC			hMainDC = NULL, hMemDC1 = NULL, hMemDC2 = NULL;
	HBITMAP		hOldBmp1 = NULL, hOldBmp2 = NULL;

	hMainDC = ::GetDC(NULL);
	if (hMainDC == NULL)	return NULL;
	hMemDC1 = ::CreateCompatibleDC(hMainDC);
	if (hMemDC1 == NULL)
	{
		::ReleaseDC(NULL, hMainDC);
		return NULL;
	} // if
	hMemDC2 = ::CreateCompatibleDC(hMainDC);
	if (hMemDC2 == NULL)
	{
		::DeleteDC(hMemDC1);
		::ReleaseDC(NULL, hMainDC);
		return NULL;
	} // if

	hGrayBitmap = ::CreateCompatibleBitmap(hMainDC, dwWidth, dwHeight);
	if (hGrayBitmap)
	{
		hOldBmp1 = (HBITMAP)::SelectObject(hMemDC1, hGrayBitmap);
		hOldBmp2 = (HBITMAP)::SelectObject(hMemDC2, hBitmap);

		//::BitBlt(hMemDC1, 0, 0, dwWidth, dwHeight, hMemDC2, 0, 0, SRCCOPY);

		DWORD		dwLoopY = 0, dwLoopX = 0;
		COLORREF	crPixel = 0;
		BYTE		byNewPixel = 0;

		for (dwLoopY = 0; dwLoopY < dwHeight; dwLoopY++)
		{
			for (dwLoopX = 0; dwLoopX < dwWidth; dwLoopX++)
			{
				crPixel = ::GetPixel(hMemDC2, dwLoopX, dwLoopY);
				byNewPixel = (BYTE)((GetRValue(crPixel) * 0.299) + (GetGValue(crPixel) * 0.587) + (GetBValue(crPixel) * 0.114));

				if (crPixel != crTrans)
					::SetPixel(hMemDC1, dwLoopX, dwLoopY, RGB(byNewPixel, byNewPixel, byNewPixel));
				else
					::SetPixel(hMemDC1, dwLoopX, dwLoopY, crPixel);
			} // for
		} // for

		::SelectObject(hMemDC1, hOldBmp1);
		::SelectObject(hMemDC2, hOldBmp2);
	} // if

	::DeleteDC(hMemDC1);
	::DeleteDC(hMemDC2);
	::ReleaseDC(NULL, hMainDC);

	return hGrayBitmap;
} 

HBITMAP CMyBmButton::CreateDarkerBitmap(HBITMAP hBitmap, DWORD dwWidth, DWORD dwHeight, COLORREF crTrans)
{
	HBITMAP		hGrayBitmap = NULL;
	HDC			hMainDC = NULL, hMemDC1 = NULL, hMemDC2 = NULL;
	HBITMAP		hOldBmp1 = NULL, hOldBmp2 = NULL;

	hMainDC = ::GetDC(NULL);
	if (hMainDC == NULL)	return NULL;
	hMemDC1 = ::CreateCompatibleDC(hMainDC);
	if (hMemDC1 == NULL)
	{
		::ReleaseDC(NULL, hMainDC);
		return NULL;
	} // if
	hMemDC2 = ::CreateCompatibleDC(hMainDC);
	if (hMemDC2 == NULL)
	{
		::DeleteDC(hMemDC1);
		::ReleaseDC(NULL, hMainDC);
		return NULL;
	} // if

	hGrayBitmap = ::CreateCompatibleBitmap(hMainDC, dwWidth, dwHeight);
	if (hGrayBitmap)
	{
		hOldBmp1 = (HBITMAP)::SelectObject(hMemDC1, hGrayBitmap);
		hOldBmp2 = (HBITMAP)::SelectObject(hMemDC2, hBitmap);

		//::BitBlt(hMemDC1, 0, 0, dwWidth, dwHeight, hMemDC2, 0, 0, SRCCOPY);

		DWORD		dwLoopY = 0, dwLoopX = 0;
		COLORREF	crPixel = 0;

		for (dwLoopY = 0; dwLoopY < dwHeight; dwLoopY++)
		{
			for (dwLoopX = 0; dwLoopX < dwWidth; dwLoopX++)
			{
				crPixel = ::GetPixel(hMemDC2, dwLoopX, dwLoopY);

				if (crPixel != crTrans)
					::SetPixel(hMemDC1, dwLoopX, dwLoopY, DarkenColor(crPixel, 0.25));
				else
					::SetPixel(hMemDC1, dwLoopX, dwLoopY, crPixel);
			} // for
		} // for

		::SelectObject(hMemDC1, hOldBmp1);
		::SelectObject(hMemDC2, hOldBmp2);
	} // if

	::DeleteDC(hMemDC1);
	::DeleteDC(hMemDC2);
	::ReleaseDC(NULL, hMainDC);

	return hGrayBitmap;
} 

COLORREF CMyBmButton::DarkenColor(COLORREF crColor, double dFactor)
{
	if (dFactor > 0.0 && dFactor <= 1.0)
	{
		BYTE red,green,blue,lightred,lightgreen,lightblue;
		red = GetRValue(crColor);
		green = GetGValue(crColor);
		blue = GetBValue(crColor);
		lightred = (BYTE)(red-(dFactor * red));
		lightgreen = (BYTE)(green-(dFactor * green));
		lightblue = (BYTE)(blue-(dFactor * blue));
		crColor = RGB(lightred,lightgreen,lightblue);
	} 
	return crColor;
}

HBITMAP CMyBmButton::CreateBitmapMask(HBITMAP hSourceBitmap, DWORD dwWidth, DWORD dwHeight, COLORREF crTransColor)
{
	HBITMAP		hMask		= NULL;
	HDC			hdcSrc		= NULL;
	HDC			hdcDest		= NULL;
	HBITMAP		hbmSrcT		= NULL;
	HBITMAP		hbmDestT	= NULL;
	COLORREF	crSaveBk;
	COLORREF	crSaveDestText;

	hMask = ::CreateBitmap(dwWidth, dwHeight, 1, 1, NULL);
	if (hMask == NULL)	
		return NULL;
	hdcSrc	= ::CreateCompatibleDC(NULL);
	hdcDest	= ::CreateCompatibleDC(NULL);
	hbmSrcT = (HBITMAP)::SelectObject(hdcSrc, hSourceBitmap);
	hbmDestT = (HBITMAP)::SelectObject(hdcDest, hMask);
	crSaveBk = ::SetBkColor(hdcSrc, crTransColor);
	::BitBlt(hdcDest, 0, 0, dwWidth, dwHeight, hdcSrc, 0, 0, SRCCOPY);
	crSaveDestText = ::SetTextColor(hdcSrc, RGB(255, 255, 255));
	::SetBkColor(hdcSrc,RGB(0, 0, 0));
	::BitBlt(hdcSrc, 0, 0, dwWidth, dwHeight, hdcDest, 0, 0, SRCAND);
	SetTextColor(hdcDest, crSaveDestText);
	::SetBkColor(hdcSrc, crSaveBk);
	::SelectObject(hdcSrc, hbmSrcT);
	::SelectObject(hdcDest, hbmDestT);
	::DeleteDC(hdcSrc);
	::DeleteDC(hdcDest);

	return hMask;
} 

LRESULT CMyBmButton::OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CancelHover();
	return S_OK;
} 

void CMyBmButton::CancelHover()
{
	if(m_bIsFlat)
	{
		if(m_bMouseOnButton)
		{
			m_bMouseOnButton = FALSE;
			if(m_ToolTip.IsWindow())
				m_ToolTip.Activate(false);
			Invalidate();
		} 
	}
}

LRESULT CMyBmButton::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
	if(m_ToolTip.IsWindow())
	{
		CTime time;
		time = time.GetCurrentTime();
		MSG msg;
		msg.hwnd = m_hWnd;
		msg.message = uMsg;
		msg.wParam = wParam;
		msg.lParam = lParam;
		msg.time = (DWORD)time.GetTime();
		msg.pt = point;
		m_ToolTip.Activate(true);
		m_ToolTip.RelayEvent(&msg);
	}
	CWindow				wndUnderMouse;
	CWindow				wndActive(m_hWnd);
	TRACKMOUSEEVENT		csTME;

	UINT nFlags = (UINT)wParam;
	ClientToScreen(&point);
	wndUnderMouse.Attach(WindowFromPoint(point));

	// If the mouse enter the button with the left button pressed then do nothing
	if(nFlags & MK_LBUTTON && m_bMouseOnButton == FALSE) 
		return S_OK;
	// If our button is not flat then do nothing
	if(m_bIsFlat == FALSE) 
		return S_OK;
	if(m_bAlwaysTrack == FALSE)	
	{
		wndActive.Detach();
		wndActive.Attach(GetActiveWindow());
	}
	if((wndUnderMouse.m_hWnd == m_hWnd) && wndActive.IsWindow())
	{
		if(!m_bMouseOnButton)
		{
			m_bMouseOnButton = TRUE;
			Invalidate();
			csTME.cbSize = sizeof(csTME);
			csTME.dwFlags = TME_LEAVE;
			csTME.hwndTrack = m_hWnd;
			::_TrackMouseEvent(&csTME);			
		} 
	} 
	else 
		CancelHover();
	return S_OK;
} 

// sets tool tip
void CMyBmButton::CreateToolTip(ATL::CString strText)
{
	CRect rect;
	GetClientRect(rect);
	if(!m_ToolTip.IsWindow())
	{
		HWND hwnd = m_ToolTip.Create(m_hWnd,rect,NULL,WS_POPUP|TTS_NOPREFIX|TTS_BALLOON ,0 );
		CToolInfo ti(0, m_hWnd, 0, rect, strText.GetBuffer(strText.GetLength()));
		m_ToolTip.AddTool(&ti);
		strText.ReleaseBuffer();
		m_ToolTip.SetMaxTipWidth(100);
	}	
}

// Destroy Tool Tip
void CMyBmButton::DestroyToolTip(void)
{
	m_ToolTip.DestroyWindow();
}
