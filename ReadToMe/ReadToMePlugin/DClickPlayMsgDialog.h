// DClickPlayMsgDialog.h : Declaration of the CDClickPlayMsgDialog

#pragma once

#include "resource.h"       // main symbols
#include <atlhost.h>
#include "helpers.h"       

// CDClickPlayMsgDialog

class CDClickPlayMsgDialog : public CAxDialogImpl<CDClickPlayMsgDialog>
{
public:
	CDClickPlayMsgDialog()
	{
	}

	~CDClickPlayMsgDialog()
	{
	}

	enum { IDD = IDD_DCLICKPLAYMSGDIALOG };

BEGIN_MSG_MAP(CDClickPlayMsgDialog)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	CHAIN_MSG_MAP(CAxDialogImpl<CDClickPlayMsgDialog>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CDClickPlayMsgDialog>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		HFONT hFont = m_Font.CreatePointFont(160,_T("Times New Roman"));
		CenterWindow();
		return 1;  // Let the system set the focus
	}

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		EndDialog(0);
		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if(BST_CHECKED == SendDlgItemMessage(IDC_CHECK_DONT_SHOW_AGAIN,BM_GETCHECK))
			MyWriteProfileInt("ShowDClickDlgMsg",0);

		EndDialog(wID);
		return 0;
	}

private:
	CFont m_Font;

};


