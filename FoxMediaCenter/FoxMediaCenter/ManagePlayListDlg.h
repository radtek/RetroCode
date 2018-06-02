#if !defined(AFX_MANAGEPLAYLISTDLG_H__38EC9557_3253_42D6_AD77_E32FA653D97A__INCLUDED_)
#define AFX_MANAGEPLAYLISTDLG_H__38EC9557_3253_42D6_AD77_E32FA653D97A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManagePlayListDlg.h : header file
//
#include "MyTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CManagePlayListDlg dialog

class CManagePlayListDlg : public CDialog
{
// Construction
public:
	void SaveScreenPos();
	CString m_strSelectedFile;
	BOOL SaveCurrentPlayLists();
	void ReloadPlayLists();
	CManagePlayListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CManagePlayListDlg)
	enum { IDD = IDD_MANAGE_PLAYLIST };
	CMyBitMapButton	m_butPlaySelected;
	CMyBitMapButton	m_butNewPlayList;
	CMyBitMapButton	m_butNewRandom;
	CMyBitMapButton	m_butDelete;
	CMyBitMapButton	m_butAdd;
	CMyBitMapButton	m_butCancel;
	CMyBitMapButton	m_butOK;
	CMyBitMapButton	m_butRename;
	CMyTreeCtrl	m_ctlTreePlaylists;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManagePlayListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	long OnPlaySelected(WPARAM wParam,LPARAM lParam);

	// Generated message map functions
	//{{AFX_MSG(CManagePlayListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnNewPlaylist();
	afx_msg void OnRenamePlaylist();
	afx_msg void OnDelete();
	afx_msg void OnAddFiles();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPlaySelected();
	afx_msg void OnNewNormalPlaylist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGEPLAYLISTDLG_H__38EC9557_3253_42D6_AD77_E32FA653D97A__INCLUDED_)
