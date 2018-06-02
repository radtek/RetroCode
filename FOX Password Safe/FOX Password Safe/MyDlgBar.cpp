// MyDlgBar.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "MyDlgBar.h"
#include ".\mydlgbar.h"


// CMyDlgBar

IMPLEMENT_DYNAMIC(CMyDlgBar, CDialogBar)
CMyDlgBar::CMyDlgBar()
{
}

CMyDlgBar::~CMyDlgBar()
{
}


BEGIN_MESSAGE_MAP(CMyDlgBar, CDialogBar)
END_MESSAGE_MAP()



// CMyDlgBar message handlers
/*
To implement a transparent dialog bar in a rebar band 
Using the Add Class dialog box, add a new class (for example, CMyDlgBar) that implements your dialog bar object. 
Add a handler for the WM_ERASEBKGND message. 
In the new handler, modify the existing code to match the following example: 
BOOL CMyDlgBar::OnEraseBkgnd( CDC* pDC )
{
    CWnd* pParent = GetParent();
    ASSERT_VALID(pParent);
    CPoint pt(0, 0);
    MapWindowPoints(pParent, &pt, 1);
    pt = pDC->OffsetWindowOrg(pt.x, pt.y);
    LRESULT lResult = pParent->SendMessage(WM_ERASEBKGND,
        (WPARAM)pDC->m_hDC, 0L);
    pDC->SetWindowOrg(pt.x, pt.y);
    return lResult;
}
Add a handler for the WM_MOVE message. 
In the new handler, modify the existing code to match the following example: 
BOOL CMyDlgBar::OnMove( int cx, int cy )
{
    Invalidate();
}
*/

BOOL CMyDlgBar::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	BOOL bOK = CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID);

	m_butNew.Create("New",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_OWNERDRAW,CRect(0,10,50,10+27),this,IDC_NEW);
	m_butNew.LoadImage(IDR_JPEG_NEW_UP);
	m_butNew.LoadImageDown(IDR_JPEG_NEW_DOWN);

	m_butOpen.Create("Open",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_OWNERDRAW,CRect(50,10,50+54,10+27),this,IDC_OPEN);
	m_butOpen.LoadImage(IDR_JPEG_OPEN_UP);
	m_butOpen.LoadImageDown(IDR_JPEG_OPEN_DOWN);

	m_butLoadURL.Create("LoadURL",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_OWNERDRAW,CRect(104,10,104+84,10+27),this,IDC_LOAD_URL);
	m_butLoadURL.LoadImage(IDR_JPEG_LOADURL_UP);
	m_butLoadURL.LoadImageDown(IDR_JPEG_LOADURL_DOWN);

	m_butCopyUser.Create("CopyUser",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_OWNERDRAW,CRect(188,10,188+122,10+27),this,IDC_COPY_USER_CLIP);
	m_butCopyUser.LoadImage(IDR_JPEG_COPYUSER_UP);
	m_butCopyUser.LoadImageDown(IDR_JPEG_COPYUSER_DOWN);

	m_butCopyPass.Create("CopyPass",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_OWNERDRAW,CRect(310,10,310+121,10+27),this,IDC_COPY_PASS_CLIP);
	m_butCopyPass.LoadImage(IDR_JPEG_COPYPASS_UP);
	m_butCopyPass.LoadImageDown(IDR_JPEG_COPYPASS_DOWN);

	m_butClearClip.Create("ClearCipboard",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_OWNERDRAW,CRect(431,10,431+110,10+27),this,IDC_CLEAR_CLIP);
	m_butClearClip.LoadImage(IDR_JPEG_CLEARMEM_UP);
	m_butClearClip.LoadImageDown(IDR_JPEG_CLEARMEM_DOWN);

	return bOK;
}
