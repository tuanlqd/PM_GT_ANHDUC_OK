#pragma once
#include "afxdialogex.h"
#include "Plan.h"

// DlgDeviceJackProperties dialog

class DlgDeviceJackProperties : public CDialogEx
{
	DECLARE_DYNAMIC(DlgDeviceJackProperties)

public:
	DlgDeviceJackProperties(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgDeviceJackProperties();

	bool InitListCtrlData();
	CImageList	m_cImageListNormal;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEVICE_JACK_PROPERTIES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_JackName;
	CString m_Jack_Sign;
	JACK_DEF m_Jack;
	CListCtrl m_ListCtrl;

	BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnNMClickListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblclkListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	
};
