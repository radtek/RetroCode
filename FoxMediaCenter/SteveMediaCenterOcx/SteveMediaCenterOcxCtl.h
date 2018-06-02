#if !defined(AFX_STEVEMEDIACENTEROCXCTL_H__7D489DD1_A68C_43E8_8BE5_AC94AD9DE4A8__INCLUDED_)
#define AFX_STEVEMEDIACENTEROCXCTL_H__7D489DD1_A68C_43E8_8BE5_AC94AD9DE4A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SteveMediaCenterOcxCtl.h : Declaration of the CSteveMediaCenterOcxCtrl ActiveX Control class.

#include "MyListCtrl.h"
#include "MyMessageWnd.h"
#include "VolumeWnd.h"
#include "SeekWnd.h"


class CSteveMediaCenterOcxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CSteveMediaCenterOcxCtrl)

// Constructor
public:
	CSteveMediaCenterOcxCtrl();

	CMyListCtrl		m_ctlPlayList;
	CMyMessageWnd	m_msgWnd;
	CVolumeWnd		m_VolWnd;
	CSeekWnd		m_SeekWnd;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSteveMediaCenterOcxCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CSteveMediaCenterOcxCtrl();

	DECLARE_OLECREATE_EX(CSteveMediaCenterOcxCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CSteveMediaCenterOcxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CSteveMediaCenterOcxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CSteveMediaCenterOcxCtrl)		// Type name and misc status

	long OnPlayAll(WPARAM wParam,LPARAM lParam);
	long OnPlayAllFromSelected(WPARAM wParam,LPARAM lParam);
	
// Message maps
	//{{AFX_MSG(CSteveMediaCenterOcxCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnFileSettings();
	afx_msg void OnFileActivetimedshutdown();
	afx_msg void OnFileSelectskin();
	afx_msg void OnFileSelectplaylist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CSteveMediaCenterOcxCtrl)
	CString m_mediaTitle;
	afx_msg void OnMediaTitleChanged();
	CString m_mediaLength;
	afx_msg void OnMediaLengthChanged();
	CString m_mediaArtist;
	afx_msg void OnMediaArtistChanged();
	CString m_mediaBitrate;
	afx_msg void OnMediaBitrateChanged();
	CString m_currentMediaPosition;
	afx_msg void OnCurrentMediaPositionChanged();
	CString m_hexBackGroundColor;
	afx_msg void OnHexBackGroundColorChanged();
	CString m_hexTextColor;
	afx_msg void OnHexTextColorChanged();
	CString m_strJpgBKImageFilePath;
	afx_msg void OnJpgBKImageFilePathChanged();
	long m_jpgBKOriginXPoint;
	afx_msg void OnJpgBKOriginXPointChanged();
	long m_jpgBKOriginYPoint;
	afx_msg void OnJpgBKOriginYPointChanged();
	CString m_hexSelectTextColor;
	afx_msg void OnHexSelectTextColorChanged();
	CString m_hexSelectedBKColor;
	afx_msg void OnHexSelectedBKColorChanged();
	short m_nAlignText012;
	afx_msg void OnNAlignText012Changed();
	CString m_strScollingTextMsg;
	afx_msg void OnScollingTextMsgChanged();
	short m_volumeLeftOffset;
	afx_msg void OnVolumeLeftOffsetChanged();
	short m_volumeRightOffset;
	afx_msg void OnVolumeRightOffsetChanged();
	afx_msg BOOL PlaySelected();
	afx_msg BOOL Play();
	afx_msg BOOL Pause();
	afx_msg BOOL Stop();
	afx_msg void ClearPlayList();
	afx_msg void Mute();
	afx_msg void LowerVolume();
	afx_msg void IncreaseVolume();
	afx_msg void AddToPlayList(LPCTSTR strFilePath);
	afx_msg void ShowOpenFileDialog();
	afx_msg void ShowManagePlayList();
	afx_msg void Previous();
	afx_msg void Next();
	afx_msg void ShowSelectSkin();
	afx_msg void Rewind();
	afx_msg void Forward();
	afx_msg void ShowPopUpMenu();
	afx_msg void ShowVolumeControl();
	afx_msg void ShowSeekControl();
	afx_msg BOOL IsPlayListEmpty();
	afx_msg void SkinUpdate(LPCTSTR strParams);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CSteveMediaCenterOcxCtrl)
	void FireChangeCurrentMediaInfo()
		{FireEvent(eventidChangeCurrentMediaInfo,EVENT_PARAM(VTS_NONE));}
	void FireUpdatePlayPosition()
		{FireEvent(eventidUpdatePlayPosition,EVENT_PARAM(VTS_NONE));}
	void FireUpdateScrollingText()
		{FireEvent(eventidUpdateScrollingText,EVENT_PARAM(VTS_NONE));}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()


	BEGIN_INTERFACE_PART(ObjectSafety, IObjectSafety)
		STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD __RPC_FAR *pdwSupportedOptions, DWORD __RPC_FAR *pdwEnabledOptions);
		STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);
	END_INTERFACE_PART(ObjectSafety)

	DECLARE_INTERFACE_MAP();


// Dispatch and event IDs
public:
	
	enum {
	//{{AFX_DISP_ID(CSteveMediaCenterOcxCtrl)
	dispidMediaTitle = 1L,
	dispidMediaLength = 2L,
	dispidMediaArtist = 3L,
	dispidMediaBitrate = 4L,
	dispidCurrentMediaPosition = 5L,
	dispidHexBackGroundColor = 6L,
	dispidHexTextColor = 7L,
	dispidJpgBKImageFilePath = 8L,
	dispidJpgBKOriginXPoint = 9L,
	dispidJpgBKOriginYPoint = 10L,
	dispidHexSelectTextColor = 11L,
	dispidHexSelectedBKColor = 12L,
	dispidNAlignText012 = 13L,
	dispidScollingTextMsg = 14L,
	dispidVolumeLeftOffset = 15L,
	dispidVolumeRightOffset = 16L,
	dispidPlaySelected = 17L,
	dispidPlay = 18L,
	dispidPause = 19L,
	dispidStop = 20L,
	dispidClearPlayList = 21L,
	dispidMute = 22L,
	dispidLowerVolume = 23L,
	dispidIncreaseVolume = 24L,
	dispidAddToPlayList = 25L,
	dispidShowOpenFileDialog = 26L,
	dispidShowManagePlayList = 27L,
	dispidPrevious = 28L,
	dispidNext = 29L,
	dispidShowSelectSkin = 30L,
	dispidRewind = 31L,
	dispidForward = 32L,
	dispidShowPopUpMenu = 33L,
	dispidShowVolumeControl = 34L,
	dispidShowSeekControl = 35L,
	dispidIsPlayListEmpty = 36L,
	dispidSkinUpdate = 37L,
	eventidChangeCurrentMediaInfo = 1L,
	eventidUpdatePlayPosition = 2L,
	eventidUpdateScrollingText = 3L,
	//}}AFX_DISP_ID
	};

	friend class CMyMessageWnd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEVEMEDIACENTEROCXCTL_H__7D489DD1_A68C_43E8_8BE5_AC94AD9DE4A8__INCLUDED)
