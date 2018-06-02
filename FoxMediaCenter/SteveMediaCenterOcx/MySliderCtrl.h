#if !defined(AFX_MYSLIDERCTRL_H__E87B0D78_DE3E_447F_98E2_0FC10ED26D05__INCLUDED_)
#define AFX_MYSLIDERCTRL_H__E87B0D78_DE3E_447F_98E2_0FC10ED26D05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySliderCtrl.h : header file
//
#include "VolumeControl.h"

/////////////////////////////////////////////////////////////////////////////
// CMySliderCtrl window

class CMySliderCtrl : public CWnd
{
// Construction
public:
	CMySliderCtrl();
	void SetPos(ULONG lPos);
	ULONG GetPos();

// Attributes
public:
	DWORD m_dwMax;
	DWORD m_dwMin;

// Operations
public:
	long OnMixerCtrlChange(UINT wParam, LONG lParam);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySliderCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_strText;
	BOOL m_bIsWave;
	DWORD m_dwLineColor;
	DWORD m_dwBkColor;
	void Init();
	int m_nVol_Start;
	int m_nVold_Width;
	long m_lSliderPos;
	BOOL m_bMouseDown;
	virtual ~CMySliderCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMySliderCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSLIDERCTRL_H__E87B0D78_DE3E_447F_98E2_0FC10ED26D05__INCLUDED_)
