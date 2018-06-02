#pragma once


// CWarningDlg dialog

class CWarningDlg : public CDialog
{
	DECLARE_DYNAMIC(CWarningDlg)

public:
	CWarningDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWarningDlg();

// Dialog Data
	enum { IDD = IDD_WARNING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	// don't show dialog again check
	BOOL m_bDontShowAgain;
	// text to display in dialog
	CString m_strText;
	// registry tag to write to don't show again
	CString m_strRegistryTag;
	// static control text
	CString m_strTextStatic;
};
