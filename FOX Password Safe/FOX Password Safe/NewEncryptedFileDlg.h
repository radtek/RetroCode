#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "atlcomtime.h"


// CNewEncryptedFileDlg dialog

class CNewEncryptedFileDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewEncryptedFileDlg)

public:
	CNewEncryptedFileDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewEncryptedFileDlg();

// Dialog Data
	enum { IDD = IDD_ENTER_NEW_ENCRYPTED_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// methods
	virtual BOOL OnInitDialog();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonShowPassword();
	afx_msg void OnBnClickedButtonGeneratePassword();
	afx_msg void OnBnClickedButtonShowPasswordPrevious();
	afx_msg void OnBnClickedButtonBrowse();
	afx_msg void OnBnClickedCheckNeverExpires();

	// return newly created entry
	CString GetNewData(void);

	// properties
	CString m_strComboHeading;
	CString m_strDescription;
	CComboBox m_ctlComboHeading;
	CEdit m_ctlPassword1;
	CEdit m_ctlPassword2;
	CDateTimeCtrl m_ctlDateExpire;
	CString m_strNotes;
	BOOL m_bPassNeverExpires;
	BOOL m_bUseAZ;
	BOOL m_bUseaz;
	BOOL m_bUse09;
	BOOL m_UseSpecialChars;
	CString m_strExcludeChars;
	CString m_strPassLength;
	CEdit m_ctlPreviousPassword;
	CButton m_ctlPreviousPassButton;
	CString m_strFilePath;
	CStringArray* m_pstraEntries;	

	CString m_strCurrentData;
	CString m_strNewEntry;
	CString	m_strPasswordLoaded;
	CString m_strPasswordOld;
	CString m_strSelectHeader;
	afx_msg void OnBnClickedUnencrypt();
	// hide file name using random chars
	BOOL m_bHideFileName;
	CButton m_ctlUnEncrypt;
	CButton m_ctlEncryptButton;
};
