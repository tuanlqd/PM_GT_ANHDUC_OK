// DlgPlanFileConfig.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgPlanFileConfig.h"
#include "mta_io_client.hpp"


// DlgPlanFileConfig dialog

IMPLEMENT_DYNAMIC(DlgPlanFileConfig, CDialogEx)

DlgPlanFileConfig::DlgPlanFileConfig(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PLAN_FILE_CONFIG, pParent)
{

}

DlgPlanFileConfig::~DlgPlanFileConfig()
{
}

void DlgPlanFileConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgPlanFileConfig, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_PLAN, &DlgPlanFileConfig::OnBnClickedButtonConfigPlan)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_AS_CONFIG_FILE, &DlgPlanFileConfig::OnBnClickedButtonSaveAsConfigFile)
	ON_BN_CLICKED(IDOK, &DlgPlanFileConfig::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgPlanFileConfig::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &DlgPlanFileConfig::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// DlgPlanFileConfig message handlers
BOOL DlgPlanFileConfig::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//MessageBox(_T("Plan file config"), _T("Mess"));
return TRUE;  // return TRUE unless you set the focus to a control
// EXCEPTION: OCX Property Pages should return FALSE
}


void DlgPlanFileConfig::OnBnClickedButtonConfigPlan()
{
	// TODO: Add your control notification handler code here
	CString Filename;
	CIniReader m_tIniReader;
	Filename = _T("TestCase.ini");
	m_tIniReader.setINIFileName(Filename);

	if(m_pPlan->LoadTestCase(&m_tIniReader)){
		UpdateData(false);
		MessageBox(_T("Successfull"), _T("Mess"));
	}
	else	MessageBox(_T("Error"), _T("Mess"));

}

void DlgPlanFileConfig::OnBnClickedButtonSaveAsConfigFile()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CIniReader m_tIniReader;
	m_tIniReader.setINIFileName(_T("TestCase.ini"));
	
	if (m_pPlan->SaveTestCase(&m_tIniReader, 0)){
		MessageBox(_T("Successfull"), _T("Mess"));
	}
	else	MessageBox(_T("Error"), _T("Mess"));
}


void DlgPlanFileConfig::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void DlgPlanFileConfig::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void DlgPlanFileConfig::OnBnClickedButtonSend()
{
	// TODO: Add your control notification handler code here
	byte m_pBuffSend[] = { 0x00,0x7A,0x01,0x00,0x00, 0x01,0x00,0x00};
	byte m_pBuffRecv_Ret[] = { 0x7A,0x00,0x01,0x00,0x00, 0x01,0x00,0x01,0x00};
	byte m_pBuffRecv[1024];

	//int nRet = uart_sent_data((char*)m_pBuffSend + m_HeaderFile.sendStart, m_HeaderFile.sendEnd - m_HeaderFile.sendStart, (char*)m_pBuffRecv, 1024);
	int flag = 1;
	CString Str = _T(""), tmpStr;
	int nRet = uart_sent_data((char*)m_pBuffSend, 8, (char*)m_pBuffRecv, 1024);
	if (nRet==-1) {
		MessageBox(_T("Fail rec"),_T("Mess"));
	}
	else
	{
		//Str.Format(_T("nRet = %d", nRet));
		//for (int i = 0; i < nRet; i++) {
		//	Str
		//}
			
		for (int i = 0; i < nRet; i++) {
			if (m_pBuffRecv[i] != m_pBuffRecv_Ret[i]) {
				flag = 0;
				MessageBox(_T("Fail data"), _T("Mess"));
				break;
			}
		}
		if (flag == 1) MessageBox(_T("Success!"), _T("Mess"));
	}

}
