// MyDirectXPlayer.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "MyMediaPlayer.h"
#include "MyDirectXPlayer.h"
#include <wmsdkidl.h>
#include "ID3COM.h"
#include "id3com_i.c"
#include "MP3Info.h"



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
		GUID format = TIME_FORMAT_MEDIA_TIME;
		m_pMediaSeeking->SetTimeFormat(&format); 
		m_pGraph->QueryInterface(IID_IMediaEventEx, (void **)&m_pEvent);
		m_pGraph->QueryInterface(IID_IMediaPosition, (void **)&m_pMediaPosition);
		m_pGraph->QueryInterface(IID_IBasicAudio, (void **)&m_pBasicAudio);
		m_pGraph->QueryInterface(IID_IBasicVideo, (void **)&m_pBasicVideo);
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
						DWORD dwTestEnd = llEndPos / (LONGLONG)10000000;
						BOOL bEndedEarly = TestEndedEarly(dwTestEnd);
						if(bEndedEarly)
						{
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
	m_strCurrentFile = strFile;
	HRESULT hr = 0;
	TRY
	{
		ReleaseComponents();
		CreateComponents();
		hr = m_pGraph->RenderFile(strFile.AllocSysString(), NULL);
		// try fixing mp3 tag if fails
		if(hr != 0 && IsMp3File(strFile))
		{
			RemovePicTag(strFile);
		}
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
	}
	CATCH(CException,e)
	{
	}
	END_CATCH
}

void CMyDirectXPlayer::ShowVideoWindow(BOOL bShow)
{
	HRESULT hr;
	hr = m_pVideoWindow->put_Owner((OAHWND)m_hWnd);
	hr = m_pVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	if(bShow)
	{
		hr = m_pVideoWindow->put_Visible(OATRUE);
		CRect rect;
		GetClientRect(rect);
		m_pVideoWindow->SetWindowPosition(0,0,rect.Width(),rect.Height());
	}
	else
	{
		hr = m_pVideoWindow->put_Visible(OAFALSE);
		m_pVideoWindow->SetWindowPosition(0,0,0,0);
	}
	if(FAILED(hr))
		AfxMessageBox("Error creating video window");
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

/*
BOOL CMyDirectXPlayer::RemovePicTag(CString strFile)
{
	CString strImage = strFile + ".image";
	BSTR bstrImage = strImage.AllocSysString();
	BOOL bReplacePic = false;

	IID3ComTag* pMyTag = NULL;
	HRESULT hr = CoCreateInstance(CLSID_ID3ComTag,
									NULL,
									CLSCTX_INPROC_SERVER,
									IID_IID3ComTag,
									(void**)&pMyTag);
	if(hr == 0 && pMyTag)
	{
		BSTR bstr = strFile.AllocSysString();
		pMyTag->Link(&bstr);
		// get frame
		IID3ComFrame* pFrame = NULL;
		hr = pMyTag->FindFrame(ID3_PICTURE,false,&pFrame);
		if(hr == 0 && pFrame)
		{
			// get field
			IID3ComField* pComField = NULL;
			hr = pFrame->get_Field(ID3_FIELD_DATA,&pComField); 
			if(hr == 0 && pComField)
			{
				hr = pComField->CopyDataToFile(bstrImage);
				bReplacePic = (hr == 0);
			}
		}
		// remove picture data
		hr = pMyTag->RemoveFrame(ID3_PICTURE);

		pMyTag->put_UnSync(false);
		pMyTag->put_Padding(true);
		pMyTag->SaveV2Tag();

		hr = m_pGraph->RenderFile(bstr, NULL);

		// replace picture
		if(bReplacePic)
		{
			hr = pMyTag->Clear();
			hr = pMyTag->Link(&bstr);
			hr = pMyTag->FindFrame(ID3_PICTURE,-1,&pFrame);
			if(hr == 0 && pFrame)
			{
				// get field
				IID3ComField* pComField = NULL;
				hr = pFrame->get_Field(ID3_FIELD_DATA,&pComField); 
				if(hr == 0 && pComField)
				{
					hr = pComField->CopyDataFromFile(bstrImage);
					if(hr == 0)
					{
						hr = pMyTag->SaveV2Tag();
					}
				}
			}
		}
		// release com
		if(pMyTag)
			pMyTag->Release();
	}
	return (hr == 0);
}
*/

BOOL CMyDirectXPlayer::TestEndedEarly(DWORD dwTestEnd)
{
	BOOL bEndedEarly = false;
	
	LONGLONG dwDur = 0;
	m_pMediaSeeking->GetDuration(&dwDur);
	DWORD dwSecs = dwDur / (LONGLONG)10000000;
	if((dwTestEnd + 1) < dwSecs)
		bEndedEarly = true;

	if(bEndedEarly && IsMp3File(m_strCurrentFile))
	{
		// Length tag
		long lSecs = 0;
		CMP3Info info(m_strCurrentFile);
		lSecs = (long)info.GetLength();
		if(lSecs > 0)
		{
			if((dwTestEnd + 1) < lSecs)
				bEndedEarly = true;
		}
	}
	
	return bEndedEarly;
}

BOOL CMyDirectXPlayer::RemovePicTag(CString strFile)
{
	IID3ComTag* pMyTag = NULL;
	HRESULT hr = CoCreateInstance(CLSID_ID3ComTag,
									NULL,
									CLSCTX_INPROC_SERVER,
									IID_IID3ComTag,
									(void**)&pMyTag);
	if(hr == 0 && pMyTag)
	{
		BSTR bstr = strFile.AllocSysString();
		pMyTag->Link(&bstr);
		// remove picture data
		hr = pMyTag->RemoveFrame(ID3_PICTURE);

		pMyTag->put_UnSync(false);
		pMyTag->put_Padding(true);
		pMyTag->SaveV2Tag();

		hr = m_pGraph->RenderFile(bstr, NULL);

		// release com
		if(pMyTag)
			pMyTag->Release();
	}
	return (hr == 0);
}

CString CMyDirectXPlayer::GetTitle()
{
	CString str;
	CMP3Info info(m_strCurrentFile);
	str = info.GetTitle();
	if(str.IsEmpty())
	{
		IID3ComTag* pMyTag = NULL;
		HRESULT hr = CoCreateInstance(CLSID_ID3ComTag,
										NULL,
										CLSCTX_INPROC_SERVER,
										IID_IID3ComTag,
										(void**)&pMyTag);
		if(hr == 0 && pMyTag)
		{
			BSTR bstr = m_strCurrentFile.AllocSysString();
			pMyTag->Link(&bstr);
			BSTR bstrTag;
			hr = pMyTag->get_Title(&bstrTag);
			// release com
			if(pMyTag)
				pMyTag->Release();
			str = bstrTag;
		}
	}
	return str;
}

CString CMyDirectXPlayer::GetArtist()
{
	CString str;
	CMP3Info info(m_strCurrentFile);
	str = info.GetArtist();
	if(str.IsEmpty())
	{
		IID3ComTag* pMyTag = NULL;
		HRESULT hr = CoCreateInstance(CLSID_ID3ComTag,
										NULL,
										CLSCTX_INPROC_SERVER,
										IID_IID3ComTag,
										(void**)&pMyTag);
		if(hr == 0 && pMyTag)
		{
			BSTR bstr = m_strCurrentFile.AllocSysString();
			pMyTag->Link(&bstr);
			BSTR bstrTag;
			hr = pMyTag->get_Artist(&bstrTag);
			// release com
			if(pMyTag)
				pMyTag->Release();
			str = bstrTag;
		}
	}
	return str;
}

CString CMyDirectXPlayer::GetBitrate()
{
	CMP3Info info(m_strCurrentFile);
	int nBirate = info.GetBitRate();
	CString str;
	str.Format("%d bps",nBirate);
	return str;
}
