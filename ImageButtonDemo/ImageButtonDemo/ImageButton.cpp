// ImageButton.cpp : implementation file
//

#include "stdafx.h"
#include "ImageButtonDemo.h"
#include "ImageButton.h"


// CImageButton

IMPLEMENT_DYNAMIC(CImageButton, CButton)

CImageButton::CImageButton()
{
	m_bHover		= FALSE;
	m_bTracking		= FALSE;
}

CImageButton::~CImageButton()
{
}


BEGIN_MESSAGE_MAP(CImageButton, CButton)
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CImageButton message handlers



void CImageButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		::ZeroMemory(&tme, sizeof(tme));

		tme.cbSize		= sizeof(tme);
		tme.hwndTrack	= m_hWnd;
		tme.dwFlags		= TME_LEAVE | TME_HOVER;
		tme.dwHoverTime	= 1;

		m_bTracking = ::_TrackMouseEvent(&tme);
	}

	CButton::OnMouseMove(nFlags, point);
}

void CImageButton::OnMouseHover(UINT nFlags, CPoint point)
{
	m_bHover = TRUE;
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	CButton::OnMouseHover(nFlags, point);
}

void CImageButton::OnMouseLeave()
{
	m_bHover	= FALSE;
	m_bTracking	= FALSE;
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	CButton::OnMouseLeave();
}

void CImageButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap Bmp;
	Bmp.LoadBitmap(IDB_Button_Image);
	CBitmap* pOldBitmap = MemDC.SelectObject(&Bmp);

	if(lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		pDC->BitBlt(0, 0, 40, 40, &MemDC, 40, 0, SRCCOPY);
	}
	else
	{
		if(m_bHover)	pDC->BitBlt(0, 0, 40, 40, &MemDC, 80, 0, SRCCOPY);
		else			pDC->BitBlt(0, 0, 40, 40, &MemDC, 0, 0, SRCCOPY);
	}

	MemDC.SelectObject(pOldBitmap);
}

