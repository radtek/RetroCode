#if !defined(AFX_MYMEDIAPLAYER_H__FD3A432C_A247_4FBA_9499_051505DBFC81__INCLUDED_)
#define AFX_MYMEDIAPLAYER_H__FD3A432C_A247_4FBA_9499_051505DBFC81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyMediaPlayer.h : header file
//
#include "helpers.h"
#include "FullScreenWnd.h"	// Added by ClassView
#include "MyQuickTimeWnd.h"
#include "MyRealAudio1.h"

/////////////////////////////////////////////////////////////////////////////
// CMyMediaPlayer window
class CMyDirectXPlayer;
class CSteveMediaPlayerCtrl;

class CMyMediaPlayer : public CWnd
{
// Construction
public:
	CMyMediaPlayer();

// Attributes
public:
	void SendCurrentMediaInfo();
	void SendCurrentPlayPos();
	void SetZeroTimePlayed();


// Operations
public:
	void OnEndOfStreamMediaplayer1(long Result);
	void OnReadyStateChangeMediaplayer1(long Result);	
	long OnEndFullScreen(UINT wParam,LPARAM lparam);
	CString GetCurrentPlayingInfo();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMediaPlayer)
	//}}AFX_VIRTUAL

// Implementation
public:
	CFullScreenWnd m_wndFullScreen;
	BOOL m_bIsInFullScreen;
	DWORD GetLengthInSecs();
	LONGLONG m_lLastPlayPos;
	UINT m_TimerPlayPos;
	void Rewind();
	void Forward();
	void FullScreen();
	void SaveCurrentVolume();
	CString GetCurrentMediaName();
	BOOL m_bRepeatOn;
	void SetCurrentPosition(LONGLONG dwPos);
	LONGLONG GetCurrentPosition();
	DWORD m_dwPrevVol;
	BOOL m_bMuted;
	void Mute();
	void IncreaseVolume();
	void LowerVolume();
	virtual ~CMyMediaPlayer();

	BOOL Pause();
	void Stop();
	BOOL Play();
	void SetFilePath(CString strFilePath);

	EnumFileType		m_enumCurrentMediaType;
	EnumPlayState		m_enumCurrentPlayState;

	BOOL m_bDXVideoGood;
	CMyDirectXPlayer* m_pDXVideoPlayer;
	CSteveMediaPlayerCtrl* m_pMainWnd;
	CString m_strCurrentVideoPath;

	BOOL m_bQTVideoGood;
	CMyQuickTimeWnd* m_pQTPlayer;

//	BOOL m_bRealVideoGood;
//	CMyRealAudio*	m_pRealPlayer;

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyMediaPlayer)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class CMyDirectXPlayer;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMEDIAPLAYER_H__FD3A432C_A247_4FBA_9499_051505DBFC81__INCLUDED_)
