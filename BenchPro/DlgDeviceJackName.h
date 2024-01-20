#pragma once
#include "afxdialogex.h"
#include "Plan.h"


// DlgDeviceJackName dialog

class DlgDeviceJackName : public CDialogEx
{
	DECLARE_DYNAMIC(DlgDeviceJackName)

public:
	DlgDeviceJackName(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgDeviceJackName();

	CPlan* m_pPlan;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEVICE_JACK_NAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl *m_ListCtrl;
	CString m_Symbol, m_Symbol_old;
	CString m_JackName;
	CString m_BoardName; //Pre name

	bool CheckName;
	afx_msg BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	bool ExistName(CString JackName);
	//CString m_Jack_ID;
};
