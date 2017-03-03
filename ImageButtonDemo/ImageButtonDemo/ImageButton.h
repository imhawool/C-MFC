#pragma once


// CImageButton

class CImageButton : public CButton
{
	DECLARE_DYNAMIC(CImageButton)

public:
	CImageButton();
	virtual ~CImageButton();

	BOOL	m_bHover;
	BOOL	m_bTracking;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


