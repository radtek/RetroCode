// PassPopupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "PassPopupDlg.h"
#include ".\passpopupdlg.h"
#include ".\helpers.h"

// CPassPopupDlg dialog

IMPLEMENT_DYNAMIC(CPassPopupDlg, CDialog)
CPassPopupDlg::CPassPopupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPassPopupDlg::IDD, pParent)
	, m_strDescription(_T(""))
	, m_strUserID(_T(""))
	, m_strPassword(_T(""))
	, m_strURL(_T(""))
{
	m_brush.CreateSolidBrush(RGB(255,255,255));
}

CPassPopupDlg::~CPassPopupDlg()
{
}

void CPassPopupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_DESCRIPTION, m_strDescription);
	DDX_Text(pDX, IDC_EDIT_USERID, m_strUserID);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_ctlPassword);
	DDX_Control(pDX, IDC_BUTTON_LOAD_URL, m_ctlLoadWebSite);
	DDX_Control(pDX, IDOK, m_ctlDone);
	DDX_Control(pDX, IDC_BUTTON_COPY_USER, m_ctlCopyUser);
	DDX_Control(pDX, IDC_BUTTON_COPY_PASS, m_ctlCopyPass);
	DDX_Control(pDX, IDC_BUTTON_SHOW_PASS, m_ctlShowPass);
	DDX_Control(pDX, IDC_EDIT_USERID, m_ctlUserID);
}

BEGIN_MESSAGE_MAP(CPassPopupDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COPY_USER, OnBnClickedButtonCopyUser)
	ON_BN_CLICKED(IDC_BUTTON_COPY_PASS, OnBnClickedButtonCopyPass)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_PASS, OnBnClickedButtonShowPass)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_LOAD_URL, OnBnClickedButtonLoadUrl)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void CPassPopupDlg::OnBnClickedButtonCopyUser()
{
	CSharedFile sf(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT);
	sf.Write(m_strUserID, m_strUserID.GetLength()); 
	if(OpenClipboard())
	{
		EmptyClipboard();
		SetClipboardData(CF_TEXT, sf.Detach());
		CloseClipboard();
	}
	else
		AfxMessageBox("Error, failed to copy username to the clipboard.");
}

void CPassPopupDlg::OnBnClickedButtonCopyPass()
{
	CSharedFile sf(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT);
	sf.Write(m_strPassword, m_strPassword.GetLength()); 
	if(OpenClipboard())
	{
		EmptyClipboard();
		SetClipboardData(CF_TEXT, sf.Detach());
		CloseClipboard();
	}
	else
		AfxMessageBox("Error, failed to copy password to the clipboard.");
}

void CPassPopupDlg::OnBnClickedButtonShowPass()
{
	if(m_ctlPassword.GetStyle() & ES_PASSWORD)
	{
		m_ctlPassword.SetPasswordChar(0);
	}
	else
	{
		m_ctlPassword.SetPasswordChar('*');
	}
	m_ctlPassword.RedrawWindow();	
}

// set description field
void CPassPopupDlg::SetDescription(CString strDescription)
{
	m_strDescription = strDescription;
	UpdateData(false);
}

// set user ID field
void CPassPopupDlg::SetUserID(CString strUser)
{
	m_strUserID = strUser;
	UpdateData(false);
}

// set password field
void CPassPopupDlg::SetPassword(CString strPassword)
{
	m_strPassword = strPassword;
	UpdateData(false);
}

// hide window on OK
void CPassPopupDlg::OnBnClickedOk()
{
	SaveRectPos();
	ShowWindow(SW_HIDE);	
}

// hide window OnClose
void CPassPopupDlg::OnClose()
{
	SaveRectPos();
	ShowWindow(SW_HIDE);	
}

// set url and show or hide url button
void CPassPopupDlg::SetURL(CString strURl)
{
	m_strURL = strURl;
	m_ctlLoadWebSite.ShowWindow(m_strURL.IsEmpty()?SW_HIDE:SW_SHOW);
}

// load web site 
void CPassPopupDlg::OnBnClickedButtonLoadUrl()
{
	LoadURLInBrowser(m_strURL);	
}
HBRUSH CPassPopupDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return m_brush;
}

BOOL CPassPopupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	m_ctlDone.GetWindowRect(rect);
	ScreenToClient(rect);
	m_ctlDone.MoveWindow(rect.left,rect.top,60,20);
	m_ctlCopyUser.GetWindowRect(rect);
	ScreenToClient(rect);
	m_ctlCopyUser.MoveWindow(rect.left,rect.top,60,20);
	m_ctlCopyPass.GetWindowRect(rect);
	ScreenToClient(rect);
	m_ctlCopyPass.MoveWindow(rect.left,rect.top,60,20);
	m_ctlShowPass.GetWindowRect(rect);
	ScreenToClient(rect);
	m_ctlShowPass.MoveWindow(rect.left,rect.top,60,20);
	m_ctlLoadWebSite.GetWindowRect(rect);
	ScreenToClient(rect);
	m_ctlLoadWebSite.MoveWindow(rect.left,rect.top,90,20);

	m_bmDone1.LoadBitmap(IDB_BUT_DONE1);
	m_bmDone2.LoadBitmap(IDB_BUT_DONE2);
	m_bmCopy1.LoadBitmap(IDB_BUT_COPY1);
	m_bmCopy2.LoadBitmap(IDB_BUT_COPY2);
	m_bmShow1.LoadBitmap(IDB_BUT_SHOW1);
	m_bmShow2.LoadBitmap(IDB_BUT_SHOW2);
	m_bmLoad1.LoadBitmap(IDB_BUT_LOADSITE1);
	m_bmLoad2.LoadBitmap(IDB_BUT_LOADSITE2);

	m_ctlDone.SetBitmaps(m_bmDone2,RGB(0,128,128),m_bmDone1,RGB(0,128,128));
	m_ctlCopyUser.SetBitmaps(m_bmCopy2,RGB(0,128,128),m_bmCopy1,RGB(0,128,128));
	m_ctlCopyPass.SetBitmaps(m_bmCopy2,RGB(0,128,128),m_bmCopy1,RGB(0,128,128));
	m_ctlShowPass.SetBitmaps(m_bmShow2,RGB(0,128,128),m_bmShow1,RGB(0,128,128));
	m_ctlLoadWebSite.SetBitmaps(m_bmLoad2,RGB(0,128,128),m_bmLoad1,RGB(0,128,128));

	m_ctlDone.CreateToolTip(_T("Close this window"));
	m_ctlCopyUser.CreateToolTip(_T("Copy username to clipboard"));
	m_ctlCopyPass.CreateToolTip(_T("Copy password to clipboard"));
	m_ctlShowPass.CreateToolTip(_T("Show the password"));
	m_ctlLoadWebSite.CreateToolTip(_T("Load the associated website"));

    // set font for user / pass
	m_ctlUserID.SetFont("Times New Roman",10,false);
	m_ctlPassword.SetFont("Times New Roman",10,false);

	return TRUE;  // return TRUE unless you set the focus to a control
}

// save position of dlg
void CPassPopupDlg::SaveRectPos(void)
{
	if(IsWindow(m_hWnd))
	{
		CRect rect;
		GetWindowRect(rect);
		MyWriteProfileInt("PopupX1",rect.left);
		MyWriteProfileInt("PopupY1",rect.top);
		MyWriteProfileInt("PopupX2",rect.right);
		MyWriteProfileInt("PopupY2",rect.bottom);
	}
}

// restore last saved position 
void CPassPopupDlg::SetLastRectPos(void)
{
	int nX2 = MyGetProfileInt("PopupX2",0);
	if(nX2 > 0 && IsWindow(m_hWnd))
	{
		CRect rectCurrent;
		GetWindowRect(rectCurrent);
		int x1 = MyGetProfileInt("PopupX1",0);
		int y1 = MyGetProfileInt("PopupY1",0);
		CRect rect = CRect(x1,y1,x1 + rectCurrent.Width(),y1 + rectCurrent.Height());
		//CRect rect = CRect(MyGetProfileInt("PopupX1",0),MyGetProfileInt("PopupY1",0),nX2,MyGetProfileInt("PopupY2",0));
		
		CRect rectDesk;
		GetDesktopWindow()->GetClientRect(rectDesk);
		if(rect.left >= 0 && rect.top >= 0 && rect.Width() <= rectDesk.Width() && rect.Height() <= rectDesk.Height())
			MoveWindow(rect);
	}
}



