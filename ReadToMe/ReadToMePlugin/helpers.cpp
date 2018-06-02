
// helpers.cpp

#include "stdafx.h"
#include "helpers.h"
#include "atltime.h"
#include "atlwfile.h"
#include "crypto\\rijndael.h"

CString	MyGetProfileString(CString strTag, CString strDefault, DWORD dwMaxChars)
{
	CString strReturn = "";
	CRegKey reg;
	if(reg.Open(HKEY_CURRENT_USER, MY_REGISTRY_PATH, KEY_READ) == ERROR_SUCCESS)
	{
		 DWORD ulChars = dwMaxChars;
		 BOOL bOK = false;
		 bOK = (reg.QueryStringValue(strTag.GetBuffer(strTag.GetLength()),strReturn.GetBuffer(ulChars),&ulChars) == ERROR_SUCCESS);
		 strTag.ReleaseBuffer();
		 strReturn.ReleaseBuffer();
		 if(!bOK)
		 {
			 strReturn = strDefault;
		 }
		 reg.Close();
	}  
	else
		strReturn = strDefault;
	return strReturn;
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
	DWORD dwSize = 0;
	CFile fp;
	if(fp.Open(strPath,GENERIC_READ,0))
	{
		dwSize = fp.GetSize();
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
		if(dwKeySize > 32)
			dwKeySize = 32;
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

DWORD MyGetProfileInt(CString strTag, DWORD dwDefault)
{
	DWORD dwReturn = 0;
	CRegKey reg;
	if(reg.Open(HKEY_CURRENT_USER, MY_REGISTRY_PATH, KEY_READ) == ERROR_SUCCESS)
	{
		 BOOL bOK = false;
		 bOK = (reg.QueryDWORDValue(strTag,dwReturn) == ERROR_SUCCESS);
		 if(!bOK)
		 {
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
	if(reg.Create(HKEY_CURRENT_USER, MY_REGISTRY_PATH) == ERROR_SUCCESS)
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
	if(reg.Create(HKEY_CURRENT_USER, MY_REGISTRY_PATH) == ERROR_SUCCESS)
	{
		 bOK = (reg.SetStringValue(strTag.GetBuffer(strTag.GetLength()),strValue.GetBuffer(strValue.GetLength())) == ERROR_SUCCESS);
		 strTag.ReleaseBuffer();
		 strValue.ReleaseBuffer();
		 reg.Close();
	}  
	return bOK;
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
	int nMagic = 2000 - nNum;
	strTest.Format("%d",nMagic);
	if(strTest != strReg.Mid(2,strTest.GetLength()))
		return false;

	// 2nd sect
	nNum = atoi(strReg.Mid(15,1));
	nNum = nNum * atoi(strReg.Mid(14,1));
	nMagic = 1000 - nNum;
	strTest.Format("%d",nMagic);
	if(strTest != strReg.Mid(14-strTest.GetLength(),strTest.GetLength()))
		return false;

	return true;
}

BOOL IsRegistered()
{
	CString strReg = MyGetProfileString("Reg","");
	return IsRegCodeGood(strReg);	
}

int GetFreeTrialDaysUsed()
{
	CTime tm;
	tm = tm.GetCurrentTime();

	CString strFilePath;
	GetSystemDirectory(strFilePath.GetBuffer(MAX_PATH),MAX_PATH);
	strFilePath.ReleaseBuffer();
	strFilePath += "\\" + CString(APP_FILE);

	CString strData = ReadEncryptedFile(strFilePath,ENCRYPT_KEY);
	BOOL bExpired = (ParseXML("Expired",strData) == "TRUE");

	CString strInstallTime = ParseXML("InstallTime",strData);
	CTime tmTimeInstall;
	if(!strInstallTime.IsEmpty())
		tmTimeInstall = (long)atol(strInstallTime);
	else
		tmTimeInstall = (long)MyGetProfileInt("id",0);

	CTimeSpan tspan = tm - tmTimeInstall;
	DWORD dwDays = (DWORD)tspan.GetDays();

	if(bExpired)
		return -1;
	else
		return dwDays;
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



