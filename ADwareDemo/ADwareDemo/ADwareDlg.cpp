// ADwareDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ADwareDemo.h"
#include "ADwareDlg.h"


// CADwareDlg dialog

IMPLEMENT_DYNCREATE(CADwareDlg, CDHtmlDialog)

CADwareDlg::CADwareDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CADwareDlg::IDD, CADwareDlg::IDH, pParent)
{

}

CADwareDlg::~CADwareDlg()
{
}

void CADwareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL CADwareDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	Navigate(_T("http://www.freelec.co.kr"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CADwareDlg, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CADwareDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// CADwareDlg message handlers

HRESULT CADwareDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CADwareDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}
