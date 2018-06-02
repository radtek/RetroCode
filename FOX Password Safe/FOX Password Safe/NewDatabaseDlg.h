#pragma once
#include "afxwin.h"


// CNewDatabaseDlg dialog

class CNewDatabaseDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewDatabaseDlg)

public:
	CNewDatabaseDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewDatabaseDlg();

// Dialog Data
	enum { IDD = IDD_NEW_DATABASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// path to new database file
	CString m_strFilePath;
	// password to database
	CString m_strPassword;
	// password verification
	CString m_strPassword2;
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnBnClickedOk();
	// return path to new database file
	CString GetPathName(void);
	// return new password
	CString GetPassword(void);
	// create default categories in new database
	BOOL m_bCreateDefaultCat;
	virtual BOOL OnInitDialog();
};
