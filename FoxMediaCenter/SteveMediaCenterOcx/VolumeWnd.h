#if !defined(AFX_VOLUMEWND_H__290CE620_4928_4858_A485_0F49DB507123__INCLUDED_)
#define AFX_VOLUMEWND_H__290CE620_4928_4858_A485_0F49DB507123__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VolumeWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVolumeWnd window
#include "MySliderCtrl.h"

class CVolumeWnd : public CWnd
{
// Construction
public:
	CVolumeWnd();

// Attributes
public:
	CMySliderCtrl	m_ctlWave;
	CMySliderCtrl	m_ctlVolume;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVolumeWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVolumeWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVolumeWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOLUMEWND_H__290CE620_4928_4858_A485_0F49DB507123__INCLUDED_)
