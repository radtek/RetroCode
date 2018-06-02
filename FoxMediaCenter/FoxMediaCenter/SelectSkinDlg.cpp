// SelectSkinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "SelectSkinDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectSkinDlg dialog


CSelectSkinDlg::CSelectSkinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectSkinDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectSkinDlg)
	m_strNewSkin = _T("");
	//}}AFX_DATA_INIT
	m_pImage = NULL;
}

CSelectSkinDlg::~CSelectSkinDlg()
{
	if(m_pImage)
	{
		delete m_pImage;
		m_pImage = NULL;
	}
}

void CSelectSkinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectSkinDlg)
	DDX_Control(pDX, IDOK, m_ctlOK);
	DDX_Control(pDX, IDCANCEL, m_ctlCancel);
	DDX_Control(pDX, IDC_SELECT_SKIN, m_ctlSkinCombo);
	DDX_CBString(pDX, IDC_SELECT_SKIN, m_strNewSkin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectSkinDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectSkinDlg)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_SELECT_SKIN, OnSelchangeSelectSkin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectSkinDlg message handlers

BOOL CSelectSkinDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CStringArray* pstra = GetListOfSkins();
	for(int n=0;n<pstra->GetSize();n++)
		m_ctlSkinCombo.AddString(pstra->GetAt(n));
	delete pstra;

	CString strSkin = AfxGetApp()->GetProfileString("Settings","CurrentSkin","");
	if(!strSkin.IsEmpty())
	{
		CString strImage = GetPreviewImagePath(strSkin);
		LoadImage(strImage);
		m_ctlSkinCombo.SelectString(-1,strSkin);
	}
	else
	{		
		if (m_ctlSkinCombo.GetCount() > 0)
		{
			m_ctlSkinCombo.SetCurSel(0);
			OnSelchangeSelectSkin();
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CSelectSkinDlg::OnOK() 
{
	UpdateData(true);
	
	CString strSkin = AfxGetApp()->GetProfileString("Settings","CurrentSkin",DEFAULT_SKIN);	
	if(strSkin != m_strNewSkin)
	{
		AfxGetApp()->WriteProfileString("Settings","CurrentSkin",m_strNewSkin);	
		CDialog::OnOK();
	}
	else
		EndDialog(IDCANCEL);
}

CStringArray* CSelectSkinDlg::GetListOfSkins()
{
	CStringArray* pstra = new CStringArray;

	CString strPath;
	GetModuleFileName(NULL,strPath.GetBuffer(MAX_PATH),MAX_PATH);
	strPath.ReleaseBuffer();
	strPath = strPath.Left(strPath.ReverseFind('\\')+1);
	strPath += "Skins";

	SECFileSystem fs;
	CStringList* pStrList = fs.GetFileList(strPath + "\\*.*",fs.directory);
	if(pStrList->GetCount()>0)
	{
		POSITION pos = pStrList->GetHeadPosition();
		while(pos !=NULL)
		{
			CString str = pStrList->GetNext(pos);
			str = str.Mid(str.ReverseFind('\\')+1);
			//str = str.Left(str.ReverseFind('.'));
			pstra->Add(str);
		}
	}
	delete pStrList;

	return pstra;
}

void CSelectSkinDlg::OnPaint() 
{
//	CDialog::OnPaint();

	CPaintDC dc(this); 
	CRect rectCl;
	GetClientRect(rectCl);
	CBrush br;
	br.CreateSolidBrush(RGB(37,80,112));
	dc.FillRect(rectCl,&br);
	
	if(m_pImage)
	{
		CRect rect(10,50,310,300);

		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmMem; 
		bmMem.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
		CBitmap* pBm = dcMem.SelectObject(&bmMem);

		int rx = rect.Width();
		int ry = rect.Height();

		SECJpeg copyImage;
		copyImage.CopyImage(m_pImage);
		SECImage* pImage = &copyImage;

		int ix = pImage->m_dwWidth;
		int iy = pImage->m_dwHeight;

		pImage->Crop(0,0,(ix>rx)?rx:ix,(iy>ry)?ry:iy);

		if(rx > 0)
		{
			dcMem.FillRect(CRect(0,0,rx,ry),&br);
			pImage->StretchDIBits(&dcMem,0,0,rx,ry,
				0,0,rx,ry,
				pImage->m_lpSrcBits,pImage->m_lpBMI,DIB_RGB_COLORS,SRCCOPY); 
		}

		dc.BitBlt(rect.left,rect.top,rx,ry,&dcMem,0,0,SRCCOPY);
		dcMem.SelectObject(pBm);
		dcMem.DeleteDC();	
	}
}

CString CSelectSkinDlg::GetPreviewImagePath(CString strSkin)
{
	CString strPath;
	GetModuleFileName(NULL,strPath.GetBuffer(MAX_PATH),MAX_PATH);
	strPath.ReleaseBuffer();
	strPath = strPath.Left(strPath.ReverseFind('\\')+1);
	strPath += "Skins\\";

	strPath += strSkin + "\\Preview\\";

	SECFileSystem fs;
	CStringList* pStrList = fs.GetFileList(strPath + "*.jpg",fs.allfiles);
	CString str;
	if(pStrList->GetCount()>0)
	{
		POSITION pos = pStrList->GetHeadPosition();
		while(pos !=NULL)
		{
			str = pStrList->GetNext(pos);
			break;
		}
	}
	delete pStrList;
	return str;
}

void CSelectSkinDlg::LoadImage(CString strPath)
{
	if(m_pImage)
	{
		delete m_pImage;
		m_pImage = NULL;
	}

	SECFileSystem fp;
	if(!fp.FileExists(strPath))
		return;
	m_pImage = new SECJpeg;
	m_pImage->LoadImage(strPath);
}

void CSelectSkinDlg::OnSelchangeSelectSkin() 
{
	int nItem = m_ctlSkinCombo.GetCurSel();
	CString strSkin;
	m_ctlSkinCombo.GetLBText(nItem, strSkin); 

	CString strImage = GetPreviewImagePath(strSkin);
	LoadImage(strImage);
	InvalidateRect(NULL);
}
