#pragma once


// CBackupDlg dialog

class CBackupDlg : public CDialog
{
	DECLARE_DYNAMIC(CBackupDlg)

public:
	CBackupDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBackupDlg();

// Dialog Data
	enum { IDD = IDD_BACKUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBrowse();
	afx_msg void OnBnClickedOk();
	// default file name for save dialog
	CString m_strFileName;
	// path to save backup file
	CString m_strPath;
	// backup file password
	CString m_strPassword;
	// current loaded database path
	CString m_strCurrentLoadedPath;
};
