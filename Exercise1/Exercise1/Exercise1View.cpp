
// Exercise1View.cpp : CExercise1View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Exercise1.h"
#endif

#include "Exercise1Doc.h"
#include "Exercise1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise1View

IMPLEMENT_DYNCREATE(CExercise1View, CView)

BEGIN_MESSAGE_MAP(CExercise1View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CExercise1View ����/�Ҹ�

CExercise1View::CExercise1View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CExercise1View::~CExercise1View()
{
}

BOOL CExercise1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CExercise1View �׸���

void CExercise1View::OnDraw(CDC* /*pDC*/)
{
	CExercise1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CExercise1View �μ�

BOOL CExercise1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CExercise1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CExercise1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CExercise1View ����

#ifdef _DEBUG
void CExercise1View::AssertValid() const
{
	CView::AssertValid();
}

void CExercise1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExercise1Doc* CExercise1View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExercise1Doc)));
	return (CExercise1Doc*)m_pDocument;
}
#endif //_DEBUG


// CExercise1View �޽��� ó����


void CExercise1View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.
	//�ǽ�����1,2,3
	/*
	DWORD style[] = {6,3};
	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(192,0,0);

	CPen NewPen;
	NewPen.CreatePen(PS_GEOMETRIC |PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_MITER,3,&lb);
	CPen* pOldPen = dc.SelectObject(&NewPen);

	CBrush NewBrush(RGB(192,192,192));
	CBrush* pOldBrush = dc.SelectObject(&NewBrush);

	//POINT arPt[4] = {{20,20},{140,20},{140,140},{20,140}};
	//dc.Polygon(arPt,4);

	POINT arPt[4] = {{200,20},{320,20},{320,140},{200,140}};
	dc.Polygon(arPt,4);
	//dc.Rectangle(CRect(180,20,300,140));
	dc.BeginPath();	
	dc.MoveTo(50,0);
	dc.LineTo(150,0);
	dc.LineTo(195,85);
	dc.LineTo(150,170);
	dc.LineTo(50,170);
	dc.LineTo(0,85);
	dc.LineTo(50,0);	
	dc.EndPath();	
	dc.StrokeAndFillPath();


	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush); 
	*/
	//����4
	CRect Rect; 
	GetClientRect(&Rect);

	CBrush brush(RGB(0,0,0)); 
	CBrush *oldbrush = dc.SelectObject(&brush);
	dc.Rectangle(Rect);
	dc.SelectObject(oldbrush); 

	const int radius = 10; 
	CPen NewPen;
	NewPen.CreatePen(PS_ENDCAP_FLAT|PS_JOIN_ROUND,radius*2,RGB(255,255,255)); 
	CBrush NewBrush(RGB(255,255,255));
	CBrush *pOldBrush = dc.SelectObject(&NewBrush);
	CPen* pOldPen = dc.SelectObject(&NewPen);

	
	Rect.left += radius;
	Rect.bottom -= radius;
	Rect.right -= radius;
	Rect.top += radius;

	POINT arPt[4] = {
		{Rect.left,Rect.top},
		{Rect.right,Rect.top},
		{Rect.right,Rect.bottom},
		{Rect.left,Rect.bottom}
	};
	dc.Polygon(arPt,4); 

	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldPen);


	dc.SelectObject(pOldPen);  
}

