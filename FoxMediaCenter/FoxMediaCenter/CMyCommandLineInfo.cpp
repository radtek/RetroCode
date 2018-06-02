
// class CMyCommandLineInfo
#include "stdafx.h"
#include "CMyCommandLineInfo.h"

CMyCommandLineInfo::CMyCommandLineInfo()
{
}

CMyCommandLineInfo::~CMyCommandLineInfo()
{
}

void CMyCommandLineInfo::ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast )
{
	CString str = lpszParam;
	SECFileSystem fp;
	if(!str.IsEmpty() && fp.FileExists(str))
		m_straFiles.Add(str);
}

