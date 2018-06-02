// MyStatic.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "MyStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyStatic

CMyStatic::CMyStatic()
{
	m_dwTextColor = RGB(0,0,0);
}

CMyStatic::~CMyStatic()
{
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	//{{AFX_MSG_MAP(CMyStatic)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyStatic message handlers

HBRUSH CMyStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_dwTextColor);

	return m_brush;
}

void CMyStatic::SetColor(DWORD dwColor)
{
	m_brush.CreateSolidBrush(dwColor);
}
