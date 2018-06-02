#if !defined(AFX_SETTINGSDLG_H__BD7AC98C_DB6E_4922_8848_172E5923933A__INCLUDED_)
#define AFX_SETTINGSDLG_H__BD7AC98C_DB6E_4922_8848_172E5923933A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingsDlg.h : header file
//
#include "MyButton.h"
/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg dialog

class CSettingsDlg : public CDialog
{
// Construction
public:
	void WriteAutoStart(BOOL bAuto);
	CSettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingsDlg)
	enum { IDD = IDD_SETTINGS };
	CMyButton	m_ctl8;
	CMyBitMapButton	m_ctlFileAssocBut;
	CMyButton	m_ctl7;
	CMyButton	m_ctl6;
	CMyButton	m_ctl5;
	CMyButton	m_ctl4;
	CMyButton	m_ctl3;
	CMyButton	m_ctl2;
	CMyButton	m_ctl1;
	CMyBitMapButton	m_ctlOK;
	CMyBitMapButton	m_ctlCancel;
	BOOL	m_bAutoStart;
	BOOL	m_bEnableShortcutKeys;
	BOOL	m_bPreLoadWnds;
	BOOL	m_bHidePlayerWindow;
	BOOL	m_bRepeat;
	BOOL	m_bStartPlayLastSong;
	BOOL	m_bShowPlayListOnStart;
	BOOL	m_bAppendToTemp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingsDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnFileAssociation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSDLG_H__BD7AC98C_DB6E_4922_8848_172E5923933A__INCLUDED_)
