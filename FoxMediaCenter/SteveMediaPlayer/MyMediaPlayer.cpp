// MyMediaPlayer.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaPlayer.h"
#include "SteveMediaPlayerCtl.h"
#include "MyDirectXPlayer.h"
#include "MyMediaPlayer.h"
#include "helpers.h"
#include "VolumeControl.h"
#include "SeekWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyMediaPlayer

CMyMediaPlayer::CMyMediaPlayer()
{
	m_enumCurrentMediaType = NONE;
	m_enumCurrentPlayState = STOPPED;
	m_pDXVideoPlayer = NULL;
	m_bDXVideoGood = false;
	m_bQTVideoGood = false;
	m_pQTPlayer = NULL;	
//	m_bRealVideoGood = false;
//	m_pRealPlayer = NULL;

	m_bMuted = false;
	m_dwPrevVol = 0;
	m_bRepeatOn = true;
	m_pMainWnd = NULL;
	m_TimerPlayPos = NULL;
	m_lLastPlayPos = 0;
	m_bIsInFullScreen = false;
}

CMyMediaPlayer::~CMyMediaPlayer()
{
	if(m_pDXVideoPlayer)
	{
		delete m_pDXVideoPlayer;
		m_pDXVideoPlayer = NULL;
	}
	if(m_pQTPlayer)
	{
		delete m_pQTPlayer;
		m_pQTPlayer = NULL;
	}
/*	if(m_pRealPlayer)
	{
		delete m_pRealPlayer;
		m_pRealPlayer = NULL;
	} */
}

BEGIN_MESSAGE_MAP(CMyMediaPlayer, CWnd)
	//{{AFX_MSG_MAP(CMyMediaPlayer)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_END_QT_FULLSCREEN,OnEndFullScreen)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyMediaPlayer message handlers

int CMyMediaPlayer::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(rect);
	m_pDXVideoPlayer = new CMyDirectXPlayer(); 
	m_pDXVideoPlayer->m_pMain = this;
	m_bDXVideoGood = m_pDXVideoPlayer->Create(NULL,"Media64",WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,ID_MEDIA_PLAYER_64);

	// full screen wnd
	CWnd* pDesk = GetDesktopWindow();
	pDesk->GetWindowRect(rect);
	rect.bottom += 50;
	BOOL bOK = m_wndFullScreen.CreateEx(NULL,AfxRegisterWndClass(0),"Full Screen",WS_POPUP,rect,this,0);
	
	return 0;
}

void CMyMediaPlayer::OnSize(UINT nType, int cx, int cy) 
{
	if(m_pDXVideoPlayer && IsWindow(m_pDXVideoPlayer->m_hWnd))
		m_pDXVideoPlayer->MoveWindow(0,0,cx,cy);
	if(m_pQTPlayer && IsWindow(m_pQTPlayer->m_hWnd))
		m_pQTPlayer->MoveWindow(0,0,cx,cy);
//	if(m_pRealPlayer && IsWindow(m_pRealPlayer->m_hWnd))
//		m_pRealPlayer->MoveWindow(0,0,cx,cy);
}

void CMyMediaPlayer::SetFilePath(CString strFilePath)
{
	m_strCurrentVideoPath = strFilePath;
}

BOOL CMyMediaPlayer::Pause()
{
	if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		if(m_bDXVideoGood)
		{
			if(m_enumCurrentPlayState == PAUSED)
			{
				m_pDXVideoPlayer->Play();
				m_enumCurrentPlayState = PLAYING;
			}
			else
			{
				m_pDXVideoPlayer->Pause();
				m_enumCurrentPlayState = PAUSED;
			}
			return true;
		}
	}
	else if(m_enumCurrentMediaType == QUICKTIME)
	{
		if(m_bQTVideoGood)
		{
			if(m_pQTPlayer)
			{
				if(m_enumCurrentPlayState == PAUSED)
				{
					m_pQTPlayer->Play();
					m_enumCurrentPlayState = PLAYING;
				}
				else
				{
					m_pQTPlayer->Pause();
					m_enumCurrentPlayState = PAUSED;
				}
				return true;
			}
		}
	}
/*	else if(m_enumCurrentMediaType == REAL_VIDEO)
	{
		if(m_bRealVideoGood)
		{
			if(m_pRealPlayer)
			{
				if(m_enumCurrentPlayState == PAUSED)
				{
					m_pRealPlayer->Play();
					m_enumCurrentPlayState = PLAYING;
				}
				else
				{
					m_pRealPlayer->Pause();
					m_enumCurrentPlayState = PAUSED;
				}
				return true;
			}
		}
	} */
	return false;
}

void CMyMediaPlayer::LowerVolume()
{
	TRY
	{
		DWORD vol;
		CVolumeControl volCtl;
		BOOL bOK = FALSE;
		bOK = volCtl.Open(GetSafeHwnd());
		if(bOK)
		{
			if (volCtl.GetCurrentVolume(&vol))
			{
				if(vol > VOLUME_ADJUST_AMOUNT)
					volCtl.SetVolume(vol-VOLUME_ADJUST_AMOUNT);
				else
					volCtl.SetVolume(0);
			}
			volCtl.Close();
		}
	}
	CATCH(CException,e)
	{
	}
	END_CATCH
}

void CMyMediaPlayer::IncreaseVolume()
{
	TRY
	{
		DWORD vol;
		CVolumeControl volCtl;
		BOOL bOK = FALSE;
		bOK = volCtl.Open(GetSafeHwnd());
		if(bOK)
		{
			if (volCtl.GetCurrentVolume(&vol))
				volCtl.SetVolume(vol+VOLUME_ADJUST_AMOUNT);
			volCtl.Close();
		}
	}
	CATCH(CException,e)
	{
	}
	END_CATCH
}

void CMyMediaPlayer::Mute()
{
	TRY
	{
		CVolumeControl volCtl;
		BOOL bOK = FALSE;
		bOK = volCtl.Open(GetSafeHwnd());

		if(!m_bMuted)
		{
			DWORD vol;
			volCtl.GetCurrentVolume(&vol);
			m_dwPrevVol = vol;
			m_bMuted = true;
			volCtl.SetVolume(0);
		}
		else
		{
			m_bMuted = false;
			volCtl.SetVolume(m_dwPrevVol);
		}
		volCtl.Close();
	}
	CATCH(CException,e)
	{
	}
	END_CATCH
}

void CMyMediaPlayer::OnReadyStateChangeMediaplayer1(long Result)
{
}

CString CMyMediaPlayer::GetCurrentPlayingInfo()
{
	if(m_enumCurrentPlayState == STOPPED || m_enumCurrentPlayState == LOADING)
		return "";
	
	CString strData;
	CString strFileName = m_strCurrentVideoPath;

	if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		if(m_bDXVideoGood)
		{
			DWORD dwPos = m_pDXVideoPlayer->GetCurrentPosition();
			strData.Format("<CurrentFile>%s</CurrentFile><CurrentPos>%u</CurrentPos>",
				strFileName,dwPos);
		}
	}
	else if(m_enumCurrentMediaType == QUICKTIME)
	{
		if(m_bQTVideoGood)
		{
			if(m_pQTPlayer)
			{
				DWORD dwPos = m_pQTPlayer->GetCurrentPosition();
				strData.Format("<CurrentFile>%s</CurrentFile><CurrentPos>%u</CurrentPos>",
							strFileName,dwPos);
			}
		}
	}
/*	else if(m_enumCurrentMediaType == REAL_VIDEO)
	{
		if(m_bRealVideoGood)
		{
			if(m_pRealPlayer)
			{
				DWORD dwPos = m_pRealPlayer->GetCurrentPosition();
				strData.Format("<CurrentFile>%s</CurrentFile><CurrentPos>%u</CurrentPos>",
							strFileName,dwPos);
			}
		}
	} */

	return strData;
}

LONGLONG CMyMediaPlayer::GetCurrentPosition()
{
	LONGLONG dwPos = 0;
	if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		if(m_bDXVideoGood)
		{
			dwPos = m_pDXVideoPlayer->GetCurrentPosition();			
		}
	}
	else if(m_enumCurrentMediaType == QUICKTIME)
	{
		if(m_bQTVideoGood)
		{
			if(m_pQTPlayer)
				dwPos = m_pQTPlayer->GetCurrentPosition();
		}
	}
/*	else if(m_enumCurrentMediaType == REAL_VIDEO)
	{
		if(m_bRealVideoGood)
		{
			if(m_pRealPlayer)
				dwPos = m_pRealPlayer->GetCurrentPosition();
		}
	} */
	return dwPos;
}

void CMyMediaPlayer::SetCurrentPosition(LONGLONG llPos)
{
	if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		if(m_bDXVideoGood)
		{
			m_pDXVideoPlayer->SetCurrentPosition(llPos);			
		}
	}
	else if(m_enumCurrentMediaType == QUICKTIME)
	{
		if(m_bQTVideoGood)
		{
			if(m_pQTPlayer)
				m_pQTPlayer->SetCurrentPosition(llPos);
		}
	}
/*	else if(m_enumCurrentMediaType == REAL_VIDEO)
	{
		if(m_bRealVideoGood)
		{
			if(m_pRealPlayer)
				m_pRealPlayer->SetCurrentPosition(llPos);
		}
	} */
}

CString CMyMediaPlayer::GetCurrentMediaName()
{
	return m_strCurrentVideoPath;	
}

void CMyMediaPlayer::SaveCurrentVolume()
{
	DWORD vol = 0;
	TRY
	{
		CVolumeControl volCtl;
		BOOL bOK = FALSE;
		bOK = volCtl.Open(GetSafeHwnd());
		if(bOK)
		{
			volCtl.GetCurrentVolume(&vol);
			volCtl.Close();
		}
	}
	CATCH(CException,e)
	{
	}
	END_CATCH

	AfxGetApp()->WriteProfileInt("Settings","LastVolume",vol);
}

void CMyMediaPlayer::Forward()
{
	if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		if(m_bDXVideoGood)
		{
			m_pDXVideoPlayer->Forward();			
		}
	}
	else if(m_enumCurrentMediaType == QUICKTIME)
	{
		if(m_bQTVideoGood)
		{
			if(m_pQTPlayer)
				m_pQTPlayer->Forward();
		}
	}
/*	else if(m_enumCurrentMediaType == REAL_VIDEO)
	{
		if(m_bRealVideoGood)
		{
			if(m_pRealPlayer)
				m_pRealPlayer->Forward();
		}
	} */
}

void CMyMediaPlayer::Rewind()
{
	if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		if(m_bDXVideoGood)
		{
			m_pDXVideoPlayer->Rewind();			
		}
	}
	else if(m_enumCurrentMediaType == QUICKTIME)
	{
		if(m_bQTVideoGood)
		{
			if(m_pQTPlayer)
				m_pQTPlayer->Rewind();
		}
	}
/*	else if(m_enumCurrentMediaType == REAL_VIDEO)
	{
		if(m_bRealVideoGood)
		{
			if(m_pRealPlayer)
				m_pRealPlayer->Rewind();
		}
	} */
}

void CMyMediaPlayer::SendCurrentMediaInfo()
{
	CString strTitle;
	CString strLength;
	CString strArtist;
	CString strBitrate;
	int nMins = 0;
	int nSecs = 0;
	DWORD dwLen = 0;

	if(m_enumCurrentMediaType == WMP_VIDEO && m_enumCurrentPlayState == PLAYING)
	{
		if(m_bDXVideoGood)
		{
			// format total time
			dwLen = m_pDXVideoPlayer->GetLengthInSecs();
			if(dwLen > 59)
				nMins = dwLen / 60;
			nSecs = dwLen - (nMins * 60);
			CString strLeadMin;
			CString strLeanSec;
			if(nMins < 10)
				strLeadMin = "0";
			if(nSecs < 10)
				strLeanSec = "0";
			strLength.Format("%s%d:%s%d",strLeadMin,nMins,strLeanSec,nSecs);
		}
	}
	else if(m_enumCurrentMediaType == QUICKTIME)
	{
		if(m_bQTVideoGood && m_pQTPlayer)
		{
			// format total time
			dwLen = m_pQTPlayer->GetLengthInSecs();
			if(dwLen > 59)
				nMins = dwLen / 60;
			nSecs = dwLen - (nMins * 60);
			CString strLeadMin;
			CString strLeanSec;
			if(nMins < 10)
				strLeadMin = "0";
			if(nSecs < 10)
				strLeanSec = "0";
			strLength.Format("%s%d:%s%d",strLeadMin,nMins,strLeanSec,nSecs);
		}
	}
/*	else if(m_enumCurrentMediaType == REAL_VIDEO)
	{
		if(m_bRealVideoGood && m_pRealPlayer)
		{
			// format total time
			dwLen = m_pRealPlayer->GetLengthInSecs();
			if(dwLen > 59)
				nMins = dwLen / 60;
			nSecs = dwLen - (nMins * 60);
			CString strLeadMin;
			CString strLeanSec;
			if(nMins < 10)
				strLeadMin = "0";
			if(nSecs < 10)
				strLeanSec = "0";
			strLength.Format("%s%d:%s%d",strLeadMin,nMins,strLeanSec,nSecs);
		}
	} */

	CString strMsg;
	strMsg.Format("<Message>CurrentMediaInfo</Message><MediaTitle>%s</MediaTitle><MediaLength>%s</MediaLength><MediaArtist>%s</MediaArtist><MediaBitrate>%s</MediaBitrate><MediaLenSecs>%u</MediaLenSecs>"
		,strTitle,strLength,strArtist,strBitrate,dwLen);
	SendMessageToPlayListOcx(strMsg);
}

void CMyMediaPlayer::OnTimer(UINT nIDEvent)
{
	if(ID_UPDATE_PLAY_POS == nIDEvent)
	{
		SendCurrentPlayPos();	
	}
	CWnd::OnTimer(nIDEvent);	
}

void CMyMediaPlayer::SendCurrentPlayPos()
{
	int nMins = 0;
	int nSecs = 0;
	DWORD dwPos = 0;
	LONGLONG llPos = 0;
	if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		if(m_bDXVideoGood)
		{
			llPos = m_pDXVideoPlayer->GetCurrentPosition();
		}
	}
	else if(m_enumCurrentMediaType == QUICKTIME)
	{
		if(m_bQTVideoGood && m_pQTPlayer)
		{
			llPos = m_pQTPlayer->GetCurrentPosition();
		}
	}
/*	else if(m_enumCurrentMediaType == REAL_VIDEO)
	{
		if(m_bRealVideoGood && m_pRealPlayer)
		{
			llPos = m_pRealPlayer->GetCurrentPosition();
		}
	} */
	dwPos = llPos / (LONGLONG)10000000;
	if(dwPos > 59)
		nMins = dwPos / 60;
	nSecs = dwPos - (nMins * 60);	

	if(m_lLastPlayPos == llPos && m_enumCurrentPlayState == PLAYING)
	{
		DWORD dwLen = 0;
		if(m_enumCurrentMediaType == WMP_VIDEO)
		{
			dwLen = m_pDXVideoPlayer->GetLengthInSecs();
		}
		else if(m_enumCurrentMediaType == QUICKTIME)
		{
			dwLen = m_pQTPlayer->GetLengthInSecs();
			dwPos += 1;
		}
/*		else if(m_enumCurrentMediaType == REAL_VIDEO)
		{
			dwLen = m_pRealPlayer->GetLengthInSecs();
		} */

		if(dwLen <= dwPos)
		{
			OnEndOfStreamMediaplayer1(1);
			return;
		}
	}
	m_lLastPlayPos = llPos;
	m_pMainWnd->m_SeekWnd.UpdatePosition(dwPos);

	CString strLeadMin;
	CString strLeanSec;
	if(nMins < 10)
		strLeadMin = "0";
	if(nSecs < 10)
		strLeanSec = "0";

	CString strMsg;
	strMsg.Format("<Message>UpdatePlayPosition</Message><CurrentMediaPosition>%s%d:%s%d</CurrentMediaPosition><CurrentMediaPosSecs>%u</CurrentMediaPosSecs>",strLeadMin,nMins,strLeanSec,nSecs,dwPos);
	SendMessageToPlayListOcx(strMsg);
}

void CMyMediaPlayer::SetZeroTimePlayed()
{
	KillTimer(m_TimerPlayPos);

	m_pMainWnd->m_SeekWnd.UpdatePosition(0);

	CString strMsg = "<Message>UpdatePlayPosition</Message><CurrentMediaPosition></CurrentMediaPosition>CurrentMediaPosSecs></CurrentMediaPosSecs";
	SendMessageToPlayListOcx(strMsg);

	strMsg = "<Message>CurrentMediaInfo</Message><MediaTitle></MediaTitle><MediaLength></MediaLength><MediaArtist></MediaArtist><MediaBitrate></MediaBitrate>";
	SendMessageToPlayListOcx(strMsg);
}

DWORD CMyMediaPlayer::GetLengthInSecs()
{
	DWORD dwLen = 0;
	if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		if(m_bDXVideoGood)
		{
			dwLen = m_pDXVideoPlayer->GetLengthInSecs();
		}
	}
	else if(m_enumCurrentMediaType == QUICKTIME)
	{
		if(m_bQTVideoGood && m_pQTPlayer)
		{
			dwLen = m_pQTPlayer->GetLengthInSecs();
		}
	}
/*	else if(m_enumCurrentMediaType == REAL_VIDEO)
	{
		if(m_bRealVideoGood && m_pRealPlayer)
		{
			dwLen = m_pRealPlayer->GetLengthInSecs();
		}
	} */
	return dwLen;
}

void CMyMediaPlayer::OnPaint() 
{
	CPaintDC dc(this); 
	CRect rect;
	GetClientRect(rect);

	CBrush brBkGnd;
	brBkGnd.CreateSolidBrush(0x000000);
	dc.FillRect(rect,&brBkGnd);

	if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		if(m_bDXVideoGood)
			m_pDXVideoPlayer->InvalidateRect(NULL);
	}
	else if(m_enumCurrentMediaType == QUICKTIME)
	{
		if(m_bQTVideoGood && m_pQTPlayer)
		{
			m_pQTPlayer->InvalidateRect(NULL);
		}
	} 
/*	else if(m_enumCurrentMediaType == REAL_VIDEO)
	{
		if(m_bRealVideoGood && m_pRealPlayer)
		{
			if(IsWindow(m_pRealPlayer->m_hWnd))
				m_pRealPlayer->InvalidateRect(NULL);
		}
	} */
}

void CMyMediaPlayer::Stop()
{
	if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		if(m_bDXVideoGood)
		{
			if(m_bIsInFullScreen)
			{
				m_wndFullScreen.ShowWindow(SW_HIDE);
				ShowTaskBar(true);

				if(m_pDXVideoPlayer->m_pVideoWindow)
					m_pDXVideoPlayer->m_pVideoWindow->put_FullScreenMode(OAFALSE);
				m_bIsInFullScreen = false;
			}

			m_pDXVideoPlayer->Stop();
			m_enumCurrentPlayState = STOPPED;
		}
	}
	else if(m_enumCurrentMediaType == QUICKTIME)
	{
		if(m_bQTVideoGood)
		{
			if(m_bIsInFullScreen)
			{
				m_wndFullScreen.ShowWindow(SW_HIDE);
				ShowTaskBar(true);

				if(m_pQTPlayer)
					m_pQTPlayer->FullScreen(false);
				m_bIsInFullScreen = false;
			}
			if(m_pQTPlayer)
				m_pQTPlayer->Stop();
			m_enumCurrentPlayState = STOPPED;

			m_bQTVideoGood = false;
			if(m_pQTPlayer)
			{
				delete m_pQTPlayer;
				m_pQTPlayer = NULL;
			}
		}
	}
/*	else if(m_enumCurrentMediaType == REAL_VIDEO)
	{
		if(m_bRealVideoGood)
		{
			if(m_bIsInFullScreen)
			{
				m_wndFullScreen.ShowWindow(SW_HIDE);
				ShowTaskBar(true);

				if(m_pRealPlayer)
					m_pRealPlayer->FullScreen(false);
				m_bIsInFullScreen = false;
			}
			if(m_pRealPlayer)
				m_pRealPlayer->Stop();
			m_enumCurrentPlayState = STOPPED;

			m_bRealVideoGood = false;
			if(m_pRealPlayer)
			{
				delete m_pRealPlayer;
				m_pRealPlayer = NULL;
			}
		}
	} */
	SetZeroTimePlayed();

	CString strMsg;
	strMsg.Format("<Message>SetNormalIcon</Message><POS>%d</POS>",-1);
	SendMessageToPlayListOcx(strMsg);
}

void CMyMediaPlayer::FullScreen()
{
	ShowCursor(false);

	if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		if(m_bDXVideoGood)
		{
			m_wndFullScreen.ShowWindow(SW_SHOW);
			ShowTaskBar(false);

			m_pDXVideoPlayer->FullScreen();	
			m_bIsInFullScreen = true;
		}
	}
	else if(m_enumCurrentMediaType == QUICKTIME)
	{
		if(m_bQTVideoGood)
		{
			if(m_pQTPlayer)
				m_pQTPlayer->FullScreen();
			m_bIsInFullScreen = true;
		}
	}
/*	else if(m_enumCurrentMediaType == REAL_VIDEO)
	{
		if(m_bRealVideoGood)
		{
			m_wndFullScreen.ShowWindow(SW_SHOW);
			ShowTaskBar(false);

			m_pRealPlayer->FullScreen();	
			m_bIsInFullScreen = true;
		}
	} */
}

BOOL CMyMediaPlayer::Play()
{
	if(m_enumCurrentPlayState == PLAYING)
		return true;
	if(m_enumCurrentPlayState == PAUSED)
	{
		Pause();
		return true;
	}

	KillTimer(m_TimerPlayPos);

	CString strFileName = m_strCurrentVideoPath;
	m_enumCurrentMediaType = GetMediaFileType(strFileName);	

	if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		if(m_bDXVideoGood)
		{
			m_pDXVideoPlayer->SetFileName(strFileName);
			m_pDXVideoPlayer->Play();
			m_enumCurrentPlayState = PLAYING;

			CRect rect;
			GetClientRect(rect);
			m_pDXVideoPlayer->MoveWindow(rect);


			if(m_bIsInFullScreen)
				FullScreen();

			SendCurrentMediaInfo();
			// set timer for update position
			m_TimerPlayPos = SetTimer(ID_UPDATE_PLAY_POS,1000,NULL);
		}
		else
		{
			// SetMessageBoxLink(WMP installer link);
			//MyMessageBox("Error you cannot play this media type, make sure you have Windows Media Player installed");
		}
		m_pMainWnd->m_SeekWnd.Init();
	}
/*	else if(m_enumCurrentMediaType == REAL_VIDEO)
	{
		if(!m_bRealVideoGood)
		{
			if(!m_pRealPlayer)
				m_pRealPlayer = new CMyRealAudio();
			m_pRealPlayer->m_pMain = this;
			m_bRealVideoGood = m_pRealPlayer->Create(this);
			if(!m_bRealVideoGood)
			{
				// SetMessageBoxLink(Real installer link);
				//MyMessageBox("Error you cannot play this media type, make sure you have Real Player installed");
				AfxMessageBox("Error failed to create real player window, make sure you have Real Player installed");
				return false;
			}
		}
		m_pRealPlayer->SetFileName(strFileName);
		m_pRealPlayer->Play();
		m_enumCurrentPlayState = PLAYING;

		CRect rect;
		GetClientRect(rect);
		m_pRealPlayer->MoveWindow(rect);

		if(m_bIsInFullScreen)
		{
			FullScreen();
			m_wndFullScreen.ShowWindow(SW_HIDE);
		}

		SendCurrentMediaInfo();
		// set timer for update position
		m_TimerPlayPos = SetTimer(ID_UPDATE_PLAY_POS,1000,NULL);

		m_pMainWnd->m_SeekWnd.Init();
	} */
	else if(m_enumCurrentMediaType == QUICKTIME)
	{
		if(!m_bQTVideoGood)
		{
			if(!m_pQTPlayer)
				m_pQTPlayer = new CMyQuickTimeWnd();
			m_pQTPlayer->m_pMain = this;
			m_bQTVideoGood = m_pQTPlayer->Create(NULL,"Quicktime",WS_CHILD,CRect(0,0,0,0),this,ID_QUICKTIME);
			if(!m_bQTVideoGood)
			{
				// SetMessageBoxLink(Real installer link);
				//MyMessageBox("Error you cannot play this media type, make sure you have Real Player installed");
				AfxMessageBox("Error failed to create real player window, make sure you have Real Player installed");
				return false;
			}
		}
		m_pQTPlayer->SetFileName(strFileName);
		m_pQTPlayer->Play();
		m_enumCurrentPlayState = PLAYING;

		CRect rect;
		GetClientRect(rect);
		m_pQTPlayer->MoveWindow(rect);

		if(m_bIsInFullScreen)
		{
			FullScreen();
			m_wndFullScreen.ShowWindow(SW_HIDE);
		}

		SendCurrentMediaInfo();
		// set timer for update position
		m_TimerPlayPos = SetTimer(ID_UPDATE_PLAY_POS,1000,NULL);

		m_pMainWnd->m_SeekWnd.Init();
	}
	return true;
}

// quicktime message end fullscreen
long CMyMediaPlayer::OnEndFullScreen(UINT wParam,LPARAM lparam)
{
	if(!m_bIsInFullScreen || !m_pQTPlayer || !m_pQTPlayer->m_RestoreState)
		return 0;
	// get file pos
	LONGLONG llPos = m_pQTPlayer->GetCurrentPosition();

	OSErr myErr = EndFullScreen(m_pQTPlayer->m_RestoreState, 0L); 
	m_pQTPlayer->m_RestoreState = NULL;

	m_bIsInFullScreen = false;
	Stop();

	m_bQTVideoGood = false;
	if(m_pQTPlayer)
	{
		delete m_pQTPlayer;
		m_pQTPlayer = NULL;
	}

	Play();
	// set file pos
	if(m_pQTPlayer)
		m_pQTPlayer->SetCurrentPosition(llPos);

	CRect rect;
	GetClientRect(rect);
	ClientToScreen(rect);
	SetCursorPos(rect.Width()/2,rect.Height()/2);
	ShowCursor(true);

	m_pMainWnd->InvalidateRect(NULL);

	return 1;
}

void CMyMediaPlayer::OnEndOfStreamMediaplayer1(long Result) 
{
	m_enumCurrentPlayState = STOPPED;

	if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		if(m_bIsInFullScreen)
			ShowCursor(true);

		if(m_bDXVideoGood)
			m_pDXVideoPlayer->ShowWindow(SW_HIDE);
	}
/*	else if(m_enumCurrentMediaType == REAL_VIDEO)
	{
		if(m_bIsInFullScreen)
		{
			m_wndFullScreen.ShowWindow(SW_SHOW);
			if(m_pRealPlayer)
				m_pRealPlayer->FullScreen(false);
		}
		if(m_pRealPlayer)
			m_pRealPlayer->Stop();
		m_enumCurrentPlayState = STOPPED;

		m_bRealVideoGood = false;
		if(m_pRealPlayer)
		{
			delete m_pRealPlayer;
			m_pRealPlayer = NULL;
		}
	} */
	else if(m_enumCurrentMediaType == QUICKTIME)
	{
		if(m_bIsInFullScreen)
		{
			ShowCursor(true);

			m_wndFullScreen.ShowWindow(SW_SHOW);
			if(m_pQTPlayer)
				m_pQTPlayer->FullScreen(false);
		}
		if(m_pQTPlayer)
			m_pQTPlayer->Stop();
		m_enumCurrentPlayState = STOPPED;

		m_bQTVideoGood = false;
		if(m_pQTPlayer)
		{
			delete m_pQTPlayer;
			m_pQTPlayer = NULL;
		}
	}
	SetZeroTimePlayed();
	SendMessageToInstanseOfApp("<Message>EndofstreamMediaPlayer</Message>");
}


