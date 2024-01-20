#pragma once
#include "afxdialogex.h"

#include "INI.h"
#include <vector>

// DlgPinSetting dialog

class DlgPinSetting : public CDialogEx
{
	DECLARE_DYNAMIC(DlgPinSetting)

public:
	DlgPinSetting(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgPinSetting();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PIN_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonRemove();

	virtual BOOL OnInitDialog();
	CListCtrl m_ListCtrl;
	CImageList m_cImageListNormal;
	CIniReader* m_pCIniReader;
	afx_msg void OnNMDblclkListCtrl(NMHDR* pNMHDR, LRESULT* pResult);

private:
	bool Save();
	bool Restore();
public:
	afx_msg void OnNMClickListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonSetpinChanel();
};
