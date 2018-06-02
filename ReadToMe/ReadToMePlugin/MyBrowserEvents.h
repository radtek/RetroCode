// MyBrowserEvents.h : Declaration of the CMyBrowserEvents

#pragma once
#include "resource.h"       // main symbols


// IMyBrowserEvents
[
	object,
	uuid("F06319D4-C694-4E50-8AEB-45CDACDA37A4"),
	dual,	helpstring("IMyBrowserEvents Interface"),
	pointer_default(unique)
]
__interface IMyBrowserEvents : IDispatch
{
};



// CMyBrowserEvents

[
	coclass,
	threading("single"),
	vi_progid("ReadToMePlugin.MyBrowserEvents"),
	progid("ReadToMePlugin.MyBrowserEvents.1"),
	version(1.0),
	uuid("51A96B6A-8D5E-4BA3-953C-4FE6EEC0EF65"),
	helpstring("MyBrowserEvents Class")
]
class ATL_NO_VTABLE CMyBrowserEvents : 
	public IObjectWithSiteImpl<CMyBrowserEvents>,
	public IMyBrowserEvents
{
public:
	CMyBrowserEvents()
	{
	}


	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

};

