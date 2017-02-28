// LeftListView.cpp : ���� �����Դϴ�.
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


// CLeftListView �����Դϴ�.

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


// CLeftListView �޽��� ó�����Դϴ�.


int CLeftListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	CListCtrl& List = GetListCtrl();

	List.InsertColumn(0,_T("Name"),LVCFMT_LEFT,200);
	List.InsertItem(0,_T("Seulki"));

	List.ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	
	return 0;
}
