
// USerMsgDemoView.cpp : CUSerMsgDemoView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "USerMsgDemo.h"
#endif

#include "USerMsgDemoDoc.h"
#include "USerMsgDemoView.h"
#include "atlimage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUSerMsgDemoView

IMPLEMENT_DYNCREATE(CUSerMsgDemoView, CView)

BEGIN_MESSAGE_MAP(CUSerMsgDemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_MESSAGE(UM_TESTMESSAGE, &CUSerMsgDemoView::OnTestMessage)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CUSerMsgDemoView 생성/소멸

CUSerMsgDemoView::CUSerMsgDemoView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CUSerMsgDemoView::~CUSerMsgDemoView()
{
}

BOOL CUSerMsgDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CUSerMsgDemoView 그리기

void CUSerMsgDemoView::OnDraw(CDC* /*pDC*/)
{
	CUSerMsgDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CUSerMsgDemoView 인쇄

BOOL CUSerMsgDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CUSerMsgDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CUSerMsgDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CUSerMsgDemoView 진단

#ifdef _DEBUG
void CUSerMsgDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CUSerMsgDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUSerMsgDemoDoc* CUSerMsgDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUSerMsgDemoDoc)));
	return (CUSerMsgDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CUSerMsgDemoView 메시지 처리기

LRESULT CUSerMsgDemoView::OnTestMessage(WPARAM wParam, LPARAM lParam)
{

	AfxMessageBox(_T("CUserMsgDemoView::OnTestMessage()"));

	return 0;
}

int CUSerMsgDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	if (SetTimer(10,1000,NULL) != 10)
	{

		AfxMessageBox(_T("ERROR : Failes to set timer!"));
	}
	srand((unsigned)time(NULL));

	return 0;
}


void CUSerMsgDemoView::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	KillTimer(10);
	CView::OnClose();
}


void CUSerMsgDemoView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 10)
	{
		CRect Rect;
		GetClientRect(&Rect);

		if (Rect.Width() != 0 && Rect.Height() != 0)
		{
			m_nImageX = rand()%Rect.Width();
			m_nImageY = rand()%Rect.Height();
			RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW);
		}
	}
	CView::OnTimer(nIDEvent);
}


void CUSerMsgDemoView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	CRect Rect;
	GetClientRect(&Rect);
	dc.FillSolidRect(&Rect,RGB(0,0,0));

	CImage Image;
	Image.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP);
	Image.BitBlt(dc.m_hDC, m_nImageX, m_nImageY, SRCCOPY);
}
