// FOX Password SafeView.cpp : implementation of the CFOXPasswordSafeView class
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "FOX Password SafeDoc.h"
#include "FOX Password SafeView.h"
#include ".\fox password safeview.h"
#include "helpers.h"
#include "PrintSelectDlg.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define LEFT_TEXT_WIDTH		140
#define RIGHT_TEXT_START	150

// CFOXPasswordSafeView

IMPLEMENT_DYNCREATE(CFOXPasswordSafeView, CScrollView)

BEGIN_MESSAGE_MAP(CFOXPasswordSafeView, CScrollView)
	ON_WM_STYLECHANGED()
	// Standard printing commands
	ON_COMMAND(ID_MY_FILE_PRINT, OnMyFilePrint)
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnMyFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnMyFilePrintPreview)
	ON_COMMAND(ID_SHOW_HIDE_PASSWORD,OnShowHidePassword)
	ON_COMMAND(ID_SHOW_HIDE_PREVIOUS_PASSWORD,OnShowHidePrevPassword)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CFOXPasswordSafeView construction/destruction

CFOXPasswordSafeView::CFOXPasswordSafeView()
{	

}

CFOXPasswordSafeView::~CFOXPasswordSafeView()
{
}

BOOL CFOXPasswordSafeView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

void CFOXPasswordSafeView::OnInitialUpdate()
{
	SetScrollSizes(MM_TEXT,CSize(100,100));
	CScrollView::OnInitialUpdate();

	CRect rect;
	GetClientRect(rect);
	// description field
	m_rectDesc = CRect(RIGHT_TEXT_START,20,rect.Width()-10,20+20);
	m_editDesc.Create(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,m_rectDesc,this,1);
	m_editDesc.SetFont("Times New Roman",12,true);
	// username password fields
	// username or ID field
	m_rectUsername = CRect(RIGHT_TEXT_START,50,rect.Width()-10,50+20);
	m_editUsername.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,m_rectUsername,this);
	// password field
	m_rectPassword = CRect(RIGHT_TEXT_START,80,rect.Width()-170,80+20);
	m_editPassword.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY|ES_PASSWORD,m_rectPassword,this);
	// show or hide password button
	m_rectButShowPass = CRect(rect.Width()-30,80,rect.Width()-10,80+20);
	m_butShowPass.Create(_T(""),WS_CHILD|WS_TABSTOP|BS_PUSHBUTTON|BS_OWNERDRAW,m_rectButShowPass,this,ID_SHOW_HIDE_PASSWORD);
	m_bmShowPass2.LoadBitmap(IDB_SHOWPASS2);
	m_bmShowPass1.LoadBitmap(IDB_SHOWPASS1);
	m_butShowPass.SetToolTip(_T("Show or hide password."));
	m_butShowPass.LoadImage(IDB_SHOWPASS1);
	m_butShowPass.LoadImageDown(IDB_SHOWPASS2);
	// Previous password field
	m_rectPreviousPassword = CRect(RIGHT_TEXT_START,110,rect.Width()-170,110+20);
	m_editPreviousPassword.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY|ES_PASSWORD,m_rectPreviousPassword,this);
	// show or hide previous password button
	m_rectButShowPrevPass = CRect(rect.Width()-30,110,rect.Width()-10,110+20);
	m_butShowPrevPass.Create(_T(""),WS_CHILD|WS_TABSTOP|BS_PUSHBUTTON|BS_OWNERDRAW,m_rectButShowPrevPass,this,ID_SHOW_HIDE_PREVIOUS_PASSWORD);
	m_butShowPrevPass.SetToolTip("Show or hide password");
	m_butShowPrevPass.LoadImage(IDB_SHOWPASS1);
	m_butShowPrevPass.LoadImageDown(IDB_SHOWPASS2);
	// password expire date field
	m_rectPassExpire = CRect(RIGHT_TEXT_START,140,rect.Width()-10,140+20);
	m_editPassExpire.Create(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,m_rectPassExpire,this,1);
	// URL field
	m_rectURL = CRect(RIGHT_TEXT_START,170,rect.Width()-10,170+20);
	m_editURL.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,m_rectURL,this);
	// Notes field
	m_rectNotes = CRect(RIGHT_TEXT_START,200,rect.Width()-10,200+100);
	m_editNotes.Create(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_READONLY,m_rectNotes,this,1);	
	// credit card edit fields
	// card type
	m_editCardType.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// card number
	m_editCardNumber.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// name on card
	m_editNameOnCard.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// expire date
	m_editExpireDate.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// CCV number
	m_editCCVNumber.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// bank name
	m_editBankName.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// Billing full name
	m_editBillingName.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// company
	m_editCompany.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// Address line 1
	m_editAddress1.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// Address line 2
	m_editAddress2.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// City
	m_editCity.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// State
	m_editState.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// Postcode
	m_editPostcode.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// Country
	m_editCountry.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// Email
	m_editEmail.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
	// Phone
	m_editPhone.MyCreate(WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL|ES_READONLY,CRect(0,0,0,0),this);
}

// CFOXPasswordSafeView diagnostics

#ifdef _DEBUG
void CFOXPasswordSafeView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFOXPasswordSafeView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CFOXPasswordSafeDoc* CFOXPasswordSafeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFOXPasswordSafeDoc)));
	return (CFOXPasswordSafeDoc*)m_pDocument;
}
#endif //_DEBUG


// CFOXPasswordSafeView message handlers
void CFOXPasswordSafeView::OnStyleChanged(int /*nStyleType*/, LPSTYLESTRUCT /*lpStyleStruct*/)
{
	Default();
}

// add item to list control
BOOL CFOXPasswordSafeView::InsertListItem(CString strDesc)
{
	return 0;
}

// save entry data in document
void CFOXPasswordSafeView::SetMyData(CString strData, bool bHeader)
{
	CFOXPasswordSafeDoc* pDoc = GetDocument();
	pDoc->m_strData = strData;
	pDoc->m_bIsHeader = bHeader;
	pDoc->UpdateAllViews(NULL);
}

void CFOXPasswordSafeView::OnDraw(CDC* pDC)
{
	CFOXPasswordSafeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_strData.IsEmpty()) // display empty message
	{
		//ShowButtons(false,false);
		// draw logo
		BITMAP bit;
		CBitmap bmp;
		bmp.LoadBitmap(IDB_LOGO1);
		bmp.GetBitmap(&bit);

		CDC dcMemory;
		dcMemory.CreateCompatibleDC(pDC);
		CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);
		pDC->BitBlt(20,10,bit.bmWidth,bit.bmHeight,&dcMemory,0, 0, SRCCOPY);
		dcMemory.SelectObject(pOldBitmap);

		CFont font;
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));
		lf.lfWeight = 700;
		lf.lfHeight = -MulDiv(20, GetDeviceCaps(pDC->m_hDC, LOGPIXELSY), 72);  
		lf.lfItalic = true;
		strcpy(lf.lfFaceName, "Times New Roman");
		VERIFY(font.CreateFontIndirect(&lf));  

		CFont* pOld = pDC->SelectObject(&font);
		pDC->DrawText("FOX Password Safe",CRect(100,20,500,60),DT_WORDBREAK|DT_LEFT);
		// draw msg
		CFont font2;
		font2.CreatePointFont(120,"Times New Roman");
		pDC->SelectObject(&font2);
		CString strText;
		strText.LoadString(IDS_BLANK_DOC_INTRO);
		pDC->DrawText(strText,CRect(100,60,500,200),DT_WORDBREAK|DT_LEFT);

		pDC->SelectObject(pOld);
	}
	else if(pDoc->m_bIsHeader) // draw header
	{
		//ShowButtons(false,false);
		CFont font2;
		font2.CreatePointFont(120,"Times New Roman");
		CFont* pOld = pDC->SelectObject(&font2);
		CString strText;
		strText.Format("%s - Category",ParseXML("Header",pDoc->m_strData));
		pDC->DrawText(strText,CRect(100,20,500,200),DT_WORDBREAK|DT_LEFT);
		pDC->SelectObject(pOld);
	}
	else // draw entry
	{
		CFont font2;
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));
		lf.lfHeight = -MulDiv(12, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSY), 72);  
		lf.lfItalic = true;
		strcpy(lf.lfFaceName, "Times New Roman");
		VERIFY(font2.CreateFontIndirect(&lf));
		CFont* pOld = pDC->SelectObject(&font2);

		// description
		pDC->DrawText(_T("Description:"),CRect(10,m_rectDesc.top,LEFT_TEXT_WIDTH,m_rectDesc.bottom),DT_RIGHT);
		m_editDesc.SetWindowText(ParseXML("Description",pDoc->m_strData));

		// credit card entry ?
		if(ParseXML("CreditCard",pDoc->m_strData) == "TRUE")
		{
			CRect rect;
			GetClientRect(rect);
			CRect rectTopText(10,m_rectUsername.top,LEFT_TEXT_WIDTH,m_rectUsername.bottom);
			// card type
			CString strBuffer = ParseXML("CardType",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("Card Type:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}
			// card number
			strBuffer = ParseXML("CardNumber",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("Card number:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}
			// name on card
			strBuffer = ParseXML("NameOnCard",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("Name on Card:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}
			// expire date
			strBuffer = ParseXML("Expiredate",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("Expire Date:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}
			// verification number
			strBuffer = ParseXML("CCVNumber",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("Verification Num:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}	
			// bank name
			strBuffer = ParseXML("BankName",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("Bank Name:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}	
			// billing information
			// full name
			strBuffer = ParseXML("BillingName",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("Billing Name:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}	
			// company
			strBuffer = ParseXML("BillingCompany",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("Company:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}	
			// address line 1
			strBuffer = ParseXML("BillingAddress1",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("Address Line 1:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}	
			// address line 2
			strBuffer = ParseXML("BillingAddress2",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("Address Line 2:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}	
			// city
			strBuffer = ParseXML("BillingCity",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("City:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}	
			// state
			strBuffer = ParseXML("BillingState",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("State:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}	
			// postcode
			strBuffer = ParseXML("BillingPostcode",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("Postcode:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}	
			// country
			strBuffer = ParseXML("BillingCountry",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("County:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}	
			// email address
			strBuffer = ParseXML("BillingEmail",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("Email:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}	
			// phone number
			strBuffer = ParseXML("BillingPhone",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("Phone:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}
			//ShowButtons(true,true);
		}
		// encrypted file entry
		else if(ParseXML("EncryptedFile",pDoc->m_strData) == "TRUE")
		{
			CRect rect;
			GetClientRect(rect);
			CRect rectTopText(10,m_rectUsername.top,LEFT_TEXT_WIDTH,m_rectUsername.bottom);
			// File name
			CString strBuffer = ParseXML("FilePath",pDoc->m_strData);
			if(!strBuffer.IsEmpty())
			{
				pDC->DrawText(_T("File path:"),rectTopText,DT_RIGHT);
				rectTopText.InflateRect(0,-30,0,30);
			}
			// password
			pDC->DrawText(_T("Password:"),CRect(10,m_rectPassword.top,LEFT_TEXT_WIDTH,m_rectPassword.bottom),DT_RIGHT);
			// previous password
			pDC->DrawText(_T("Previous Password:"),CRect(10,m_rectPreviousPassword.top,LEFT_TEXT_WIDTH,m_rectPreviousPassword.bottom),DT_RIGHT);
			// expire date	
			pDC->DrawText(_T("Password expires:"),CRect(10,m_rectPassExpire.top,LEFT_TEXT_WIDTH,m_rectPassExpire.bottom),DT_RIGHT);
			BOOL bHasExpired = false;
			CString strExpires = ConvertToDateString(ParseXML("Expires",pDoc->m_strData),bHasExpired);
			if(strExpires.IsEmpty())
				strExpires = _T("Never");
			if(bHasExpired)
			{
				m_editPassExpire.SetFont("Times New Roman",12,true);
				m_editPassExpire.SetWindowText(strExpires + " Password Expired...");
			}
			else
			{
				m_editPassExpire.SetFont("Times New Roman",12,false);
				m_editPassExpire.SetWindowText(strExpires);
			}
			// notes
			pDC->DrawText(_T("Notes:"),CRect(10,m_rectURL.top,LEFT_TEXT_WIDTH,m_rectNotes.bottom),DT_RIGHT);
			m_editNotes.SetWindowText(ParseXML("Notes",pDoc->m_strData));
			//ShowButtons(true,false);
		}
		// draw username password entry
		else 
		{
			// userID
			pDC->DrawText(_T("Username or ID:"),CRect(10,m_rectUsername.top,LEFT_TEXT_WIDTH,m_rectUsername.bottom),DT_RIGHT);
			m_editUsername.SetText(ParseXML("UserID",pDoc->m_strData));
			// password
			pDC->DrawText(_T("Password:"),CRect(10,m_rectPassword.top,LEFT_TEXT_WIDTH,m_rectPassword.bottom),DT_RIGHT);
			// previous password
			pDC->DrawText(_T("Previous Password:"),CRect(10,m_rectPreviousPassword.top,LEFT_TEXT_WIDTH,m_rectPreviousPassword.bottom),DT_RIGHT);
			// expire date	
			pDC->DrawText(_T("Password expires:"),CRect(10,m_rectPassExpire.top,LEFT_TEXT_WIDTH,m_rectPassExpire.bottom),DT_RIGHT);
			BOOL bHasExpired = false;
			CString strExpires = ConvertToDateString(ParseXML("Expires",pDoc->m_strData),bHasExpired);
			if(strExpires.IsEmpty())
				strExpires = _T("Never");
			if(bHasExpired)
			{
				m_editPassExpire.SetFont("Times New Roman",12,true);
				m_editPassExpire.SetWindowText(strExpires + " Password Expired...");
			}
			else
			{
				m_editPassExpire.SetFont("Times New Roman",12,false);
				m_editPassExpire.SetWindowText(strExpires);
			}
			// web site
			pDC->DrawText(_T("Web site:"),CRect(10,m_rectURL.top,LEFT_TEXT_WIDTH,m_rectURL.bottom),DT_RIGHT);
			// notes
			pDC->DrawText(_T("Notes:"),CRect(10,m_rectNotes.top,LEFT_TEXT_WIDTH,m_rectNotes.bottom),DT_RIGHT);
			m_editNotes.SetWindowText(ParseXML("Notes",pDoc->m_strData));
			//ShowButtons(true,false);
		}
		pDC->SelectObject(pOld);
	}
}

// Show or hide buttons and edit controls
void CFOXPasswordSafeView::ShowButtons(BOOL bShow, BOOL bIsCreditCard)
{
	if(bShow)
	{
		m_editDesc.ShowWindow(SW_SHOW);
		if(!bIsCreditCard)
		{
			// show user pass
			m_editUsername.ShowWindow(SW_SHOW);
			m_editPassword.ShowWindow(SW_SHOW);
			m_editPreviousPassword.ShowWindow(SW_SHOW);
			m_editPassExpire.ShowWindow(SW_SHOW);
			m_editURL.ShowWindow(SW_SHOW);
			m_editNotes.ShowWindow(SW_SHOW);
			m_butShowPass.ShowWindow(SW_SHOW);

			CFOXPasswordSafeDoc* pDoc = GetDocument();
			if(pDoc)
			{
				if(ParseXML("PasswordOld",pDoc->m_strData).IsEmpty())
					m_butShowPrevPass.ShowWindow(SW_HIDE);
				else
					m_butShowPrevPass.ShowWindow(SW_SHOW);
			}
			// hide credit cards
			m_editCardType.ShowWindow(SW_HIDE);
			m_editCardNumber.ShowWindow(SW_HIDE);
			m_editNameOnCard.ShowWindow(SW_HIDE);
			m_editExpireDate.ShowWindow(SW_HIDE);
			m_editCCVNumber.ShowWindow(SW_HIDE);
			m_editBankName.ShowWindow(SW_HIDE);
			m_editBillingName.ShowWindow(SW_HIDE);
			m_editCompany.ShowWindow(SW_HIDE);
			m_editAddress1.ShowWindow(SW_HIDE);
			m_editAddress2.ShowWindow(SW_HIDE);
			m_editCity.ShowWindow(SW_HIDE);
			m_editState.ShowWindow(SW_HIDE);
			m_editPostcode.ShowWindow(SW_HIDE);
			m_editCountry.ShowWindow(SW_HIDE);
			m_editEmail.ShowWindow(SW_HIDE);
			m_editPhone.ShowWindow(SW_HIDE);
		}
		else
		{
			// hide user pass
			m_editUsername.ShowWindow(SW_HIDE);
			m_editPassword.ShowWindow(SW_HIDE);
			m_editPreviousPassword.ShowWindow(SW_HIDE);
			m_editPassExpire.ShowWindow(SW_HIDE);
			m_editURL.ShowWindow(SW_HIDE);
			m_editNotes.ShowWindow(SW_HIDE);
			m_butShowPass.ShowWindow(SW_HIDE);
			m_butShowPrevPass.ShowWindow(SW_HIDE);
			// show credit cards
			m_editCardType.ShowWindow(SW_SHOW);
			m_editCardNumber.ShowWindow(SW_SHOW);
			m_editNameOnCard.ShowWindow(SW_SHOW);
			m_editExpireDate.ShowWindow(SW_SHOW);
			m_editCCVNumber.ShowWindow(SW_SHOW);
			m_editBankName.ShowWindow(SW_SHOW);
			m_editBillingName.ShowWindow(SW_SHOW);
			m_editCompany.ShowWindow(SW_SHOW);
			m_editAddress1.ShowWindow(SW_SHOW);
			m_editAddress2.ShowWindow(SW_SHOW);
			m_editCity.ShowWindow(SW_SHOW);
			m_editState.ShowWindow(SW_SHOW);
			m_editPostcode.ShowWindow(SW_SHOW);
			m_editCountry.ShowWindow(SW_SHOW);
			m_editEmail.ShowWindow(SW_SHOW);
			m_editPhone.ShowWindow(SW_SHOW);
		}
	}
	else
	{
		// hide user pass
		m_editDesc.ShowWindow(SW_HIDE);
		m_editUsername.ShowWindow(SW_HIDE);
		m_editPassword.ShowWindow(SW_HIDE);
		m_editPreviousPassword.ShowWindow(SW_HIDE);
		m_editPassExpire.ShowWindow(SW_HIDE);
		m_editURL.ShowWindow(SW_HIDE);
		m_editNotes.ShowWindow(SW_HIDE);
		m_butShowPass.ShowWindow(SW_HIDE);
		m_butShowPrevPass.ShowWindow(SW_HIDE);
		// hide credit cards
		m_editCardType.ShowWindow(SW_HIDE);
		m_editCardNumber.ShowWindow(SW_HIDE);
		m_editNameOnCard.ShowWindow(SW_HIDE);
		m_editExpireDate.ShowWindow(SW_HIDE);
		m_editCCVNumber.ShowWindow(SW_HIDE);
		m_editBankName.ShowWindow(SW_HIDE);
		m_editBillingName.ShowWindow(SW_HIDE);
		m_editCompany.ShowWindow(SW_HIDE);
		m_editAddress1.ShowWindow(SW_HIDE);
		m_editAddress2.ShowWindow(SW_HIDE);
		m_editCity.ShowWindow(SW_HIDE);
		m_editState.ShowWindow(SW_HIDE);
		m_editPostcode.ShowWindow(SW_HIDE);
		m_editCountry.ShowWindow(SW_HIDE);
		m_editEmail.ShowWindow(SW_HIDE);
		m_editPhone.ShowWindow(SW_HIDE);
	}	
}

void CFOXPasswordSafeView::OnShowHidePassword()
{
	if(m_editPassword.m_Edit.GetStyle() & ES_PASSWORD)
	{
		m_editPassword.SetPasswordChar(0);
	}
	else
	{
		m_editPassword.SetPasswordChar('*');
	}
	m_editPassword.RedrawWindow();	
}

void CFOXPasswordSafeView::OnShowHidePrevPassword()
{
	if(m_editPreviousPassword.m_Edit.GetStyle() & ES_PASSWORD)
	{
		m_editPreviousPassword.SetPasswordChar(0);
	}
	else
	{
		m_editPreviousPassword.SetPasswordChar('*');
	}
	m_editPreviousPassword.RedrawWindow();	
}

// Get selected username
BOOL CFOXPasswordSafeView::GetSelectedUserName(CString& strReturn)
{
	CFOXPasswordSafeDoc* pDoc = GetDocument();
	if(pDoc->m_strData.IsEmpty() || pDoc->m_bIsHeader)
		return false;
	strReturn = ParseXML("UserID",pDoc->m_strData);
	return true;
}

// get selected password
BOOL CFOXPasswordSafeView::GetSelectedPassword(CString& strReturn)
{
	CFOXPasswordSafeDoc* pDoc = GetDocument();
	if(pDoc->m_strData.IsEmpty() || pDoc->m_bIsHeader)
		return false;
	strReturn = ParseXML("Password",pDoc->m_strData);
	return true;
}

// load selected url in browser
BOOL CFOXPasswordSafeView::GetSelectedURL(CString& strReturn,BOOL& bLockDown)
{
	CFOXPasswordSafeDoc* pDoc = GetDocument();
	if(pDoc->m_strData.IsEmpty() || pDoc->m_bIsHeader)
		return false;
	strReturn = ParseXML("URL",pDoc->m_strData);
	bLockDown = (ParseXML("LockDownBrowser",pDoc->m_strData) == "TRUE");
	return true;
}

void CFOXPasswordSafeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CRect rect;
	GetClientRect(rect);
	if(!IsWindow(m_editPassword.m_hWnd))
		return;
	CFOXPasswordSafeDoc* pDoc = GetDocument();
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();

	// display empty message
	if(pDoc->m_strData.IsEmpty()) 
	{
		ShowButtons(false,false);
	}
	// draw header
	else if(pDoc->m_bIsHeader) 
	{
		ShowButtons(false,false);
	}
	// credit card entry
	else if(ParseXML("CreditCard",pDoc->m_strData) == "TRUE")
	{
		pMain->ShowToolBar(TOOLBAR_CREDIT_CARD);

		ShowButtons(true,true);

		int cx = 10;
		int nSizeX = 0;
		int nWidth = rect.Width()-10;
		if(nWidth < 800)
			nWidth = 800;
		CRect rectTopField(RIGHT_TEXT_START,50,nWidth,50+20);
		CPoint pt = GetScrollPosition();
		rectTopField.DeflateRect(-pt.x,-pt.y,pt.x,pt.y);
		// card type
		CString strBuffer = ParseXML("CardType",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editCardType.MoveWindow(rectTopField);
			m_editCardType.SetText(strBuffer);
			m_editCardType.ShowWindow(SW_SHOW);
			m_editCardType.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editCardType.SetToolTip("Copy text to clipboard");
			CRect rectSize;
			m_editCardType.GetClientRect(rectSize);
			nSizeX = rectSize.Width();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}
		else
		{
			m_editCardType.ShowWindow(SW_HIDE);
			m_editCardType.SetText("");
		}
		// card number
		strBuffer = ParseXML("CardNumber",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editCardNumber.MoveWindow(rectTopField);
			m_editCardNumber.SetText(strBuffer);
			m_editCardNumber.ShowWindow(SW_SHOW);
			m_editCardNumber.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editCardNumber.SetToolTip("Copy text to clipboard");
			CRect rectSize;
			m_editCardNumber.GetClientRect(rectSize);
			nSizeX = rectSize.Width();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}
		else
		{
			m_editCardNumber.ShowWindow(SW_HIDE);
			m_editCardNumber.SetText("");
		}
		// name on card
		strBuffer = ParseXML("NameOnCard",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editNameOnCard.MoveWindow(rectTopField);
			m_editNameOnCard.SetText(strBuffer);
			m_editNameOnCard.ShowWindow(SW_SHOW);
			m_editNameOnCard.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editNameOnCard.SetToolTip("Copy text to clipboard");
			CRect rectSize;
			m_editNameOnCard.GetClientRect(rectSize);
			nSizeX = rectSize.Width();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}
		else
		{
			m_editNameOnCard.ShowWindow(SW_HIDE);
			m_editNameOnCard.SetText("");
		}
		// expire date
		strBuffer = ParseXML("Expiredate",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editExpireDate.MoveWindow(rectTopField);
			m_editExpireDate.SetText(strBuffer);
			m_editExpireDate.ShowWindow(SW_SHOW);
			m_editExpireDate.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editExpireDate.SetToolTip("Copy text to clipboard");
			CRect rectSize;
			m_editExpireDate.GetClientRect(rectSize);
			nSizeX = rectSize.Width();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}
		else
		{
			m_editExpireDate.ShowWindow(SW_HIDE);
			m_editExpireDate.SetText("");
		}
		// verification number
		strBuffer = ParseXML("CCVNumber",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editCCVNumber.MoveWindow(rectTopField);
			m_editCCVNumber.SetText(strBuffer);
			m_editCCVNumber.ShowWindow(SW_SHOW);
			m_editCCVNumber.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editCCVNumber.SetToolTip("Copy text to clipboard");
			CRect rectSize;
			m_editCCVNumber.GetClientRect(rectSize);
			nSizeX = rectSize.Width();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}	
		else
		{
			m_editCCVNumber.ShowWindow(SW_HIDE);
			m_editCCVNumber.SetText("");
		}
		// bank name
		strBuffer = ParseXML("BankName",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editBankName.MoveWindow(rectTopField);
			m_editBankName.SetText(strBuffer);
			m_editBankName.ShowWindow(SW_SHOW);
			m_editBankName.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editBankName.SetToolTip("Copy text to clipboard");
			CRect rectSize;
			m_editBankName.GetClientRect(rectSize);
			nSizeX = rectSize.Width();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}	
		else
		{
			m_editBankName.ShowWindow(SW_HIDE);
			m_editBankName.SetText("");
		}
		// billing information
		// full name
		strBuffer = ParseXML("BillingName",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editBillingName.MoveWindow(rectTopField);
			m_editBillingName.SetText(strBuffer);
			m_editBillingName.ShowWindow(SW_SHOW);
			m_editBillingName.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editBillingName.SetToolTip("Copy text to clipboard");
			nSizeX = m_editBillingName.GetSizeX();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}	
		else
		{
			m_editBillingName.ShowWindow(SW_HIDE);
			m_editBillingName.SetText("");
		}
		// company
		strBuffer = ParseXML("BillingCompany",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editCompany.MoveWindow(rectTopField);
			m_editCompany.SetText(strBuffer);
			m_editCompany.ShowWindow(SW_SHOW);
			m_editCompany.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editCompany.SetToolTip("Copy text to clipboard");
			nSizeX = m_editCompany.GetSizeX();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}	
		else
		{
			m_editCompany.ShowWindow(SW_HIDE);
			m_editCompany.SetText("");
		}
		// address line 1
		strBuffer = ParseXML("BillingAddress1",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editAddress1.MoveWindow(rectTopField);
			m_editAddress1.SetText(strBuffer);
			m_editAddress1.ShowWindow(SW_SHOW);
			m_editAddress1.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editAddress1.SetToolTip("Copy text to clipboard");
			nSizeX = m_editAddress1.GetSizeX();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}	
		else
		{
			m_editAddress1.ShowWindow(SW_HIDE);
			m_editAddress1.SetText("");
		}
		// address line 2
		strBuffer = ParseXML("BillingAddress2",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editAddress2.MoveWindow(rectTopField);
			m_editAddress2.SetText(strBuffer);
			m_editAddress2.ShowWindow(SW_SHOW);
			m_editAddress2.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editAddress2.SetToolTip("Copy text to clipboard");
			nSizeX = m_editAddress2.GetSizeX();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}	
		else
		{
			m_editAddress2.ShowWindow(SW_HIDE);
			m_editAddress2.SetText("");
		}
		// city
		strBuffer = ParseXML("BillingCity",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editCity.MoveWindow(rectTopField);
			m_editCity.SetText(strBuffer);
			m_editCity.ShowWindow(SW_SHOW);
			m_editCity.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editCity.SetToolTip("Copy text to clipboard");
			nSizeX = m_editCity.GetSizeX();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}	
		else
		{
			m_editCity.ShowWindow(SW_HIDE);
			m_editCity.SetText("");
		}
		// state
		strBuffer = ParseXML("BillingState",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editState.MoveWindow(rectTopField);
			m_editState.SetText(strBuffer);
			m_editState.ShowWindow(SW_SHOW);
			m_editState.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editState.SetToolTip("Copy text to clipboard");
			nSizeX = m_editState.GetSizeX();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}	
		else
		{
			m_editState.ShowWindow(SW_HIDE);
			m_editState.SetText("");
		}
		// postcode
		strBuffer = ParseXML("BillingPostcode",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editPostcode.MoveWindow(rectTopField);
			m_editPostcode.SetText(strBuffer);
			m_editPostcode.ShowWindow(SW_SHOW);
			m_editPostcode.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editPostcode.SetToolTip("Copy text to clipboard");
			nSizeX = m_editPostcode.GetSizeX();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}	
		else
		{
			m_editPostcode.ShowWindow(SW_HIDE);
			m_editPostcode.SetText("");
		}
		// country
		strBuffer = ParseXML("BillingCountry",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editCountry.MoveWindow(rectTopField);
			m_editCountry.SetText(strBuffer);
			m_editCountry.ShowWindow(SW_SHOW);
			m_editCountry.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editCountry.SetToolTip("Copy text to clipboard");
			nSizeX = m_editCountry.GetSizeX();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}	
		else
		{
			m_editCountry.ShowWindow(SW_HIDE);
			m_editCountry.SetText("");
		}
		// email address
		strBuffer = ParseXML("BillingEmail",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editEmail.MoveWindow(rectTopField);
			m_editEmail.SetText(strBuffer);
			m_editEmail.ShowWindow(SW_SHOW);
			m_editEmail.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editEmail.SetToolTip("Copy text to clipboard");
			nSizeX = m_editEmail.GetSizeX();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}	
		else
		{
			m_editEmail.ShowWindow(SW_HIDE);
			m_editEmail.SetText("");
		}
		// phone number
		strBuffer = ParseXML("BillingPhone",pDoc->m_strData);
		if(!strBuffer.IsEmpty())
		{
			m_editPhone.MoveWindow(rectTopField);
			m_editPhone.SetText(strBuffer);
			m_editPhone.ShowWindow(SW_SHOW);
			m_editPhone.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editPhone.SetToolTip("Copy text to clipboard");
			nSizeX = m_editEmail.GetSizeX();
			if(nSizeX > cx)
				cx = nSizeX;
			rectTopField.InflateRect(0,-30,0,30);
		}
		else
		{
			m_editPhone.ShowWindow(SW_HIDE);
			m_editPhone.SetText("");
		}
		// work out scroll size
		int cy = rectTopField.bottom;
		SetScrollSizes(MM_TEXT,CSize(RIGHT_TEXT_START + cx,cy + pt.y));
	}
	// encrypted file entry
	else if(ParseXML("EncryptedFile",pDoc->m_strData) == "TRUE")
	{
		pMain->ShowToolBar(TOOLBAR_ENCRYPTED_FILE);

		CRect rectTmp;
		CPoint pt = GetScrollPosition();

		CString strText = m_editUsername.GetCompactText(ParseXML("FilePath",pDoc->m_strData));
		m_editUsername.SetText(strText);
		m_editUsername.ShowWindow(SW_SHOW);
		m_editUsername.HideIconButton();
		m_editUsername.SetToolTip("Copy text to clipboard");

		// work out where to place password button after text
		CDC* pDC = NULL;
		CFont* pOld = NULL;
		int nX = 0;
		CRect rectNeeded;
		pDC = m_editPassword.m_Edit.GetDC();
		CFont font;
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));
		lf.lfHeight = -MulDiv(12, GetDeviceCaps(pDC->m_hDC, LOGPIXELSY), 72);  
		lf.lfItalic = true;
		strcpy(lf.lfFaceName, "Times New Roman");
		font.CreateFontIndirect(&lf);  
		pOld = pDC->SelectObject(&font);

		pDC->DrawText(ParseXML("Password",pDoc->m_strData),&rectNeeded,DT_CALCRECT);
		nX = rectNeeded.Width();
		nX += ICON_SPACE_X + 18;
		m_rectPassword = CRect(RIGHT_TEXT_START,80,RIGHT_TEXT_START+nX+10,80+20);
		
		rectTmp = m_rectPassword;
		rectTmp.DeflateRect(-pt.x,-pt.y,pt.x,pt.y);
		m_editPassword.MoveWindow(rectTmp);

		m_editPassword.SetPasswordChar('*');
		m_editPassword.SetText(ParseXML("Password",pDoc->m_strData));
		m_editPassword.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
		m_editPassword.SetToolTip("Copy text to clipboard");
		// move password button
		m_rectButShowPass = CRect(RIGHT_TEXT_START+nX+15,80,RIGHT_TEXT_START+nX+15+20,80+20);
		m_rectButShowPass.DeflateRect(-pt.x,-pt.y,pt.x,pt.y);
		m_butShowPass.MoveWindow(m_rectButShowPass);

		// work out previous password length and button position
		CString strPreviousPass = ParseXML("PasswordOld",pDoc->m_strData);
		BOOL bPrevPass = !strPreviousPass.IsEmpty();
		if(!bPrevPass)
		{
			//strPreviousPass = "No previous password";
			m_editPreviousPassword.SetPasswordChar(0);
		}
		else
		{
			m_editPreviousPassword.SetPasswordChar('*');
		}
		m_editPreviousPassword.SetText(strPreviousPass);
		// calculate rect m_rectPreviousPassword
		pDC->DrawText(strPreviousPass,&rectNeeded,DT_CALCRECT);
		nX = rectNeeded.Width();
		if(bPrevPass)
			nX += ICON_SPACE_X + 18;
		m_rectPreviousPassword = CRect(RIGHT_TEXT_START,110,RIGHT_TEXT_START+nX+10,110+20);
		rectTmp = m_rectPreviousPassword;
		rectTmp.DeflateRect(-pt.x,-pt.y,pt.x,pt.y);
		m_editPreviousPassword.MoveWindow(rectTmp);
		if(bPrevPass)
		{
			m_editPreviousPassword.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editPreviousPassword.SetToolTip("Copy text to clipboard");
		}
		else
		{
			m_editPreviousPassword.ShowWindow(SW_HIDE);
			m_editPreviousPassword.HideIconButton();
		}

		// move previous password button
		m_rectButShowPrevPass = CRect(RIGHT_TEXT_START+nX+15,110,RIGHT_TEXT_START+nX+15+20,110+20);
		m_rectButShowPrevPass.DeflateRect(-pt.x,-pt.y,pt.x,pt.y);
		m_butShowPrevPass.MoveWindow(m_rectButShowPrevPass);

		m_editURL.ShowWindow(SW_HIDE);			
		m_editURL.SetText("");

		// move notes to fit all text
		pDC->DrawText(ParseXML("Notes",pDoc->m_strData),&rectNeeded,DT_CALCRECT);
		nX = RIGHT_TEXT_START + rectNeeded.Width();
		int nY = m_rectURL.top + rectNeeded.Height();
		if(rect.bottom > nY)
			nY = rect.bottom;
		m_rectNotes = CRect(RIGHT_TEXT_START,m_rectURL.top,RIGHT_TEXT_START+nX,nY);
		rectTmp = m_rectNotes;
		rectTmp.DeflateRect(-pt.x,-pt.y,pt.x,pt.y);
		m_editNotes.MoveWindow(rectTmp);

		// work out scroll size
		int cx = m_rectButShowPass.right;
		if(m_rectNotes.right > cx)
			cx = m_rectNotes.right;
		CRect rectTest;
		m_editURL.GetClientRect(rectTest);
		if(rectTest.right > cx)
			cx = rectTest.right;
		int cy = m_rectNotes.bottom;
		
		pDC->SelectObject(pOld);
		m_editPassword.m_Edit.ReleaseDC(pDC);
		SetScrollSizes(MM_TEXT,CSize(cx,cy));

		ShowButtons(true,false);
	}
	// username password entry
	else
	{
		pMain->ShowToolBar(TOOLBAR_USERNAME_PASSWORD);

		CRect rectTmp;
		CPoint pt = GetScrollPosition();

		m_editUsername.SetText(ParseXML("UserID",pDoc->m_strData));
		m_editUsername.ShowWindow(SW_SHOW);
		m_editUsername.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
		m_editUsername.SetToolTip("Copy text to clipboard");

		// work out where to place password button after text
		CDC* pDC = NULL;
		CFont* pOld = NULL;
		int nX = 0;
		CRect rectNeeded;
		pDC = m_editPassword.m_Edit.GetDC();
		CFont font;
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));
		lf.lfHeight = -MulDiv(12, GetDeviceCaps(pDC->m_hDC, LOGPIXELSY), 72);  
		lf.lfItalic = true;
		strcpy(lf.lfFaceName, "Times New Roman");
		font.CreateFontIndirect(&lf);  
		pOld = pDC->SelectObject(&font);

		pDC->DrawText(ParseXML("Password",pDoc->m_strData),&rectNeeded,DT_CALCRECT);
		nX = rectNeeded.Width();
		nX += ICON_SPACE_X + 18;
		m_rectPassword = CRect(RIGHT_TEXT_START,80,RIGHT_TEXT_START+nX+10,80+20);
		
		rectTmp = m_rectPassword;
		rectTmp.DeflateRect(-pt.x,-pt.y,pt.x,pt.y);
		m_editPassword.MoveWindow(rectTmp);

		m_editPassword.SetPasswordChar('*');
		m_editPassword.SetText(ParseXML("Password",pDoc->m_strData));
		m_editPassword.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
		m_editPassword.SetToolTip("Copy text to clipboard");
		// move password button
		m_rectButShowPass = CRect(RIGHT_TEXT_START+nX+15,80,RIGHT_TEXT_START+nX+15+20,80+20);
		m_rectButShowPass.DeflateRect(-pt.x,-pt.y,pt.x,pt.y);
		m_butShowPass.MoveWindow(m_rectButShowPass);

		// work out previous password length and button position
		CString strPreviousPass = ParseXML("PasswordOld",pDoc->m_strData);
		BOOL bPrevPass = !strPreviousPass.IsEmpty();
		if(!bPrevPass)
		{
			//strPreviousPass = "No previous password";
			m_editPreviousPassword.SetPasswordChar(0);
		}
		else
		{
			m_editPreviousPassword.SetPasswordChar('*');
		}
		m_editPreviousPassword.SetText(strPreviousPass);
		// calculate rect m_rectPreviousPassword
		pDC->DrawText(strPreviousPass,&rectNeeded,DT_CALCRECT);
		nX = rectNeeded.Width();
		if(bPrevPass)
			nX += ICON_SPACE_X + 18;
		m_rectPreviousPassword = CRect(RIGHT_TEXT_START,110,RIGHT_TEXT_START+nX+10,110+20);
		rectTmp = m_rectPreviousPassword;
		rectTmp.DeflateRect(-pt.x,-pt.y,pt.x,pt.y);
		m_editPreviousPassword.MoveWindow(rectTmp);
		if(bPrevPass)
		{
			m_editPreviousPassword.ShowButton(IDB_CLIP_DOWN,IDB_CLIP_UP,18,16,1);
			m_editPreviousPassword.SetToolTip("Copy text to clipboard");
		}
		else
		{
			m_editPreviousPassword.ShowWindow(SW_HIDE);
			m_editPreviousPassword.HideIconButton();
		}

		// move previous password button
		m_rectButShowPrevPass = CRect(RIGHT_TEXT_START+nX+15,110,RIGHT_TEXT_START+nX+15+20,110+20);
		m_rectButShowPrevPass.DeflateRect(-pt.x,-pt.y,pt.x,pt.y);
		m_butShowPrevPass.MoveWindow(m_rectButShowPrevPass);

		// set url text	
		CString strURL = ParseXML("URL",pDoc->m_strData);
		if(!strURL.IsEmpty())
		{
			pDC->DrawText(strURL,&rectNeeded,DT_CALCRECT);
			nX = RIGHT_TEXT_START + rectNeeded.Width();
			m_rectURL = CRect(RIGHT_TEXT_START,170,RIGHT_TEXT_START+nX,170+20);
			rectTmp = m_rectURL;
			rectTmp.DeflateRect(-pt.x,-pt.y,pt.x,pt.y);
			m_editURL.MoveWindow(rectTmp);
			m_editURL.SetText(strURL);
			m_editURL.ShowButton(IDB_GLOBE_DOWN, IDB_GLOBE_UP, 16, 16, 2);
			m_editURL.SetToolTip("Load web site");
		}
		else
		{
			m_editURL.ShowWindow(SW_HIDE);			
			m_editURL.SetText("");
			m_editURL.HideIconButton();
		}		

		// move notes to fit all text
		pDC->DrawText(ParseXML("Notes",pDoc->m_strData),&rectNeeded,DT_CALCRECT);
		nX = RIGHT_TEXT_START + rectNeeded.Width();
		int nY = 200 + rectNeeded.Height();
		if(rect.bottom > nY)
			nY = rect.bottom;
		m_rectNotes = CRect(RIGHT_TEXT_START,200,RIGHT_TEXT_START+nX,nY);
		rectTmp = m_rectNotes;
		rectTmp.DeflateRect(-pt.x,-pt.y,pt.x,pt.y);
		m_editNotes.MoveWindow(rectTmp);

		// work out scroll size
		int cx = m_rectButShowPass.right;
		if(m_rectNotes.right > cx)
			cx = m_rectNotes.right;
		CRect rectTest;
		m_editURL.GetClientRect(rectTest);
		if(rectTest.right > cx)
			cx = rectTest.right;
		int cy = m_rectNotes.bottom;
		
		pDC->SelectObject(pOld);
		m_editPassword.m_Edit.ReleaseDC(pDC);
		SetScrollSizes(MM_TEXT,CSize(cx,cy));

		ShowButtons(true,false);
	}
	
	CScrollView::OnUpdate(pSender, lHint, pHint);
}

// CFOXPasswordSafeView printing
BOOL CFOXPasswordSafeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	m_CustomPrint.OnPreparePrinting(pInfo);
	return DoPreparePrinting(pInfo);
}

void CFOXPasswordSafeView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	m_CustomPrint.OnBeginPrinting(pDC, pInfo);
}

void CFOXPasswordSafeView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	m_CustomPrint.OnEndPrinting(pDC, pInfo);
}

void CFOXPasswordSafeView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	m_CustomPrint.OnPrint(pDC, pInfo);
}

void CFOXPasswordSafeView::OnMyFilePrint()
{
	CPrintSelectDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
		// clear entries from array
		m_CustomPrint.ClearArray();

		m_CustomPrint.m_pCtrlWnd = this;
		m_CustomPrint.m_PrintDatabasePassword = dlg.m_PrintDatabasePassword;
		m_CustomPrint.m_bCategory = dlg.m_bCategory;
		m_CustomPrint.m_bDescription = dlg.m_bDescription;
		m_CustomPrint.m_bPrintUserID = dlg.m_bUsername;
		m_CustomPrint.m_bPrintPass = dlg.m_bPassword;
		m_CustomPrint.m_bPrintURL = dlg.m_bWebSite;
		m_CustomPrint.m_bPrintNotes = false;

		// load array with entries selected
		if(dlg.m_bPrintSingleItem == 0) // 0 = selected
		{
			if(!pMain->GetSingleSelectedItemData((LPVOID)&m_CustomPrint))
				return;
		}
		else if(dlg.m_bPrintAll == 0)
		{
			if(!pMain->GetAllItemData((LPVOID)&m_CustomPrint))
				return;
		}
		else if(!pMain->GetSelectedItemData((LPVOID)&m_CustomPrint))
		{
			return;
		}		// work out largest text size
		m_CustomPrint.SetLargestColumnSize();
		
		CScrollView::OnFilePrint();
	}	
}

void CFOXPasswordSafeView::OnMyFilePrintPreview()
{
	CPrintSelectDlg dlg;
	if(dlg.DoModal() == IDOK)
	{		
		CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
		// clear entries from array
		m_CustomPrint.ClearArray();

		m_CustomPrint.m_pCtrlWnd = this;
		m_CustomPrint.m_PrintDatabasePassword = dlg.m_PrintDatabasePassword;
		m_CustomPrint.m_bCategory = dlg.m_bCategory;
		m_CustomPrint.m_bDescription = dlg.m_bDescription;
		m_CustomPrint.m_bPrintUserID = dlg.m_bUsername;
		m_CustomPrint.m_bPrintPass = dlg.m_bPassword;
		m_CustomPrint.m_bPrintURL = dlg.m_bWebSite;
		m_CustomPrint.m_bPrintNotes = false;

		// load array with entries selected
		if(dlg.m_bPrintSingleItem == 0) // 0 = selected
		{
			if(!pMain->GetSingleSelectedItemData((LPVOID)&m_CustomPrint))
				return;
		}
		else if(dlg.m_bPrintAll == 0)
		{
			if(!pMain->GetAllItemData((LPVOID)&m_CustomPrint))
				return;
		}
		else if(!pMain->GetSelectedItemData((LPVOID)&m_CustomPrint))
		{
			return;
		}
		// work out largest text size
		m_CustomPrint.SetLargestColumnSize();

		CScrollView::OnFilePrintPreview();
	}
}

void CFOXPasswordSafeView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CScrollView::OnRButtonDown(nFlags, point);

	ClientToScreen(&point);
	CMenu menu;
	BOOL bOK = menu.CreatePopupMenu();
	bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_COPY, "Copy Username to Clipboard");
	bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_COPYPASSWORDTOCLIPBOARD, "Copy Password to Clipboard");
	bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_EMPTYPASSWORDFROMCLIPBOARD, "Empty Password from Clipboard");
	bOK = menu.AppendMenu(MF_SEPARATOR, NULL, "");
	bOK = menu.AppendMenu(MF_POPUP, ID_FILE_ADDNEWCATEGORY, "Create New Category");
	bOK = menu.AppendMenu(MF_POPUP, ID_FILE_ADDNEWENTRY, "Create New Entry");
	bOK = menu.AppendMenu(MF_SEPARATOR, NULL, "");
	bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_EDITSELECTEDCATEGORY, "Edit Selected Category");
	bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_EDITSELECTEDENTRY, "Edit Selected Entry");
	bOK = menu.AppendMenu(MF_POPUP, ID_EDIT_DELETESELECTEDCATEGORY, "Delete Selected Item");

	::TrackPopupMenu(menu.m_hMenu,TPM_CENTERALIGN|TPM_RIGHTBUTTON, point.x, point.y,NULL,AfxGetMainWnd()->m_hWnd,NULL);
}

// return currently selected XML data
BOOL CFOXPasswordSafeView::GetSelectedUserData(CString& strData)
{
	CFOXPasswordSafeDoc* pDoc = GetDocument();
	if(pDoc->m_strData.IsEmpty() || pDoc->m_bIsHeader)
		return false;
	strData = pDoc->m_strData;
	return true;	
}
