// RegKeyGeneratorDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CRegKeyGeneratorDlg dialog
class CRegKeyGeneratorDlg : public CDialog
{
// Construction
public:
	CRegKeyGeneratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_REGKEYGENERATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// number of keys to create
	CString m_strKeysNeeded;
	// reg codes edit box text
	CString m_strRegCodesText;
};
