#pragma once


// CNewCategoryDlg dialog

class CNewCategoryDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewCategoryDlg)

public:
	CNewCategoryDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewCategoryDlg();

// Dialog Data
	enum { IDD = IDD_ENTER_NEW_CATEGORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// name of new category to save
	CString m_strCatName;
	// return new category name
	CString GetNewName(void);
	// current category to edit
	CString m_strCurrentHeader;
	virtual BOOL OnInitDialog();
};
