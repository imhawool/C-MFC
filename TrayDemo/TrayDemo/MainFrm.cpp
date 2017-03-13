
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "TrayDemo.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_DESTROY()
	ON_MESSAGE(UM_TRAY, &CMainFrame::OnTray)
	ON_WM_CLOSE()
	ON_COMMAND(ID_TrayMenu_ShowApp, &CMainFrame::OnTraymenuShowapp)
	ON_COMMAND(ID_APP_EXIT, &CMainFrame::OnAppExit)
	ON_COMMAND(ID_Menu_ToggleIcon, &CMainFrame::OnMenuToggleicon)
	ON_COMMAND(ID_Menu_StartAnimation, &CMainFrame::OnMenuStartanimation)
	ON_COMMAND(ID_Menu_StopAnimation, &CMainFrame::OnStopanimation)
	ON_WM_TIMER()
	ON_COMMAND(ID_Menu_RestartShell, &CMainFrame::OnMenuRestartshell)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2003);
	m_bIconFlag = TRUE;

	m_uShellRestart = ::RegisterWindowMessage(__TEXT("TaskbarCreated"));
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // fail to create
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// Allow user-defined toolbars operations:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Enable toolbar and docking window menu replacement
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// enable quick (Alt+drag) toolbar customization
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// load user-defined toolbar images
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			m_UserImages.SetImageSize(CSize(16, 16), FALSE);
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	GotoTray();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;


	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 기본 클래스가 실제 작업을 수행합니다.
	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// enable customization button for all user toolbars
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}

void CMainFrame::GotoTray(void)
{
	NOTIFYICONDATA nid;
	::ZeroMemory(&nid, sizeof(nid));
	nid.cbSize				= sizeof(nid);
	nid.hWnd				= m_hWnd;
	nid.uID					= IDR_MAINFRAME;
	nid.uFlags				= NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage	= UM_TRAY;
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	wsprintf(nid.szTip, _T("%s"), _T("TrayDemo"));

	::Shell_NotifyIcon(NIM_ADD, &nid);
}

void CMainFrame::OnDestroy()
{
	NOTIFYICONDATA nid;
	nid.cbSize	= sizeof(nid);
	nid.hWnd	= m_hWnd;
	nid.uID		= IDR_MAINFRAME;
	::Shell_NotifyIcon(NIM_DELETE, &nid);

	CFrameWndEx::OnDestroy();
}

LRESULT CMainFrame::OnTray(WPARAM wParam, LPARAM lParam)
{
	if(lParam == WM_RBUTTONDOWN)
	{
		SetCapture();
	}
    else if(lParam == WM_RBUTTONUP)
    {
		CMenu menu, *pMenu = NULL;
		CPoint pt;

		menu.LoadMenu(IDR_Tray);
		pMenu = menu.GetSubMenu(0);

		GetCursorPos(&pt);
		SetForegroundWindow();
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON,
								pt.x, pt.y, this);
		::PostMessage(m_hWnd, WM_NULL, 0, 0);

		ReleaseCapture();
	}
	else if(lParam == WM_LBUTTONDBLCLK)
	{
		ShowWindow(SW_SHOW);
		SetForegroundWindow();
	}
	return 0;
}

void CMainFrame::OnClose()
{
	ShowWindow(SW_HIDE);
//	CFrameWndEx::OnClose();
}

void CMainFrame::OnTraymenuShowapp()
{
	ShowWindow(SW_SHOW);
}

void CMainFrame::OnAppExit()
{
	CFrameWndEx::OnClose();
}

void CMainFrame::OnMenuToggleicon()
{
	NOTIFYICONDATA nid;
	::ZeroMemory(&nid, sizeof(nid));
	nid.cbSize				= sizeof(nid);
	nid.hWnd				= m_hWnd;
	nid.uID					= IDR_MAINFRAME;
	nid.uFlags				= NIF_ICON;
	nid.uCallbackMessage	= UM_TRAY;

	m_bIconFlag = !m_bIconFlag;
	if(m_bIconFlag)		nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	else				nid.hIcon = AfxGetApp()->LoadIcon(IDR_TrayDemoTYPE);

	::Shell_NotifyIcon(NIM_MODIFY, &nid);
}

void CMainFrame::OnMenuStartanimation()
{
	SetTimer(100, 500, NULL);
}

void CMainFrame::OnStopanimation()
{
	KillTimer(100);
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	OnMenuToggleicon();

	CFrameWndEx::OnTimer(nIDEvent);
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message == m_uShellRestart)		GotoTray();
	return CFrameWndEx::WindowProc(message, wParam, lParam);
}

void CMainFrame::OnMenuRestartshell()
{
	HWND hWnd = ::FindWindow(_T("Progman"), NULL);
	::PostMessage(hWnd, WM_QUIT, 0, 0);

	::ShellExecute(NULL, NULL, _T("explorer.exe"), NULL, NULL, SW_SHOW);
}
