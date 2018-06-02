// SteveMediaCenterOcx.cpp : Implementation of CSteveMediaCenterOcxApp and DLL registration.

#include "stdafx.h"
#include "SteveMediaCenterOcx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CSteveMediaCenterOcxApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x4336d4e7, 0x3ce3, 0x47ee, { 0x84, 0x4d, 0xbe, 0x1f, 0x7, 0x96, 0xaf, 0xb9 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterOcxApp::InitInstance - DLL initialization

BOOL CSteveMediaCenterOcxApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		AfxEnableControlContainer();
		free((void*)m_pszRegistryKey);
		m_pszRegistryKey =_tcsdup(_T("SteveSoftware"));
		free((void*)m_pszProfileName);
		m_pszProfileName =_tcsdup(_T("FoxMediaCenter"));
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CSteveMediaCenterOcxApp::ExitInstance - DLL termination

int CSteveMediaCenterOcxApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
