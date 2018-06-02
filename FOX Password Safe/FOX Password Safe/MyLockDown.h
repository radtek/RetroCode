#pragma once


// CMyLockDown

class CMyLockDown : public CWnd
{
	DECLARE_DYNAMIC(CMyLockDown)

public:
	CMyLockDown();
	virtual ~CMyLockDown();

protected:
	DECLARE_MESSAGE_MAP()

	// handle to hook dll
	HINSTANCE m_hinstHookDLL;
	// timer for end lockdown
	UINT m_TimerUnlockBrowser;
public:
	// start lock down measures
	void StartLockDown(BOOL bAutoEndLockdown);
	// end lock down
	void EndLockdown(void);
	afx_msg void OnTimer(UINT nIDEvent);
	// start hooking messages
	void StartHook(void);
	// end hooking functions
	void EndHook(void);	
};


