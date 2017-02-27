
// ListComboDemoDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CListComboDemoDlg 대화 상자
class CListComboDemoDlg : public CDialogEx
{
// 생성입니다.
public:
	CListComboDemoDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LISTCOMBODEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_List;
	CString m_strInput;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonInsertstring();
	afx_msg void OnBnClickedButtonAddstring();
	afx_msg void OnBnClickedButtonFind();
	afx_msg void OnBnClickedButtonFindexact();
	CString m_strSelected;
	afx_msg void OnLbnSelchangeList1();
	CComboBox m_Combo_Address;
	CString m_strAddress;

	afx_msg void OnBnClickedButtonAddaddress();
};
