
#if !defined(AFX_CFTP_H__534B6BED_4956_4191_BA64_CFBA49EDFF9C__INCLUDED_)
#define AFX_CFTP_H__534B6BED_4956_4191_BA64_CFBA49EDFF9C__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

// CCFtpApp:
// �� Ŭ������ ������ ���ؼ��� FtpEx.cpp�� �����Ͻʽÿ�.
//

class CCFtpApp : public CWinApp
{
public:
	CCFtpApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();


// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

#endif 
