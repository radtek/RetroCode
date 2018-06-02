// MyDirectXPlayer.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaPlayer.h"
#include "MyMediaPlayer.h"
#include "MyDirectXPlayer.h"
#include <wmsdkidl.h>
#include "SteveMediaPlayerCtl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDirectXPlayer

CMyDirectXPlayer::CMyDirectXPlayer()
{
	m_pGraph = NULL;
	m_pMediaControl = NULL;
	m_pEvent = NULL;
	m_pMediaSeeking = NULL;
	m_pVideoWindow = NULL;
	m_pMediaPosition = NULL;
	m_pBasicAudio = NULL;
	m_pBasicVideo = NULL;

	m_pMain = NULL;
	m_timeStart = NULL;
	m_llStartPos = 0;
}

CMyDirectXPlayer::~CMyDirectXPlayer()
{
	ReleaseComponents();
}


BEGIN_MESSAGE_MAP(CMyDirectXPlayer, CWnd)
	//{{AFX_MSG_MAP(CMyDirectXPlayer)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_GRAPHNOTIFY,HandleGraphEvent)
END_MESSAGE_MAP()


int CMyDirectXPlayer::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CMyDirectXPlayer::CreateComponents()
{
	HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
							IID_IGraphBuilder, (void **)&m_pGraph);
	if(!FAILED(hr))
	{
		m_pGraph->QueryInterface(IID_IMediaControl, (void **)&m_pMediaControl);
		m_pGraph->QueryInterface(IID_IMediaSeeking, (void **)&m_pMediaSeeking);
		m_pGraph->QueryInterface(IID_IMediaEventEx, (void **)&m_pEvent);
		m_pGraph->QueryInterface(IID_IMediaPosition, (void **)&m_pMediaPosition);
		m_pGraph->QueryInterface(IID_IBasicAudio, (void **)&m_pBasicAudio);
		m_pGraph->QueryInterface(IID_IBasicVideo2, (void **)&m_pBasicVideo);
		m_pGraph->QueryInterface(IID_IVideoWindow, (void **)&m_pVideoWindow);	
	}
	else
	{
		AfxMessageBox("Error creating Media Player window, please make sure DirectX 7 or better is installed.");
	}

	SetWindowOwner();
}

void CMyDirectXPlayer::ReleaseComponents()
{
	if(m_pVideoWindow)
	{
		m_pVideoWindow->put_Owner(NULL);
		m_pVideoWindow->put_Visible(OAFALSE);
	}
	if(m_pBasicVideo)
	{
		m_pBasicVideo->Release();
		m_pBasicVideo = NULL;
	}
	if(m_pBasicAudio)
	{
		m_pBasicAudio->Release();
		m_pBasicAudio = NULL;
	}
	if(m_pMediaPosition)
	{
		m_pMediaPosition->Release();
		m_pMediaPosition = NULL;
	}
	if(m_pVideoWindow)
	{
		m_pVideoWindow->Release();
		m_pVideoWindow = NULL;
	}
	if(m_pMediaSeeking)
	{
		m_pMediaSeeking->Release();
		m_pMediaSeeking = NULL;
	}
	if(m_pMediaControl)
	{
		m_pMediaControl->Release();
		m_pMediaControl = NULL;
	}
	if(m_pEvent)
	{
		m_pEvent->Release();
		m_pEvent = NULL;
	}
	if(m_pGraph)
	{
		m_pGraph->Release();
		m_pGraph = NULL;
	}
}

BOOL CMyDirectXPlayer::SetWindowOwner()
{
	// set video window params
	HRESULT hr = m_pEvent->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0);
	return (hr == 0);
}

long CMyDirectXPlayer::HandleGraphEvent(WPARAM wParam,LPARAM lParam)
{
    LONG evCode, evParam1, evParam2;
    HRESULT hr=S_OK;
	if(m_pEvent)
	{
		while(SUCCEEDED(m_pEvent->GetEvent(&evCode, &evParam1, &evParam2, 0)))
		{
			// Spin through the events
			if(m_pEvent)
			{
				hr = m_pEvent->FreeEventParams(evCode, evParam1, evParam2);
				if(EC_COMPLETE == evCode)
				{
					// check for premeture ending
					if(m_pMediaSeeking)
					{
						CTime timeEnd = CTime::GetCurrentTime();
						LONGLONG llEndPos = GetCurrentPosition();
						llEndPos -= m_llStartPos; 	
						CTimeSpan tm = timeEnd - m_timeStart;
						long lSecs = tm.GetTotalSeconds();
						lSecs += 1;	
						llEndPos = llEndPos / (LONGLONG)10000000;
						
						if(lSecs < llEndPos)
						{		
							Stop();
							SetCurrentPosition(lSecs * (LONGLONG)10000000);
							Play();
							return 1;
						}
					}
					m_pMain->OnEndOfStreamMediaplayer1(0);
				}
				else if(EC_OPENING_FILE == evCode)
				{
					if(evParam1 == FALSE)
						m_pMain->OnReadyStateChangeMediaplayer1(4);
				}
				else if(EC_WMT_EVENT == evCode)
				{
					//         WMT_NO_RIGHTS        - pData is a pointer to a WCHAR string containing a challenge URL
					//         WMT_ACQUIRE_LICENSE  - lParam2 is a pointer to a WM_GET_LICENSE_DATA struct
					//         WMT_NO_RIGHTS_EX     - lParam2 is a pointer to a WM_GET_LICENSE_DATA struct
					//         WMT_NEEDS_INDIVIDUALIZATION - lParam2 is NULL
					//         WMT_INDIVIDUALIZE    - lParam2 is a pointer to a WM_INDIVIDUALIZE_STATUS struct
					// lParam2 is a pointer an AM_WMT_EVENT_DATA structure where,
					//                          hrStatus is the status code sent by the wmsdk
					//                          pData is specific to the lParam1 event

					AM_WMT_EVENT_DATA* pStruct = (AM_WMT_EVENT_DATA*)evParam2;
					if(evParam1 == WMT_NO_RIGHTS)
					{
						CString strURL = (LPSTR)pStruct->pData;
						AfxMessageBox(strURL);	
					}
				}
			}
		}
	}
    return hr;
}

void CMyDirectXPlayer::SetFileName(CString strFile)
{
	TRY
	{
		ShowVideoWindow(false);
		ReleaseComponents();
		CreateComponents();
		HRESULT hr = m_pGraph->RenderFile(strFile.AllocSysString(), NULL);
		ShowVideoWindow(true);

	}
	CATCH(CException,e)
	{
		e->ReportError();
	}
	END_CATCH
}

BOOL CMyDirectXPlayer::Play()
{
	HRESULT hr;
	TRY
	{
		hr = m_pMediaControl->Run();
		m_timeStart = CTime::GetCurrentTime();
		m_llStartPos = GetCurrentPosition();
	}
	CATCH(CException,e)
	{
		return false;
	}
	END_CATCH
	
	return (hr==0);
}

void CMyDirectXPlayer::Pause()
{
	TRY
	{
		m_pMediaControl->Pause();
		m_timeStart = CTime::GetCurrentTime();
		m_llStartPos = GetCurrentPosition();
	}
	CATCH(CException,e)
	{
	}
	END_CATCH
}

void CMyDirectXPlayer::Stop()
{
	TRY
	{
		LONGLONG pos = 0;
		HRESULT hr = m_pMediaControl->Stop();
		if(!FAILED(hr))
			hr = m_pMediaSeeking->SetPositions(&pos,AM_SEEKING_AbsolutePositioning,NULL, AM_SEEKING_NoPositioning);
		ShowVideoWindow(false);
	}
	CATCH(CException,e)
	{
	}
	END_CATCH
}

void CMyDirectXPlayer::ShowVideoWindow(BOOL bShow)
{
	HRESULT hr;
	if(!m_pVideoWindow)
	{
		if(IsWindow(m_hWnd) && !bShow)
			ShowWindow(SW_HIDE);
		return;
	}
	
	hr = m_pVideoWindow->put_Owner((OAHWND)m_hWnd);
	hr = m_pVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	if(bShow)
	{
		CRect rect;
		GetClientRect(rect);
		ShowWindow(SW_NORMAL);

		CRect rectAsp = GetAspectRatio(rect.Width(),rect.Height());
		m_pVideoWindow->SetWindowPosition(rectAsp.left,rectAsp.top,rectAsp.Width(),rectAsp.Height());
		hr = m_pVideoWindow->put_Visible(OATRUE);
	}
	else
	{
		hr = m_pVideoWindow->put_Visible(OAFALSE);
		m_pVideoWindow->SetWindowPosition(0,0,0,0);
		ShowWindow(SW_HIDE);
	}
}

LONGLONG CMyDirectXPlayer::GetCurrentPosition()
{
	LONGLONG lPos = 0;
	if(m_pMediaSeeking)
	{
		m_pMediaSeeking->GetCurrentPosition(&lPos);
	}
	return lPos;
}

void CMyDirectXPlayer::SetCurrentPosition(LONGLONG llPos)
{
	if(m_pMediaSeeking)
	{
		m_pMediaSeeking->SetPositions(&llPos,AM_SEEKING_AbsolutePositioning,
			NULL, AM_SEEKING_NoPositioning);	
		m_timeStart = CTime::GetCurrentTime();
		m_llStartPos = llPos;
	}
}

void CMyDirectXPlayer::Rewind()
{
	if(m_pMediaSeeking)
	{
		LONGLONG dwPos = GetCurrentPosition();
		dwPos -= 20 * (LONGLONG)10000000;
		if(dwPos < 0)
			dwPos = 0;
		SetCurrentPosition(dwPos);
	}
}

void CMyDirectXPlayer::Forward()
{
	if(m_pMediaSeeking)
	{
		LONGLONG dwDur = 0;
		m_pMediaSeeking->GetDuration(&dwDur);
		LONGLONG dwPos = GetCurrentPosition();
		dwPos += 20 * (LONGLONG)10000000;
		if(dwPos > dwDur)
			dwPos = dwDur -1;
		SetCurrentPosition(dwPos);
	}
}

long CMyDirectXPlayer::GetLengthInSecs()
{
	LONGLONG dwDur = 0;
	m_pMediaSeeking->GetDuration(&dwDur);
	long lSecs = dwDur / (LONGLONG)10000000;
	return lSecs;
}

void CMyDirectXPlayer::OnSize(UINT nType, int cx, int cy) 
{
	if(m_pVideoWindow)
	{
		CRect rect = GetAspectRatio(cx,cy);
		m_pVideoWindow->SetWindowPosition(rect.left,rect.top,rect.Width(),rect.Height());
	}
}

// pass in CWnd onsize x and y and return a CRect
// used in a call to m_pVideoWindow->SetWindowPosition(x,y,w,h)
CRect CMyDirectXPlayer::GetAspectRatio(long lx,long ly)
{
	CRect rect(0,0,lx,ly);
	if(!m_pBasicVideo)
		return rect;
	
	HRESULT hr = 0;
	long lNewX = lx;
	long lNewY = ly;
	long lX = 0;
	long lY = 0;
	// work out multiplier for x,y
	float fXvideo = 1;
	float fYvideo = 1;
	hr = m_pBasicVideo->get_VideoWidth(&lX);
	hr = m_pBasicVideo->get_VideoHeight(&lY);
	// video aspect ratio
	if(lX > lY)
		fYvideo = (float)lY / (float)lX;
	else if(lX < lY)
		fXvideo = (float)lX / (float)lY;

	// screen x,y by aspect
	if(lx > ly || lX > lY)
	{
		float fXscreen = (float)ly / (float)lx;
		// screen ratio
		lNewX = lNewX * fXscreen;
		// video ratio
		lNewX = lNewX / fYvideo;
		// too big, shrink
		if(lNewX > lx)
		{
			lNewX = lx;	
			lNewY = lNewX * fYvideo;
		}
	}
	else
	{
		float fYscreen = (float)lx / (float)ly;
		lNewY = lNewY * fYscreen;
		lNewY = lNewY / fXvideo;
		// too big, shrink
		if(lNewY > ly)
		{
			lNewY = ly;	
			lNewX = lNewY * fXvideo;
		}
	}

	int nOffSetX = (rect.Width() - lNewX) / 2;
	int nOffSetY = (rect.Height() - lNewY) / 2;

	rect.left = rect.left + nOffSetX;
	rect.top = rect.top + nOffSetY;
	rect.right = rect.right - nOffSetX;
	rect.bottom = rect.bottom - nOffSetY;
	
	return rect;
}

void CMyDirectXPlayer::FullScreen()
{
	m_pVideoWindow->put_MessageDrain((OAHWND)m_hWnd);
	if(m_pVideoWindow)
		m_pVideoWindow->put_FullScreenMode(OATRUE);	
}

void CMyDirectXPlayer::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar == 27)
	{
		ShowTaskBar(true);

		if(m_pVideoWindow)
			m_pVideoWindow->put_FullScreenMode(OAFALSE);
		m_pMain->m_bIsInFullScreen = false;

		m_pMain->m_wndFullScreen.ShowWindow(SW_HIDE);
		m_pMain->m_pMainWnd->InvalidateRect(NULL);

		ShowCursor(true);
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);
		SetCursorPos(rect.Width()/2,rect.Height()/2);
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
