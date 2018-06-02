// NagDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "NagDlg.h"
#include ".\nagdlg.h"
#include "helpers.h"
#include "EnterRegCode.h"

// CNagDlg dialog

IMPLEMENT_DYNAMIC(CNagDlg, CDialog)
CNagDlg::CNagDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNagDlg::IDD, pParent)
	, m_strTextMsg(_T(""))
{
}

CNagDlg::~CNagDlg()
{
}

void CNagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT_MSG, m_strTextMsg);
}


BEGIN_MESSAGE_MAP(CNagDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ORDER, OnBnClickedButtonOrder)
	ON_BN_CLICKED(IDC_BUTTON_ENTER_CODE, OnBnClickedButtonEnterCode)
END_MESSAGE_MAP()


// CNagDlg message handlers

void CNagDlg::OnBnClickedOk()
{
	OnOK();
}

void CNagDlg::OnBnClickedButtonOrder()
{
	LoadURLInBrowser(GetRegisterURL());
}

void CNagDlg::OnBnClickedButtonEnterCode()
{
	CEnterRegCode dlg;
	dlg.DoModal();	
}

BOOL CNagDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	int nDaysUsed = GetFreeTrialDaysUsed();
	if(nDaysUsed > 30)
		m_strTextMsg.Format("Your evaluation period has expired. You need to register the software or uninstall it.");
	else
		m_strTextMsg.Format("You are entitled to evaluate this software free of charge for another %d days.",30 - GetFreeTrialDaysUsed());
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
