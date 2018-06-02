#if !defined(AFX_FILEASSOCIATIONDLG_H__D116E9FA_6AB4_4460_B7C0_27943BDF3215__INCLUDED_)
#define AFX_FILEASSOCIATIONDLG_H__D116E9FA_6AB4_4460_B7C0_27943BDF3215__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileAssociationDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileAssociationDlg dialog
#include "MyButton.h"
#include "Mystatic.h"

class CFileAssociationDlg : public CDialog
{
// Construction
public:
	void RemoveCheckOfKnowType(CString strExt);
	void AddToList(CString strExt,BOOL bIsAudio);
	BOOL IsAssociatedType(CString strExt);
	void Associate(CString strExt,BOOL bIsAudio);
	void UnAssociate(CString strExt);
	CFileAssociationDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileAssociationDlg)
	enum { IDD = IDD_FILE_ASSOCIATION };
	CMyButton		m_ctlQuicktime;
	CMyBitMapButton	m_ctlOK;
	CMyBitMapButton	m_ctlRemoveBut;
	CMyBitMapButton	m_ctlNewBut;
	CListCtrl		m_ctlList;
	CMyButton		m_ctlWinVid;
	CMyButton		m_ctlWinAu;
	CMyButton		m_ctlOgg;
	CMyButton		m_ctlMpg;
	CMyButton		m_ctlMp3;
	CMyButton		m_ctlDivx;
	CMyStatic		m_ctlText2;
	CMyStatic		m_ctlText1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileAssociationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileAssociationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMp3();
	afx_msg void OnMpg();
	afx_msg void OnOgg();
	afx_msg void OnWinAudio();
	afx_msg void OnWinVideo();
	afx_msg void OnDivx();
	afx_msg void OnRemove();
	afx_msg void OnNewTypeButton();
	afx_msg void OnQuicktime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEASSOCIATIONDLG_H__D116E9FA_6AB4_4460_B7C0_27943BDF3215__INCLUDED_)
