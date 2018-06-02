#pragma once

class CMySortArray
{
public:
	CMySortArray(void);
	~CMySortArray(void);
	void QuickSortEntries(int nLower, int nUpper);
	int PartitionEntries(int nLower, int nUpper);

	// sort on xml 1 or 2 tag
	CString m_strCurrentXMLTag;
	// XML string tag to sort on
	CString m_strXMLSortParam;
	// 2nd XML string tag to sort on
	CString m_strXMLSortParam2;
	// array of items to sort
	CStringArray* m_pstraEntries;
	// do sort
	void Sort(void);
};
