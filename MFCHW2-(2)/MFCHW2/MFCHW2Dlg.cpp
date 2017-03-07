
// MFCHW2Dlg.cpp : ���� ����
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


// CMFCHW2Dlg ��ȭ ����




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


// CMFCHW2Dlg �޽��� ó����

BOOL CMFCHW2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	srand( (unsigned int)(time(NULL)) );
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

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFCHW2Dlg::OnPaint()
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
HCURSOR CMFCHW2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCHW2Dlg::OnBnClickedButtonCreatedata()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int i, j, temp = 0;
	int comparison_count = 0;
	int parm_data[11];
	CString  str, tmpstr;
	AfxMessageBox(_T("���� ����!!"));
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
			tmpstr.Format(_T("%d �ܰ� ������!"), i);
			AfxMessageBox(tmpstr);
		}
		else
		{
			AfxMessageBox(_T("���� �Ϸ�!!"));
		}

	}
	for(int i = 0; i < 10; i++)
	{
	
		str.Format(_T("%d"), parm_data[i+1]);
		GetDlgItem(IDC_EDIT1 +i)->SetWindowText(str);
	}
	
}
