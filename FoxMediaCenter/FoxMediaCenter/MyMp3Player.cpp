// MyMp3Player.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "MyMediaPlayer.h"
#include "MyMp3Player.h"
#include "defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyMp3Player

CMyMp3Player::CMyMp3Player()
{
	m_pMain = NULL;

}

CMyMp3Player::~CMyMp3Player()
{
}


BEGIN_MESSAGE_MAP(CMyMp3Player, CWnd)
	//{{AFX_MSG_MAP(CMyMp3Player)
	ON_WM_TIMER()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CMyMp3Player::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CMyMp3Player::SetFileName(CString strFileName)
{

}

void CMyMp3Player::Play()
{

}

void CMyMp3Player::Stop()
{

}

void CMyMp3Player::Pause()
{
}

LONGLONG CMyMp3Player::GetCurrentPosition()
{
	DWORD llPos = 0;

	return llPos;
}

void CMyMp3Player::SetCurrentPosition(LONGLONG dwPos)
{
}

void CMyMp3Player::Rewind()
{
}

LONGLONG CMyMp3Player::GetDuration()
{
	DWORD llFrames = 0;
	return llFrames;
}

void CMyMp3Player::Forward()
{
}

long CMyMp3Player::GetLengthInSecs()
{
	DWORD llLen = 0;
	return llLen;
}

void CMyMp3Player::OnTimer(UINT nIDEvent) 
{

	
	CWnd::OnTimer(nIDEvent);
}

