#pragma once


// CExpiredPasswordDlg dialog

class CExpiredPasswordDlg : public CDialog
{
	DECLARE_DYNAMIC(CExpiredPasswordDlg)

public:
	CExpiredPasswordDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExpiredPasswordDlg();

// Dialog Data
	enum { IDD = IDD_EXPIRED_PASSWORD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedOk();
	// don't show this dialog again
	BOOL m_bDontShowAgain;
};
