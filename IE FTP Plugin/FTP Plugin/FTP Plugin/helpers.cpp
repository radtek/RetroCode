
// helpers

#include "stdafx.h"
#include "helpers.h"
#include "crypto\\rijndael.h"

CString	MyGetProfileString(CString strTag, CString strDefault, DWORD dwMaxChars)
{
	CString strReturn = "";
	CRegKey reg;
	if(reg.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\STEVEFOXOVER\\IEFtpPlugin\\Settings", KEY_READ) == ERROR_SUCCESS)
	{
		 DWORD ulChars = dwMaxChars;
		 BOOL bOK = false;
		 bOK = (reg.QueryStringValue(strTag.GetBuffer(strTag.GetLength()),strReturn.GetBuffer(ulChars),&ulChars) == ERROR_SUCCESS);
		 strTag.ReleaseBuffer();
		 strReturn.ReleaseBuffer();
		 if(!bOK)
		 {
			 ATLTRACE("Failed to read registry error: %d",GetLastError());		
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
	if(reg.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\STEVEFOXOVER\\IEFtpPlugin\\Settings", KEY_READ) == ERROR_SUCCESS)
	{
		 BOOL bOK = false;
		 bOK = (reg.QueryDWORDValue(strTag.GetBuffer(strTag.GetLength()),dwReturn) == ERROR_SUCCESS);
		 strTag.ReleaseBuffer();
		 if(!bOK)
		 {
			 ATLTRACE("Failed to read registry error: %d",GetLastError());		
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
	if(reg.Create(HKEY_LOCAL_MACHINE, "SOFTWARE\\STEVEFOXOVER\\IEFtpPlugin\\Settings") == ERROR_SUCCESS)
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
	if(reg.Create(HKEY_LOCAL_MACHINE, "SOFTWARE\\STEVEFOXOVER\\IEFtpPlugin\\Settings") == ERROR_SUCCESS)
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
	unsigned char* pszBuffer = NULL;
	DWORD dwSize = 0;
	CFile fp;
	if(fp.Open(strPath,GENERIC_READ,0))
	{
		dwSize = (DWORD)fp.GetSize();
		pszBuffer = new unsigned char[dwSize+1];
		fp.Read(pszBuffer,dwSize);
		fp.Close();
	}
	else
		return "";
	
	CString strData;
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
		
		unsigned char* pszPlainText = new unsigned char[dwSize + 100];
		ZeroMemory(pszPlainText,dwSize + 100);

		// init decrypt
		rin.init(Rijndael::CBC,Rijndael::Decrypt,szKey,Rijndael::Key32Bytes);
		DWORD nLen = rin.padDecrypt(pszBuffer,dwSize,pszPlainText);
		
		if(nLen > 0 && nLen < dwSize + 100)
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
	if(strReg.IsEmpty())
		return false;

	if(strReg.GetLength() != 16)
		return false;

	// 1st sect
	CString strTest;
	int nNum = atoi(strReg.Left(1));
	nNum = nNum * atoi(strReg.Mid(1,1));
	int nMagic = 3456 - nNum;
	strTest.Format("%d",nMagic);
	if(strTest != strReg.Mid(2,strTest.GetLength()))
		return false;

	// 2nd sect
	nNum = atoi(strReg.Mid(15,1));
	nNum = nNum * atoi(strReg.Mid(14,1));
	nMagic = 1987 - nNum;
	strTest.Format("%d",nMagic);
	if(strTest != strReg.Mid(14-strTest.GetLength(),strTest.GetLength()))
		return false;

	return true;
}

/*
BOOL IsRegCodeGood(CString strReg)
{
	// 9CC95325-B3A8-43ef-BAEB-22D6A4EBB967
	// first sect, last 2 number add to 7
	// 2nd last sect, 2nd and 3rd digit are vowels A E I O U
	// last sect, first and last number add to 9

	if(strReg.IsEmpty())
		return FALSE;

	// 1st sect
	int nFind = strReg.Find('-');
	if(nFind == -1)
		return false;
	CString strTest = strReg.Left(nFind);
	int nNum = atoi(CString(strTest.GetAt(strTest.GetLength()-1)));
	nNum += atoi(CString(strTest.GetAt(strTest.GetLength()-2)));
	if(nNum != 7)
		return FALSE;
	
	// 2nd sect
	strTest = strReg.Left(strReg.ReverseFind('-'));
	strTest = strTest.Mid(strTest.ReverseFind('-')+1);
	strTest.MakeUpper();	
	char ch = strTest.GetAt(1);
	if(ch != 'A' && ch != 'E' && ch != 'I' && ch != 'O' && ch != 'U')
		return FALSE;
	ch = strTest.GetAt(2);
	if(ch != 'A' && ch != 'E' && ch != 'I' && ch != 'O' && ch != 'U')
		return FALSE;

	// last sect
	strTest = strReg.Mid(strReg.ReverseFind('-')+1);
	nNum = atoi(CString(strTest.GetAt(0)));
	nNum += atoi(CString(strTest.GetAt(strTest.GetLength()-1)));
	if(nNum != 9)
		return FALSE;

	return TRUE;
}
*/
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
	strFilePath += "\\";
	strFilePath += APP_FILE;

	CString strData = ReadEncryptedFile(strFilePath,ENCRYPT_KEY);
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

void SetPasvMode(BOOL bTrue)
{
	CString strValue;
	bTrue ? strValue="yes" : strValue="no";
	CRegKey reg;
	if(reg.Create(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Internet Explorer\\AdvancedOptions\\BROWSE\\FTPPASV") == ERROR_SUCCESS)
	{
		 BOOL bOK = (reg.SetStringValue("CheckedValue",strValue.GetBuffer(strValue.GetLength())) == ERROR_SUCCESS);
		 strValue.ReleaseBuffer();
		 reg.Close();
	}  
}

CString GetRegisterURL()
{
	CString strReturn;
	CString strTag = "URL";
	CRegKey reg;
	if(reg.Open(HKEY_CURRENT_USER, AFFILIATE_REGISTRY_KEY, KEY_READ) == ERROR_SUCCESS)
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

// return XP or better
BOOL IsWindowsXP()
{
	OSVERSIONINFO os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&os);
	if(os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
	{
		return false;
	}
	else
	{
		if(os.dwMajorVersion < 5 || (os.dwMajorVersion == 5 && os.dwMinorVersion < 1))
			return false;
	}
	return true;
}