#pragma once


// CMyPrintListCtrl

class CMyPrintListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMyPrintListCtrl)

public:
	CMyPrintListCtrl();
	virtual ~CMyPrintListCtrl();

protected:
	

	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


