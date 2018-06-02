// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "MainFrm.h"
#include "LeftView.h"
#include "FOX Password SafeView.h"
#include ".\mainfrm.h"
#include ".\loaddatabasedlg.h"
#include "helpers.h"
#include "CreateNewEntryDlg.h"
#include "NewDatabaseDlg.h"
#include "NewCategoryDlg.h"
#include "BackupDlg.h"
#include "RestoreDlg.h"
#include "NewPasswordDlg.h"
#include "SelectPrintItemsDlg.h"
#include "WarningDlg.h"
#include ".\mysortarray.h"
#include "OptionsDlg.h"
#include "ExpiredPasswordDlg.h"
#include "NagDlg.h"
#include "ChooseNewEntryTypeDlg.h"
#include "NewCreditCardEntryDlg.h"
#include "AskCloseOrHideDlg.h"
#include "EnterRegCode.h"
#include ".\newencryptedfiledlg.h"
#include ".\unencryptdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
	ON_COMMAND(ID_FILE_ADDNEWENTRY, OnFileAddnewentry)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_MESSAGE(WM_STARTUP,OnStartup)
	ON_COMMAND(ID_FILE_ADDNEWCATEGORY, OnFileAddnewcategory)
	ON_BN_CLICKED(IDC_OPEN, ShowLoadDataBaseScreenMsg)
	ON_BN_CLICKED(IDC_NEW, OnFileAddnewentry)
	ON_BN_CLICKED(IDC_COPY_USER_CLIP, OnBnClickedCopyUserClip)
	ON_BN_CLICKED(IDC_COPY_PASS_CLIP, OnBnClickedCopyPassClip)
	ON_BN_CLICKED(IDC_CLEAR_CLIP, OnBnClickedClearClip)
	ON_BN_CLICKED(IDC_LOAD_URL, OnBnClickedLoadUrl)
	ON_BN_CLICKED(IDC_LOAD_FILE, OnBnClickedLoadFile)
	ON_COMMAND(ID_FILE_OPEN, ShowLoadDataBaseScreenMsg)
	ON_COMMAND(ID_FILE_BACKUP, OnFileBackup)
	ON_COMMAND(ID_FILE_RESTOREDATABASE, OnFileRestoredatabase)
	ON_COMMAND(ID_EDIT_EDITSELECTEDCATEGORY, OnEditEditselectedcategory)
	ON_COMMAND(ID_EDIT_EDITSELECTEDENTRY, OnEditEditselectedentry)
	ON_COMMAND(ID_EDIT_DELETESELECTEDCATEGORY, OnEditDeleteselectedcategory)
	ON_COMMAND(ID_HELP_ONLINEHELPPAGE, OnHelpOnlinehelppage)
	ON_COMMAND(ID_EDIT_COPY, OnBnClickedCopyUserClip)
	ON_COMMAND(ID_EDIT_COPYPASSWORDTOCLIPBOARD, OnBnClickedCopyPassClip)
	ON_COMMAND(ID_EDIT_EMPTYPASSWORDFROMCLIPBOARD, OnBnClickedClearClip)
	ON_COMMAND(ID_FILE_CHANGEDATABASEPASSWORD, OnFileChangedatabasepassword)
	ON_MESSAGE(WM_TRAY_NOTIFICATION_MSG,OnSystemTrayMsg)
	ON_COMMAND(ID_TRAYMENU_SHOWFOXPASSWORDSAFE,OnTraymenuShowfoxpasswordsafe) 
	ON_COMMAND(ID_TRAYMENU_EXIT, OnTraymenuExit)
	ON_COMMAND_RANGE(ID_BASE_MENU_UID,ID_BASE_MENU_UID + MAX_POPUP_MENUS,OnClickConnectToURL)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_EDIT_LOCKDOWNWEBBROWSER, OnEditLockdownwebbrowser)
	ON_COMMAND(ID_EDIT_RESTOREBROWSERTODEFAULT, OnEditRestorebrowsertodefault)
	ON_COMMAND(ID_SHOW_POPUP, OnShowPopup)
	ON_WM_TIMER()
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_MESSAGE(WM_CHECK_ASK_PASSWORD, OnCheckAskPassword)
	ON_MESSAGE(WM_LOAD_URL, OnLoadUrl)
	ON_COMMAND(ID_HELP_REGISTERFOXPASSWORDSAFE, OnHelpRegisterfoxpasswordsafe)
	ON_COMMAND(ID_HELP_ENTERREGISTRATIONCODE, OnHelpEnterregistrationcode)
	ON_COMMAND(ID_FIND_ITEM, OnShowSearchPage)
	ON_COMMAND(IDC_BUTTON_SEARCH, OnButtonSearch)	
	ON_COMMAND(IDC_BUTTON_SHOW_ALL, OnButtonShowAll)	
	ON_WM_DROPFILES()
	ON_COMMAND(ID_EDIT_ENCRYPTFILEENTRY, OnEditEncryptfileentry)
	ON_COMMAND(ID_EDIT_UNENCRYPTFILEENTRY, OnEditUnencryptfileentry)
	ON_COMMAND(ID_TOOLS_LOADSELECTEDENCRYPTEDFILE, OnToolsLoadselectedencryptedfile)
	ON_COMMAND(ID_TRAYMENU_ENCRYPTANYUNENCRYPTEDFILES, OnTraymenuEncryptanyunencryptedfiles)
	ON_COMMAND(ID_TOOLS_UNENCRYPTBACKEDUPFILE, OnToolsUnencryptbackedupfile)
	ON_COMMAND(ID_TOOLS_EXPORTDATATOCSVFILE, &CMainFrame::OnToolsExportdatatocsvfile)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
: m_strCurrentLoadedPath(_T(""))
, m_strCurrentPassword(_T(""))
, m_pPopupDlg(NULL)
, m_TimerUnlockBrowser(0)
, m_pLockDown(NULL)
, m_TimerClearPasswords(0)
, m_TimerCheckScreenSaver(0)
, m_bHasNotClearedForScreenSaver(true)
, m_bHasFreeTrialExpired(FALSE)
, m_bSearchVisible(true)
{
}

CMainFrame::~CMainFrame()
{
	RestoreBrowserSecurity();

	if(m_pPopupDlg)
	{
		m_pPopupDlg->SaveRectPos();
		if(IsWindow(m_pPopupDlg->m_hWnd))
			m_pPopupDlg->DestroyWindow();
		delete m_pPopupDlg;
		m_pPopupDlg = NULL;
	}
	if(m_pLockDown)
	{
		if(IsWindow(m_pLockDown->m_hWnd))
			m_pLockDown->DestroyWindow();
		delete m_pLockDown;
		m_pLockDown = NULL;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
		
	// custom toolbar
	if(!m_wndMyToolbar.Create(NULL,"MyToolbar",WS_CHILD|WS_VISIBLE,CRect(0,0,380,22),this,0))
	{
		TRACE("Failed to create custom toolbar\r\n");
		return -1;
	}
	// search bar
	if(!m_SearchBarWnd.Create(NULL,"MySearchbar",WS_CHILD|WS_VISIBLE,CRect(0,0,80,22),this,0))
	{
		TRACE("Failed to create MySearchbar\r\n");
	}
	if (!m_wndReBar.Create(this))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}
	// add toolbar
	if(!m_wndReBar.AddBar(&m_wndMyToolbar))
	{
		TRACE("Failed to add m_wndMyToolbar to rebar\r\n");
	}
	// add search bar
	if(!m_wndReBar.AddBar(&m_SearchBarWnd,NULL,NULL,RBBS_GRIPPERALWAYS|RBBS_BREAK))
	{
		TRACE("Failed to add m_dlgSearchBar to rebar\r\n");
	}
	OnShowSearchPage();

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	BOOL bOK = m_trayIcon.Create(this,WM_TRAY_NOTIFICATION_MSG,hIcon,"FOX Password Safe");
	m_trayIcon.LoadMenu(IDR_MENU_TRAY);
	
	// restore window to last saved position
	SetLastRectPos();

	DragAcceptFiles();

	// start timer check for screen saver active
//	if(MyGetProfileInt("ClearPassOnScreensaver",1) == 1)
//		m_TimerCheckScreenSaver = (UINT)SetTimer(ID_CHECK_SCREEN_SAVER_ACTIVE,SCREEN_SAVER_CHECK_TIME,NULL);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(200, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CFOXPasswordSafeView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1),true);

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL bOK = CFrameWnd::PreCreateWindow(cs);

	PCSTR szClass = APP_CLASS_NAME;
	WNDCLASS wndcls;
	GetClassInfo(AfxGetInstanceHandle(),cs.lpszClass ,&wndcls);
	wndcls.lpszClassName = szClass;
	bOK = AfxRegisterClass(&wndcls);

	cs.lpszClass = szClass;
	
	return bOK;
}

// initialize functions
void CMainFrame::Startup(void)
{
	// show nag screen if not registered once per day
	ShowNagScreen();
	// load default database
	if(MyGetProfileInt("MinimizeOnStart",0) == 0)
	{
		// show create new database
		if(MyGetProfileString("LastDataPath","").IsEmpty())
			OnFileNew();
		// load existing database
		else
			ShowLoadDataBaseScreen();
	}
}

long CMainFrame::OnStartup(WPARAM, LPARAM)
{
	Startup();
	return true;
}

// CMainFrame diagnostics
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers

CFOXPasswordSafeView* CMainFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CFOXPasswordSafeView* pView = DYNAMIC_DOWNCAST(CFOXPasswordSafeView, pWnd);
	return pView;
}

void CMainFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	if (!pCmdUI)
		return;

	CFOXPasswordSafeView* pView = GetRightPane(); 
	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;
		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// otherwise, use dots to reflect the style of the view
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;
			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}

void CMainFrame::OnViewStyle(UINT nCommandID)
{
	// TODO: customize or extend this code to handle choices on the View menu
	CFOXPasswordSafeView* pView = GetRightPane();

	// if the right-hand pane has been created and is a CFOXPasswordSafeView,
	// process the menu commands...
	if (pView != NULL)
	{
		DWORD dwStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// ask the list control to snap to grid
			}
			break;		
		}

		// change the style; window will repaint automatically
		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}

void CMainFrame::ShowLoadDataBaseScreenMsg()
{
	ShowLoadDataBaseScreen();
}

// load default database or open new database dialog
BOOL CMainFrame::ShowLoadDataBaseScreen(void)
{
	// load list of passwords
	BOOL bTryAgain = false;
	do
	{
		bTryAgain = false;
		CLoadDatabaseDlg dlg;
		if(dlg.DoModal() == IDOK)
		{
			CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
			if(pView)
				pView->ClearList();
			CFOXPasswordSafeView* pView2 = (CFOXPasswordSafeView*)m_wndSplitter.GetPane(0,1);
			if(pView2)
				pView2->SetMyData("",false);

			m_strCurrentLoadedPath = dlg.GetPathName();
			m_strCurrentPassword = dlg.GetPassword();
			CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
			if(ParseXML("Version",strData).IsEmpty())
			{
				if(AfxMessageBox("Error, incorrect password. Would you like to try again?",MB_YESNO) == IDYES)
					bTryAgain = true;
			}
			else
			{				
				LoadTreeData(strData,true);
				CString strName = m_strCurrentLoadedPath.Mid(m_strCurrentLoadedPath.ReverseFind('\\')+1);
				m_wndStatusBar.SetPaneText(0,"  Loaded database file '" + strName + "'...");
				return true;
			}
		}
	}
	while(bTryAgain);
	
	if(IsWindow(m_hWnd))
		m_strCurrentPassword = "";
	return false;
}

// loads passwords into tree and list view
void CMainFrame::LoadTreeData(CString strData,BOOL bCanSave)
{
	CWaitCursor wait;
	m_straEntries.RemoveAll();

	CString strVersion = ParseXML("Version",strData);
	BOOL bRemovedExtras = false;
	CStringArray* pStra = LoadEntries(strData,bRemovedExtras);
	for(int n=0;n<pStra->GetCount();n++)
		m_straEntries.Add(pStra->GetAt(n));
	if(bCanSave && bRemovedExtras)
	{
		if(!SaveAllEntries(pStra))
			AfxMessageBox("Error saving new entry to database.");
	}
	delete pStra;

	// sort on header
	CMySortArray sort;
	sort.m_strXMLSortParam = "Header";
	sort.m_strXMLSortParam2 = "Description";
	sort.m_pstraEntries = &m_straEntries;
	sort.Sort();

	// have any passwords expired
    BOOL bHaveAnyPasswordsExpired = false;	

	// add headers to tree view
	CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
	ASSERT(pView);
	if(pView)
	{
		pView->ClearList();
		HTREEITEM hItemParent = NULL;
		HTREEITEM hItemToSelect = NULL;
		int nCount = (int)m_straEntries.GetSize();
		CString strParams;
		for(int n=0;n<nCount;n++)
		{
			strParams = m_straEntries.GetAt(n);
			BOOL bHasChild = (!ParseXML("Description",strParams).IsEmpty());
			CString strHeader = ParseXML("Header",strParams);
			// check if has expired
			CString strExpire = ParseXML("Expires",strParams);
			BOOL bHasExpired = false;
			if(!strExpire.IsEmpty())
				ConvertToDateString(strExpire,bHasExpired);
			if(bHasExpired)
				bHaveAnyPasswordsExpired = true;
			// add header
			if(!bHasChild)
			{
				hItemParent = pView->InsertHeader(strHeader,bHasExpired,n);
			}
			else // add child item
			{
				if(pView->InsertHeader(strHeader,hItemParent,bHasExpired,(int)m_straEntries.GetSize()))
				{
					m_straEntries.Add("<Header>" + strHeader + "</Header>");
				}
				// insert child entry
				pView->InsertChildItem(m_straEntries.GetAt(n),hItemParent,bHasExpired,n);
			}
		}
	}
	// update menus
	m_trayIcon.LoadDynamicMenuItems(IDR_MENU_TRAY, &m_straEntries);
	
	SetLastViewSelection();
	m_bHasNotClearedForScreenSaver = true;
	
	// show expired dialog if applicable
	if(bHaveAnyPasswordsExpired && CanShowExpiredDlg())
	{
		CExpiredPasswordDlg dlg;
		dlg.DoModal();
	}
}

// save entries to current file with current password
BOOL CMainFrame::SaveAllEntries(CStringArray *pstra,BOOL bReloadTree)
{
	if(m_strCurrentPassword.IsEmpty())
	{
		if(!ShowLoadDataBaseScreen())
			return false;
	}
	CString strUpdatedData;
	strUpdatedData.Format("<Version>%s</Version>",VERSION);
	for(int x=0;x<pstra->GetCount();x++)
	{
		CString strEntry = pstra->GetAt(x);
		strUpdatedData += "<Entry>" + strEntry + "</Entry>";
	}
	if(strUpdatedData.Find("<Entry><Entry>") != -1)
	{
		strUpdatedData.Replace("<Entry><Entry>","<Entry>");
		strUpdatedData.Replace("</Entry></Entry>","</Entry>");
	}
	if(!WriteEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword,strUpdatedData))
	{
		return false;
	}
	if(bReloadTree)
		LoadTreeData(strUpdatedData,false);
	return true;
}

// create and open a new password database
void CMainFrame::OnFileNew()
{	
	CNewDatabaseDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
		if(pView)
			pView->ClearList();
		CFOXPasswordSafeView* pView2 = (CFOXPasswordSafeView*)m_wndSplitter.GetPane(0,1);
		if(pView2)
			pView2->SetMyData("",false);

		m_strCurrentLoadedPath = dlg.GetPathName();
		m_strCurrentPassword = dlg.GetPassword();
		MyWriteProfileString("LastDataPath",m_strCurrentLoadedPath);
		CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
		if(strData.IsEmpty())
		{
			AfxMessageBox("Failed to create and load database.");
		}
		else
		{
			LoadTreeData(strData);
			CString strName = m_strCurrentLoadedPath.Mid(m_strCurrentLoadedPath.ReverseFind('\\')+1);
			m_wndStatusBar.SetPaneText(0,"  Loaded database file '" + strName + "'...");
		}
	}
}

// add a new entry to the password database
void CMainFrame::OnFileAddnewentry()
{
	if(m_bHasFreeTrialExpired)
	{
		CNagDlg dlg;
		dlg.DoModal();
		if(m_bHasFreeTrialExpired)
			return;
	}

	if(m_strCurrentLoadedPath.IsEmpty() || m_strCurrentPassword.IsEmpty())
		ShowLoadDataBaseScreen();
	if(m_strCurrentLoadedPath.IsEmpty() || m_strCurrentPassword.IsEmpty())
	{
		AfxMessageBox("Error you must load or create a database and enter the correct password before you can add new entries.");
		return;
	}
	// get selected header if any
	CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
	long lPos = pView->GetSelectedArrayPos();
	// ask if password or credit card entry
	CChooseNewEntryTypeDlg dlgEntry;
	if(dlgEntry.DoModal() != IDOK)
		return;
	// username password entry
	if(dlgEntry.m_bUserNameCheck)
	{
		CCreateNewEntryDlg dlg;
		dlg.m_pstraEntries = &m_straEntries;
		if(lPos >=0 && lPos < m_straEntries.GetSize())
			dlg.m_strSelectHeader = ParseXML("Header",m_straEntries.GetAt(lPos));
		if(dlg.DoModal() == IDOK)
		{
			CString strNewEntry = dlg.GetNewData();
			CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
			TRACE(strNewEntry + "\r\n");
			TRACE(strData + "\r\n");
			strData += strNewEntry;

			if(strData.Find("<Entry><Entry>") != -1)
			{
				strData.Replace("<Entry><Entry>","<Entry>");
				strData.Replace("</Entry></Entry>","</Entry>");
			}

			if(!WriteEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword,strData))
			{
				AfxMessageBox("Error saving new entry to database.");
				return;
			}
			SaveLastViewSelection();
			LoadTreeData(strData);
		}
	}
	// new category
	else if(dlgEntry.m_bNewcategory)
	{
		OnFileAddnewcategory();
	}
	// new encrypted file dlg
	else if(dlgEntry.m_bNewEncryptedFile)
	{
		CNewEncryptedFileDlg dlg;
		dlg.m_pstraEntries = &m_straEntries;
		if(lPos >=0 && lPos < m_straEntries.GetSize())
			dlg.m_strSelectHeader = ParseXML("Header",m_straEntries.GetAt(lPos));
		if(dlg.DoModal() == IDOK)
		{
			CString strNewEntry = dlg.GetNewData();
			CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
			strData += strNewEntry;

			if(strData.Find("<Entry><Entry>") != -1)
			{
				strData.Replace("<Entry><Entry>","<Entry>");
				strData.Replace("</Entry></Entry>","</Entry>");
			}

			if(!WriteEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword,strData))
			{
				AfxMessageBox("Error saving new entry to database.");
				return;
			}
			// encrypt this file
			EncryptFile(strNewEntry);

			SaveLastViewSelection();
			LoadTreeData(strData);
		}
	}
	// credit card entry
	else
	{
		CNewCreditCardEntryDlg dlg;
		dlg.m_pstraEntries = &m_straEntries;
		if(lPos >=0 && lPos < m_straEntries.GetSize())
			dlg.m_strSelectHeader = ParseXML("Header",m_straEntries.GetAt(lPos));
		if(dlg.DoModal() == IDOK)
		{
			CString strNewEntry = dlg.GetNewData();
			CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
			strData += strNewEntry;

			if(strData.Find("<Entry><Entry>") != -1)
			{
				strData.Replace("<Entry><Entry>","<Entry>");
				strData.Replace("</Entry></Entry>","</Entry>");
			}

			if(!WriteEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword,strData))
			{
				AfxMessageBox("Error saving new entry to database.");
				return;
			}
			SaveLastViewSelection();
			LoadTreeData(strData);
		}
	}
}

// add a new category
void CMainFrame::OnFileAddnewcategory()
{
	if(m_strCurrentPassword.IsEmpty())
	{
		if(!ShowLoadDataBaseScreen())
		{
			AfxMessageBox("Error you need to enter the database password.");
			return;
		}
	}
	CNewCategoryDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		CString strNewEntry;
		strNewEntry.Format("<Entry><Header>%s</Header></Entry>",dlg.GetNewName());

		CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
		strData += strNewEntry;
		if(!WriteEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword,strData))
		{
			AfxMessageBox("Error saving new entry to database.");
			return;
		}
		SaveLastViewSelection();
		LoadTreeData(strData);
	}
}

// show the selected data for this header
void CMainFrame::ShowSelectedHeader(long lArrayPos)
{
	if(lArrayPos >= m_straEntries.GetSize())
		return;
	CString strData = m_straEntries.GetAt(lArrayPos);
	CFOXPasswordSafeView* pView = (CFOXPasswordSafeView*)m_wndSplitter.GetPane(0,1);
	ASSERT(pView);
	if(pView)
	{
		pView->SetMyData(strData,true);
	}
}

// copy selected username to clipboard
void CMainFrame::OnBnClickedCopyUserClip()
{
	CFOXPasswordSafeView* pView = (CFOXPasswordSafeView*)m_wndSplitter.GetPane(0,1);
	if(pView)
	{
		CString strUser;
		if(pView->GetSelectedUserName(strUser))
		{
			if(!strUser.IsEmpty())
			{
				CSharedFile sf(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT);
				sf.Write(strUser, strUser.GetLength()); 
				if(OpenClipboard())
				{
					EmptyClipboard();
					SetClipboardData(CF_TEXT, sf.Detach());
					CloseClipboard();
				}
				else
					AfxMessageBox("Error, failed to copy username to the clipboard.");
			}
		}
		else
		{
			AfxMessageBox("Please load and select an entry to copy to the clipboard.");
		}
	}
}

// copy selected password to clipboard
void CMainFrame::OnBnClickedCopyPassClip()
{
	CFOXPasswordSafeView* pView = (CFOXPasswordSafeView*)m_wndSplitter.GetPane(0,1);
	if(pView)
	{
		CString strUser;
		if(pView->GetSelectedPassword(strUser))
		{
			if(!strUser.IsEmpty())
			{
				CSharedFile sf(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT);
				sf.Write(strUser, strUser.GetLength()); 
				if(OpenClipboard())
				{
					EmptyClipboard();
					SetClipboardData(CF_TEXT, sf.Detach());
					CloseClipboard();
				}
				else
					AfxMessageBox("Error, failed to copy password to the clipboard.");
			}
		}
		else
		{
			AfxMessageBox("Please load and select an entry to copy to the clipboard.");
		}
	}
}

// empty password from clipboard
void CMainFrame::OnBnClickedClearClip()
{
	if(OpenClipboard())
	{
		EmptyClipboard();
		CloseClipboard();
	}
	else
		AfxMessageBox("Error, failed to empty the clipboard.");
}

// backup current database
void CMainFrame::OnFileBackup()
{
	if(m_strCurrentPassword.IsEmpty())
	{
		if(!ShowLoadDataBaseScreen())
		{
			AfxMessageBox("Error you must first enter the database password before backing it up.");
			return;
		}
	}
	if(m_strCurrentLoadedPath.IsEmpty())
	{
		AfxMessageBox("Error you must first load a database before backing it up.");
		return;
	}
	CString strDefaultName = m_strCurrentLoadedPath.Mid(m_strCurrentLoadedPath.ReverseFind('\\')+1);
	strDefaultName = strDefaultName.Left(strDefaultName.Find('.'));
	CTime tm = CTime::GetCurrentTime();
	strDefaultName = "Backup " + strDefaultName + tm.Format(" %x");
	strDefaultName.Replace("/","-");
	CBackupDlg dlg;
	dlg.m_strFileName = strDefaultName;
	dlg.m_strPassword = m_strCurrentPassword;
	dlg.m_strCurrentLoadedPath = m_strCurrentLoadedPath;
	dlg.DoModal();
}

// restore an archived database
void CMainFrame::OnFileRestoredatabase()
{
	CRestoreDlg dlg;
	dlg.m_strCurrentLoadedPath = m_strCurrentLoadedPath;
	if(dlg.DoModal() == IDOK)
	{
		m_strCurrentLoadedPath = dlg.GetPathName();
		m_strCurrentPassword = dlg.GetPassword();

		CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
		if(strData.IsEmpty())
		{
			AfxMessageBox("Failed to load database.");
			m_strCurrentPassword = "";
		}
		else
		{
			LoadTreeData(strData);
			CString strName = m_strCurrentLoadedPath.Mid(m_strCurrentLoadedPath.ReverseFind('\\')+1);
			m_wndStatusBar.SetPaneText(0,"  Loaded database file '" + strName + "'...");
		}
	}
}

// alter a category name
void CMainFrame::OnEditEditselectedcategory()
{
	if(m_strCurrentPassword.IsEmpty())
	{
		if(!ShowLoadDataBaseScreen())
		{
			AfxMessageBox("Error you must first enter the database password.");
			return;
		}
	}
	CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
	if(!pView)
		return;
	long lArrayPos = pView->GetSelectedArrayPos();
	if(lArrayPos < 0 || lArrayPos >= m_straEntries.GetSize())
	{
		AfxMessageBox("Please select a category on the left window pane to edit.");
		return;
	}
	CString strData = m_straEntries.GetAt(lArrayPos);
	CString strHeader = ParseXML("Header",strData);
	if(strHeader.IsEmpty())
	{
		AfxMessageBox("Please select a category on the left window pane to edit.");
		return;
	}
	// show dialog to enter new category
	CNewCategoryDlg dlg;
	dlg.m_strCurrentHeader = strHeader;
	if(dlg.DoModal() == IDOK)
	{
		// replace old header with new header
		CString strNewHeader = dlg.GetNewName();
		CString strNewEntry;
		strNewEntry.Format("<Header>%s</Header>",strNewHeader);
		CString strOldEntry;
		strOldEntry.Format("<Header>%s</Header>",strHeader);	

		strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
		strData.Replace(strOldEntry,strNewEntry);

		if(!WriteEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword,strData))
		{
			AfxMessageBox("Error saving new category to database.");
			return;
		}
		LoadTreeData(strData);
	}	
}

// edit the selected entry
void CMainFrame::OnEditEditselectedentry()
{
	if(m_bHasFreeTrialExpired)
	{
		CNagDlg dlg;
		dlg.DoModal();
		if(m_bHasFreeTrialExpired)
			return;
	}

	if(m_strCurrentPassword.IsEmpty())
	{
		if(!ShowLoadDataBaseScreen())
		{
			AfxMessageBox("Error you must first enter the database password.");
			return;
		}
	}
	CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
	if(!pView)
		return;
	long lArrayPos = pView->GetSelectedArrayPos();
	if(lArrayPos < 0 || lArrayPos >= m_straEntries.GetSize())
	{
		AfxMessageBox("Please select an entry on the left window pane to edit.");
		return;
	}
	// current entry data
	CString strOldEntry = "<Entry>" + m_straEntries.GetAt(lArrayPos) + "</Entry>";
	CString strDescription = ParseXML("Description",strOldEntry);
	CString strOldHeader = ParseXML("Header",strOldEntry);
	if(strDescription.IsEmpty())
	{
		AfxMessageBox("Please select an entry on the left window pane to edit.");
		return;
	}
	// show dialog to edit an entry
	// credit card entry edit
	if(ParseXML("CreditCard",strOldEntry) == "TRUE")
	{
		CNewCreditCardEntryDlg dlg;
		dlg.m_pstraEntries = &m_straEntries;
		dlg.m_strCurrentData = strOldEntry;
		if(dlg.DoModal() == IDOK)
		{
			// replace old data with new entry
			CString strNewEntry = dlg.GetNewData();
			CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
			strData.Replace(strOldEntry,strNewEntry);
			if(!WriteEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword,strData))
			{
				AfxMessageBox("Error saving new entry to database.");
				return;
			}
			CString strHeader = ParseXML("Header",strNewEntry);
			CString strDescription = ParseXML("Description",strNewEntry);
			MyWriteProfileString("LastHeader",strHeader);
			MyWriteProfileString("LastDescription",strDescription);		

			LoadTreeData(strData);		
		}		
	}
	// edit encrypted file
	else if(ParseXML("EncryptedFile",strOldEntry) == "TRUE")
	{
		CNewEncryptedFileDlg dlg;
		dlg.m_pstraEntries = &m_straEntries;
		dlg.m_strCurrentData = strOldEntry;
		if(dlg.DoModal() == IDOK)
		{
			// replace old data with new entry
			CString strNewEntry = dlg.GetNewData();
			CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
			strData.Replace(strOldEntry,strNewEntry);
			if(!WriteEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword,strData))
			{
				AfxMessageBox("Error saving new entry to database.");
				return;
			}
			CString strHeader = ParseXML("Header",strNewEntry);
			CString strDescription = ParseXML("Description",strNewEntry);
			MyWriteProfileString("LastHeader",strHeader);
			MyWriteProfileString("LastDescription",strDescription);		

			// encrypt this file
			EncryptFile(strNewEntry);

			LoadTreeData(strData);		
		}	
	}
	// username password edit
	else
	{
		CCreateNewEntryDlg dlg;
		dlg.m_pstraEntries = &m_straEntries;
		dlg.m_strCurrentData = strOldEntry;
		if(dlg.DoModal() == IDOK)
		{
			// replace old data with new entry
			CString strNewEntry = dlg.GetNewData();
			CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
			strData.Replace(strOldEntry,strNewEntry);
			if(!WriteEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword,strData))
			{
				AfxMessageBox("Error saving new entry to database.");
				return;
			}
			CString strHeader = ParseXML("Header",strNewEntry);
			CString strDescription = ParseXML("Description",strNewEntry);
			MyWriteProfileString("LastHeader",strHeader);
			MyWriteProfileString("LastDescription",strDescription);		

			LoadTreeData(strData);		
		}		
	}
}

// change master password for database
void CMainFrame::OnFileChangedatabasepassword()
{
	CNewPasswordDlg dlg;
	dlg.m_strCurrentLoadedPath = m_strCurrentLoadedPath;
	if(dlg.DoModal() == IDOK)
	{
		if(!m_strCurrentPassword.IsEmpty())
			m_strCurrentPassword = dlg.m_strNewPass1;		
	}
}

// delete a category name
void CMainFrame::OnEditDeleteselectedcategory()
{
	if(m_strCurrentPassword.IsEmpty())
	{
		if(!ShowLoadDataBaseScreen())
		{
			AfxMessageBox("Error you must first enter the database password.");
			return;
		}
	}
	CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
	if(!pView)
		return;
	long lArrayPos = pView->GetSelectedArrayPos();
	if(lArrayPos < 0 || lArrayPos >= m_straEntries.GetSize())
	{
		AfxMessageBox("Please select a category on the left window pane to delete.");
		return;
	}
	CString strData = m_straEntries.GetAt(lArrayPos);
	// delete selected entry
	CString strDescription = ParseXML("Description",strData);
	if(!strDescription.IsEmpty())
	{
		OnEditDeleteselectedentry();
		return;
	}
	CString strHeader = ParseXML("Header",strData);
	if(strHeader.IsEmpty())
	{
		AfxMessageBox("Please select a category on the left window pane to delete.");
		return;
	}
	if(AfxMessageBox("Are you sure you want to delete the selected category and all the items it contains?",MB_YESNO) != IDYES)
		return;
	// read all entries
	BOOL bHasRemovedExtras = false;
	CString strAllData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
	CStringArray* pStra = LoadEntries(strAllData,bHasRemovedExtras);
	m_straEntries.RemoveAll();
	for(int n=0;n<pStra->GetCount();n++)
		m_straEntries.Add(pStra->GetAt(n));
	delete pStra;
	pStra = NULL;

	CStringArray straNew;
	for(int n=0;n<m_straEntries.GetSize();n++)
	{
		CString strHeaderList = ParseXML("Header",m_straEntries.GetAt(n));
		if(strHeaderList != strHeader)
			straNew.Add(m_straEntries.GetAt(n));
	}
	strData.Format("<Version>%s</Version>",VERSION);
	for(int n=0;n<straNew.GetSize();n++)
	{
		strData += "<Entry>" + straNew.GetAt(n) + "</Entry>";
	}
	if(!WriteEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword,strData))
	{
		AfxMessageBox("Error saving deleting category from database.");
		return;
	}
	LoadTreeData(strData,true);		
}

// load ONLINE_HELP_PAGE 
void CMainFrame::OnHelpOnlinehelppage()
{
	// load URL in default web browser
	CString strURL = ONLINE_HELP_PAGE;
	LoadURLInBrowser(strURL);
}

// get single list of item data
BOOL CMainFrame::GetSingleSelectedItemData(LPVOID lpVoid)
{	
	if(m_strCurrentPassword.IsEmpty())
	{
		if(!ShowLoadDataBaseScreen())
		{
			AfxMessageBox("Error you must first enter the database password.");
			return false;
		}
	}
	CCustomPrint* pCustPrint = (CCustomPrint*)lpVoid;
	CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
	if(!pView)
		return false;
	long lArrayPos = pView->GetSelectedArrayPos();
	if(lArrayPos < 0 || lArrayPos >= m_straEntries.GetSize())
	{
		AfxMessageBox("Please select an entry on the left window pane to print.");
		return false;
	}
	CString strEntry = m_straEntries.GetAt(lArrayPos);
	if(ParseXML("CreditCard",strEntry) == "TRUE")
		return false;
	// create new entry
	C2DString* p2DEntry = new C2DString;
	int nCol = 0;
	if(pCustPrint->m_bCategory)
	{
		p2DEntry->straCol[nCol] = ParseXML("Header",strEntry);
		nCol++;
	}
	if(pCustPrint->m_bDescription)
	{
		p2DEntry->straCol[nCol] = ParseXML("Description",strEntry);
		nCol++;
	}
	if(pCustPrint->m_bPrintUserID)
	{
		p2DEntry->straCol[nCol] = ParseXML("UserID",strEntry);
		nCol++;
	}
	if(pCustPrint->m_bPrintPass)
	{
		p2DEntry->straCol[nCol] = ParseXML("Password",strEntry);
		nCol++;
	}
	if(pCustPrint->m_bPrintURL)
	{
		p2DEntry->straCol[nCol] = ParseXML("URL",strEntry);
		nCol++;
	}
	if(pCustPrint->m_bPrintNotes)
	{
		p2DEntry->straCol[nCol] = ParseXML("Notes",strEntry);
		nCol++;
	}
	pCustPrint->m_2DstraRows.Add(p2DEntry);

	if(pCustPrint->m_PrintDatabasePassword)
	{
		CString strTitle;
		strTitle.Format("FOX Password Safe - Database: %s  Password: %s"
			,m_strCurrentLoadedPath.Mid(m_strCurrentLoadedPath.ReverseFind('\\')+1), m_strCurrentPassword);
		pCustPrint->SetAppName(strTitle);
	}

	return true;
}

// get all entries of item data
BOOL CMainFrame::GetAllItemData(LPVOID lpVoid)
{	
	if(m_strCurrentPassword.IsEmpty())
	{
		if(!ShowLoadDataBaseScreen())
		{
			AfxMessageBox("Error you must first enter the database password.");
			return false;
		}
	}
	CCustomPrint* pCustPrint = (CCustomPrint*)lpVoid;
	if(m_straEntries.GetSize() == 0)
	{
		AfxMessageBox("Error, there are no entries to print.");
		return false;
	}
	CStringArray straItems;
	straItems.Copy(m_straEntries);
	if(!pCustPrint->m_bCategory)
	{
		// sort on Description
		CMySortArray sort;
		sort.m_strXMLSortParam = "Description";
		sort.m_pstraEntries = &straItems;
		sort.Sort();
	}
	// max length for column text
	int nMaxTextSize = MyGetProfileInt(_T("MaxPrintTextLength"),30);

	for(int n=0;n<straItems.GetSize();n++)
	{
		CString strEntry = straItems.GetAt(n);
		CString strDesc = ParseXML("Description",strEntry);
		if(!strDesc.IsEmpty() && ParseXML("CreditCard",strEntry) != "TRUE")
		{
			// create new entry
			C2DString* p2DEntry = new C2DString;
			int nCol = 0;
			CString strTemp;
			if(pCustPrint->m_bCategory)
			{
				strTemp = ParseXML("Header",strEntry);
				if(strTemp.GetLength() > nMaxTextSize)
				{
					strTemp.GetBufferSetLength(nMaxTextSize);
					strTemp.ReleaseBuffer();
					strTemp += "...";
				}
				p2DEntry->straCol[nCol] = strTemp;
				nCol++;
			}
			if(pCustPrint->m_bDescription)
			{
				strTemp = ParseXML("Description",strEntry);
				if(strTemp.GetLength() > nMaxTextSize)
				{
					strTemp.GetBufferSetLength(nMaxTextSize);
					strTemp.ReleaseBuffer();
					strTemp += "...";
				}
				p2DEntry->straCol[nCol] = strTemp;
				nCol++;
			}
			if(pCustPrint->m_bPrintUserID)
			{
				strTemp = ParseXML("UserID",strEntry);
				if(strTemp.GetLength() > nMaxTextSize)
				{
					strTemp.GetBufferSetLength(nMaxTextSize);
					strTemp.ReleaseBuffer();
					strTemp += "...";
				}
				p2DEntry->straCol[nCol] = strTemp;
				nCol++;
			}
			if(pCustPrint->m_bPrintPass)
			{
				strTemp = ParseXML("Password",strEntry);
				if(strTemp.GetLength() > nMaxTextSize)
				{
					strTemp.GetBufferSetLength(nMaxTextSize);
					strTemp.ReleaseBuffer();
					strTemp += "...";
				}
				p2DEntry->straCol[nCol] = strTemp;
				nCol++;
			}
			if(pCustPrint->m_bPrintURL)
			{
				strTemp = ParseXML("URL",strEntry);
				if(strTemp.GetLength() > nMaxTextSize)
				{
					strTemp.GetBufferSetLength(nMaxTextSize);
					strTemp.ReleaseBuffer();
					strTemp += "...";
				}
				p2DEntry->straCol[nCol] = strTemp;
				nCol++;
			}
			if(pCustPrint->m_bPrintNotes)
			{
				strTemp = ParseXML("Notes",strEntry);
				if(strTemp.GetLength() > nMaxTextSize)
				{
					strTemp.GetBufferSetLength(nMaxTextSize);
					strTemp.ReleaseBuffer();
					strTemp += "...";
				}
				p2DEntry->straCol[nCol] = strTemp;
				nCol++;
			}
			pCustPrint->m_2DstraRows.Add(p2DEntry);
		}
	}
	if(pCustPrint->m_PrintDatabasePassword)
	{
		CString strTitle;
		strTitle.Format("FOX Password Safe - Database: %s  Password: %s"
			,m_strCurrentLoadedPath.Mid(m_strCurrentLoadedPath.ReverseFind('\\')+1), m_strCurrentPassword);
		pCustPrint->SetAppName(strTitle);
	}
	return true;
}

// get all selected entries of item data
BOOL CMainFrame::GetSelectedItemData(LPVOID lpVoid)
{	
	if(m_strCurrentPassword.IsEmpty())
	{
		if(!ShowLoadDataBaseScreen())
		{
			AfxMessageBox("Error you must first enter the database password.");
			return false;
		}
	}
	CCustomPrint* pCustPrint = (CCustomPrint*)lpVoid;

	CStringArray straTemp;
	straTemp.Copy(m_straEntries);
	CSelectPrintItemsDlg dlg;
	dlg.m_pstraItems = &straTemp;
	if(dlg.DoModal() != IDOK)
		return false;
	if(straTemp.GetSize() == 0)
	{
		AfxMessageBox("Please select entries to print.");
		return false;
	}
	for(int n=0;n<straTemp.GetSize();n++)
	{
		CString strEntry = straTemp.GetAt(n);
		CString strDesc = ParseXML("Description",strEntry);
		if(!strDesc.IsEmpty() && ParseXML("CreditCard",strEntry) != "TRUE")
		{
			// create new entry
			C2DString* p2DEntry = new C2DString;
			int nCol = 0;
			if(pCustPrint->m_bCategory)
			{
				p2DEntry->straCol[nCol] = ParseXML("Header",strEntry);
				nCol++;
			}
			if(pCustPrint->m_bDescription)
			{
				p2DEntry->straCol[nCol] = ParseXML("Description",strEntry);
				nCol++;
			}
			if(pCustPrint->m_bPrintUserID)
			{
				p2DEntry->straCol[nCol] = ParseXML("UserID",strEntry);
				nCol++;
			}
			if(pCustPrint->m_bPrintPass)
			{
				p2DEntry->straCol[nCol] = ParseXML("Password",strEntry);
				nCol++;
			}
			if(pCustPrint->m_bPrintURL)
			{
				p2DEntry->straCol[nCol] = ParseXML("URL",strEntry);
				nCol++;
			}
			if(pCustPrint->m_bPrintNotes)
			{
				p2DEntry->straCol[nCol] = ParseXML("Notes",strEntry);
				nCol++;
			}
			pCustPrint->m_2DstraRows.Add(p2DEntry);
		}
	}
	return true;
}

// close app from system tray
void CMainFrame::OnTraymenuExit()
{
	SaveRectPos();
	SaveLastViewSelection();
	CFrameWnd::OnClose();
}

LRESULT CMainFrame::OnSystemTrayMsg(WPARAM wParam,LPARAM lParam)
{
	if(lParam == WM_LBUTTONDBLCLK)
	{
		OnTraymenuShowfoxpasswordsafe();
	}
	else if(lParam == WM_RBUTTONUP)
	{
		CPoint point;
		GetCursorPos(&point);	
		if(m_trayIcon.m_pMenu)
		{
			if(m_trayIcon.m_pMenu->m_hMenu == NULL) 
				m_trayIcon.LoadMenu(IDR_MENU_TRAY);
			if(IsWindowVisible()) // display Hide FOX Password Safe
			{
				CMenu* submenu = m_trayIcon.m_pMenu->m_hMenu?m_trayIcon.m_pMenu->GetSubMenu(0):NULL;
				if(submenu)
					submenu->ModifyMenu(0,MF_BYPOSITION|MF_STRING,ID_TRAYMENU_SHOWFOXPASSWORDSAFE,"Hide FOX Password Safe");
			}
			else // display Show FOX Password Safe
			{
				CMenu* submenu = m_trayIcon.m_pMenu?m_trayIcon.m_pMenu->GetSubMenu(0):NULL;
				if(submenu)
					submenu->ModifyMenu(0,MF_BYPOSITION|MF_STRING,ID_TRAYMENU_SHOWFOXPASSWORDSAFE,"Show FOX Password Safe");
			}
			SetForegroundWindow();
			m_trayIcon.m_pMenu->GetSubMenu(0)->TrackPopupMenu(TPM_CENTERALIGN|TPM_RIGHTBUTTON, point.x, point.y,this);
			PostMessage(WM_NULL, 0, 0);
		} 
	}
 	return 1;
}

// show or hide app to system tray
void CMainFrame::OnTraymenuShowfoxpasswordsafe()
{
	if(!IsWindowVisible()) // show window
	{
		ShowWindow(SW_SHOW);
		if(m_TimerClearPasswords)
		{
			KillTimer(m_TimerClearPasswords);
			m_TimerClearPasswords = NULL;
		}
		if(m_strCurrentPassword.IsEmpty())
		{
			ShowLoadDataBaseScreen();
		}		
	}
	else // hide window
	{
		SaveRectPos();
		SaveLastViewSelection();

		ShowWindow(SW_HIDE);
		// check clear passwords
		CheckClearPasswords();		
	}
}

void CMainFrame::OnClickConnectToURL(UINT nID)
{
	if(m_strCurrentPassword.IsEmpty())
	{
		if(!ShowLoadDataBaseScreen())
		{
			AfxMessageBox("Error you need to enter the database password.");
			return;
		}
	}
	int nPos = nID - ID_BASE_MENU_UID;
	// load URL's menu's
	int nCount = 0;
	for(int n=0;n<m_straEntries.GetSize();n++)
	{			
		CString strData = m_straEntries[n];
		CString strName = ParseXML("Description",strData);
		CString strURL = ParseXML("URL",strData);
		if(!strName.IsEmpty() && !strURL.IsEmpty())
		{
			if(nCount == nPos)
			{
				// make URL current selection
				CLeftView* pTreeView = (CLeftView*)m_wndSplitter.GetPane(0,0);
				if(pTreeView)
				{
					CString strHeader = ParseXML("Header",strData);
					pTreeView->SetCurrentSelection(strHeader,strName);
				}
				CFOXPasswordSafeView* pView = (CFOXPasswordSafeView*)m_wndSplitter.GetPane(0,1);
				if(pView)
				{
					pView->SetMyData(strData,false);
				}

				// show popup if option set
				if(MyGetProfileInt("PopupOnWebMenu",1) == 1)
					OnShowPopup();

				BOOL bLockDown = (ParseXML("LockDownBrowser",strData) == "TRUE");
				if(bLockDown)
					LockDownBrowser();
				// check hide after loading url
				CheckHideAfterLoadingURL();
				// load URL in default web browser
				LoadURLInBrowser(strURL);
				return;
			}
			nCount ++;
		}		
	}
}

// close or minimize app depending on user settings
void CMainFrame::OnClose()
{
	SaveRectPos();
	SaveLastViewSelection();

	if(MyGetProfileInt("AskCloseOrHide",1) == 1)
	{
		CAskCloseOrHideDlg dlg;
		dlg.DoModal();
	}

	BOOL bEmptyClip = (MyGetProfileInt("ClearClipOnClose",1) == 1);
	BOOL bClose = (MyGetProfileInt("MinimizeOnClose",0) == 0);
	if(bClose)
	{
		if(bEmptyClip)
			OnBnClickedClearClip();		
		CFrameWnd::OnClose();
	}
	else
	{
		ShowWindow(SW_HIDE);	
		CheckClearPasswords();
	}
}

void CMainFrame::OnEditLockdownwebbrowser()
{
	LockDownBrowser(false/*auto unlock browser*/);
	
	if(MyGetProfileInt("DontShowLockDownWarning",0) == 0)
	{
		CWarningDlg dlg;
		dlg.m_strText = "You will need to close any open copies of Internet Explorer\r\n and launch a new copy to ensure you are protected.";
		dlg.m_strRegistryTag = "DontShowLockDownWarning";
		dlg.DoModal();
	}
}

void CMainFrame::OnEditRestorebrowsertodefault()
{
	RestoreBrowserSecurity();	
}

// show popup window with current username and pasword 
void CMainFrame::OnShowPopup()
{	
	CFOXPasswordSafeView* pView = (CFOXPasswordSafeView*)m_wndSplitter.GetPane(0,1);
	if(pView)
	{
		CString strData;
		if(pView->GetSelectedUserData(strData))
		{
			// credit card dialog
			if(ParseXML("CreditCard",strData) != "TRUE")
			{
				if(!m_pPopupDlg)
				{
					m_pPopupDlg = new CPassPopupDlg();
					m_pPopupDlg->Create(IDD_PASSWORD_POPUP,GetDesktopWindow());
					m_pPopupDlg->SetLastRectPos();
				}
				m_pPopupDlg->SetDescription(ParseXML("Description",strData));
				m_pPopupDlg->SetUserID(ParseXML("UserID",strData));
				m_pPopupDlg->SetPassword(ParseXML("Password",strData));		
				m_pPopupDlg->SetURL(ParseXML("URL",strData));
				m_pPopupDlg->ShowWindow(SW_SHOW);
			}
		}
		else
		{
			AfxMessageBox("Please select the entry you want from the left window pane.");
		}
	}
}

// save position of main window
void CMainFrame::SaveRectPos(void)
{
	if(IsWindow(m_hWnd))
	{
		CRect rect;
		GetWindowRect(rect);
		MyWriteProfileInt("MainWndX1",rect.left);
		MyWriteProfileInt("MainWndY1",rect.top);
		MyWriteProfileInt("MainWndX2",rect.right);
		MyWriteProfileInt("MainWndY2",rect.bottom);
	}
}

// restore last saved position 
void CMainFrame::SetLastRectPos(void)
{
	int nX2 = MyGetProfileInt("MainWndX2",0);
	if(nX2 > 0 && IsWindow(m_hWnd))
	{
		CRect rect = CRect(MyGetProfileInt("MainWndX1",0),MyGetProfileInt("MainWndY1",0),nX2,MyGetProfileInt("MainWndY2",0));
		CRect rectDesk;
		GetDesktopWindow()->GetClientRect(rectDesk);
		if(rect.left >= 0 && rect.top >= 0 && rect.Width() <= rectDesk.Width() && rect.Height() <= rectDesk.Height())
			MoveWindow(rect);
	}
}

// Save last selected tree position
void CMainFrame::SaveLastViewSelection()
{
	if(!IsWindow(m_hWnd))
		return;
	CLeftView* pTreeView = (CLeftView*)m_wndSplitter.GetPane(0,0);
	if(pTreeView)
	{
		long lArrayPos = pTreeView->GetSelectedArrayPos();
		if(lArrayPos >= 0 && lArrayPos < m_straEntries.GetSize())
		{
			CString strEntry = m_straEntries.GetAt(lArrayPos);
			CString strHeader = ParseXML("Header",strEntry);
			CString strDescription = ParseXML("Description",strEntry);
			MyWriteProfileString("LastHeader",strHeader);
			MyWriteProfileString("LastDescription",strDescription);		
		}
		else
		{
			MyWriteProfileString("LastHeader","");
			MyWriteProfileString("LastDescription","");		
		}
	}
}

// restore last selected tree position
void CMainFrame::SetLastViewSelection()
{
	if(!IsWindow(m_hWnd))
		return;
	CLeftView* pTreeView = (CLeftView*)m_wndSplitter.GetPane(0,0);
	if(pTreeView)
	{
		CString strHeader = MyGetProfileString("LastHeader","");
		CString strDescription = MyGetProfileString("LastDescription","");
		if(!strHeader.IsEmpty() || !strDescription.IsEmpty())
			pTreeView->SetCurrentSelection(strHeader,strDescription);
	}
}

// load selected url in web browser
void CMainFrame::OnBnClickedLoadUrl()
{
	CFOXPasswordSafeView* pView = (CFOXPasswordSafeView*)m_wndSplitter.GetPane(0,1);
	if(pView)
	{
		CString strURL;
		BOOL bLockDown = true;
		if(pView->GetSelectedURL(strURL,bLockDown))
		{
			if(strURL.IsEmpty())
			{
				AfxMessageBox("Error there is no web site to load for the selected entry.");
			}
			else
			{				
				// show popup if option set
				if(MyGetProfileInt("PopupOnWebMenu",1) == 1)
					OnShowPopup();
				// lock down browser
				if(bLockDown)
					LockDownBrowser();
				// check hide after loading url
				CheckHideAfterLoadingURL();

				LoadURLInBrowser(strURL);
			}
		}
		else
		{
			AfxMessageBox("Please load and select an entry to load in your web browser.");
		}
	}
}

void CMainFrame::OnTimer(UINT nIDEvent)
{
	CFrameWnd::OnTimer(nIDEvent);	

	// clear password
	if(nIDEvent == ID_CLEAR_PASSWORD)
	{
		KillTimer(m_TimerClearPasswords);
		m_TimerClearPasswords = NULL;
		
		ClearPasswordsFromMemory();
	}
	else if(nIDEvent == ID_CHECK_SCREEN_SAVER_ACTIVE)
	{
		if(m_bHasNotClearedForScreenSaver && IsScreenSaverActive())
		{
			m_bHasNotClearedForScreenSaver = false;
			ClearPasswordsFromMemory();
			AfxMessageBox("Cleared memory from screen saver");
		}
	}
}

// lock down security settings in browser
void CMainFrame::LockDownBrowser(BOOL bAutoUnlock)
{
	if(!m_pLockDown)
	{
		m_pLockDown = new CMyLockDown();
		BOOL bOK = m_pLockDown->Create(NULL,"Timer",NULL,CRect(0,0,0,0),this,1);
		if(!bOK)
			AfxMessageBox("Error creating lock down session. Window creation failed...");
	}
	m_pLockDown->StartLockDown(bAutoUnlock);	
}

// restore the default browser security settings
void CMainFrame::RestoreBrowserSecurity(void)
{
	if(!m_pLockDown)
	{
		m_pLockDown = new CMyLockDown();
		if(IsWindow(m_hWnd))
		{
			BOOL bOK = m_pLockDown->Create(NULL,"Timer",NULL,CRect(0,0,0,0),this,1);
			if(!bOK)
				AfxMessageBox("Error creating lock down session. Window creation failed...");
		}
	}
	m_pLockDown->EndLockdown();
}

// check if need to clear passwords from memory
void CMainFrame::CheckClearPasswords(void)
{
	// clear passwords on minimize to system tray
	int nClearPassOnMinimize = MyGetProfileInt("ClearPassOnMinimize",2);
	switch(nClearPassOnMinimize)
	{
	case 0: // do not clear password
		break;
	case 1: // clear password
		ClearPasswordsFromMemory();
		break;
	case 2: // clear password after certain time
		int nMins = MyGetProfileInt("ClearPassOnMinimizeTimeMins",15);
		m_TimerClearPasswords = (UINT)SetTimer(ID_CLEAR_PASSWORD,nMins*1000*60,NULL);
		break;
	}
}

// check if screen saver active or workstation locked
BOOL CMainFrame::IsScreenSaverActive(void)
{
	if(IsWindowsNT4())
	{
		HDESK hDesktop;
		hDesktop = OpenDesktop(TEXT("screen-saver"),0,FALSE,MAXIMUM_ALLOWED);
		if(hDesktop == NULL)
		{
			if(GetLastError() == ERROR_ACCESS_DENIED)
			{
				return TRUE;
			}
			return FALSE;
		}
		// Successfully opened the desktop (the screen saver is running).
		CloseDesktop(hDesktop);
		return TRUE;
	}
	else
	{
		BOOL bActive = false;
		SystemParametersInfo(SPI_GETSCREENSAVERRUNNING, NULL,(LPVOID) &bActive, NULL);
		return bActive;

	/*	HDESK hDesk = OpenDesktop("default",NULL,false,DESKTOP_SWITCHDESKTOP);
		BOOL bDeskLocked = !SwitchDesktop(hDesk);
		CloseDesktop(hDesk);
		return bDeskLocked;   */

	}
}

// clear passwords and information for lock down state
void CMainFrame::ClearPasswordsFromMemory(void)
{
	OnBnClickedClearClip();
	m_strCurrentPassword = "";
	CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
	if(pView)
		pView->ClearList();
	CFOXPasswordSafeView* pView2 = (CFOXPasswordSafeView*)m_wndSplitter.GetPane(0,1);
	if(pView2)
		pView2->SetMyData("",false);
	m_wndStatusBar.SetPaneText(0,"  Please re-enter the database password...");
}

// show options dialog
void CMainFrame::OnToolsOptions()
{
	COptionsDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		// start timer check for screen saver active
		/*BOOL bClearOnScreenSaver = (MyGetProfileInt("ClearPassOnScreensaver",1) == 1);
		if(bClearOnScreenSaver && m_TimerCheckScreenSaver == NULL)
		{
			m_TimerCheckScreenSaver = (UINT)SetTimer(ID_CHECK_SCREEN_SAVER_ACTIVE,SCREEN_SAVER_CHECK_TIME,NULL);
		}
		else if(m_TimerCheckScreenSaver != NULL)
		{
			KillTimer(m_TimerCheckScreenSaver);
			m_TimerCheckScreenSaver = NULL;
		}*/
	}
}

// hide window after loading URL option
void CMainFrame::CheckHideAfterLoadingURL()
{
	// auto hide app when loading web site
	if(MyGetProfileInt("AutoHideAppWhenLoadURL",0) == 0)
		return;

	SaveRectPos();
	SaveLastViewSelection();

	ShowWindow(SW_HIDE);
	// check clear passwords
	CheckClearPasswords();	
}

// show nag dialog once per day if not registered
void CMainFrame::ShowNagScreen(void)
{
	if(IsRegistered())
		return;
	CTime tm = CTime::GetCurrentTime();
	CString strRegTime = MyGetProfileString("LastNagTime","");
	if(strRegTime.IsEmpty())
	{
		strRegTime.Format("%I64u",tm.GetTime());
		MyWriteProfileString("LastNagTime",strRegTime);
		return;
	}
	CTime tmReg = CTime(_atoi64(strRegTime));
	CTimeSpan span = tm - tmReg;
	if(span.GetTotalHours() > 23)
	{
		CNagDlg dlg;
		dlg.DoModal();
	}
	m_bHasFreeTrialExpired = (GetFreeTrialDaysUsed() > 30);
}

LRESULT CMainFrame::OnCheckAskPassword(WPARAM, LPARAM)
{
	if(m_strCurrentPassword.IsEmpty())
	{
		ShowLoadDataBaseScreen();
	}	
	return 0L;
}

LRESULT CMainFrame::OnLoadUrl(WPARAM, LPARAM)
{
	OnBnClickedLoadUrl();
	return 0L;
}

void CMainFrame::OnHelpRegisterfoxpasswordsafe()
{
	LoadURLInBrowser(GetRegisterURL());
}

void CMainFrame::OnHelpEnterregistrationcode()
{
	CString strReg = MyGetProfileString("Reg","");
	CEnterRegCode dlg;
	dlg.m_strRegCode = strReg;
	dlg.DoModal();
}

void CMainFrame::OnShowSearchPage()
{	
	REBARBANDINFO info;
	ZeroMemory(&info,sizeof(REBARBANDINFO));
	info.cbSize = sizeof(REBARBANDINFO);
	info.fMask = RBBIM_STYLE;
	// hide search
	if(m_bSearchVisible)
	{
		info.fStyle = RBBS_HIDDEN|RBBS_BREAK|RBBS_GRIPPERALWAYS|RBBS_FIXEDBMP;
	}
	else // show search
	{
		info.fStyle = RBBS_BREAK|RBBS_GRIPPERALWAYS|RBBS_FIXEDBMP;
	}
	m_wndReBar.GetReBarCtrl().SetBandInfo(1,&info);
	m_bSearchVisible = !m_bSearchVisible;
	if(m_bSearchVisible)
		m_SearchBarWnd.SetEditFocus();
}

void CMainFrame::OnButtonShowAll()
{
	CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
	if(ParseXML("Version",strData).IsEmpty())
	{
		AfxMessageBox("Error, incorrect password. Please load a password database and search again.",MB_OK);
	}
	else
	{	
		CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
		if(pView)
			pView->ClearList();
		CFOXPasswordSafeView* pView2 = (CFOXPasswordSafeView*)m_wndSplitter.GetPane(0,1);
		if(pView2)
			pView2->SetMyData("",false);
		LoadTreeData(strData);
		m_wndStatusBar.SetPaneText(0,"  Showing all entries...");
	}
}

void CMainFrame::OnButtonSearch()
{
	CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
	if(ParseXML("Version",strData).IsEmpty())
	{
		AfxMessageBox("Error, incorrect password. Please load a password database and search again.",MB_OK);
	}
	else
	{	
		CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
		if(pView)
			pView->ClearList();
		CFOXPasswordSafeView* pView2 = (CFOXPasswordSafeView*)m_wndSplitter.GetPane(0,1);
		if(pView2)
			pView2->SetMyData("",false);
		strData = FilterData(strData);
		LoadTreeData(strData,false /*can save*/);
		m_wndStatusBar.SetPaneText(0,"  Search results...");
	}
}
CString CMainFrame::FilterData(CString strData)
{
	CString strText = m_SearchBarWnd.GetSearchText();
	if(strText.IsEmpty())
		return strData;

	strText.MakeLower();
	CStringArray straExtras;
	int nFind = -1;
	while((nFind = strData.Find("</Entry>")) != -1)
	{
		CString strEntry = ParseXML("Entry",strData);
		strData = strData.Mid(nFind + (int)strlen("</Entry>"));
		CString strTest = strEntry;
		strTest.MakeLower();
		if(strTest.Find(strText) != -1)
		{
			straExtras.Add(strEntry);
		}
	}
	CString strNew;
	for(int n=0;n<straExtras.GetCount();n++)
	{
		strNew += "<Entry>" + straExtras.GetAt(n) + "</Entry>";
	}
	return strNew;
}

// move an item to a new header
void CMainFrame::MoveTreeItem(long lArrayPosSource,long lArrayPosTarget)
{
	// check password is OK
	if(m_strCurrentPassword.IsEmpty())
	{
		if(!ShowLoadDataBaseScreen())
		{
			AfxMessageBox("Error you must first enter the database password.");
			return;
		}
	}
	if(lArrayPosSource < 0 || lArrayPosSource >= m_straEntries.GetSize())
		return;
	if(lArrayPosTarget < 0 || lArrayPosTarget >= m_straEntries.GetSize())
		return;
	CString strDataTarget = m_straEntries.GetAt(lArrayPosTarget);
	CString strNewHeader = ParseXML("Header",strDataTarget);
	if(strNewHeader.IsEmpty())
		return;
	// replace old header with new header
	CString strOldEntry = m_straEntries.GetAt(lArrayPosSource);
	CString strNewEntry = ReplaceXML(strNewHeader,"Header",strOldEntry);

	CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
	BOOL bRemove = false;
	CStringArray* pStra = LoadEntries(strData,bRemove);
	m_straEntries.RemoveAll();
	for(int n=0;n<pStra->GetCount();n++)
	{
		if(pStra->GetAt(n) != strOldEntry)
			m_straEntries.Add(pStra->GetAt(n));
		else
			m_straEntries.Add(strNewEntry);
	}
	delete pStra;

	if(!SaveAllEntries(&m_straEntries,true))
	{
		AfxMessageBox("Error saving change to database.");
	}	
	else
	{
		CString strName = ParseXML("Description",strNewEntry);
		CLeftView* pTreeView = (CLeftView*)m_wndSplitter.GetPane(0,0);
		if(pTreeView)
		{
			CString strHeader = ParseXML("Header",strNewEntry);
			pTreeView->SetCurrentSelection(strHeader,strName);
		}
	}
}

// show selected body for this entry
void CMainFrame::ShowSelectedEntry(long lArrayPos)
{
	if(lArrayPos >= m_straEntries.GetSize())
		return;
	CString strData = m_straEntries.GetAt(lArrayPos);
	CFOXPasswordSafeView* pView = (CFOXPasswordSafeView*)m_wndSplitter.GetPane(0,1);
	ASSERT(pView);
	if(pView)
	{
		pView->SetMyData(strData,false);
	}
}

// load url web page or associated file application
void CMainFrame::LoadFileAssociation(BOOL bShowMsg)
{
	CFOXPasswordSafeView* pView = (CFOXPasswordSafeView*)m_wndSplitter.GetPane(0,1);
	BOOL bIsURL = false;
	if(pView)
	{
		CWaitCursor wait;
		CString strXML;
		if(pView->GetSelectedUserData(strXML))
		{
			// encrypted file
			if(ParseXML("EncryptedFile",strXML) == "TRUE")
			{
				if(UnEncryptFile(strXML))
				{
					CLeftView* pLeftView = (CLeftView*)m_wndSplitter.GetPane(0,0);
					pLeftView->SetItemImageEncrypted(false);
					LoadFileObject(strXML);
				}
				return;
			}
		}
		// check if url link
		CString strURL;
		BOOL bLockDown = true;
		if(pView->GetSelectedURL(strURL,bLockDown))
		{
			if(!strURL.IsEmpty())
				bIsURL = true;
		}
	}
	if(bIsURL || bShowMsg)
		OnBnClickedLoadUrl();
}


// delete the selected entry
void CMainFrame::OnEditDeleteselectedentry()
{
	CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
	if(!pView)
		return;
	long lArrayPos = pView->GetSelectedArrayPos();
	if(lArrayPos < 0 || lArrayPos >= m_straEntries.GetSize())
	{
		AfxMessageBox("Please select an entry on the left window pane to delete.");
		return;
	}
	CString strOldEntry = m_straEntries.GetAt(lArrayPos);
	if(AfxMessageBox("Are you sure you want to delete the selected entry?",MB_YESNO) != IDYES)
		return;

	// encrypted file
	if(ParseXML("EncryptedFile",strOldEntry) == "TRUE")
	{
		if(AfxMessageBox("Would you like to unencrypt the file before you delete it forever?",MB_YESNO) == IDYES)
		{
			if(!UnEncryptFile(strOldEntry))
			{
				AfxMessageBox("Error unencrypting file. It has not been removed.");
				return;
			}
		}
		CString strEncPath = ParseXML("EncFilePath",strOldEntry);
		DeleteFile(strEncPath);
	}
	// remove entry
	BOOL bHasRemovedExtras = false;
	CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
	CStringArray* pStra = LoadEntries(strData,bHasRemovedExtras);
	m_straEntries.RemoveAll();
	for(int n=0;n<pStra->GetCount();n++)
	{
		if(pStra->GetAt(n) != strOldEntry)
			m_straEntries.Add(pStra->GetAt(n));
	}
	delete pStra;
	pStra = NULL;
	// check if there is another entry for this header
	CString strHeader = ParseXML("Header",strOldEntry);
	if(!strHeader.IsEmpty())
	{
		BOOL bFound = false;
		for(int n=0;n<m_straEntries.GetCount();n++)
		{
			if(ParseXML("Header",m_straEntries.GetAt(n)).CompareNoCase(strHeader) == 0)
			{
				bFound = true;
				break;
			}
		}
		// add just header entry
		if(!bFound)
			m_straEntries.Add("<Header>" + strHeader + "</Header>");	
	}
	if(!SaveAllEntries(&m_straEntries,true))
	{
		AfxMessageBox("Error saving deleting entry from database.");
		return;
	}
	m_wndStatusBar.SetPaneText(0,"  Entry has been deleted...");
}

void CMainFrame::OnDropFiles(HDROP hDropInfo)
{
	CString strFilePath;
	DragQueryFile(hDropInfo,0,strFilePath.GetBuffer(MAX_PATH),MAX_PATH);
	strFilePath.ReleaseBuffer();

	if(m_strCurrentPassword.IsEmpty())
	{
		if(!ShowLoadDataBaseScreen())
		{
			AfxMessageBox("Error you must first enter the database password.");
			return;
		}
	}

	if(FileExists(strFilePath))
	{
		// get selected header if any
		CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
		long lPos = pView->GetSelectedArrayPos();
		CNewEncryptedFileDlg dlg;
		dlg.m_pstraEntries = &m_straEntries;
		if(lPos >=0 && lPos < m_straEntries.GetSize())
			dlg.m_strSelectHeader = ParseXML("Header",m_straEntries.GetAt(lPos));
		dlg.m_strFilePath = strFilePath;
		if(dlg.DoModal() == IDOK)
		{
			CString strNewEntry = dlg.GetNewData();
			CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
			strData += strNewEntry;

			if(strData.Find("<Entry><Entry>") != -1)
			{
				strData.Replace("<Entry><Entry>","<Entry>");
				strData.Replace("</Entry></Entry>","</Entry>");
			}

			if(!WriteEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword,strData))
			{
				AfxMessageBox("Error saving new entry to database.");
				return;
			}
			// encrypt this file
			EncryptFile(strNewEntry);

			SaveLastViewSelection();
			LoadTreeData(strData);
		}
	}
}

// encrypt current selected file
void CMainFrame::OnEditEncryptfileentry()
{
	CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
	if(!pView)
		return;
	long lArrayPos = pView->GetSelectedArrayPos();
	if(lArrayPos < 0 || lArrayPos >= m_straEntries.GetSize())
	{
		AfxMessageBox("Please select an entry on the left window pane to encrypt.");
		return;
	}
	CString strOldEntry = m_straEntries.GetAt(lArrayPos);
	// encrypted file
	if(ParseXML("EncryptedFile",strOldEntry) == "TRUE")
	{
		if(!EncryptFile(strOldEntry))
		{
			pView->SetItemImageEncrypted(false);
			AfxMessageBox("Error encrypting file.");
		}
		else
		{
			pView->SetItemImageEncrypted(true);
		}
	}
	else
		AfxMessageBox("Error selected entry is not an encrypted file.");
}

// Unencrypt current selected file
void CMainFrame::OnEditUnencryptfileentry()
{
	CLeftView* pView = (CLeftView*)m_wndSplitter.GetPane(0,0);
	if(!pView)
		return;
	long lArrayPos = pView->GetSelectedArrayPos();
	if(lArrayPos < 0 || lArrayPos >= m_straEntries.GetSize())
	{
		AfxMessageBox("Please select an entry on the left window pane to unencrypt.");
		return;
	}
	CString strOldEntry = m_straEntries.GetAt(lArrayPos);
	// encrypted file
	if(ParseXML("EncryptedFile",strOldEntry) == "TRUE")
	{
		if(!UnEncryptFile(strOldEntry))
		{
			pView->SetItemImageEncrypted(true);
			AfxMessageBox("Error unencrypting file.");
		}
		else
		{
			pView->SetItemImageEncrypted(false);
		}
	}
	else
		AfxMessageBox("Error selected entry is not an encrypted file.");
}

// get string entry
CString CMainFrame::GetStringEntry(int nPos)
{
	if(nPos < 0 || nPos >= m_straEntries.GetSize())
		return "";
	else
		return m_straEntries.GetAt(nPos);
}

void CMainFrame::OnToolsLoadselectedencryptedfile()
{
	LoadFileAssociation(true);
}

// load associated app
void CMainFrame::LoadFileObject(CString strXML)
{
	CString strPath = ParseXML("FilePath",strXML);

	SHELLEXECUTEINFO info;
	ZeroMemory(&info,sizeof(SHELLEXECUTEINFO));
	info.cbSize = sizeof(SHELLEXECUTEINFO);
	info.fMask = 0;
	info.lpVerb = "open";
    info.lpFile = strPath;
	info.nShow = SW_SHOWNORMAL;
	::ShellExecuteEx(&info);
}

// encrypt any unencrypted files
void CMainFrame::OnTraymenuEncryptanyunencryptedfiles()
{
	CWaitCursor wait;
	CString strEntry;
	for(int n=0;n<m_straEntries.GetCount();n++)
	{
		strEntry = m_straEntries.GetAt(n);
		// encrypted file
		if(IsEncryptedFileEntry(strEntry) && !IsFileEncrypted(strEntry))
		{
			if(!EncryptFile(strEntry))
			{
				AfxMessageBox("Error encrypting file. Path:- " + ParseXML("FilePath",strEntry));
			}
		}
	}
	// reload tree 
	CString strData = ReadEncryptedFile(m_strCurrentLoadedPath,m_strCurrentPassword);
	LoadTreeData(strData);
}

// unencrypt backed up file
void CMainFrame::OnToolsUnencryptbackedupfile()
{
	CUnencryptDlg dlg;
	dlg.DoModal();
}

// show toolbar for particular view
void CMainFrame::ShowToolBar(TOOLBAR_TYPES eToolbar)
{
	m_wndMyToolbar.ShowToolBar(eToolbar);
}

// load selected file
void CMainFrame::OnBnClickedLoadFile()
{
	CFOXPasswordSafeView* pView = (CFOXPasswordSafeView*)m_wndSplitter.GetPane(0,1);
	BOOL bIsURL = false;
	if(pView)
	{
		CWaitCursor wait;
		CString strXML;
		if(pView->GetSelectedUserData(strXML))
		{
			// encrypted file
			if(ParseXML("EncryptedFile",strXML) == "TRUE")
			{
				if(UnEncryptFile(strXML))
				{
					CLeftView* pLeftView = (CLeftView*)m_wndSplitter.GetPane(0,0);
					pLeftView->SetItemImageEncrypted(false);
					LoadFileObject(strXML);
				}
			}
		}
	}
}

// check if encryted file paths already exist
BOOL CMainFrame::EncryptFileAlreadyExists(CString strData)
{
	CString strEntry;
	CString strEncPath = ParseXML(_T("EncFilePath"),strData);
	CString strFilePath = ParseXML(_T("FilePath"),strData);
	for(int n=0;n<m_straEntries.GetCount();n++)
	{
		strEntry = m_straEntries.GetAt(n);
		if(ParseXML(_T("EncryptedFile"),strEntry) == "TRUE")
		{
			if(ParseXML(_T("EncFilePath"),strEntry).CompareNoCase(strEncPath) == 0)
				return true;
			if(ParseXML(_T("FilePath"),strEntry).CompareNoCase(strFilePath) == 0)
				return true;
		}
	}
	return false;
}

void CMainFrame::OnToolsExportdatatocsvfile()
{
	if(m_straEntries.GetCount() == 0)
	{
		AfxMessageBox("Error no file is open... ");
		return;
	}
	CFileDialog dlgFile(FALSE);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	dlgFile.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	dlgFile.GetOFN().nMaxFile = c_cMaxFiles;
	dlgFile.DoModal();
	fileName.ReleaseBuffer();
	if(fileName.IsEmpty())
		return;

	CString strCSV;
	CString strParams;
	for(int n=0;n<m_straEntries.GetCount();n++)
	{
		strParams = m_straEntries.GetAt(n);
 
		// look for username password only
		if(ParseXML("CreditCard",strParams) != "TRUE" && ParseXML("EncryptedFile",strParams) != "TRUE")
		{
			// userID
			CString strUsername = ParseXML("UserID",strParams);
			// password
			CString strPass = ParseXML("Password",strParams);
			// previous password
			CString strPassPrev = ParseXML("PasswordOld",strParams);
			// set url 	
			CString strURL = ParseXML("URL",strParams);
			// notes 	
			CString strNotes = ParseXML("Notes",strParams);
			// Description 	
			CString strDescription = ParseXML("Description",strParams);
			// category 	
			CString strCategory = ParseXML("Header",strParams);
			// format
			// title,category,username,password,previouspasswords,url,tags,notes
			CString strExport;
			strExport.Format("\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"\",\"%s\"",
				strDescription,strCategory,strUsername,strPass,strPassPrev,strURL,strNotes);
			strExport.Replace("\r\n","\t");
			strExport.Replace("\n","\t");
			strCSV += strExport + "\r\n";
		}
	}
	CFile fp;
	if(fp.Open(fileName,CFile::modeCreate|CFile::modeWrite))
	{
		DWORD dwSize = strCSV.GetLength();
		fp.Write(strCSV.GetBuffer(dwSize),dwSize);
		strCSV.ReleaseBuffer();
		fp.Close();
		AfxMessageBox("Export complete.");
		return;
	}
	AfxMessageBox("Error opening export file.");	
}
