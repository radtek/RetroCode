// ZipPathComponent.cpp: implementation of the CZipPathComponent class.
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
#include "ZipPathComponent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CZipPathComponent::~CZipPathComponent()
{

}

void CZipPathComponent::SetFullPath(const CZipString& szFullPath)
{
	TCHAR szDrive[_MAX_DRIVE];
	TCHAR szDir[_MAX_DIR];
	TCHAR szFname[_MAX_FNAME];
	TCHAR szExt[_MAX_EXT];
	_tsplitpath(szFullPath, szDrive , szDir, szFname, szExt);
	m_szDrive = szDrive;
	m_szDirectory = szDir;
	m_szDirectory.TrimLeft(m_cSeparator);
	m_szDirectory.TrimRight(m_cSeparator);
	SetExtension(szExt);
	m_szFileName = szFname;
}


CZipString CZipPathComponent::GetNoDrive()
{
	CZipString szPath = m_szDirectory;
	CZipString szFileName = GetFullFileName();
	if (!szFileName.IsEmpty() && !szPath.IsEmpty())
		szPath += m_cSeparator;

	szPath += szFileName;
	return szPath;	
}

