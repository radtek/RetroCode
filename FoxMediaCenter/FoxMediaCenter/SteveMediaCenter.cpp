// SteveMediaCenter.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SteveMediaCenter.h"

#include "MainFrm.h"
#include "helpers.h"
#include "CMyCommandLineInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterApp

BEGIN_MESSAGE_MAP(CSteveMediaCenterApp, CWinApp)
	//{{AFX_MSG_MAP(CSteveMediaCenterApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterApp construction

CSteveMediaCenterApp::CSteveMediaCenterApp()
{
	m_bHasCheckedForProxyPasswordFromFile = false;
	m_bCheckingProxyName = false;
	m_bIsAutoDialOn = false;
	m_nREAD_WAIT_TIME = READ_WAIT_TIME;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSteveMediaCenterApp object

CSteveMediaCenterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterApp initialization

BOOL CSteveMediaCenterApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	free((void*)m_pszRegistryKey);
	m_pszRegistryKey =_tcsdup(_T("SteveSoftware"));
	free((void*)m_pszProfileName);
	m_pszProfileName =_tcsdup(_T("FoxMediaCenter"));


	AfxOleInit();
	AfxEnableControlContainer();
	AfxSocketInit();

	CMyCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	BOOL bHasFiles = (cmdInfo.m_straFiles.GetSize() > 0);
	if(bHasFiles)
	{
		if(SendMessageToInstanseOfApp("<Message>Testing</Message>"))
		{
			for(int n=0;n<cmdInfo.m_straFiles.GetSize();n++)
			{
				CString strUrl = cmdInfo.m_straFiles.GetAt(n);
				AddToInstancePlayList(strUrl);
			}
			return false;
		}
	}
	else
	{
		if(SendMessageToInstanseOfApp("<Message>ShowPlayList</Message>"))
			return false;
	}

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;
	
	BOOL bAutoLoadPlayList = (cmdInfo.m_straFiles.GetSize() == 0);
	pFrame->m_bAutoLoadPlayList = bAutoLoadPlayList;
	BOOL bOK = pFrame->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,	NULL);

	if(IsWindow(pFrame->m_hWnd))
	{
		pFrame->ShowWindow(SW_HIDE);
		pFrame->UpdateWindow();
	}

	if(!bAutoLoadPlayList)
	{
		pFrame->LoadTempPlayList(&cmdInfo.m_straFiles);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterApp message handlers





/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
		// No message handlers
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

// App command to run the dialog
void CSteveMediaCenterApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterApp message handlers

