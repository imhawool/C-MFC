
// RedrawDemoDoc.cpp : CRedrawDemoDoc 클래스의 구현
//

#include "stdafx.h"
#include "RedrawDemo.h"

#include "RedrawDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRedrawDemoDoc

IMPLEMENT_DYNCREATE(CRedrawDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CRedrawDemoDoc, CDocument)
END_MESSAGE_MAP()


// CRedrawDemoDoc 생성/소멸

CRedrawDemoDoc::CRedrawDemoDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CRedrawDemoDoc::~CRedrawDemoDoc()
{
}

BOOL CRedrawDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CRedrawDemoDoc serialization

void CRedrawDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CRedrawDemoDoc 진단

#ifdef _DEBUG
void CRedrawDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRedrawDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRedrawDemoDoc 명령
