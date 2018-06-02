// SettingsDlg.h : Declaration of the CSettingsDlg

#pragma once

#include "resource.h"       // main symbols
#include <atlhost.h>
class CReadToMe;

// CSettingsDlg

class CSettingsDlg : public CAxDialogImpl<CSettingsDlg>
{
public:
	CSettingsDlg();
	~CSettingsDlg();

	enum { IDD = IDD_SETTINGSDLG };

BEGIN_MSG_MAP(CSettingsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	MESSAGE_HANDLER(WM_HSCROLL, OnHScroll)
	COMMAND_HANDLER(IDC_COMBO_VOICE, CBN_SELCHANGE, OnCbnSelchangeComboVoice)
	NOTIFY_HANDLER( IDC_TAB_SETTINGS, TCN_SELCHANGE, OnTabChange )
	CHAIN_MSG_MAP(CAxDialogImpl<CSettingsDlg>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnHScroll(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	HRESULT VoiceChange();
	LRESULT OnCbnSelchangeComboVoice(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTabChange(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	
	// speech rate
	long m_lDefaultRate;
	// volume
	USHORT m_lDefaultVolume;
	// sapi control
	ISpVoice*  m_cpVoice;
	// pointer to main wnd
	CReadToMe* m_pMain;
	// show page 1
	void ShowPage1();
	// show page 2
	void ShowPage2();
};


