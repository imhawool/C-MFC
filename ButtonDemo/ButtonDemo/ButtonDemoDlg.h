
// ButtonDemoDlg.h : ��� ����
//

#pragma once


// CButtonDemoDlg ��ȭ ����
class CButtonDemoDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CButtonDemoDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BUTTONDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	BOOL m_bAuto;
	BOOL m_bCheck;
	BOOL m_bSystem;
	afx_msg void OnBnClickedCheckAuto();
	int m_nOS;
};
