// SteveMediaCenterOcxCtl.cpp : Implementation of the CSteveMediaCenterOcxCtrl ActiveX Control class.

#include "stdafx.h"
#include "SteveMediaCenterOcx.h"
#include "SteveMediaCenterOcxCtl.h"
#include "SteveMediaCenterOcxPpg.h"
#include "helpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSteveMediaCenterOcxCtrl, COleControl)

BEGIN_INTERFACE_MAP(CSteveMediaCenterOcxCtrl, COleControl)
  INTERFACE_PART(CSteveMediaCenterOcxCtrl, IID_IObjectSafety, ObjectSafety)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CSteveMediaCenterOcxCtrl, COleControl)
	//{{AFX_MSG_MAP(CSteveMediaCenterOcxCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_COPYDATA()
	ON_COMMAND(ID_FILE_SETTINGS, OnFileSettings)
	ON_COMMAND(ID_FILE_ACTIVETIMEDSHUTDOWN, OnFileActivetimedshutdown)
	ON_COMMAND(ID_FILE_SELECTSKIN, OnFileSelectskin)
	ON_COMMAND(ID_FILE_SELECTPLAYLIST, OnFileSelectplaylist)
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_MESSAGE(WM_PLAY_ALL,OnPlayAll)
	ON_MESSAGE(WM_PLAY_ALL_FROM_SELECTED,OnPlayAllFromSelected)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CSteveMediaCenterOcxCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CSteveMediaCenterOcxCtrl)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "MediaTitle", m_mediaTitle, OnMediaTitleChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "MediaLength", m_mediaLength, OnMediaLengthChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "MediaArtist", m_mediaArtist, OnMediaArtistChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "MediaBitrate", m_mediaBitrate, OnMediaBitrateChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "CurrentMediaPosition", m_currentMediaPosition, OnCurrentMediaPositionChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "hexBackGroundColor", m_hexBackGroundColor, OnHexBackGroundColorChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "hexTextColor", m_hexTextColor, OnHexTextColorChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "jpgBKImageFilePath", m_strJpgBKImageFilePath, OnJpgBKImageFilePathChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "jpgBKOriginXPoint", m_jpgBKOriginXPoint, OnJpgBKOriginXPointChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "jpgBKOriginYPoint", m_jpgBKOriginYPoint, OnJpgBKOriginYPointChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "hexSelectTextColor", m_hexSelectTextColor, OnHexSelectTextColorChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "hexSelectedBKColor", m_hexSelectedBKColor, OnHexSelectedBKColorChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "nAlignText012", m_nAlignText012, OnNAlignText012Changed, VT_I2)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "ScollingTextMsg", m_strScollingTextMsg, OnScollingTextMsgChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "VolumeLeftOffset", m_volumeLeftOffset, OnVolumeLeftOffsetChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CSteveMediaCenterOcxCtrl, "VolumeRightOffset", m_volumeRightOffset, OnVolumeRightOffsetChanged, VT_I2)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "PlaySelected", PlaySelected, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "Play", Play, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "Pause", Pause, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "Stop", Stop, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "ClearPlayList", ClearPlayList, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "Mute", Mute, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "LowerVolume", LowerVolume, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "IncreaseVolume", IncreaseVolume, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "AddToPlayList", AddToPlayList, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "ShowOpenFileDialog", ShowOpenFileDialog, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "ShowManagePlayList", ShowManagePlayList, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "Previous", Previous, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "Next", Next, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "ShowSelectSkin", ShowSelectSkin, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "Rewind", Rewind, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "Forward", Forward, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "ShowPopUpMenu", ShowPopUpMenu, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "ShowVolumeControl", ShowVolumeControl, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "ShowSeekControl", ShowSeekControl, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "IsPlayListEmpty", IsPlayListEmpty, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CSteveMediaCenterOcxCtrl, "SkinUpdate", SkinUpdate, VT_EMPTY, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CSteveMediaCenterOcxCtrl, COleControl)
	//{{AFX_EVENT_MAP(CSteveMediaCenterOcxCtrl)
	EVENT_CUSTOM("ChangeCurrentMediaInfo", FireChangeCurrentMediaInfo, VTS_NONE)
	EVENT_CUSTOM("UpdatePlayPosition", FireUpdatePlayPosition, VTS_NONE)
	EVENT_CUSTOM("UpdateScrollingText", FireUpdateScrollingText, VTS_NONE)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CSteveMediaCenterOcxCtrl, 1)
	PROPPAGEID(CSteveMediaCenterOcxPropPage::guid)
END_PROPPAGEIDS(CSteveMediaCenterOcxCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSteveMediaCenterOcxCtrl, "STEVEMEDIACENTEROCX.SteveMediaCenterOcxCtrl.1",
	0x9da8a279, 0xecd6, 0x4125, 0xa2, 0x53, 0x42, 0x2f, 0x9b, 0x1c, 0xbb, 0x1a)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CSteveMediaCenterOcxCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DSteveMediaCenterOcx =
		{ 0xdc9a4388, 0xf0a2, 0x443e, { 0xb2, 0x9b, 0xa6, 0x6a, 0x12, 0x3a, 0x2d, 0xd1 } };
const IID BASED_CODE IID_DSteveMediaCenterOcxEvents =
		{ 0xe79c0265, 0xb2cf, 0x456f, { 0xb7, 0x8f, 0x6a, 0x7e, 0x3c, 0x7e, 0x66, 0x6 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwSteveMediaCenterOcxOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CSteveMediaCenterOcxCtrl, IDS_STEVEMEDIACENTEROCX, _dwSteveMediaCenterOcxOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterOcxCtrl::CSteveMediaCenterOcxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CSteveMediaCenterOcxCtrl

BOOL CSteveMediaCenterOcxCtrl::CSteveMediaCenterOcxCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegInsertable | afxRegApartmentThreading to afxRegInsertable.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_STEVEMEDIACENTEROCX,
			IDB_STEVEMEDIACENTEROCX,
			afxRegInsertable | afxRegApartmentThreading,
			_dwSteveMediaCenterOcxOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

// Implementation of IObjectSafety
STDMETHODIMP CSteveMediaCenterOcxCtrl::XObjectSafety::GetInterfaceSafetyOptions(
			REFIID riid, 
			DWORD __RPC_FAR *pdwSupportedOptions, 
			DWORD __RPC_FAR *pdwEnabledOptions)
{
	METHOD_PROLOGUE_EX(CSteveMediaCenterOcxCtrl, ObjectSafety)

	if (!pdwSupportedOptions || !pdwEnabledOptions)
	{
		return E_POINTER;
	}

	*pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
	*pdwEnabledOptions = 0;

	if (NULL == pThis->GetInterface(&riid))
	{
		TRACE("Requested interface is not supported.\n");
		return E_NOINTERFACE;
	}

	// What interface is being checked out anyhow?
	OLECHAR szGUID[39];
	int i = StringFromGUID2(riid, szGUID, 39);

	if (riid == IID_IDispatch)
	{
		// Client wants to know if object is safe for scripting
		*pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER;
		return S_OK;
	}
	else if (riid == IID_IPersistPropertyBag 
		  || riid == IID_IPersistStreamInit
		  || riid == IID_IPersistStorage
		  || riid == IID_IPersistMemory)
	{
		// Those are the persistence interfaces COleControl derived controls support
		// as indicated in AFXCTL.H
		// Client wants to know if object is safe for initializing from persistent data
		*pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA;
		return S_OK;
	}
	else
	{
		// Find out what interface this is, and decide what options to enable
		TRACE("We didn't account for the safety of this interface, and it's one we support...\n");
		return E_NOINTERFACE;
	}	
}

STDMETHODIMP CSteveMediaCenterOcxCtrl::XObjectSafety::SetInterfaceSafetyOptions(
		REFIID riid, 
		DWORD dwOptionSetMask, 
		DWORD dwEnabledOptions)
{
	METHOD_PROLOGUE_EX(CSteveMediaCenterOcxCtrl, ObjectSafety)

	OLECHAR szGUID[39];
	// What is this interface anyway?
	// We can do a quick lookup in the registry under HKEY_CLASSES_ROOT\Interface
	int i = StringFromGUID2(riid, szGUID, 39);

	if (0 == dwOptionSetMask && 0 == dwEnabledOptions)
	{
		// the control certainly supports NO requests through the specified interface
		// so it's safe to return S_OK even if the interface isn't supported.
		return S_OK;
	}

	// Do we support the specified interface?
	if (NULL == pThis->GetInterface(&riid))
	{
		TRACE1("%s is not support.\n", szGUID);
		return E_FAIL;
	}


	if (riid == IID_IDispatch)
	{
		TRACE("Client asking if it's safe to call through IDispatch.\n");
		TRACE("In other words, is the control safe for scripting?\n");
		if (INTERFACESAFE_FOR_UNTRUSTED_CALLER == dwOptionSetMask && INTERFACESAFE_FOR_UNTRUSTED_CALLER == dwEnabledOptions)
		{
			return S_OK;
		}
		else
		{
			return E_FAIL;
		}
	}
	else if (riid == IID_IPersistPropertyBag 
		  || riid == IID_IPersistStreamInit
		  || riid == IID_IPersistStorage
		  || riid == IID_IPersistMemory)
	{
		TRACE("Client asking if it's safe to call through IPersist*.\n");
		TRACE("In other words, is the control safe for initializing from persistent data?\n");

		if (INTERFACESAFE_FOR_UNTRUSTED_DATA == dwOptionSetMask && INTERFACESAFE_FOR_UNTRUSTED_DATA == dwEnabledOptions)
		{
			return NOERROR;
		}
		else
		{
			return E_FAIL;
		}
	}
	else
	{
		TRACE1("We didn't account for the safety of %s, and it's one we support...\n", szGUID);
		return E_FAIL;
	}
}

STDMETHODIMP_(ULONG) CSteveMediaCenterOcxCtrl::XObjectSafety::AddRef()
{
	METHOD_PROLOGUE_EX_(CSteveMediaCenterOcxCtrl, ObjectSafety)
	return (ULONG)pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CSteveMediaCenterOcxCtrl::XObjectSafety::Release()
{
	METHOD_PROLOGUE_EX_(CSteveMediaCenterOcxCtrl, ObjectSafety)
	return (ULONG)pThis->ExternalRelease();
}

STDMETHODIMP CSteveMediaCenterOcxCtrl::XObjectSafety::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(CSteveMediaCenterOcxCtrl, ObjectSafety)
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}
/////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterOcxCtrl::CSteveMediaCenterOcxCtrl - Constructor

CSteveMediaCenterOcxCtrl::CSteveMediaCenterOcxCtrl()
{
	InitializeIIDs(&IID_DSteveMediaCenterOcx, &IID_DSteveMediaCenterOcxEvents);

	m_volumeLeftOffset = 0;
	m_volumeRightOffset = 0;
	m_SeekWnd.m_pMain = this;
}

CSteveMediaCenterOcxCtrl::~CSteveMediaCenterOcxCtrl()
{
}

void CSteveMediaCenterOcxCtrl::OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	CRect rect;
	GetClientRect(rect);
	CBrush br;
	br.CreateSolidBrush(0x000000);
	pdc->FillRect(rect,&br);
}

/////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterOcxCtrl::DoPropExchange - Persistence support

void CSteveMediaCenterOcxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
}

void CSteveMediaCenterOcxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}

int CSteveMediaCenterOcxCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(rect);

	BOOL bOK = m_ctlPlayList.Create(WS_HSCROLL|WS_CHILD|WS_VISIBLE|LVS_REPORT|
		LVS_NOCOLUMNHEADER|LVS_SHOWSELALWAYS|LVS_OWNERDRAWFIXED|LVS_SINGLESEL,
		rect,this,ID_PLAYLIST_CONTROL);
	if(!bOK)
	{
		AfxMessageBox("Error creating list control");
		return 1;
	}
	m_ctlPlayList.DragAcceptFiles(true);

	CWnd* pWnd = GetDesktopWindow();	
	m_msgWnd.m_pParent = this;
	BOOL bOk = m_msgWnd.CreateEx(0,0,"PlayListUpdateWnd",
				WS_BORDER, CRect(1,1,1,1),pWnd,0);

	// volume wnd
	rect.top = rect.bottom - 30;
	m_VolWnd.Create(NULL,"VolumeWnd",WS_CHILD,rect,this,4102);
	m_SeekWnd.Create(NULL,"SeekWnd",WS_CHILD,rect,this,4103);

	SendMessageToInstanseOfApp("<Message>SendCurrentPlayList</Message>");

	return 0;
}

void CSteveMediaCenterOcxCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
	if(IsWindow(m_ctlPlayList.m_hWnd))
	{
		m_ctlPlayList.MoveWindow(0,0,cx,cy);
	}
}

BOOL CSteveMediaCenterOcxCtrl::PlaySelected() 
{
	CString strSendData = m_ctlPlayList.GetPlaySelectedList();
	return SendMessageToInstanseOfApp(strSendData);
}

BOOL CSteveMediaCenterOcxCtrl::Play() 
{
	DWORD nHotItem = m_ctlPlayList.GetSelectedItem();
	for(int n=0;n<m_ctlPlayList.GetItemCount();n++)
		m_ctlPlayList.SetNormalIcon(n);

	CString strSendData;
	strSendData.Format("<Message>PlayAllFromSelected</Message><HotItem>%u</HotItem>",nHotItem);
	return SendMessageToInstanseOfApp(strSendData);
}

BOOL CSteveMediaCenterOcxCtrl::Pause() 
{
	CString strSendData = "<Message>Pause</Message>";
	return SendMessageToInstanseOfApp(strSendData);
}

BOOL CSteveMediaCenterOcxCtrl::Stop() 
{
	CString strSendData = "<Message>Stop</Message>";
	return SendMessageToInstanseOfApp(strSendData);
}

void CSteveMediaCenterOcxCtrl::OnMediaTitleChanged() 
{

	SetModifiedFlag();
}

void CSteveMediaCenterOcxCtrl::OnMediaLengthChanged() 
{

	SetModifiedFlag();
}

void CSteveMediaCenterOcxCtrl::OnMediaArtistChanged() 
{
	SetModifiedFlag();
}

void CSteveMediaCenterOcxCtrl::OnMediaBitrateChanged() 
{
	SetModifiedFlag();
}

void CSteveMediaCenterOcxCtrl::OnCurrentMediaPositionChanged() 
{
	SetModifiedFlag();
}

void CSteveMediaCenterOcxCtrl::ClearPlayList() 
{
	if(IsWindow(m_ctlPlayList.m_hWnd))
	{
		m_ctlPlayList.ClearPlayList();
	}
}

void CSteveMediaCenterOcxCtrl::Mute() 
{
	CString strSendData = "<Message>Mute</Message>";
	SendMessageToInstanseOfApp(strSendData);
}

void CSteveMediaCenterOcxCtrl::LowerVolume() 
{
	CString strSendData = "<Message>LowerVolume</Message>";
	SendMessageToInstanseOfApp(strSendData);
}

void CSteveMediaCenterOcxCtrl::IncreaseVolume() 
{
	CString strSendData = "<Message>IncreaseVolume</Message>";
	SendMessageToInstanseOfApp(strSendData);
}

long CSteveMediaCenterOcxCtrl::OnPlayAll(WPARAM wParam,LPARAM lParam)
{
	return Play();	
}

long CSteveMediaCenterOcxCtrl::OnPlayAllFromSelected(WPARAM wParam,LPARAM lParam)
{
	m_currentMediaPosition = "";
	FireUpdatePlayPosition();	

	DWORD nHotItem = m_ctlPlayList.GetSelectedItem();
	CString strSendData;
	strSendData.Format("<Message>PlayAllFromSelected</Message><HotItem>%u</HotItem>",nHotItem);
	return SendMessageToInstanseOfApp(strSendData);
}

void CSteveMediaCenterOcxCtrl::AddToPlayList(LPCTSTR strFilePath) 
{
	if(IsWindow(m_ctlPlayList.m_hWnd))
	{
		m_ctlPlayList.AddNewFile(strFilePath);
	}
}

void CSteveMediaCenterOcxCtrl::ShowOpenFileDialog() 
{
	CString strLastFolder = AfxGetApp()->GetProfileString("Settings","LastFileOpenPath",NULL);
	CString strExt;
	if(strLastFolder.Find('\\') != -1)
	{
		strExt = strLastFolder.Mid(strLastFolder.ReverseFind('\\')+1);
		strLastFolder = strLastFolder.Mid(strLastFolder.ReverseFind('\\')+1);
	}

	LPCTSTR lpszFilter = _T("MP3 (*.mp3)|*.mp3|ogg files (*.ogg)|*.ogg|Mpeg (*.mpg)|*.mpg;*.mpeg|Divx AVI (*.avi)|*.avi|Windows Media (*.wm*)|*.wm*|All Files (*.*)|*.*||");
	CFileDialog dlg(true,strExt,strLastFolder,0,lpszFilter);
	if(dlg.DoModal() == IDOK)
	{
		strLastFolder = dlg.GetPathName();
		AddToPlayList(strLastFolder);
		strLastFolder = strLastFolder.Left(strLastFolder.ReverseFind('\\')+1);
		strLastFolder += "*." + dlg.GetFileExt();
		AfxGetApp()->WriteProfileString("Settings","LastFileOpenPath",strLastFolder);
	}
}

void CSteveMediaCenterOcxCtrl::Previous() 
{
	CString strSendData = "<Message>Previous</Message>";
	SendMessageToInstanseOfApp(strSendData);
}

void CSteveMediaCenterOcxCtrl::Next() 
{
	CString strSendData = "<Message>Next</Message>";
	SendMessageToInstanseOfApp(strSendData);
}

void CSteveMediaCenterOcxCtrl::OnJpgBKImageFilePathChanged() 
{
	SECFileSystem fp;
	CString strPath;

	m_strJpgBKImageFilePath.Replace('/','\\');
	
	if(!fp.FileExists(m_strJpgBKImageFilePath))
	{
		strPath = AfxGetApp()->GetProfileString("Settings","InstallPath",DEFAULT_INSTALL_PATH);
		CString strSkin = AfxGetApp()->GetProfileString("Settings","CurrentSkin",DEFAULT_SKIN);	
		if(strPath.Right(1) != '\\')
			strPath += "\\";
		strPath += "Skins\\" + strSkin;
		if(m_strJpgBKImageFilePath.Left(1) != '\\')
			strPath += "\\";
		strPath += m_strJpgBKImageFilePath;
	}
	else
		strPath = m_strJpgBKImageFilePath;
	
	if(fp.FileExists(strPath))
	{
		m_ctlPlayList.m_strImageBK = strPath;
		m_ctlPlayList.LoadImage();
	}
	SetModifiedFlag();
}

void CSteveMediaCenterOcxCtrl::OnJpgBKOriginXPointChanged() 
{
	m_ctlPlayList.m_nJpgBKOriginX = m_jpgBKOriginXPoint;

	SetModifiedFlag();
}

void CSteveMediaCenterOcxCtrl::OnJpgBKOriginYPointChanged() 
{
	m_ctlPlayList.m_nJpgBKOriginY = m_jpgBKOriginYPoint;

	SetModifiedFlag();
}

// list box colors
void CSteveMediaCenterOcxCtrl::OnHexBackGroundColorChanged() 
{
	DWORD dwVal = strtoul(m_hexBackGroundColor,NULL,16);
	int nB = GetBValue(dwVal);
	int nG = GetGValue(dwVal);
	int nR = GetRValue(dwVal);
	m_ctlPlayList.m_dwBKColor = RGB(nB,nG,nR);

	SetModifiedFlag();
}

void CSteveMediaCenterOcxCtrl::OnHexTextColorChanged() 
{
	DWORD dwVal = strtoul(m_hexTextColor,NULL,16);
	int nB = GetBValue(dwVal);
	int nG = GetGValue(dwVal);
	int nR = GetRValue(dwVal);
	m_ctlPlayList.m_dwTextColor = RGB(nB,nG,nR);

	SetModifiedFlag();
}

void CSteveMediaCenterOcxCtrl::OnHexSelectTextColorChanged() 
{
	DWORD dwVal = strtoul(m_hexSelectTextColor,NULL,16);
	int nB = GetBValue(dwVal);
	int nG = GetGValue(dwVal);
	int nR = GetRValue(dwVal);
	m_ctlPlayList.m_dwSelectTextColor = RGB(nB,nG,nR);
	
	SetModifiedFlag();
}

void CSteveMediaCenterOcxCtrl::OnHexSelectedBKColorChanged() 
{
	if(!m_hexSelectedBKColor.IsEmpty())
	{
		m_ctlPlayList.m_bDrawBKSelected = true;
		DWORD dwVal = strtoul(m_hexSelectedBKColor,NULL,16);
		int nB = GetBValue(dwVal);
		int nG = GetGValue(dwVal);
		int nR = GetRValue(dwVal);
		m_ctlPlayList.m_dwSelectBKColor = RGB(nB,nG,nR);
	}
	SetModifiedFlag();
}

void CSteveMediaCenterOcxCtrl::OnNAlignText012Changed() 
{
	if(m_nAlignText012 >=0 && m_nAlignText012 < 3)
		m_ctlPlayList.m_nAlignText = m_nAlignText012;
	SetModifiedFlag();
}

void CSteveMediaCenterOcxCtrl::ShowSelectSkin() 
{
	SendMessageToInstanseOfApp("<Message>ShowSelectSkin</Message>");
}

void CSteveMediaCenterOcxCtrl::ShowManagePlayList() 
{
	SendMessageToInstanseOfApp("<Message>ShowManagePlayList</Message>");	
}

void CSteveMediaCenterOcxCtrl::Rewind() 
{
	SendMessageToInstanseOfApp("<Message>Rewind</Message>");	
}

void CSteveMediaCenterOcxCtrl::Forward() 
{
	SendMessageToInstanseOfApp("<Message>Forward</Message>");
}

void CSteveMediaCenterOcxCtrl::OnScollingTextMsgChanged() 
{
	SetModifiedFlag();
}

BOOL CSteveMediaCenterOcxCtrl::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	CString strParams;
	int nSize = pCopyDataStruct->cbData;
	memcpy(strParams.GetBuffer(nSize),pCopyDataStruct->lpData,nSize);
	strParams.ReleaseBuffer();
	
	// drop message to add new media file
	if(ParseXML("Message",strParams) == "CurrentFileListXML")
	{
		ClearPlayList();

		CStringArray stra;
		while(strParams.Find("</PlayListEntry>") != -1)
		{
			stra.Add(ParseXML("PlayListEntry",strParams));
			strParams = strParams.Mid(strParams.Find("</PlayListEntry>")+strlen("</PlayListEntry>"));
		}
		for(int n=0;n<stra.GetSize();n++)
		{
			m_ctlPlayList.AddNewFile(ParseXML("FullPath",stra.GetAt(n)),false);
		}
		if(stra.GetSize() > 0)
		{
			m_strScollingTextMsg = "";
			FireUpdateScrollingText();
		}
		InvalidateRect(NULL);
	}
	else if(ParseXML("Message",strParams) == "ClearAll")
	{
		m_ctlPlayList.ClearPlayList();
	}
	else if(ParseXML("Message",strParams) == "SetNormalIcon")
	{
		long lPos = atol(ParseXML("POS",strParams));
		if(lPos == -1)
			m_ctlPlayList.SetNormalIconAll();
		else
			m_ctlPlayList.SetNormalIcon(lPos);
	}
	else if(ParseXML("Message",strParams) == "SetPlayingIcon")
	{
		DWORD dwPos = atol(ParseXML("POS",strParams));
		BOOL bSelect = (ParseXML("Select",strParams) == "TRUE");

		m_ctlPlayList.SetPlayingIcon(dwPos,bSelect);
		if(bSelect)
		{
			m_ctlPlayList.SetItemState(dwPos,LVIS_SELECTED,LVIS_SELECTED);
			m_ctlPlayList.EnsureVisible(dwPos,false);
		}
		m_strScollingTextMsg = "";
		FireUpdateScrollingText();
	}
	else if(ParseXML("Message",strParams) == "UpdatePlayPosition")
	{
		m_currentMediaPosition = ParseXML("CurrentMediaPosition",strParams);
		DWORD dwPos = atol(ParseXML("CurrentMediaPosSecs",strParams));
		m_SeekWnd.UpdatePosition(dwPos);

		FireUpdatePlayPosition();	
	}
	else if(ParseXML("Message",strParams) == "CurrentMediaInfo")
	{
		m_mediaTitle = ParseXML("MediaTitle",strParams);
		m_mediaLength = ParseXML("MediaLength",strParams);
		m_mediaArtist = ParseXML("MediaArtist",strParams);
		m_mediaBitrate = ParseXML("MediaBitrate",strParams);
	
		m_SeekWnd.m_wndSlider.m_dwMax = atol(ParseXML("MediaLenSecs",strParams));
		m_SeekWnd.m_wndSlider.Init();

		FireChangeCurrentMediaInfo();	
	}

	return COleControl::OnCopyData(pWnd, pCopyDataStruct);
}

void CSteveMediaCenterOcxCtrl::ShowPopUpMenu() 
{
	CRect rect;
	GetWindowRect(rect);

	BOOL bIsTimedShutdownActive = SendMessageToInstanseOfApp("<Message>IsTimedShutdownActive</Message>");

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING,ID_FILE_SETTINGS,"Settings");
	if(bIsTimedShutdownActive)
		menu.AppendMenu(MF_CHECKED|MF_STRING,ID_FILE_ACTIVETIMEDSHUTDOWN,"Active Timed Shutdown...ZZZ");
	else
		menu.AppendMenu(MF_STRING,ID_FILE_ACTIVETIMEDSHUTDOWN,"Active Timed Shutdown...ZZZ");
	menu.AppendMenu(MF_STRING,ID_FILE_SELECTSKIN,"Select Skin");
	menu.AppendMenu(MF_STRING,ID_FILE_SELECTPLAYLIST,"Select/Manage Playlists");

	menu.TrackPopupMenu(TPM_CENTERALIGN,rect.right,rect.bottom,this);
}

void CSteveMediaCenterOcxCtrl::OnFileSettings() 
{
	SendMessageToInstanseOfApp("<Message>ShowSettings</Message>");
}

void CSteveMediaCenterOcxCtrl::OnFileActivetimedshutdown() 
{
	SendMessageToInstanseOfApp("<Message>ShowActivetimedshutdown</Message>");	
}

void CSteveMediaCenterOcxCtrl::OnFileSelectskin() 
{
	SendMessageToInstanseOfApp("<Message>ShowSelectSkin</Message>");
}

void CSteveMediaCenterOcxCtrl::OnFileSelectplaylist() 
{
	SendMessageToInstanseOfApp("<Message>ShowManagePlayList</Message>");	
}

void CSteveMediaCenterOcxCtrl::ShowVolumeControl() 
{
	if(!IsWindow(m_VolWnd.m_hWnd))
		return;

	CRect rect;
	GetClientRect(rect);
	CRect rect2 = rect;
	rect2.top = rect2.bottom - 30;
	rect2.left += m_volumeLeftOffset;
	rect2.right -= m_volumeRightOffset;
	
	BOOL bIsVisibleShow = m_VolWnd.IsWindowVisible();
	if(!bIsVisibleShow)
	{
		rect.bottom = rect.bottom - 30;
		m_ctlPlayList.MoveWindow(rect);
		m_VolWnd.MoveWindow(rect2);
		m_SeekWnd.ShowWindow(SW_HIDE);
		m_VolWnd.ShowWindow(SW_NORMAL);
	}
	else
	{
		m_VolWnd.ShowWindow(SW_HIDE);
		m_ctlPlayList.MoveWindow(rect);
	}	
}

void CSteveMediaCenterOcxCtrl::OnVolumeLeftOffsetChanged() 
{
	SetModifiedFlag();
}

void CSteveMediaCenterOcxCtrl::OnVolumeRightOffsetChanged() 
{
	SetModifiedFlag();
}

void CSteveMediaCenterOcxCtrl::ShowSeekControl() 
{
	if(!IsWindow(m_SeekWnd.m_hWnd))
		return;

	CRect rect;
	GetClientRect(rect);
	CRect rect2 = rect;
	rect2.top = rect2.bottom - 30;
	rect2.left += m_volumeLeftOffset;
	rect2.right -= m_volumeRightOffset;
	
	BOOL bIsVisibleShow = m_SeekWnd.IsWindowVisible();
	if(!bIsVisibleShow)
	{
		rect.bottom = rect.bottom - 30;
		m_ctlPlayList.MoveWindow(rect);
		m_SeekWnd.MoveWindow(rect2);
		m_VolWnd.ShowWindow(SW_HIDE);
		m_SeekWnd.ShowWindow(SW_NORMAL);
	}
	else
	{
		m_SeekWnd.ShowWindow(SW_HIDE);
		m_ctlPlayList.MoveWindow(rect);
	}
}

BOOL CSteveMediaCenterOcxCtrl::IsPlayListEmpty() 
{
	return (m_ctlPlayList.m_straPlayList.GetSize() == 0);
}

void CSteveMediaCenterOcxCtrl::SkinUpdate(LPCTSTR strParams) 
{
	CString strCmd;
	strCmd.Format("<Message>OrderSkin</Message><Params>%s</Params>",strParams);
	SendMessageToInstanseOfApp(strCmd);
}
