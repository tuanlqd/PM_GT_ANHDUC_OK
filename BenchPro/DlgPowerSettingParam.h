#pragma once
#include "afxdialogex.h"
#include "INI.h"
#include "Plan.h"

// DlgPowerSettingParam dialog

class DlgPowerSettingParam : public CDialogEx
{
	DECLARE_DYNAMIC(DlgPowerSettingParam)

public:
	DlgPowerSettingParam(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgPowerSettingParam();

	CIniReader* m_pIniReader;
	CPlan* m_pPlan;
	CImageList m_ImageList;
	CBitmap cBmpOK, cBmpERR, cBmpNM;
	int m_numChanel;
	byte m_Setmode = 1; // 1/2
	int nSelHV1, nSelHV2, nSelSYS1, nSelSYS2, nSelADC1, nSelADC2, nSelDAC1, nSelDAC2;
	byte ChanelSelArr1[95];
	byte ChanelSelArr2[95];
	byte ChanelPinArr[95];
	CFont* m_sfont;
	CFont* m_bfont;
	CFont* m_tfont;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POWER_SETTING_PARAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_HV_OUT1_name;
	CString m_HV_OUT2_name;
	CString m_HV_IN1_name;
	CString m_HV_IN2_name;
	CString m_IOEXT_1_name;
	CString m_IOEXT_2_name;

	CString m_ADC1_name;
	CString m_ADC2_name;
	CString m_DAC1_name;
	CString m_DAC2_name;
	CString m_V_Hi_LOGIC_OUT_name;
	CString m_V_CMP_LOGIC_IN_name;
	//----------------------------------------
	CString m_HV_OUT1;
	CString m_HV_OUT2;
	CString m_HV_IN1;
	CString m_HV_IN2;
	CString m_IOEXT_1;
	CString m_IOEXT_2;
	

	CString m_ADC1;
	CString m_ADC2;
	CString m_DAC1;
	CString m_DAC2;
	CString m_V_Hi_LOGIC_OUT;
	CString m_V_CMP_LOGIC_IN;

	CStatic m_BMP_HV_OUT1;
	CStatic m_BMP_HV_OUT2;
	CStatic m_BMP_HV_IN1;
	CStatic m_BMP_HV_IN2;
	CStatic m_BMP_IOEXT_1;
	CStatic m_BMP_IOEXT_2;

	CStatic m_BMP_ADC1;
	CStatic m_BMP_ADC2;
	CStatic m_BMP_DAC1;
	CStatic m_BMP_DAC2;
	CStatic m_BMP_V_Hi_LOGIC_OUT;
	CStatic m_BMP_V_CMP_LOGIC_IN;

	CStatic m_BMP_HV_OUT1_Ico;
	CStatic m_BMP_HV_OUT2_Ico;
	CStatic m_BMP_HV_IN1_Ico;
	CStatic m_BMP_HV_IN2_Ico;
	CStatic m_BMP_IOEXT_1_Ico;
	CStatic m_BMP_IOEXT_2_Ico;

	CStatic m_BMP_ADC1_Ico;
	CStatic m_BMP_ADC2_Ico;
	CStatic m_BMP_DAC1_Ico;
	CStatic m_BMP_DAC2_Ico;
	CStatic m_BMP_V_Hi_LOGIC_OUT_Ico;
	CStatic m_BMP_V_CMP_LOGIC_IN_Ico;

	afx_msg BOOL OnInitDialog();
	afx_msg void UpdateDataToGUI();
	afx_msg int UpdateDataGUIToVar();
	afx_msg void UpdateStatus(int);
	afx_msg int Set_Get_Power_Param();

	afx_msg void OnBnClickedBtnSet();
	afx_msg void OnBnClickedOk();

	afx_msg void Init_CB_Value_ADC();

	afx_msg void Init_CB_M1(int);
	afx_msg void Init_CB_M2(int);
	afx_msg int ChanelToNum(CString strTmp);
	// ----------------------------------

	CComboBox m_HV_IN1_Cb;
	CComboBox m_HV_IN2_Cb;
	CComboBox m_IOEXT_1_Cb;
	CComboBox m_IOEXT_2_Cb;

	CComboBox m_Value_ADC1_Cb;
	CComboBox m_Value_ADC2_Cb;

	CComboBox m_ADC1_Cb;
	CComboBox m_ADC2_Cb;
	CComboBox m_DAC1_Cb;
	CComboBox m_DAC2_Cb;
	//-------------------------------------
	CButton m_Chk_HV_OUT1;
	CButton m_Chk_HV_OUT2;
	CButton m_Chk_HV_IN1;
	CButton m_Chk_HV_IN2;
	CButton m_Chk_IOEXT_2;
	CButton m_Chk_IOEXT_1;

	CButton m_Chk_DAC2;
	CButton m_Chk_DAC1;
	CButton m_Chk_ADC2;
	CButton m_Chk_ADC1;
	afx_msg void OnBnClickedButton1();
	//afx_msg void OnBnClickedBtnEdit();
	afx_msg void OnBnClickedBttnSave();
	
	//afx_msg void OnBnClickedBtnGetinfo();
	afx_msg void OnCbnSelchangeComboHvIn1();
	afx_msg void OnCbnSelchangeComboHvIn2();
	afx_msg void OnCbnSelchangeComboAdc1();
	afx_msg void OnCbnSelchangeComboAdc2();
	afx_msg void OnCbnSelchangeComboDac1();
	afx_msg void OnCbnSelchangeComboDac2();
	CEdit c_EDIT_TITLE;
	CButton m_radio1;
	CButton m_Radio2;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnEnChangeEditTitle();
	afx_msg void OnCbnSelchangeComboValueADC1();
	afx_msg void OnCbnSelchangeComboValueADC2();
};
