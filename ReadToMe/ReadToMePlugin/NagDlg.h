// NagDlg.h : Declaration of the CNagDlg

#pragma once

#include "resource.h"       // main symbols
#include <atlhost.h>


// CNagDlg

class CNagDlg : 
	public CAxDialogImpl<CNagDlg>
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
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	COMMAND_HANDLER(IDC_BUTTON_ENTER_NUMBER, BN_CLICKED, OnBnClickedButtonEnterNumber)
	COMMAND_HANDLER(IDC_BUTTON_REGISTER, BN_CLICKED, OnBnClickedButtonRegister)
	CHAIN_MSG_MAP(CAxDialogImpl<CNagDlg>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CNagDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		CenterWindow();
		return 1;  // Let the system set the focus
	}

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		EndDialog(IDCANCEL);
		return 0L;
	}
	
	LRESULT OnBnClickedButtonEnterNumber(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonRegister(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};


