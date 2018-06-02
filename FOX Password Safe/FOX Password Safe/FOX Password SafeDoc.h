// FOX Password SafeDoc.h : interface of the CFOXPasswordSafeDoc class
//


#pragma once

class CFOXPasswordSafeDoc : public CDocument
{
protected: // create from serialization only
	CFOXPasswordSafeDoc();
	DECLARE_DYNCREATE(CFOXPasswordSafeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CFOXPasswordSafeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	// XML data on selected item
	CString m_strData;
public:
	// is header or selected data
	bool m_bIsHeader;

	friend class CFOXPasswordSafeView;
};


