// FOX Password Safe SetupDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CFOXPasswordSafeSetupDlg dialog
class CFOXPasswordSafeSetupDlg : public CDialog
{
// Construction
public:
	CFOXPasswordSafeSetupDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FOXPASSWORDSAFESETUP_DIALOG };

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
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonBrowse();
	// install path
	CString m_strInstallPath;
	// control install path
	CEdit m_ctlInstallPath;
	// control browse button
	CButton m_ctlBrowse;
	// control license
	CEdit m_ctlLicense;
	// control next button
	CButton m_ctlNextBut;
	// control back button
	CButton m_ctlBackButton;
	// load license into buffer
	CString m_strLicense;
	// font for license
	CFont m_LicFont;
	// show first page screen
	void ShowPage1(void);
	// current page number
	int m_nPage;
	// show screen 2
	void ShowPage2(void);
	// show screen 3
	void ShowPage3(void);
	// text to display in title
	CString m_strTitleText;
	// install files
	void Finished(void);
};
