// LeftListView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "StaticSplitDemo.h"
#include "LeftListView.h"


// CLeftListView

IMPLEMENT_DYNCREATE(CLeftListView, CListView)

CLeftListView::CLeftListView()
{

}

CLeftListView::~CLeftListView()
{
}

BEGIN_MESSAGE_MAP(CLeftListView, CListView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CLeftListView 진단입니다.

#ifdef _DEBUG
void CLeftListView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftListView 메시지 처리기입니다.


int CLeftListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CListCtrl& List = GetListCtrl();

	List.InsertColumn(0,_T("Name"),LVCFMT_LEFT,200);
	List.InsertItem(0,_T("Seulki"));

	List.ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	
	return 0;
}
