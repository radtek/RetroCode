// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "MyButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyButton

CMyButton::CMyButton()
{
	m_dwTextColor = RGB(0,0,0);
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	//{{AFX_MSG_MAP(CMyButton)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyButton message handlers

HBRUSH CMyButton::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_dwTextColor);

	return m_brush;
}

void CMyButton::SetColor(DWORD dwColor)
{
	m_brush.CreateSolidBrush(dwColor);
}
