#if !defined(AFX_NEWRANDOMPLAYLISTDLG_H__9C8F8E9D_F256_4243_9034_78BD3B378C53__INCLUDED_)
#define AFX_NEWRANDOMPLAYLISTDLG_H__9C8F8E9D_F256_4243_9034_78BD3B378C53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewRandomPlaylistDlg.h : header file
//
#include "MyStatic.h"
#include "MyButton.h"
#include "MyListBox.h"
/////////////////////////////////////////////////////////////////////////////
// CNewRandomPlaylistDlg dialog

class CNewRandomPlaylistDlg : public CDialog
{
// Construction
public:
	CNewRandomPlaylistDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewRandomPlaylistDlg)
	enum { IDD = IDD_NEW_RANDOM_PLAYLIST };
	CMyListBox	m_ctlListOfExts;
	CMyListBox	m_ctlListOfDirs;
	CString	m_strDirPath;
	CString	m_strFileExt;
	BOOL	m_bRandomEachTime;
	CString	m_strMaxFiles;
	CString	m_strPlaylistName;
	CMyBitMapButton	m_ctlOK;
	CMyBitMapButton	m_ctlCancel;
	CMyBitMapButton	m_ctlB1;
	CMyBitMapButton	m_ctlB2;
	CMyBitMapButton	m_ctlB3;
	CMyBitMapButton	m_ctlB4;

	CMyStatic	m_static1;
	CMyStatic	m_static2;
	CMyStatic	m_static3;
	CMyStatic	m_static4;
	CMyStatic	m_static5;
	CMyStatic	m_static6;
	CMyStatic	m_static7;
	CMyButton	m_ctl1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewRandomPlaylistDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewRandomPlaylistDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddDirTolist();
	afx_msg void OnAddExtention();
	afx_msg void OnBrowse();
	afx_msg void OnRandomPlaylistHelp();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWRANDOMPLAYLISTDLG_H__9C8F8E9D_F256_4243_9034_78BD3B378C53__INCLUDED_)
