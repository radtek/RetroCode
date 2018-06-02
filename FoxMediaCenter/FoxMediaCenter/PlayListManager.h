// PlayListManager.h: interface for the CPlayListManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYLISTMANAGER_H__ECEBFB17_D142_4338_8AE1_2B5FB29F15D0__INCLUDED_)
#define AFX_PLAYLISTMANAGER_H__ECEBFB17_D142_4338_8AE1_2B5FB29F15D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame;

class CPlayListManager  
{
public:
	CString MakeNewRandomList(CString strData);
	BOOL CheckFileIsStillValid(CString strFilePath);
	void DeletePlayList(CString strName);
	void UpdatePlayList(CString strName,CStringArray* pstra);
	BOOL SaveNewPlayList(CString strFileName,CString strData);
	CString GetNextRandomPlaylistName();
	CStringArray* GetEntriesForName(CString strName,BOOL bReturnRandName=false);
	void SaveCurrent(CStringArray* pstra,CString strCurrent);
	long LoadCurrent(BOOL bResetOcx=true,BOOL bStopPlaying=true,BOOL bCanReloadRandom=false);
	CPlayListManager();
	virtual ~CPlayListManager();
	CStringArray* GetPlayListNames();

	CMainFrame* m_pMainWnd;

};

#endif // !defined(AFX_PLAYLISTMANAGER_H__ECEBFB17_D142_4338_8AE1_2B5FB29F15D0__INCLUDED_)
