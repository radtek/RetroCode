#if !defined(AFX_UPDATEMANAGER_H__DC912264_4947_4F9D_B0AA_C20ABC65B6A5__INCLUDED_)
#define AFX_UPDATEMANAGER_H__DC912264_4947_4F9D_B0AA_C20ABC65B6A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateManager.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUpdateManager window

class CUpdateManager : public CWnd
{
// Construction
public:
	CUpdateManager();

// Attributes
public:
	CStringArray m_straJobs;
// Operations
public:
	void SaveData();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateManager)
	//}}AFX_VIRTUAL

// Implementation
public:
	void RunUpdateExe();
	UINT m_TimerRetryFail;
	BOOL IsURLAlreadyInUpdateList(CString strURL);
	BOOL NewUpdate(CString strParams,BOOL bTimerRetry=FALSE);
	virtual ~CUpdateManager();

private:
	void Serialize(CArchive& ar);
	// Generated message map functions
protected:
	//{{AFX_MSG(CUpdateManager)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATEMANAGER_H__DC912264_4947_4F9D_B0AA_C20ABC65B6A5__INCLUDED_)
