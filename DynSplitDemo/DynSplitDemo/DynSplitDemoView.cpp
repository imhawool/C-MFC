
// DynSplitDemoView.cpp : CDynSplitDemoView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

// CDynSplitDemoView ����/�Ҹ�

CDynSplitDemoView::CDynSplitDemoView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CDynSplitDemoView::~CDynSplitDemoView()
{
}

BOOL CDynSplitDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CHtmlView::PreCreateWindow(cs);
}

void CDynSplitDemoView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	Navigate2(_T("C:\\"),NULL,NULL);
}


// CDynSplitDemoView �μ�



// CDynSplitDemoView ����

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


// CDynSplitDemoView �޽��� ó����
