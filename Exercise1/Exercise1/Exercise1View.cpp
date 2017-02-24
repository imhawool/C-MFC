
// Exercise1View.cpp : CExercise1View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Exercise1.h"
#endif

#include "Exercise1Doc.h"
#include "Exercise1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise1View

IMPLEMENT_DYNCREATE(CExercise1View, CView)

BEGIN_MESSAGE_MAP(CExercise1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CExercise1View 생성/소멸

CExercise1View::CExercise1View()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CExercise1View::~CExercise1View()
{
}

BOOL CExercise1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CExercise1View 그리기

void CExercise1View::OnDraw(CDC* /*pDC*/)
{
	CExercise1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CExercise1View 인쇄

BOOL CExercise1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CExercise1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CExercise1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CExercise1View 진단

#ifdef _DEBUG
void CExercise1View::AssertValid() const
{
	CView::AssertValid();
}

void CExercise1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExercise1Doc* CExercise1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExercise1Doc)));
	return (CExercise1Doc*)m_pDocument;
}
#endif //_DEBUG


// CExercise1View 메시지 처리기


void CExercise1View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	//실습예제1,2,3
	/*
	DWORD style[] = {6,3};
	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(192,0,0);

	CPen NewPen;
	NewPen.CreatePen(PS_GEOMETRIC |PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_MITER,3,&lb);
	CPen* pOldPen = dc.SelectObject(&NewPen);

	CBrush NewBrush(RGB(192,192,192));
	CBrush* pOldBrush = dc.SelectObject(&NewBrush);

	//POINT arPt[4] = {{20,20},{140,20},{140,140},{20,140}};
	//dc.Polygon(arPt,4);

	POINT arPt[4] = {{200,20},{320,20},{320,140},{200,140}};
	dc.Polygon(arPt,4);
	//dc.Rectangle(CRect(180,20,300,140));
	dc.BeginPath();	
	dc.MoveTo(50,0);
	dc.LineTo(150,0);
	dc.LineTo(195,85);
	dc.LineTo(150,170);
	dc.LineTo(50,170);
	dc.LineTo(0,85);
	dc.LineTo(50,0);	
	dc.EndPath();	
	dc.StrokeAndFillPath();


	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush); 
	*/
	//예제4
	CRect Rect; 
	GetClientRect(&Rect);

	CBrush brush(RGB(0,0,0)); 
	CBrush *oldbrush = dc.SelectObject(&brush);
	dc.Rectangle(Rect);
	dc.SelectObject(oldbrush); 

	const int radius = 10; 
	CPen NewPen;
	NewPen.CreatePen(PS_ENDCAP_FLAT|PS_JOIN_ROUND,radius*2,RGB(255,255,255)); 
	CBrush NewBrush(RGB(255,255,255));
	CBrush *pOldBrush = dc.SelectObject(&NewBrush);
	CPen* pOldPen = dc.SelectObject(&NewPen);

	
	Rect.left += radius;
	Rect.bottom -= radius;
	Rect.right -= radius;
	Rect.top += radius;

	POINT arPt[4] = {
		{Rect.left,Rect.top},
		{Rect.right,Rect.top},
		{Rect.right,Rect.bottom},
		{Rect.left,Rect.bottom}
	};
	dc.Polygon(arPt,4); 

	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldPen);


	dc.SelectObject(pOldPen);  
}

