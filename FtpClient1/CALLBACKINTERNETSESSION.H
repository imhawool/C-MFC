
#ifndef __CALLBACK_H__
#define __CALLBACK_H__

#include "AfxInet.h"

class CCFtpDlg;

class CCallbackInternetSession : public CInternetSession
{
public:
	CCFtpDlg* m_pFtpDlg;
	void SetFtpPtr(CCFtpDlg* pFtp) { m_pFtpDlg = pFtp; }

	CCallbackInternetSession(LPCTSTR pstrAgent=NULL,
		DWORD dwContext=1,
		DWORD dwAccessType=PRE_CONFIG_INTERNET_ACCESS, 
		LPCTSTR pstrProxyName=NULL,
		LPCTSTR pstrProxyBypass=NULL,
		DWORD dwFlags=0)						
		{
			m_pFtpDlg = NULL; 
			EnableStatusCallback();
		}

protected:
	virtual void OnStatusCallback(DWORD dwContext,DWORD dwInternalStatus,
				LPVOID lpvStatusInformation,DWORD dwStatusInformationLength);

};

#endif
