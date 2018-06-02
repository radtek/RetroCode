// AskCloseOrHideDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "AskCloseOrHideDlg.h"
#include ".\askcloseorhidedlg.h"
#include "helpers.h"

// CAskCloseOrHideDlg dialog

IMPLEMENT_DYNAMIC(CAskCloseOrHideDlg, CDialog)
CAskCloseOrHideDlg::CAskCloseOrHideDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAskCloseOrHideDlg::IDD, pParent)
	, m_bDoNotShowAgain(FALSE)
	, m_bHide(FALSE)
{
}

CAskCloseOrHideDlg::~CAskCloseOrHideDlg()
{
}

void CAskCloseOrHideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_bDoNotShowAgain);
	DDX_Radio(pDX, IDC_RADIO_HIDE_APP, m_bHide);
}

BEGIN_MESSAGE_MAP(CAskCloseOrHideDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

void CAskCloseOrHideDlg::OnBnClickedOk()
{
	UpdateData(true);
	
	if(m_bDoNotShowAgain)
		MyWriteProfileInt("AskCloseOrHide",0);
	
	if(m_bHide == 0)
		MyWriteProfileInt("MinimizeOnClose",1);
	else
		MyWriteProfileInt("MinimizeOnClose",0);

	OnOK();
}




