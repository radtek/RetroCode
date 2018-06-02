// MyRealAudio1.h: interface for the CMyRealAudio class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYREALAUDIO1_H__4CBA6776_9B3D_4674_B514_687319521D0F__INCLUDED_)
#define AFX_MYREALAUDIO1_H__4CBA6776_9B3D_4674_B514_687319521D0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RealAudio.h"
class CMyMediaPlayer;

class CMyRealAudio : public CWnd  
{
public:
	DWORD GetLengthInSecs();
	LONGLONG GetCurrentPosition();
	void SetCurrentPosition(LONGLONG llPos);
	void Forward();
	void Rewind();
	void FullScreen(BOOL bMakeFull = true);
	void Stop();
	void Pause();
	void Play();
	BOOL SetFileName(CString strFilePath);
	CMyRealAudio();
	virtual ~CMyRealAudio();
	BOOL Create(CWnd* pParent);

	CMyMediaPlayer* m_pMain;

	CRealAudio* m_pReal;

	// Generated message map functions
protected:

	//{{AFX_MSG(CMyRealAudio)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_MYREALAUDIO1_H__4CBA6776_9B3D_4674_B514_687319521D0F__INCLUDED_)
