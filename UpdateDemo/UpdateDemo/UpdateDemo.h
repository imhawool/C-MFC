
// UpdateDemo.h : UpdateDemo ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CUpdateDemoApp:
// �� Ŭ������ ������ ���ؼ��� UpdateDemo.cpp�� �����Ͻʽÿ�.
//

class CUpdateDemoApp : public CWinApp
{
public:
	CUpdateDemoApp();

	CEvent m_ExitEvent;
	CEvent m_UpdateEvent;

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	static UINT ThreadUpdate(LPVOID pParam);
};

extern CUpdateDemoApp theApp;
