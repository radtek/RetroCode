// AddNewAddress.h : Declaration of the CAddNewAddress

#pragma once

#include "resource.h"       // main symbols
#include "helpers.h"
#include <atlhost.h>


// CAddNewAddress

class CAddNewAddress : public CAxDialogImpl<CAddNewAddress>
{
public:
	CAddNewAddress()
	{
		m_bEditMode = false;
	}

	~CAddNewAddress()
	{
	}

	enum { IDD = IDD_ADDNEWADDRESS };

BEGIN_MSG_MAP(CAddNewAddress)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	COMMAND_HANDLER(IDC_BUTTON_BROWSE, BN_CLICKED, OnBnClickedButtonBrowse)
	COMMAND_HANDLER(IDC_RADIO_ANONYMOUS, BN_CLICKED, OnBnClickedRadioAnonymous)
	COMMAND_HANDLER(IDC_RADIO_USER_LOGON, BN_CLICKED, OnBnClickedRadioUserLogon)
	CHAIN_MSG_MAP(CAxDialogImpl<CAddNewAddress>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CAddNewAddress>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;

		CString strTitle = _T(APP_NAME);
		strTitle += _T(" - New FTP server address");
		SetWindowText(strTitle);

		SetIcon(LoadIcon(_AtlBaseModule.m_hInst,MAKEINTRESOURCE(IDI_MAIN)), true);

		// edit address
		if(m_bEditMode)
		{
			SetWindowText("Edit FTP Server Address");
			
			CString strURL = ParseXML("URL",m_strEditParams);
			CString strName = ParseXML("Name",m_strEditParams);
			CString strUser = ParseXML("User",m_strEditParams);
			CString strPass = ParseXML("Pass",m_strEditParams);
			CString strPort = ParseXML("Port",m_strEditParams);
			CString strLocalPath = ParseXML("LocalPath",m_strEditParams);
			if(!strLocalPath.IsEmpty())
			{
				// show Windows Explorer
				HWND hWnd = GetDlgItem(IDC_CHECK_SHOW_FILE_MANAGER);
				::SendMessage(hWnd,BM_SETCHECK,BST_CHECKED,0);
				SetDlgItemText(IDC_EDIT_FILE_MANAGER_PATH,strLocalPath);
			}
			
			SetDlgItemText(IDC_EDIT_URL,strURL);
			SetDlgItemText(IDC_EDIT_NAME,strName);
			SetDlgItemText(IDC_EDIT_PORT,strPort);
			// passive mode FTP
			if(ParseXML("PasvMode",m_strEditParams) == "TRUE")
			{
				HWND hWnd = GetDlgItem(IDC_CHECK_PASV_MODE);
				::SendMessage(hWnd,BM_SETCHECK,BST_CHECKED,0);
			}		

			if(!strUser.IsEmpty())
			{
				// set user pass
				HWND hWnd = GetDlgItem(IDC_RADIO_USER_LOGON);
				::SendMessage(hWnd,BM_SETCHECK,BST_CHECKED,0);
				SetDlgItemText(IDC_EDIT_USERNAME,strUser);
				SetDlgItemText(IDC_EDIT_PASSWORD,strPass);
				SetDlgItemText(IDC_EDIT_PASSWORD2,strPass);
			}
			else
			{
				// set anonymous
				HWND hWnd = GetDlgItem(IDC_RADIO_ANONYMOUS);
				::SendMessage(hWnd,BM_SETCHECK,BST_CHECKED,0);
				HideUserPass();
			}
		}
		// new address
		else
		{
			// set anonymous
			HWND hWnd = GetDlgItem(IDC_RADIO_ANONYMOUS);
			::SendMessage(hWnd,BM_SETCHECK,BST_CHECKED,0);
			// show file manager
			hWnd = GetDlgItem(IDC_CHECK_SHOW_FILE_MANAGER);
			::SendMessage(hWnd,BM_SETCHECK,BST_UNCHECKED,0);

			// passive mode FTP
			hWnd = GetDlgItem(IDC_CHECK_PASV_MODE);
			::SendMessage(hWnd,BM_SETCHECK,BST_UNCHECKED,0);

			HideUserPass();
			// set port 21
			SetDlgItemText(IDC_EDIT_PORT,"21");
		}	
		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CString strURL;
		CString strName;
		CString strPort;
		CString strUser;
		CString strPass;
		CString strPass2;
		CString strTemp;

		// check anonymous, username
		HWND hWnd = GetDlgItem(IDC_RADIO_ANONYMOUS);
		BOOL bAnonymous = (::SendMessage(hWnd,BM_GETCHECK,0,0) == BST_CHECKED);
		// get URL	
		GetDlgItemText(IDC_EDIT_URL,strURL.GetBuffer(1024),1024);
		strURL.ReleaseBuffer();
		if(strURL.IsEmpty())
		{
			MessageBox("You must enter a URL for the FTP server. eg. ftp.microsoft.com","Error");
			return 0;
		}
		// get Name	
		GetDlgItemText(IDC_EDIT_NAME,strName.GetBuffer(1024),1024);
		strName.ReleaseBuffer();
		if(strName.IsEmpty())
		{
			MessageBox("You must enter a name for the FTP server. eg. Microsoft's FTP server","Error");
			return 0;
		}
		// get Port	
		GetDlgItemText(IDC_EDIT_PORT,strPort.GetBuffer(1024),1024);
		strPort.ReleaseBuffer();
		if(strPort.IsEmpty())
		{
			strPort = "21";
		}

		// strip any ftp:// url
		if((UINT)strURL.GetLength() > (int)strlen("ftp://"))
		{
			strTemp = strURL.Left((int)strlen("ftp://"));
			strTemp.MakeLower();
		}
		if(strTemp == "ftp://")
			strURL = strURL.Mid((int)strlen("ftp://"));

		// strip any username pass from url
		if(!bAnonymous)
		{
			if(strURL.Find('@') != -1)
				strURL = strURL.Mid(strURL.Find('@')+1);

			GetDlgItemText(IDC_EDIT_USERNAME,strUser.GetBuffer(1024),1024);
			strUser.ReleaseBuffer();

			GetDlgItemText(IDC_EDIT_PASSWORD,strPass.GetBuffer(1024),1024);
			strPass.ReleaseBuffer();

			GetDlgItemText(IDC_EDIT_PASSWORD2,strPass2.GetBuffer(1024),1024);
			strPass2.ReleaseBuffer();

			if(strUser.IsEmpty() || strPass.IsEmpty())
			{
				MessageBox("You must enter a username and password, or otherwise use an anonymous logon.","Error");
				return 0;
			}
			if(strPass != strPass2)
			{
				MessageBox("Passwords do not match. Try again.","Error");
				return 0;
			}
		}
		// check for non standard port
		if(strPort != "21")
		{
			strTemp = strURL;
			CString strTemp2 = strURL;
			// save anything after /
			int nFind = -1;
			if((nFind = strTemp.Find('/')) != -1)
			{
				strTemp = strTemp.Mid(nFind);
				// save before /
				strTemp2 = strURL.Left(nFind);
			}
			else
				strTemp = "";
			// check for :
			if((nFind = strTemp2.ReverseFind(':')) != -1)
			{
				int nFind2 = -1;
				if((nFind2 = strTemp2.Find('@')) != -1)
				{
					// using port :
					if(nFind > nFind2)
					{
						strTemp2 = strTemp2.Left(nFind);
					}
				}
				else // trim extra :
					strTemp2 = strTemp2.Left(nFind);
			}
			// port is stripped out
			strTemp2 += strTemp;
			strURL = strTemp2;			
		}

		// add header
		strURL = "ftp://" + strURL;

		// get windows explorer path
		CString strLocalPath;
		hWnd = GetDlgItem(IDC_CHECK_SHOW_FILE_MANAGER);
		BOOL bShowWindowsExplorer = (::SendMessage(hWnd,BM_GETCHECK,0,0) == BST_CHECKED);
		if(bShowWindowsExplorer)
		{
			GetDlgItemText(IDC_EDIT_FILE_MANAGER_PATH,strLocalPath.GetBuffer(1024),1024);
			strLocalPath.ReleaseBuffer();	
			if(strLocalPath.IsEmpty())
			{
				MessageBox("You must enter a local file path or uncheck 'Open Windows Exporer'.","Error");
				return 0;
			}
		}

		// passive mode FTP
		hWnd = GetDlgItem(IDC_CHECK_PASV_MODE);
		BOOL bPasvMode = (::SendMessage(hWnd,BM_GETCHECK,0,0) == BST_CHECKED);

		CString strNewEntry;
		if(bAnonymous)
			strNewEntry.Format("<Entry><Name>%s</Name><URL>%s</URL><Port>%s</Port>%s<PasvMode>%s</PasvMode></Entry>\r\n",
			strName,strURL,strPort,bShowWindowsExplorer?"<LocalPath>" + strLocalPath + "</LocalPath>":"",bPasvMode?"TRUE":"FALSE");
		else
			strNewEntry.Format("<Entry><Name>%s</Name><URL>%s</URL><Port>%s</Port><User>%s</User><Pass>%s</Pass>%s<PasvMode>%s</PasvMode></Entry>\r\n",
				strName,strURL,strPort,strUser,strPass,bShowWindowsExplorer?"<LocalPath>" + strLocalPath + "</LocalPath>":"",bPasvMode?"TRUE":"FALSE");
		ATLTRACE(strNewEntry);

		if(SaveNewEntry(strNewEntry))
			EndDialog(IDOK);
		else
			MessageBox("Failed to save new entry.","Error");

		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	BOOL SaveNewEntry(LPCSTR strNew);
	void ShowUserPass();
	void HideUserPass();
	BOOL m_bEditMode;
	CString m_strEditParams;
public:
	LRESULT OnBnClickedButtonBrowse(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
public:
	LRESULT OnBnClickedRadioAnonymous(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
public:
	LRESULT OnBnClickedRadioUserLogon(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};


