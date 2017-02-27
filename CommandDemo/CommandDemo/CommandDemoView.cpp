
// CommandDemoView.cpp : CCommandDemoView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "CommandDemo.h"
#endif

#include "CommandDemoDoc.h"
#include "CommandDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCommandDemoView

IMPLEMENT_DYNCREATE(CCommandDemoView, CView)

BEGIN_MESSAGE_MAP(CCommandDemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CCommandDemoView 생성/소멸

CCommandDemoView::CCommandDemoView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CCommandDemoView::~CCommandDemoView()
{
}

BOOL CCommandDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCommandDemoView 그리기

void CCommandDemoView::OnDraw(CDC* /*pDC*/)
{
	CCommandDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CCommandDemoView 인쇄

BOOL CCommandDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCommandDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCommandDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CCommandDemoView 진단

#ifdef _DEBUG
void CCommandDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CCommandDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCommandDemoDoc* CCommandDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCommandDemoDoc)));
	return (CCommandDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CCommandDemoView 메시지 처리기


void CCommandDemoView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMenu* pMainMenu = AfxGetMainWnd()->GetMenu();

	CMenu* pSubMenu = pMainMenu->GetSubMenu(4);
	CPoint ptMenu = point;
	ClientToScreen(&ptMenu);

	pSubMenu->TrackPopupMenu(TPM_LEFTBUTTON|TPM_LEFTALIGN,ptMenu.x,ptMenu.y,AfxGetMainWnd());
	CView::OnRButtonDown(nFlags, point);
}
