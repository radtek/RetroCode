// PlayListManager.cpp: implementation of the CPlayListManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SteveMediaCenter.h"
#include "mainfrm.h"

#include "PlayListManager.h"
#include "helpers.h"
#include "MyMediaPlayer.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlayListManager::CPlayListManager()
{

}

CPlayListManager::~CPlayListManager()
{

}

long CPlayListManager::LoadCurrent(BOOL bResetOcx,BOOL bStopPlaying,BOOL bCanReloadRandom)
{
	CString strPath = AfxGetApp()->GetProfileString("Settings","InstallPath",DEFAULT_INSTALL_PATH);
	strPath += "\\Playlists";
	CString strCurrentPlayList = AfxGetApp()->GetProfileString("Settings","CurrentPlaylist","default");
	strPath += "\\" + strCurrentPlayList + ".spl";

	SECFileSystem fs;
	if(!fs.FileExists(strPath))
		return -1;

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

	// make new random list	
	BOOL bRandomEachTime = (bCanReloadRandom && ParseXML("RandomEachTime",strData) == "TRUE");
	if(bRandomEachTime)
	{
		strData = MakeNewRandomList(strData);
	}
		
	CString strCurrentFile = ParseXML("CurrentFile",strData);
	CString strCurrentPos = ParseXML("CurrentPos",strData);

	CStringArray stra;
	while(strData.Find("</PlayListEntry>") != -1)
	{
		stra.Add(ParseXML("PlayListEntry",strData));
		strData = strData.Mid(strData.Find("</PlayListEntry>")+strlen("</PlayListEntry>"));
	}
	if(bRandomEachTime)
		UpdatePlayList(strCurrentPlayList,&stra);
	
	(((CMainFrame*)AfxGetMainWnd()))->ClearPlayList(bResetOcx);

	long nHotItem = -1;
	for(int n=0;n<stra.GetSize();n++)
	{
		CString strNew = ParseXML("FullPath",stra.GetAt(n));
		(((CMainFrame*)AfxGetMainWnd()))->AddToPlayList(stra.GetAt(n));
		if(strNew == strCurrentFile)
			nHotItem = n;
	}
	if(bStopPlaying && !strCurrentFile.IsEmpty())
	{
		((CMainFrame*)AfxGetMainWnd())->SetSelectItemOcx(nHotItem,true);
		((CMainFrame*)AfxGetMainWnd())->OnPlayAllFromSelected(nHotItem,0);
		if(!strCurrentPos.IsEmpty())
		{
			LONGLONG dwPos = atol(strCurrentPos);
			((CMainFrame*)AfxGetMainWnd())->m_pMyMediaPlayer->SetCurrentPosition(dwPos);
		}
	}
	return nHotItem;
}

void CPlayListManager::SaveCurrent(CStringArray* pstra,CString strCurrent)
{
	CString strPath = AfxGetApp()->GetProfileString("Settings","InstallPath",DEFAULT_INSTALL_PATH);
	strPath += "\\Playlists";
	SECFileSystem fs;
	if(!fs.DirectoryExists(strPath))
		fs.MakePath(strPath);

	CString strCurrentPlayList = AfxGetApp()->GetProfileString("Settings","CurrentPlaylist","default");
	strPath += "\\" + strCurrentPlayList + ".spl";

	// read data
	CString strData;
	if(fs.FileExists(strPath))
	{
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
	}
	// make new playlist data
	CString strNewData = strCurrent;
	strNewData += "<RandomPlayList>" + ParseXML("RandomPlayList",strData) + "</RandomPlayList>";
	strNewData += "<RandomEachTime>" + ParseXML("RandomEachTime",strData) + "</RandomEachTime>\r\n";
	strNewData += "<MaxFiles>" + ParseXML("MaxFiles",strData) + "</MaxFiles>\r\n";	
	strNewData += ParseXMLArray("RandomDirPath",strData);
	strNewData += "\r\n";

	for(int n=0;n<pstra->GetSize();n++)
	{
		strNewData += "<PlayListEntry>" + pstra->GetAt(n) + "</PlayListEntry>";
	}

	CFile fp;
	TRY
	{
		if(fp.Open(strPath,CFile::modeWrite|CFile::modeCreate))
		{
			DWORD dwSize = strNewData.GetLength();
			fp.Write(strNewData.GetBuffer(dwSize),dwSize);
			strNewData.ReleaseBuffer();
			fp.Close();
		}
	}
	CATCH(CFileException,e)
	{
	}
	END_CATCH
}

CStringArray* CPlayListManager::GetPlayListNames()
{
	CStringArray* pstra = new CStringArray;

	CString strPath = AfxGetApp()->GetProfileString("Settings","InstallPath",DEFAULT_INSTALL_PATH);
	strPath += "\\Playlists";
	SECFileSystem fs;
	if(fs.DirectoryExists(strPath))
	{
		CStringList* pStrList = fs.GetFileList(strPath + "\\*.spl",fs.allfiles);
		if(pStrList->GetCount()>0)
		{
			POSITION pos = pStrList->GetHeadPosition();
			while(pos !=NULL)
			{
				CString str = pStrList->GetNext(pos);
				str = str.Mid(str.ReverseFind('\\')+1);
				str = str.Left(str.ReverseFind('.'));
				pstra->Add(str);
			}
		}
		delete pStrList;
	}
	return pstra;
}

CStringArray* CPlayListManager::GetEntriesForName(CString strName,BOOL bReturnRandName)
{
	CStringArray* pstra = new CStringArray;

	CString strPath = AfxGetApp()->GetProfileString("Settings","InstallPath",DEFAULT_INSTALL_PATH);
	strPath += "\\Playlists\\" + strName + ".spl";
	SECFileSystem fs;
	if(fs.FileExists(strPath))
	{
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

		if(bReturnRandName)
		{
			if(ParseXML("RandomEachTime",strData) == "TRUE")
			{
				pstra->Add(RANDOM_ENTRY_NAME);
				return pstra;
			}
		}

		while(strData.Find("</PlayListEntry>") != -1)
		{
			pstra->Add(ParseXML("PlayListEntry",strData));
			strData = strData.Mid(strData.Find("</PlayListEntry>")+strlen("</PlayListEntry>"));
		}
	}
	return pstra;
}

CString CPlayListManager::GetNextRandomPlaylistName()
{
	CString strName = _T("RandomPlaylist");
	CStringArray* stra = GetPlayListNames();
	int nNum = 1;
	while(nNum < 1000)
	{
		strName.Format("RandomPlaylist%u",nNum);
		BOOL bFound = false;
		for(int n=0;n<stra->GetSize();n++)
		{
			if(strName == stra->GetAt(n))
			{
				bFound = true;
				break;
			}
		}
		if(!bFound)
			break;
		nNum++;
	}
	delete stra;

	return strName;
}

BOOL CPlayListManager::SaveNewPlayList(CString strFileName, CString strData)
{
	CString strPath = AfxGetApp()->GetProfileString("Settings","InstallPath",DEFAULT_INSTALL_PATH);
	strPath += "\\Playlists";
	SECFileSystem fs;
	if(!fs.DirectoryExists(strPath))
		fs.MakePath(strPath);

	strPath += "\\" + strFileName + ".spl";

	CFile fp;
	TRY
	{
		if(fp.Open(strPath,CFile::modeWrite|CFile::modeCreate))
		{
			DWORD dwSize = strData.GetLength();
			fp.Write(strData.GetBuffer(dwSize),dwSize);
			strData.ReleaseBuffer();
			fp.Close();
		}
	}
	CATCH(CFileException,e)
	{
		return false;
	}
	END_CATCH

	return true;
}

void CPlayListManager::UpdatePlayList(CString strName, CStringArray *pstraList)
{
	CString strPath = AfxGetApp()->GetProfileString("Settings","InstallPath",DEFAULT_INSTALL_PATH);
	strPath += "\\Playlists";
	strPath += "\\" + strName + ".spl";

	CString strData;
	// read data
	SECFileSystem fs;
	if(fs.FileExists(strPath))
	{
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
	}
	// make new playlist data
	CString strNewData;
	strNewData += "<CurrentFile>" + ParseXML("CurrentFile",strData) + "</CurrentFile>";
	strNewData += "<CurrentPos>" + ParseXML("CurrentPos",strData) + "</CurrentPos>";
	strNewData += "<RandomPlayList>" + ParseXML("RandomPlayList",strData) + "</RandomPlayList>";
	strNewData += "<RandomEachTime>" + ParseXML("RandomEachTime",strData) + "</RandomEachTime>\r\n";
	strNewData += "<MaxFiles>" + ParseXML("MaxFiles",strData) + "</MaxFiles>\r\n";	
	strNewData += ParseXMLArray("RandomDirPath",strData);
	strNewData += "\r\n";

	for(int n=0;n<pstraList->GetSize();n++)
	{
		strNewData += "<PlayListEntry><FullPath>" + pstraList->GetAt(n) + "</FullPath>";
		CString strShortName = pstraList->GetAt(n);
		strShortName = strShortName.Mid(strShortName.ReverseFind('\\')+1);
		strNewData += "<Name>" + strShortName + "</Name>";
		strNewData += "</PlayListEntry>\r\n";
	}	

	SaveNewPlayList(strName,strNewData);
}

void CPlayListManager::DeletePlayList(CString strName)
{
	CString strPath = AfxGetApp()->GetProfileString("Settings","InstallPath",DEFAULT_INSTALL_PATH);
	strPath += "\\Playlists";
	strPath += "\\" + strName + ".spl";

	SECFileSystem fs;
	fs.DeleteFile(strPath);
}

BOOL CPlayListManager::CheckFileIsStillValid(CString strFilePath)
{
	CString strCurrentPlayList = AfxGetApp()->GetProfileString("Settings","CurrentPlaylist","default");
	CStringArray* pStra = GetEntriesForName(strCurrentPlayList);
	BOOL bFound = false;
	for(int n=0;n<pStra->GetSize();n++)
	{
		CString strTest = pStra->GetAt(n);
		strTest = ParseXML("FullPath",strTest);
		if(strFilePath.CompareNoCase(strTest) == 0)
		{
			bFound = true;
			break;
		}
	}
	delete pStra;
	return bFound;
}

CString CPlayListManager::MakeNewRandomList(CString strOldData)
{
	// num of files
	CString strMaxFiles = ParseXML("MaxFiles",strOldData);
	if(strMaxFiles.IsEmpty())
		strMaxFiles = "30";	
	int nMaxFiles = atoi(strMaxFiles);	

	// random paths
	CStringArray straRandomDirPaths;
	CString strTemp = strOldData;
	while(!ParseXML("RandomDirPath",strTemp).IsEmpty())
	{
		straRandomDirPaths.Add(ParseXML("RandomDirPath",strTemp));
		strTemp = strTemp.Mid(strTemp.Find("</RandomDirPath>") + strlen("</RandomDirPath>"));
	}

	CString strData = _T("<RandomPlayList>TRUE</RandomPlayList>");
	strData += "<MaxFiles>" + strMaxFiles + "</MaxFiles>";
	strData += "<RandomEachTime>TRUE</RandomEachTime>";

	for(int n=0;n<straRandomDirPaths.GetSize();n++)
	{
		strData += "<RandomDirPath>" + straRandomDirPaths.GetAt(n) + "</RandomDirPath>";
	}
	strData += "\r\n";

	CStringArray* pstraList = MakeRandomPlaylist(&straRandomDirPaths,nMaxFiles);
	for(n=0;n<pstraList->GetSize();n++)
	{
		strData += "<PlayListEntry><FullPath>" + pstraList->GetAt(n) + "</FullPath>";
		CString strShortName = pstraList->GetAt(n);
		strShortName = strShortName.Mid(strShortName.ReverseFind('\\')+1);
		strData += "<Name>" + strShortName + "</Name>";
		strData += "</PlayListEntry>\r\n";
	}	
	delete pstraList;

	return strData;
}
