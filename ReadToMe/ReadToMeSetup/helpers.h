
// helpers.h
// copyright Steve Foxover Software 2005

#pragma once

BOOL CreateProgramsLink(CString strExePath,CString strLinkName,CString strDisplayName);
CString ParseXML(CString strTag,CString strParams);
CString ReplaceXML(CString strParam,CString strTag,CString strParams);
CString ReadEncryptedFile(CString strPath,CString strKey);
BOOL WriteEncryptedFile(CString strPath,CString strKey,CString strData);
void LoadHTMLFile(CString strFile);
DWORD GetFileVersionDW(CString strPath);
BOOL DirectoryExists(CString strPath);
BOOL FileExists(CString strPath);
BOOL MyMakePath(CString strPath);
void MarkFileNormal(CString strPath);
void CheckBHOEnabled();
CString GetRegisterURL();
BOOL RegisterOCX(CString strPath);
BOOL MyWriteProfileString(CString strTag, CString strValue);
BOOL MyWriteProfileInt(CString strTag, DWORD dwValue);
void CreateLinkAddRemovePrograms(CString strUninstallerPath,CString strDisplayName);
BOOL NeedsTTSINstall();