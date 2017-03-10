// dllmain.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxwin.h>
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE DllDemoDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("DllDemo.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(DllDemoDLL, hInstance))
			return 0;

		new CDynLinkLibrary(DllDemoDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("DllDemo.DLL Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(DllDemoDLL);
	}
	return 1;   // ok
}

BOOL WINAPI GetModulePath(CString& strPath)
{
	TCHAR szBuffer[MAX_PATH];
	::ZeroMemory(szBuffer, sizeof(szBuffer));
	::GetModuleFileName(NULL, szBuffer, MAX_PATH);

	for(int i = lstrlen(szBuffer) - 1; i >= 0; --i)
	{
		if(szBuffer[i] == '\\')
		{
			int j = lstrlen(szBuffer) - 1;
			for(; j >= i; --j)
			{
				szBuffer[j] = NULL;
			}

			if(szBuffer[j] == ':')		szBuffer[j + 1] = '\\';

			strPath = szBuffer;
			return TRUE;
		}
	}

	return FALSE;
}
