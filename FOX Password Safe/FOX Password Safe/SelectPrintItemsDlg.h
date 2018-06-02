#pragma once
#include "afxcmn.h"


// CSelectPrintItemsDlg dialog
#include "MyPrintListCtrl.h"

class CSelectPrintItemsDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectPrintItemsDlg)

public:
	CSelectPrintItemsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectPrintItemsDlg();

// Dialog Data
	enum { IDD = IDD_CHOOSE_SELECT_PRINT_ITEMS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

	CImageList m_ImageList;
public:
	afx_msg void OnBnClickedOk();
	// [int,out] selected items to print
	CStringArray* m_pstraItems;
	virtual BOOL OnInitDialog();
	// list box control
	CMyPrintListCtrl m_crlList;
};
