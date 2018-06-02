
#include "StdAfx.h"
#include "ReadToMe.h"
#include ".\toolbarwnd.h"

CToolBarWnd::CToolBarWnd(void) : m_RebarContainer(NULL, this, 1), m_bInitialSeparator(false), m_nResourceID(0), m_pWebBrowser(NULL)
{
	m_pParent = NULL;
}

CToolBarWnd::~CToolBarWnd(void)
{
	if(::IsWindow(m_RebarContainer.m_hWnd))
		m_RebarContainer.UnsubclassWindow();
    if (::IsWindow(m_hWnd))
        DestroyWindow();
}

HWND CToolBarWnd::CreateSimpleToolBarCtrl(HWND hWndParent, UINT nResourceID, BOOL bInitialSeparator, DWORD dwStyle, DWORD dwExStyle, UINT nID)
{
	m_nResourceID = nResourceID;
    m_bInitialSeparator = bInitialSeparator;
    HINSTANCE hInst = _AtlBaseModule.GetResourceInstance();
	HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(nResourceID), RT_TOOLBAR);
	if (hRsrc == NULL)
		return NULL;

	HGLOBAL hGlobal = ::LoadResource(hInst, hRsrc);
	if (hGlobal == NULL)
		return NULL;

	_AtlToolBarData* pData = (_AtlToolBarData*)::LockResource(hGlobal);
	if (pData == NULL)
		return NULL;
	ATLASSERT(pData->wVersion == 1);

	WORD* pItems = pData->items();
	int nItems = pData->wItemCount + (bInitialSeparator ? 1 : 0);
	TBBUTTON* pTBBtn = (TBBUTTON*)_alloca(nItems * sizeof(TBBUTTON));

	int nBmp = 0;
	for(int i = 0, j = bInitialSeparator ? 1 : 0; i < pData->wItemCount; i++, j++)
	{
		if(pItems[i] != 0)
		{
			pTBBtn[j].iBitmap = nBmp++;
			pTBBtn[j].idCommand = pItems[i];
			pTBBtn[j].fsState = TBSTATE_ENABLED;
			pTBBtn[j].fsStyle = TBSTYLE_BUTTON;
			pTBBtn[j].dwData = 0;
			pTBBtn[j].iString = 0;
		}
		else
		{
			pTBBtn[j].iBitmap = 8;
			pTBBtn[j].idCommand = 0;
			pTBBtn[j].fsState = 0;
			pTBBtn[j].fsStyle = TBSTYLE_SEP;
			pTBBtn[j].dwData = 0;
			pTBBtn[j].iString = 0;
		}
	}

    CRect rect(0,0,100,100);
    HWND hWnd = CWindowImpl<CToolBarWnd, CToolBarCtrl>::Create(hWndParent,rect,NULL, dwStyle, dwExStyle, nID);

	::SendMessage(hWnd, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0L);

	TBADDBITMAP tbab;
	tbab.hInst = hInst;
	tbab.nID = nResourceID;
	::SendMessage(hWnd, TB_ADDBITMAP, nBmp, (LPARAM)&tbab);
	::SendMessage(hWnd, TB_ADDBUTTONS, nItems, (LPARAM)pTBBtn);
	::SendMessage(hWnd, TB_SETBITMAPSIZE, 0, MAKELONG(pData->wWidth, pData->wHeight));
	::SendMessage(hWnd, TB_SETBUTTONSIZE, 0, MAKELONG(pData->wWidth + 7, pData->wHeight + 7));

    // Aditional Initialisation can go here
    CClientDC dc(m_hWnd);
	dc.SelectFont((HFONT) GetStockObject( DEFAULT_GUI_FONT ));		
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	int cxChar = tm.tmAveCharWidth;
	int cyChar = tm.tmHeight + tm.tmExternalLeading;
	int cx = (LF_FACESIZE + 4) * cxChar;
	int cy = 16 * cyChar;
    m_ncy = cy;
    // Create an Edit Control		
    UpdateToolBarCtrlType(toTextOnRight);
	return hWnd;
}

BOOL CToolBarWnd::UpdateToolBarCtrlType(TextOptions nTextOption)
{        
    // Modify toolbar style according to new text options
    ModifyStyle(( nTextOption == toTextOnRight ) ? 0 : TBSTYLE_LIST,
                ( nTextOption == toTextOnRight ) ? TBSTYLE_LIST : 0 );
    HINSTANCE hInst = _AtlBaseModule.GetResourceInstance();
	HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(m_nResourceID), RT_TOOLBAR);
	if (hRsrc == NULL)
		return NULL;
	HGLOBAL hGlobal = ::LoadResource(hInst, hRsrc);
	if (hGlobal == NULL)
		return NULL;
	_AtlToolBarData* pData = (_AtlToolBarData*)::LockResource(hGlobal);
	if (pData == NULL)
		return NULL;
	ATLASSERT(pData->wVersion == 1);
	WORD* pItems = pData->items();
	int nItems = pData->wItemCount + (m_bInitialSeparator ? 1 : 0);
	TBBUTTON* pTBBtn = (TBBUTTON*)_alloca(nItems * sizeof(TBBUTTON));
    int nBmp = 0;
    int nButtonCount = 0;
	for(int i = 0, j = m_bInitialSeparator ? 1 : 0; i < pData->wItemCount; i++, j++)
	{
        DeleteButton(j);		
        if(pItems[i] != 0)
		{
			pTBBtn[j].iBitmap = nBmp++;
			pTBBtn[j].idCommand = pItems[i];
			pTBBtn[j].fsState = TBSTATE_ENABLED;
			pTBBtn[j].fsStyle = TBSTYLE_BUTTON;
			pTBBtn[j].dwData = 0;
            pTBBtn[j].iString = nButtonCount;
            switch ( nTextOption )
			{            
                case toTextLabels:
					{
						pTBBtn[j].iString =nButtonCount;
						pTBBtn[j].fsStyle &= ~( TBSTYLE_AUTOSIZE | BTNS_SHOWTEXT );
					}
					break;
				case toTextOnRight:
                    {
						pTBBtn[j].iString = nButtonCount;
						pTBBtn[j].fsStyle |= ( TBSTYLE_AUTOSIZE | BTNS_SHOWTEXT );
					}
					break;
				case toNoTextLabels:
 					pTBBtn[j].iString=-1; //Set string to zero
					pTBBtn[j].fsStyle &= ~BTNS_SHOWTEXT;
					pTBBtn[j].fsStyle |= TBSTYLE_AUTOSIZE;
					break;
			}
            nButtonCount++;
        }
		else
		{
			pTBBtn[j].iBitmap = 8;
			pTBBtn[j].idCommand = 0;
			pTBBtn[j].fsState = 0;
			pTBBtn[j].fsStyle = TBSTYLE_SEP;
			pTBBtn[j].dwData = 0;
			pTBBtn[j].iString = 0;
		}
        InsertButton(j,  &pTBBtn[j]);    
    }
    // Additional Styles should be set here
    //SetToolBarButtonInfo(ID_PLAY, TBIF_STYLE, pTBBtn[PLAY_BUTTON].fsStyle);
    // make sure the control is where it should be
    ::SendMessage(m_hWnd, WM_SIZE, 0, 0);

    return true;
}

void CToolBarWnd::SetToolBarButtonInfo(int nID, DWORD dwMask, BYTE fsStyle)
{
    TBBUTTONINFO tbi;	
    tbi.cbSize = sizeof(TBBUTTONINFO);
    tbi.dwMask = dwMask;
    tbi.fsStyle = fsStyle;	
    SetButtonInfo(nID, &tbi);
}

BOOL CToolBarWnd::SetBandRebar() 
{
	HWND hWnd(NULL);
	m_pWebBrowser->get_HWND((long*)&hWnd);
	if (hWnd == NULL) 
		return FALSE;
	m_ctlRebar.m_hWnd = FindRebar(hWnd);
	if (m_ctlRebar.m_hWnd == NULL) 
		return FALSE;
	m_RebarContainer.SubclassWindow(m_ctlRebar);

	return TRUE;
}

LRESULT CToolBarWnd::OnToolbarNeedText(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)	
{
    CString sToolTip;    
	//-- make sure this 1is not a seperator
    if (idCtrl != 0) 
    {
        if (!sToolTip.LoadString(idCtrl))
        {
	        bHandled = FALSE;
            return 0;
        }
    }
    LPNMTTDISPINFO pttdi = reinterpret_cast<LPNMTTDISPINFO>(pnmh);
	pttdi->lpszText = MAKEINTRESOURCE(idCtrl);
	pttdi->hinst = _AtlBaseModule.GetResourceInstance();
	pttdi->uFlags = TTF_DI_SETITEM;
	//-- message processed
	return 0;
}

HWND CToolBarWnd::FindRebar(HWND hwndStart)
{
	HWND hwndFound=NULL;
	if (((hwndFound = FindWindowEx(hwndStart, NULL, REBARCLASSNAME, NULL)) != NULL))
		return hwndFound;
	HWND hwndEnum=NULL;
	while ((hwndEnum = FindWindowEx(hwndStart, hwndEnum, NULL, NULL)) != NULL){
		if ((hwndFound = FindRebar(hwndEnum)) != NULL)
			return hwndFound;
	}
	return NULL;
}


