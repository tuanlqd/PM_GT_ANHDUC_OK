#pragma once
#include "afxdialogex.h"
#include "Plan.h"


// DlgDeviceJack dialog

class DlgDeviceJack : public CDialogEx
{
	DECLARE_DYNAMIC(DlgDeviceJack)

public:
	DlgDeviceJack(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgDeviceJack();

	CImageList	m_cImageListNormal;
	CPlan* m_pPlan;

	bool InitListCtrlData();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEVICE_JACK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonRemove();
	
	afx_msg void OnLvnItemchangedListCrtl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickListCrtl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMRClickListCrtl(NMHDR* pNMHDR, LRESULT* pResult);

	CListCtrl m_ListCtrl;
	CString m_BoardName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnSua();
	afx_msg void Init_CB();
	CComboBox m_CB_ID_Jack;
	afx_msg void OnCbnSelchangeCmbIdJack();
};
