// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "MyIEWnd.h"
#include "MyMediaPlayer.h"
#include "sockets\PingJobManager.h"
#include "sockets\job.h"
#include "sockets\jobManager.h"
#include "blowfish\blowfish.h"

#include "MainFrm.h"
#include "helpers.h"
#include "TimedShutdownDlg.h"
#include "SettingsDlg.h"
#include "VolumeControl.h"
#include "SelectSkinDlg.h"
#include "ManagePlayListDlg.h"
#include "PlayListManager.h"
#include "FileAssociationDlg.h"

static HINSTANCE glhinstDLL; 
static HHOOK ghhookKeyMsg; 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_FILE_SHOWPLAYLIST, OnFileShowplaylist)
	ON_COMMAND(ID_FILE_HIDEPLAYLIST, OnFileHideplaylist)
	ON_COMMAND(ID_FILE_SELECTSKIN, OnFileSelectskin)
	ON_COMMAND(ID_FILE_ACTIVATETIMEDSHUTDOWN, OnFileActivatetimedshutdown)
	ON_UPDATE_COMMAND_UI(ID_FILE_ACTIVATETIMEDSHUTDOWN, OnUpdateFileActivatetimedshutdown)
	ON_WM_TIMER()
	ON_WM_COPYDATA()
	ON_COMMAND(ID_FILE_PLAY, OnFilePlay)
	ON_COMMAND(ID_FILE_PAUSE, OnFilePause)
	ON_COMMAND(ID_FILE_STOP, OnFileStop)
	ON_COMMAND(ID_FILE_SETTINGS, OnFileSettings)
	ON_COMMAND(ID_FILE_SELECTPLAYLIST, OnFileSelectplaylist)
	ON_COMMAND(ID_FILE_PREVIOUS, OnFilePrevious)
	ON_COMMAND(ID_FILE_NEXT, OnFileNext)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SEC_TRAYICON_NOTIFY,OnTrayIcon)
	ON_MESSAGE(WM_PRE_LOAD_PLAYLIST,OnPreLoadPlayList)
	ON_MESSAGE(WM_PRE_LOAD_PLAYER,OnPreLoadPlayer)
	ON_MESSAGE(WM_ONQUIT_PRE_LOAD_PLAYER,OnQuitPreLoadPlayer)
	ON_MESSAGE(WM_KEYBOARD_HOOK_MSG,OnKeyboardHookMsg)
	ON_MESSAGE(WM_END_OF_VIDEO,EndOfVideo)
	ON_MESSAGE(WM_SHOW_HIDE_PLAYLIST,ShowHidePlayList)
	ON_MESSAGE(WM_VIDEO_PLAYER_READY,OnVideoPlayerReady)
	ON_MESSAGE(WM_SET_CURRENT_POS,OnSetCurrentPos)
	ON_MESSAGE(WM_DELETE_JOB,OnDeleteJob)
	ON_MESSAGE(WM_FINISHED_JOB,OnFinishedJob)
	ON_MESSAGE(WM_RETRYLATER_JOB,OnRetryJobLater)
	ON_MESSAGE(WM_DELETE_PLAYER,OnDeletePlayer)
	ON_MESSAGE(WM_DELETE_PLAYLIST,OnDeletePlayList)
	ON_MESSAGE(WM_DELETE_AD_PAGE,OnDeleteAdPage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_pIEAds = NULL;
	m_pIESkin = NULL;
	m_pIEPlayer = NULL;
	m_bTimedShutdownActive = false;
	m_bShutoffAfterPlayList = false;
	m_TimerShutDown = 0;

	m_pMyMediaPlayer = NULL;
	m_bAutoLoadPlayList = true;
	m_TimerLowerVolume = NULL;
	m_dwLowerVolVal = 0;
	m_pPingJobManager = NULL;
	m_pJobManager = NULL;
	m_bIsUnzipping = false;
	m_bPaused = false;
	m_bPopUpPlayList = false;
}

CMainFrame::~CMainFrame()
{
	StopKeyBoardHook();

	EnableAutoDial();

	if(m_pPingJobManager)
	{
		m_pPingJobManager->StopAllJobs();
		delete m_pPingJobManager;
		m_pPingJobManager = NULL;
	}
	if(m_pJobManager)
	{
		m_pJobManager->StopAllJobs();
		delete m_pJobManager;
		m_pJobManager = NULL;
	}
	if(m_pMyMediaPlayer)
	{
		CString strCurrentPlayInfo = m_pMyMediaPlayer->GetCurrentPlayingInfo();
		CPlayListManager list;
		list.SaveCurrent(&m_pMyMediaPlayer->m_straPlayList,strCurrentPlayInfo);
	}
	if(m_pIEAds)
	{
		delete m_pIEAds;
		m_pIEAds = NULL;
	}
	if(m_pIESkin)
	{
		delete m_pIESkin;
		m_pIESkin = NULL;
	}
	if(m_pIEPlayer)
	{
		delete m_pIEPlayer;
		m_pIEPlayer = NULL;
	}
	if(m_pMyMediaPlayer)
	{
		delete m_pMyMediaPlayer;
		m_pMyMediaPlayer = NULL;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if(!HasBeenInstalled())
	{
		m_bPopUpPlayList = true;
		SetInstallParams();
	}

	// tray icon
	m_trayIcon.Create(this);
	m_trayIcon.SetIcon(IDR_MAINFRAME);
	m_trayIcon.Show(TRUE);
	m_trayIcon.SetTip(_T("Fox Media Center"));

	// media player
	m_pMyMediaPlayer = new CMyMediaPlayer();
	m_pMyMediaPlayer->m_pMainWnd = this;

	BOOL bOK = m_pMyMediaPlayer->Create(NULL,"Media Center",WS_CHILD,CRect(0,0,0,0),this,ID_MEDIA_CENTER_WND);
	if(!bOK)
	{
		AfxMessageBox("Error creating media control");
		return 1;
	}

	UINT dwVol = AfxGetApp()->GetProfileInt("Settings","LastVolume",0);
	if(dwVol != 0)
	{
		CVolumeControl volCtl;
		BOOL bOK = FALSE;
		bOK = volCtl.Open(GetSafeHwnd());
		if(bOK)
		{
			volCtl.SetVolume(dwVol);
			volCtl.Close();
		}
		AfxGetApp()->WriteProfileInt("Settings","LastVolume",0);
	}

	StartKeyBoardHook();

	BOOL bShowPlayListOnStart = m_bPopUpPlayList || (AfxGetApp()->GetProfileInt("Settings","ShowPlaylist",0) == 1);
	BOOL bPreLoadPlayList = (AfxGetApp()->GetProfileInt("Settings","PreLoadPlayList",1) == 1);
	if(bPreLoadPlayList || bShowPlayListOnStart)
	{
		m_timerLoadSkin = SetTimer(ID_LOAD_WEB_PAGES,1000,NULL);
	}

	if(m_bAutoLoadPlayList)
	{
		CPlayListManager list;
		BOOL bStartPlayLastSong = (AfxGetApp()->GetProfileInt("Settings","AutoPlay",1) == 1);
		if(list.LoadCurrent(true,bStartPlayLastSong,true) == -1 && bStartPlayLastSong)
			OnFilePlay();
	}

	AutoDetectProxy();

	// stop modem autodial
	DisableAutoDial();
	m_pJobManager = new CJobManager();
	m_pPingJobManager = new CPingJobManager();

	m_pJobManager->ContinueAnyCurrentJobs();
	m_pPingJobManager->ContinueAnyCurrentJobs(TRUE);

	// timer to check for file updates
	m_TimerCheckUpdates = SetTimer(ID_CHECK_UPDATES,10*1000,NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	LPCSTR szClass = APP_EXE_CLASSNAME;
	WNDCLASS wndcls;
	// register a new class
	HINSTANCE hInst = AfxGetInstanceHandle();
	wndcls.style = 0;
	wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
	wndcls.hInstance = hInst;
	wndcls.hIcon = NULL;
	wndcls.hCursor = NULL;
	wndcls.hbrBackground = NULL;
	wndcls.lpszMenuName = NULL;
	wndcls.lpszClassName = szClass;
	BOOL bOK = AfxRegisterClass(&wndcls);

	cs.lpszClass = szClass;
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

long CMainFrame::OnTrayIcon(UINT wParam, LONG lParam)
{
	switch(lParam) 
	{
		case WM_RBUTTONUP:
	        m_trayIcon.ShowContextMenu(this, IDR_TRAY_MENU);
			break;
		case WM_LBUTTONDBLCLK:
			DWORD dwMsg = MAKEWPARAM(ID_FILE_SHOWPLAYLIST,0);
			PostMessage(WM_COMMAND,dwMsg,0);			
			break;
	}
    return 0L;
}

void CMainFrame::OnFileExit() 
{
	CFrameWnd::OnClose();	
}

BOOL CMainFrame::LoadPlayerSkin(CString strPath,int nShow)
{
	if(strPath.IsEmpty())
		return FALSE;
	
	BOOL bOK = TRUE;
	if(!m_pIEPlayer)
	{
		m_pIEPlayer = new CMyIEWnd();
	}
	m_pIEPlayer->m_bIsPlayList = 0;

	// get reg settings
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	CString strTitle = _T("Fox Media Player");

	int xSize = ReadPageSize(strPath,true);
	int ySize = ReadPageSize(strPath,false);
	if(xSize == 0)
		xSize = 580;
	if(ySize == 0)
		ySize = 500;

	if(!IsWindow(m_pIEPlayer->m_hWnd))	
	{
		CRect rect;
		// last pos
		int nLeft = pApp->GetProfileInt("Settings","xposPlayer",0);
		if(nLeft < 0 || nLeft > 10000)
			nLeft = 0;
		rect.left = nLeft;
		int nTop = pApp->GetProfileInt("Settings","yposPlayer",200);
		if(nTop < 0 || nTop > 10000)
			nTop = 0;
		rect.top = nTop;
		// last know size
		int nRight = pApp->GetProfileInt("Settings","x2posPlayer",580);
		if(nRight < 0 || nRight > 10000)
			nRight = xSize;
		int nBot = pApp->GetProfileInt("Settings","y2posPlayer",500);
		if(nBot < 0 || nBot > 10000)
			nBot = ySize;

		rect.right = rect.left + nRight;
		rect.bottom = rect.top + nBot;

		TRY
		{
			bOK = m_pIEPlayer->CreateEx(WS_EX_APPWINDOW,AfxRegisterWndClass(0),"MyIEWnd",
				WS_OVERLAPPEDWINDOW|WS_POPUPWINDOW,CRect(0,0,0,0),this,0);
			if(!bOK)
				return FALSE;
			m_pIEPlayer->CreateMyWindow();
			m_pIEPlayer->MoveWindow(rect);
			m_pIEPlayer->SetWindowText(strTitle);
		}
		CATCH(CException,e)
		{
			return FALSE;
		}
		END_CATCH
	}
	BOOL bHidePlayerWindow = (AfxGetApp()->GetProfileInt("Settings","HideVideoWindow",0) == 1);
	m_pIEPlayer->ShowWindow(bHidePlayerWindow?SW_HIDE:nShow);

	m_pIEPlayer->m_bCanLoadAWebPage = true;
	bOK = m_pIEPlayer->Navigate2(strPath);
	if(!bOK)
		bOK = m_pIEPlayer->Navigate(strPath);
	m_pIEPlayer->m_bCanLoadAWebPage = false;

	if(SW_SHOW == nShow)
		m_TimerNoTopMost = SetTimer(ID_NO_TOP_MOST,100,NULL);

	return bOK;
}

BOOL CMainFrame::LoadPlayListSkin(CString strPath,int nShow)
{
	if(strPath.IsEmpty())
		return FALSE;
	
	BOOL bOK = TRUE;
	if(!m_pIESkin)
	{
		m_pIESkin = new CMyIEWnd();
	}
	m_pIESkin->m_bIsPlayList = 1;

	// get reg settings
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	CString strTitle = _T("Fox Media Center");

	int xSize = ReadPageSize(strPath,true);
	int ySize = ReadPageSize(strPath,false);
	if(xSize == 0)
		xSize = 500;
	if(ySize == 0)
		ySize = 500;

	if(!IsWindow(m_pIESkin->m_hWnd))	
	{
		CRect rect;
		int nLeft = pApp->GetProfileInt("Settings","xposList",0);
		if(nLeft < 0 || nLeft > 10000)
			nLeft = 0;
		rect.left = nLeft;
		int nTop = pApp->GetProfileInt("Settings","yposList",200);
		if(nTop < 0 || nTop > 10000)
			nTop = 0;
		rect.top = nTop;
		rect.right = rect.left + xSize;
		rect.bottom = rect.top + ySize;

		TRY
		{
			bOK = m_pIESkin->CreateEx(WS_EX_APPWINDOW,AfxRegisterWndClass(0),"MyIEWnd",
				WS_THICKFRAME|WS_POPUP|WS_CAPTION|WS_SYSMENU|WS_BORDER,CRect(0,0,0,0),this,0);
			if(!bOK)
				return FALSE;
			m_pIESkin->CreateMyWindow();
			m_pIESkin->MoveWindow(rect);
			m_pIESkin->SetWindowText(strTitle);
		}
		CATCH(CException,e)
		{
			return FALSE;
		}
		END_CATCH
	}

	m_pIESkin->ShowWindow(nShow);

	m_pIESkin->m_bCanLoadAWebPage = true;
	bOK = m_pIESkin->Navigate2(strPath);
	if(!bOK)
		bOK = m_pIESkin->Navigate(strPath);
	m_pIESkin->m_bCanLoadAWebPage = false;

	if(SW_SHOW == nShow)
		m_TimerNoTopMost = SetTimer(ID_NO_TOP_MOST,100,NULL);

	return bOK;
}

void CMainFrame::OnFileShowplaylist() 
{
	if(m_pIESkin &&	IsWindow(m_pIESkin->m_hWnd))
	{
		m_pIESkin->ShowWindow(SW_NORMAL);
		m_TimerNoTopMost = SetTimer(ID_NO_TOP_MOST,100,NULL);
		return;
	}

	CString strPath;
	GetModuleFileName(NULL,strPath.GetBuffer(MAX_PATH),MAX_PATH);
	strPath.ReleaseBuffer();
	strPath = strPath.Left(strPath.ReverseFind('\\')+1);
	strPath += "Skins\\";

	CString strSkin;
	strSkin = AfxGetApp()->GetProfileString("Settings","CurrentSkin",DEFAULT_SKIN);	
	
	CString strFile = strPath + strSkin + "\\playlist.html";
	SECFileSystem fp;
	if(!fp.FileExists(strFile))
		strFile = FindHtmlFile(strPath + strSkin);

	if(!LoadPlayListSkin(strFile))
		DebugMessage("Error loading skin " + strFile);	
}

void CMainFrame::OnFileHideplaylist() 
{
	if(m_pIESkin)
		m_pIESkin->ShowWindow(SW_HIDE);
}

long CMainFrame::OnPreLoadPlayList(UINT wParam, LONG lParam)
{
	if(m_pIESkin &&	IsWindow(m_pIESkin->m_hWnd))
		return 1;

	if(m_pIESkin)
	{
		delete m_pIESkin;
		m_pIESkin = NULL;
	}

	CString strPath;
	GetModuleFileName(NULL,strPath.GetBuffer(MAX_PATH),MAX_PATH);
	strPath.ReleaseBuffer();
	strPath = strPath.Left(strPath.ReverseFind('\\')+1);
	strPath += "Skins\\";

	CString strSkin;
	strSkin = AfxGetApp()->GetProfileString("Settings","CurrentSkin",DEFAULT_SKIN);	
	
	SECFileSystem fp;
	if(!fp.DirectoryExists(strPath + strSkin))
	{
		CSelectSkinDlg dlg;
		if(dlg.DoModal() != IDOK)
			return 1;
		strSkin = AfxGetApp()->GetProfileString("Settings","CurrentSkin",DEFAULT_SKIN);	
	}
	
	CString strFile = strPath + strSkin + "\\playlist.html";
	if(!fp.FileExists(strFile))
		strFile = FindHtmlFile(strPath + strSkin);

	if(!LoadPlayListSkin(strFile,SW_HIDE))
		DebugMessage("Error loading skin " + strFile);

	return 1;
}

long CMainFrame::OnPreLoadPlayer(UINT wParam, LONG lParam)
{
	if(m_pIEPlayer && IsWindow(m_pIEPlayer->m_hWnd))
		return 1;

	if(m_pIEPlayer)
	{
		delete m_pIEPlayer;
		m_pIEPlayer = NULL;
	}

	CString strPath;
	GetModuleFileName(NULL,strPath.GetBuffer(MAX_PATH),MAX_PATH);
	strPath.ReleaseBuffer();
	strPath = strPath.Left(strPath.ReverseFind('\\')+1);
	strPath += "Skins\\";

	CString strSkin;
	strSkin = AfxGetApp()->GetProfileString("Settings","CurrentSkin",DEFAULT_SKIN);	
	
	CString strFile = strPath + strSkin + "\\player.html";
	SECFileSystem fp;
	if(!fp.FileExists(strFile))
	{
		AfxMessageBox("Error loading player skin, " + strFile);
		return 1;
	}

	if(!LoadPlayerSkin(strFile,SW_HIDE))
		DebugMessage("Error loading skin " + strFile);

	return 1;
}

void CMainFrame::OnFileSelectskin() 
{
	CSelectSkinDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		// reload new skin
		if(m_pIESkin)
		{
			delete m_pIESkin;
			m_pIESkin = NULL;
		}
		OnFileShowplaylist();	
	}
}

void CMainFrame::OnFileActivatetimedshutdown() 
{
	m_bTimedShutdownActive = m_bTimedShutdownActive ? false:true;
	// start timer
	if(m_bTimedShutdownActive)
	{
		CTimedShutdownDlg dlg;
		if(dlg.DoModal() == IDOK)
		{
			m_bShutoffAfterPlayList = (AfxGetApp()->GetProfileInt("Settings","ShutOffAfterPlayList",1) == 1);
			// timed shutdown
			if(!m_bShutoffAfterPlayList)
			{
				CString strMinutes = AfxGetApp()->GetProfileString("Settings","MinsShutdown","30");
				DWORD dwTime = atol(strMinutes);
				DWORD dwLowerIntervals = dwTime * 3; // every 20 secs
				dwTime = dwTime * 60;
				m_TimerShutDown = SetTimer(ID_TIMER_SHUTDOWN,dwTime * 1000,NULL); 
				// lower volume
				BOOL bLowerVolume =(AfxGetApp()->GetProfileInt("Settings","LowerVolume",1) == 1);
				if(bLowerVolume)
				{
					m_TimerLowerVolume = SetTimer(ID_TIMER_LOWER_VOLUME,20 * 1000,NULL); 
					m_dwLowerVolVal = m_pMyMediaPlayer->GetLowerVolumeVal(dwLowerIntervals);
				}
			}
			m_pMyMediaPlayer->SaveCurrentVolume();
		}
		else
		{
			m_bTimedShutdownActive = false;
			m_bShutoffAfterPlayList = false;
		}
	}
	else
	{
		KillTimer(m_TimerShutDown);
		KillTimer(m_TimerLowerVolume);
		AfxGetApp()->WriteProfileInt("Settings","LastVolume",0);
	}
}

void CMainFrame::OnUpdateFileActivatetimedshutdown(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bTimedShutdownActive);	
}

void CMainFrame::OnFilePlay() 
{
	if(m_pMyMediaPlayer)
		m_pMyMediaPlayer->Play();	
}

void CMainFrame::OnFilePause() 
{
	if(m_pMyMediaPlayer)
		m_pMyMediaPlayer->Pause();	
}

void CMainFrame::OnFileStop() 
{
	if(m_pMyMediaPlayer)
		m_pMyMediaPlayer->Stop();	
}

void CMainFrame::OnFileSettings() 
{
	CSettingsDlg dlg;
	DWORD dwRes;
	if((dwRes = dlg.DoModal()) == IDOK)
	{
		BOOL bEnableShortcutKeys = (AfxGetApp()->GetProfileInt("Settings","EnableShortcutKeys",1) == 1);
		if(bEnableShortcutKeys)
			StartKeyBoardHook();
		else
			StopKeyBoardHook();

		// kill skins from memory
		BOOL bPreLoadPlayList = (AfxGetApp()->GetProfileInt("Settings","PreLoadPlayList",1) == 1);
		if(!bPreLoadPlayList)
		{
			if(!m_pMyMediaPlayer->IsPlayingVideo())
			{
				if(m_pIEPlayer)
				{
					delete m_pIEPlayer;
					m_pIEPlayer = NULL;
				}
			}
			BOOL bVisible = (m_pIESkin && IsWindow(m_pIESkin->m_hWnd) && m_pIESkin->IsWindowVisible());
			if(!bVisible)
			{
				if(m_pIESkin)
				{
					delete m_pIESkin;
					m_pIESkin = NULL;
				}
			}
		}
		// show/hide video player window
		BOOL bHidePlayerWindow = (AfxGetApp()->GetProfileInt("Settings","HideVideoWindow",0) == 1);
		BOOL bVisible = (m_pIEPlayer && IsWindow(m_pIEPlayer->m_hWnd) && m_pIEPlayer->IsWindowVisible());
		if(!bHidePlayerWindow)
		{
			if(!bVisible && m_pMyMediaPlayer->IsPlayingVideo())
			{
				if(m_pIEPlayer)
				{
					m_pIEPlayer->ShowWindow(SW_NORMAL);
					BumpWindow(m_pIEPlayer);
				}
			}
		}
		else
		{
			if(bVisible && m_pMyMediaPlayer->IsPlayingVideo())
			{
				if(m_pIEPlayer)
					m_pIEPlayer->ShowWindow(SW_HIDE);
			}
		}
	}
	else if(dwRes == IDYES) // show file association dlg
	{
		CFileAssociationDlg dlg;
		if(dlg.DoModal() == IDOK)
		{
			SHChangeNotify(SHCNE_ASSOCCHANGED,SHCNF_IDLIST,NULL,NULL);
		}
	}
}

void CMainFrame::OnFileSelectplaylist() 
{
	CPlayListManager list;

	CManagePlayListDlg dlg;
	int nResult = dlg.DoModal();
	if(nResult == IDYES)
	{
		OnFileStop();
		list.LoadCurrent(true,false,true);
		if(!dlg.m_strSelectedFile.IsEmpty())
			SetSelectItemOcx(dlg.m_strSelectedFile);
		OnFilePlay();
		// hide video player if need be
		if(!m_pMyMediaPlayer->IsPlayingVideo())
		{
			if(m_pIEPlayer)
				m_pIEPlayer->ShowWindow(SW_HIDE);
		}
	}
	else if(nResult == IDOK)
	{
		CString strCurrentPlayInfo = m_pMyMediaPlayer->GetCurrentPlayingInfo();
		if(!strCurrentPlayInfo.IsEmpty())
		{
			CString strCurrentFile = ParseXML("CurrentFile",strCurrentPlayInfo);
			if(!list.CheckFileIsStillValid(strCurrentFile))
			{
				OnFileStop();
				list.LoadCurrent(true,true,true);
				OnFilePlay();
			}
			else
			{
				list.LoadCurrent(true,false,true);
				SetSelectItemOcx(strCurrentFile.Mid(strCurrentFile.ReverseFind('\\')+1));
			}
		}
	}
}

// start hook
void CMainFrame::StartKeyBoardHook()
{
	if(glhinstDLL)
		return;

	CString strPath;
	GetModuleFileName(NULL,strPath.GetBuffer(MAX_PATH),MAX_PATH);
	strPath.ReleaseBuffer();
	strPath = strPath.Left(strPath.ReverseFind('\\')+1);
	strPath += "FoxKeyHook.dll";
	
	HOOKPROC hModuleHook = NULL; 
	// load dll
	glhinstDLL = LoadLibrary(strPath); 
	// get hook function
	hModuleHook = (HOOKPROC)GetProcAddress(glhinstDLL, "MyKeyboardProc"); 
	if(hModuleHook)
		ghhookKeyMsg = SetWindowsHookEx(WH_KEYBOARD,hModuleHook,glhinstDLL,0); 
	else
		AfxMessageBox("Unable to load keyboard hook for remote control");
}

void CMainFrame::StopKeyBoardHook()
{
	if(ghhookKeyMsg) 
	{
		UnhookWindowsHookEx(ghhookKeyMsg);
		ghhookKeyMsg = NULL;
		FreeLibrary(glhinstDLL);    
		glhinstDLL = NULL;
	}
}

long CMainFrame::OnKeyboardHookMsg(UINT wParam, LONG lParam)
{
	CTime tm = CTime::GetCurrentTime();
	CTimeSpan ts = tm - m_timeLastClick;

	if(ts.GetTotalSeconds() < 1 && m_timeLastClick.GetTime() > 0)
		return 0;

	m_timeLastClick = tm;
	CString strData;

	if(wParam >= 112 && wParam <= 123)
	{
		switch(wParam)
		{
		case 116:
			OnFilePlay();
			break;
		case 117:
			OnFilePause();
			break;
		case 118:
			OnFileStop();
			break;
		case 119:
			OnFileSelectplaylist();
			break;
		case 112:
			if(m_pMyMediaPlayer)
				m_pMyMediaPlayer->LowerVolumeWave();	
			break;
		case 113:
			if(m_pMyMediaPlayer)
				m_pMyMediaPlayer->IncreaseVolumeWave();	
			break;
		case 114:
			OnFilePrevious();
			break;
		case 115:
			OnFileNext();
			break;
		}
	}
	return 1;
}

void CMainFrame::OnFilePrevious() 
{
	if(m_pMyMediaPlayer)
		m_pMyMediaPlayer->Previous();	
}

void CMainFrame::OnFileNext() 
{
	if(m_pMyMediaPlayer)
		m_pMyMediaPlayer->Next();	
}

long CMainFrame::OnPlayAllFromSelected(WPARAM wParam,LPARAM lParam)
{
	if(m_pMyMediaPlayer)
	{
		m_pMyMediaPlayer->Stop();
		if(wParam != -1)
			m_pMyMediaPlayer->m_nCurrentMediaPos = (DWORD)wParam;
		m_pMyMediaPlayer->Play();	
	}
	return 1;
}

void CMainFrame::SetSelectItemOcx(DWORD dwItem, BOOL bSelect)
{
	if(m_pMyMediaPlayer && m_pMyMediaPlayer->m_straPlayList.GetSize() > dwItem)
	{
		m_pMyMediaPlayer->m_nCurrentMediaPos = dwItem;
	}
}

long CMainFrame::SetSelectItemOcx(CString strName, BOOL bSelect)
{
	long lPos = -1;
	if(!m_pMyMediaPlayer)
		return - 1;
	for(int n=0;n<m_pMyMediaPlayer->m_straPlayList.GetSize();n++)
	{
		CString strTest = ParseXML("Name",m_pMyMediaPlayer->m_straPlayList.GetAt(n));
		if(strTest == strName)
		{
			m_pMyMediaPlayer->m_nCurrentMediaPos = n;
			m_pMyMediaPlayer->SetPlayingIcon(n,bSelect);
			lPos = n;
			break;
		}
	}
	return lPos;
}

void CMainFrame::AddToPlayList(CString strNew,BOOL bSendToOcx)
{
	if(m_pMyMediaPlayer)
		m_pMyMediaPlayer->m_straPlayList.Add(strNew);
	if(bSendToOcx)
		m_TimerAddToPlayList = SetTimer(ID_TIMER_SEND_FILELIST_TO_PLAYLIST,100,NULL);
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	if(ID_TIMER_SHUTDOWN == nIDEvent)
	{
		KillTimer(m_TimerShutDown);
		KillTimer(m_TimerLowerVolume);
		BOOL bShutdown = (AfxGetApp()->GetProfileInt("Settings","ShutdownComputer",1) == 1);
		if(bShutdown)
		{
			if(m_pMyMediaPlayer)
			{
				m_pMyMediaPlayer->Mute();
				m_pMyMediaPlayer->Stop();
			}
			
			BOOL bOK = MySystemShutDown();
			if(!bOK)
			{
				DWORD dwErr = GetLastError();
				CString strErr;
				strErr.Format("Shutdown failed, error code = %u",dwErr);
				DebugMessage(strErr);
				AfxMessageBox("Error shutting down computer, you may need to check with your Network Administrator that your logon has permission for this task.");
			}				
		}
		else
		{
			OnFileStop();
		}			
	}	
	else if(ID_TIMER_LOWER_VOLUME == nIDEvent)
	{
		m_pMyMediaPlayer->LowerVolume(m_dwLowerVolVal);	
	}
	else if(nIDEvent == ID_5MIN_PING_RETRY)
	{
		KillTimer(m_pPingJobManager->m_nTimerRetry5Mins);
		m_pPingJobManager->m_nTimerRetry5Mins = 0;
		m_pPingJobManager->ContinueAnyCurrentJobs();
	}
	else if(ID_TIMER_SEND_FILELIST_TO_PLAYLIST == nIDEvent)
	{
		KillTimer(m_TimerAddToPlayList);
		if(m_pMyMediaPlayer)
		{
			CString strData = m_pMyMediaPlayer->GetCurrentFileListXML();
			SendMessageToPlayListOcx(strData);

			if(m_pMyMediaPlayer->m_enumCurrentPlayState != STOPPED && m_pMyMediaPlayer->m_enumCurrentPlayState != LOADING)
				m_pMyMediaPlayer->SetPlayingIcon(m_pMyMediaPlayer->m_nCurrentMediaPos);
			// send playing meta data as well
			m_pMyMediaPlayer->SendCurrentMediaInfo();
		}
	}
	else if(ID_NO_TOP_MOST == nIDEvent)
	{
		KillTimer(m_TimerNoTopMost);
		if(m_pIESkin && IsWindow(m_pIESkin->m_hWnd))
			m_pIESkin->SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		if(m_pIEPlayer && IsWindow(m_pIEPlayer->m_hWnd))
			m_pIEPlayer->SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	}
	else if(ID_LOAD_WEB_PAGES == nIDEvent)
	{
		KillTimer(m_timerLoadSkin);
		BOOL bShowPlayListOnStart = m_bPopUpPlayList || (AfxGetApp()->GetProfileInt("Settings","ShowPlaylist",0) == 1);
		BOOL bPreLoadPlayList = (AfxGetApp()->GetProfileInt("Settings","PreLoadPlayList",1) == 1);
		// load playlist
		OnPreLoadPlayList(0,0);
		// only load player if need pre loaded
		if(bPreLoadPlayList)
			OnPreLoadPlayer(0,0);
		// show playlist?
		if(bShowPlayListOnStart)
			OnFileShowplaylist();		
	}
	else if(nIDEvent == ID_CHECK_UPDATES)
	{
		KillTimer(m_TimerCheckUpdates);

		// check only 1 time per day
		BOOL bCheckForUpdate = false;

		CTime tm = CTime::GetCurrentTime();
		CString strLastTime = AfxGetApp()->GetProfileString("Settings","lasttimecheck","");
		if(strLastTime.IsEmpty())
			bCheckForUpdate = true;
		else
		{
			DWORD dwTimeInstall;
			dwTimeInstall = atol(strLastTime);
			CTime tmInstall(dwTimeInstall);

			CTimeSpan ts = tm - tmInstall;
			if(ts.GetDays() >= 1)
				bCheckForUpdate = true;			
		}
		if(bCheckForUpdate)
		{
			strLastTime.Format("%u",tm.GetTime());
			AfxGetApp()->WriteProfileString("Settings","lasttimecheck",strLastTime);
			// Update server URL
			CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
			CString strURL = ReadURL("UpdateURL",DEFAULT_UPDATE_URL);
			// add ID and Brand just in case
			strURL += "?CHECKUPDATE=" + GetCheckUpdateString();

			CString strJob = "<FileURL>" + strURL + "</FileURL>";
			strJob += "<JobType>CheckForUpdates</JobType>";
			// job status
			strJob += "<Status>none</Status>";
			m_pPingJobManager->NewJob(strJob);
		}
		m_TimerCheckUpdates = SetTimer(ID_CHECK_UPDATES,ONE_HOUR,NULL);
	}
	else if(nIDEvent == ID_SEND_NEW_USER_STAT)
	{
		KillTimer(m_TimerSendNewUser);
		SendNewUserStat();
	}
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::ClearPlayList(BOOL bResetOcx)
{
	m_pMyMediaPlayer->m_straPlayList.RemoveAll();
	m_pMyMediaPlayer->m_nCurrentMediaPos = 0;
	if(bResetOcx)
	{
		CString strData = "<Message>ClearAll</Message>";
		SendMessageToPlayListOcx(strData);
		m_TimerAddToPlayList = SetTimer(ID_TIMER_SEND_FILELIST_TO_PLAYLIST,50,NULL);
	}
}

void CMainFrame::UpdateListFromOCX(CString strParams)
{
	CString strCurrentPlayList = AfxGetApp()->GetProfileString("Settings","CurrentPlaylist","default");
	CStringArray straTemp;
	CString strTemp;
	while(strParams.Find("</PlayListEntry>") != -1)
	{
		strTemp = ParseXML("PlayListEntry",strParams);
		strTemp = ParseXML("FullPath",strTemp);
		straTemp.Add(strTemp);
		strParams = strParams.Mid(strParams.Find("</PlayListEntry>")+strlen("</PlayListEntry>"));
	}
	CPlayListManager list;
	list.UpdatePlayList(strCurrentPlayList,&straTemp);

	CString strCurrentPlayInfo = m_pMyMediaPlayer->GetCurrentPlayingInfo();
	if(!strCurrentPlayInfo.IsEmpty())
	{
		CString strCurrentFile = ParseXML("CurrentFile",strCurrentPlayInfo);
		if(!list.CheckFileIsStillValid(strCurrentFile))
		{
			OnFileStop();
			list.LoadCurrent(false,true);
			OnFilePlay();
		}
		else
		{
			list.LoadCurrent(false,false);
			SetSelectItemOcx(strCurrentFile.Mid(strCurrentFile.ReverseFind('\\')+1),false);
		}
	}
	else
		list.LoadCurrent(false,false);
}

long CMainFrame::OnQuitPreLoadPlayer(UINT wParam, LONG lParam)
{
	OnFileStop();
	ShowWindow(SW_HIDE);

	return 1;
}

long CMainFrame::ShowHidePlayList(UINT wParam, LONG lParam)
{
	BOOL bHide = (m_pIESkin &&	IsWindow(m_pIESkin->m_hWnd)	&& m_pIESkin->IsWindowVisible());
	if(bHide)
		OnFileHideplaylist();
	else
		OnFileShowplaylist();
	return 1;
}

BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	CString strParams;
	int nSize = pCopyDataStruct->cbData;
	memcpy(strParams.GetBuffer(nSize),pCopyDataStruct->lpData,nSize);
	strParams.ReleaseBuffer();
	
	// drop message to add new media file
	if("ShowPlayList" == ParseXML("Message",strParams))
	{
		PostMessage(WM_SHOW_HIDE_PLAYLIST);
	}	
	else if("SendCurrentPlayList" == ParseXML("Message",strParams))
	{
		m_TimerAddToPlayList = SetTimer(ID_TIMER_SEND_FILELIST_TO_PLAYLIST,100,NULL);
	}
	else if("ShowSelectSkin" == ParseXML("Message",strParams))
	{
		WPARAM dwMsg = MAKEWPARAM(ID_FILE_SELECTSKIN,0);
		PostMessage(WM_COMMAND,dwMsg,0);
	}
	else if("ShowSettings" == ParseXML("Message",strParams))
	{
		WPARAM dwMsg = MAKEWPARAM(ID_FILE_SETTINGS,0);
		PostMessage(WM_COMMAND,dwMsg,0);
	}
	else if("ShowActivetimedshutdown" == ParseXML("Message",strParams))
	{
		WPARAM dwMsg = MAKEWPARAM(ID_FILE_ACTIVATETIMEDSHUTDOWN,0);
		PostMessage(WM_COMMAND,dwMsg,0);
	}
	else if("PlayAllFromSelected" == ParseXML("Message",strParams))
	{
		DWORD dwPos = atol(ParseXML("HotItem",strParams));
		if(m_pMyMediaPlayer->m_nCurrentMediaPos != dwPos)
			OnFileStop();
		if(m_pMyMediaPlayer)
		{
			m_pMyMediaPlayer->m_nCurrentMediaPos = dwPos;
		}
		OnFilePlay();
	}
	else if("PlayAll" == ParseXML("Message",strParams))
	{
		OnFilePlay();
	}
	else if("Pause" == ParseXML("Message",strParams))
	{
		OnFilePause();
	}
	else if("Stop" == ParseXML("Message",strParams))
	{
		OnFileStop();
	}
	else if("Previous" == ParseXML("Message",strParams))
	{
		OnFilePrevious();
	}
	else if("Next" == ParseXML("Message",strParams))
	{
		OnFileNext();
	}
	else if("Rewind" == ParseXML("Message",strParams))
	{
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->Rewind();	
	}
	else if("Forward" == ParseXML("Message",strParams))
	{
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->Forward();	
	}
	else if("Mute" == ParseXML("Message",strParams))
	{
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->Mute();	
	}
	else if("LowerVolume" == ParseXML("Message",strParams))
	{
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->LowerVolume();	
	}
	else if("IncreaseVolume" == ParseXML("Message",strParams))
	{
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->IncreaseVolume();	
	}
	else if("ShowManagePlayList" == ParseXML("Message",strParams))
	{
		WPARAM dwMsg = MAKEWPARAM(ID_FILE_SELECTPLAYLIST,0);
		PostMessage(WM_COMMAND,dwMsg,0);
	}
	else if("AddToPlayList" == ParseXML("Message",strParams))
	{
		BOOL bAppendTempPlaylist = (m_pMyMediaPlayer->m_enumCurrentPlayState == PLAYING);
		if(!bAppendTempPlaylist)
			OnFileStop();

		CString strFile = ParseXML("FilePath",strParams);
		CString strName = strFile.Mid(strFile.ReverseFind('\\')+1);
		CString strNew;
		strNew.Format("<FullPath>%s</FullPath><Name>%s</Name>",strFile,strName);

		SetTempPlayList();
		AddToPlayList(strNew,true);
		CPlayListManager list;
		list.SaveCurrent(&m_pMyMediaPlayer->m_straPlayList,"");

		if(!bAppendTempPlaylist)
		{
			OnFilePlay();
		}
		else if(m_pMyMediaPlayer->m_enumCurrentPlayState == STOPPED)
		{
			m_pMyMediaPlayer->m_nCurrentMediaPos = m_pMyMediaPlayer->m_straPlayList.GetSize() - 1;
			OnFilePlay();
		}
	}
	else if("CurrentFileListXML" == ParseXML("Message",strParams))
	{
		UpdateListFromOCX(strParams);
	}
	// video player requests its file
	else if("VideoPlayerReady" == ParseXML("Message",strParams))
	{
		PostMessage(WM_VIDEO_PLAYER_READY);
	}
	else if("EndofstreamMediaPlayer" == ParseXML("Message",strParams))
	{
		PostMessage(WM_END_OF_VIDEO);
	}
	else if("IsTimedShutdownActive" == ParseXML("Message",strParams))
	{
		return m_bTimedShutdownActive;
	}
	else if("SetCurrentPosition" == ParseXML("Message",strParams))
	{
		DWORD dwPos = atol(ParseXML("Position",strParams));
		PostMessage(WM_SET_CURRENT_POS,0,dwPos);
	}
	else if("OrderSkin" == ParseXML("Message",strParams))
	{
		CString strData = ParseXML("Params",strParams);
		// convert from hex
		strParams = DecryptBlow(strData);
		
		if(!ParseXML("FileURL",strParams).IsEmpty())
			m_pJobManager->GetUpdateFile(strParams);		
	}

	return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}

long CMainFrame::OnVideoPlayerReady(UINT wParam, LONG lParam)
{
	if(m_pMyMediaPlayer && m_pMyMediaPlayer->m_enumCurrentMediaType == WMP_VIDEO
		&& m_pMyMediaPlayer->m_enumCurrentPlayState == PLAYING)
	{
		CString strFile;
		strFile.Format("<Message>SetCurrentFilePath</Message><FullPath>%s</FullPath>",m_pMyMediaPlayer->GetCurrentMediaName());
		SendMessageToPlayerOcx(strFile);
		BOOL bHidePlayerWindow = (AfxGetApp()->GetProfileInt("Settings","HideVideoWindow",0) == 1);
		if(m_pIEPlayer)
		{
			m_pIEPlayer->ShowWindow(bHidePlayerWindow?SW_HIDE:SW_SHOW);
			BumpWindow(m_pIEPlayer);
			m_TimerNoTopMost = SetTimer(ID_NO_TOP_MOST,100,NULL);
		}
		m_pMyMediaPlayer->m_enumCurrentPlayState = PLAYING;
	}
	return 1;
}

void CMainFrame::LoadTempPlayList(CStringArray *pstra)
{
	SetTempPlayList();

	for(int n=0;n<pstra->GetSize();n++)
	{
		CString strFile = pstra->GetAt(n);
		CString strName = strFile.Mid(strFile.ReverseFind('\\')+1);
		CString strNew;
		strNew.Format("<FullPath>%s</FullPath><Name>%s</Name>",strFile,strName);
		AddToPlayList(strNew,false);
	}
	CPlayListManager list;
	list.SaveCurrent(&m_pMyMediaPlayer->m_straPlayList,"");

	m_TimerAddToPlayList = SetTimer(ID_TIMER_SEND_FILELIST_TO_PLAYLIST,100,NULL);
	OnFilePlay();
}

void CMainFrame::SetTempPlayList()
{
	BOOL bAppendTempPlaylist = (m_pMyMediaPlayer->m_enumCurrentPlayState == PLAYING);
	AfxGetApp()->WriteProfileString("Settings","CurrentPlaylist",DEFAULT_TEMP_PLAYLIST_NAME);

	if(!bAppendTempPlaylist)
	{
		ClearPlayList(true);
		CPlayListManager list;
		list.DeletePlayList(DEFAULT_TEMP_PLAYLIST_NAME);
	}
}

long CMainFrame::EndOfVideo(UINT wParam, LONG lParam)
{
	m_pMyMediaPlayer->m_bLastWasVideo = true;
	m_pMyMediaPlayer->OnEndOfStreamMediaplayer1(1);
	m_pMyMediaPlayer->m_bLastWasVideo = false;
	if(!m_pMyMediaPlayer->IsPlayingVideo())
	{
		if(m_pIEPlayer)
			m_pIEPlayer->ShowWindow(SW_HIDE);
	}

	return 1;
}

long CMainFrame::OnSetCurrentPos(UINT wParam, LONG lParam)
{
	LONGLONG llPos = lParam * (LONGLONG)10000000;
	if(m_pMyMediaPlayer)
		m_pMyMediaPlayer->SetCurrentPosition(llPos);	
	return 1;
}

void CMainFrame::SetInstallParams()
{
	// exe path
	CString strPath;
	GetModuleFileName(NULL,strPath.GetBuffer(MAX_PATH),MAX_PATH);
	strPath.ReleaseBuffer();
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	AfxGetApp()->WriteProfileString("Settings","InstallPath",strPath);

	// mime type reg entry
	CreateRootRegEntry();

	// create GUID
	AfxGetApp()->WriteProfileString("Settings","InstallParam",CreateGUID());
	AfxGetApp()->WriteProfileInt("Settings","IsInstalled",1);

	// create startup key
	SECRegistry reg;
	CString strExe;
	GetModuleFileName(NULL,strExe.GetBuffer(MAX_PATH),MAX_PATH);
	strExe.ReleaseBuffer();

	BOOL bOK = reg.Connect(HKEY_LOCAL_MACHINE);
	bOK = reg.Open("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",SECRegistry::permissionWrite);
	bOK = reg.SetStringValue("FoxMediaCenter",strExe);

	MessageBox("To finish the install you now have to choose the media file types you want associated with this program and a skin.","Fox Media Center",MB_OK);

	// file association
	CFileAssociationDlg dlg2;
	if(dlg2.DoModal() == IDOK)
		SHChangeNotify(SHCNE_ASSOCCHANGED,SHCNF_IDLIST,NULL,NULL);

	// skin dialog
	CSelectSkinDlg dlg;
	dlg.DoModal();
	
	// load help page
	LoadInDefaultBrowser(DEFAULT_HELP);

	m_TimerSendNewUser = SetTimer(ID_SEND_NEW_USER_STAT,5 * 1000,NULL);
}

void CMainFrame::SendNewUserStat()
{
	CString strURL = ReadURL("UserProfileURL",NEW_USER_URL);
	CString strData = "?CHECKUPDATE=" + GetNewUserInfo();
	strURL += strData;

	CString strJob = "<FileURL>" + strURL + "</FileURL>";
	strJob += "<JobType>Stats</JobType>";
	strJob += "<Status>none</Status>";
	m_pPingJobManager->NewJob(strJob);
}

BOOL CMainFrame::HasBeenInstalled()
{
	return (AfxGetApp()->GetProfileInt("Settings","IsInstalled",0) == 1);
}

long CMainFrame::OnDeleteJob(UINT wParam, LONG lParam)
{
	// WM_DELETE_JOB
	if(wParam ==1)  // Ping job
	{
		m_pPingJobManager->DeleteJob((CPingJob*)lParam);
		m_pPingJobManager->ContinueAnyCurrentJobs();
	}
	else
	{
		CJob* pJob = (CJob*)lParam;
		pJob->m_strParams = ReplaceXML("Started","Status",pJob->m_strParams);
		m_pJobManager->DeleteJob(pJob);
		m_pJobManager->ContinueAnyCurrentJobs();
	}	
	return 1;
}

long CMainFrame::OnRetryJobLater(UINT wParam, LONG lParam)
{
	if(wParam ==1)  // Ping job
	{
		CPingJob* pJob = (CPingJob*)lParam;
		// .......... later retry
		m_pPingJobManager->RetryJobLater((CPingJob*)lParam);
		m_pPingJobManager->ContinueAnyCurrentJobs();
	}
	else			// http job
	{
		CJob* pJob = (CJob*)lParam;
		pJob->m_strParams = ReplaceXML("Started","Status",pJob->m_strParams);
		CString strParams = pJob->m_strParams;
		CString strFileURL = ParseXML("FileURL",pJob->m_strParams);
		// .......... later retry
		m_pJobManager->DeleteAnyJobsWithFileURL(strFileURL);
		
		m_pJobManager->ContinueAnyCurrentJobs();
	} 
	return 1;
}

long CMainFrame::OnFinishedJob(UINT wParam, LONG lParam)
{
	// WM_FINISHED_JOB
	if(wParam ==1)  // Ping job
	{
		CPingJob* pJob = (CPingJob*)lParam;
		if(pJob)
		{
			CString strReply = ParseXML("PingReply",pJob->m_strParams);
			// look for updates
			if(ParseXML("JobType",pJob->m_strParams) == "CheckForUpdates")
			{
				CString strReply = ParseXML("PingReply",pJob->m_strParams);
				CheckForUpdates(strReply);
			}
			m_pPingJobManager->DeleteJob(pJob);
		}
		m_pPingJobManager->ContinueAnyCurrentJobs();
	}
	else		// http job
	{
		CJob* pJob = (CJob*)lParam;
		if(pJob)
		{
			if(!m_pJobManager->VerfifyJobOK(pJob))
				return 1;

			// Finished
			pJob->m_strParams = ReplaceXML("Finished","Status",pJob->m_strParams);
			pJob->UpdateTime();

			m_pJobManager->ExecuteJob(pJob);
		}
	} 
	return 1;
}

void CMainFrame::CheckForUpdates(CString strReply)
{
	// DEFAULT_UPDATE_URL
	CString strUpdateURL = ParseXML("UpdateURLChange",strReply);
	if(!strUpdateURL.IsEmpty())
		WriteURL("UpdateURL",strUpdateURL);
	
	// update retry time
	CString strRetryTime = ParseXML("RetryTimeMins",strReply);
	if(!strRetryTime.IsEmpty())
	{
		int nMins = atoi(strRetryTime);
		if(nMins > 0 && nMins < 10000)
			AfxGetApp()->WriteProfileInt("Settings","RetryTimeMins",nMins);
	}

	// look for updated files
	while(strReply.Find("<UpdateFile>") != -1)
	{
		CString strData = ParseXML("UpdateFile",strReply);
		strReply = strReply.Mid(strReply.Find("</UpdateFile>") + strlen("</UpdateFile>"));
		// check version vs registry
		CString strRegVal = ParseXML("RegName",strData);
		CString strVer = ParseXML("Version",strData);
		CString strRegVer = AfxGetApp()->GetProfileString("Settings",strRegVal,"");
		if(!strVer.IsEmpty())
		{
			// needs update
			if(strRegVer.IsEmpty() || strVer > strRegVer)
			{
				m_pJobManager->GetUpdateFile(strData);
			}
		}
	}
	// look for message
	while(strReply.Find("<Message>") != -1)
	{
		CString strData = ParseXML("Message",strReply);
		strReply = strReply.Mid(strReply.Find("</Message>") + strlen("</Message>"));
		// check msg version vs registry
		CString strRegVal = ParseXML("RegName",strData);
		CString strVer = ParseXML("Version",strData);
		CString strRegVer = AfxGetApp()->GetProfileString("Settings",strRegVal,"");
		if(!strVer.IsEmpty())
		{
			// not yet showed msg
			if(strRegVer.IsEmpty() || strVer > strRegVer)
			{
				LoadMessage(strData);
				return;
			}
		}
	}
}

long CMainFrame::OnDeletePlayer(UINT wParam, LONG lParam)
{
	OnFileStop();
	if(m_pIEPlayer)
	{
		delete m_pIEPlayer;
		m_pIEPlayer = NULL;
	}
	return 1;
}

long CMainFrame::OnDeletePlayList(UINT wParam, LONG lParam)
{
	if(m_pIESkin)
	{
		delete m_pIESkin;
		m_pIESkin = NULL;
	}
	return 1;
}

long CMainFrame::OnDeleteAdPage(UINT wParam, LONG lParam)
{
	if(m_pIEAds)
	{
		delete m_pIEAds;
		m_pIEAds = NULL;
	}
	return 1;
}

BOOL CMainFrame::LoadMessage(CString strData)
{
	CString strURL = ParseXML("URL",strData);
	BOOL bOK;

	CString strRegVal = ParseXML("RegName",strData);
	CString strVer = ParseXML("Version",strData);
	AfxGetApp()->WriteProfileString("Settings",strRegVal,strVer);

	if(!m_pIEAds)
	{
		m_pIEAds = new CMyIEWnd();
	}
	m_pIEAds->m_bIsPlayList = 2;

	// get reg settings
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	CString strTitle = _T("Fox Media Center Message");

	int xSize = atoi(ParseXML("xSize",strData));
	int ySize = atoi(ParseXML("ySize",strData));
	if(xSize == 0)
		xSize = 500;
	if(ySize == 0)
		ySize = 500;

	if(!IsWindow(m_pIEAds->m_hWnd))	
	{
		CRect rect;
		int nLeft = pApp->GetProfileInt("Settings","xposad",100);
		if(nLeft < 0 || nLeft > 10000)
			nLeft = 0;
		rect.left = nLeft;
		int nTop = pApp->GetProfileInt("Settings","yposad",10);
		if(nTop < 0 || nTop > 10000)
			nTop = 0;
		rect.top = nTop;
		rect.right = rect.left + xSize;
		rect.bottom = rect.top + ySize;

		TRY
		{
			bOK = m_pIEAds->CreateEx(WS_EX_APPWINDOW,AfxRegisterWndClass(0),"MyIEWndAds",
				WS_THICKFRAME|WS_POPUP|WS_CAPTION|WS_SYSMENU|WS_BORDER,CRect(0,0,0,0),this,0);
			if(!bOK)
				return FALSE;
			m_pIEAds->CreateMyWindow();
			m_pIEAds->MoveWindow(rect);
			m_pIEAds->SetWindowText(strTitle);
		}
		CATCH(CException,e)
		{
			return FALSE;
		}
		END_CATCH
	}

	m_pIEAds->ShowWindow(SW_HIDE);

	m_pIEAds->m_bCanLoadAWebPage = true;
	bOK = m_pIEAds->Navigate2(strURL);
	if(!bOK)
		bOK = m_pIEAds->Navigate(strURL);
	m_pIEAds->m_bCanLoadAWebPage = false;

	return true;
}
