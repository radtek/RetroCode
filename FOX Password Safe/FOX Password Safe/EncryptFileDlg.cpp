// EncryptFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "EncryptFileDlg.h"
#include ".\encryptfiledlg.h"
#include "helpers.h"


// CEncryptFileDlg dialog

IMPLEMENT_DYNAMIC(CEncryptFileDlg, CDialog)
CEncryptFileDlg::CEncryptFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEncryptFileDlg::IDD, pParent)
	, m_strText(_T(""))
	, m_strPlainFile(_T(""))
	, m_strEncryptFile(_T(""))
	, m_bIsEncrypting(true)
	, m_bCancelled(false)
	, m_bRemoveFile(true)
{
}

CEncryptFileDlg::~CEncryptFileDlg()
{
}

void CEncryptFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MSG, m_strText);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctlProgress);
}


BEGIN_MESSAGE_MAP(CEncryptFileDlg, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_ENDDLG_OK,OnEndDlgOK)
	ON_MESSAGE(WM_ENDDLG_CANCEL,OnEndDlgCANCEL)
END_MESSAGE_MAP()


// CEncryptFileDlg message handlers

BOOL CEncryptFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strText.Format(_T("%s file %s."),m_bIsEncrypting?_T("Encrypting"):_T("Decrypting"),m_strPlainFile);
	m_bError = false;
	m_ctlProgress.SetRange(0,100);
	if(m_bIsEncrypting)
		SetWindowText(_T("Encrytping please wait..."));
	else
		SetWindowText(_T("Decrytping please wait..."));

	UpdateData(false);
	AfxBeginThread(ProcEncrypt,this);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEncryptFileDlg::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
}

void CEncryptFileDlg::OnBnClickedCancel()
{
	m_bCancelled = true;
}

UINT CEncryptFileDlg::ProcEncrypt(LPVOID pParam)
{
	CEncryptFileDlg* pDlg = (CEncryptFileDlg*)pParam;
	
	CString strPath = pDlg->m_strPlainFile;
	CString strEncPath = pDlg->m_strEncryptFile;
	CString strPassword = pDlg->m_strPassword;

	if(strPath.IsEmpty() || strEncPath.IsEmpty() || strPassword.IsEmpty())
	{
		pDlg->m_bError = true;
		pDlg->PostMessage(WM_ENDDLG_CANCEL);
		return 0;
	}

	// encrypt
	if(pDlg->m_bIsEncrypting)
	{
		// check if file is already encrypted
		if(!FileExists(strPath))
		{
			if(FileExists(strEncPath))
			{
				pDlg->PostMessage(WM_ENDDLG_OK);
				return 1;
			}
			AfxMessageBox("Error file does not exist. Path:- " + strPath);
			pDlg->m_bError = true;
			pDlg->PostMessage(WM_ENDDLG_CANCEL);
			return 0;
		}
		if(FileExists(strEncPath))
		{
			DeleteFile(strEncPath);
		}
		CFile fp;
		if(fp.Open(strPath,CFile::modeRead))
		{
			__int64 nSize = fp.GetLength();
			__int64 nReadPos = 0;
			CFile fpEnc;
			if(fpEnc.Open(strEncPath,CFile::modeWrite|CFile::modeCreate))
			{
				while(nReadPos < nSize)
				{
					DWORD dwReadSize = 32768;
					if((dwReadSize + nReadPos) > nSize)
						dwReadSize = (DWORD)(nSize - nReadPos);
					char* pBuf = new char[dwReadSize];
					fp.Read(pBuf,dwReadSize);
					// encrypt chunk in memory
					DWORD dwReadWriteSize = dwReadSize;
					char* pEncBuf = EncryptBuffer(pBuf, dwReadWriteSize, strPassword);
					// error encrypting
					if(pEncBuf == NULL)
					{
						delete [] pBuf;
						fpEnc.Close();
						fp.Close();
						pDlg->m_bError = true;
						pDlg->PostMessage(WM_ENDDLG_CANCEL);
						return 0;
					}
					// write to enc file
					fpEnc.Write(pEncBuf,dwReadWriteSize);
					delete [] pEncBuf;
					delete [] pBuf;
					nReadPos += dwReadSize;

					DWORD nPercent = (double)nReadPos / (double)nSize * 100;
					pDlg->m_ctlProgress.SetPos(nPercent);

					if(pDlg->m_bCancelled)
					{
						fpEnc.Close();
						fp.Close();
						while(FileExists(strEncPath) && !DeleteFile(strEncPath))
						{
							AfxMessageBox("Error deleting partial file. Please close any applications that may be using the file. Path:- " + strEncPath);
						}
						pDlg->PostMessage(WM_ENDDLG_CANCEL);
						return 0L;
					}
				}
			}
			fpEnc.Close();
			fp.Close();
		}
		if(!DeleteFile(strPath))
			AfxMessageBox("Error deleting unencrypted file. Please close any applications that may be using the file. Then delete file:- " + strPath);
	}
	// decrypt
	else 
	{
		// check if file is already unencrypted
		if(!FileExists(strEncPath))
		{
			if(FileExists(strPath))
			{
				pDlg->PostMessage(WM_ENDDLG_OK);
				return 1;
			}
			AfxMessageBox("Error file does not exist. Path:- " + strEncPath);
			pDlg->m_bError = true;
			pDlg->PostMessage(WM_ENDDLG_CANCEL);
			return 0;
		}
		if(FileExists(strPath))
		{
			DeleteFile(strPath);
		}
		CFile fpEnc;
		if(fpEnc.Open(strEncPath,CFile::modeRead))
		{
			__int64 nSize = fpEnc.GetLength();
			__int64 nReadPos = 0;
			CFile fp;
			if(fp.Open(strPath,CFile::modeWrite|CFile::modeCreate))
			{
				while(nReadPos < nSize)
				{
					DWORD dwReadSize = 32784;
					if((dwReadSize + nReadPos) > nSize)
						dwReadSize = (DWORD)(nSize - nReadPos);
					char* pEncBuf = new char[dwReadSize];
					fpEnc.Read(pEncBuf,dwReadSize);
					DWORD dwReadWriteSize = dwReadSize;
					// unencrypt chunk in memory
					char* pBuf = UnEncryptBuffer(pEncBuf, dwReadWriteSize, strPassword);
					if(pBuf == NULL)
					{
						delete [] pEncBuf;
						fpEnc.Close();
						fp.Close();
						pDlg->m_bError = true;
						pDlg->PostMessage(WM_ENDDLG_CANCEL);
						return 0;
					}
					// write to enc file
					fp.Write(pBuf,dwReadWriteSize);
					delete [] pEncBuf;
					delete [] pBuf;
					nReadPos += dwReadSize;

					DWORD nPercent = (double)nReadPos / (double)nSize * 100;
					pDlg->m_ctlProgress.SetPos(nPercent);

					if(pDlg->m_bCancelled)
					{
						fpEnc.Close();
						fp.Close();
						while(FileExists(strPath) && !DeleteFile(strPath))
						{
							AfxMessageBox("Error deleting partial file. Please close any applications that may be using the file. The delete file:- " + strPath);
						}
						pDlg->PostMessage(WM_ENDDLG_CANCEL);
						return 0L;
					}
				}
			}
			fpEnc.Close();
			fp.Close();
		}
		if(pDlg->m_bRemoveFile && !DeleteFile(strEncPath))
			AfxMessageBox("Error deleting encrypted file. Please close any applications that may be using the file. Path:- " + strPath);
	}
	pDlg->PostMessage(WM_ENDDLG_OK);
	return 1L;
}

void CEncryptFileDlg::OnClose()
{
	m_bCancelled = true;
}

long CEncryptFileDlg::OnEndDlgOK(WPARAM wParam, LPARAM lParam)
{
	EndDialog(IDOK);
	return 0L;
}

long CEncryptFileDlg::OnEndDlgCANCEL(WPARAM wParam, LPARAM lParam)
{
	EndDialog(IDCANCEL);
	return 0L;
}
