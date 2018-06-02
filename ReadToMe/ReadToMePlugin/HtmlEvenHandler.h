// HtmlEvenHandler.h : Declaration of the CHtmlEvenHandler

#pragma once
#include "resource.h"       // main symbols
class CReadToMe;

// IHtmlEvenHandler
[
	object,
	uuid("D0F58ABF-0B8E-4888-B97F-27FA76FF7E44"),
	dual,	helpstring("IHtmlEvenHandler Interface"),
	pointer_default(unique)
]

__interface IHtmlEvenHandler : IDispatch
{
};

// CHtmlEvenHandler
[
	coclass,
	threading("apartment"),
	aggregatable("never"),
	vi_progid("ReadToMePlugin.HtmlEvenHandler"),
	progid("ReadToMePlugin.HtmlEvenHandler.1"),
	version(1.0),
	uuid("E6A7F2CD-F0DF-4C78-87E9-60516BCF6AFA"),
	helpstring("HtmlEvenHandler Class")
]

//class CReadToMe;
class ATL_NO_VTABLE CHtmlEvenHandler : public IDispatchImpl<IHtmlEvenHandler, &__uuidof(IHtmlEvenHandler)>
	
{
public:
	CHtmlEvenHandler();
	~CHtmlEvenHandler();

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
	HRESULT Init(IWebBrowser2* pBrowser);
	HRESULT Init(IHTMLDocument2* pDoc2);
	STDMETHOD(Invoke)(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*); 
    STDMETHOD(GetTypeInfoCount)(unsigned int*) { return E_NOTIMPL; } 
    STDMETHOD(GetTypeInfo)(unsigned int, LCID, ITypeInfo**) {return E_NOTIMPL;} 
    STDMETHOD(GetIDsOfNames)(REFIID, LPOLESTR*, UINT, LCID, DISPID*){ return E_NOTIMPL; } 
	HRESULT CleanUp();	

	CReadToMe* m_pParent;
	HRESULT m_hrConnected;
	DWORD m_dwCookie;
	DWORD m_dwCookie2;
	DWORD m_dwCookie3;
	LPCONNECTIONPOINT m_pCP;
	LPCONNECTIONPOINT m_pCP2;
	LPCONNECTIONPOINT m_pCP3;
	DWORD m_dwRef;
	int m_cRef;

	friend class CReadToMe;
};

