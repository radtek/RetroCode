#if !defined(AFX_STEVEMEDIAPLAYERCTL_H__08512BD6_C614_43D0_B6F6_D590ECD810F7__INCLUDED_)
#define AFX_STEVEMEDIAPLAYERCTL_H__08512BD6_C614_43D0_B6F6_D590ECD810F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SteveMediaPlayerCtl.h : Declaration of the CSteveMediaPlayerCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CSteveMediaPlayerCtrl : See SteveMediaPlayerCtl.cpp for implementation.
class CMyMediaPlayer;
#include "MyMessageWnd.h"
#include "VolumeWnd.h"
#include "SeekWnd.h"

class CSteveMediaPlayerCtrl : public COleControl
{
	DECLARE_DYNCREATE(CSteveMediaPlayerCtrl)

// Constructor
public:
	CSteveMediaPlayerCtrl();

	CMyMediaPlayer* m_pMyMediaPlayer;
	CMyMessageWnd	m_msgWnd;
	CVolumeWnd		m_VolWnd;
	CSeekWnd		m_SeekWnd;

	long OnSendPlayingInfo(UINT wParam,LPARAM lparam);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSteveMediaPlayerCtrl)
	public:
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CSteveMediaPlayerCtrl();

	DECLARE_OLECREATE_EX(CSteveMediaPlayerCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CSteveMediaPlayerCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CSteveMediaPlayerCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CSteveMediaPlayerCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CSteveMediaPlayerCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CSteveMediaPlayerCtrl)
	short m_nLeftPos;
	afx_msg void OnNLeftPosChanged();
	short m_nTopPos;
	afx_msg void OnNTopPosChanged();
	short m_nRightPos;
	afx_msg void OnNRightPosChanged();
	short m_nBottomPos;
	afx_msg void OnNBottomPosChanged();
	short m_volumeLeftOffset;
	afx_msg void OnVolumeLeftOffsetChanged();
	short m_volumeRightOffset;
	afx_msg void OnVolumeRightOffsetChanged();
	afx_msg void ResizeMyControl(short nWidth, short nHeight);
	afx_msg void Previous();
	afx_msg void Next();
	afx_msg void Play();
	afx_msg void Stop();
	afx_msg void Pause();
	afx_msg void FullScreen();
	afx_msg void LowerVolume();
	afx_msg void IncreaseVolume();
	afx_msg void ShowPlayList();
	afx_msg void Mute();
	afx_msg void Rewind();
	afx_msg void Forward();
	afx_msg void ShowVolumeControl();
	afx_msg void ShowSeekControl();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CSteveMediaPlayerCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

	BEGIN_INTERFACE_PART(ObjectSafety, IObjectSafety)
		STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD __RPC_FAR *pdwSupportedOptions, DWORD __RPC_FAR *pdwEnabledOptions);
		STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);
	END_INTERFACE_PART(ObjectSafety)

	DECLARE_INTERFACE_MAP();

// Dispatch and event IDs
public:
	UINT m_TimerPlayerReady;
	enum {
	//{{AFX_DISP_ID(CSteveMediaPlayerCtrl)
	dispidNLeftPos = 1L,
	dispidNTopPos = 2L,
	dispidNRightPos = 3L,
	dispidNBottomPos = 4L,
	dispidVolumeLeftOffset = 5L,
	dispidVolumeRightOffset = 6L,
	dispidResizeMyControl = 7L,
	dispidPrevious = 8L,
	dispidNext = 9L,
	dispidPlay = 10L,
	dispidStop = 11L,
	dispidPause = 12L,
	dispidSetFilePath = 13L,
	dispidLowerVolume = 14L,
	dispidIncreaseVolume = 15L,
	dispidShowPlayList = 16L,
	dispidMute = 17L,
	dispidFullScreen = 13L,
	dispidRewind = 18L,
	dispidForward = 19L,
	dispidShowVolumeControl = 20L,
	dispidShowSeekControl = 21L,
	//}}AFX_DISP_ID
	};
	friend class CMyMessageWnd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEVEMEDIAPLAYERCTL_H__08512BD6_C614_43D0_B6F6_D590ECD810F7__INCLUDED)
