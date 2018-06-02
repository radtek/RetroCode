
// helpers header file 
// copyright Steve Foxover Software 2004

CString	MyGetProfileString(CString strTag, CString strDefault, DWORD dwMaxChars);
DWORD MyGetProfileInt(CString strTag, DWORD dwDefault);
BOOL MyWriteProfileInt(CString strTag, DWORD dwValuse);
BOOL MyWriteProfileString(CString strTag, CString strValue);
CString ReadEncryptedFile(CString strPath,CString strKey);
BOOL WriteEncryptedFile(CString strPath,CString strKey,CString strData);
CString ParseXML(CString strTag,CString strParams);
CString ReplaceXML(CString strParam,CString strTag,CString strParams);
HRESULT CreateShortCut(LPCSTR pszShortcutFile, LPSTR pszLink,LPSTR pszDesc);
CString GetProgramsPath();
BOOL CreateProgramsLink(CString strExePath,CString strLinkName,CString strDisplayName);
CString GetWinDesktopPath();
BOOL CreateDesktopLink(CString strExePath,CString strLinkName,CString strDisplayName);
BOOL DirectoryExists(CString strPath);
BOOL FileExists(CString strPath);
BOOL MyMakePath(CString strPath);
void MarkFileNormal(CString strPath);
CString GetDefaultBrowserPath();
void LoadURLInBrowser(CString strURL);
BOOL LoadExe(CString strExePath);
void CreateLinkAddRemovePrograms(CString strUninstallerPath,CString strDisplayName);
CString GetRegisterURL();