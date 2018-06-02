#if !defined(AFX_STEVEMEDIAPLAYERPPG_H__09F1F557_4E22_4629_9A7D_1B0FE63D5350__INCLUDED_)
#define AFX_STEVEMEDIAPLAYERPPG_H__09F1F557_4E22_4629_9A7D_1B0FE63D5350__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SteveMediaPlayerPpg.h : Declaration of the CSteveMediaPlayerPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CSteveMediaPlayerPropPage : See SteveMediaPlayerPpg.cpp.cpp for implementation.

class CSteveMediaPlayerPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CSteveMediaPlayerPropPage)
	DECLARE_OLECREATE_EX(CSteveMediaPlayerPropPage)

// Constructor
public:
	CSteveMediaPlayerPropPage();

// Dialog Data
	//{{AFX_DATA(CSteveMediaPlayerPropPage)
	enum { IDD = IDD_PROPPAGE_STEVEMEDIAPLAYER };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CSteveMediaPlayerPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEVEMEDIAPLAYERPPG_H__09F1F557_4E22_4629_9A7D_1B0FE63D5350__INCLUDED)
