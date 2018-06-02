// MyBitMapButton.cpp : implementation file
//

#include "stdafx.h"
#include "MyBitMapButton.h"
#include "defines.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyBitMapButton

CMyBitMapButton::CMyBitMapButton()
{
	m_bDontShowHand = FALSE;
	m_pImg = new CBitmap;
	m_pImg2 = new CBitmap;
	m_pImg3 = new CBitmap;
	EnableToolTips(TRUE);
	m_hCursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE (IDC_HAND));

	LoadImage(IDB_BUTTON_UP);
	LoadImageDown(IDB_BUTTON_DOWN);
}

CMyBitMapButton::~CMyBitMapButton()
{
	delete m_pImg;
	delete m_pImg2;
	delete m_pImg3;
}


BEGIN_MESSAGE_MAP(CMyBitMapButton, CButton)
	//{{AFX_MSG_MAP(CMyBitMapButton)
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyBitMapButton message handlers

void CMyBitMapButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CString strText;
	GetWindowText(strText);
	
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	CRect ScreenRect(lpDrawItemStruct->rcItem);

	CDC dcScreen;
	dcScreen.CreateCompatibleDC(&dc);

	CBitmap bmMem; 
	bmMem.CreateCompatibleBitmap(&dc,ScreenRect.Width(),ScreenRect.Height());
	CBitmap* pOldBm = dcScreen.SelectObject(&bmMem);

	CBitmap* pImage;
	if(lpDrawItemStruct->itemAction == ODA_SELECT)   
		pImage = m_pImg2;	
	else if(lpDrawItemStruct->itemState == ODS_DISABLED)
		pImage = m_pImg3;
	else
		pImage = m_pImg;	

	BITMAP BitMap;
	pImage->GetBitmap(&BitMap);
	int cx = (int)BitMap.bmWidth;
	int cy = (int)BitMap.bmHeight;

	if(cx >0)
	{
		CBitmap* pOldBm = dcScreen.SelectObject(pImage);
		dc.StretchBlt(0,0,ScreenRect.Width(),ScreenRect.Height(),&dcScreen,0,0,cx,cy,SRCCOPY);

		dc.SetTextColor(RGB(255,255,255));
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(strText,ScreenRect,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		
		dcScreen.SelectObject(pOldBm);
	}

	dcScreen.DeleteDC();
	dc.Detach();
}

// Up image
void CMyBitMapButton::LoadImage(UINT nIDResource)
{
	TRY
	{
		m_pImg->LoadBitmap(nIDResource);
	}
	CATCH(CFileException, e)
	{
	}
	END_CATCH
}

// Down image
void CMyBitMapButton::LoadImageDown(UINT nIDResource)
{
	TRY
	{
		m_pImg2->LoadBitmap(nIDResource);
	}
	CATCH(CFileException, e)
	{
	}
	END_CATCH
}

// Ghosted image
void CMyBitMapButton::LoadImageGhost(UINT nIDResource)
{
	TRY
	{
		m_pImg3->LoadBitmap(nIDResource);
	}
	CATCH(CFileException, e)
	{
	}
	END_CATCH
}

void CMyBitMapButton::SetToolTip(UINT nText)
{
	CRect rect;
	GetClientRect(rect);
	m_ToolTip.DelTool(this,1);
	m_ToolTip.AddTool(this,nText, &rect,1);
	m_ToolTip.Activate(TRUE);
}

BOOL CMyBitMapButton::PreTranslateMessage(MSG* pMsg) 
{
	if(IsWindow(m_ToolTip.m_hWnd))
		m_ToolTip.RelayEvent(pMsg);
	return CButton::PreTranslateMessage(pMsg);
}

int CMyBitMapButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_ToolTip.Create(this, WS_VISIBLE|TTS_ALWAYSTIP);
	
	return 0;
}

BOOL CMyBitMapButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(m_bDontShowHand)
	{
		CButton::OnSetCursor(pWnd,nHitTest,message);
		return TRUE;
	}
	::SetCursor(m_hCursor);
	return FALSE;
}
