#if !defined(AFX_TIMEDSHUTDOWNDLG_H__AF1FE749_E938_4746_A304_8090671E75E0__INCLUDED_)
#define AFX_TIMEDSHUTDOWNDLG_H__AF1FE749_E938_4746_A304_8090671E75E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimedShutdownDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimedShutdownDlg dialog
#include "MyButton.h"
#include "Mystatic.h"

class CTimedShutdownDlg : public CDialog
{
// Construction
public:
	SECJpeg* m_pImage;
	CTimedShutdownDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTimedShutdownDlg();

	void LoadImage(CString strPath);

// Dialog Data
	//{{AFX_DATA(CTimedShutdownDlg)
	enum { IDD = IDD_TIME_SHUTDOWN };
	CMyButton	m_ctlTimeChoice;
	CMyButton	m_ctl4;
	CMyStatic	m_ctlOr;
	CMyStatic	m_static4;
	CMyButton	m_ctlStopAtEnd;
	CMyButton	m_ctl1;
	CMyBitMapButton	m_ctlOK;
	CMyBitMapButton	m_ctlCancel;
	CMyStatic	m_ctlText;
	CString	m_strMinutes;
	BOOL	m_bShutdown;
	BOOL	m_bLowerVolume;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimedShutdownDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimedShutdownDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnShutdownAfterLastSong();
	afx_msg void OnTimeToPlayChoice();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMEDSHUTDOWNDLG_H__AF1FE749_E938_4746_A304_8090671E75E0__INCLUDED_)
