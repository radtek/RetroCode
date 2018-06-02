
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

EnumFileType GetMediaFileType(CString strFileName)
{
	EnumFileType myType;
	CString strExt = strFileName.Mid(strFileName.ReverseFind('.')+1);
	strExt.MakeLower();

	if(strExt == "ogg" || strExt == "mp3" || strExt == "wma")
		myType = WMP_AUDIO;
		
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
 
		BOOL bOK = ::SendMessage(handle,WM_COPYDATA,wParam,lParam);
		strMessage.ReleaseBuffer();
		return bOK;
	}
	else
		return false;
}



void LoadWebPage(CString strURL)
{

}


