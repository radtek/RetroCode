////////////////////////////////////////////////////////////////
// MSDN Magazine -- October 2001
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0 for Windows 98 and probably Windows 2000 too.
// Set tabsize = 3 in your editor.
//
#pragma once
//#include <atlimage.h>

//////////////////
// Picture object--encapsulates IPicture
//
class CPicture {
public:
	CPicture();
	~CPicture();

	// Load frm various sosurces
	BOOL Load(UINT nIDRes);
	BOOL Load(LPCTSTR pszPathName);
	BOOL Load(IStream* pstm);
	BOOL Load(CFile& file);
	BOOL Load(CArchive& ar);

	// render to device context
	BOOL Render(CDC* pDC, CRect rc=CRect(0,0,0,0),
		LPCRECT prcMFBounds=NULL) const;

	CSize GetImageSize(CDC* pDC=NULL) const;
	
protected:
//	CImage m_Image;
};
