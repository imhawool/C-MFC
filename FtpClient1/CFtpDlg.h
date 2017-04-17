// CFtpDlg.h : 헤더 파일
//

#if !defined(AFX_CFTPDLG_H__9E5682E5_5EF2_4D83_9DDB_68A99A74D62C__INCLUDED_)
#define AFX_CFTPDLG_H__9E5682E5_5EF2_4D83_9DDB_68A99A74D62C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

// CCFtpDlg 대화 상자

#include <afxinet.h>	//ftp 를 위해 추가해야됨
#include "RoundButton.h"
#include "CallbackInternetSession.h"
#include "afxwin.h"


class CCFtpDlg : public CDialog
{
// 생성입니다.
public:
	void StatusList(CString& str);
	void InitRoundButton();
	void Get(CString local, CString remote, long fileSize);
	void ResumePut(CString local, CString remote, long localfileSize, long remotefileSize);
	void InitRemoteList();
	void InitLocalList();
	void InitRemoteMenu();
	void InitLocalMenu();
	void TrueButton();
	void InitButton();

	bool m_bConnected;

	bool          m_bOpen;
     
	void UpdateRemoteListCtrl();
	void UpdateLocalListCtrl();
	void InsertColumn();

	CRgn m_rgn;

	CCFtpDlg(CWnd* pParent = NULL);  // 표준 생성자입니다.
private:
	HANDLE hCloseEvent;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CFTP_DIALOG };
	CRoundButton    m_BtnAbort;
	CRoundButton    m_BtnLocRefresh; 
	CRoundButton	m_BtnReRefresh;
	CRoundButton	m_BtnUpload;
	CRoundButton	m_BtnDown;
	CRoundButton	m_BtnAbout;
	CRoundButton	m_BtnExit;
	CRoundButton	m_BtnConn;
	CRoundButton	m_BtnUnconn;
	CProgressCtrl	m_prsUpload;
	CProgressCtrl	m_prsDownload;
	CListCtrl	m_ctrlRemoteFile;
	CListCtrl	m_ctrlLocalFile;
	CString	m_strLocalDirText;
	CString	m_strRemoteDirText;
	CString	m_strUpload;
	CString	m_strDownload;
	
	// ClassWizard generated virtual function overrides

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	CImageList  imgList;
	DWORD StartTime, CurrentTime;

	CCallbackInternetSession m_Session;
	CFtpConnection *m_pConnection;
	CFtpFileFind *m_pFileFind;
	CFtpFileFind* ftpFind;

	CMenu subMenu;
	
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonConnect();
	afx_msg void OnDblclkListLocalFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListRemoteFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonUpload();
	afx_msg void OnButtonDownload();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonAbout();
	afx_msg void OnButtonLmkdir();
	afx_msg void OnButtonLrefresh();
	afx_msg void OnButtonLrename();
	afx_msg void OnButtonLdelete();
	afx_msg void OnButtonRmkdir();
	afx_msg void OnButtonRrename();
	afx_msg void OnButtonRdelete();
	afx_msg void OnButtonRrefresh();
	afx_msg void OnRclickListLocalFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListRemoteFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListLocalFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListRemoteFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonUnconnect();
	afx_msg void OnLbnSelchangeListStatus();
	afx_msg void OnBnClickedButtonAbort();
	afx_msg void OnBnClickedButtonResume();
};

#endif