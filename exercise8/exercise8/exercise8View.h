
// exercise8View.h : Cexercise8View Ŭ������ �������̽�
//

#pragma once


class Cexercise8View : public CView
{
protected: // serialization������ ��������ϴ�.
	Cexercise8View();
	DECLARE_DYNCREATE(Cexercise8View)

// Ư���Դϴ�.
public:
	Cexercise8Doc* GetDocument() const;

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
	virtual ~Cexercise8View();
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

#ifndef _DEBUG  // exercise8View.cpp�� ����� ����
inline Cexercise8Doc* Cexercise8View::GetDocument() const
   { return reinterpret_cast<Cexercise8Doc*>(m_pDocument); }
#endif

