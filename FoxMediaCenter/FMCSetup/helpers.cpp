
// helpers.cpp

#include "stdafx.h"
#include "helpers.h"
#include "zip\ZipArchive.h"	

HRESULT CreateShortCut(LPCSTR pszShortcutFile, LPSTR pszLink,LPSTR pszDesc)
{
	CString str = pszShortcutFile;
	str += " ";
	str += pszLink;
	str += " ";
	str += pszDesc;

	HRESULT hres;		 
	IShellLink *psl;
	CoInitialize(NULL);
	// Create an IShellLink object and get a pointer to the IShellLink 
	// interface (returned from CoCreateInstance).
	hres = CoCreateInstance (CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
	IID_IShellLink, (void **)&psl);
	if (SUCCEEDED (hres))
	{
		IPersistFile *ppf;
		// Query IShellLink for the IPersistFile interface for 
		// saving the shortcut in persistent storage.
		hres = psl->QueryInterface (IID_IPersistFile, (void **)&ppf);
		if (SUCCEEDED (hres))
		{ 
			WORD wsz [MAX_PATH]; // buffer for Unicode string
			// Set the path to the shortcut target.
			hres = psl->SetPath (pszShortcutFile);
			// Set the description of the shortcut.
			hres = psl->SetDescription (pszDesc);
			// Ensure that the string consists of ANSI characters.
			MultiByteToWideChar (CP_ACP, 0, pszLink, -1, wsz, MAX_PATH);
			// Save the shortcut via the IPersistFile::Save member function.
			hres = ppf->Save (wsz, TRUE);
			// Release the pointer to IPersistFile.
			ppf->Release ();
		}
		// Release the pointer to IShellLink.
		psl->Release ();
	}
	CoUninitialize();  
	return hres;
} 

CString GetProgramsPath()
{
	CString strRegPrograms;
	SECRegistry reg;
	BOOL bOk = reg.Connect(HKEY_CURRENT_USER);
	bOk = reg.Open("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",SECRegistry::permissionRead);
	bOk = reg.GetStringValue("Programs", strRegPrograms); 

	return strRegPrograms;
}

BOOL CreateProgramsLink(CString strExePath,CString strLinkName,CString strDisplayName)
{
	CString strPathStartup;
	strPathStartup = GetProgramsPath();

	// put is program files
	CString strLink;
	strLink = strPathStartup + "\\" + strLinkName;
	if(strLinkName.Find("\\")!= -1)
	{
		SECFileSystem fp;
		fp.MakePath(strLink.Left(strLink.ReverseFind('\\')));
	}
	HRESULT hr = CreateShortCut(strExePath,strLink.GetBuffer(strLink.GetLength()),strDisplayName.GetBuffer(strDisplayName.GetLength()));
	strLink.ReleaseBuffer();
	strDisplayName.ReleaseBuffer(); 

	return (hr == 0);
}

CString GetWinDesktopPath()
{
	CString strRegStartup;
	SECRegistry reg;
	BOOL bOk = reg.Connect(HKEY_CURRENT_USER);
	bOk = reg.Open("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",SECRegistry::permissionRead);
	bOk = reg.GetStringValue("Desktop", strRegStartup); 

	return strRegStartup;
}

BOOL CreateDesktopLink(CString strExePath,CString strLinkName,CString strDisplayName)
{
	CString strPathStartup;
	strPathStartup = GetWinDesktopPath();
	
	CString strLink;
	strLink = strPathStartup + "\\" + strLinkName;
	CreateShortCut(strExePath,strLink.GetBuffer(strLink.GetLength()),strDisplayName.GetBuffer(strDisplayName.GetLength()));
	strLink.ReleaseBuffer();
	strDisplayName.ReleaseBuffer();

	return TRUE;
}

BOOL UnzipFile(CString strZipName)
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
	return true;
}

