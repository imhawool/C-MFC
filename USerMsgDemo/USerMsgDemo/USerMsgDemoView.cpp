
// USerMsgDemoView.cpp : CUSerMsgDemoView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "USerMsgDemo.h"
#endif

#include "USerMsgDemoDoc.h"
#include "USerMsgDemoView.h"
#include "atlimage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUSerMsgDemoView

IMPLEMENT_DYNCREATE(CUSerMsgDemoView, CView)

BEGIN_MESSAGE_MAP(CUSerMsgDemoView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_MESSAGE(UM_TESTMESSAGE, &CUSerMsgDemoView::OnTestMessage)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CUSerMsgDemoView ����/�Ҹ�

CUSerMsgDemoView::CUSerMsgDemoView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CUSerMsgDemoView::~CUSerMsgDemoView()
{
}

BOOL CUSerMsgDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CUSerMsgDemoView �׸���

void CUSerMsgDemoView::OnDraw(CDC* /*pDC*/)
{
	CUSerMsgDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CUSerMsgDemoView �μ�

BOOL CUSerMsgDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CUSerMsgDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CUSerMsgDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CUSerMsgDemoView ����

#ifdef _DEBUG
void CUSerMsgDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CUSerMsgDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUSerMsgDemoDoc* CUSerMsgDemoView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUSerMsgDemoDoc)));
	return (CUSerMsgDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CUSerMsgDemoView �޽��� ó����

LRESULT CUSerMsgDemoView::OnTestMessage(WPARAM wParam, LPARAM lParam)
{

	AfxMessageBox(_T("CUserMsgDemoView::OnTestMessage()"));

	return 0;
}

int CUSerMsgDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	if (SetTimer(10,1000,NULL) != 10)
	{

		AfxMessageBox(_T("ERROR : Failes to set timer!"));
	}
	srand((unsigned)time(NULL));

	return 0;
}


void CUSerMsgDemoView::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	KillTimer(10);
	CView::OnClose();
}


void CUSerMsgDemoView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nIDEvent == 10)
	{
		CRect Rect;
		GetClientRect(&Rect);

		if (Rect.Width() != 0 && Rect.Height() != 0)
		{
			m_nImageX = rand()%Rect.Width();
			m_nImageY = rand()%Rect.Height();
			RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW);
		}
	}
	CView::OnTimer(nIDEvent);
}


void CUSerMsgDemoView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CRect Rect;
	GetClientRect(&Rect);
	dc.FillSolidRect(&Rect,RGB(0,0,0));

	CImage Image;
	Image.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP);
	Image.BitBlt(dc.m_hDC, m_nImageX, m_nImageY, SRCCOPY);
}
