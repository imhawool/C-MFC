#pragma once


// CBottomEditView ���Դϴ�.

class CBottomEditView : public CEditView
{
	DECLARE_DYNCREATE(CBottomEditView)

protected:
	CBottomEditView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CBottomEditView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


