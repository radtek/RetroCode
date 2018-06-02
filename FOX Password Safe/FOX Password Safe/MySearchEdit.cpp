// MySearchEdit.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "MySearchEdit.h"
#include ".\mysearchedit.h"


// CMySearchEdit

IMPLEMENT_DYNAMIC(CMySearchEdit, CEdit)
CMySearchEdit::CMySearchEdit()
{
}

CMySearchEdit::~CMySearchEdit()
{
}


BEGIN_MESSAGE_MAP(CMySearchEdit, CEdit)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CMySearchEdit message handlers

void CMySearchEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	if(nChar == 13)
		AfxGetMainWnd()->PostMessage(WM_COMMAND,IDC_BUTTON_SEARCH,0);
	else
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
