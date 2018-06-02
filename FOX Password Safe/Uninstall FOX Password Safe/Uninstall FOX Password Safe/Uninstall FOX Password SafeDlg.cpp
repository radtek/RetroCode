// Uninstall FOX Password SafeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Uninstall FOX Password Safe.h"
#include "Uninstall FOX Password SafeDlg.h"
#include ".\uninstall fox password safedlg.h"
#include "helpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUninstallFOXPasswordSafeDlg dialog

CUninstallFOXPasswordSafeDlg::CUninstallFOXPasswordSafeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUninstallFOXPasswordSafeDlg::IDD, pParent)
	, m_strTitleText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CUninstallFOXPasswordSafeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUninstallFOXPasswordSafeDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CUninstallFOXPasswordSafeDlg message handlers

BOOL CUninstallFOXPasswordSafeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_strTitleText.Format("Click 'Uninstall' to remove %s\r\nfrom your system.",MY_APP_NAME);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUninstallFOXPasswordSafeDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect(10,10,380,100);
	CFont font;
	font.CreatePointFont(140,"Times New Roman");
	CFont* pOld = (CFont*)dc.SelectObject(&font);

	dc.SetBkMode(TRANSPARENT);   

	CRect rectFill;
	GetClientRect(rectFill);
	rectFill.bottom = 88;
	dc.FillSolidRect(rectFill,RGB(255,255,255));
	dc.DrawText(m_strTitleText,rect,DT_LEFT);
	
	dc.SelectObject(pOld);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUninstallFOXPasswordSafeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUninstallFOXPasswordSafeDlg::OnBnClickedOk()
{
	CString strMsg;
	strMsg.Format("Are you sure you want to uninstall %s?",MY_APP_NAME);
	if(MessageBox(strMsg,MY_APP_NAME,MB_YESNO) == IDYES)
	{
		UninstallApp();
		OnOK();
	}
}

// function to uninstall application
void CUninstallFOXPasswordSafeDlg::UninstallApp(void)
{
	HWND hWnd = ::FindWindow(APP_CLASS_NAME,NULL);
	if(hWnd != NULL)
	{
		DWORD dwProcessId = 0;
		DWORD dwThreadID = GetWindowThreadProcessId(hWnd,&dwProcessId);
		UINT nExitCode = 0;
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessId);
		if(hProcess == NULL || !::TerminateProcess(hProcess,nExitCode))
		{
			TRACE("TerminateProcess failed: %d\r\n",GetLastError());
			AfxMessageBox(CString(MY_APP_NAME) + " is still running.Pleasee close it before continuing.");
		}
		if(hProcess != NULL)
			CloseHandle(hProcess);
	}

	CString strInstallDir = MyGetProfileString("InstallPath",MY_DEFAULT_INSTALL_PATH,1024);
	CString strFile = strInstallDir + "\\" + CString(EXE_TO_RUN_NAME);
	
	// delete files
	if(!DeleteDirectory(strInstallDir) && DirectoryExists(strInstallDir))
	{
		AfxMessageBox("Error, some files could not be removed from " + strInstallDir + " Close all other applications and try deleting the directory manually.");
	}

	// delete create links in program files
	CString strProgramLinks = GetProgramsPath() + "\\";
	strProgramLinks += MY_APP_NAME;
	DeleteDirectory(strProgramLinks);	
	// delete desktop link
	CString strWinDesktopLinks = GetWinDesktopPath() + "\\";
	strWinDesktopLinks += MY_APP_NAME;
	strWinDesktopLinks += ".lnk";
	MarkFileNormal(strWinDesktopLinks);
	DeleteFile(strWinDesktopLinks);

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

	AfxMessageBox("Uninstall complete.");
}
