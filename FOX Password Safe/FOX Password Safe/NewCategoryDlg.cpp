// NewCategoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "NewCategoryDlg.h"
#include ".\newcategorydlg.h"


// CNewCategoryDlg dialog

IMPLEMENT_DYNAMIC(CNewCategoryDlg, CDialog)
CNewCategoryDlg::CNewCategoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewCategoryDlg::IDD, pParent)
	, m_strCatName(_T(""))
	, m_strCurrentHeader(_T(""))
{
}

CNewCategoryDlg::~CNewCategoryDlg()
{
}

void CNewCategoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEW_NAME, m_strCatName);
}


BEGIN_MESSAGE_MAP(CNewCategoryDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CNewCategoryDlg message handlers
void CNewCategoryDlg::OnBnClickedOk()
{
	UpdateData(true);
	if(m_strCatName.IsEmpty())
	{
		AfxMessageBox("Error you must enter a name.");
		return;
	}
	OnOK();
}

// return new category name
CString CNewCategoryDlg::GetNewName(void)
{
	return m_strCatName;
}

BOOL CNewCategoryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// edit if m_strCurrentHeader is not empty
	if(!m_strCurrentHeader.IsEmpty())
	{
		SetWindowText("FOX Password Safe - Edit Category");
		m_strCatName = m_strCurrentHeader;
		UpdateData(false);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
