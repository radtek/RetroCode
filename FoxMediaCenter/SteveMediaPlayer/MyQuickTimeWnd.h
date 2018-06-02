#if !defined(AFX_MYQUICKTIMEWND_H__31A53B75_3775_47E9_8968_168005EA76EB__INCLUDED_)
#define AFX_MYQUICKTIMEWND_H__31A53B75_3775_47E9_8968_168005EA76EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyQuickTimeWnd.h : header file
//
#include "CQuickTime.h"
#include "QTML.h"

class CMyMediaPlayer;


/////////////////////////////////////////////////////////////////////////////
// CMyQuickTimeWnd window

class CMyQuickTimeWnd : public CWnd
{
// Construction
public:
	CMyQuickTimeWnd();

// Attributes
public:
	CQuickTime *m_pQuickTime;
	CMyMediaPlayer* m_pMain;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyQuickTimeWnd)
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL IsFinished();
	void HideDisplayBar();
	DWORD GetLengthInSecs();
	void Rewind();
	void Forward();
	void SetCurrentPosition(LONGLONG llPos);
	LONGLONG GetCurrentPosition();
	void FullScreen(BOOL bMakeFullScreen = true);
	void Stop();
	void Pause();
	void Play();
	void SetFileName(CString strFileName);
	virtual ~CMyQuickTimeWnd();


	WindowPtr m_FullScreenWindow;	// the full-screen window
	MovieController	m_MC;			// movie controller for the full-screen window
	Ptr	m_RestoreState;	// restore state; used when closing the full-screen window

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyQuickTimeWnd)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYQUICKTIMEWND_H__31A53B75_3775_47E9_8968_168005EA76EB__INCLUDED_)
