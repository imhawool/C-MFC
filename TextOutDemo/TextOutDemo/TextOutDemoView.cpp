
// TextOutDemoView.cpp : CTextOutDemoView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "TextOutDemo.h"
#endif

#include "TextOutDemoDoc.h"
#include "TextOutDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTextOutDemoView

IMPLEMENT_DYNCREATE(CTextOutDemoView, CView)

BEGIN_MESSAGE_MAP(CTextOutDemoView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CTextOutDemoView ����/�Ҹ�

CTextOutDemoView::CTextOutDemoView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CTextOutDemoView::~CTextOutDemoView()
{
}

BOOL CTextOutDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CTextOutDemoView �׸���

void CTextOutDemoView::OnDraw(CDC* /*pDC*/)
{
	CTextOutDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CTextOutDemoView �μ�

BOOL CTextOutDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CTextOutDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CTextOutDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CTextOutDemoView ����

#ifdef _DEBUG
void CTextOutDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CTextOutDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTextOutDemoDoc* CTextOutDemoView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTextOutDemoDoc)));
	return (CTextOutDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CTextOutDemoView �޽��� ó����


void CTextOutDemoView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.
	int nY = 0;
	CFont Font;
	CFont* pOldFont;

	LOGFONT lf;

	::ZeroMemory(&lf,sizeof(lf));
	lf.lfWeight = FW_BOLD;
	lf.lfItalic = TRUE;
	lf.lfUnderline = TRUE;
	//::ZeroMemory(&lf,sizeof(lf));

	Font.CreateFontIndirect(&lf);
	pOldFont = dc.SelectObject(&Font);
	dc.TextOutW(20,50,_T("\t�̰��� �ǽ��� ���� ���ڿ��Դϴ�.\n"));

	int nTapStop = 0;
	dc.TabbedTextOutW(20,80,_T("\t�̰��� �ǽ��� ���� ���ڿ��Դϴ�.\n"),1,&nTapStop,20);
	dc.DrawText(_T("\t�̰��� �ǽ��� ���� ���ڿ��Դϴ�.\n"),CRect(0,100,350,150),DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	dc.SelectObject(pOldFont);
	Font.DeleteObject();
	
}
