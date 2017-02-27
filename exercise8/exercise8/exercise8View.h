
// exercise8View.h : Cexercise8View 클래스의 인터페이스
//

#pragma once


class Cexercise8View : public CView
{
protected: // serialization에서만 만들어집니다.
	Cexercise8View();
	DECLARE_DYNCREATE(Cexercise8View)

// 특성입니다.
public:
	Cexercise8Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~Cexercise8View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // exercise8View.cpp의 디버그 버전
inline Cexercise8Doc* Cexercise8View::GetDocument() const
   { return reinterpret_cast<Cexercise8Doc*>(m_pDocument); }
#endif

