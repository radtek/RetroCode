#if !defined(AFX_MYMP3PLAYER_H__0C1897EA_ADA7_43EE_9A86_C10F05F3BB56__INCLUDED_)
#define AFX_MYMP3PLAYER_H__0C1897EA_ADA7_43EE_9A86_C10F05F3BB56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyMp3Player.h : header file
//
class CMyMediaPlayer;
/////////////////////////////////////////////////////////////////////////////
// CMyMp3Player window

class CMyMp3Player : public CWnd
{
// Construction
public:
	CMyMp3Player();

// Attributes
public:
	CMyMediaPlayer* m_pMain;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMp3Player)
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT m_timerCheckEOF;
	long GetLengthInSecs();
	void Forward();
	void Rewind();
	void SetCurrentPosition(LONGLONG dwPos);
	LONGLONG GetCurrentPosition();
	void Pause();
	void Stop();
	void Play();
	void SetFileName(CString strFileName);
	virtual ~CMyMp3Player();
	LONGLONG GetDuration();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyMp3Player)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMP3PLAYER_H__0C1897EA_ADA7_43EE_9A86_C10F05F3BB56__INCLUDED_)
