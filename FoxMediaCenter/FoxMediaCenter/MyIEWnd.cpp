// MyIEWnd.cpp: implementation of the CMyIEWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "MyIEWnd.h"
#include "helpers.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CMyIEWnd, CWnd)
	//{{AFX_MSG_MAP(CManagePlayListDlg)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMyIEWnd::CMyIEWnd()
{
	// know what settings in reg to save
	m_bIsPlayList = 1;
	m_bCanLoadAWebPage = false;
	m_pIEWnd = NULL;
}

CMyIEWnd::~CMyIEWnd()
{
	if(m_pIEWnd)
	{
		delete m_pIEWnd;
		m_pIEWnd = NULL;
	}
}

void CMyIEWnd::OnPaint() 
{
	CPaintDC dc(this); 
	CRect rectCl;
	GetClientRect(rectCl);
	CBrush br;
	br.CreateSolidBrush(RGB(0,0,0));
	dc.FillRect(rectCl,&br);
}

void CMyIEWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if(m_pIEWnd && IsWindow(m_pIEWnd->m_hWnd))
	{
		m_pIEWnd->SetTop(0);
		m_pIEWnd->SetLeft(0);
		m_pIEWnd->SetHeight(cy);
		m_pIEWnd->SetWidth(cx);
	}
}

BOOL CMyIEWnd::CreateMyWindow()
{
	CRect rect;
	GetClientRect(rect);
	m_pIEWnd = new CWebBrowser2();
	BOOL bOK = m_pIEWnd->Create(NULL,WS_CHILD|WS_VISIBLE,rect,this,ID_PLAYLIST_WND);
	if(bOK)
	{
		m_pIEWnd->SetStatusBar(false);
		m_pIEWnd->SetToolBar(0L);
		m_pIEWnd->SetMenuBar(false);
	}
	
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME),true);

	return true;
}

BOOL CMyIEWnd::Navigate2(CString strPath)
{
	if(!m_pIEWnd)
		return false;
	DWORD dwFlags = 0;
	LPCTSTR lpszTargetFrameName = NULL;
	LPCTSTR lpszHeaders = NULL;
	LPVOID lpvPostData = NULL;
	DWORD dwPostDataLen = 0;
	COleSafeArray vPostData;
	COleVariant vaURL(strPath);

	TRY
	{
		m_pIEWnd->Navigate2(vaURL, COleVariant((long) dwFlags, VT_I4), COleVariant(lpszTargetFrameName, VT_BSTR), 
 			vPostData, COleVariant(lpszHeaders, VT_BSTR));
	}
	CATCH(CException,e)
	{
		return false;
	}
	END_CATCH	
	return true;
}

BOOL CMyIEWnd::Navigate(CString strPath)
{
	if(!m_pIEWnd)
		return false;
	DWORD dwFlags = 0;
	LPCTSTR lpszTargetFrameName = NULL;
	LPCTSTR lpszHeaders = NULL;
	LPVOID lpvPostData = NULL;
	DWORD dwPostDataLen = 0;
	COleSafeArray vPostData;

	TRY
	{
		m_pIEWnd->Navigate(strPath, COleVariant((long) dwFlags, VT_I4), COleVariant(lpszTargetFrameName, VT_BSTR), 
 			vPostData, COleVariant(lpszHeaders, VT_BSTR));
	}
	CATCH(CException,e)
	{
		return false;
	}
	END_CATCH	
	return true;
}

void CMyIEWnd::OnClose()
{
	// save window co ordinates
	CRect rect;
	GetWindowRect(rect);
	int nX = rect.left;
	int nY = rect.top;
	if(nX < 3000 && nY < 3000)
	{
		CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
		if(m_bIsPlayList == 1)
		{
			pApp->WriteProfileInt("Settings","xposList",nX);		
			pApp->WriteProfileInt("Settings","yposList",nY);
		}
		else if(m_bIsPlayList == 0)
		{
			pApp->WriteProfileInt("Settings","xposPlayer",nX);		
			pApp->WriteProfileInt("Settings","yposPlayer",nY);
			pApp->WriteProfileInt("Settings","x2posPlayer",rect.Width());		
			pApp->WriteProfileInt("Settings","y2posPlayer",rect.Height());
		}
		else
		{
			pApp->WriteProfileInt("Settings","xposad",nX);		
			pApp->WriteProfileInt("Settings","xposad",nY);
		}
	}
	// close if an ad
	if(m_bIsPlayList == 2)
	{
		AfxGetMainWnd()->PostMessage(WM_DELETE_AD_PAGE);
		return;
	}
	BOOL bPreLoadPlayList = (AfxGetApp()->GetProfileInt("Settings","PreLoadPlayList",1) == 1);
	if(bPreLoadPlayList)
	{
		if(m_bIsPlayList == 1)
		{
			ShowWindow(SW_HIDE);
			return;
		}
		// stop video player and reload if set
		else if(m_bIsPlayList == 0)
		{
			AfxGetMainWnd()->PostMessage(WM_ONQUIT_PRE_LOAD_PLAYER);
		}
	}
	// close
	if(m_bIsPlayList == 1)
		AfxGetMainWnd()->PostMessage(WM_DELETE_PLAYLIST);
	else
		AfxGetMainWnd()->PostMessage(WM_DELETE_PLAYER);
}

BEGIN_EVENTSINK_MAP(CMyIEWnd, CWnd)
    //{{AFX_EVENTSINK_MAP(CMyIEWnd)
	ON_EVENT(CMyIEWnd, ID_PLAYLIST_WND, 104 /* DownloadComplete */, OnDownloadCompleteExplorer1, VTS_NONE)
	ON_EVENT(CMyIEWnd, ID_PLAYLIST_WND, 250 /* BeforeNavigate2 */, OnBeforeNavigate2Explorer1, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	ON_EVENT(CMyIEWnd, ID_PLAYLIST_WND, 259 /* DocumentComplete */, OnDocumentCompleteExplorer1, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CMyIEWnd, ID_PLAYLIST_WND, 253 /* OnQuit */, OnOnQuitExplorer1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CMyIEWnd::OnDownloadCompleteExplorer1() 
{
}

void CMyIEWnd::OnBeforeNavigate2Explorer1(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel) 
{
	CString strHeaders = (BSTR)Headers->bstrVal;
	CString strUrl = (BSTR)URL->bstrVal;	
	CString strTest = strUrl;
	strTest.MakeLower();
	BOOL bIsScriptLink = (strTest.Find("javascript:") != -1);

	if(IsMyMediaType(strUrl))
	{
		CString strFile = strUrl;
		CString strName = strFile.Mid(strFile.ReverseFind('\\')+1);
		CString strNew;
		strNew.Format("<FullPath>%s</FullPath><Name>%s</Name>",strFile,strName);

		((CMainFrame*)AfxGetMainWnd())->AddToPlayList(strNew,true);
		*Cancel = true;
		return;
	}

	if(!bIsScriptLink && !m_bCanLoadAWebPage)
	{
		*Cancel = true;
		LoadInDefaultBrowser(strUrl);
	}
}

void CMyIEWnd::OnDocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	if(m_bIsPlayList == 2)
		ShowWindow(SW_SHOW);
}

void CMyIEWnd::OnOnQuitExplorer1() 
{
}
