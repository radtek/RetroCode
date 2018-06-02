// ZipCollections.h: various platform-dependent definitions to try to make
//   sanity of cross platform datatyping.
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

#ifndef ZIPCOLLECTIONS_DOT_H
#define ZIPCOLLECTIONS_DOT_H

#include <afxtempl.h>
typedef CStringArray CZipStringArray;
struct CZipFindFast;
typedef CArray<CZipFindFast, CZipFindFast> CZipFindFastArray;

class CZipWordArray : public CWordArray
{
protected:
	static int CompareAsc(const void *pArg1, const void *pArg2);
	static int CompareDesc(const void *pArg1, const void *pArg2);
public:
	void Sort(bool bAscending);	
};

template<class TYPE>
class CZipPtrList : public CTypedPtrList<CPtrList, TYPE>
{
public:
	typedef POSITION iterator;
	bool IteratorValid(const iterator &iter)
	{
		return iter != NULL;
	}
};



#endif  /* ZIPCOLLECTIONS_DOT_H */