#pragma once


// CUnencryptDlg dialog

class CUnencryptDlg : public CDialog
{
	DECLARE_DYNAMIC(CUnencryptDlg)

public:
	CUnencryptDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUnencryptDlg();

// Dialog Data
	enum { IDD = IDD_UNENCRYPT_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_strPath;
	CString m_strPassword;
	afx_msg void OnBnClickedBrowse2();
	CString m_strPathUnencrypted;
};
