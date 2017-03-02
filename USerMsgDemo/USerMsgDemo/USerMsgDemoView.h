
// USerMsgDemoView.h : CUSerMsgDemoView Ŭ������ �������̽�
//

#pragma once


class CUSerMsgDemoView : public CView
{
protected: // serialization������ ��������ϴ�.
	CUSerMsgDemoView();
	DECLARE_DYNCREATE(CUSerMsgDemoView)

// Ư���Դϴ�.
public:
	CUSerMsgDemoDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	int m_nImageX;
	int m_nImageY;

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
	virtual ~CUSerMsgDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
	LRESULT afx_msg OnTestMessage(WPARAM wParam, LPARAM lParam);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // USerMsgDemoView.cpp�� ����� ����
inline CUSerMsgDemoDoc* CUSerMsgDemoView::GetDocument() const
   { return reinterpret_cast<CUSerMsgDemoDoc*>(m_pDocument); }
#endif

