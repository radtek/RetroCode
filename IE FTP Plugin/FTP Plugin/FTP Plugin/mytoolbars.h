#pragma once

class CIEFTPPlugin;
#include "mybmbutton.h"

class CMyToolbars : public CWindowImpl<CMyToolbars>
{
public:
	CMyToolbars(void);
	~CMyToolbars(void);

	CMyBmButton m_buttonFTP;

	CBitmap m_bmFTP1;
	CBitmap m_bmFTP2;

	CIEFTPPlugin* m_pParent;

	BEGIN_MSG_MAP(CMyToolbars)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
		CHAIN_MSG_MAP_MEMBER(m_buttonFTP)
		COMMAND_ID_HANDLER(ID_FTP_BUTTON, OnMainMenu)
		COMMAND_ID_HANDLER(ID_ADDRESS_BUTTON, OnClickAddressBook)
		COMMAND_ID_HANDLER(ID_FTP_SERVER_ADDRESSBOOK, OnClickAddressBook)
		COMMAND_ID_HANDLER(ID_REGISTER, OnClickEnterRegistrationCode)
		COMMAND_ID_HANDLER(ID_REGISTER_ONLINE, OnClickRegister)
		COMMAND_ID_HANDLER(ID_MYMENU_ABOUT, OnClickAbout)
		COMMAND_ID_HANDLER(ID_FTP_CONNECT_TO_LAST_SERVER, OnClickConnectLastServer)
		COMMAND_ID_HANDLER(ID_MYMENU_POPUP_WIN_EXPLORER, OnClickPopupWinExplorer)	
		COMMAND_ID_HANDLER(ID_FTP_CHANGEDIRECTORYTO, OnClickChangeDirectoryTo)
		COMMAND_ID_HANDLER(ID_DISCONNECT, OnDisconnect)
		COMMAND_RANGE_HANDLER(ID_BASE_MENU_UID,ID_BASE_MENU_UID + MAX_POPUP_MENUS,OnClickConnectToServer)		
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	LRESULT OnDrawItem(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMainMenu(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnClickAddressBook(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickRegister(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickConnectLastServer(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickConnectToServer(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickPopupWinExplorer(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickEnterRegistrationCode(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickChangeDirectoryTo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDisconnect(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	// update tooltips
	void UpdateToolTips(int nShowToolsTips);
};
