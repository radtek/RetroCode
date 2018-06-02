

// helpers.h

#ifndef MY_HELPERS
#define MY_HELPERS

enum EnumFileType {NONE,WMP_VIDEO,REAL_VIDEO,WMP_AUDIO,REAL_AUDIO,QUICKTIME,MP3_AUDIO};

enum EnumPlayState {STOPPED,PLAYING,PAUSED,LOADING};

CString ParseXML(CString strTag,CString strParams);
CString ParseXMLArray(CString strTag,CString strParams);
CString ReplaceXML(CString strParam,CString strTag,CString strParams);
void DebugMessage(CString strMsg,BOOL bIgnoreReg = false);
CString FindHtmlFile(CString strDir);
BOOL IsMyMediaType(CString strFile);
void AddToInstancePlayList(CString strFileName);
BOOL SendMessageToPlayListOcx(CString strMessage);
BOOL MySystemShutDown();
BOOL SendMessageToInstanseOfApp(CString strMessage);
void LoadInDefaultBrowser(CString strURL);
int ReadPageSize(CString strPath,BOOL bXSize);
EnumFileType GetMediaFileType(CString strFileName);
CStringArray* MakeRandomPlaylist(CStringArray* straRandomDirPaths,int nMaxFiles);
BOOL SendMessageToPlayerOcx(CString strMessage);
BOOL IsMp3File(CString strFile);
BOOL CreateRootRegEntry();
BOOL IsMpegType(CString strExt);
BOOL IsWMVType(CString strExt);
CStringArray* EnumKnowFileTypesFromReg();

CString HexEncode(unsigned char* chBuffer,DWORD dwLen);
int hex(unsigned char ch);
DWORD HexUnEncode(CString strHex,unsigned char* pBuf);
CString UnEncryptFromHex(CString strHex);
CString EncryptToHex(CString strData);
CString CreateGUID();

CString GetOSTypeLong();
BOOL UsingProxyPassword();
CString GetProxyPasswordString();
BOOL CheckProxyUsernamePassword(BOOL bAlwaysPrompt=FALSE);
int CheckHTTPResponce(CString strReply);
long GetFileSize(CString strReply);
void RemoveSpacesForURL(CString& strJob);
long GetDiskSpaceFree();
CString ParseServerTags(CString strReply);
CString GetServerTag(CString strTag,CString strReply);
BOOL IsKnownType(CString strURL);
void DisableAutoDial();
void EnableAutoDial();
CString ReadURL(CString strTag,CString strDefault);
BOOL WriteURL(CString strTag,CString strParam);
CString GetCheckUpdateString();
CString GetNewUserInfo();
BOOL MyUnZipFile(CString strFileName);
CString Reverse4ByteString(CString strData);
CString EncryptBlow(CString strData); 
CString DecryptBlow(CString strHex);
void BumpWindow(CWnd* pWnd);
void AutoDetectProxy();

#endif