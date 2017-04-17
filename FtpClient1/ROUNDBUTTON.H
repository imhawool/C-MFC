#if !defined(AFX_ROUNDBUTTON_H__5254170E_59CF_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_ROUNDBUTTON_H__5254170E_59CF_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RoundButton.h : header file
//
// Round buttons!
//
// Written by Chris Maunder (Chris.Maunder@cbr.clw.csiro.au)
// Copyright (c) 1998.
//
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CRoundButton window


class CRoundButton : public CButton
{
// Construction
public:
	CRoundButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoundButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetRoundTextColor(COLORREF color);
	virtual ~CRoundButton();

	CRgn   m_rgn;
	CPoint m_ptCentre;
	CPoint m_ptLeft;
	CPoint m_ptRight;
	int    m_nRadius;
	BOOL   m_bDrawDashedFocusCircle;
	BOOL   m_bStretch;
	COLORREF m_TextColor;

	// Generated message map functions
protected:
	//{{AFX_MSG(CRoundButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUNDBUTTON_H__5254170E_59CF_11D1_ABBA_00A0243D1382__INCLUDED_)
