#pragma once
#include "afxwin.h"


// CNewCreditCardEntryDlg dialog

class CNewCreditCardEntryDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewCreditCardEntryDlg)

public:
	CNewCreditCardEntryDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewCreditCardEntryDlg();

// Dialog Data
	enum { IDD = IDD_ENTER_NEW_CREDIT_CARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// heading control
	CComboBox m_ctlComboHeading;
	// heading string
	CString m_strComboHeading;
	// description string
	CString m_strDescription;
	// Credit card type control
	CComboBox m_ctlCardType;
	// card type string
	CString m_strCardType;
	// card number string
	CString m_strCardNumber;
	// name on card
	CString m_strNameOnCard;
	// card expire date
	CString m_strExpiredate;
	// credit card verification number
	CString m_strCCVNumber;
	// name of bank
	CString m_strBankName;
	// billing name
	CString m_strBillingName;
	// billing company name
	CString m_strBillingCompany;
	// billing address line 1
	CString m_strBillingAddress1;
	// billing address line 2
	CString m_strBillingAddress2;
	// billing city
	CString m_strBillingCity;
	// billing state
	CString m_strBillingState;
	// billing postcode
	CString m_strBillingPostcode;
	// billing country
	CString m_strBillingCountry;
	// billing email address
	CString m_strBillingEmail;
	// billing phone number
	CString m_strBillingPhone;
	virtual BOOL OnInitDialog();
	// array of header fields
	CStringArray* m_pstraEntries;
	// cuurent data for editing
	CString m_strCurrentData;
	// return newly created entry
	CString GetNewData(void);
	CString m_strNewEntry;
	// selected header for dialog
	CString m_strSelectHeader;
};
