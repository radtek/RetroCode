// SettingsDlg.cpp : Implementation of CSettingsDlg

#include "stdafx.h"
#include "ReadToMe.h"
#include "SettingsDlg.h"
#include "helpers.h"
#include ".\settingsdlg.h"


// CSettingsDlg
CSettingsDlg::CSettingsDlg()
{
	m_lDefaultRate = 0;
	m_lDefaultVolume = 0;
	m_cpVoice = NULL;
	m_pMain = NULL;
}

CSettingsDlg::~CSettingsDlg()
{
}

LRESULT CSettingsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CAxDialogImpl<CSettingsDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
	HRESULT hr;
	// Use the SAPI5 helper function in sphelper.h to initialize the Voice combo box.
	hr = SpInitTokenComboBox(GetDlgItem(IDC_COMBO_VOICE), SPCAT_VOICES);
	// Set default voice data 
	VoiceChange();
	 // Get default rate and volume
    if(SUCCEEDED(hr))
    {
        hr = m_cpVoice->GetRate(&m_lDefaultRate);
        // initialize sliders and edit boxes with default rate
		if (SUCCEEDED(hr))
		{
        	SendDlgItemMessage(IDC_SLIDER_VOICE_RATE, TBM_SETRANGE, TRUE, MAKELONG( SPMIN_RATE, SPMAX_RATE ) );
        	SendDlgItemMessage(IDC_SLIDER_VOICE_RATE, TBM_SETPOS, TRUE, m_lDefaultRate );
        	SendDlgItemMessage(IDC_SLIDER_VOICE_RATE, TBM_SETPAGESIZE, TRUE, 5 );
		}
    }
	// get default volume
	if(SUCCEEDED(hr))
    {
        hr = m_cpVoice->GetVolume(&m_lDefaultVolume);
        // initialize sliders and edit boxes with default volume
		if(SUCCEEDED(hr))
		{
	        SendDlgItemMessage(IDC_SLIDER_VOLUME, TBM_SETRANGE, TRUE, MAKELONG( SPMIN_VOLUME, SPMAX_VOLUME ) );
	        SendDlgItemMessage(IDC_SLIDER_VOLUME, TBM_SETPOS, TRUE, m_lDefaultVolume );
	        SendDlgItemMessage(IDC_SLIDER_VOLUME, TBM_SETPAGESIZE, TRUE, 10 );
		}
    }
	// read settings from registry
	if(MyGetProfileInt("AutoScrollText",1) == 1)
		SendDlgItemMessage(IDC_CHECK_AUTO_SELECT,BM_SETCHECK,BST_CHECKED);
	else
		SendDlgItemMessage(IDC_CHECK_AUTO_SELECT,BM_SETCHECK,BST_UNCHECKED);

	// select text
	int nSelect = MyGetProfileInt("SelectText",2);
	if(nSelect == 0)
		SendDlgItemMessage(IDC_RADIO_NO_SELECT_TEXT,BM_SETCHECK,BST_CHECKED);
	else if(nSelect == 1)
		SendDlgItemMessage(IDC_RADIO_SELECT_TEXT,BM_SETCHECK,BST_CHECKED);
	else if(nSelect == 2)
		SendDlgItemMessage(IDC_RADIO_UNDERLINE,BM_SETCHECK,BST_CHECKED);

	// select text color
	CString strTextCol = MyGetProfileString("UnderlineColor", "blue", 100);	
	SetDlgItemText(IDC_EDIT_UNDERLINE_TEXT_COLOR, strTextCol);

	// show tool tips
	if(MyGetProfileInt("ShowToolTips",1) == 1)
		SendDlgItemMessage(IDC_CHECK_SHOW_TOOL_TIPS,BM_SETCHECK,BST_CHECKED);
	else
		SendDlgItemMessage(IDC_CHECK_SHOW_TOOL_TIPS,BM_SETCHECK,BST_UNCHECKED);

	// double click to speak
	if(MyGetProfileInt("DoubleClickPlay",1) == 1)
		SendDlgItemMessage(IDC_CHECK_DCLICK_PLAY,BM_SETCHECK,BST_CHECKED);
	else
		SendDlgItemMessage(IDC_CHECK_DCLICK_PLAY,BM_SETCHECK,BST_UNCHECKED);

	// junk chars
	CString strTemp = MyGetProfileString("JunkWordChars","|,<,>",4096);
	SetDlgItemText(IDC_EDIT_CHARCTERS_TO_SKIP, strTemp);
	// junk words
	strTemp = MyGetProfileString("JunkWords","",8096);
	SetDlgItemText(IDC_EDIT_WORDS_TO_SKIP_SPEAKING, strTemp);
	if(MyGetProfileInt("IgnoreHyperlinks",1) == 1)
		SendDlgItemMessage(IDC_CHECK_DO_NOT_SPEAK_LINKS,BM_SETCHECK,BST_CHECKED);
	else
		SendDlgItemMessage(IDC_CHECK_DO_NOT_SPEAK_LINKS,BM_SETCHECK,BST_UNCHECKED);
	
	// add tabs
	TC_ITEM item;
	ZeroMemory(&item,sizeof(TC_ITEM));
	item.mask = TCIF_TEXT;
	item.pszText = "General settings";
	TabCtrl_InsertItem(GetDlgItem(IDC_TAB_SETTINGS),0,&item);
	item.pszText = "Words/characters to ignore";
	TabCtrl_InsertItem(GetDlgItem(IDC_TAB_SETTINGS),1,&item);

	// show page 1 controls
	ShowPage1();

	HINSTANCE hInst = _AtlBaseModule.GetResourceInstance();
	SetIcon(LoadIcon(hInst,MAKEINTRESOURCE(IDI_MAIN)));
	CenterWindow();

	return 1;  // Let the system set the focus
}

LRESULT CSettingsDlg::OnHScroll(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	long hpos = 1;
    HWND hVolume, hRate;
    HRESULT	hr = S_OK;
	HWND hCtl = (HWND)lParam;

    // Get the current position of the slider
	hpos = (long)::SendMessage(hCtl,TBM_GETPOS,0,0);
    // Get the Handle for the scroll bar so it can be associated with an edit box
    hVolume = GetDlgItem(IDC_SLIDER_VOLUME);
    hRate = GetDlgItem(IDC_SLIDER_VOICE_RATE);
    
    if(hCtl == hVolume)
    {
        hr = m_cpVoice->SetVolume((USHORT)hpos);
    }
    else if(hCtl == hRate)
    {
		hr = m_cpVoice->SetRate(hpos);
    }    
	return hr;
}

// change to new selected voice
HRESULT CSettingsDlg::VoiceChange()
{
    HRESULT hr = S_OK;
    // Get the token associated with the selected voice
    ISpObjectToken* pToken = SpGetCurSelComboBoxToken(GetDlgItem(IDC_COMBO_VOICE));
    //Determine if it is the current voice
    CComPtr<ISpObjectToken> pOldToken;
    hr = m_cpVoice->GetVoice(&pOldToken);

    if(SUCCEEDED(hr))
    {
        if(pOldToken != pToken)
        {   
            if(SUCCEEDED(hr))
            {
				hr = SpSetDefaultTokenForCategoryId(SPCAT_VOICES,pToken);				
				BOOL bOK;
				if(m_pMain)
				{
					m_pMain->OnPause(0,0,0,bOK);
					hr = m_cpVoice->SetVoice(pToken);
					m_pMain->OnPause(0,0,0,bOK);
				}
            }
        }
    }
    return hr;
}

LRESULT CSettingsDlg::OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{	
	// auto scroll text
	MyWriteProfileInt("AutoScrollText",(BST_CHECKED == SendDlgItemMessage(IDC_CHECK_AUTO_SELECT,BM_GETCHECK)?1:0));
	// select text
	int nSelect = 0;
	if(BST_CHECKED == SendDlgItemMessage(IDC_RADIO_SELECT_TEXT,BM_GETCHECK))
		nSelect = 1;
	else if(BST_CHECKED == SendDlgItemMessage(IDC_RADIO_UNDERLINE,BM_GETCHECK))
		nSelect = 2;
	MyWriteProfileInt("SelectText",nSelect);
	// select text color
	CString strTextCol;
	GetDlgItemText(IDC_EDIT_UNDERLINE_TEXT_COLOR, strTextCol.GetBuffer(100), 100);
	strTextCol.ReleaseBuffer();
	MyWriteProfileString("UnderlineColor", strTextCol);	
	// show tool tips
	MyWriteProfileInt("ShowToolTips",(BST_CHECKED == SendDlgItemMessage(IDC_CHECK_SHOW_TOOL_TIPS,BM_GETCHECK)?1:0));
	// double click to speak
	MyWriteProfileInt("DoubleClickPlay",(BST_CHECKED == SendDlgItemMessage(IDC_CHECK_DCLICK_PLAY,BM_GETCHECK)?1:0));

	// junk chars
	CString strTemp;
	GetDlgItemText(IDC_EDIT_CHARCTERS_TO_SKIP, strTemp.GetBuffer(4096),4096);
	strTemp.ReleaseBuffer();
	MyWriteProfileString("JunkWordChars",strTemp);
	// junk words
	GetDlgItemText(IDC_EDIT_WORDS_TO_SKIP_SPEAKING, strTemp.GetBuffer(4096),4096);
	strTemp.ReleaseBuffer();
	MyWriteProfileString("JunkWords",strTemp);
	// IgnoreHyperlinks
	MyWriteProfileInt("IgnoreHyperlinks",(BST_CHECKED == SendDlgItemMessage(IDC_CHECK_DO_NOT_SPEAK_LINKS,BM_GETCHECK)?1:0));

	m_pMain->SettingsChange();

	DestroyWindow();
	return 0;
}

LRESULT CSettingsDlg::OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DestroyWindow();
	return 0;
}

LRESULT CSettingsDlg::OnCbnSelchangeComboVoice(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	return VoiceChange();
}

void CSettingsDlg::ShowPage1()
{
	// page 1
	::ShowWindow(GetDlgItem(IDC_STATIC_PAGE1_1),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_STATIC_PAGE1_2),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_STATIC_PAGE1_3),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_STATIC_PAGE1_4),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_COMBO_VOICE),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_SLIDER_VOICE_RATE),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_SLIDER_VOLUME),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_RADIO_UNDERLINE),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_RADIO_SELECT_TEXT),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_RADIO_NO_SELECT_TEXT),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_EDIT_UNDERLINE_TEXT_COLOR),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_CHECK_AUTO_SELECT),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_CHECK_SHOW_TOOL_TIPS),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_CHECK_DCLICK_PLAY),SW_SHOW);
	// page 2	
	::ShowWindow(GetDlgItem(IDC_STATIC_WORDS_TO_SKIP),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_EDIT_CHARCTERS_TO_SKIP),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_STATIC_WORDS_SKIP_LABEL),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_EDIT_WORDS_TO_SKIP_SPEAKING),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_CHECK_DO_NOT_SPEAK_LINKS),SW_HIDE);
}	

void CSettingsDlg::ShowPage2()
{
	// page 1
	::ShowWindow(GetDlgItem(IDC_STATIC_PAGE1_1),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_STATIC_PAGE1_2),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_STATIC_PAGE1_3),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_STATIC_PAGE1_4),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_COMBO_VOICE),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_SLIDER_VOICE_RATE),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_SLIDER_VOLUME),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_RADIO_UNDERLINE),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_RADIO_SELECT_TEXT),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_RADIO_NO_SELECT_TEXT),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_EDIT_UNDERLINE_TEXT_COLOR),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_CHECK_AUTO_SELECT),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_CHECK_SHOW_TOOL_TIPS),SW_HIDE);
	::ShowWindow(GetDlgItem(IDC_CHECK_DCLICK_PLAY),SW_HIDE);
	// page 2	
	::ShowWindow(GetDlgItem(IDC_STATIC_WORDS_TO_SKIP),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_EDIT_CHARCTERS_TO_SKIP),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_STATIC_WORDS_SKIP_LABEL),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_EDIT_WORDS_TO_SKIP_SPEAKING),SW_SHOW);
	::ShowWindow(GetDlgItem(IDC_CHECK_DO_NOT_SPEAK_LINKS),SW_SHOW);
}

LRESULT CSettingsDlg::OnTabChange(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	int idFrom = TabCtrl_GetCurSel(pnmh->hwndFrom);
	if(idFrom == 0)
		ShowPage1();
	else
		ShowPage2();
	bHandled = true;
	return S_OK;
}