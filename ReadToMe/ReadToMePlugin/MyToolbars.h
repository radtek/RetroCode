#pragma once

class CReadToMe;
#include "mybmbutton.h"

class CMyToolbars : public CWindowImpl<CMyToolbars>
{
public:
	CMyToolbars(void);
	~CMyToolbars(void);

	CMyBmButton m_buttonReadToMe;
	CMyBmButton m_buttonPlay;
	CMyBmButton m_buttonPause;
	CMyBmButton m_buttonStop;

	CBitmap m_bmReadToMe;
	CBitmap m_bmReadToMe2;
	CBitmap m_bmPlay;
	CBitmap m_bmPlay2;
	CBitmap m_bmPause;
	CBitmap m_bmPause2;
	CBitmap m_bmStop;
	CBitmap m_bmStop2;

	CReadToMe* m_pParent;

	BEGIN_MSG_MAP(CMyToolbars)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
		COMMAND_ID_HANDLER(ID_PLAY, OnPlay)
		COMMAND_ID_HANDLER(ID_STOP, OnStop)
		COMMAND_ID_HANDLER(ID_PAUSE, OnPause)
		COMMAND_ID_HANDLER(ID_READTOME, OnMainMenu)
		COMMAND_ID_HANDLER(ID_REGISTER, OnClickEnterRegistrationCode)
		COMMAND_ID_HANDLER(ID_REGISTER_ONLINE, OnClickRegister)
		COMMAND_ID_HANDLER(ID_MENU_SETTINGSANDOPTIONS, OnSettings)
		COMMAND_ID_HANDLER(ID_MENU_REWIND, OnRewind)
		COMMAND_ID_HANDLER(ID_MENU_FORWARD, OnForward)
		COMMAND_ID_HANDLER(ID_MENU_FASTREWIND, OnFastRewind)
		COMMAND_ID_HANDLER(ID_MENU_FASTFORWARD, OnFastForward)
		COMMAND_ID_HANDLER(ID_MENU_ABOUT, OnAbout)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	LRESULT OnDrawItem(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnStop(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnPlay(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnPause(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnMainMenu(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnSettings(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickEnterRegistrationCode(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickRegister(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnRewind(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFastRewind(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnForward(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFastForward(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	// update tooltips
	void UpdateToolTips(int nShowToolsTips);
};
