// FOX Password SafeView.h : interface of the CFOXPasswordSafeView class
//


#pragma once

#include "MyEdit.h"
#include "MyButton.h"
#include "CustomPrint.h"
#include "MyIconEdit.h"

class CFOXPasswordSafeView : public CScrollView
{
protected: // create from serialization only
	CFOXPasswordSafeView();
	DECLARE_DYNCREATE(CFOXPasswordSafeView)

// Attributes
public:
	CFOXPasswordSafeDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	afx_msg void OnMyFilePrint();
	afx_msg void OnMyFilePrintPreview();
// Implementation
public:
	virtual ~CFOXPasswordSafeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CCustomPrint m_CustomPrint;
// Generated message map functions
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	afx_msg void OnShowHidePassword();
	afx_msg void OnShowHidePrevPassword();
	DECLARE_MESSAGE_MAP()

	// user password fields
	// description field
	CRect m_rectDesc;
	CMyEdit m_editDesc;
	// username or ID field
	CRect m_rectUsername;
	CMyIconEdit m_editUsername;
	// password field
	CRect m_rectPassword;
	CMyIconEdit m_editPassword;
	// previous password field
	CRect m_rectPreviousPassword;
	CMyIconEdit m_editPreviousPassword;
	// password expire date field
	CRect m_rectPassExpire;
	CMyEdit m_editPassExpire;
	// URL field
	CRect m_rectURL;
	CMyIconEdit m_editURL;
	// Notes field
	CRect m_rectNotes;
	CMyEdit m_editNotes;
	// toggle show password
	CRect m_rectButShowPass;
	CMyButton m_butShowPass;
	CBitmap m_bmShowPass2;
	CBitmap m_bmShowPass1;
	// toggle show previous password
	CRect m_rectButShowPrevPass;
	CMyButton m_butShowPrevPass;
	// credit card fields
	// card type
	CMyIconEdit m_editCardType;
	// card number
	CMyIconEdit m_editCardNumber;
	// name on card
	CMyIconEdit m_editNameOnCard;
	// expire date
	CMyIconEdit m_editExpireDate;
	// CCV number
	CMyIconEdit m_editCCVNumber;
	// bank name
	CMyIconEdit m_editBankName;
	// Billing full name
	CMyIconEdit m_editBillingName;
	// company
	CMyIconEdit m_editCompany;
	// Address line 1
	CMyIconEdit m_editAddress1;
	// Address line 2
	CMyIconEdit m_editAddress2;
	// City
	CMyIconEdit m_editCity;
	// State
	CMyIconEdit m_editState;
	// Postcode
	CMyIconEdit m_editPostcode;
	// Country
	CMyIconEdit m_editCountry;
	// Email
	CMyIconEdit m_editEmail;
	// Phone
	CMyIconEdit m_editPhone;

public:
	// add item to list control
	BOOL InsertListItem(CString strDesc);	
	// save entry data in document
	void SetMyData(CString strData, bool bHeader);
	// Show or hide buttons and edit controls
	void ShowButtons(BOOL bShow,BOOL bIsCreditCard);
	// Get selected username
	BOOL GetSelectedUserName(CString& strReturn);
	// get selected password
	BOOL GetSelectedPassword(CString& strReturn);
	// load selected url in browser
	BOOL GetSelectedURL(CString& strURL,BOOL& bLockDown);
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	// return currently selected XML data
	BOOL GetSelectedUserData(CString& strData);

};

#ifndef _DEBUG  // debug version in FOX Password SafeView.cpp
inline CFOXPasswordSafeDoc* CFOXPasswordSafeView::GetDocument() const
   { return reinterpret_cast<CFOXPasswordSafeDoc*>(m_pDocument); }
#endif

