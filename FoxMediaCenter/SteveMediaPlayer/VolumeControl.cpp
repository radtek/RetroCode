// VolumeControl.cpp: implementation of the CVolumeControl class.
//
// Author:  Bill Oatman
// Version: 1.0
//          http://www.netacc.net/~waterbry/BillsApps.htm
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "VolumeControl.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVolumeControl::CVolumeControl()
{
	m_mixer = NULL;
	m_volumeControlID = NULL;
}

CVolumeControl::~CVolumeControl()
{
	if(m_mixer || m_volumeControlID)
		Close();
}

bool CVolumeControl::Open(HWND dlgHwnd)
{
	MIXERLINE mxl;
	MIXERCONTROL mxc;
	MIXERLINECONTROLS mxlc;

	// get the number of mixer devices present in the system
	m_numMixers = ::mixerGetNumDevs();

	m_mixer = NULL;
	m_volumeControlID = NULL;
	::ZeroMemory(&m_mxCaps, sizeof(MIXERCAPS));

	// open the first mixer
	if (m_numMixers != 0)
	{
		if (::mixerOpen(&m_mixer,
						0,
						(DWORD)dlgHwnd,
						NULL,
						MIXER_OBJECTF_MIXER | CALLBACK_WINDOW)
			!= MMSYSERR_NOERROR)
			return FALSE;

		if (::mixerGetDevCaps((UINT)m_mixer, &m_mxCaps, sizeof(MIXERCAPS)) != MMSYSERR_NOERROR)
			return FALSE;

		// get dwLineID

		mxl.cbStruct = sizeof(MIXERLINE);
		mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
		if(::mixerGetLineInfo((HMIXEROBJ)m_mixer,&mxl,MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE) != MMSYSERR_NOERROR)
			return FALSE;

		// get dwControlID

		mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
		mxlc.dwLineID = mxl.dwLineID;
		mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
		mxlc.cControls = 1;
		mxlc.cbmxctrl = sizeof(MIXERCONTROL);
		mxlc.pamxctrl = &mxc;
		if(::mixerGetLineControls((HMIXEROBJ)m_mixer,&mxlc,MIXER_OBJECTF_HMIXER | MIXER_GETLINECONTROLSF_ONEBYTYPE) != MMSYSERR_NOERROR)
			return FALSE;

		// save record dwControlID
		m_minimum = mxc.Bounds.dwMinimum;
		m_maximum = mxc.Bounds.dwMaximum;
		m_volumeControlID = mxc.dwControlID;
	}
	else
		return FALSE;

	return TRUE;
}

bool CVolumeControl::Close()
{
	if (m_mixer != NULL)
	{
		if(::mixerClose(m_mixer) != MMSYSERR_NOERROR)
			return FALSE;

		m_mixer = NULL;
		m_volumeControlID = NULL;
	}

	return TRUE;
}

bool CVolumeControl::GetCurrentVolume(DWORD *volume)
{
	MIXERCONTROLDETAILS_UNSIGNED mxcdVolume;
	MIXERCONTROLDETAILS mxcd;

	if (m_mixer == NULL)
		return FALSE;

	mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID = m_volumeControlID;
	mxcd.cChannels = 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mxcd.paDetails = &mxcdVolume;

	BOOL bOK = (::mixerGetControlDetails((HMIXEROBJ)m_mixer,&mxcd,
		MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE) == MMSYSERR_NOERROR);
	if(!bOK)
		return false;
	
	*volume = mxcdVolume.dwValue;

	return TRUE;
}

bool CVolumeControl::SetVolume(DWORD volume)
{
	MIXERCONTROLDETAILS_UNSIGNED mxcdVolume = { volume };
	MIXERCONTROLDETAILS mxcd;

	if (m_mixer == NULL)
		return FALSE;

	mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID = m_volumeControlID;
	mxcd.cChannels = 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mxcd.paDetails = &mxcdVolume;
	if (::mixerSetControlDetails((HMIXEROBJ)m_mixer,&mxcd,
		 MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR)
		return FALSE;
	
	return TRUE;
}

void CVolumeControl::GetMaxMin(DWORD *max, DWORD *min)
{
	*max = m_maximum;
	*min = m_minimum;
}

HMIXER CVolumeControl::GetMixerID()
{
	return m_mixer;
}

DWORD CVolumeControl::GetVolumeID()
{
	return m_volumeControlID;
}

DWORD CVolumeControl::WaveGetVolume()
{
	UINT uNumDevs = 0;
    DWORD volume = 0;
    long lLeftVol = 0;
	long lRightVol = 0;

	WAVEOUTCAPS waveCaps;
	if(uNumDevs = waveOutGetNumDevs())
	{
		if(!waveOutGetDevCaps(0,(LPWAVEOUTCAPS)&waveCaps,sizeof(WAVEOUTCAPS)))
		{
			if(waveCaps.dwSupport & WAVECAPS_VOLUME)
			{
				waveOutGetVolume(0,(LPDWORD)&volume);
				lLeftVol = (long)LOWORD(volume);
		        lRightVol = (long)HIWORD(volume);
			}
		}
	}
	return lLeftVol;
}

void CVolumeControl::WaveSetVolume(DWORD vol)
{
	UINT uNumDevs = 0;
    long lLeftVol = 0;
	long lRightVol = 0;
	DWORD volume = MAKELONG(vol,vol);

	WAVEOUTCAPS waveCaps;
	if(uNumDevs = waveOutGetNumDevs())
	{
		if(!waveOutGetDevCaps(0,(LPWAVEOUTCAPS)&waveCaps,sizeof(WAVEOUTCAPS)))
		{
			if(waveCaps.dwSupport & WAVECAPS_VOLUME)
			{
				waveOutSetVolume(0,volume);
			}
		}
	}
}

DWORD CVolumeControl::WaveGetMax()
{
	DWORD dwVal = 0xFFFF;
	return dwVal;
}

DWORD CVolumeControl::WaveGetMin()
{
	DWORD dwVal = 0;
	return dwVal;
}