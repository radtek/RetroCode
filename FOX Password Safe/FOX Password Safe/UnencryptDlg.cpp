// UnencryptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "UnencryptDlg.h"
#include ".\unencryptdlg.h"
#include "helpers.h"

// CUnencryptDlg dialog

IMPLEMENT_DYNAMIC(CUnencryptDlg, CDialog)
CUnencryptDlg::CUnencryptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUnencryptDlg::IDD, pParent)
	, m_strPath(_T(""))
	, m_strPassword(_T(""))
	, m_strPathUnencrypted(_T(""))
{
}

CUnencryptDlg::~CUnencryptDlg()
{
}

void CUnencryptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILE_PATH, m_strPath);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT3, m_strPathUnencrypted);
}

BEGIN_MESSAGE_MAP(CUnencryptDlg, CDialog)
	ON_BN_CLICKED(IDC_BROWSE, OnBnClickedBrowse)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BROWSE2, OnBnClickedBrowse2)
END_MESSAGE_MAP()


// CUnencryptDlg message handlers

void CUnencryptDlg::OnBnClickedBrowse()
{
	CFileDialog dlg(true);
	if(dlg.DoModal())
	{
		m_strPath = dlg.GetPathName();
		if(m_strPathUnencrypted.IsEmpty())
			m_strPathUnencrypted = m_strPath.Left(m_strPath.ReverseFind('.'));
		UpdateData(false);
	}
}

void CUnencryptDlg::OnBnClickedOk()
{
	UpdateData(true);
	if(!FileExists(m_strPath))
	{
		AfxMessageBox("Error, please enter the correct path to the file you wish to unencrypt.");
		return;
	}
	if(m_strPathUnencrypted.IsEmpty())
	{
		AfxMessageBox("Error, please enter a path to save the unencrypted file to.");
		return;
	}

	CString strData = ReplaceXML(m_strPathUnencrypted,"FilePath","");
	strData = ReplaceXML(m_strPath,"EncFilePath",strData);
	strData = ReplaceXML(m_strPassword,"Password",strData);

	if(!UnEncryptFile(strData,false))
	{
		AfxMessageBox("Error unencrypting file.");
		return;
	}
	AfxMessageBox("File has been unencrypted successfully.");

	OnOK();
}

void CUnencryptDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CUnencryptDlg::OnBnClickedBrowse2()
{
	CFileDialog dlg(true);
	if(dlg.DoModal())
	{
		m_strPathUnencrypted = dlg.GetPathName();
		UpdateData(false);
	}
}
