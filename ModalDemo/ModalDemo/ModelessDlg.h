#pragma once


// CModelessDlg ��ȭ �����Դϴ�.

class CModelessDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelessDlg)

public:
	CModelessDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CModelessDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_MODELESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
