// DlgTestOnBoard.cpp : implementation file
//
#include <stdio.h>

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgTestOnBoard.h"

#include "DlgConnectToDevide.h"
#include "DlgPowerSetting.h"
#include "DlgPowerSettingThreshold.h"
#include "DlgPinSettingEdit.h"
#include "DlgChanelSelection.h"

#include "mta_io_client.hpp"

// DlgTestOnBoard dialog



IMPLEMENT_DYNAMIC(DlgTestOnBoard, CDialogEx)

std::string toUtf8(const std::wstring& str)
{
	std::string ret;
	int len = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0, NULL, NULL);
	if (len > 0)
	{
		ret.resize(len);
		WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), &ret[0], len, NULL, NULL);
	}
	return ret;
}
BOOL DlgTestOnBoard::IsFileExists(const CString& filePath) {
	CFileStatus fileStatus;
	return CFile::GetStatus(filePath, fileStatus);
}
int DlgTestOnBoard::OpenTestCase() {
	m_pCIniReader->setINIFileName(_T(""));
	m_pCPlan->Load_PhiFileConfigPath(m_pCIniReader);
	//-------------------------------------------------------------
	//if (!IsFileExists(m_pCPlan->mTestCase.mPathInfo.PhiFileConfigPath)) {
	//	MessageBox(_T("LỖI: Lỗi ghi file \r\nXem lại đường dẫn:\r\n") + m_pCPlan->mTestCase.mPathInfo.PhiFileConfigPath, _T("Thông báo"));
	////DUkkkkkkkkkkkkkkkk
	//}
	//------------------------------------------
	m_pCIniReader->setTestCaseFileName(m_pCPlan->mTestCase.mPathInfo.PhiFileConfigPath);  // PATH  Phi
	m_pCPlan->Load_UserName_UserPath(m_pCIniReader);
	m_Username = s_NguoiKT+_T(" ") + m_pCPlan->mTestCase.mPathInfo.Usermane;
	UpdateData(FALSE);
	//--------------------------------------
	m_pCPlan->InitJavaPath(m_pCPlan->mTestCase.mPathInfo.PhiPath);
	m_pCPlan->InitMFCPath();
	//--------------------------------------
	m_pCIniReader->setTestCaseFileName(m_pCPlan->mTestCase.mPathInfo.FullPath);
	//////--------------------------------------------
	//if (iRet != 1) {
	//	MessageBox(_T("LỖI: Lỗi ghi file \r\nXem lại đường dẫn:\r\n") + ThanhFileName, _T("Thông báo"));
	//	return;
	//}

	m_pCPlan->LoadTestCase(m_pCIniReader);
	m_pCPlan->OrderRun = 1;

	if (m_pCPlan->Check_MapPinArr()) {
		MessageBox(_T("Trong dữ liệu thiết lập sai chân - kênh"), _T("Cảnh báo"));
		m_pCPlan->New_PinGrid_GridHeader_GUIGridArr();
		m_pCPlan->New_ChanelGridArr();
	}
	else {
		if (m_pCPlan->Check_ChanelSelectArr()) MessageBox(_T("Thiết lập sai"), _T("Cảnh báo"));
		if (m_pCPlan->Check_ChanelConfigArr()) MessageBox(_T("Thiết lập sai"), _T("Cảnh báo"));

		if (m_pCPlan->Check_ChanelSelectArr() || m_pCPlan->Check_ChanelConfigArr()) {
			MessageBox(_T("Thiết lập sai thuộc tính kênh"), _T("Cảnh báo"));
			m_pCPlan->Init_PinGrid_GridHeader_GUIGridArr();
			m_pCPlan->New_ChanelGridArr();
		}
		else
		{
			m_pCPlan->Init_PinGrid_GridHeader_GUIGridArr();
			m_pCPlan->Init_ChanelGridArr();
		}
	}
	return 1;
}
DlgTestOnBoard::DlgTestOnBoard(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_TESTONBOARD, pParent)
{
}

DlgTestOnBoard::~DlgTestOnBoard()
{
	KillTimer(m_timer);
}


void DlgTestOnBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_SENDTOTHANH, m_BtnSendThanh);
	DDX_Control(pDX, IDC_PROGRESS, m_ProgressCtrl);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_Username);
}


BEGIN_MESSAGE_MAP(DlgTestOnBoard, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_POWER_SETTING, &DlgTestOnBoard::OnBnClickedBtnPowerSetting)
	ON_BN_CLICKED(IDC_BTN_RECONNECT, &DlgTestOnBoard::OnBnClickedBtnReconnect)
	ON_BN_CLICKED(IDC_BTN_POWER_THRESHOL, &DlgTestOnBoard::OnBnClickedBtnPowerThreshol)
	ON_BN_CLICKED(IDC_BTN_PINSELECT, &DlgTestOnBoard::OnBnClickedBtnPinselect)
	ON_BN_CLICKED(IDC_BTN_KT_CN, &DlgTestOnBoard::OnBnClickedBtnKtCn)
	ON_BN_CLICKED(IDC_BTN_EXIT, &DlgTestOnBoard::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_RESET_PATH, &DlgTestOnBoard::OnBnClickedBtnResetPath)
	ON_BN_CLICKED(IDC_BTN_EXIT2, &DlgTestOnBoard::OnBnClickedBtnExit2)
END_MESSAGE_MAP()

// DlgTestOnBoard message handlers
BOOL DlgTestOnBoard::OnInitDialog()
{
	m_pCIniReader->setINIFileName(_T(""));
	CString strSection;
	CString strValue, strKey;
	int mlength = 5;
	if (m_pCIniReader != NULL) {
		strSection = _T("DEFINE_STRINGFORM");
		strKey = _T("user_s_SubTitle");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_SubTitle = strValue;
		strKey = _T("user_s_MainTitle");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_MainTitle = strValue;
		strKey = _T("user_s_KTketnoi");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_KTketnoi = strValue;
		strKey = _T("user_s_TLThanSoThietBi");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_TLThanSoThietBi = strValue;
		strKey = _T("user_s_TLDinhTuyenVaThamSoTinHieu");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_TLDinhTuyenVaThamSoTinHieu = strValue;
		strKey = _T("user_s_NguonCap");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_NguonCap = strValue;
		strKey = _T("user_s_ChayKiemTraCN");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_ChayKiemTraCN = strValue;
		strKey = _T("user_s_XoaDinhTuyen");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_XoaDinhTuyen = strValue;
		strKey = _T("user_s_Thoat");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_Thoat = strValue;
		strKey = _T("user_s_NguoiKT");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if ((strValue.GetLength() >= mlength)&& (m_User == 1)) s_NguoiKT = strValue;
	}
	//===========================================

	CEdit* pEditCtrl;
	CButton* pButtonCtrl;
	this->SetWindowTextW(s_SubTitle);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_RECONNECT);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_KTketnoi);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_POWER_THRESHOL);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_TLThanSoThietBi);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_PINSELECT);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_TLDinhTuyenVaThamSoTinHieu);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_POWER_SETTING);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_NguonCap);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_KT_CN);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_ChayKiemTraCN);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_RESET_PATH);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_XoaDinhTuyen);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_EXIT);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_Thoat);

	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_MAIN_TITLE_U);
	pEditCtrl->SetFont(m_bfont);
	pEditCtrl->SetWindowTextW(s_MainTitle);
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_USERNAME);
	pEditCtrl->SetFont(m_sfont);
	if (m_User == 1) flagOpen = OpenTestCase();  

	this->BringWindowToTop();
	UpdateData(FALSE);
	//--------------------------
	m_pCPlan->p_ProgressCtrl = &m_ProgressCtrl;
	m_ProgressCtrl.SetRange(0, 100);
	m_ProgressCtrl.SetStep(1);
	//m_timer = SetTimer(1, 1, NULL);
	//--------------------------
	return TRUE;
}

void DlgTestOnBoard::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == m_timer)
	{
		int currentPosition = m_ProgressCtrl.GetPos();
		currentPosition += 1;
		m_ProgressCtrl.SetPos(currentPosition);
		if (currentPosition >= 100)
		{
			KillTimer(m_timer);
		}
	}
	
	CDialogEx::OnTimer(nIDEvent);
}
void DlgTestOnBoard::OnBnClickedBtnReconnect()
{
	// TODO: Add your control notification handler code here
	//m_pCPlan->SetPhanTramProgress(2);
	//------------------------------
	if (m_User) {
		m_pCIniReader->setINIFileName(_T(""));
		DlgConnectToDevide mDlgConnectToDevide;
		mDlgConnectToDevide.m_pCIniReader = m_pCIniReader;
		mDlgConnectToDevide.pFlagConnected = pFlagConnected;
		mDlgConnectToDevide.p_nfont = m_nfont;
		mDlgConnectToDevide.pPubstrAdrressConn = pPubstrAdrressConn;
		if (mDlgConnectToDevide.DoModal() == IDOK)
		{
			//connect
		}
		m_pCIniReader->setTestCaseFileName(m_pCPlan->mTestCase.mPathInfo.FullPath);
	}
	else {
		CString m_strConnect;
		//m_strConnect = m_pCPlan->strAdrressConn;
		m_strConnect = *pPubstrAdrressConn;
		int m_nTimeOut = 2000;
		CT2A ascii(m_strConnect, CP_UTF8);
		int nRet = set_baseUrl(ascii.m_psz, m_nTimeOut);
		if (nRet != 0) {
			*pFlagConnected = ERR;
			AfxMessageBox(_T("LỖI: Mất kết nối giữa máy tính và thiết bị!!! "));
		}
		else {
			*pFlagConnected = OK;
			//if (AfxMessageBox(_T("Trạng thái kết nối tốt!\n\r Bắt đầu cấu hình thiết bị?"), MB_OKCANCEL))  
			if (AfxMessageBox(_T("Trạng thái kết nối tốt!\n\r Bắt đầu cấu hình thiết bị?"), MB_OKCANCEL) != IDOK)  //  MB_OKCANCEL
			{
				// khi chon Cancel hoac Close
				// MessageBox(_T("Canceled / Closed"), _T("mess"));
				return;
			}
			 
		}
	}
	//-------------------------------
	if (!((*pFlagConnected == OK) || (*p_mode == DEBUGNORMAL) || (*p_mode == DEBUGADMIN) || (*p_mode == DEBUGUSER))) return;
	
	//if (*pFlagConnected == OK) MessageBox(_T("OK"),_T("mess"));
	//else MessageBox(_T("OK"), _T("mess"));

	//StatusConnect = ERR;
	m_pCPlan->CAN_Network_Flag_Connected = ERR;

	CString stmp;
	//-----------------------------------
	m_pCPlan->SetPhanTramProgress(5);
	//-----------------------------------
	int nRet = m_pCPlan->ping_network_to_1_board(ADDR_M6_0);
	if (nRet == 0) {
		m_pCPlan->CAN_Network_Flag_Connected = ERR;
		AfxMessageBox(_T("LỖI: Không kết nối được khối  - M6 "));
	}
	else
	{
		m_pCPlan->CAN_Network_Flag_Connected = OK;
		// ---------------------- Tuan code ------------------------- 1
		//	// kiem tra vi tri cac khe ca

		nRet = m_pCPlan->send_active_All_board();
		if (nRet != 0) {
				m_pCPlan->CAN_Network_Flag_Connected = ERR;
				stmp.Format(_T("LỖI: <Khối chức năng THỨ [%d]> : Bị lỗi kết nối hoặc cắm nhầm vị trí"), nRet);
				AfxMessageBox(stmp);
			}
		

		if (m_pCPlan->CAN_Network_Flag_Connected == OK)
		{
			MessageBox(_T("THIẾT BỊ ĐÃ SẴN SÀNG HỌAT ĐỘNG! "), _T("Thông báo"));
		}
	}
		
	if ((m_pCPlan->CAN_Network_Flag_Connected == OK) || (*p_mode == DEBUGADMIN) || (*p_mode == DEBUGNORMAL) || (*p_mode == DEBUGUSER))
	{
		CWnd* pwnd = GetDlgItem(IDC_BTN_POWER_THRESHOL);
		if (pwnd)
			pwnd->EnableWindow(true);
	}
	
}

void DlgTestOnBoard::OnBnClickedBtnPowerThreshol()
{
	//====================================================
	// TODO: Add your control notification handler code here
	int nResult = 0;
	
	if (m_pCPlan->CAN_Network_Flag_Connected == OK || *p_mode == DEBUGADMIN || *p_mode == DEBUGUSER) {
		DlgPowerSettingThreshold mDlgPowerSettingThreshold;
		mDlgPowerSettingThreshold.m_pcFigCIniReader = m_pCIniReader;
		mDlgPowerSettingThreshold.m_pPlan = m_pCPlan;
		mDlgPowerSettingThreshold.m_User = 1;
		mDlgPowerSettingThreshold.DoModal();
		int mstatus = mDlgPowerSettingThreshold.m_status;
		//-----------Tuan code ---------- 2
		// BTN thiet lap tham so thiet bi
		/*
		1. thiet lap gia tri nguon bao ve cho he thong
		*/
		//nResult = StatusConnect + mstatus - 1;
		nResult = mstatus;
		if (nResult == OK) {
			MessageBox(_T("Thiết lập các ngưỡng cho nguồn thành công"));
		}
		else {
			AfxMessageBox(_T("LỖI: Thiết lập không thành công"));
		}
	}
	if ((nResult == OK) || (*p_mode == DEBUGNORMAL) || (*p_mode == DEBUGADMIN) || (*p_mode == DEBUGUSER)) {
		CWnd* pwnd = GetDlgItem(IDC_BTN_PINSELECT);
		if (pwnd)
			pwnd->EnableWindow(true);
	}
}

void DlgTestOnBoard::OnBnClickedBtnPinselect()
{
	m_pCPlan->ResetProgress();
	m_pCPlan->i_Progress = 0;
	m_pCPlan->n_Progress = 42;  // M x N
	//---------------------------------
	DlgPinSettingEdit mDlgPinSettingEdit;
	mDlgPinSettingEdit.m_pPlan = m_pCPlan;
	mDlgPinSettingEdit.m_pCIniReader = m_pCIniReader;
	mDlgPinSettingEdit.m_DeviceName = m_pCPlan->mTestCase.mPathInfo.DeviceName;
	mDlgPinSettingEdit.m_BoardName = m_pCPlan->mTestCase.mPathInfo.BoardName;
	mDlgPinSettingEdit.m_User = 1;

	mDlgPinSettingEdit.DoModal();

	DlgChanelSelection mDlgChanelSelection;
	mDlgChanelSelection.m_pPlan = m_pCPlan;
	mDlgChanelSelection.m_pCIniReader = m_pCIniReader;
	mDlgChanelSelection.m_DeviceName = m_pCPlan->mTestCase.mPathInfo.DeviceName;
	mDlgChanelSelection.m_BoardName = m_pCPlan->mTestCase.mPathInfo.BoardName;
	mDlgChanelSelection.m_User = 1;
	mDlgChanelSelection.DoModal();
	//-------------------------------------
	//-----------Tuan code ---------- 3: thiet lap dinh tuyen và tham so tin hieu
	// tien xu ly du lieu cho thiet lap nguon


	int ret = m_pCPlan->Process_Seting_PWR();



	// to view setup power line
	/*CString stmp, stmp1, stmp2;
	stmp1.Format(_T("Process_Seting_PWR = : %d "), ret);
	MessageBox(stmp1, _T("Mess"));


	stmp.Format(_T("Data_relay_M2PS_0{0...10}: %d , %d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d"), m_pCPlan->Data_relay_M2PS_0[1], m_pCPlan->Data_relay_M2PS_0[2], m_pCPlan->Data_relay_M2PS_0[3], m_pCPlan->Data_relay_M2PS_0[4], m_pCPlan->Data_relay_M2PS_0[5], m_pCPlan->Data_relay_M2PS_0[6], m_pCPlan->Data_relay_M2PS_0[7], m_pCPlan->Data_relay_M2PS_0[8], m_pCPlan->Data_relay_M2PS_0[9], m_pCPlan->Data_relay_M2PS_0[10]);
	MessageBox(stmp, _T("Mess"));
	stmp2.Format(_T("Data_relay_M2PS_3{0...10}: %d , %d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d"), m_pCPlan->Data_relay_M2PS_3[1], m_pCPlan->Data_relay_M2PS_3[2], m_pCPlan->Data_relay_M2PS_3[3], m_pCPlan->Data_relay_M2PS_3[4], m_pCPlan->Data_relay_M2PS_3[5], m_pCPlan->Data_relay_M2PS_3[6], m_pCPlan->Data_relay_M2PS_3[7], m_pCPlan->Data_relay_M2PS_3[8], m_pCPlan->Data_relay_M2PS_3[9], m_pCPlan->Data_relay_M2PS_3[30]);
	MessageBox(stmp2, _T("Mess"));


	stmp.Format(_T("Data_relay_M3_0{0...7}: %d , %d ,%d ,%d ,%d ,%d ,%d ,%d "), m_pCPlan->Data_Relay_M3_0[0], m_pCPlan->Data_Relay_M3_0[1], m_pCPlan->Data_Relay_M3_0[2], m_pCPlan->Data_Relay_M3_0[3], m_pCPlan->Data_Relay_M3_0[4], m_pCPlan->Data_Relay_M3_0[5], m_pCPlan->Data_Relay_M3_0[6], m_pCPlan->Data_Relay_M3_0[7]);
	MessageBox(stmp, _T("Mess"));
	stmp2.Format(_T("Data_relay_M3_1{0...7}: %d , %d ,%d ,%d ,%d ,%d ,%d ,%d "), m_pCPlan->Data_Relay_M3_1[0], m_pCPlan->Data_Relay_M3_1[1], m_pCPlan->Data_Relay_M3_1[2], m_pCPlan->Data_Relay_M3_1[3], m_pCPlan->Data_Relay_M3_1[4], m_pCPlan->Data_Relay_M3_1[5], m_pCPlan->Data_Relay_M3_1[6], m_pCPlan->Data_Relay_M3_1[7]);
	MessageBox(stmp2, _T("Mess"));
	*/

	
	
	//*************************************************************************************************************
	// buoc 1: reset all to default
	int mRunOK = 0;
	int nRet;
	CString stmp;
	if (mRunOK == 0) {
		//MessageBox(_T("Xóa các định tuyến về mặc định (hở) "), _T("Thông báo"));
		nRet = m_pCPlan->Reset_All_paths();
		if (nRet != 0)
		{
			stmp.Format(_T("LỖI:  Thiết lập định tuyến hệ thống về trạng thái hở. mã lỗi = %d "), nRet);
			MessageBox(stmp, _T("Thông báo"));
			mRunOK++;
		}
		else;//	MessageBox(_T("Reset_All_paths: OK "), _T("Thông báo"));
	}
	//*************************************************************************************************************
	if (mRunOK == 0) {
		// buoc 2: thiet lap Pins_FPGA_default: Inputs, dong bo trong, tan so 1 Khz
	
	//*************************************************************************************************************
	// BUOC NAY DA THIET LAP O DUOI THANH, TRƯƠC KHI THOÁT, THÀNH SET IO_CONFIG_FPGA 
	// ve defualt: all inputs io_mask [0,0,0], CLK_internal, mask_clk = [0,0,0], clk = 1 khz,sample unit = 1000
	//*************************************************************************************************************
	
		Sleep(10);
		nRet = m_pCPlan->Reset_IO_FPGA_Default();  // to all inputs
		if (nRet != 0)
		{
			AfxMessageBox(_T("LỖI: Thiết lập tất cả các cổng I/O về mặc định "));	
			mRunOK++;
		}
		else;//	MessageBox(_T("Reset_IO_FPGA_Default: OK "), _T("Thông báo"));
	}
	 
	 

	// *************************************************************************************************************
	

	m_pCPlan->dinh_tuyen_Flag = 1;  //  he thong duoc dinh tuyen

	if (mRunOK == 0) {
		//MessageBox(_T("Bat dau set Path M1 "), _T("Thông báo"));
		// buoc 4: cau hinh dinh tuyen cho M1_0, M1_1
		Sleep(500);
		nRet = m_pCPlan->Set_Paths_M1(); // thiet lap ca 2 board M1_0 va M1_1
		if (nRet != 0)
		{
			AfxMessageBox(_T("LỖI: Thiết lập định tuyến M1"));	
			mRunOK++;
		}
		else;//	MessageBox(_T("Set_Paths_M1: OK "), _T("Thông báo"));
	}
	// *************************************************************************************************************
	if (mRunOK == 0) {
		//MessageBox(_T("Bat dau set Path M2PS "), _T("Thông báo"));
		// buoc 5: cau hinh dinh tuyen cho M2_PS:  M2_0, M2_3
		Sleep(500);
		nRet = m_pCPlan->Set_Paths_M2_PS(); // thiet lap dinh tuyen cho nguon: ca 2 board o M2_0, M2_3
		if (nRet != 0)
		{
			AfxMessageBox(_T("LỖI: Thiết lập định tuyến M2_PS ")); 
			mRunOK++;
		}
		else;//	MessageBox(_T("Set_Paths_M2_PS: OK "), _T("Thông báo"));
	}
	


	// *********************************** set up cho board mo rong: M4, M2Sig1,2  ***********************************
	// dau tien can phai xu ly cau hinh tỏng file config/ gia odien de tao ra ca mang thiet lap can thiet
		m_pCPlan->Process_setting_Analog_Channels();
/*
		KET QUA HAM NAY TAO RA:    M4_ADDA_CM_Arr[8];


		WITH MODE = 1
		vi tri:[0..7]  <==> ADC1, ADC2, DAC1. DAC2, HV1, HV2, BNC1, BNC2
		gia tri:
		0/ 4 : ONLY FOR ADC_1
		1/ 5 : ONLY FOR ADC_2
		2/ 6 : ONLY FOR DAC_1
		3/ 7 : ONLY FOR DAC_2


		WITH MODE = 2
		vi tri:[0..7]  <==> HV1, HV2, BNC1, BNC2
		gia tri:
		0/ 4 : ONLY FOR HV1
		1/ 5 : ONLY FOR HV2
		2/ 6 : ONLY FOR BNC1
		3/ 7 : ONLY FOR BNC2

*/

		// THUC HIEN CAU HINH CAC THIET LAP CHO MODE PHU HOP

		// for test
/*
		// in ra ma tan du lieu sau khi da phan tich set up
		
		CString stmp_1;

		stmp_1.Format(_T("MODE = %d"), m_pCPlan->mTestCase.ExtChanel_Set.SetMode);
		AfxMessageBox(stmp_1);




		byte dtest[8];

		dtest[0] = m_pCPlan->M4_CM_RL_CONNECT_TO_MAIN[0];
		dtest[1] = m_pCPlan->M4_CM_RL_CONNECT_TO_MAIN[1];
		dtest[2] = m_pCPlan->M4_CM_RL_CONNECT_TO_MAIN[2];
		dtest[3] = m_pCPlan->M4_CM_RL_CONNECT_TO_MAIN[3];

		dtest[4] = m_pCPlan->M4_CM_RL_CONNECT_TO_MAIN[4];
		dtest[5] = m_pCPlan->M4_CM_RL_CONNECT_TO_MAIN[5];
		dtest[6] = m_pCPlan->M4_CM_RL_CONNECT_TO_MAIN[6];
		dtest[7] = m_pCPlan->M4_CM_RL_CONNECT_TO_MAIN[7];


		stmp_1.Format(_T("M4_CM_RL_CONNECT_TO_MAIN[ ]: %d,%d,%d,%d,%d,%d, %d,%d"), dtest[0], dtest[1], dtest[2], dtest[3], dtest[4], dtest[5], dtest[6], dtest[7] );
		AfxMessageBox(stmp_1);


		// 


		dtest[0] = m_pCPlan->M4_CM_Arr[0];
		dtest[1] = m_pCPlan->M4_CM_Arr[1];
		dtest[2] = m_pCPlan->M4_CM_Arr[2];
		dtest[3] = m_pCPlan->M4_CM_Arr[3];

		dtest[4] = m_pCPlan->M4_CM_Arr[4];
		dtest[5] = m_pCPlan->M4_CM_Arr[5];
		dtest[6] = m_pCPlan->M4_CM_Arr[6];
		dtest[7] = m_pCPlan->M4_CM_Arr[7];


		stmp_1.Format(_T("M4_CM_Arr[ ]: %d,%d,%d,%d,%d,%d, %d,%d"), dtest[0], dtest[1], dtest[2], dtest[3], dtest[4], dtest[5], dtest[6], dtest[7]);
		AfxMessageBox(stmp_1);

		// 


		dtest[0] = m_pCPlan->M2_SIG_RL_Data_1[0];
		dtest[1] = m_pCPlan->M2_SIG_RL_Data_1[1];
		dtest[2] = m_pCPlan->M2_SIG_RL_Data_1[2];
		dtest[3] = m_pCPlan->M2_SIG_RL_Data_1[3];

		dtest[4] = m_pCPlan->M2_SIG_RL_Data_1[4];
		dtest[5] = m_pCPlan->M2_SIG_RL_Data_1[5];
		dtest[6] = m_pCPlan->M2_SIG_RL_Data_1[6];
		dtest[7] = m_pCPlan->M2_SIG_RL_Data_1[7];



		stmp_1.Format(_T("M2_SIG_RL_Data_1[ ]: %d,%d,%d,%d,%d,%d, %d,%d"), dtest[0], dtest[1], dtest[2], dtest[3], dtest[4], dtest[5], dtest[6], dtest[7]);
		AfxMessageBox(stmp_1);





		//
		dtest[0] = m_pCPlan->M2_SIG_RL_Data_2[0];
		dtest[1] = m_pCPlan->M2_SIG_RL_Data_2[1];
		dtest[2] = m_pCPlan->M2_SIG_RL_Data_2[2];
		dtest[3] = m_pCPlan->M2_SIG_RL_Data_2[3];

		dtest[4] = m_pCPlan->M2_SIG_RL_Data_2[4];
		dtest[5] = m_pCPlan->M2_SIG_RL_Data_2[5];
		dtest[6] = m_pCPlan->M2_SIG_RL_Data_2[6];
		dtest[7] = m_pCPlan->M2_SIG_RL_Data_2[7];


		stmp_1.Format(_T("M2_SIG_RL_Data_2[ ]: %d,%d,%d,%d,%d,%d, %d,%d"), dtest[0], dtest[1], dtest[2], dtest[3], dtest[4], dtest[5], dtest[6], dtest[7]);
		AfxMessageBox(stmp_1);
*/
		// -------------------------------------------------------------------------






	if (mRunOK == 0) {
		// buoc 6: cau hinh dinh tuyen cho M2_Sig1,2
		nRet = m_pCPlan->Set_Paths_M2_SIG(); // thiet lap ca 2 board o M2_sig0, M2_sig1, apply relay luon trong ham nay
		if (nRet == -1)
		{
			AfxMessageBox(_T("LỖI: Thiết lập Set_Paths_M2_SIG "));
			mRunOK++;
		}

	}

	if (mRunOK == 0) {
		nRet = m_pCPlan->Set_Param_M4_ADDA_BUFF();
		if (nRet == -1)
		{
			AfxMessageBox(_T("LỖI: Thiết lập Set_Param_M4_ADDA_BUFF ")); 
			mRunOK++;
		}
	}
	// ---------------- 

















	// *************************************************************************************************************
	// buoc 7: cau hinh dinh tuyen va tham so tin hieu cho M5
	
	
	if (mRunOK == 0) {
		//MessageBox(_T("Bat dau set Path M5 "), _T("Thông báo"));

		// in ra de kiem tra
		//stmp1.Format(_T(" LogicInComp.value = : %f "), m_pCPlan->mTestCase.ExtChanel_Get.LogicInComp.value);  // van o gia tri mac dinh: 0.5V ?????????  --> loi
		//MessageBox(stmp1, _T("Mess"));

		nRet = m_pCPlan->Set_tham_so_Tin_hieu_M5();
		if (nRet != 0)
		{
			AfxMessageBox(_T(" LỖI: Thiết lập tham số tín hiệu"));	mRunOK++;
		}
		else;// 	MessageBox(_T("Set tham so tin hieu: OK "), _T("Thông báo"));
	}

	// thiet lap treo tro keo len truoc
	if (mRunOK == 0) {
		// 
		// buoc 10: thiet lap tham so cho Board M10: R Pulled Up 
		if (m_pCPlan->Flag_Used_M10 == 1)   // khi he thong co M10.  Khi Active board, neu chon Opton bo qua M9, M10 thi co nay = 0
		{
			//MessageBox(_T("Bat dau set Path M10 - R Pulled Up "), _T("Thông báo"));
			Sleep(1000);
			nRet = m_pCPlan->SetUp_RPullUp_M10();
			if (nRet == -1)
			{
				AfxMessageBox(_T("LỖI: Set_Paths_M10 - R Pulled Up\n"));	mRunOK++;
			}
			else
			{
				Sleep(1000);
				nRet = m_pCPlan->Start_Apply_Relay(ADDR_M10);
				if (nRet == -1)
				{
					AfxMessageBox(_T("LỖI: Thực thi tham số cho M10 - R Pulled Up \n"));	mRunOK++;
				}
				else;
			}
		}
		else;
	}

	if (mRunOK == 0) {
		// 
		// buoc 10: theit lap tham so cho Board M9: Plug DUT
		if (m_pCPlan->Flag_Used_M9 == 1)   // khi he thong co M9.  Khi Active board, neu chon Opton bo qua M9, M10 thi co nay = 0
		{
			/*stmp.Format(_T("cấu hình định tuyến cho JACK thứ [%d] M9 "), m_pCPlan->mTestCase.mID_Jack);
			AfxMessageBox(stmp);*/

			Sleep(1000);
			if (m_pCPlan->mTestCase.mID_Jack == 0)
			{
				// reset M9
				nRet = m_pCPlan->Reset_1_paths(ADDR_M9);

				if (nRet == -1)
				{
					AfxMessageBox(_T("LỖI: Cấu hình định tuyến M9 về mặc định không thành công "));
					mRunOK++;
				}
			}
			else
			{
				nRet = m_pCPlan->Set_Paths_M9(m_pCPlan->mTestCase.mID_Jack);
				if (nRet == -1)
					{
					AfxMessageBox(_T("LỖI: 'Set_Paths_M9' Mảng cắm bo mạch kiểm tra "));	mRunOK++;
					}
				else
				{
					Sleep(1000);
					nRet = m_pCPlan->Start_Apply_Relay_M9(m_pCPlan->mTestCase.mID_Jack);
					if (nRet == -1)
					{
						AfxMessageBox(_T("LỖI: 'Start_Apply_Relay_M9' - Mảng cắm bo mạch kiểm tra\n"));	mRunOK++;
					}
					else;
				}
			}
		}
		else;
	}
	
	
	

	if (mRunOK == 0) {
		// buoc 10: cau hinh dinh tuyen cho M3
		//MessageBox(_T("Bat dau set Path M3 "), _T("Thông báo"));
		Sleep(500);
		nRet = m_pCPlan->Set_Paths_M3(); // thiet lap ca 2 board o M5_0,1,2,3
		if (nRet != 0)
		{
			AfxMessageBox(_T("ERROR: Set_Paths_M3 không thành công "));	mRunOK++;
		}
		else;//MessageBox(_T("Set_Paths_M3: OK "), _T("Thông báo"));
	}
	
	//*************************************************************************************************************
	if ((mRunOK == 0) || (*p_mode == DEBUGNORMAL) || (*p_mode == DEBUGADMIN) || (*p_mode == DEBUGUSER)) {
		m_pCPlan->SetFullProgress();
		MessageBox(_T("THIẾT LẬP ĐỊNH TUYẾN XONG "), _T("Thông báo"));
		CWnd* pwnd = GetDlgItem(IDC_BTN_POWER_SETTING);
		if (pwnd)
			pwnd->EnableWindow(true);
		
		pwnd = GetDlgItem(IDC_BTN_RESET_PATH);
		if (pwnd)
			pwnd->EnableWindow(true);
		
	}
}
//*************************************************************************************************************


void DlgTestOnBoard::OnBnClickedBtnPowerSetting()
{
	// TODO: Add your control notification handler code here
	//---------------------------
	DlgPowerSetting mDlgPowerSetting;
	mDlgPowerSetting.m_pcFigCIniReader = m_pCIniReader;
	mDlgPowerSetting.m_pPlan = m_pCPlan;
	mDlgPowerSetting.m_User = 1;
	mDlgPowerSetting.DoModal();

	int nResult = mDlgPowerSetting.m_status;
	if (nResult == OK) {
		MessageBox(_T("THÀNH CÔNG: Thiết lập nguồn thành công"), _T("Thông báo"));
		CWnd* pwnd = GetDlgItem(IDC_BTN_KT_CN);
		if (pwnd)
			pwnd->EnableWindow(true);
	}
	else {
		AfxMessageBox(_T("LỖI: Thiết lập nguồn có lỗi"));
	}

	if ((nResult == OK) || (*p_mode == DEBUGNORMAL) || (*p_mode == DEBUGADMIN) || (*p_mode == DEBUGUSER)) {
		CWnd* pwnd = GetDlgItem(IDC_BTN_KT_CN);
		if (pwnd)
			pwnd->EnableWindow(true);
	}
}


void DlgTestOnBoard::OnBnClickedBtnKtCn()
{
	// TODO: Add your control notification handler code here

	//m_pCPlan->ResetProgress();
	//for (int ii = 0; ii <= 50; ii++) {
	//	Sleep(100);
	//	m_pCPlan->IncreateProgress(5);
	//}
	//m_pCPlan->SetFullProgress();
	//MessageBox(_T("Ok"), _T("Ok"));

	////------------------------------------------------------
	//int PhanTramMin, PhanTramMax;
	////------------------------------------------------------
	//PhanTramMin = 0; PhanTramMax = 30;
	//m_pCPlan->SetPhanTramProgress(PhanTramMin);
	//for (int ii = 0; ii <= 100; ii++) {
	//	Sleep(100);
	//	m_pCPlan->IncreateProgressInMinMax(1, PhanTramMin, PhanTramMax);
	//}
	//m_pCPlan->SetPhanTramProgress(PhanTramMax);
	////------------------------------------------------------
	//MessageBox(_T("Ok"), _T("Ok"));
	////------------------------------------------------------
	//PhanTramMin = 30; PhanTramMax = 60;
	//m_pCPlan->SetPhanTramProgress(PhanTramMin);
	//for (int ii = 0; ii <= 100; ii++) {
	//	Sleep(100);
	//	m_pCPlan->IncreateProgressInMinMax(1, PhanTramMin, PhanTramMax);
	//}
	//m_pCPlan->SetPhanTramProgress(PhanTramMax);
	////------------------------------------------------------
	//MessageBox(_T("Ok"), _T("Ok"));
	//PhanTramMin = 60; PhanTramMax = 100;
	//m_pCPlan->SetPhanTramProgress(PhanTramMin);
	//for (int ii = 0; ii <= 100; ii++) {
	//	Sleep(100);
	//	m_pCPlan->IncreateProgressInMinMax(1, PhanTramMin, PhanTramMax);
	//}
	//m_pCPlan->SetPhanTramProgress(PhanTramMax);
	////------------------------------------------------------
	//return;
	////-------------------------------------------------------

	CString strKey, strValue, strSection = _T("PATH");
	CString fullPath = m_pCPlan->mTestCase.mPathInfo.FullPath;
	CString datapath = m_pCPlan->mTestCase.mPathInfo.TestPath + _T("\\data.dat");
	CString ThanhFileName = m_pCPlan->mTestCase.mPathInfo.RootPath + _T("\\FilePath\\datapath.txt");
	m_pCIniReader->setTestCaseFileName(ThanhFileName);
	strKey = _T("datapath");
	strValue = datapath;
	int iRet = m_pCIniReader->setKey(strValue, strKey, strSection);
	if (iRet != 1) {
		AfxMessageBox(_T("LỖI: Lỗi tạo file \r\nXem lại đường dẫn:\r\n")+ ThanhFileName);
		return;
	}

	if (!IsFileExists(datapath)) {
		AfxMessageBox(_T("LỖI: Lỗi tạo dữ liệu\r\nXem lại đường dẫn:\r\n") + datapath);
		return;
	}

	m_pCIniReader->setTestCaseFileName(fullPath);

	//------------------------------------
	*pFlagThRun = 1;
	
	if (!*pFlagThConnected) {
		AfxMessageBox(_T("LỖI: Trạng thái kết nối lỗi, không gửi được dữ liệu cấu hình"));
		//SocketTh->TCP_shutdown();
		//SocketTh->TCP_init();
		//SocketTh->TCP_connect();
		return;
	}

	CString tmp = _T(";admin");
	if (m_User) tmp = _T(";user");
	//--------------------------------
	ThanhFileName += tmp;
	CT2A ascii(ThanhFileName);
	//--------------------------------

	SocketTh->TCP_send(ascii);
	Sleep(100);

	this->ShowWindow(SW_HIDE);
	*pFlagThRun = 1;
	while (1) {
		Sleep(1000);
		if (*pFlagThRun == 0) {
			SocketTh->TCP_send("off\n\r");
			this->ShowWindow(SW_SHOW);
			this->BringWindowToTop();
			return;
		}
		if (!*pFlagThConnected) {
			this->ShowWindow(SW_SHOW);
			this->BringWindowToTop();
			return;
		}
	}
}


void DlgTestOnBoard::OnBnClickedBtnExit()
{
	// TODO: Add your control notification handler code here


	if (AfxMessageBox(_T("CẢNH BÁO: Thực hiện THOÁT BÀI KIỂM TRA ? \n\r "), MB_OKCANCEL) != IDOK)  // MB_OKCANCEL
		return;   // thoat khi chon CANCEL

	uint32_t nRet;
	// tat nguon cho bo mach M1_0. M1_1: bo sung ngay 17_1_2024
	nRet = m_pCPlan->Power_Ctrl_M1_For_DUT(P_OFF, ADDR_M1_0);
	if (nRet < 8)
	{
		AfxMessageBox(_T("LỖI:Tắt nguồn cho bo mạch kiểm tra M1_0"));
	}
	else;

	Sleep(100);
	nRet = m_pCPlan->Power_Ctrl_M1_For_DUT(P_OFF, ADDR_M1_1);
	if (nRet < 8)
	{
		AfxMessageBox(_T("LỖI:Tắt nguồn cho bo mạch kiểm tra M1_1"));
	}
	else;
	Sleep(100);

	if (m_pCPlan->CAN_Network_Flag_Connected == OK)
	{
		if (m_pCPlan->dinh_tuyen_Flag == 1)
		{
			////	m_pCPlan->dinh_tuyen_Flag = 0;  //  he thong da xoa dinh tuyen
			//if (AfxMessageBox(_T("CẢNH BÁO: Hệ thống chưa được xóa định tuyến! Hệ thống sẽ thực hiện xóa định tuyến bây giờ. \n\r "), MB_OKCANCEL) != IDOK)  // MB_OKCANCEL
			//	return;   // thoat khi chon CANCEL

			OnBnClickedBtnResetPath();    // neu xoa thanh con thi: dinh_tuyen_Flag = 0;
			if (m_pCPlan->dinh_tuyen_Flag == 1)
			{
				AfxMessageBox(_T("CẢNH BÁO: Xóa định tuyến hệ thống không thành công! NÊN: Thử lại 'xóa định tuyến' HOẶC khởi động lại nguồn hệ thống. Bấm 'THOÁT' để thoát chương trình. \n\r "));
			}
			else;
		}
	}
	else
		if (m_pCPlan->dinh_tuyen_Flag == 1)
		{
			AfxMessageBox(_T("CẢNH BÁO: Kết nối điều khiển không thành công. Định tuyến vẫn chưa được xóa. Cần khởi động lại nguồn cho thiết bị \n\r "));
		}
	CDialogEx::OnOK();
}


void DlgTestOnBoard::OnBnClickedBtnResetPath()
{
	// TODO: Add your control notification handler code here
	int nRet;

	m_pCPlan->ResetProgress();
	m_pCPlan->i_Progress = 0;
	m_pCPlan->n_Progress = 18;  // M x N



	if (m_pCPlan->CAN_Network_Flag_Connected == OK)
	{
		//--------------------------------------------------------------------------------
		// tat nguon cấp từ m3_0 va M3_1
		// buoc 1: luu trang thai m_pPlan ra mang phu truoc khi cau hinh OFF

		m_pCPlan->Temp_8PWR_on_off_save_stt[0] = m_pCPlan->mTestCase.mPowers.POWER[1].ON_OFF;
		m_pCPlan->Temp_8PWR_on_off_save_stt[1] = m_pCPlan->mTestCase.mPowers.POWER[2].ON_OFF;

		m_pCPlan->Temp_8PWR_on_off_save_stt[2] = m_pCPlan->mTestCase.mPowers.POWER[3].ON_OFF;
		m_pCPlan->Temp_8PWR_on_off_save_stt[3] = m_pCPlan->mTestCase.mPowers.POWER[4].ON_OFF;

		m_pCPlan->Temp_8PWR_on_off_save_stt[4] = m_pCPlan->mTestCase.mPowers.POWER[5].ON_OFF;
		m_pCPlan->Temp_8PWR_on_off_save_stt[5] = m_pCPlan->mTestCase.mPowers.POWER[6].ON_OFF;

		m_pCPlan->Temp_8PWR_on_off_save_stt[6] = m_pCPlan->mTestCase.mPowers.POWER[7].ON_OFF;
		m_pCPlan->Temp_8PWR_on_off_save_stt[7] = m_pCPlan->mTestCase.mPowers.POWER[8].ON_OFF;


		m_pCPlan->mTestCase.mPowers.POWER[1].ON_OFF = 0;   // OFF
		m_pCPlan->mTestCase.mPowers.POWER[2].ON_OFF = 0;   // OFF
		m_pCPlan->mTestCase.mPowers.POWER[3].ON_OFF = 0;   // OFF
		m_pCPlan->mTestCase.mPowers.POWER[4].ON_OFF = 0;   // OFF
		m_pCPlan->mTestCase.mPowers.POWER[5].ON_OFF = 0;   // OFF

		m_pCPlan->mTestCase.mPowers.POWER[6].ON_OFF = 0;   // OFF
		m_pCPlan->mTestCase.mPowers.POWER[7].ON_OFF = 0;   // OFF
		m_pCPlan->mTestCase.mPowers.POWER[8].ON_OFF = 0;   // OFF

		// setup nguon: M3_0, M3_1
		char RecArr[256];
		int lenRecArr;

		//UpdateData(true);
		//if (UpdateDataGUIToVar()) return;
		m_pCPlan->i_Progress++;
		m_pCPlan->SetPhanTramProgress(m_pCPlan->i_Progress * 100 / m_pCPlan->n_Progress);

		m_pCPlan->SetUp8Power(m_pCPlan->mTestCase.mPowers, RecArr, &lenRecArr);
		//--------------------------------------------------------------------------------
		m_pCPlan->SetPhanTramProgress(2);
		// ngat nguon cap +30V cho M9, M10: qua bo mach M1_0
		nRet = m_pCPlan->Power_Ctrl_M1_For_DUT(P_OFF, ADDR_M1_0);
		if (nRet < 8)
		{
			AfxMessageBox(_T("LỖI:Tắt nguồn cho bo mạch kiểm tra M1_0"));	return;
		}
		else;

		m_pCPlan->i_Progress++;
		m_pCPlan->SetPhanTramProgress(m_pCPlan->i_Progress * 100 / m_pCPlan->n_Progress);
		nRet = m_pCPlan->Power_Ctrl_M1_For_DUT(P_OFF, ADDR_M1_1);
		if (nRet < 8)
		{
			AfxMessageBox(_T("LỖI:Tắt nguồn cho bo mạch kiểm tra M1_1"));	return;
		}
		else;
		//--------------------------------------------------------------------------------

		// Tat cac kenh Analog: ADC, DAC, HV_out, HV_in
		// buoc 1: luu trang thai m_pPlan ra mang phu truoc khi cau hinh OFF

		m_pCPlan->Tem_ADDA_HV_on_off_save_stt[0] = m_pCPlan->mTestCase.ExtChanel_Set.ADC_in1.used;
		m_pCPlan->Tem_ADDA_HV_on_off_save_stt[1] = m_pCPlan->mTestCase.ExtChanel_Set.ADC_in2.used;

		m_pCPlan->Tem_ADDA_HV_on_off_save_stt[2] = m_pCPlan->mTestCase.ExtChanel_Set.DAC_out1.used;
		m_pCPlan->Tem_ADDA_HV_on_off_save_stt[3] = m_pCPlan->mTestCase.ExtChanel_Set.DAC_out2.used;

		m_pCPlan->Tem_ADDA_HV_on_off_save_stt[4] = m_pCPlan->mTestCase.ExtChanel_Set.HV_out1.used;
		m_pCPlan->Tem_ADDA_HV_on_off_save_stt[5] = m_pCPlan->mTestCase.ExtChanel_Set.HV_out2.used;

		m_pCPlan->Tem_ADDA_HV_on_off_save_stt[6] = m_pCPlan->mTestCase.ExtChanel_Set.HV_in1.used;
		m_pCPlan->Tem_ADDA_HV_on_off_save_stt[7] = m_pCPlan->mTestCase.ExtChanel_Set.HV_in2.used;

		// buoc 2: Xoa tam thoi de tat he thong phan cung
		m_pCPlan->mTestCase.ExtChanel_Set.ADC_in1.used = 0;
		m_pCPlan->mTestCase.ExtChanel_Set.ADC_in2.used = 0;

		m_pCPlan->mTestCase.ExtChanel_Set.DAC_out1.used = 0;
		m_pCPlan->mTestCase.ExtChanel_Set.DAC_out2.used = 0;

		m_pCPlan->mTestCase.ExtChanel_Set.HV_out1.used = 0;
		m_pCPlan->mTestCase.ExtChanel_Set.HV_out2.used = 0;

		m_pCPlan->mTestCase.ExtChanel_Set.HV_in1.used = 0;
		m_pCPlan->mTestCase.ExtChanel_Set.HV_in2.used = 0;

		m_pCPlan->i_Progress++;
		m_pCPlan->SetPhanTramProgress(m_pCPlan->i_Progress * 100 / m_pCPlan->n_Progress);
	
		//AfxMessageBox(_T("Test xoa dinh tuyen: tắt Khối M4: Start "));
		nRet = m_pCPlan->Set_Param_M4_ADDA_BUFF();
		if (nRet == -1)
		{
			AfxMessageBox(_T("LỖI: Lỗi tắt Khối M4 "));
		}

		//CString stmp_1;

		//stmp_1.Format(_T("Test xoa dinh tuyen: tắt Khối M4: END, nRet = %d"), nRet);
		//AfxMessageBox(stmp_1);
// ----------------------------------------------------------------------------------------

		nRet = m_pCPlan->Reset_All_paths();
		if (nRet != 0)
		{
			AfxMessageBox(_T("LỖI: Reset_All_paths "));	return;
		}
		else;//	MessageBox(_T("Reset_All_paths: OK "), _T("Thông báo"));
		// buoc 2: thiet lap Pins_FPGA_default: Inputs, dong bo trong, tan so 1 Khz
		Sleep(100);
		nRet = m_pCPlan->Reset_IO_FPGA_Default();  // to all inputs
		if (nRet != 0)
		{
			AfxMessageBox(_T("LỖI: Reset_IO_FPGA_Default"));	return;
		}
		else;//	MessageBox(_T("Reset_IO_FPGA_Default: OK "), _T("Thông báo"));
		//-----------------------------------------------------------------------------


		m_pCPlan->SetFullProgress();   // SET FULL THANH THANH TRANG THAI
		m_pCPlan->dinh_tuyen_Flag = 0;  //  he thong da xoa dinh tuyen
		MessageBox(_T("THÀNH CÔNG: Xóa định tuyến xong!"), _T("Thông báo"));
		
	}
	else
	{
		AfxMessageBox(_T("LỖI: Kết nối điều khiển với thiết bị không tốt. Chưa xóa định tuyến thành công. Hãy 'THOÁT' và khởi động lại nguồn cho thiết bị!"));
	}
	CWnd* pwnd;
	pwnd = GetDlgItem(IDC_BTN_POWER_THRESHOL); if (pwnd) pwnd->EnableWindow(false);
	pwnd = GetDlgItem(IDC_BTN_PINSELECT); if (pwnd) pwnd->EnableWindow(false);
	pwnd = GetDlgItem(IDC_BTN_POWER_SETTING); if (pwnd) pwnd->EnableWindow(false);
	pwnd = GetDlgItem(IDC_BTN_KT_CN); if (pwnd) pwnd->EnableWindow(false);
	pwnd = GetDlgItem(IDC_BTN_RESET_PATH); if (pwnd) pwnd->EnableWindow(false);


	// khoi phục lại tham số của mPlan
	//PWR
	m_pCPlan->mTestCase.mPowers.POWER[1].ON_OFF = m_pCPlan->Temp_8PWR_on_off_save_stt[0];
	m_pCPlan->mTestCase.mPowers.POWER[2].ON_OFF = m_pCPlan->Temp_8PWR_on_off_save_stt[1];
	m_pCPlan->mTestCase.mPowers.POWER[3].ON_OFF = m_pCPlan->Temp_8PWR_on_off_save_stt[2];
	m_pCPlan->mTestCase.mPowers.POWER[4].ON_OFF = m_pCPlan->Temp_8PWR_on_off_save_stt[3];
	m_pCPlan->mTestCase.mPowers.POWER[5].ON_OFF = m_pCPlan->Temp_8PWR_on_off_save_stt[4];
	m_pCPlan->mTestCase.mPowers.POWER[6].ON_OFF = m_pCPlan->Temp_8PWR_on_off_save_stt[5];
	m_pCPlan->mTestCase.mPowers.POWER[7].ON_OFF = m_pCPlan->Temp_8PWR_on_off_save_stt[6];
	m_pCPlan->mTestCase.mPowers.POWER[8].ON_OFF = m_pCPlan->Temp_8PWR_on_off_save_stt[7];

	// ADDA, HV
	m_pCPlan->mTestCase.ExtChanel_Set.ADC_in1.used = m_pCPlan->Tem_ADDA_HV_on_off_save_stt[0];
	m_pCPlan->mTestCase.ExtChanel_Set.ADC_in2.used = m_pCPlan->Tem_ADDA_HV_on_off_save_stt[1];

	m_pCPlan->mTestCase.ExtChanel_Set.DAC_out1.used = m_pCPlan->Tem_ADDA_HV_on_off_save_stt[2];
	m_pCPlan->mTestCase.ExtChanel_Set.DAC_out2.used = m_pCPlan->Tem_ADDA_HV_on_off_save_stt[3];

	m_pCPlan->mTestCase.ExtChanel_Set.HV_out1.used = m_pCPlan->Tem_ADDA_HV_on_off_save_stt[4];
	m_pCPlan->mTestCase.ExtChanel_Set.HV_out2.used = m_pCPlan->Tem_ADDA_HV_on_off_save_stt[5];

	m_pCPlan->mTestCase.ExtChanel_Set.HV_in1.used = m_pCPlan->Tem_ADDA_HV_on_off_save_stt[6];
	m_pCPlan->mTestCase.ExtChanel_Set.HV_in2.used = m_pCPlan->Tem_ADDA_HV_on_off_save_stt[7];

	return;
}



void DlgTestOnBoard::OnBnClickedBtnExit2()
{
	// TODO: Add your control notification handler code here
	m_pCPlan->Set_Paths_M9(m_pCPlan->mTestCase.mID_Jack);
	Sleep(2000);
	m_pCPlan->Start_Apply_Relay_M9(M9_JA4JA1_Jack_8);    //
}
