#pragma once

#include <atltime.h>

#pragma pack(1)
	typedef struct _STRUCT_BITMAPS
	{
		HBITMAP		hBitmap;		// Handle to bitmap
		DWORD		dwWidth;		// Width of bitmap
		DWORD		dwHeight;		// Height of bitmap
		HBITMAP		hMask;			// Handle to mask bitmap
		COLORREF	crTransparent;	// Transparent color
	} STRUCT_BITMAPS;
#pragma pack()

// Dummy identifier for grayscale icon
#ifndef	BTNST_AUTO_GRAY
#define	BTNST_AUTO_GRAY					(0xffffffff - 1L)
#endif
// Dummy identifier for 15% darker icon
#ifndef	BTNST_AUTO_DARKER
#define	BTNST_AUTO_DARKER				(0xffffffff - 2L)
#endif

class CMyBmButton :	public CWindowImpl<CMyBmButton,WTL::CButton>					
{
public:

	   enum	{	ST_ALIGN_HORIZ	= 0,			// Icon/bitmap on the left, text on the right
				ST_ALIGN_VERT,					// Icon/bitmap on the top, text on the bottom
				ST_ALIGN_HORIZ_RIGHT,			// Icon/bitmap on the right, text on the left
				ST_ALIGN_OVERLAP				// Icon/bitmap on the same space as text
			};

	   enum	{	BTNST_COLOR_BK_IN	= 0,		// Background color when mouse is INside
				BTNST_COLOR_FG_IN,				// Text color when mouse is INside
				BTNST_COLOR_BK_OUT,				// Background color when mouse is OUTside
				BTNST_COLOR_FG_OUT,				// Text color when mouse is OUTside
				BTNST_COLOR_BK_FOCUS,			// Background color when the button is focused
				BTNST_COLOR_FG_FOCUS,			// Text color when the button is focused

				BTNST_MAX_COLORS
			};

	   enum	{	BTNST_PRESSED_LEFTRIGHT = 0,	// Pressed style from left to right (as usual)
				BTNST_PRESSED_TOPBOTTOM			// Pressed style from top to bottom
			};

	CMyBmButton(void);
	~CMyBmButton(void);

	BEGIN_MSG_MAP(CMyBmButton)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)

		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MBUTTONDOWN, OnMButtonDown)
		MESSAGE_HANDLER(WM_MBUTTONUP, OnMButtonUp)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
		MESSAGE_HANDLER(WM_RBUTTONUP, OnRButtonUp)

		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	// tool tip relay messages
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CPoint point(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
		if(m_ToolTip.IsWindow())
		{
			CTime time;
			time = time.GetCurrentTime();
			MSG msg;
			msg.hwnd = m_hWnd;
			msg.message = uMsg;
			msg.wParam = wParam;
			msg.lParam = lParam;
			msg.time = (DWORD)time.GetTime();
			msg.pt = point;
			m_ToolTip.RelayEvent(&msg);
		}
		bHandled = false;
		return S_OK;
	}
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CPoint point(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
		if(m_ToolTip.IsWindow())
		{
			CTime time;
			time = time.GetCurrentTime();
			MSG msg;
			msg.hwnd = m_hWnd;
			msg.message = uMsg;
			msg.wParam = wParam;
			msg.lParam = lParam;
			msg.time = (DWORD)time.GetTime();
			msg.pt = point;
			m_ToolTip.RelayEvent(&msg);
		}
		bHandled = false;
		return S_OK;
	}
	LRESULT OnMButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& )
	{
		CPoint point(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
		if(m_ToolTip.IsWindow())
		{
			CTime time;
			time = time.GetCurrentTime();
			MSG msg;
			msg.hwnd = m_hWnd;
			msg.message = uMsg;
			msg.wParam = wParam;
			msg.lParam = lParam;
			msg.time = (DWORD)time.GetTime();
			msg.pt = point;
			m_ToolTip.RelayEvent(&msg);
		}
		return S_OK;
	}
	LRESULT OnMButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& )
	{
		CPoint point(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
		if(m_ToolTip.IsWindow())
		{
			CTime time;
			time = time.GetCurrentTime();
			MSG msg;
			msg.hwnd = m_hWnd;
			msg.message = uMsg;
			msg.wParam = wParam;
			msg.lParam = lParam;
			msg.time = (DWORD)time.GetTime();
			msg.pt = point;
			m_ToolTip.RelayEvent(&msg);
		}
		return S_OK;
	}
	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& )
	{
		CPoint point(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
		if(m_ToolTip.IsWindow())
		{
			CTime time;
			time = time.GetCurrentTime();
			MSG msg;
			msg.hwnd = m_hWnd;
			msg.message = uMsg;
			msg.wParam = wParam;
			msg.lParam = lParam;
			msg.time = (DWORD)time.GetTime();
			msg.pt = point;
			m_ToolTip.RelayEvent(&msg);
		}
		return S_OK;
	}
	LRESULT OnRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& )
	{
		CPoint point(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
		if(m_ToolTip.IsWindow())
		{
			CTime time;
			time = time.GetCurrentTime();
			MSG msg;
			msg.hwnd = m_hWnd;
			msg.message = uMsg;
			msg.wParam = wParam;
			msg.lParam = lParam;
			msg.time = (DWORD)time.GetTime();
			msg.pt = point;
			m_ToolTip.RelayEvent(&msg);
		}
		return S_OK;
	} 

	LRESULT OnStop(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnPlay(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnPause(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSettings(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	void OnDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void CancelHover();
	void OnDrawBackground(CDC* pDC, CRect* pRect);
	void OnDrawBorder(CDC* pDC, CRect* pRect);
	void DrawTheBitmap(CDC* pDC, BOOL bHasTitle, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed, BOOL bIsDisabled);
	void FreeResources(BOOL bCheckForNULL = TRUE);
	void SetDefaultColors(BOOL bRepaint = TRUE);
	void PrepareImageRect(BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, DWORD dwWidth, DWORD dwHeight, CRect* rpImage);
	void SetBitmaps(HBITMAP hBitmapIn, COLORREF crTransColorIn, HBITMAP hBitmapOut = NULL, COLORREF crTransColorOut = 0, ULONG ulBitOutDefault = 0);
	void SetPressedStyle(BYTE byStyle, BOOL bRepaint);
	HBITMAP CreateGrayscaleBitmap(HBITMAP hBitmap, DWORD dwWidth, DWORD dwHeight, COLORREF crTrans);
	HBITMAP CreateDarkerBitmap(HBITMAP hBitmap, DWORD dwWidth, DWORD dwHeight, COLORREF crTrans);
	HBITMAP CreateBitmapMask(HBITMAP hSourceBitmap, DWORD dwWidth, DWORD dwHeight, COLORREF crTransColor);
	COLORREF DarkenColor(COLORREF crColor, double dFactor);

	STRUCT_BITMAPS	m_csBitmaps[2];

	BOOL m_bIsPressed;
	BOOL m_bIsFocused;
	BOOL m_bIsDisabled;
	BOOL m_bIsFlat;
	BOOL m_bDrawBorder;
	BOOL m_bMouseOnButton;
	BOOL m_bDrawFlatFocus;
	BOOL m_bIsDefault;
	BOOL m_bAlwaysTrack;
	POINT	m_ptImageOrg;
	POINT	m_ptPressedOffset;
	BYTE		m_byAlign;			// Align mode
	COLORREF	m_crColors[BTNST_MAX_COLORS];	
	// tool tip control
	CToolTipCtrl m_ToolTip;
	// sets tool tip
	void CreateToolTip(CString strText);
	// Destroy Tool Tip
	void DestroyToolTip(void);
};
