#pragma once
#include "afxdialogex.h"


// DlgConnectToDevideConnect dialog

class DlgConnectToDevideConnect : public CDialogEx
{
	DECLARE_DYNAMIC(DlgConnectToDevideConnect)

public:
	DlgConnectToDevideConnect(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgConnectToDevideConnect();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONNECT_DEVIDECONNCET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Log;
	CString m_strConnect;
	unsigned int m_nTimeOut;
	int* pFlagConnected;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
