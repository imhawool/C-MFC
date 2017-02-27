
// exercise8View.cpp : Cexercise8View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "exercise8.h"
#endif

#include "exercise8Doc.h"
#include "exercise8View.h"

#include<atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cexercise8View

IMPLEMENT_DYNCREATE(Cexercise8View, CView)

BEGIN_MESSAGE_MAP(Cexercise8View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// Cexercise8View 생성/소멸

Cexercise8View::Cexercise8View()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

Cexercise8View::~Cexercise8View()
{
}

BOOL Cexercise8View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Cexercise8View 그리기

void Cexercise8View::OnDraw(CDC* /*pDC*/)
{
	Cexercise8Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// Cexercise8View 인쇄

BOOL Cexercise8View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Cexercise8View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Cexercise8View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// Cexercise8View 진단

#ifdef _DEBUG
void Cexercise8View::AssertValid() const
{
	CView::AssertValid();
}

void Cexercise8View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cexercise8Doc* Cexercise8View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cexercise8Doc)));
	return (Cexercise8Doc*)m_pDocument;
}
#endif //_DEBUG


// Cexercise8View 메시지 처리기


void Cexercise8View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	CDC MemDC;
	BITMAP bmpInfo;

	MemDC.CreateCompatibleDC(&dc);

	CBitmap bmp;
	CBitmap* pOldBmp = NULL;
	bmp.LoadBitmapW(IDB_Test_Image2);

	bmp.GetBitmap(&bmpInfo);

	pOldBmp = MemDC.SelectObject(&bmp);
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 80;
	bf.AlphaFormat = 0;
	dc.AlphaBlend(100,250,bmpInfo.bmWidth*2,bmpInfo.bmHeight*2,&MemDC,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,bf);

	MemDC.SelectObject(pOldBmp);

	CImage Image;
	
	Image.LoadFromResource(AfxGetInstanceHandle(),IDB_Test_Image);

	CDC* pDC = CDC::FromHandle(Image.GetDC());

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetBkColor(RGB(255, 255, 255));  
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->TextOutW(400,350,_T("이슬기"));
	Image.ReleaseDC();
	Image.BitBlt(dc.m_hDC, 0, 0);

	
}
