#if !defined(AFX_MSGSOCKWNDPOST_H__A6A5ED1D_DADC_4A77_83F9_917FCED7C5BF__INCLUDED_)
#define AFX_MSGSOCKWNDPOST_H__A6A5ED1D_DADC_4A77_83F9_917FCED7C5BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgSockWndPost.h : header file
//
class CPingSocket;
/////////////////////////////////////////////////////////////////////////////
// CMsgSockWndPost window

class CMsgSockWndPost : public CWnd
{
// Construction
public:
	CMsgSockWndPost();

// Attributes
public:
	char m_buf[MAXGETHOSTSTRUCT]; // DNS lookup reply
	UINT m_TimerConnect;
	CPingSocket* m_pParent;
	UINT m_TimerRead;
	CString m_strIPAddress;

// Operations
public:
   LONG OnHostName(UINT wParam, LONG lParam); 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgSockWndPost)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMsgSockWndPost();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMsgSockWndPost)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGSOCKWNDPOST_H__A6A5ED1D_DADC_4A77_83F9_917FCED7C5BF__INCLUDED_)
