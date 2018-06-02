#if !defined(AFX_HTTPSOCK_H__6442C4EF_3956_457E_AE9D_4652C9548D20__INCLUDED_)
#define AFX_HTTPSOCK_H__6442C4EF_3956_457E_AE9D_4652C9548D20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HttpSock.h : header file
//

#include "MsgSockWndHTTP.h"
class CJob;
/////////////////////////////////////////////////////////////////////////////
// CHttpSock command target

class CHttpSock : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CHttpSock();
	virtual ~CHttpSock();

// Overrides
public:
	CFile m_fileSave;
	void FailedCRCCheck();
	UINT m_nTimerCalcSpeed;
	int m_nTimeOut;
	void CalculateSpeed();
	CTime m_startTime;
	long m_lTotalSize;
	void Finished();
	BOOL m_bSaveFile;
	BOOL m_bDoResume;
	BOOL m_bIsUsingProxy;
	CString m_strDownloadPath;
	long m_lBytesStart;
	int m_nHTTPStatus;
	long m_lReceived;
	long m_lSent;
	CString m_strReply;
	void ResetStrings();
	CJob* m_pParent;
	void ConnectAsync();
	CString m_strURL;
	void CancelAsyncLookup();
	BOOL SaveBytes(char* pChar,int nLen,BOOL bTimer = TRUE);

	int m_nPort;
	void Retry();
	CString m_strSend;
	CString m_strConnect;
	BOOL StartDownload();
	CMsgSockWndHTTP m_MsgWnd;
	int m_nTries;
	HANDLE m_hRequest;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHttpSock)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CHttpSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTTPSOCK_H__6442C4EF_3956_457E_AE9D_4652C9548D20__INCLUDED_)
