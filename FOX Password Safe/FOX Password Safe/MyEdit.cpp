// MyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "MyEdit.h"
#include ".\myedit.h"

// CMyEdit
IMPLEMENT_DYNAMIC(CMyEdit, CEdit)
CMyEdit::CMyEdit()
{
	m_pfont = NULL;
	m_brush.CreateSolidBrush(RGB(255,255,255));
}

CMyEdit::~CMyEdit()
{
	if(m_pfont)
	{
		delete m_pfont;
		m_pfont = NULL;
	}	
}

BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_CREATE()	
END_MESSAGE_MAP()

// CMyEdit message handlers
HBRUSH CMyEdit::CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/)
{
	return m_brush;
}

int CMyEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetFont();

	return 0;
}

// create font for this control
void CMyEdit::SetFont(CString strTypeFace, int nSize, bool bBold)
{
	if(m_pfont)
	{
		delete m_pfont;
		m_pfont = NULL;
	}
	m_pfont = new CFont();

	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = -MulDiv(12, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSY), 72);
	if(bBold)
		lf.lfWeight = 700;
	strcpy(lf.lfFaceName, strTypeFace);
	m_pfont->CreateFontIndirect(&lf);  

	CEdit::SetFont(m_pfont);
}

