// ReadToMe.h : Declaration of the CReadToMe

#pragma once
#include "resource.h"       // main symbols

class CHtmlEvenHandler;
class CMySpeechCtl;
class CMyBrowserEvents;
#include "SettingsDlg.h"
#include "MyToolbars.h"

// IReadToMe
[
	object,
	uuid("6A7C0940-D1F2-4343-ABB9-58AB669E9E4F"),
	dual,	helpstring("IReadToMe Interface"),
	pointer_default(unique)
]
__interface IReadToMe : IDispatch
{
};

// CReadToMe
[
	coclass,
	threading("apartment"),
	aggregatable("never"),
	vi_progid("ReadToMePlugin.ReadToMe"),
	progid("ReadToMePlugin.ReadToMe.1"),
	version(1.0),
	uuid("1FFFE263-3C8E-4DD8-9BAA-36998D29561E"),
	helpstring("ReadToMe Class")
]
class ATL_NO_VTABLE CReadToMe : 
	public IObjectWithSiteImpl<CReadToMe>,
	public IDeskBand,
	public CWindowImpl<CReadToMe,CAxWindow>,
	public IDispatchImpl<IReadToMe, &__uuidof(IReadToMe)>
{
public:
	CReadToMe();
	~CReadToMe();

	BEGIN_MSG_MAP(CReadToMe)
		MESSAGE_HANDLER(MY_EM_SETSEL, OnMySetSelect)
		MESSAGE_HANDLER(MY_EM_END_OF_STREAM, OnMyEndOfTextStream)
        MESSAGE_HANDLER(MY_MSG_DOUBLE_CLICK, OnDoubleClick)
        MESSAGE_HANDLER(MY_MSG_STOP_SPEAKING, OnStopSpeaking)
        MESSAGE_HANDLER(MY_WM_PLAY_FROM_POS, OnPlayFromPos)
        MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		COMMAND_ID_HANDLER(ID_PLAY, OnPlay)
		COMMAND_ID_HANDLER(ID_STOP, OnStop)
		COMMAND_ID_HANDLER(ID_PAUSE, OnPause)
	END_MSG_MAP()

	// message handlers
	LRESULT OnPlayFromPos(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMySetSelect(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMyEndOfTextStream(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDoubleClick(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnStopSpeaking(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	
	LRESULT OnStop(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnPlay(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnPause(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSettings();

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

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
	CMySpeechCtl* m_pSpeechCtl;
	CComObject<CHtmlEvenHandler>* m_pHtmlEvenHandler;
	DWORD m_dwBandID;
	DWORD m_dwViewMode;
	BOOL m_bShow;
	HWND m_hWndParent;
	HWND m_hWnd;
	IUnknown *m_pUnkSite;
	// IWebBrowser2 pointer
	IWebBrowser2* m_spWebBrowser2; 
	// toobar window
	CMyToolbars	m_wndToolBar;

	// speech objects
	BOOL m_bFirstPlay;
    // stop button hit
	BOOL m_bStopped;
	// paused
	BOOL m_bPaused;
	// auto scroll selected text
	BOOL m_bAutoScrollText;
	// auto scroll registry setting
	BOOL m_bAutoScrollTextRegistry;
	// timer that will enable auto scroll to text 
	UINT_PTR m_nTimerResumeAutoScroll;
	// InitializeSpeechControl
	BOOL InitializeSpeechControl(void);

	// html speech objects
	// last found offset
	int m_nLastFoundOffset;
	// text offset
	int m_nOffset;
	// stop auto scroll
	void StopAutoScroll();
	// clean up all text range objects
	void CleanUpTxtRanges(void);
	// get current char position from cursor position
	int GetCurrentPosition(void);
	void SetPositionOffset(int nOffset);
	// get all text
	CString GetText(void);
	// get text from buffer
	CString GetBufferedText();
	// reset state
	void ResetState(void);
	// text functions
	CString GetTextFromDocument(IHTMLDocument2* pHtmlDoc2,BOOL bSelectedText,BOOL bStoreRange);
	CString EnumerateAllFrames(IHTMLDocument2 * pHtmlDoc2, BOOL bSelectedText,BOOL bStoreRange);
	void CreateSelection(IHTMLTxtRange* pDuplicate,CString strWord,long wParam,long lCount);
	BOOL MyFindText(IHTMLTxtRange* pDuplicate,CString strWord,CString strWordExtra,int nPosAjustment,BOOL bCanUseDupTest=true);
	// get current url
	BOOL GetCurrentURL(CComBSTR&,CComBSTR&);
	// is using selected html text
	BOOL m_bIsUsingSelectedText;
	// current frame that text is played from
	int m_nCurrentFramePlaying;
	// document text
	CString m_strDocumentText;
	// previous selected word position
	LONG m_lPrevCarrotPosMin;
	// text range, text values array
	CInterfaceArray<IHTMLTxtRange> m_aTextRanges;
	// last found word position
	IHTMLTxtRange* m_pLastTxtRange;
	// highlight text
	IHighlightSegment* MySelectText(IHTMLTxtRange* pDuplicate);
	IHighlightSegment* m_pPrevSelectSegment;
	// set render style based on user preferences
	HRESULT MySetRenderStyle(IHTMLRenderStyle* pStyle);
	// show or hide caret
	void ShowCaret(BOOL bShow);
	// get the currently selected text
	CString GetSelectedText(void);
	// scrolling into view, do not disable auto scroll
	BOOL m_bScrollingIntoView;
	// show voice settings
	CSettingsDlg m_VoiceDlg;

	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	// Settings Change
	void SettingsChange(void);
	// look for junk word to skip
	BOOL IsJunkWord(CString strWord);
	// skip word
	void Skip(int nPos, int nLen);
	// select word
	void MySetSelect(long nPos, long nLen);
	// has any junk words
	BOOL m_bCheckJunkWords;
	// ignore hyperlinks
	BOOL m_bIgnoreHyperlinks;
	// array of junk words
	CAtlArray<CString> m_straJunkWords;
	// load list of junk words
	void LoadJunkWordsList();
	// expired trial
	BOOL m_bHasExpired;
	// nag timer
	UINT_PTR m_nTimerNag;
	// Check nag screen
	void CheckNagScreen();
	// load url
	void LoadURL(CString strURL);
	// rewind
	void OnRewind();
	// fast rewind
	void OnFastRewind();
	// forward
	void OnForward();
	// fast forward
	void OnFastForward();
};

