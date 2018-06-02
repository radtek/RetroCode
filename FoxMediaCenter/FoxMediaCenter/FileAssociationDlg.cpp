// FileAssociationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "FileAssociationDlg.h"
#include "helpers.h"
#include "NewFileTypeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileAssociationDlg dialog


CFileAssociationDlg::CFileAssociationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileAssociationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileAssociationDlg)
	//}}AFX_DATA_INIT

	m_ctlDivx.SetColor(RGB(37,80,112));
	m_ctlMp3.SetColor(RGB(37,80,112));
	m_ctlMpg.SetColor(RGB(37,80,112));
	m_ctlOgg.SetColor(RGB(37,80,112));
	m_ctlQuicktime.SetColor(RGB(37,80,112));
	m_ctlWinAu.SetColor(RGB(37,80,112));
	m_ctlWinVid.SetColor(RGB(37,80,112));

	m_ctlDivx.m_dwTextColor = RGB(255,255,255);
	m_ctlMp3.m_dwTextColor = RGB(255,255,255);
	m_ctlMpg.m_dwTextColor = RGB(255,255,255);
	m_ctlOgg.m_dwTextColor = RGB(255,255,255);
	m_ctlQuicktime.m_dwTextColor = RGB(255,255,255);
	m_ctlWinAu.m_dwTextColor = RGB(255,255,255);
	m_ctlWinVid.m_dwTextColor = RGB(255,255,255);

	m_ctlText1.SetColor(RGB(37,80,112));
	m_ctlText2.SetColor(RGB(37,80,112));
	m_ctlText1.m_dwTextColor = RGB(255,255,255);
	m_ctlText2.m_dwTextColor = RGB(255,255,255);
}


void CFileAssociationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileAssociationDlg)
	DDX_Control(pDX, IDC_QUICKTIME, m_ctlQuicktime);
	DDX_Control(pDX, IDOK, m_ctlOK);
	DDX_Control(pDX, IDC_REMOVE, m_ctlRemoveBut);
	DDX_Control(pDX, IDC_NEW_TYPE_BUTTON, m_ctlNewBut);
	DDX_Control(pDX, IDC_LIST1, m_ctlList);
	DDX_Control(pDX, IDC_WIN_VIDEO, m_ctlWinVid);
	DDX_Control(pDX, IDC_WIN_AUDIO, m_ctlWinAu);
	DDX_Control(pDX, IDC_OGG, m_ctlOgg);
	DDX_Control(pDX, IDC_MPG, m_ctlMpg);
	DDX_Control(pDX, IDC_MP3, m_ctlMp3);
	DDX_Control(pDX, IDC_DIVX, m_ctlDivx);
	DDX_Control(pDX, IDC_QUICK_TYPE_TEXT, m_ctlText2);
	DDX_Control(pDX, IDC_LIST_TEXT, m_ctlText1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileAssociationDlg, CDialog)
	//{{AFX_MSG_MAP(CFileAssociationDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MP3, OnMp3)
	ON_BN_CLICKED(IDC_MPG, OnMpg)
	ON_BN_CLICKED(IDC_OGG, OnOgg)
	ON_BN_CLICKED(IDC_WIN_AUDIO, OnWinAudio)
	ON_BN_CLICKED(IDC_WIN_VIDEO, OnWinVideo)
	ON_BN_CLICKED(IDC_DIVX, OnDivx)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_NEW_TYPE_BUTTON, OnNewTypeButton)
	ON_BN_CLICKED(IDC_QUICKTIME, OnQuicktime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileAssociationDlg message handlers

BOOL CFileAssociationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctlList.InsertColumn(0,"File Extension",LVCFMT_LEFT,100);
	m_ctlList.InsertColumn(1,"Audio/Video",LVCFMT_LEFT,100);

	m_ctlMp3.SetCheck(IsAssociatedType(".mp3"));
	m_ctlOgg.SetCheck(IsAssociatedType(".ogg"));
	m_ctlQuicktime.SetCheck(IsAssociatedType(".mov"));
	m_ctlWinAu.SetCheck(IsAssociatedType(".wma"));
	m_ctlWinVid.SetCheck(IsAssociatedType(".wmv"));
	m_ctlDivx.SetCheck(IsAssociatedType(".avi"));
	m_ctlMpg.SetCheck(IsAssociatedType(".mpg"));

	CStringArray* pstra = EnumKnowFileTypesFromReg();
	for(int n=0;n<pstra->GetSize();n++)
	{
		CString strData = pstra->GetAt(n);
		AddToList(ParseXML("Ext",strData),ParseXML("IsAudio",strData)=="TRUE"?true:false);
	}
	delete pstra;

	return TRUE;
}

void CFileAssociationDlg::OnPaint() 
{
	CPaintDC dc(this); 
	CRect rectCl;
	GetClientRect(rectCl);
	CBrush br;
	br.CreateSolidBrush(RGB(37,80,112));
	dc.FillRect(rectCl,&br);
}

void CFileAssociationDlg::OnMp3() 
{
	if(m_ctlMp3.GetCheck() == 1)
	{
		m_ctlMp3.SetCheck(0);
		UnAssociate(".mp3");
	}
	else
	{
		m_ctlMp3.SetCheck(1);
		Associate(".mp3",true);
	}	
}

void CFileAssociationDlg::OnMpg() 
{
	if(m_ctlMpg.GetCheck() == 1)
	{
		m_ctlMpg.SetCheck(0);
		UnAssociate(".mpg");
		UnAssociate(".mpeg");
		UnAssociate(".mp4");
	}
	else
	{
		m_ctlMpg.SetCheck(1);
		Associate(".mpg",false);
		Associate(".mpeg",false);
		Associate(".mp4",false);
	}		
}

void CFileAssociationDlg::OnOgg() 
{
	if(m_ctlOgg.GetCheck() == 1)
	{
		m_ctlOgg.SetCheck(0);
		UnAssociate(".ogg");
	}
	else
	{
		m_ctlOgg.SetCheck(1);
		Associate(".ogg",true);
	}		
}

void CFileAssociationDlg::OnWinAudio() 
{
	if(m_ctlWinAu.GetCheck() == 1)
	{
		m_ctlWinAu.SetCheck(0);
		UnAssociate(".wma");
	}
	else
	{
		m_ctlWinAu.SetCheck(1);
		Associate(".wma",true);
	}	
}

void CFileAssociationDlg::OnWinVideo() 
{
	if(m_ctlWinVid.GetCheck() == 1)
	{
		m_ctlWinVid.SetCheck(0);
		UnAssociate(".wmv");
		UnAssociate(".asf");
	}
	else
	{
		m_ctlWinVid.SetCheck(1);
		Associate(".wmv",false);
		Associate(".asf",false);
	}
}

void CFileAssociationDlg::OnDivx() 
{
	if(m_ctlDivx.GetCheck() == 1)
	{
		m_ctlDivx.SetCheck(0);
		UnAssociate(".avi");
	}
	else
	{
		m_ctlDivx.SetCheck(1);
		Associate(".avi",false);
	}	
}

void CFileAssociationDlg::OnQuicktime() 
{
	if(m_ctlQuicktime.GetCheck() == 1)
	{
		m_ctlQuicktime.SetCheck(0);
		UnAssociate(".mov");
	}
	else
	{
		m_ctlQuicktime.SetCheck(1);
		Associate(".mov",false);
	}		
}

void CFileAssociationDlg::UnAssociate(CString strExt)
{
	// remove from list
	for(int n=0;n<m_ctlList.GetItemCount();n++)
	{
		if(m_ctlList.GetItemText(n,0).CompareNoCase(strExt) == 0)
		{
			m_ctlList.DeleteItem(n);
			break;
		}
	}
	// read mime type
	DWORD dwLen = 1024;
	CRegKey reg;
	long lErr = 0;
	CString strMimeType;
	lErr = reg.Open(HKEY_CLASSES_ROOT,strExt);
	lErr = reg.QueryValue(strMimeType.GetBuffer(1024),"OldMimeType",&dwLen);
	strMimeType.ReleaseBuffer();
	if(!strMimeType.IsEmpty())
		lErr = reg.SetKeyValue("",strMimeType,"" );
	else
		lErr = reg.DeleteValue("");
	reg.Close();

	// add to local registry as known type
	AfxGetApp()->WriteProfileString(strExt,"Associated","FALSE");
}

void CFileAssociationDlg::Associate(CString strExt,BOOL bIsAudio)
{
	AddToList(strExt,bIsAudio);

	// add to local registry as known type
	AfxGetApp()->WriteProfileString(strExt,"Associated","TRUE");
	AfxGetApp()->WriteProfileString(strExt,"IsAudio",bIsAudio?"TRUE":"FALSE");

	CString strName = "Fox.FoxMediaCenter.1";

	DWORD dwLen = 1024;
	CRegKey reg;
	long lErr = 0;
	// read mime type
	CString strMimeType;
	lErr = reg.Open(HKEY_CLASSES_ROOT,strExt);
	if(lErr == 2)
	{
		lErr = reg.Create(HKEY_CLASSES_ROOT,strExt);	
		lErr = reg.Open(HKEY_CLASSES_ROOT,strExt);
	}
	lErr = reg.QueryValue(strMimeType.GetBuffer(1024),"",&dwLen);
	strMimeType.ReleaseBuffer();
	// save old mime params
	if(!strMimeType.IsEmpty() && strMimeType != strName)
		lErr = reg.SetKeyValue("",strMimeType,"OldMimeType");
	// save new mime params
	lErr = reg.SetKeyValue("",strName,"" );
	reg.Close();	
}

BOOL CFileAssociationDlg::IsAssociatedType(CString strExt)
{
	BOOL bIsAssoc = (AfxGetApp()->GetProfileString(strExt,"Associated","FALSE") == "TRUE");
	return bIsAssoc;
}

void CFileAssociationDlg::AddToList(CString strExt, BOOL bIsAudio)
{
	// add to list
	LVITEM item;
	ZeroMemory(&item,sizeof(LVITEM));
	item.mask = LVIF_TEXT|LVIF_PARAM|LVIF_STATE;
	item.iItem = m_ctlList.GetItemCount();
	item.iSubItem = 0;
	int nLen = strExt.GetLength();
	item.pszText = strExt.GetBuffer(nLen);
	item.cchTextMax = nLen;
	item.lParam = 0;
	item.state = 0;
	m_ctlList.InsertItem(&item);
	strExt.ReleaseBuffer();

	if(bIsAudio)
		m_ctlList.SetItemText(item.iItem,1,"Audio");
	else
		m_ctlList.SetItemText(item.iItem,1,"Video");
}

void CFileAssociationDlg::OnRemove() 
{
	// remove from list
	for(int n=0;n<m_ctlList.GetItemCount();n++)
	{
		if(m_ctlList.GetItemState(n,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strExt;
			m_ctlList.GetItemText(n,0,strExt.GetBuffer(1024),1024);
			strExt.ReleaseBuffer();
			if(IsMpegType(strExt))
			{
				m_ctlMpg.SetCheck(1);
				OnMpg();
			}
			else if(IsWMVType(strExt))
			{
				m_ctlWinVid.SetCheck(1);
				OnWinVideo();
			}
			else
			{
				UnAssociate(strExt);
				RemoveCheckOfKnowType(strExt);
			}
			break;
		}
	}
}

void CFileAssociationDlg::RemoveCheckOfKnowType(CString strExt)
{
	if(strExt == ".mp3")
		m_ctlMp3.SetCheck(0);
	else if(strExt == ".mpg" || strExt == ".mpeg" || strExt == ".mp4")
		m_ctlMpg.SetCheck(0);
	else if(strExt == ".ogg")
		m_ctlOgg.SetCheck(0);
	else if(strExt == ".mov")
		m_ctlQuicktime.SetCheck(0);
	else if(strExt == ".wma")
		m_ctlWinAu.SetCheck(0);
	else if(strExt == ".wmv" || strExt == ".asf")
		m_ctlWinVid.SetCheck(0);
	else if(strExt == ".avi")
		m_ctlDivx.SetCheck(0);	
}

void CFileAssociationDlg::OnNewTypeButton() 
{
	CNewFileTypeDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		Associate(dlg.m_strFileExt,dlg.m_bIsAudio);
	}
}

