// ConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CFtp.h"
#include "ConnectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectDlg::IDD, pParent)
{
	m_bAnonymous = FALSE;
	m_strPassword = _T("");
	m_strAddress = _T("");
	m_strName = _T("");
	m_strPort = _T("");
	m_bOpen=true;
}

void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_Ok);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDC_COMBO_NAME, m_ctrlName);
	DDX_Control(pDX, IDC_COMBO_ADDRESS, m_ctrlAddress);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_ctrlPassword);
	DDX_Control(pDX, IDC_COMBO_PORT, m_ctrlPort);
	DDX_Check(pDX, IDC_CHECK_ANONYMOUS, m_bAnonymous);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_CBString(pDX, IDC_COMBO_ADDRESS, m_strAddress);
	DDX_CBString(pDX, IDC_COMBO_NAME, m_strName);
	DDX_CBString(pDX, IDC_COMBO_PORT, m_strPort);

}

BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_ANONYMOUS, OnCheckAnonymous)
END_MESSAGE_MAP()

// 익명으로 연결
void CConnectDlg::OnCheckAnonymous() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if(m_bAnonymous)
	{
		m_strPassword.Empty();	
		m_strName.Empty();			
		UpdateData(FALSE);
		
		m_ctrlName.EnableWindow(FALSE);
		m_ctrlPassword.EnableWindow(FALSE);
	}
	else
	{
		m_ctrlName.EnableWindow();
		m_ctrlPassword.EnableWindow();
		m_ctrlPort.EnableWindow();
	}
}

BOOL CConnectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow(CWnd::GetDesktopWindow());
     
	CWinApp *pApp = AfxGetApp();
	int i;
	CString strName, strAddress, strPort;
	//레지스트리 삭제
	/*
	HKEY hkey	= NULL;
	BOOL bRet	= FALSE;
	TCHAR tszSubKey[5] = {0};
	TCHAR tszKey[5] = {0};

	_tcscpy( tszSubKey, _T( "CFtp22" ) );            
	_tcscpy( tszKey, _T( "CFtp2" ) );   

	LONG lRet = ::RegOpenKey( HKEY_LOCAL_MACHINE, tszKey, &hkey );

	if( lRet == ERROR_SUCCESS )
	{
		lRet = ::RegDeleteKey( hkey, tszKey );

		if( lRet == ERROR_SUCCESS )
			bRet = TRUE;

		::RegCloseKey( hkey );
	}
	*/
	// 레지스트리로 부터 값을 읽어 온다
	for ( i = 0 ; i < 10 ; i++ )
	{
		strName.Format("이름(FTP)%d",i);
		strAddress.Format("주소(FTP)%d",i);
		strPort.Format("포트(FTP)%d",i);
	
		m_strPreName[i] = pApp->GetProfileString("CFtp",strName);
		m_strPreAddress[i] = pApp->GetProfileString("CFtp",strAddress);
		m_strPrePort[i] = pApp->GetProfileString("CFtp",strPort);

		if(!m_strPreName[i].IsEmpty())
			m_ctrlName.AddString(m_strPreName[i]);

		if(!m_strPreAddress[i].IsEmpty())
			m_ctrlAddress.AddString(m_strPreAddress[i]);

		if(!m_strPrePort[i].IsEmpty())
			m_ctrlPort.AddString(m_strPrePort[i]);
	}
	m_ctrlName.SetCurSel(0);
	m_ctrlAddress.SetCurSel(0);
	m_ctrlPort.SetCurSel(0);

	return TRUE;  
}

void CConnectDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	CWinApp *pApp = AfxGetApp();
	BOOL bUpdate = TRUE;
	int i;

	//같은게 있으면 Registery에 추가 안함
	for ( i = 0 ; i < 10 ; i++ ) {
		if(m_strAddress == m_strPreAddress[i])
			bUpdate = FALSE;
	}

	// 최근 접속한 열개의 주소를 레지스트리에 기억
	CString strName, strAddress, strPort;
	if( bUpdate ) {
		strName.Format("이름(FTP)0");
		strAddress.Format("주소(FTP)0");
		strPort.Format("포트(FTP)0");
		pApp->WriteProfileString("CFtp",strName,m_strName);
		pApp->WriteProfileString("CFtp",strAddress,m_strAddress);
		pApp->WriteProfileString("CFtp",strPort,m_strPort);
		
		for ( i = 0 ; i < 9 ; i++ ) {
			strName.Format("이름(FTP)%d",i+1);
			strAddress.Format("주소(FTP)%d",i+1);
			strPort.Format("포트(FTP)%d",i+1);
			pApp->WriteProfileString("CFtp",strName,m_strPreName[i]);
			pApp->WriteProfileString("CFtp",strAddress,m_strPreAddress[i]);
			pApp->WriteProfileString("CFtp",strPort,m_strPrePort[i]);
		}
		
	}	
	CDialog::OnOK();
}

void CConnectDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}

BOOL CConnectDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	// 리턴키를 눌렀을 경우 자동으로 다음으로 내려옴
	if ((pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN))
	{
		if (GetDlgItem(IDOK)->m_hWnd != pMsg->hwnd) pMsg->wParam=VK_TAB;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}
