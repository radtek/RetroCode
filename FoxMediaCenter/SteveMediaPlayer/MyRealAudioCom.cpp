// MyRealAudioCom.cpp : implementation file
//

#include "stdafx.h"
#include "SteveMediaPlayer.h"
#include "MyRealAudioCom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyRealAudioCom

CMyRealAudioCom::CMyRealAudioCom()
{
}

CMyRealAudioCom::~CMyRealAudioCom()
{
}


BEGIN_MESSAGE_MAP(CMyRealAudioCom, CWnd)
	//{{AFX_MSG_MAP(CMyRealAudioCom)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyRealAudioCom message handlers

int CMyRealAudioCom::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
