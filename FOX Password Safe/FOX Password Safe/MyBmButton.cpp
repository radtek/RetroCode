// MyBmButton.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "MyBmButton.h"
#include ".\mybmbutton.h"

// CMyBmButton



IMPLEMENT_DYNAMIC(CMyBmButton, CButton)
CMyBmButton::CMyBmButton()
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

	m_Font.CreatePointFont(100,"Arial");
}

CMyBmButton::~CMyBmButton()
{
	FreeResources();
}


BEGIN_MESSAGE_MAP(CMyBmButton, CButton)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()



// CMyBmButton message handlers

int CMyBmButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

void CMyBmButton::OnMouseMove(UINT nFlags, CPoint point)
{
	CButton::OnMouseMove(nFlags, point);
	if(IsWindow(m_ToolTip.m_hWnd))
	{
		CTime time;
		time = time.GetCurrentTime();
		MSG msg;
		msg.hwnd = m_hWnd;
		msg.message = WM_MOUSEMOVE;
		msg.wParam = nFlags;
		msg.lParam = MAKELPARAM(point.x,point.y);
		msg.time = (DWORD)time.GetTime();
		msg.pt = point;
		m_ToolTip.Activate(true);
		m_ToolTip.RelayEvent(&msg);
	}
	TRACKMOUSEEVENT		csTME;

	ClientToScreen(&point);

	// If the mouse enter the button with the left button pressed then do nothing
	if(nFlags & MK_LBUTTON && m_bMouseOnButton == FALSE) 
		return;
	// If our button is not flat then do nothing
	if(m_bIsFlat == FALSE) 
		return;
	if(WindowFromPoint(point)->m_hWnd == m_hWnd)
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
}

void CMyBmButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	CButton::OnLButtonDown(nFlags, point);
	if(IsWindow(m_ToolTip.m_hWnd))
	{
		CTime time;
		time = time.GetCurrentTime();
		MSG msg;
		msg.hwnd = m_hWnd;
		msg.message = WM_LBUTTONDOWN;
		msg.wParam = nFlags;
		msg.lParam = MAKELPARAM(point.x,point.y);
		msg.time = (DWORD)time.GetTime();
		msg.pt = point;
		m_ToolTip.RelayEvent(&msg);
	}
}

void CMyBmButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	CButton::OnLButtonUp(nFlags, point);
	if(IsWindow(m_ToolTip.m_hWnd))
	{
		CTime time;
		time = time.GetCurrentTime();
		MSG msg;
		msg.hwnd = m_hWnd;
		msg.message = WM_LBUTTONUP;
		msg.wParam = nFlags;
		msg.lParam = MAKELPARAM(point.x,point.y);
		msg.time = (DWORD)time.GetTime();
		msg.pt = point;
		m_ToolTip.RelayEvent(&msg);
	}
}

void CMyBmButton::OnMButtonDown(UINT nFlags, CPoint point)
{
	CButton::OnMButtonDown(nFlags, point);
	if(IsWindow(m_ToolTip.m_hWnd))
	{
		CTime time;
		time = time.GetCurrentTime();
		MSG msg;
		msg.hwnd = m_hWnd;
		msg.message = WM_MBUTTONDOWN;
		msg.wParam = nFlags;
		msg.lParam = MAKELPARAM(point.x,point.y);
		msg.time = (DWORD)time.GetTime();
		msg.pt = point;
		m_ToolTip.RelayEvent(&msg);
	}
}

void CMyBmButton::OnMButtonUp(UINT nFlags, CPoint point)
{
	CButton::OnMButtonUp(nFlags, point);
	if(IsWindow(m_ToolTip.m_hWnd))
	{
		CTime time;
		time = time.GetCurrentTime();
		MSG msg;
		msg.hwnd = m_hWnd;
		msg.message = WM_MBUTTONUP;
		msg.wParam = nFlags;
		msg.lParam = MAKELPARAM(point.x,point.y);
		msg.time = (DWORD)time.GetTime();
		msg.pt = point;
		m_ToolTip.RelayEvent(&msg);
	}
}

void CMyBmButton::OnRButtonDown(UINT nFlags, CPoint point)
{
	CButton::OnRButtonDown(nFlags, point);
	if(IsWindow(m_ToolTip.m_hWnd))
	{
		CTime time;
		time = time.GetCurrentTime();
		MSG msg;
		msg.hwnd = m_hWnd;
		msg.message = WM_RBUTTONDOWN;
		msg.wParam = nFlags;
		msg.lParam = MAKELPARAM(point.x,point.y);
		msg.time = (DWORD)time.GetTime();
		msg.pt = point;
		m_ToolTip.RelayEvent(&msg);
	}
}

void CMyBmButton::OnRButtonUp(UINT nFlags, CPoint point)
{
	CButton::OnRButtonUp(nFlags, point);
	if(IsWindow(m_ToolTip.m_hWnd))
	{
		CTime time;
		time = time.GetCurrentTime();
		MSG msg;
		msg.hwnd = m_hWnd;
		msg.message = WM_RBUTTONUP;
		msg.wParam = nFlags;
		msg.lParam = MAKELPARAM(point.x,point.y);
		msg.time = (DWORD)time.GetTime();
		msg.pt = point;
		m_ToolTip.RelayEvent(&msg);
	}
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
			pDC->FrameRect(pRect, &br);
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
	pDC->FillRect(pRect, &brBackground);
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
			pDC->FrameRect(pRect, &brBtnShadow);
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
			CPen* pOldPen = (CPen*)pDC->SelectObject(penBtnHiLight);
			pDC->MoveTo(pRect->left, pRect->bottom-1);
			pDC->LineTo(pRect->left, pRect->top);
			pDC->LineTo(pRect->right, pRect->top);
			// Light gray line
			pDC->SelectObject(pen3DLight);
			pDC->MoveTo(pRect->left+1, pRect->bottom-1);
			pDC->LineTo(pRect->left+1, pRect->top+1);
			pDC->LineTo(pRect->right, pRect->top+1);
			// Draw bottom-right borders
			// Black line
			pDC->SelectObject(pen3DDKShadow);
			pDC->MoveTo(pRect->left, pRect->bottom-1);
			pDC->LineTo(pRect->right-1, pRect->bottom-1);
			pDC->LineTo(pRect->right-1, pRect->top-1);
			// Dark gray line
			pDC->SelectObject(penBtnShadow);
			pDC->MoveTo(pRect->left+1, pRect->bottom-2);
			pDC->LineTo(pRect->right-2, pRect->bottom-2);
			pDC->LineTo(pRect->right-2, pRect->top);
			//
			pDC->SelectObject(pOldPen);
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

void CMyBmButton::CancelHover()
{
	if(m_bIsFlat)
	{
		if(m_bMouseOnButton)
		{
			m_bMouseOnButton = FALSE;
			if(IsWindow(m_ToolTip.m_hWnd))
				m_ToolTip.Activate(false);
			Invalidate();
		} 
	}
}

// sets tool tip
void CMyBmButton::CreateToolTip(CString strText)
{
	if(!IsWindow(m_ToolTip.m_hWnd))
	{
		BOOL bOK = m_ToolTip.Create(this,WS_POPUP|TTS_NOPREFIX|TTS_BALLOON);
		m_ToolTip.AddTool(this,strText);
		m_ToolTip.SetMaxTipWidth(100);
	}	
}

// Destroy Tool Tip
void CMyBmButton::DestroyToolTip(void)
{
	m_ToolTip.DestroyWindow();
}

void CMyBmButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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

	// Read the button's title
	CString sTitle;
	GetWindowText(sTitle);

	CRect captionRect = lpDrawItemStruct->rcItem;
	if(m_csBitmaps[0].hBitmap)
	{
		dc.SetBkColor(RGB(255,255,255));
		DrawTheBitmap(&dc, !sTitle.IsEmpty(), &lpDrawItemStruct->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);
	} 	
	// Write the button title (if any)
	if (sTitle.IsEmpty() == FALSE)
	{
		DrawTheText(&dc, (LPCTSTR)sTitle, &lpDrawItemStruct->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);
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
}
BOOL CMyBmButton::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if(message == WM_MOUSELEAVE)
	{
		CancelHover();
	}

	return CButton::OnWndMsg(message, wParam, lParam, pResult);
}

void CMyBmButton::DrawTheText(CDC* pDC, LPCTSTR lpszText, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed, BOOL bIsDisabled)
{
	// Draw the button's title
	// If button is pressed then "press" title also
	if (m_bIsPressed)
		rpCaption->OffsetRect(m_ptPressedOffset.x, m_ptPressedOffset.y);

	// Center text
	CRect centerRect = rpCaption;
	pDC->DrawText(lpszText, -1, rpCaption, DT_WORDBREAK | DT_CENTER | DT_CALCRECT);
	rpCaption->OffsetRect((centerRect.Width() - rpCaption->Width())/2, (centerRect.Height() - rpCaption->Height())/2);
	pDC->SetBkMode(TRANSPARENT);
	
	CFont* pfOld = pDC->SelectObject(&m_Font);
	if(m_bIsDisabled)
	{
		rpCaption->OffsetRect(1, 1);
		pDC->SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
		pDC->DrawText(lpszText, -1, rpCaption, DT_WORDBREAK | DT_CENTER);
		rpCaption->OffsetRect(-1, -1);
		pDC->SetTextColor(::GetSysColor(COLOR_3DSHADOW));
		pDC->DrawText(lpszText, -1, rpCaption, DT_WORDBREAK | DT_CENTER);
	} // if
	else
	{
		if (m_bMouseOnButton || m_bIsPressed) 
		{
			pDC->SetTextColor(m_crColors[BTNST_COLOR_FG_IN]);
			pDC->SetBkColor(m_crColors[BTNST_COLOR_BK_IN]);
		} // if
		else 
		{
			if (m_bIsFocused)
			{ 
				pDC->SetTextColor(m_crColors[BTNST_COLOR_FG_FOCUS]); 
				pDC->SetBkColor(m_crColors[BTNST_COLOR_BK_FOCUS]); 
			} // if
			else 
			{
				pDC->SetTextColor(m_crColors[BTNST_COLOR_FG_OUT]); 
				pDC->SetBkColor(m_crColors[BTNST_COLOR_BK_OUT]); 
			} // else
		} // else
		pDC->DrawText(lpszText, -1, rpCaption, DT_WORDBREAK | DT_CENTER);
	} 
	pDC->SelectObject(pfOld);
} 