// ModalDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ModalDemo.h"
#include "ModalDlg.h"
#include "afxdialogex.h"


// CModalDlg ��ȭ �����Դϴ�.

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


// CModalDlg �޽��� ó�����Դϴ�.
