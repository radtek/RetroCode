// RegKeyGeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RegKeyGenerator.h"
#include "RegKeyGeneratorDlg.h"
#include ".\regkeygeneratordlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CRegKeyGeneratorDlg dialog



CRegKeyGeneratorDlg::CRegKeyGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegKeyGeneratorDlg::IDD, pParent)
	, m_strKeysNeeded(_T(""))
	, m_strRegCodesText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegKeyGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM_KEYS, m_strKeysNeeded);
	DDX_Text(pDX, IDC_EDIT_REG_CODES, m_strRegCodesText);
}

BEGIN_MESSAGE_MAP(CRegKeyGeneratorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CRegKeyGeneratorDlg message handlers

BOOL CRegKeyGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	srand((unsigned)time(NULL));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRegKeyGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRegKeyGeneratorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRegKeyGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRegKeyGeneratorDlg::OnBnClickedOk()
{
	UpdateData(true);

	CString strCodes;
	int nCodes = atoi(m_strKeysNeeded);
	if(nCodes < 1 || nCodes > 10000)
		nCodes = 1;

	for(int n=0;n<nCodes;n++)
	{
		CString strNewNum = CreateGUID();
		int nRand = 0;
		
		// first sect, last 2 number add to 5
		nRand = (rand() / (RAND_MAX / 4 + 1)) + 1;
		CString str1;
		if(nRand == 1)
			str1 = "41";
		else if(nRand == 2)
			str1 = "50";
		else if(nRand == 3)
			str1 = "32";
		else
			str1 = "14";
		// append number
		CString strTemp = strNewNum.Left(strNewNum.Find('-'));
		strTemp += str1;
		strTemp += strNewNum.Mid(strNewNum.Find('-'));
		strNewNum = strTemp;

		// 2nd last sect, 1st and 4th digit are vowels A E I O U
		nRand = (rand() / (RAND_MAX / 5 + 1)) + 1;
		CString str2;
		if(nRand == 1)
			str2 = "A";
		else if(nRand == 2)
			str2 = "E";
		else if(nRand == 3)
			str2 = "I";
		else if(nRand == 4)
			str2 = "O";
		else
			str2 = "U";
		nRand = (rand() / (RAND_MAX / 5 + 1)) + 1;
		CString str3;
		if(nRand == 1)
			str3 = "A";
		else if(nRand == 2)
			str3 = "E";
		else if(nRand == 3)
			str3 = "I";
		else if(nRand == 4)
			str3 = "O";
		else
			str3 = "U";

		int n2ndDash = strNewNum.ReverseFind('-');
		strTemp = strNewNum.Left(n2ndDash);
		n2ndDash = strTemp.ReverseFind('-');
		n2ndDash -= 1; //  for dashes
		strTemp = strNewNum.Mid(n2ndDash+2); // find middle spot in 3rd set
		strTemp.SetAt(0,str2[0]);
		strTemp.SetAt(3,str3[0]);
		strTemp = strNewNum.Left(n2ndDash+2) + strTemp;
		strNewNum = strTemp;

		// last sect, first and last number add to 6
		nRand = (rand() / (RAND_MAX / 4 + 1)) + 1;
		CString str4,str5;
		if(nRand == 1)
		{
			str4 = "5";
			str5 = "1";
		}
		else if(nRand == 2)
		{
			str4 = "2";
			str5 = "4";
		}
		else if(nRand == 3)
		{
			str4 = "3";
			str5 = "3";
		}
		else
		{
			str4 = "6";
			str5 = "0";
		}
		
		strTemp = strNewNum.Mid(strNewNum.ReverseFind('-')+1);
		strTemp.SetAt(0,str4[0]);
		strTemp.SetAt(strTemp.GetLength()-1,str5[0]);
		strNewNum = strNewNum.Left(strNewNum.ReverseFind('-')+1);
		strNewNum += strTemp;

		if(IsRegCodeGood(strNewNum))
			strCodes += strNewNum + "\r\n";
		else
			AfxMessageBox(strNewNum + " is bad code");
	}
	
	m_strRegCodesText = strCodes;
	
	UpdateData(false);
}

