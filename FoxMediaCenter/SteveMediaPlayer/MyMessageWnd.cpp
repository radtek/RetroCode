// MyMessageWnd.cpp : implementation file
//

#include "stdafx.h"
#include "MyMessageWnd.h"

#include "SteveMediaPlayerCtl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyMessageWnd

CMyMessageWnd::CMyMessageWnd()
{
}

CMyMessageWnd::~CMyMessageWnd()
{
}


BEGIN_MESSAGE_MAP(CMyMessageWnd, CWnd)
	//{{AFX_MSG_MAP(CMyMessageWnd)
	ON_WM_CREATE()
	ON_WM_COPYDATA()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyMessageWnd message handlers

int CMyMessageWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	return 0;
}

BOOL CMyMessageWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	
	LPCSTR szClass = MEDIA_PLAYER_CLASSNAME;

	WNDCLASS wndcls;
	// register a new class
	HINSTANCE hInst = AfxGetInstanceHandle();
	wndcls.style = 0;
	wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
	wndcls.hInstance = hInst;
	wndcls.hIcon = NULL;
	wndcls.hCursor = NULL;
	wndcls.hbrBackground = NULL;
	wndcls.lpszMenuName = NULL;
	wndcls.lpszClassName = szClass;
	BOOL bOK = AfxRegisterClass(&wndcls);

	cs.lpszClass = szClass;
	
	if( !CWnd::PreCreateWindow(cs))
		return FALSE;
	
	return TRUE;
}

BOOL CMyMessageWnd::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	CSteveMediaPlayerCtrl* pMain = (CSteveMediaPlayerCtrl*)m_pParent;

	if(IsWindow(m_pParent->m_hWnd))
		return pMain->OnCopyData(pWnd, pCopyDataStruct);
	else
		return FALSE;
}
