// RestoreDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "RestoreDlg.h"
#include ".\restoredlg.h"
#include "helpers.h"

// CRestoreDlg dialog

IMPLEMENT_DYNAMIC(CRestoreDlg, CDialog)
CRestoreDlg::CRestoreDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRestoreDlg::IDD, pParent)
	, m_strPath(_T(""))
	, m_strCurrentLoadedPath(_T(""))
	, m_strPathSaveFile(_T(""))
	, m_strPassword(_T(""))
{
}

CRestoreDlg::~CRestoreDlg()
{
}

void CRestoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strPath);
	DDX_Text(pDX, IDC_EDIT_PATH2, m_strPathSaveFile);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
}

BEGIN_MESSAGE_MAP(CRestoreDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE2, OnBnClickedButtonBrowse2)
	ON_BN_CLICKED(IDC_BUTTON_READ_LOCATION, OnBnClickedButtonReadLocation)
END_MESSAGE_MAP()


BOOL CRestoreDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(!m_strCurrentLoadedPath.IsEmpty())
		m_strPathSaveFile = m_strCurrentLoadedPath;

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CRestoreDlg::OnBnClickedButtonBrowse()
{
	UpdateData(false);
	static char BASED_CODE szFilter[] = "FOX Password Safe Files (*.fps)|*.fps|All Files (*.*)|*.*||";
	CFileDialog dlg(true,"fps",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(dlg.DoModal() == IDOK)
	{
		// file to restore
		m_strPath = dlg.GetPathName();
		// try and load restore to path if its empty
		if(m_strCurrentLoadedPath.IsEmpty() && !m_strPassword.IsEmpty())
		{
			CString strData = ReadEncryptedFile(m_strPath,m_strPassword);
			if(!ParseXML("Version",strData).IsEmpty())
			{			
				m_strPathSaveFile = ParseXML("OriginalPath",strData);
			}
		}
		UpdateData(false);
	}
}

void CRestoreDlg::OnBnClickedButtonBrowse2()
{
	UpdateData(false);
	static char BASED_CODE szFilter[] = "FOX Password Safe Files (*.fps)|*.fps|All Files (*.*)|*.*||";
	CFileDialog dlg(false,"fps",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(dlg.DoModal() == IDOK)
	{
		m_strPathSaveFile = dlg.GetPathName();
		UpdateData(false);
	}
}

void CRestoreDlg::OnBnClickedButtonReadLocation()
{
	UpdateData(true);
	if(m_strPath.IsEmpty())
	{
		AfxMessageBox("Please enter the location of the backed up database first.");
		return;
	}
	if(m_strPassword.IsEmpty())
	{
		AfxMessageBox("Please enter the password of the backed up database first.");
		return;
	}
	// read data then load original database location
	CWaitCursor wait;
	CString strData = ReadEncryptedFile(m_strPath,m_strPassword);
	if(ParseXML("Version",strData).IsEmpty())
	{
		wait.Restore();
		AfxMessageBox("Error, failed to read database... " + m_strPath);
		return;
	}
	m_strPathSaveFile = ParseXML("OriginalPath",strData);
	UpdateData(false);
}

void CRestoreDlg::OnBnClickedOk()
{
	UpdateData(true);
	// make sure restore path not empty
	if(m_strPath.IsEmpty())
	{
		AfxMessageBox("Error, you must enter a file to restore from.");
		return;
	}
	// make sure restore file exists
	if(!FileExists(m_strPath))
	{
		AfxMessageBox("Error, " + m_strPath + " does not exist.");
		return;
	}
	// make sure path is valid
	CString strPath = m_strPathSaveFile.Left(m_strPathSaveFile.ReverseFind('\\'));
	if(!DirectoryExists(strPath))
	{
		if(!MyMakePath(strPath))
		{
			AfxMessageBox("Error, failed to retsore file please try again or select another location to save the restored database.");
			return;
		}
	}	
	// read data, strip OriginalPath, then save to original database location
	CWaitCursor wait;
	CString strData = ReadEncryptedFile(m_strPath,m_strPassword);
	if(ParseXML("Version",strData).IsEmpty())
	{
		wait.Restore();
		AfxMessageBox("Error, failed to read database... " + m_strPath);
		return;
	}
	strData = ReplaceXML("","OriginalPath",strData);
	if(!WriteEncryptedFile(m_strPathSaveFile,m_strPassword,strData))
	{
		wait.Restore();
		AfxMessageBox("Error, failed to restore database... " + m_strPathSaveFile);
		return;
	}	
	MyWriteProfileString("LastDataPath",m_strPathSaveFile);
	AfxMessageBox("Restored database OK... ");
	OnOK();
}

// get path to loaded database
CString CRestoreDlg::GetPathName(void)
{
	return m_strPathSaveFile;
}

// get password to loaded file
CString CRestoreDlg::GetPassword(void)
{
	return m_strPassword;
}
