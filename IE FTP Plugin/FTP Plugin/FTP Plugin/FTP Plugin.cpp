// FTP Plugin.cpp : Implementation of DLL Exports.


#include "stdafx.h"
#include "resource.h"
#include "FTPPlugin.h"


class CFTPPluginModule : public CAtlDllModuleT< CFTPPluginModule >
{
public :
	DECLARE_LIBID(LIBID_FTPPluginLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FTPPLUGIN, "{8BC5D1D8-C7CB-49C0-B4F6-FF9B1BDC41F0}")
};

CFTPPluginModule _AtlModule;


#ifdef _MANAGED
#pragma managed(push, off)
#endif

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}

#ifdef _MANAGED
#pragma managed(pop)
#endif




// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	HKEY hKeyLocal = NULL;
	CString strValue = _T(APP_NAME);
	DWORD dwSize = strValue.GetLength();
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Internet Explorer\\Toolbar"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKeyLocal, NULL);
	RegSetValueEx(hKeyLocal, _T("{DF9A8ABF-A30C-4240-9BFE-E03E7EADC816}"), 0, REG_BINARY, (BYTE*)strValue.GetBuffer(dwSize), dwSize);
	strValue.ReleaseBuffer();
	RegCloseKey(hKeyLocal);

    // registers object, typelib and all interfaces in typelib
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	HKEY hKeyLocal = NULL;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Internet Explorer\\Toolbar"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKeyLocal, NULL);
	RegDeleteValue(hKeyLocal, _T("{DF9A8ABF-A30C-4240-9BFE-E03E7EADC816}"));
	RegCloseKey(hKeyLocal);

	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}

