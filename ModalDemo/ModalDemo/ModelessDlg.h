#pragma once


// CModelessDlg 대화 상자입니다.

class CModelessDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelessDlg)

public:
	CModelessDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CModelessDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MODELESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
