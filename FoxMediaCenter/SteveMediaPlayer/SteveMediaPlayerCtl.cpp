// SteveMediaPlayerCtl.cpp : Implementation of the CSteveMediaPlayerCtrl ActiveX Control class.

#include "stdafx.h"
#include "SteveMediaPlayer.h"
#include "MyMediaPlayer.h"
#include "SteveMediaPlayerCtl.h"
#include "SteveMediaPlayerPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSteveMediaPlayerCtrl, COleControl)

BEGIN_INTERFACE_MAP(CSteveMediaPlayerCtrl, COleControl)
  INTERFACE_PART(CSteveMediaPlayerCtrl, IID_IObjectSafety, ObjectSafety)
END_INTERFACE_MAP()


BEGIN_MESSAGE_MAP(CSteveMediaPlayerCtrl, COleControl)
	//{{AFX_MSG_MAP(CSteveMediaPlayerCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_COPYDATA()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_MESSAGE(WM_SEND_PLAY_INFO,OnSendPlayingInfo)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CSteveMediaPlayerCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CSteveMediaPlayerCtrl)
	DISP_PROPERTY_NOTIFY(CSteveMediaPlayerCtrl, "nLeftPos", m_nLeftPos, OnNLeftPosChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CSteveMediaPlayerCtrl, "nTopPos", m_nTopPos, OnNTopPosChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CSteveMediaPlayerCtrl, "nRightPos", m_nRightPos, OnNRightPosChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CSteveMediaPlayerCtrl, "nBottomPos", m_nBottomPos, OnNBottomPosChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CSteveMediaPlayerCtrl, "VolumeLeftOffset", m_volumeLeftOffset, OnVolumeLeftOffsetChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CSteveMediaPlayerCtrl, "VolumeRightOffset", m_volumeRightOffset, OnVolumeRightOffsetChanged, VT_I2)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "ResizeMyControl", ResizeMyControl, VT_EMPTY, VTS_I2 VTS_I2)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "Previous", Previous, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "Next", Next, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "Play", Play, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "Stop", Stop, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "Pause", Pause, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "FullScreen", FullScreen, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "LowerVolume", LowerVolume, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "IncreaseVolume", IncreaseVolume, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "ShowPlayList", ShowPlayList, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "Mute", Mute, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "Rewind", Rewind, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "Forward", Forward, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "ShowVolumeControl", ShowVolumeControl, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CSteveMediaPlayerCtrl, "ShowSeekControl", ShowSeekControl, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CSteveMediaPlayerCtrl, COleControl)
	//{{AFX_EVENT_MAP(CSteveMediaPlayerCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CSteveMediaPlayerCtrl, 1)
	PROPPAGEID(CSteveMediaPlayerPropPage::guid)
END_PROPPAGEIDS(CSteveMediaPlayerCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSteveMediaPlayerCtrl, "STEVEMEDIAPLAYER.SteveMediaPlayerCtrl.1",
	0x1eb178e4, 0x9fb1, 0x428c, 0x94, 0xb8, 0xba, 0x94, 0x5b, 0xb7, 0xa8, 0xe3)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CSteveMediaPlayerCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DSteveMediaPlayer =
		{ 0x767946e1, 0xe005, 0x49a4, { 0xbb, 0x7a, 0x22, 0x28, 0x2b, 0x67, 0xd5, 0x56 } };
const IID BASED_CODE IID_DSteveMediaPlayerEvents =
		{ 0x369fd439, 0xf992, 0x4dc7, { 0xb2, 0xd4, 0xd1, 0x25, 0x45, 0x7a, 0x18, 0x22 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwSteveMediaPlayerOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CSteveMediaPlayerCtrl, IDS_STEVEMEDIAPLAYER, _dwSteveMediaPlayerOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CSteveMediaPlayerCtrl::CSteveMediaPlayerCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CSteveMediaPlayerCtrl

BOOL CSteveMediaPlayerCtrl::CSteveMediaPlayerCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_STEVEMEDIAPLAYER,
			IDB_STEVEMEDIAPLAYER,
			afxRegInsertable | afxRegApartmentThreading,
			_dwSteveMediaPlayerOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

// Implementation of IObjectSafety
STDMETHODIMP CSteveMediaPlayerCtrl::XObjectSafety::GetInterfaceSafetyOptions(
			REFIID riid, 
			DWORD __RPC_FAR *pdwSupportedOptions, 
			DWORD __RPC_FAR *pdwEnabledOptions)
{
	METHOD_PROLOGUE_EX(CSteveMediaPlayerCtrl, ObjectSafety)

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

STDMETHODIMP CSteveMediaPlayerCtrl::XObjectSafety::SetInterfaceSafetyOptions(
		REFIID riid, 
		DWORD dwOptionSetMask, 
		DWORD dwEnabledOptions)
{
	METHOD_PROLOGUE_EX(CSteveMediaPlayerCtrl, ObjectSafety)

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

STDMETHODIMP_(ULONG) CSteveMediaPlayerCtrl::XObjectSafety::AddRef()
{
	METHOD_PROLOGUE_EX_(CSteveMediaPlayerCtrl, ObjectSafety)
	return (ULONG)pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CSteveMediaPlayerCtrl::XObjectSafety::Release()
{
	METHOD_PROLOGUE_EX_(CSteveMediaPlayerCtrl, ObjectSafety)
	return (ULONG)pThis->ExternalRelease();
}

STDMETHODIMP CSteveMediaPlayerCtrl::XObjectSafety::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(CSteveMediaPlayerCtrl, ObjectSafety)
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

CSteveMediaPlayerCtrl::CSteveMediaPlayerCtrl()
{
	InitializeIIDs(&IID_DSteveMediaPlayer, &IID_DSteveMediaPlayerEvents);

	m_nLeftPos=0;
	m_nTopPos=0;
	m_nRightPos=0;
	m_nBottomPos=0;
	m_pMyMediaPlayer = NULL;
	m_TimerPlayerReady = NULL;
	m_volumeLeftOffset = 0;
	m_volumeRightOffset = 0;
	m_SeekWnd.m_pMain = this;
}

CSteveMediaPlayerCtrl::~CSteveMediaPlayerCtrl()
{
	if(m_pMyMediaPlayer)
	{
		delete m_pMyMediaPlayer;
		m_pMyMediaPlayer = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSteveMediaPlayerCtrl::DoPropExchange - Persistence support

void CSteveMediaPlayerCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
}

void CSteveMediaPlayerCtrl::OnResetState()
{
	COleControl::OnResetState();  
}

int CSteveMediaPlayerCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(rect);

	m_pMyMediaPlayer = new CMyMediaPlayer();
	m_pMyMediaPlayer->m_pMainWnd = this;
	BOOL bOK = m_pMyMediaPlayer->Create(NULL,"Media Center Player",WS_CHILD|WS_VISIBLE,rect,this,ID_MEDIA_CENTER_WND);
	if(!bOK)
	{
		AfxMessageBox("Error creating media control");
		return 1;
	}

	CWnd* pWnd = GetDesktopWindow();	
	m_msgWnd.m_pParent = this;
	BOOL bOk = m_msgWnd.CreateEx(0,0,"PlayListUpdateWnd",
				WS_BORDER, CRect(1,1,1,1),pWnd,0);
	
	// volume wnd
	rect.top = rect.bottom - 30;
	m_VolWnd.Create(NULL,"VolumeWnd",WS_CHILD,rect,this,4102);
	m_SeekWnd.Create(NULL,"SeekWnd",WS_CHILD,rect,this,4103);

	m_TimerPlayerReady = SetTimer(ID_TIMER_PLAYER_READY,50,NULL);

	return 0;
}

void CSteveMediaPlayerCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);

	if(!m_pMyMediaPlayer || !IsWindow(m_pMyMediaPlayer->m_hWnd))
		return;

	CRect rect;
	GetClientRect(rect);
	CRect rect2 = rect;
	rect2.top = rect2.bottom - 30;
	rect2.left += m_volumeLeftOffset;
	rect2.right -= m_volumeRightOffset;
	
	// volume visible?
	BOOL bIsVisibleShow = false;
	if(IsWindow(m_VolWnd.m_hWnd))		
		bIsVisibleShow = m_VolWnd.IsWindowVisible();
	// seek visible?
	BOOL bIsVisibleSeek = false;
	if(IsWindow(m_SeekWnd.m_hWnd))		
		bIsVisibleSeek = m_SeekWnd.IsWindowVisible();
	if(bIsVisibleShow)
	{
		rect.bottom = rect.bottom - 30;
		m_pMyMediaPlayer->MoveWindow(rect);
		m_VolWnd.MoveWindow(rect2);
	}
	else if(bIsVisibleSeek)
	{
		rect.bottom = rect.bottom - 30;
		m_pMyMediaPlayer->MoveWindow(rect);
		m_SeekWnd.MoveWindow(rect2);
	}
	else
	{
		m_pMyMediaPlayer->MoveWindow(rect);
	}	
}

void CSteveMediaPlayerCtrl::ResizeMyControl(short nWidth, short nHeight) 
{
	CRect rect(m_nLeftPos,m_nTopPos,nWidth-m_nRightPos,nHeight-m_nBottomPos);
	SetRectInContainer(rect);
}

void CSteveMediaPlayerCtrl::OnNLeftPosChanged() 
{
	SetModifiedFlag();
}

void CSteveMediaPlayerCtrl::OnNTopPosChanged() 
{
	SetModifiedFlag();
}

void CSteveMediaPlayerCtrl::OnNRightPosChanged() 
{
	SetModifiedFlag();
}

void CSteveMediaPlayerCtrl::OnNBottomPosChanged() 
{
	SetModifiedFlag();
}

void CSteveMediaPlayerCtrl::Play() 
{
	if(m_pMyMediaPlayer)
		m_pMyMediaPlayer->Play();	
}

void CSteveMediaPlayerCtrl::Stop() 
{
	if(m_pMyMediaPlayer)
		m_pMyMediaPlayer->Stop();	
}

void CSteveMediaPlayerCtrl::Pause() 
{
	if(m_pMyMediaPlayer)
		m_pMyMediaPlayer->Pause();	
}

BOOL CSteveMediaPlayerCtrl::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	CString strParams;
	int nSize = pCopyDataStruct->cbData;
	memcpy(strParams.GetBuffer(nSize),pCopyDataStruct->lpData,nSize);
	strParams.ReleaseBuffer();
	
	if("SetCurrentFilePath" == ParseXML("Message",strParams))
	{
		if(m_pMyMediaPlayer)
		{
			CString strFile = ParseXML("FullPath",strParams);
			m_pMyMediaPlayer->SetFilePath(strFile);
			m_pMyMediaPlayer->Play();	
		}
	}	
	else if("Play" == ParseXML("Message",strParams))
	{
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->Play();	
	}
	else if("Pause" == ParseXML("Message",strParams))
	{
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->Pause();	
	}
	else if("Stop" == ParseXML("Message",strParams))
	{
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->Stop();	
	}
	else if("Rewind" == ParseXML("Message",strParams))
	{
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->Rewind();	
	}
	else if("Forward" == ParseXML("Message",strParams))
	{
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->Forward();	
	}
	else if("SendPlayingInfo" == ParseXML("Message",strParams))
	{
		PostMessage(WM_SEND_PLAY_INFO);
	}
	else if("SetCurrentPosition" == ParseXML("Message",strParams))
	{
		DWORD dwPos = atol(ParseXML("Position",strParams));
		LONGLONG llPos = dwPos * (LONGLONG)10000000;
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->SetCurrentPosition(llPos);
	}

	return COleControl::OnCopyData(pWnd, pCopyDataStruct);
}

void CSteveMediaPlayerCtrl::FullScreen() 
{
	if(m_pMyMediaPlayer)
		m_pMyMediaPlayer->FullScreen();	
}

void CSteveMediaPlayerCtrl::LowerVolume() 
{
	CString strSendData = "<Message>LowerVolume</Message>";
	SendMessageToInstanseOfApp(strSendData);
}

void CSteveMediaPlayerCtrl::IncreaseVolume() 
{
	CString strSendData = "<Message>IncreaseVolume</Message>";
	SendMessageToInstanseOfApp(strSendData);
}

void CSteveMediaPlayerCtrl::ShowPlayList() 
{
	CString strSendData = "<Message>ShowPlayList</Message>";
	SendMessageToInstanseOfApp(strSendData);
}

void CSteveMediaPlayerCtrl::Previous() 
{
	CString strSendData = "<Message>Previous</Message>";
	SendMessageToInstanseOfApp(strSendData);
}

void CSteveMediaPlayerCtrl::Next() 
{
	CString strSendData = "<Message>Next</Message>";
	SendMessageToInstanseOfApp(strSendData);
}

void CSteveMediaPlayerCtrl::Mute() 
{
	CString strSendData = "<Message>Mute</Message>";
	SendMessageToInstanseOfApp(strSendData);
}

void CSteveMediaPlayerCtrl::Rewind() 
{
	if(m_pMyMediaPlayer)
		m_pMyMediaPlayer->Rewind();	
}

void CSteveMediaPlayerCtrl::Forward() 
{
	if(m_pMyMediaPlayer)
		m_pMyMediaPlayer->Forward();	
}

void CSteveMediaPlayerCtrl::OnTimer(UINT nIDEvent) 
{
	if(ID_TIMER_PLAYER_READY == nIDEvent)
	{
		KillTimer(m_TimerPlayerReady);
		SendMessageToInstanseOfApp("<Message>VideoPlayerReady</Message>");
	}
	COleControl::OnTimer(nIDEvent);
}

long CSteveMediaPlayerCtrl::OnSendPlayingInfo(UINT wParam,LPARAM lparam)
{
	if(m_pMyMediaPlayer)
		m_pMyMediaPlayer->SendCurrentMediaInfo();	

	return 1;
}

void CSteveMediaPlayerCtrl::OnVolumeLeftOffsetChanged() 
{
	SetModifiedFlag();
}

void CSteveMediaPlayerCtrl::OnVolumeRightOffsetChanged() 
{
	SetModifiedFlag();
}

void CSteveMediaPlayerCtrl::ShowVolumeControl() 
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
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->MoveWindow(rect);
		m_VolWnd.MoveWindow(rect2);
		m_SeekWnd.ShowWindow(SW_HIDE);
		m_VolWnd.ShowWindow(SW_NORMAL);
	}
	else
	{
		m_VolWnd.ShowWindow(SW_HIDE);
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->MoveWindow(rect);
	}	
}

void CSteveMediaPlayerCtrl::ShowSeekControl() 
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
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->MoveWindow(rect);
		m_VolWnd.ShowWindow(SW_HIDE);
		m_SeekWnd.MoveWindow(rect2);
		m_SeekWnd.ShowWindow(SW_NORMAL);
	}
	else
	{
		m_SeekWnd.ShowWindow(SW_HIDE);
		if(m_pMyMediaPlayer)
			m_pMyMediaPlayer->MoveWindow(rect);
	}
}

