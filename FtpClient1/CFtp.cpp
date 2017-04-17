

#include "stdafx.h"
#include "CFtp.h"
#include "CFtpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CCFtpApp, CWinApp)
	//{{AFX_MSG_MAP(CCFtpApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCFtpApp construction

CCFtpApp::CCFtpApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

CCFtpApp theApp;

BOOL CCFtpApp::InitInstance()
{
	AfxEnableControlContainer();
	SetRegistryKey(_T("CFtp")); // 레지스트리 키를 설정

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CCFtpDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
	return FALSE;

}
