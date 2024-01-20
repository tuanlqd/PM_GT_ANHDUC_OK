#pragma once
#include "afxdialogex.h"


// DlgConnectToDevideAdd dialog

class DlgConnectToDevideAdd : public CDialogEx
{
	DECLARE_DYNAMIC(DlgConnectToDevideAdd)

public:
	DlgConnectToDevideAdd(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgConnectToDevideAdd();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONNECT_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString	m_DevideName;
	CIPAddressCtrl m_IPDevide;
	unsigned int m_DevidePort;
	unsigned int m_LocalPort;
	BYTE m_FieldIPDevide[4];
	  
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
