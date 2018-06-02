// ReadToMePlugin.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"

// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
[ module(dll, uuid = "{9BA94845-6AAB-4BBB-9E0F-3BE22B8C1AFB}", 
		 name = "ReadToMePlugin", 
		 helpstring = "ReadToMePlugin 1.0 Type Library",
		 resource_name = "IDR_READTOMEPLUGIN") ]
class CReadToMePluginModule
{
public:
// Override CAtlDllModuleT members

	BOOL WINAPI DllMain(DWORD dwReason, LPVOID lpReserved) 
	{
		if (dwReason == DLL_PROCESS_ATTACH)
		{
			// Don't attach to Windows Explorer
			TCHAR pszLoader[MAX_PATH];
			GetModuleFileName(NULL, pszLoader, MAX_PATH);
			CString sLoader = pszLoader;
			sLoader.MakeLower();
			if (sLoader.Find(_T("explorer.exe")) >= 0)
				return FALSE;
		}
	
		return __super::DllMain(dwReason, lpReserved);
	}

	HRESULT DllRegisterServer(BOOL bRegTypeLib = TRUE) throw()
	{
		HRESULT hr = __super::DllRegisterServer(bRegTypeLib);
		if (SUCCEEDED(hr))
			hr = __super::UpdateRegistryFromResourceS(IDR_READTOMEPLUGIN, TRUE);
		return hr;
	}

	HRESULT DllUnregisterServer(BOOL bUnRegTypeLib = TRUE) throw()
	{
		HRESULT hr = __super::DllUnregisterServer(bUnRegTypeLib);
		hr = __super::UnregisterAppId();
		return hr;
	} 
};
		 
