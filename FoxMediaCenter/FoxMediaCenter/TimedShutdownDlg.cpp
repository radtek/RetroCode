// TimedShutdownDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "TimedShutdownDlg.h"
#include "PlayListManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimedShutdownDlg dialog


CTimedShutdownDlg::CTimedShutdownDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimedShutdownDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimedShutdownDlg)
	m_strMinutes = _T("");
	m_bShutdown = FALSE;
	m_bLowerVolume = FALSE;
	//}}AFX_DATA_INIT

	m_pImage = NULL;
	m_ctl1.SetColor(RGB(255,255,255));
	m_ctlTimeChoice.SetColor(RGB(255,255,255));
	m_ctlStopAtEnd.SetColor(RGB(255,255,255));
	m_ctl4.SetColor(RGB(255,255,255));

	m_ctlText.SetColor(RGB(255,255,255));
	m_static4.SetColor(RGB(255,255,255));
	m_ctlOr.SetColor(RGB(255,255,255));
}

CTimedShutdownDlg::~CTimedShutdownDlg()
{
	if(m_pImage)
	{
		delete m_pImage;
		m_pImage = NULL;
	}
}

void CTimedShutdownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimedShutdownDlg)
	DDX_Control(pDX, IDC_TIME_TO_PLAY_CHOICE, m_ctlTimeChoice);
	DDX_Control(pDX, IDC_SHUTDOWN_AFTER_LAST_SONG, m_ctlStopAtEnd);
	DDX_Control(pDX, IDC_OR, m_ctlOr);
	DDX_Control(pDX, IDC_STATIC4, m_static4);
	DDX_Control(pDX, IDC_SHUTDOWN_COMPUTER, m_ctl4);
	DDX_Control(pDX, IDC_LOWER_VOLUME, m_ctl1);
	DDX_Control(pDX, IDOK, m_ctlOK);
	DDX_Control(pDX, IDCANCEL, m_ctlCancel);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_ctlText);
	DDX_Text(pDX, IDC_EDIT_MINUTES, m_strMinutes);
	DDV_MaxChars(pDX, m_strMinutes, 4);
	DDX_Check(pDX, IDC_SHUTDOWN_COMPUTER, m_bShutdown);
	DDX_Check(pDX, IDC_LOWER_VOLUME, m_bLowerVolume);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTimedShutdownDlg, CDialog)
	//{{AFX_MSG_MAP(CTimedShutdownDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SHUTDOWN_AFTER_LAST_SONG, OnShutdownAfterLastSong)
	ON_BN_CLICKED(IDC_TIME_TO_PLAY_CHOICE, OnTimeToPlayChoice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimedShutdownDlg message handlers

BOOL CTimedShutdownDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_strMinutes =	AfxGetApp()->GetProfileString("Settings","MinsShutdown","30");
	if(AfxGetApp()->GetProfileInt("Settings","ShutOffAfterPlayList",0) == 1)
		OnShutdownAfterLastSong();
	else
		OnTimeToPlayChoice();
	m_bShutdown =	(AfxGetApp()->GetProfileInt("Settings","ShutdownComputer",1) == 1);
	m_bLowerVolume =(AfxGetApp()->GetProfileInt("Settings","LowerVolume",1) == 1);

	UpdateData(false);

	CString strPath;
	GetModuleFileName(NULL,strPath.GetBuffer(MAX_PATH),MAX_PATH);
	strPath.ReleaseBuffer();
	strPath = strPath.Left(strPath.ReverseFind('\\')+1);
	strPath += "Images\\snooze.jpg";
	LoadImage(strPath);

	return TRUE; 
}

void CTimedShutdownDlg::OnOK() 
{
	UpdateData(true);

	AfxGetApp()->WriteProfileString("Settings","MinsShutdown",m_strMinutes);
	int nTimed = m_ctlTimeChoice.GetCheck();
	AfxGetApp()->WriteProfileInt("Settings","ShutOffAfterPlayList",(nTimed == 1)?0:1);
	AfxGetApp()->WriteProfileInt("Settings","ShutdownComputer",m_bShutdown?1:0);
	AfxGetApp()->WriteProfileInt("Settings","LowerVolume",m_bLowerVolume?1:0);

	CDialog::OnOK();
}

void CTimedShutdownDlg::OnPaint() 
{
	//CPaintDC dc(this); 

	CPaintDC dc(this); 
	CRect rectCl;
	GetClientRect(rectCl);
	CBrush br;
	br.CreateSolidBrush(RGB(255,255,255));
	dc.FillRect(rectCl,&br);
	
	if(m_pImage)
	{
		SECImage* pImage = m_pImage;

		int ix = pImage->m_dwWidth;
		int iy = pImage->m_dwHeight;
		
		CRect rect(260,110,260+ix,110+iy);

		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmMem; 
		bmMem.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
		CBitmap* pBm = dcMem.SelectObject(&bmMem);

		if(ix > 0)
		{
			dcMem.FillRect(CRect(0,0,ix,iy),&br);
			pImage->StretchDIBits(&dcMem,0,0,ix,iy,
				0,0,ix,iy,
				pImage->m_lpSrcBits,pImage->m_lpBMI,DIB_RGB_COLORS,SRCCOPY); 
		}

		dc.BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);
		dcMem.SelectObject(pBm);
		dcMem.DeleteDC();	
	}
}

void CTimedShutdownDlg::LoadImage(CString strPath)
{
	SECFileSystem fp;
	if(!fp.FileExists(strPath))
		return;

	if(m_pImage)
	{
		delete m_pImage;
		m_pImage = NULL;
	}
	m_pImage = new SECJpeg;
	m_pImage->LoadImage(strPath);
}

void CTimedShutdownDlg::OnShutdownAfterLastSong() 
{
	m_ctlTimeChoice.SetCheck(0);
	m_ctlStopAtEnd.SetCheck(1);	
}

void CTimedShutdownDlg::OnTimeToPlayChoice() 
{
	m_ctlTimeChoice.SetCheck(1);
	m_ctlStopAtEnd.SetCheck(0);	
}
