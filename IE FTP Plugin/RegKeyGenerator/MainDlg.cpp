// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainDlg.h"
#include "time.h"

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
	return FALSE;
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);

	return TRUE;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CreateRegCodes();
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog(wID);
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

LRESULT CMainDlg::CreateRegCodes()
{
	srand((unsigned)time(NULL));

	CString strNum;
	GetDlgItemText(IDC_EDIT_NUM_KEYS,strNum.GetBuffer(1024),1024);
	strNum.ReleaseBuffer();
	int nNum = atoi(strNum);
	CString strKeys;
	for(int n=0;n<nNum;n++)
	{
		strKeys += GetKey() + "\r\n";
	}
	SetDlgItemText(IDC_EDIT_KEYS,strKeys);

	return S_OK;
}

CString CMainDlg::GetKey()
{
	CString strKey;
	int n1 = 0;
	int n2 = 0;
	int n15 = 0;
	int n16 = 0;
	for(int n=0;n<16;n++)
	{
		int nNum = rand()%9;
		CString strTemp;
		strTemp.Format("%d",nNum);
		strKey += strTemp;
		switch(n)
		{
		case 0:
			n1 = nNum;
			break;
		case 1:
			n2 = nNum;
			break;
		case 14:
			n15 = nNum;
			break;
		case 15:
			n16 = nNum;
			break;
		}
	}

	// 1219981901197056 16 digits
	// first 2 * + next numbers = 3456
	// last 2 * + previous numbers = 1987

	int nFirst = 3456 - (n1*n2);
	int nLast = 1987 - (n15*n16);
	CString strNum;
	strNum.Format("%d",nFirst);
	for(n=0;n<strNum.GetLength();n++)
		strKey.SetAt(n+2,strNum.GetAt(n));
	strNum.Format("%d",nLast);
	for(n=0;n<strNum.GetLength();n++)
		strKey.SetAt(14-strNum.GetLength()+n,strNum.GetAt(n));

	return strKey;
}

