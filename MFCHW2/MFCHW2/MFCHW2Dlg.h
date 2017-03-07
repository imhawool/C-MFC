
// MFCHW2Dlg.h : 헤더 파일
//

#pragma once


// CMFCHW2Dlg 대화 상자
class CMFCHW2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCHW2Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MFCHW2_DIALOG };

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

	CString m_Edit1;
	CString m_Edit2;
	CString m_Edit3;
	CString m_Edit4;
	CString m_Edit5;
	CString m_Edit6;
	CString m_Edit7;
	CString m_Edit8;
	CString m_Edit9;
	CString m_Edit10;

	afx_msg void OnBnClickedButtonCreatedata();
	afx_msg void OnBnClickedButtonSort();
};
