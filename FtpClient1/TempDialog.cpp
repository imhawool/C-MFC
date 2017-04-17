// TempDialog.cpp : implementation file
//
#include "stdafx.h"
#include "CFtp.h"
#include "TempDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CTempDialog 대화상자


CTempDialog::CTempDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTempDialog::IDD, pParent)
{
	m_strInput = _T("");
	m_stTitle = _T("");
}


void CTempDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_strInput);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_stTitle);
}


BEGIN_MESSAGE_MAP(CTempDialog, CDialog)
END_MESSAGE_MAP()

// CTempDialog 메시지 처리기