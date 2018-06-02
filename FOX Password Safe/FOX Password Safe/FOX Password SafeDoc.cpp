// FOX Password SafeDoc.cpp : implementation of the CFOXPasswordSafeDoc class
//

#include "stdafx.h"
#include "FOX Password Safe.h"

#include "FOX Password SafeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFOXPasswordSafeDoc

IMPLEMENT_DYNCREATE(CFOXPasswordSafeDoc, CDocument)

BEGIN_MESSAGE_MAP(CFOXPasswordSafeDoc, CDocument)
END_MESSAGE_MAP()


// CFOXPasswordSafeDoc construction/destruction

CFOXPasswordSafeDoc::CFOXPasswordSafeDoc()
: m_strData(_T(""))
, m_bIsHeader(false)
{
	// TODO: add one-time construction code here

}

CFOXPasswordSafeDoc::~CFOXPasswordSafeDoc()
{
}

BOOL CFOXPasswordSafeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

// CFOXPasswordSafeDoc serialization

void CFOXPasswordSafeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CFOXPasswordSafeDoc diagnostics

#ifdef _DEBUG
void CFOXPasswordSafeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFOXPasswordSafeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFOXPasswordSafeDoc commands
