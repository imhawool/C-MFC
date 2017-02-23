#pragma once


// CTrackWnd

class CTrackWnd : public CWnd
{
	DECLARE_DYNAMIC(CTrackWnd)

public:
	CTrackWnd();
	virtual ~CTrackWnd();

	BOOL m_bTrack;
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};


