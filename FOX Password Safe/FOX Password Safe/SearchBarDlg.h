#pragma once
#include "afxwin.h"
#include "MyBmButton.h"

// CSearchBarDlg dialog

class CSearchBarDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchBarDlg)

public:
	CSearchBarDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchBarDlg();

// Dialog Data
	enum { IDD = IDD_SEARCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSearch();

	CMyBmButton m_ctlSearch;
	CBitmap		m_bmSearch1;
	CBitmap		m_bmSearch2;
	virtual BOOL OnInitDialog();
};
