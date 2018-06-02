#if !defined(AFX_STEVEMEDIACENTEROCXPPG_H__42BAA921_5C56_49C9_A96D_F21FD870C294__INCLUDED_)
#define AFX_STEVEMEDIACENTEROCXPPG_H__42BAA921_5C56_49C9_A96D_F21FD870C294__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SteveMediaCenterOcxPpg.h : Declaration of the CSteveMediaCenterOcxPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterOcxPropPage : See SteveMediaCenterOcxPpg.cpp.cpp for implementation.

class CSteveMediaCenterOcxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CSteveMediaCenterOcxPropPage)
	DECLARE_OLECREATE_EX(CSteveMediaCenterOcxPropPage)

// Constructor
public:
	CSteveMediaCenterOcxPropPage();

// Dialog Data
	//{{AFX_DATA(CSteveMediaCenterOcxPropPage)
	enum { IDD = IDD_PROPPAGE_STEVEMEDIACENTEROCX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CSteveMediaCenterOcxPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEVEMEDIACENTEROCXPPG_H__42BAA921_5C56_49C9_A96D_F21FD870C294__INCLUDED)
