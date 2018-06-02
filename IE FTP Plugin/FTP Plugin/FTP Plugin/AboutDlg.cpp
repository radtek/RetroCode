// AboutDlg.cpp : Implementation of CAboutDlg

#include "stdafx.h"
#include "AboutDlg.h"
#include "EnterRegCode.h"

// CAboutDlg

void CAboutDlg::SetRegistrationText()
{
	CString strText;
	if(IsRegistered())
	{
		CString strName = MyGetProfileString("Name","");
		CString strCompany = MyGetProfileString("Company","");
		strText = strName + "\r\n" + strCompany;

		HWND hWnd = GetDlgItem(IDC_BUTTON_GET_REGISTRATION);
		::ShowWindow(hWnd,SW_HIDE);
		// change button text
		hWnd = GetDlgItem(IDC_BUTTON_ENTER_REG);
		::SetWindowText(hWnd,"Change registration details");
	}
	else
	{
		int nDays = GetFreeTrialDaysUsed();
		if(nDays == -1 || nDays > 29)
			strText = "Not registered. Your free trial has expired. Please Register.";
		else
			strText.Format("Not registered.\r\n\r\nYou have %d days remaining for your free trial.",
			30 - nDays);
	}
	SetDlgItemText(IDC_STATIC_REG_NAME,strText);
}

LRESULT CAboutDlg::OnBnClickedButtonEnterReg(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CEnterRegCode dlg;
	if(dlg.DoModal() == IDOK)
	{
		SetRegistrationText();
	}

	return 0;
}

LRESULT CAboutDlg::OnBnClickedButtonGetRegistration(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(IDYES);

	return 0;
}

LRESULT CAboutDlg::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPaintDC dc(m_hWnd);
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect,RGB(255,255,255));

	return 0;
}
