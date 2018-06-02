#if !defined(AFX_IECOMCTRLSINK_H__6E51B128_CD88_4EAD_821E_41D4FE9E09EC__INCLUDED_)
#define AFX_IECOMCTRLSINK_H__6E51B128_CD88_4EAD_821E_41D4FE9E09EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IEComCtrlSink.h : header file
//

#include <afxmt.h>
#include <exdisp.h> //For IWebBrowser2* and others
#include <exdispid.h>
/////////////////////////////////////////////////////////////////////////////
// CIEComCtrlSink command target

class CIEComCtrlSink : public CCmdTarget
{
	DECLARE_DYNCREATE(CIEComCtrlSink)

	CIEComCtrlSink();           // protected constructor used by dynamic creation
	afx_msg void OnQuit();
	afx_msg void BeforeNavigate2(LPDISPATCH pDisp, VARIANT FAR *url, VARIANT FAR *Flags, VARIANT FAR *TargetFrameName, VARIANT FAR *PostData, VARIANT FAR *Headers, VARIANT_BOOL* Cancel);

	IWebBrowser2* m_pWebBrowser2;
	IWebBrowserApp* m_pIEApp;

// Attributes
public:
	CWnd m_wndWebBrowser;
	BOOL Navigate(CString strURL);

// Operations
public:
	CCriticalSection m_CritSection;
	void SetNoTopMost();
	BOOL m_bCanLoadAWebPage;
	int m_bIsPlayList;
	void SetClientSize(int x,int y);
	CString m_strCurrentURL;
	BOOL m_bOpenedByMe;
	void MoveWindow(LPCRECT lpRect);
	void GetWindowRect(LPRECT lpRect) const;
	BOOL CreateMyWindow(CString strTitle, CRect rect);
	void ShowWindow(UINT nShow);
	BOOL Navigate2(CString strURL);

	BOOL UnAdviseSink();
	DWORD m_dwCookie;
	BOOL CreateMyObject();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIEComCtrlSink)
	//}}AFX_VIRTUAL

	virtual ~CIEComCtrlSink();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIEComCtrlSink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	DECLARE_DISPATCH_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IECOMCTRLSINK_H__6E51B128_CD88_4EAD_821E_41D4FE9E09EC__INCLUDED_)
