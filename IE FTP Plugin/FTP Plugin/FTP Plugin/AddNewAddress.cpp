// AddNewAddress.cpp : Implementation of CAddNewAddress

#include "stdafx.h"
#include "AddNewAddress.h"


// CAddNewAddress

LRESULT CAddNewAddress::OnBnClickedButtonBrowse(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	LPMALLOC pMalloc;
    /* Gets the Shell's default allocator */
    if (SHGetMalloc(&pMalloc) == NOERROR)
    {
        BROWSEINFO bi;
        char pszBuffer[MAX_PATH];
        LPITEMIDLIST pidl;
        // Get help on BROWSEINFO struct - it's got all the bit settings.
        bi.hwndOwner = m_hWnd;
        bi.pidlRoot = NULL;
        bi.pszDisplayName = pszBuffer;
        bi.lpszTitle = _T("Select a Directory");
        bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS | BIF_USENEWUI | BIF_SHAREABLE;
        bi.lpfn = NULL;
        bi.lParam = 0;
        // This next call issues the dialog box.
        if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)
        {
            if (::SHGetPathFromIDList(pidl, pszBuffer))
            { 
				// At this point pszBuffer contains the selected path */.
				SetDlgItemText(IDC_EDIT_FILE_MANAGER_PATH,pszBuffer);
            }
            // Free the PIDL allocated by SHBrowseForFolder.
            pMalloc->Free(pidl);
        }
        // Release the shell's allocator.
        pMalloc->Release();
    }

	return 0;
}

LRESULT CAddNewAddress::OnBnClickedRadioAnonymous(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	HideUserPass();

	return 0;
}

LRESULT CAddNewAddress::OnBnClickedRadioUserLogon(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowUserPass();

	return 0;
}

void CAddNewAddress::HideUserPass()
{
	::SendMessage(GetDlgItem(IDC_RADIO_ANONYMOUS),BM_SETCHECK,BST_CHECKED,0);
	::SendMessage(GetDlgItem(IDC_RADIO_USER_LOGON),BM_SETCHECK,BST_UNCHECKED,0);

	HWND hWnd = GetDlgItem(IDC_USERNAME_TEXT);
	::ShowWindow(hWnd,SW_HIDE);
	hWnd = GetDlgItem(IDC_EDIT_USERNAME);
	::ShowWindow(hWnd,SW_HIDE);
	hWnd = GetDlgItem(IDC_PASSWORD_TEXT);
	::ShowWindow(hWnd,SW_HIDE);
	hWnd = GetDlgItem(IDC_PASSWORD_TEXT2);
	::ShowWindow(hWnd,SW_HIDE);
	hWnd = GetDlgItem(IDC_EDIT_PASSWORD);
	::ShowWindow(hWnd,SW_HIDE);
	hWnd = GetDlgItem(IDC_EDIT_PASSWORD2);
	::ShowWindow(hWnd,SW_HIDE);
}

void CAddNewAddress::ShowUserPass()
{
	::SendMessage(GetDlgItem(IDC_RADIO_ANONYMOUS),BM_SETCHECK,BST_UNCHECKED,0);
	::SendMessage(GetDlgItem(IDC_RADIO_USER_LOGON),BM_SETCHECK,BST_CHECKED,0);

	HWND hWnd = GetDlgItem(IDC_USERNAME_TEXT);
	::ShowWindow(hWnd,SW_SHOW);
	hWnd = GetDlgItem(IDC_EDIT_USERNAME);
	::ShowWindow(hWnd,SW_SHOW);
	hWnd = GetDlgItem(IDC_PASSWORD_TEXT);
	::ShowWindow(hWnd,SW_SHOW);
	hWnd = GetDlgItem(IDC_PASSWORD_TEXT2);
	::ShowWindow(hWnd,SW_SHOW);
	hWnd = GetDlgItem(IDC_EDIT_PASSWORD);
	::ShowWindow(hWnd,SW_SHOW);
	hWnd = GetDlgItem(IDC_EDIT_PASSWORD2);
	::ShowWindow(hWnd,SW_SHOW);
}

BOOL CAddNewAddress::SaveNewEntry(LPCSTR strNew)
{
	CString strBasePath = MyGetProfileString("InstallPath",DEFAULT_INSTALL_PATH);
	if(strBasePath.Right(1) != "\\") 
		strBasePath += "\\";
	strBasePath += "entries.dat";
	
	CString strData = ReadEncryptedFile(strBasePath,ENCRYPT_KEY);
	// save new
	if(!m_bEditMode)
	{
		strData += strNew;
	}
	// update existing
	else
	{
		int nFind = strData.Find(m_strEditParams);
		if(nFind != -1)
		{
			int nSize = m_strEditParams.GetLength();
			CString strTemp = strData.Left(nFind);
			strTemp += ParseXML("Entry",strNew);
			if(nFind + nSize < strData.GetLength())
				strTemp += strData.Mid(nFind + nSize);
			strData = strTemp;
		}
	}
	BOOL bOK = WriteEncryptedFile(strBasePath,ENCRYPT_KEY,strData);
	return bOK;	
}