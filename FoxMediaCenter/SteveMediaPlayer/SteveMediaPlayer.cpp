// SteveMediaPlayer.cpp : Implementation of CSteveMediaPlayerApp and DLL registration.

#include "stdafx.h"
#include "SteveMediaPlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CSteveMediaPlayerApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x5a560e8f, 0xcb40, 0x4dc7, { 0x86, 0xc2, 0x4d, 0xb3, 0x1c, 0x75, 0x90, 0xf2 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CSteveMediaPlayerApp::InitInstance - DLL initialization

BOOL CSteveMediaPlayerApp::InitInstance()
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
// CSteveMediaPlayerApp::ExitInstance - DLL termination

int CSteveMediaPlayerApp::ExitInstance()
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
