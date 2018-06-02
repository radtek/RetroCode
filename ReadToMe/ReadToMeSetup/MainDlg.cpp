// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainDlg.h"
#include <exdisp.h> //For IWebBrowser2* and others
#include "helpers.h"
#include "Defines.h"
#include ".\maindlg.h"
#include "comutil.h"

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
	m_nPage = 1;
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

	// init
	LoadString(_Module.m_hInst,IDS_LICENSE,m_strLicense.GetBuffer(4024),4024);
	m_strLicense.ReleaseBuffer();
	SetDlgItemText(IDC_EDIT_LICENSE,m_strLicense);
	
	m_LicFont.CreatePointFont(120,"Times New Roman");
	//m_ctlLicense.SetFont(&m_LicFont,true);

	// look in registry for 'program files' location
	CString strReturn = "";
	CRegKey reg;
	DWORD ulChars = 1024;
	BOOL bOK = false;
	if(reg.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", KEY_READ) == ERROR_SUCCESS)
	{		 
		 bOK = (reg.QueryStringValue("ProgramFilesDir",strReturn.GetBuffer(ulChars),&ulChars) == ERROR_SUCCESS);
		 strReturn.ReleaseBuffer();
		 reg.Close();
	}  
	if(strReturn.IsEmpty())
	{
		strReturn = "C:\\program files";
	}

	CString strDir = strReturn + "\\ReadToMe";
	strDir.Replace("\\\\","\\");
	SetDlgItemText(IDC_INSTALL_DIR ,strDir);

	ShowPage1();

	return TRUE;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

LRESULT CMainDlg::OnBrowse(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	LPMALLOC pMalloc;
    /* Gets the Shell's default allocator */
    if (::SHGetMalloc(&pMalloc) == NOERROR)
    {
        BROWSEINFO bi;
        char pszBuffer[MAX_PATH];
        LPITEMIDLIST pidl;
        // Get help on BROWSEINFO struct - it's got all the bit settings.
        bi.hwndOwner = m_hWnd;
        bi.pidlRoot = NULL;
        bi.pszDisplayName = pszBuffer;
        bi.lpszTitle = _T("Select a Directory");
        bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
        bi.lpfn = NULL;
        bi.lParam = 0;
        // This next call issues the dialog box.
        if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)
        {
            if (::SHGetPathFromIDList(pidl, pszBuffer))
            { 
				// At this point pszBuffer contains the selected path */.
				CString strText = pszBuffer;
				CString strTest = strText.Right(strlen("\\ReadToMe"));
				strTest.MakeLower();
				if(strTest != "\\readtome")	
					strText += "\\ReadToMe";
				SetDlgItemText(IDC_INSTALL_DIR,strText);
            }
            // Free the PIDL allocated by SHBrowseForFolder.
            pMalloc->Free(pidl);
        }
        // Release the shell's allocator.
        pMalloc->Release();
    }
	return S_OK;
}

LRESULT CMainDlg::OnBnClickedCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnBnClickedPrevious(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_nPage == 3)
		ShowPage2();
	else if(m_nPage == 2)
		ShowPage1();
	return 0;
}

LRESULT CMainDlg::OnBnClickedNext(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_nPage == 1)
	{
		ShowPage2();
	}
	else if(m_nPage == 2)
	{
		ShowPage3();
	}
	else // finished
	{
		m_strTitleText = "Installing please wait...";
		InvalidateRect(NULL);
		GetDlgItem(IDC_NEXT).EnableWindow(false);
		m_nTimerFinish = SetTimer(ID_FINISH,200,NULL);
	}
	return 0;
}

void CMainDlg::ShowPage1()
{
	m_nPage = 1;
	m_strTitleText = "Welcome to the ReadToMe Setup Wizard";

	::EnableWindow(GetDlgItem(IDC_PREVIOUS),false);
	SetDlgItemText(IDC_NEXT,"Next");
	::ShowWindow(GetDlgItem(IDC_BROWSE),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_INSTALL_DIR),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_EDIT_LICENSE),SW_HIDE);

	InvalidateRect(NULL);
}

void CMainDlg::ShowPage2()
{
	m_nPage = 2;
	m_strTitleText = "Please read and accept the license agreement\r\nto continue.";

	::EnableWindow(GetDlgItem(IDC_PREVIOUS),true);
	SetDlgItemText(IDC_NEXT,"I Agree");

	::ShowWindow(GetDlgItem(IDC_INSTALL_DIR),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_BROWSE),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_EDIT_LICENSE),SW_SHOW);

	InvalidateRect(NULL);
}

void CMainDlg::ShowPage3()
{
	m_nPage = 3;
	m_strTitleText = "Please select the installation folder.";

	SetDlgItemText(IDC_NEXT,"Finished");

	::ShowWindow(GetDlgItem(IDC_INSTALL_DIR),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_BROWSE),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_EDIT_LICENSE),SW_HIDE);

	InvalidateRect(NULL);
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
	dc.DrawText(m_strTitleText,m_strTitleText.GetLength(),rect,DT_LEFT);

	if(m_nPage == 1)
	{
		CFont font2;
		font2.CreatePointFont(120,"Times New Roman");
		dc.SelectFont(font2.m_hFont);
		CRect rectText(10,100,475,288);
		CString strNext = _T("Click 'Next' to continue.");
		dc.DrawText(strNext,strNext.GetLength(),rectText,DT_LEFT|DT_WORDBREAK);
	}
	dc.SelectFont(pOld);

	return 0;
}

BOOL CMainDlg::ShowToolBarAndHelp()
{
	IWebBrowser2* pWebBrowser2 = NULL;
	HRESULT hr = CoCreateInstance(CLSID_InternetExplorer,
                               NULL,
                               CLSCTX_LOCAL_SERVER,
                               IID_IWebBrowser2,
                               (void**)&pWebBrowser2);

	if(!SUCCEEDED(hr))
	{
		MessageBox(_T("Failed to load Internet Explorer web browser, please load it manually."),MY_APP_NAME,MB_OK);
		return FALSE;
	}
	
	// Display the band object 
	VARIANT vtBandGUID, vtShow, vtSize;
	vtBandGUID.vt = VT_BSTR;
	CComBSTR bstrURL = BAND_GUID;
	vtBandGUID.bstrVal = bstrURL;
	vtShow.vt = VT_BOOL;
	vtShow.boolVal = true;
	vtSize.vt = VT_INT;
	vtSize.intVal = 0;
	hr = pWebBrowser2->ShowBrowserBar(&vtBandGUID, &vtShow,&vtSize);
	hr = pWebBrowser2->put_Visible(VARIANT_TRUE);

	// load help page
	_variant_t varEmpty;
	_variant_t vaURL = _bstr_t(ONLINE_HELP_PAGE);
    hr = pWebBrowser2->Navigate2(&vaURL, &varEmpty,&varEmpty,&varEmpty,&varEmpty);
	return TRUE;
}

void CMainDlg::Finished() 
{
	// create Dir
	CString strDir;
	GetDlgItemText(IDC_INSTALL_DIR,strDir.GetBuffer(MAX_PATH),MAX_PATH);
	strDir.ReleaseBuffer();

	BOOL bDirOK = ((strDir.CompareNoCase("c:\\") != 0) && 
		(strDir.CompareNoCase("c:\\program files") != 0) && (strDir.CompareNoCase("c:\\program files\\") != 0));
	if(!bDirOK || strDir.IsEmpty() || (!MyMakePath(strDir) && !DirectoryExists(strDir)))
	{
		MessageBox("Error, install directory is not valid.",MY_APP_NAME,MB_OK);
		GetDlgItem(IDC_NEXT).EnableWindow(true);
		return;
	}
	if(strDir.Right(1) != "\\")
		strDir += "\\";

	m_strTitleText = "Please wait while installation completes...";

	MyWriteProfileString("InstallPath",strDir.Left(strDir.GetLength()-1));

	// copy files
	CString strCurDir;
	GetModuleFileName(NULL,strCurDir.GetBuffer(MAX_PATH),MAX_PATH); 
	strCurDir.ReleaseBuffer();
	strCurDir = strCurDir.Left(strCurDir.ReverseFind('\\')+1);

	// todo read manifest and copy files
	CString strFile = OCX_TO_RUN_NAME; // BHO Dll file
	if(!CopyFile(strCurDir + strFile, strDir + strFile,false) &&
		!FileExists(strDir + strFile))
	{
		MessageBox("Error, failed to copy install file, check disk space free and uninstall any old versions of this software.",MY_APP_NAME,MB_OK);
		GetDlgItem(IDC_NEXT).EnableWindow(true);
		return;
	}

	// register ocx
	if(!RegisterOCX(strDir + strFile))
		MessageBox("Error, failed to register OCX. Do you have Internet Explorer 5.5+ installed? Also use Windows update to look for system file updates.",MY_APP_NAME,MB_OK);
	
	// copy uninstaller to win dir
	CString strWin;
	GetWindowsDirectory(strWin.GetBuffer(MAX_PATH),MAX_PATH);
	strWin.ReleaseBuffer();
	if(strWin.Right(1) != "\\")
		strWin += "\\";
	strWin += EXE_UNINSTALLER_NAME;

	if(FileExists(strWin))
	{
		MarkFileNormal(strWin);
		DeleteFile(strWin);
	}
	if(!CopyFile(strCurDir + EXE_UNINSTALLER_NAME, strWin,false) &&	!FileExists(strWin))
	{
		MessageBox("Error, failed to copy uninstaller, check disk space free and uninstall any old versions of this software.",MY_APP_NAME,MB_OK);
	}

	// copy readme.txt file
	strFile = _T("readme.txt"); 
	if(!CopyFile(strCurDir + strFile, strDir + strFile,false) && !FileExists(strDir + strFile))
	{
		MessageBox("Error, failed to copy install file, check disk space free and uninstall any old versions of this software.",MY_APP_NAME,MB_OK);
	}

	// copy sapi installer files
	strFile = SAPI_INSTALL_FILE1; 
	if(!CopyFile(strCurDir + strFile, strDir + strFile,false) && !FileExists(strDir + strFile))
	{
		MessageBox("Error, failed to copy install file, check disk space free and uninstall any old versions of this software.",MY_APP_NAME,MB_OK);
		GetDlgItem(IDC_NEXT).EnableWindow(true);
		return;
	}
	strFile = SAPI_INSTALL_FILE2; 
	if(!CopyFile(strCurDir + strFile, strDir + strFile,false) && !FileExists(strDir + strFile))
	{
		MessageBox("Error, failed to copy install file, check disk space free and uninstall any old versions of this software.",MY_APP_NAME,MB_OK);
		GetDlgItem(IDC_NEXT).EnableWindow(true);
		return;
	}
	strFile = SAPI_INSTALL_FILE3; 
	if(!CopyFile(strCurDir + strFile, strDir + strFile,false) && !FileExists(strDir + strFile))
	{
		MessageBox("Error, failed to copy install file, check disk space free and uninstall any old versions of this software.",MY_APP_NAME,MB_OK);
		GetDlgItem(IDC_NEXT).EnableWindow(true);
		return;
	}
	strFile = SAPI_INSTALL_FILE4; 
	if(!CopyFile(strCurDir + strFile, strDir + strFile,false) && !FileExists(strDir + strFile))
	{
		MessageBox("Error, failed to copy install file, check disk space free and uninstall any old versions of this software.",MY_APP_NAME,MB_OK);
		GetDlgItem(IDC_NEXT).EnableWindow(true);
		return;
	}
	strFile = SAPI_INSTALL_FILE5; 
	if(!CopyFile(strCurDir + strFile, strDir + strFile,false) && !FileExists(strDir + strFile))
	{
		MessageBox("Error, failed to copy install file, check disk space free and uninstall any old versions of this software.",MY_APP_NAME,MB_OK);
		GetDlgItem(IDC_NEXT).EnableWindow(true);
		return;
	}

	// create links in program files
 	BOOL bOK = CreateProgramsLink(strWin,CString(MY_APP_NAME) + "\\Uninstall.lnk","Uninstall");
	bOK = CreateProgramsLink(GetRegisterURL(),CString(MY_APP_NAME) + "\\Register.lnk","Order Registration Code");
	bOK = CreateProgramsLink(ONLINE_HELP_PAGE,CString(MY_APP_NAME) + "\\help.lnk","Help");
	// create link in add/remove programs
	CreateLinkAddRemovePrograms(strWin,MY_APP_NAME);	

	// create install date if needed
	CTime tm;
	tm = tm.GetCurrentTime();
	
	CString strFilePath;
	GetSystemDirectory(strFilePath.GetBuffer(MAX_PATH),MAX_PATH);
	strFilePath.ReleaseBuffer();
	strFilePath += "\\" + CString(APP_FILE);
	CString strInstallTime = ParseXML("InstallTime",ReadEncryptedFile(strFilePath,ENCRYPT_KEY));
	
	if(strInstallTime.IsEmpty())
	{
		strInstallTime.Format("%u",(long)tm.GetTime());
		CString strData = "<InstallTime>" + strInstallTime + "</InstallTime>";
		WriteEncryptedFile(strFilePath,ENCRYPT_KEY,strData);
		MyWriteProfileInt("id",(long)tm.GetTime());		
	}
	// run TTS installer
	RunTTSInstaller(strDir);
	// check BHO enabled
	CheckBHOEnabled();
	// show toolbar in browser and load help page
	ShowToolBarAndHelp();

	CloseDialog(0);
}

void CMainDlg::RunTTSInstaller(CString strDir)
{
	if(NeedsTTSINstall())
	{
		ShowWindow(SW_HIDE);

		// run installer
		PROCESS_INFORMATION pi;
		ZeroMemory(&pi,sizeof(pi));
		STARTUPINFO si;
		ZeroMemory(&si,sizeof(si));
		BOOL bOK = CreateProcess(strDir + SAPI_INSTALL_FILE1,NULL,NULL,NULL,false,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi);
		WaitForSingleObject(pi.hProcess,INFINITE);
	}

	// delete file
	DeleteFile(strDir + SAPI_INSTALL_FILE1);
	DeleteFile(strDir + SAPI_INSTALL_FILE2);
	DeleteFile(strDir + SAPI_INSTALL_FILE3);
	DeleteFile(strDir + SAPI_INSTALL_FILE4);
	DeleteFile(strDir + SAPI_INSTALL_FILE5);
}

LRESULT CMainDlg::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if(wParam == ID_FINISH)
	{
		KillTimer(m_nTimerFinish);
		m_nTimerFinish = NULL;
		Finished();
	}
	return S_OK;
}



