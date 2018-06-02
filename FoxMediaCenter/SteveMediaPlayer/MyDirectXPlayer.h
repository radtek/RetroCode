#if !defined(AFX_MYDIRECTXPLAYER_H__B36E347C_D376_4428_B124_B60C443676FC__INCLUDED_)
#define AFX_MYDIRECTXPLAYER_H__B36E347C_D376_4428_B124_B60C443676FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDirectXPlayer.h : header file
//
class CMyMediaPlayer;
/////////////////////////////////////////////////////////////////////////////
// CMyDirectXPlayer window

class CMyDirectXPlayer : public CWnd
{
// Construction
public:
	CMyDirectXPlayer();

// Attributes
public:
	LONGLONG m_llStartPos;
	CTime m_timeStart;

// Operations
public:
	void CreateComponents();
	void ReleaseComponents();
	BOOL SetWindowOwner();
	LONGLONG GetCurrentPosition();
	void SetCurrentPosition(LONGLONG llPos);
	long GetLengthInSecs();
	CRect GetAspectRatio(long lx,long ly);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDirectXPlayer)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Forward();
	void Rewind();
	void FullScreen();
	void ShowVideoWindow(BOOL bShow);
	void Stop();
	void Pause();
	BOOL Play();
	void SetFileName(CString strFile);
	virtual ~CMyDirectXPlayer();
	
	CMyMediaPlayer* m_pMain;
	// Generated message map functions
protected:

	long HandleGraphEvent(WPARAM wParam,LPARAM lParam);

	// Com params
	IGraphBuilder		*m_pGraph;
	IMediaControl		*m_pMediaControl;
	IMediaEventEx		*m_pEvent;
	IMediaSeeking		*m_pMediaSeeking;	
	IVideoWindow		*m_pVideoWindow;
	IMediaPosition		*m_pMediaPosition;
	IBasicAudio			*m_pBasicAudio;
	IBasicVideo			*m_pBasicVideo;

	//{{AFX_MSG(CMyDirectXPlayer)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class CMyMediaPlayer;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIRECTXPLAYER_H__B36E347C_D376_4428_B124_B60C443676FC__INCLUDED_)
