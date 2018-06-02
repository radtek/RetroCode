// NewFileTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "NewFileTypeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewFileTypeDlg dialog


CNewFileTypeDlg::CNewFileTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewFileTypeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewFileTypeDlg)
	m_strFileType = _T("");
	//}}AFX_DATA_INIT

	m_ctlText1.SetColor(RGB(37,80,112));
	m_ctlText2.SetColor(RGB(37,80,112));
	m_ctlText3.SetColor(RGB(37,80,112));
	m_ctlText1.m_dwTextColor = RGB(255,255,255);
	m_ctlText2.m_dwTextColor = RGB(255,255,255);
	m_ctlText3.m_dwTextColor = RGB(255,255,255);

	m_ctlAudio.SetColor(RGB(37,80,112));
	m_ctlVideo.SetColor(RGB(37,80,112));
	m_ctlAudio.m_dwTextColor = RGB(255,255,255);
	m_ctlVideo.m_dwTextColor = RGB(255,255,255);
}


void CNewFileTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewFileTypeDlg)
	DDX_Control(pDX, IDC_VIDEO, m_ctlVideo);
	DDX_Control(pDX, IDC_AUDIO, m_ctlAudio);
	DDX_Control(pDX, IDCANCEL, m_but2);
	DDX_Control(pDX, IDOK, m_but1);
	DDX_Control(pDX, IDC_TEXT3, m_ctlText3);
	DDX_Control(pDX, IDC_TEXT2, m_ctlText2);
	DDX_Control(pDX, IDC_TEXT1, m_ctlText1);
	DDX_Text(pDX, IDC_EDIT1, m_strFileType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewFileTypeDlg, CDialog)
	//{{AFX_MSG_MAP(CNewFileTypeDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_AUDIO, OnAudio)
	ON_BN_CLICKED(IDC_VIDEO, OnVideo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewFileTypeDlg message handlers

BOOL CNewFileTypeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_bIsAudio = false;
	m_ctlAudio.SetCheck(1);

	return TRUE;  
}

void CNewFileTypeDlg::OnPaint() 
{
	CPaintDC dc(this);
	CRect rectCl;
	GetClientRect(rectCl);
	CBrush br;
	br.CreateSolidBrush(RGB(37,80,112));
	dc.FillRect(rectCl,&br);
}

void CNewFileTypeDlg::OnAudio() 
{
	m_ctlAudio.SetCheck(1);
	m_ctlVideo.SetCheck(0);	
}

void CNewFileTypeDlg::OnVideo() 
{
	m_ctlAudio.SetCheck(0);
	m_ctlVideo.SetCheck(1);	
}

void CNewFileTypeDlg::OnOK() 
{
	UpdateData(true);

	if(m_strFileType.IsEmpty())
	{
		AfxMessageBox("Please enter a file type like .mp3");
		return;
	}
	if(m_strFileType.GetAt(0) != '.')
		m_strFileType = "." + m_strFileType;
	m_strFileExt = m_strFileType;

	if(m_ctlAudio.GetCheck() == 1)
		m_bIsAudio = true;
	CDialog::OnOK();
}