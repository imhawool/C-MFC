
// LogonDemoDlg.h : ��� ����
//

#pragma once


// CLogonDemoDlg ��ȭ ����
class CLogonDemoDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CLogonDemoDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LOGONDEMO_DIALOG };

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
	// �α׿�ID
	CString m_strID;
	// �α׿�PW
	CString m_strPassword;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedMfclink1();
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
};
