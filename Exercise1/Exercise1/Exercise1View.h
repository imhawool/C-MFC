
// Exercise1View.h : CExercise1View Ŭ������ �������̽�
//

#pragma once


class CExercise1View : public CView
{
protected: // serialization������ ��������ϴ�.
	CExercise1View();
	DECLARE_DYNCREATE(CExercise1View)

// Ư���Դϴ�.
public:
	CExercise1Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CExercise1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // Exercise1View.cpp�� ����� ����
inline CExercise1Doc* CExercise1View::GetDocument() const
   { return reinterpret_cast<CExercise1Doc*>(m_pDocument); }
#endif

