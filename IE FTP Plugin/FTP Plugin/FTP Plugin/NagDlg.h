// NagDlg.h : Declaration of the CNagDlg

#pragma once

#include "resource.h"       // main symbols
#include <atlhost.h>


// CNagDlg

class CNagDlg : public CAxDialogImpl<CNagDlg>
{
public:
	CNagDlg()
	{
	}

	~CNagDlg()
	{
	}

	enum { IDD = IDD_NAGDLG };

BEGIN_MSG_MAP(CNagDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDC_BUTTON_ENTER_REGISTRATION, BN_CLICKED, OnClickedButton_enter_number)
	COMMAND_HANDLER(IDC_BUTTON_REGISTER, BN_CLICKED, OnClickedButton_register)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	CHAIN_MSG_MAP(CAxDialogImpl<CNagDlg>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CNagDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		
		CString strTitle = _T(APP_NAME);
		strTitle += _T(" - your free trial has ended");
		SetWindowText(strTitle);

		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedButton_enter_number(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedButton_register(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

public:
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
public:
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};


