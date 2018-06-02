////////////////////////////////////////////////////////////////
// MSDN Magazine -- October 2001
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0 for Windows 98 and probably Windows 2000 too.
// Set tabsize = 3 in your editor.
//
#include "StdAfx.h"
#include "Picture.h"
#include "AFXPRIV2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////
// CPicture implementation
//

CPicture::CPicture()
{
}

CPicture::~CPicture()
{
}

//////////////////
// Load from resource. Looks for "IMAGE" type.
//
BOOL CPicture::Load(UINT nIDRes)
{
	// find resource in resource file
	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hRsrc = ::FindResource(hInst,	MAKEINTRESOURCE(nIDRes),"jpeg"); // type
	if (!hRsrc)
		return FALSE;

	// load resource into memory
	DWORD len = SizeofResource(hInst, hRsrc);
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
	if (!lpRsrc)
		return FALSE;

	// create memory file and load it
	CMemFile file(lpRsrc, len);
	BOOL bRet = Load(file);
	FreeResource(hRsrc);

	return bRet;
}

//////////////////
// Load from path name.
//
BOOL CPicture::Load(LPCTSTR pszPathName)
{
	CFile file;
	if (!file.Open(pszPathName, CFile::modeRead|CFile::shareDenyWrite))
		return FALSE;
	BOOL bRet = Load(file);
	file.Close();
	return bRet;
}

//////////////////
// Load from CFile
//
BOOL CPicture::Load(CFile& file)
{
	CArchive ar(&file, CArchive::load | CArchive::bNoFlushOnDelete);
	return Load(ar);
}

//////////////////
// Load from archive--create stream and load from stream.
//
BOOL CPicture::Load(CArchive& ar)
{
	CArchiveStream arcstream(&ar);
	return Load((IStream*)&arcstream);
}

//////////////////
// Load from stream (IStream). This is the one that really does it: call
// OleLoadPicture to do the work.
//
BOOL CPicture::Load(IStream* pstm)
{
	//HRESULT hr = m_Image.Load(pstm);
	return TRUE;
}

//////////////////
// Render to device context. Covert to HIMETRIC for IPicture.
//
BOOL CPicture::Render(CDC* pDC, CRect rc, LPCRECT prcMFBounds) const
{
	ASSERT(pDC);

	// rect
	if (rc.IsRectNull()) 
	{
		CSize sz = GetImageSize(pDC);
		rc.right = sz.cx;
		rc.bottom = sz.cy;
	}
	//m_Image.BitBlt(pDC->m_hDC,rc,CPoint(0,0));

	return TRUE;
}

CSize CPicture::GetImageSize(CDC* pDC) const
{
	//CSize size(m_Image.GetWidth(),m_Image.GetHeight());
	CSize size(1,1);
	return size;	
}

