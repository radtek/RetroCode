// NewDatabaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "NewDatabaseDlg.h"
#include ".\newdatabasedlg.h"
#include "helpers.h"

// CNewDatabaseDlg dialog

IMPLEMENT_DYNAMIC(CNewDatabaseDlg, CDialog)
CNewDatabaseDlg::CNewDatabaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewDatabaseDlg::IDD, pParent)
	, m_strPassword(_T(""))
	, m_strPassword2(_T(""))
	, m_bCreateDefaultCat(FALSE)
{
}

CNewDatabaseDlg::~CNewDatabaseDlg()
{
}

void CNewDatabaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NEW_FILE_PATH, m_strFilePath);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_PASSWORD2, m_strPassword2);
	DDX_Check(pDX, IDC_CHECK_DEFAULT_CATEGORIES, m_bCreateDefaultCat);
}

BEGIN_MESSAGE_MAP(CNewDatabaseDlg, CDialog)
	ON_BN_CLICKED(IDC_BROWSE, OnBnClickedBrowse)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CNewDatabaseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bCreateDefaultCat = true;
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CNewDatabaseDlg::OnBnClickedBrowse()
{
	UpdateData(false);
	
	static char BASED_CODE szFilter[] = "FOX Password Safe Files (*.fps)|*.fps|All Files (*.*)|*.*||";
	CFileDialog dlg(false,"fps","My passwords",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(dlg.DoModal() == IDOK)
	{
		m_strFilePath = dlg.GetPathName();
		UpdateData(false);
	}
}

void CNewDatabaseDlg::OnBnClickedOk()
{
	UpdateData(true);

	if(m_strPassword != m_strPassword2)
	{
		AfxMessageBox("Error, passwords do not match. Please re-enter passwords.");
		return;
	}
	if(m_strPassword.IsEmpty())
	{
		AfxMessageBox("Error, passwords cannot be empty");
		return;
	}
	CString strPath = m_strFilePath.Left(m_strFilePath.ReverseFind('\\'));
	if(!DirectoryExists(strPath))
	{
		MyMakePath(strPath);
	}
	CString strVer;
	if(m_bCreateDefaultCat)
		strVer.Format("<Version>%s<Entry><Header>%s</Header></Entry><Entry><Header>%s</Header></Entry><Entry><Header>%s</Header></Entry></Version>",
		VERSION,_T("Email accounts"),_T("Web sites"),_T("Credit Cards"));
	else
		strVer.Format("<Version>%s</Version>",VERSION);
	if(!WriteEncryptedFile(m_strFilePath,m_strPassword,strVer))
	{
		AfxMessageBox("Error, failed to save database... " + m_strFilePath);
		return;
	}	

	AfxMessageBox("Database created OK. It is VERY important you write down the password you just used and keep it somewhere safe. You can also print it out from the 'File/Print' menu.");

	OnOK();
}

// return path to new database file
CString CNewDatabaseDlg::GetPathName(void)
{
	return m_strFilePath;
}

// return new password
CString CNewDatabaseDlg::GetPassword(void)
{
	return m_strPassword;
}


