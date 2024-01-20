#pragma once
#include "afxdialogex.h"
#include "INI.h"
#include "Plan.h"



// DlgPowerSetting dialog

class DlgPowerSetting : public CDialogEx
{
	DECLARE_DYNAMIC(DlgPowerSetting)

public:
	DlgPowerSetting(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgPowerSetting();

	CIniReader* m_pcFigCIniReader;
	CPlan* m_pPlan;
	int m_status;
	int m_User = 0;
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POWER_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	afx_msg BOOL OnInitDialog();


	CButton mBtnP1_OnOFF;
	CButton mBtnP2_OnOFF;
	CButton mBtnP3_OnOFF;
	CButton mBtnP4_OnOFF;
	CButton mBtnP5_OnOFF;
	CButton mBtnP6_OnOFF;
	CButton mBtnP7_OnOFF;
	CButton mBtnP8_OnOFF;

	afx_msg void OnBnClickedBtnP1OnOff();
	afx_msg void OnBnClickedBtnP2OnOff();
	afx_msg void OnBnClickedBtnP3OnOff();
	afx_msg void OnBnClickedBtnP4OnOff();
	afx_msg void OnBnClickedBtnP5OnOff();
	afx_msg void OnBnClickedBtnP6OnOff();
	afx_msg void OnBnClickedBtnP7OnOff();
	afx_msg void OnBnClickedBtnP8OnOff();

	afx_msg void InitBtnOnOff();
	afx_msg void UpdateDataToGUI();
	afx_msg int UpdateDataGUIToVar();
	afx_msg void UpdateStatus();

	//DUKKK
	//float m_UsetP1;
	CString m_UsetP1;
	CString m_UsetP2;
	CString m_UsetP3;
	CString m_UsetP4;
	CString m_UsetP5;
	CString m_UsetP6;
	CString m_UsetP7;
	CString m_UsetP8;

	CString m_UgetP1;
	CString m_UgetP2;
	CString m_UgetP3;
	CString m_UgetP4;
	CString m_UgetP5;
	CString m_UgetP6;
	CString m_UgetP7;
	CString m_UgetP8;



	CString m_Iget_P1;
	CString m_Iget_P2;
	CString m_Iget_P3;
	CString m_Iget_P4;
	CString m_Iget_P5;
	CString m_Iget_P6;
	CString m_Iget_P7;
	CString m_Iget_P8;

	CString m_ImaxSetP1;
	CString m_ImaxSetP2;
	CString m_ImaxSetP3;
	CString m_ImaxSetP4;
	CString m_ImaxSetP5;
	CString m_ImaxSetP6;
	CString m_ImaxSetP7;
	CString m_ImaxSetP8;
	afx_msg void OnBnClickedButtonSet();

	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonEnableBoard();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonSetPath();
	//-----------------------------------
	afx_msg int send_active_1_board(byte addr_board);
	afx_msg int send_active_All_board();
	afx_msg int apply_relay(byte addr_board);
	afx_msg int set_paths();
	afx_msg void OnBnClickedButtonResetPath();

	afx_msg int Reset_paths();
	afx_msg int Reset_1_paths(byte addr_board);
	afx_msg int Reset_all_paths();

	//CButton m_BTN_UGET1;
	//CButton m_BTN_UGET2;
	//CButton m_BTN_UGET3;
	//CButton m_BTN_UGET4;
	//CButton m_BTN_UGET5;
	//CButton m_BTN_UGET6;
	//CButton m_BTN_UGET7;
	//CButton m_BTN_UGET8;
	//CButton m_BTN_IGET1;
	//CButton m_BTN_IGET2;
	//CButton m_BTN_IGET3;
	//CButton m_BTN_IGET4;
	//CButton m_BTN_IGET5;
	//CButton m_BTN_IGET6;
	//CButton m_BTN_IGET7;
	//CButton m_BTN_IGET8;

	CStatic m_BMP_UGET1;
	CStatic m_BMP_UGET2;
	CStatic m_BMP_UGET3;
	CStatic m_BMP_UGET4;
	CStatic m_BMP_UGET5;
	CStatic m_BMP_UGET6;
	CStatic m_BMP_UGET7;
	CStatic m_BMP_UGET8;

	CStatic m_BMP_IGET1;
	CStatic m_BMP_IGET2;
	CStatic m_BMP_IGET3;
	CStatic m_BMP_IGET4;
	CStatic m_BMP_IGET5;
	CStatic m_BMP_IGET6;
	CStatic m_BMP_IGET7;
	CStatic m_BMP_IGET8;

	afx_msg void OnBnClickedSave();

	afx_msg void OnBnClickedReadPwrM3Value();
};
