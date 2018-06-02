// SMCSetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMCSetup.h"
#include "SMCSetupDlg.h"
#include "helpers.h"
#include "Defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
typedef HRESULT (STDAPICALLTYPE *CTLREGPROC)(void) ; //see COMPOBJ.H

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMCSetupDlg dialog

CSMCSetupDlg::CSMCSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSMCSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSMCSetupDlg)
	m_strDir = _T("");
	m_bInstallDivx = FALSE;
	m_bInstallOgg = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nPage = 1;
}

void CSMCSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSMCSetupDlg)
	DDX_Control(pDX, IDC_OGG, m_check2);
	DDX_Control(pDX, IDC_INSTALL_DIVX, m_check1);
	DDX_Control(pDX, IDC_CLICK_NEXT, m_ctlClickNext);
	DDX_Control(pDX, IDOK, m_ctlDone);
	DDX_Control(pDX, IDC_PREVIOUS, m_ctlPrevious);
	DDX_Control(pDX, IDC_NEXT, m_ctlNext);
	DDX_Control(pDX, IDC_LICENSE_HEADER, m_ctlLicenseHeader);
	DDX_Control(pDX, IDC_LICENSE, m_ctlLicense);
	DDX_Control(pDX, IDC_INTRO_IMAGE, m_ctlImage);
	DDX_Control(pDX, IDC_INSTALL_DIR, m_ctlDir);
	DDX_Control(pDX, IDC_CHOOSE_DIR_HEADER, m_ctlDirHeader);
	DDX_Control(pDX, IDC_BROWSE, m_butBrowse);
	DDX_Text(pDX, IDC_INSTALL_DIR, m_strDir);
	DDX_Check(pDX, IDC_INSTALL_DIVX, m_bInstallDivx);
	DDX_Check(pDX, IDC_OGG, m_bInstallOgg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSMCSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSMCSetupDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMCSetupDlg message handlers

BOOL CSMCSetupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_ctlLicense.SetWindowText("This software is freeware. Feel free to distibute this software in any manner you like as long as you don't charge for it. This software is written with the best of my ability to be bug free. I am not liable for any bugs or problems the software may cause you. I hope you find the software useful and have a nice day....");
	m_strDir = "C:\\Program Files\\FoxMediaCenter";

	m_ctlClickNext.SetColor(RGB(0,0,0));
	m_ctlClickNext.m_dwTextColor = RGB(255,255,255);


	ShowPage1();

	m_bInstallDivx = true;
	m_bInstallOgg = true;

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSMCSetupDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSMCSetupDlg::OnPaint() 
{
	if(m_nPage == 1)
	{
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		CBrush br;
		br.CreateSolidBrush(0x000000);
		dc.FillRect(rect,&br);
	}
	else
		CDialog::OnPaint();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSMCSetupDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSMCSetupDlg::OnBrowse() 
{
	LPMALLOC pMalloc;
    /* Gets the Shell's default allocator */
    if (::SHGetMalloc(&pMalloc) == NOERROR)
    {
        BROWSEINFO bi;
        char pszBuffer[MAX_PATH];
        LPITEMIDLIST pidl;
        // Get help on BROWSEINFO struct - it's got all the bit settings.
        bi.hwndOwner = GetSafeHwnd();
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
				m_strDir = pszBuffer;
            }
            // Free the PIDL allocated by SHBrowseForFolder.
            pMalloc->Free(pidl);
        }
        // Release the shell's allocator.
        pMalloc->Release();
    }

	UpdateData(FALSE);			
}

void CSMCSetupDlg::OnPrevious() 
{
	if(m_nPage == 3)
		ShowPage2();
	else if(m_nPage == 2)
		ShowPage1();
	InvalidateRect(NULL);
}

void CSMCSetupDlg::OnNext() 
{
	if(m_nPage == 1)
		ShowPage2();
	else if(m_nPage == 2)
		ShowPage3();
	InvalidateRect(NULL);
}

void CSMCSetupDlg::ShowPage1()
{
	m_nPage = 1;

	m_ctlDone.ShowWindow(SW_HIDE);
	m_ctlPrevious.EnableWindow(FALSE);
	m_ctlNext.ShowWindow(SW_SHOW);
	m_ctlNext.EnableWindow();

	m_ctlImage.ShowWindow(TRUE);
	m_ctlClickNext.ShowWindow(TRUE);

	m_ctlLicenseHeader.ShowWindow(FALSE);
	m_ctlLicense.ShowWindow(FALSE);
	m_ctlDir.ShowWindow(FALSE);
	m_ctlDirHeader.ShowWindow(FALSE);
	m_butBrowse.ShowWindow(FALSE);
	m_check1.ShowWindow(FALSE);
	m_check2.ShowWindow(FALSE);
}

void CSMCSetupDlg::ShowPage2()
{
	m_nPage = 2;

	m_ctlPrevious.EnableWindow();
	m_ctlNext.EnableWindow();
	m_ctlDone.ShowWindow(SW_HIDE);
	m_ctlNext.ShowWindow(SW_SHOW);

	m_ctlImage.ShowWindow(FALSE);
	m_ctlClickNext.ShowWindow(FALSE);

	m_ctlLicenseHeader.ShowWindow(TRUE);
	m_ctlLicense.ShowWindow(TRUE);
	m_ctlDir.ShowWindow(FALSE);
	m_ctlDirHeader.ShowWindow(FALSE);
	m_butBrowse.ShowWindow(FALSE);

	m_check1.ShowWindow(FALSE);
	m_check2.ShowWindow(FALSE);
}

void CSMCSetupDlg::ShowPage3()
{
	m_nPage = 3;

	m_ctlPrevious.EnableWindow();
	m_ctlNext.EnableWindow(FALSE);
	m_ctlDone.ShowWindow(SW_SHOW);
	m_ctlNext.ShowWindow(SW_HIDE);
	m_ctlDone.EnableWindow();

	m_ctlImage.ShowWindow(FALSE);
	m_ctlClickNext.ShowWindow(FALSE);

	m_ctlLicenseHeader.ShowWindow(FALSE);
	m_ctlLicense.ShowWindow(FALSE);
	m_ctlDir.ShowWindow(TRUE);
	m_ctlDirHeader.ShowWindow(TRUE);
	m_butBrowse.ShowWindow(TRUE);
	m_check1.ShowWindow(TRUE);
	m_check2.ShowWindow(TRUE);
}

BOOL CSMCSetupDlg::RegisterOCX(CString strPath)
{
	BOOL bResult = FALSE;

	HINSTANCE hModule = ::LoadLibrary(strPath.GetBuffer(strPath.GetLength()));
	strPath.ReleaseBuffer() ;
	if (!hModule)
	{
		DWORD dwErr = GetLastError();
		return FALSE;
	}
			
	CTLREGPROC DLLRegisterServer = (CTLREGPROC)::GetProcAddress(hModule,"DllRegisterServer" ) ;
	if (DLLRegisterServer != NULL)
	{
		HRESULT regResult = DLLRegisterServer() ;
		bResult = (regResult == NOERROR) ; 
	}
		
	::FreeLibrary(hModule) ;          
		
	return bResult;	
}

void CSMCSetupDlg::OnOK() 
{
	CWaitCursor wait;
	UpdateData(TRUE);

	SECFileSystem fp;
	// create Dir
	BOOL bDirOK = ((m_strDir.CompareNoCase("c:\\") != 0) && 
		(m_strDir.CompareNoCase("c:\\program files") != 0) && (m_strDir.CompareNoCase("c:\\program files\\") != 0));
	if(!bDirOK || m_strDir.IsEmpty() || (!fp.MakePath(m_strDir) && !fp.DirectoryExists(m_strDir)))
	{
		AfxMessageBox("Error, install directory is not valid.");
		return;
	}

	if(m_strDir.Right(1) != "\\")
		m_strDir += "\\";

	// copy files
	CString strCurDir;
	GetModuleFileName(NULL,strCurDir.GetBuffer(MAX_PATH),MAX_PATH); 
	strCurDir.ReleaseBuffer();
	strCurDir = strCurDir.Left(strCurDir.ReverseFind('\\')+1);

	CString strFile = "FoxMediaCenter.dat";
	if(!fp.CopyFile(strCurDir + strFile, m_strDir + strFile) &&
		!fp.FileExists(m_strDir + strFile))
	{
		AfxMessageBox("Error, failed to copy install file FoxMediaCenter.dat, make sure you unzip all install files to a temp directory and then run Setup.exe.");
		return;
	}

	if(!UnzipFile(m_strDir + strFile))
	{
		AfxMessageBox("Error, failed to unzip conpressed files in FoxMediaCenter.dat, make sure you have some free disk space.");
		return;
	}
	else
		fp.DeleteFile(m_strDir + strFile);

	// copy uninstaller to win dir
	CString strWin;
	GetWindowsDirectory(strWin.GetBuffer(MAX_PATH),MAX_PATH);
	strWin.ReleaseBuffer();
	if(strWin.Right(1) != "\\")
		strWin += "\\";

	if(fp.FileExists(strWin + "FMCUnInstall.exe"))
		fp.DeleteFile(strWin + "FMCUnInstall.exe");
	if(!fp.CopyFile(strCurDir + "FMCUnInstall.exe", strWin + "FMCUnInstall.exe") &&
		!fp.FileExists(strWin + "FMCUnInstall.exe"))
	{
		AfxMessageBox("Error, failed to copy uninstaller, check disk space free and uninstall any old versions of this software.");
	}

	// register ocx
	if(!RegisterOCX(m_strDir + "SteveMediaCenterOcx.ocx") || !RegisterOCX(m_strDir + "SteveMediaPlayer.ocx"))
	{
		AfxMessageBox("Error, failed to register OCX. Please close down any other programs and try again.");
		return;
	}
	// try register tag dll
	RegisterOCX(m_strDir + "id3com.dll");

	// install divx codec
	if(m_bInstallDivx)
	{
		ShowWindow(SW_HIDE);

		CString strLaunchFile = m_strDir + "ffdshow-20020617.exe";

		PROCESS_INFORMATION pInfo;
		memset(&pInfo,0,sizeof(PROCESS_INFORMATION));
		STARTUPINFO startup;
		memset(&startup,0,sizeof(STARTUPINFO));
		startup.cb = sizeof(STARTUPINFO);
		startup.lpReserved = NULL;
		startup.lpDesktop = NULL;
		startup.lpTitle = NULL;
		startup.dwFlags = STARTF_USESHOWWINDOW;
		startup.wShowWindow = SW_NORMAL;
		startup.lpReserved2 = NULL;

		BOOL bOK = CreateProcess(strLaunchFile,NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE|HIGH_PRIORITY_CLASS,NULL,NULL,&startup,&pInfo); 
		WaitForSingleObject(pInfo.hThread,30*1000);
		fp.DeleteFile(strLaunchFile);	
		
		ShowWindow(SW_NORMAL);
	}
	// register divx codec
	if(m_bInstallOgg)
	{
		ShowWindow(SW_HIDE);
		CString strLaunchFile = m_strDir + "OggDS0995.exe";

		PROCESS_INFORMATION pInfo;
		memset(&pInfo,0,sizeof(PROCESS_INFORMATION));
		STARTUPINFO startup;
		memset(&startup,0,sizeof(STARTUPINFO));
		startup.cb = sizeof(STARTUPINFO);
		startup.lpReserved = NULL;
		startup.lpDesktop = NULL;
		startup.lpTitle = NULL;
		startup.dwFlags = STARTF_USESHOWWINDOW;
		startup.wShowWindow = SW_NORMAL;
		startup.lpReserved2 = NULL;

		BOOL bOK = CreateProcess(strLaunchFile,NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE|HIGH_PRIORITY_CLASS,NULL,NULL,&startup,&pInfo); 
		WaitForSingleObject(pInfo.hThread,30*1000);
		fp.DeleteFile(strLaunchFile);

		ShowWindow(SW_NORMAL);
	}

 	BOOL bOK = CreateProgramsLink(strWin + "FMCUnInstall.exe","Fox Media Center\\Uninstall.lnk","Uninstall");
	bOK = CreateProgramsLink(HELP_URL,"Fox Media Center\\help.lnk","Help");
	bOK = CreateProgramsLink(m_strDir + "FoxMediaCenter.exe","Fox Media Center\\Fox Media Center.lnk","Fox Media Player");
	bOK = CreateProgramsLink("http://www.stevefoxover.com/smc/Creating skins.zip","Fox Media Center\\How to make skins.lnk","How to make skins");

	bOK = CreateDesktopLink(m_strDir + "FoxMediaCenter.exe","Fox Media Center.lnk","Fox Media Player");

	CTime tm = CTime::GetCurrentTime();
	AfxGetApp()->WriteProfileInt("Settings","InstallDate",(DWORD)tm.GetTime());	

	// run app
	WinExec(m_strDir + "FoxMediaCenter.exe",SW_HIDE);

	EndDialog(IDOK);
}
