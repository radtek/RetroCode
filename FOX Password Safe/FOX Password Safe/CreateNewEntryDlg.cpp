// CreateNewEntryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "CreateNewEntryDlg.h"
#include ".\createnewentrydlg.h"
#include "helpers.h"


// CCreateNewEntryDlg dialog

IMPLEMENT_DYNAMIC(CCreateNewEntryDlg, CDialog)
CCreateNewEntryDlg::CCreateNewEntryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateNewEntryDlg::IDD, pParent)
	, m_strCombHeading(_T(""))
	, m_strDescription(_T(""))
	, m_strUserName(_T(""))
	, m_ctldDateExpire(COleDateTime::GetCurrentTime())
	, m_bPassNeverExpires(FALSE)
	, m_strURL(_T(""))
	, m_strNotes(_T(""))
	, m_bUseAZ(FALSE)
	, m_bUseaz(FALSE)
	, m_bUse09(FALSE)
	, m_UseSpecialChars(FALSE)
	, m_strExcludeChars(_T(""))
	, m_pstraEntries(NULL)
	, m_strPassLength(_T(""))
	, m_strNewEntry(_T(""))
	, m_strCurrentData(_T(""))
	, m_strSelectHeader(_T(""))
	, m_bLockDownBrowser(true)
{	
}

CCreateNewEntryDlg::~CCreateNewEntryDlg()
{
}

void CCreateNewEntryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_HEADING, m_ctlComboHeading);
	DDX_CBString(pDX, IDC_COMBO_HEADING, m_strCombHeading);
	DDX_Text(pDX, IDC_EDIT_DESC, m_strDescription);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_ctlPassword1);
	DDX_Control(pDX, IDC_EDIT_PASSWORD2, m_ctlPassword2);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_ctldDateExpire);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctlDateExpire);
	DDX_Check(pDX, IDC_CHECK_NEVER_EXPIRES, m_bPassNeverExpires);
	DDX_Text(pDX, IDC_EDIT_URL, m_strURL);
	DDX_Text(pDX, IDC_EDIT_NOTES, m_strNotes);
	DDX_Check(pDX, IDC_CHECK_USE_A_Z, m_bUseAZ);
	DDX_Check(pDX, IDC_CHECK_USE_A_Z_LOWER, m_bUseaz);
	DDX_Check(pDX, IDC_CHECK_USE_0_9, m_bUse09);
	DDX_Check(pDX, IDC_CHECK_USE_SPECIAL_CHARS, m_UseSpecialChars);
	DDX_Text(pDX, IDC_EDIT_EXCLUDE_CHARS, m_strExcludeChars);
	DDX_Text(pDX, IDC_EDIT_PASSWORD_LENGTH, m_strPassLength);
	DDX_Check(pDX, IDC_CHECK_LOCK_BROWSER, m_bLockDownBrowser);
	DDX_Control(pDX, IDC_EDIT_PASSWORD_PREVIOUS, m_ctlPreviousPassword);
	DDX_Control(pDX, IDC_BUTTON_SHOW_PASSWORD_PREVIOUS, m_ctlPreviousPassButton);
}

BEGIN_MESSAGE_MAP(CCreateNewEntryDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE_PASSWORD, OnBnClickedButtonGeneratePassword)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_PASSWORD, OnBnClickedButtonShowPassword)
	ON_BN_CLICKED(IDC_CHECK_NEVER_EXPIRES, OnBnClickedCheckNeverExpires)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_PASSWORD_PREVIOUS, OnBnClickedButtonShowPasswordPrevious)
END_MESSAGE_MAP()

BOOL CCreateNewEntryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_strPassLength = "8";
	m_bUseAZ = true;
	m_bUseaz = true;
	m_bUse09 = true;
	m_UseSpecialChars = false;
	m_strExcludeChars = MyGetProfileString("PassExcludeChars","");
	m_ctlPassword1.SetPasswordChar('*');
	m_ctlPassword2.SetPasswordChar('*');
	m_bLockDownBrowser = true;

	m_bPassNeverExpires = (MyGetProfileInt("DefaultPassNeverExpires",0) == 1);
	COleDateTime time = COleDateTime::GetCurrentTime();
	time += COleDateTimeSpan(MyGetProfileInt("DefaultPassExpireInDays",30));
	m_ctldDateExpire = time;

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
		m_strCombHeading = m_strSelectHeader;
	}
	m_ctlPreviousPassword.EnableWindow(false);
	m_ctlPreviousPassButton.EnableWindow(false);

	// if m_strCurrentData not empty then edit entry
	if(!m_strCurrentData.IsEmpty())
	{
		SetWindowText("FOX Password Safe - Edit Entry");
		m_strCombHeading = ParseXML("Header",m_strCurrentData);
		m_strDescription = ParseXML("Description",m_strCurrentData);
		m_strUserName = ParseXML("UserID",m_strCurrentData);
		m_strPasswordLoaded = ParseXML("Password",m_strCurrentData);
		m_ctlPassword1.SetWindowText(m_strPasswordLoaded);
		m_ctlPassword2.SetWindowText(m_strPasswordLoaded);
		m_strPasswordOld = ParseXML("PasswordOld",m_strCurrentData);
		if(!m_strPasswordOld.IsEmpty())
		{
			m_ctlPreviousPassword.EnableWindow(true);
			m_ctlPreviousPassButton.EnableWindow(true);
			m_ctlPreviousPassword.SetWindowText(m_strPasswordOld);
		}
		m_strURL = ParseXML("URL",m_strCurrentData);
		m_strNotes = ParseXML("Notes",m_strCurrentData);
		CString strExpires = ParseXML("Expires",m_strCurrentData);
		if(!strExpires.IsEmpty())
		{
			BOOL bHasExpired = false;
			ConvertToDateString(strExpires,bHasExpired);
			if(bHasExpired)
			{
				COleDateTime tm = COleDateTime::GetCurrentTime();
				tm += COleDateTimeSpan(MyGetProfileInt("DefaultPassExpireInDays",30));				
				m_ctldDateExpire.SetDate(tm.GetYear(),tm.GetMonth(),tm.GetDay());
				m_bPassNeverExpires = false;
			}
			else
			{
				ULARGE_INTEGER n64Time;
				n64Time.QuadPart = _atoi64(strExpires);
				FILETIME fileTime;
				fileTime.dwHighDateTime = n64Time.HighPart;
				fileTime.dwLowDateTime = n64Time.LowPart;
				CTime tm(fileTime);	
				m_ctldDateExpire.SetDate(tm.GetYear(),tm.GetMonth(),tm.GetDay());
				m_bPassNeverExpires = false;
			}
		}
		else
			m_bPassNeverExpires = true;
		m_bLockDownBrowser = (ParseXML("LockDownBrowser",m_strCurrentData) == "TRUE");
	}
	m_ctlDateExpire.EnableWindow(!m_bPassNeverExpires);

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CCreateNewEntryDlg::OnBnClickedButtonShowPassword()
{
	if(m_ctlPassword1.GetStyle() & ES_PASSWORD)
	{
		m_ctlPassword1.SetPasswordChar(0);
		m_ctlPassword2.SetPasswordChar(0);
	}
	else
	{
		m_ctlPassword1.SetPasswordChar('*');
		m_ctlPassword2.SetPasswordChar('*');
	}
	m_ctlPassword1.RedrawWindow();
	m_ctlPassword2.RedrawWindow();
}

// return newly created entry
CString CCreateNewEntryDlg::GetNewData(void)
{
	return m_strNewEntry;
}

// create a random password
void CCreateNewEntryDlg::OnBnClickedButtonGeneratePassword()
{
	UpdateData(true);
	// save exclude chars
	MyWriteProfileString("PassExcludeChars",m_strExcludeChars);
	
	int nPassLen = atoi(m_strPassLength);
	if(nPassLen <= 0)
	{
		AfxMessageBox("Error, password length has to be greater than zero.");
		return;
	}
	int nTumbles = 0;
	int nTumbleMatrix[4][2];
	if(m_bUseAZ)
	{
		nTumbleMatrix[nTumbles][0] = 65;
		nTumbleMatrix[nTumbles][1] = 26;
		nTumbles ++;
	}
	if(m_bUseaz)
	{
		nTumbleMatrix[nTumbles][0] = 97;
		nTumbleMatrix[nTumbles][1] = 26;
		nTumbles ++;
	}
	if(m_bUse09)
	{
		nTumbleMatrix[nTumbles][0] = 48;
		nTumbleMatrix[nTumbles][1] = 10;
		nTumbles ++;
	}
	if(m_UseSpecialChars)
	{
		nTumbleMatrix[nTumbles][0] = 33;
		nTumbleMatrix[nTumbles][1] = 15;
		nTumbles ++;
	}
	if(nTumbles == 0)
	{
		AfxMessageBox("Error, you need to choose at least one option to create a random password.");
		return;
	}
	int nGeneratedChars = 0;
	int nTries = 0;
	CString strNewPassword;
	srand((unsigned)time(NULL));
	while(nGeneratedChars < nPassLen && (nGeneratedChars + nTries) < (nPassLen + 10000))
	{
		nTries ++;
		// work out which char to randomly choose
		int nUseTumble = rand()%nTumbles;
		char nChar = rand()%nTumbleMatrix[nUseTumble][1] + nTumbleMatrix[nUseTumble][0];
		if(m_strExcludeChars.IsEmpty() || m_strExcludeChars.Find(nChar) == -1)
		{
			strNewPassword += nChar;
			nGeneratedChars ++;
		}
	}
	m_ctlPassword1.SetWindowText(strNewPassword);
	m_ctlPassword2.SetWindowText(strNewPassword);
}

void CCreateNewEntryDlg::OnBnClickedCheckNeverExpires()
{
	m_bPassNeverExpires?m_bPassNeverExpires=false:m_bPassNeverExpires=true;
	m_ctlDateExpire.EnableWindow(!m_bPassNeverExpires);
}

// CCreateNewEntryDlg message handlers
void CCreateNewEntryDlg::OnBnClickedOk()
{
	UpdateData(true);
	// verify data
	// check passwords
	CString strPassword1;
	CString strPassword2;
	m_ctlPassword1.GetWindowText(strPassword1.GetBuffer(4028),4028);
	strPassword1.ReleaseBuffer();
	m_ctlPassword2.GetWindowText(strPassword2.GetBuffer(4028),4028);
	strPassword2.ReleaseBuffer();

	// trim whitespace from user and password
	m_strUserName.Trim();
	strPassword1.Trim("");
	strPassword2.Trim("");
	if(strPassword1 != strPassword2)
	{
		AfxMessageBox("Error, passwords do not match please try again.");
		return;
	}
	// check description not empty
	if(m_strDescription.IsEmpty())
	{
		AfxMessageBox("Error, you must enter a description.");
		return;
	}
	CString strTime;
	if(!m_bPassNeverExpires)
	{
		SYSTEMTIME sysTime; 
		FILETIME fileTime;
		m_ctldDateExpire.GetAsSystemTime(sysTime);
		SystemTimeToFileTime(&sysTime,&fileTime);
		ULARGE_INTEGER n64Time;
		n64Time.HighPart = fileTime.dwHighDateTime;
		n64Time.LowPart = fileTime.dwLowDateTime;
		strTime.Format("%I64u",n64Time);
	}
	if(m_strPasswordLoaded != strPassword1)
		m_strPasswordOld = m_strPasswordLoaded;
	// save new data
	m_strNewEntry.Format("<Entry><Header>%s</Header><Description>%s</Description><CreditCard>FALSE</CreditCard><UserID>%s</UserID><Password>%s</Password><URL>%s</URL><Expires>%s</Expires><LockDownBrowser>%s</LockDownBrowser><PasswordOld>%s</PasswordOld><Notes>%s</Notes></Entry>",
		m_strCombHeading,m_strDescription,m_strUserName,strPassword1,m_strURL,strTime,m_bLockDownBrowser?"TRUE":"FALSE",m_strPasswordOld,m_strNotes);

	OnOK();
}


void CCreateNewEntryDlg::OnBnClickedButtonShowPasswordPrevious()
{
	if(m_ctlPreviousPassword.GetStyle() & ES_PASSWORD)
	{
		m_ctlPreviousPassword.SetPasswordChar(0);
	}
	else
	{
		m_ctlPreviousPassword.SetPasswordChar('*');
	}
	m_ctlPreviousPassword.RedrawWindow();
}
