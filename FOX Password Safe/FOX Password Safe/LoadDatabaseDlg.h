#pragma once


// CLoadDatabaseDlg dialog

class CLoadDatabaseDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoadDatabaseDlg)

public:
	CLoadDatabaseDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoadDatabaseDlg();

// Dialog Data
	enum { IDD = IDD_LOAD_DATABASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// database file path
	CString m_strFilePath;
	// database password
	CString m_strPassword;
	afx_msg void OnBnClickedButtonBrowse();
	afx_msg void OnBnClickedButtonCreateNew();
	afx_msg void OnBnClickedOk();
	// return path to selected database
	CString GetPathName(void);
	// returns entered password
	CString GetPassword(void);
};
