// NewEncryptedFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "NewEncryptedFileDlg.h"
#include ".\newencryptedfiledlg.h"
#include "helpers.h"
#include "MainFrm.h"

// CNewEncryptedFileDlg dialog

IMPLEMENT_DYNAMIC(CNewEncryptedFileDlg, CDialog)
CNewEncryptedFileDlg::CNewEncryptedFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewEncryptedFileDlg::IDD, pParent)
	, m_strComboHeading(_T(""))
	, m_strDescription(_T(""))
	, m_strNotes(_T(""))
	, m_bPassNeverExpires(FALSE)
	, m_bUseAZ(FALSE)
	, m_bUseaz(FALSE)
	, m_bUse09(FALSE)
	, m_UseSpecialChars(FALSE)
	, m_strExcludeChars(_T(""))
	, m_strPassLength(_T(""))
	, m_strFilePath(_T(""))
	, m_bHideFileName(FALSE)
{
}

CNewEncryptedFileDlg::~CNewEncryptedFileDlg()
{
}

void CNewEncryptedFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_HEADING, m_strComboHeading);
	DDX_Text(pDX, IDC_EDIT_DESC, m_strDescription);
	DDX_Control(pDX, IDC_COMBO_HEADING, m_ctlComboHeading);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_ctlPassword1);
	DDX_Control(pDX, IDC_EDIT_PASSWORD2, m_ctlPassword2);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctlDateExpire);
	DDX_Text(pDX, IDC_EDIT_NOTES, m_strNotes);
	DDX_Check(pDX, IDC_CHECK_NEVER_EXPIRES, m_bPassNeverExpires);
	DDX_Check(pDX, IDC_CHECK_USE_A_Z, m_bUseAZ);
	DDX_Check(pDX, IDC_CHECK_USE_A_Z_LOWER, m_bUseaz);
	DDX_Check(pDX, IDC_CHECK_USE_0_9, m_bUse09);
	DDX_Check(pDX, IDC_CHECK_USE_SPECIAL_CHARS, m_UseSpecialChars);
	DDX_Text(pDX, IDC_EDIT_EXCLUDE_CHARS, m_strExcludeChars);
	DDX_Text(pDX, IDC_EDIT_PASSWORD_LENGTH, m_strPassLength);
	DDX_Control(pDX, IDC_EDIT_PASSWORD_PREVIOUS, m_ctlPreviousPassword);
	DDX_Control(pDX, IDC_BUTTON_SHOW_PASSWORD_PREVIOUS, m_ctlPreviousPassButton);
	DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_strFilePath);
	DDX_Check(pDX, IDC_CHECK_HIDE_FILENAME, m_bHideFileName);
	DDX_Control(pDX, IDB_UNENCRYPT, m_ctlUnEncrypt);
	DDX_Control(pDX, IDOK, m_ctlEncryptButton);
}


BEGIN_MESSAGE_MAP(CNewEncryptedFileDlg, CDialog)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_PASSWORD, OnBnClickedButtonShowPassword)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE_PASSWORD, OnBnClickedButtonGeneratePassword)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_PASSWORD_PREVIOUS, OnBnClickedButtonShowPasswordPrevious)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDC_CHECK_NEVER_EXPIRES, OnBnClickedCheckNeverExpires)
	ON_BN_CLICKED(IDB_UNENCRYPT, OnBnClickedUnencrypt)
END_MESSAGE_MAP()


// CNewEncryptedFileDlg message handlers

BOOL CNewEncryptedFileDlg::OnInitDialog()
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

	m_bPassNeverExpires = (MyGetProfileInt("DefaultPassNeverExpires",0) == 1);
	COleDateTime time = COleDateTime::GetCurrentTime();
	time += COleDateTimeSpan(MyGetProfileInt("DefaultPassExpireInDays",30));
	m_ctlDateExpire.SetTime(time);

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
	m_ctlPreviousPassword.EnableWindow(false);
	m_ctlPreviousPassButton.EnableWindow(false);

	// if m_strCurrentData not empty then edit entry
	if(!m_strCurrentData.IsEmpty())
	{
		m_ctlEncryptButton.SetWindowText(_T("Save changes"));
		m_ctlUnEncrypt.EnableWindow();
		SetWindowText("FOX Password Safe - Edit Entry");
		m_strComboHeading = ParseXML("Header",m_strCurrentData);
		m_strDescription = ParseXML("Description",m_strCurrentData);
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
		m_strFilePath = ParseXML("FilePath",m_strCurrentData);

		m_strNotes = ParseXML("Notes",m_strCurrentData);
		m_bHideFileName = (ParseXML("HideName",m_strCurrentData) == "1");
		CString strExpires = ParseXML("Expires",m_strCurrentData);
		if(!strExpires.IsEmpty())
		{
			BOOL bHasExpired = false;
			ConvertToDateString(strExpires,bHasExpired);
			if(bHasExpired)
			{
				COleDateTime tm = COleDateTime::GetCurrentTime();
				tm += COleDateTimeSpan(MyGetProfileInt("DefaultPassExpireInDays",30));				
				m_ctlDateExpire.SetTime(tm);
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
				m_ctlDateExpire.SetTime(&tm);
				m_bPassNeverExpires = false;
			}
		}
		else
			m_bPassNeverExpires = true;
	}
	m_ctlDateExpire.EnableWindow(!m_bPassNeverExpires);

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CNewEncryptedFileDlg::OnDropFiles(HDROP hDropInfo)
{
	CDialog::OnDropFiles(hDropInfo);
	
	DragQueryFile(hDropInfo,0,m_strFilePath.GetBuffer(MAX_PATH),MAX_PATH);
	m_strFilePath.ReleaseBuffer();

	if(m_strDescription.IsEmpty())
		m_strDescription = m_strFilePath.Mid(m_strFilePath.ReverseFind('\\') + 1);

	UpdateData(false);
}

void CNewEncryptedFileDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CNewEncryptedFileDlg::OnBnClickedButtonShowPassword()
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

// create a random password
void CNewEncryptedFileDlg::OnBnClickedButtonGeneratePassword()
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

void CNewEncryptedFileDlg::OnBnClickedButtonShowPasswordPrevious()
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

void CNewEncryptedFileDlg::OnBnClickedButtonBrowse()
{
	CFileDialog dlg(true);
	if(dlg.DoModal() == IDOK)
	{
		m_strFilePath = dlg.GetPathName();
		if(m_strDescription.IsEmpty())
			m_strDescription = m_strFilePath.Mid(m_strFilePath.ReverseFind('\\') + 1);
		UpdateData(false);
	}
}

void CNewEncryptedFileDlg::OnBnClickedCheckNeverExpires()
{
	m_bPassNeverExpires?m_bPassNeverExpires=false:m_bPassNeverExpires=true;
	m_ctlDateExpire.EnableWindow(!m_bPassNeverExpires);
}

// return newly created entry
CString CNewEncryptedFileDlg::GetNewData(void)
{
	return m_strNewEntry;
}

void CNewEncryptedFileDlg::OnBnClickedOk()
{
	UpdateData(true);
	// verify data
	if(m_strComboHeading.IsEmpty())
	{
		AfxMessageBox("Error, please enter a category to place this file under.");
		return;
	}
	if(m_strFilePath.IsEmpty())
	{
		AfxMessageBox("Error, please enter a file to encrypt.");
		return;
	}
	if(!FileExists(m_strFilePath))
	{
		if(!m_strCurrentData.IsEmpty())
		{
			if(!UnEncryptFile(m_strCurrentData))
			{
				AfxMessageBox("Error failed to unencrypt file. The file needs to be unencrypted before this entry can be updated...");
				return;
			}
			if(!FileExists(m_strFilePath))
			{
				AfxMessageBox("Error, file to encrypt does not exist.");
				return;
			}
		}
		else
		{
			AfxMessageBox("Error, file to encrypt does not exist.");
			return;
		}
	}
	// check passwords
	CString strPassword1;
	CString strPassword2;
	m_ctlPassword1.GetWindowText(strPassword1.GetBuffer(4028),4028);
	strPassword1.ReleaseBuffer();
	m_ctlPassword2.GetWindowText(strPassword2.GetBuffer(4028),4028);
	strPassword2.ReleaseBuffer();

	// trim whitespace from user and password
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
		m_ctlDateExpire.GetTime(&sysTime);
		SystemTimeToFileTime(&sysTime,&fileTime);
		ULARGE_INTEGER n64Time;
		n64Time.HighPart = fileTime.dwHighDateTime;
		n64Time.LowPart = fileTime.dwLowDateTime;
		strTime.Format("%I64u",n64Time);
	}
	if(m_strPasswordLoaded != strPassword1)
		m_strPasswordOld = m_strPasswordLoaded;
	
	CString strEncFile = m_strFilePath;
	if(!m_bHideFileName)
	{
		strEncFile += ".enc";
	}
	else
	{
		strEncFile = strEncFile.Left(strEncFile.ReverseFind('\\') + 1);
		strEncFile += GetGUID() + ".enc";
	}
	// rename old encrypted file to new name
	if(!m_strCurrentData.IsEmpty())
	{
		CString strOldFile = ParseXML("EncFilePath",m_strCurrentData);
		if(FileExists(strOldFile))
			MoveFile(strOldFile,strEncFile);
	}

	m_strNotes = MakeTextSafeForXML(m_strNotes);

	// save new data
	m_strNewEntry.Format("<Entry><Header>%s</Header><Description>%s</Description><EncryptedFile>TRUE</EncryptedFile><Password>%s</Password><Expires>%s</Expires><FilePath>%s</FilePath><EncFilePath>%s</EncFilePath><PasswordOld>%s</PasswordOld><HideName>%d</HideName><Notes>%s</Notes></Entry>",
		m_strComboHeading,m_strDescription,strPassword1,strTime,m_strFilePath,strEncFile,m_strPasswordOld,m_bHideFileName?1:0,m_strNotes);

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if(m_strCurrentData.IsEmpty() && pMain->EncryptFileAlreadyExists(m_strNewEntry))
	{
		AfxMessageBox("Error, you already have an entry for this file. Only one entry is allowed for the same file.");
		return;
	}

	OnOK();
}

// unencrypt file
void CNewEncryptedFileDlg::OnBnClickedUnencrypt()
{
	// rename old encrypted file to new name
	if(!m_strCurrentData.IsEmpty())
	{
		if(UnEncryptFile(m_strCurrentData))
		{
			AfxMessageBox("File has been unencrypted successfully.");
			return;
		}
	}
	AfxMessageBox("Error, file could not be unencrypted");
}
