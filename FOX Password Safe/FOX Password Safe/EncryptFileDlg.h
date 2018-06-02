#pragma once
#include "afxcmn.h"
#include "resource.h"

// CEncryptFileDlg dialog

class CEncryptFileDlg : public CDialog
{
	DECLARE_DYNAMIC(CEncryptFileDlg)

public:
	CEncryptFileDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEncryptFileDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_ECRYTPING_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strText;
	CProgressCtrl m_ctlProgress;
	CString m_strPlainFile;
	CString m_strEncryptFile;
	CString m_strPassword;
	BOOL m_bIsEncrypting;
	BOOL m_bCancelled;
	BOOL m_bError;

	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedCancel();
	static UINT ProcEncrypt(LPVOID pParam);
	afx_msg void OnClose();

	long OnEndDlgOK(WPARAM, LPARAM);
	long OnEndDlgCANCEL(WPARAM, LPARAM);
	BOOL m_bRemoveFile;
};
