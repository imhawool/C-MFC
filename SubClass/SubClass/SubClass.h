
// SubClass.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSubClassApp:
// �� Ŭ������ ������ ���ؼ��� SubClass.cpp�� �����Ͻʽÿ�.
//

class CSubClassApp : public CWinApp
{
public:
	CSubClassApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSubClassApp theApp;