
// MFCHW2Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFCHW2.h"
#include "MFCHW2Dlg.h"
#include "afxdialogex.h"
#include <time.h>
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCHW2Dlg 대화 상자




CMFCHW2Dlg::CMFCHW2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCHW2Dlg::IDD, pParent)
	, m_Edit1(_T(""))
	, m_Edit2(_T(""))
	, m_Edit3(_T(""))
	, m_Edit4(_T(""))
	, m_Edit5(_T(""))
	, m_Edit6(_T(""))
	, m_Edit7(_T(""))
	, m_Edit8(_T(""))
	, m_Edit9(_T(""))
	, m_Edit10(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCHW2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	DDX_Text(pDX, IDC_EDIT2, m_Edit2);
	DDX_Text(pDX, IDC_EDIT3, m_Edit3);
	DDX_Text(pDX, IDC_EDIT4, m_Edit4);
	DDX_Text(pDX, IDC_EDIT5, m_Edit5);
	DDX_Text(pDX, IDC_EDIT6, m_Edit6);
	DDX_Text(pDX, IDC_EDIT7, m_Edit7);
	DDX_Text(pDX, IDC_EDIT8, m_Edit8);
	DDX_Text(pDX, IDC_EDIT9, m_Edit9);
	DDX_Text(pDX, IDC_EDIT10, m_Edit10);
}

BEGIN_MESSAGE_MAP(CMFCHW2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CREATEDATA, &CMFCHW2Dlg::OnBnClickedButtonCreatedata)
	ON_BN_CLICKED(IDC_BUTTON_SORT, &CMFCHW2Dlg::OnBnClickedButtonSort)
END_MESSAGE_MAP()


// CMFCHW2Dlg 메시지 처리기

BOOL CMFCHW2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	srand( (unsigned int)(time(NULL)) );
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

void CMFCHW2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCHW2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCHW2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCHW2Dlg::OnBnClickedButtonCreatedata()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString  str;
	int start_number = 0;
	int end_number = 100;
	
		for(int i = 0; i < 10; i++)
		{
			int random_number = (rand() % (end_number - start_number+1)) + start_number;
			TRACE("Random number: %d", random_number);
			str.Format(_T("%d"), random_number);
			GetDlgItem(IDC_EDIT1 +i)->SetWindowText(str);
		}
	
}


void CMFCHW2Dlg::OnBnClickedButtonSort()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i, j, temp = 0;
	int comparison_count = 0;
	int parm_data[11];
	CString  str, tmpstr;
	AfxMessageBox(_T("정렬 시작!!"));
	for(int i = 0; i < 10; i++)
	{
		GetDlgItem(IDC_EDIT1 +i)->GetWindowText(str);
		parm_data[i+1] = _ttoi(str);
	}

	for(i = 1; i < 11; i++)
	{
		for(j = 1; j < 11 - i; j++)
		{
			comparison_count++;
			if(parm_data[j] > parm_data[j+1])
			{
				temp = parm_data[j];
				parm_data[j] = parm_data[j+1];
				parm_data[j+1] = temp;                                    
			}
		}
		if ( i < 10)
		{		
			tmpstr.Format(_T("%d 단계 정렬중!"), i);
			AfxMessageBox(tmpstr);
		}
		else
		{
			AfxMessageBox(_T("정렬 완료!!"));
		}

	}
	for(int i = 0; i < 10; i++)
	{
	
		str.Format(_T("%d"), parm_data[i+1]);
		GetDlgItem(IDC_EDIT1 +i)->SetWindowText(str);
	}
	
}
