#if !defined(AFX_MYREALAUDIOCOM_H__E941987E_0319_4B1A_90B4_1383FC026CC0__INCLUDED_)
#define AFX_MYREALAUDIOCOM_H__E941987E_0319_4B1A_90B4_1383FC026CC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyRealAudioCom.h : header file
//
#define INITGUID     /* Interface ID's */

#include "RealSDK\\pntypes.h"
#include "RealSDK\\pnwintyp.h"
#include "RealSDK\\pncom.h"
#include "RealSDK\\rmapckts.h"
#include "RealSDK\\rmacomm.h"
#include "RealSDK\\rmamon.h"
#include "RealSDK\\rmafiles.h"
#include "RealSDK\\rmaengin.h"
#include "RealSDK\\rmacore.h"
#include "RealSDK\\rmaclsnk.h"
#include "RealSDK\\rmaerror.h"
#include "RealSDK\\rmaauth.h"
#include "RealSDK\\rmawin.h"

#include "RealSDK\\os.h"
#include "RealSDK\\fivemmap.h"
#include "RealSDK\\exadvsnk.h"
#include "RealSDK\\exerror.h"
#include "RealSDK\\exsitsup.h"
#include "RealSDK\\exaumgr.h"
#include "RealSDK\\excontxt.h"

// XXXXXJEB: this should really be in rmacore.h
typedef PN_RESULT (PNEXPORT_PTR FPRMSETDLLACCESSPATH) (const char*);


/////////////////////////////////////////////////////////////////////////////
// CMyRealAudioCom window

class CMyRealAudioCom : public CWnd
{
// Construction
public:
	CMyRealAudioCom();

// Attributes
public:
	FPRMCREATEENGINE	m_fpCreateEngine;
	FPRMCLOSEENGINE	 	m_fpCloseEngine;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyRealAudioCom)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyRealAudioCom();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyRealAudioCom)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYREALAUDIOCOM_H__E941987E_0319_4B1A_90B4_1383FC026CC0__INCLUDED_)






