
// TreeCtrlDemoDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "TreeCtrlDemo.h"
#include "TreeCtrlDemoDlg.h"
#include "afxdialogex.h"

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


// CTreeCtrlDemoDlg 대화 상자




CTreeCtrlDemoDlg::CTreeCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTreeCtrlDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_Tree);
}

BEGIN_MESSAGE_MAP(CTreeCtrlDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, &CTreeCtrlDemoDlg::OnTvnSelchangedTree)
	ON_BN_CLICKED(IDC_BUTTON_CHECKUPCHILD, &CTreeCtrlDemoDlg::OnBnClickedButtonCheckupchild)
END_MESSAGE_MAP()


// CTreeCtrlDemoDlg 메시지 처리기

BOOL CTreeCtrlDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	InitTreeCtrl();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTreeCtrlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTreeCtrlDemoDlg::OnPaint()
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
HCURSOR CTreeCtrlDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTreeCtrlDemoDlg::InitTreeCtrl(void)
{
	CBitmap Bmp;
	Bmp.LoadBitmapW(IDB_TreeImageList);

	static CImageList ImgList;
	ImgList.Create(16,16,ILC_COLOR24,6,0);
	ImgList.Add(&Bmp,RGB(255,0,0));
	m_Tree.SetImageList(&ImgList,TVSIL_NORMAL);

	HTREEITEM hItem = NULL;
	hItem = m_Tree.InsertItem(_T("바탕화면"),0,0,TVI_ROOT);
	hItem = m_Tree.InsertItem(_T("내 문서"),1,5,hItem);
	m_Tree.InsertItem(_T("내 그림"),2,5,hItem);
	m_Tree.InsertItem(_T("내 비디오"),3,5,hItem);
	hItem = m_Tree.InsertItem(_T("Sample folder"),4,5,hItem);
	hItem = m_Tree.InsertItem(_T("Sub folder"),4,5,hItem);

	m_Tree.EnsureVisible(hItem);

}


void CTreeCtrlDemoDlg::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strItem = m_Tree.GetItemText(pNMTreeView->itemNew.hItem);
	GetDlgItem(IDC_STATIC_SELECTED)->SetWindowText(strItem);

	*pResult = 0;
}


void CTreeCtrlDemoDlg::OnBnClickedButtonCheckupchild()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HTREEITEM hItem = m_Tree.GetRootItem();
	if(m_Tree.GetCheck(hItem))
		AfxMessageBox(m_Tree.GetItemText(hItem));
	
	CheckupChild(m_Tree.GetRootItem());


}


void CTreeCtrlDemoDlg::CheckupChild(HTREEITEM hItem)
{
	HTREEITEM hChildItem = m_Tree.GetChildItem(hItem);
	
	while(hChildItem != NULL)
	{
		if (m_Tree.GetCheck(hChildItem))
			AfxMessageBox(m_Tree.GetItemText(hChildItem));

		if(m_Tree.ItemHasChildren(hChildItem))
			CheckupChild(hChildItem);

		hChildItem = m_Tree.GetNextItem(hChildItem,TVGN_NEXT);
	}
}
