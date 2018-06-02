// FOX Password Safe.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "MainFrm.h"

#include "FOX Password SafeDoc.h"
#include "LeftView.h"
#include ".\fox password safe.h"
#include "helpers.h"
#include "EnterRegCode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFOXPasswordSafeApp

BEGIN_MESSAGE_MAP(CFOXPasswordSafeApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CFOXPasswordSafeApp construction

CFOXPasswordSafeApp::CFOXPasswordSafeApp()
{
}


// The one and only CFOXPasswordSafeApp object

CFOXPasswordSafeApp theApp;

// CFOXPasswordSafeApp initialization

BOOL CFOXPasswordSafeApp::InitInstance()
{
	// check for previous instance of app APP_CLASS_NAME
	// if found show window on previous instance and exit
	HWND hWnd = ::FindWindow(APP_CLASS_NAME,NULL);
	if(hWnd != NULL)
	{
		::ShowWindow(hWnd,SW_SHOW);
		::PostMessage(hWnd,WM_CHECK_ASK_PASSWORD,0,0);
		return false;
	}

	InitCommonControls();

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CFOXPasswordSafeDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CLeftView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	BOOL bHide = (MyGetProfileInt("MinimizeOnStart",0) == 1); 
	m_pMainWnd->ShowWindow(bHide?SW_HIDE:SW_SHOW);
	m_pMainWnd->UpdateWindow();

	m_pMainWnd->SetWindowText("FOX Password Safe");

	return TRUE;
}

void CFOXPasswordSafeApp::SetPortraitPrintMode()
{
	PRINTDLG pd;
	pd.lStructSize = (DWORD)sizeof(PRINTDLG);
	BOOL bRet = GetPrinterDeviceDefaults(&pd);
	if(bRet)
	{
		// protect memory handle with ::GlobalLock and ::GlobalUnlock
		DEVMODE FAR *pDevMode = (DEVMODE FAR *)::GlobalLock(m_hDevMode);
		// set orientation to landscape
		pDevMode->dmOrientation = DMORIENT_LANDSCAPE;
		//pDevMode->dmOrientation =  DMORIENT_PORTRAIT;
		::GlobalUnlock(m_hDevMode);
	}
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonEnterRegCode();
	afx_msg void OnBnClickedButtonOrderOnline();
	// enter registration text
	void SetRegistrationText(void);
	virtual BOOL OnInitDialog();
	// display registration details
	CString m_strDisplayText;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
, m_strDisplayText(_T(""))
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_REGISTERED_TO, m_strDisplayText);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ENTER_REG_CODE, OnBnClickedButtonEnterRegCode)
	ON_BN_CLICKED(IDC_BUTTON_ORDER_ONLINE, OnBnClickedButtonOrderOnline)
END_MESSAGE_MAP()

// App command to run the dialog
void CFOXPasswordSafeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetRegistrationText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnBnClickedButtonEnterRegCode()
{
	CEnterRegCode dlg;
	if(dlg.DoModal() == IDOK)
	{
		SetRegistrationText();
	}
}

void CAboutDlg::OnBnClickedButtonOrderOnline()
{
	// load online page
	LoadURLInBrowser(GetRegisterURL());
}

// enter registration text
void CAboutDlg::SetRegistrationText(void)
{
	if(IsRegistered())
	{
		CString strName = MyGetProfileString("Name","");
		CString strCompany = MyGetProfileString("Company","");
		m_strDisplayText = strName + "\r\n" + strCompany;
	}
	else
	{
		int nDays = GetFreeTrialDaysUsed();
		if(nDays == -1 || nDays > 29)
			m_strDisplayText = "Not registered. Your free trial has expired. Please Register.";
		else
			m_strDisplayText.Format("Not registered.\r\n\r\nYou have %d days remaining for your free trial.",30 - nDays);
	}
	UpdateData(false);
}

