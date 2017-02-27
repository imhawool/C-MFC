
// exercise8View.cpp : Cexercise8View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "exercise8.h"
#endif

#include "exercise8Doc.h"
#include "exercise8View.h"

#include<atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cexercise8View

IMPLEMENT_DYNCREATE(Cexercise8View, CView)

BEGIN_MESSAGE_MAP(Cexercise8View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// Cexercise8View ����/�Ҹ�

Cexercise8View::Cexercise8View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

Cexercise8View::~Cexercise8View()
{
}

BOOL Cexercise8View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// Cexercise8View �׸���

void Cexercise8View::OnDraw(CDC* /*pDC*/)
{
	Cexercise8Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// Cexercise8View �μ�

BOOL Cexercise8View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void Cexercise8View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void Cexercise8View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// Cexercise8View ����

#ifdef _DEBUG
void Cexercise8View::AssertValid() const
{
	CView::AssertValid();
}

void Cexercise8View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cexercise8Doc* Cexercise8View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cexercise8Doc)));
	return (Cexercise8Doc*)m_pDocument;
}
#endif //_DEBUG


// Cexercise8View �޽��� ó����


void Cexercise8View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CDC MemDC;
	BITMAP bmpInfo;

	MemDC.CreateCompatibleDC(&dc);

	CBitmap bmp;
	CBitmap* pOldBmp = NULL;
	bmp.LoadBitmapW(IDB_Test_Image2);

	bmp.GetBitmap(&bmpInfo);

	pOldBmp = MemDC.SelectObject(&bmp);
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 80;
	bf.AlphaFormat = 0;
	dc.AlphaBlend(100,250,bmpInfo.bmWidth*2,bmpInfo.bmHeight*2,&MemDC,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,bf);

	MemDC.SelectObject(pOldBmp);

	CImage Image;
	
	Image.LoadFromResource(AfxGetInstanceHandle(),IDB_Test_Image);

	CDC* pDC = CDC::FromHandle(Image.GetDC());

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetBkColor(RGB(255, 255, 255));  
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->TextOutW(400,350,_T("�̽���"));
	Image.ReleaseDC();
	Image.BitBlt(dc.m_hDC, 0, 0);

	
}
