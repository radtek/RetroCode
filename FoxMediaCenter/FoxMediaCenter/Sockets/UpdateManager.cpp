// UpdateManager.cpp : implementation file
//

#include "stdafx.h"
#include "..\SteveMediaCenter.h"
#include "UpdateManager.h"
#include "..\helpers.h"
#include "..\MainFrm.h"
#include "JobManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateManager

CUpdateManager::CUpdateManager()
{
	m_TimerRetryFail = NULL;

	CString strFile;
	// install dir
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\'));
	strFile = strDestination + "\\updates.dat";
	// serialize
	TRY
	{
		SECCryptoFile fp;
		if(fp.Open(strFile,"duyb783slp", CFile::modeCreate|CFile::modeNoTruncate|CFile::modeRead, SECCryptoFile::ECB))
		{
			CArchive ar( &fp, CArchive::load);
			Serialize(ar);
			ar.Close();
			fp.Close();
		}
	}
	CATCH(CFileException,e)
	{
		DebugMessage("Error while trying to load updates file");
	}
	END_CATCH
}

CUpdateManager::~CUpdateManager()
{
	SaveData();
}

BEGIN_MESSAGE_MAP(CUpdateManager, CWnd)
	//{{AFX_MSG_MAP(CUpdateManager)
	ON_WM_TIMER()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CUpdateManager message handlers
void CUpdateManager::SaveData()
{
	CString strFile;
	// install dir
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\'));
	strFile = strDestination + "\\updates.dat";
	// serialize
	TRY
	{
		SECCryptoFile fp;
		if(fp.Open(strFile,"duyb783slp", CFile::modeCreate|CFile::modeWrite, SECCryptoFile::ECB))
		{
			CArchive ar( &fp, CArchive::store);
			Serialize(ar);
			ar.Close();
			fp.Close();
		}
	}
	CATCH(CFileException,e)
	{
		DebugMessage("Error while trying to save updates file");
	}
	END_CATCH
}

int CUpdateManager::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// try updates after 10 secs
	if(m_straJobs.GetSize() > 0)
		m_TimerRetryFail = SetTimer(ID_RETRY_UPDATE,10*1000,NULL);

	return 0;
}

void CUpdateManager::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{
		for(int n=0;n<m_straJobs.GetSize();n++)
		{
			TRY
			{
				ar << m_straJobs.GetAt(n);
			}
			CATCH(CArchiveException,e)
			{
				DebugMessage("CUpdateManager::Serialize store exception");
			}
			END_CATCH
		}
	}
	else
	{	
		m_straJobs.RemoveAll();
		BOOL bLoad = TRUE;
		while(bLoad)
		{
			CString strParams;
			TRY
			{
				ar >> strParams;
				BOOL bAdd = TRUE;
				CString strRegVal = ParseXML("RegName",strParams);
				if(strRegVal == "AppVersion")
				{
					CString strVer = ParseXML("Version",strParams);
					if(strVer <= CString(VERSION))
						bAdd = FALSE;
				}
				if(bAdd)
					m_straJobs.Add(strParams);
			}
			CATCH(CArchiveException,e)
			{
				bLoad = FALSE;
			}
			END_CATCH
		}
	}
}

BOOL CUpdateManager::IsURLAlreadyInUpdateList(CString strURL)
{
	for(int n=0;n<m_straJobs.GetSize();n++)
	{		
		CString strJobURL = ParseXML("FileURL",m_straJobs.GetAt(n));
		if(strJobURL.CompareNoCase(strURL) == 0)
			return TRUE;
	}
	
	return FALSE;
}

BOOL CUpdateManager::NewUpdate(CString strParams,BOOL bTimerRetry)
{
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\')+1);
	
	CString strRegVal = ParseXML("RegName",strParams);
	BOOL bIsApp = (strRegVal == "AppVersion");
	BOOL bRegister = (ParseXML("NeedsRegister",strParams) == "TRUE");
	SECFileSystem fp;
	if(!bIsApp)
	{
		// Downloaded file name
		CString strFileName = ParseXML("FileName",strParams);
		// filename to copy over
		CString strFileNameOriginal = ParseXML("OriginalFileName",strParams);
		//fp.DeleteFile(strDestination + strFileNameOriginal);
		if(::CopyFile(strDestination + strFileName,strDestination + strFileNameOriginal,FALSE))
		{
			if(bRegister)
				RegisterOCX(strFileNameOriginal);
			SECFileSystem fp;
			fp.DeleteFile(strDestination + strFileName);
			CString strVer = ParseXML("Version",strParams);
			CVodexaDownloaderApp* pApp = (CVodexaDownloaderApp*)AfxGetApp();
			pApp->WriteProfileString("Settings",strRegVal,strVer);
			return TRUE;
		}
		else	// failed update
		{
			if(fp.FileExists(strDestination + strFileName))
			{
				DebugMessage("File locked " + strDestination + strFileName);
				if(!IsURLAlreadyInUpdateList(ParseXML("FileURL",strParams)))
				{
					m_straJobs.Add(strParams);
				}
				m_TimerRetryFail = SetTimer(ID_RETRY_UPDATE,ONE_MINUTE,NULL);
				if(bTimerRetry)
					return FALSE;
				else
					return TRUE;
			}
			else
				return TRUE;
		}

	}
	// run exe to update App
	if(!IsURLAlreadyInUpdateList(ParseXML("FileURL",strParams)))
	{
		DebugMessage("adding exe to list, " + ParseXML("FileURL",strParams));
		m_straJobs.Add(strParams);
	}

	// don't update if Playing video
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if(SendMessageToPlayerOcx("<Message>PlayingVideo</Message>",pMain->m_hWnd))
	{
		DebugMessage("Playing video, update in a minute");
		m_TimerRetryFail = SetTimer(ID_RETRY_UPDATE,ONE_MINUTE,NULL);
		SaveData();
		if(bTimerRetry)
			return FALSE;
		else
			return TRUE;
	}
	DebugMessage("About to run update");
	
	if(bTimerRetry)
	{
		CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
		pMain->m_pJobManager->StopAllJobs();
		RunUpdateExe();
	}

	return FALSE;
}

void CUpdateManager::OnTimer(UINT nIDEvent) 
{
	CWnd::OnTimer(nIDEvent);

	// retry failed
	if(nIDEvent == ID_RETRY_UPDATE)
	{
		KillTimer(m_TimerRetryFail);
		//if job there
		if(m_straJobs.GetSize() > 0)
		{	
			DebugMessage("NewUpdate retry timer");
			DebugMessage("TimeStamp");	
			CString strParams = m_straJobs.GetAt(0);
			if(NewUpdate(strParams,TRUE))
			{
				m_straJobs.RemoveAt(0);
				m_TimerRetryFail = SetTimer(ID_RETRY_UPDATE,5*1000,NULL);
			}
		}	
	}
}

void CUpdateManager::RunUpdateExe()
{
	CString strDestination;
	GetModuleFileName(NULL,strDestination.GetBuffer(MAX_PATH),MAX_PATH);
	strDestination.ReleaseBuffer();
	strDestination = strDestination.Left(strDestination.ReverseFind('\\'));
	CString strExe = strDestination + "\\update.exe";

	// run updater
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
	
	BOOL bOK = CreateProcess(strExe,NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE|HIGH_PRIORITY_CLASS,NULL,NULL,&startup,&pInfo); 

	WPARAM wPar = MAKEWPARAM(ID_TRAY_EXIT,0);
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	pMain->PostMessage(WM_COMMAND,wPar,NULL);
}
