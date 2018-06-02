// NewCreditCardEntryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "NewCreditCardEntryDlg.h"
#include ".\newcreditcardentrydlg.h"
#include "helpers.h"

// CNewCreditCardEntryDlg dialog

IMPLEMENT_DYNAMIC(CNewCreditCardEntryDlg, CDialog)
CNewCreditCardEntryDlg::CNewCreditCardEntryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewCreditCardEntryDlg::IDD, pParent)
	, m_strComboHeading(_T(""))
	, m_strDescription(_T(""))
	, m_strCardType(_T(""))
	, m_strCardNumber(_T(""))
	, m_strNameOnCard(_T(""))
	, m_strExpiredate(_T(""))
	, m_strCCVNumber(_T(""))
	, m_strBankName(_T(""))
	, m_strBillingName(_T(""))
	, m_strBillingCompany(_T(""))
	, m_strBillingAddress1(_T(""))
	, m_strBillingAddress2(_T(""))
	, m_strBillingCity(_T(""))
	, m_strBillingState(_T(""))
	, m_strBillingPostcode(_T(""))
	, m_strBillingCountry(_T(""))
	, m_strBillingEmail(_T(""))
	, m_strBillingPhone(_T(""))
	, m_pstraEntries(NULL)
	, m_strCurrentData(_T(""))
	, m_strSelectHeader(_T(""))
{
}

CNewCreditCardEntryDlg::~CNewCreditCardEntryDlg()
{
}

void CNewCreditCardEntryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_HEADING, m_ctlComboHeading);
	DDX_CBString(pDX, IDC_COMBO_HEADING, m_strComboHeading);
	DDX_Text(pDX, IDC_EDIT_DESC, m_strDescription);
	DDX_Control(pDX, IDC_CREDIT_CARD_TYPE, m_ctlCardType);
	DDX_CBString(pDX, IDC_CREDIT_CARD_TYPE, m_strCardType);
	DDX_Text(pDX, IDC_EDIT_CARD_NUMBER, m_strCardNumber);
	DDX_Text(pDX, IDC_EDIT_NAME_ON_CARD, m_strNameOnCard);
	DDX_Text(pDX, IDC_EDIT_EXPIRE_DATE, m_strExpiredate);
	DDX_Text(pDX, IDC_EDIT_CC_VERIFICATION_NUMBER, m_strCCVNumber);
	DDX_Text(pDX, IDC_EDIT_BANK_NAME, m_strBankName);
	DDX_Text(pDX, IDC_EDIT_BILLING_NAME, m_strBillingName);
	DDX_Text(pDX, IDC_EDIT_BILLING_COMPANY, m_strBillingCompany);
	DDX_Text(pDX, IDC_EDIT_BILLING_ADDRESS1, m_strBillingAddress1);
	DDX_Text(pDX, IDC_EDIT_BILLING_ADDRESS2, m_strBillingAddress2);
	DDX_Text(pDX, IDC_EDIT_BILLING_CITY, m_strBillingCity);
	DDX_Text(pDX, IDC_EDIT_BILLING_STATE, m_strBillingState);
	DDX_Text(pDX, IDC_EDIT_BILLING_POSTCODE, m_strBillingPostcode);
	DDX_Text(pDX, IDC_EDIT_BILLING_COUNTRY, m_strBillingCountry);
	DDX_Text(pDX, IDC_EDIT_BILLING_EMAIL, m_strBillingEmail);
	DDX_Text(pDX, IDC_EDIT_BILLING_PHONE, m_strBillingPhone);
}

BEGIN_MESSAGE_MAP(CNewCreditCardEntryDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CNewCreditCardEntryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// load main list headers
	if(m_pstraEntries)
	{
		for(int n=0;n<m_pstraEntries->GetSize();n++)
		{
			CString strHeader = ParseXML("Header",m_pstraEntries->GetAt(n));
			BOOL bFound = false;
			for(int n2=0;n2<m_ctlComboHeading.GetCount();n2++)
			{
				CString strTest;
				m_ctlComboHeading.GetLBText(n2,strTest);
				if(strTest.CompareNoCase(strHeader) == 0)
				{
					bFound = true;
					break;
				}
			}
			if(!bFound)
			{
				m_ctlComboHeading.AddString(strHeader);
			}
		}
		m_strComboHeading = m_strSelectHeader;
	}
	// load card types
	m_ctlCardType.AddString("MasterCard");
	m_ctlCardType.AddString("Visa");
	m_ctlCardType.AddString("Discover");
	m_ctlCardType.AddString("American Express");
	m_strCardType = "MasterCard";

	// if m_strCurrentData not empty then edit entry
	if(!m_strCurrentData.IsEmpty())
	{
		SetWindowText("FOX Password Safe - Edit Credit Card Entry");
		m_strComboHeading = ParseXML("Header",m_strCurrentData);
		m_strDescription = ParseXML("Description",m_strCurrentData);
		m_strCardType = ParseXML("CardType",m_strCurrentData);
		m_strCardNumber = ParseXML("CardNumber",m_strCurrentData);
		m_strNameOnCard  = ParseXML("NameOnCard",m_strCurrentData);
		m_strExpiredate = ParseXML("Expiredate",m_strCurrentData);
		m_strCCVNumber = ParseXML("CCVNumber",m_strCurrentData);
		m_strBankName = ParseXML("BankName",m_strCurrentData);
		m_strBillingName = ParseXML("BillingName",m_strCurrentData);
		m_strBillingCompany = ParseXML("BillingCompany",m_strCurrentData);
		m_strBillingAddress1 = ParseXML("BillingAddress1",m_strCurrentData);
		m_strBillingAddress2 = ParseXML("BillingAddress2",m_strCurrentData);
		m_strBillingCity = ParseXML("BillingCity",m_strCurrentData);
		m_strBillingState = ParseXML("BillingState",m_strCurrentData);
		m_strBillingPostcode = ParseXML("BillingPostcode",m_strCurrentData);
		m_strBillingCountry = ParseXML("BillingCountry",m_strCurrentData);
		m_strBillingEmail = ParseXML("BillingEmail",m_strCurrentData);
		m_strBillingPhone = ParseXML("BillingPhone",m_strCurrentData);
	}

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CNewCreditCardEntryDlg::OnBnClickedOk()
{
	UpdateData(true);
	// verify data
	// check description not empty
	if(m_strDescription.IsEmpty())
	{
		AfxMessageBox("Error, you must enter a description.");
		return;
	}
	// save new data
	m_strNewEntry.Format("<Entry><Header>%s</Header><Description>%s</Description><CreditCard>TRUE</CreditCard><CardType>%s</CardType><CardNumber>%s</CardNumber><NameOnCard>%s</NameOnCard><Expiredate>%s</Expiredate><CCVNumber>%s</CCVNumber><BankName>%s</BankName><BillingName>%s</BillingName>\
						 <BillingCompany>%s</BillingCompany><BillingAddress1>%s</BillingAddress1><BillingAddress2>%s</BillingAddress2>\
						 <BillingCity>%s</BillingCity><BillingState>%s</BillingState><BillingPostcode>%s</BillingPostcode><BillingCountry>%s</BillingCountry>\
						 <BillingEmail>%s</BillingEmail><BillingPhone>%s</BillingPhone></Entry>",
		m_strComboHeading,m_strDescription,m_strCardType,m_strCardNumber,m_strNameOnCard,m_strExpiredate,m_strCCVNumber,
		m_strBankName,m_strBillingName,m_strBillingCompany,m_strBillingAddress1,m_strBillingAddress2,
		m_strBillingCity,m_strBillingState,m_strBillingPostcode,m_strBillingCountry,m_strBillingEmail,m_strBillingPhone);

	OnOK();
}

// return newly created entry
CString CNewCreditCardEntryDlg::GetNewData(void)
{
	return m_strNewEntry;
}


		
