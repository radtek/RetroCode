// ReadToMe.cpp : Implementation of CReadToMe

#include "stdafx.h"
#include "HtmlEvenHandler.h"
#include "MyBrowserEvents.h"
#include "MySpeechCtl.h"
#include "SettingsDlg.h"
#include "mytoolbars.h"
#include "ReadToMe.h"
#include "helpers.h"
#include ".\readtome.h"
#include "NagDlg.h"
#include "DClickPlayMsgDialog.h"

// CReadToMe
CReadToMe::CReadToMe()
{
	m_dwBandID = 0;
	m_dwViewMode = 0;
	m_bShow = false;
	m_hWndParent = NULL;
	m_hWnd = NULL;
	m_pHtmlEvenHandler = NULL;
	m_pUnkSite = NULL;
	m_pSpeechCtl = NULL;
	m_bStopped = false;
	m_bPaused = false;
	m_bAutoScrollText = true;
	m_nOffset = 0;
	m_spWebBrowser2 = NULL;
	m_bIsUsingSelectedText = false;
	m_bFirstPlay = true;
	m_lPrevCarrotPosMin = 0;
	m_nCurrentFramePlaying = 0;
	m_pLastTxtRange = NULL;
	m_pPrevSelectSegment = NULL;
	m_bScrollingIntoView = false;
	m_bCheckJunkWords = false;
	m_bIgnoreHyperlinks = false;
	m_nLastFoundOffset = 0;
	LoadJunkWordsList();
	m_bAutoScrollTextRegistry = (MyGetProfileInt("AutoScrollText",1) == 1);
	m_bHasExpired = false;
}

CReadToMe::~CReadToMe()
{	
	CleanUpTxtRanges();

	if(m_pHtmlEvenHandler)
	{
		m_pHtmlEvenHandler->CleanUp();
		m_pHtmlEvenHandler->Release();
		m_pHtmlEvenHandler = NULL;
	}	
	if(m_pSpeechCtl)
	{
		if(m_pSpeechCtl->IsPlaying())
			m_pSpeechCtl->Stop();
		m_bStopped = true;
		if(m_pSpeechCtl->IsWindow())
			m_pSpeechCtl->DestroyWindow();
		delete m_pSpeechCtl;
		m_pSpeechCtl = NULL;
	}
	SAFERELEASE(m_pPrevSelectSegment);
	SAFERELEASE(m_pLastTxtRange);
	SAFERELEASE(m_pUnkSite);
	SAFERELEASE(m_spWebBrowser2);
}

LRESULT CReadToMe::OnDoubleClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// double click to speak
	if(IsWindow() && (MyGetProfileInt("DoubleClickPlay",1) == 1))
	{
		PostMessage(MY_WM_PLAY_FROM_POS,(WPARAM)m_nOffset, 0);
	}
	bHandled = true;
	return S_OK;
}

// IOleObjectWithSite Methods
STDMETHODIMP CReadToMe::SetSite(IUnknown *pUnkSite)
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
			// create speech control
			if(m_pSpeechCtl)
			{
				delete m_pSpeechCtl;
				m_pSpeechCtl = NULL;
			}
			m_pSpeechCtl = new CMySpeechCtl();
			if(!InitializeSpeechControl())
			{
				MessageBox("Error initializing speech control.");
			} 
			// check registration expired
			if(!IsRegistered())
			{
				CheckNagScreen();
			}
		}
        // Query pUnkSite for the IWebBrowser2 interface.
		IServiceProviderPtr pSP = pUnkSite;
		HRESULT hr = pSP->QueryService(SID_SWebBrowserApp, IID_IWebBrowser2, (void**)&m_spWebBrowser2);
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

// Funnel web browser events through this class
HRESULT CReadToMe::ManageBrowserConnection(BOOL bAdvise,IWebBrowser2* spWebBrowser2)
{
	HRESULT hr = S_OK;
    ATLASSERT(spWebBrowser2);
    if (!spWebBrowser2)
        return S_OK;

	if(bAdvise)
	{			
		if(m_pHtmlEvenHandler)
		{
			m_pHtmlEvenHandler->CleanUp();
			m_pHtmlEvenHandler->Release();
			m_pHtmlEvenHandler = NULL;
		}
		hr = CComObject<CHtmlEvenHandler>::CreateInstance(&m_pHtmlEvenHandler);
		m_pHtmlEvenHandler->AddRef();
		if(SUCCEEDED(hr) && m_pHtmlEvenHandler)
		{
			m_pHtmlEvenHandler->m_pParent = this;
			m_pHtmlEvenHandler->Init(spWebBrowser2);
		} 
	}
	else
	{
		if(m_pHtmlEvenHandler)
		{
			m_pHtmlEvenHandler->CleanUp();
			m_pHtmlEvenHandler->Release();
			m_pHtmlEvenHandler = NULL;
		}
	} 
    return hr;
}

// IDeskBand
STDMETHODIMP CReadToMe::GetBandInfo(DWORD dwBandID, DWORD dwViewMode, DESKBANDINFO* pdbi)
{
	USES_CONVERSION;

	m_dwBandID = dwBandID;
	m_dwViewMode = dwViewMode;

	if (pdbi)
	{
		if (pdbi->dwMask & DBIM_MINSIZE)
		{
			pdbi->ptMinSize.x = 100;
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
			pdbi->ptActual.x = 100;
			pdbi->ptActual.y = TB_HEIGHT;
		}
		if (pdbi->dwMask & DBIM_TITLE)
		{
			//wcscpy(pdbi->wszTitle, A2W(MY_APP_NAME));			
		}
		if (pdbi->dwMask & DBIM_BKCOLOR)
		{
			//Use the default background color by removing this flag.
			pdbi->dwMask &= ~DBIM_BKCOLOR;
		}
		if (pdbi->dwMask & DBIM_MODEFLAGS)
		{
			//pdbi->dwModeFlags = DBIMF_DEBOSSED |  0x0080 | ;
			pdbi->dwModeFlags = DBIMF_NORMAL;
		}
	}
	return S_OK;
}

// IOleWindow
STDMETHODIMP CReadToMe::GetWindow(HWND* phwnd)
{
	HRESULT hr = S_OK;
	if (NULL == phwnd)
		hr = E_INVALIDARG;
	else
		*phwnd = m_hWnd;
	return hr;
}

STDMETHODIMP CReadToMe::ContextSensitiveHelp(BOOL fEnterMode)
{
	return S_OK;
}

// IDockingWindow
STDMETHODIMP CReadToMe::CloseDW(unsigned long dwReserved)
{
	if (::IsWindow(m_hWnd))
		::DestroyWindow(m_hWnd);
	return S_OK;
}

STDMETHODIMP CReadToMe::ResizeBorderDW(const RECT* prcBorder, IUnknown* punkToolbarSite, BOOL fReserved)
{
	return E_NOTIMPL;
}

STDMETHODIMP CReadToMe::ShowDW(BOOL fShow)
{
	HRESULT hr = S_OK;
	m_bShow = fShow;
	::ShowWindow(m_hWnd, m_bShow ? SW_SHOW : SW_HIDE);
	return S_OK;	
}

// stop auto scroll
void CReadToMe::StopAutoScroll()
{
	if(m_bScrollingIntoView)
		return;
	m_bAutoScrollText = false;
	if(m_nTimerResumeAutoScroll)
		KillTimer(m_nTimerResumeAutoScroll);
	int nSecs = MyGetProfileInt("AutoResumeScrollTime",10);
	m_nTimerResumeAutoScroll = SetTimer(ID_RESUME_AUTOSCROLL,nSecs*1000,NULL);	
}

// clean up all text range objects
void CReadToMe::CleanUpTxtRanges(void)
{
	SAFERELEASE(m_pLastTxtRange);
	// clean up all text range objects
	for(size_t n=0;n<m_aTextRanges.GetCount();n++)
	{
		IHTMLTxtRange* piTextRange = m_aTextRanges.GetAt(n);
		if(piTextRange)
			piTextRange->Release();
	}
	m_aTextRanges.RemoveAll();
}

// get current char position from cursor position
int CReadToMe::GetCurrentPosition(void)
{	
	return m_lPrevCarrotPosMin;
}

CString CReadToMe::GetBufferedText()
{
	SAFERELEASE(m_pLastTxtRange);
	if(m_strDocumentText.IsEmpty())
		return GetText();
	else
		return m_strDocumentText;
}
	
// get text from passed document
CString CReadToMe::GetTextFromDocument(IHTMLDocument2* pHtmlDoc2,BOOL bSelectedText, BOOL bStoreRange)
{
	if(!pHtmlDoc2)
	{
		ATLTRACE("NULL error GetTextFromDocument(pHtmlDoc2)\n");
		return "";
	}
	HRESULT hr;
	CString strText;
	if(bSelectedText)
	{
		// try and get selection first
		IHTMLSelectionObject* pSelectionObj = NULL;
		hr = pHtmlDoc2->get_selection(&pSelectionObj);
		if(pSelectionObj)
		{
			IHTMLTxtRange* piTextRange = NULL;
			pSelectionObj->createRange((IDispatch**)&piTextRange);
			if(piTextRange)
			{
				CComBSTR bstr;
				hr = piTextRange->get_text(&bstr);
				strText = bstr;
				bool bIsEmpty = strText.IsEmpty();
				// less than 20 chars so do all text after this point
				if(!bIsEmpty && strText.GetLength() < 20) 
				{
					CComBSTR strRange = L"textedit";
					long lRes = 0;
					piTextRange->moveEnd(strRange,1,&lRes);
					hr = piTextRange->get_text(&bstr);
					strText = bstr;
				}
				// add to array
				if(!bIsEmpty)
				{					
					m_aTextRanges.Add(piTextRange);
				}
				else
				{
					SAFERELEASE(piTextRange);
				}
			}
		}
		SAFERELEASE(pSelectionObj);
	}
	else
	{
		IHTMLElement* pBodyElement = NULL; 
		hr = pHtmlDoc2->get_body(&pBodyElement);
		// body IHTMLElement
		if(pBodyElement)
		{
			// IHTMLBodyElement
			CComQIPtr<IHTMLBodyElement,&IID_IHTMLBodyElement> pHTMLBody(pBodyElement); 	
			if(pHTMLBody)
			{
				// create text range
				IHTMLTxtRange* piTextRange = NULL;
				hr = pHTMLBody->createTextRange(&piTextRange);
				if(piTextRange)
				{
					CComBSTR bstr;
					hr = piTextRange->get_text(&bstr); 
					strText = bstr;
					// add to array
					if(!strText.IsEmpty())
						m_aTextRanges.Add(piTextRange);
					else
						SAFERELEASE(piTextRange);
				}
			}
		}
		SAFERELEASE(pBodyElement);
	}
	return strText;
}

// enumerate all frames for Text
CString CReadToMe::EnumerateAllFrames(IHTMLDocument2* pHtmlDoc2,BOOL bSelectedText,BOOL bStoreRange)
{
	if(!pHtmlDoc2)
	{
		ATLTRACE("NULL error EnumerateAllFrames(pHtmlDoc2)\n");
		return "";
	}
	CString strText;
	HRESULT hr;
	if(pHtmlDoc2)
	{
		// check all frames
		long lSize = 0;
		// frames collection
		IHTMLFramesCollection2* pFramesColl = NULL;
		pHtmlDoc2->get_frames(&pFramesColl);
		if(pFramesColl)
		{
			VARIANT frameRequested;
			pFramesColl->get_length(&lSize);
			for(long n=0;n<lSize;n++)
			{
				frameRequested.vt = VT_I4;
				frameRequested.lVal = n;
				VARIANT frameOut;
				IHTMLWindow2* pFrameWindow = NULL;
				IHTMLDocument2* pFrameDoc = NULL;
				hr = pFramesColl->item(&frameRequested, &frameOut);
				hr = frameOut.pdispVal->QueryInterface(IID_IHTMLWindow2, (void**)&pFrameWindow);
				hr = pFrameWindow->get_document(&pFrameDoc);
				if(pFrameDoc)
				{
					// get text from this frame
					strText += GetTextFromDocument(pFrameDoc,bSelectedText,bStoreRange);
					// enumerate any child frames
					strText += EnumerateAllFrames(pFrameDoc,bSelectedText,bStoreRange);
				}
				SAFERELEASE(pFrameDoc);
				SAFERELEASE(pFrameWindow);
			}
		}
		SAFERELEASE(pFramesColl);
		// no frames
		if(lSize <= 1 || strText.IsEmpty())
			strText += GetTextFromDocument(pHtmlDoc2,bSelectedText,bStoreRange);
	}
	return strText;
}
	
// find exact text location
BOOL CReadToMe::MyFindText(IHTMLTxtRange* pDuplicate,CString strWord,CString strWordExtra,int nPosAjustment, BOOL bCanUseDupTest)
{
	if(!pDuplicate)
	{
		ATLTRACE("NULL error MyFindText(pDuplicate) word:%s\n",strWord);
		return false;
	}
	HRESULT hr;
	CComBSTR bstrBuf = NULL;
	long lChars = 0;
	CString strUnit = _T("character");
	CString strTest;
	if(nPosAjustment < 0)
		hr = pDuplicate->moveStart(strUnit.AllocSysString(),nPosAjustment,&lChars);
	else
		hr = pDuplicate->moveEnd(strUnit.AllocSysString(),nPosAjustment,&lChars);
	pDuplicate->get_text(&bstrBuf);
	strTest = bstrBuf;

	int nPos = -1;
	int nFoundPos = -1;
	// find match for word closest to right of stream
	while((nPos = strTest.Find(strWord)) != -1)
	{
		if(nFoundPos == -1)
			nFoundPos = 0;
		nFoundPos += nPos;

		// check extra HTML_PRE_CHAR_TEST chars before
		int nFindTest = 0;
		if(!strWordExtra.IsEmpty())
		{
			nFindTest = strTest.Find(strWordExtra);
			if(nFindTest == -1)
			{
				nFoundPos = -1;
				break;
			}	
		}
		if(nFindTest != -1)
		{
			strTest = strTest.Mid(nPos + strWord.GetLength());
			if(nPosAjustment > 0)
			{				
				break;
			}
		} 
	}
	// if found keep comparing till we match entire word
	if(nFoundPos != -1)
	{
		int nAdjustment = 0;
		// move to position it should be at
		hr = pDuplicate->moveStart(strUnit.AllocSysString(),nFoundPos,&lChars);
		hr = pDuplicate->collapse();
		hr = pDuplicate->moveEnd(strUnit.AllocSysString(),strWord.GetLength(),&lChars); 
		int nCounter = abs(nPosAjustment);
		BOOL bFindZero = false;
		do
		{				
			pDuplicate->get_text(&bstrBuf);
			strTest = bstrBuf;
			
			if(strTest == strWord)
			{
				// test that range is further to right of last word
				if(bCanUseDupTest && m_pLastTxtRange)
				{
					CComBSTR strHow = _T("StartToStart");
					long lCmp = 0;
					hr = m_pLastTxtRange->compareEndPoints(strHow,pDuplicate,&lCmp);
					if(lCmp > 0)
					{
						ATLTRACE("CompareEndPoints less than duplicate for %s\r\n",strWord);
						if(m_nLastFoundOffset == 0)
							m_nLastFoundOffset = nPosAjustment;
						return false;
					}
				}
				else if(!bCanUseDupTest)
				{
					ATLTRACE("CompareEndPoints ignored and word now found for %s\r\n",strWord);
				}
				SAFERELEASE(m_pLastTxtRange);
				hr = pDuplicate->duplicate(&m_pLastTxtRange);
				return true;
			}
			else
			{	
				int nFind = strTest.Find(strWord);
				// find in text
				if(nFind < 0)
				{
					hr = pDuplicate->moveStart(strUnit.AllocSysString(),-1,&lChars);
					hr = pDuplicate->moveEnd(strUnit.AllocSysString(),1,&lChars);
					nAdjustment --;
				}
				else if(nFind > 0)
				{
					hr = pDuplicate->moveStart(strUnit.AllocSysString(),nFind,&lChars);
					nAdjustment += nFind;
				}
				else if(nFind == 0)
				{					
					hr = pDuplicate->collapse();
					hr = pDuplicate->moveEnd(strUnit.AllocSysString(),bFindZero?strWord.GetLength()-1:strWord.GetLength(),&lChars); 
					bFindZero = true;
				}
			}
			nCounter --;
		} while(nCounter > 0);
	}
	return false;	
}

// get current url
BOOL CReadToMe::GetCurrentURL(CComBSTR& strURL,CComBSTR& strTitle)
{
	HRESULT hr;
	CComPtr<IWebBrowser2> pBrowser;	
	hr = QueryControl(IID_IWebBrowser2,(void**)&pBrowser);
	if(pBrowser)
	{
		hr = pBrowser->get_LocationURL(&strURL);
		hr = pBrowser->get_LocationName(&strTitle);
		return (SUCCEEDED(hr));			
	}
	return false;
}

// offset selected position by this number
void CReadToMe::SetPositionOffset(int nOffset)
{
	m_nOffset = nOffset;
}

// set render style based on user preferences
HRESULT CReadToMe::MySetRenderStyle(IHTMLRenderStyle* pStyle)
{
	HRESULT hr = S_OK;
	CComBSTR bStr;
	bStr = "false";
	hr = pStyle->put_defaultTextSelection(bStr);
	VARIANT col;
	col.vt = VT_BSTR;
	CString strTextCol = MyGetProfileString("UnderlineColor", "blue", 100);	
	bStr = strTextCol;
	col.bstrVal = bStr;
	hr = pStyle->put_textColor(col);
	bStr = "transparent";
	col.bstrVal = bStr;
	hr = pStyle->put_textBackgroundColor(col);
	bStr = "underline";
	col.bstrVal = bStr;
	hr = pStyle->put_textDecoration(bStr);

	return hr;
}

// show or hide caret
void CReadToMe::ShowCaret(BOOL bShow)
{
	HRESULT hr;
	// web browser object
	CComPtr<IWebBrowser2> pBrowser = NULL;	
	hr = QueryControl(IID_IWebBrowser2,(void**)&pBrowser);
	if(pBrowser)
	{		
		// document2 object
		IDispatch* pHtmlDocDispatch = NULL;
		CComPtr<IHTMLDocument2> pHtmlDoc2 = NULL;	
		hr = pBrowser->get_Document(&pHtmlDocDispatch); 
		if(pHtmlDocDispatch)
			hr = pHtmlDocDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&pHtmlDoc2); 
		if(pHtmlDoc2)
		{
			CComPtr<IDisplayServices> pIDisplay;
			hr = pHtmlDoc2->QueryInterface(IID_IDisplayServices, (void**)&pIDisplay); 
			if(pIDisplay)
			{				
				CComPtr<IHTMLCaret> pcaret;
				hr = pIDisplay->GetCaret(&pcaret);
				if(pcaret)
					pcaret->Show(bShow);
			}
		}
	}
}

// get the currently selected text
CString CReadToMe::GetSelectedText(void)
{
	HRESULT hr;
	CleanUpTxtRanges();

	m_bIsUsingSelectedText = true;
	CString strText;
	// web browser object
	IWebBrowser2* pBrowser = NULL;	
	hr = QueryControl(IID_IWebBrowser2,(void**)&pBrowser);
	if(pBrowser)
	{		
		// document2 object
		IDispatch* pHtmlDocDispatch = NULL;
		IHTMLDocument2* pHtmlDoc2 = NULL;	
		hr = pBrowser->get_Document(&pHtmlDocDispatch); 
		if(pHtmlDocDispatch)
			hr = pHtmlDocDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&pHtmlDoc2); 
		if(pHtmlDoc2) 
		{	
			// check all frames for selected text
			strText = EnumerateAllFrames(pHtmlDoc2,true,false);			
		}
		SAFERELEASE(pHtmlDoc2);
		SAFERELEASE(pHtmlDocDispatch);
	}
	SAFERELEASE(pBrowser);	

	return strText;
}

// reset to default state
void CReadToMe::ResetState(void)
{	
	// remove any old highlight
	HRESULT hr;
	IHighlightSegment* pHighlight = NULL;
	// web browser object
	if(m_spWebBrowser2)
	{		
		// document4 object
		IDispatch* pHtmlDocDispatch = NULL;
		hr = m_spWebBrowser2->get_Document(&pHtmlDocDispatch); 
		CComPtr<IHTMLDocument4> pHtmlDoc4 = NULL;	
		if(pHtmlDocDispatch)
			hr = pHtmlDocDispatch->QueryInterface(IID_IHTMLDocument4, (void**)&pHtmlDoc4); 
		if(pHtmlDoc4)
		{
			// IHighlightRenderingServices
			CComPtr<IHighlightRenderingServices> pRendering;
			hr = pHtmlDoc4->QueryInterface(IID_IHighlightRenderingServices, (void**)&pRendering);
			if(pRendering)
			{
				// remove last highlight
				if(m_pPrevSelectSegment)
				{
					pRendering->RemoveSegment(m_pPrevSelectSegment);
					SAFERELEASE(m_pPrevSelectSegment);					
				}
			}			
		}
		SAFERELEASE(pHtmlDocDispatch);
	}
	m_lPrevCarrotPosMin = 0;
	m_pLastTxtRange = NULL;
}

// is text visible on display
IHighlightSegment* CReadToMe::MySelectText(IHTMLTxtRange* pDuplicate)
{
	IHighlightSegment* pHighlight = NULL;
	HRESULT hr;
	// web browser object
	if(m_spWebBrowser2)
	{		
		// document4 object
		IDispatch* pHtmlDocDispatch = NULL;
		hr = m_spWebBrowser2->get_Document(&pHtmlDocDispatch); 
		CComPtr<IHTMLDocument4> pHtmlDoc4 = NULL;	
		if(pHtmlDocDispatch)
			hr = pHtmlDocDispatch->QueryInterface(IID_IHTMLDocument4, (void**)&pHtmlDoc4); 
		if(pHtmlDoc4)
		{
			// IHighlightRenderingServices
			CComPtr<IHighlightRenderingServices> pRendering;
			hr = pHtmlDoc4->QueryInterface(IID_IHighlightRenderingServices, (void**)&pRendering);
			if(pRendering)
			{
				// remove last highlight
				if(m_pPrevSelectSegment)
				{
					pRendering->RemoveSegment(m_pPrevSelectSegment);
					SAFERELEASE(m_pPrevSelectSegment);					
				}
				// check pDuplicate not null
				if(pDuplicate)
				{
					// Positions the beginning and end of a text range at the positions of two markup pointers
					CComPtr<IMarkupPointer> ppoint1;
					CComPtr<IMarkupPointer> ppoint2;
					// IMarkupServices
					CComPtr<IMarkupServices> pMarkupServices;
					hr = pHtmlDoc4->QueryInterface(IID_IMarkupServices, (void**)&pMarkupServices);
					if(pMarkupServices)
					{
						hr = pMarkupServices->CreateMarkupPointer(&ppoint1);
						hr = pMarkupServices->CreateMarkupPointer(&ppoint2);
						hr = pMarkupServices->MovePointersToRange(pDuplicate,ppoint1,ppoint2);
					}
					// highlight style
					CComPtr<IHTMLRenderStyle> pStyle;	
					hr = pHtmlDoc4->createRenderStyle(NULL,&pStyle);
					// select text 0 - none, 1 - select, 2 - underline
					int nSelectStyle = MyGetProfileInt("SelectText",2);
					if(nSelectStyle == 2)
						hr = MySetRenderStyle(pStyle);

					// IDisplayPointer
					CComPtr<IDisplayPointer> pDisPoint1;
					CComPtr<IDisplayPointer> pDisPoint2;
					// IDisplayServices
					CComPtr<IDisplayServices> pIDisplay;
					hr = pHtmlDoc4->QueryInterface(IID_IDisplayServices, (void**)&pIDisplay); 
					if(pIDisplay)
					{				
						hr = pIDisplay->CreateDisplayPointer(&pDisPoint1);
						hr = pIDisplay->CreateDisplayPointer(&pDisPoint2);
						if(pDisPoint1 && pDisPoint2)
						{
							hr = pDisPoint1->MoveToMarkupPointer(ppoint1,NULL);
							if(SUCCEEDED(hr))
							{
								hr = pDisPoint2->MoveToMarkupPointer(ppoint2,NULL);
								// Creates a highlight segment for the markup between two display pointers and highlights it according to a specified rendering style.
								if(SUCCEEDED(hr))
								{
									if(nSelectStyle != 0)
										hr = pRendering->AddSegment(pDisPoint1,pDisPoint2,pStyle,&pHighlight);
									// scroll into view
									if(m_bAutoScrollText && m_bAutoScrollTextRegistry)
									{
										m_bScrollingIntoView = true;
										hr = pDisPoint1->ScrollIntoView();
										if(hr != S_OK)
										{
											ATLTRACE("ScrollIntoView failed lasterror:%d\r\n",GetLastError());
										}
										m_bScrollingIntoView = false;
									}
								}
							}
						}
					}
				}
			}			
		}
		SAFERELEASE(pHtmlDocDispatch);
	}
	return pHighlight;
}

// my timer messages
LRESULT CReadToMe::OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(wParam == ID_RESUME_AUTOSCROLL)
	{
		KillTimer(m_nTimerResumeAutoScroll);
		m_nTimerResumeAutoScroll = NULL;
		m_bAutoScrollText = true;
	}
	else if(wParam == ID_NAG)
	{
		KillTimer(m_nTimerNag);
		CNagDlg dlg;
		if(dlg.DoModal() == IDYES)
		{
			LoadURL(GetRegisterURL());
		}
		if(IsRegistered())
		{
			m_bHasExpired = false;
		}
	}
	return 0;
}

// create and initialize speech control
BOOL CReadToMe::InitializeSpeechControl(void)
{
	if(m_pSpeechCtl)
	{
		m_pSpeechCtl->m_hWndEdit = m_hWnd;
		if(m_pSpeechCtl->Create(m_hWnd, rcDefault, NULL, WS_CHILD) != NULL)
			return m_pSpeechCtl->InitializeSpeechControl();
	}
	return false;
}

// stop any speech
LRESULT CReadToMe::OnStopSpeaking(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	OnStop(NULL,NULL,NULL,bHandled);
	m_nOffset = 0;
	bHandled = true;
	return 0L;
}

// end of speech stream
LRESULT CReadToMe::OnMyEndOfTextStream(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(!m_bStopped)
	{
		ResetState();
		m_bFirstPlay = true;
	}
	m_bStopped = true;
	return 0;
}

LRESULT CReadToMe::OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	if(m_wndToolBar.IsWindow())
		m_wndToolBar.MoveWindow(0,0,x,22);
	return 0;
}

// play from this position
LRESULT CReadToMe::OnPlayFromPos(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(m_pSpeechCtl)
	{
		if(m_pSpeechCtl->IsPlaying())
		{
			m_pSpeechCtl->Stop();
		}
		m_bStopped = false;
		m_bAutoScrollText = true;
		// check for expired trial
		if(m_bHasExpired)
		{
			m_nTimerNag = SetTimer(ID_NAG,300);
			return 0;
		}
		// Get the text from the view window
		CString strBuf = GetText();
		int nCharPos = (int)wParam;
		strBuf = strBuf.Mid(nCharPos);
		if(!strBuf.IsEmpty() && !m_pSpeechCtl->Play(strBuf))
		{
			MessageBox(_T("Error, failed to speak selected text."));
		}
	}
	return S_OK;
}

LRESULT CReadToMe::OnPlay(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(m_bPaused)
	{
		m_bPaused = false;
		return OnPause(wNotifyCode, wID, hWndCtl, bHandled);
	}
	if(m_pSpeechCtl)
	{
		if(m_pSpeechCtl->IsPlaying())
		{
			MessageBox(_T("Please click stop first. Then double click the text you would want to start speaking from."),MY_APP_NAME,MB_OK);
			return S_OK;
		}
		// check for expired trial
		if(m_bHasExpired)
		{
			m_nTimerNag = SetTimer(ID_NAG,300);
			return 0;
		}
		// Get the text from the view window
		CString strBuf = GetText();
		m_bStopped = false;

		// advise user they can double click to play text
		if(!m_bIsUsingSelectedText)
		{
			if(MyGetProfileInt("ShowDClickDlgMsg",1) == 1)
			{
				CDClickPlayMsgDialog dlg;
				dlg.DoModal();
			}
		}
		// check if start playing from cursor position
		BOOL bPlayFromCursorPos = (MyGetProfileInt("PlayFromCursor",1) == 1);		
		if(!m_bFirstPlay && bPlayFromCursorPos)
		{
			int nCharPos = 0;
			nCharPos = GetCurrentPosition();
			SetPositionOffset(nCharPos);			
			strBuf = strBuf.Mid(nCharPos);
		}
		else
			m_bFirstPlay = false;
		if(!strBuf.IsEmpty() && !m_pSpeechCtl->Play(strBuf))
		{
			MessageBox(_T("Error, failed to speak selected text."));
		}
	}
	bHandled = true;
	return S_OK;
}

// stop speech
LRESULT CReadToMe::OnStop(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled)
{
	if(m_pSpeechCtl)
	{
		m_bPaused = false;
		m_bStopped = true;
		m_nOffset = 0;			
		if(!m_pSpeechCtl->Stop())
			MessageBox(_T("Error, failed to stop speech engine."));
		ResetState();
	}
	bHandled = true;
	return S_OK;
}

// stop speech
LRESULT CReadToMe::OnPause(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled)
{
	if(m_pSpeechCtl)
	{
		if(m_pSpeechCtl->IsPlaying())
		{
			m_bStopped = true;
			m_bPaused = true;
			if(!m_pSpeechCtl->Stop())
				MessageBox(_T("Error, failed to pause speech engine."));
		}
		else
		{
			// check for expired trial
			if(m_bHasExpired)
			{
				m_nTimerNag = SetTimer(ID_NAG,300);
				return 0;
			}
			int nCharPos = GetCurrentPosition();
			CString strBuf = GetBufferedText();
			strBuf = strBuf.Mid(nCharPos);
			SetPositionOffset(nCharPos);
			if(!m_pSpeechCtl->Play(strBuf))
				MessageBox(_T("Error, failed to pause speech engine."));
		}
	}
	bHandled = true;
	return S_OK;
}

// settings
LRESULT CReadToMe::OnSettings()
{
	if(m_pSpeechCtl)
	{
		m_VoiceDlg.m_cpVoice = m_pSpeechCtl->GetVoiceInterface();
		m_VoiceDlg.m_pMain = this;
		if(!::IsWindow(m_VoiceDlg.m_hWnd))
			m_VoiceDlg.Create(m_hWnd);
		m_VoiceDlg.ShowWindow(SW_SHOW);
	}
	return S_OK;
}

// Settings Change
void CReadToMe::SettingsChange(void)
{
	// show tool tips
	m_wndToolBar.UpdateToolTips(MyGetProfileInt("ShowToolTips",1));
	// auto scroll setting
	m_bAutoScrollTextRegistry = (MyGetProfileInt("AutoScrollText",1) == 1);
	// reload junk word list
	LoadJunkWordsList();
}

// set selected text message from speech engine EM_SETSEL
LRESULT CReadToMe::OnMySetSelect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// create new selection range						
	LONG lCount = (LONG)(lParam - wParam);
	MySetSelect((long)wParam, lCount);
	bHandled = true;
	return 0;
}

// make sure selection matches text from buffer
void CReadToMe::CreateSelection(IHTMLTxtRange* pDuplicate,CString strWord,long wParam,long lCount)
{
	if(!pDuplicate)
	{
		ATLTRACE("NULL error CreateSelection(pDuplicate) word:%s\n",strWord);
		return;
	}	
	HRESULT hr;
	long lChars = 0;
	BOOL bFound = false;
	// collapse range position to zero
	CComBSTR bstrBuf;
	CString strUnit = _T("character");	

	hr = pDuplicate->move(strUnit.AllocSysString(),0,&lChars);
	hr = pDuplicate->moveStart(strUnit.AllocSysString(),wParam ,&lChars);
	hr = pDuplicate->moveEnd(strUnit.AllocSysString(),lCount,&lChars); 
	// check range text
	pDuplicate->get_text(&bstrBuf);
	CString strTest;
	strTest = bstrBuf;
	if(strTest != strWord)
	{
		// check surrounding chars as well to get correct word in sentence
		CString strWordExtra;
		if(wParam >= HTML_PRE_CHAR_TEST)
		{	
			if(m_strDocumentText.GetLength() >= (wParam + lCount + HTML_POST_CHAR_TEST - HTML_PRE_CHAR_TEST))
				strWordExtra = m_strDocumentText.Mid(wParam-HTML_PRE_CHAR_TEST,lCount+HTML_POST_CHAR_TEST);
			else if(m_strDocumentText.GetLength() >= (wParam + lCount + 6 - HTML_PRE_CHAR_TEST))
				strWordExtra = m_strDocumentText.Mid(wParam-HTML_PRE_CHAR_TEST,lCount + 6);
		}
		// find in adjusted text
		m_nLastFoundOffset = 0;
        bFound = MyFindText(pDuplicate,strWord,strWordExtra,-10);
        if(!bFound) 
			bFound = MyFindText(pDuplicate,strWord,strWordExtra,10);
		if(!bFound)	
			bFound = MyFindText(pDuplicate,strWord,strWordExtra,-30);
		if(!bFound)	
			bFound = MyFindText(pDuplicate,strWord,strWordExtra,30);
		if(!bFound)	
			bFound = MyFindText(pDuplicate,strWord,strWordExtra,-50);
		if(!bFound)	
			bFound = MyFindText(pDuplicate,strWord,strWordExtra,50);
		if(!bFound)	
			bFound = MyFindText(pDuplicate,strWord,strWordExtra,-100);
		if(!bFound)	
			bFound = MyFindText(pDuplicate,strWord,strWordExtra,100);
		if(!bFound)	
			bFound = MyFindText(pDuplicate,strWord,strWordExtra,-150);
		if(!bFound)	
			bFound = MyFindText(pDuplicate,strWord,strWordExtra,150);
		if(!bFound)	
			bFound = MyFindText(pDuplicate,strWord,strWordExtra,-200);
		if(!bFound)	
			bFound = MyFindText(pDuplicate,strWord,strWordExtra,200); 		
		if(!bFound)
		{
			/*if(m_nLastFoundOffset != 0)
			{
				bFound = MyFindText(pDuplicate,strWord,strWordExtra,m_nLastFoundOffset,false); 		
			} */
			if(!bFound)
			{
				ATLTRACE("Not found in last MyFindText attempt for word: %s\r\n",strWord);
				SAFERELEASE(m_pLastTxtRange);
			}
		}
	}
	else
	{
		bFound = true;
	}
	if(bFound)
	{			
		m_pPrevSelectSegment = MySelectText(pDuplicate);
	}
}

// skip word
void CReadToMe::Skip(int nPos, int nLen)
{
	m_pSpeechCtl->Mute(true);

	if(m_pSpeechCtl->IsPlaying())
		m_pSpeechCtl->Stop();
	m_bStopped = false;
	m_bAutoScrollText = true;
	int nCharPos = (int)nPos + nLen;
	m_nOffset = nCharPos;
	CString strBuf = m_strDocumentText.Mid(nCharPos);
	m_pSpeechCtl->Play(strBuf);

	m_pSpeechCtl->Mute(false); 
}

// select text
void CReadToMe::MySetSelect(long nPos, long lCount)
{
	m_lPrevCarrotPosMin = (LONG)(m_nOffset + nPos);
	// get word from buffer and use to ensure selection correct
	CString strWord = m_strDocumentText.Mid((int)(m_nOffset + nPos),lCount);
	if(IsJunkWord(strWord))
	{
		Skip((int)(m_nOffset + nPos),lCount);
		return;
	}

	if((int)m_aTextRanges.GetCount() > m_nCurrentFramePlaying)
	{
		IHTMLTxtRange* piTextRange = m_aTextRanges.GetAt(m_nCurrentFramePlaying);
		if(piTextRange)
		{
			IHTMLTxtRange *pDuplicate = NULL;
			HRESULT hr = piTextRange->duplicate(&pDuplicate);
			if(hr == S_OK)
				CreateSelection(pDuplicate,strWord,(LONG)(m_nOffset + nPos),lCount);
			SAFERELEASE(pDuplicate);
		}
	}
	else
	{
		ATLTRACE("OnMySetSelect m_aTextRanges.GetCount < m_nCurrentFramePlaying\n");
	}
}

// get text from IE
CString CReadToMe::GetText(void)
{
	HRESULT hr;
	CleanUpTxtRanges();

	m_bIsUsingSelectedText = true;
	CString strText;
	// web browser object
	if(m_spWebBrowser2)
	{		
		// document2 object
		IDispatch* pHtmlDocDispatch = NULL;
		IHTMLDocument2* pHtmlDoc2 = NULL;	
		hr = m_spWebBrowser2->get_Document(&pHtmlDocDispatch); 
		if(pHtmlDocDispatch)
		{
			 // query for html object
			if(pHtmlDocDispatch)
				hr = pHtmlDocDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&pHtmlDoc2); 
			if(pHtmlDoc2) 
			{	
				// check all frames for selected text
				strText = EnumerateAllFrames(pHtmlDoc2,true,true);			
				// no selected text, get all text
				if(strText.IsEmpty())
				{
					m_bIsUsingSelectedText = false;
					CleanUpTxtRanges();
					strText = EnumerateAllFrames(pHtmlDoc2,false,true);
					m_nOffset = 0;
				}
			}
			SAFERELEASE(pHtmlDoc2);
			SAFERELEASE(pHtmlDocDispatch);
		}
	}

	m_nCurrentFramePlaying = 0;
	// auto detect best frame to start with
	if(!m_bIsUsingSelectedText)
	{
		int nFrames = (int)m_aTextRanges.GetCount();
		if(nFrames > 1)
		{
			// look for frame with largest text
			int dwLargestSize = 0;
			int nLargestFrame = 0;
			for(int n=0;n<nFrames;n++)
			{
				IHTMLTxtRange* piTextRange = m_aTextRanges.GetAt(n);
				if(piTextRange)
				{
					CComBSTR bstr;
					hr = piTextRange->get_text(&bstr);
					CString strTest;
					strTest = bstr;
					if(strTest.GetLength() > dwLargestSize)
					{
						dwLargestSize = strTest.GetLength();
						nLargestFrame = n;
						m_strDocumentText = strTest;
					}
				}
			}
			m_nCurrentFramePlaying = nLargestFrame;
		}
		else // look for start of text sentences in page
		{
			m_strDocumentText = strText;
		}
	}
	else // use all selected text 
	{
		m_strDocumentText = strText;
	}
	// unselect any selected text
	for(size_t n=0;n<m_aTextRanges.GetCount();n++)
	{
		IHTMLTxtRange* piTextRange = m_aTextRanges.GetAt(n);
		if(piTextRange)
		{
			CComPtr<IHTMLTxtRange> pDuplicate;
			hr = piTextRange->duplicate(&pDuplicate);
			if(pDuplicate)
			{
				pDuplicate->collapse();
				pDuplicate->select();
			}
		}
	}	
	return m_strDocumentText;
}

// test for junk word
BOOL CReadToMe::IsJunkWord(CString strWord)
{
	if(!m_bCheckJunkWords)
		return false;

	strWord.MakeLower();
	CString strTest;
	for(int n=0; n<(int)m_straJunkWords.GetCount(); n++)
	{
		strTest = m_straJunkWords.GetAt(n).MakeLower();
		if(strWord == strTest)
			return true;
	}
	// check for hyperlink
	if(m_bIgnoreHyperlinks)
		return (strWord.Find("http://") != -1 || strWord.Find("https://") != -1);		
	// not junk word
	return false;
}

// load list of junk words
void CReadToMe::LoadJunkWordsList()
{
	m_bCheckJunkWords = false;
	m_straJunkWords.RemoveAll();

	// junk chars
	CString strJunk = MyGetProfileString("JunkWordChars","|,<,>,",4096);
	int nFind = -1;
	if(!strJunk.IsEmpty())
	{
		CString strTemp = strJunk;
		strTemp.MakeLower();
		nFind = strTemp.Find(",");
		while((nFind = strTemp.Find(",")) != -1)
		{
			CString strWord = strTemp.Left(nFind);
			if(!strWord.IsEmpty())
				m_straJunkWords.Add(strWord);
			strTemp = strTemp.Mid(nFind + 1);
		}
		if(!strTemp.IsEmpty())
			m_straJunkWords.Add(strTemp);
	}
	// junk words
	strJunk = MyGetProfileString("JunkWords","",8096);
	nFind = -1;
	if(!strJunk.IsEmpty())
	{
		CString strTemp = strJunk;
		strTemp.MakeLower();
		nFind = strTemp.Find(",");
		while((nFind = strTemp.Find(",")) != -1)
		{
			CString strWord = strTemp.Left(nFind);
			if(!strWord.IsEmpty())
				m_straJunkWords.Add(strWord);
			strTemp = strTemp.Mid(nFind + 1);
		}
		if(!strTemp.IsEmpty())
			m_straJunkWords.Add(strTemp);
	}
	if(MyGetProfileInt("IgnoreHyperlinks",1) == 1)
	{
		m_bIgnoreHyperlinks = true;
		m_bCheckJunkWords = true;
	}
	else
		m_bCheckJunkWords = (m_straJunkWords.GetCount() > 0);
}

void CReadToMe::CheckNagScreen()
{
	CTime tm;
	tm = tm.GetCurrentTime();

	CString strFilePath;
	GetSystemDirectory(strFilePath.GetBuffer(MAX_PATH),MAX_PATH);
	strFilePath.ReleaseBuffer();
	strFilePath += "\\" + CString(APP_FILE);

	CString strData = ReadEncryptedFile(strFilePath,ENCRYPT_KEY);
	BOOL bExpired = (ParseXML("Expired",strData) == "TRUE");

	CString strInstallTime = ParseXML("InstallTime",strData);
	CTime tmTimeInstall;
	if(!strInstallTime.IsEmpty())
		tmTimeInstall = (long)atol(strInstallTime);
	else
		tmTimeInstall = (long)MyGetProfileInt("id",0);

	CTimeSpan tspan = tm - tmTimeInstall;
	DWORD dwDays = (DWORD)tspan.GetDays();

	if(bExpired || dwDays > 29)
	{
		m_bHasExpired = true;
		// mark as expired
		if(!bExpired)
		{
			strData = ReplaceXML("TRUE","Expired",strData);
			WriteEncryptedFile(strFilePath,ENCRYPT_KEY,strData);
		}
		CTime tmNag = (long)MyGetProfileInt("ln",0);
		tspan = tm - tmNag;
		dwDays = (DWORD)tspan.GetDays();
		// pop up message 1 time per day
		if(dwDays >= 1)
		{
			MyWriteProfileInt("ln",(DWORD)tm.GetTime());
			// set nag timer
			m_nTimerNag = SetTimer(ID_NAG,300);
		}
	}
}

void CReadToMe::LoadURL(CString strURL)
{
	if(m_spWebBrowser2 == NULL)
		return;
	HRESULT hr = S_OK;
	_variant_t varEmpty;
	// convert CString to a COleVariant
	_variant_t vaURL = _bstr_t(strURL);
	hr = m_spWebBrowser2->Navigate2(&vaURL,&varEmpty,&varEmpty,&varEmpty,&varEmpty);
}

// rewind
void CReadToMe::OnRewind()
{
	if(m_pSpeechCtl)
		m_pSpeechCtl->Rewind();
}

// fast rewind
void CReadToMe::OnFastRewind()
{
	if(m_pSpeechCtl)
		m_pSpeechCtl->FastRewind();
}

// forward
void CReadToMe::OnForward()
{
	if(m_pSpeechCtl)
		m_pSpeechCtl->Forward();
}

// fast forward
void CReadToMe::OnFastForward()
{
	if(m_pSpeechCtl)
		m_pSpeechCtl->FastForward();
}

