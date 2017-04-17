
#if !defined(AFX_CFTP_H__534B6BED_4956_4191_BA64_CFBA49EDFF9C__INCLUDED_)
#define AFX_CFTP_H__534B6BED_4956_4191_BA64_CFBA49EDFF9C__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// 주 기호입니다.

// CCFtpApp:
// 이 클래스의 구현에 대해서는 FtpEx.cpp을 참조하십시오.
//

class CCFtpApp : public CWinApp
{
public:
	CCFtpApp();

// 재정의입니다.
	public:
	virtual BOOL InitInstance();


// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

#endif 
