// NewRandomPlaylistDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "NewRandomPlaylistDlg.h"
#include "PlayListManager.h"
#include "helpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewRandomPlaylistDlg dialog

CNewRandomPlaylistDlg::CNewRandomPlaylistDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewRandomPlaylistDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewRandomPlaylistDlg)
	m_strDirPath = _T("");
	m_strFileExt = _T("");
	m_bRandomEachTime = FALSE;
	m_strMaxFiles = _T("");
	m_strPlaylistName = _T("");
	//}}AFX_DATA_INIT

	m_static1.SetColor(RGB(37,80,112));
	m_static2.SetColor(RGB(37,80,112));
	m_static3.SetColor(RGB(37,80,112));
	m_static4.SetColor(RGB(37,80,112));
	m_static5.SetColor(RGB(37,80,112));
	m_static6.SetColor(RGB(37,80,112));
	m_static7.SetColor(RGB(37,80,112));

	m_static1.m_dwTextColor = RGB(255,255,255);
	m_static2.m_dwTextColor = RGB(255,255,255);
	m_static3.m_dwTextColor = RGB(255,255,255);
	m_static4.m_dwTextColor = RGB(255,255,255);
	m_static5.m_dwTextColor = RGB(255,255,255);
	m_static6.m_dwTextColor = RGB(255,255,255);
	m_static7.m_dwTextColor = RGB(255,255,255);
	
	m_ctl1.SetColor(RGB(37,80,112));
	m_ctl1.m_dwTextColor = RGB(255,255,255);
}


void CNewRandomPlaylistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewRandomPlaylistDlg)
	DDX_Control(pDX, IDC_LIST_EXTS, m_ctlListOfExts);
	DDX_Control(pDX, IDC_LIST_DIRS, m_ctlListOfDirs);
	DDX_Text(pDX, IDC_DIR_PATH, m_strDirPath);
	DDX_Text(pDX, IDC_FILE_EXT, m_strFileExt);
	DDX_Check(pDX, IDC_MAKE_RANDOM_EACH_TIME, m_bRandomEachTime);
	DDX_Text(pDX, IDC_MAX_FILES, m_strMaxFiles);
	DDX_Text(pDX, IDC_PLAYLIST_NAME, m_strPlaylistName);
	DDX_Control(pDX, IDOK, m_ctlOK);
	DDX_Control(pDX, IDCANCEL, m_ctlCancel);
	DDX_Control(pDX, IDC_BROWSE, m_ctlB1);
	DDX_Control(pDX, IDC_ADD_DIR_TOLIST, m_ctlB2);
	DDX_Control(pDX, IDC_ADD_EXTENTION, m_ctlB3);
	DDX_Control(pDX, IDC_RANDOM_PLAYLIST_HELP, m_ctlB4);

	DDX_Control(pDX, IDC_STATIC1, m_static1);
	DDX_Control(pDX, IDC_STATIC2, m_static2);
	DDX_Control(pDX, IDC_STATIC3, m_static3);
	DDX_Control(pDX, IDC_STATIC4, m_static4);
	DDX_Control(pDX, IDC_STATIC5, m_static5);
	DDX_Control(pDX, IDC_STATIC6, m_static6);
	DDX_Control(pDX, IDC_STATIC7, m_static7);
	
	DDX_Control(pDX, IDC_MAKE_RANDOM_EACH_TIME, m_ctl1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewRandomPlaylistDlg, CDialog)
	//{{AFX_MSG_MAP(CNewRandomPlaylistDlg)
	ON_BN_CLICKED(IDC_ADD_DIR_TOLIST, OnAddDirTolist)
	ON_BN_CLICKED(IDC_ADD_EXTENTION, OnAddExtention)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_RANDOM_PLAYLIST_HELP, OnRandomPlaylistHelp)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewRandomPlaylistDlg message handlers

BOOL CNewRandomPlaylistDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CPlayListManager list;
	
	m_strPlaylistName = list.GetNextRandomPlaylistName();
	m_strFileExt = AfxGetApp()->GetProfileString("Settings","LastRandomFileExt","*.mp3");
	m_strDirPath = AfxGetApp()->GetProfileString("Settings","LastRandomDirPath","");
	m_strMaxFiles = "50";
	m_bRandomEachTime = false;
	
	UpdateData(false);

	return TRUE; 
}

void CNewRandomPlaylistDlg::OnAddDirTolist() 
{
	UpdateData(true);

	SECFileSystem fp;
	if(!fp.DirectoryExists(m_strDirPath))
	{
		AfxMessageBox("Error, directory is not valid.");
		return;
	}
	m_ctlListOfDirs.AddString(m_strDirPath);
}

void CNewRandomPlaylistDlg::OnAddExtention() 
{
	UpdateData(true);

	if(m_strFileExt.Find('.') == -1)
	{
		AfxMessageBox("Error, file extention is not valid, try something like '*.mp3'.");
		return;
	}
	m_ctlListOfExts.AddString(m_strFileExt);
	UpdateData(false);		
}

void CNewRandomPlaylistDlg::OnBrowse() 
{
	UpdateData(true);

	LPMALLOC pMalloc;
    /* Gets the Shell's default allocator */
    if (::SHGetMalloc(&pMalloc) == NOERROR)
    {
        BROWSEINFO bi;
        char pszBuffer[MAX_PATH];
        LPITEMIDLIST pidl;
        // Get help on BROWSEINFO struct - it's got all the bit settings.
        bi.hwndOwner = GetSafeHwnd();
        bi.pidlRoot = NULL;
        bi.pszDisplayName = pszBuffer;
        bi.lpszTitle = _T("Select a Directory");
        bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
        bi.lpfn = NULL;
        bi.lParam = 0;
        // This next call issues the dialog box.
        if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)
        {
            if (::SHGetPathFromIDList(pidl, pszBuffer))
            { 
				// At this point pszBuffer contains the selected path */.
				m_strDirPath = pszBuffer;
            }
            // Free the PIDL allocated by SHBrowseForFolder.
            pMalloc->Free(pidl);
        }
        // Release the shell's allocator.
        pMalloc->Release();
    }
	UpdateData(false);		
}

void CNewRandomPlaylistDlg::OnRandomPlaylistHelp() 
{
	LoadInDefaultBrowser(DEFAULT_HELP_RANDOM_PLAYLIST);
}

void CNewRandomPlaylistDlg::OnOK() 
{
	UpdateData(true);

	// check for data entry errors
	int nMaxFiles = atoi(m_strMaxFiles);	
	if(nMaxFiles <= 0)
	{
		AfxMessageBox("Error, max files needs to be greater than zero.");		
		return;
	}
	if(m_ctlListOfDirs.GetCount() <= 0)
	{
		AfxMessageBox("Error, you need to enter a directory to search for files in, and click 'Add directory' button.");		
		return;
	}
	if(m_ctlListOfExts.GetCount() <= 0)
	{
		AfxMessageBox("Error, you need to enter a file extention like '*.mp3', and click 'Add file type' directory button.");		
		return;
	}

	AfxGetApp()->WriteProfileString("Settings","LastRandomFileExt",m_strFileExt);
	AfxGetApp()->WriteProfileString("Settings","LastRandomDirPath",m_strDirPath);

	CString strData = _T("<RandomPlayList>TRUE</RandomPlayList>");
	CStringArray straRandomDirPaths;

	for(int n=0;n<m_ctlListOfDirs.GetCount();n++)
	{
		CString strTemp;
		DWORD dwSize = m_ctlListOfDirs.GetTextLen(n);
		m_ctlListOfDirs.GetText(n,strTemp.GetBuffer(dwSize));
		strTemp.ReleaseBuffer();

		for(int n2=0;n2<m_ctlListOfExts.GetCount();n2++)
		{
			CString strTempExt;
			dwSize = m_ctlListOfExts.GetTextLen(n2);
			m_ctlListOfExts.GetText(n2,strTempExt.GetBuffer(dwSize));
			strTempExt.ReleaseBuffer();

			straRandomDirPaths.Add(strTemp + "\\" + strTempExt);
		}
	}

	strData += "<MaxFiles>" + m_strMaxFiles + "</MaxFiles>";
	
	if(m_bRandomEachTime)
		strData += "<RandomEachTime>TRUE</RandomEachTime>";
	else	
		strData += "<RandomEachTime>FALSE</RandomEachTime>";

	for(n=0;n<straRandomDirPaths.GetSize();n++)
	{
		strData += "<RandomDirPath>" + straRandomDirPaths.GetAt(n) + "</RandomDirPath>";
	}
	strData += "\r\n";

	CStringArray* pstraList = MakeRandomPlaylist(&straRandomDirPaths,nMaxFiles);
	for(n=0;n<pstraList->GetSize();n++)
	{
		strData += "<PlayListEntry><FullPath>" + pstraList->GetAt(n) + "</FullPath>";
		CString strShortName = pstraList->GetAt(n);
		strShortName = strShortName.Mid(strShortName.ReverseFind('\\')+1);
		strData += "<Name>" + strShortName + "</Name>";
		strData += "</PlayListEntry>\r\n";
	}	
	delete pstraList;

	// save new list
	CPlayListManager list;
	list.SaveNewPlayList(m_strPlaylistName, strData);

	CDialog::OnOK();
}

void CNewRandomPlaylistDlg::OnPaint() 
{
	CPaintDC dc(this); 
	CRect rectCl;
	GetClientRect(rectCl);
	CBrush br;
	br.CreateSolidBrush(RGB(37,80,112));
	dc.FillRect(rectCl,&br);
}

