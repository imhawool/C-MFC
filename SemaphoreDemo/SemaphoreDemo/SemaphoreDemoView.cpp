
// SemaphoreDemoView.cpp : CSemaphoreDemoView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SemaphoreDemo.h"
#endif

#include "SemaphoreDemoDoc.h"
#include "SemaphoreDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSemaphoreDemoView

IMPLEMENT_DYNCREATE(CSemaphoreDemoView, CView)

BEGIN_MESSAGE_MAP(CSemaphoreDemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSemaphoreDemoView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CSemaphoreDemoView 생성/소멸

CSemaphoreDemoView::CSemaphoreDemoView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSemaphoreDemoView::~CSemaphoreDemoView()
{
}

BOOL CSemaphoreDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSemaphoreDemoView 그리기

void CSemaphoreDemoView::OnDraw(CDC* /*pDC*/)
{
	CSemaphoreDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CSemaphoreDemoView 인쇄


void CSemaphoreDemoView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSemaphoreDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSemaphoreDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSemaphoreDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CSemaphoreDemoView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSemaphoreDemoView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSemaphoreDemoView 진단

#ifdef _DEBUG
void CSemaphoreDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CSemaphoreDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSemaphoreDemoDoc* CSemaphoreDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSemaphoreDemoDoc)));
	return (CSemaphoreDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CSemaphoreDemoView 메시지 처리기


int CSemaphoreDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(100, 1000, NULL);
	return 0;
}


void CSemaphoreDemoView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	dc.FillSolidRect(0, 0, 300, 300, RGB(255, 255, 255));

	for(int i = 0 ; i < 10 ; ++i)
	{
		if (g_arString[i].GetAt(0) == '#')	dc.SetTextColor(RGB(192, 0, 0));
		else								dc.SetTextColor(RGB(192, 192, 192));

		dc.TextOutW(30, 20 * i + 10, g_arString[i]);
	}
	CView::OnTimer(nIDEvent);
}
