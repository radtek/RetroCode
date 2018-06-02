#include "StdAfx.h"
#include ".\customprint.h"
#include "FOX Password Safe.h"

CCustomPrint::CCustomPrint(void)
{
	m_pCtrlWnd = NULL;

	m_PrintDatabasePassword = true;
	m_bCategory = true;
	m_bDescription = true;
	m_bPrintUserID = true;
	m_bPrintPass = true;
	m_bPrintURL = true;
	m_bPrintNotes = false;

	m_strAppName = "FOX Password Safe";
	m_strDocName = CTime::GetCurrentTime().Format("%x");
	
	CFOXPasswordSafeApp* pApp = (CFOXPasswordSafeApp*)AfxGetApp();
	pApp->SetPortraitPrintMode();
}

CCustomPrint::~CCustomPrint(void)
{
	ClearArray();
}

BOOL CCustomPrint::OnPreparePrinting(CPrintInfo* pInfo)
{
	UNUSED_ALWAYS(pInfo);
	m_rectPaper  = CRect(0,0,0,0);
	m_rectPage   = CRect(0,0,0,0);
	m_rectHeader = CRect(0,0,0,0);
	m_rectFooter = CRect(0,0,0,0);
	m_rectBody   = CRect(0,0,0,0);
	m_pFontHeader = NULL;
	m_pFontFooter = NULL;
	m_pFontColumn = NULL;
	m_pFontBody   = NULL;
	m_CharSizeHeader = CSize(0,0);
	m_CharSizeFooter = CSize(0,0);
	m_CharSizeBody   = CSize(0,0);
	m_marginLeft   = MARGIN_LEFT;
	m_marginTop    = MARGIN_TOP;
	m_marginRight  = MARGIN_RIGHT;
	m_marginBottom = MARGIN_BOTTOM;
	m_headerHeight = 0;
	m_footerHeight = 0;
	m_headerLines = HEADER_LINES;
	m_footerLines = FOOTER_LINES;
	m_nPageCols = 0;
	m_nPageRows = 0;
	m_nPageCount = 0;
	m_nRowCount = 0;

	return TRUE;
}

void CCustomPrint::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{   
	// Create fonts
	ASSERT(pDC != NULL && pInfo != NULL);
	m_pFontHeader = CreateFont(pDC,_T("Arial"), 12, FW_BOLD);
	m_pFontFooter = CreateFont(pDC,_T("Arial"), 10);
	m_pFontColumn = CreateFont(pDC,_T("Arial"), 9, FW_BOLD);
	m_pFontBody   = CreateFont(pDC,_T("Times New Roman"), 10);

	// Calculate character size
	m_CharSizeHeader = GetCharSize(pDC, m_pFontHeader);
	m_CharSizeFooter = GetCharSize(pDC, m_pFontFooter);
	m_CharSizeBody   = GetCharSize(pDC, m_pFontBody);

	// Prepare layout 
	m_rectPaper  = GetPaperRect(pDC);
	m_rectPage   = GetPageRect();
	m_rectHeader = GetHeaderRect();
	m_rectFooter = GetFooterRect();
	m_rectBody = GetBodyRect();

	m_nRowCount = GetRowCount();
	m_nPageCols = GetPageColumns();
	m_nPageRows = GetPageRows();
	m_nPageCount = (m_nRowCount + m_nPageRows - 1) / m_nPageRows;	

	// How many pages?
	pInfo->SetMaxPage(m_nPageCount);   
}

void CCustomPrint::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	PrintHeader(pDC, pInfo);
	PrintBody(pDC, pInfo);
	PrintFooter(pDC, pInfo);
}

void CCustomPrint::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
   delete m_pFontHeader;
   delete m_pFontFooter;
   delete m_pFontColumn;
   delete m_pFontBody;

   if(!pInfo->m_bPreview)
   {
		ClearArray();
   }
}

void CCustomPrint::DrawRow(CDC* pDC, int nRow)
{
	for (int nCol = 0; nCol < m_nPageCols; nCol++)
	{
		CRect rect = GetCellRect(nRow,nCol);
		CString strText = GetTextForRow(nRow, nCol);
		DrawText(pDC->m_hDC, strText, -1, rect, DT_LEFT | DT_VCENTER);
	}
}

CRect CCustomPrint::GetPaperRect(CDC* pDC)
{
   ASSERT(pDC != NULL);
   CSize paperSize = CSize(pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES));
   return CRect(0, 0, paperSize.cx, paperSize.cy);
}

CRect CCustomPrint::GetPageRect()
{
   ASSERT(m_rectPaper != CRect(0,0,0,0));
   CRect rect = m_rectPaper;
   rect.DeflateRect(m_marginLeft, m_marginTop, m_marginRight, m_marginBottom);
   return rect;
}

CRect CCustomPrint::GetHeaderRect()
{
   ASSERT(m_rectPage != CRect(0,0,0,0));
   CRect rect = m_rectPage;
   CSize charSize = m_CharSizeHeader;
   rect.DeflateRect(0, 0, 0, rect.Height() - m_headerLines * charSize.cy);
   return rect;
}

CRect CCustomPrint::GetFooterRect()
{
   ASSERT(m_rectPage != CRect(0,0,0,0));
   CRect rect = m_rectPage;
   CSize charSize = m_CharSizeFooter;
   rect.DeflateRect(0, rect.Height() - m_footerLines * charSize.cy, 0, 0);
   return rect;
}

CRect CCustomPrint::GetBodyRect()
{
   ASSERT(m_rectPage != CRect(0,0,0,0));
   ASSERT(m_rectHeader != CRect(0,0,0,0));
   ASSERT(m_rectFooter != CRect(0,0,0,0));
   CRect rectPage = m_rectPage;
   CRect rectHead = m_rectHeader;
   CRect rectFoot = m_rectFooter;
   rectPage.DeflateRect(0, rectHead.Height(), 0, rectFoot.Height());
   return rectPage;
}

CSize CCustomPrint::GetCharSize(CDC* pDC, CFont* pFont)
{
   ASSERT(pDC != NULL && pFont != NULL);
   CFont *pOldFont = pDC->SelectObject(pFont);
   CSize charSize = pDC->GetTextExtent(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSATUVWXYZ"),52);
   charSize.cx /= 52;
   pDC->SelectObject(pOldFont);
   return charSize;
}

int CCustomPrint::GetPageColumns()
{
	int nCol = 0;
	if(m_bCategory)
		nCol++;
	if(m_bDescription)
		nCol++;
	if(m_bPrintUserID)
		nCol++;
	if(m_bPrintPass)
		nCol++;
	if(m_bPrintURL)
		nCol++;
	if(m_bPrintNotes)
		nCol++;
	return nCol;
}

CString CCustomPrint::GetColumnHeading(int col)
{
	CStringArray straTemp;
	if(m_bCategory)
		straTemp.Add("Category");
	if(m_bDescription)
		straTemp.Add("Description");
	if(m_bPrintUserID)
		straTemp.Add("Username");
	if(m_bPrintPass)
		straTemp.Add("Password");
	if(m_bPrintURL)
		straTemp.Add("Web Site");
	if(m_bPrintNotes)
		straTemp.Add("Notes");
	if(col >=0 && col < straTemp.GetSize())
		return straTemp.GetAt(col);
	else
		return "";
}

CFont* CCustomPrint::CreateFont(CDC* pDC, CString strName, int nPoints, int lfWeight, bool lfItalic)
{
	ASSERT(pDC && m_pCtrlWnd);   
	CDC* pCurrentDC = m_pCtrlWnd->GetDC();
	LOGFONT lf; 
	ZeroMemory(&lf,sizeof(LOGFONT));
	TEXTMETRIC tm;
	CFont* pCurrentFont = m_pCtrlWnd->GetFont();
	if(pCurrentFont)
		pCurrentFont->GetLogFont(&lf);
	pCurrentDC->GetTextMetrics(&tm);
	CFont* pFont = new CFont();
	CSize PaperPixelsPerInch(pDC->GetDeviceCaps(LOGPIXELSX),pDC->GetDeviceCaps(LOGPIXELSY));
	CSize ScreenPixelsPerInch(pCurrentDC->GetDeviceCaps(LOGPIXELSX),pCurrentDC->GetDeviceCaps(LOGPIXELSY));
	if (nPoints == 0)
		nPoints = MulDiv((tm.tmHeight - tm.tmInternalLeading),72,ScreenPixelsPerInch.cy);
	lf.lfWeight = lfWeight;
	lf.lfItalic = lfItalic;
	lf.lfHeight = -MulDiv(nPoints,PaperPixelsPerInch.cy,72);  
	if (!strName.IsEmpty())
		_tcscpy(lf.lfFaceName, strName);  
	m_pCtrlWnd->ReleaseDC(pCurrentDC);
	BOOL bResult = pFont->CreateFontIndirect(&lf);
	ASSERT(bResult == TRUE);
	return pFont;
}

void CCustomPrint::PrintHeader(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT(m_pFontHeader && pInfo);
	UNUSED_ALWAYS(pInfo);
	CFont *pOldFont = pDC->SelectObject(m_pFontHeader);

	// Create black brush
	CBrush brush;
	brush.CreateSolidBrush(RGB(0,0,0));
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	// Draw line
	CRect rectLine = m_rectHeader;
	rectLine.top = rectLine.top + m_CharSizeHeader.cy * 3 / 2;
	rectLine.bottom = rectLine.top + HEADER_LINE_SIZE;
	pDC->FillRect(&rectLine, &brush);
	pDC->SelectObject(pOldBrush);

	// Draw "Program" and "Document"
	CRect rectHeader = m_rectHeader;
	rectHeader.bottom = rectHeader.top + m_CharSizeHeader.cy;
	pDC->DrawText(m_strAppName, rectHeader, DT_LEFT | DT_BOTTOM);
	pDC->DrawText(m_strDocName, rectHeader, DT_RIGHT | DT_BOTTOM);   
	pDC->SelectObject(pOldFont);
}

void CCustomPrint::PrintBody(CDC* pDC, CPrintInfo* pInfo)
{
   ASSERT(m_pFontBody && m_pFontColumn && pInfo);

   // Print column headings
   CFont *pOldFont = pDC->SelectObject(m_pFontColumn); 
   for (int i = 0; i < m_nPageCols; i++)
      DrawText(pDC->m_hDC, GetColumnHeading(i), -1, GetColumnRect(i), DT_LEFT | DT_VCENTER);

   // Start and end row
   pDC->SelectObject(m_pFontBody);
   int nStartRow = (pInfo->m_nCurPage - 1) * m_nPageRows;
   int nEndRow = nStartRow + m_nPageRows;
   if(nEndRow > m_nRowCount)       
      nEndRow = m_nRowCount;

   // Prepare document and print rows
   for (int i=nStartRow; i < nEndRow; i++)
      DrawRow(pDC, i);
   pDC->SelectObject(pOldFont);
}

void CCustomPrint::PrintFooter(CDC* pDC, CPrintInfo* pInfo)
{
   ASSERT(m_pFontFooter != NULL && pInfo != NULL);
   CFont *pOldFont = pDC->SelectObject(m_pFontFooter);

   // Create black brush
   CBrush brush;
   brush.CreateSolidBrush(RGB(0,0,0));
   CBrush* pOldBrush = pDC->SelectObject(&brush);

   // Draw line
   CRect rectLine = m_rectFooter;
   rectLine.top = rectLine.top + m_CharSizeHeader.cy * 1 / 2;
   rectLine.bottom = rectLine.top + HEADER_LINE_SIZE;
   pDC->FillRect(&rectLine, &brush);
   pDC->SelectObject(pOldBrush);

   // Draw "Pages"
   CString strPages;
   strPages.Format(_T("Page %d of %d"),pInfo->m_nCurPage, m_nPageCount);
   CRect rectPage = m_rectFooter;
   rectPage.top = rectPage.bottom - m_CharSizeFooter.cy;
   pDC->DrawText(strPages, rectPage, DT_RIGHT | DT_BOTTOM);
   pDC->SelectObject(pOldFont);
}

void CCustomPrint::SetAppName(const CString& strName)
{
   m_strAppName = strName;
}

void CCustomPrint::SetDocTitle(const CString &strName)
{
   m_strDocName = strName;
}

// return text for the desired position
CString CCustomPrint::GetTextForRow(int nRow, int nCol)
{
	CString strReturn;
	if(nRow >= 0 && nRow<m_2DstraRows.GetSize() && nCol>= 0 && nCol<CUSTOM_PRINT_ARRAY_COLUMN_SIZE)
	{
		strReturn = m_2DstraRows.GetAt(nRow)->straCol[nCol];
	}
	return strReturn;
}

// clear multi dimensional array of item entries
void CCustomPrint::ClearArray(void)
{
	for(int n=0;n<m_2DstraRows.GetSize();n++)
	{
		C2DString* pStruct = (C2DString*)m_2DstraRows.GetAt(n);
		delete pStruct;
	}
	m_2DstraRows.RemoveAll();
}

// loop through entries and work out largest column size in chars
void CCustomPrint::SetLargestColumnSize(void)
{
	for(int n=0;n<CUSTOM_PRINT_ARRAY_COLUMN_SIZE;n++)
	{
		m_nMaxTextSize[n] = GetColumnHeading(n).GetLength();
		m_nMaxTextIsHeader[n] = true;
		for(int i=0;i<m_2DstraRows.GetSize();i++)
		{
			C2DString* pStruct = (C2DString*)m_2DstraRows.GetAt(i);
			int nSize = pStruct->straCol[n].GetLength();
			if(nSize > m_nMaxTextSize[n])
			{
				m_nMaxTextSize[n] = nSize;
				m_nMaxTextIsHeader[n] = false;
			}
		}
	}	
}

int CCustomPrint::GetPageRows()
{
   CSize charSize = m_CharSizeBody;
   if(charSize.cy == 0)
	   charSize.cy = 57;
   CRect rectBody = m_rectBody;
   CRect rectCol = GetColumnRect(0);
   return (rectBody.Height() - rectCol.Height()) / charSize.cy;
}

int CCustomPrint::GetColumnWidth(int col)
{
	int nChars = m_nMaxTextSize[col];
	if(m_nMaxTextIsHeader[col])
		return (int)(nChars * m_CharSizeHeader.cx);
	else
		return (int)(nChars * m_CharSizeBody.cx);
}

double CCustomPrint::GetTextRatioX(CDC* pDC)
{
   ASSERT(m_pCtrlWnd);
   CDC* pCurrentDC = m_pCtrlWnd->GetDC();
   TEXTMETRIC tmSrc;
   pCurrentDC->GetTextMetrics(&tmSrc);
   m_pCtrlWnd->ReleaseDC(pCurrentDC);
   return ((double)m_CharSizeBody.cx) / ((double)tmSrc.tmAveCharWidth);
}

int CCustomPrint::GetRowCount()
{
   return (int)m_2DstraRows.GetSize();
}

CRect CCustomPrint::GetColumnRect(int nCol)
{
	CSize charSize = m_CharSizeBody;
	CRect rectBody = m_rectBody;
	int nLeft = 0;
	int i=0;
	for (i=0; i < nCol; i++) 
		nLeft += GetColumnWidth(i);
	int nRight = nLeft + GetColumnWidth(i);
	CRect rect(rectBody.left + nLeft,rectBody.top,rectBody.left + nRight,rectBody.top + charSize.cy);
	rect.left += (int)(CELL_PADDING*nCol);
	rect.right += (int)(CELL_PADDING*nCol);
	if (rect.right > rectBody.right)
		rect.right = rectBody.right;
	return rect;
}

CRect CCustomPrint::GetCellRect(int nRow, int nCol)
{
	CSize charSize = m_CharSizeBody;
	CRect rectBody = m_rectBody;
	CRect rectCol = GetColumnRect(nCol);
	int nLeft = 0;
	int i=0;
	for (i=0, i=0; i < nCol; i++) 
		nLeft += GetColumnWidth(i);
	int nRight = nLeft + GetColumnWidth(i);   
	int nPageRow =  nRow % m_nPageRows;

	CRect rect(rectBody.left + nLeft,rectBody.top + rectCol.Height() + charSize.cy * nPageRow, 
		rectBody.left + nRight,rectBody.top + rectCol.Height() + charSize.cy * (nPageRow + 1));
	rect.left += (int)(CELL_PADDING*nCol);
	rect.right += (int)(CELL_PADDING*nCol);
	if (rect.right > rectBody.right)
		rect.right = rectBody.right;
	return rect;
}