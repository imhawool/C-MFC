
// DynSplitDemoView.h : CDynSplitDemoView 클래스의 인터페이스
//

#pragma once


class CDynSplitDemoView : public CHtmlView
{
protected: // serialization에서만 만들어집니다.
	CDynSplitDemoView();
	DECLARE_DYNCREATE(CDynSplitDemoView)

// 특성입니다.
public:
	CDynSplitDemoDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CDynSplitDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	bool OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	
};

#ifndef _DEBUG  // DynSplitDemoView.cpp의 디버그 버전
inline CDynSplitDemoDoc* CDynSplitDemoView::GetDocument() const
   { return reinterpret_cast<CDynSplitDemoDoc*>(m_pDocument); }
#endif

