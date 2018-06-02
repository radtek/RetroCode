// AuthorizeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\SteveMediaCenter.h"
#include "AuthorizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAuthorizeDlg dialog


CAuthorizeDlg::CAuthorizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAuthorizeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAuthorizeDlg)
	m_strUserName = _T("");
	m_strPassword = _T("");
	m_strPassword2 = _T("");
	//}}AFX_DATA_INIT
}

CAuthorizeDlg::CAuthorizeDlg(CString strUser,CString strPass)
	: CDialog(CAuthorizeDlg::IDD, NULL)
{
	m_strUserName = _T(strUser);
	m_strPassword = _T(strPass);
	m_strPassword2 = _T(strPass);
}

void CAuthorizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAuthorizeDlg)
	DDX_Text(pDX, IDC_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_PASSWORD2, m_strPassword2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAuthorizeDlg, CDialog)
	//{{AFX_MSG_MAP(CAuthorizeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAuthorizeDlg message handlers

void CAuthorizeDlg::OnOK() 
{
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	UpdateData(TRUE);

	m_strUserName.TrimRight();
	m_strPassword.TrimRight();
	m_strPassword2.TrimRight();

	if(m_strPassword != m_strPassword2)
	{
		AfxMessageBox("Error passwords do not match");
		return;
	}

	// save to password file
	CString strData;
	strData.Format("<UserName>%s</UserName><Password>%s</Password>",m_strUserName,m_strPassword);

	CString strBasePath;
	GetModuleFileName(NULL,strBasePath.GetBuffer(255),255);
	strBasePath.ReleaseBuffer();
	strBasePath = strBasePath.Left(strBasePath.ReverseFind('\\')+1);
	strBasePath += "auth.dat";
	TRY
	{
		SECCryptoFile fp;
		if(fp.Open(strBasePath,"duyb783slp", CFile::modeCreate|CFile::modeWrite,SECCryptoFile::ECB))
		{
			int nLen = strData.GetLength();
			fp.Write(strData.GetBuffer(nLen),nLen);
			strData.ReleaseBuffer();
			fp.Close();
		}
	}
	CATCH(CFileException, e)
	{
	}
	END_CATCH
	
	// update memory variables
	pApp->m_strProxyUserName = m_strUserName;
	pApp->m_strProxyPassword = m_strPassword;

	CDialog::OnOK();
}

BOOL CAuthorizeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
