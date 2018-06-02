// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "MyButton.h"
#include ".\mybutton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)
CMyButton::CMyButton()
: m_bImageLoaded(FALSE),
  m_bImageDownLoaded(FALSE)
{	
	m_bUseCustColor = false;
	m_bUseGradientFill = true;
	m_crCustomColor = 0;
	m_crTextColor = RGB(0,0,0);
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CMyButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = -MulDiv(10, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSY), 72);  
	lf.lfItalic = false;
	strcpy(lf.lfFaceName, "Times New Roman");
	m_font.CreateFontIndirect(&lf);  
	SetFont(&m_font);

	EnableToolTips();

	return 0;
}

// CMyButton message handlers
BOOL CMyButton::LoadImage(UINT nResourceID)
{
	m_bImageLoaded = m_Image.LoadBitmap(nResourceID);
	return m_bImageLoaded;
}

// CMyButton message handlers
BOOL CMyButton::LoadImageDown(UINT nResourceID)
{
	m_bImageDownLoaded = m_ImageDown.LoadBitmap(nResourceID);
	return m_bImageDownLoaded;
}

void CMyButton::SetRGBCustomColor(COLORREF rgb)
{
	m_bUseCustColor = true;
	m_crCustomColor = rgb;
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	CRect rect(lpDrawItemStruct->rcItem);

	// draw image down
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		if(m_bImageDownLoaded)
		{
			CDC dcMemory;
			dcMemory.CreateCompatibleDC(&dc);
			BITMAP bmpInfo;
		    m_ImageDown.GetBitmap(&bmpInfo);
			CBitmap* pOldBitmap = dcMemory.SelectObject(&m_ImageDown);
		    dc.BitBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory, 0, 0, SRCCOPY);
		    dcMemory.SelectObject(pOldBitmap);
		}
		else
		{
			if(m_bUseCustColor)
			{
				dc.FillSolidRect(rect,RGB(0,0,0));
				rect.DeflateRect(1,1);
				dc.FillSolidRect(rect,m_crCustomColor);	
				if(m_bUseGradientFill)
				{
					TRIVERTEX        vert[2] ;
					GRADIENT_RECT    gRect;
					vert[0] .x      = rect.left;
					vert[0] .y      = rect.Height();
					vert[0] .Red    = 0x0000;
					vert[0] .Green  = 0x0000;
					vert[0] .Blue   = 0x0000;
					vert[0] .Alpha  = 0x0000;

					vert [1] .x      = rect.Width();
					vert [1] .y      = rect.Height() - rect.Height()/3; 
					vert [1] .Red    = GetRValue(m_crCustomColor)<<8;
					vert [1] .Green  = GetGValue(m_crCustomColor)<<8;
					vert [1] .Blue   = GetBValue(m_crCustomColor)<<8;
					vert [1] .Alpha  = 0x0000;

					gRect.UpperLeft  = 0;
					gRect.LowerRight = 1;
					GradientFill(dc.m_hDC,vert,2,&gRect,1,GRADIENT_FILL_RECT_V);
				}
			}
			else
				dc.FillSolidRect(rect,GetSysColor(COLOR_BTNFACE));

			dc.Draw3dRect(rect,GetSysColor(COLOR_3DDKSHADOW),GetSysColor(COLOR_3DHILIGHT));
			CString strText;
			GetWindowText(strText);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(m_crTextColor);
			dc.DrawText(strText,rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}
	}
	else // draw up image
	{
		if(m_bImageLoaded)
		{
			CDC dcMemory;
			dcMemory.CreateCompatibleDC(&dc);
			BITMAP bmpInfo;
		    m_Image.GetBitmap(&bmpInfo);
			CBitmap* pOldBitmap = dcMemory.SelectObject(&m_Image);
		    dc.BitBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory, 0, 0, SRCCOPY);
		    dcMemory.SelectObject(pOldBitmap);
		}
		else
		{
			if(m_bUseCustColor)
			{
				dc.FillSolidRect(rect,RGB(0,0,0));
				rect.DeflateRect(1,1);
				dc.FillSolidRect(rect,m_crCustomColor);
				if(m_bUseGradientFill)
				{
					TRIVERTEX        vert[2];
					GRADIENT_RECT    gRect;
					vert[0] .x      = rect.left;
					vert[0] .y      = rect.Height();
					vert[0] .Red    = 0x0000;
					vert[0] .Green  = 0x0000;
					vert[0] .Blue   = 0x0000;
					vert[0] .Alpha  = 0x0000;

					vert [1] .x      = rect.Width();
					vert [1] .y      = rect.Height() - rect.Height()/3; 
					vert [1] .Red    = GetRValue(m_crCustomColor)<<8;
					vert [1] .Green  = GetGValue(m_crCustomColor)<<8;
					vert [1] .Blue   = GetBValue(m_crCustomColor)<<8;
					vert [1] .Alpha  = 0x0000;

					gRect.UpperLeft  = 0;
					gRect.LowerRight = 1;
					GradientFill(dc.m_hDC,vert,2,&gRect,1,GRADIENT_FILL_RECT_V);
				}
			}
			else
			{
				dc.FillSolidRect(rect,GetSysColor(COLOR_BTNFACE));
			}
			
			dc.Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DDKSHADOW));
			CString strText;
			GetWindowText(strText);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(m_crTextColor);
			dc.DrawText(strText,rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}
	}
}

// set tool tip for this button
void CMyButton::SetToolTip(CString strText)
{
	if (!IsWindow(m_ToolTip.m_hWnd))
	{
		m_ToolTip.Create(this);
	}
	BOOL bOK;
	// If there is no tooltip defined then add it
	if (m_ToolTip.GetToolCount() == 0)
	{
		CRect rectBtn; 
		GetClientRect(rectBtn);
		bOK = m_ToolTip.AddTool(this, strText, rectBtn,1);
	}
	else
	{
		// Set text for tooltip
		m_ToolTip.UpdateTipText(strText, this,1);
	}
	m_ToolTip.Activate(true);
}

BOOL CMyButton::PreTranslateMessage(MSG* pMsg)
{
	if(IsWindow(m_ToolTip.m_hWnd))
		m_ToolTip.RelayEvent(pMsg);

	return CButton::PreTranslateMessage(pMsg);
}
