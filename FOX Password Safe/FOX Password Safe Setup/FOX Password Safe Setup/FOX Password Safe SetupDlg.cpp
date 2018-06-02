// FOX Password Safe SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe Setup.h"
#include "FOX Password Safe SetupDlg.h"
#include ".\fox password safe setupdlg.h"
#include "helpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFOXPasswordSafeSetupDlg dialog



CFOXPasswordSafeSetupDlg::CFOXPasswordSafeSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFOXPasswordSafeSetupDlg::IDD, pParent)
	, m_strInstallPath(_T(""))
	, m_strLicense(_T(""))
	, m_nPage(0)
	, m_strTitleText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CFOXPasswordSafeSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INSTALL_PATH, m_strInstallPath);
	DDX_Control(pDX, IDC_EDIT_INSTALL_PATH, m_ctlInstallPath);
	DDX_Control(pDX, IDC_BUTTON_BROWSE, m_ctlBrowse);
	DDX_Control(pDX, IDC_EDIT_LICENSE, m_ctlLicense);
	DDX_Control(pDX, IDOK, m_ctlNextBut);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_ctlBackButton);
}

BEGIN_MESSAGE_MAP(CFOXPasswordSafeSetupDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnBnClickedButtonBack)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnBnClickedButtonBrowse)
END_MESSAGE_MAP()

// CFOXPasswordSafeSetupDlg message handlers
BOOL CFOXPasswordSafeSetupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// load license string
	LoadString(AfxGetInstanceHandle(),IDS_STRING_LICENSE,m_strLicense.GetBuffer(4024),4024);
	m_strLicense.ReleaseBuffer();
	m_ctlLicense.SetWindowText(m_strLicense);
	
	// create license font
	m_LicFont.CreatePointFont(120,"Times New Roman");
	m_ctlLicense.SetFont(&m_LicFont,true);

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

	m_strInstallPath = strReturn + "\\" + CString(MY_APP_NAME);
	m_strInstallPath.Replace("\\\\","\\");

	ShowPage1();

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFOXPasswordSafeSetupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFOXPasswordSafeSetupDlg::OnBnClickedButtonBack()
{
	if(m_nPage == 3)
		ShowPage2();
	else if(m_nPage == 2)
		ShowPage1();
}

void CFOXPasswordSafeSetupDlg::OnBnClickedOk()
{
	if(m_nPage == 1)
		ShowPage2();
	else if(m_nPage == 2)
		ShowPage3();
	else
		Finished();
}

void CFOXPasswordSafeSetupDlg::OnBnClickedButtonBrowse()
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
				// At this point pszBuffer contains the selected path */
				CString strTest = "\\" + CString(MY_APP_NAME);
				m_strInstallPath = pszBuffer;
				CString strText = m_strInstallPath.Right(strTest.GetLength());
				strText.MakeLower();
				if(strText.CompareNoCase(strTest) != 0)
					m_strInstallPath += "\\" + CString(MY_APP_NAME);
				m_strInstallPath.Replace("\\\\","\\");
            }
            // Free the PIDL allocated by SHBrowseForFolder.
            pMalloc->Free(pidl);
        }
        // Release the shell's allocator.
        pMalloc->Release();
    }

	UpdateData(false);			
}

// show first page screen
void CFOXPasswordSafeSetupDlg::ShowPage1(void)
{
	m_nPage = 1;

	m_strTitleText = "Welcome to the " + CString(MY_APP_NAME) + " setup wizard.";

	m_ctlBackButton.EnableWindow(false);
	m_ctlNextBut.SetWindowText("Next >");
	m_ctlInstallPath.ShowWindow(SW_HIDE);
	m_ctlBrowse.ShowWindow(SW_HIDE);
	m_ctlLicense.ShowWindow(SW_HIDE);

	InvalidateRect(NULL);
}

// show screen 2
void CFOXPasswordSafeSetupDlg::ShowPage2(void)
{
	m_nPage = 2;

	m_strTitleText = "Please read and accept the license agreement\r\nto continue.";

	m_ctlBackButton.EnableWindow(true);
	m_ctlNextBut.SetWindowText("I Agree");
	m_ctlInstallPath.ShowWindow(SW_HIDE);
	m_ctlBrowse.ShowWindow(SW_HIDE);
	m_ctlLicense.ShowWindow(SW_SHOW);

	InvalidateRect(NULL);
}

// show screen 3
void CFOXPasswordSafeSetupDlg::ShowPage3(void)
{
	m_nPage = 3;

	m_strTitleText = "Please select the installation folder.";

	m_ctlNextBut.SetWindowText("Finished");
	m_ctlInstallPath.ShowWindow(SW_SHOW);
	m_ctlBrowse.ShowWindow(SW_SHOW);
	m_ctlLicense.ShowWindow(SW_HIDE);

	InvalidateRect(NULL);
}

void CFOXPasswordSafeSetupDlg::OnPaint() 
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

	if(m_nPage == 1)
	{
		CFont font2;
		font2.CreatePointFont(120,"Times New Roman");
		dc.SelectObject(&font2);
		CRect rectText(10,100,475,288);
		dc.DrawText("Click 'Next' to continue.",rectText,DT_LEFT|DT_WORDBREAK);
	}
	dc.SelectObject(pOld);
}

// install files
void CFOXPasswordSafeSetupDlg::Finished(void)
{
	UpdateData(true);
	InvalidateRect(NULL);

	// create Directory
	BOOL bDirOK = ((m_strInstallPath.CompareNoCase("c:\\") != 0) && 
		(m_strInstallPath.CompareNoCase("c:\\program files") != 0) && (m_strInstallPath.CompareNoCase("c:\\program files\\") != 0));
	if(!bDirOK || m_strInstallPath.IsEmpty() || (!MyMakePath(m_strInstallPath) && !DirectoryExists(m_strInstallPath)))
	{
		AfxMessageBox("Error, install directory is not valid.");
		return;
	}
	if(m_strInstallPath.Right(1) != "\\")
		m_strInstallPath += "\\";

	m_strTitleText = "Please wait while installation completes...";

	MyWriteProfileString("InstallPath",m_strInstallPath.Left(m_strInstallPath.GetLength()-1));

	// copy files
	CString strCurDir;
	GetModuleFileName(NULL,strCurDir.GetBuffer(MAX_PATH),MAX_PATH); 
	strCurDir.ReleaseBuffer();
	strCurDir = strCurDir.Left(strCurDir.ReverseFind('\\')+1);

	// todo read manifest and copy files
	CString strFile = EXE_TO_RUN_NAME; // FOX Password Safe.exe
	if(!CopyFile(strCurDir + strFile, m_strInstallPath + strFile,false) &&
		!FileExists(m_strInstallPath + strFile))
	{
		AfxMessageBox("Error, failed to copy install file, check disk space free and uninstall any old versions of this software.");
		return;
	}
	
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
		AfxMessageBox("Error, failed to copy uninstaller, check disk space free and uninstall any old versions of this software.");
	}

	// create links in program files
 	BOOL bOK = CreateProgramsLink(strWin,CString(MY_APP_NAME) + "\\Uninstall.lnk","Uninstall");
	bOK = CreateProgramsLink(GetRegisterURL(),CString(MY_APP_NAME) + "\\Register.lnk","Order Registration Code");
	bOK = CreateProgramsLink(ONLINE_HELP_PAGE,CString(MY_APP_NAME) + "\\help.lnk","Help");
	bOK = CreateProgramsLink(m_strInstallPath + strFile,CString(MY_APP_NAME) + "\\" + CString(MY_APP_NAME) + ".lnk",MY_APP_NAME);
	// create a desktop link
	bOK = CreateDesktopLink(m_strInstallPath + strFile,CString(MY_APP_NAME) + ".lnk",MY_APP_NAME);
	// create link in add/remove programs
	CreateLinkAddRemovePrograms(strWin,MY_APP_NAME);	

	// create install date if needed
	time_t tm;
	time(&tm);
	
	CString strFilePath;
	GetSystemDirectory(strFilePath.GetBuffer(MAX_PATH),MAX_PATH);
	strFilePath.ReleaseBuffer();
	strFilePath += "\\" + CString(APP_FILE);
	CString strInstallTime = ParseXML("InstallTime",ReadEncryptedFile(strFilePath,ENCRYPT_KEY));
	
	if(strInstallTime.IsEmpty())
	{
		strInstallTime.Format("%u",(long)tm);
		CString strData = "<InstallTime>" + strInstallTime + "</InstallTime>";
		WriteEncryptedFile(strFilePath,ENCRYPT_KEY,strData);
		MyWriteProfileInt("id",(long)tm);		
	}
	// load app
	if(!LoadExe(m_strInstallPath + strFile))
		AfxMessageBox("Error, failed to launch application.");

	// load help page
	LoadURLInBrowser(ONLINE_HELP_PAGE);

	// close installer
	CDialog::OnOK();
}
