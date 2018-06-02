// EnterRegCode.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "EnterRegCode.h"
#include ".\enterregcode.h"
#include "helpers.h"
#include ".\mainfrm.h"
// CEnterRegCode dialog

IMPLEMENT_DYNAMIC(CEnterRegCode, CDialog)
CEnterRegCode::CEnterRegCode(CWnd* pParent /*=NULL*/)
	: CDialog(CEnterRegCode::IDD, pParent)
	, m_strName(_T(""))
	, m_strCompany(_T(""))
	, m_strRegCode(_T(""))
{
}

CEnterRegCode::~CEnterRegCode()
{
}

void CEnterRegCode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_COMPANY_NAME, m_strCompany);
	DDX_Text(pDX, IDC_EDIT_REG_CODE, m_strRegCode);
}


BEGIN_MESSAGE_MAP(CEnterRegCode, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CEnterRegCode message handlers

void CEnterRegCode::OnBnClickedOk()
{
	UpdateData(true);

	m_strRegCode.Trim();
	if(m_strRegCode.IsEmpty() || !IsRegCodeGood(m_strRegCode))
	{
		AfxMessageBox("Error, registration code is invalid, please copy and past all digits from the registration code you were given.");
		return;
	}
	MyWriteProfileString("Name",m_strName);
	MyWriteProfileString("Company",m_strCompany);
	MyWriteProfileString("Reg",m_strRegCode);

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	pMain->m_bHasFreeTrialExpired = false;

	MessageBox(CString(MY_APP_TITLE) + " is now fully registered.","Thank you");

	OnOK();
}

BOOL CEnterRegCode::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
