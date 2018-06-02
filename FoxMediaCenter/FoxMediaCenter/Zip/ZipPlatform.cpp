// ZipPlatform.cpp: implementation of the ZipPlatform namespace.
// Part of the ZipArchive library
// 
// Copyright (C) 2000 - 2001 Tadeusz Dracz.
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// For the licensing details see the file License.txt
////////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "ZipPlatform.h"
#include "ZipFileHeader.h"
#include "ZipException.h"
#include "ZipAutoBuffer.h"
#include <sys/stat.h>

#if defined _MSC_VER && !defined __BORLANDC__ /*_MSC_VER may be defined in Borland after converting the VC project */
        #include <sys/utime.h>
#else
        #include <utime.h>
#endif

#include <direct.h>
#include <io.h>
#include <time.h> 


#include "ZipPathComponent.h"
TCHAR CZipPathComponent::m_cSeparator = _T('\\');

#include "ZipCompatibility.h"

#ifndef _UTIMBUF_DEFINED
#define _utimbuf utimbuf 
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DWORD ZipPlatform::GetDeviceFreeSpace(LPCTSTR lpszPath)
{
	DWORD SectorsPerCluster, BytesPerSector, NumberOfFreeClusters, TotalNumberOfClusters;
	CZipPathComponent zpc (lpszPath);
	if (!GetDiskFreeSpace(
		zpc.GetFileDrive(),
		&SectorsPerCluster,
		&BytesPerSector,
		&NumberOfFreeClusters,
		&TotalNumberOfClusters))
			return 0;
	__int64 total = SectorsPerCluster * BytesPerSector * NumberOfFreeClusters;
	return (DWORD)total;
}
bool ZipPlatform::GetCurrentDirectory(CZipString& sz)
{
	DWORD i = ::GetCurrentDirectory(0, NULL);
	if (!i)
		return false;
	TCHAR* pBuf = new TCHAR[i];
	bool b = true;
	if (!::GetCurrentDirectory(i, pBuf))
		b = false;
	else
		sz = pBuf;
	delete[] pBuf;
	return b;
}

bool ZipPlatform::SetFileAttr(LPCTSTR lpFileName, DWORD uAttr)
{
	return ::SetFileAttributes(lpFileName, uAttr) != 0;
}

bool ZipPlatform::GetFileAttr(LPCTSTR lpFileName, DWORD& uAttr)
{
	// not using MFC due to MFC bug (attr is one byte there)
	DWORD temp = ::GetFileAttributes(lpFileName);
	if (temp == -1)
		return false;
	uAttr = temp;
	return true;
	
}

bool ZipPlatform::GetFileModTime(LPCTSTR lpFileName, time_t & ttime)
{
#if defined _MSC_VER && !defined __BORLANDC__ /*_MSC_VER may be defined in Borland after converting the VC project */
    struct _stat st;
    if (_tstat(lpFileName, &st) != 0)
#else
    struct stat st;
    if (stat(lpFileName, &st) != 0)
#endif
	return false;

	ttime = st.st_mtime;
	return true;
}

bool ZipPlatform::SetFileModTime(LPCTSTR lpFileName, time_t ttime)
{
	struct _utimbuf ub;
	ub.actime = time(NULL);
	ub.modtime = ttime;
	return _tutime(lpFileName, &ub) == 0;
}


bool ZipPlatform::ChangeDirectory(LPCTSTR lpDirectory)
{
	return _tchdir(lpDirectory) == 0; // returns 0 if ok
}
int ZipPlatform::FileExists(LPCTSTR lpszName)
{
	if (_taccess(lpszName, 0) == 0)
	{
		if (DirectoryExists(lpszName))
			return -1;
		return 1;
	}
	else
		return 0;

}

ZIPINLINE  bool ZipPlatform::IsDriveRemovable(LPCTSTR lpszFilePath)
{
	CZipPathComponent zpc(lpszFilePath);
	return ::GetDriveType(zpc.GetFileDrive()) == DRIVE_REMOVABLE;
}

ZIPINLINE  bool ZipPlatform::SetVolLabel(LPCTSTR lpszPath, LPCTSTR lpszLabel)
{
	CZipPathComponent zpc(lpszPath);
	CZipString szDrive = zpc.GetFileDrive();
	CZipPathComponent::AppendSeparator(szDrive);
	return ::SetVolumeLabel(szDrive, lpszLabel) != 0;
}

ZIPINLINE void ZipPlatform::AnsiOem(CZipAutoBuffer& buffer, bool bAnsiToOem)
{
	if (bAnsiToOem)
		CharToOemBuffA(buffer, buffer, buffer.GetSize());
	else
		OemToCharBuffA(buffer, buffer, buffer.GetSize());
}

ZIPINLINE  void ZipPlatform::RemoveFile(LPCTSTR lpszFileName)
{
	if (!::DeleteFile((LPTSTR)lpszFileName))
		CZipException::Throw(CZipException::notRemoved, lpszFileName);

}
ZIPINLINE  void ZipPlatform::RenameFile( LPCTSTR lpszOldName, LPCTSTR lpszNewName )
{
	if (!::MoveFile((LPTSTR)lpszOldName, (LPTSTR)lpszNewName))
		CZipException::Throw(CZipException::notRenamed, lpszOldName);
}
ZIPINLINE  bool ZipPlatform::IsDirectory(DWORD uAttr)
{
	return (uAttr & FILE_ATTRIBUTE_DIRECTORY) != 0;
}
ZIPINLINE  bool ZipPlatform::CreateDirectory(LPCTSTR lpDirectory)
{
	return ::CreateDirectory(lpDirectory, NULL) != 0;
}

// ZIPINLINE  DWORD ZipPlatform::GetDefaultAttributes()
// {
// 	return FILE_ATTRIBUTE_ARCHIVE;
// }

ZIPINLINE  int ZipPlatform::GetSystemID()
{
	return ZipCompatibility::zcDosFat;
}

#ifdef _UNICODE	
int ZipPlatform::WideToSingle(LPCTSTR lpWide, CZipAutoBuffer &szSingle)
{
	size_t wideLen = wcslen(lpWide);
	if (wideLen == 0)
	{
		szSingle.Release();
		return 0;
	}

	// iLen does not include terminating character
	int iLen = WideCharToMultiByte(CP_ACP,0, lpWide, wideLen, szSingle, 
		0, NULL, NULL);
	if (iLen > 0)
	{
		szSingle.Allocate(iLen, true);
		iLen = WideCharToMultiByte(CP_ACP,0, lpWide , wideLen, szSingle, 
			iLen, NULL, NULL);
		ASSERT(iLen != 0);
	}
	else // here it means error
	{
		szSingle.Release();
		iLen --;
	}
	return iLen;

}
int ZipPlatform::SingleToWide(const CZipAutoBuffer &szSingle, CZipString& szWide)
{
	int singleLen = szSingle.GetSize();
		// iLen doesn't include terminating character
	int iLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szSingle.GetBuffer(), singleLen, NULL, 0);
	if (iLen > 0)
	{
		iLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szSingle.GetBuffer(), singleLen, 
			szWide.GetBuffer(iLen) , iLen);
		szWide.ReleaseBuffer(iLen);
		ASSERT(iLen != 0);
	}
	else
	{
		szWide.Empty();
		iLen --; // return -1
	}
	return iLen;

}
#endif

#ifndef _MFC_VER
#include <io.h>
#include <share.h>
bool ZipPlatform::TruncateFile(int iDes, DWORD iSize)
{
	int ret = chsize(iDes, iSize);
	return ret != -1;

}

int ZipPlatform::OpenFile(LPCTSTR lpszFileName, UINT iMode, int iShareMode)
{
	switch (iShareMode)
	{
	case (CZipFile::shareDenyWrite & CZipFile::shareDenyRead):
		iShareMode = SH_DENYRW;
		break;
	case (CZipFile::shareDenyRead):
		iShareMode = SH_DENYRD;
		break;
	case (CZipFile::shareDenyWrite):
		iShareMode = SH_DENYWR;
		break;
	default:
		iShareMode = SH_DENYNO;
	}
	return  _tsopen(lpszFileName, iMode, iShareMode, S_IREAD | S_IWRITE /*required only when O_CREAT mode*/);
}

bool ZipPlatform::FlushFile(int iDes)
{
	return _commit(iDes) == 0;
}

int ZipPlatform::GetFileSystemHandle(int iDes)
{
	return _get_osfhandle(iDes);
}
#endif //_MFC_VER