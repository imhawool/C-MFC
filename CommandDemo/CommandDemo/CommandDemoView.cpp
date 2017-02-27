
// CommandDemoView.cpp : CCommandDemoView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "CommandDemo.h"
#endif

#include "CommandDemoDoc.h"
#include "CommandDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCommandDemoView

IMPLEMENT_DYNCREATE(CCommandDemoView, CView)

BEGIN_MESSAGE_MAP(CCommandDemoView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CCommandDemoView ����/�Ҹ�

CCommandDemoView::CCommandDemoView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CCommandDemoView::~CCommandDemoView()
{
}

BOOL CCommandDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CCommandDemoView �׸���

void CCommandDemoView::OnDraw(CDC* /*pDC*/)
{
	CCommandDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CCommandDemoView �μ�

BOOL CCommandDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CCommandDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CCommandDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CCommandDemoView ����

#ifdef _DEBUG
void CCommandDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CCommandDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCommandDemoDoc* CCommandDemoView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCommandDemoDoc)));
	return (CCommandDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CCommandDemoView �޽��� ó����


void CCommandDemoView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CMenu* pMainMenu = AfxGetMainWnd()->GetMenu();

	CMenu* pSubMenu = pMainMenu->GetSubMenu(4);
	CPoint ptMenu = point;
	ClientToScreen(&ptMenu);

	pSubMenu->TrackPopupMenu(TPM_LEFTBUTTON|TPM_LEFTALIGN,ptMenu.x,ptMenu.y,AfxGetMainWnd());
	CView::OnRButtonDown(nFlags, point);
}
