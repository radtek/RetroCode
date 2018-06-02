// EnterRegCode.h : Declaration of the CEnterRegCode

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>
#include "helpers.h"

// CEnterRegCode

class CEnterRegCode : public CAxDialogImpl<CEnterRegCode>
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
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	CHAIN_MSG_MAP(CAxDialogImpl<CEnterRegCode>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CEnterRegCode>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		SetIcon(LoadIcon(_AtlBaseModule.m_hInst,MAKEINTRESOURCE(IDI_MAIN)), true);
		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CString strName;
		CString strCompany;
		CString strCode;

		GetDlgItemText(IDC_EDIT_NAME,strName.GetBuffer(1024),1024);
		strName.ReleaseBuffer();
		GetDlgItemText(IDC_EDIT_COMPANY_NAME,strCompany.GetBuffer(1024),1024);
		strCompany.ReleaseBuffer();
		GetDlgItemText(IDC_EDIT_REGISTRATION_CODE,strCode.GetBuffer(1024),1024);
		strCode.ReleaseBuffer();

		strCode.TrimLeft();
		strCode.TrimRight();

		if(!IsRegCodeGood(strCode))
		{
			MessageBox(_T("Registration code is invalid, please copy and past all digits from the registration code you were given. Ensure there are no spaces before or after the code. Also ensure it's the 'Serial Number:' and not another number in your email receipt."),_T("Error"));
			return 0;
		}
		else
		{
			CString strMsg = _T(APP_NAME);
			strMsg += _T(" is now fully registered.");
			MessageBox(strMsg,_T(APP_NAME));
		}

		MyWriteProfileString(_T("Name"),strName);
		MyWriteProfileString(_T("Company"),strCompany);
		MyWriteProfileString(_T("Reg"),strCode);

		EndDialog(wID);
		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
public:
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};


