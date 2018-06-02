#pragma once


// CRestoreDlg dialog

class CRestoreDlg : public CDialog
{
	DECLARE_DYNAMIC(CRestoreDlg)

public:
	CRestoreDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRestoreDlg();

// Dialog Data
	enum { IDD = IDD_RESTORE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBrowse();
	afx_msg void OnBnClickedOk();
	// path to restore file
	CString m_strPath;
	// path to current database file
	CString m_strCurrentLoadedPath;
	// location to save restored data
	CString m_strPathSaveFile;
	afx_msg void OnBnClickedButtonBrowse2();
	// password to archived database
	CString m_strPassword;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonReadLocation();
	// get path to loaded database
	CString GetPathName(void);
	// get password to loaded file
	CString GetPassword(void);
};
