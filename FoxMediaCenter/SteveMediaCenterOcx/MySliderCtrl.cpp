// MySliderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenterOcx.h"
#include "MySliderCtrl.h"
#include "VolumeControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySliderCtrl

CMySliderCtrl::CMySliderCtrl()
{
	m_bMouseDown = FALSE;
	m_lSliderPos = 0;
	m_dwMax = 0;
	m_dwMin = 0;
	m_dwBkColor = RGB(0,0,0);
	m_dwLineColor = 0x3B3E43;//0x07A007;

	m_bIsWave = false;
}

CMySliderCtrl::~CMySliderCtrl()
{
}


BEGIN_MESSAGE_MAP(CMySliderCtrl, CWnd)
	//{{AFX_MSG_MAP(CMySliderCtrl)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_MESSAGE(MM_MIXM_CONTROL_CHANGE, OnMixerCtrlChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySliderCtrl message handlers

int CMySliderCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CMySliderCtrl::Init()
{
	CRect rect;
	GetClientRect(rect);

	m_nVold_Width = rect.Width()-20;
	m_nVol_Start = 10;

	DWORD nValue = 0;
	nValue = GetPos();
	m_lSliderPos = nValue;
}

void CMySliderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	m_bMouseDown = TRUE;
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CMySliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bMouseDown = FALSE;
	CRect rect;
	GetClientRect(rect);
	SetPos(point.x);
	InvalidateRect(NULL);

	CWnd::OnLButtonUp(nFlags, point);
	
	ReleaseCapture();
}

void CMySliderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);
	if(m_bMouseDown)
	{
		CRect rect;
		GetClientRect(rect);
		SetPos(point.x);
		InvalidateRect(NULL);
	}
}

LONG CMySliderCtrl::OnMixerCtrlChange(UINT wParam, LONG lParam)
{
	return 0L;

/*	DWORD vol;
	CVolumeControl volCtl;
	if(volCtl.Open(GetSafeHwnd()))
	{
		if ((HMIXER)wParam == volCtl.GetMixerID() && (DWORD)lParam == volCtl.GetVolumeID())
		{
			if (volCtl.GetCurrentVolume(&vol))
				SetPos(m_dwMax-vol);
		}
		volCtl.Close();
	} 
	return 0L; */
}

void CMySliderCtrl::SetPos(ULONG lPos)
{
	if(lPos > m_nVold_Width)
		lPos = m_nVold_Width;
	else if(lPos < m_nVol_Start)
		lPos = m_nVol_Start;
	
	m_lSliderPos = lPos;
	float fNum = 0;
	if(lPos > 0)
		fNum = (float)(lPos-m_nVol_Start) / (float)(m_nVold_Width-m_nVol_Start);
	DWORD nNum = (float)(m_dwMax) * fNum;

	if(nNum > m_dwMax)
		nNum = m_dwMax;
	CVolumeControl volCtl;
	if(m_bIsWave)
	{
		volCtl.WaveSetVolume(nNum);
	}
	else if(volCtl.Open(GetSafeHwnd()))
	{
		volCtl.SetVolume(nNum);
		volCtl.Close();
	}
}

ULONG CMySliderCtrl::GetPos()
{
	DWORD max, min, vol;
	CVolumeControl volCtl;
	if(m_bIsWave)
	{
		vol = volCtl.WaveGetVolume();
		m_dwMax = volCtl.WaveGetMax();
		m_dwMin = volCtl.WaveGetMin();
	}
	else if(volCtl.Open(GetSafeHwnd()))
	{
		volCtl.GetMaxMin(&max, &min);
		m_dwMax = max;
		m_dwMin = min;
		volCtl.GetCurrentVolume(&vol);
		volCtl.Close();
	}
	float fNum = (float)vol / (float)m_dwMax;
	m_lSliderPos = (float)((m_nVold_Width-m_nVol_Start) * fNum + m_nVol_Start);

	if(m_lSliderPos > m_nVold_Width)
		m_lSliderPos = m_nVold_Width;
	if(m_lSliderPos < m_nVol_Start)
		m_lSliderPos = m_nVol_Start;

	return m_lSliderPos;
}

void CMySliderCtrl::OnPaint() 
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

		dcMem.SetTextColor(0x00D500);
		dcMem.SetBkMode(TRANSPARENT);
		dcMem.DrawText(" - ",rect,DT_BOTTOM|DT_LEFT|DT_SINGLELINE);
		dcMem.DrawText(m_strText,rect,DT_BOTTOM|DT_CENTER|DT_SINGLELINE);
		dcMem.DrawText(" + ",rect,DT_BOTTOM|DT_RIGHT|DT_SINGLELINE);

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
