// ZipFile.h: interface for the ZipFiles class.
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

#if !defined(AFX_ZIPFILE_H__80609DE0_2C6D_4C94_A90C_0BE34A50C769__INCLUDED_)
#define AFX_ZIPFILE_H__80609DE0_2C6D_4C94_A90C_0BE34A50C769__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ZipAbstractFile.h"

class CZipFile :public CZipAbstractFile, public CFile
{
public:
	DECLARE_DYNAMIC(CZipFile)
// 	__int64 Seek(__int64 dOff, UINT nFrom);
void Flush(){CFile::Flush();}
	long GetPosition() {return CFile::GetPosition() ;}
	CZipString GetFilePath(){return CFile::GetFilePath();}
	void SetLength(long nNewLen) {CFile::SetLength(nNewLen);}
	UINT Read(void *lpBuf, UINT nCount){return CFile::Read(lpBuf, nCount);}
	void Write(const void* lpBuf, UINT nCount){CFile::Write(lpBuf, nCount);}
	long Seek(long lOff, int nFrom){return CFile::Seek(lOff, nFrom);}
	DWORD GetLength(){return CFile::GetLength();}
	bool Open( LPCTSTR lpszFileName, UINT nOpenFlags, bool bThrowExc)
	{
		CFileException* e = new CFileException;
		bool bRet = CFile::Open(lpszFileName, nOpenFlags, e) != 0;
		if (!bRet && bThrowExc)
			throw e;
		e->Delete();
		return bRet;

	}
	CZipFile();
	bool IsClosed()
	{
		return m_hFile == (UINT)CFile::hFileNull;
	}


	CZipFile( LPCTSTR lpszFileName, UINT nOpenFlags ):CFile(lpszFileName, nOpenFlags)
	{
	}
	void Close( )
	{
#ifdef _DEBUG // to prevent assertion if the file is already closed
 		if (!IsClosed())
#endif
			CFile::Close();

	}
	virtual ~CZipFile();

};

#endif // !defined(AFX_ZIPFILE_H__80609DE0_2C6D_4C94_A90C_0BE34A50C769__INCLUDED_)
