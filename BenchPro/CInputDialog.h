#pragma once
#include "afxdialogex.h"


// CInputDialog dialog

class CInputDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CInputDialog)

public:
	CInputDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CInputDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAG_PASSWORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Edit_Password;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
