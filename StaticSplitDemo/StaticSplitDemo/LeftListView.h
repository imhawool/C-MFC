#pragma once


// CLeftListView 뷰입니다.

class CLeftListView : public CListView
{
	DECLARE_DYNCREATE(CLeftListView)

protected:
	CLeftListView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CLeftListView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


