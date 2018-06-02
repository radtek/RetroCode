// MyRealAudio1.cpp: implementation of the CMyRealAudio class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SteveMediaPlayer.h"
#include "MyRealAudio1.h"
#include "helpers.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyRealAudio::CMyRealAudio()
{
	m_pReal = NULL;
}

CMyRealAudio::~CMyRealAudio()
{
	if(m_pReal)
	{
		delete m_pReal;
		m_pReal = NULL;
	} 
}

BEGIN_MESSAGE_MAP(CMyRealAudio, CWnd)
	//{{AFX_MSG_MAP(CMyRealAudio)
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMyRealAudio::Create(CWnd* pParent)
{
	CRect rect;
	pParent->GetClientRect(rect);

	if(m_pReal)
	{
		delete m_pReal;
		m_pReal = NULL;
	}
	m_pReal = new CRealAudio();

	BOOL bOK = CWnd::Create(NULL,"RealParentPlayer",WS_CHILD,rect,pParent,ID_REAL_PLAYER_PARENT);
	bOK = m_pReal->Create("","G2Player",WS_CHILD,CRect(0,0,0,0),pParent,4027);
	
	if(bOK)
	{
		CString strVersion = m_pReal->GetVersionInfo();
		int nVer = atoi(strVersion);
		if(nVer < 6)
			return false;
	}
	return bOK;
}

BOOL CMyRealAudio::SetFileName(CString strFilePath)
{
	if(strFilePath.Left(strlen("file://")) != "file://")
		strFilePath = "file://" + strFilePath;
	
	m_pReal->SetSource(strFilePath);

	m_pReal->SetWindowName("Real");
	m_pReal->SetEnableOriginalSize(true);
	m_pReal->SetOriginalSize();
	m_pReal->SetEnableContextMenu(false);
	m_pReal->SetWantMouseEvents(false);
	m_pReal->SetImageStatus(true);

	m_pReal->SetMaintainAspect(true);
	
	m_pReal->SetControls("ImageWindow");
	m_pReal->SetNoLogo(false);
	m_pReal->SetAutoStart(false);

	return true;
}

void CMyRealAudio::Play()
{
	ShowWindow(SW_SHOW);
	m_pReal->DoPlay();

	InvalidateRect(NULL);
}

void CMyRealAudio::Pause()
{
	m_pReal->DoPause();
}

void CMyRealAudio::Stop()
{
	ShowWindow(SW_HIDE);
	m_pReal->DoStop();
	m_pReal->SetSource("");
}

void CMyRealAudio::FullScreen(BOOL bMakeFull)
{
	if(bMakeFull)
		m_pReal->SetFullScreen();
	else
		m_pReal->SetOriginalSize();
}

void CMyRealAudio::Rewind()
{
	LONGLONG dwPos = GetCurrentPosition();
	dwPos -= 20 * (LONGLONG)10000000;
	if(dwPos < 0)
		dwPos = 0;
	SetCurrentPosition(dwPos);
}

void CMyRealAudio::Forward()
{
	LONGLONG llDur = m_pReal->GetLength();
	llDur = llDur * (LONGLONG)10000000;
	LONGLONG llPos = GetCurrentPosition();
	llPos += 20 * (LONGLONG)10000000;
	if(llPos > llDur)
		llPos = llDur - 1;
	SetCurrentPosition(llPos);
}

void CMyRealAudio::SetCurrentPosition(LONGLONG llPos)
{
	long lPos = llPos / (LONGLONG)10000000;
	m_pReal->SetPosition(lPos);
}

LONGLONG CMyRealAudio::GetCurrentPosition()
{
	LONGLONG llLen = 0;
	long lPos = m_pReal->GetPosition();
	llLen = lPos * (LONGLONG)10000000;
	return llLen;
}

DWORD CMyRealAudio::GetLengthInSecs()
{
	DWORD dwSecs = m_pReal->GetLength();

	return dwSecs;
}

void CMyRealAudio::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(rect);

	CBrush brBkGnd;
	brBkGnd.CreateSolidBrush(0x000000);
	dc.FillRect(rect,&brBkGnd);	
}

void CMyRealAudio::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

	if(m_pReal && IsWindow(m_pReal->m_hWnd))	
		m_pReal->MoveWindow(0,0,cx,cy);
}
