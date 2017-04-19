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
#include <afxmt.h>			// 이벤트 처리할려고...

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

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };
	CRoundButton	m_Ok;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);     // DDX/DDV 지원입니다.

// 구현입니다.
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

// CCFtpDlg 대화 상자

CEvent g_eventStop;	// 작업도중 중지하기위해 쓰는 이벤트변수 

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

// CCFtpDlg 메시지 처리기

BOOL CCFtpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	
	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CenterWindow(CWnd::GetDesktopWindow());

	InitRoundButton(); // 라운드 버튼 설정
	InitButton(); // 버튼 초기화
	InsertColumn();	// 컬럼 설정
	UpdateLocalListCtrl(); //로컬 리스트 업데이트

	CButton* pCheck = (CButton*)GetDlgItem(IDC_RADIO_BINARY); //라디오 버튼(Binary로 초기화)
	pCheck->SetCheck(1);
	CButton* pCheck1 = (CButton*)GetDlgItem(IDC_RADIO_PASSIVE); //라디오 버튼(PASSIVE로 초기화)
	pCheck1->SetCheck(1);
	return TRUE; // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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


// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.


void CCFtpDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);  // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
HCURSOR CCFtpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// 컬럼 설정
void CCFtpDlg::InsertColumn()
{
	CRect rect;
	m_ctrlLocalFile.GetClientRect(&rect);
	m_ctrlLocalFile.InsertColumn(0,"파일명",LVCFMT_LEFT,120);
	m_ctrlLocalFile.InsertColumn(1,"크기",LVCFMT_RIGHT,60);
	m_ctrlLocalFile.InsertColumn(2,"날짜",LVCFMT_LEFT,95);

	m_ctrlRemoteFile.GetClientRect(&rect);
	m_ctrlRemoteFile.InsertColumn(0,"파일명",LVCFMT_LEFT,120);
	m_ctrlRemoteFile.InsertColumn(1,"크기",LVCFMT_RIGHT,60);
	m_ctrlRemoteFile.InsertColumn(2,"날짜",LVCFMT_LEFT,95);

}

// 내 컴퓨터 파일 업데이트
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

		// 로컬 리스트 컨트롤에 그림 설정
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

// 서버쪽 파일 업데이트
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

		CStringW strTemp =  CA2W(m_pFileFind->GetFileName(), CP_UTF8);//디렉토리 또는 파일명
		str = CW2A(strTemp);

		if (str=="..") bDir=TRUE; //상위디렉토리 예외처리
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
		// 리모트 리스트 컨트롤에 그림 설정
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
	CStringW strTemp =  CA2W(strItem, CP_UTF8);//디렉토리 또는 파일명
	m_strRemoteDirText = CW2A(strTemp);

	UpdateData(FALSE);
}

// 연걸 버튼
void CCFtpDlg::OnButtonConnect() 
{
	BOOL mode;
	DWORD dwValue = 10000;
	// TODO: Add your control notification handler code here
	if(m_pConnection !=NULL)
	{
		if (AfxMessageBox("기존의 연결을 끊으시겠습니까?", MB_YESNO|MB_ICONQUESTION)==IDYES)
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

	//time-out 설정
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
		AfxMessageBox("연결이 안됩니다",MB_OK);
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

// 로컬 디렉토리 변경
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

// 리모트 디렉토리 변경
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
			AfxMessageBox("디렉토리 이동이 불가능함니다.");
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

// 파일 업로드
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
	
	g_eventStop.ResetEvent();	// 전송도중 중지하기 위해 쓰는 이벤트 변수 초기화

	POSITION pos;

	GetDlgItem(IDC_BUTTON_ABORT)->EnableWindow(TRUE);
	pos = m_ctrlLocalFile.GetFirstSelectedItemPosition();
	if ( !pos ) return;

	while ( pos )
	{
		BeginWaitCursor();

		int nItem = m_ctrlLocalFile.GetNextSelectedItem( pos );
		strItem = m_ctrlLocalFile.GetItemText( nItem, 0 );
	
		CStringW strTemp =  CA2W(m_ctrlLocalFile.GetItemText( nItem, 0 ), CP_ACP);//디렉토리 또는 파일명
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
			AfxMessageBox("알 수 없는 문제 입니다.");
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
					if(::WaitForSingleObject(g_eventStop,0)	== WAIT_OBJECT_0)  // 혹시 올지 모르는 이벤트를 기다림
					{
						canceled = TRUE;
						break;
					}
				
					nByteRead = localFile.Read(lpBuffer,2048); // 2048 실험값 설정
					remoteFile->Write(lpBuffer,nByteRead);
					nSumOfnByteRead += nByteRead;
					
					//m_pConnection->PutFile(m_strLocalDirText, strPathName, FTP_TRANSFER_TYPE_BINARY, 1);
					//FindFtpFile(m_strLocalDirText);
					SetDlgItemText(IDC_STATIC_UPLOAD,"파일 이름 : " + strItem);

					CString strItemSize;
					strItemSize.Format("%ld %%", nSumOfnByteRead * 100 / fileSize);
				
					SetDlgItemText(IDC_STATIC_UPLOADSIZE, strItemSize);

					m_prsUpload.SetPos(nSumOfnByteRead * 100 / fileSize);

					if(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) 	// 다른 메세지도 처리할수 있도록
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
			AfxMessageBox("파일을 읽을 수 없습니다."); 
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
		AfxMessageBox("원격지에 파일을 쓸 수 없습니다."); 
	}
	
	}
	GetDlgItem(IDC_BUTTON_ABORT)->EnableWindow(FALSE);
	EndWaitCursor();
}

// 프로그램 종료
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

// 로컬 디렉토리 만들기
void CCFtpDlg::OnButtonLmkdir() 
{
	// TODO: Add your control notification handler code here
	CTempDialog dlg;
	dlg.m_stTitle="새로 만들 디렉토리명을 입력하시오!";
	
	if (dlg.DoModal() != IDOK) return;

	_mkdir(dlg.m_strInput);
	UpdateLocalListCtrl();
}

// 로컬 파일 이름 변경
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

		dlg.m_stTitle="바꿀 파일(디렉토리)이름을 넣으시오!";
		
		strInput=m_ctrlLocalFile.GetItemText(number, 0);
		if (strInput.GetAt(0) == '\\' ) strInput=strInput.Right(strInput.GetLength()-1);
		dlg.m_strInput=strInput;

		if (dlg.DoModal() != IDOK) return; //에러메시지 나타나지 않게함.
		
		CString strNewName, strOldName;
		strNewName=dlg.m_strInput;
		strOldName=m_ctrlLocalFile.GetItemText(number, 0);

		if (strOldName.GetAt(0) == '\\' ) strOldName=strOldName.Right(strOldName.GetLength()-1);
		file.Rename(strOldName,strNewName);
		
		UpdateLocalListCtrl();
	}
	else
		MessageBox("파일(디렉토리)을 선택해 주세요!");
}

// 로컬 파일 지우기
void CCFtpDlg::OnButtonLdelete() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	CString strPathName;

	int number=m_ctrlLocalFile.GetSelectionMark();
	pos = m_ctrlLocalFile.GetFirstSelectedItemPosition();

	if(number !=-1)
	{
		if(MessageBox("선택한 파일(디렉토리)을 지우시겠습니까?","파일(디렉토리) 삭제!",MB_OKCANCEL)==IDOK)
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
		MessageBox("파일(디렉토리)을 선택해 주세요!");
	}
}

// 로컬 업데이트
void CCFtpDlg::OnButtonLrefresh() 
{
	// TODO: Add your control notification handler code here
	UpdateLocalListCtrl();
}

// 리모트 디렉토리 생성
void CCFtpDlg::OnButtonRmkdir() 
{
	// TODO: Add your control notification handler code here
	CTempDialog dlg;
	dlg.m_stTitle="새로 만들 디렉토리명을 입력하시오!";
	
	if (dlg.DoModal() != IDOK) return;

	m_pConnection->CreateDirectory(dlg.m_strInput);
	UpdateRemoteListCtrl();
}

// 리모트 파일이름 변경
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
		dlg.m_stTitle="바꿀 파일(디렉토리)이름을 넣으시오!";

		strInput=m_ctrlRemoteFile.GetItemText(number, 0);
		if (strInput.GetAt(0) == '/' ) strInput=strInput.Right(strInput.GetLength()-1);
		dlg.m_strInput=strInput;
		
		if (dlg.DoModal() != IDOK) return; //에러메시지 나타나지 않게함.

		CString strNewName, strOldName;
		strNewName=dlg.m_strInput;
		strOldName=m_ctrlRemoteFile.GetItemText(number, 0);
		if (strOldName.GetAt(0) == '/' ) strOldName=strOldName.Right(strOldName.GetLength()-1);

		m_pConnection->GetCurrentDirectory(strCurr);
		m_pConnection->Rename(strOldName, strCurr+strNewName);
		
		UpdateRemoteListCtrl();
	}
	else
		MessageBox("파일(디렉토리)을 선택해 주세요!");	
}

// 리모트 파일 삭제
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
		if(MessageBox("선택한 파일(디렉토리)을 지우시겠습니까?","파일(디렉토리) 삭제!",MB_OKCANCEL)==IDOK)
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
		MessageBox("파일(디렉토리)을 선택해 주세요!");
	}
}

// 리모트 업데이트
void CCFtpDlg::OnButtonRrefresh() 
{
	// TODO: Add your control notification handler code here
	UpdateRemoteListCtrl();
}

// 버튼 설정
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

// 로컬 컨텍스트 메뉴
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

	// 디렉토리만을 선택했을 경우...
	if ( state == 1 )
	{
		subMenu.EnableMenuItem( IDC_BUTTON_UPLOAD, MF_GRAYED );
	}

	// 다중 선택한 것중에 디렉토리와 파일이 섞여 있을 경우
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

	// 컨텍스트 메뉴를 설정
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_UPLOAD, "업로드" );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_LREFRESH, "새로고침" );
	subMenu.AppendMenu( MF_SEPARATOR );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_LMKDIR, "디렉토리 생성" );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_LDELETE, "삭제" );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_LRENAME, "이름 바꾸기" );
}

// 리모트 컨텍스트 메뉴
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

	// 디렉토리만을 선택했을 경우...
	if ( state == 1 )
	{
		subMenu.EnableMenuItem( IDC_BUTTON_DOWNLOAD, MF_GRAYED );
	}

	// 다중 선택한 것중에 디렉토리와 파일이 섞여 있을 경우
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

	// 리모트 컨텍스트 메뉴 설정
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_DOWNLOAD, "다운로드" );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_RREFRESH, "새로고침" );
	subMenu.AppendMenu( MF_SEPARATOR );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_RMKDIR, "디렉토리 생성" );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_RDELETE, "삭제" );
	subMenu.AppendMenu( MF_STRING, IDC_BUTTON_RRENAME, "이름 바꾸기" );
}

// 로컬 파일 여러개 선택시(변경시)
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

			SetDlgItemText(IDC_STATIC_UPLOAD, "파일 이름 : " + strItem);
			SetDlgItemText(IDC_STATIC_UPLOADSIZE , "파일 크기 : " + strItemSize);
			
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

	// 디렉토리만을 선택했을 경우...
	if ( state == 1 )
	{
		GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_LRENAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_LDELETE)->EnableWindow(TRUE);
	}

	// 다중 선택한 것중에 디렉토리와 파일이 섞여 있을 경우
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

// 로컬 버튼 설정
void CCFtpDlg::InitLocalList()
{
	GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LMKDIR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LRENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LDELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LREFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(FALSE); //로컬리스트에서 리모트 다운로드 금지
	GetDlgItem(IDC_BUTTON_RRENAME)->EnableWindow(FALSE); //로컬리스트에서 리모트 파일이름변경 금지
	GetDlgItem(IDC_BUTTON_RDELETE)->EnableWindow(FALSE); //로컬리스트에서 리모트 파일지우기 금지
}

// 리모트 버튼 설정
void CCFtpDlg::InitRemoteList()
{
	GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RMKDIR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_RRENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RDELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RREFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE); //리모트리스트에서 로컬 업로드 금지
	GetDlgItem(IDC_BUTTON_LRENAME)->EnableWindow(FALSE); //리모트리스트에서 로컬 파일이름변경 금지
	GetDlgItem(IDC_BUTTON_LDELETE)->EnableWindow(FALSE); //리모트리스트에서 로컬 파일지우기 금지
}

// 리모트 파일 여러개 선택시(변경시)
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
			
			SetDlgItemText(IDC_STATIC_DOWNLOAD, "파일 이름 : " + strItem);
			SetDlgItemText(IDC_STATIC_DOWNLOADINFO, "파일 크기 : " + strItemSize);

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

	// 디렉토리만을 선택했을 경우
	if ( state == 1 )
	{
		GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RRENAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_RDELETE)->EnableWindow(TRUE);
	}

	// 다중 선택한 것중에 디렉토리와 파일이 섞여 있을 경우
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

// 다운로드 받기
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
	
	g_eventStop.ResetEvent();	// 전송도중 중지하기 위해 쓰는 이벤트 변수 초기화

	POSITION pos;

	pos = m_ctrlRemoteFile.GetFirstSelectedItemPosition();
	if ( !pos ) return;

	int bWorking;

	while ( pos )
	{
		BeginWaitCursor();

		int nItem = m_ctrlRemoteFile.GetNextSelectedItem( pos );
		//strItem = m_ctrlRemoteFile.GetItemText( nItem, 0 );
		CStringW strTemp =  CA2W(m_ctrlRemoteFile.GetItemText( nItem, 0 ), CP_ACP);//디렉토리 또는 파일명
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

// 하나의 파일을 받는 중..
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

	CStringW strTemp =  CA2W(local, CP_ACP);//디렉토리 또는 파일명
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
			AfxMessageBox("알 수 없는 문제 입니다.");
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
			return;	// 파일크기가 0이면 작업을 하지 안는다
		}

		fileLength=fileSize;
			
		//CStringW strTemp =  CA2W(local, CP_UTF8);//디렉토리 또는 파일명
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
					{	// 혹시 올지 모르는 이벤트를 기다림
						canceled = TRUE;
						break;
					}
					nByteRead = remoteFile->Read(lpBuffer, 2048); // 2048 실험값 설정
					localFile.Write(lpBuffer,nByteRead);
					nSumOfnByteRead += nByteRead;
					CurrentTime = ::GetTickCount();

					SetDlgItemText(IDC_STATIC_DOWNLOAD, "파일 이름 : " + remote);
					SetDlgItemText(IDC_STATIC_DOWNLOADINFO, "파일 크기 : " + fileSize);
					CString strItemSize;
					strItemSize.Format("%ld %%", nSumOfnByteRead * 100 / fileSize);
	
						SetDlgItemText(IDC_STATIC_DOWNLOADINFO, strItemInfo );

					m_prsDownload.SetPos(nSumOfnByteRead * 100 / fileSize);

					if(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
					{	// 다른 메세지도 처리할수 있도록
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
			AfxMessageBox("파일을 읽을 수 없읍니다."); 
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
		AfxMessageBox("로컬에 파일을 쓸 수 없습니다."); 
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

// 라운드 버튼으로 설정
void CCFtpDlg::InitRoundButton()
{
	m_BtnDown.SetRoundTextColor(RGB(255, 0, 0));
	m_BtnUpload.SetRoundTextColor(RGB(255, 0, 0));
	m_BtnUnconn.SetRoundTextColor(RGB(255, 0, 0));
}

// 창을 움직일수 있도록
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pConnection->Close();
	delete m_pConnection;
	m_pConnection = NULL;

	m_ctrlRemoteFile.DeleteAllItems();

	InitButton();
	UpdateLocalListCtrl();
}


//일시중지
void CCFtpDlg::OnBnClickedButtonAbort()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	g_eventStop.ResetEvent();	// 전송도중 중지하기 위해 쓰는 이벤트 변수 초기화

	POSITION pos;

	pos = m_ctrlLocalFile.GetFirstSelectedItemPosition();
	if ( !pos ) return;

	int bWorking;

	while ( pos )
	{
		BeginWaitCursor();

		int nItem = m_ctrlLocalFile.GetNextSelectedItem( pos );

		CStringW strTemp =  CA2W(m_ctrlLocalFile.GetItemText( nItem, 0 ), CP_ACP);//디렉토리 또는 파일명
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
				AfxMessageBox("알 수 없는 문제 입니다.");
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
				if(::WaitForSingleObject(g_eventStop,0)	== WAIT_OBJECT_0)  // 혹시 올지 모르는 이벤트를 기다림
				{
					canceled = TRUE;
					break;

				}

				nByteRead = localFile.Read(lpBuffer,2048); // 2048 실험값 설정
				remoteFile->Write(lpBuffer,nByteRead);
				nSumOfnByteRead += nByteRead;

				SetDlgItemText(IDC_STATIC_UPLOAD,"파일 이름 : " + local);

				CString strItemSize;
				//strItemSize.Format("%ld %%", (nSumOfnByteRead * 100) /  (localfileSize - remotefileSize));

				SetDlgItemText(IDC_STATIC_UPLOADSIZE, strItemSize);

				m_prsUpload.SetPos(nSumOfnByteRead * 100 / (localfileSize - remotefileSize));
				if(nSumOfnByteRead >= fileLength) break;

				
				if(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) 	// 다른 메세지도 처리할수 있도록
				{
					::TranslateMessage(&message);
					::DispatchMessage(&message);
				}
				if(nSumOfnByteRead >= fileLength) break;
			}
		}
		else 
		{
			AfxMessageBox("파일을 읽을 수 없습니다."); 
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
