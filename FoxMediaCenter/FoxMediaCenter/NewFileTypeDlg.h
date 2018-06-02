#if !defined(AFX_NEWFILETYPEDLG_H__DE2BED00_D30E_4A44_80C3_33E3CF054910__INCLUDED_)
#define AFX_NEWFILETYPEDLG_H__DE2BED00_D30E_4A44_80C3_33E3CF054910__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewFileTypeDlg.h : header file
//

#include "MyButton.h"
#include "MyStatic.h"

class CNewFileTypeDlg : public CDialog
{
// Construction
public:
	CString m_strFileExt;
	BOOL m_bIsAudio;
	CNewFileTypeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewFileTypeDlg)
	enum { IDD = IDD_NEW_ASSOC_FILE_TYPE };
	CMyButton	m_ctlVideo;
	CMyButton	m_ctlAudio;
	CMyBitMapButton	m_but2;
	CMyBitMapButton	m_but1;
	CMyStatic	m_ctlText3;
	CMyStatic	m_ctlText2;
	CMyStatic	m_ctlText1;
	CString	m_strFileType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewFileTypeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewFileTypeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnAudio();
	afx_msg void OnVideo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWFILETYPEDLG_H__DE2BED00_D30E_4A44_80C3_33E3CF054910__INCLUDED_)
