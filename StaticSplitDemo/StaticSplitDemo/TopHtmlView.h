#pragma once


// CTopHtmlView ���Դϴ�.

class CTopHtmlView : public CHtmlEditView
{
	DECLARE_DYNCREATE(CTopHtmlView)

protected:
	CTopHtmlView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CTopHtmlView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	void OnInitialUpdate(void);
};


