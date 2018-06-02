// PrintSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "PrintSelectDlg.h"
#include ".\printselectdlg.h"
#include ".\helpers.h"

// CPrintSelectDlg dialog

IMPLEMENT_DYNAMIC(CPrintSelectDlg, CDialog)
CPrintSelectDlg::CPrintSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintSelectDlg::IDD, pParent)
	, m_bPrintSingleItem(1)
	, m_bPrintAllSelected(1)
	, m_bPrintAll(0)
	, m_bDescription(true)
	, m_bUsername(true)
	, m_bPassword(true)
	, m_bWebSite(true)
	, m_bCategory(true)
	, m_PrintDatabasePassword(true)
	, m_strMaxLen(_T(""))
{
}

CPrintSelectDlg::~CPrintSelectDlg()
{
}

void CPrintSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_PRINT1, m_bPrintSingleItem);
	DDX_Radio(pDX, IDC_RADIO_PRINT_ALL_SEL, m_bPrintAllSelected);
	DDX_Radio(pDX, IDC_RADIO_PRINT_ALL, m_bPrintAll);
	DDX_Check(pDX, IDC_CHECK_DESCRIPTION, m_bDescription);
	DDX_Check(pDX, IDC_CHECK_USERNAME, m_bUsername);
	DDX_Check(pDX, IDC_CHECK_PASSWORD, m_bPassword);
	DDX_Check(pDX, IDC_CHECK_WEB_SITE, m_bWebSite);
	DDX_Check(pDX, IDC_CHECK_CATEGORY, m_bCategory);
	DDX_Check(pDX, IDC_CHECK_MASTER_PASS, m_PrintDatabasePassword);
	DDX_Text(pDX, IDC_EDIT_MAX_LEN, m_strMaxLen);
}


BEGIN_MESSAGE_MAP(CPrintSelectDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_PRINT1, OnBnClickedRadioPrint1)
	ON_BN_CLICKED(IDC_RADIO_PRINT_ALL_SEL, OnBnClickedRadioPrintAllSel)
	ON_BN_CLICKED(IDC_RADIO_PRINT_ALL, OnBnClickedRadioPrintAll)
END_MESSAGE_MAP()


// CPrintSelectDlg message handlers

BOOL CPrintSelectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_strMaxLen.Format("%u",MyGetProfileInt(_T("MaxPrintTextLength"),30));
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CPrintSelectDlg::OnBnClickedOk()
{
	UpdateData(true);
	// save max text length
	MyWriteProfileInt(_T("MaxPrintTextLength"),atoi(m_strMaxLen));
	OnOK();
}

void CPrintSelectDlg::OnBnClickedRadioPrint1()
{
	m_bPrintSingleItem = 0;
	m_bPrintAllSelected = 1;
	m_bPrintAll = 1;
	UpdateData(false);
}

void CPrintSelectDlg::OnBnClickedRadioPrintAllSel()
{
	m_bPrintSingleItem = 1;
	m_bPrintAllSelected = 0;
	m_bPrintAll = 1;
	UpdateData(false);
}

void CPrintSelectDlg::OnBnClickedRadioPrintAll()
{
	m_bPrintSingleItem = 1;
	m_bPrintAllSelected = 1;
	m_bPrintAll = 0;
	UpdateData(false);
}
