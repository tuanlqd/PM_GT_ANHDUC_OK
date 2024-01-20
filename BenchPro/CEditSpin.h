#pragma once
#include <afxwin.h>
class CEditSpin : public CEdit
{
public:
	CEditSpin();
	CWnd* m_pParent;
protected:
	//{{AFX_MSG(CAutoEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()	
};

