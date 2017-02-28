// BottomEditView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "StaticSplitDemo.h"
#include "BottomEditView.h"


// CBottomEditView

IMPLEMENT_DYNCREATE(CBottomEditView, CEditView)

CBottomEditView::CBottomEditView()
{

}

CBottomEditView::~CBottomEditView()
{
}

BEGIN_MESSAGE_MAP(CBottomEditView, CEditView)
END_MESSAGE_MAP()


// CBottomEditView 진단입니다.

#ifdef _DEBUG
void CBottomEditView::AssertValid() const
{
	CEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CBottomEditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBottomEditView 메시지 처리기입니다.
