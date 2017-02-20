
// KeyMoveView.cpp : CKeyMoveView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "KeyMove.h"
#endif

#include "KeyMoveDoc.h"
#include "KeyMoveView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKeyMoveView

IMPLEMENT_DYNCREATE(CKeyMoveView, CView)

BEGIN_MESSAGE_MAP(CKeyMoveView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
//	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CHAR()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSCHAR()
//	ON_WM_SIZE()
ON_WM_KEYDOWN()
ON_WM_CLOSE()
END_MESSAGE_MAP()

// CKeyMoveView ����/�Ҹ�

CKeyMoveView::CKeyMoveView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CKeyMoveView::~CKeyMoveView()
{
}

BOOL CKeyMoveView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CKeyMoveView �׸���

void CKeyMoveView::OnDraw(CDC* /*pDC*/)
{
	CKeyMoveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CKeyMoveView �μ�

BOOL CKeyMoveView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CKeyMoveView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CKeyMoveView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CKeyMoveView ����

#ifdef _DEBUG
void CKeyMoveView::AssertValid() const
{
	CView::AssertValid();
}

void CKeyMoveView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKeyMoveDoc* CKeyMoveView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKeyMoveDoc)));
	return (CKeyMoveDoc*)m_pDocument;
}
#endif //_DEBUG


// CKeyMoveView �޽��� ó����


int CKeyMoveView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_wndChild.Create(_T("STATIC"),_T("KeyMove"),WS_CHILD | WS_VISIBLE |WS_BORDER,
		CRect(200,200,300,300), this, 1234);
	//STATIC: ������ Ÿ�� KeyMove: �ؽ�Ʈ ��� WS_CHILD: �ڽ� �������� �� WS_VISIVLE: ȭ�鿡 ǥ�� 
	//WS_BORDER: �׵θ� ǥ�� 
    //CRect: ������ ��ǥ(���� �� 100/100, ������ �ϴ� ��ǥ ����) 
	//This: ���������� ������ 1234: ���Ƿ� ���� 

	return 0;
}





void CKeyMoveView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CKeyMoveView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CString strTmp = _T("");

	strTmp.Format(_T("%c"), nChar);
	m_wndChild.SetWindowText(strTmp);

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CKeyMoveView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	/*
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CString strMessage = TEXT("");

	WORD wResult = ::GetKeyState(VK_SPACE);
	BYTE byHigh = HIBYTE(wResult);
	if(byHigh & 0x01);
	{
		strMessage += TEXT("Alt + Space");
		wResult = ::GetKeyState(VK_CAPITAL);
		BYTE byLow = LOBYTE(wResult);
		if(byLow & 0x01)	strMessage += TEXT("CAPS LOCK ON");
		else strMessage += TEXT("CAPS LOCK OFF");
	
		AfxMessageBox(strMessage);
	}

	CView::OnSysKeyDown(nChar, nRepCnt, nFlags);
	*/
}


void CKeyMoveView::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(nChar == VK_RETURN)
		AfxMessageBox(TEXT("Alt + Enter"));
	else if(nChar == 's' || nChar == 'S')
		AfxMessageBox(TEXT("Alt + S"));
	else if(nChar == 'x' || nChar == 'X') // �ǽ�����4
	{
		AfxMessageBox(TEXT("Close"));
		OnClose();
	}

	CView::OnSysChar(nChar, nRepCnt, nFlags);
}




void CKeyMoveView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	/*�ǽ�����1
	CPoint ptChild;
	CRect Rect;
	m_wndChild.GetWindowRect(&Rect);

	ptChild.x = Rect.left;
	ptChild.y = Rect.top;

	ScreenToClient(&ptChild);

	switch(nChar)
	{
	case VK_LEFT:
		ptChild.x -= 10;
		break;
	case VK_RIGHT:
		ptChild.x += 10;
		break;
	case VK_UP:
		ptChild.y -= 10;
		break;
	case VK_DOWN:
		ptChild.y += 10;
		break;
	}
	
	m_wndChild.SetWindowPos(&CWnd::wndTop, ptChild.x,ptChild.y,0,0,
		SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	
	//�ǽ�����2
	CPoint ptChild;
	CRect Rect;
	m_wndChild.GetWindowRect(&Rect);

	ptChild.x = Rect.left;
	ptChild.y = Rect.top;

	ScreenToClient(&ptChild);
	
	if((nChar == VK_LEFT) && (::GetKeyState(VK_CONTROL)<0))
	{
		ptChild.x -= 50;
	}
	else if((nChar == VK_RIGHT) && (::GetKeyState(VK_CONTROL)<0))
	{
		ptChild.x += 50;
	}
	else if((nChar == VK_UP) && (::GetKeyState(VK_CONTROL)<0))
	{
		ptChild.y -= 50;
	}
	else if((nChar == VK_DOWN) && (::GetKeyState(VK_CONTROL)<0))
	{
		ptChild.y += 50;
	}
	
	switch(nChar)
	{
	case VK_LEFT:
		ptChild.x -= 10;
		break;
	case VK_RIGHT:
		ptChild.x += 10;
		break;
	case VK_UP:
		ptChild.y -= 10;
		break;
	case VK_DOWN:
		ptChild.y += 10;
		break;
	}

	m_wndChild.SetWindowPos(&CWnd::wndTop, ptChild.x,ptChild.y,0,0,
		SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	*/
	//�ǽ�����3
	CPoint ptChild;
	CRect Rect;
	CSize  sizeChild;

	m_wndChild.GetWindowRect(&Rect);

	ptChild.x = Rect.left;
	ptChild.y = Rect.top;
	sizeChild.cx = Rect.right - Rect.left;
	sizeChild.cy = Rect.bottom - Rect.top;
	ScreenToClient(&ptChild);

	switch(nChar)
	{
	case VK_LEFT:
		sizeChild.cx -= 100;
		break;
	case VK_RIGHT:
		sizeChild.cx += 100;
		break;
	case VK_UP:
		sizeChild.cy -= 100;
		break;
	case VK_DOWN:
		sizeChild.cy += 100;
		break;
	
	}

	CString debugOut = "";

	debugOut.Format("p1 x[%d] y[%d] \r\n",  (int)ptChild.x, (int)ptChild.y);
	TRACE(debugOut);

	debugOut.Format("p2 x[%d] y[%d] \r\n",  (int)sizeChild.cx, (int)sizeChild.cy);
	TRACE(debugOut);


	m_wndChild.SetWindowPos(&CWnd::wndTop, ptChild.x,ptChild.y,	200, 200,
		SWP_SHOWWINDOW | SWP_NOZORDER);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	
}


void CKeyMoveView::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	//�ǽ�����4
	GetParent()->PostMessage(WM_CLOSE,NULL,NULL);
	CView::OnClose();
}
