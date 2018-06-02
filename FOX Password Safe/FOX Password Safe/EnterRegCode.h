#pragma once


// CEnterRegCode dialog

class CEnterRegCode : public CDialog
{
	DECLARE_DYNAMIC(CEnterRegCode)

public:
	CEnterRegCode(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEnterRegCode();

// Dialog Data
	enum { IDD = IDD_ENTER_REG_CODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// user name
	CString m_strName;
	// company name
	CString m_strCompany;
	// registration code
	CString m_strRegCode;
	virtual BOOL OnInitDialog();
};
