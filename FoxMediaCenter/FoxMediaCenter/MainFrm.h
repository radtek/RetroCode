// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__0710769A_0DBB_4EF4_AC1C_522F1685480D__INCLUDED_)
#define AFX_MAINFRM_H__0710769A_0DBB_4EF4_AC1C_522F1685480D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChildView.h"
class CMyMediaPlayer;
class CPingJobManager;
class CJobManager;
class CJob;
class CMyIEWnd;

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

	long OnDeleteJob(UINT wParam, LONG lParam);
	long OnRetryJobLater(UINT wParam, LONG lParam);
	long OnFinishedJob(UINT wParam, LONG lParam);
	long OnDeletePlayer(UINT wParam, LONG lParam);
	long OnDeletePlayList(UINT wParam, LONG lParam);
	long OnDeleteAdPage(UINT wParam, LONG lParam);

// Attributes
public:
	SECTrayIcon m_trayIcon;
	CMyIEWnd* m_pIESkin;
	CMyIEWnd* m_pIEPlayer;
	CMyIEWnd* m_pIEAds;
	CMyMediaPlayer* m_pMyMediaPlayer;

	CPingJobManager* m_pPingJobManager;
	CJobManager* m_pJobManager;

// Operations
public:
	long OnTrayIcon(UINT wParam, LONG lParam);
	BOOL LoadPlayListSkin(CString strPath,int nShow=SW_SHOW);
	BOOL LoadPlayerSkin(CString strPath,int nShow=SW_SHOW);
	long OnPreLoadPlayList(UINT wParam, LONG lParam);
	long ShowHidePlayList(UINT wParam, LONG lParam);
	long EndOfVideo(UINT wParam, LONG lParam);
	void StartKeyBoardHook();
	void StopKeyBoardHook();
	long OnKeyboardHookMsg(UINT wParam, LONG lParam);
	long OnVideoPlayerReady(UINT wParam, LONG lParam);

	long OnPlayAllFromSelected(WPARAM wParam,LPARAM lParam);
	long OnPreLoadPlayer(UINT wParam, LONG lParam);
	long OnQuitPreLoadPlayer(UINT wParam, LONG lParam);
	long OnSetCurrentPos(UINT wParam, LONG lParam);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL LoadMessage(CString strData);
	BOOL m_bPopUpPlayList;
	BOOL m_bPaused;
	BOOL m_bIsUnzipping;
	UINT m_TimerSendNewUser;
	void SendNewUserStat();
	void CheckForUpdates(CString strData);
	UINT m_TimerCheckUpdates;
	BOOL HasBeenInstalled();
	void SetInstallParams();
	BOOL m_bShutoffAfterPlayList;
	DWORD m_dwLowerVolVal;
	UINT m_TimerLowerVolume;
	void SetTempPlayList();
	BOOL m_bAutoLoadPlayList;
	void LoadTempPlayList(CStringArray* pstra);
	UINT m_timerLoadSkin;
	void UpdateListFromOCX(CString strData);
	void ClearPlayList(BOOL bResetOcx);
	void SetSelectItemOcx(DWORD dwItem,BOOL bSelect=true);
	long SetSelectItemOcx(CString strName, BOOL bSelect=true);

	void AddToPlayList(CString strNew,BOOL bSendToOcx=false);
	CTime m_timeLastClick;
	UINT m_TimerNoTopMost;
	UINT m_TimerAddToPlayList;
	UINT m_TimerShutDown;
	BOOL m_bTimedShutdownActive;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CChildView    m_wndView;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnFileExit();
	afx_msg void OnFileShowplaylist();
	afx_msg void OnFileHideplaylist();
	afx_msg void OnFileSelectskin();
	afx_msg void OnFileActivatetimedshutdown();
	afx_msg void OnUpdateFileActivatetimedshutdown(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnFilePlay();
	afx_msg void OnFilePause();
	afx_msg void OnFileStop();
	afx_msg void OnFileSettings();
	afx_msg void OnFileSelectplaylist();
	afx_msg void OnFilePrevious();
	afx_msg void OnFileNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__0710769A_0DBB_4EF4_AC1C_522F1685480D__INCLUDED_)
