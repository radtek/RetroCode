// IEComCtrlSink.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "IEComCtrlSink.h"
#include <Mshtmdid.h>
#include "helpers.h"
#include "Mainfrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIEComCtrlSink

IMPLEMENT_DYNCREATE(CIEComCtrlSink, CCmdTarget)

CIEComCtrlSink::CIEComCtrlSink()
{
	EnableAutomation();

	m_pWebBrowser2 = NULL;
	m_pIEApp = NULL;
	m_wndWebBrowser.m_hWnd = NULL;

	m_dwCookie = 0;
	// know what settings in reg to save
	m_bIsPlayList = 1;

	m_bCanLoadAWebPage = false;
}

CIEComCtrlSink::~CIEComCtrlSink()
{
	UnAdviseSink();

	HRESULT hr;
	if(IsWindow(m_wndWebBrowser.m_hWnd))
	{
		m_wndWebBrowser.Detach();
		m_wndWebBrowser.m_hWnd = NULL;
		if(m_pIEApp)
		{
			hr = m_pIEApp->Release();
			m_pIEApp = NULL;
		}
		if(m_pWebBrowser2)
		{
			hr = m_pWebBrowser2->Quit();
			hr = m_pWebBrowser2->Release();
			m_pWebBrowser2 = NULL;
		}
	}
}

BEGIN_MESSAGE_MAP(CIEComCtrlSink, CCmdTarget)
	//{{AFX_MSG_MAP(CIEComCtrlSink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CIEComCtrlSink, CCmdTarget)

DISP_FUNCTION_ID(CIEComCtrlSink, "OnQuit",DISPID_ONQUIT,OnQuit,VT_EMPTY, VTS_NONE)
DISP_FUNCTION_ID(CIEComCtrlSink, "BeforeNavigate2",DISPID_BEFORENAVIGATE2,BeforeNavigate2,
				 VT_EMPTY, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
END_DISPATCH_MAP()


BOOL CIEComCtrlSink::CreateMyObject()
{
	CSingleLock singleLock(&m_CritSection);
	singleLock.Lock();

	HRESULT hr = CoCreateInstance(CLSID_InternetExplorer,
                               NULL,
                               CLSCTX_LOCAL_SERVER,
                               IID_IWebBrowser2,
                               (void**)&m_pWebBrowser2);

	if(!SUCCEEDED(hr))
	{
		CString strMsg;
		strMsg.Format("CIEComCtrlSink::CreateMyObject Failed to create object error = %d",(int)hr);
		DebugMessage(strMsg);
		return FALSE;
	}
	hr = m_pWebBrowser2->QueryInterface(IID_IWebBrowserApp,(void**)&m_pIEApp);
	hr = m_pIEApp->put_StatusBar(false);
	hr = m_pIEApp->put_ToolBar(false);
	hr = m_pIEApp->put_MenuBar(false);

	long hIE = 0;
	hr = m_pWebBrowser2->get_HWND(&hIE);
	if(!SUCCEEDED(hr))
	{
		CString strMsg;
		strMsg.Format("m_pWebBrowser2->get_HWND Failed to create object error = %d",(int)hr);
		DebugMessage(strMsg);
		return FALSE;
	}
	m_wndWebBrowser.Attach((HWND)hIE);
	m_wndWebBrowser.EnableScrollBar( SB_BOTH, ESB_DISABLE_BOTH);

	// declare events
	LPUNKNOWN pUnkSink = GetIDispatch(FALSE);
	AfxConnectionAdvise((LPUNKNOWN)m_pWebBrowser2,DIID_DWebBrowserEvents2,pUnkSink,FALSE,&m_dwCookie); 

	singleLock.Unlock();

	return TRUE;
}

BOOL CIEComCtrlSink::UnAdviseSink()
{
	BOOL bOK = TRUE;
	if(m_dwCookie != 0)
	{
		LPUNKNOWN pUnkSink = GetIDispatch(FALSE);
		bOK = AfxConnectionUnadvise((LPUNKNOWN)m_pWebBrowser2, DIID_DWebBrowserEvents2, pUnkSink, FALSE, m_dwCookie);
		m_dwCookie = 0;
	}
	return bOK;
}

void CIEComCtrlSink::OnQuit()
{
	// save window co ordinates
	CRect rect;
	m_wndWebBrowser.GetWindowRect(rect);
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
		}
		else
		{
			pApp->WriteProfileInt("Settings","xposad",nX);		
			pApp->WriteProfileInt("Settings","xposad",nY);
		}
	}
	UnAdviseSink();

	HRESULT hr;
	if(IsWindow(m_wndWebBrowser.m_hWnd))
	{
		m_wndWebBrowser.Detach();
	}
	m_wndWebBrowser.m_hWnd = NULL;
	if(m_pIEApp)
	{
		hr = m_pIEApp->Release();
		m_pIEApp = NULL;
	}
	if(m_pWebBrowser2)
	{
		hr = m_pWebBrowser2->Release();
		m_pWebBrowser2 = NULL;
	}

	BOOL bPreLoadPlayList = (AfxGetApp()->GetProfileInt("Settings","PreLoadPlayList",1) == 1);
	if(bPreLoadPlayList)
	{
		if(m_bIsPlayList == 1)
		{
			AfxGetMainWnd()->PostMessage(WM_PRE_LOAD_PLAYLIST);
		}
	}
	// stop video and reload if set
	if(m_bIsPlayList == 0)
	{
		AfxGetMainWnd()->PostMessage(WM_ONQUIT_PRE_LOAD_PLAYER);
	}
}

BOOL CIEComCtrlSink::Navigate(CString strURL)
{
	HRESULT hr = S_OK;

	if(!m_pWebBrowser2)
	{
		if(!CreateMyObject())
			return FALSE;
	}

	DWORD dwFlags = 0;
	LPCTSTR lpszTargetFrameName = NULL;
	LPCTSTR lpszHeaders = NULL;
	LPVOID lpvPostData = NULL;
	DWORD dwPostDataLen = 0;
	COleSafeArray vPostData;

	BSTR bstrURL = strURL.AllocSysString();
    hr = m_pWebBrowser2->Navigate(bstrURL, COleVariant((long) dwFlags, VT_I4), COleVariant(lpszTargetFrameName, VT_BSTR), 
                            vPostData, COleVariant(lpszHeaders, VT_BSTR));
	SysFreeString(bstrURL);

	return (hr == S_OK); 
}

BOOL CIEComCtrlSink::Navigate2(CString strURL)
{
	HRESULT hr = S_OK;

	if(!m_pWebBrowser2)
	{
		if(!CreateMyObject())
			return FALSE;
	}

	DWORD dwFlags = 0;
	LPCTSTR lpszTargetFrameName = NULL;
	LPCTSTR lpszHeaders = NULL;
	LPVOID lpvPostData = NULL;
	DWORD dwPostDataLen = 0;
	COleSafeArray vPostData;

	COleVariant vaURL(strURL);
    hr = m_pWebBrowser2->Navigate2(vaURL, COleVariant((long) dwFlags, VT_I4), COleVariant(lpszTargetFrameName, VT_BSTR), 
                            vPostData, COleVariant(lpszHeaders, VT_BSTR));

	return (hr == S_OK);
}

void CIEComCtrlSink::ShowWindow(UINT nShow)
{
	if(IsWindow(m_wndWebBrowser.m_hWnd))
	{
		m_wndWebBrowser.ShowWindow(nShow);
		m_wndWebBrowser.SetFocus();
		m_wndWebBrowser.SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	}
}

BOOL CIEComCtrlSink::CreateMyWindow(CString strTitle, CRect rect)
{
	if(m_pWebBrowser2)
	{
		m_pWebBrowser2->Release();
		m_pWebBrowser2 = NULL;
		m_wndWebBrowser.m_hWnd = NULL;
	}
	
	if(!CreateMyObject())
	{
		DebugMessage("Failed CreateMyObject()");
		return FALSE;
	}
	
	if(IsWindow(m_wndWebBrowser.m_hWnd))
	{
		m_wndWebBrowser.SetWindowText(strTitle);
		MoveWindow(rect);
	}

	return TRUE;
}

void CIEComCtrlSink::GetWindowRect(LPRECT lpRect) const
{
	if(IsWindow(m_wndWebBrowser.m_hWnd))
		m_wndWebBrowser.GetWindowRect(lpRect);
}

void CIEComCtrlSink::MoveWindow(LPCRECT lpRect)
{
	if(IsWindow(m_wndWebBrowser.m_hWnd))
		m_wndWebBrowser.MoveWindow(lpRect);
}

void CIEComCtrlSink::SetClientSize(int x, int y)
{
	if(IsWindow(m_wndWebBrowser.m_hWnd))
	{
		CRect rect1;
		m_wndWebBrowser.GetClientRect(rect1);
		CRect rect2;
		m_wndWebBrowser.GetWindowRect(rect2);
		int xDiff = rect2.Width() - rect1.Width();
		int yDiff = rect2.Height() - rect1.Height();
		CRect rectNew(rect2.left,rect2.top,rect2.left + x + xDiff,rect2.top + y + yDiff);
		MoveWindow(rectNew);
	}
}

// before navigate
void CIEComCtrlSink::BeforeNavigate2(LPDISPATCH pDisp, VARIANT FAR *url, VARIANT FAR *Flags, 
			VARIANT FAR *TargetFrameName, VARIANT FAR *PostData, VARIANT FAR *Headers, VARIANT_BOOL* Cancel)
{
	CString strHeaders = (BSTR)Headers->bstrVal;
	CString strUrl = (BSTR)url->bstrVal;	
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

void CIEComCtrlSink::SetNoTopMost()
{
	if(IsWindow(m_wndWebBrowser.m_hWnd))
	{
		m_wndWebBrowser.SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	}
}
