// MainFrm.h : interface of the CMainFrame class
//


#pragma once

#include "afxcoll.h"
#include "MyDlgBar.h"
#include "trayicon.h"
#include "PassPopupDlg.h"
#include "MyLockDown.h"
#include "MyToolbar.h"
#include "SearchBarWnd.h"

class CFOXPasswordSafeView;

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
	CFOXPasswordSafeView* GetRightPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CReBar      m_wndReBar;
	CMyToolbar	m_wndMyToolbar;
	CSearchBarWnd m_SearchBarWnd;
	CTrayIcon m_trayIcon;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	// show nag dialog once per day if not registered
	void ShowNagScreen(void);
	// sort headers and entries
	void QuickSortEntries(int nLower, int nUpper);
	int PartitionEntries(int nLower, int nUpper);
	afx_msg LRESULT OnStartup( WPARAM, LPARAM );

	// save entries to current file with current password
	BOOL SaveAllEntries(CStringArray *pstra,BOOL bReloadTree = false);

public:
	// load default database or open new database dialog
	BOOL ShowLoadDataBaseScreen(void);
	afx_msg void ShowLoadDataBaseScreenMsg(void);
	// loads passwords into tree and list view
	void LoadTreeData(CString strData,BOOL bCanSave=true);
	// show toolbar for particular view
	void ShowToolBar(TOOLBAR_TYPES eToolbar);
protected:
	// array of password entries
	CStringArray m_straEntries;
private:
	// currently loaded database file
	CString m_strCurrentLoadedPath;
public:
	// password to currently loaded database
	CString m_strCurrentPassword;
	// initialize functions
	void Startup(void);
	afx_msg void OnFileAddnewcategory();
	// show the selected data for this header
	void ShowSelectedHeader(long lArrayPos);
	// show selected body for this entry
	void ShowSelectedEntry(long lArrayPos);
	afx_msg void OnBnClickedCopyUserClip();
	afx_msg void OnBnClickedCopyPassClip();
	afx_msg void OnBnClickedClearClip();
	afx_msg void OnBnClickedLoadUrl();
	afx_msg void OnBnClickedLoadFile();
	afx_msg void OnFileBackup();
	afx_msg void OnFileRestoredatabase();
	afx_msg void OnEditEditselectedcategory();
	afx_msg void OnEditEditselectedentry();
	afx_msg void OnEditDeleteselectedcategory();
	afx_msg void OnEditDeleteselectedentry();
	afx_msg void OnHelpOnlinehelppage();
	afx_msg void OnEditEmptypasswordfromclipboard();
	afx_msg void OnFileChangedatabasepassword();
	afx_msg void OnShowSearchPage();
	afx_msg void OnHelpRegisterfoxpasswordsafe();
	afx_msg void OnHelpEnterregistrationcode();
	afx_msg void OnButtonSearch();
	afx_msg void OnButtonShowAll();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnEditEncryptfileentry();
	afx_msg void OnEditUnencryptfileentry();
	afx_msg void OnToolsLoadselectedencryptedfile();
	afx_msg void OnTraymenuExit();
	afx_msg void OnClickConnectToURL(UINT nID);
	afx_msg void OnTraymenuShowfoxpasswordsafe();
	afx_msg void OnEditLockdownwebbrowser();
	afx_msg void OnEditRestorebrowsertodefault();
	afx_msg void OnShowPopup();
	afx_msg void OnToolsOptions();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	afx_msg void OnFileAddnewentry();
	afx_msg void OnFileNew();
	afx_msg void OnTraymenuEncryptanyunencryptedfiles();
	afx_msg void OnToolsUnencryptbackedupfile();

	LRESULT OnCheckAskPassword(WPARAM, LPARAM);
	LRESULT OnLoadUrl(WPARAM, LPARAM);

	// get single list of item data
	BOOL GetSingleSelectedItemData(LPVOID lpVoid);
	BOOL GetAllItemData(LPVOID lpVoid);
	BOOL GetSelectedItemData(LPVOID lpVoid);
	LRESULT OnSystemTrayMsg(WPARAM wParam,LPARAM lParam);
	// lock down security settings in browser
	void LockDownBrowser(BOOL bAutoUnlock=true);
	// restore the default browser security settings
	void RestoreBrowserSecurity(void);
	// popup password dialog
	CPassPopupDlg* m_pPopupDlg;
	// save position of main window
	void SaveRectPos(void);
	// restore last saved position 
	void SetLastRectPos(void);
	// restore last tree selection
	void SetLastViewSelection();
	// save last tree selection
	void SaveLastViewSelection();
	// timer to unlock browser
	UINT m_TimerUnlockBrowser;
	// timer to check if screen saver running
	UINT m_TimerCheckScreenSaver;
	// only clear once on screen saver
	BOOL m_bHasNotClearedForScreenSaver;
	// lock down class
	CMyLockDown* m_pLockDown;
	// clear passwords from memory
	void CheckClearPasswords(void);
	// timer to clear passwords from memory
	UINT m_TimerClearPasswords;
	// check if screen saver active or workstation locked
	BOOL IsScreenSaverActive(void);
	// clear passwords and information for lock down state
	void ClearPasswordsFromMemory(void);
	// hide window after loading URL option
	void CheckHideAfterLoadingURL();
	// free trial expired
	BOOL m_bHasFreeTrialExpired;
	// showing search bar
	BOOL m_bSearchVisible;
	CString FilterData(CString strData);
	// load url web page or associated file application
	void LoadFileAssociation(BOOL bShowMsg=true);
	// move an item to a new header
	void MoveTreeItem(long lArrayPosSource,long lArrayPosTarget);
	// get string entry
	CString GetStringEntry(int nPos);
	// load and track files application
	void LoadFileObject(CString strXML);
	// check if encryted file paths already exist
	BOOL EncryptFileAlreadyExists(CString strData);	
	afx_msg void OnToolsExportdatatocsvfile();
};


