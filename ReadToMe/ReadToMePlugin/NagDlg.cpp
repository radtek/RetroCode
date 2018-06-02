// NagDlg.cpp : Implementation of CNagDlg

#include "stdafx.h"
#include "NagDlg.h"
#include ".\nagdlg.h"
#include "EnterRegCode.h"


// CNagDlg

LRESULT CNagDlg::OnBnClickedButtonEnterNumber(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CEnterRegCode dlg;
	dlg.DoModal();	
	EndDialog(IDOK);
	return 0;
}

LRESULT CNagDlg::OnBnClickedButtonRegister(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(IDYES);
	return 0;
}
