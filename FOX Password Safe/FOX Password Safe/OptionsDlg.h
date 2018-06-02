#pragma once
#include "afxwin.h"


// COptionsDlg dialog

class COptionsDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionsDlg)

public:
	COptionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionsDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:	
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	// start when windows starts
	BOOL m_bStartWhenWindowsStarts;
	// hide in system tray when closed
	BOOL m_bHideInTrayOnClose;
	// hide to system tray when started
	BOOL m_bHideInTrayOnStart;
	// clear clipboard on exit
	BOOL m_bClearClipboardOnExit;
	// do not clear passwords when hidden in system tray
	CButton m_ctlNoClearPassHideToTray;
	// clear password when minimized to system tray	
	CButton m_ctlClearPassWhenHideInTray;
	// clear password after n minutes when minimize to system tray
	CButton m_ctlClearPassAfterMinsHideInTray;
	// minutes setting for clear password after n minutes when minimize to system tray
	CString m_strClearPassAfterMins;
	// popup password dialog when loading URL
	BOOL m_bPopupPassDlgOnLoadURL;
	// hide in system tray after loading a URL
	BOOL m_bHideInTrayAfterLoadURL;
	// restore default browser security after certain minutes of loading a URL
	CButton m_ctlRestoreBrowserAfterMins;
	// leave browser secure after loading URL
	CButton m_ctlLeaveBrowersSecure;
	afx_msg void OnBnClickedRadioBrowserAutoUnlockdown();
	afx_msg void OnBnClickedRadioManuallyUnlockDownBrowser();
	// Clear passwords from memory when screen saver is activated
	BOOL m_bClearPassOnScreenSaverRun;
	afx_msg void OnBnClickedRadioNoEmptyPassOnminimize();
	afx_msg void OnBnClickedRadioEmptyPassInSystemTray();
	afx_msg void OnBnClickedRadioEmptyPassAfterTimePeriod();
	// minutes to wait before restoring browser
	CString m_strRestoreBrowserTimeMins;
	// auto restore default browser security after x seconds
	CString m_strRestoreBrowserTimeSecs;
	CEdit m_ctlRestoreBrowserTimeMins;
	CEdit m_ctlRestoreBrowserTimeSecs;
	CEdit m_ctlClearPassAfterMins;
	afx_msg void OnBnClickedRadioPassNeverExpires();
	afx_msg void OnBnClickedRadioPassExpiresInDays();
	// password never expires as default for new entries
	CButton m_ctlPassNeverExpires;
	// password expires after x days as default for new entries
	CButton m_ctlPassExpiresAfterXDays;
	// password expires after x days
	CEdit m_ctlPassExpiresDays;
};
