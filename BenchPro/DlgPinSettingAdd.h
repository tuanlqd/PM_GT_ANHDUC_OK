#pragma once
#include "afxdialogex.h"
#include "INI.h"
#include "./GridCtrl_src/GridCtrl.h"
#include "NewCellTypes/GridCellCombo.h"


// DlgPinSettingAdd dialog

class DlgPinSettingAdd : public CDialogEx
{
	DECLARE_DYNAMIC(DlgPinSettingAdd)

public:
	DlgPinSettingAdd(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgPinSettingAdd();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PIN_SETTING_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CIniReader* m_pCIniReader;
	CString m_Name;
	CString m_BoardSelect;
	CString m_PowerSelect;

	CListCtrl* m_ListCtrl;
	
	CComboBox m_CmbBoard;
	CComboBox m_CmbPower;

	CGridCtrl m_Grid;

	afx_msg bool GetPowerList();
	afx_msg bool GetBoardList();
	afx_msg bool ExistName(CString Name);
	afx_msg void InitPinChanelLogic();
	afx_msg bool cmpStr(CString str1, CString str2);
};
