// MyListBox.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "MyListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListBox

CMyListBox::CMyListBox()
{
}

CMyListBox::~CMyListBox()
{
}


BEGIN_MESSAGE_MAP(CMyListBox, CListBox)
	//{{AFX_MSG_MAP(CMyListBox)
	ON_WM_VKEYTOITEM_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListBox message handlers


int CMyListBox::VKeyToItem(UINT nKey, UINT nIndex)
{
	if(nKey == 46)
	{
		DeleteString(nIndex);
	}

	return -1;
}
