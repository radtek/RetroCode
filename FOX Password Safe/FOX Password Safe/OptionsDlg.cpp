// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "OptionsDlg.h"
#include "helpers.h"
#include ".\optionsdlg.h"


// COptionsDlg dialog

IMPLEMENT_DYNAMIC(COptionsDlg, CDialog)
COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDlg::IDD, pParent)
	, m_bStartWhenWindowsStarts(FALSE)
	, m_bHideInTrayOnClose(FALSE)
	, m_bHideInTrayOnStart(FALSE)
	, m_bClearClipboardOnExit(FALSE)
	, m_strClearPassAfterMins(_T(""))
	, m_bPopupPassDlgOnLoadURL(FALSE)
	, m_bHideInTrayAfterLoadURL(FALSE)
	, m_bClearPassOnScreenSaverRun(FALSE)
	, m_strRestoreBrowserTimeMins(_T(""))
	, m_strRestoreBrowserTimeSecs(_T(""))
{
}

COptionsDlg::~COptionsDlg()
{
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_AUTO_START, m_bStartWhenWindowsStarts);
	DDX_Check(pDX, IDC_CHECK_HIDE_IN_TRAY, m_bHideInTrayOnClose);
	DDX_Check(pDX, IDC_CHECK_HIDE_ONSTART, m_bHideInTrayOnStart);
	DDX_Check(pDX, IDC_CHECK_EMPTY_CLIP_ONCLOSE, m_bClearClipboardOnExit);
	DDX_Control(pDX, IDC_RADIO_NO_EMPTY_PASS_ONMINIMIZE, m_ctlNoClearPassHideToTray);
	DDX_Control(pDX, IDC_RADIO_EMPTY_PASS_IN_SYSTEM_TRAY, m_ctlClearPassWhenHideInTray);
	DDX_Control(pDX, IDC_RADIO_EMPTY_PASS_AFTER_TIME_PERIOD, m_ctlClearPassAfterMinsHideInTray);
	DDX_Text(pDX, IDC_EDIT_MINUTES_CLEAR_PASS, m_strClearPassAfterMins);
	DDX_Check(pDX, IDC_CHECK_POPUP_PASS_DLG_ONLOAD_URL, m_bPopupPassDlgOnLoadURL);
	DDX_Check(pDX, IDC_CHECK_HIDE_ONLOAD_URL, m_bHideInTrayAfterLoadURL);
	DDX_Control(pDX, IDC_RADIO_BROWSER_AUTO_UNLOCKDOWN, m_ctlRestoreBrowserAfterMins);
	DDX_Control(pDX, IDC_RADIO_MANUALLY_UNLOCK_DOWN_BROWSER, m_ctlLeaveBrowersSecure);
	DDX_Text(pDX, IDC_EDIT_RESTORE_BROWER_TIME_MINS, m_strRestoreBrowserTimeMins);
	DDX_Text(pDX, IDC_EDIT_RESTORE_BROWER_TIME_SECS, m_strRestoreBrowserTimeSecs);
	DDX_Control(pDX, IDC_EDIT_RESTORE_BROWER_TIME_MINS, m_ctlRestoreBrowserTimeMins);
	DDX_Control(pDX, IDC_EDIT_RESTORE_BROWER_TIME_SECS, m_ctlRestoreBrowserTimeSecs);
	DDX_Control(pDX, IDC_EDIT_MINUTES_CLEAR_PASS, m_ctlClearPassAfterMins);
	//	DDX_Check(pDX, IDC_CHECK_CLEAR_PASS_WHEN_SCREENSAVER_RUN, m_bClearPassOnScreenSaverRun);
	DDX_Control(pDX, IDC_RADIO_PASS_NEVER_EXPIRES, m_ctlPassNeverExpires);
	DDX_Control(pDX, IDC_RADIO_PASS_EXPIRES_IN_DAYS, m_ctlPassExpiresAfterXDays);
	DDX_Control(pDX, IDC_EDIT_DEFAULT_DAYS_PASS_EXPIRES, m_ctlPassExpiresDays);
}

BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_BROWSER_AUTO_UNLOCKDOWN, OnBnClickedRadioBrowserAutoUnlockdown)
	ON_BN_CLICKED(IDC_RADIO_MANUALLY_UNLOCK_DOWN_BROWSER, OnBnClickedRadioManuallyUnlockDownBrowser)
	ON_BN_CLICKED(IDC_RADIO_NO_EMPTY_PASS_ONMINIMIZE, OnBnClickedRadioNoEmptyPassOnminimize)
	ON_BN_CLICKED(IDC_RADIO_EMPTY_PASS_IN_SYSTEM_TRAY, OnBnClickedRadioEmptyPassInSystemTray)
	ON_BN_CLICKED(IDC_RADIO_EMPTY_PASS_AFTER_TIME_PERIOD, OnBnClickedRadioEmptyPassAfterTimePeriod)
	ON_BN_CLICKED(IDC_RADIO_PASS_NEVER_EXPIRES, OnBnClickedRadioPassNeverExpires)
	ON_BN_CLICKED(IDC_RADIO_PASS_EXPIRES_IN_DAYS, OnBnClickedRadioPassExpiresInDays)
END_MESSAGE_MAP()

BOOL COptionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// hide or close app on close click
	m_bHideInTrayOnClose = (MyGetProfileInt("MinimizeOnClose",0) == 1);
	// show or hide app on startup
	m_bStartWhenWindowsStarts = (MyGetProfileInt("StartWhenWindowsStarts",0) == 1);
	// show or hide app on startup
	m_bHideInTrayOnStart = (MyGetProfileInt("MinimizeOnStart",0) == 1);
	// empty passwords from clipboard when closed
	m_bClearClipboardOnExit = (MyGetProfileInt("ClearClipOnClose",1) == 1);
	// empty passwords when screen saver running
	m_bClearPassOnScreenSaverRun = (MyGetProfileInt("ClearPassOnScreensaver",1) == 1);
	// clear passwords on minimize to system tray
	int nClearPassOnMinimize = MyGetProfileInt("ClearPassOnMinimize",2);
	// clear passwords after certain time period on minimize
	m_strClearPassAfterMins.Format("%d",MyGetProfileInt("ClearPassOnMinimizeTimeMins",15));
	// popup password window when url menu clicked
	m_bPopupPassDlgOnLoadURL = (MyGetProfileInt("PopupOnWebMenu",1) == 1);
	// auto hide app when loading web site
	m_bHideInTrayAfterLoadURL = (MyGetProfileInt("AutoHideAppWhenLoadURL",0) == 1);
	// auto unlock browser after time period
	BOOL bAutoUnlockBrowser = (MyGetProfileInt("AutoUnlockBrowser",1) == 1);
	// time period for auto unlock browser
	DWORD nSecs = MyGetProfileInt("AutoUnlockBrowserTimeSecs",DEFAULT_AUTO_UNLOCK_BROWSER_SECS);
	DWORD nMins = nSecs / 60;
	nSecs = nSecs - (nMins*60);
	m_strRestoreBrowserTimeMins.Format("%d",nMins);
	m_strRestoreBrowserTimeSecs.Format("%d",nSecs);

	// clear password on minimize to system tray
	switch(nClearPassOnMinimize)
	{
	case 0: // do not clear password
		m_ctlNoClearPassHideToTray.SetCheck(BST_CHECKED);
		m_ctlClearPassWhenHideInTray.SetCheck(BST_UNCHECKED);
		m_ctlClearPassAfterMinsHideInTray.SetCheck(BST_UNCHECKED);
		m_ctlClearPassAfterMins.EnableWindow(false);
		break;
	case 1: // clear password
		m_ctlNoClearPassHideToTray.SetCheck(BST_UNCHECKED);
		m_ctlClearPassWhenHideInTray.SetCheck(BST_CHECKED);
		m_ctlClearPassAfterMinsHideInTray.SetCheck(BST_UNCHECKED);
		m_ctlClearPassAfterMins.EnableWindow(false);
		break;
	case 2: // clear password after certain time
		m_ctlNoClearPassHideToTray.SetCheck(BST_UNCHECKED);
		m_ctlClearPassWhenHideInTray.SetCheck(BST_UNCHECKED);
		m_ctlClearPassAfterMinsHideInTray.SetCheck(BST_CHECKED);
		m_ctlClearPassAfterMins.EnableWindow(true);
		break;
	}
	// auto unlock browser 
	if(bAutoUnlockBrowser)
	{
		m_ctlRestoreBrowserAfterMins.SetCheck(BST_CHECKED);
		m_ctlLeaveBrowersSecure.SetCheck(BST_UNCHECKED);
		m_ctlRestoreBrowserTimeMins.EnableWindow(true);
		m_ctlRestoreBrowserTimeSecs.EnableWindow(true);
	}
	else
	{
		m_ctlRestoreBrowserAfterMins.SetCheck(BST_UNCHECKED);
		m_ctlLeaveBrowersSecure.SetCheck(BST_CHECKED);
		m_ctlRestoreBrowserTimeMins.EnableWindow(false);
		m_ctlRestoreBrowserTimeSecs.EnableWindow(false);
	}
	// default password never expires
	BOOL bPassNeverExpires = (MyGetProfileInt("DefaultPassNeverExpires",0) == 1);
	// default password expires in x days when creating new entry
	int nDays = MyGetProfileInt("DefaultPassExpireInDays",30);
	CString strDays;
	strDays.Format("%d",nDays);
	m_ctlPassExpiresDays.SetWindowText(strDays);
	if(bPassNeverExpires)
		OnBnClickedRadioPassNeverExpires();
	else
		OnBnClickedRadioPassExpiresInDays();

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void COptionsDlg::OnBnClickedRadioBrowserAutoUnlockdown()
{
	m_ctlRestoreBrowserAfterMins.SetCheck(BST_CHECKED);
	m_ctlLeaveBrowersSecure.SetCheck(BST_UNCHECKED);
	m_ctlRestoreBrowserTimeMins.EnableWindow(true);
	m_ctlRestoreBrowserTimeSecs.EnableWindow(true);
}

void COptionsDlg::OnBnClickedRadioManuallyUnlockDownBrowser()
{
	m_ctlRestoreBrowserAfterMins.SetCheck(BST_UNCHECKED);
	m_ctlLeaveBrowersSecure.SetCheck(BST_CHECKED);
	m_ctlRestoreBrowserTimeMins.EnableWindow(false);
	m_ctlRestoreBrowserTimeSecs.EnableWindow(false);
}

void COptionsDlg::OnBnClickedRadioNoEmptyPassOnminimize()
{
	m_ctlNoClearPassHideToTray.SetCheck(BST_CHECKED);
	m_ctlClearPassWhenHideInTray.SetCheck(BST_UNCHECKED);
	m_ctlClearPassAfterMinsHideInTray.SetCheck(BST_UNCHECKED);
	m_ctlClearPassAfterMins.EnableWindow(false);
}

void COptionsDlg::OnBnClickedRadioEmptyPassInSystemTray()
{
	m_ctlNoClearPassHideToTray.SetCheck(BST_UNCHECKED);
	m_ctlClearPassWhenHideInTray.SetCheck(BST_CHECKED);
	m_ctlClearPassAfterMinsHideInTray.SetCheck(BST_UNCHECKED);
	m_ctlClearPassAfterMins.EnableWindow(false);
}

void COptionsDlg::OnBnClickedRadioEmptyPassAfterTimePeriod()
{
	m_ctlNoClearPassHideToTray.SetCheck(BST_UNCHECKED);
	m_ctlClearPassWhenHideInTray.SetCheck(BST_UNCHECKED);
	m_ctlClearPassAfterMinsHideInTray.SetCheck(BST_CHECKED);
	m_ctlClearPassAfterMins.EnableWindow(true);
}

void COptionsDlg::OnBnClickedRadioPassNeverExpires()
{
	m_ctlPassNeverExpires.SetCheck(BST_CHECKED);
	m_ctlPassExpiresAfterXDays.SetCheck(BST_UNCHECKED);
	m_ctlPassExpiresDays.EnableWindow(false);
}

void COptionsDlg::OnBnClickedRadioPassExpiresInDays()
{
	m_ctlPassNeverExpires.SetCheck(BST_UNCHECKED);
	m_ctlPassExpiresAfterXDays.SetCheck(BST_CHECKED);
	m_ctlPassExpiresDays.EnableWindow(true);
}

// COptionsDlg message handlers
void COptionsDlg::OnBnClickedOk()
{
	UpdateData(true);

	// data validation
	// clear passwords on minimize to system tray
	int nMins = atoi(m_strClearPassAfterMins);
	int nClearPassOnMinimize = 0;
	if(m_ctlClearPassWhenHideInTray.GetCheck() == BST_CHECKED)
		nClearPassOnMinimize = 1;
	else if(m_ctlClearPassAfterMinsHideInTray.GetCheck() == BST_CHECKED)
		nClearPassOnMinimize = 2;
	// clear passwords after certain time period on minimize
	if(nClearPassOnMinimize == 2)
	{
		if(nMins <= 0)
		{
			AfxMessageBox("Please enter a value of 1 or greater for 'Empty passwords from memory when in Windows system tray after x minutes'");
			return;
		}
		MyWriteProfileInt("ClearPassOnMinimizeTimeMins",nMins);
	}
	MyWriteProfileInt("ClearPassOnMinimize",nClearPassOnMinimize);

	// auto unlock browser after time period
	BOOL bAutoUnlockBrowser = (m_ctlRestoreBrowserAfterMins.GetCheck() == 1);
	// time period for auto unlock browser
	if(bAutoUnlockBrowser)
	{
		nMins = atoi(m_strRestoreBrowserTimeMins);
		int nSecs = atoi(m_strRestoreBrowserTimeSecs);
		DWORD nTotal = nMins * 60 + nSecs;
		if(nTotal <= 0)
		{
			AfxMessageBox("Please enter a value of 1 or greater for 'Automatically restore default browser security settings after x minutes x secs'");
			return;
		}
		MyWriteProfileInt("AutoUnlockBrowserTimeSecs",nTotal);
	}
	MyWriteProfileInt("AutoUnlockBrowser",bAutoUnlockBrowser?1:0);

	// hide or close app on close click
	MyWriteProfileInt("MinimizeOnClose",m_bHideInTrayOnClose?1:0);
	// show or hide app on startup
	MyWriteProfileInt("StartWhenWindowsStarts",m_bStartWhenWindowsStarts?1:0);
	SetAutoStartExe(m_bStartWhenWindowsStarts);
	// show or hide app on startup
	MyWriteProfileInt("MinimizeOnStart",m_bHideInTrayOnStart?1:0);
	// empty passwords from clipboard when closed
	MyWriteProfileInt("ClearClipOnClose",m_bClearClipboardOnExit?1:0);
	// empty passwords when screen saver running
//	MyWriteProfileInt("ClearPassOnScreensaver",m_bClearPassOnScreenSaverRun?1:0);
	
	// popup password window when url menu clicked
	MyWriteProfileInt("PopupOnWebMenu",m_bPopupPassDlgOnLoadURL?1:0);
	// auto hide app when loading web site
	MyWriteProfileInt("AutoHideAppWhenLoadURL",m_bHideInTrayAfterLoadURL?1:0);

	// default password never expires
	BOOL bPassNeverExpires = (m_ctlPassNeverExpires.GetCheck() == BST_CHECKED);
	if(bPassNeverExpires)
	{
		MyWriteProfileInt("DefaultPassNeverExpires",1);
	}
	else
	{
		MyWriteProfileInt("DefaultPassNeverExpires",0);
		CString strDays;
		m_ctlPassExpiresDays.GetWindowText(strDays);
		MyWriteProfileInt("DefaultPassExpireInDays",atoi(strDays));	
	}

	OnOK();
}

