#include "StdAfx.h"
#include ".\mysortarray.h"
#include ".\helpers.h"

CMySortArray::CMySortArray(void)
: m_strXMLSortParam(_T(""))
{
}

CMySortArray::~CMySortArray(void)
{
}

// do sort
void CMySortArray::Sort(void)
{
	if(m_pstraEntries->GetCount() == 0)
		return;
	
	// sort on first XML tag
	m_strCurrentXMLTag = m_strXMLSortParam;
	QuickSortEntries(0,(int)m_pstraEntries->GetSize() - 1);

	// sort on second XML tag
	if(!m_strXMLSortParam2.IsEmpty())
	{
		CStringArray* pArrayXML1 = m_pstraEntries;
		m_strCurrentXMLTag = m_strXMLSortParam2;

		CStringArray straTemp;
		CString strPreXML1;
		CString strXML1;
		int nStartPos = 0;
		for(int n=0;n<pArrayXML1->GetSize();n++)
		{
			strXML1 = ParseXML(m_strXMLSortParam,pArrayXML1->GetAt(n));
			// add items to temp array if same as previous item in XML 1 param
			if(strPreXML1.CompareNoCase(strXML1) == 0)
			{
				straTemp.Add(pArrayXML1->GetAt(n));
			}
			else
			{
				// sort these items
				if(straTemp.GetSize() > 1)
				{
					// swap pointer to temp array for sort
					m_pstraEntries = &straTemp;
					QuickSortEntries(0,(int)straTemp.GetSize() - 1);
					for(int x=0;x<straTemp.GetSize();x++)
						pArrayXML1->SetAt(x+nStartPos,straTemp.GetAt(x));
				}
				straTemp.RemoveAll();
				nStartPos = n;
				strPreXML1 = strXML1;
				straTemp.Add(pArrayXML1->GetAt(n));
			}
		}
		// sort last category if more than 1 item
		if(straTemp.GetSize() > 1)
		{
			// swap pointer to temp array for sort
			m_pstraEntries = &straTemp;
			QuickSortEntries(0,(int)straTemp.GetSize() - 1);
			for(int x=0;x<straTemp.GetSize();x++)
				pArrayXML1->SetAt(x+nStartPos,straTemp.GetAt(x));
		}
		m_pstraEntries = pArrayXML1;
	} 
}

// QuickSort implementation for Entries
void CMySortArray::QuickSortEntries(int nLower, int nUpper)
{
    // Check for non-base case
    if (nLower < nUpper)
    {
        // Split and sort partitions
        int nSplit = PartitionEntries (nLower, nUpper);
        QuickSortEntries (nLower, nSplit - 1);
        QuickSortEntries (nSplit + 1, nUpper);
    }
}

// QuickSort partition implementation for Entries
int CMySortArray::PartitionEntries(int nLower, int nUpper)
{
    // Pivot with first element
    int nLeft = nLower + 1;
    CString szPivot = m_pstraEntries->GetAt(nLower);
    int nRight = nUpper;
    // Partition array elements
    CString szSwap;
    while (nLeft <= nRight)
    {
        // Find item out of place
        while(nLeft <= nRight && (ParseXML(m_strCurrentXMLTag,m_pstraEntries->GetAt(nLeft)).CompareNoCase(ParseXML(m_strCurrentXMLTag,szPivot)) <= 0))
			nLeft = nLeft + 1;
        while (nLeft <= nRight && (ParseXML(m_strCurrentXMLTag,m_pstraEntries->GetAt(nRight)).CompareNoCase(ParseXML(m_strCurrentXMLTag,szPivot)) > 0))
            nRight = nRight - 1;
        // Swap values if necessary
        if (nLeft < nRight)
        {
            szSwap = m_pstraEntries->GetAt(nLeft);
            m_pstraEntries->SetAt(nLeft, m_pstraEntries->GetAt(nRight));
            m_pstraEntries->SetAt(nRight, szSwap);
            nLeft = nLeft + 1;
            nRight = nRight - 1;
        }
    }
    // Move pivot element
    szSwap = m_pstraEntries->GetAt(nLower);
    m_pstraEntries->SetAt(nLower, m_pstraEntries->GetAt(nRight));
    m_pstraEntries->SetAt(nRight, szSwap);
    return nRight;
}

