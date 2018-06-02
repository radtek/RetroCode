#include "StdAfx.h"
#include "IEFTPPlugin.h"
#include "IEEvenHandler.h"

#define SAFERELEASE(obj) if(obj) obj->Release()

CIEEvenHandler::CIEEvenHandler(void)
{
	m_hrConnected = CONNECT_E_CANNOTCONNECT;
	m_dwCookie = 0;
	m_cRef = 0;
	m_dwRef = 0;
	m_pParent = NULL;
	m_pCP = NULL;
}

CIEEvenHandler::~CIEEvenHandler(void)
{
	CleanUp();
}

LRESULT CIEEvenHandler::CleanUp()
{
	HRESULT hr = NOERROR;
	if(m_pCP)
	{
		if (m_dwCookie)
		{
			hr = m_pCP->Unadvise(m_dwCookie);
			m_dwCookie = 0;
		}
		m_pCP->Release();
		m_pCP = NULL;
	}
	return NOERROR;
}

STDMETHODIMP CIEEvenHandler::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags,
							 DISPPARAMS* pDispParams, VARIANT* pvarResult,
							 EXCEPINFO*  pExcepInfo,  UINT* puArgErr)
{
	if (!pDispParams)
		return E_INVALIDARG;
	HRESULT hr = S_OK;
	switch (dispidMember)
	{
		case DISPID_HTMLWINDOWEVENTS2_ONSCROLL:
		{
			break;
		}
		case DISPID_NEWWINDOW2:
		{
			break;
		}

		// The parameters for this DISPID are as follows:
		// [0]: Cancel flag  - VT_BYREF|VT_BOOL
		// [1]: HTTP headers - VT_BYREF|VT_VARIANT
		// [2]: Address of HTTP POST data  - VT_BYREF|VT_VARIANT 
		// [3]: Target frame name - VT_BYREF|VT_VARIANT 
		// [4]: Option flags - VT_BYREF|VT_VARIANT
		// [5]: URL to navigate to - VT_BYREF|VT_VARIANT
		// [6]: An object that evaluates to the top-level or frame
		//      WebBrowser object corresponding to the event. 
		// 
		// User clicked a link or launched the browser.
		//
		case DISPID_BEFORENAVIGATE2:
		{
			break;
		}
		case DISPID_HTMLDOCUMENTEVENTS2_ONCLICK:
		{
			break;
		}
		case DISPID_HTMLDOCUMENTEVENTS2_ONDBLCLICK:
		{
			break;
		}
		//
		// The parameters for this DISPID:
		// [0]: URL navigated to - VT_BYREF|VT_VARIANT
		// [1]: An object that evaluates to the top-level or frame
		//      WebBrowser object corresponding to the event. 
		//
		// Fires after a navigation to a link is completed on either 
		// a window or frameSet element.
		//

		case DISPID_HTMLDOCUMENTEVENTS2_ONSTOP:
		{
			if(m_pParent && m_pParent->IsWindow())
			{
			//	m_pParent->LoadURL(_T("about:blank"));
			}
			break;
		}
		case DISPID_NAVIGATECOMPLETE2:
		break;
		//
		// The parameters for this DISPID:
		// [0]: New status bar text - VT_BSTR
		//
		case DISPID_STATUSTEXTCHANGE:
		break;
		//
		// The parameters for this DISPID:
		// [0]: Maximum progress - VT_I4
		// [1]: Amount of total progress - VT_I4
		//
		case DISPID_PROGRESSCHANGE:
		break;

		//
		// The parameters for this DISPID:
		// [0]: URL navigated to - VT_BYREF|VT_VARIANT
		// [1]: An object that evaluates to the top-level or frame
		//      WebBrowser object corresponding to the event. 
		//
		// Fires when a document has been completely loaded and initialized.
		// Unreliable -- currently, the DWebBrowserEvents2::DocumentComplete 
		// does not fire when the IWebBrowser2::Visible property of the 
		// WebBrowser Control is set to false (see Q259935).  Also, multiple 
		// DISPID_DOCUMENTCOMPLETE events can be fired before the final 
		// READYSTATE_COMPLETE (see Q180366).
		//
		case DISPID_DOCUMENTCOMPLETE:
		break;
		// No parameters
		//
		// Fires when a navigation operation is beginning.
		//
		case DISPID_DOWNLOADBEGIN:
		break;
		//
		// No parameters
		//
		// Fires when a navigation operation finishes, is halted, or fails.
		//
		case DISPID_DOWNLOADCOMPLETE:
		break;
		
		//
		// The parameters for this DISPID:
		// [0]: Enabled state - VT_BOOL
		// [1]: Command identifier - VT_I4
		//
		case DISPID_COMMANDSTATECHANGE:
		break;
		
		//
		// The parameters for this DISPID:
		// [0]: Document title - VT_BSTR
		// [1]: An object that evaluates to the top-level or frame
		//      WebBrowser object corresponding to the event.
		//
		case DISPID_TITLECHANGE:
		break;
		
		//
		// The parameters for this DISPID:
		// [0]: Name of property that changed - VT_BSTR
		//
		case DISPID_PROPERTYCHANGE:
		break;

		//
		// No parameters
		//
		// The BHO docs in MSDN say to use DISPID_QUIT, but this is an error.
		// The BHO never gets a DISPID_QUIT and thus the browser connection
		// never gets unadvised and so the BHO never gets the FinalRelease().
		// This is bad.  So use DISPID_ONQUIT instead and everything is cool --
		// EXCEPT when you exit the browser when viewing a page that launches
		// a popup in the onunload event!  In that case the BHO is already
		// unadvised so it does not intercept the popup.  So the trick is to
		// navigate to a known page (I used the about:blank page) that does 
		// not have a popup in the onunload event before unadvising.
		//
		case DISPID_ONQUIT:
		// Unadvise
		CleanUp();
		break;

		default:
		break;
   } 
   
   return S_OK;
}

HRESULT CIEEvenHandler::Init(IWebBrowser2* pBrowser)
{	
	HRESULT hr = NOERROR;
	// clean up
	if(m_pCP)
	{
		if(m_dwCookie)
		{
			hr = m_pCP->Unadvise(m_dwCookie);
			m_dwCookie = 0;
		}
		m_pCP->Release();
		m_pCP = NULL;
	}
	// advice new web browser
	LPCONNECTIONPOINTCONTAINER pCPC = NULL;
	hr = pBrowser->QueryInterface(IID_IConnectionPointContainer, (LPVOID*)&pCPC);
	if(SUCCEEDED(hr))
	{
		hr = pCPC->FindConnectionPoint(DIID_DWebBrowserEvents2, &m_pCP);
		if(SUCCEEDED(hr))
			m_hrConnected = m_pCP->Advise(reinterpret_cast<IUnknown*>(this),&m_dwCookie);
	}	
	SAFERELEASE(pCPC);	
	return hr;
}

