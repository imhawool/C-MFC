
// MFCHW2Dlg.h : ��� ����
//

#pragma once


// CMFCHW2Dlg ��ȭ ����
class CMFCHW2Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMFCHW2Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MFCHW2_DIALOG };

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
