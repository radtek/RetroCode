
#include "StdAfx.h"
#include ".\myspeechctl.h"

CMySpeechCtl::CMySpeechCtl(void)
{
	m_enState = Stopped;
}

CMySpeechCtl::~CMySpeechCtl(void)
{	
}

// create and initialize the speech control
BOOL CMySpeechCtl::InitializeSpeechControl(void)
{
	HRESULT hr;
    hr = m_cpVoice.CoCreateInstance(CLSID_SpVoice);
    if(hr == S_OK)
	{		 
		m_cpVoice->GetVolume(&m_nVolume);
		// Set the notification message for the voice
		hr = m_cpVoice->SetNotifyWindowMessage(m_hWnd,WM_TTSAPPCUSTOMEVENT,0,0);
	    // We're interested in all TTS events
        hr = m_cpVoice->SetInterest(SPFEI_ALL_TTS_EVENTS, SPFEI_ALL_TTS_EVENTS);

		return true;
	}
	return false;
}

// speak text buffer
BOOL CMySpeechCtl::Play(CString strText)
{
	HRESULT hr = S_OK;
	
	if(m_enState == Paused)
	{
		hr = m_cpVoice->Resume();
	}
	else
	{
		CComBSTR szWTextString = strText;
		if(m_cpVoice)
			hr = m_cpVoice->Speak(szWTextString, SVSFPurgeBeforeSpeak|SVSFlagsAsync|SVSFIsNotXML , 0 );
	}
	if(hr == S_OK)
		m_enState = Playing;
	return (hr == S_OK);
}

// pause speaking
BOOL CMySpeechCtl::Pause(void)
{
	HRESULT hr;
	if(m_enState == Playing)
	{	
		hr = m_cpVoice->Pause();
		m_enState = Paused;		
	}
	else
	{
		hr = m_cpVoice->Resume();
		m_enState = Playing;
	}
	return (hr == S_OK);
}

// stop speaking
BOOL CMySpeechCtl::Stop(void)
{
	HRESULT hr = S_OK;
	if(m_cpVoice)
		hr = m_cpVoice->Speak(NULL, SPF_PURGEBEFORESPEAK, 0);	
	m_enState = Stopped;

    return (hr == S_OK);
}

// rewind a sentence
BOOL CMySpeechCtl::Rewind(void)
{
	ULONG ulNumSkipped = 0;
	CComBSTR wszBuf = _T("SENTENCE");
	HRESULT hr = m_cpVoice->Skip(wszBuf,-1,&ulNumSkipped);
	return (hr == S_OK);
}

// forward a sentence
BOOL CMySpeechCtl::Forward(void)
{	
	ULONG ulNumSkipped = 0;
	CComBSTR wszBuf = _T("SENTENCE");
	HRESULT hr = m_cpVoice->Skip(wszBuf,1,&ulNumSkipped);
	return (hr == S_OK);
}

// rewind a paragraph
BOOL CMySpeechCtl::FastRewind(void)
{
	ULONG ulNumSkipped = 0;
	CComBSTR wszBuf = _T("SENTENCE");
	HRESULT hr = m_cpVoice->Skip(wszBuf,-4,&ulNumSkipped);
	return (hr == S_OK);
}

// forward a paragraph
BOOL CMySpeechCtl::FastForward(void)
{
	ULONG ulNumSkipped = 0;
	CComBSTR wszBuf = _T("SENTENCE");
	HRESULT hr = m_cpVoice->Skip(wszBuf,4,&ulNumSkipped);
	return (hr == S_OK);
}

// Speech Event
LRESULT CMySpeechCtl::OnSpeechEvent(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CSpEvent        event;  // helper class in sphelper.h for events that releases any 
                            // allocated memory in it's destructor - SAFER than SPEVENT
    SPVOICESTATUS   Stat;
    WPARAM          nStart;
    LPARAM          nEnd;
    int             i = 0;
    HRESULT 		hr = S_OK;

    while(event.GetFrom(m_cpVoice) == S_OK)
    {
        switch(event.eEventId )
        {
            case SPEI_START_INPUT_STREAM:
                break; 
			
			// end of text
            case SPEI_END_INPUT_STREAM:
				m_enState = Stopped;
				::PostMessage(m_hWndEdit, MY_EM_END_OF_STREAM, 0,0);
				break;     
                
            case SPEI_VOICE_CHANGE:
                break;     

            case SPEI_TTS_BOOKMARK:
                break;
			
			// highlight next word
            case SPEI_WORD_BOUNDARY:
                hr = m_cpVoice->GetStatus(&Stat, NULL);
                // Highlight word
                nStart = (LPARAM)(Stat.ulInputWordPos / sizeof(char));
                nEnd = nStart + Stat.ulInputWordLen;
				::PostMessage(m_hWndEdit, MY_EM_SETSEL, nStart, nEnd);				
                break;

            case SPEI_PHONEME:
                break;

            case SPEI_VISEME:
                // Get the current mouth viseme position and map it to one of the 
                // 7 mouth bitmaps.               
                break;

            case SPEI_SENTENCE_BOUNDARY:               
                break;

            case SPEI_TTS_AUDIO_LEVEL:               
                break;

            case SPEI_TTS_PRIVATE:                
                break;

            default:
                ATLTRACE(_T("Unknown message\r\n"));
                break;
        }
    }
	return S_OK;
}

// true if currently speaking
BOOL CMySpeechCtl::IsPlaying(void)
{
	return (m_enState == Playing);
}

void CMySpeechCtl::Mute(BOOL bMute)
{
	if(bMute)
	{
		m_cpVoice->GetVolume(&m_nVolume);
		m_cpVoice->SetVolume(0);
	}
	else
		m_cpVoice->SetVolume(m_nVolume);
}
