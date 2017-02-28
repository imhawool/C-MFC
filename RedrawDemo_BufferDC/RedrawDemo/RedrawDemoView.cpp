
// RedrawDemoView.cpp : CRedrawDemoView 클래스의 구현
//

#include "stdafx.h"
#include "RedrawDemo.h"

#include "RedrawDemoDoc.h"
#include "RedrawDemoView.h"

#include "BufferDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRedrawDemoView

IMPLEMENT_DYNCREATE(CRedrawDemoView, CView)

BEGIN_MESSAGE_MAP(CRedrawDemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CRedrawDemoView 생성/소멸

CRedrawDemoView::CRedrawDemoView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CRedrawDemoView::~CRedrawDemoView()
{
}

BOOL CRedrawDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CRedrawDemoView 그리기

void CRedrawDemoView::OnDraw(CDC* /*pDC*/)
{
	CRedrawDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CRedrawDemoView 인쇄

BOOL CRedrawDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CRedrawDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CRedrawDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CRedrawDemoView 진단

#ifdef _DEBUG
void CRedrawDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CRedrawDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRedrawDemoDoc* CRedrawDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRedrawDemoDoc)));
	return (CRedrawDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CRedrawDemoView 메시지 처리기

void CRedrawDemoView::OnPaint()
{
//	CPaintDC dc(this); // device context for painting
	CBufferDC dc(this);

	CRect Rect;
	GetClientRect(&Rect);
	dc.FillSolidRect(&Rect, RGB(192, 0, 0));

	Rect -= CRect(7, 7, 7, 7);
	dc.SelectStockObject(NULL_PEN);
	dc.RoundRect(&Rect, CPoint(21, 21));

	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(30, 30, _T("Test string!"));

}

BOOL CRedrawDemoView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
//	return CView::OnEraseBkgnd(pDC);
}
