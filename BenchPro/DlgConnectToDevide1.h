#pragma once
#include "afxdialogex.h"
#include "INI.h"

// DlgConnectToDevide dialog

class DlgConnectToDevide : public CDialog
{
	DECLARE_DYNAMIC(DlgConnectToDevide)

public:
	DlgConnectToDevide(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgConnectToDevide();

	bool save();
	bool Restore();
	CIniReader* m_pCIniReader;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONNECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonVerify();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
