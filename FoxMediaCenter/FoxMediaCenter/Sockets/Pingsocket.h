#if !defined(AFX_PINGSOCKET_H__DDB5EA92_0B66_4B05_9D7A_43A99EF26054__INCLUDED_)
#define AFX_PINGSOCKET_H__DDB5EA92_0B66_4B05_9D7A_43A99EF26054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PingSocket.h : header file
//

#include "MsgSockWndPost.h"
class CPingJob;
/////////////////////////////////////////////////////////////////////////////
// CPingSocket command target

class CPingSocket : public CAsyncSocket
{
// Attributes
public:
	CMsgSockWndPost m_MsgWnd;
	CPingJob* m_pParent;

// Operations
public:
	CPingSocket();
	virtual ~CPingSocket();
	void Retry(BOOL bRetryMsg = TRUE);
	void CancelAsyncLookup();
	BOOL StartDownload();
	void ResetStrings();
	void ConnectAsync();

// Overrides
public:
	long m_lBytesReceived;
	long m_lURLFileSize;
	BOOL m_bStartRec;
	CString m_strRecData;
	long m_lReceived;
	CString m_strSend;
	long m_lSent;
	void RemoveSpaces();
	int m_nPort;
	CString m_strConnect;
	CString m_strURL;
	BOOL m_bIsUsingProxy;
	int m_nTries;
	HANDLE m_hRequest;
	void Finished();
	void Send302Retry();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPingSocket)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CPingSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PINGSOCKET_H__DDB5EA92_0B66_4B05_9D7A_43A99EF26054__INCLUDED_)
