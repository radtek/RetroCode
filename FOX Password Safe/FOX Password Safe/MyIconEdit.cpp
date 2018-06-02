// MyIconEdit.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "MyIconEdit.h"
#include ".\myiconedit.h"
#include "helpers.h"

// CMyIconEdit


IMPLEMENT_DYNAMIC(CMyIconEdit, CWnd)
CMyIconEdit::CMyIconEdit()
: m_nIconXPos(0)
{
	m_pButtonIcon = NULL;
	m_nButtonFunction = 0;
	m_nIconXPos = 0;
}

CMyIconEdit::~CMyIconEdit()
{
	if(m_pButtonIcon)
	{
		delete m_pButtonIcon;
		m_pButtonIcon = NULL;
	}
}

BEGIN_MESSAGE_MAP(CMyIconEdit, CWnd)
	ON_WM_CREATE()
	ON_COMMAND(IDC_MYBUTTON_ID,OnButtonClick)	
END_MESSAGE_MAP()

int CMyIconEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

// custom create function
BOOL CMyIconEdit::MyCreate(DWORD style, CRect rect, CWnd* pParent)
{
	BOOL bOK = CWnd::Create(NULL,"MyIconEdit",WS_CHILD,rect,pParent,1);
	m_Edit.Create(WS_VISIBLE|style,rect,this,1);

	return 0;
}

// get width size of text and icon 
int CMyIconEdit::GetSizeX(void)
{
	int nSizeX = m_nIconXPos;
	if(m_pButtonIcon)
	{
		CRect rect;
		m_pButtonIcon->GetClientRect(rect);
		nSizeX += rect.Width();
	}
	return nSizeX;
}

// set edit text
void CMyIconEdit::SetText(CString strText)
{
	if(IsWindow(m_Edit.m_hWnd))
		m_Edit.SetWindowText(strText);
}

void CMyIconEdit::OnButtonClick()
{
	// copy text to clipboard
	if(m_nButtonFunction == 1)
	{
		CString strBuf;
		m_Edit.GetWindowText(strBuf);
		if(strBuf.IsEmpty())
			return;
		CSharedFile sf(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT);
		sf.Write(strBuf, strBuf.GetLength()); 
		if(OpenClipboard())
		{
			EmptyClipboard();
			SetClipboardData(CF_TEXT, sf.Detach());
			CloseClipboard();
		}
		else
			AfxMessageBox("Error, failed to copy text to the clipboard.");
	}
	// load URL
	else if(m_nButtonFunction == 2)
	{
		AfxGetMainWnd()->PostMessage(WM_LOAD_URL);
	}
}

void CMyIconEdit::SetPasswordChar(char nChar)
{
	if(IsWindow(m_Edit.m_hWnd))
		m_Edit.SetPasswordChar(nChar);
}

// hides icon from window
void CMyIconEdit::HideIconButton(void)
{
	if(m_pButtonIcon)
	{
		delete m_pButtonIcon;
		m_pButtonIcon = NULL;
	}
	CRect rectCl;
	GetClientRect(rectCl);
	m_Edit.MoveWindow(rectCl);
}

// set buttons tool tip
void CMyIconEdit::SetToolTip(CString strText)
{
	if(m_pButtonIcon)
		m_pButtonIcon->SetToolTip(strText);
}

// show an icon button at the end of the text
void CMyIconEdit::ShowButton(UINT imageDown, UINT imageUp, int nImageLength, int nImageHeight, UINT buttonFunction, CRect* pRectPos)
{
	if(m_pButtonIcon)
	{
		delete m_pButtonIcon;
		m_pButtonIcon = NULL;
	}
	// create icon button
	m_pButtonIcon = new CMyButton();
	CRect rect;
	if(pRectPos != NULL)
	{
		rect = pRectPos;
	}
	else
	{
		CRect rectText;
		m_Edit.GetRect(rectText);
		CString strBuf;
		m_Edit.GetWindowText(strBuf);
		CSize size;
		CDC* pDC = m_Edit.GetDC();
		GetTextExtentPoint32(pDC->m_hDC,strBuf,strBuf.GetLength(),&size);
		m_Edit.ReleaseDC(pDC);
		size.cx += rectText.left;

		rect.top = 0;
		rect.bottom = nImageHeight;
		rect.left = size.cx + ICON_SPACE_X;
		rect.right = rect.left + nImageLength;
	}
	BOOL bOK = m_pButtonIcon->Create(_T(""),WS_CHILD|WS_TABSTOP|BS_PUSHBUTTON|BS_OWNERDRAW,
		rect,this,IDC_MYBUTTON_ID);
	m_pButtonIcon->LoadImageDown(imageDown);
	m_pButtonIcon->LoadImage(imageUp);
	m_pButtonIcon->ShowWindow(SW_SHOW);
	m_nButtonFunction = buttonFunction;

	CRect rectCl;
	GetClientRect(rectCl);
	rectCl.right = rect.left;// - ICON_SPACE_X;
	m_nIconXPos = rect.left;
	m_Edit.MoveWindow(rectCl);
}