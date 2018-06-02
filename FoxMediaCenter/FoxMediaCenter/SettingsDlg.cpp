// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "SettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg dialog


CSettingsDlg::CSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingsDlg)
	m_bAutoStart = FALSE;
	m_bEnableShortcutKeys = FALSE;
	m_bPreLoadWnds = FALSE;
	m_bHidePlayerWindow = FALSE;
	m_bRepeat = FALSE;
	m_bStartPlayLastSong = FALSE;
	m_bShowPlayListOnStart = FALSE;
	m_bAppendToTemp = FALSE;
	//}}AFX_DATA_INIT

	m_ctl1.SetColor(RGB(37,80,112));
	m_ctl2.SetColor(RGB(37,80,112));
	m_ctl3.SetColor(RGB(37,80,112));
	m_ctl4.SetColor(RGB(37,80,112));
	m_ctl5.SetColor(RGB(37,80,112));
	m_ctl6.SetColor(RGB(37,80,112));
	m_ctl7.SetColor(RGB(37,80,112));
	m_ctl8.SetColor(RGB(37,80,112));
	m_ctl1.m_dwTextColor = RGB(255,255,255);
	m_ctl2.m_dwTextColor = RGB(255,255,255);
	m_ctl3.m_dwTextColor = RGB(255,255,255);
	m_ctl4.m_dwTextColor = RGB(255,255,255);
	m_ctl5.m_dwTextColor = RGB(255,255,255);
	m_ctl6.m_dwTextColor = RGB(255,255,255);
	m_ctl7.m_dwTextColor = RGB(255,255,255);
	m_ctl8.m_dwTextColor = RGB(255,255,255);
}


void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsDlg)
	DDX_Control(pDX, IDC_APPEND_TO_TEMP, m_ctl8);
	DDX_Control(pDX, IDC_FILE_ASSOCIATION, m_ctlFileAssocBut);
	DDX_Control(pDX, IDC_SHOW_PLAYLIST, m_ctl7);
	DDX_Control(pDX, IDC_AUTO_START_LAST_SONG, m_ctl6);
	DDX_Control(pDX, IDC_REPEAT, m_ctl5);
	DDX_Control(pDX, IDC_PRELOAD_IE_WNDS, m_ctl4);
	DDX_Control(pDX, IDC_HIDE_PLAYER, m_ctl3);
	DDX_Control(pDX, IDC_ENABLE_SHORTCUT_KEYS, m_ctl2);
	DDX_Control(pDX, IDC_AUTO_START_APP, m_ctl1);
	DDX_Control(pDX, IDOK, m_ctlOK);
	DDX_Control(pDX, IDCANCEL, m_ctlCancel);
	DDX_Check(pDX, IDC_AUTO_START_APP, m_bAutoStart);
	DDX_Check(pDX, IDC_ENABLE_SHORTCUT_KEYS, m_bEnableShortcutKeys);
	DDX_Check(pDX, IDC_PRELOAD_IE_WNDS, m_bPreLoadWnds);
	DDX_Check(pDX, IDC_HIDE_PLAYER, m_bHidePlayerWindow);
	DDX_Check(pDX, IDC_REPEAT, m_bRepeat);
	DDX_Check(pDX, IDC_AUTO_START_LAST_SONG, m_bStartPlayLastSong);
	DDX_Check(pDX, IDC_SHOW_PLAYLIST, m_bShowPlayListOnStart);
	DDX_Check(pDX, IDC_APPEND_TO_TEMP, m_bAppendToTemp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingsDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_FILE_ASSOCIATION, OnFileAssociation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg message handlers

BOOL CSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_bAutoStart = (AfxGetApp()->GetProfileInt("Settings","AutoStartApp",1) == 1);
	m_bEnableShortcutKeys = (AfxGetApp()->GetProfileInt("Settings","EnableShortcutKeys",1) == 1);
	m_bPreLoadWnds = (AfxGetApp()->GetProfileInt("Settings","PreLoadPlayList",1) == 1);
	m_bHidePlayerWindow = (AfxGetApp()->GetProfileInt("Settings","HideVideoWindow",0) == 1);
	m_bRepeat = (AfxGetApp()->GetProfileInt("Settings","Repeat",1) == 1);
	m_bStartPlayLastSong = (AfxGetApp()->GetProfileInt("Settings","AutoPlay",1) == 1);
	m_bShowPlayListOnStart = (AfxGetApp()->GetProfileInt("Settings","ShowPlaylist",0) == 1);
	m_bAppendToTemp = (AfxGetApp()->GetProfileInt("Settings","AppendToTemp",1) == 1);

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingsDlg::OnOK() 
{
	UpdateData(true);

	WriteAutoStart(m_bAutoStart);

	AfxGetApp()->WriteProfileInt("Settings","AutoStartApp",m_bAutoStart);
	AfxGetApp()->WriteProfileInt("Settings","EnableShortcutKeys",m_bEnableShortcutKeys);
	AfxGetApp()->WriteProfileInt("Settings","PreLoadPlayList",m_bPreLoadWnds);
	AfxGetApp()->WriteProfileInt("Settings","HideVideoWindow",m_bHidePlayerWindow);
	AfxGetApp()->WriteProfileInt("Settings","Repeat",m_bRepeat);
	AfxGetApp()->WriteProfileInt("Settings","AutoPlay",m_bStartPlayLastSong);
	AfxGetApp()->WriteProfileInt("Settings","ShowPlaylist",m_bShowPlayListOnStart);
	AfxGetApp()->WriteProfileInt("Settings","AppendToTemp",m_bAppendToTemp);

	CDialog::OnOK();
}

void CSettingsDlg::WriteAutoStart(BOOL bAuto)
{
	// HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
	CString strExe;
	GetModuleFileName(NULL,strExe.GetBuffer(MAX_PATH),MAX_PATH);
	strExe.ReleaseBuffer();

	SECRegistry reg;
	BOOL bOK = reg.Connect(HKEY_LOCAL_MACHINE);
	if(bAuto)
	{
		bOK = reg.Open("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",SECRegistry::permissionWrite);
		bOK = reg.SetStringValue("FoxMediaCenter",strExe);
	}
	else
	{
		bOK = reg.Open("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",SECRegistry::permissionAllAccess);
		bOK = reg.DeleteValue("FoxMediaCenter");
	}
	reg.Close();

	if(!bOK)
		AfxMessageBox("Error setting registry values, you may need to log on to Windows with Administrator privilages");
}

void CSettingsDlg::OnPaint() 
{
	CPaintDC dc(this); 
	CRect rectCl;
	GetClientRect(rectCl);
	CBrush br;
	br.CreateSolidBrush(RGB(37,80,112));
	dc.FillRect(rectCl,&br);
}

void CSettingsDlg::OnFileAssociation() 
{
	EndDialog(IDYES);	
}
