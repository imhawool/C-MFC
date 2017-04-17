#if !defined(AFX_CONNECTDLG_H__41F7B6F6_18B9_4EA7_B75B_053C2A68A737__INCLUDED_)
#define AFX_CONNECTDLG_H__41F7B6F6_18B9_4EA7_B75B_053C2A68A737__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 
// ConnectDlg.h : 헤더 파일
//
/////////////////////////////////////////////////////////////////////////////
// CConnectDlg 대화 상자

#include "RoundButton.h"
#include "afxwin.h"

class CConnectDlg : public CDialog
{
// 생성입니다.
public:
	bool         m_bOpen;
     
	CConnectDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CONNECT };
	CRoundButton	m_Ok;
	CRoundButton	m_Cancel;
	CComboBox	m_ctrlName;
	CComboBox	m_ctrlAddress;
	CComboBox m_ctrlPort;
	CEdit	m_ctrlPassword;
	BOOL	m_bAnonymous;
	CString	m_strPassword;
	CString	m_strAddress;
	CString	m_strName;
	CString	m_strPort;

	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);   // DDX/DDV 지원입니다.


// 구현입니다.
protected:
	CString m_strPreName[10];
	CString m_strPreAddress[10];
	CString m_strPrePort[10];
	// 생성된 메시지 맵 함수

	afx_msg void OnCheckAnonymous();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
public:
	
};


#endif 

