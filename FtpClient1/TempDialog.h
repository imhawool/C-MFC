#if !defined(AFX_TEMPDIALOG_H__AD9FA4A5_93AD_4A39_BCAE_DC21369C5929__INCLUDED_)
#define AFX_TEMPDIALOG_H__AD9FA4A5_93AD_4A39_BCAE_DC21369C5929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TempDialog.h : 헤더 파일

// CTempDialog 대화 상자

class CTempDialog : public CDialog
{
// 생성입니다.
public:
	CTempDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.

// 대화 상자 데이터입니다.

	enum { IDD = IDD_DIALOG_TEMP };
	CString	m_strInput;
	CString	m_stTitle;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.


// 구현입니다.
protected:

	// 생성된 메시지 맵 함수
	DECLARE_MESSAGE_MAP()
};


#endif
