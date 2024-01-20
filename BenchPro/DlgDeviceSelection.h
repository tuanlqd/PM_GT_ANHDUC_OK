#pragma once
#include "INI.h"
#include "afxdialogex.h"
#include <vector>


// DlgDeviceSelection dialog

class DlgDeviceSelection : public CDialogEx
{
	DECLARE_DYNAMIC(DlgDeviceSelection)

public:
	DlgDeviceSelection(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgDeviceSelection();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEVICE_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSelection();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	//virtual BOOL OnInitDialog();
	CListCtrl m_ListCtrl;
	CImageList m_cImageListNormal;
	CIniReader* m_pCIniReader;
private:
	//bool Save();
	//bool Restore();

};
