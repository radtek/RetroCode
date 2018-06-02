// SMCUnInstallDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMCUnInstall.h"
#include "SMCUnInstallDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
typedef HRESULT (STDAPICALLTYPE *CTLREGPROC)(void) ; //see COMPOBJ.H
#define DEFAULT_INSTALL		"c:\\program files\\Foxmediacenter"
#define		APP_EXE_CLASSNAME				"81557EA5-E161-4fd5-9CAA-1DAC5BE73E25"


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
// CSMCUnInstallDlg dialog

CSMCUnInstallDlg::CSMCUnInstallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSMCUnInstallDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSMCUnInstallDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSMCUnInstallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSMCUnInstallDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSMCUnInstallDlg, CDialog)
	//{{AFX_MSG_MAP(CSMCUnInstallDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMCUnInstallDlg message handlers

BOOL CSMCUnInstallDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSMCUnInstallDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSMCUnInstallDlg::OnPaint() 
{
	CDialog::OnPaint();
}

HCURSOR CSMCUnInstallDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL UnRegisterOCX(CString strPath)
{
	BOOL bResult = FALSE;

	HMODULE hModule = LoadLibrary(strPath);
	strPath.ReleaseBuffer() ;
	if (!hModule)
	{
		DWORD dwErr = GetLastError();
		return FALSE;
	}
			
	CTLREGPROC DLLRegisterServer = (CTLREGPROC)::GetProcAddress(hModule,"DllUnregisterServer" ) ;
	if (DLLRegisterServer != NULL)
	{
		HRESULT regResult = DLLRegisterServer() ;
		bResult = (regResult == NOERROR); 
		if(!bResult)
		{
			DWORD dwErr = GetLastError();
		}
	}
	else
	{
		DWORD dwErr = GetLastError();
	}
	FreeLibrary(hModule);          
		
	return bResult;	
}

void UnRegisterStartupOcxs(CString strPath)
{
	strPath += "\\";
	
	SECFileSystem fp;
	CStringList* pStrList = fp.GetFileList(strPath + "*.ocx",fp.allfiles);
	if(pStrList->GetCount()>0)
	{
		POSITION pos = pStrList->GetHeadPosition();
		while(pos !=NULL)
		{
			CString str = pStrList->GetNext(pos);
			UnRegisterOCX(str);
		}
	}
	delete pStrList;
}

CString GetProgramsPath()
{
	CString strRegPrograms;
	SECRegistry reg;
	BOOL bOk = reg.Connect(HKEY_CURRENT_USER);
	bOk = reg.Open("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",SECRegistry::permissionRead);
	bOk = reg.GetStringValue("Programs", strRegPrograms); 

	return strRegPrograms;
}

CString GetStartUpPath()
{
	CString strRegStartup;
	SECRegistry reg;
	BOOL bOk = reg.Connect(HKEY_CURRENT_USER);
	bOk = reg.Open("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",SECRegistry::permissionRead);
	bOk = reg.GetStringValue("Startup", strRegStartup); 

	return strRegStartup;
}

CString GetWinDesktopPath()
{
	CString strRegStartup;
	SECRegistry reg;
	BOOL bOk = reg.Connect(HKEY_CURRENT_USER);
	bOk = reg.Open("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",SECRegistry::permissionRead);
	bOk = reg.GetStringValue("Desktop", strRegStartup); 

	return strRegStartup;
}

void Cleanup()
{
	CString strPath = AfxGetApp()->GetProfileString("Settings","InstallPath",DEFAULT_INSTALL);
	if(strPath.IsEmpty())
		return;

	SECFileSystem fp;
	// delete from program files
	strPath = GetProgramsPath();
	CString strLink = strPath + "\\";
	strLink += "Fox Media Center";
	fp.DeleteDirectory(strLink,TRUE);	
	// delete from desktop
	strPath = GetWinDesktopPath();
	strLink = strPath + "\\";
	strLink += "Fox Media Center.lnk";
	fp.DeleteFile(strLink);
}

void CSMCUnInstallDlg::OnOK() 
{
	// unasscoiate file types
	CStringArray* pstra = EnumKnowFileTypesFromReg();
	for(int n=0;n<pstra->GetSize();n++)
		UnAssociate(pstra->GetAt(n));
	delete pstra;

	SHChangeNotify(SHCNE_ASSOCCHANGED,SHCNF_IDLIST,NULL,NULL);

	HWND handle = ::FindWindow(APP_EXE_CLASSNAME,NULL);
	if(handle)
	{
		MessageBox("Fox Media Center is still running. Right click on the icon in the task tray and select 'Exit'.","Fox Media Center",MB_OK);
		return;
	}

	
	// install path
	CString strPath = AfxGetApp()->GetProfileString("Settings","InstallPath",DEFAULT_INSTALL);
	// unregister ocx's
	UnRegisterStartupOcxs(strPath);
	// delete Files
	SECFileSystem fp;
	if(!strPath.IsEmpty())
		fp.DeleteDirectory(strPath,TRUE);						

	// delete start menus
	Cleanup();
	
	// Delete Registry
	SECRegistry reg;
	BOOL bOk = reg.Connect(HKEY_CURRENT_USER);
	bOk = reg.Open("Software\\SteveSoftware",SECRegistry::permissionWrite);
	bOk = reg.DeleteKey("FoxMediaCenter", TRUE);
	reg.Close();

	MessageBox("Uninstall complete..","Fox Media Center",MB_OK);
		
	CDialog::OnOK();
}

CStringArray* CSMCUnInstallDlg::EnumKnowFileTypesFromReg()
{
	CStringArray* pstra = new CStringArray;

	// HKEY_CURRENT_USER\Software\SteveSoftware\FoxMediaCenter
	SECRegistry reg;
	// read mime type
	CString strMimeType;
	BOOL lErr = false;
	lErr = reg.Connect(HKEY_CURRENT_USER);
	lErr = reg.Open("Software\\SteveSoftware\\FoxMediaCenter",reg.permissionAllAccess);
	if(!lErr)
		return pstra;

	UINT nIndex = 0;
	CString strKeyName;
	CString strData;
	while (reg.EnumerateKeys(nIndex++, strKeyName))
	{
		
		if(!strKeyName.IsEmpty() && strKeyName.GetAt(0) == '.')
		{
			if(AfxGetApp()->GetProfileString(strKeyName,"Associated","FALSE") == "TRUE")
			{
				pstra->Add(strKeyName);
			}
		}
	}
	reg.Close();

	return pstra;
}

void CSMCUnInstallDlg::UnAssociate(CString strExt)
{
	// read mime type
	DWORD dwLen = 1024;
	CRegKey reg;
	long lErr = 0;
	CString strMimeType;
	lErr = reg.Open(HKEY_CLASSES_ROOT,strExt);
	lErr = reg.QueryValue(strMimeType.GetBuffer(1024),"OldMimeType",&dwLen);
	strMimeType.ReleaseBuffer();
	if(!strMimeType.IsEmpty())
	{
		lErr = reg.SetKeyValue("",strMimeType,"" );
	}
	else
	{
		lErr = reg.DeleteValue("");
	}	
	reg.Close();
}