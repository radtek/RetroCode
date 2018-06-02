// AboutDlg.h : Declaration of the CAboutDlg

#pragma once

#include "resource.h"       // main symbols
#include <atlhost.h>
#include "helpers.h" 

// CAboutDlg

class CAboutDlg : public CAxDialogImpl<CAboutDlg>
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
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	COMMAND_HANDLER(IDC_BUTTON_ENTER_REG, BN_CLICKED, OnBnClickedButtonEnterReg)
	COMMAND_HANDLER(IDC_BUTTON_GET_REGISTRATION, BN_CLICKED, OnBnClickedButtonGetRegistration)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
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
		SetIcon(LoadIcon(_AtlBaseModule.m_hInst,MAKEINTRESOURCE(IDI_MAIN)), true);
		SetRegistrationText();

		CString strTitle = _T(APP_NAME);
		SetWindowText(strTitle + _T(" - About"));

		SetDlgItemText(IDC_TITLE,strTitle + _T(APP_VERSION_STRING));

		bHandled = TRUE;
		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnBnClickedButtonEnterReg(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonGetRegistration(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	void SetRegistrationText();
};


