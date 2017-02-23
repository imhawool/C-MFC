// calcuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "calcu.h"
#include "calcuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalcuDlg dialog

CCalcuDlg::CCalcuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalcuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalcuDlg)
	m_strLed = _T("");
	m_strLed1 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalcuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalcuDlg)
	DDX_Text(pDX, IDC_EDIT_LED, m_strLed);
	DDX_Text(pDX, IDC_EDIT_LED2, m_strLed1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalcuDlg, CDialog)
	//{{AFX_MSG_MAP(CCalcuDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTT_0, OnButt0)
	ON_BN_CLICKED(IDC_BUTT_1, OnButt1)
	ON_BN_CLICKED(IDC_BUTT_2, OnButt2)
	ON_BN_CLICKED(IDC_BUTT_3, OnButt3)
	ON_BN_CLICKED(IDC_BUTT_4, OnButt4)
	ON_BN_CLICKED(IDC_BUTT_5, OnButt5)
	ON_BN_CLICKED(IDC_BUTT_6, OnButt6)
	ON_BN_CLICKED(IDC_BUTT_7, OnButt7)
	ON_BN_CLICKED(IDC_BUTT_8, OnButt8)
	ON_BN_CLICKED(IDC_BUTT_9, OnButt9)
	ON_BN_CLICKED(IDC_BUTT_ZERO, OnButtZero)
	ON_BN_CLICKED(IDC_BUTT_RESULT, OnButtResult)
	ON_BN_CLICKED(IDC_BUTT_ADD, OnButtAdd)
	ON_BN_CLICKED(IDC_BUTT_SUB, OnButtSub)
	ON_BN_CLICKED(IDC_BUTT_MUL, OnButtMul)
	ON_BN_CLICKED(IDC_BUTT_DIV, OnButtDiv)
	ON_BN_CLICKED(IDC_BUTT_EXIT, OnButtExit)
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalcuDlg message handlers

BOOL CCalcuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here     //변수들을 초기화 한다.
	m_iCal=0;   
	m_iOne=0;  
	m_iTwo=0;   
	m_iSwitch=0;  
	m_strLed=""; 
	m_strNumber="";  

	static CFont font,font1;
	LOGFONT LogFont,LogFont1;


	GetDlgItem(IDC_EDIT_LED)->GetFont()->GetLogFont(&LogFont);
	GetDlgItem(IDC_EDIT_LED2)->GetFont()->GetLogFont(&LogFont);
	GetDlgItem(IDC_STATIC)->GetFont()->GetLogFont(&LogFont1);
	LogFont.lfWeight = 100;
	LogFont.lfHeight = 40;
	LogFont1.lfWeight = 300;
	LogFont1.lfHeight = 30;

	font.CreateFontIndirectA(&LogFont);

	GetDlgItem(IDC_EDIT_LED)->SetFont(&font);
	GetDlgItem(IDC_EDIT_LED2)->SetFont(&font);
	GetDlgItem(IDC_STATIC)->SetFont(&font1);

	//GetDlgItem(IDC_STATIC)->GetFont()->GetLogFont(&LogFont);
	
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalcuDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalcuDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);


		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalcuDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCalcuDlg::Number(int a)
{
	m_strNumber.Format("%d",a);

	m_strLed+=m_strNumber;
	m_strLed1+=m_strNumber;

	if (m_iSwitch==0)   
	{
		m_iOne=atoi(m_strLed);
	} 
	else
	{
		m_iTwo=atoi(m_strLed);
	}
	m_strLed="";
	UpdateData(FALSE);


}

void CCalcuDlg::Cal(int a)
{
	m_iSwitch=10;          
	m_strLed="";
	m_strNumber="";
	m_iCal=a;            
	UpdateData(FALSE);

}

void CCalcuDlg::OnButt0() 
{
	// TODO: Add your control notification handler code here
	Number(0); 
	
}

void CCalcuDlg::OnButt1() 
{
	// TODO: Add your control notification handler code here
	Number(1);
	
}

void CCalcuDlg::OnButt2() 
{
	// TODO: Add your control notification handler code here
	Number(2);
}

void CCalcuDlg::OnButt3() 
{
	// TODO: Add your control notification handler code here
	Number(3);
}

void CCalcuDlg::OnButt4() 
{
	// TODO: Add your control notification handler code here
	Number(4);
}

void CCalcuDlg::OnButt5() 
{
	// TODO: Add your control notification handler code here
	Number(5);
}

void CCalcuDlg::OnButt6() 
{
	// TODO: Add your control notification handler code here
	Number(6);
}

void CCalcuDlg::OnButt7() 
{
	// TODO: Add your control notification handler code here
	Number(7);
}

void CCalcuDlg::OnButt8() 
{
	// TODO: Add your control notification handler code here
	Number(8);
}

void CCalcuDlg::OnButt9() 
{
	// TODO: Add your control notification handler code here
	Number(9);
}

void CCalcuDlg::OnButtZero() 
{
	// TODO: Add your control notification handler code here
	m_iCal=0;
	m_iOne=0;
	m_iTwo=0;
	m_iSwitch=0;
	m_strLed="";
	m_strLed1="";
	m_strNumber="";
	UpdateData(FALSE);

}

void CCalcuDlg::OnButtResult() 
{
	// TODO: Add your control notification handler code here
	
	switch(m_iCal)
	{
	case 1:
		m_strLed.Format("%d",m_iOne+m_iTwo);
		break;
	case 2:
		m_strLed.Format("%d",m_iOne-m_iTwo);
		break;
	case 3:
		m_strLed.Format("%d",m_iOne*m_iTwo);
	    break;
	case 4:
		m_strLed.Format("%d",m_iOne/m_iTwo);
	    break;
	}
	m_iOne=atoi(m_strLed);

	UpdateData(FALSE);
}

void CCalcuDlg::OnButtAdd() 
{
	// TODO: Add your control notification handler code here
	m_strLed1+="+";
	Cal(1);
	UpdateData(FALSE); 
}

void CCalcuDlg::OnButtSub() 
{
	// TODO: Add your control notification handler code here
	m_strLed1+="-";
	Cal(2);
	UpdateData(FALSE);
}

void CCalcuDlg::OnButtMul() 
{
	// TODO: Add your control notification handler code here
	m_strLed1+="*";
	Cal(3);
	UpdateData(FALSE);
}

void CCalcuDlg::OnButtDiv() 
{
	// TODO: Add your control notification handler code here
	m_strLed1+="/";
	Cal(4);
	UpdateData(FALSE);
}

void CCalcuDlg::OnButtExit() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}


