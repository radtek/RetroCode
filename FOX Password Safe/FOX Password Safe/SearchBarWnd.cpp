// SearchBarWnd.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "SearchBarWnd.h"
#include ".\searchbarwnd.h"


// CSearchBarWnd

IMPLEMENT_DYNAMIC(CSearchBarWnd, CWnd)
CSearchBarWnd::CSearchBarWnd()
{
}

CSearchBarWnd::~CSearchBarWnd()
{
}


BEGIN_MESSAGE_MAP(CSearchBarWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CSearchBarWnd message handlers
int CSearchBarWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_ctlEdit.Create(ES_MULTILINE|WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER,CRect(0,0,195,22),this,0);

	m_ctlSearch.Create("Search",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(197,0,197+70,22),this,IDC_BUTTON_SEARCH);
	m_bmSearch2.LoadBitmap(IDB_FILE_FIND2);
	m_bmSearch1.LoadBitmap(IDB_FILE_FIND1);
	m_ctlSearch.SetBitmaps(m_bmSearch2,RGB(0,255,0),m_bmSearch1,RGB(0,255,0));
	m_ctlSearch.CreateToolTip(_T("Search for an entry."));

	m_ctlShowAll.Create("Show All",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(200+70,0,200+152,22),this,IDC_BUTTON_SHOW_ALL);
	m_bmShowAll2.LoadBitmap(IDB_FILE_SHOWALL2);
	m_bmShowAll1.LoadBitmap(IDB_FILE_SHOWALL1);
	m_ctlShowAll.SetBitmaps(m_bmShowAll2,RGB(0,255,0),m_bmShowAll1,RGB(0,255,0));
	m_ctlShowAll.CreateToolTip(_T("Show all passwords."));

	return 0;
}

void CSearchBarWnd::OnPaint()
{
	CRect rect;
	GetClientRect(rect);
	CPaintDC dc(this); // device context for painting

	COLORREF col = GetSysColor(COLOR_BTNFACE);
	CBrush br;
	br.CreateSolidBrush(col);
	dc.FillRect(rect,&br);
}

BOOL CSearchBarWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	BOOL bOK = CWnd::OnCommand(wParam, lParam);
	AfxGetMainWnd()->PostMessage(WM_COMMAND,wParam,lParam);
	return bOK;
}

CString CSearchBarWnd::GetSearchText(void)
{
	CString strText;
	m_ctlEdit.GetWindowText(strText.GetBuffer(255),255);
	strText.ReleaseBuffer();
	return strText;
}

void CSearchBarWnd::SetEditFocus(void)
{
	if(IsWindow(m_ctlEdit.m_hWnd))
		m_ctlEdit.SetFocus();
}
