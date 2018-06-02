// SMCSetupDlg.h : header file
//

#if !defined(AFX_SMCSETUPDLG_H__FDE28B7C_1E98_4E7E_A8ED_357FC9C40F90__INCLUDED_)
#define AFX_SMCSETUPDLG_H__FDE28B7C_1E98_4E7E_A8ED_357FC9C40F90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSMCSetupDlg dialog
#include "MyStatic.h"

class CSMCSetupDlg : public CDialog
{
// Construction
public:
	CSMCSetupDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSMCSetupDlg)
	enum { IDD = IDD_SMCSETUP_DIALOG };
	CButton	m_check2;
	CButton	m_check1;
	CMyStatic	m_ctlClickNext;
	CButton	m_ctlDone;
	CButton	m_ctlPrevious;
	CButton	m_ctlNext;
	CStatic	m_ctlLicenseHeader;
	CEdit	m_ctlLicense;
	CStatic	m_ctlImage;
	CEdit	m_ctlDir;
	CStatic	m_ctlDirHeader;
	CButton	m_butBrowse;
	CString	m_strDir;
	BOOL	m_bInstallDivx;
	BOOL	m_bInstallOgg;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMCSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	int m_nPage;
	void ShowPage3();
	void ShowPage2();
	void ShowPage1();
	BOOL RegisterOCX(CString strPath);


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSMCSetupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnPrevious();
	afx_msg void OnNext();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMCSETUPDLG_H__FDE28B7C_1E98_4E7E_A8ED_357FC9C40F90__INCLUDED_)
