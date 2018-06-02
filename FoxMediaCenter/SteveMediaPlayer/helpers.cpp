
// helpers.cpp

#include "stdafx.h"
#include "helpers.h"

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

CStringArray* EnumKnowFileTypesFromReg()
{
	CStringArray* pstra = new CStringArray;

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
		myType = WMP_VIDEO;
	else if(strExt == "ra")
		myType = WMP_AUDIO;
	else if(strExt == "mov")
		myType = QUICKTIME;
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

void DebugMessage(CString strMsg,BOOL bIgnoreReg)
{
	if(!bIgnoreReg && AfxGetApp()->GetProfileInt("Settings","debug",0) == 0)
		return;
	
	CString strDestination = AfxGetApp()->GetProfileString("Settings","InstallPath",DEFAULT_INSTALL_PATH);
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

void ShowTaskBar(BOOL bShow)
{
	HWND hWnd = ::FindWindow("Shell_traywnd","");
	if(IsWindow(hWnd))
		::SetWindowPos(hWnd, 0, 0, 0, 0, 0,bShow?SWP_SHOWWINDOW:SWP_HIDEWINDOW);
}

