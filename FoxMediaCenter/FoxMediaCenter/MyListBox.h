#if !defined(AFX_MYLISTBOX_H__EE0BD2E4_C813_4E35_9E54_CA079CA4126A__INCLUDED_)
#define AFX_MYLISTBOX_H__EE0BD2E4_C813_4E35_9E54_CA079CA4126A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListBox window

class CMyListBox : public CListBox
{
// Construction
public:
	CMyListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListBox)
	afx_msg int VKeyToItem(UINT nKey, UINT nIndex);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTBOX_H__EE0BD2E4_C813_4E35_9E54_CA079CA4126A__INCLUDED_)
