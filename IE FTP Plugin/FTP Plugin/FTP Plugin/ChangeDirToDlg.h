// ChangeDirToDlg.h : Declaration of the CChangeDirToDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>


// CChangeDirToDlg

class CChangeDirToDlg : public CAxDialogImpl<CChangeDirToDlg>
{
public:
	CChangeDirToDlg()
	{
	}

	~CChangeDirToDlg()
	{
	}

	enum { IDD = IDD_CHANGEDIRTODLG };

BEGIN_MSG_MAP(CChangeDirToDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	CHAIN_MSG_MAP(CAxDialogImpl<CChangeDirToDlg>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CChangeDirToDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;

		CString strTitle = _T(APP_NAME);
		strTitle += _T(" - Change current directory");
		SetWindowText(strTitle);

		SetIcon(LoadIcon(_AtlBaseModule.m_hInst,MAKEINTRESOURCE(IDI_MAIN)), true);

		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		GetDlgItemText(IDC_EDIT_DIR, m_strDir.GetBuffer(MAX_PATH), MAX_PATH);
		m_strDir.ReleaseBuffer();
		EndDialog(wID);
		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	// new path to change to
	CString m_strDir;
};


