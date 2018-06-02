// SelectPrintItemsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOX Password Safe.h"
#include "SelectPrintItemsDlg.h"
#include ".\selectprintitemsdlg.h"
#include "helpers.h"

// CSelectPrintItemsDlg dialog
IMPLEMENT_DYNAMIC(CSelectPrintItemsDlg, CDialog)
CSelectPrintItemsDlg::CSelectPrintItemsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectPrintItemsDlg::IDD, pParent)
	, m_pstraItems(NULL)
{
}

CSelectPrintItemsDlg::~CSelectPrintItemsDlg()
{
}

void CSelectPrintItemsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SELECT, m_crlList);
}

BEGIN_MESSAGE_MAP(CSelectPrintItemsDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

// CSelectPrintItemsDlg message handlers
BOOL CSelectPrintItemsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	BOOL bOK = m_ImageList.Create(IDB_IMAGELIST2,16,1,RGB(0,128,128));
	m_crlList.SetImageList(&m_ImageList,TVSIL_NORMAL); 

	CRect rect;
	GetClientRect(rect);
	m_crlList.InsertColumn(0,"Category",LVCFMT_LEFT,rect.Width()/2);
	m_crlList.InsertColumn(1,"Description",LVCFMT_LEFT,rect.Width()/2);

	// load main list headers
	if(m_pstraItems)
	{
		for(int n=0;n<m_pstraItems->GetSize();n++)
		{
			CString strHeader = ParseXML("Header",m_pstraItems->GetAt(n));
			CString strDescription = ParseXML("Description",m_pstraItems->GetAt(n));	
			// add item to list
			if(!strDescription.IsEmpty() && ParseXML("CreditCard",m_pstraItems->GetAt(n)) != "TRUE")
			{
				int nPos = m_crlList.InsertItem(LVIF_IMAGE|LVIF_PARAM|LVIF_TEXT|LVIF_STATE,m_crlList.GetItemCount()
					,strHeader,0,0,10,n);
				if(nPos != -1)
					m_crlList.SetItemText(nPos,1,strDescription);
  			}
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CSelectPrintItemsDlg::OnBnClickedOk()
{
	CStringArray straTemp;
	for(int n=0;n<m_crlList.GetItemCount();n++)
	{
		if(m_crlList.GetItemState(n,LVIS_SELECTED) & LVIS_SELECTED)
		{
			int nPos = (int)m_crlList.GetItemData(n);
			if(nPos > -1 && nPos < m_pstraItems->GetCount())
				straTemp.Add(m_pstraItems->GetAt(nPos));
		}
	}
	m_pstraItems->RemoveAll();
	m_pstraItems->Copy(straTemp);
	OnOK();
}

