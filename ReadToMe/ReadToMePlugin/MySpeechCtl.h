
// MySpeechCtrl.h
// Copyright 2005 Steve Foxover

#pragma once


class CMySpeechCtl : public CWindowImpl<CMySpeechCtl>
{
public:

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	BEGIN_MSG_MAP(CMySpeechCtl)
		MESSAGE_HANDLER(WM_TTSAPPCUSTOMEVENT, OnSpeechEvent)
	END_MSG_MAP()

	CMySpeechCtl(void);
	~CMySpeechCtl(void);
	// // create and initialize the speech control
	BOOL InitializeSpeechControl(void);
	// speak text buffer
	BOOL Play(CString strText);
	// pause speaking
	BOOL Pause(void);
	// stop speaking
	BOOL Stop(void);
	// handle speech event
	LRESULT OnSpeechEvent(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	// get voice interface
	ISpVoice* GetVoiceInterface() {return m_cpVoice;}
private:
	enum MY_ENUM_STATE { Playing, Paused, Stopped };
	// speech com pointer
	CComPtr<ISpVoice> m_cpVoice;
	// speaking state of control
	MY_ENUM_STATE m_enState;
	// current volume level
	USHORT m_nVolume;
public:
	// handle to the text window to change selected text
	HWND m_hWndEdit;
	// rewind a paragraph
	BOOL FastRewind(void);
	// rewind a few words
	BOOL Rewind(void);
	// forward a few words
	BOOL Forward(void);
	// forward a paragraph
	BOOL FastForward(void);
	// true if currently speaking
	BOOL IsPlaying(void);
	// mute
	void Mute(BOOL bMute);
};
