// HtmlEvenHandler.cpp : Implementation of CHtmlEvenHandler

#include "stdafx.h"
#include "ReadToMe.h"
#include "HtmlEvenHandler.h"

// CHtmlEvenHandler
CHtmlEvenHandler::CHtmlEvenHandler(void)
{
	m_hrConnected = CONNECT_E_CANNOTCONNECT;
	m_dwCookie = 0;
	m_dwCookie2 = 0;
	m_dwCookie3 = 0;
	m_cRef = 0;
	m_dwRef = 0;
	m_pParent = NULL;
	m_pCP = NULL;
	m_pCP2 = NULL;
	m_pCP3 = NULL;
}

CHtmlEvenHandler::~CHtmlEvenHandler()
{
	CleanUp();
}

LRESULT CHtmlEvenHandler::CleanUp()
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
	if(m_pCP2)
	{
		if (m_dwCookie2)
		{
			hr = m_pCP2->Unadvise(m_dwCookie2);
			m_dwCookie2 = 0;
		}
		m_pCP2->Release();
		m_pCP2 = NULL;
	}
	if(m_pCP3)
	{
		if (m_dwCookie3)
		{
			hr = m_pCP3->Unadvise(m_dwCookie3);
			m_dwCookie3 = 0;
		}
		m_pCP3->Release();
		m_pCP3 = NULL;
	}
	return NOERROR;
}

STDMETHODIMP CHtmlEvenHandler::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags,
							 DISPPARAMS* pDispParams, VARIANT* pvarResult,
							 EXCEPINFO*  pExcepInfo,  UINT* puArgErr)
{
	if (!pDispParams)
		return E_INVALIDARG;
	HRESULT hr = S_OK;
	switch (dispidMember)
	{
		//
		// The parameters for this DISPID are as follows:
		// [0]: Cancel flag  - VT_BYREF|VT_BOOL
		// [1]: IDispatch* - Pointer to an IDispatch interface. 
		//		You can set this parameter to the IDispatch of 
		//		a WebBrowser Control that you've created. When 
		//		you pass back an IDispatch like this, MSHTML will 
		//		use the control you've given it to open the link.
		//
		// If you cancel here, ALL popups will be blocked.
		// This will also block links that open a new window and
		// opening a link in a new window via the context menu.
		// Popup blocker gives finer control of this feature via
		// the m_bBlockNewWindow flag and hot key override.
		//
	// stop auto scroll from scroll event
	case DISPID_HTMLWINDOWEVENTS2_ONSCROLL:
	{
		if(m_pParent)
			m_pParent->StopAutoScroll();
		break;
	}
	// stop auto scroll from mousewheel event
	case DISPID_HTMLDOCUMENTEVENTS2_ONMOUSEWHEEL:
	{
		if(m_pParent)
			m_pParent->StopAutoScroll();
		break;
	}
	case DISPID_NEWWINDOW2:
		ATLTRACE(_T("(%ld) DISPID_NEWWINDOW2\n"), ::GetCurrentThreadId());
		{
		}
		break;

		//
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
		ATLTRACE(_T("(%ld) DISPID_BEFORENAVIGATE2\n"), ::GetCurrentThreadId());
		{
			if(m_pParent && m_pParent->IsWindow())
			{
				m_pParent->SendMessage(MY_MSG_STOP_SPEAKING);
			}
		}
		break;

	case DISPID_HTMLDOCUMENTEVENTS2_ONCLICK:
		{
			ATLTRACE("DISPID_HTMLDOCUMENTEVENTS2_ONCLICK\n");
			break;
		}

	case DISPID_HTMLDOCUMENTEVENTS2_ONDBLCLICK:
		{
			ATLTRACE("DISPID_HTMLDOCUMENTEVENTS2_ONDBLCLICK\n");	
			CComPtr<IDispatch> spDisp = pDispParams->rgvarg[0].pdispVal;
			if(spDisp)
			{
				// IHTMLEventObj
				CComQIPtr<IHTMLEventObj, &IID_IHTMLEventObj> spEventObj(spDisp);
				if (spEventObj)
				{						
					CComPtr<IHTMLElement> spElem;
					hr = spEventObj->get_srcElement(&spElem);
					// IHTMLElement
					if(SUCCEEDED(hr) && spElem)
					{
						CComBSTR bsTagName;
						spElem->get_tagName(&bsTagName);
						bsTagName.ToUpper();
						if(bsTagName == "A" || bsTagName == "IMG")
							break;
					}					
				}
			}
			// start playing from this position
			if(m_pParent)
			{
				m_pParent->m_bPaused = false;
				m_pParent->m_nOffset = 0;			
				m_pParent->PostMessage(MY_MSG_DOUBLE_CLICK);
			}
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
				m_pParent->SendMessage(MY_MSG_STOP_SPEAKING);
			}
		}
		break;

	case DISPID_NAVIGATECOMPLETE2:
		ATLTRACE(_T("(%ld) DISPID_NAVIGATECOMPLETE2\n"), ::GetCurrentThreadId());
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
		{
			ATLTRACE("DISPID_DOCUMENTCOMPLETE\n");
			CComPtr<IDispatch> spDisp = pDispParams->rgvarg[1].pdispVal;
			if(spDisp)
			{
				CComQIPtr<IWebBrowser2, &IID_IWebBrowser2> pBrowser(spDisp);
				CComPtr<IDispatch> pHtmlDocDispatch;
				if(pBrowser)
					hr = pBrowser->get_Document(&pHtmlDocDispatch); 
				CComQIPtr<IHTMLDocument2, &IID_IHTMLDocument2> pHtmlDoc2(pHtmlDocDispatch);	
				if(pHtmlDoc2)
					Init(pHtmlDoc2);
			}
			break;
		}
		// No parameters
		//
		// Fires when a navigation operation is beginning.
		//
	case DISPID_DOWNLOADBEGIN:
		ATLTRACE(_T("(%ld) DISPID_DOWNLOADBEGIN\n"), ::GetCurrentThreadId());
		break;
		
		//
		// No parameters
		//
		// Fires when a navigation operation finishes, is halted, or fails.
		//
	case DISPID_DOWNLOADCOMPLETE:
		ATLTRACE(_T("(%ld) DISPID_DOWNLOADCOMPLETE\n"), ::GetCurrentThreadId());
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
		if(m_pParent && m_pParent->IsWindow())
		{
			BOOL bHandled = true;
			m_pParent->OnStop(NULL,NULL,NULL,bHandled);
		}
		CleanUp();
		break;

	default:
		break;
   } 
   
   return S_OK;
}

HRESULT CHtmlEvenHandler::Init(IWebBrowser2* pBrowser)
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

HRESULT CHtmlEvenHandler::Init(IHTMLDocument2* pDoc2)
{	
	HRESULT hr = NOERROR;
	// clean up
	if(m_pCP2)
	{
		if (m_dwCookie2)
		{
			hr = m_pCP2->Unadvise(m_dwCookie2);
			m_dwCookie2 = 0;
		}
		m_pCP2->Release();
		m_pCP2 = NULL;
	}
	// clean up
	if(m_pCP3)
	{
		if (m_dwCookie3)
		{
			hr = m_pCP3->Unadvise(m_dwCookie3);
			m_dwCookie3 = 0;
		}
		m_pCP3->Release();
		m_pCP3 = NULL;
	}
	// advice new sink
	LPCONNECTIONPOINTCONTAINER pCPC = NULL;
	hr = pDoc2->QueryInterface(IID_IConnectionPointContainer, (LPVOID*)&pCPC);
	if(SUCCEEDED(hr))
	{		
		hr = pCPC->FindConnectionPoint(DIID_HTMLDocumentEvents2, &m_pCP2);
		if(SUCCEEDED(hr))
			hr = m_pCP2->Advise(reinterpret_cast<IUnknown*>(this),&m_dwCookie2);		
	}	

	CComPtr<IHTMLWindow2> pWindow2;
	hr = pDoc2->get_parentWindow(&pWindow2);
	if(pWindow2)
	{
		//HTMLWindowEvents2
		hr = pWindow2->QueryInterface(IID_IConnectionPointContainer, (LPVOID*)&pCPC);
		if(SUCCEEDED(hr))
		{		
			hr = pCPC->FindConnectionPoint(DIID_HTMLWindowEvents2, &m_pCP3);
			if(SUCCEEDED(hr))
				hr = m_pCP3->Advise(reinterpret_cast<IUnknown*>(this),&m_dwCookie3);		
		}		
	}
	SAFERELEASE(pCPC);
	return hr;
}

