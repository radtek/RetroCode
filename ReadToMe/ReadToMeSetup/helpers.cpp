


#include "stdafx.h"
#include "helpers.h"
#include "crypto\\rijndael.h"
#include <direct.h>
#include "defines.h"
#include "ModulVer.h"

#define PACKVERSION(major,minor) MAKELONG(minor,major)
typedef HRESULT (STDAPICALLTYPE *CTLREGPROC)(void) ; 

HRESULT CreateShortCut(LPCSTR pszShortcutFile, LPSTR pszLink,LPSTR pszDesc)
{
	CString str = pszShortcutFile;
	str += " ";
	str += pszLink;
	str += " ";
	str += pszDesc;

	HRESULT hres;		 
	IShellLink *psl;
	// Create an IShellLink object and get a pointer to the IShellLink 
	// interface (returned from CoCreateInstance).
	hres = CoCreateInstance (CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
	IID_IShellLink, (void **)&psl);
	if (SUCCEEDED (hres))
	{
		IPersistFile *ppf;
		// Query IShellLink for the IPersistFile interface for 
		// saving the shortcut in persistent storage.
		hres = psl->QueryInterface (IID_IPersistFile, (void **)&ppf);
		if (SUCCEEDED (hres))
		{ 
			WCHAR wsz[MAX_PATH]; // buffer for Unicode string
			// Set the path to the shortcut target.
			hres = psl->SetPath (pszShortcutFile);
			// Set the description of the shortcut.
			hres = psl->SetDescription (pszDesc);
			// Ensure that the string consists of ANSI characters.
			MultiByteToWideChar (CP_ACP, 0, pszLink, -1, wsz, MAX_PATH);
			// Save the shortcut via the IPersistFile::Save member function.
			hres = ppf->Save (wsz, false);
			// Release the pointer to IPersistFile.
			ppf->Release ();
		}
		// Release the pointer to IShellLink.
		psl->Release ();
	}
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

CString ReadEncryptedFile(CString strPath,CString strKey)
{
	unsigned char* pszBuffer = NULL;
	if(!FileExists(strPath))
		return "";
   	
	DWORD dwSize = 0;
	CFile fp;
	if(fp.Open(strPath))
	{
		dwSize = (DWORD)fp.GetSize();
		pszBuffer = new unsigned char[dwSize+1];
		UINT nRead = fp.Read(pszBuffer,dwSize);
		fp.Close();
	}
	
	CString strData;
	if(dwSize > 0)
	{
		// copy CString key to key buffer
		unsigned char szKey[32];
		ZeroMemory(szKey,32);
		DWORD dwKeySize = strKey.GetLength();
		if(dwKeySize > 32)
			dwKeySize = 32;
		memcpy((void*)szKey,(void*)strKey.GetBuffer(dwKeySize),dwKeySize);
		strKey.ReleaseBuffer();
		Rijndael rin;
		int dwOutLen = dwSize + 16;
		// init decrypt
		rin.init(Rijndael::CBC,Rijndael::Decrypt,szKey,Rijndael::Key32Bytes);
		unsigned char* pszPlainText = new unsigned char[dwOutLen];
		int nLen = rin.padDecrypt((unsigned char*)pszBuffer,dwSize,pszPlainText);

		if(nLen > 0 && nLen < dwOutLen)
		{
			pszPlainText[nLen] = '\0';
			strData = pszPlainText;			
		}
		delete [] pszPlainText;
		pszPlainText = NULL;
	}
	if(pszBuffer)
	{
		delete [] pszBuffer;
		pszBuffer = NULL;
	}
	return strData;
}

BOOL WriteEncryptedFile(CString strPath,CString strKey,CString strData)
{
	// copy CString key to key buffer
	unsigned char szKey[32];
	ZeroMemory(szKey,32);
	DWORD dwKeySize = strKey.GetLength();
	if(dwKeySize > 32)
		dwKeySize = 32;
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
		return false;

	CFile fp;
	if(fp.Create(strPath))
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

BOOL GetIsOSTypeWin9X()
{
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);

	if(osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
	{
		// win95
		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
			return true;
		// win98
		else 	
		if(osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
			return true;
	}
	return false;

}

//GetFileVersionInfo ?
CString GetFileVersion(CString strPath)
{
	CString strVer;
	CModuleVersion ver;
	if(ver.GetFileVersionInfo(strPath.GetBuffer(strPath.GetLength()))) 
	{
		strVer = ver.GetValue(_T("FileVersion"));
	}
	strPath.ReleaseBuffer();

	return strVer;
}

DWORD GetFileVersionDW(CString strPath)
{
	DWORD dwVal = 0;
	CString strVer;
	CModuleVersion ver;
	if(ver.GetFileVersionInfo(strPath.GetBuffer(strPath.GetLength()))) 
	{
		strVer = ver.GetValue(_T("FileVersion"));
	}
	strPath.ReleaseBuffer();

	if(!strVer.IsEmpty() && strVer.Find(".") != -1)
	{
		int n1 = atoi(strVer);
		strVer = strVer.Mid(strVer.Find(".") + 1);
		int n2 = atoi(strVer);
		dwVal = PACKVERSION(n1,n2);
	}

	return dwVal;
}

void LoadHTMLFile(CString strFile)
{
	HWND hWnd = GetDesktopWindow();
	ShellExecute(hWnd,"open",strFile,NULL,NULL,SW_MAXIMIZE);
}

BOOL DirectoryExists(CString strPath)
{
	return (GetFileAttributes(strPath) & FILE_ATTRIBUTE_DIRECTORY);  
}

BOOL FileExists(CString strPath)
{
	return CFile::FileExists(strPath);
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
	SetFileAttributes(strPath,FILE_ATTRIBUTE_NORMAL);
}

// check for disabled BHO's
void CheckBHOEnabled()
{
	BOOL bOK = false;
	CString strReturn = "";
	CRegKey reg;
	DWORD ulChars = 1024;
	if(reg.Open(HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\Main", KEY_READ) == ERROR_SUCCESS)
	{		 
		 bOK = (reg.QueryStringValue("Enable Browser Extensions",strReturn.GetBuffer(ulChars),&ulChars) == ERROR_SUCCESS);
		 strReturn.ReleaseBuffer();
		 reg.Close();
	}  
	if(strReturn.CompareNoCase("no") == 0)
	{
		if(MessageBox(NULL,"Error, Internet Explorer has browser helpers set to disabled. You need to enable them to run IE FTP Enhancer. Would you like to turn them on?","IE FTP Enhancer - Error",MB_YESNO) == IDYES)
		{
			if(reg.Create(HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\Main") == ERROR_SUCCESS)
			{
				 bOK = (reg.SetStringValue("Enable Browser Extensions","yes") == ERROR_SUCCESS);
				 reg.Close();
			}  
		}
		else
			MessageBox(NULL,"You can manually enable or disable browser helpers in the Internet Explorer/Tools/Internet Options/Advanced dialog by checking \"Enable third-party browser extensions\".","IE FTP Enhancer",MB_OK);
	}
}

CString GetRegisterURL()
{
	CString strReturn;
	CString strTag = "URL";
	CRegKey reg;
	if(reg.Open(HKEY_CURRENT_USER, "SOFTWARE\\eSellerate\\Affiliates\\PUB3186100900\\SKU01352798019", KEY_READ) == ERROR_SUCCESS)
	{
		 DWORD ulChars = 4024;
		 BOOL bOK = false;
		 bOK = (reg.QueryStringValue(strTag.GetBuffer(strTag.GetLength()),strReturn.GetBuffer(ulChars),&ulChars) == ERROR_SUCCESS);
		 strTag.ReleaseBuffer();
		 strReturn.ReleaseBuffer();
		 if(!bOK)
		 {
			 strReturn = DEFAULT_REGISTRATION_URL;
		 }
		 reg.Close();
	} 
	if(strReturn.IsEmpty())
		strReturn = DEFAULT_REGISTRATION_URL;
    return strReturn;
}

BOOL RegisterOCX(CString strPath)
{
	BOOL bResult = FALSE;

	char* szPathName = strPath.GetBuffer(strPath.GetLength()) ;
	HINSTANCE hModule = ::LoadLibrary(szPathName);
	strPath.ReleaseBuffer() ;
	if (!hModule)
		return FALSE ;
			
	CTLREGPROC DLLRegisterServer = (CTLREGPROC)::GetProcAddress(hModule,"DllRegisterServer" ) ;
	if (DLLRegisterServer != NULL)
	{
		HRESULT regResult = DLLRegisterServer() ;
		bResult = (regResult == NOERROR) ; 
	}
		
	::FreeLibrary(hModule) ;          
		
	return bResult;	
}

BOOL MyWriteProfileString(CString strTag, CString strValue)
{
	BOOL bOK = false;
	CRegKey reg;
	if(reg.Create(HKEY_CURRENT_USER, MY_REGISTRY_PATH) == ERROR_SUCCESS)
	{
		 bOK = (reg.SetStringValue(strTag.GetBuffer(strTag.GetLength()),strValue.GetBuffer(strValue.GetLength())) == ERROR_SUCCESS);
		 strTag.ReleaseBuffer();
		 strValue.ReleaseBuffer();
		 reg.Close();
	}  
	return bOK;
}

BOOL MyWriteProfileInt(CString strTag, DWORD dwValuse)
{
	BOOL bOK = false;
	CRegKey reg;
	if(reg.Create(HKEY_CURRENT_USER, MY_REGISTRY_PATH) == ERROR_SUCCESS)
	{
		 bOK = (reg.SetDWORDValue(strTag.GetBuffer(strTag.GetLength()),dwValuse) == ERROR_SUCCESS);
		 strTag.ReleaseBuffer();
		 reg.Close();
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

BOOL NeedsTTSINstall()
{
	int nVersion = 0;
	OSVERSIONINFO info;
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
	if(GetVersionEx(&info))
	{
		// Win9x/NT
		if(info.dwMajorVersion == 4)
			return true;
		if(info.dwMajorVersion == 5 && info.dwMinorVersion == 0) // windows 2000
			return true;
	} 
	return false;
}