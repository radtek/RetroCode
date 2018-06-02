// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainDlg.h"
#include "helpers.h"

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
	CString strTitle = MY_APP_NAME;
	strTitle += _T(" - Uninstall");
	SetWindowText(strTitle);

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

	m_strTitleText.Format("Click 'Uninstall' to remove %s\r\nfrom your system.",MY_APP_NAME);

	return TRUE;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

LRESULT CMainDlg::OnBnClickedCancel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog(0);
	return 0;
}

LRESULT CMainDlg::OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString strMsg;
	strMsg.Format("Are you sure you want to uninstall %s?",MY_APP_NAME);
	if(MessageBox(strMsg,MY_APP_NAME,MB_YESNO) == IDYES)
	{
		UninstallApp();
		CloseDialog(0);
	}

	return 0;
}

LRESULT CMainDlg::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPaintDC dc(m_hWnd); // device context for painting
	
	CRect rect(10,10,380,100);
	CFont font;
	font.CreatePointFont(140,"Times New Roman");
	HFONT pOld = dc.SelectFont(font.m_hFont);

	dc.SetBkMode(TRANSPARENT);   

	CRect rectFill;
	GetClientRect(rectFill);
	rectFill.bottom = 88;
	dc.FillSolidRect(rectFill,RGB(255,255,255));
	dc.DrawText(m_strTitleText,m_strTitleText.GetLength(), rect,DT_LEFT);
	
	dc.SelectFont(pOld);

	return 0;
}


// function to uninstall application
void CMainDlg::UninstallApp(void)
{	
	if(FindWindow("IEFrame",NULL))
	{
		MessageBox("Please close any open 'Internet Explorer' windows then click OK to continue with the uninstall.",MY_APP_NAME,MB_OK);
	}

	CString strInstallDir = MyGetProfileString("InstallPath",MY_DEFAULT_INSTALL_PATH,1024);
	CString strFile = strInstallDir + "\\" + CString(OCX_TO_RUN_NAME);
	
	UnRegisterOCX(strFile);

	// delete files
	if(!DeleteDirectory(strInstallDir) && DirectoryExists(strInstallDir))
	{
		MessageBox("Error, some files could not be removed from " + strInstallDir + " Close all copies of Microsoft Internet Explorer and then click OK.",MY_APP_NAME,MB_OK);
		DeleteDirectory(strInstallDir);
	}

	// delete create links in program files
	CString strProgramLinks = GetProgramsPath() + "\\";
	strProgramLinks += MY_APP_NAME;
	DeleteDirectory(strProgramLinks);	

	// delete registry
	BOOL bOK = false;
	CRegKey reg;
	if(reg.Create(HKEY_LOCAL_MACHINE, MY_ROOT_REGISTRY_PATH) == ERROR_SUCCESS)
	{
		 bOK = (reg.RecurseDeleteKey(MY_SUB_KEY_NAME) == ERROR_SUCCESS);
		 reg.Close();
	}  
	// remove from add remove programs
	DeleteLinkAddRemovePrograms();

	MessageBox("Uninstall complete.",MY_APP_NAME,MB_OK);
}