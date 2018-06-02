// SeekWnd.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenterOcx.h"
#include "SteveMediaCenterOcxCtl.h"
#include "SeekWnd.h"
#include "helpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeekWnd

CSeekWnd::CSeekWnd()
{
	m_pMain = NULL;
	m_wndSlider.m_pParent = this;
}

CSeekWnd::~CSeekWnd()
{
}


BEGIN_MESSAGE_MAP(CSeekWnd, CWnd)
	//{{AFX_MSG_MAP(CSeekWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSeekWnd message handlers

void CSeekWnd::SetPosition(DWORD dwPos)
{
	CString strMsg;
	strMsg.Format("<Message>SetCurrentPosition</Message><Position>%u</Position>",dwPos);
	SendMessageToInstanseOfApp(strMsg);
}

DWORD CSeekWnd::GetPosition()
{
	DWORD dwPos = 0;
	return dwPos;
}

int CSeekWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(rect);

	BOOL bOK = m_wndSlider.Create(NULL,"Seekwnd",WS_CHILD|WS_VISIBLE,rect,this,4106);

	m_wndSlider.m_strText = "Video seek position";
	m_wndSlider.Init();

	return 0;
}

void CSeekWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	CRect rect;
	GetClientRect(rect);

	m_wndSlider.MoveWindow(rect);
}

void CSeekWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(rect);

	CBrush brBkGnd;
	brBkGnd.CreateSolidBrush(0x000000);
	dc.FillRect(rect,&brBkGnd);	
}

void CSeekWnd::UpdatePosition(DWORD dwPos)
{
	m_wndSlider.UpdatePosition(dwPos);
}

void CSeekWnd::Init()
{
	m_wndSlider.Init();
}
