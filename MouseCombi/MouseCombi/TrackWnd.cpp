// TrackWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MouseCombi.h"
#include "TrackWnd.h"


// CTrackWnd

IMPLEMENT_DYNAMIC(CTrackWnd, CWnd)

CTrackWnd::CTrackWnd()
{
	m_bTrack = FALSE;
}

CTrackWnd::~CTrackWnd()
{
}


BEGIN_MESSAGE_MAP(CTrackWnd, CWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CTrackWnd 메시지 처리기입니다.




void CTrackWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(!m_bTrack)
	{
		TRACKMOUSEEVENT tme = {0};
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		tme.dwHoverTime = 0;

		m_bTrack = ::_TrackMouseEvent(&tme);

		if(m_bTrack)	SetWindowText(_T("Tracking"));
	}
	SetWindowText(_T("tracking"));
	CWnd::OnMouseMove(nFlags, point);
}


void CTrackWnd::OnMouseLeave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SetWindowText(_T("TRACK TEST"));
	m_bTrack = false;
	CWnd::OnMouseLeave();
}
