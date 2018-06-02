// ManagePlayListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "ManagePlayListDlg.h"
#include "PlayListManager.h"
#include "helpers.h"
#include "NewRandomPlaylistDlg.h"
#include "NewPlayListNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManagePlayListDlg dialog


CManagePlayListDlg::CManagePlayListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManagePlayListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManagePlayListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CManagePlayListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManagePlayListDlg)
	DDX_Control(pDX, IDC_RENAME_PLAYLIST, m_butRename);
	DDX_Control(pDX, IDC_PLAY_SELECTED, m_butPlaySelected);
	DDX_Control(pDX, IDC_NEW_NORMAL_PLAYLIST, m_butNewPlayList);
	DDX_Control(pDX, IDC_NEW_RANDOM, m_butNewRandom);
	DDX_Control(pDX, IDC_DELETE, m_butDelete);
	DDX_Control(pDX, IDC_ADD_FILES, m_butAdd);
	DDX_Control(pDX, IDCANCEL, m_butCancel);
	DDX_Control(pDX, IDOK, m_butOK);
	DDX_Control(pDX, IDC_TREE_PLAYLISTS, m_ctlTreePlaylists);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CManagePlayListDlg, CDialog)
	//{{AFX_MSG_MAP(CManagePlayListDlg)
	ON_BN_CLICKED(IDC_RENAME_PLAYLIST, OnRenamePlaylist)
	ON_BN_CLICKED(IDC_NEW_RANDOM, OnNewPlaylist)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_ADD_FILES, OnAddFiles)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_PLAY_SELECTED, OnPlaySelected)
	ON_BN_CLICKED(IDC_NEW_NORMAL_PLAYLIST, OnNewNormalPlaylist)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_PLAY_SELECTED,OnPlaySelected)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManagePlayListDlg message handlers

BOOL CManagePlayListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME),true);

	CPlayListManager list;
	CStringArray* pstra = list.GetPlayListNames();
	CString strCurrentPlayList = AfxGetApp()->GetProfileString("Settings","CurrentPlaylist","default");

	m_ctlTreePlaylists.Init();

	for(int n=0;n<pstra->GetSize();n++)
	{
		CString strName = pstra->GetAt(n);
		m_ctlTreePlaylists.AddRootItem(strName,(strCurrentPlayList == strName));
	}
	delete pstra;
	
	CRect rect;
	GetWindowRect(rect);
	// get last position of playlist
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	int nLeft = pApp->GetProfileInt("Settings","xposManList",0);
	if(nLeft < 0 || nLeft > 10000)
		nLeft = 0;
	rect.left = nLeft;
	int nTop = pApp->GetProfileInt("Settings","yposManList",200);
	if(nTop < 0 || nTop > 10000)
		nTop = 0;

	int xSize = pApp->GetProfileInt("Settings","xsizeManList",480);
	int ySize = pApp->GetProfileInt("Settings","ysizeManList",500);
	if(xSize < 0 || xSize > 10000)
		xSize = 480;
	if(ySize < 0 || ySize > 10000)
		ySize = 500;

	rect.top = nTop;
	rect.right = rect.left + xSize;
	rect.bottom = rect.top + ySize;

	MoveWindow(rect);

	GetClientRect(rect);

	if(IsWindow(m_ctlTreePlaylists.m_hWnd))
	{
		int cx = rect.Width();
		int cy = rect.Height();
		int nX = 90;
		int nX2 = 80;
		int nY = 5;
		int nY2 = 25;
		int nSpace = 5;

		m_ctlTreePlaylists.MoveWindow(0,0,cx-nX-10,cy);

		m_butPlaySelected.MoveWindow(cx-nX,nY,nX2,nY2);
		nY = nY + nY2 + nSpace;
		m_butOK.MoveWindow(cx-nX,nY,nX2,nY2);
		nY = nY + nY2 + nSpace;
		m_butCancel.MoveWindow(cx-nX,nY,nX2,nY2);
		nY = nY + nY2 + nSpace + 20;
		m_butNewPlayList.MoveWindow(cx-nX,nY,nX2,nY2);
		nY = nY + nY2 + nSpace;
		m_butNewRandom.MoveWindow(cx-nX,nY,nX2,nY2);
		nY = nY + nY2 + nSpace;
		m_butAdd.MoveWindow(cx-nX,nY,nX2,nY2);
		nY = nY + nY2 + nSpace;
		m_butDelete.MoveWindow(cx-nX,nY,nX2,nY2);
		nY = nY + nY2 + nSpace;
		m_butRename.MoveWindow(cx-nX,nY,nX2,nY2);
	}	

	UpdateData(false);

	return TRUE;  
}

void CManagePlayListDlg::OnDelete() 
{
	HTREEITEM hItem = m_ctlTreePlaylists.GetSelectedItem();
	HTREEITEM hParent = m_ctlTreePlaylists.GetParentItem(hItem);
	
	CString strPlayList = hParent?m_ctlTreePlaylists.GetItemText(hParent):m_ctlTreePlaylists.GetItemText(hItem);
	m_ctlTreePlaylists.DeleteItem(hItem);

	UpdateData(true);
}

void CManagePlayListDlg::OnAddFiles() 
{
	HTREEITEM hItem = m_ctlTreePlaylists.GetSelectedItem();
	CString strLastFolder = AfxGetApp()->GetProfileString("Settings","LastFileOpenPath",NULL);
	CString strExt;
	if(strLastFolder.Find('\\') != -1)
	{
		strExt = strLastFolder.Mid(strLastFolder.ReverseFind('\\')+1);
		strLastFolder = strLastFolder.Mid(strLastFolder.ReverseFind('\\')+1);
	}

	LPCTSTR lpszFilter = _T("MP3 (*.mp3)|*.mp3|ogg files (*.ogg)|*.ogg|Mpeg (*.mpg)|*.mpg;*.mpeg|Divx AVI (*.avi)|*.avi|Windows Media (*.wm*)|*.wm*|All Files (*.*)|*.*||");
	CFileDialog dlg(true,strExt,strLastFolder,0,lpszFilter);
	if(dlg.DoModal() == IDOK)
	{
		strLastFolder = dlg.GetPathName();
		m_ctlTreePlaylists.AddNewFile(strLastFolder, hItem);
		strLastFolder = strLastFolder.Left(strLastFolder.ReverseFind('\\')+1);
		strLastFolder += "*." + dlg.GetFileExt();
		AfxGetApp()->WriteProfileString("Settings","LastFileOpenPath",strLastFolder);
	}	
}

void CManagePlayListDlg::OnNewPlaylist() // new random
{
	UpdateData(true);
	SaveCurrentPlayLists();

	CNewRandomPlaylistDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		// reload playlists
		ReloadPlayLists();
	}	
}

void CManagePlayListDlg::ReloadPlayLists()
{
	m_ctlTreePlaylists.DeleteAllItems();
	m_ctlTreePlaylists.m_straFullPathLists.RemoveAll();

	CPlayListManager list;
	CStringArray* pstra = list.GetPlayListNames();
	CString strCurrentPlayList = AfxGetApp()->GetProfileString("Settings","CurrentPlaylist","default");
	for(int n=0;n<pstra->GetSize();n++)
	{
		CString strName = pstra->GetAt(n);
		m_ctlTreePlaylists.AddRootItem(strName,(strCurrentPlayList == strName));
	}
	delete pstra;
}

void CManagePlayListDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	if(IsWindow(m_ctlTreePlaylists.m_hWnd))
	{
		int nX = 90;
		int nX2 = 80;
		int nY = 5;
		int nY2 = 25;
		int nSpace = 5;

		m_ctlTreePlaylists.MoveWindow(0,0,cx-nX-10,cy);

		m_butPlaySelected.MoveWindow(cx-nX,nY,nX2,nY2);
		nY = nY + nY2 + nSpace;
		m_butOK.MoveWindow(cx-nX,nY,nX2,nY2);
		nY = nY + nY2 + nSpace;
		m_butCancel.MoveWindow(cx-nX,nY,nX2,nY2);
		nY = nY + nY2 + nSpace + 20;
		m_butNewPlayList.MoveWindow(cx-nX,nY,nX2,nY2);
		nY = nY + nY2 + nSpace;
		m_butNewRandom.MoveWindow(cx-nX,nY,nX2,nY2);
		nY = nY + nY2 + nSpace;
		m_butAdd.MoveWindow(cx-nX,nY,nX2,nY2);
		nY = nY + nY2 + nSpace;
		m_butDelete.MoveWindow(cx-nX,nY,nX2,nY2);
		nY = nY + nY2 + nSpace;
		m_butRename.MoveWindow(cx-nX,nY,nX2,nY2);
	}
}

void CManagePlayListDlg::OnNewNormalPlaylist() 
{
	UpdateData(true);

	CNewPlayListNameDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_ctlTreePlaylists.AddRootItem(dlg.m_strNewName,true);
	}
}

void CManagePlayListDlg::OnPlaySelected()
{
	CString strCurrentPlayList = m_ctlTreePlaylists.GetSelectPlayList();
	m_strSelectedFile = m_ctlTreePlaylists.GetSelectedFile();

	if(!strCurrentPlayList.IsEmpty())
	{
		if(SaveCurrentPlayLists())
		{
			AfxGetApp()->WriteProfileString("Settings","CurrentPlaylist",strCurrentPlayList);
			SaveScreenPos();
			EndDialog(IDYES);
		}
	}
}

long CManagePlayListDlg::OnPlaySelected(WPARAM wParam,LPARAM lParam)
{
	OnPlaySelected();
	return 1;
}

// save current playlists
void CManagePlayListDlg::OnOK() 
{
	SaveCurrentPlayLists();
	SaveScreenPos();
	CDialog::OnOK();
}

BOOL CManagePlayListDlg::SaveCurrentPlayLists()
{
	CPlayListManager list;
	CStringArray* pstra = m_ctlTreePlaylists.GetRootPlayLists();
	for(int n=0;n<pstra->GetSize();n++)
	{
		CString strRootName = pstra->GetAt(n);
		CStringArray* pstra2 = m_ctlTreePlaylists.GetChildPlayListItems(strRootName);
		
		list.UpdatePlayList(strRootName,pstra2);

		delete pstra2;
	}

	CStringArray* pStraFiles = list.GetPlayListNames();
	for(n=0;n<pStraFiles->GetSize();n++)
	{
		CString strFileName = pStraFiles->GetAt(n);
		BOOL bFound = false;
		for(int n2=0;n2<pstra->GetSize();n2++)
		{
			CString strTest = pstra->GetAt(n2);
			if(strFileName == strTest)
			{
				bFound = true;
				break;
			}
		}
		if(!bFound)
			list.DeletePlayList(strFileName);
	}
	delete pStraFiles;
	delete pstra;

	return true;
}

void CManagePlayListDlg::SaveScreenPos()
{
	// save window co ordinates
	CRect rect;
	GetWindowRect(rect);
	int nX = rect.left;
	int nY = rect.top;
	if(nX < 3000 && nY < 3000)
	{
		CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
		pApp->WriteProfileInt("Settings","xposManList",nX);		
		pApp->WriteProfileInt("Settings","yposManList",nY);
		pApp->WriteProfileInt("Settings","xsizeManList",rect.Width());
		pApp->WriteProfileInt("Settings","ysizeManList",rect.Height());
	}
}

void CManagePlayListDlg::OnClose() 
{
	SaveScreenPos();	
	CDialog::OnClose();
}

void CManagePlayListDlg::OnPaint() 
{
	CPaintDC dc(this); 
	CRect rectCl;
	GetClientRect(rectCl);
	CBrush br;
	br.CreateSolidBrush(RGB(37,80,112));
	dc.FillRect(rectCl,&br);
}

void CManagePlayListDlg::OnRenamePlaylist()
{
	HTREEITEM hItem = m_ctlTreePlaylists.GetSelectedItem();
	HTREEITEM hParent = m_ctlTreePlaylists.GetParentItem(hItem);
	if(hParent)
		hItem = hParent;
	CString strPlayListOld = m_ctlTreePlaylists.GetItemText(hItem);
	// get new name
	CNewPlayListNameDlg dlg;
	if(dlg.DoModal() != IDOK)
		return;
	CString strPlayListNew = dlg.m_strNewName;
	// rename files
	CString strPath = AfxGetApp()->GetProfileString("Settings","InstallPath",DEFAULT_INSTALL_PATH);
	strPath += "\\Playlists\\";
	SECFileSystem fs;
	fs.RenameFile(strPath + strPlayListOld + ".spl",strPath + strPlayListNew + ".spl");

	// see if current selected playlist
	if(strPlayListOld == AfxGetApp()->GetProfileString("Settings","CurrentPlaylist",""))		
		AfxGetApp()->WriteProfileString("Settings","CurrentPlaylist",strPlayListNew);	

	// update text
	m_ctlTreePlaylists.SetItemText(hItem,strPlayListNew);

	UpdateData(true);
}
