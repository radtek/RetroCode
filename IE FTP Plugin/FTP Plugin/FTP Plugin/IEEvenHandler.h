#pragma once

class CIEFTPPlugin;

class ATL_NO_VTABLE  CIEEvenHandler : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IIEEventHandler,&__uuidof(IIEEventHandler)>
	
{
public:
	CIEEvenHandler(void);
	~CIEEvenHandler(void);

	BEGIN_COM_MAP(CIEEvenHandler)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

	HRESULT Init(IWebBrowser2* pBrowser);
	STDMETHOD(Invoke)(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*); 
    STDMETHOD(GetTypeInfoCount)(unsigned int*) { return E_NOTIMPL; } 
    STDMETHOD(GetTypeInfo)(unsigned int, LCID, ITypeInfo**) {return E_NOTIMPL;} 
    STDMETHOD(GetIDsOfNames)(REFIID, LPOLESTR*, UINT, LCID, DISPID*){ return E_NOTIMPL; } 
	HRESULT CleanUp();	

	CIEFTPPlugin* m_pParent;
	HRESULT m_hrConnected;
	DWORD m_dwCookie;
	LPCONNECTIONPOINT m_pCP;
	DWORD m_dwRef;
	int m_cRef;
};
