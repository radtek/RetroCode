// NewPlayListNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "NewPlayListNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewPlayListNameDlg dialog


CNewPlayListNameDlg::CNewPlayListNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewPlayListNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewPlayListNameDlg)
	m_strNewName = _T("");
	//}}AFX_DATA_INIT
	m_ctlText.SetColor(RGB(37,80,112));
	m_ctlText.m_dwTextColor = RGB(255,255,255);
}


void CNewPlayListNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewPlayListNameDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strNewName);
	DDX_Control(pDX, IDOK, m_ctlOK);
	DDX_Control(pDX, IDCANCEL, m_ctlCancel);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_ctlText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewPlayListNameDlg, CDialog)
	//{{AFX_MSG_MAP(CNewPlayListNameDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewPlayListNameDlg message handlers

void CNewPlayListNameDlg::OnOK() 
{
	UpdateData(true);

	if(m_strNewName.IsEmpty())
	{
		AfxMessageBox("Please enter a name");
		return;
	}

	CDialog::OnOK();
}

void CNewPlayListNameDlg::OnPaint() 
{
	CPaintDC dc(this); 
	CRect rectCl;
	GetClientRect(rectCl);
	CBrush br;
	br.CreateSolidBrush(RGB(37,80,112));
	dc.FillRect(rectCl,&br);
}
