
// MFCHW2.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFCHW2App:
// �� Ŭ������ ������ ���ؼ��� MFCHW2.cpp�� �����Ͻʽÿ�.
//

class CMFCHW2App : public CWinApp
{
public:
	CMFCHW2App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFCHW2App theApp;