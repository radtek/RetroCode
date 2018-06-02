
// helpers

#include "stdafx.h"
#include "helpers.h"

BOOL IsRegCodeGood(CString strReg)
{
	// 28320405-7FEB-41a1-EC2U-24E137B536E4

	// first sect, last 2 number add to 5
	// 2nd last sect, 1st and 4rd digit are vowels A E I O U
	// last sect, first and last number add to 6

	if(strReg.IsEmpty())
		return FALSE;

	// 1st sect
	int nFind = strReg.Find('-');
	if(nFind == -1)
		return false;
	CString strTest = strReg.Left(nFind);
	int nNum = atoi(CString(strTest.GetAt(strTest.GetLength()-1)));
	nNum += atoi(CString(strTest.GetAt(strTest.GetLength()-2)));
	if(nNum != 5)
		return FALSE;
	
	// 2nd sect
	strTest = strReg.Left(strReg.ReverseFind('-'));
	strTest = strTest.Mid(strTest.ReverseFind('-')+1);
	strTest.MakeUpper();	
	char ch = strTest.GetAt(0);
	if(ch != 'A' && ch != 'E' && ch != 'I' && ch != 'O' && ch != 'U')
		return FALSE;
	ch = strTest.GetAt(3);
	if(ch != 'A' && ch != 'E' && ch != 'I' && ch != 'O' && ch != 'U')
		return FALSE;

	// last sect
	strTest = strReg.Mid(strReg.ReverseFind('-')+1);
	nNum = atoi(CString(strTest.GetAt(0)));
	nNum += atoi(CString(strTest.GetAt(strTest.GetLength()-1)));
	if(nNum != 6)
		return FALSE;

	return TRUE;
}

CString CreateGUID()
{
	CString strNewNum;
	GUID guid;
	ZeroMemory(&guid,sizeof(GUID));
	HRESULT hr = CoCreateGuid(&guid);

	// format GUID
	WCHAR        wszGuid[40]; 
	StringFromGUID2(guid, wszGuid, sizeof(wszGuid) / sizeof(WCHAR)); 
	wcstombs(strNewNum.GetBuffer(MAX_PATH), wszGuid,MAX_PATH);
	strNewNum.ReleaseBuffer();
	strNewNum.TrimLeft("{");
	strNewNum.TrimRight("}");

	return strNewNum;
}