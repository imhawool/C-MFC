
#include "stdafx.h"
#include "CallbackInternetSession.h"
#include "CFtp.h"
#include "CFtpDlg.h"


// 세션 상태
void CCallbackInternetSession::OnStatusCallback(DWORD dwContext,DWORD dwInternalStatus,
		LPVOID lpvStatusInformation,DWORD dwStatusInformationLength)
{
	CString str;

	if(m_pFtpDlg) // 메인 다이얼로그가 있으면
	{
		switch(dwInternalStatus)
		{
		case INTERNET_STATUS_RESOLVING_NAME:
			str.Format("< Name=%s",lpvStatusInformation);
			break;
		case INTERNET_STATUS_NAME_RESOLVED:
			str.Format("< IP=%s",(LPCTSTR)lpvStatusInformation);
			break;
		case INTERNET_STATUS_CONNECTING_TO_SERVER:
			str="서버에 연결중...";
			str.Format("< IP=%s",(LPCTSTR)lpvStatusInformation);
			break;
		case INTERNET_STATUS_CONNECTED_TO_SERVER:
			str="< 서버에 연결 완료";
			break;
		case INTERNET_STATUS_SENDING_REQUEST:
			str="< Sending the information request to the server.";
			break;
		case INTERNET_STATUS_REQUEST_SENT:
			str="< Successfully sent the information request to the server.";
			break;
		case INTERNET_STATUS_RECEIVING_RESPONSE:
			str="< Waiting for the server to respond to a request.";
			break;
		case INTERNET_STATUS_RESPONSE_RECEIVED:
			str="< Successfully received a response from the server.";
			break;
		case INTERNET_STATUS_CLOSING_CONNECTION:
			str="< Closing the connection to the server.";
			break;
		case INTERNET_STATUS_CONNECTION_CLOSED:
			str="< Successfully closed the connection to the server.";
			break;
		case INTERNET_STATUS_HANDLE_CREATED:
			str="< It has created the new handle.";
			break;
		case INTERNET_STATUS_HANDLE_CLOSING:
			str="< Successfully terminated this handle value.";
			break;
		case INTERNET_STATUS_REQUEST_COMPLETE:
			str="< Successfully completed the asynchronous operation.";
			break;
		}
		m_pFtpDlg->StatusList(str);
	}
}
