// SearchBarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "SearchBarDlg.h"
#include ".\searchbardlg.h"


// CSearchBarDlg dialog

IMPLEMENT_DYNAMIC(CSearchBarDlg, CDialog)
CSearchBarDlg::CSearchBarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchBarDlg::IDD, pParent)
{
}

CSearchBarDlg::~CSearchBarDlg()
{
}

void CSearchBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_ctlSearch);
}

BEGIN_MESSAGE_MAP(CSearchBarDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
END_MESSAGE_MAP()

BOOL CSearchBarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bmSearch2.LoadBitmap(IDB_FILE_FIND2);
	m_bmSearch1.LoadBitmap(IDB_FILE_FIND1);
	m_ctlSearch.SetBitmaps(m_bmSearch2,RGB(0,255,0),m_bmSearch1,RGB(0,255,0));

	return TRUE;  // return TRUE unless you set the focus to a control
}

// CSearchBarDlg message handlers
void CSearchBarDlg::OnBnClickedButtonSearch()
{
	AfxMessageBox("Click search");
}
