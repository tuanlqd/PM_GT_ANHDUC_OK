#pragma once
#include "afxdialogex.h"
#include "INI.h"
#include "Plan.h"


// DlgPlanFileConfig dialog

class DlgPlanFileConfig : public CDialogEx
{
	DECLARE_DYNAMIC(DlgPlanFileConfig)

public:
	DlgPlanFileConfig(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgPlanFileConfig();

	CIniReader*		  m_pcFigCIniReader;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PLAN_FILE_CONFIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CPlan *m_pPlan;
	BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonConfigPlan();
	afx_msg void OnBnClickedButtonSaveAsConfigFile();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonSend();
};
