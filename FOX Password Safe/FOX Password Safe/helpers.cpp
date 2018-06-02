
#include "stdafx.h"
#include "helpers.h"
#include "crypto\\rijndael.h"
#include "atlbase.h"
#include <direct.h>
#include ".\encryptfiledlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void DebugMessage(CString strMsg)
{
	CString strPath;
	GetModuleFileName(NULL,strPath.GetBuffer(MAX_PATH),MAX_PATH);
	strPath.ReleaseBuffer();
	strPath = strPath.Left(strPath.ReverseFind('\\') + 1);
	strPath += "debug.log";
	CFile fp;
	if(fp.Open(strPath,CFile::modeWrite|CFile::modeCreate|CFile::modeNoTruncate))
	{
		fp.SeekToEnd();
		if(strMsg.Right(2) != "\r\n")
			strMsg += "\r\n";
		DWORD dwSize = strMsg.GetLength();
		fp.Write(strMsg.GetBuffer(dwSize),dwSize);
		strMsg.ReleaseBuffer();
		fp.Close();
	}
}

CString	MyGetProfileString(CString strTag, CString strDefault, DWORD dwMaxChars)
{
	CString strReturn = "";
	CRegKey reg;
	if(reg.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\STEVEFOXOVER\\FOXPasswordSafe\\Settings", KEY_READ) == ERROR_SUCCESS)
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
	if(reg.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\STEVEFOXOVER\\FOXPasswordSafe\\Settings", KEY_READ) == ERROR_SUCCESS)
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
	if(reg.Create(HKEY_LOCAL_MACHINE, "SOFTWARE\\STEVEFOXOVER\\FOXPasswordSafe\\Settings") == ERROR_SUCCESS)
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
	if(reg.Create(HKEY_LOCAL_MACHINE, "SOFTWARE\\STEVEFOXOVER\\FOXPasswordSafe\\Settings") == ERROR_SUCCESS)
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

BOOL IsRegCodeGood(CString strReg)
{
	// 28320405-7FEB-41a1-EC2U-24E137B536E4

	// first sect, last 2 number add to 5
	// 2nd last sect, 1st and 4rd digit are vowels A E I O U
	// last sect, first and last number add to 6

	if(strReg.IsEmpty())
		return FALSE;

	// 1st sect
	int nFind = strReg.Find('-');
	if(nFind == -1)
		return false;
	CString strTest = strReg.Left(nFind);
	int nNum = atoi(CString(strTest.GetAt(strTest.GetLength()-1)));
	nNum += atoi(CString(strTest.GetAt(strTest.GetLength()-2)));
	if(nNum != 5)
		return FALSE;
	
	// 2nd sect
	strTest = strReg.Left(strReg.ReverseFind('-'));
	strTest = strTest.Mid(strTest.ReverseFind('-')+1);
	strTest.MakeUpper();	
	char ch = strTest.GetAt(0);
	if(ch != 'A' && ch != 'E' && ch != 'I' && ch != 'O' && ch != 'U')
		return FALSE;
	ch = strTest.GetAt(3);
	if(ch != 'A' && ch != 'E' && ch != 'I' && ch != 'O' && ch != 'U')
		return FALSE;

	// last sect
	strTest = strReg.Mid(strReg.ReverseFind('-')+1);
	nNum = atoi(CString(strTest.GetAt(0)));
	nNum += atoi(CString(strTest.GetAt(strTest.GetLength()-1)));
	if(nNum != 6)
		return FALSE;

	return TRUE;
}

BOOL IsRegistered()
{
	CString strReg = MyGetProfileString("Reg","");
	return IsRegCodeGood(strReg);	
}

int GetFreeTrialDaysUsed()
{
	time_t tm;
	time(&tm);

	CString strFilePath;
	GetSystemDirectory(strFilePath.GetBuffer(MAX_PATH),MAX_PATH);
	strFilePath.ReleaseBuffer();
	strFilePath += "\\iq3R8.prn";

	CString strData = ReadEncryptedFile(strFilePath,REG_ENCRYPT_KEY);
	BOOL bExpired = (ParseXML("Expired",strData) == "TRUE");

	CString strInstallTime = ParseXML("InstallTime",strData);
	time_t tmTimeInstall;
	if(!strInstallTime.IsEmpty())
		tmTimeInstall = (long)atol(strInstallTime);
	else
		tmTimeInstall = (long)MyGetProfileInt("id",0);

	time_t tspan = tm - tmTimeInstall;
	DWORD dwDays = (long)tspan / 60;
	dwDays = dwDays / 60;
	dwDays = dwDays / 24;

	if(bExpired)
		return -1;
	else
		return dwDays;
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

CString ConvertToDateString(CString strDateInt,BOOL &bHasExpired)
{
	if(strDateInt.IsEmpty())
		return "";
	ULARGE_INTEGER n64Time;
	n64Time.QuadPart = _atoi64(strDateInt);
	FILETIME fileTime;
	fileTime.dwHighDateTime = n64Time.HighPart;
	fileTime.dwLowDateTime = n64Time.LowPart;
	CTime tm(fileTime);	
	if(tm < CTime::GetCurrentTime())
		bHasExpired = true;
	else
		bHasExpired = false;
	CString strTime = tm.Format("%A, %B %d, %Y");

	return strTime;
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
/*	CString strTest = strURL;
	strTest.MakeLower();
	if(strTest.Left(strlen(_T("http://"))) != _T("http://") &&
		strTest.Left(strlen(_T("https://"))) != _T("https://"))
		strURL = _T("http://") + strURL;
	::ShellExecute(NULL, "open", strURL, NULL, NULL, SW_SHOWNORMAL);
	return;
*/	// load URL in default web browser
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
		if(strPath.Find("%1") != -1)
			strPath.Replace("%1",strURL);
		else
		{
			strPath = strPath + " " + strURL;
			strPath.Replace("\"\"","\"");
		}
		// Start the child process. 
		bOK = CreateProcess( NULL,strPath.GetBuffer(strPath.GetLength()),NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);
		strPath.ReleaseBuffer();					
	}
	if(!bOK)
		::ShellExecute(NULL, "open", strURL, NULL, NULL, SW_SHOWNORMAL);
}

BOOL IsWindowsNT4()
{
	BOOL bNT4 = false;
	OSVERSIONINFO info;
	ZeroMemory(&info,sizeof(OSVERSIONINFO));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	BOOL bOK = GetVersionEx(&info);

	bNT4 = (info.dwPlatformId == VER_PLATFORM_WIN32_NT && info.dwMajorVersion == 4 && info.dwMinorVersion == 0);
	return bNT4;
}

void SetAutoStartExe(BOOL bAutoStart)
{
	CRegKey reg;
	BOOL bOK = true;
	if(bAutoStart)
	{
		CString strExePath;
		GetModuleFileName(NULL,strExePath.GetBuffer(MAX_PATH),MAX_PATH);
		strExePath.ReleaseBuffer();

		if(reg.Create(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run") == ERROR_SUCCESS)
		{
			bOK = (reg.SetStringValue(MY_APP_TITLE,strExePath) == ERROR_SUCCESS);
			reg.Close();
		}
	}
	else
	{
		if(reg.Create(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run") == ERROR_SUCCESS)
		{
			if(reg.DeleteValue(MY_APP_TITLE) != ERROR_SUCCESS)
			{
				TRACE("Failed to delete value SetAutoStartExe error:%d",GetLastError());
			}
			reg.Close();
		}
	}
	if(!bOK)
		AfxMessageBox("Error, failed to change start when Windows starts setting.");
}

BOOL CanShowExpiredDlg()
{
	BOOL bCanShowExpireDlg = (MyGetProfileInt("DontShowExpireDlg",0) == 0);
	return bCanShowExpireDlg;	
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

CStringArray* LoadEntries(CString strData,BOOL& bRemovedExtras)
{
	CStringArray* pStra = new CStringArray();
	CString strVersion = ParseXML("Version",strData);
	int nFind = -1;
	bRemovedExtras = false;
	CStringArray straExtras;
	while((nFind = strData.Find("</Entry>")) != -1)
	{
		CString strEntry = ParseXML("Entry",strData);
		strData = strData.Mid(nFind + (int)strlen("</Entry>"));
		// check for extra not needed headers
		CString strHeader = ParseXML("Header",strEntry);
		CString strDescription = ParseXML("Description",strEntry);
		// single header only
		if(strDescription.IsEmpty())
		{
			straExtras.Add(strHeader);
		}
		else // check if we already have header for this entry
		{
			for(int n=0;n<straExtras.GetCount();n++)
			{
				CString strTestHeader = straExtras.GetAt(n);
				// remove spare header
				if(strTestHeader.CompareNoCase(strHeader) == 0)
				{
					straExtras.RemoveAt(n);
					for(int x=0;x<pStra->GetCount();x++)
					{
						CString strTestEntry = pStra->GetAt(x);
						if(ParseXML("Header",strTestEntry).CompareNoCase(strHeader) == 0
							&& ParseXML("Description",strTestEntry).IsEmpty())
						{					
							pStra->RemoveAt(x);
							bRemovedExtras = true;
							break;
						}
					}
					break;
				}
			}
		}
		if(!strHeader.IsEmpty() || !strDescription.IsEmpty())
			pStra->Add(strEntry);					
	}
	return pStra;
}

CString GetGUID()
{
	CString strGUID;
	GUID guid;
	HRESULT hr = CoCreateGuid(&guid);
	if(hr == S_OK)
	{
		BYTE * buf;
		UuidToString((UUID*)&guid, &buf);
		strGUID = (LPTSTR)buf;
		RpcStringFree(&buf);
		strGUID.MakeUpper();	
	}
	return strGUID;
}

BOOL EncryptFile(CString strData)
{
	CString strPath = ParseXML("FilePath",strData);
	CString strEncPath = ParseXML("EncFilePath",strData);
	CString strPassword = ParseXML("Password",strData);

	CEncryptFileDlg dlg;
	dlg.m_strEncryptFile = strEncPath;
	dlg.m_strPassword = strPassword;
	dlg.m_strPlainFile = strPath;
	dlg.m_bIsEncrypting = true;
	dlg.DoModal();
	return (!dlg.m_bCancelled && !dlg.m_bError);
}

BOOL UnEncryptFile(CString strData,BOOL bDeleteFile)
{
	CString strPath = ParseXML("FilePath",strData);
	CString strEncPath = ParseXML("EncFilePath",strData);
	CString strPassword = ParseXML("Password",strData);

	CEncryptFileDlg dlg;
	dlg.m_strEncryptFile = strEncPath;
	dlg.m_strPassword = strPassword;
	dlg.m_strPlainFile = strPath;
	dlg.m_bIsEncrypting = false;
	dlg.m_bRemoveFile = bDeleteFile;
	dlg.DoModal();
	return (!dlg.m_bCancelled && !dlg.m_bError);
}

char* EncryptBuffer(char* pBuf, DWORD& dwSize, CString strKey)
{
	// copy CString key to key buffer
	unsigned char szKey[32];
	ZeroMemory(szKey,32);
	DWORD dwKeySize = strKey.GetLength();
	memcpy((void*)szKey,(void*)strKey.GetBuffer(dwKeySize),dwKeySize);
	strKey.ReleaseBuffer();
	Rijndael rin;

	unsigned char* pEncBuf = new unsigned char[dwSize + 100];
	ZeroMemory(pEncBuf,dwSize + 100);

	// init encrypt
	rin.init(Rijndael::CBC,Rijndael::Encrypt,szKey,Rijndael::Key32Bytes);
	int nLen = rin.padEncrypt((unsigned char*)pBuf,dwSize,(unsigned char*)pEncBuf);
	
	if(nLen < 0)
	{
		delete [] pEncBuf;
		return NULL;
	}
	dwSize = nLen;
	return (char*)pEncBuf;
}

char* UnEncryptBuffer(char* pBufEnc, DWORD& dwSize, CString strKey)
{
	// copy CString key to key buffer
	unsigned char szKey[32];
	ZeroMemory(szKey,32);
	DWORD dwKeySize = strKey.GetLength();
	memcpy((void*)szKey,(void*)strKey.GetBuffer(dwKeySize),dwKeySize);
	strKey.ReleaseBuffer();
	Rijndael rin;

	unsigned char* pBuf = new unsigned char[dwSize + 100];
	ZeroMemory(pBuf,dwSize + 100);

	// init decrypt
	rin.init(Rijndael::CBC,Rijndael::Decrypt,szKey,Rijndael::Key32Bytes);
	int nLen = rin.padDecrypt((unsigned char*)pBufEnc,dwSize,pBuf);
	if(nLen < 0)
		return "";
	if(nLen < dwSize + 100)
		pBuf[nLen] = '\0';
	dwSize = nLen;
	return (char*)pBuf;
}

BOOL IsEncryptedFileEntry(CString strData)
{
	return (ParseXML("EncryptedFile",strData) == "TRUE");
}

BOOL IsFileEncrypted(CString strData)
{
	CString strPath = ParseXML("FilePath",strData);
	CString strEncPath = ParseXML("EncFilePath",strData);
	// check if file is encrypted
	if(FileExists(strEncPath) && !FileExists(strPath))
		return true;
	else
		return false;
}

BOOL IsBadFileEntry(CString strData)
{
	CString strPath = ParseXML("FilePath",strData);
	CString strEncPath = ParseXML("EncFilePath",strData);
	CString strPassword = ParseXML("Password",strData);

	if(strPath.IsEmpty() || strEncPath.IsEmpty() || strPassword.IsEmpty())
		return true;
	return false;
}

CString MakeTextSafeForXML(CString strText)
{
	int nFind = -1;
	CStringArray stra;
	stra.Add(_T("<Notes>"));
	stra.Add(_T("</Notes>"));
	stra.Add(_T("<Entry>"));
	stra.Add(_T("</Entry>"));

	for(int n=0;n<stra.GetCount();n++)
	{
		CString strTag = stra[n];
		strText.Replace(strTag,_T("< ") + strTag.Mid(1));
	}
	return strText;
}