// MyMediaPlayer.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "mainfrm.h"
#include "MyDirectXPlayer.h"
#include "MyMediaPlayer.h"
#include "helpers.h"
#include "VolumeControl.h"
#include "PlayListManager.h"
#include "MyIEWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyMediaPlayer

CMyMediaPlayer::CMyMediaPlayer()
{
	m_nCurrentMediaPos = 0;
	m_enumCurrentMediaType = NONE;
	m_enumCurrentPlayState = STOPPED;
	m_pDXAudioPlayer = NULL;
	m_bDXAudioGood = false;
	m_bMP3AudioGood = false;
	m_bMuted = false;
	m_dwPrevVol = 0;
	m_pMainWnd = NULL;
	m_TimerPlayPos = 0;
	m_lLastPlayPos = 0;
	m_bLastWasVideo = false;
}

CMyMediaPlayer::~CMyMediaPlayer()
{
	if(m_pDXAudioPlayer)
	{
		delete m_pDXAudioPlayer;
		m_pDXAudioPlayer = NULL;
	}
}


BEGIN_MESSAGE_MAP(CMyMediaPlayer, CWnd)
	//{{AFX_MSG_MAP(CMyMediaPlayer)
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyMediaPlayer message handlers

int CMyMediaPlayer::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pDXAudioPlayer = new CMyDirectXPlayer(); 
	m_pDXAudioPlayer->m_pMain = this;
	m_bDXAudioGood = m_pDXAudioPlayer->Create(NULL,"MediaDX",WS_CHILD,CRect(0,0,0,0),this,ID_MEDIA_PLAYER_64);
	
	return 0;
}

void CMyMediaPlayer::SetPlayList(CStringArray *pStra)
{
	m_straPlayList.RemoveAll();
	for(int n=0;n<pStra->GetSize();n++)
		m_straPlayList.Add(pStra->GetAt(n));
	delete pStra;
	m_nCurrentMediaPos = 0;
}

BOOL CMyMediaPlayer::Play()
{
	if(m_enumCurrentPlayState == PLAYING)
		return true;
	if(m_enumCurrentPlayState == PAUSED)
	{
		Pause();
		SetPlayingIcon(m_nCurrentMediaPos);
		return true;
	}

	KillTimer(m_TimerPlayPos);

	if(m_straPlayList.GetSize() == 0)
		return false;

	CString strFileName;
	strFileName = ParseXML("FullPath",m_straPlayList.GetAt(m_nCurrentMediaPos));
	SECFileSystem fs;
	// file is missing so delete it
	if(!fs.FileExists(strFileName))
	{
		m_straPlayList.RemoveAt(m_nCurrentMediaPos);
		CPlayListManager list;
		list.SaveCurrent(&m_straPlayList,"");

		m_pMainWnd->m_TimerAddToPlayList = m_pMainWnd->SetTimer(ID_TIMER_SEND_FILELIST_TO_PLAYLIST,100,NULL);

		OnEndOfStreamMediaplayer1(1);
		return false;
	}

	m_enumCurrentMediaType = GetMediaFileType(strFileName);	

	if(m_enumCurrentMediaType == WMP_AUDIO)
	{
		if(m_bDXAudioGood)
		{
			m_pDXAudioPlayer->SetFileName(strFileName);
			m_pDXAudioPlayer->Play();
			m_enumCurrentPlayState = PLAYING;
		
			m_strTitle = GetTitle();
			m_strArtist = GetArtist();
			m_strBitrate = GetBitrate();

			SendCurrentMediaInfo();
			// set timer for update position
			m_TimerPlayPos = SetTimer(ID_UPDATE_PLAY_POS,1000,NULL);
		}
		else
		{
			// SetMessageBoxLink(WMP installer link);
			//MyMessageBox("Error you cannot play this media type, make sure you have Windows Media Player installed");
		}
	}
	else if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		CString strFile;
		strFile.Format("<Message>SetCurrentFilePath</Message><FullPath>%s</FullPath>",GetCurrentMediaName());
		if(!SendMessageToPlayerOcx(strFile))
		{
			m_enumCurrentPlayState = PLAYING;
			m_pMainWnd->PostMessage(WM_PRE_LOAD_PLAYER);			
		}
		else if(m_pMainWnd->m_pIEPlayer)	
		{
			BOOL bHidePlayerWindow = (AfxGetApp()->GetProfileInt("Settings","HideVideoWindow",0) == 1);
			if(bHidePlayerWindow)
			{
				m_pMainWnd->m_pIEPlayer->ShowWindow(SW_HIDE);
			}
			else if(!m_bLastWasVideo)
			{
				m_pMainWnd->m_pIEPlayer->ShowWindow(SW_SHOW);
				BumpWindow(m_pMainWnd->m_pIEPlayer);
				m_pMainWnd->m_TimerNoTopMost = m_pMainWnd->SetTimer(ID_NO_TOP_MOST,100,NULL);
			}
			m_enumCurrentPlayState = PLAYING;
		}
	}

	SetPlayingIcon(m_nCurrentMediaPos);

	return true;
}

void CMyMediaPlayer::Stop()
{
	if(m_enumCurrentMediaType == WMP_AUDIO)
	{
		if(m_bDXAudioGood)
		{
			m_pDXAudioPlayer->Stop();
			m_enumCurrentPlayState = STOPPED;
		}
	}
	else if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		SendMessageToPlayerOcx("<Message>Stop</Message>");	
		m_enumCurrentPlayState = STOPPED;
	}
	SetNormalIcon(m_nCurrentMediaPos);
	SetZeroTimePlayed();
}

BOOL CMyMediaPlayer::Pause()
{
	if(m_enumCurrentMediaType == WMP_AUDIO)
	{
		if(m_bDXAudioGood)
		{
			if(m_enumCurrentPlayState == PAUSED)
			{
				m_pDXAudioPlayer->Play();
				m_enumCurrentPlayState = PLAYING;
			}
			else
			{
				m_pDXAudioPlayer->Pause();
				m_enumCurrentPlayState = PAUSED;
			}
			return true;
		}
	}
	else if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		SendMessageToPlayerOcx("<Message>Pause</Message>");	
		m_enumCurrentPlayState = PAUSED;
	}
	return true;
}

void CMyMediaPlayer::LowerVolume(DWORD volLowerAmount)
{
	DWORD dwAmount = volLowerAmount;
	if(dwAmount == 0)
		dwAmount = VOLUME_ADJUST_AMOUNT;
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
				if(vol > dwAmount)
					volCtl.SetVolume(vol-dwAmount);
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

void CMyMediaPlayer::OnEndOfStreamMediaplayer1(long Result) 
{
	m_enumCurrentPlayState = STOPPED;
	SetNormalIcon(m_nCurrentMediaPos);
	SetZeroTimePlayed();

	int nListSize = 0;
	nListSize= m_straPlayList.GetSize();
	
	BOOL bRepeatOn = (AfxGetApp()->GetProfileInt("Settings","Repeat",1) == 1);

	if((m_nCurrentMediaPos + 1) < nListSize)
	{
		m_nCurrentMediaPos ++;
		Play();
	}
	else if(m_pMainWnd->m_bShutoffAfterPlayList)
	{
		m_pMainWnd->m_TimerShutDown = m_pMainWnd->SetTimer(ID_TIMER_SHUTDOWN,1000,NULL); 
	}
	else if(bRepeatOn)
	{
		m_nCurrentMediaPos = 0;
		Play();
	}
}

void CMyMediaPlayer::OnReadyStateChangeMediaplayer1(long Result)
{
}

CString CMyMediaPlayer::GetCurrentPlayingInfo()
{
	if(m_enumCurrentPlayState == STOPPED || m_enumCurrentPlayState == LOADING)
		return "";
	
	if(m_nCurrentMediaPos > m_straPlayList.GetSize())
		return "";
	CString strData;
	CString strFileName = ParseXML("FullPath",m_straPlayList.GetAt(m_nCurrentMediaPos));

	if(m_enumCurrentMediaType == WMP_AUDIO)
	{
		if(m_bDXAudioGood)
		{
			LONGLONG dwPos = m_pDXAudioPlayer->GetCurrentPosition();
			strData.Format("<CurrentFile>%s</CurrentFile><CurrentPos>%u</CurrentPos>",
				strFileName,dwPos);
		}
	}
	else if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		strData.Format("<CurrentFile>%s</CurrentFile>",strFileName);
	}
	return strData;
}

void CMyMediaPlayer::SetCurrentPosition(LONGLONG llPos)
{
	if(m_enumCurrentMediaType == WMP_AUDIO)
	{
		if(m_bDXAudioGood)
		{
			m_pDXAudioPlayer->SetCurrentPosition(llPos);			
		}
	}
	else if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		CString strMsg;
		DWORD dwPos = llPos / (LONGLONG)10000000;
		strMsg.Format("<Message>SetCurrentPosition</Message><Position>%u</Position>",dwPos);
		SendMessageToPlayerOcx(strMsg);	
	}
}

CString CMyMediaPlayer::GetCurrentMediaName()
{
	if(m_straPlayList.GetSize() > m_nCurrentMediaPos)
		return ParseXML("FullPath",m_straPlayList.GetAt(m_nCurrentMediaPos));
	else
		return "";
}

void CMyMediaPlayer::SetCurrentMediaName(CString strName)
{
	if(strName.IsEmpty())
		return;

	for(int n=0;n<m_straPlayList.GetSize();n++)
	{
		CString strTest = m_straPlayList.GetAt(n);
		if(strName == strTest)
		{
			m_nCurrentMediaPos = n;
			return;
		}
	}
}

void CMyMediaPlayer::SetNormalIcon(DWORD nPos)
{
	CString strMsg;
	strMsg.Format("<Message>SetNormalIcon</Message><POS>%u</POS>",nPos);
	SendMessageToPlayListOcx(strMsg);
}

void CMyMediaPlayer::SetPlayingIcon(DWORD nPos,BOOL bSelect)
{
	CString strMsg;
	if(bSelect)
		strMsg.Format("<Message>SetPlayingIcon</Message><POS>%u</POS><Select>TRUE</Select>",nPos);
	else
		strMsg.Format("<Message>SetPlayingIcon</Message><POS>%u</POS><Select>FALSE</Select>",nPos);

	SendMessageToPlayListOcx(strMsg);
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

void CMyMediaPlayer::Next()
{
	Stop();
	if((m_nCurrentMediaPos + 1) < m_straPlayList.GetSize())
	{
		m_nCurrentMediaPos ++;
		Play();
	}
	else
	{
		m_nCurrentMediaPos = 0;
		Play();
	}
}

void CMyMediaPlayer::Previous()
{
	Stop();
	if((m_nCurrentMediaPos - 1) < 0)
	{
		m_nCurrentMediaPos = m_straPlayList.GetSize() -1;
		Play();
	}
	else
	{
		m_nCurrentMediaPos --;
		Play();
	}
}

CString CMyMediaPlayer::GetCurrentFileListXML()
{
	CString strCurrentPlayInfo = GetCurrentPlayingInfo();
	CString strData = "<Message>CurrentFileListXML</Message>" + strCurrentPlayInfo;
	for(int n=0;n<m_straPlayList.GetSize();n++)
	{
		strData += "<PlayListEntry>" + m_straPlayList.GetAt(n) + "</PlayListEntry>";
	}
	return strData;
}

BOOL CMyMediaPlayer::IsPlayingVideo()
{
	return (m_enumCurrentMediaType == WMP_VIDEO && m_enumCurrentPlayState == PLAYING);
}

void CMyMediaPlayer::Rewind()
{
	if(m_enumCurrentMediaType == WMP_AUDIO)
	{
		if(m_bDXAudioGood)
		{
			m_pDXAudioPlayer->Rewind();			
		}
	}
	else if(m_enumCurrentMediaType == WMP_VIDEO)
	{
		SendMessageToPlayerOcx("<Message>Rewind</Message>");	
	}
}

void CMyMediaPlayer::Forward()
{
	if(m_enumCurrentMediaType == WMP_AUDIO)
	{
		if(m_bDXAudioGood)
		{
			m_pDXAudioPlayer->Forward();			
		}
	}
	else if(m_enumCurrentMediaType == WMP_VIDEO )
	{
		SendMessageToPlayerOcx("<Message>Forward</Message>");	
	}
}

void CMyMediaPlayer::SetZeroTimePlayed()
{
	KillTimer(m_TimerPlayPos);

	CString strMsg = "<Message>UpdatePlayPosition</Message><CurrentMediaPosition></CurrentMediaPosition><CurrentMediaPosSecs></CurrentMediaPosSecs>";
	SendMessageToPlayListOcx(strMsg);

	strMsg = "<Message>CurrentMediaInfo</Message><MediaTitle></MediaTitle><MediaLength></MediaLength><MediaArtist></MediaArtist><MediaBitrate></MediaBitrate>";
	SendMessageToPlayListOcx(strMsg);
}

void CMyMediaPlayer::SendCurrentPlayPos()
{
	int nMins = 0;
	int nSecs = 0;
	DWORD dwPos = 0;
	if(m_enumCurrentMediaType == WMP_AUDIO)
	{
		if(m_bDXAudioGood)
		{
			LONGLONG llPos = m_pDXAudioPlayer->GetCurrentPosition();
			dwPos = llPos / (LONGLONG)10000000;
			if(dwPos > 59)
				nMins = dwPos / 60;
			nSecs = dwPos - (nMins * 60);	

			if(m_lLastPlayPos == llPos && m_enumCurrentPlayState == PLAYING)
			{
				if(m_pDXAudioPlayer->GetLengthInSecs() == dwPos)
				{
					Stop();
					OnEndOfStreamMediaplayer1(1);
					return;
				}
			}
			m_lLastPlayPos = llPos;
		}
	}
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

void CMyMediaPlayer::OnTimer(UINT nIDEvent)
{
	if(ID_UPDATE_PLAY_POS == nIDEvent)
	{
		SendCurrentPlayPos();	
	}

	CWnd::OnTimer(nIDEvent);	
}

void CMyMediaPlayer::SendCurrentMediaInfo()
{
	int nMins = 0;
	int nSecs = 0;
	DWORD dwLen = 0;
	CString strLength;
	if(m_enumCurrentMediaType == WMP_AUDIO && m_enumCurrentPlayState == PLAYING)
	{
		if(m_bDXAudioGood)
		{
			// format total time
			dwLen = m_pDXAudioPlayer->GetLengthInSecs();
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
	else if(m_enumCurrentMediaType == WMP_VIDEO && m_enumCurrentPlayState == PLAYING)
	{
		SendMessageToPlayerOcx("<Message>SendPlayingInfo</Message>");
		return;
	}

	CString strMsg;
	strMsg.Format("<Message>CurrentMediaInfo</Message><MediaTitle>%s</MediaTitle><MediaLength>%s</MediaLength><MediaArtist>%s</MediaArtist><MediaBitrate>%s</MediaBitrate><MediaLenSecs>%u</MediaLenSecs>"
		,m_strTitle,strLength,m_strArtist,m_strBitrate,dwLen);
	SendMessageToPlayListOcx(strMsg);
}

DWORD CMyMediaPlayer::GetLowerVolumeVal(DWORD dwLowerIntervals)
{
	DWORD dwIntervalAmt = 0;
	DWORD dwCurrent = 0;

	CVolumeControl volCtl;
	BOOL bOK = FALSE;
	bOK = volCtl.Open(GetSafeHwnd());
	if(bOK)
	{
		volCtl.GetCurrentVolume(&dwCurrent);
		volCtl.Close();
	}
	if(dwLowerIntervals > 0)
	{
		dwCurrent -= (dwCurrent / 100 * 10);
		dwIntervalAmt = dwCurrent / dwLowerIntervals;

		if(dwIntervalAmt == 0)
			dwIntervalAmt = 500;
	}
	return dwIntervalAmt;
}

void CMyMediaPlayer::LowerVolumeWave(DWORD volLowerAmount)
{
	DWORD dwAmount = volLowerAmount;
	if(dwAmount == 0)
		dwAmount = VOLUME_ADJUST_AMOUNT_WAVE;
	TRY
	{
		CVolumeControl volCtl;
		DWORD vol = volCtl.WaveGetVolume();
		if(vol > dwAmount)
			volCtl.WaveSetVolume(vol-dwAmount);
		else
			volCtl.WaveSetVolume(0);
	}
	CATCH(CException,e)
	{
	}
	END_CATCH
}

void CMyMediaPlayer::IncreaseVolumeWave()
{
	TRY
	{		
		CVolumeControl volCtl;
		DWORD vol = volCtl.WaveGetVolume();
			volCtl.WaveSetVolume(vol+VOLUME_ADJUST_AMOUNT_WAVE);
	}
	CATCH(CException,e)
	{
	}
	END_CATCH
}

CString CMyMediaPlayer::GetTitle()
{
	if(m_bDXAudioGood)
	{
		return m_pDXAudioPlayer->GetTitle();
	}
	return "";
}

CString CMyMediaPlayer::GetArtist()
{
	if(m_bDXAudioGood)
	{
		return m_pDXAudioPlayer->GetArtist();
	}
	return "";
}

CString CMyMediaPlayer::GetBitrate()
{
	if(m_bDXAudioGood)
	{
		return m_pDXAudioPlayer->GetBitrate();
	}
	return "";
}
