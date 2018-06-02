// VolumeWnd.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenterOcx.h"
#include "VolumeWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVolumeWnd

CVolumeWnd::CVolumeWnd()
{
}

CVolumeWnd::~CVolumeWnd()
{
}


BEGIN_MESSAGE_MAP(CVolumeWnd, CWnd)
	//{{AFX_MSG_MAP(CVolumeWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CVolumeWnd message handlers

int CVolumeWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(rect);
	CRect rectWave = rect;
	rect.right = rect.left + (rect.Width() /2) - 2;
	rectWave.left = rect.right + 2; 

	BOOL bOK = m_ctlVolume.Create(NULL,"Volume",WS_CHILD|WS_VISIBLE,rect,this,4100);
	bOK = m_ctlWave.Create(NULL,"Wave",WS_CHILD|WS_VISIBLE,rectWave,this,4101);

	m_ctlVolume.m_strText = "Volume";
	m_ctlWave.m_strText = "Wave";
	m_ctlVolume.Init();
	m_ctlWave.m_bIsWave = true;
	m_ctlWave.Init();
	
	return 0;
}

void CVolumeWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	CRect rect;
	GetClientRect(rect);
	CRect rectWave = rect;
	rect.right = rect.left + (rect.Width() /2) - 2;
	rectWave.left = rect.right + 2; 

	m_ctlVolume.MoveWindow(rect);
	m_ctlWave.MoveWindow(rectWave);	
}

void CVolumeWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(rect);

	CBrush brBkGnd;
	brBkGnd.CreateSolidBrush(0x000000);
	dc.FillRect(rect,&brBkGnd);

}
