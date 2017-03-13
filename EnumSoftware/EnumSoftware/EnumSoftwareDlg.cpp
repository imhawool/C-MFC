
// EnumSoftwareDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "EnumSoftware.h"
#include "EnumSoftwareDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CEnumSoftwareDlg 대화 상자




CEnumSoftwareDlg::CEnumSoftwareDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEnumSoftwareDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnumSoftwareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_List, m_List);
}

BEGIN_MESSAGE_MAP(CEnumSoftwareDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_Button_InstalledSoftware, &CEnumSoftwareDlg::OnBnClickedButtonInstalledsoftware)
END_MESSAGE_MAP()


// CEnumSoftwareDlg 메시지 처리기

BOOL CEnumSoftwareDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CEnumSoftwareDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CEnumSoftwareDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CEnumSoftwareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEnumSoftwareDlg::OnBnClickedButtonInstalledsoftware()
{
	if(m_List.GetCount() > 0)		m_List.ResetContent();

	CString csSWKey =
		_T("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
	CString	csSubKey = _T("");

	DWORD	dwIndex = 0;
	DWORD	dwType = 0;
	TCHAR	szKeyName[MAX_PATH] = {0};
	TCHAR	szValue[MAX_PATH] = {0};
	DWORD	dwBufferSize = 0;
	HKEY	hKey = NULL, hKeySub = NULL;

	DWORD dwResult = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE,
									(LPCTSTR)csSWKey, 0, KEY_READ, &hKey);
	if(dwResult != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("ERROR: Failed to open registry key!"));
		return;
	}

	dwBufferSize = MAX_PATH;
	while(::RegEnumKey(hKey,
					dwIndex,
					szKeyName,
					dwBufferSize) != ERROR_NO_MORE_ITEMS)
	{
		csSubKey = csSWKey + TEXT("\\") + szKeyName;
		dwResult = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE,
									(LPCTSTR)csSubKey, 0, KEY_READ, &hKeySub);
		if(dwResult != ERROR_SUCCESS)
		{
			dwIndex++;
			::ZeroMemory(szKeyName, MAX_PATH);
			dwBufferSize = MAX_PATH;
			continue;
		}

		dwType = 0;
		::ZeroMemory(szValue, MAX_PATH);
		dwBufferSize = MAX_PATH;
		if(::RegQueryValueEx(hKeySub, _T("DisplayName"), NULL, &dwType,
							(BYTE*)szValue, &dwBufferSize) == ERROR_SUCCESS)
		{
			m_List.AddString(szValue);
		}

		::RegCloseKey(hKeySub);
		dwIndex++;
		::ZeroMemory(szKeyName, MAX_PATH);
		dwBufferSize = MAX_PATH;
	}

	::RegCloseKey(hKey);
}
