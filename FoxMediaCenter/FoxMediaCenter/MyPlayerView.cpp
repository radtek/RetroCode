// MyPlayerView.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "MyPlayerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPlayerView

IMPLEMENT_DYNCREATE(CMyPlayerView, CHtmlView)

CMyPlayerView::CMyPlayerView()
{
	//{{AFX_DATA_INIT(CMyPlayerView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMyPlayerView::~CMyPlayerView()
{
}

void CMyPlayerView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPlayerView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPlayerView, CHtmlView)
	//{{AFX_MSG_MAP(CMyPlayerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPlayerView diagnostics

#ifdef _DEBUG
void CMyPlayerView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMyPlayerView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPlayerView message handlers
