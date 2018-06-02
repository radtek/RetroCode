#pragma once


// CMyBmButton


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


class CMyBmButton : public CButton
{
	DECLARE_DYNAMIC(CMyBmButton)

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
public:
	CMyBmButton();
	virtual ~CMyBmButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

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
	void DrawTheText(CDC* pDC, LPCTSTR lpszText, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed, BOOL bIsDisabled);

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
	CFont	m_Font;
	// tool tip control
	CToolTipCtrl m_ToolTip;
	// sets tool tip
	void CreateToolTip(CString strText);
	// Destroy Tool Tip
	void DestroyToolTip(void);
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};


