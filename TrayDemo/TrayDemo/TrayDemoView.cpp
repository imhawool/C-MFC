
// TrayDemoView.cpp : CTrayDemoView 클래스의 구현
//

#include "stdafx.h"
#include "TrayDemo.h"

#include "TrayDemoDoc.h"
#include "TrayDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrayDemoView

IMPLEMENT_DYNCREATE(CTrayDemoView, CView)

BEGIN_MESSAGE_MAP(CTrayDemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTrayDemoView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTrayDemoView 생성/소멸

CTrayDemoView::CTrayDemoView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTrayDemoView::~CTrayDemoView()
{
}

BOOL CTrayDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTrayDemoView 그리기

void CTrayDemoView::OnDraw(CDC* /*pDC*/)
{
	CTrayDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CTrayDemoView 인쇄


void CTrayDemoView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CTrayDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTrayDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTrayDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CTrayDemoView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTrayDemoView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CTrayDemoView 진단

#ifdef _DEBUG
void CTrayDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CTrayDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTrayDemoDoc* CTrayDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTrayDemoDoc)));
	return (CTrayDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CTrayDemoView 메시지 처리기

void CTrayDemoView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}
