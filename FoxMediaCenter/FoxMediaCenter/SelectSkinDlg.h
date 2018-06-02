#if !defined(AFX_SELECTSKINDLG_H__C5C713AD_6129_42D3_96FB_CF35510FF4A0__INCLUDED_)
#define AFX_SELECTSKINDLG_H__C5C713AD_6129_42D3_96FB_CF35510FF4A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectSkinDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectSkinDlg dialog

class CSelectSkinDlg : public CDialog
{
// Construction
public:
	void LoadImage(CString strPath);
	CString GetPreviewImagePath(CString strSkin);
	SECJpeg* m_pImage;
	CStringArray* GetListOfSkins();
	
	CSelectSkinDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectSkinDlg();

// Dialog Data
	//{{AFX_DATA(CSelectSkinDlg)
	enum { IDD = IDD_SELECT_SKIN };
	CMyBitMapButton	m_ctlOK;
	CMyBitMapButton	m_ctlCancel;
	CComboBox	m_ctlSkinCombo;
	CString	m_strNewSkin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectSkinDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectSkinDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeSelectSkin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTSKINDLG_H__C5C713AD_6129_42D3_96FB_CF35510FF4A0__INCLUDED_)
