#pragma once


// CNewPasswordDlg dialog

class CNewPasswordDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewPasswordDlg)

public:
	CNewPasswordDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewPasswordDlg();

// Dialog Data
	enum { IDD = IDD_CHANGE_PASSWORD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_strPass;
	CString m_strNewPass1;
	CString m_strNewPass2;
	CString m_strCurrentLoadedPath;
};
