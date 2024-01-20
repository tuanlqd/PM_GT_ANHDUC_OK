#include "pch.h"
#include "CEditSpin.h"
//#include "CMFCLogicDlg.h" 
//CEditSpin::CEditSpin()
//{
//}
//
//BEGIN_MESSAGE_MAP(CEditSpin, CEdit)
//    //{{AFX_MSG_MAP(CAutoEdit)
//    ON_WM_CHAR()
//    ON_WM_KILLFOCUS()
//    //}}AFX_MSG_MAP
//END_MESSAGE_MAP()
//
///////////////////////////////////////////////////////////////////////////////
//// Behandlungsroutinen für Nachrichten CAutoEdit 
//
//void CEditSpin::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//    if (nChar == VK_TAB || nChar == VK_RETURN)
//    {
//        if (m_pParent)
//        {
//            CMFCLogicDlg* pCMFCLogicDlg = (CMFCLogicDlg*)m_pParent;
//            CString strString;
//            GetWindowText(strString);
//            int nCol = _ttoi(strString)+2;
//            pCMFCLogicDlg->SetGridColumCount(nCol);
//        }
//        return;
//    }
//    if (nChar == VK_ESCAPE)
//    {
//        GetParent()->SetFocus();
//        return;
//    }
//    CEdit::OnChar(nChar, nRepCnt, nFlags);
//}
//void CEditSpin::OnKillFocus(CWnd* pNewWnd)
//{
//    CEdit::OnKillFocus(pNewWnd); // ALWAYS call this !
//}
