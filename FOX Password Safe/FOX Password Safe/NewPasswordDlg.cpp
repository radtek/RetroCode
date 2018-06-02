// NewPasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "NewPasswordDlg.h"
#include ".\newpassworddlg.h"
#include "helpers.h"

// CNewPasswordDlg dialog

IMPLEMENT_DYNAMIC(CNewPasswordDlg, CDialog)
CNewPasswordDlg::CNewPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewPasswordDlg::IDD, pParent)
	, m_strPass(_T(""))
	, m_strNewPass1(_T(""))
	, m_strNewPass2(_T(""))
	, m_strCurrentLoadedPath(_T(""))
{
}

CNewPasswordDlg::~CNewPasswordDlg()
{
}

void CNewPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CURRENT_PASS, m_strPass);
	DDX_Text(pDX, IDC_EDIT_NEW_PASS, m_strNewPass1);
	DDX_Text(pDX, IDC_EDIT_REPEAT_PASS, m_strNewPass2);
}


BEGIN_MESSAGE_MAP(CNewPasswordDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CNewPasswordDlg message handlers

void CNewPasswordDlg::OnBnClickedOk()
{
	UpdateData(true);

	if(m_strNewPass1 != m_strNewPass2)
	{
		AfxMessageBox("Error, new passwords do not match. Please try again.");
		return;
	}
	if(m_strNewPass1.IsEmpty())
	{
		AfxMessageBox("Error, please enter a new password.");
		return;
	}

	CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strPass);
	if(strData.IsEmpty())
	{
		AfxMessageBox("Error, database password incorrect, please try again.");
		return;
	}
	if(!WriteEncryptedFile(m_strCurrentLoadedPath,m_strNewPass1,strData))
	{
		AfxMessageBox("Error saving new password.");
		return;
	}
	AfxMessageBox("New password saved OK. You need to write down this new password or print out your list of passwords so you don't forget it.");

	OnOK();
}
