#pragma once
#include "afxdialogex.h"
#include "INI.h"


// DlgDevideSetting dialog

class DlgDevideSetting : public CDialogEx
{
	DECLARE_DYNAMIC(DlgDevideSetting)

public:
	DlgDevideSetting(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgDevideSetting();
	bool Save();
	bool Restore();
	CIniReader* m_pCIniReader;
	CImageList	m_cImageListNormal;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEVIDE_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonRemove();
	CListCtrl m_ListCtrl;
	afx_msg void OnNMClickDevideListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMRClickDevideListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
};
