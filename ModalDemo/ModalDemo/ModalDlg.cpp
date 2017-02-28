// ModalDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ModalDemo.h"
#include "ModalDlg.h"
#include "afxdialogex.h"


// CModalDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CModalDlg, CDialogEx)

CModalDlg::CModalDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModalDlg::IDD, pParent)
{

}

CModalDlg::~CModalDlg()
{
}

void CModalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModalDlg, CDialogEx)
END_MESSAGE_MAP()


// CModalDlg 메시지 처리기입니다.
