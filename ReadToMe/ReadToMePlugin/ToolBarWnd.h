#pragma once

#include "resource.h"
class CReadToMe;

class CToolBarWnd :	public CWindowImpl<CToolBarWnd, CToolBarCtrl>
{
public:
	CToolBarWnd(void);
	~CToolBarWnd(void);

	enum TextOptions
    {
        toNone          = -1,
        toTextLabels    =  0,
        toTextOnRight   =  1,
        toNoTextLabels  =  2,
    };

	BEGIN_MSG_MAP(CToolBarWnd)
        NOTIFY_CODE_HANDLER(TTN_NEEDTEXT, OnToolbarNeedText)
        DEFAULT_REFLECTION_HANDLER()
	ALT_MSG_MAP(1)
	END_MSG_MAP()

	LRESULT OnToolbarNeedText(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/);
	
	void SetWebBrowser(IWebBrowser2* pWebBrowser) {m_pWebBrowser = pWebBrowser;}
    HWND CreateSimpleToolBarCtrl(HWND hWndParent, UINT nResourceID, BOOL bInitialSeparator = FALSE, DWORD dwStyle = 0, DWORD dwExStyle = 0, UINT nID = ATL_IDW_TOOLBAR);
    BOOL UpdateToolBarCtrlType(TextOptions nTextOption);
	BOOL SetBandRebar();
    void SetToolBarButtonInfo(int nID, DWORD dwMask, BYTE fsStyle);
	HWND FindRebar(HWND hwndStart);

	CReadToMe*		m_pParent;
	IWebBrowser2*	m_pWebBrowser;

	CContainedWindow m_RebarContainer;
	CReBarCtrl m_ctlRebar;
	TextOptions  m_eTextOptions;

    BOOL m_bInitialSeparator;
    UINT m_nResourceID;
	int m_ncy;

	struct _AtlToolBarData
	{
		WORD wVersion;
		WORD wWidth;
		WORD wHeight;
		WORD wItemCount;
		WORD* items() { return (WORD*)(this+1); }
	};

};
