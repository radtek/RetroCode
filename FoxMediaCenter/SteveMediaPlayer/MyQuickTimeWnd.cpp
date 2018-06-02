// MyQuickTimeWnd.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaPlayer.h"
#include "MyMediaPlayer.h"
#include "MyQuickTimeWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyQuickTimeWnd
HWND ghwnd = NULL;
LRESULT CALLBACK QTFullScreen_HandleMessages (HWND theWnd, UINT theMessage, UINT wParam, LONG lParam);

CMyQuickTimeWnd::CMyQuickTimeWnd()
{
	m_pMain = NULL;
	
	m_RestoreState = NULL;
	m_FullScreenWindow = NULL;
	m_MC = NULL;

	// Initialize QTML and QuickTime
	InitializeQTML(0);
	EnterMovies();

	m_pQuickTime = new CQuickTime();
}

CMyQuickTimeWnd::~CMyQuickTimeWnd()
{
	if(m_pQuickTime)
	{
		delete m_pQuickTime;
		m_pQuickTime = NULL;
	}

	// Exit QuickTime and terminate QTML
	ExitMovies();
	TerminateQTML();
}


BEGIN_MESSAGE_MAP(CMyQuickTimeWnd, CWnd)
	//{{AFX_MSG_MAP(CMyQuickTimeWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyQuickTimeWnd message handlers


int CMyQuickTimeWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(rect);
	m_pQuickTime->m_rectSize = rect;
	// Setup movie window	 
	m_pQuickTime->OnMovieWindowCreate( m_hWnd, lpCreateStruct);

	Rect rt;
	rt.top = 0;
	rt.left = 0;
	rt.right = rect.right;
	rt.bottom = rect.bottom;
	MCSetControllerBoundsRect(m_pQuickTime->theMC,&rt);

	return 0;
}

void CMyQuickTimeWnd::Play()
{
	HideDisplayBar();
	ShowWindow(SW_SHOW);
	StartMovie(m_pQuickTime->GetMovie());
}

void CMyQuickTimeWnd::Pause()
{
	StopMovie(m_pQuickTime->GetMovie());
}

void CMyQuickTimeWnd::Stop()
{
	ShowWindow(SW_HIDE);
	m_pQuickTime->CloseMovie();
}

void CMyQuickTimeWnd::SetFileName(CString strFileName)
{
	DWORD dwLen = strFileName.GetLength();
	m_pQuickTime->OpenMovie((unsigned char*)strFileName.GetBuffer(dwLen));
	strFileName.ReleaseBuffer();
}

void CMyQuickTimeWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Movie	theMovie;
	if (theMovie = m_pQuickTime->GetMovie())
		UpdateMovie(theMovie);
}


void CMyQuickTimeWnd::OnDestroy() 
{
	CWnd::OnDestroy();
	if(m_pQuickTime)
		m_pQuickTime->OnMovieWindowDestroy();	
}

LRESULT CMyQuickTimeWnd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message == WM_ERASEBKGND)
	{
		LRESULT theResult = CWnd::DefWindowProc(message, wParam, lParam);
		if(m_pQuickTime)
			m_pQuickTime->ProcessMovieEvent (m_hWnd, message, wParam, lParam);	
		return theResult;
	} 
	else 
	{
		if(m_pQuickTime)
			m_pQuickTime->ProcessMovieEvent (m_hWnd, message, wParam, lParam);
		return CWnd::DefWindowProc(message, wParam, lParam);
	}
}

void CMyQuickTimeWnd::HideDisplayBar()
{
	MCSetVisible(m_pQuickTime->theMC, false);
}

void CMyQuickTimeWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);	
	
	if(m_pQuickTime && m_pQuickTime->theMC)
	{
		Rect rect;
		rect.top = 0;
		rect.left = 0;
		rect.right = cx;
		rect.bottom = cy;
		MCSetControllerBoundsRect(m_pQuickTime->theMC,&rect);
	}
}

LRESULT CALLBACK QTFullScreen_HandleMessages (HWND theWnd, UINT theMessage, UINT wParam, LONG lParam)
{
	if(theMessage == WM_KEYDOWN && wParam == 27)
	{
		if(IsWindow(ghwnd))
			::PostMessage(ghwnd,WM_END_QT_FULLSCREEN,0,0);
		return 1;
	}
	
	return ::DefWindowProc(theWnd, theMessage, wParam, lParam);
}

void CMyQuickTimeWnd::Forward()
{
	LONGLONG dwDur = GetLengthInSecs() * (LONGLONG)10000000;
	LONGLONG dwPos = GetCurrentPosition();
	dwPos += 20 * (LONGLONG)10000000;
	if(dwPos > dwDur)
		dwPos = dwDur -1;
	SetCurrentPosition(dwPos);
}

void CMyQuickTimeWnd::Rewind()
{
	LONGLONG dwPos = GetCurrentPosition();
	dwPos -= 20 * (LONGLONG)10000000;
	if(dwPos < 0)
		dwPos = 0;
	SetCurrentPosition(dwPos);
}

DWORD CMyQuickTimeWnd::GetLengthInSecs()
{
	long lSecs = 0;
	TimeScale ts = GetMovieTimeScale(m_pQuickTime->GetMovie());
	lSecs = GetMovieDuration(m_pQuickTime->GetMovie());
	
	if(ts != 0)
		lSecs = lSecs / ts;

	return lSecs;
}

LONGLONG CMyQuickTimeWnd::GetCurrentPosition()
{
	LONGLONG llPos = 0;
	TimeValue ltm = GetMovieTime(m_pQuickTime->GetMovie(),NULL);
	TimeScale ts = GetMovieTimeScale(m_pQuickTime->GetMovie());
	if(ts != 0)
		ltm = ltm / ts;

	llPos = ltm * (LONGLONG)10000000;	
	return llPos;
}

void CMyQuickTimeWnd::SetCurrentPosition(LONGLONG llPos)
{
	DWORD dwPos = llPos / (LONGLONG)10000000;
	TimeRecord rec;
	rec.value.hi = HIWORD(dwPos);
	rec.value.lo = LOWORD(dwPos);
    rec.scale = 1;
    rec.base = NULL;        
	
	SetMovieTime(m_pQuickTime->GetMovie(),&rec);
}

BOOL CMyQuickTimeWnd::IsFinished()
{
	return IsMovieDone(m_pQuickTime->GetMovie());
}

void CMyQuickTimeWnd::FullScreen(BOOL bMakeFullScreen)
{
	ghwnd = m_pMain->m_hWnd;
	if(bMakeFullScreen)
	{
		Movie theMovie = m_pQuickTime->GetMovie();
		long myFlags = fullScreenAllowEvents|fullScreenHideCursor;
		GWorldPtr myOrigGWorld = NULL;
		Rect myRect;
		OSErr myErr = noErr;
		
		StopMovie(theMovie);
		// set up for full-screen display
		myErr = BeginFullScreen(&m_RestoreState, NULL, 0, 0, &m_FullScreenWindow, NULL, myFlags); 
		// on Windows, set a window procedure for the new window and associate a port with that window
		QTMLSetWindowWndProc(m_FullScreenWindow, QTFullScreen_HandleMessages);
		CreatePortAssociation(GetPortNativeWindow(m_FullScreenWindow), NULL, 0L);
		
		GetMovieBox(theMovie, &myRect);
		GetMovieGWorld(theMovie, &myOrigGWorld, NULL);
		SetMovieGWorld(theMovie, (CGrafPtr)m_FullScreenWindow, GetGWorldDevice((CGrafPtr)m_FullScreenWindow));
		SetMovieBox(theMovie, &m_FullScreenWindow->portRect);

		Play();

		::SetFocus(GetPortHWND(m_FullScreenWindow));
	}
	else
	{
		if(!m_RestoreState)
			return;
		OSErr myErr = EndFullScreen(m_RestoreState, 0L); 
		m_RestoreState = NULL;
	}
}


