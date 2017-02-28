
// ListCtrlDemoDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ListCtrlDemo.h"
#include "ListCtrlDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CListCtrlDemoDlg ��ȭ ����




CListCtrlDemoDlg::CListCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CListCtrlDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}

BEGIN_MESSAGE_MAP(CListCtrlDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST, &CListCtrlDemoDlg::OnLvnEndlabeleditList)
	ON_BN_CLICKED(ID_BUTTON_DELETE, &CListCtrlDemoDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CListCtrlDemoDlg �޽��� ó����

BOOL CListCtrlDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	static CImageList ImgList,ImgListSmall;
	ImgList.Create(48,48,ILC_COLOR32,5,0);
	ImgListSmall.Create(16,16,ILC_COLOR32,5,0);
	
	CString strItem = _T("");

	for (int i=0; i<5; ++i)
	{
		ImgList.Add(AfxGetApp()->LoadIconW(IDR_MAINFRAME));
		ImgListSmall.Add(AfxGetApp()->LoadIconW(IDR_MAINFRAME));
		strItem.Format(_T("%dth Item"),i);

		m_List.InsertItem(i,strItem,i);
	}
	
	m_List.SetImageList(&ImgList,LVSIL_NORMAL);
	m_List.SetImageList(&ImgListSmall,LVSIL_SMALL);
	
	LVITEM item;
	::ZeroMemory(&item,sizeof(item));
	item.mask = LVIF_TEXT |LVIF_IMAGE |LVIF_STATE;
	item.pszText = _T("TEST ITEM");
	item.iItem = 5;
	item.iImage = 1;
	item.state = LVIS_SELECTED | LVIS_FOCUSED;

	m_List.InsertItem(&item);

	m_List.InsertColumn(0,_T("Name"),LVCFMT_LEFT,200);
	m_List.InsertColumn(1,_T("Description"),LVCFMT_LEFT,300);
	m_List.ModifyStyle(LVS_TYPEMASK,LVS_REPORT);

	m_List.SetItemText(0,0,_T("New Name"));
	m_List.SetItemText(0,1,_T("Tet string"));
	
	DWORD dwExStyle = m_List.GetExtendedStyle();
	m_List.SetExtendedStyle(dwExStyle | LVS_EX_CHECKBOXES |LVS_EX_BORDERSELECT);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CListCtrlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CListCtrlDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CListCtrlDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CListCtrlDemoDlg::OnLvnEndlabeleditList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strText = _T("");
	CEdit* pEdit = m_List.GetEditControl();
	pEdit->GetWindowTextW(strText);

	m_List.SetItemText(pDispInfo->item.iItem,0,strText);

	*pResult = 0;
}


void CListCtrlDemoDlg::OnBnClickedButtonDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nCount = m_List.GetItemCount();
	for (int i = nCount; i >= 0; --i)
	{
		if (m_List.GetCheck(i))
			m_List.DeleteItem(i);
	}
}
