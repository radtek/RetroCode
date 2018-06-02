#pragma once
#include "afxwin.h"
#include "atlcomtime.h"
#include "afxdtctl.h"


// CCreateNewEntryDlg dialog

class CCreateNewEntryDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateNewEntryDlg)

public:
	CCreateNewEntryDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCreateNewEntryDlg();

// Dialog Data
	enum { IDD = IDD_ENTER_NEW_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// combo control used to select or create a main header
	CComboBox m_ctlComboHeading;
	// string value of combo heading
	CString m_strCombHeading;
	// description of new entry
	CString m_strDescription;
	// entry username or ID
	CString m_strUserName;
	// control of password 1
	CEdit m_ctlPassword1;
	// control of password 2
	CEdit m_ctlPassword2;
	// previous password if its updated
	CString m_strPasswordOld;
	// test to see if password changed
	CString m_strPasswordLoaded;
	// Date password expires
	COleDateTime m_ctldDateExpire;
	// control of date expire
	CDateTimeCtrl m_ctlDateExpire;
	// password never expires check
	BOOL m_bPassNeverExpires;
	// web site URL
	CString m_strURL;
	// misc notes
	CString m_strNotes;
	// use A - Z chars
	BOOL m_bUseAZ;
	// use a - z chars
	BOOL m_bUseaz;
	// use 0 - 9 chars
	BOOL m_bUse09;
	// use special chars
	BOOL m_UseSpecialChars;
	// exclude these chars from password
	CString m_strExcludeChars;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonGeneratePassword();
	afx_msg void OnBnClickedButtonShowPassword();
	virtual BOOL OnInitDialog();
	// return newly created entry
	CString GetNewData(void);
	// pointer to a list of main headers
	CStringArray* m_pstraEntries;
	// length of auto generated password
	CString m_strPassLength;
	afx_msg void OnBnClickedCheckNeverExpires();
	// newly created password entry
	CString m_strNewEntry;
	// current entry data to edit
	CString m_strCurrentData;
	// if not empty select this entry in drop down
	CString m_strSelectHeader;
	// lock down browser before loading web site
	BOOL m_bLockDownBrowser;
	// previous password read only backup
	CEdit m_ctlPreviousPassword;
	afx_msg void OnBnClickedButtonShowPasswordPrevious();
	// previous password button
	CButton m_ctlPreviousPassButton;
};
