
// GdiplusPolygonView.cpp : CGdiplusPolygonView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "GdiplusPolygon.h"
#endif

#include "GdiplusPolygonDoc.h"
#include "GdiplusPolygonView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGdiplusPolygonView

IMPLEMENT_DYNCREATE(CGdiplusPolygonView, CView)

BEGIN_MESSAGE_MAP(CGdiplusPolygonView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CGdiplusPolygonView ����/�Ҹ�

CGdiplusPolygonView::CGdiplusPolygonView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CGdiplusPolygonView::~CGdiplusPolygonView()
{
}

BOOL CGdiplusPolygonView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CGdiplusPolygonView �׸���

void CGdiplusPolygonView::OnDraw(CDC* /*pDC*/)
{
	CGdiplusPolygonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CGdiplusPolygonView �μ�

BOOL CGdiplusPolygonView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CGdiplusPolygonView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CGdiplusPolygonView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CGdiplusPolygonView ����

#ifdef _DEBUG
void CGdiplusPolygonView::AssertValid() const
{
	CView::AssertValid();
}

void CGdiplusPolygonView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGdiplusPolygonDoc* CGdiplusPolygonView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGdiplusPolygonDoc)));
	return (CGdiplusPolygonDoc*)m_pDocument;
}
#endif //_DEBUG


// CGdiplusPolygonView �޽��� ó����


void CGdiplusPolygonView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.
	Graphics graphics(dc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	//�簢�� �ΰ� �׸���
	
	Pen BlackPen(Color(255, 0, 0, 0), 20.0f);
	graphics.DrawRectangle(&BlackPen, 30, 30, 100, 100);

	BlackPen.SetLineJoin(LineJoinRound);
	graphics.DrawRectangle(&BlackPen, 170, 30, 100, 100);
	
	//�� �׸���
	graphics.DrawEllipse(&BlackPen, 30, 200, 100, 100);
	graphics.DrawEllipse(&BlackPen, 150, 200, 200, 100);
	
	//��ä�� �׸���
	Pen RedPen(Color(255, 192, 0, 0), 2.0f);
	Pen GrayPen(Color(255, 192, 192, 192), 15.0f);
	graphics.DrawEllipse(&GrayPen, 30, 400, 100, 100);

	graphics.DrawArc(&RedPen, 30, 400, 100, 100, 0.0f, 90.0f);
	graphics.DrawPie(&RedPen, 30, 400, 100, 100, 180.0f, 90.0f);

}
