// ExpiredPasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "ExpiredPasswordDlg.h"
#include ".\expiredpassworddlg.h"
#include "helpers.h"

// CExpiredPasswordDlg dialog

IMPLEMENT_DYNAMIC(CExpiredPasswordDlg, CDialog)
CExpiredPasswordDlg::CExpiredPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExpiredPasswordDlg::IDD, pParent)
	, m_bDontShowAgain(FALSE)
{
}

CExpiredPasswordDlg::~CExpiredPasswordDlg()
{
}

void CExpiredPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_DONT_SHOW_AGAIN, m_bDontShowAgain);
}


BEGIN_MESSAGE_MAP(CExpiredPasswordDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CExpiredPasswordDlg message handlers

BOOL CExpiredPasswordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bDontShowAgain = false;
	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	
}

void CExpiredPasswordDlg::OnBnClickedOk()
{
	UpdateData(true);

	if(m_bDontShowAgain)
		MyWriteProfileInt("DontShowExpireDlg",1);

	OnOK();
}
