// ChooseNewEntryTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "ChooseNewEntryTypeDlg.h"
#include ".\choosenewentrytypedlg.h"


// CChooseNewEntryTypeDlg dialog

IMPLEMENT_DYNAMIC(CChooseNewEntryTypeDlg, CDialog)
CChooseNewEntryTypeDlg::CChooseNewEntryTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseNewEntryTypeDlg::IDD, pParent)
	, m_bUserNameCheck(FALSE)
	, m_bCreditCardChecked(FALSE)
{
	
}

CChooseNewEntryTypeDlg::~CChooseNewEntryTypeDlg()
{
}

void CChooseNewEntryTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_PASSWORD, m_ctlPassword);
	DDX_Control(pDX, IDC_RADIO_CREDIT_CARD, m_ctlCreditCard);
	DDX_Control(pDX, IDC_RADIO_NEW_CATEGORY, m_ctlNewCat);
	DDX_Control(pDX, IDC_RADIO_ENCRYPTED_FILE, m_ctlEncFile);
}


BEGIN_MESSAGE_MAP(CChooseNewEntryTypeDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_PASSWORD, OnBnClickedRadioPassword)
	ON_BN_CLICKED(IDC_RADIO_CREDIT_CARD, OnBnClickedRadioCreditCard)
	ON_BN_CLICKED(IDC_RADIO_NEW_CATEGORY, OnBnClickedRadioNewCategory)
	ON_BN_CLICKED(IDC_RADIO_ENCRYPTED_FILE, OnBnClickedRadioEncryptedFile)
END_MESSAGE_MAP()


// CChooseNewEntryTypeDlg message handlers
BOOL CChooseNewEntryTypeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bUserNameCheck = true;
	m_bCreditCardChecked = false;	
	m_bNewcategory = false;
	m_bNewEncryptedFile = false;
	m_ctlPassword.SetCheck(BST_CHECKED);
	m_ctlCreditCard.SetCheck(BST_UNCHECKED);
	m_ctlNewCat.SetCheck(BST_UNCHECKED);
	m_ctlEncFile.SetCheck(BST_UNCHECKED);

	return TRUE;  
}

void CChooseNewEntryTypeDlg::OnBnClickedOk()
{
	OnOK();
}

void CChooseNewEntryTypeDlg::OnBnClickedRadioPassword()
{
	m_bUserNameCheck = true;
	m_bCreditCardChecked = false;
	m_bNewcategory = false;
	m_bNewEncryptedFile = false;
	m_ctlPassword.SetCheck(BST_CHECKED);
	m_ctlCreditCard.SetCheck(BST_UNCHECKED);
	m_ctlNewCat.SetCheck(BST_UNCHECKED);
	m_ctlEncFile.SetCheck(BST_UNCHECKED);
}

void CChooseNewEntryTypeDlg::OnBnClickedRadioCreditCard()
{
	m_bUserNameCheck = false;
	m_bCreditCardChecked = true;
	m_bNewcategory = false;
	m_bNewEncryptedFile = false;
	m_ctlPassword.SetCheck(BST_UNCHECKED);
	m_ctlCreditCard.SetCheck(BST_CHECKED);
	m_ctlNewCat.SetCheck(BST_UNCHECKED);
	m_ctlEncFile.SetCheck(BST_UNCHECKED);
}

void CChooseNewEntryTypeDlg::OnBnClickedRadioNewCategory()
{
	m_bUserNameCheck = false;
	m_bCreditCardChecked = false;
	m_bNewcategory = true;
	m_bNewEncryptedFile = false;
	m_ctlPassword.SetCheck(BST_UNCHECKED);
	m_ctlCreditCard.SetCheck(BST_UNCHECKED);
	m_ctlNewCat.SetCheck(BST_CHECKED);
	m_ctlEncFile.SetCheck(BST_UNCHECKED);
}

void CChooseNewEntryTypeDlg::OnBnClickedRadioEncryptedFile()
{
	m_bUserNameCheck = false;
	m_bCreditCardChecked = false;
	m_bNewcategory = false;
	m_bNewEncryptedFile = true;
	m_ctlPassword.SetCheck(BST_UNCHECKED);
	m_ctlCreditCard.SetCheck(BST_UNCHECKED);
	m_ctlNewCat.SetCheck(BST_UNCHECKED);
	m_ctlEncFile.SetCheck(BST_CHECKED);
}
