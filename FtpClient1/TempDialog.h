#if !defined(AFX_TEMPDIALOG_H__AD9FA4A5_93AD_4A39_BCAE_DC21369C5929__INCLUDED_)
#define AFX_TEMPDIALOG_H__AD9FA4A5_93AD_4A39_BCAE_DC21369C5929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TempDialog.h : ��� ����

// CTempDialog ��ȭ ����

class CTempDialog : public CDialog
{
// �����Դϴ�.
public:
	CTempDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.

	enum { IDD = IDD_DIALOG_TEMP };
	CString	m_strInput;
	CString	m_stTitle;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:

	// ������ �޽��� �� �Լ�
	DECLARE_MESSAGE_MAP()
};


#endif
