#pragma once
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
	virtual ~CRoundButton();

	CRgn   m_rgn;
	CPoint m_ptCentre;
	int    m_nRadius;
	BOOL   m_bDrawDashedFocusCircle;

	// Generated message map functions
protected:
	//{{AFX_MSG(CRoundButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
