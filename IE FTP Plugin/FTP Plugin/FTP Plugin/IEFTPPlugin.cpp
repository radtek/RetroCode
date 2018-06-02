// IEFTPPlugin.cpp : Implementation of CIEFTPPlugin

#include "stdafx.h"
#include "IEFTPPlugin.h"
#include "helpers.h"
#include "Servprov.h"
#include "NagDlg.h"
// CIEFTPPlugin

DWORD WINAPI RunWindowsExplorerThread(LPVOID pParam);

CIEFTPPlugin::CIEFTPPlugin()
{
	m_bShow = false;
	m_hWndParent = NULL;
	m_hWnd = NULL;
	m_pUnkSite = NULL;
	m_spWebBrowser2 = NULL;
	m_bHasExpired = false;
	m_nTimer = NULL;
	m_pIEEvenHandler = NULL;
}

// IDeskBand
STDMETHODIMP CIEFTPPlugin::GetBandInfo(DWORD dwBandID, DWORD dwViewMode, DESKBANDINFO* pdbi)
{
	if (pdbi)
	{
		if (pdbi->dwMask & DBIM_MINSIZE)
		{
			pdbi->ptMinSize.x = MIN_X_SIZE;
			pdbi->ptMinSize.y = TB_HEIGHT;
		}
		if (pdbi->dwMask & DBIM_MAXSIZE)
		{
			pdbi->ptMaxSize.x = -1; // ignored
			pdbi->ptMaxSize.y = TB_HEIGHT;	// height
		}
		if (pdbi->dwMask & DBIM_INTEGRAL)
		{
			pdbi->ptIntegral.x = 1; // ignored
			pdbi->ptIntegral.y = 1; // not sizeable
		}
		if (pdbi->dwMask & DBIM_ACTUAL)
		{
			pdbi->ptActual.x = MIN_X_SIZE;
			pdbi->ptActual.y = TB_HEIGHT;
		}
		if (pdbi->dwMask & DBIM_TITLE)
		{
			//wcscpy(pdbi->wszTitle, A2W(MY_APP_NAME));			
		}
		if (pdbi->dwMask & DBIM_BKCOLOR)
		{
			//Use the default background color by removing this flag.
		//	pdbi->dwMask &= ~DBIM_BKCOLOR;
		}
		if (pdbi->dwMask & DBIM_MODEFLAGS)
		{
			//pdbi->dwModeFlags = DBIMF_DEBOSSED |  0x0080 ;
			pdbi->dwModeFlags = DBIMF_NORMAL;
		}
	}
	return S_OK;
}
// end IDeskBand

// IOleWindow
STDMETHODIMP CIEFTPPlugin::GetWindow(HWND* phwnd)
{
	HRESULT hr = S_OK;
	if (NULL == phwnd)
		hr = E_INVALIDARG;
	else
		*phwnd = m_hWnd;
	return hr;
}

STDMETHODIMP CIEFTPPlugin::ContextSensitiveHelp(BOOL fEnterMode)
{
	return S_OK;
}
// end IOleWindow

// IDockingWindow
STDMETHODIMP CIEFTPPlugin::CloseDW(unsigned long dwReserved)
{
	if (::IsWindow(m_hWnd))
		::DestroyWindow(m_hWnd);
	return S_OK;
}

STDMETHODIMP CIEFTPPlugin::ResizeBorderDW(const RECT* prcBorder, IUnknown* punkToolbarSite, BOOL fReserved)
{
	return E_NOTIMPL;
}

STDMETHODIMP CIEFTPPlugin::ShowDW(BOOL fShow)
{
	HRESULT hr = S_OK;
	m_bShow = fShow;
	::ShowWindow(m_hWnd, m_bShow ? SW_SHOW : SW_HIDE);
	return S_OK;	
}
// end IDockingWindow

// IOleObjectWithSite Methods
STDMETHODIMP CIEFTPPlugin::SetSite(IUnknown *pUnkSite)
{
    if(!pUnkSite)
    {
        if(m_pUnkSite)
		{
			m_pUnkSite->Release();
			m_pUnkSite = NULL;
		}
    }
    else
    {
		if(m_pUnkSite)
		{
			m_pUnkSite->Release();
			m_pUnkSite = NULL;
		}
		m_pUnkSite = pUnkSite;
		m_pUnkSite->AddRef();
		//Get the parent window.
		CComPtr<IOleWindow> pOleWindow;
		HWND hWnd = NULL;
		if(SUCCEEDED(pUnkSite->QueryInterface(IID_IOleWindow, (LPVOID*)&pOleWindow)))
		{
			pOleWindow->GetWindow(&hWnd);
		}
		if(::IsWindow(hWnd) && !::IsWindow(m_hWndParent))
		{
			// create window
			m_hWndParent = hWnd;
			m_hWnd = Create(m_hWndParent);
			// create toolbar
			m_wndToolBar.m_pParent = this;
			HWND wndToolbar = m_wndToolBar.Create(m_hWnd,0,0,WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);	
			
			// check registration expired
			if(!IsRegistered())
			{
				CheckNagScreen();
			}
		}
		HRESULT hr;
		CComPtr<IOleCommandTarget> pOleCommandTarget; 
		hr = pUnkSite->QueryInterface(IID_IOleCommandTarget,(LPVOID*)&pOleCommandTarget); 
		if(SUCCEEDED(hr)) 
		{ 
			CComPtr<IServiceProvider> pServiceProvider; 
			hr = pOleCommandTarget->QueryInterface(&pServiceProvider); 
			if(SUCCEEDED(hr)) 
				hr = pServiceProvider->QueryService(SID_SWebBrowserApp,&m_spWebBrowser2); 
		} 
        if(m_spWebBrowser2)
        {		
            // Connect to the browser in order to handle events.
            hr = ManageBrowserConnection(true,m_spWebBrowser2);
            if (FAILED(hr))
                ATLTRACE(_T("Failure sinking events from IWebBrowser2\n"));
        }
        else
        {
            ATLTRACE(_T("QI for IWebBrowser2 failed\n"));
        }
    }    
    return S_OK;
}

LRESULT CIEFTPPlugin::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if(m_wndToolBar.IsWindow())
		m_wndToolBar.MoveWindow(0,0,LOWORD(lParam),HIWORD(lParam));
	bHandled = false;
	return 0L;
}

LRESULT CIEFTPPlugin::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	CRect rect;
	GetClientRect(rect);
	CPaintDC dc(m_hWnd);
	// paint HDC
	COLORREF col = GetSysColor(COLOR_BTNFACE);
	dc.FillSolidRect(rect,col);

	bHandled = true;
	return S_OK;
}

// Funnel web browser events through this class
HRESULT CIEFTPPlugin::ManageBrowserConnection(BOOL bAdvise,IWebBrowser2* spWebBrowser2)
{
	HRESULT hr = S_OK;
    ATLASSERT(spWebBrowser2);
    if (!spWebBrowser2)
        return S_OK;

	if(bAdvise)
	{			
		if(m_pIEEvenHandler)
		{
			m_pIEEvenHandler->CleanUp();
			m_pIEEvenHandler->Release();
			m_pIEEvenHandler = NULL;
		}
		hr = CComObject<CIEEvenHandler>::CreateInstance(&m_pIEEvenHandler);
		m_pIEEvenHandler->AddRef();
		if(SUCCEEDED(hr) && m_pIEEvenHandler)
		{
			m_pIEEvenHandler->m_pParent = this;
			m_pIEEvenHandler->Init(spWebBrowser2);
		} 
	}
	else
	{
		if(m_pIEEvenHandler)
		{
			m_pIEEvenHandler->CleanUp();
			m_pIEEvenHandler->Release();
			m_pIEEvenHandler = NULL;
		}
	} 
    return hr;
}

void CIEFTPPlugin::CheckNagScreen()
{
	time_t tm;
	time(&tm);

	CString strFilePath;
	GetSystemDirectory(strFilePath.GetBuffer(MAX_PATH),MAX_PATH);
	strFilePath.ReleaseBuffer();
	strFilePath += "\\";
	strFilePath += APP_FILE;

	CString strData = ReadEncryptedFile(strFilePath,_T(ENCRYPT_KEY));
	BOOL bExpired = (ParseXML(_T("Expired"),strData) == "TRUE");

	CString strInstallTime = ParseXML(_T("InstallTime"),strData);
	time_t tmTimeInstall;
	if(!strInstallTime.IsEmpty())
		tmTimeInstall = (long)atol(strInstallTime);
	else
		tmTimeInstall = (long)MyGetProfileInt("id",0);

	time_t tspan = tm - tmTimeInstall;
	DWORD dwDays = (long)tspan / 60;
	dwDays = dwDays / 60;
	dwDays = dwDays / 24;

	if(bExpired || dwDays > 29)
	{
		m_bHasExpired = true;
		// mark as expired
		if(!bExpired)
		{
			strData = ReplaceXML("TRUE","Expired",strData);
			WriteEncryptedFile(strFilePath,ENCRYPT_KEY,strData);
		}
		time_t tmNag = MyGetProfileInt("ln",0);
		tspan = tm - tmNag;
		dwDays = (long)tspan / 60;
		dwDays = dwDays / 60;
		dwDays = dwDays / 24;
		// pop up message 1 time per day
		if(dwDays >= 1)
		{
			MyWriteProfileInt("ln",(DWORD)tm);
			// set nag timer
			m_nTimer = SetTimer(ID_NAG,300);
		}
	}
}

LRESULT CIEFTPPlugin::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if(wParam == ID_NAG)
	{
		KillTimer(m_nTimer);
		CNagDlg dlg;
		if(dlg.DoModal() == IDYES)
		{
			LoadURL(GetRegisterURL());
		}
		if(IsRegistered())
			m_bHasExpired = false;
	}
	return S_OK;
}

BOOL CIEFTPPlugin::LoadURL(CString strURL,CString strName,CString strLocalPath)
{
	if(m_spWebBrowser2 == NULL)
		return false;

	HRESULT hr = S_OK;
	VARIANT varEmpty;
	varEmpty.vt = VT_NULL;
	// convert CString to a COleVariant
	CComBSTR bstrURL(strURL);
	VARIANT vaURL;
	vaURL.vt = VT_BSTR;
	vaURL.bstrVal = bstrURL;

	if(!strName.IsEmpty())
	{
		CString strText = "Connecting to " + strName + "...";
		CComBSTR bstrText = strText;
		m_spWebBrowser2->put_StatusText(bstrText);
		SHANDLE_PTR hWnd;
		m_spWebBrowser2->get_HWND(&hWnd);
		if(::IsWindow((HWND)hWnd))
			::SetWindowText((HWND)hWnd,strText); 
	}

	hr = m_spWebBrowser2->Navigate2(&vaURL,&varEmpty,&varEmpty,&varEmpty,&varEmpty);
	if(hr == S_OK)
		m_strCurrentURL = strURL;
	else
		m_strCurrentURL = "";

	// load windows explorer if applicable
	if(!strLocalPath.IsEmpty() && (MyGetProfileInt("PopupWinExplorer",1) == 1))
	{
		m_strLocalPathToLoad = strLocalPath;

		DWORD dwThreadId = 0; 
		HANDLE hThread; 
		hThread = CreateThread(NULL, 0, RunWindowsExplorerThread,this,0,&dwThreadId); 
		CloseHandle(hThread); 
	}
	return (hr == S_OK);
}

DWORD WINAPI RunWindowsExplorerThread(LPVOID pParam)
{
	CIEFTPPlugin* pParent = (CIEFTPPlugin*)pParam;
	ShellExecute(NULL, NULL, pParent->m_strLocalPathToLoad, NULL, NULL, SW_SHOWNORMAL);
	return 0;
}

// change dir to
void CIEFTPPlugin::ChangeFTPDir(CString strDir)
{
	if(m_spWebBrowser2 == NULL)
		return;

	CString strURL = m_strCurrentURL;
	int nPos = -1;
	if((nPos = strURL.Find("://")) != -1)
	{
		strURL = strURL.Mid(nPos + (int)strlen("://"));
		if((nPos = strURL.Find("/")) != -1)
		{
			strURL = strURL.Left(nPos);
		}
	}
	strURL = "ftp://" + strURL + "/%2F" + strDir;
	HRESULT hr = S_OK;
	VARIANT varEmpty;
	varEmpty.vt = VT_NULL;
	// convert CString to a COleVariant
	CComBSTR bstrURL(strURL);
	VARIANT vaURL;
	vaURL.vt = VT_BSTR;
	vaURL.bstrVal = bstrURL;

	hr = m_spWebBrowser2->Navigate2(&vaURL,&varEmpty,&varEmpty,&varEmpty,&varEmpty);
}
