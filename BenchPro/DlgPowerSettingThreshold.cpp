// DlgPowerSettingThreshold.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgPowerSettingThreshold.h"
#include "CInputDialog.h";


// DlgPowerSettingThreshold dialog

IMPLEMENT_DYNAMIC(DlgPowerSettingThreshold, CDialogEx)

DlgPowerSettingThreshold::DlgPowerSettingThreshold(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_POWER_SETTING_THRESHOLd, pParent)
	, m_Imax_3v3(_T(""))
	, m_Imax_5v(_T(""))
	, m_Imax_12v(_T(""))
	, m_Imax_12v_n(_T(""))
	, m_Imax_12v_cpu(_T(""))
	, m_Imax_12v_role(_T(""))
	, m_Imax_30v(_T(""))
	, m_U12v_Down(_T(""))
	, m_U12v_Up(_T(""))
	, m_U30vUP(_T(""))
	, m_U30vDown(_T(""))
{

}

DlgPowerSettingThreshold::~DlgPowerSettingThreshold()
{
}

void DlgPowerSettingThreshold::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IMAX_3V3, m_Imax_3v3);
	DDX_Text(pDX, IDC_EDIT_IMAX_5V, m_Imax_5v);
	DDX_Text(pDX, IDC_EDIT_IMAX_12V, m_Imax_12v);
	DDX_Text(pDX, IDC_EDIT_IMAX_12V_N, m_Imax_12v_n);
	DDX_Text(pDX, IDC_EDIT_IMAX_12V_CPU, m_Imax_12v_cpu);
	DDX_Text(pDX, IDC_EDIT_IMAX_12V_ROLE, m_Imax_12v_role);
	DDX_Text(pDX, IDC_EDIT_IMAX_30V, m_Imax_30v);
	DDX_Text(pDX, IDC_EDIT_U12V_DOWN, m_U12v_Down);
	DDX_Text(pDX, IDC_EDIT_U12V_UP, m_U12v_Up);
	DDX_Text(pDX, IDC_EDIT_U30V_UP, m_U30vUP);
	DDX_Text(pDX, IDC_EDIT_U30V_DOWN, m_U30vDown);

	DDX_Control(pDX, IDC_BMP_IMAX_3V3, m_BMP_IMAX_3V3);
	DDX_Control(pDX, IDC_BMP_IMAX_5V, m_BMP_IMAX_5V);
	DDX_Control(pDX, IDC_BMP_IMAX_12V, m_BMP_IMAX_12V);
	DDX_Control(pDX, IDC_BMP_IMAX_12V_N, m_BMP_IMAX_12V_N);
	DDX_Control(pDX, IDC_BMP_IMAX_12V_CPU, m_BMP_IMAX_12V_CPU);
	DDX_Control(pDX, IDC_BMP_IMAX_12V_ROLE, m_BMP_IMAX_12V_ROLE);
	DDX_Control(pDX, IDC_BMP_IMAX_30V, m_BMP_IMAX_30V);

	DDX_Control(pDX, IDC_BMP_U12V_DOWN, m_BMP_U12V_DOWN);
	DDX_Control(pDX, IDC_BMP_U30V_DOWN, m_BMP_U30V_DOWN);
	DDX_Control(pDX, IDC_BMP_U12V_UP, m_BMP_U12V_UP);
	DDX_Control(pDX, IDC_BMP_U30V_UP, m_BMP_U30V_UP);
}

BEGIN_MESSAGE_MAP(DlgPowerSettingThreshold, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SET, &DlgPowerSettingThreshold::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDEXIT, &DlgPowerSettingThreshold::OnBnClickedExit)
	ON_BN_CLICKED(IDC_SAVE, &DlgPowerSettingThreshold::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BTN_EDIT, &DlgPowerSettingThreshold::OnBnClickedBtnEdit)
END_MESSAGE_MAP()


// DlgPowerSettingThreshold message handlers

BOOL DlgPowerSettingThreshold::OnInitDialog() {
	CDialog::OnInitDialog();
	CEdit* pEditCtrl;
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_MAIN_TITLE_TL1);
	pEditCtrl->SetFont(m_tfont);
	pEditCtrl->SetWindowTextW(_T("THIẾT LẬP BẢO VỆ NGUỒN"));
	UpdateDataToGUI();
	UpdateData(false);
	if (m_User) {
		CWnd* pwnd = GetDlgItem(IDC_EDIT_IMAX_3V3);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_IMAX_5V);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_IMAX_12V);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_IMAX_12V_N);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_IMAX_12V_CPU);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_IMAX_12V_ROLE);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_IMAX_30V);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_U12V_DOWN);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_U12V_UP);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_U30V_UP);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_U30V_DOWN);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_SAVE);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_BTN_EDIT);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_BUTTON_SET);
		if (pwnd) pwnd->EnableWindow(true);
	}

	if (GETDATABASE) {
		CWnd* pwnd = GetDlgItem(IDC_BUTTON_SET);
		if (pwnd)
			pwnd->EnableWindow(false);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void DlgPowerSettingThreshold::UpdateDataToGUI() {

	m_Imax_3v3.Format(_T("%0.3f"), m_pPlan->mTestCase.mSupply_Set.Imax_3v3);
	m_Imax_5v.Format(_T("%0.3f"), m_pPlan->mTestCase.mSupply_Set.Imax_5v);
	m_Imax_12v.Format(_T("%0.3f"), m_pPlan->mTestCase.mSupply_Set.Imax_12v);
	m_Imax_12v_n.Format(_T("%0.3f"), m_pPlan->mTestCase.mSupply_Set.Imax_12v_N);
	m_Imax_12v_cpu.Format(_T("%0.3f"), m_pPlan->mTestCase.mSupply_Set.Imax_12v_CPU);
	m_Imax_12v_role.Format(_T("%0.3f"), m_pPlan->mTestCase.mSupply_Set.Imax_12v_ROLE);
	m_Imax_30v.Format(_T("%0.3f"), m_pPlan->mTestCase.mSupply_Set.Imax_30v);
	m_U12v_Down.Format(_T("%0.2f"), m_pPlan->mTestCase.mSupply_Set.U12v_DOWN);
	m_U12v_Up.Format(_T("%0.2f"), m_pPlan->mTestCase.mSupply_Set.U12v_UP);
	m_U30vUP.Format(_T("%0.2f"), m_pPlan->mTestCase.mSupply_Set.U30v_UP);
	m_U30vDown.Format(_T("%0.2f"), m_pPlan->mTestCase.mSupply_Set.U30v_DOWN);

}

void DlgPowerSettingThreshold::UpdateDataGUIToVar() {
	UpdateData(TRUE);

	swscanf_s(m_Imax_3v3.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mSupply_Set.Imax_3v3);
	swscanf_s(m_Imax_5v.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mSupply_Set.Imax_5v);
	swscanf_s(m_Imax_12v.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mSupply_Set.Imax_12v);
	swscanf_s(m_Imax_12v_n.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mSupply_Set.Imax_12v_N);
	swscanf_s(m_Imax_12v_cpu.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mSupply_Set.Imax_12v_CPU);
	swscanf_s(m_Imax_12v_role.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mSupply_Set.Imax_12v_ROLE);
	swscanf_s(m_Imax_30v.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mSupply_Set.Imax_30v);
	swscanf_s(m_U12v_Down.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mSupply_Set.U12v_DOWN);
	swscanf_s(m_U12v_Up.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mSupply_Set.U12v_UP);
	swscanf_s(m_U30vUP.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mSupply_Set.U30v_UP);
	swscanf_s(m_U30vDown.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mSupply_Set.U30v_DOWN);
}

int DlgPowerSettingThreshold::Set_Power_Safe() {
	// thiet lap tham so nguong dong bao ve cho he thong
	// 1. thiet lap nguong dong bao ve cho nguon 3.3V
	int mret;


	mret = m_pPlan->Set_Ithres_Protect_M7A(ID_I_Thres_PwrSys_3V3_1);
	if (mret < 8)
	{
		AfxMessageBox(_T("LỖI: Thiết lập dòng bảo vệ cho nguồn 3.3V_1 không thành công"));
		return -1;
	}


	mret = m_pPlan->Set_Ithres_Protect_M7A(ID_I_Thres_PwrSys_3V3_2);
	if (mret < 8)
	{
		AfxMessageBox(_T("LỖI: Thiết lập dòng bảo vệ cho nguồn 3.3V_2 không thành công"));
		return -1;
	}

	mret = m_pPlan->Set_Ithres_Protect_M7A(ID_I_Thres_PwrSys_5V);
	if (mret < 8)
	{
		AfxMessageBox(_T("LỖI: Thiết lập dòng bảo vệ cho nguồn 5V không thành công"));
		return -1;
	}

	mret = m_pPlan->Set_Ithres_Protect_M7A(ID_I_Thres_PwrSys_12V);
	if (mret < 8)
	{
		AfxMessageBox(_T("LỖI: Thiết lập dòng bảo vệ cho nguồn 12V không thành công"));
		return -1;
	}

	mret = m_pPlan->Set_Ithres_Protect_M7A(ID_I_Thres_PwrSys_12V_N);
	if (mret < 8)
	{
		AfxMessageBox(_T("LỖI: Thiết lập dòng bảo vệ cho nguồn -12V không thành công"));
		return -1;
	}

	mret = m_pPlan->Set_Ithres_Protect_M7A(ID_I_Thres_PwrSys_12V_CPU);
	if (mret < 8)
	{
		AfxMessageBox(_T("LỖI: Thiết lập dòng bảo vệ cho nguồn 12V_CPU không thành công"));
		return -1;
	}
	mret = m_pPlan->Set_Ithres_Protect_M7A(ID_I_Thres_PwrSys_12V_RL_1);
	if (mret < 8)
	{
		AfxMessageBox(_T("LỖI: Thiết lập dòng bảo vệ cho nguồn 12V_Relay_1 không thành công"));
		return -1;
	}

	mret = m_pPlan->Set_Ithres_Protect_M7A(ID_I_Thres_PwrSys_12V_RL_2);
	if (mret < 8)
	{
		AfxMessageBox(_T("LỖI: Thiết lập dòng bảo vệ cho nguồn 12V_Relay_2 không thành công"));
		return -1;
	}
	mret = m_pPlan->Set_Ithres_Protect_M7A(ID_I_Thres_PwrSys_30V);
	if (mret < 8)
	{
		AfxMessageBox(_T("LỖI: Thiết lập dòng bảo vệ cho nguồn 30V không thành công"));
		return -1;
	}


	//..................... thiet lap nguong dien ap bao ve cho nguon cao ap ...........

	mret = m_pPlan->Set_UThres_HV_Protect_M7A(ID_UThres_HV_Pwr_Sys_30V);
	if (mret < 8)
	{
		AfxMessageBox(_T("LỖI: Thiết lập ngưỡng điện áp bảo vệ cho nguồn 30V không thành công"));
		return -1;
	}
	mret = m_pPlan->Set_UThres_HV_Protect_M7A(ID_UThres_HV_Pwr_Sys_12V_Relay);
	if (mret < 8)
	{
		AfxMessageBox(_T("LỖI: Thiết lập ngưỡng điện áp bảo vệ cho nguồn 12V_RELAY không thành công"));
		return -1;
	}

	return 1;
}



int DlgPowerSettingThreshold::Get_Power_Safe() {
	// doc tham so nguong dong bao ve cho he thong


	int mret;

	mret = m_pPlan->Get_Ithres_Protect_M7A(ID_I_Thres_PwrSys_3V3_1);

	if (mret < 0)
	{
		AfxMessageBox(_T("LỖI: Đọc dòng bảo vệ cho nguồn 3.3V_1 không thành công"));
		return -1;
	}

	Sleep(10);


	mret = m_pPlan->Get_Ithres_Protect_M7A(ID_I_Thres_PwrSys_3V3_2);
	if (mret < 0)
	{
		AfxMessageBox(_T("LỖI: Đọc dòng bảo vệ cho nguồn 3.3V_2 không thành công"));
		return -1;
	}
	Sleep(10);
	mret = m_pPlan->Get_Ithres_Protect_M7A(ID_I_Thres_PwrSys_5V);
	if (mret < 0)
	{
		AfxMessageBox(_T("LỖI: Đọc dòng bảo vệ cho nguồn 5V không thành công"));
		return -1;
	}
	Sleep(10);
	mret = m_pPlan->Get_Ithres_Protect_M7A(ID_I_Thres_PwrSys_12V);
	if (mret < 0)
	{
		AfxMessageBox(_T("LỖI: Đọc dòng bảo vệ cho nguồn 12V không thành công"));
		return -1;
	}
	Sleep(10);
	mret = m_pPlan->Get_Ithres_Protect_M7A(ID_I_Thres_PwrSys_12V_N);
	if (mret < 0)
	{
		AfxMessageBox(_T("LỖI: Đọc dòng bảo vệ cho nguồn -12V không thành công"));
		return -1;
	}
	Sleep(10);
	mret = m_pPlan->Get_Ithres_Protect_M7A(ID_I_Thres_PwrSys_12V_CPU);
	if (mret < 0)
	{
		AfxMessageBox(_T("LỖI: Đọc dòng bảo vệ cho nguồn 12V_CPU không thành công"));
		return -1;
	}
	Sleep(10);
	mret = m_pPlan->Get_Ithres_Protect_M7A(ID_I_Thres_PwrSys_12V_RL_1);
	if (mret < 0)
	{
		AfxMessageBox(_T("LỖI: Đọc dòng bảo vệ cho nguồn 12V_Relay_1 không thành công"));
		return -1;
	}
	Sleep(10);
	mret = m_pPlan->Get_Ithres_Protect_M7A(ID_I_Thres_PwrSys_12V_RL_2);
	if (mret < 0)
	{
		AfxMessageBox(_T("LỖI: Đọc dòng bảo vệ cho nguồn 12V_Relay_2 không thành công"));
		return -1;
	}
	Sleep(10);
	mret = m_pPlan->Get_Ithres_Protect_M7A(ID_I_Thres_PwrSys_30V);
	if (mret < 0)
	{
		AfxMessageBox(_T("LỖI: Đọc dòng bảo vệ cho nguồn 30V không thành công"));
		return -1;
	}
	Sleep(10);

	//..................... thiet lap nguong dien ap bao ve cho nguon cao ap ...........

	mret = m_pPlan->Get_UThres_HV_Protect_M7A(ID_UThres_HV_Pwr_Sys_30V);
	if (mret < 0)
	{
		AfxMessageBox(_T("LỖI: Đọc ngưỡng điện áp bảo vệ cho nguồn 30V không thành công"));
		return -1;
	}
	Sleep(10);
	mret = m_pPlan->Get_UThres_HV_Protect_M7A(ID_UThres_HV_Pwr_Sys_12V_Relay);
	if (mret < 0)
	{
		AfxMessageBox(_T("LỖI: Đọc ngưỡng điện áp bảo vệ cho nguồn 12V_RELAY không thành công"));
		return -1;
	}

	Sleep(10);
	return 1;
}




int DlgPowerSettingThreshold::UpdateStatus() {

	CBitmap cBmpOK, cBmpERR;
	cBmpOK.LoadBitmap(IDB_BITMAP_ON);
	cBmpERR.LoadBitmap(IDB_BITMAP_OFF);
	m_status = 1;
	float tmpThreshol = m_pPlan->mTestCase.mSupply_Set.PowerSafeVerifyThreshol;
	float ftmpGet, ftmpSet;

	float MOT = 1.0;


	// so sanh xem thiet lap thanh cong chua?
	float epsilon_Inguong = 0.005;   // sai số lượng tử 5mA và 5 mV@ độ phân giải 1mV, 1mA


	// 1. kiem tra thiet lap thành công xuống phần cứng
	ftmpSet = m_pPlan->mTestCase.mSupply_Set.Imax_3v3;   // nguong dong tieu thu bao ve
	ftmpGet = m_pPlan->mTestCase.mSupply_Get.Imax_3v3;   // dong tieu thu thuc te hien tai cua he thong
	if (abs(ftmpGet - ftmpSet) > epsilon_Inguong) {
		m_status = 0;
		m_BMP_IMAX_3V3.SetBitmap(cBmpERR);
	}
	else m_BMP_IMAX_3V3.SetBitmap(cBmpOK);

	// 2. kiem tra quá dòng với nguồn 5V
	ftmpSet = m_pPlan->mTestCase.mSupply_Set.Imax_5v;   // ngưỡng dòng bảo vệ
	ftmpGet = m_pPlan->mTestCase.mSupply_Get.Imax_5v;   // dòng dang tiêu thụ
	if (abs(ftmpGet - ftmpSet) > epsilon_Inguong) {
		m_status = 0;
		m_BMP_IMAX_5V.SetBitmap(cBmpERR);
	}
	else m_BMP_IMAX_5V.SetBitmap(cBmpOK);

	// 3. kiem tra quá dòng với nguồn 12V
	ftmpSet = m_pPlan->mTestCase.mSupply_Set.Imax_12v;    // ngưỡng dòng bảo vệ
	ftmpGet = m_pPlan->mTestCase.mSupply_Get.Imax_12v;    // dòng dang tiêu thụ
	if (abs(ftmpGet - ftmpSet) > epsilon_Inguong) {
		m_status = 0;
		m_BMP_IMAX_12V.SetBitmap(cBmpERR);
	}
	else m_BMP_IMAX_12V.SetBitmap(cBmpOK);


	// 4. kiem tra quá dòng với nguồn -12V
	ftmpSet = m_pPlan->mTestCase.mSupply_Set.Imax_12v_N;    // ngưỡng dòng bảo vệ
	ftmpGet = m_pPlan->mTestCase.mSupply_Get.Imax_12v_N;    // dòng dang tiêu thụ
	if (abs(ftmpGet - ftmpSet) > epsilon_Inguong) {
		m_status = 0;
		m_BMP_IMAX_12V_N.SetBitmap(cBmpERR);
	}
	else m_BMP_IMAX_12V_N.SetBitmap(cBmpOK);

	// 5. kiem tra quá dòng với nguồn 12V_CPU
	ftmpSet = m_pPlan->mTestCase.mSupply_Set.Imax_12v_CPU;// ngưỡng dòng bảo vệ
	ftmpGet = m_pPlan->mTestCase.mSupply_Get.Imax_12v_CPU;// dòng dang tiêu thụ
	if (abs(ftmpGet - ftmpSet) > epsilon_Inguong) {
		m_status = 0;
		m_BMP_IMAX_12V_CPU.SetBitmap(cBmpERR);
	}
	else m_BMP_IMAX_12V_CPU.SetBitmap(cBmpOK);


	// 6. kiem tra quá dòng với nguồn 12V_relay
	ftmpSet = m_pPlan->mTestCase.mSupply_Set.Imax_12v_ROLE;   // ngưỡng dòng bảo vệ
	ftmpGet = m_pPlan->mTestCase.mSupply_Get.Imax_12v_ROLE;   // dòng dang tiêu thụ
	if (abs(ftmpGet - ftmpSet) > epsilon_Inguong) {
		m_status = 0;
		m_BMP_IMAX_12V_ROLE.SetBitmap(cBmpERR);
	}
	else m_BMP_IMAX_12V_ROLE.SetBitmap(cBmpOK);


	// 7. kiem tra quá dòng với nguồn 30V
	ftmpSet = m_pPlan->mTestCase.mSupply_Set.Imax_30v;   // ngưỡng dòng bảo vệ
	ftmpGet = m_pPlan->mTestCase.mSupply_Get.Imax_30v;   // dòng dang tiêu thụ
	if (abs(ftmpGet - ftmpSet) > epsilon_Inguong) {
		m_status = 0;
		m_BMP_IMAX_30V.SetBitmap(cBmpERR);
	}
	else m_BMP_IMAX_30V.SetBitmap(cBmpOK);


	// #######  dien ap hoat dong   #####
	//8. kiem tra dai dien ap hoat dong của nguồn 12V
	ftmpSet = m_pPlan->mTestCase.mSupply_Set.U12v_DOWN;     // gia tri yeu cau
	ftmpGet = m_pPlan->mTestCase.mSupply_Get.U12v_DOWN;     // gia tri thuc te
	if (abs(ftmpGet - ftmpSet) > epsilon_Inguong) {
		m_status = 0;
		m_BMP_U12V_DOWN.SetBitmap(cBmpERR);
	}
	else m_BMP_U12V_DOWN.SetBitmap(cBmpOK);


	//9. kiem tra dai dien ap hoat dong của nguồn 12V
	ftmpSet = m_pPlan->mTestCase.mSupply_Set.U12v_UP;    // gia tri yeu cau
	ftmpGet = m_pPlan->mTestCase.mSupply_Get.U12v_UP;   // gia tri thuc te
	if (abs(ftmpGet - ftmpSet) > epsilon_Inguong) {
		m_status = 0;
		m_BMP_U12V_UP.SetBitmap(cBmpERR);
	}
	else m_BMP_U12V_UP.SetBitmap(cBmpOK);


	// 10. kiem tra dai dien ap hoat dong của nguồn 30V
	ftmpSet = m_pPlan->mTestCase.mSupply_Set.U30v_UP;   // gia tri yeu cau
	ftmpGet = m_pPlan->mTestCase.mSupply_Get.U30v_UP;  // gia tri thuc te
	if (abs(ftmpGet - ftmpSet) > epsilon_Inguong) {
		m_status = 0;
		m_BMP_U30V_UP.SetBitmap(cBmpERR);
	}
	else m_BMP_U30V_UP.SetBitmap(cBmpOK);

	// 11. kiem tra dai dien ap hoat dong của nguồn 30V
	ftmpSet = m_pPlan->mTestCase.mSupply_Set.U30v_DOWN;// gia tri yeu cau
	ftmpGet = m_pPlan->mTestCase.mSupply_Get.U30v_DOWN; // gia tri thuc te
	if (abs(ftmpGet - ftmpSet) > epsilon_Inguong) {
		m_status = 0;
		m_BMP_U30V_DOWN.SetBitmap(cBmpERR);
	}
	else m_BMP_U30V_DOWN.SetBitmap(cBmpOK);

	return 1;
}


void DlgPowerSettingThreshold::OnBnClickedButtonSet()
{
	// TODO: Add your control notification handler code here
	char RecArr[16];
	int lenRecArr;

	UpdateData(true);     // lenh nay lam gi ?
	UpdateDataGUIToVar();   //    lấy thông tin (String) từ GUI chuyển sang dữ liệu hiện tại (float) của APP đang chạy
	//------------------------------------------

		// in ra de check gia tri get ve
	CString stmp;
	/*
	//stmp.Format(_T("Test get back: Imax_3v3 = %.3f"), m_pPlan->mTestCase.mSupply_Set.Imax_3v3);MessageBox(stmp, _T("Mess"));
	//stmp.Format(_T("Test get back: Imax_5v = %.3f"), m_pPlan->mTestCase.mSupply_Set.Imax_5v);MessageBox(stmp, _T("Mess"));
	//stmp.Format(_T("Test get back: Imax_12v = %.3f"), m_pPlan->mTestCase.mSupply_Set.Imax_12v);MessageBox(stmp, _T("Mess"));
	//stmp.Format(_T("Test get back: Imax_12v_N = %.3f"), m_pPlan->mTestCase.mSupply_Set.Imax_12v_N);MessageBox(stmp, _T("Mess"));

	//stmp.Format(_T("Test get back: Imax_12v_CPU = %.3f"), m_pPlan->mTestCase.mSupply_Set.Imax_12v_CPU);MessageBox(stmp, _T("Mess"));
	//stmp.Format(_T("Test get back: Imax_12v_relay = %.3f"), m_pPlan->mTestCase.mSupply_Set.Imax_12v_ROLE);MessageBox(stmp, _T("Mess"));
	//stmp.Format(_T("Test get back: Imax_30v = %.3f"), m_pPlan->mTestCase.mSupply_Set.Imax_30v);MessageBox(stmp, _T("Mess"));


	//stmp.Format(_T("Test get back: U12V_RL_Down = %.3f"), m_pPlan->mTestCase.mSupply_Set.U12v_DOWN);MessageBox(stmp, _T("Mess"));
	//stmp.Format(_T("Test get back: U12V_RL_UP = %.3f"), m_pPlan->mTestCase.mSupply_Set.U12v_UP);MessageBox(stmp, _T("Mess"));

	//stmp.Format(_T("Test get back: U30V_RL_Down = %.3f"), m_pPlan->mTestCase.mSupply_Set.U30v_DOWN);MessageBox(stmp, _T("Mess"));
	//stmp.Format(_T("Test get back: U30V_RL_UP = %.3f"), m_pPlan->mTestCase.mSupply_Set.U30v_UP);MessageBox(stmp, _T("Mess"));
*/

	Set_Power_Safe();   // set tham so nguong cho thiet bi,
	Sleep(500);
	// read gia tri dong tieu thu cua thiet bi  hien tai len
	Get_Power_Safe();
	m_pPlan->mTestCase.mSupply_Get.Imax_3v3 = m_pPlan->I_max_3v_temp_1 + m_pPlan->I_max_3v_temp_2;
	m_pPlan->mTestCase.mSupply_Get.Imax_12v_ROLE = m_pPlan->I_max_12V_Relay_temp_1 + m_pPlan->I_max_12V_Relay_temp_2;

	// in ra de check gia tri get ve
	//CString stmp;
/*
	stmp.Format(_T("Test get back: Imax_3v3 = %.3f"), m_pPlan->mTestCase.mSupply_Get.Imax_3v3);MessageBox(stmp, _T("Mess"));
	stmp.Format(_T("Test get back: Imax_5v = %.3f"), m_pPlan->mTestCase.mSupply_Get.Imax_5v);MessageBox(stmp, _T("Mess"));
	stmp.Format(_T("Test get back: Imax_12v = %.3f"), m_pPlan->mTestCase.mSupply_Get.Imax_12v);MessageBox(stmp, _T("Mess"));
	stmp.Format(_T("Test get back: Imax_12v_N = %.3f"), m_pPlan->mTestCase.mSupply_Get.Imax_12v_N);MessageBox(stmp, _T("Mess"));

	stmp.Format(_T("Test get back: Imax_12v_CPU = %.3f"), m_pPlan->mTestCase.mSupply_Get.Imax_12v_CPU);MessageBox(stmp, _T("Mess"));
	stmp.Format(_T("Test get back: Imax_12v_relay = %.3f"), m_pPlan->mTestCase.mSupply_Get.Imax_12v_ROLE);MessageBox(stmp, _T("Mess"));
	stmp.Format(_T("Test get back: Imax_30v = %.3f"), m_pPlan->mTestCase.mSupply_Get.Imax_30v);MessageBox(stmp, _T("Mess"));


	stmp.Format(_T("Test get back: U12V_RL_Down = %.3f"), m_pPlan->mTestCase.mSupply_Get.U12v_DOWN);MessageBox(stmp, _T("Mess"));
	stmp.Format(_T("Test get back: U12V_RL_UP = %.3f"), m_pPlan->mTestCase.mSupply_Get.U12v_UP);MessageBox(stmp, _T("Mess"));

	stmp.Format(_T("Test get back: U30V_RL_Down = %.3f"), m_pPlan->mTestCase.mSupply_Get.U30v_DOWN);MessageBox(stmp, _T("Mess"));
	stmp.Format(_T("Test get back: U30V_RL_UP = %.3f"), m_pPlan->mTestCase.mSupply_Get.U30v_UP);MessageBox(stmp, _T("Mess"));
*/


/*

 //   // so sanh xem thiet lap thanh cong chua?
	//float epsilon_Inguong = 0.005;
	//if (abs(m_pPlan->mTestCase.mSupply_Set.Imax_3v3 - m_pPlan->mTestCase.mSupply_Get.Imax_3v3) > epsilon_Inguong)			{ AfxMessageBox(_T("LỖI:  Thiết lập tham số dòng ngưỡng 3V3 không thành công")); return; }
	//else if (abs(m_pPlan->mTestCase.mSupply_Set.Imax_5v - m_pPlan->mTestCase.mSupply_Get.Imax_5v) > epsilon_Inguong)		{ AfxMessageBox(_T("LỖI:  Thiết lập tham số dòng ngưỡng 5V không thành công")); return; }
	//else if (abs(m_pPlan->mTestCase.mSupply_Set.Imax_12v - m_pPlan->mTestCase.mSupply_Get.Imax_12v) > epsilon_Inguong)		{ AfxMessageBox(_T("LỖI:  Thiết lập tham số dòng ngưỡng 12V không thành công")); return; }
	//else if (abs(m_pPlan->mTestCase.mSupply_Set.Imax_12v_N - m_pPlan->mTestCase.mSupply_Get.Imax_12v_N) > epsilon_Inguong)	{ AfxMessageBox(_T("LỖI:  Thiết lập tham số dòng ngưỡng -12V không thành công")); return; }
	//else if (abs(m_pPlan->mTestCase.mSupply_Set.Imax_12v_CPU - m_pPlan->mTestCase.mSupply_Get.Imax_12v_CPU) > epsilon_Inguong) { AfxMessageBox(_T("LỖI:  Thiết lập tham số dòng ngưỡng 12V_CPU không thành công")); return; }
	//else if (abs(m_pPlan->mTestCase.mSupply_Set.Imax_12v_ROLE - m_pPlan->mTestCase.mSupply_Get.Imax_12v_ROLE) > epsilon_Inguong) { AfxMessageBox(_T("LỖI:  Thiết lập tham số dòng ngưỡng 12V_Relay không thành công")); return; }
	//else if (abs(m_pPlan->mTestCase.mSupply_Set.Imax_30v - m_pPlan->mTestCase.mSupply_Get.Imax_30v) > epsilon_Inguong)		{ AfxMessageBox(_T("LỖI:  Thiết lập tham số dòng ngưỡng 30V không thành công")); return; }
	//	 else;
*/
////----------------------------------------

// UpdateDataToGUI();     // lenh nay dang thừa, vì data trùng với data trước đó đã update lên GUI
	UpdateStatus();			// so sanh cau hinh thanh cong va hien thi trang thai
	UpdateData(false);     // ?
}


void DlgPowerSettingThreshold::OnBnClickedExit()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

}


void DlgPowerSettingThreshold::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	UpdateDataGUIToVar();
	
	if (m_pPlan->Save_SUPPLY_TestCase(m_pcFigCIniReader, 0) == 1)
		MessageBox(_T("Lưu thông tin thành công"), _T("Thông báo"));
	else MessageBox(_T("Qua trình lưu xảy ra lỗi"), _T("Thông báo"));
}


void DlgPowerSettingThreshold::OnBnClickedBtnEdit()
{
	// TODO: Add your control notification handler code here
	CInputDialog dlg; 
	if (dlg.DoModal() == IDOK)
	{
		CEdit* pEditCtrl;
		CButton* pButtonCtrl;
		pButtonCtrl = (CButton*)GetDlgItem(IDC_SAVE);
		pButtonCtrl->EnableWindow(true);
		pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_EDIT);
		pButtonCtrl->EnableWindow(false);

		pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_IMAX_3V3);
		pEditCtrl->EnableWindow(true);
		pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_IMAX_5V);
		pEditCtrl->EnableWindow(true);
		pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_IMAX_12V);
		pEditCtrl->EnableWindow(true);
		pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_IMAX_12V_N);
		pEditCtrl->EnableWindow(true);
		pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_IMAX_12V_CPU);
		pEditCtrl->EnableWindow(true);
		pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_IMAX_12V_ROLE);
		pEditCtrl->EnableWindow(true);
		pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_IMAX_30V);
		pEditCtrl->EnableWindow(true);
		pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_U12V_DOWN);
		pEditCtrl->EnableWindow(true);
		pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_U12V_UP);
		pEditCtrl->EnableWindow(true);
		pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_U30V_DOWN);
		pEditCtrl->EnableWindow(true);
		pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_U30V_UP);
		pEditCtrl->EnableWindow(true);
	}
	else MessageBox(_T("Mật khẩu không đúng"), _T("Thông báo"));
}
