
// DynSplitDemoView.cpp : CDynSplitDemoView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DynSplitDemo.h"
#endif

#include "DynSplitDemoDoc.h"
#include "DynSplitDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDynSplitDemoView

IMPLEMENT_DYNCREATE(CDynSplitDemoView, CHtmlView)

BEGIN_MESSAGE_MAP(CDynSplitDemoView, CHtmlView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

// CDynSplitDemoView 생성/소멸

CDynSplitDemoView::CDynSplitDemoView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CDynSplitDemoView::~CDynSplitDemoView()
{
}

BOOL CDynSplitDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CHtmlView::PreCreateWindow(cs);
}

void CDynSplitDemoView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	Navigate2(_T("C:\\"),NULL,NULL);
}


// CDynSplitDemoView 인쇄



// CDynSplitDemoView 진단

#ifdef _DEBUG
void CDynSplitDemoView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CDynSplitDemoView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

#endif //_DEBUG


// CDynSplitDemoView 메시지 처리기
