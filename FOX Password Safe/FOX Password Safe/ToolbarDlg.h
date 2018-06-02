#pragma once


// CToolbarDlg dialog

class CToolbarDlg : public CDialog
{
	DECLARE_DYNAMIC(CToolbarDlg)

public:
	CToolbarDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CToolbarDlg();

// Dialog Data
	enum { IDD = IDD_TOOLBAR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
