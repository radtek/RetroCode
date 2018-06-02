// SteveMediaCenterOcxPpg.cpp : Implementation of the CSteveMediaCenterOcxPropPage property page class.

#include "stdafx.h"
#include "SteveMediaCenterOcx.h"
#include "SteveMediaCenterOcxPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSteveMediaCenterOcxPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CSteveMediaCenterOcxPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CSteveMediaCenterOcxPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSteveMediaCenterOcxPropPage, "STEVEMEDIACENTEROCX.SteveMediaCenterOcxPropPage.1",
	0xd03ded31, 0x135a, 0x4f3c, 0x92, 0x73, 0xf0, 0x4b, 0x9d, 0xb0, 0x88, 0x20)


/////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterOcxPropPage::CSteveMediaCenterOcxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CSteveMediaCenterOcxPropPage

BOOL CSteveMediaCenterOcxPropPage::CSteveMediaCenterOcxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_STEVEMEDIACENTEROCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterOcxPropPage::CSteveMediaCenterOcxPropPage - Constructor

CSteveMediaCenterOcxPropPage::CSteveMediaCenterOcxPropPage() :
	COlePropertyPage(IDD, IDS_STEVEMEDIACENTEROCX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CSteveMediaCenterOcxPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterOcxPropPage::DoDataExchange - Moves data between page and properties

void CSteveMediaCenterOcxPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CSteveMediaCenterOcxPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterOcxPropPage message handlers
