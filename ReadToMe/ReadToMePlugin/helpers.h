
// copyright Steve Foxover Software 2005

#pragma once

// helpers.h

CString ParseXML(CString strTag,CString strParams);
CString ReplaceXML(CString strParam,CString strTag,CString strParams);
CString ReadEncryptedFile(CString strPath,CString strKey);
BOOL WriteEncryptedFile(CString strPath,CString strKey,CString strData);
DWORD MyGetProfileInt(CString strTag, DWORD dwDefault);
CString	MyGetProfileString(CString strTag, CString strDefault = "", DWORD dwMaxChars = 1024);
BOOL MyWriteProfileInt(CString strTag, DWORD dwValuse);
BOOL MyWriteProfileString(CString strTag, CString strValue);
BOOL IsRegCodeGood(CString strReg);
BOOL IsRegistered();
int GetFreeTrialDaysUsed();
CString GetRegisterURL();
CString GetDefaultBrowserPath();