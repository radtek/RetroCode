// AddressBookDlg.h : Declaration of the CAddressBookDlg

#pragma once

#include "resource.h"       // main symbols
#include <atlhost.h>
class CMyToolbars;

// CAddressBookDlg

class CAddressBookDlg : public CAxDialogImpl<CAddressBookDlg>
{
public:
	CAddressBookDlg()
	{
	}

	~CAddressBookDlg()
	{
	}

	enum { IDD = IDD_ADDRESSBOOKDLG };

BEGIN_MSG_MAP(CAddressBookDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	COMMAND_HANDLER(IDC_BUTTON_NEW, BN_CLICKED, OnBnClickedButtonNew)
	COMMAND_HANDLER(IDC_BUTTON_EDIT, BN_CLICKED, OnBnClickedButtonEdit)
	COMMAND_HANDLER(IDC_BUTTON_DELETE, BN_CLICKED, OnBnClickedButtonDelete)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	NOTIFY_HANDLER(IDC_LIST_SERVERS, LVN_ITEMCHANGED, OnItemchangedList_servers)
	CHAIN_MSG_MAP(CAxDialogImpl<CAddressBookDlg>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CAddressBookDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;

		CString strTitle = _T(APP_NAME);
		strTitle += _T(" - FTP servers list");
		SetWindowText(strTitle);

		CenterWindow();
		SetIcon(LoadIcon(_AtlBaseModule.m_hInst,MAKEINTRESOURCE(IDI_MAIN)), true);

		// create column
		HWND hWnd = GetDlgItem(IDC_LIST_SERVERS);

		LVCOLUMN lvc; 
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM; 
		// Add the columns. 
		lvc.iSubItem = 0;
		lvc.pszText = "FTP Servers";
		CRect rect;
		::GetClientRect(hWnd,rect);
		lvc.cx = rect.Width(); //255;
		lvc.fmt = LVCFMT_LEFT;  
		ListView_InsertColumn(hWnd, 0, &lvc);

		LoadServerList();

		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CString strData = GetSelectedTextData();
		if(strData.IsEmpty() || !LoadURLData(strData))
			return 0L;

		EndDialog(IDOK);
		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	CString m_strLocalPath;
	BOOL LoadURLData(CString strData);
	CString LookUpDataForName(CString strName);
	CString GetSelectedTextData();
	void LoadServerList();
	void InsertListEntry(CString strData);

	void LoadEntries();
	BOOL SaveEntries();
	void HideUserPass();
	void ShowUserPass();

	void SortEntries();
	void QuickSort (int nLower, int nUpper);
	int Partition (int nLower, int nUpper);

	CSimpleArray<CString>	m_straEntries;
	CString m_strURL;
	CString m_strName;
	CMyToolbars*	m_pParent;
	int GetSelectedPos();

	LRESULT OnBnClickedButtonNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonEdit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonDelete(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnItemchangedList_servers(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
};


