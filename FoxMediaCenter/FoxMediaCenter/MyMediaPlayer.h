#if !defined(AFX_MYMEDIAPLAYER_H__FD3A432C_A247_4FBA_9499_051505DBFC81__INCLUDED_)
#define AFX_MYMEDIAPLAYER_H__FD3A432C_A247_4FBA_9499_051505DBFC81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyMediaPlayer.h : header file
//
#include "helpers.h"


/////////////////////////////////////////////////////////////////////////////
// CMyMediaPlayer window
class CMyDirectXPlayer;
class CMainFrame;

class CMyMediaPlayer : public CWnd
{
// Construction
public:
	CMyMediaPlayer();

// Attributes
public:


// Operations
public:
	void OnEndOfStreamMediaplayer1(long Result);
	void OnReadyStateChangeMediaplayer1(long Result);	
	
	CString GetCurrentPlayingInfo();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMediaPlayer)
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetBitrate();
	CString GetArtist();
	CString GetTitle();
	CString m_strBitrate;
	CString m_strArtist;
	CString m_strTitle;
	BOOL m_bLastWasVideo;
	void IncreaseVolumeWave();
	void LowerVolumeWave(DWORD volLowerAmount=0);
	LONGLONG m_lLastPlayPos;
	DWORD GetLowerVolumeVal(DWORD dwLowerIntervals);
	void SendCurrentMediaInfo();
	UINT m_TimerPlayPos;
	void SendCurrentPlayPos();
	void SetZeroTimePlayed();
	void Forward();
	void Rewind();
	BOOL IsPlayingVideo();
	CString GetCurrentFileListXML();
	void Previous();
	void Next();
	void SaveCurrentVolume();
	void SetPlayingIcon(DWORD nPos,BOOL bSelect=true);
	void SetNormalIcon(DWORD nCurrentMediaPos);
	void SetCurrentMediaName(CString strName);
	CString GetCurrentMediaName();
	void SetCurrentPosition(LONGLONG dwPos);
	DWORD m_dwPrevVol;
	BOOL m_bMuted;
	void Mute();
	void IncreaseVolume();
	void LowerVolume(DWORD volLowerAmount=0);
	virtual ~CMyMediaPlayer();

	BOOL Pause();
	void Stop();
	BOOL Play();
	void SetPlayList(CStringArray* pStra);

	EnumFileType		m_enumCurrentMediaType;
	EnumPlayState		m_enumCurrentPlayState;

	BOOL m_bDXAudioGood;
	BOOL m_bMP3AudioGood;
	CMyDirectXPlayer* m_pDXAudioPlayer;
	int m_nCurrentMediaPos;
	CStringArray m_straPlayList;
	CMainFrame* m_pMainWnd;


	// Generated message map functions
protected:
	//{{AFX_MSG(CMyMediaPlayer)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class CMyDirectXPlayer;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMEDIAPLAYER_H__FD3A432C_A247_4FBA_9499_051505DBFC81__INCLUDED_)
