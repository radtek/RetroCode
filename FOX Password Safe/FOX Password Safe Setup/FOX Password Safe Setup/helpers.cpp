
// helpers

#include "stdafx.h"
#include "helpers.h"
#include "crypto\\rijndael.h"
#include <direct.h>

CString	MyGetProfileString(CString strTag, CString strDefault, DWORD dwMaxChars)
{
	CString strReturn = "";
	CRegKey reg;
	if(reg.Open(HKEY_LOCAL_MACHINE, MY_REGISTRY_PATH, KEY_READ) == ERROR_SUCCESS)
	{
		 DWORD ulChars = dwMaxChars;
		 BOOL bOK = false;
		 bOK = (reg.QueryStringValue(strTag.GetBuffer(strTag.GetLength()),strReturn.GetBuffer(ulChars),&ulChars) == ERROR_SUCCESS);
		 strTag.ReleaseBuffer();
		 strReturn.ReleaseBuffer();
		 if(!bOK)
		 {
			 TRACE("Failed to read registry error: %d\r\n",GetLastError());		
			 strReturn = strDefault;
		 }
		 reg.Close();
	}  
	else
		strReturn = strDefault;
	return strReturn;
}

DWORD MyGetProfileInt(CString strTag, DWORD dwDefault)
{
	DWORD dwReturn = 0;
	CRegKey reg;
	if(reg.Open(HKEY_LOCAL_MACHINE, MY_REGISTRY_PATH, KEY_READ) == ERROR_SUCCESS)
	{
		 BOOL bOK = false;
		 bOK = (reg.QueryDWORDValue(strTag,dwReturn) == ERROR_SUCCESS);
		 if(!bOK)
		 {
			 TRACE("Failed to read registry error: %d\r\n",GetLastError());		
			 dwReturn = dwDefault;
		 }
		 reg.Close();
	}  
	else
		dwReturn = dwDefault;
	return dwReturn;
}

BOOL MyWriteProfileInt(CString strTag, DWORD dwValuse)
{
	BOOL bOK = false;
	CRegKey reg;
	if(reg.Create(HKEY_LOCAL_MACHINE, MY_REGISTRY_PATH) == ERROR_SUCCESS)
	{
		 bOK = (reg.SetDWORDValue(strTag.GetBuffer(strTag.GetLength()),dwValuse) == ERROR_SUCCESS);
		 strTag.ReleaseBuffer();
		 reg.Close();
	}  
	return bOK;
}

BOOL MyWriteProfileString(CString strTag, CString strValue)
{
	BOOL bOK = false;
	CRegKey reg;
	if(reg.Create(HKEY_LOCAL_MACHINE, MY_REGISTRY_PATH) == ERROR_SUCCESS)
	{
		 bOK = (reg.SetStringValue(strTag.GetBuffer(strTag.GetLength()),strValue.GetBuffer(strValue.GetLength())) == ERROR_SUCCESS);
		 strTag.ReleaseBuffer();
		 strValue.ReleaseBuffer();
		 reg.Close();
	}  
	return bOK;
}

CString ReadEncryptedFile(CString strPath,CString strKey)
{
	CString strReply;
	unsigned char* pszBuffer = NULL;
	BOOL bOK = true;
	UINT dwSize = 0;
	TRY
	{
		CFile fp;
		if(fp.Open(strPath,CFile::modeRead|CFile::shareDenyWrite))
		{
			dwSize = (UINT)fp.GetLength();
			pszBuffer = new unsigned char[dwSize];
			fp.Read(pszBuffer,dwSize);
			fp.Close();
		}
		else
			bOK = false;
	}
	CATCH(CFileException,e)
	{
		TRACE("ReadEncryptedFile CFileException\r\n");
		bOK = false;
	}
	END_CATCH
	
	if(!bOK)
	{
		if(pszBuffer)
		{
			delete [] pszBuffer;
			pszBuffer = NULL;
		}
		return "";
	}

	if(dwSize > 0)
	{
		// copy CString key to key buffer
		unsigned char szKey[32];
		ZeroMemory(szKey,32);
		DWORD dwKeySize = strKey.GetLength();
		memcpy((void*)szKey,(void*)strKey.GetBuffer(dwKeySize),dwKeySize);
		strKey.ReleaseBuffer();
		Rijndael rin;
		DWORD dwOutLen = dwSize + 16;
		
		unsigned char* pBuff = new unsigned char[dwSize + 100];
		ZeroMemory(pBuff,dwSize + 100);

		// init decrypt
		rin.init(Rijndael::CBC,Rijndael::Decrypt,szKey,Rijndael::Key32Bytes);
		DWORD nLen = rin.padDecrypt(pszBuffer,dwSize,(unsigned char*)pBuff);
		if(pszBuffer)
		{
			delete [] pszBuffer;
			pszBuffer = NULL;
		}	
		if(nLen < 0)
			return "";
		if(nLen < dwSize + 100)
			pBuff[nLen] = '\0';
		strReply = pBuff;
		delete [] pBuff;
	}

	return strReply;
}

BOOL WriteEncryptedFile(CString strPath,CString strKey,CString strData)
{
	// copy CString key to key buffer
	unsigned char szKey[32];
	ZeroMemory(szKey,32);
	DWORD dwKeySize = strKey.GetLength();
	memcpy((void*)szKey,(void*)strKey.GetBuffer(dwKeySize),dwKeySize);
	strKey.ReleaseBuffer();
	Rijndael rin;
	DWORD dwSize = strData.GetLength();

	unsigned char* pBuff = new unsigned char[dwSize + 100];
	ZeroMemory(pBuff,dwSize + 100);

	// init encrypt
	rin.init(Rijndael::CBC,Rijndael::Encrypt,szKey,Rijndael::Key32Bytes);
	int nLen = rin.padEncrypt((unsigned char*)strData.GetBuffer(dwSize),dwSize,(unsigned char*)pBuff);
	strData.ReleaseBuffer();
	
	if(nLen < 0)
	{
		delete [] pBuff;
		return false;
	}

	CFile fp;
	if(fp.Open(strPath,CFile::modeWrite|CFile::modeCreate|CFile::shareExclusive))
	{
		fp.Write(pBuff,nLen);
		fp.Close();
	}
	else
	{
		delete [] pBuff;
		return false;
	}

	delete [] pBuff;

	return true;
}

CString ParseXML(CString strTag,CString strParams)
{
	// make not case sensitive
	CString strLower = strParams;
	strLower.MakeLower();
	strTag.MakeLower();
	
	int nFind = strLower.Find("<" + strTag + ">");
	if(nFind == -1)
		return "";
	CString strTemp = strParams.Mid(nFind + strTag.GetLength() + 2);
	strLower = strTemp;
	strLower.MakeLower();

	nFind = strLower.Find("</" + strTag + ">");
	if(nFind == -1)
		return "";
	strTemp = strTemp.Left(nFind);

	strTemp.TrimLeft();
	strTemp.TrimRight(" \t");

	return strTemp;
}

CString ReplaceXML(CString strParam,CString strTag,CString strParams)
{
	CString strLower = strParams;
	strLower.MakeLower();
	CString strTagLower = strTag;
	strTagLower.MakeLower();

	int nFind = strLower.Find("<" + strTagLower + ">");
	//not found just append
	if(nFind == -1)
	{
		return strParams + "<" + strTag + ">" + strParam + "</" + strTag + ">";
	}
	else
	{
		CString strTemp = strParams.Left(nFind + strTag.GetLength() + 2);
		strTemp += strParam;

		nFind = strLower.Find("</" + strTagLower + ">");
		strTemp += strParams.Mid(nFind);
		
		strTemp.TrimLeft();
		strTemp.TrimRight();

		return strTemp;
	}
}

HRESULT CreateShortCut(LPCSTR pszShortcutFile, LPSTR pszLink,LPSTR pszDesc)
{
	CString str = pszShortcutFile;
	str += " ";
	str += pszLink;
	str += " ";
	str += pszDesc;

	HRESULT hres;		 
	IShellLink *psl;
	CoInitialize(NULL);
	// Create an IShellLink object and get a pointer to the IShellLink 
	// interface (returned from CoCreateInstance).
	hres = CoCreateInstance (CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,IID_IShellLink, (void **)&psl);
	if (SUCCEEDED (hres))
	{
		IPersistFile *ppf;
		// Query IShellLink for the IPersistFile interface for 
		// saving the shortcut in persistent storage.
		hres = psl->QueryInterface (IID_IPersistFile, (void **)&ppf);
		if (SUCCEEDED (hres))
		{ 
			WCHAR wsz [MAX_PATH]; // buffer for Unicode string
			// Set the path to the shortcut target.
			hres = psl->SetPath (pszShortcutFile);
			// Set the description of the shortcut.
			hres = psl->SetDescription (pszDesc);
			// Ensure that the string consists of ANSI characters.
			MultiByteToWideChar (CP_ACP, 0, pszLink, -1, wsz, MAX_PATH);
			// Save the shortcut via the IPersistFile::Save member function.
			hres = ppf->Save (wsz, TRUE);
			// Release the pointer to IPersistFile.
			ppf->Release ();
		}
		// Release the pointer to IShellLink.
		psl->Release ();
	}
	CoUninitialize();  
	return hres;
} 

CString GetProgramsPath()
{
	CString strReturn;
	CRegKey reg;
	if(reg.Open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", KEY_READ) == ERROR_SUCCESS)
	{
		 DWORD ulChars = 1024;
		 BOOL bOK = false;
		 bOK = (reg.QueryStringValue("Programs",strReturn.GetBuffer(ulChars),&ulChars) == ERROR_SUCCESS);
		 strReturn.ReleaseBuffer();
		 if(!bOK)
		 {
			 ATLTRACE("Failed to read registry error: %d",GetLastError());		
		 }
		 reg.Close();
	}  
	
	return strReturn;
}

BOOL CreateProgramsLink(CString strExePath,CString strLinkName,CString strDisplayName)
{
	CString strPathStartup;
	strPathStartup = GetProgramsPath();

	// put is program files
	CString strLink;
	strLink = strPathStartup + "\\" + strLinkName;
	if(strLinkName.Find("\\")!= -1)
	{
		MyMakePath(strLink.Left(strLink.ReverseFind('\\')));
	}
	HRESULT hr = CreateShortCut(strExePath,strLink.GetBuffer(strLink.GetLength()),strDisplayName.GetBuffer(strDisplayName.GetLength()));
	strLink.ReleaseBuffer();
	strDisplayName.ReleaseBuffer(); 

	return (hr == 0);
}

CString GetWinDesktopPath()
{
	CString strReturn;
	CRegKey reg;
	if(reg.Open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", KEY_READ) == ERROR_SUCCESS)
	{
		 DWORD ulChars = 1024;
		 BOOL bOK = false;
		 bOK = (reg.QueryStringValue("Desktop",strReturn.GetBuffer(ulChars),&ulChars) == ERROR_SUCCESS);
		 strReturn.ReleaseBuffer();
		 if(!bOK)
		 {
			 ATLTRACE("Failed to read registry error: %d",GetLastError());		
		 }
		 reg.Close();
	}  
	return strReturn;	
}

BOOL CreateDesktopLink(CString strExePath,CString strLinkName,CString strDisplayName)
{
	CString strPathDeskTop;
	strPathDeskTop = GetWinDesktopPath();

	// put is program files
	CString strLink;
	strLink = strPathDeskTop + "\\" + strLinkName;
	if(strLinkName.Find("\\")!= -1)
	{
		MyMakePath(strLink.Left(strLink.ReverseFind('\\')));
	}
	HRESULT hr = CreateShortCut(strExePath,strLink.GetBuffer(strLink.GetLength()),strDisplayName.GetBuffer(strDisplayName.GetLength()));
	strLink.ReleaseBuffer();
	strDisplayName.ReleaseBuffer(); 

	return (hr == 0);
}

BOOL DirectoryExists(CString strPath)
{
	CFileStatus fs;
	if(!CFile::GetStatus(strPath,fs))
		return false;
	
	if(!(fs.m_attribute & CFile::directory))
		return false;
	else
		return true;
}

BOOL FileExists(CString strPath)
{
	CFileStatus fs;
	return (CFile::GetStatus(strPath,fs));
}

BOOL MyMakePath(CString strPath)
{
	CString strTemp = strPath;
	int nFind = -1;
	int nCounter = 0;
	BOOL bFirst = true;
	while((nFind = strTemp.Find('\\')) != -1)
	{
		nCounter += nFind;
		strTemp = strTemp.Mid(nFind+1);
		if(!bFirst)
		{
			CString strTest = strPath.Left(nCounter);
			if(!FileExists(strTest))
				if(_mkdir(strTest)) // 0 = OK
					return false;
		}
		nCounter ++;
		bFirst = false;
	}
	if(!FileExists(strPath))
		if(_mkdir(strPath)) // 0 = OK
			return false;

	return true;
}

void MarkFileNormal(CString strPath)
{
	TRY
	{
		CFileStatus fs;
		if(CFile::GetStatus(strPath,fs))
		{
			fs.m_attribute = CFile::normal;
			CFile::SetStatus(strPath,fs);
		}
	}
	CATCH(CFileException,e)
	{

	}
	END_CATCH
}

CString GetDefaultBrowserPath()
{
	CString strReturn = "";
	CRegKey reg;
	// get default browser
	if(reg.Open(HKEY_CLASSES_ROOT, "HTTP\\shell\\open\\command", KEY_READ) == ERROR_SUCCESS)
	{
		 DWORD ulChars = 4024;
		 BOOL bOK = false;
		 bOK = (reg.QueryStringValue(NULL,strReturn.GetBuffer(ulChars),&ulChars) == ERROR_SUCCESS);
		 strReturn.ReleaseBuffer();
		 if(!bOK)
		 {
			 TRACE("Failed to read registry error: %d\r\n",GetLastError());		
			 strReturn = "";
		 }
		 reg.Close();
	}  
	// if empty get path to IExplorer
	if(strReturn.IsEmpty())
	{
		if(reg.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths", KEY_READ) == ERROR_SUCCESS)
		{
			DWORD ulChars = 4024;
			BOOL bOK = false;
			bOK = (reg.QueryStringValue("IEXPLORE.EXE",strReturn.GetBuffer(ulChars),&ulChars) == ERROR_SUCCESS);
			strReturn.ReleaseBuffer();
			if(!bOK)
			{
				TRACE("Failed to read registry error: %d\r\n",GetLastError());		
				strReturn = "";
			}
			reg.Close();
		}  
	}
	return strReturn;
}

void LoadURLInBrowser(CString strURL)
{
	// load URL in default web browser
	CString strPath = GetDefaultBrowserPath();
	BOOL bOK = false;
	if(!strPath.IsEmpty())
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		si.wShowWindow = SW_MAXIMIZE;
		ZeroMemory(&pi, sizeof(pi));
		if(strPath.Find("%1") == -1)
		{
			strPath = strPath + " " + strURL;
			strPath.Replace("\"\"","\"");
		}
		else
		{
			strPath.Replace("%1",strURL);
		}
		// Start the child process. 
		bOK = CreateProcess( NULL,strPath.GetBuffer(strPath.GetLength()),NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);
		strPath.ReleaseBuffer();					
	}
	if(!bOK)
		::ShellExecute(NULL, "open", strURL, NULL, NULL, SW_SHOWNORMAL);
}

BOOL LoadExe(CString strExePath)
{
	BOOL bOK = false;
	if(!strExePath.IsEmpty())
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		si.wShowWindow = SW_SHOW;
		ZeroMemory(&pi, sizeof(pi));
		// Start the child process. 
		bOK = CreateProcess( NULL,strExePath.GetBuffer(strExePath.GetLength()),NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);
		strExePath.ReleaseBuffer();					
	}
	return bOK;
}

void CreateLinkAddRemovePrograms(CString strUninstallerPath,CString strDisplayName)
{
	BOOL bOK = false;
	CRegKey reg;
	if(reg.Create(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + CString(strDisplayName)) == ERROR_SUCCESS)
	{
		bOK = (reg.SetStringValue("DisplayName",strDisplayName.GetBuffer(strDisplayName.GetLength())) == ERROR_SUCCESS);
		strDisplayName.ReleaseBuffer();
		bOK = (reg.SetStringValue("UninstallString",strUninstallerPath.GetBuffer(strUninstallerPath.GetLength())) == ERROR_SUCCESS);
		strUninstallerPath.ReleaseBuffer();	
		bOK = (reg.SetStringValue("DisplayIcon",strUninstallerPath.GetBuffer(strUninstallerPath.GetLength())) == ERROR_SUCCESS);
		strUninstallerPath.ReleaseBuffer();	
		reg.Close();
	}	
}

CString GetRegisterURL()
{
	CString strReturn;
	CString strTag = "URL";
	CRegKey reg;
	if(reg.Open(HKEY_CURRENT_USER, "SOFTWARE\\eSellerate\\Affiliates\\PUB3186100900\\SKU65807647859", KEY_READ) == ERROR_SUCCESS)
	{
		 DWORD ulChars = 4024;
		 BOOL bOK = false;
		 bOK = (reg.QueryStringValue(strTag.GetBuffer(strTag.GetLength()),strReturn.GetBuffer(ulChars),&ulChars) == ERROR_SUCCESS);
		 strTag.ReleaseBuffer();
		 strReturn.ReleaseBuffer();
		 if(!bOK)
		 {
			 TRACE("Failed to read registry error: %d\r\n",GetLastError());		
			 strReturn = ONLINE_REGISTRATION_PAGE;
		 }
		 reg.Close();
	} 
	if(strReturn.IsEmpty())
		strReturn = ONLINE_REGISTRATION_PAGE;
    return strReturn;
}

