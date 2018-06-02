// SteveMediaPlayerPpg.cpp : Implementation of the CSteveMediaPlayerPropPage property page class.

#include "stdafx.h"
#include "SteveMediaPlayer.h"
#include "SteveMediaPlayerPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSteveMediaPlayerPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CSteveMediaPlayerPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CSteveMediaPlayerPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSteveMediaPlayerPropPage, "STEVEMEDIAPLAYER.SteveMediaPlayerPropPage.1",
	0xf9d07cff, 0x5603, 0x46d0, 0x80, 0x3d, 0, 0x40, 0x7a, 0x6c, 0xdb, 0xff)


/////////////////////////////////////////////////////////////////////////////
// CSteveMediaPlayerPropPage::CSteveMediaPlayerPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CSteveMediaPlayerPropPage

BOOL CSteveMediaPlayerPropPage::CSteveMediaPlayerPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_STEVEMEDIAPLAYER_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CSteveMediaPlayerPropPage::CSteveMediaPlayerPropPage - Constructor

CSteveMediaPlayerPropPage::CSteveMediaPlayerPropPage() :
	COlePropertyPage(IDD, IDS_STEVEMEDIAPLAYER_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CSteveMediaPlayerPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CSteveMediaPlayerPropPage::DoDataExchange - Moves data between page and properties

void CSteveMediaPlayerPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CSteveMediaPlayerPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CSteveMediaPlayerPropPage message handlers
