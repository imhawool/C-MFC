
// TrayDemoDoc.cpp : CTrayDemoDoc 클래스의 구현
//

#include "stdafx.h"
#include "TrayDemo.h"

#include "TrayDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrayDemoDoc

IMPLEMENT_DYNCREATE(CTrayDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CTrayDemoDoc, CDocument)
END_MESSAGE_MAP()


// CTrayDemoDoc 생성/소멸

CTrayDemoDoc::CTrayDemoDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CTrayDemoDoc::~CTrayDemoDoc()
{
}

BOOL CTrayDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CTrayDemoDoc serialization

void CTrayDemoDoc::Serialize(CArchive& ar)
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


// CTrayDemoDoc 진단

#ifdef _DEBUG
void CTrayDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTrayDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTrayDemoDoc 명령
