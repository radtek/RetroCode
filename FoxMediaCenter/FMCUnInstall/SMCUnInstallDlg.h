// SMCUnInstallDlg.h : header file
//

#if !defined(AFX_SMCUNINSTALLDLG_H__452789C6_B70D_4CC6_BED4_3616828E3F27__INCLUDED_)
#define AFX_SMCUNINSTALLDLG_H__452789C6_B70D_4CC6_BED4_3616828E3F27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSMCUnInstallDlg dialog

class CSMCUnInstallDlg : public CDialog
{
// Construction
public:
	CSMCUnInstallDlg(CWnd* pParent = NULL);	// standard constructor

	CStringArray* EnumKnowFileTypesFromReg();
	void UnAssociate(CString strExt);

// Dialog Data
	//{{AFX_DATA(CSMCUnInstallDlg)
	enum { IDD = IDD_SMCUNINSTALL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMCUnInstallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSMCUnInstallDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMCUNINSTALLDLG_H__452789C6_B70D_4CC6_BED4_3616828E3F27__INCLUDED_)
