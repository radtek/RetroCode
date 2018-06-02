#pragma once


// CNagDlg dialog

class CNagDlg : public CDialog
{
	DECLARE_DYNAMIC(CNagDlg)

public:
	CNagDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNagDlg();

// Dialog Data
	enum { IDD = IDD_NAG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonOrder();
	afx_msg void OnBnClickedButtonEnterCode();
	// notification message of days remaining
	CString m_strTextMsg;
	virtual BOOL OnInitDialog();
};
