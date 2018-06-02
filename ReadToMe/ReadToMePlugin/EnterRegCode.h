// EnterRegCode.h : Declaration of the CEnterRegCode

#pragma once

#include "resource.h"       // main symbols
#include <atlhost.h>
#include "helpers.h"

// CEnterRegCode

class CEnterRegCode : 
	public CAxDialogImpl<CEnterRegCode>
{
public:
	CEnterRegCode()
	{
	}

	~CEnterRegCode()
	{
	}

	enum { IDD = IDD_ENTERREGCODE };

BEGIN_MSG_MAP(CEnterRegCode)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	CHAIN_MSG_MAP(CAxDialogImpl<CEnterRegCode>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CEnterRegCode>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		CenterWindow();
		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CString strName;
		CString strCompany;
		CString strCode;

		GetDlgItemText(IDC_EDIT_NAME,strName.GetBuffer(1024),1024);
		strName.ReleaseBuffer();
		GetDlgItemText(IDC_EDIT_COMPANY,strCompany.GetBuffer(1024),1024);
		strCompany.ReleaseBuffer();
		GetDlgItemText(IDC_EDIT_REG_CODE,strCode.GetBuffer(1024),1024);
		strCode.ReleaseBuffer();

		strCode.TrimLeft();
		strCode.TrimRight();

		if(!IsRegCodeGood(strCode))
		{
			MessageBox("Registration code is invalid, please copy and past all digits from the registration code you were given.","Error");
			return 0;
		}
		else
		{
			MessageBox("ReadToMe is now fully registered.","Thank you");
		}

		MyWriteProfileString("Name",strName);
		MyWriteProfileString("Company",strCompany);
		MyWriteProfileString("Reg",strCode);
		EndDialog(wID);
		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};


