// FullScreenWnd.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaPlayer.h"
#include "FullScreenWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFullScreenWnd

CFullScreenWnd::CFullScreenWnd()
{
}

CFullScreenWnd::~CFullScreenWnd()
{
}


BEGIN_MESSAGE_MAP(CFullScreenWnd, CWnd)
	//{{AFX_MSG_MAP(CFullScreenWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFullScreenWnd message handlers

void CFullScreenWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(rect);

	CBrush brBkGnd;
	brBkGnd.CreateSolidBrush(0x000000);
	dc.FillRect(rect,&brBkGnd);

}
