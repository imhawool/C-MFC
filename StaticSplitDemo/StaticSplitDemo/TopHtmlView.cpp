// TopHtmlView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "StaticSplitDemo.h"
#include "TopHtmlView.h"


// CTopHtmlView

IMPLEMENT_DYNCREATE(CTopHtmlView, CHtmlEditView)

CTopHtmlView::CTopHtmlView()
{

}

CTopHtmlView::~CTopHtmlView()
{
}

BEGIN_MESSAGE_MAP(CTopHtmlView, CHtmlEditView)
END_MESSAGE_MAP()


// CTopHtmlView 진단입니다.

#ifdef _DEBUG
void CTopHtmlView::AssertValid() const
{
	CHtmlEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CTopHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTopHtmlView 메시지 처리기입니다.


void CTopHtmlView::OnInitialUpdate(void)
{
	CHtmlView::OnInitialUpdate();

	Navigate2(_T("C:\\"));
}
