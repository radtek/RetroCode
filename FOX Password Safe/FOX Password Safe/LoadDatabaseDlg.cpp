// LoadDatabaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "LoadDatabaseDlg.h"
#include ".\loaddatabasedlg.h"
#include "helpers.h"
#include "NewDatabaseDlg.h"

// CLoadDatabaseDlg dialog
IMPLEMENT_DYNAMIC(CLoadDatabaseDlg, CDialog)
CLoadDatabaseDlg::CLoadDatabaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadDatabaseDlg::IDD, pParent)
	, m_strFilePath(_T(""))
	, m_strPassword(_T(""))
{
}

CLoadDatabaseDlg::~CLoadDatabaseDlg()
{
}

void CLoadDatabaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILE_PATH, m_strFilePath);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(CLoadDatabaseDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_NEW, OnBnClickedButtonCreateNew)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CLoadDatabaseDlg message handlers
BOOL CLoadDatabaseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strFilePath = MyGetProfileString("LastDataPath","");
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CLoadDatabaseDlg::OnBnClickedButtonBrowse()
{
	UpdateData(false);
	static char BASED_CODE szFilter[] = "FOX Password Safe Files (*.fps)|*.fps|All Files (*.*)|*.*||";
	CFileDialog dlg(true,"fps","My passwords",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(dlg.DoModal() == IDOK)
	{
		m_strFilePath = dlg.GetPathName();
		UpdateData(false);
	}
}

void CLoadDatabaseDlg::OnBnClickedButtonCreateNew()
{
	UpdateData(false);
	CNewDatabaseDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_strFilePath = dlg.GetPathName();
		m_strPassword = dlg.GetPassword();
		MyWriteProfileString("LastDataPath",m_strFilePath);
		UpdateData(false);
		
		OnOK();
	}
}

// return path to selected database
CString CLoadDatabaseDlg::GetPathName(void)
{
	return m_strFilePath;
}

void CLoadDatabaseDlg::OnBnClickedOk()
{
	UpdateData(true);
	if(!FileExists(m_strFilePath))
	{
		AfxMessageBox("Error, database file does not exist.");
		return;
	}
	if(m_strPassword.IsEmpty())
	{
		AfxMessageBox("Error, you must enter the password for this database.");
		return;
	}
	MyWriteProfileString("LastDataPath",m_strFilePath);
	OnOK();
}

// returns entered password
CString CLoadDatabaseDlg::GetPassword(void)
{
	return m_strPassword;
}
