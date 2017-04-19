// CFtpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CFtp.h"
#include "CFtpDlg.h"

#include "direct.h" // for _getcwd	and	_chdir
#include "ConnectDlg.h"
#include "TempDialog.h"
#include "atlconv.h "
#include <locale.h> 

//#include <afxtempl.h>
#include <process.h>
#include <afxmt.h>			// �̺�Ʈ ó���ҷ���...

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


class CAboutDlg : public CDialog
{
public:
	bool         m_bOpen;

	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };
	CRoundButton	m_Ok;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);     // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	m_bOpen=true;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_Ok);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CCFtpDlg ��ȭ ����

CEvent g_eventStop;	// �۾����� �����ϱ����� ���� �̺�Ʈ���� 

CCFtpDlg::CCFtpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCFtpDlg::IDD, pParent)
{
	m_strLocalDirText = _T("");
	m_strRemoteDirText = _T("");
	m_strUpload = _T("");
	m_strDownload = _T("");
	m_bOpen=true;

	m_pConnection = NULL;
	m_pFileFind = NULL;
	HANDLE g_eventStop = NULL;
	g_eventStop = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_bConnected = FALSE;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCFtpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_BUTTON_ABORT, m_BtnAbort);
	DDX_Control(pDX, IDC_BUTTON_LREFRESH, m_BtnLocRefresh);
	DDX_Control(pDX, IDC_BUTTON_RREFRESH, m_BtnReRefresh);
	DDX_Control(pDX, IDC_BUTTON_UPLOAD, m_BtnUpload);
	DDX_Control(pDX, IDC_BUTTON_DOWNLOAD, m_BtnDown);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_BtnExit);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_BtnConn);
	DDX_Control(pDX, IDC_BUTTON_UNCONNECT, m_BtnUnconn);
	
	DDX_Control(pDX, IDC_PROGRESS_UPLOAD, m_prsUpload);
	DDX_Control(pDX, IDC_PROGRESS_DOWNLOAD, m_prsDownload);
	DDX_Control(pDX, IDC_LIST_REMOTE_FILE, m_ctrlRemoteFile);
	DDX_Control(pDX, IDC_LIST_LOCAL_FILE, m_ctrlLocalFile);
	DDX_Text(pDX, IDC_STATIC_LOCAL_DIR_TEXT, m_strLocalDirText);
	DDX_Text(pDX, IDC_STATIC_REMOTE_DIR_TEXT, m_strRemoteDirText);
	DDX_Text(pDX, IDC_STATIC_UPLOAD, m_strUpload);
	DDX_Text(pDX, IDC_STATIC_DOWNLOAD, m_strDownload);

}

BEGIN_MESSAGE_MAP(CCFtpDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_LOCAL_FILE, OnDblclkListLocalFile)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_REMOTE_FILE, OnDblclkListRemoteFile)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, OnButtonUpload)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, OnButtonDownload)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	//ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
	ON_BN_CLICKED(IDC_BUTTON_LMKDIR, OnButtonLmkdir)
	ON_BN_CLICKED(IDC_BUTTON_LREFRESH, OnButtonLrefresh)
	ON_BN_CLICKED(IDC_BUTTON_LRENAME, OnButtonLrename)
	ON_BN_CLICKED(IDC_BUTTON_LDELETE, OnButtonLdelete)
	ON_BN_CLICKED(IDC_BUTTON_RMKDIR, OnButtonRmkdir)
	ON_BN_CLICKED(IDC_BUTTON_RRENAME, OnButtonRrename)
	ON_BN_CLICKED(IDC_BUTTON_RDELETE, OnButtonRdelete)
	ON_BN_CLICKED(IDC_BUTTON_RREFRESH, OnButtonRrefresh)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_LOCAL_FILE, OnRclickListLocalFile)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_REMOTE_FILE, OnRclickListRemoteFile)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_LOCAL_FILE, OnItemchangedListLocalFile)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_REMOTE_FILE, OnItemchangedListRemoteFile)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_WM_NCCREATE()
	ON_BN_CLICKED(IDC_BUTTON_UNCONNECT, &CCFtpDlg::OnBnClickedButtonUnconnect)

	ON_BN_CLICKED(IDC_BUTTON_ABORT, &CCFtpDlg::OnBnClickedButtonAbort)
	ON_BN_CLICKED(IDC_BUTTON_RESUME, &CCFtpDlg::OnBnClickedButtonResume)
END_MESSAGE_MAP()

// CCFtpDlg �޽��� ó����

BOOL CCFtpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.
	
	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CenterWindow(CWnd::GetDesktopWindow());

	InitRoundButton(); // ���� ��ư ����
	InitButton(); // ��ư �ʱ�ȭ
	InsertColumn();	// �÷� ����
	UpdateLocalListCtrl(); //���� ����Ʈ ������Ʈ

	CButton* pCheck = (CButton*)GetDlgItem(IDC_RADIO_BINARY); //���� ��ư(Binary�� �ʱ�ȭ)
	pCheck->SetCheck(1);
	CButton* pCheck1 = (CButton*)GetDlgItem(IDC_RADIO_PASSIVE); //���� ��ư(PASSIVE�� �ʱ�ȭ)
	pCheck1->SetCheck(1);
	return TRUE; // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CCFtpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow(CWnd::GetDesktopWindow());

	return TRUE;  
}


// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.


void CCFtpDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);  // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CCFtpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// �÷� ����
void CCFtpDlg::InsertColumn()
{
	CRect rect;
	m_ctrlLocalFile.GetClientRect(&rect);
	m_ctrlLocalFile.InsertColumn(0,"���ϸ�",LVCFMT_LEFT,120);
	m_ctrlLocalFile.InsertColumn(1,"ũ��",LVCFMT_RIGHT,60);
	m_ctrlLocalFile.InsertColumn(2,"��¥",LVCFMT_LEFT,95);

	m_ctrlRemoteFile.GetClientRect(&rect);
	m_ctrlRemoteFile.InsertColumn(0,"���ϸ�",LVCFMT_LEFT,120);
	m_ctrlRemoteFile.InsertColumn(1,"ũ��",LVCFMT_RIGHT,60);
	m_ctrlRemoteFile.InsertColumn(2,"��¥",LVCFMT_LEFT,95);

}

// �� ��ǻ�� ���� ������Ʈ
void CCFtpDlg::UpdateLocalListCtrl()
{
	CFileFind finder;
	CString	str;
	unsigned long size;
	CTime time;
	int bWorking;
	int index;
	int imgType=0;

	m_ctrlLocalFile.DeleteAllItems();

	bWorking = finder.FindFile("*.*");

	while(bWorking)
	{
		imgList.DeleteImageList();
		bWorking = finder.FindNextFile();
		str = finder.GetFileName();

		if (str==".") continue;

		if(finder.IsDirectory())
		{
			if (str=="..")
			{
				str="\\" + str;
				imgType=2;
			}
			else
			{
			str="\\" + str;
			imgType=1;
			}
		}
		else
		{
			imgType=0;
		}

		// ���� ����Ʈ ��Ʈ�ѿ� �׸� ����
		imgList.Create(IDB_BITMAP_IMAGE, 16, 1, (COLORREF)-1);
		m_ctrlLocalFile.SetImageList(&imgList, LVSIL_SMALL);
		index=m_ctrlLocalFile.InsertItem(0, str, imgType);

		size = finder.GetLength()/1024;
		str.Format("%d",size);
		m_ctrlLocalFile.SetItemText(index,1,str+"KB");

		finder.GetLastWriteTime(time);
		str = time.Format("%y-%m-%d %H:%M");
		m_ctrlLocalFile.SetItemText(index,2,str);
		
	}

	char buff[256];
	_getcwd(buff,255);
	m_strLocalDirText = buff;

	UpdateData(FALSE);
}

// ������ ���� ������Ʈ
void CCFtpDlg::UpdateRemoteListCtrl()
{
	CString str;
	BOOL bContinue = TRUE;
	BOOL bDir=false;
	unsigned long size;
	CTime time;
	int bWorking;
	int index;
	int imgType=0;
	CString dirName, strtemp;

	m_ctrlRemoteFile.DeleteAllItems();

	bWorking = m_pFileFind->FindFile("*.*");

	while(bWorking)
	{
		imgList.DeleteImageList();
		bWorking = m_pFileFind->FindNextFile();

		CStringW strTemp =  CA2W(m_pFileFind->GetFileName(), CP_UTF8);//���丮 �Ǵ� ���ϸ�
		str = CW2A(strTemp);

		if (str=="..") bDir=TRUE; //�������丮 ����ó��
		if (str=="." ) continue;

		if (m_pFileFind->IsDirectory())
		{
			str = "/" + str;
			imgType=1;
		}
		else
		{
			imgType=0;
		}
		// ����Ʈ ����Ʈ ��Ʈ�ѿ� �׸� ����
		imgList.Create(IDB_BITMAP_IMAGE, 16, 1, (COLORREF)-1);
		m_ctrlRemoteFile.SetImageList(&imgList, LVSIL_SMALL);
		index=m_ctrlRemoteFile.InsertItem(0, str, imgType);

		size = m_pFileFind->GetLength()/1024;
		str.Format("%d",size);
		m_ctrlRemoteFile.SetItemText(index,1,str+"KB");

		m_pFileFind->GetLastWriteTime(time);
		str = time.Format("%y-%m-%d %H:%M");
		m_ctrlRemoteFile.SetItemText(index,2,str);
	}

	if (!bDir) m_ctrlRemoteFile.InsertItem(0, "/..", 2);
	CString strItem;
	m_pConnection->GetCurrentDirectory(strItem);
	CStringW strTemp =  CA2W(strItem, CP_UTF8);//���丮 �Ǵ� ���ϸ�
	m_strRemoteDirText = CW2A(strTemp);

	UpdateData(FALSE);
}

// ���� ��ư
void CCFtpDlg::OnButtonConnect() 
{
	BOOL mode;
	DWORD dwValue = 10000;
	// TODO: Add your control notification handler code here
	if(m_pConnection !=NULL)
	{
		if (AfxMessageBox("������ ������ �����ðڽ��ϱ�?", MB_YESNO|MB_ICONQUESTION)==IDYES)
		{
		m_pConnection->Close();
		delete m_pConnection;
		m_pConnection = NULL;

		m_ctrlRemoteFile.DeleteAllItems();

		InitButton();
		UpdateLocalListCtrl();
		}
		else return;
	}
	
	CConnectDlg dlg;
	if(dlg.DoModal() != IDOK) return;

	m_Session.SetFtpPtr(this);

	//time-out ����
	m_Session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, &dwValue, sizeof(dwValue));
	m_Session.SetOption(INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, &dwValue, sizeof(dwValue));
	m_Session.SetOption(INTERNET_OPTION_CONTROL_SEND_TIMEOUT, &dwValue, sizeof(dwValue));
	m_Session.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, &dwValue, sizeof(dwValue));
	m_Session.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, &dwValue, sizeof(dwValue));

	BeginWaitCursor();
	if (((CButton*)GetDlgItem(IDC_RADIO_PASSIVE))->GetCheck() == BST_CHECKED)
		mode = TRUE;
	else
		mode = FALSE;	
	if((dlg.m_strPassword).GetLength() == 0)
		m_pConnection = m_Session.GetFtpConnection(dlg.m_strAddress);
	else
		m_pConnection = m_Session.GetFtpConnection(dlg.m_strAddress, dlg.m_strName, dlg.m_strPassword, _ttoi(dlg.m_strPort), mode);
			
	
	if(!m_pConnection)
	{
		AfxMessageBox("������ �ȵ˴ϴ�",MB_OK);
		m_pConnection = NULL;
		return;
	}

	m_pConnection->GetCurrentDirectory(m_strRemoteDirText);
	UpdateData(FALSE);

	if(m_pFileFind) delete m_pFileFind;
	m_pFileFind = new CFtpFileFind(m_pConnection);

	UpdateRemoteListCtrl();

	m_bConnected=TRUE;
	GetDlgItem(IDC_BUTTON_UNCONNECT)->EnableWindow(TRUE);

	InitRemoteList();
	EndWaitCursor();
}

// ���� ���丮 ����
void CCFtpDlg::OnDblclkListLocalFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	CString str;

	pos = m_ctrlLocalFile.GetFirstSelectedItemPosition();
	if(pos == NULL) return;
	pos = pos -1;
	str = m_ctrlLocalFile.GetItemText((int)pos,0);
	
	if(str.GetAt(0) == '\\')
	{
		str = str.Right(str.GetLength() -1);

		_chdir(str);
		UpdateLocalListCtrl();
	}
	else
	{
		CString filePath=m_strLocalDirText + "\\" + str;
		ShellExecute(NULL, "open", filePath, NULL, NULL, SW_SHOW);
	}
	*pResult = 0;
}

// ����Ʈ ���丮 ����
void CCFtpDlg::OnDblclkListRemoteFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	BeginWaitCursor();

	POSITION pos;
	CString str;

	pos = m_ctrlRemoteFile.GetFirstSelectedItemPosition();
	if(pos == NULL) return;

	pos = pos -1;
	str = m_ctrlRemoteFile.GetItemText((int)pos,0);
	
	if(str.GetAt(0) == '/')
	{
		str = str.Right(str.GetLength() -1);
		
		if(!m_pConnection->SetCurrentDirectory(str))
		{
			m_pConnection->GetCurrentDirectory(str);
			AfxMessageBox("���丮 �̵��� �Ұ����Դϴ�.");
			return;
		}

		//m_pConnection->GetCurrentDirectory(m_strRemoteDirText);
		//UpdateData(FALSE);

		UpdateRemoteListCtrl();
	}
	else
	{
		//CString filePath = "//" + str;
		//ShellExecute(NULL, "open", filePath, NULL, NULL, SW_SHOW);
	}
	*pResult = 0;
}

// ���� ���ε�
void CCFtpDlg::OnButtonUpload() 
{
	// TODO: Add your control notification handler code here
	CString strPathName;
	CString strItem;

	CInternetFile* remoteFile;

	char	lpBuffer[2048+1];
	UINT	nByteRead;
	DWORD	fileLength, nSumOfnByteRead;
	MSG		message;
	BOOL	canceled = FALSE;
	long	fileSize;
	DWORD	mode;

	CString remote;
	
	//CString local;
	//GetDlgItemText(IDC_STATIC_LOCAL_DIR_TEXT, local);
	
	g_eventStop.ResetEvent();	// ���۵��� �����ϱ� ���� ���� �̺�Ʈ ���� �ʱ�ȭ

	POSITION pos;

	GetDlgItem(IDC_BUTTON_ABORT)->EnableWindow(TRUE);
	pos = m_ctrlLocalFile.GetFirstSelectedItemPosition();
	if ( !pos ) return;

	while ( pos )
	{
		BeginWaitCursor();

		int nItem = m_ctrlLocalFile.GetNextSelectedItem( pos );
		strItem = m_ctrlLocalFile.GetItemText( nItem, 0 );
	
		CStringW strTemp =  CA2W(m_ctrlLocalFile.GetItemText( nItem, 0 ), CP_ACP);//���丮 �Ǵ� ���ϸ�
		strItem = CW2A(strTemp);
		
		remote=strItem;
		
	CFile	localFile;
	try
	{
		if (((CButton*)GetDlgItem(IDC_RADIO_BINARY))->GetCheck() == BST_CHECKED)
		{
			((CButton*)GetDlgItem(IDC_RADIO_ASCII))->SetCheck(0);
			mode = FTP_TRANSFER_TYPE_BINARY;
		}
		else
		{
			((CButton*)GetDlgItem(IDC_RADIO_BINARY))->SetCheck(0);
			mode = FTP_TRANSFER_TYPE_ASCII;
		}
		remoteFile = m_pConnection->OpenFile(remote.GetBuffer(remote.GetLength()), GENERIC_WRITE, mode);
	}
	catch (CInternetException* pEx)
	{
		TCHAR szErr[1024];
		if(pEx->GetErrorMessage(szErr, 1024)) 
		{
			AfxMessageBox(szErr, MB_OK);
		}
		else
		{
			AfxMessageBox("�� �� ���� ���� �Դϴ�.");
		}
		return;
	}
	remote.ReleaseBuffer();
	
	if(remoteFile != NULL)
	{		
		//AfxMessageBox("%d",strItem.GetLength());
		LPSTR p;
		p = strItem.GetBuffer(strItem.GetLength());

		if(localFile.Open(p, CFile::modeRead)) 
		{
			fileLength = localFile.GetLength();
			fileSize = fileLength;

			nSumOfnByteRead = 0;
	
			if(fileLength > 0) 
			{
				while(TRUE) 
				{
					if(::WaitForSingleObject(g_eventStop,0)	== WAIT_OBJECT_0)  // Ȥ�� ���� �𸣴� �̺�Ʈ�� ��ٸ�
					{
						canceled = TRUE;
						break;
					}
				
					nByteRead = localFile.Read(lpBuffer,2048); // 2048 ���谪 ����
					remoteFile->Write(lpBuffer,nByteRead);
					nSumOfnByteRead += nByteRead;
					
					//m_pConnection->PutFile(m_strLocalDirText, strPathName, FTP_TRANSFER_TYPE_BINARY, 1);
					//FindFtpFile(m_strLocalDirText);
					SetDlgItemText(IDC_STATIC_UPLOAD,"���� �̸� : " + strItem);

					CString strItemSize;
					strItemSize.Format("%ld %%", nSumOfnByteRead * 100 / fileSize);
				
					SetDlgItemText(IDC_STATIC_UPLOADSIZE, strItemSize);

					m_prsUpload.SetPos(nSumOfnByteRead * 100 / fileSize);

					if(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) 	// �ٸ� �޼����� ó���Ҽ� �ֵ���
					{
						::TranslateMessage(&message);
						::DispatchMessage(&message);
					}

					if(nSumOfnByteRead >= fileLength) break;
				}
			}
			localFile.Close();
		}
		else 
		{
			AfxMessageBox("������ ���� �� �����ϴ�."); 
			localFile.Close();
			remoteFile->Close();
			break;
		}
		strItem.ReleaseBuffer();
		remoteFile->Close();

		UpdateRemoteListCtrl();
		SetDlgItemText(IDC_STATIC_UPLOADSIZE, "");
		m_prsUpload.SetPos(0);
	}
	else 
	{
		AfxMessageBox("�������� ������ �� �� �����ϴ�."); 
	}
	
	}
	GetDlgItem(IDC_BUTTON_ABORT)->EnableWindow(FALSE);
	EndWaitCursor();
}

// ���α׷� ����
void CCFtpDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	DestroyWindow();
}
void CAboutDlg::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

// ���� ���丮 �����
void CCFtpDlg::OnButtonLmkdir() 
{
	// TODO: Add your control notification handler code here
	CTempDialog dlg;
	dlg.m_stTitle="���� ���� ���丮���� �Է��Ͻÿ�!";
	
	if (dlg.DoModal() != IDOK) return;

	_mkdir(dlg.m_strInput);
	UpdateLocalListCtrl();
}

// ���� ���� �̸� ����
void CCFtpDlg::OnButtonLrename() 
{
	// TODO: Add your control notification handler code here
	int number=m_ctrlLocalFile.GetSelectionMark();

	if(number!=-1)
	{
		CFile file;
		CTempDialog dlg;
		CString strInput;

		strInput=dlg.m_strInput;

		dlg.m_stTitle="�ٲ� ����(���丮)�̸��� �����ÿ�!";
		
		strInput=m_ctrlLocalFile.GetItemText(number, 0);
		if (strInput.GetAt(0) == '\\' ) strInput=strInput.Right(strInput.GetLength()-1);
		dlg.m_strInput=strInput;

		if (dlg.DoModal() != IDOK) return; //�����޽��� ��Ÿ���� �ʰ���.
		
		CString strNewName, strOldName;
		strNewName=dlg.m_strInput;
		strOldName=m_ctrlLocalFile.GetItemText(number, 0);

		if (strOldName.GetAt(0) == '\\' ) strOldName=strOldName.Right(strOldName.GetLength()-1);
		file.Rename(strOldName,strNewName);
		
		UpdateLocalListCtrl();
	}
	else
		MessageBox("����(���丮)�� ������ �ּ���!");
}

// ���� ���� �����
void CCFtpDlg::OnButtonLdelete() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	CString strPathName;

	int number=m_ctrlLocalFile.GetSelectionMark();
	pos = m_ctrlLocalFile.GetFirstSelectedItemPosition();

	if(number !=-1)
	{
		if(MessageBox("������ ����(���丮)�� ����ðڽ��ϱ�?","����(���丮) ����!",MB_OKCANCEL)==IDOK)
		{
		if ( !pos ) return;

		while ( pos )
		{
			int nItem = m_ctrlLocalFile.GetNextSelectedItem( pos );
			CString strItem = m_ctrlLocalFile.GetItemText( nItem, 0 );
			
			if (strItem.GetAt(0) == '\\' ) 
			{
				CString filePath=m_strLocalDirText + strItem;
				_rmdir(filePath);
			}
			else
			{
				CString filePath=m_strLocalDirText + "\\" + strItem;

				CFile file;
				file.Remove(filePath);
			}
		}
		UpdateLocalListCtrl();
		}
	}
	else
	{
		MessageBox("����(���丮)�� ������ �ּ���!");
	}
}

// ���� ������Ʈ
void CCFtpDlg::OnButtonLrefresh() 
{
	// TODO: Add your control notification handler code here
	UpdateLocalListCtrl();
}

// ����Ʈ ���丮 ����
void CCFtpDlg::OnButtonRmkdir() 
{
	// TODO: Add your control notification handler code here
	CTempDialog dlg;
	dlg.m_stTitle="���� ���� ���丮���� �Է��Ͻÿ�!";
	
	if (dlg.DoModal() != IDOK) return;

	m_pConnection->CreateDirectory(dlg.m_strInput);
	UpdateRemoteListCtrl();
}

// ����Ʈ �����̸� ����
void CCFtpDlg::OnButtonRrename() 
{
	// TODO: Add your control notification handler code here
	CString strInput;
	CString strCurr;
	int number=m_ctrlRemoteFile.GetSelectionMark();

	if(number!=-1)
	{
		CTempDialog dlg;

		strInput=dlg.m_strInput;
		dlg.m_stTitle="�ٲ� ����(���丮)�̸��� �����ÿ�!";

		strInput=m_ctrlRemoteFile.GetItemText(number, 0);
		if (strInput.GetAt(0) == '/' ) strInput=strInput.Right(strInput.GetLength()-1);
		dlg.m_strInput=strInput;
		
		if (dlg.DoModal() != IDOK) return; //�����޽��� ��Ÿ���� �ʰ���.

		CString strNewName, strOldName;
		strNewName=dlg.m_strInput;
		strOldName=m_ctrlRemoteFile.GetItemText(number, 0);
		if (strOldName.GetAt(0) == '/' ) strOldName=strOldName.Right(strOldName.GetLength()-1);

		m_pConnection->GetCurrentDirectory(strCurr);
		m_pConnection->Rename(strOldName, strCurr+strNewName);
		
		UpdateRemoteListCtrl();
	}
	else
		MessageBox("����(���丮)�� ������ �ּ���!");	
}

// ����Ʈ ���� ����
void CCFtpDlg::OnButtonRdelete() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	CString strPathName;
	CString strCurr;
	
	int number=m_ctrlRemoteFile.GetSelectionMark();
	pos = m_ctrlRemoteFile.GetFirstSelectedItemPosition();

	if(number!=-1)
	{
		if(MessageBox("������ ����(���丮)�� ����ðڽ��ϱ�?","����(���丮) ����!",MB_OKCANCEL)==IDOK)
		{
		BeginWaitCursor();
		if ( !pos ) return;

		while ( pos )
		{
			int nItem = m_ctrlRemoteFile.GetNextSelectedItem( pos );
			CString strItem = m_ctrlRemoteFile.GetItemText( nItem, 0 );

			if (strItem.GetAt(0) == '/' )
			{
				strItem=strItem.Right(strItem.GetLength()-1);						
				m_pConnection->RemoveDirectory(strItem);
			}
			else m_pConnection->Remove(strItem);
		}
		UpdateRemoteListCtrl();
		EndWaitCursor();
		}
	}
	else
	{
		MessageBox("����(���丮)�� ������ �ּ���!");
	}
}

// ����Ʈ ������Ʈ
void CCFtpDlg::OnButtonRrefresh() 
{
	// TODO: Add your control notification handler code here
	UpdateRemoteListCtrl();
}

// ��ư ����
void CCFtpDlg::InitButton()
{
	GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LRENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LDELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_UNCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RMKDIR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RRENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RDELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RREFRESH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ABORT)->EnableWindow(FALSE);

}

// ���� ���ؽ�Ʈ �޴�
void CCFtpDlg::OnRclickListLocalFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	InitLocalMenu();

	CPoint pt;
	GetCursorPos(&pt);

	POSITION pos;
	int state = 0;
	int itemCount = 0;

	pos = m_ctrlLocalFile.GetFirstSelectedItemPosition();

	if ( pos )
	{
		while ( pos )
		{
			int nItem = m_ctrlLocalFile.GetNextSelectedItem( pos );
			CString strItem = m_ctrlLocalFile.GetItemText( nItem, 0 );
			
			if ( strItem.Left(1) == "\\" ) state |= 1;
			else state |= 2;
			itemCount ++;
		}
	}

	if ( itemCount > 1 )
	{
		subMenu.EnableMenuItem( IDC_BUTTON_LRENAME, MF_GRAYED );
	}
	else if ( itemCount == 1 )
	{
		
	}
	else if ( itemCount <= 0 )
	{
		subMenu.EnableMenuItem( IDC_BUTTON_UPLOAD, MF_GRAYED );
		subMenu.EnableMenuItem( IDC_BUTTON_LRENAME, MF_GRAYED );
		subMenu.EnableMenuItem( IDC_BUTTON_LDELETE, MF_GRAYED );
	}

	// ���丮���� �������� ���...
	if ( state == 1 )
	{
		subMenu.EnableMenuItem( IDC_BUTTON_UPLOAD, MF_GRAYED );
	}

	// ���� ������ ���߿� ���丮�� ������ ���� ���� ���
	if ( state == 3 ) 
	{
		subMenu.EnableMenuItem( IDC_BUTTON_UPLOAD, MF_GRAYED );
		subMenu.EnableMenuItem( IDC_BUTTON_LRENAME, MF_GRAYED );
	}

	if ( !m_bConnected ) 
	{
		subMenu.EnableMenuItem( IDC_BUTTON_UPLOAD, MF_GRAYED );
	}
	else 
	{

	}

	subMenu.TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this );

	//itemCount = 0;
	*pResult = 0;
}

void CCFtpDlg::InitLocalMenu()
{
	subMenu.CreatePopupMenu();

	// ���ؽ�Ʈ �޴��� ����
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_UPLOAD, "���ε�" );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_LREFRESH, "���ΰ�ħ" );
	subMenu.AppendMenu( MF_SEPARATOR );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_LMKDIR, "���丮 ����" );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_LDELETE, "����" );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_LRENAME, "�̸� �ٲٱ�" );
}

// ����Ʈ ���ؽ�Ʈ �޴�
void CCFtpDlg::OnRclickListRemoteFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (m_bConnected==FALSE) return;

	InitRemoteMenu();

	CPoint pt;
	GetCursorPos(&pt);

	POSITION pos;
	int state = 0;
	int itemCount = 0;

	pos = m_ctrlRemoteFile.GetFirstSelectedItemPosition();

	if ( pos )
	{
		while ( pos )
		{
			int nItem = m_ctrlRemoteFile.GetNextSelectedItem( pos );
			CString strItem = m_ctrlRemoteFile.GetItemText( nItem, 0 );
			
			if ( strItem.Left(1) == "/" ) state |= 1;
			else state |= 2;
			itemCount ++;
		}
	}

	if ( itemCount > 1 )
	{
		subMenu.EnableMenuItem( IDC_BUTTON_RRENAME, MF_GRAYED );
	}
	else if ( itemCount == 1 )
	{
		
	}
	else if ( itemCount <= 0 )
	{
		subMenu.EnableMenuItem( IDC_BUTTON_DOWNLOAD, MF_GRAYED );
		subMenu.EnableMenuItem( IDC_BUTTON_RRENAME, MF_GRAYED );
		subMenu.EnableMenuItem( IDC_BUTTON_RDELETE, MF_GRAYED );
	}

	// ���丮���� �������� ���...
	if ( state == 1 )
	{
		subMenu.EnableMenuItem( IDC_BUTTON_DOWNLOAD, MF_GRAYED );
	}

	// ���� ������ ���߿� ���丮�� ������ ���� ���� ���
	if ( state == 3 ) 
	{
		subMenu.EnableMenuItem( IDC_BUTTON_RRENAME, MF_GRAYED );
	}

	if ( !m_bConnected ) 
	{
		subMenu.EnableMenuItem( IDC_BUTTON_DOWNLOAD, MF_GRAYED );
	}
	else 
	{
		
	}

	subMenu.TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this );
	
	*pResult = 0;
}

void CCFtpDlg::InitRemoteMenu()
{
	subMenu.CreatePopupMenu();

	// ����Ʈ ���ؽ�Ʈ �޴� ����
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_DOWNLOAD, "�ٿ�ε�" );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_RREFRESH, "���ΰ�ħ" );
	subMenu.AppendMenu( MF_SEPARATOR );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_RMKDIR, "���丮 ����" );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_RDELETE, "����" );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_RRENAME, "�̸� �ٲٱ�" );
}

// ���� ���� ������ ���ý�(�����)
void CCFtpDlg::OnItemchangedListLocalFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	InitLocalList();

	CPoint pt;
	GetCursorPos(&pt);

	POSITION pos;
	int state = 0;
	int itemCount = 0;

	CString strPathName;
	CString strItemSize;
	

	pos = m_ctrlLocalFile.GetFirstSelectedItemPosition();

	if ( pos )
	{
		while ( pos )
		{
			int nItem = m_ctrlLocalFile.GetNextSelectedItem( pos );
			CString strItem = m_ctrlLocalFile.GetItemText( nItem, 0 );
			CString strItemSize = m_ctrlLocalFile.GetItemText( nItem, 1 );

			SetDlgItemText(IDC_STATIC_UPLOAD, "���� �̸� : " + strItem);
			SetDlgItemText(IDC_STATIC_UPLOADSIZE , "���� ũ�� : " + strItemSize);
			
			if ( strItem.Left(1) == "\\" ) state |= 1;
			else state |= 2;
			itemCount ++;
		}
	}

	if ( itemCount > 1 )
	{
		GetDlgItem(IDC_BUTTON_LRENAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_LDELETE)->EnableWindow(TRUE);
	}
	else if ( itemCount == 1 )
	{
		GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_LRENAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_LDELETE)->EnableWindow(TRUE);
	}
	else if ( itemCount <= 0 )
	{
		GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_LRENAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_LDELETE)->EnableWindow(FALSE);
	}

	// ���丮���� �������� ���...
	if ( state == 1 )
	{
		GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_LRENAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_LDELETE)->EnableWindow(TRUE);
	}

	// ���� ������ ���߿� ���丮�� ������ ���� ���� ���
	if ( state == 3 ) 
	{
		GetDlgItem(IDC_BUTTON_LRENAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_LDELETE)->EnableWindow(TRUE);
	}

	if ( !m_bConnected ) 
	{
		GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE);
	}
	else 
	{

	}
	*pResult = 0;
}

// ���� ��ư ����
void CCFtpDlg::InitLocalList()
{
	GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LMKDIR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LRENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LDELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LREFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(FALSE); //���ø���Ʈ���� ����Ʈ �ٿ�ε� ����
	GetDlgItem(IDC_BUTTON_RRENAME)->EnableWindow(FALSE); //���ø���Ʈ���� ����Ʈ �����̸����� ����
	GetDlgItem(IDC_BUTTON_RDELETE)->EnableWindow(FALSE); //���ø���Ʈ���� ����Ʈ ��������� ����
}

// ����Ʈ ��ư ����
void CCFtpDlg::InitRemoteList()
{
	GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RMKDIR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_RRENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RDELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RREFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE); //����Ʈ����Ʈ���� ���� ���ε� ����
	GetDlgItem(IDC_BUTTON_LRENAME)->EnableWindow(FALSE); //����Ʈ����Ʈ���� ���� �����̸����� ����
	GetDlgItem(IDC_BUTTON_LDELETE)->EnableWindow(FALSE); //����Ʈ����Ʈ���� ���� ��������� ����
}

// ����Ʈ ���� ������ ���ý�(�����)
void CCFtpDlg::OnItemchangedListRemoteFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	InitRemoteList();

	CPoint pt;
	GetCursorPos(&pt);

	POSITION pos;
	int state = 0;
	int itemCount = 0;
	CString strItem;
	CString strItemSize;

	pos = m_ctrlRemoteFile.GetFirstSelectedItemPosition();

	if ( pos )
	{
		while ( pos )
		{
			int nItem = m_ctrlRemoteFile.GetNextSelectedItem( pos );
			strItem = m_ctrlRemoteFile.GetItemText( nItem, 0 );
			strItemSize = m_ctrlRemoteFile.GetItemText( nItem, 1 );
			
			SetDlgItemText(IDC_STATIC_DOWNLOAD, "���� �̸� : " + strItem);
			SetDlgItemText(IDC_STATIC_DOWNLOADINFO, "���� ũ�� : " + strItemSize);

			if ( strItem.Left(1) == "/" ) state |= 1;
			else state |= 2;
			itemCount ++;
		}
	}

	if ( itemCount > 1 )
	{
		GetDlgItem(IDC_BUTTON_RRENAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_RDELETE)->EnableWindow(TRUE);
	}
	else if ( itemCount == 1 )
	{
		GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_RRENAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_RDELETE)->EnableWindow(TRUE);
	}
	else if ( itemCount <= 0 )
	{
		GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RRENAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RDELETE)->EnableWindow(FALSE);
	}

	// ���丮���� �������� ���
	if ( state == 1 )
	{
		GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RRENAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_RDELETE)->EnableWindow(TRUE);
	}

	// ���� ������ ���߿� ���丮�� ������ ���� ���� ���
	if ( state == 3 ) 
	{
		GetDlgItem(IDC_BUTTON_RRENAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RDELETE)->EnableWindow(TRUE);
	}

	if ( !m_bConnected ) 
	{
		GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE);
	}
	else 
	{

	}
	*pResult = 0;
}

// �ٿ�ε� �ޱ�
void CCFtpDlg::OnButtonDownload() 
{
	// TODO: Add your control notification handler code here
	CString strPathName;
	CString strItem;
	CString strItem2;

	long	fileSize;
	
	CString local;
	CString str;
	CString remote;
	
	g_eventStop.ResetEvent();	// ���۵��� �����ϱ� ���� ���� �̺�Ʈ ���� �ʱ�ȭ

	POSITION pos;

	pos = m_ctrlRemoteFile.GetFirstSelectedItemPosition();
	if ( !pos ) return;

	int bWorking;

	while ( pos )
	{
		BeginWaitCursor();

		int nItem = m_ctrlRemoteFile.GetNextSelectedItem( pos );
		//strItem = m_ctrlRemoteFile.GetItemText( nItem, 0 );
		CStringW strTemp =  CA2W(m_ctrlRemoteFile.GetItemText( nItem, 0 ), CP_ACP);//���丮 �Ǵ� ���ϸ�
		strItem = CW2A(strTemp);

		CString strDir;
		m_pConnection->GetCurrentDirectory(strDir);

		strPathName=strDir + "/" + strItem;		
		strItem.ReleaseBuffer();
		
		bWorking = m_pFileFind->FindFile(strItem.GetBuffer(strItem.GetLength()));

		while(bWorking)
		{

			bWorking = m_pFileFind->FindNextFile();
			remote=m_pFileFind->GetFileName();
			fileSize=m_pFileFind->GetLength();
		}
		local=strItem;

		StartTime = ::GetTickCount();
		Get(local, remote, fileSize);
	}
}

// �ϳ��� ������ �޴� ��..
void CCFtpDlg::Get(CString local, CString remote, long fileSize)
{
	char	lpBuffer[2048+1];
	UINT	nByteRead;
	//DWORD	nSumOfnByteRead, fileLength;
	long	nSumOfnByteRead, fileLength;
	MSG		message;
	BOOL	canceled = FALSE;
	DWORD   mode;
	DWORD	nSpeed =0, nRemainTime = 0;
	int     nDevide;
	double	ElapsedTime = 0;
	int		nHour = 0, nMinute = 0, nSecond = 0;
	CString strItemInfo;
	CInternetFile* remoteFile;
	CFile	localFile;
	CString strItem;

	CStringW strTemp =  CA2W(local, CP_ACP);//���丮 �Ǵ� ���ϸ�
	strItem = CW2A(strTemp);

	try 
	{
		if (((CButton*)GetDlgItem(IDC_RADIO_BINARY))->GetCheck() == BST_CHECKED)
		{
			((CButton*)GetDlgItem(IDC_RADIO_ASCII))->SetCheck(0);
			mode = FTP_TRANSFER_TYPE_BINARY;
		}
		else
		{
			((CButton*)GetDlgItem(IDC_RADIO_BINARY))->SetCheck(0);
			mode = FTP_TRANSFER_TYPE_ASCII;
		}
		remoteFile=m_pConnection->OpenFile(remote.GetBuffer(remote.GetLength()), GENERIC_READ, mode);
	}

	catch (CInternetException* pEx) 
	{
		TCHAR szErr[1024];
		if(pEx->GetErrorMessage(szErr, 1024)) 
		{
			AfxMessageBox(szErr, MB_OK);
		}
		else 
		{
			AfxMessageBox("�� �� ���� ���� �Դϴ�.");
		}
		return;
	}
				
	remote.ReleaseBuffer();	

	if(remoteFile != NULL) 
	{
		if(fileSize == 0)
		{
			localFile.Close();
			remoteFile->Close();
			return;	// ����ũ�Ⱑ 0�̸� �۾��� ���� �ȴ´�
		}

		fileLength=fileSize;
			
		//CStringW strTemp =  CA2W(local, CP_UTF8);//���丮 �Ǵ� ���ϸ�
		//strItem = CW2A(strTemp);
		LPSTR p;
		p = strItem.GetBuffer(strItem.GetLength());
		if(localFile.Open(p, CFile::modeCreate|CFile::modeWrite)) 
		{

			nSumOfnByteRead = 0;				
			nByteRead = 0;

			if(fileLength > 0) 
			{
								
				while(TRUE) 
				{
					if(::WaitForSingleObject(g_eventStop,0)	== WAIT_OBJECT_0) 
					{	// Ȥ�� ���� �𸣴� �̺�Ʈ�� ��ٸ�
						canceled = TRUE;
						break;
					}
					nByteRead = remoteFile->Read(lpBuffer, 2048); // 2048 ���谪 ����
					localFile.Write(lpBuffer,nByteRead);
					nSumOfnByteRead += nByteRead;
					CurrentTime = ::GetTickCount();

					SetDlgItemText(IDC_STATIC_DOWNLOAD, "���� �̸� : " + remote);
					SetDlgItemText(IDC_STATIC_DOWNLOADINFO, "���� ũ�� : " + fileSize);
					CString strItemSize;
					strItemSize.Format("%ld %%", nSumOfnByteRead * 100 / fileSize);
	
						SetDlgItemText(IDC_STATIC_DOWNLOADINFO, strItemInfo );

					m_prsDownload.SetPos(nSumOfnByteRead * 100 / fileSize);

					if(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
					{	// �ٸ� �޼����� ó���Ҽ� �ֵ���
						::TranslateMessage(&message);
						::DispatchMessage(&message);
					}

					if(nSumOfnByteRead >= fileSize) 
					
						break;
				}
			}
			localFile.Close();
		}
		else 
		{
			AfxMessageBox("������ ���� �� �����ϴ�."); 
			localFile.Close();
			remoteFile->Close();
		}
		strItem.ReleaseBuffer();
		remoteFile->Close();

		UpdateLocalListCtrl();
		SetDlgItemText(IDC_STATIC_DOWNLOADINFO, "");
		m_prsDownload.SetPos(0);
	}
	else 
	{
		AfxMessageBox("���ÿ� ������ �� �� �����ϴ�."); 
	}
	
	EndWaitCursor();	
}

void CCFtpDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_pConnection != NULL)
	{
		m_pConnection->Close();
		delete m_pConnection;
	}
}

BOOL CCFtpDlg::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	//m_rgn.CreateRoundRectRgn(0, 0, 685, 450, 100, 100);
	SetWindowRgn((HRGN)m_rgn, TRUE);
	SetWindowText("CFtp 3.0");
	return TRUE;
}

// ���� ��ư���� ����
void CCFtpDlg::InitRoundButton()
{
	m_BtnDown.SetRoundTextColor(RGB(255, 0, 0));
	m_BtnUpload.SetRoundTextColor(RGB(255, 0, 0));
	m_BtnUnconn.SetRoundTextColor(RGB(255, 0, 0));
}

// â�� �����ϼ� �ֵ���
void CCFtpDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	DefWindowProc(WM_NCLBUTTONDOWN, HTCAPTION, 0);
    	
	CDialog::OnLButtonDown(nFlags, point);
}

void CCFtpDlg::StatusList(CString& str)
{
	((CListBox*)GetDlgItem(IDC_LIST_STATUS))->InsertString(-1, str);
	int idx = ((CListBox*)GetDlgItem(IDC_LIST_STATUS))->GetCount();
	if(idx > 100)
		((CListBox*)GetDlgItem(IDC_LIST_STATUS))->ResetContent();
	((CListBox*)GetDlgItem(IDC_LIST_STATUS))->SetCurSel(idx-1);
}


void CCFtpDlg::OnBnClickedButtonUnconnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_pConnection->Close();
	delete m_pConnection;
	m_pConnection = NULL;

	m_ctrlRemoteFile.DeleteAllItems();

	InitButton();
	UpdateLocalListCtrl();
}


//�Ͻ�����
void CCFtpDlg::OnBnClickedButtonAbort()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	g_eventStop.SetEvent();

}



void CCFtpDlg::OnBnClickedButtonResume()
{
	// TODO: Add your control notification handler code here
	CString strPathName;
	CString strItem;
	CString strItem2;

	long	localfileSize;
	long	remotefileSize;
	
	CFile	localFile;

	CString local;
	CString str;
	CString remote;
	
	MSG		message;
	BOOL	canceled = FALSE;
	CInternetFile* remoteFile;
	UINT	nByteRead;
	DWORD	fileLength, nSumOfnByteRead, mode;
	char	lpBuffer[2048+1];

	GetDlgItem(IDC_BUTTON_ABORT)->EnableWindow(TRUE);
	g_eventStop.ResetEvent();	// ���۵��� �����ϱ� ���� ���� �̺�Ʈ ���� �ʱ�ȭ

	POSITION pos;

	pos = m_ctrlLocalFile.GetFirstSelectedItemPosition();
	if ( !pos ) return;

	int bWorking;

	while ( pos )
	{
		BeginWaitCursor();

		int nItem = m_ctrlLocalFile.GetNextSelectedItem( pos );

		CStringW strTemp =  CA2W(m_ctrlLocalFile.GetItemText( nItem, 0 ), CP_ACP);//���丮 �Ǵ� ���ϸ�
		strItem = CW2A(strTemp);

		CString strDir;
		m_pConnection->GetCurrentDirectory(strDir);

		strPathName=strDir + "/" + strItem;		
		strItem.ReleaseBuffer();
		
		bWorking = m_pFileFind->FindFile(strItem.GetBuffer(strItem.GetLength()));

		while(bWorking)
		{

			bWorking = m_pFileFind->FindNextFile();
			remote=m_pFileFind->GetFileName();
			remotefileSize=m_pFileFind->GetLength();
		}
		local=strItem;

		LPSTR p;
		p = strItem.GetBuffer(strItem.GetLength());

		if(localFile.Open(p, CFile::modeRead)) 
		{
			fileLength = localFile.GetLength();
			localfileSize = fileLength;

		}
		try
		{
			if (((CButton*)GetDlgItem(IDC_RADIO_BINARY))->GetCheck() == BST_CHECKED)
		{
			((CButton*)GetDlgItem(IDC_RADIO_ASCII))->SetCheck(0);
			mode = FTP_TRANSFER_TYPE_BINARY;
		}
		else
		{
			((CButton*)GetDlgItem(IDC_RADIO_BINARY))->SetCheck(0);
			mode = FTP_TRANSFER_TYPE_ASCII;
		}
			remoteFile = m_pConnection->OpenFile(remote.GetBuffer(remote.GetLength()), GENERIC_READ, mode);
		}
		catch (CInternetException* pEx)
		{
			TCHAR szErr[1024];
			if(pEx->GetErrorMessage(szErr, 1024)) 
			{
				AfxMessageBox(szErr, MB_OK);
			}
			else
			{
				AfxMessageBox("�� �� ���� ���� �Դϴ�.");
			}
			return;
		}

		

		LONGLONG lOffset = remotefileSize;
		localFile.Seek(lOffset, SEEK_SET);
		remoteFile->Seek(lOffset, CFile::begin);
		nSumOfnByteRead=0;
		if(fileLength > 0) 
		{
			while(TRUE)
			{
				if(::WaitForSingleObject(g_eventStop,0)	== WAIT_OBJECT_0)  // Ȥ�� ���� �𸣴� �̺�Ʈ�� ��ٸ�
				{
					canceled = TRUE;
					break;

				}

				nByteRead = localFile.Read(lpBuffer,2048); // 2048 ���谪 ����
				remoteFile->Write(lpBuffer,nByteRead);
				nSumOfnByteRead += nByteRead;

				SetDlgItemText(IDC_STATIC_UPLOAD,"���� �̸� : " + local);

				CString strItemSize;
				//strItemSize.Format("%ld %%", (nSumOfnByteRead * 100) /  (localfileSize - remotefileSize));

				SetDlgItemText(IDC_STATIC_UPLOADSIZE, strItemSize);

				m_prsUpload.SetPos(nSumOfnByteRead * 100 / (localfileSize - remotefileSize));
				if(nSumOfnByteRead >= fileLength) break;

				
				if(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) 	// �ٸ� �޼����� ó���Ҽ� �ֵ���
				{
					::TranslateMessage(&message);
					::DispatchMessage(&message);
				}
				if(nSumOfnByteRead >= fileLength) break;
			}
		}
		else 
		{
			AfxMessageBox("������ ���� �� �����ϴ�."); 
			localFile.Close();
			remoteFile->Close();
			break;
		}
		localFile.Close();

		strItem.ReleaseBuffer();
		remoteFile->Close();

		UpdateRemoteListCtrl();
		SetDlgItemText(IDC_STATIC_UPLOADSIZE, "");
		m_prsUpload.SetPos(0);
	}

	EndWaitCursor();
}
