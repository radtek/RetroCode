// MySeekSliderWnd.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenterOcx.h"
#include "SeekWnd.h"
#include "MySeekSliderWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySeekSliderWnd

CMySeekSliderWnd::CMySeekSliderWnd()
{
	m_bMouseDown = FALSE;
	m_lSliderPos = 0;
	m_dwMax = 0;
	m_dwMin = 0;
	m_dwBkColor = RGB(0,0,0);
	m_dwLineColor = 0x3B3E43;//0x07A007;
	m_pParent = NULL;
}

CMySeekSliderWnd::~CMySeekSliderWnd()
{
}


BEGIN_MESSAGE_MAP(CMySeekSliderWnd, CWnd)
	//{{AFX_MSG_MAP(CMySeekSliderWnd)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMySeekSliderWnd message handlers

int CMySeekSliderWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CMySeekSliderWnd::Init()
{
	if(!IsWindow(m_hWnd))
		return;

	CRect rect;
	GetClientRect(rect);

	m_nVold_Width = rect.Width()-10;
	m_nVol_Start = 10;

	int nMins = m_dwMax / 60;
	int nSecs = m_dwMax - (nMins * 60);
	if(nSecs < 10)
		m_strMax.Format("%u:0%u",nMins,nSecs);
	else
		m_strMax.Format("%u:%u",nMins,nSecs);

	m_strMin.Format("0:00",m_dwMin);
}

void CMySeekSliderWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	m_bMouseDown = TRUE;
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CMySeekSliderWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bMouseDown = FALSE;
	int nX = point.x;
	if(nX < m_nVol_Start)
		nX = m_nVol_Start;
	if(nX > m_nVold_Width)
		nX = m_nVold_Width;
	SetPos(nX);
	InvalidateRect(NULL);

	CWnd::OnLButtonUp(nFlags, point);
	
	ReleaseCapture();
}

void CMySeekSliderWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);
	if(m_bMouseDown)
	{
		CRect rect;
		GetClientRect(rect);
		SetPos(point.x,false);
		InvalidateRect(NULL);
	} 
}

void CMySeekSliderWnd::SetPos(ULONG lPos,BOOL bSeek)
{
	if(lPos > m_nVold_Width || lPos < m_nVol_Start)
		return;
	
	m_lSliderPos = lPos;
	float fNum = 0;
	if(lPos > 0)
		fNum = (float)(lPos-m_nVol_Start) / (float)(m_nVold_Width-m_nVol_Start);
	DWORD nNum = (float)(m_dwMax) * fNum;

	if(nNum > m_dwMax)
		nNum = m_dwMax;
	if(bSeek)
		m_pParent->SetPosition(nNum);
}

ULONG CMySeekSliderWnd::GetPos()
{
	DWORD pos = 0;
	pos = m_pParent->GetPosition();

	float fNum = (float)pos / (float)m_dwMax;
	m_lSliderPos = (float)((m_nVold_Width-m_nVol_Start) * fNum + m_nVol_Start);
	
	if(m_lSliderPos > m_nVold_Width)
		m_lSliderPos = m_nVold_Width;
	if(m_lSliderPos < m_nVol_Start)
		m_lSliderPos = m_nVol_Start;

	return m_lSliderPos;
}

void CMySeekSliderWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(rect);

	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmMem; 
	bmMem.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
	CBitmap* pBm = dcMem.SelectObject(&bmMem);

	// draw BK
	CBrush brBkGnd;
	brBkGnd.CreateSolidBrush(m_dwBkColor);
	dcMem.FillRect(rect,&brBkGnd);

	// draw line
	CBrush brLine;
	brLine.CreateSolidBrush(m_dwLineColor);
	CRect rectLine = rect;
	rectLine.top = (rect.Height() / 3) - 1;
	rectLine.bottom = rectLine.top + 2;
	dcMem.FillRect(rectLine,&brLine);

	// draw text
	if(!m_strText.IsEmpty())
	{
		CFont font;
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));      
		lf.lfHeight = 100;                
		lstrcpy(lf.lfFaceName, "Courier New");
		font.CreatePointFontIndirect(&lf, &dcMem);

		CFont* pOld;
		pOld = dcMem.SelectObject(&font);

		CString str;
		dcMem.SetTextColor(0x00D500);
		dcMem.SetBkMode(TRANSPARENT);
		dcMem.DrawText(m_strMin,rect,DT_BOTTOM|DT_LEFT|DT_SINGLELINE);
		dcMem.DrawText(m_strText,rect,DT_BOTTOM|DT_CENTER|DT_SINGLELINE);
		dcMem.DrawText(m_strMax,rect,DT_BOTTOM|DT_RIGHT|DT_SINGLELINE);
		dcMem.SelectObject(pOld);			
	}

	// draw slider
	CBitmap bm;
	bm.LoadBitmap(IDB_SLIDER);
	BITMAP bmStruct;
	bm.GetBitmap(&bmStruct);
	int nXBit = bmStruct.bmWidth;
	int nYBit = bmStruct.bmHeight;
	int cx = m_lSliderPos - (nXBit / 2);
	int cy = (rect.Height() - nYBit) / 3;

	SECDib imgBm;
	imgBm.CreateFromBitmap(&dcMem,&bm);
	SECImage* pImage = &imgBm;
	pImage->StretchDIBits(&dcMem,cx,cy,nXBit,nYBit,
		  0,0,nXBit,nYBit,pImage->m_lpSrcBits,pImage->m_lpBMI, DIB_RGB_COLORS,SRCCOPY );

	dc.BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);
	dcMem.SelectObject(pBm);
	dcMem.DeleteDC();	
}

void CMySeekSliderWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	CRect rect;
	GetClientRect(rect);

	m_nVold_Width = rect.Width()-10;
	m_nVol_Start = 10;
}

void CMySeekSliderWnd::UpdatePosition(DWORD dwSecs)
{
	if(m_bMouseDown)
		return;

	int nMins = dwSecs / 60;
	int nSecs = dwSecs - (nMins * 60);
	if(nSecs < 10)
		m_strText.Format("%u:0%u",nMins,nSecs);
	else
		m_strText.Format("%u:%u",nMins,nSecs);

	if(dwSecs == 0)
		m_lSliderPos = m_nVol_Start;
	else
	{
		float fNum = 0;
		fNum = dwSecs / (float)(m_dwMax - m_dwMin);
		DWORD lPos = (m_nVold_Width) * fNum;

		if(lPos > m_nVold_Width)
			lPos = m_nVold_Width;
		else if(lPos < m_nVol_Start)
			lPos = m_nVol_Start;
		
		m_lSliderPos = lPos;
	}
	if(IsWindow(m_hWnd))
		InvalidateRect(NULL);
}
