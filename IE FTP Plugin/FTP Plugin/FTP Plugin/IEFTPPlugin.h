// IEFTPPlugin.h : Declaration of the CIEFTPPlugin

#pragma once
#include "resource.h"       // main symbols

#include "FTPPlugin.h"
#include "MyToolbars.h"
#include "IEEvenHandler.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CIEFTPPlugin

class ATL_NO_VTABLE CIEFTPPlugin :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIEFTPPlugin, &CLSID_IEFTPPlugin>,
	public IDeskBand,
	public CWindowImpl<CIEFTPPlugin,CAxWindow>,
	public IObjectWithSiteImpl<CIEFTPPlugin>,
	public IDispatchImpl<IIEFTPPlugin, &IID_IIEFTPPlugin, &LIBID_FTPPluginLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CIEFTPPlugin();	

DECLARE_REGISTRY_RESOURCEID(IDR_IEFTPPLUGIN)


BEGIN_COM_MAP(CIEFTPPlugin)
	COM_INTERFACE_ENTRY(IIEFTPPlugin)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IID(IID_IDeskBand, IDeskBand)
	COM_INTERFACE_ENTRY(IObjectWithSite)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_MSG_MAP(CIEFTPPlugin)
        MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		CHAIN_MSG_MAP_MEMBER(m_wndToolBar)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);

	STDMETHODIMP SetSite(IUnknown *pUnkSite);
	HRESULT ManageBrowserConnection(BOOL bAdvise,IWebBrowser2* spWebBrowser2);

	// IDeskBand
	STDMETHOD(GetBandInfo)(DWORD dwBandID, DWORD dwViewMode, DESKBANDINFO* pdbi);
	// IOleWindow
	STDMETHOD(GetWindow)(HWND* phwnd);
	STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode);
	// IDockingWindow
	STDMETHOD(CloseDW)(unsigned long dwReserved);
	STDMETHOD(ResizeBorderDW)(const RECT* prcBorder, IUnknown* punkToolbarSite, BOOL fReserved);
	STDMETHOD(ShowDW)(BOOL fShow);

	// change dir to
	void ChangeFTPDir(CString strDir);
	CString m_strLocalPathToLoad;
	BOOL LoadURL(CString strURL,CString strName = _T(""), CString strLocalPath = _T(""));
	BOOL RegisterAndCreateWindow();
	void CheckNagScreen();

public:
	BOOL m_bShow;
	HWND m_hWndParent;
	HWND m_hWnd;
	// toobar window
	CMyToolbars	m_wndToolBar;

	// currently loaded URL
	CString m_strCurrentURL;
	// handler for IE events
	CComObject<CIEEvenHandler>* m_pIEEvenHandler;
	IUnknown* m_pUnkSite;
	// IWebBrowser2 pointer
	IWebBrowser2* m_spWebBrowser2; 
	// trial expired
	BOOL m_bHasExpired;
	UINT_PTR	m_nTimer;
};

OBJECT_ENTRY_AUTO(__uuidof(IEFTPPlugin), CIEFTPPlugin)
