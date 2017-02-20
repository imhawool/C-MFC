
// KeyMoveView.cpp : CKeyMoveView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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

// CKeyMoveView 생성/소멸

CKeyMoveView::CKeyMoveView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CKeyMoveView::~CKeyMoveView()
{
}

BOOL CKeyMoveView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CKeyMoveView 그리기

void CKeyMoveView::OnDraw(CDC* /*pDC*/)
{
	CKeyMoveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CKeyMoveView 인쇄

BOOL CKeyMoveView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CKeyMoveView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CKeyMoveView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CKeyMoveView 진단

#ifdef _DEBUG
void CKeyMoveView::AssertValid() const
{
	CView::AssertValid();
}

void CKeyMoveView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKeyMoveDoc* CKeyMoveView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKeyMoveDoc)));
	return (CKeyMoveDoc*)m_pDocument;
}
#endif //_DEBUG


// CKeyMoveView 메시지 처리기


int CKeyMoveView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_wndChild.Create(_T("STATIC"),_T("KeyMove"),WS_CHILD | WS_VISIBLE |WS_BORDER,
		CRect(200,200,300,300), this, 1234);
	//STATIC: 윈도우 타입 KeyMove: 텍스트 명시 WS_CHILD: 자식 윈도우라는 뜻 WS_VISIVLE: 화면에 표시 
	//WS_BORDER: 테두리 표시 
    //CRect: 윈도우 좌표(왼쪽 위 100/100, 오른쪽 하단 좌표 각각) 
	//This: 뷰윈도우의 포인터 1234: 임의로 지정 

	return 0;
}





void CKeyMoveView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CKeyMoveView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString strTmp = _T("");

	strTmp.Format(_T("%c"), nChar);
	m_wndChild.SetWindowText(strTmp);

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CKeyMoveView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	/*
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nChar == VK_RETURN)
		AfxMessageBox(TEXT("Alt + Enter"));
	else if(nChar == 's' || nChar == 'S')
		AfxMessageBox(TEXT("Alt + S"));
	else if(nChar == 'x' || nChar == 'X') // 실습예제4
	{
		AfxMessageBox(TEXT("Close"));
		OnClose();
	}

	CView::OnSysChar(nChar, nRepCnt, nFlags);
}




void CKeyMoveView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*실습예제1
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
	
	//실습예제2
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
	//실습예제3
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	//실습예제4
	GetParent()->PostMessage(WM_CLOSE,NULL,NULL);
	CView::OnClose();
}
