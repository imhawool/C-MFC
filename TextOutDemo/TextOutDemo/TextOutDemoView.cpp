
// TextOutDemoView.cpp : CTextOutDemoView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "TextOutDemo.h"
#endif

#include "TextOutDemoDoc.h"
#include "TextOutDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTextOutDemoView

IMPLEMENT_DYNCREATE(CTextOutDemoView, CView)

BEGIN_MESSAGE_MAP(CTextOutDemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CTextOutDemoView 생성/소멸

CTextOutDemoView::CTextOutDemoView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTextOutDemoView::~CTextOutDemoView()
{
}

BOOL CTextOutDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTextOutDemoView 그리기

void CTextOutDemoView::OnDraw(CDC* /*pDC*/)
{
	CTextOutDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CTextOutDemoView 인쇄

BOOL CTextOutDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTextOutDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTextOutDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CTextOutDemoView 진단

#ifdef _DEBUG
void CTextOutDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CTextOutDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTextOutDemoDoc* CTextOutDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTextOutDemoDoc)));
	return (CTextOutDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CTextOutDemoView 메시지 처리기


void CTextOutDemoView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	int nY = 0;
	CFont Font;
	CFont* pOldFont;

	LOGFONT lf;

	::ZeroMemory(&lf,sizeof(lf));
	lf.lfWeight = FW_BOLD;
	lf.lfItalic = TRUE;
	lf.lfUnderline = TRUE;
	//::ZeroMemory(&lf,sizeof(lf));

	Font.CreateFontIndirect(&lf);
	pOldFont = dc.SelectObject(&Font);
	dc.TextOutW(20,50,_T("\t이것은 실습을 위한 문자열입니다.\n"));

	int nTapStop = 0;
	dc.TabbedTextOutW(20,80,_T("\t이것은 실습을 위한 문자열입니다.\n"),1,&nTapStop,20);
	dc.DrawText(_T("\t이것은 실습을 위한 문자열입니다.\n"),CRect(0,100,350,150),DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	dc.SelectObject(pOldFont);
	Font.DeleteObject();
	
}
