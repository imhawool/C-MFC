// ModelessDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ModalDemo.h"
#include "ModelessDlg.h"
#include "afxdialogex.h"


// CModelessDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CModelessDlg, CDialogEx)

CModelessDlg::CModelessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModelessDlg::IDD, pParent)
{

}

CModelessDlg::~CModelessDlg()
{
}

void CModelessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelessDlg, CDialogEx)
END_MESSAGE_MAP()


// CModelessDlg 메시지 처리기입니다.
