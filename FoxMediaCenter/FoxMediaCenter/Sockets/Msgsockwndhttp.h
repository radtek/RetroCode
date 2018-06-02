#if !defined(AFX_MSGSOCKWNDHTTP_H__686AFFD0_0A96_47FC_A8A8_5D2763E30F68__INCLUDED_)
#define AFX_MSGSOCKWNDHTTP_H__686AFFD0_0A96_47FC_A8A8_5D2763E30F68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgSockWndHTTP.h : header file
//
class CHttpSock;
/////////////////////////////////////////////////////////////////////////////
// CMsgSockWndHTTP window

class CMsgSockWndHTTP : public CWnd
{
// Construction
public:
	CMsgSockWndHTTP();

// Attributes
public:
	char m_buf[MAXGETHOSTSTRUCT]; // DNS lookup reply
	UINT m_TimerConnect;
	CHttpSock* m_pParent;
// Operations
public:
   LONG OnHostName(UINT wParam, LONG lParam); 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgSockWndHTTP)
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_strIPAddress;
	UINT m_TimerRead;
	virtual ~CMsgSockWndHTTP();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMsgSockWndHTTP)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGSOCKWNDHTTP_H__686AFFD0_0A96_47FC_A8A8_5D2763E30F68__INCLUDED_)
