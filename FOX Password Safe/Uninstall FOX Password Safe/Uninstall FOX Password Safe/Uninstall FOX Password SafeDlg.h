// Uninstall FOX Password SafeDlg.h : header file
//

#pragma once


// CUninstallFOXPasswordSafeDlg dialog
class CUninstallFOXPasswordSafeDlg : public CDialog
{
// Construction
public:
	CUninstallFOXPasswordSafeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UNINSTALLFOXPASSWORDSAFE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// function to uninstall application
	void UninstallApp(void);
	// text to display in title
	CString m_strTitleText;
};
