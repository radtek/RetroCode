// MyIEWnd.h: interface for the CMyIEWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYIEWND_H__785160A0_357C_4C2C_B0C1_C98CACF18C76__INCLUDED_)
#define AFX_MYIEWND_H__785160A0_357C_4C2C_B0C1_C98CACF18C76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WebBrowser2.h"

class CMyIEWnd : public CWnd  
{
public:
	BOOL Navigate(CString strPath);
	BOOL Navigate2(CString strPath);
	CMyIEWnd();
	virtual ~CMyIEWnd();

	CWebBrowser2* m_pIEWnd;

	BOOL m_bCanLoadAWebPage;
	int m_bIsPlayList;
	CString m_strCurrentURL;
	BOOL m_bOpenedByMe;
	BOOL CreateMyWindow();

		// Generated message map functions
	//{{AFX_MSG(CMyIEWnd)
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDownloadCompleteExplorer1();
	afx_msg void OnBeforeNavigate2Explorer1(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel);
	afx_msg void OnDocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT FAR* URL);
	afx_msg void OnOnQuitExplorer1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_MYIEWND_H__785160A0_357C_4C2C_B0C1_C98CACF18C76__INCLUDED_)
