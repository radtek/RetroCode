// BackupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "BackupDlg.h"
#include ".\backupdlg.h"
#include "helpers.h"

// CBackupDlg dialog

IMPLEMENT_DYNAMIC(CBackupDlg, CDialog)
CBackupDlg::CBackupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBackupDlg::IDD, pParent)
	, m_strFileName(_T(""))
	, m_strPath(_T(""))
	, m_strPassword(_T(""))
	, m_strCurrentLoadedPath(_T(""))
{
}

CBackupDlg::~CBackupDlg()
{
}

void CBackupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strPath);
}


BEGIN_MESSAGE_MAP(CBackupDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

// CBackupDlg message handlers
void CBackupDlg::OnBnClickedButtonBrowse()
{
	static char BASED_CODE szFilter[] = "FOX Password Safe Files (*.fps)|*.fps|All Files (*.*)|*.*||";
	CFileDialog dlg(false,"fps",m_strFileName + ".fps",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(dlg.DoModal() == IDOK)
	{
		m_strPath = dlg.GetPathName();
		UpdateData(false);
	}
}

void CBackupDlg::OnBnClickedOk()
{
	UpdateData(true);
	// check path not empty
	if(m_strPath.IsEmpty())
	{
		AfxMessageBox("Error, you must select a path to save the backup file.");
		return;
	}
	// make sure path is valid
	CString strPath = m_strPath.Left(m_strPath.ReverseFind('\\'));
	if(!DirectoryExists(strPath))
	{
		if(!MyMakePath(strPath))
		{
			AfxMessageBox("Error, failed to create file please try again or select another location.");
			return;
		}
	}
	// read data, append original file path then save
	CWaitCursor wait;
	CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strPassword);
	if(ParseXML("Version",strData).IsEmpty())
	{
		wait.Restore();
		AfxMessageBox("Error, failed to read database... " + m_strCurrentLoadedPath);
		return;
	}
	strData = ReplaceXML(m_strCurrentLoadedPath,"OriginalPath",strData);
	if(!WriteEncryptedFile(m_strPath,m_strPassword,strData))
	{
		wait.Restore();
		AfxMessageBox("Error, failed to backup database... " + m_strPath);
		return;
	}	
	AfxMessageBox("Backup completed OK... ");
	OnOK();
}
