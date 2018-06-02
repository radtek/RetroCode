// AddressBookDlg.cpp : Implementation of CAddressBookDlg

#include "stdafx.h"
#include "AddressBookDlg.h"
#include "helpers.h"
#include "AddNewAddress.h"

// CAddressBookDlg

BOOL CAddressBookDlg::SaveEntries()
{
	CString strBasePath = MyGetProfileString("InstallPath",DEFAULT_INSTALL_PATH);
	if(strBasePath.Right(1) != "\\") 
		strBasePath += "\\";
	strBasePath += "entries.dat";

	CString strData;
	for(int n=0;n<m_straEntries.GetSize();n++)
		strData += "<Entry>" + m_straEntries[n] + "</Entry>";

	BOOL bOK = WriteEncryptedFile(strBasePath,ENCRYPT_KEY,strData);
	
	return bOK;	
}

void CAddressBookDlg::InsertListEntry(CString strData)
{
	HWND hWnd = GetDlgItem(IDC_LIST_SERVERS);
	LVITEM lvi;  
	ZeroMemory(&lvi,sizeof(LV_COLUMN));
	DWORD dwSize = strData.GetLength();
	lvi.pszText = strData.GetBuffer(dwSize);
	lvi.cchTextMax = dwSize;
	lvi.iImage = 0;
	lvi.mask = LVIF_IMAGE | LVIF_TEXT | LVIF_STATE;
	lvi.iSubItem = 0;
	lvi.iItem = ListView_GetItemCount(hWnd);	

	ListView_InsertItem(hWnd, &lvi);
	
	strData.ReleaseBuffer();
}

LRESULT CAddressBookDlg::OnBnClickedButtonNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAddNewAddress dlg;
	if(dlg.DoModal() == IDOK)
		LoadServerList();

	return 0;
}

LRESULT CAddressBookDlg::OnBnClickedButtonEdit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString strData = GetSelectedTextData();
	if(strData.IsEmpty())
		return 0;

	int nSelectPos = GetSelectedPos();

	CAddNewAddress dlg;
	dlg.m_bEditMode = true;
	dlg.m_strEditParams = strData;
	if(dlg.DoModal() == IDOK)
	{
		LoadServerList();
		HWND hWnd = GetDlgItem(IDC_LIST_SERVERS);
		if(ListView_GetItemCount(hWnd) > nSelectPos)
			ListView_SetItemState(hWnd,nSelectPos,LVIS_SELECTED,LVIS_SELECTED);
	}

	return 0;
}

LRESULT CAddressBookDlg::OnBnClickedButtonDelete(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(MessageBox("Are you sure you want to delete the selected entry?","Delete FTP Server",MB_YESNO) != IDYES)
		return 0;
	CString strData = GetSelectedTextData();
	if(strData.IsEmpty())
		return 0;
	for(int n=0;n<m_straEntries.GetSize();n++)
	{
		CString strTemp = m_straEntries[n];
		if(strData == strTemp)
		{
			m_straEntries.RemoveAt(n);
			SaveEntries();
			LoadServerList();
			return 1;
		}			
	}

	return 0;
}

CString CAddressBookDlg::GetSelectedTextData()
{
	HWND hWnd = GetDlgItem(IDC_LIST_SERVERS);
	int nCount = ListView_GetItemCount(hWnd);
    for(int n=0;n<nCount;n++)
	{
		if(ListView_GetItemState(hWnd,n,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strEntry;
			ListView_GetItemText(hWnd,n,0,strEntry.GetBuffer(1024),1024);
			strEntry.ReleaseBuffer();
			return LookUpDataForName(strEntry);
		}
	}
	return "";
}

int CAddressBookDlg::GetSelectedPos()
{
	HWND hWnd = GetDlgItem(IDC_LIST_SERVERS);
	int nCount = ListView_GetItemCount(hWnd);
    for(int n=0;n<nCount;n++)
	{
		if(ListView_GetItemState(hWnd,n,LVIS_SELECTED) & LVIS_SELECTED)
		{
			return n;
		}
	}
	return -1;
}

CString CAddressBookDlg::LookUpDataForName(CString strName)
{
	CString strData;
	for(int n=0;n<m_straEntries.GetSize();n++)
	{
		strData = m_straEntries[n];
		if(ParseXML("Name",strData) == strName)
			return strData;
	}
	return "";
}

void CAddressBookDlg::LoadServerList()
{
	HWND hWnd = GetDlgItem(IDC_LIST_SERVERS);
	ListView_DeleteAllItems(hWnd);

	// load entries
	LoadEntries();
	ATLTRACE("LoadEntries\r\n");

	for(int n=0;n<m_straEntries.GetSize();n++)
	{
		CString strData = m_straEntries[n];
		ATLTRACE(strData + "\r\n\r\n");

		CString strName = ParseXML("Name",strData);
		InsertListEntry(strName);
	}
	if(ListView_GetItemCount(hWnd) > 0)
		ListView_SetItemState(hWnd,0,LVIS_SELECTED,LVIS_SELECTED);
}

void CAddressBookDlg::LoadEntries()
{
	m_straEntries.RemoveAll();

	CString strBasePath = MyGetProfileString("InstallPath",DEFAULT_INSTALL_PATH);
	if(strBasePath.Right(1) != "\\") 
		strBasePath += "\\";
	strBasePath += "entries.dat";
	
	CString strData = ReadEncryptedFile(strBasePath,ENCRYPT_KEY);
	
	int nPos = -1;
	CString strTemp;
	while((nPos = strData.Find("</Entry>")) != -1)
	{
		strTemp = ParseXML("Entry",strData);
		if(!strTemp.IsEmpty())
			m_straEntries.Add(strTemp);
		strData = strData.Mid(nPos + (int)strlen("</Entry>"));	
	}
	SortEntries();
}

LRESULT CAddressBookDlg::OnItemchangedList_servers(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	int nPos = GetSelectedPos();
	if(nPos != -1)
	{
		CString strData = GetSelectedTextData();
		CString strURL = ParseXML("URL",strData);
		SetDlgItemText(IDC_STATIC_SERVER_URL_TEXT,strURL);
	}
	return 0;
}


LRESULT CAddressBookDlg::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPaintDC dc(m_hWnd);
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect,RGB(255,255,255));

	return 0;
}

BOOL CAddressBookDlg::LoadURLData(CString strData)
{
	CString strURL = ParseXML("URL",strData);
	CString strUser = ParseXML("User",strData);
	CString strPass = ParseXML("Pass",strData);
	CString strPort = ParseXML("Port",strData);
	CString strTemp;
	BOOL bAnonymous = (strPass.IsEmpty());
	
	if(strURL.IsEmpty())
	{
		MessageBox("You must enter a URL for the FTP server. eg. ftp.microsoft.com","Error");
		return 0;
	}

	// strip any ftp:// from url
	if((UINT)strURL.GetLength() > (int)strlen("ftp://"))
	{
		strTemp = strURL.Left((int)strlen("ftp://"));
		strTemp.MakeLower();
	}
	if(strTemp == "ftp://")
		strURL = strURL.Mid((int)strlen("ftp://"));

	if(!bAnonymous)
	{
		// strip any username pass from url
		if(strURL.Find('@') != -1)
			strURL = strURL.Mid(strURL.Find('@')+1);

		if(strUser.IsEmpty() || strPass.IsEmpty())
		{
			MessageBox("This address does not have a username and password, edit this entry.","Error");
			return 0;
		}
		strUser.Replace("@","%40");
		strUser.Replace(":","%3a");
		strPass.Replace("@","%40");
		strPass.Replace(":","%3a");
		// add username pass
		strTemp = strUser + ":" + strPass + "@";
		strURL = strTemp + strURL;
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
		// add port
		strTemp2 += ":" + strPort;
		strTemp2 += strTemp;
		strURL = strTemp2;			
	}

	// add header
	strURL = "ftp://" + strURL;

	m_strName = ParseXML("Name",strData);
	m_strLocalPath = ParseXML("LocalPath",strData);
	MyWriteProfileString("LastServer",m_strName);

	m_strURL = strURL;

	// set passive mode
	SetPasvMode(ParseXML("PasvMode",strData) == "TRUE");

	return true;
}

void CAddressBookDlg::SortEntries()
{
	QuickSort(0, m_straEntries.GetSize() - 1);
}

// QuickSort implementation
void CAddressBookDlg::QuickSort (int nLower, int nUpper)
{
    // Check for non-base case
    if (nLower < nUpper)
    {
        // Split and sort partitions
        int nSplit = Partition (nLower, nUpper);
        QuickSort (nLower, nSplit - 1);
        QuickSort (nSplit + 1, nUpper);
    }
}

// QuickSort partition implementation
int CAddressBookDlg::Partition (int nLower, int nUpper)
{
    // Pivot with first element
    int nLeft = nLower + 1;
    CString szPivot = m_straEntries[nLower];
    int nRight = nUpper;
    // Partition array elements
    CString szSwap;
    while (nLeft <= nRight)
    {
        // Find item out of place
        while (nLeft <= nRight && (ParseXML("Name",m_straEntries[nLeft]).CompareNoCase(ParseXML("Name",szPivot)) <= 0))
            nLeft = nLeft + 1;
        while (nLeft <= nRight && (ParseXML("Name",m_straEntries[nRight]).CompareNoCase(ParseXML("Name",szPivot)) > 0))
            nRight = nRight - 1;
        // Swap values if necessary
        if (nLeft < nRight)
        {
            szSwap = m_straEntries[nLeft];
            m_straEntries[nLeft] = m_straEntries[nRight];
            m_straEntries[nRight] = szSwap;
            nLeft = nLeft + 1;
            nRight = nRight - 1;
        }
    }
    // Move pivot element
    szSwap = m_straEntries[nLower];
    m_straEntries[nLower] = m_straEntries[nRight];
    m_straEntries[nRight] = szSwap;
    return nRight;
}
