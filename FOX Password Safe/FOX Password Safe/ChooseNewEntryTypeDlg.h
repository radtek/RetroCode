#pragma once
#include "afxwin.h"


// CChooseNewEntryTypeDlg dialog

class CChooseNewEntryTypeDlg : public CDialog
{
	DECLARE_DYNAMIC(CChooseNewEntryTypeDlg)

public:
	CChooseNewEntryTypeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CChooseNewEntryTypeDlg();

// Dialog Data
	enum { IDD = IDD_CHOOSE_NEW_ENTRY_TYPE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioPassword();
	afx_msg void OnBnClickedRadioCreditCard();
	// new username password entry
	BOOL m_bUserNameCheck;
	// new credit card type
	BOOL m_bCreditCardChecked;
	// new category
	BOOL m_bNewcategory;
	// new encrypted file
	BOOL m_bNewEncryptedFile;
	// password check control
	CButton m_ctlPassword;
	// credit card check control
	CButton m_ctlCreditCard;
	CButton m_ctlNewCat;
	afx_msg void OnBnClickedRadioNewCategory();
	CButton m_ctlEncFile;
	afx_msg void OnBnClickedRadioEncryptedFile();
};
