// WarningDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "WarningDlg.h"
#include ".\warningdlg.h"
#include "helpers.h"

// CWarningDlg dialog

IMPLEMENT_DYNAMIC(CWarningDlg, CDialog)
CWarningDlg::CWarningDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWarningDlg::IDD, pParent)
	, m_bDontShowAgain(FALSE)
	, m_strText(_T(""))
	, m_strRegistryTag(_T(""))
	, m_strTextStatic(_T(""))
{
}

CWarningDlg::~CWarningDlg()
{
}

void CWarningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_DONT_SHOW_AGAIN, m_bDontShowAgain);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_strTextStatic);
}

BEGIN_MESSAGE_MAP(CWarningDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

// CWarningDlg message handlers
void CWarningDlg::OnBnClickedOk()
{
	UpdateData(true);
	if(m_bDontShowAgain && !m_strRegistryTag.IsEmpty())
		MyWriteProfileInt(m_strRegistryTag,1);
	OnOK();
}

BOOL CWarningDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(!m_strText.IsEmpty())
		m_strTextStatic = m_strText;

	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
}
