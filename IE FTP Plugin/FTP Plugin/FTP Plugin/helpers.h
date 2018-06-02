
// helpers.h
#pragma once

CString	MyGetProfileString(CString strTag, CString strDefault = _T(""), DWORD dwMaxChars = 1024);
DWORD	MyGetProfileInt(CString strTag, DWORD dwDefault);
BOOL	MyWriteProfileInt(CString strTag, DWORD dwValuse);
BOOL	MyWriteProfileString(CString strTag, CString strValue);
CString ReadEncryptedFile(CString strPath,CString strKey);
BOOL	WriteEncryptedFile(CString strPath,CString strKey,CString strData);
CString ParseXML(CString strTag,CString strParams);
CString ReplaceXML(CString strParam,CString strTag,CString strParams);
BOOL	IsRegCodeGood(CString strReg);
BOOL	IsRegistered();
int		GetFreeTrialDaysUsed();
void	SetPasvMode(BOOL bTrue);
CString GetRegisterURL();
BOOL IsWindowsXP();