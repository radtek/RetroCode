#if !defined(AFX_NEWPLAYLISTNAMEDLG_H__8E5E37C1_098A_477A_ABF7_B2CC0A25DADF__INCLUDED_)
#define AFX_NEWPLAYLISTNAMEDLG_H__8E5E37C1_098A_477A_ABF7_B2CC0A25DADF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewPlayListNameDlg.h : header file
//
#include "Mystatic.h"

/////////////////////////////////////////////////////////////////////////////
// CNewPlayListNameDlg dialog

class CNewPlayListNameDlg : public CDialog
{
// Construction
public:
	CNewPlayListNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewPlayListNameDlg)
	enum { IDD = IDD_NEW_PLAYLIST_NAME };
	CString	m_strNewName;
	CMyBitMapButton	m_ctlOK;
	CMyBitMapButton	m_ctlCancel;
	CMyStatic	m_ctlText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewPlayListNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewPlayListNameDlg)
	virtual void OnOK();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPLAYLISTNAMEDLG_H__8E5E37C1_098A_477A_ABF7_B2CC0A25DADF__INCLUDED_)
