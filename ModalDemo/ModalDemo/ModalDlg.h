#pragma once


// CModalDlg ��ȭ �����Դϴ�.

class CModalDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModalDlg)

public:
	CModalDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CModalDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_MODAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
