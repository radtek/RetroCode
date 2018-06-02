#pragma once


// CPrintSelectDlg dialog

class CPrintSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CPrintSelectDlg)

public:
	CPrintSelectDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPrintSelectDlg();

// Dialog Data
	enum { IDD = IDD_CHOOSE_ITEMS_TO_PRINT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_bPrintSingleItem;
	int m_bPrintAllSelected;
	int m_bPrintAll;
	BOOL m_bDescription;
	BOOL m_bUsername;
	BOOL m_bPassword;
	BOOL m_bWebSite;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadioPrint1();
	afx_msg void OnBnClickedRadioPrintAllSel();
	afx_msg void OnBnClickedRadioPrintAll();
	BOOL m_bCategory;
	// print master database name and password
	BOOL m_PrintDatabasePassword;
	CString m_strMaxLen;
};
