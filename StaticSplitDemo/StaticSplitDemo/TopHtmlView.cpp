// TopHtmlView.cpp : ���� �����Դϴ�.
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


// CTopHtmlView �����Դϴ�.

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


// CTopHtmlView �޽��� ó�����Դϴ�.


void CTopHtmlView::OnInitialUpdate(void)
{
	CHtmlView::OnInitialUpdate();

	Navigate2(_T("C:\\"));
}
