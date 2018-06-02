
// helpers.cpp

#include "stdafx.h"
#include "helpers.h"
#include "SteveMediaCenter.h"
#include "sockets\Base64Coder.h"
#include "sockets\AuthorizeDlg.h"
#include "zip\ZipArchive.h"	

#include "blowfish\blowfish.h"


typedef BOOL (CALLBACK *FNGetDiskFreeSpaceExA)(
    LPCSTR,PULARGE_INTEGER,PULARGE_INTEGER,PULARGE_INTEGER);

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
	strTemp.TrimRight();

	return strTemp;
}

CString ParseXMLArray(CString strTag,CString strParams)
{
	// make not case sensitive
	CString strLower = strParams;
	strLower.MakeLower();
	strTag.MakeLower();
	int nFind = strLower.Find("<" + strTag + ">");
	if(nFind == -1)
		return "";
	CString strTemp = strParams.Mid(nFind);
	strLower = strTemp;
	strLower.MakeLower();
	strLower.MakeReverse();

	CString strFind = "</" + strTag + ">";
	strFind.MakeReverse();

	nFind = strLower.Find(strFind);
	if(nFind == -1)
		return "";
	
	strTemp.MakeReverse();
	strTemp = strTemp.Mid(nFind);
	strTemp.MakeReverse();

	strTemp.TrimLeft();
	strTemp.TrimRight();

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

void DebugMessage(CString strMsg,BOOL bIgnoreReg)
{
	if(!bIgnoreReg && AfxGetApp()->GetProfileInt("Settings","debug",0) == 0)
		return;
	
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\'));
	CString strPath = strDestination + "\\message.txt";

	if(strMsg == "TimeStamp")
	{
		CString str;
		CTime tm = CTime::GetCurrentTime();
		str += tm.Format("%c");
		str += "\r\n";
		strMsg = str;
	}
	else
	{
		if(strMsg.Right(2) != "\r\n")
			strMsg += "\r\n";
	}
	TRY
	{
		CFile fp;
		if(fp.Open(strPath, CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate))
		{
			fp.SeekToEnd();
			int nLen = strMsg.GetLength();
			fp.Write(strMsg.GetBuffer(nLen),nLen);
			strMsg.ReleaseBuffer();
			fp.Close();
		}
	}
	CATCH(CFileException,e)
	{
	}
	END_CATCH
}

CString FindHtmlFile(CString strDir)
{
	SECFileSystem fp;
	CStringArray straHtmlFiles;
	CStringList* pStrList = fp.GetFileList(strDir + "\\*.htm*",fp.allfiles);
	if(pStrList->GetCount()>0)
	{
		POSITION pos = pStrList->GetHeadPosition();
		while(pos !=NULL)
		{
			CString str = pStrList->GetNext(pos);
			straHtmlFiles.Add(str);
		}
	}
	delete pStrList;

	if(straHtmlFiles.GetSize() > 0)
		return straHtmlFiles.GetAt(0);
	else
		return "";
}

BOOL IsMyMediaType(CString strFileName)
{
	CString strExt = strFileName.Mid(strFileName.ReverseFind('.')+1);
	strExt.MakeLower();

	if(strExt == "ogg" || strExt == "mp3" || strExt == "wma" || strExt == "wmv" || strExt == "asf" ||
		strExt == "mpg" || strExt == "mpeg" || strExt == "avi" || strExt == "mov" ||
		strExt == "ra" || strExt == "rm" || strExt == "rv")
		return true;

	return false;
}

void AddToInstancePlayList(CString strFileName)
{
	CString strData = "<Message>AddToPlayList</Message><FilePath>";
	strData += strFileName + "</FilePath>";
	
	SendMessageToInstanseOfApp(strData);
}

BOOL SendMessageToPlayerOcx(CString strMessage)
{
	BOOL bOK = false;
	HWND handle = FindWindow(MEDIA_PLAYER_CLASSNAME,NULL);
	if(handle)
	{
		int nSize = strMessage.GetLength();
		COPYDATASTRUCT data;
		data.dwData = 0;
		data.cbData = nSize;
		data.lpData = strMessage.GetBuffer(nSize);
		 
		HWND hwnd = ::GetDesktopWindow();
		UINT wParam = (WPARAM)hwnd;
		LONG lParam = (LPARAM) &data;
 
		::SendMessage(handle,WM_COPYDATA,wParam,lParam);
		strMessage.ReleaseBuffer();
		bOK = true;
	}
	return bOK;
}

BOOL SendMessageToPlayListOcx(CString strMessage)
{
	BOOL bOK = false;
	HWND handle = FindWindow(PLAYLIST_CLASSNAME,NULL);
	if(handle)
	{
		int nSize = strMessage.GetLength();
		COPYDATASTRUCT data;
		data.dwData = 0;
		data.cbData = nSize;
		data.lpData = strMessage.GetBuffer(nSize);
		 
		HWND hwnd = ::GetDesktopWindow();
		UINT wParam = (WPARAM)hwnd;
		LONG lParam = (LPARAM) &data;
 
		::SendMessage(handle,WM_COPYDATA,wParam,lParam);
		strMessage.ReleaseBuffer();
		bOK = true;
	}
	return bOK;
}

BOOL MySystemShutDown()
{
	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 
 	// Get a token for this process. 
 	if (OpenProcessToken(GetCurrentProcess(), 
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
	{
		// Get the LUID for the shutdown privilege. 
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
				&tkp.Privileges[0].Luid); 
		tkp.PrivilegeCount = 1;  // one privilege to set    
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
		// Get the shutdown privilege for this process. 
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
				(PTOKEN_PRIVILEGES)NULL, 0); 
		// Cannot test the return value of AdjustTokenPrivileges. 
		if (GetLastError() != ERROR_SUCCESS) 
		{
			DebugMessage("AdjustTokenPrivileges"); 
			return false;
		}
	}
	// Shut down the system and force all applications to close. 
	return ExitWindowsEx(EWX_SHUTDOWN|EWX_POWEROFF|EWX_FORCE, 0); 
}

BOOL SendMessageToInstanseOfApp(CString strMessage)
{
	HWND handle = FindWindow(APP_EXE_CLASSNAME,NULL);
	if(handle)
	{
		int nSize = strMessage.GetLength();
		COPYDATASTRUCT data;
		data.dwData = 0;
		data.cbData = nSize;
		data.lpData = strMessage.GetBuffer(nSize);
		 
		UINT wParam = (WPARAM)GetDesktopWindow();
		LONG lParam = (LPARAM) &data;
 
		::SendMessage(handle,WM_COPYDATA,wParam,lParam);
		strMessage.ReleaseBuffer();
		return true;
	}
	else
		return false;
}

void LoadInDefaultBrowser(CString strURL)
{
	CString strPath;
	SECFileSystem fp;

	SECRegistry reg;
	BOOL bOk = reg.Connect(HKEY_LOCAL_MACHINE);
	bOk = reg.Open("Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\IEXPLORE.EXE",SECRegistry::permissionRead);
	bOk = reg.GetStringValue("", strPath);
	if(!bOk)
		strPath = "C:\\Program Files\\Internet Explorer\\iexplore.exe";
	if(fp.FileExists(strPath))
	{
		WinExec(strPath + " " + strURL,SW_NORMAL);
		return;
	}
}

int ReadPageSize(CString strPath,BOOL bXSize)
{
	int nSize = 0;

	SECFileSystem fs;
	if(!fs.FileExists(strPath))
		return 0;

	CString strData;
	CFile fp;
	TRY
	{
		if(fp.Open(strPath,CFile::modeRead|CFile::shareDenyNone))
		{
			DWORD dwSize = fp.GetLength();
			fp.Read(strData.GetBuffer(dwSize),dwSize);
			strData.ReleaseBuffer();
			fp.Close();
		}
	}
	CATCH(CFileException,e)
	{
	}
	END_CATCH

	CString strSize;
	if(bXSize)
		strSize = ParseXML("SteveSizeX",strData);
	else
		strSize = ParseXML("SteveSizeY",strData);
	nSize = atoi(strSize);

	return nSize;
}

CStringArray* MakeRandomPlaylist(CStringArray* straRandomDirPaths,int nMaxFiles)
{
	// reset random clock
	srand((unsigned)time(NULL));

	CStringArray* pstra = new CStringArray();
	CStringArray straTemp;

	// get all files
	SECFileSystem fs;
	for(int n=0;n<straRandomDirPaths->GetSize();n++)
	{
		CStringList* pStrList = fs.GetFileList(straRandomDirPaths->GetAt(n),fs.allfiles);
		if(pStrList->GetCount() > 0)
		{
			POSITION pos = pStrList->GetHeadPosition();
			while(pos !=NULL)
			{
				CString str = pStrList->GetNext(pos);
				straTemp.Add(str);
			}
		}
		delete pStrList;
	}

	// pick random files
	for(n=0;n<nMaxFiles;n++)
	{
		if(straTemp.GetSize() > 0)
		{
			int nRand = 0;
			// random value 
			nRand = (rand() / (RAND_MAX / straTemp.GetSize() + 1)) + 1;
			nRand --;
			pstra->Add(straTemp.GetAt(nRand));
			straTemp.RemoveAt(nRand);
		}
		else
			break;
	}

	return pstra;
}

BOOL IsMp3File(CString strFileName)
{
	CString strExt = strFileName.Mid(strFileName.ReverseFind('.')+1);
	strExt.MakeLower();

	return (strExt == "mp3");
}

BOOL CreateRootRegEntry()
{
	CString strCmdPath;
	GetModuleFileName(NULL,strCmdPath.GetBuffer(MAX_PATH),MAX_PATH);
	strCmdPath.ReleaseBuffer();

	SECRegistry reg;
	CString strName = "Fox.FoxMediaCenter.1";

	BOOL bOK = reg.Open("HKEY_CLASSES_ROOT",reg.permissionAllAccess);
	bOK = reg.Create(strName);
	bOK = reg.SetStringValue("","Fox Media Center");
	bOK = reg.SetStringValue("FriendlyTypeName","@Fox Media Center,-128");

	bOK = reg.Create(strName + "\\CurVer");
	bOK = reg.SetStringValue("",strName);
	bOK = reg.Create(strName + "\\DefaultIcon");
	bOK = reg.SetStringValue("",strCmdPath + ",-128");
	bOK = reg.Create(strName + "\\Shell");
	bOK = reg.Create(strName + "\\Shell\\play");
	bOK = reg.Create(strName + "\\Shell\\play\\command");
	bOK = reg.SetStringValue("","\"" + strCmdPath + "\" \"%1\"");
	bOK = reg.Create(strName + "\\Shell\\open");
	bOK = reg.Create(strName + "\\Shell\\open\\command");
	bOK = reg.SetStringValue("","\"" + strCmdPath + "\" \"%1\"");

	reg.Close();

	return bOK;
}

BOOL IsWMVType(CString strExt)
{
	if(strExt == ".asf" || strExt == ".wmv")
		return true;
	else
		return false;
}

BOOL IsMpegType(CString strExt)
{
	if(strExt == ".mpg" || strExt == ".mpeg" || strExt == ".mp4")
		return true;
	else
		return false;
}

CStringArray* EnumKnowFileTypesFromReg()
{
	CStringArray* pstra = new CStringArray;

	// HKEY_CURRENT_USER\Software\SteveSoftware\FoxMediaCenter
	SECRegistry reg;
	// read mime type
	CString strMimeType;
	BOOL lErr = false;
	lErr = reg.Connect(HKEY_CURRENT_USER);
	lErr = reg.Open("Software\\SteveSoftware\\FoxMediaCenter",reg.permissionAllAccess);
	if(!lErr)
		return pstra;

	UINT nIndex = 0;
	CString strKeyName;
	CString strData;
	while (reg.EnumerateKeys(nIndex++, strKeyName))
	{
		
		if(!strKeyName.IsEmpty() && strKeyName.GetAt(0) == '.')
		{
			if(AfxGetApp()->GetProfileString(strKeyName,"Associated","FALSE") == "TRUE")
			{
				strData.Format("<Ext>%s</Ext><IsAudio>%s</IsAudio>",strKeyName,
					AfxGetApp()->GetProfileString(strKeyName,"IsAudio","TRUE"));
				pstra->Add(strData);
			}
		}
	}
	reg.Close();

	return pstra;
}

// NONE,WMP_VIDEO,REAL_VIDEO,WMP_AUDIO,REAL_AUDIO,QUICKTIME,MP3_AUDIO
EnumFileType GetMediaFileType(CString strFileName)
{
	EnumFileType myType = WMP_VIDEO;
	CString strExt = strFileName.Mid(strFileName.ReverseFind('.')+1);
	strExt.MakeLower();

	if(strExt == "ogg" || strExt == "wma" || strExt == "mp3")
		myType = WMP_AUDIO;
	else if(strExt == "mpg" || strExt == "mpeg" || strExt == "wmv" || strExt == "avi" || strExt == "asf")
		myType = WMP_VIDEO;
	else if(strExt == "rm")
		myType = WMP_VIDEO; // same as REAL_VIDEO
	else if(strExt == "ra")
		myType = REAL_AUDIO;
	else if(strExt == "mov")
		myType = WMP_VIDEO;  //QUICKTIME;
	else
	{
		strExt = "." + strExt;
		CStringArray* pstra = EnumKnowFileTypesFromReg();
		for(int n=0;n<pstra->GetSize();n++)
		{
			CString strData = pstra->GetAt(n);
			if(ParseXML("Ext",strData) == strExt)
			{
				if(ParseXML("IsAudio",strData) == "TRUE")
					myType = WMP_AUDIO;
				else
					myType = WMP_VIDEO;
				break;
			}
		}
		delete pstra;
	}

	return myType;
}

CString HexEncode(unsigned char* chBuffer,DWORD dwLen)
{
	CString HexNum("0123456789ABCDEF");
	CString strReturn;
	char ch;
	for(int n=0;n<dwLen;n++)
	{
		ch = chBuffer[n];
		strReturn = strReturn + HexNum.GetAt((ch >> 4) & 0xf);
		strReturn = strReturn + HexNum.GetAt(ch & 0xf);
	}
	return strReturn;
}		  

int hex(unsigned char ch)
{
	if (ch >= 'a' && ch <= 'f')
		return ch-'a'+10;
	if (ch >= '0' && ch <= '9')
		return ch-'0';
	if (ch >= 'A' && ch <= 'F')
		return ch-'A'+10;
	return -1;
}

DWORD HexUnEncode(CString strHex,unsigned char* pBuf)
{
	DWORD nCount = strHex.GetLength();
	unsigned char ch;
	DWORD nDecodeLen = 0;
	for (int n=0; n < nCount; n += 2)
	{
		nDecodeLen += 1;
		ch = hex(strHex.GetAt(n)) << 4;
		ch |= hex(strHex.GetAt(n + 1));

		*pBuf++ = ch;
	}
	return nDecodeLen;
}

CString CreateGUID()
{
	CString strNewNum;
	GUID guid;
	ZeroMemory(&guid,sizeof(GUID));
	HRESULT hr = CoCreateGuid(&guid);

	// format GUID
	WCHAR        wszGuid[40]; 
	StringFromGUID2(guid, wszGuid, sizeof(wszGuid) / sizeof(WCHAR)); 
	wcstombs(strNewNum.GetBuffer(MAX_PATH), wszGuid,MAX_PATH);
	strNewNum.ReleaseBuffer();
	strNewNum.TrimLeft("{");
	strNewNum.TrimRight("}");

	CString strHex = EncryptToHex(strNewNum);

	return strHex;
}

CString GetOSTypeLong()
{
	OSVERSIONINFO VersionInformation;
	VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&VersionInformation);
	if(VersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT)
		return "Windows NT";
	if(VersionInformation.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS
		&& VersionInformation.dwMinorVersion ==0)
		return "Windows 95";
	else 	
		return "Windows 98";
}

BOOL UsingProxyPassword()
{
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();

	if(!pApp->m_strProxyUserName.IsEmpty())
		return TRUE;
	
	if(pApp->m_bHasCheckedForProxyPasswordFromFile)
		return FALSE;

	CString strData;
	// app dir
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\'));
	CString strBasePath = strDestination + "\\auth.dat";
	TRY
	{
		SECCryptoFile fp;
		if(fp.Open(strBasePath,"duyb783slp",CFile::modeRead,SECCryptoFile::ECB))
		{
			long lSize = fp.GetLength();
			fp.Read(strData.GetBuffer(lSize),lSize);
			strData.ReleaseBuffer();
			fp.Close();
		}
	}
	CATCH(CFileException, e)
	{
	}
	END_CATCH
	
	// don't want to read from disk each function call
	pApp->m_bHasCheckedForProxyPasswordFromFile = TRUE;

	CString strUser = ParseXML("UserName",strData);
	CString strPass = ParseXML("Password",strData);
	// load into memory
	pApp->m_strProxyUserName = strUser;
	pApp->m_strProxyPassword = strPass;

	if(!strUser.IsEmpty())
		return TRUE;
	else
		return FALSE;
}

CString GetProxyPasswordString()
{
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	// use variables from memory
	if(!pApp->m_strProxyUserName.IsEmpty())
	{
		CString strReturn = "Proxy-Connection: Keep-Alive\r\nProxy-Authorization: Basic ";
		CString strEncodeData = pApp->m_strProxyUserName + ":" + pApp->m_strProxyPassword;
		Base64Coder Coder;
		Coder.Encode(strEncodeData);
		strEncodeData = (LPCTSTR) Coder.EncodedMessage();
		strReturn += strEncodeData + "\r\n";
		return strReturn;
	}
	// load from disk
	CString strData;
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\'));
	CString strBasePath = strDestination + "\\auth.dat";
	TRY
	{
		SECCryptoFile fp;
		if(fp.Open(strBasePath,"duyb783slp",CFile::modeRead,SECCryptoFile::ECB))
		{
			long lSize = fp.GetLength();
			fp.Read(strData.GetBuffer(lSize),lSize);
			strData.ReleaseBuffer();
			fp.Close();
		}
	}
	CATCH(CFileException, e)
	{
	}
	END_CATCH
	
	if(strData.IsEmpty())
	{
		return "";
	}
	else
	{
		CString strUser = ParseXML("UserName",strData);
		CString strPass = ParseXML("Password",strData);
		// load into memory
		pApp->m_strProxyUserName = strUser;
		pApp->m_strProxyPassword = strPass;

		CString strReturn = "Proxy-Connection: Keep-Alive\r\nProxy-Authorization: Basic ";
		CString strEncodeData = strUser + ":" + strPass;
		Base64Coder Coder;
		Coder.Encode(strEncodeData);
		strEncodeData = (LPCTSTR) Coder.EncodedMessage();
		strReturn += strEncodeData + "\r\n";
		return strReturn;
	}
}

// ask the user for a username and passord for proxy authorization
BOOL CheckProxyUsernamePassword(BOOL bAlwaysPrompt)
{
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();

	pApp->m_bCheckingProxyName = true;

	CString strData;
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\'));
	CString strBasePath = strDestination + "\\auth.dat";
	TRY
	{
		SECCryptoFile fp;
		if(fp.Open(strBasePath,"duyb783slp",CFile::modeRead,SECCryptoFile::ECB))
		{
			long lSize = fp.GetLength();
			fp.Read(strData.GetBuffer(lSize),lSize);
			strData.ReleaseBuffer();
			fp.Close();
		}
	}
	CATCH(CFileException, e)
	{
	}
	END_CATCH
	
	BOOL bReturn = FALSE;
	if(strData.IsEmpty())
	{
		CAuthorizeDlg dlg;
		if(dlg.DoModal() == IDOK)
			bReturn = TRUE;
		else
			bReturn = FALSE;
	}
	else if(bAlwaysPrompt)
	{
		CString strUser = ParseXML("UserName",strData);
		CString strPass = ParseXML("Password",strData);
		CAuthorizeDlg dlg(strUser,strPass);
		if(dlg.DoModal() == IDOK)
			bReturn = TRUE;
		else
			bReturn = FALSE;
	}

	AfxGetMainWnd()->SetTimer(ID_TIMER_PROMPT_FOR_PROXY_AUTHORIZE_ENABLED,60*1000,NULL);

	return bReturn;
}

// HTTP header helpers
int CheckHTTPResponce(CString strReply)
{
	CString str = strReply.Mid(strReply.Find(' ')+1);
	str = str.Left(str.Find(' '));
	int nReply = atoi(str);
	return nReply;
}

long GetFileSize(CString strReply)
{
	while(strReply.Find("\r\n") != -1)
	{
		CString str,str2;
		str = strReply.Left(strReply.Find("\r\n"));
		strReply = strReply.Mid(strReply.Find("\r\n")+2);
		str2 = str.Left(15); //Content-length:
		if(str2.CompareNoCase("Content-length:") ==0)
		{
			CString strLen = str.Mid(16);
			return atol(strLen);
		}
	}
	return 0;
}

void RemoveSpacesForURL(CString& strJob)
{
	int nPos = 0;
	while((nPos=strJob.Find(' '))!=-1)
	{
		CString strTemp = strJob.Left(nPos);
		strTemp += "%20" + strJob.Mid(nPos+1);
		strJob = strTemp;
	}
}

long GetDiskSpaceFree()
{
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	CString strPath;
	GetModuleFileName(NULL,strPath.GetBuffer(MAX_PATH),MAX_PATH);
	strPath.ReleaseBuffer();

	CString strRootPathName;    // pointer to root path
	BOOL bOK = FALSE;
	HINSTANCE handle = ::LoadLibrary("KERNEL32.DLL");
	FNGetDiskFreeSpaceExA proc;
	if(handle)
	{
		proc = (FNGetDiskFreeSpaceExA)GetProcAddress(handle,"GetDiskFreeSpaceExA");
		if(proc)
			bOK = TRUE;
	}
	double lSize = 0;
	if(bOK)
	{
		ULARGE_INTEGER lFreeBytesAvailableToCaller; // receives the number of bytes on
		ULARGE_INTEGER lTotalNumberOfBytes;    // receives the number of bytes on disk
		ULARGE_INTEGER lTotalNumberOfFreeBytes; // receives the free bytes on disk
		proc(strPath.Left(3),&lFreeBytesAvailableToCaller,
			&lTotalNumberOfBytes,&lTotalNumberOfFreeBytes);

		double dSize = (lTotalNumberOfFreeBytes.HighPart*(double)4294967296.
			+ lTotalNumberOfFreeBytes.LowPart);
		lSize = dSize;
	}
	else
	{
		SECFileSystem fs;
		lSize = fs.GetFreeSpace(strPath.Left(3));
	}
	::FreeLibrary(handle); 
	if(lSize > 0)
	{
		lSize = lSize/1024;
		if(lSize > 0)
		{
			lSize = lSize/1000;
		}
	}
	return lSize;  // meg
}

CString ParseServerTags(CString strReply)
{
	CString strMid;
	while(strReply.Find(_T("&lt;"))!= -1)
	{
		strMid = strReply.Mid(strReply.Find(_T("&lt;"))+4);
		strReply = strReply.Left(strReply.Find(_T("&lt;")));
		strReply += _T("<");
		strReply += strMid;
	}
	while(strReply.Find(_T("&gt;"))!= -1)
	{
		strMid = strReply.Mid(strReply.Find(_T("&gt;"))+4);
		strReply = strReply.Left(strReply.Find(_T("&gt;")));
		strReply += _T(">");
		strReply += strMid;
	}
	return strReply;
}

CString GetServerTag(CString strTag,CString strReply)
{
	while(strReply.Find("\r\n") != -1)
	{
		CString str,str2;
		str = strReply.Left(strReply.Find("\r\n"));
		strReply = strReply.Mid(strReply.Find("\r\n")+2);
		str2 = str.Left(strTag.GetLength()); 
		if(str2.CompareNoCase(strTag) ==0)
		{
			CString strResult = str.Mid(strTag.GetLength());
			strResult.TrimLeft();
			return strResult;
		}
	}
	return "";
}

BOOL IsKnownType(CString strURL)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); // Needed for any MFC usage in DLL

	if(strURL.Left(strlen("http://")).CompareNoCase("http://") != 0)
		return FALSE;
	else
		return TRUE;
}

// Disable Autodial
void DisableAutoDial()
{
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();

	SECRegistry reg;
	BOOL bOk = reg.Connect(HKEY_CURRENT_USER);
	bOk = reg.Open("Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",(SECRegistry::CreatePermissions)KEY_ALL_ACCESS);
	DWORD dwAuto;
	bOk = reg.GetDoubleWordValue("EnableAutodial",dwAuto);
	pApp->m_bIsAutoDialOn = (dwAuto==1);
	dwAuto = 0;
	reg.SetDoubleWordValue("EnableAutodial",dwAuto);
	reg.Close();	
}

void EnableAutoDial()
{
	CSteveMediaCenterApp* pApp = (CSteveMediaCenterApp*)AfxGetApp();
	if(!pApp->m_bIsAutoDialOn)
		return;
	SECRegistry reg;
	BOOL bOk = reg.Connect(HKEY_CURRENT_USER);
	bOk = reg.Open("Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",(SECRegistry::CreatePermissions)KEY_ALL_ACCESS);
	DWORD dwAuto = 1;
	pApp->m_bIsAutoDialOn = 1;
	reg.SetDoubleWordValue("EnableAutodial",dwAuto);
	reg.Close();	
}

CString ReadURL(CString strTag,CString strDefault)
{
	// destination dir
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\'));
	strDestination += "\\filelist.dat";
	
	// test if encrypted
	BOOL bIsEncrypted = TRUE;
	CFile fp;
	CString strData;
	TRY
	{
		if(fp.Open(strDestination,CFile::modeRead|CFile::shareDenyNone))
		{
			DWORD dwSize = fp.GetLength();
			fp.Read(strData.GetBuffer(dwSize),dwSize);
			strData.ReleaseBuffer();
			fp.Close();
			if(!ParseXML("AllURLS",strData).IsEmpty())
				bIsEncrypted = FALSE;
		}
		// data encrypted
		if(bIsEncrypted)
		{
			SECCryptoFile fc;
			if(fc.Open(strDestination,"duyb783slp", CFile::modeRead|CFile::shareDenyNone, SECCryptoFile::ECB))
			{
				DWORD dwSize = fc.GetLength();
				fc.Read(strData.GetBuffer(dwSize),dwSize);
				strData.ReleaseBuffer();
				fc.Close();
			}
		}
	}
	CATCH(CFileException,e)
	{
		DebugMessage("File exception trying to read urls");
	}
	END_CATCH
	CString strEntry = ParseXML(strTag,strData);
	if(strEntry.IsEmpty())
		strEntry = strDefault;
	// save data as encrypted
	if(!bIsEncrypted)
	{
		SECCryptoFile fc2;
		if(fc2.Open(strDestination,"duyb783slp", CFile::modeCreate|CFile::modeWrite, SECCryptoFile::ECB))
		{
			DWORD dwSize = strData.GetLength();
			fc2.Write(strData.GetBuffer(dwSize),dwSize);
			strData.ReleaseBuffer();
			fc2.Close();
		}
	}

	return strEntry;
}

BOOL WriteURL(CString strTag,CString strParam)
{
	// destination dir
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\'));
	strDestination += "\\filelist.dat";
	
	// test if encrypted
	BOOL bIsEncrypted = TRUE;
	CFile fp;
	CString strData;
	if(fp.Open(strDestination,CFile::modeRead|CFile::shareDenyNone))
	{
		DWORD dwSize = fp.GetLength();
		fp.Read(strData.GetBuffer(dwSize),dwSize);
		strData.ReleaseBuffer();
		fp.Close();
		if(!ParseXML("AllURLS",strData).IsEmpty())
			bIsEncrypted = FALSE;
	}
	// data encrypted
	if(bIsEncrypted)
	{
		SECCryptoFile fc;
		if(fc.Open(strDestination,"duyb783slp", CFile::modeRead|CFile::shareDenyNone, SECCryptoFile::ECB))
		{
			DWORD dwSize = fc.GetLength();
			fc.Read(strData.GetBuffer(dwSize),dwSize);
			strData.ReleaseBuffer();
			fc.Close();
		}
		else
			return FALSE;
	}

	strData = ReplaceXML(strParam,strTag,strData);

	// save data 
	SECCryptoFile fc2;
	if(fc2.Open(strDestination,"duyb783slp", CFile::modeCreate|CFile::modeWrite, SECCryptoFile::ECB))
	{
		DWORD dwSize = strData.GetLength();
		fc2.Write(strData.GetBuffer(dwSize),dwSize);
		strData.ReleaseBuffer();
		fc2.Close();
	}

	return TRUE;
}

BOOL MyUnZipFile(CString strZipName)
{
	CString strPath = strZipName.Left(strZipName.ReverseFind('\\'));

	CZipArchive zip;
	try
	{
		zip.Open(strZipName, CZipArchive::zipOpen,0);
		zip.SetRootPath(NULL);
		int numFiles = zip.GetNoEntries();
		for(int n=0; n<numFiles;n++)
		{
			if(!zip.ExtractFile(n,strPath))
				return FALSE;
		}
		zip.Close();
	}
	catch (CException* e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}
	catch(...) // thrown in the STL version
	{
		return FALSE;
	}
	
	return TRUE;
}

CString GetCheckUpdateString()
{
	CString strHex = AfxGetApp()->GetProfileString("Settings","InstallParam","");
	CString strID;	
	if(!strHex.IsEmpty())
		strID = UnEncryptFromHex(strHex);

	CString strBID = AfxGetApp()->GetProfileString("Settings","BID","1");
	CString strTime = CTime::GetCurrentTime().Format("%m/%d/%Y %I:%M:%S %p");
	CString strData;
	strData.Format("<ID>%s</ID><BID>%s</BID><Version>%s</Version><LocTime>%s</LocTime><Skin>%s</Skin>"
		,strID,strBID,VERSION_EXE,strTime,AfxGetApp()->GetProfileString("Settings","CurrentSkin",""));

	CString strDataOut = EncryptToHex(strData);
	return strDataOut;
}

CString GetNewUserInfo()
{
	CString strHex = AfxGetApp()->GetProfileString("Settings","InstallParam","");
	CString strID;	
	if(!strHex.IsEmpty())
		strID = UnEncryptFromHex(strHex);

	CString strBID = AfxGetApp()->GetProfileString("Settings","BID","1");
	CString strTime = CTime::GetCurrentTime().Format("%m/%d/%Y %I:%M:%S %p");
	CString strData;
	strData.Format("<ID>%s</ID><BID>%s</BID><Version>%s</Version><LocTime>%s</LocTime><Skin>%s</Skin>"
		,strID,strBID,VERSION_EXE,strTime,AfxGetApp()->GetProfileString("Settings","CurrentSkin",""));

	CString strDataOut = EncryptToHex(strData);
	return strDataOut;
}

CString PadToMod8(CString strData)
{
	int nLen = strData.GetLength();
	int nMod = nLen % 8;
	while(nMod != 0)
	{
		strData += " ";
		nLen = strData.GetLength();
		nMod = nLen % 8;
	}
	return strData;
}

CString EncryptToHex(CString strData)
{
	DWORD dwSize = strData.GetLength();
	DWORD dwOut = dwSize;
	CString strDataOut = strData;
	strData = HexEncode((unsigned char*)strDataOut.GetBuffer(dwOut),dwOut);
	strDataOut.ReleaseBuffer();

	return strData;
}

CString UnEncryptFromHex(CString strHex)
{
	CString strData;
	DWORD dwSize = HexUnEncode(strHex,(unsigned char*)strData.GetBuffer(4024));
	strData.ReleaseBuffer();
	strData.SetAt(dwSize,'\0');

	return strData; 
}

CString EncryptBlow(CString strData) 
{
	strData = PadToMod8(strData);

	CString strDataOut;
	CString strPass = "kjdyhrbsm74hf6h0";
	int nKeySize = strPass.GetLength();
	DWORD dwSize = strData.GetLength();
	TRY
	{
		CBlowFish enc((unsigned char*)strPass.GetBuffer(nKeySize),nKeySize);
		strPass.ReleaseBuffer();
		enc.Encrypt((unsigned char*)strData.GetBuffer(dwSize),(unsigned char*)strDataOut.GetBuffer(4024),dwSize,enc.CBC);
		strData.ReleaseBuffer();
		strDataOut.ReleaseBuffer();
	}
	CATCH(CException,e)
	{
		return "";
	}
	END_CATCH

	DWORD dwOut = dwSize;
	strData = HexEncode((unsigned char*)strDataOut.GetBuffer(dwOut),dwOut);
	strDataOut.ReleaseBuffer();
	
	return strData;
}

CString DecryptBlow(CString strHex) 
{
	CString strData;
	DWORD dwSize = HexUnEncode(strHex,(unsigned char*)strData.GetBuffer(4024));
	strData.ReleaseBuffer();

	CString strDataOut;
	CString strPass = "kjdyhrbsm74hf6h0";
	int nKeySize = strPass.GetLength();
	CBlowFish dec((unsigned char*)strPass.GetBuffer(nKeySize), nKeySize);
	strPass.ReleaseBuffer();
	dec.Decrypt((unsigned char*)strData.GetBuffer(dwSize),dwSize,dec.CBC);
	strData.ReleaseBuffer();
	strData.SetAt(dwSize,'\0');

	return strData;	
}

void BumpWindow(CWnd* pWnd)
{
	if(!IsWindow(pWnd->m_hWnd))
		return;
	CRect rect;
	pWnd->GetWindowRect(rect);
	rect.right += 1;
	pWnd->MoveWindow(rect); 
	rect.right -= 1;
	pWnd->MoveWindow(rect); 
}

void AutoDetectProxy()
{
	SECRegistry reg;
	CString strProxyString;

	BOOL bOK = reg.Connect(HKEY_CURRENT_USER);
	bOK = reg.Open("Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings");
	DWORD bProxy = 0;
	bOK = reg.GetDoubleWordValue("ProxyEnable",bProxy);
	// IE set proxy used = TRUE
	if(bOK && bProxy == 1)
	{
		bOK = reg.GetStringValue("ProxyServer", strProxyString);
		reg.Close();
		strProxyString.MakeLower();
		
		BOOL bSettingsFound = FALSE;
		CString strURL,strProxyUsername,strType;
		CString strPort = "80";
		// look for http proxy
		if(strProxyString.Find("http=")!=-1)
		{
			strURL = strProxyString.Mid(strProxyString.Find("http=") + strlen("http="));
			strPort = strURL.Mid(strURL.Find(':')+1);
			strURL = strURL.Left(strURL.Find(':'));
			if(strPort.Find(';') != -1)
				strPort = strPort.Left(strPort.Find(';'));
			// set settings
			strType = "Proxy Server";
			bSettingsFound = TRUE;
		}
		// other wise look for only url:port	
		else if(strProxyString.Find(":")!=-1)
		{
			strURL = strProxyString;
			if(strURL.Find('=') != -1)
				strURL = strURL.Mid(strURL.Find('=')+1);
			strPort = strURL.Mid(strURL.Find(':')+1);
			strURL = strURL.Left(strURL.Find(':'));
			if(strPort.Find(';') != -1)
				strPort = strPort.Left(strPort.Find(';'));
			// set settings
			strType = "Proxy Server";
			bSettingsFound = TRUE;
		}
		if(bSettingsFound) // save registry settings + password
		{
			AfxGetApp()->WriteProfileInt("Settings","UseProxy",1);
			AfxGetApp()->WriteProfileString("Settings","HttpPort",strPort);
			if(strURL.Left(7).CompareNoCase("HTTP://")==0)
				strURL = strURL.Mid(7);
			AfxGetApp()->WriteProfileString("Settings","HttpProxyUrl",strURL);
		}
	}
	else  // clear settings
	{
		AfxGetApp()->WriteProfileInt("Settings","UseProxy",0);
		AfxGetApp()->WriteProfileString("Settings","HttpPort","80");
		AfxGetApp()->WriteProfileString("Settings","HttpProxyUrl","");
	}
}