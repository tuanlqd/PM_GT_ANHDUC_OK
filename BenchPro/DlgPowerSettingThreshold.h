#pragma once
#include "afxdialogex.h"
#include "INI.h"
#include "Plan.h"


// DlgPowerSettingThreshold dialog

class DlgPowerSettingThreshold : public CDialogEx
{
	DECLARE_DYNAMIC(DlgPowerSettingThreshold)

public:
	DlgPowerSettingThreshold(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgPowerSettingThreshold();

	CIniReader* m_pcFigCIniReader;
	CPlan* m_pPlan;
	int m_User = 0;
	int m_status = 1;
	CFont* m_tfont;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POWER_SETTING_THRESHOLd };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Imax_3v3;
	CString m_Imax_5v;
	CString m_Imax_12v;
	CString m_Imax_12v_n;
	CString m_Imax_12v_cpu;
	CString m_Imax_12v_role;
	CString m_Imax_30v;
	CString m_U12v_Down;
	CString m_U12v_Up;
	CString m_U30vUP;
	CString m_U30vDown;

	afx_msg BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedExit();

	//-----------------------------------------
	afx_msg void UpdateDataToGUI();
	afx_msg void UpdateDataGUIToVar();
	afx_msg int Set_Power_Safe();
	afx_msg int	Get_Power_Safe();    // Tuan bo sung: doc gia tri hien tai nguong bao ve cua cac nguon o duoi thiet bi len
	afx_msg int UpdateStatus();

	CStatic m_BMP_IMAX_3V3;
	CStatic m_BMP_IMAX_5V;
	CStatic m_BMP_IMAX_12V;
	CStatic m_BMP_IMAX_12V_N;
	CStatic m_BMP_IMAX_12V_CPU;
	CStatic m_BMP_IMAX_12V_ROLE;
	CStatic m_BMP_IMAX_30V;
	CStatic m_BMP_U12V_DOWN;
	CStatic m_BMP_U30V_DOWN;
	CStatic m_BMP_U12V_UP;
	CStatic m_BMP_U30V_UP;
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedBtnEdit();
};
