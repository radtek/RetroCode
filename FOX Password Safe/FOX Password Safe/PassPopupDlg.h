#pragma once
#include "afxwin.h"
#include "MyBmButton.h"
#include "myedit.h"

// CPassPopupDlg dialog
class CPassPopupDlg : public CDialog
{
	DECLARE_DYNAMIC(CPassPopupDlg)

public:
	CPassPopupDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPassPopupDlg();

// Dialog Data
	enum { IDD = IDD_PASSWORD_POPUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCopyUser();
	afx_msg void OnBnClickedButtonCopyPass();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonShowPass();

	// white brush
	CBrush m_brush;
	// entry description
	CString m_strDescription;
	// userId
	CString m_strUserID;
	// user password
	CString m_strPassword;
	// set description field
	void SetDescription(CString strDescription);
	// set user ID field
	void SetUserID(CString strUser);
	// set password field
	void SetPassword(CString strPassword);

	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonLoadUrl();
	// set url and show or hide url button
	void SetURL(CString strURl);
	// web site url
	CString m_strURL;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CMyBmButton m_ctlDone;
	CBitmap m_bmDone1;
	CBitmap m_bmDone2;
	CMyBmButton m_ctlCopyUser;
	CBitmap m_bmCopy1;
	CBitmap m_bmCopy2;
	CMyBmButton m_ctlCopyPass;
	CMyBmButton m_ctlShowPass;
	CBitmap m_bmShow1;
	CBitmap m_bmShow2;
	// load web site button
	CMyBmButton m_ctlLoadWebSite;
	CBitmap m_bmLoad1;
	CBitmap m_bmLoad2;
	virtual BOOL OnInitDialog();
	// save position of dlg
	void SaveRectPos(void);
	// restore last saved position 
	void SetLastRectPos(void);
	// userId control
	CMyEdit m_ctlUserID;
	// password control
	CMyEdit m_ctlPassword;
};
