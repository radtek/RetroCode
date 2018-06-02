// ZipCollections.cpp: 
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
#include "ZipCollections.h"


//************************* CZipWordArray ****************************


int CZipWordArray::CompareAsc(const void *pArg1, const void *pArg2)
{
	WORD w1 = *(WORD*)pArg1;
	WORD w2 = *(WORD*)pArg2;
	return w1 == w2 ? 0 :(w1 < w2 ? - 1 : 1);
}

int CZipWordArray::CompareDesc(const void *pArg1, const void *pArg2)
{
	WORD w1 = *(WORD*)pArg1;
	WORD w2 = *(WORD*)pArg2;
	return w1 == w2 ? 0 :(w1 > w2 ? - 1 : 1);
}

void CZipWordArray::Sort(bool bAscending)
{
	qsort((void*)&((*this)[0]), GetSize(), sizeof(WORD), bAscending ? CompareAsc : CompareDesc);	
}
