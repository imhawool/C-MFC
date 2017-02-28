#pragma once

#ifdef _WIN32_WCE
#error "CDHtmlDialog is not supported for Windows CE."
#endif 

// CADwareDlg dialog

class CADwareDlg : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CADwareDlg)

public:
	CADwareDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CADwareDlg();
// Overrides
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// Dialog Data
	enum { IDD = IDD_Form_ADware, IDH = IDR_HTML_ADWAREDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
