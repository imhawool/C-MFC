
// USerMsgDemo.h : USerMsgDemo ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CUSerMsgDemoApp:
// �� Ŭ������ ������ ���ؼ��� USerMsgDemo.cpp�� �����Ͻʽÿ�.
//

class CUSerMsgDemoApp : public CWinApp
{
public:
	CUSerMsgDemoApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CUSerMsgDemoApp theApp;
