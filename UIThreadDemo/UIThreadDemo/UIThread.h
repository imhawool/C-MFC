#pragma once



// CUIThread

class CUIThread : public CWinThread
{
	DECLARE_DYNCREATE(CUIThread)

protected:
	CUIThread();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CUIThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
	
};


