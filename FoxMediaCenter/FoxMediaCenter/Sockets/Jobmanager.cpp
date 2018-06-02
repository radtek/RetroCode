// JobManager.cpp: implementation of the CJobManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\SteveMediaCenter.h"
#include "JobManager.h"
#include "..\helpers.h"
#include "..\MainFrm.h"
#include "PingJobManager.h"
#include "UpdateManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Status for Jobs = 
// "none" = new job
// "Finished" = done...

CJobManager::CJobManager()
{
	CString strJobFile;
	// install dir
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\'));
	strJobFile = strDestination + "\\myupdates.dat";
	// serialize
	TRY
	{
		SECCryptoFile fp;
		if(fp.Open(strJobFile,"duyb783slp", CFile::modeCreate|CFile::modeNoTruncate|CFile::modeRead, SECCryptoFile::ECB))
		{
			CArchive ar( &fp, CArchive::load);
			Serialize(ar);
			ar.Close();
			fp.Close();
		}
	}
	CATCH(CFileException,e)
	{
		DebugMessage("Error while trying to load jobs file");
	}
	END_CATCH
}

CJobManager::~CJobManager()
{
	Save();

	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		CJob* pJob = (CJob*)m_obaJobs.GetAt(n);
		if(pJob)
			delete pJob;
	}
	m_obaJobs.RemoveAll();
}

void CJobManager::Save()
{
	CString strJobFile;
	// install dir
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\'));
	strJobFile = strDestination + "\\myupdates.dat";
	// serialize
	TRY
	{
		SECCryptoFile fp;
		if(fp.Open(strJobFile,"duyb783slp", CFile::modeCreate|CFile::modeWrite, SECCryptoFile::ECB))
		{
			CArchive ar( &fp, CArchive::store);
			Serialize(ar);
			ar.Close();
			fp.Close();
		}
	}
	CATCH(CFileException,e)
	{
		DebugMessage("Error while trying to save jobs file");
	}
	END_CATCH
}

void CJobManager::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{
		for(int n=0;n<m_obaJobs.GetSize();n++)
		{
			CJob* pJob = (CJob*)m_obaJobs.GetAt(n);
			TRY
			{
				ar << pJob->m_strParams;
			}
			CATCH(CArchiveException,e)
			{
				DebugMessage("CJobManager::Serialize store exception");
			}
			END_CATCH
		}
	}
	else
	{	
		m_obaJobs.RemoveAll();
		BOOL bLoad = TRUE;
		while(bLoad)
		{
			CString strParams;
			TRY
			{
				ar >> strParams;
				CJob* pJob = new CJob(strParams);
				m_obaJobs.Add(pJob);
			}
			CATCH(CArchiveException,e)
			{
				bLoad = FALSE;
			}
			END_CATCH
		}
	}
}

BOOL CJobManager::NewJob(CString strParams,BOOL bContinueDownloads,BOOL bDontCheck)
{
	// look for any existing job, means download started already, not vaid for testing for same job
	if(!bDontCheck)
	{
		for(int n=0;n<m_obaJobs.GetSize();n++)
		{
			CJob* pJob = (CJob*)m_obaJobs.GetAt(n);
			// test for same job
			CString strJobTest = pJob->m_strParams;
			CString strNewTest = strParams;	
			strJobTest = ReplaceXML("","Status",strJobTest);
			strNewTest = ReplaceXML("","Status",strNewTest);

			if(strJobTest == strNewTest)
			{
				ContinueAnyCurrentJobs();
				return FALSE;
			}
		}
	}
	strParams = ReplaceXML("Started","Status",strParams);
	CJob* pJob = new CJob(strParams);
	m_obaJobs.Add(pJob);
	
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();

	if(bContinueDownloads)
		ContinueAnyCurrentJobs();
	
	return TRUE;
}

void CJobManager::ContinueJob(CJob* pJob)
{
	if(!pJob->ContinueJob())
	{
		DeleteJob(pJob);
	}
}

void CJobManager::DeleteJob(CJob *pJob,BOOL bRemoveFromList)
{
	BOOL bJobVerified = FALSE;
	CObArray obTemp;
	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		if(pJob != m_obaJobs.GetAt(n))
			obTemp.Add(m_obaJobs.GetAt(n));
		else
			bJobVerified = TRUE;
	}

	if(pJob && bJobVerified)
	{
		pJob->StopJob();
		m_obaJobs.RemoveAll();
		m_obaJobs.Copy(obTemp);
		delete pJob;
		pJob = NULL;
	}
}

void CJobManager::StopAllJobs(CString strShowID)
{
	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		CJob *pJob = (CJob*)m_obaJobs.GetAt(n);
		if(strShowID.IsEmpty() || ParseXML("ShowID",pJob->m_strParams) == strShowID)
			pJob->StopJob();
	}
}

void CJobManager::ContinueAnyCurrentJobs(BOOL bPolite)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	pMain->m_bIsUnzipping = FALSE;
	pMain->m_bPaused = FALSE;

	if(!bPolite && AreAnyJobsDownloading())
		return;

	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		CJob* pJob = (CJob*)m_obaJobs.GetAt(n);
		CString strStatus = ParseXML("Status",pJob->m_strParams);
		if(strStatus == "none" || strStatus == "Started")
		{
			pJob->StopJob();   // maybe only continue none job, and change stopped job to none
			pJob->ContinueJob();
			return;
		}
	}
}

BOOL CJobManager::DownloadFile(CString strParams)
{	
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();

	CString strFileUrl = ParseXML("FileURL",strParams);
	// FilePackage
	BOOL bFileDownload = (ParseXML("FilePackage",strParams) == "TRUE");
	// Skin object
	BOOL bSkin = (ParseXML("Skin",strParams) == "TRUE");
	CString strSkinName = ParseXML("SkinName",strParams);

	// check if already downloading
	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		CJob* pJob = (CJob*)m_obaJobs.GetAt(n);
		// test for same job
		CString strJobTest = pJob->m_strParams;
		CString strTestURL = ParseXML("FileURL",strJobTest);	
		if(strTestURL == strFileUrl)
		{
			ContinueAnyCurrentJobs();
			return false;
		}
	}
	// copy current jobs to temp array
	CObArray obTemp;
	obTemp.Copy(m_obaJobs);
	m_obaJobs.RemoveAll();

	CString strTest = strFileUrl;
	strTest.MakeLower();
	if(strTest.Left(7) != "http://")
	{
		return false;
	}
		
	// destination dir
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\'));

	if(bSkin)
		strDestination += "\\Skins\\" + strSkinName;
	else
		strDestination += "\\temp";

	SECFileSystem fp;
	if(!fp.DirectoryExists(strDestination))
	{
		if(!fp.MakePath(strDestination))
		{
			return false;
		}
	}
	// Job string in XML format
	RemoveSpacesForURL(strFileUrl);
	CString strJob = "<FileURL>" + strFileUrl + "</FileURL>";

	// file to execute
	CString strRunFile = strFileUrl.Mid(strFileUrl.ReverseFind('/')+1);
	// path 
	strJob += "<DownloadPath>" + strDestination + "\\" + strRunFile + ".part1</DownloadPath>";
	strJob += "<RunEXE>" + strRunFile + "</RunEXE>";

	// if file add these
	if(bFileDownload)
	{
		strJob += "<FilePackage>TRUE</FilePackage>";
		strJob += "<LaunchFile>" + ParseXML("LaunchFile",strParams) + "</LaunchFile>";
	}
	// job status
	strJob += "<Status>none</Status>";

	NewJob(strJob,FALSE,TRUE);

	m_obaJobs.Append(obTemp);
	obTemp.RemoveAll();

	Save();
	ContinueAnyCurrentJobs();

	return TRUE;
}

BOOL CJobManager::AreAnyJobsDownloading()
{
	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		CJob* pJob = (CJob*)m_obaJobs.GetAt(n);
		CString strTest = ParseXML("Status",pJob->m_strParams);
		if(strTest.CompareNoCase("Downloading") == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CJobManager::DeleteAnyJobsWithFileURL(CString strFileURL)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();

	CObArray obTemp;
	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		CJob* pJob = (CJob*)m_obaJobs.GetAt(n);
		if(strFileURL == ParseXML("FileURL",pJob->m_strParams))
		{
			pJob->StopJob();

			CString strFilePath = ParseXML("DownloadPath",pJob->m_strParams);		
			SECFileSystem fp;
			if(!strFilePath.IsEmpty())
				fp.DeleteFile(strFilePath);
			delete pJob;
			pJob = NULL;
		}
		else
			obTemp.Add(pJob);
	}
	m_obaJobs.RemoveAll();
	m_obaJobs.Copy(obTemp);
}

void CJobManager::DeleteJobWithURL(CString strFileURL)
{
	CObArray obTemp;
	SECFileSystem fp;
	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		CJob* pJob = (CJob*)m_obaJobs.GetAt(n);
		if(strFileURL == ParseXML("FileURL",pJob->m_strParams))
		{
			pJob->StopJob();
			CString strFile = ParseXML("DownloadPath",pJob->m_strParams);
			fp.DeleteFile(strFile);
			delete pJob;					
		}
		else
			obTemp.Add(pJob);
	}
	m_obaJobs.RemoveAll();
	m_obaJobs.Copy(obTemp);
}

BOOL CJobManager::GetUpdateFile(CString strParams)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CString strFileURL = ParseXML("FileURL",strParams);

	// check if already downloading
	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		CJob* pJob = (CJob*)m_obaJobs.GetAt(n);
		// test for same job
		CString strJobTest = pJob->m_strParams;
		CString strTestURL = ParseXML("FileURL",strJobTest);
		if(strTestURL == strFileURL)
		{
			ContinueAnyCurrentJobs();
			return FALSE;
		}
	}

	// URL of file
	CString strTest = strFileURL;
	strTest.MakeLower();
	if(strTest.Left(7) != "http://")
	{
		DebugMessage("Error in URL for file, " + strFileURL);
		return FALSE;
	}
		
	// destination dir
	CString strDestination;
	CString strDirectory = ParseXML("Directory",strParams);
	if(strDirectory.CompareNoCase("system") == 0)
	{
		GetSystemDirectory(strDestination.GetBuffer(MAX_PATH),MAX_PATH);
		strDestination.ReleaseBuffer();
	}
	else
	{
		GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
		strDestination.ReleaseBuffer();
		strDestination = strDestination.Left(strDestination.ReverseFind('\\'));
		if(!strDirectory.IsEmpty())
			strDestination += "\\" + strDirectory;
		else
			strDestination += "\\temp";
	}

	SECFileSystem fp;
	if(!fp.DirectoryExists(strDestination))
	{
		if(!fp.MakePath(strDestination))
		{
			if(!fp.MakePath(strDestination))
				return FALSE;
		}
	}

	// Job string in XML format
	RemoveSpacesForURL(strFileURL);
	// include all params by default
	CString strJob = strParams;
	strJob = ReplaceXML(strFileURL,"FileURL",strParams);
	// file to execute
	CString strRunFile = strFileURL.Mid(strFileURL.ReverseFind('/')+1);
	// path 
	strJob += "<DownloadPath>" + strDestination + "\\" + strRunFile + ".part1</DownloadPath>";
	strJob += "<RunEXE>" + strRunFile + "</RunEXE>";
	strJob += "<RegName>" + ParseXML("RegName",strParams) + "</RegName>";
	strJob += "<Version>" + ParseXML("Version",strParams) + "</Version>";
	strJob += "<SetAsCurrentSkin>" + ParseXML("SetAsCurrentSkin",strParams) + "</SetAsCurrentSkin>";
	strJob += "<SkinName>" + ParseXML("SkinName",strParams) + "</SkinName>";

	// job status
	strJob = ReplaceXML("none","Status",strJob);
	// mark as update job	
	strJob += "<UpdateFile>TRUE</UpdateFile>";

	NewJob(strJob);

	return TRUE;
}

BOOL CJobManager::VerfifyJobOK(CJob *pJob)
{
	for(int n=0;n<m_obaJobs.GetSize();n++)
	{
		CJob* pJobFound = (CJob*)m_obaJobs.GetAt(n);
		if(pJob == pJobFound) // same job
			return TRUE;
	}
	return FALSE;
}

void CJobManager::ExecuteJob(CJob *pJob)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if(!VerfifyJobOK(pJob))
		return;

	CString strParams = pJob->m_strParams;
	CString strURL = ParseXML("FileURL",strParams);
	CString strDownloadPath = ParseXML("DownloadPath",strParams);
	BOOL bIsUpdateFile = (ParseXML("UpdateFile",strParams)=="TRUE");
	BOOL bFileDownload = (ParseXML("FilePackage",strParams)=="TRUE");

	SECFileSystem fp;
	// install job
	CString strFile = ParseXML("DownloadPath",strParams);
	CString strExe = ParseXML("RunEXE",strParams);
	strExe = strFile.Left(strFile.ReverseFind('\\')+1) + strExe;
	fp.RenameFile(strFile,strExe);

	// see if zip file
	if(strExe.Right(3).CompareNoCase("zip") == 0) // zip file
	{
		BOOL bOK = MyUnZipFile(strExe);
		fp.DeleteFile(strExe);	
		if(bOK)
		{
			CString strLaunchFile = ParseXML("LaunchFile",strParams);
			if(!strLaunchFile.IsEmpty())
			{
				strExe = strExe.Left(strExe.ReverseFind('\\')+1);
				strLaunchFile = strExe + strLaunchFile;

				PROCESS_INFORMATION pInfo;
				memset(&pInfo,0,sizeof(PROCESS_INFORMATION));
				STARTUPINFO startup;
				memset(&startup,0,sizeof(STARTUPINFO));
				startup.cb = sizeof(STARTUPINFO);
				startup.lpReserved = NULL;
				startup.lpDesktop = NULL;
				startup.lpTitle = NULL;
				startup.dwFlags = STARTF_USESHOWWINDOW;
				startup.wShowWindow = SW_HIDE;
				startup.lpReserved2 = NULL;

				BOOL bOK = CreateProcess(strLaunchFile,NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE|HIGH_PRIORITY_CLASS,NULL,NULL,&startup,&pInfo); 
				WaitForSingleObject(pInfo.hThread,30*1000);
				fp.DeleteFile(strLaunchFile);	
			}
			CString strRegVal = ParseXML("RegName",strParams);
			CString strVer = ParseXML("Version",strParams);
			AfxGetApp()->WriteProfileString("Settings",strRegVal,strVer);

			BOOL bSetSkin = (ParseXML("SetAsCurrentSkin",strParams) == "TRUE");
			if(bSetSkin)
			{
				CString strPath;
				GetModuleFileName(NULL,strPath.GetBuffer(MAX_PATH),MAX_PATH);
				strPath.ReleaseBuffer();
				strPath = strPath.Left(strPath.ReverseFind('\\')+1);
				strPath += "Skins\\";
				CString strSkin = ParseXML("SkinName",strParams);
				if(fp.DirectoryExists(strPath + strSkin))
				{
					AfxGetApp()->WriteProfileString("Settings","CurrentSkin",strSkin);
					CString strFile = strPath + strSkin + "\\playlist.html";
					pMain->OnDeletePlayList(0,0);
					pMain->LoadPlayListSkin(strFile,SW_SHOW);
				}
			}
		}
	}

	DeleteJob(pJob);
	Save();

	ContinueAnyCurrentJobs();
}