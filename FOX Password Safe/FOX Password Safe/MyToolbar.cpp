// MyToolbar.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "MyToolbar.h"
#include ".\mytoolbar.h"
#include "helpers.h"

// CMyToolbar

IMPLEMENT_DYNAMIC(CMyToolbar, CWnd)
CMyToolbar::CMyToolbar()
{
}

CMyToolbar::~CMyToolbar()
{
}


BEGIN_MESSAGE_MAP(CMyToolbar, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMyToolbar message handlers

void CMyToolbar::OnPaint()
{
	CRect rect;
	GetClientRect(rect);
	CPaintDC dc(this); // device context for painting

	COLORREF col = GetSysColor(COLOR_BTNFACE);
	CBrush br;
	br.CreateSolidBrush(col);
	dc.FillRect(rect,&br);
}

int CMyToolbar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	int nX1 = 0;
	int nY1 = 0;
	int nXSize = 20;
	int nYSize = 20;
	// open
	m_buttonOpen.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(nX1,nY1,nXSize,nYSize+nY1),this,ID_FILE_OPEN);
	m_bmOpen2.LoadBitmap(IDB_FILEOPENDOWN);
	m_bmOpen1.LoadBitmap(IDB_FILEOPENUP);
	m_buttonOpen.SetBitmaps(m_bmOpen2,RGB(0,255,0),m_bmOpen1,RGB(0,255,0));
	// new 
	m_buttonNew.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(nXSize,nY1,nXSize*2,nYSize+nY1),this,ID_FILE_ADDNEWENTRY);
	m_bmNew2.LoadBitmap(IDB_FILE_NEW2);
	m_bmNew1.LoadBitmap(IDB_FILE_NEW1);
	m_buttonNew.SetBitmaps(m_bmNew2,RGB(0,255,0),m_bmNew1,RGB(0,255,0));
	// edit 
	m_buttonEdit.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(nXSize*2,nY1,nXSize*3,nYSize+nY1),this,ID_EDIT_EDITSELECTEDENTRY);
	m_bmEdit2.LoadBitmap(IDB_FILE_EDIT2);
	m_bmEdit1.LoadBitmap(IDB_FILE_EDIT2);
	m_buttonEdit.SetBitmaps(m_bmEdit2,RGB(0,255,0),m_bmEdit1,RGB(0,255,0));
	// delete 
	m_buttonDelete.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(nXSize*3,nY1,nXSize*4,nYSize+nY1),this,ID_EDIT_DELETESELECTEDCATEGORY);
	m_bmDelete2.LoadBitmap(IDB_FILE_DELETE2);
	m_bmDelete1.LoadBitmap(IDB_FILE_DELETE1);
	m_buttonDelete.SetBitmaps(m_bmDelete2,RGB(0,255,0),m_bmDelete1,RGB(0,255,0));
	// add spacer
	int nSpacer = 10;
	// Copy username 
	m_buttonCopyUser.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(nXSize*4+nSpacer,nY1,nXSize*5+nSpacer,nYSize+nY1),this,ID_EDIT_COPY);
	m_bmCopyUser2.LoadBitmap(IDB_FILE_CLIPNAME2);
	m_bmCopyUser1.LoadBitmap(IDB_FILE_CLIPNAME1);
	m_buttonCopyUser.SetBitmaps(m_bmCopyUser2,RGB(0,255,0),m_bmCopyUser1,RGB(0,255,0));
	// Copy password 
	m_buttonCopyPassword.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(nXSize*5+nSpacer,nY1,nXSize*6+nSpacer,nYSize+nY1),this,ID_EDIT_COPYPASSWORDTOCLIPBOARD);
	m_bmCopyPassword2.LoadBitmap(IDB_FILE_CLIPPASS2);
	m_bmCopyPassword1.LoadBitmap(IDB_FILE_CLIPPASS1);
	m_buttonCopyPassword.SetBitmaps(m_bmCopyPassword2,RGB(0,255,0),m_bmCopyPassword1,RGB(0,255,0));
	// Empty clipboard 
	m_buttonEmptyClip.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(nXSize*6+nSpacer,nY1,nXSize*7+nSpacer,nYSize+nY1),this,ID_EDIT_EMPTYPASSWORDFROMCLIPBOARD);
	m_bmEmptyClip2.LoadBitmap(IDB_FILE_EMPTY2);
	m_bmEmptyClip1.LoadBitmap(IDB_FILE_EMPTY1);
	m_buttonEmptyClip.SetBitmaps(m_bmEmptyClip2,RGB(0,255,0),m_bmEmptyClip1,RGB(0,255,0));
	// print 
	m_buttonPrint.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(nXSize*7+nSpacer,nY1,nXSize*8+nSpacer,nYSize+nY1),this,ID_MY_FILE_PRINT);
	m_bmPrint2.LoadBitmap(IDB_FILE_PRINT2);
	m_bmPrint1.LoadBitmap(IDB_FILE_PRINT1);
	m_buttonPrint.SetBitmaps(m_bmPrint2,RGB(0,255,0),m_bmPrint1,RGB(0,255,0));
	nSpacer += 10;
	// search 
	m_buttonSearch.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(nXSize*8+nSpacer,nY1,nXSize*9+nSpacer,nYSize+nY1),this,ID_FIND_ITEM);
	m_bmSearch2.LoadBitmap(IDB_FILE_SEARCHBAR2);
	m_bmSearch1.LoadBitmap(IDB_FILE_SEARCHBAR1);
	m_buttonSearch.SetBitmaps(m_bmSearch2,RGB(0,255,0),m_bmSearch1,RGB(0,255,0));
	// Show details 
	m_buttonShowDetails.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(nXSize*9+nSpacer,nY1,nXSize*10+nSpacer,nYSize+nY1),this,ID_SHOW_POPUP);
	m_bmShowDetails2.LoadBitmap(IDB_FILE_INFO2);
	m_bmShowDetails1.LoadBitmap(IDB_FILE_INFO1);
	m_buttonShowDetails.SetBitmaps(m_bmShowDetails2,RGB(0,255,0),m_bmShowDetails1,RGB(0,255,0));
	// encrypt any unencrypted files 
	m_buttonEncryptFiles.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(nXSize*9+nSpacer,nY1,nXSize*10+nSpacer,nYSize+nY1),this,ID_TRAYMENU_ENCRYPTANYUNENCRYPTEDFILES);
	m_bmEncryptFiles2.LoadBitmap(IDB_FILE_ENCRYPT2);
	m_bmEncryptFiles1.LoadBitmap(IDB_FILE_ENCRYPT1);
	m_buttonEncryptFiles.SetBitmaps(m_bmEncryptFiles2,RGB(0,255,0),m_bmEncryptFiles1,RGB(0,255,0));
 	// load encrypted file 
	m_buttonLoadFile.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(nXSize*10+nSpacer,nY1,nXSize*11+nSpacer,nYSize+nY1),this,IDC_LOAD_FILE);
	m_bmLoadFile2.LoadBitmap(IDB_FILE_LOADFILE2);
	m_bmLoadFile1.LoadBitmap(IDB_FILE_LOADFILE1);
	m_buttonLoadFile.SetBitmaps(m_bmLoadFile2,RGB(0,255,0),m_bmLoadFile1,RGB(0,255,0));
  	// load website 
	m_buttonLoadSite.Create("",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(nXSize*10+nSpacer,nY1,nXSize*11+nSpacer,nYSize+nY1),this,IDC_LOAD_URL);
	m_bmLoadSite2.LoadBitmap(IDB_FILE_LOADSITE2);
	m_bmLoadSite1.LoadBitmap(IDB_FILE_LOADSITE1);
	m_buttonLoadSite.SetBitmaps(m_bmLoadSite2,RGB(0,255,0),m_bmLoadSite1,RGB(0,255,0));

	if(MyGetProfileInt(_T("ShowToolTips"),1) == 1)
	{
		m_buttonOpen.CreateToolTip(_T("Open an existing password database."));
		m_buttonNew.CreateToolTip(_T("Create a new password entry."));
		m_buttonEdit.CreateToolTip(_T("Edit the selected entry."));
		m_buttonDelete.CreateToolTip(_T("Delete the selected entry."));
		m_buttonCopyUser.CreateToolTip(_T("Copy the current username to clipboard."));
		m_buttonCopyPassword.CreateToolTip(_T("Copy the current password to clipboard."));
		m_buttonEmptyClip.CreateToolTip(_T("Empty the Windows clipboard."));
		m_buttonPrint.CreateToolTip(_T("Print."));
		m_buttonLoadSite.CreateToolTip(_T("Load the selected entries website."));
		m_buttonShowDetails.CreateToolTip(_T("Show popup dialog of current entries details."));
		m_buttonSearch.CreateToolTip(_T("Show or hide the search bar."));
		m_buttonLoadFile.CreateToolTip(_T("Load the selected, encrypted file."));
		m_buttonEncryptFiles.CreateToolTip(_T("Encrypt any unencrypted files."));
	}

	return 0;
}

BOOL CMyToolbar::OnCommand(WPARAM wParam, LPARAM lParam)
{
	BOOL bOK = CWnd::OnCommand(wParam, lParam);
	AfxGetMainWnd()->PostMessage(WM_COMMAND,wParam, lParam);
	return bOK;
}

// show toolbar for particular view
void CMyToolbar::ShowToolBar(TOOLBAR_TYPES eToolbar)
{
	switch(eToolbar)
	{
		case TOOLBAR_CREDIT_CARD :
		{
			m_buttonLoadFile.ShowWindow(SW_HIDE);
			m_buttonLoadSite.ShowWindow(SW_HIDE);
			m_buttonEncryptFiles.ShowWindow(SW_HIDE);
			m_buttonShowDetails.ShowWindow(SW_HIDE);
			break;
		}
		case TOOLBAR_ENCRYPTED_FILE :
		{
			m_buttonLoadFile.ShowWindow(SW_SHOW);
			m_buttonLoadSite.ShowWindow(SW_HIDE);
			m_buttonEncryptFiles.ShowWindow(SW_SHOW);
			m_buttonShowDetails.ShowWindow(SW_HIDE);
			break;
		}
		case TOOLBAR_USERNAME_PASSWORD :
		{
			m_buttonLoadFile.ShowWindow(SW_HIDE);
			m_buttonLoadSite.ShowWindow(SW_SHOW);
			m_buttonEncryptFiles.ShowWindow(SW_HIDE);
			m_buttonShowDetails.ShowWindow(SW_SHOW);
			break;
		}
	}
}