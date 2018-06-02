#pragma once


// CAskCloseOrHideDlg dialog

class CAskCloseOrHideDlg : public CDialog
{
	DECLARE_DYNAMIC(CAskCloseOrHideDlg)

public:
	CAskCloseOrHideDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAskCloseOrHideDlg();

// Dialog Data
	enum { IDD = IDD_ASK_CLOSE_OR_HIDE_TO_TRAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// do not show this dialog again
	BOOL m_bDoNotShowAgain;
	// hide in system tray
	BOOL m_bHide;
};
