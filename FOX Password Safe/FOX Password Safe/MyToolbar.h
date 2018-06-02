#pragma once

#include "MyBmButton.h"

// CMyToolbar

class CMyToolbar : public CWnd
{
	DECLARE_DYNAMIC(CMyToolbar)

public:
	CMyToolbar();
	virtual ~CMyToolbar();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	// show toolbar for particular view
	void ShowToolBar(TOOLBAR_TYPES eToolbar);

	// open
	CMyBmButton m_buttonOpen;
	CBitmap		m_bmOpen1;
	CBitmap		m_bmOpen2;
	// new 
	CMyBmButton m_buttonNew;
	CBitmap		m_bmNew1;
	CBitmap		m_bmNew2;
	// edit 
	CMyBmButton m_buttonEdit;
	CBitmap		m_bmEdit1;
	CBitmap		m_bmEdit2;
	// delete 
	CMyBmButton m_buttonDelete;
	CBitmap		m_bmDelete1;
	CBitmap		m_bmDelete2;
	// Copy username 
	CMyBmButton m_buttonCopyUser;
	CBitmap		m_bmCopyUser1;
	CBitmap		m_bmCopyUser2;
	// Copy password 
	CMyBmButton m_buttonCopyPassword;
	CBitmap		m_bmCopyPassword1;
	CBitmap		m_bmCopyPassword2;
	// Empty clipboard 
	CMyBmButton m_buttonEmptyClip;
	CBitmap		m_bmEmptyClip1;
	CBitmap		m_bmEmptyClip2;
	// print 
	CMyBmButton m_buttonPrint;
	CBitmap		m_bmPrint1;
	CBitmap		m_bmPrint2;
	// load website 
	CMyBmButton m_buttonLoadSite;
	CBitmap		m_bmLoadSite1;
	CBitmap		m_bmLoadSite2;
	// Show details 
	CMyBmButton m_buttonShowDetails;
	CBitmap		m_bmShowDetails1;
	CBitmap		m_bmShowDetails2;
	// search 
	CMyBmButton m_buttonSearch;
	CBitmap		m_bmSearch1;
	CBitmap		m_bmSearch2;
	// encrypt any unencrypted files 
	CMyBmButton m_buttonEncryptFiles;
	CBitmap		m_bmEncryptFiles1;
	CBitmap		m_bmEncryptFiles2;
	// load file 
	CMyBmButton m_buttonLoadFile;
	CBitmap		m_bmLoadFile1;
	CBitmap		m_bmLoadFile2;

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};


