
// ImageScrollDemoView.cpp : CImageScrollDemoView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageScrollDemo.h"
#endif

#include "ImageScrollDemoDoc.h"
#include "ImageScrollDemoView.h"
#include <atlimage.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageScrollDemoView

IMPLEMENT_DYNCREATE(CImageScrollDemoView, CScrollView)

BEGIN_MESSAGE_MAP(CImageScrollDemoView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CImageScrollDemoView 생성/소멸

CImageScrollDemoView::CImageScrollDemoView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageScrollDemoView::~CImageScrollDemoView()
{
}

BOOL CImageScrollDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageScrollDemoView 그리기

void CImageScrollDemoView::OnDraw(CDC* /*pDC*/)
{
	CImageScrollDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CImageScrollDemoView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 1600;
	sizeTotal.cy = 1200;

	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageScrollDemoView 인쇄

BOOL CImageScrollDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageScrollDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageScrollDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImageScrollDemoView 진단

#ifdef _DEBUG
void CImageScrollDemoView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageScrollDemoView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageScrollDemoDoc* CImageScrollDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageScrollDemoDoc)));
	return (CImageScrollDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageScrollDemoView 메시지 처리기


void CImageScrollDemoView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CScrollView::OnPaint()을(를) 호출하지 마십시오.
	int nVertScroll = GetScrollPos(SB_VERT);
	int nHorzScroll = GetScrollPos(SB_HORZ);

	CImage Image;
	Image.LoadFromResource(AfxGetInstanceHandle(),IDB_Image);
	Image.BitBlt(dc.m_hDC,-nHorzScroll,-nVertScroll);
}
