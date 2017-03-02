// SubClassTestWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SubClass.h"
#include "SubClassTestWnd.h"


// CSubClassTestWnd

IMPLEMENT_DYNAMIC(CSubClassTestWnd, CWnd)

CSubClassTestWnd::CSubClassTestWnd()
{
	m_bFlag = TRUE;
}

CSubClassTestWnd::~CSubClassTestWnd()
{
}


BEGIN_MESSAGE_MAP(CSubClassTestWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CSubClassTestWnd 메시지 처리기입니다.




void CSubClassTestWnd::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CWnd::OnPaint()을(를) 호출하지 마십시오.
	
	CWnd::OnPaint();

	CClientDC dc(this);

	CRect Rect(3,3,16,16);
	if (m_bFlag)	dc.FillSolidRect(&Rect, RGB(192,0,0));
	else			dc.FillSolidRect(&Rect, RGB(255,255,255));
}


void CSubClassTestWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnLButtonDown(nFlags, point);

	CRect Rect(3,3,16,16);
	if (PtInRect(&Rect, point))
	{
		m_bFlag = !m_bFlag;
		RedrawWindow();
	}
}


void CSubClassTestWnd::OnDestroy()
{
	UnsubclassWindow();

	CWnd::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
