// AboutDlg.h : Declaration of the CAboutDlg

#pragma once

#include "resource.h"       // main symbols
#include <atlhost.h>


// CAboutDlg

class CAboutDlg : 
	public CAxDialogImpl<CAboutDlg>
{
public:
	CAboutDlg()
	{
	}

	~CAboutDlg()
	{
	}

	enum { IDD = IDD_ABOUTDLG };

BEGIN_MSG_MAP(CAboutDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDC_BUTTON_ENTER_CODE, BN_CLICKED, OnBnClickedButtonEnterCode)
	COMMAND_HANDLER(IDC_BUTTON_ORDER_ONLINE, BN_CLICKED, OnBnClickedButtonOrderOnline)
	CHAIN_MSG_MAP(CAxDialogImpl<CAboutDlg>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CAboutDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		CenterWindow();
		// version
		CString strVersion = "ReadToMe Version ";
		strVersion += VERSION;
		SetDlgItemText(IDC_STATIC_VERSION, strVersion);
		// registration details
		SetRegistrationText();

		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
	LRESULT OnBnClickedButtonEnterCode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonOrderOnline(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	void SetRegistrationText();
};


