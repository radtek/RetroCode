// VolumeControl.h: interface for the CVolumeControl class.
//
// Author:  Bill Oatman
// Version: 1.0
//          http://www.netacc.net/~waterbry/BillsApps.htm
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOLUMECONTROL_H__474A1E20_7C85_11D2_AFC5_9519AA48B36F__INCLUDED_)
#define AFX_VOLUMECONTROL_H__474A1E20_7C85_11D2_AFC5_9519AA48B36F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <mmsystem.h>

class CVolumeControl  
{
public:
	DWORD GetVolumeID();
	HMIXER GetMixerID();
	void GetMaxMin(DWORD *max, DWORD *min);
	bool SetVolume(DWORD volume);
	bool GetCurrentVolume(DWORD *volume);
	bool Close(void);
	bool Open(HWND dlgHwnd);
	CVolumeControl();
	virtual ~CVolumeControl();

	DWORD WaveGetVolume();
	void WaveSetVolume(DWORD vol);
	DWORD WaveGetMax();
	DWORD WaveGetMin();


private:
	unsigned int m_numMixers;
	HMIXER m_mixer;
	MIXERCAPS m_mxCaps;
	DWORD m_minimum;
	DWORD m_maximum;
	DWORD m_volumeControlID;
};

#endif // !defined(AFX_VOLUMECONTROL_H__474A1E20_7C85_11D2_AFC5_9519AA48B36F__INCLUDED_)
