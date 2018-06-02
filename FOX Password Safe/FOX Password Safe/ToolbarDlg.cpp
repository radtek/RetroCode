// ToolbarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "ToolbarDlg.h"


// CToolbarDlg dialog

IMPLEMENT_DYNAMIC(CToolbarDlg, CDialog)
CToolbarDlg::CToolbarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolbarDlg::IDD, pParent)
{
}

CToolbarDlg::~CToolbarDlg()
{
}

void CToolbarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolbarDlg, CDialog)
END_MESSAGE_MAP()


// CToolbarDlg message handlers
