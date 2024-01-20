// DlgPowerSettingParam.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgPowerSettingParam.h"


// DlgPowerSettingParam dialog

IMPLEMENT_DYNAMIC(DlgPowerSettingParam, CDialogEx)

DlgPowerSettingParam::DlgPowerSettingParam(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_POWER_SETTING_PARAM, pParent)
	//, m_HV_OUT1(_T(""))
	//, m_HV_OUT2(_T(""))
	//, m_HV_IN1(_T(""))
	//, m_HV_IN2(_T(""))
	//, m_IOEXT_1(_T(""))
	//, m_IOEXT_2(_T(""))
	//, m_SYSCHANEL_1(_T(""))
	//, m_SYSCHANEL_2(_T(""))

	//, m_ADC1(_T(""))
	//, m_ADC2(_T(""))
	//, m_DAC1(_T(""))
	//, m_DAC2(_T(""))

	//, m_V_Hi_LOGIC_OUT(_T(""))
	//, m_V_CMP_LOGIC_IN(_T(""))
	////---------------------
	//, m_HV_OUT1_name(_T(""))
	//, m_HV_OUT2_name(_T(""))
	//, m_HV_IN1_name(_T(""))
	//, m_HV_IN2_name(_T(""))

	//, m_IOEXT_1_name(_T(""))
	//, m_IOEXT_2_name(_T(""))
	//, m_SYSCHANEL_1_name(_T(""))
	//, m_SYSCHANEL_2_name(_T(""))
	//
	//, m_ADC1_name(_T(""))
	//, m_ADC2_name(_T(""))
	//, m_DAC1_name(_T(""))
	//, m_DAC2_name(_T(""))
	//
	//, m_V_Hi_LOGIC_OUT_name(_T(""))
	//, m_V_CMP_LOGIC_IN_name(_T(""))
	//---------------------
{

}

DlgPowerSettingParam::~DlgPowerSettingParam()
{
}

void DlgPowerSettingParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_V_Hi_LOGIC_OUT, m_V_Hi_LOGIC_OUT);
	DDX_Text(pDX, IDC_EDIT_V_CMP_LOGIC_IN, m_V_CMP_LOGIC_IN);
	//DDX_Text(pDX, IDC_EDIT_IOEXT_1, m_IOEXT_1);
	//DDX_Text(pDX, IDC_EDIT_IOEXT_2, m_IOEXT_2);

	DDX_Text(pDX, IDC_EDIT_DAC1, m_DAC1);
	DDX_Text(pDX, IDC_EDIT_DAC2, m_DAC2);
	DDX_Text(pDX, IDC_EDIT_ADC1, m_ADC1);
	DDX_Text(pDX, IDC_EDIT_ADC2, m_ADC2);

	DDX_Text(pDX, IDC_EDIT_HV_OUT1, m_HV_OUT1);
	DDX_Text(pDX, IDC_EDIT_HV_OUT2, m_HV_OUT2);
	DDX_Text(pDX, IDC_EDIT_HV_IN1, m_HV_IN1);
	DDX_Text(pDX, IDC_EDIT_HV_IN2, m_HV_IN2);

	//DDX_Control(pDX, IDC_BMP_V_Hi_LOGIC_OUT, m_BMP_V_Hi_LOGIC_OUT);
	//DDX_Control(pDX, IDC_BMP_V_CMP_LOGIC_IN, m_BMP_V_CMP_LOGIC_IN);
	//DDX_Control(pDX, IDC_BMP_IOEXT_1, m_BMP_IOEXT_1);
	//DDX_Control(pDX, IDC_BMP_IOEXT_2, m_BMP_IOEXT_2);

	//DDX_Control(pDX, IDC_BMP_DAC1, m_BMP_DAC1);
	//DDX_Control(pDX, IDC_BMP_DAC2, m_BMP_DAC2);
	//DDX_Control(pDX, IDC_BMP_ADC1, m_BMP_ADC1);
	//DDX_Control(pDX, IDC_BMP_ADC2, m_BMP_ADC2);

	//DDX_Control(pDX, IDC_BMP_HV_OUT1, m_BMP_HV_OUT1);
	//DDX_Control(pDX, IDC_BMP_HV_OUT2, m_BMP_HV_OUT2);
	//DDX_Control(pDX, IDC_BMP_HV_IN1, m_BMP_HV_IN1);
	//DDX_Control(pDX, IDC_BMP_HV_IN2, m_BMP_HV_IN2);

	//DDX_Control(pDX, IDC_BMP1, m_BMP_HV_OUT1_Ico);
	//DDX_Control(pDX, IDC_BMP2, m_BMP_HV_OUT2_Ico);
	//DDX_Control(pDX, IDC_BMP3, m_BMP_HV_IN1_Ico);
	//DDX_Control(pDX, IDC_BMP4, m_BMP_HV_IN2_Ico);

	//DDX_Control(pDX, IDC_BMP7, m_BMP_IOEXT_1_Ico);
	//DDX_Control(pDX, IDC_BMP8, m_BMP_IOEXT_2_Ico);
	//DDX_Control(pDX, IDC_BMP9, m_BMP_ADC1_Ico);
	//DDX_Control(pDX, IDC_BMP10, m_BMP_ADC2_Ico);
	//DDX_Control(pDX, IDC_BMP11, m_BMP_DAC1_Ico);
	//DDX_Control(pDX, IDC_BMP12, m_BMP_DAC2_Ico);
	//DDX_Control(pDX, IDC_BMP13, m_BMP_V_Hi_LOGIC_OUT_Ico);
	//DDX_Control(pDX, IDC_BMP14, m_BMP_V_CMP_LOGIC_IN_Ico);

	//DDX_Control(pDX, IDC_COMBO_IOEXT_1, m_IOEXT_1_Cb);
	//DDX_Control(pDX, IDC_COMBO_IOEXT_2, m_IOEXT_2_Cb);

	DDX_Control(pDX, IDC_COMBO_VALUE_ADC1, m_Value_ADC1_Cb);
	DDX_Control(pDX, IDC_COMBO_VALUE_ADC2, m_Value_ADC2_Cb);

	DDX_Control(pDX, IDC_COMBO_DAC1, m_DAC1_Cb);
	DDX_Control(pDX, IDC_COMBO_DAC2, m_DAC2_Cb);
	DDX_Control(pDX, IDC_COMBO_ADC1, m_ADC1_Cb);
	DDX_Control(pDX, IDC_COMBO_ADC2, m_ADC2_Cb);

	//DDX_Control(pDX, IDC_COMBO_HV_IN1, m_HV_IN1_Cb);
	//DDX_Control(pDX, IDC_COMBO_HV_IN2, m_HV_IN2_Cb);

	//DDX_Control(pDX, IDC_CHECK_IOEXT_1, m_Chk_IOEXT_1);
	//DDX_Control(pDX, IDC_CHECK_IOEXT_2, m_Chk_IOEXT_2);

	DDX_Control(pDX, IDC_CHECK_DAC1, m_Chk_DAC1);
	DDX_Control(pDX, IDC_CHECK_DAC2, m_Chk_DAC2);
	DDX_Control(pDX, IDC_CHECK_EDIT_ADC1, m_Chk_ADC1);
	DDX_Control(pDX, IDC_CHECK_ADC2, m_Chk_ADC2);

	DDX_Control(pDX, IDC_CHECK_HV_OUT1, m_Chk_HV_OUT1);
	DDX_Control(pDX, IDC_CHECK_HV_OUT2, m_Chk_HV_OUT2);
	DDX_Control(pDX, IDC_CHECK_HV_IN1, m_Chk_HV_IN1);
	DDX_Control(pDX, IDC_CHECK_HV_IN2, m_Chk_HV_IN2);

	DDX_Text(pDX, IDC_EDIT_V_Hi_LOGIC_OUT_name, m_V_Hi_LOGIC_OUT_name);
	DDX_Text(pDX, IDC_EDIT_V_CMP_LOGIC_IN_name, m_V_CMP_LOGIC_IN_name);
	//DDX_Text(pDX, IDC_EDIT_IOEXT_1_name, m_IOEXT_1_name);
	//DDX_Text(pDX, IDC_EDIT_IOEXT_2_name, m_IOEXT_2_name);

	DDX_Text(pDX, IDC_EDIT_DAC1_name, m_DAC1_name);
	DDX_Text(pDX, IDC_EDIT_DAC2_name, m_DAC2_name);
	DDX_Text(pDX, IDC_EDIT_ADC1_name, m_ADC1_name);
	DDX_Text(pDX, IDC_EDIT_ADC2_name, m_ADC2_name);

	DDX_Text(pDX, IDC_EDIT_HV_OUT1_name, m_HV_OUT1_name);
	DDX_Text(pDX, IDC_EDIT_HV_OUT2_name, m_HV_OUT2_name);
	DDX_Text(pDX, IDC_EDIT_HV_IN1_name, m_HV_IN1_name);
	DDX_Text(pDX, IDC_EDIT_HV_IN2_name, m_HV_IN2_name);

	DDX_Control(pDX, IDC_EDIT_TITLE, c_EDIT_TITLE);
	//DDX_Control(pDX, IDC_RADIO1, m_radio1);
	//DDX_Control(pDX, IDC_RADIO2, m_Radio2);
}


BEGIN_MESSAGE_MAP(DlgPowerSettingParam, CDialogEx)

	ON_BN_CLICKED(IDC_BTN_SET, &DlgPowerSettingParam::OnBnClickedBtnSet)
	ON_BN_CLICKED(IDOK, &DlgPowerSettingParam::OnBnClickedOk)
	//ON_BN_CLICKED(IDC_BTN_EDIT, &DlgPowerSettingParam::OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTTN_SAVE, &DlgPowerSettingParam::OnBnClickedBttnSave)
	//ON_BN_CLICKED(IDC_BTN_GETINFO, &DlgPowerSettingParam::OnBnClickedBtnGetinfo)
	//ON_CBN_SELCHANGE(IDC_COMBO_HV_IN1, &DlgPowerSettingParam::OnCbnSelchangeComboHvIn1)
	//ON_CBN_SELCHANGE(IDC_COMBO_HV_IN2, &DlgPowerSettingParam::OnCbnSelchangeComboHvIn2)
	ON_CBN_SELCHANGE(IDC_COMBO_ADC1, &DlgPowerSettingParam::OnCbnSelchangeComboAdc1)
	ON_CBN_SELCHANGE(IDC_COMBO_ADC2, &DlgPowerSettingParam::OnCbnSelchangeComboAdc2)
	ON_CBN_SELCHANGE(IDC_COMBO_DAC1, &DlgPowerSettingParam::OnCbnSelchangeComboDac1)
	ON_CBN_SELCHANGE(IDC_COMBO_DAC2, &DlgPowerSettingParam::OnCbnSelchangeComboDac2)
	//ON_BN_CLICKED(IDC_RADIO1, &DlgPowerSettingParam::OnBnClickedRadio1)
	//ON_BN_CLICKED(IDC_RADIO2, &DlgPowerSettingParam::OnBnClickedRadio2)
	ON_EN_CHANGE(IDC_EDIT_TITLE, &DlgPowerSettingParam::OnEnChangeEditTitle)
	ON_CBN_SELCHANGE(IDC_COMBO_VALUE_ADC1, &DlgPowerSettingParam::OnCbnSelchangeComboValueADC1)
	ON_CBN_SELCHANGE(IDC_COMBO_VALUE_ADC2, &DlgPowerSettingParam::OnCbnSelchangeComboValueADC2)
END_MESSAGE_MAP()


// DlgPowerSettingParam message handlers
BOOL DlgPowerSettingParam::OnInitDialog() {
	CDialog::OnInitDialog();
	TESTCASE_CONFIG* m_pTetCase;
	EXTCHANELINFO_DEF* m_pExtChanel_Set;
	m_pExtChanel_Set = &(m_pPlan->mTestCase.ExtChanel_Set);
	m_pTetCase = &(m_pPlan->mTestCase.mTestCaseConfig);
	m_numChanel = m_pPlan->mTestCase.mTestCaseConfig.nChanels;
	//--------------------
	m_pExtChanel_Set->EXT_io1.text = _T("5 vol");
	m_pExtChanel_Set->EXT_io2.text = _T("5 vol");
	//--------------------
	cBmpOK.LoadBitmap(IDB_BITMAP_ON);
	cBmpERR.LoadBitmap(IDB_BITMAP_OFF);
	cBmpNM.LoadBitmap(IDB_BMP_ONOFNM);
	CEdit* pEditCtrl;
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_TITLE);
	pEditCtrl->SetFont(m_tfont);
	pEditCtrl->SetWindowTextW(_T("THIẾT LẬP THAM SỐ TÍN HIỆU VÀ KÊNH MỞ RỘNG"));
	
	for (int i = 1; i <= m_numChanel; i++) ChanelSelArr1[i] = m_pTetCase->ChanelSelectArr[i];
	for (int i = 1; i <= m_numChanel; i++) {
		ChanelPinArr[i] = 0;
		if (ChanelSelArr1[i]) {
			int _count = 0;
			for (int ii = 1; ii <= m_pTetCase->nPins; ii++)
				if (m_pTetCase->mPinsConf[ii].iChanel == i) {
					_count++;
					ChanelPinArr[i] = ii;
				}
			if (_count > 1) ChanelSelArr1[i] = 0;
		}
	}
	for (int i = 1; i <= m_numChanel; i++) ChanelSelArr1[i] = 1 - ChanelSelArr1[i];

	ChanelSelArr1[m_numChanel+1] = 0;
	ChanelSelArr1[m_numChanel+2] = 0;
	for (int i = 1; i <= m_numChanel; i++) ChanelSelArr2[i] = ChanelSelArr1[i];
	
	nSelDAC1 = m_pExtChanel_Set->DAC_out1.nChanel;		//2
	nSelDAC2 = m_pExtChanel_Set->DAC_out2.nChanel;		//3
	nSelADC1 = m_pExtChanel_Set->ADC_in1.nChanel;		//4
	nSelADC2 = m_pExtChanel_Set->ADC_in2.nChanel;		//5

	nSelHV1 = m_pExtChanel_Set->HV_in1.nChanel;			//6
	nSelHV2 = m_pExtChanel_Set->HV_in2.nChanel;			//7
	
	if(nSelDAC1!=0)
		if (ChanelSelArr1[nSelDAC1] != 0) {
			MessageBox(_T("Thiết lập sai lựa chọn kênh ra DAC1\r\nCần ghi lai thiết lập"), _T("Thông báo") );
			nSelDAC1 = 0;
		}
	ChanelSelArr1[nSelDAC1] = 2;
	if (nSelDAC2 != 0)
		if (ChanelSelArr1[nSelDAC2] != 0) {
			MessageBox(_T("Thiết lập sai lựa chọn kênh ra DAC2\r\nCần ghi lai thiết lập"),_T("Thông báo"));
			nSelDAC2 = 0;

		}
	ChanelSelArr1[nSelDAC2] = 3;
	if (nSelADC1 <= m_numChanel) {
		if (nSelADC1 != 0)
			if (ChanelSelArr1[nSelADC1] != 0) {
				MessageBox(_T("Thiết lập sai lựa chọn kênh vào ADC1\r\nCần ghi lai thiết lập"), _T("Thông báo"));
				nSelADC1 = 0;
			}
		ChanelSelArr1[nSelADC1] = 4;
	}
	else {
		ChanelSelArr1[nSelADC1 - 90 + m_numChanel] = 4;
	}

	if (nSelADC2 <= m_numChanel) {
		if(nSelADC2!=0)
			if (ChanelSelArr1[nSelADC2] != 0) {
				MessageBox(_T("Thiết lập sai lựa chọn kênh vào ADC2\r\nCần ghi lai thiết lập"), _T("Thông báo"));
				nSelADC2 = 0;

			}
		ChanelSelArr1[nSelADC2] = 5;
	}
	else {
		ChanelSelArr1[nSelADC2 - 90 + m_numChanel] = 5;
	}
	if(nSelHV1!=0)
		if (ChanelSelArr2[nSelHV1] != 0) {
			//MessageBox(_T("Thiết lập sai lựa chọn kênh vào HV_1\r\nCần ghi lai thiết lập"), _T("Thông báo"));
			nSelHV1 = 0;
		}

	ChanelSelArr2[nSelHV1] = 6;
	if(nSelHV2!=0)
		if (ChanelSelArr2[nSelHV2] != 0) {
			//MessageBox(_T("Thiết lập sai lựa chọn kênh vào HV_2\r\nCần ghi lai thiết lập"), _T("Thông báo"));
			nSelHV2 = 0;

		}
	ChanelSelArr2[nSelHV2] = 7;

	UpdateDataToGUI();
	UpdateStatus(0);

	Init_CB_Value_ADC();
	Init_CB_M1(0);
	Init_CB_M2(0);
	m_Setmode = m_pExtChanel_Set->SetMode;
	if (m_Setmode == 1) {
		m_radio1.SetCheck(1);
		m_Radio2.SetCheck(0);
	}
	else {
		m_radio1.SetCheck(0);
		m_Radio2.SetCheck(1);
	}
	UpdateData(FALSE);

	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_DAC1);
	pEditCtrl->ShowWindow(0);
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_DAC2);
	pEditCtrl->ShowWindow(0);
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_ADC1);
	pEditCtrl->ShowWindow(0);
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_ADC2);
	pEditCtrl->ShowWindow(0);
	//CWnd* pwnd = GetDlgItem(IDC_BTN_EDIT);
	//if (pwnd)
	//	pwnd->EnableWindow(true);
	//pwnd = GetDlgItem(IDC_BTN_SET);
	//if (pwnd)
	//	pwnd->EnableWindow(true);
	//pwnd = GetDlgItem(IDC_BTTN_SAVE);
	//if (pwnd)
	//	pwnd->EnableWindow(true);
	//if (GETDATABASE) {
	//	CWnd* pwnd = GetDlgItem(IDC_BTN_SET);
	//	if (pwnd)
	//		pwnd->EnableWindow(false);
	//}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

int DlgPowerSettingParam::Set_Get_Power_Param() {
	// Get xong, can lay gia trij cho vaof plan- GET
	// Thanh viet
	//m_pPlan->SetUp8Power(m_pPlan->mTestCase.mPowers, RecArr, &lenRecArr);
	return 1;
}

void DlgPowerSettingParam::OnBnClickedBtnSet()
{
	// TODO: Add your control notification handler code here
	if (UpdateDataGUIToVar()) return;

	byte Mode1Arr[9], Mode2Arr[9];
	

	EXTCHANELINFO_DEF* m_pExtChanel_Set, * m_pExtChanel_Get;
	m_pExtChanel_Set = &(m_pPlan->mTestCase.ExtChanel_Set);
	m_pExtChanel_Get = &(m_pPlan->mTestCase.ExtChanel_Get);
	m_pExtChanel_Set->SetMode = m_Setmode;
	//=============================================================================
	for (int i = 1; i <= 8; i++) Mode1Arr[i] = 0;
	if (m_pExtChanel_Set->ADC_in1.nChanel <= 40) Mode1Arr[1] = m_pExtChanel_Set->ADC_in1.nChanel;
	else Mode1Arr[5] = m_pExtChanel_Set->ADC_in1.nChanel;
	if (m_pExtChanel_Set->ADC_in2.nChanel <= 40) Mode1Arr[2] = m_pExtChanel_Set->ADC_in2.nChanel;
	else Mode1Arr[6] = m_pExtChanel_Set->ADC_in2.nChanel;
	if (m_pExtChanel_Set->DAC_out1.nChanel <= 40) Mode1Arr[3] = m_pExtChanel_Set->DAC_out1.nChanel;
	else Mode1Arr[7] = m_pExtChanel_Set->DAC_out1.nChanel;
	if (m_pExtChanel_Set->DAC_out2.nChanel <= 40) Mode1Arr[4] = m_pExtChanel_Set->DAC_out2.nChanel;
	else Mode1Arr[8] = m_pExtChanel_Set->DAC_out2.nChanel;
	
	for (int i = 1; i <= 8; i++) Mode2Arr[i] = 0;
	if (m_pExtChanel_Set->HV_in1.nChanel <= 40) Mode1Arr[1] = m_pExtChanel_Set->HV_in1.nChanel;
	else Mode1Arr[5] = m_pExtChanel_Set->HV_in1.nChanel;
	if (m_pExtChanel_Set->HV_in2.nChanel <= 40) Mode1Arr[2] = m_pExtChanel_Set->HV_in2.nChanel;
	else Mode1Arr[6] = m_pExtChanel_Set->HV_in2.nChanel;
	//==================================================
	
	// TUAN viet code 1 -> set, 2-> get dữ liẹu
	// 1. Function thiet lap
	// 2. Function lấy giá trị trả ve
	// Neu khong co lõi mErr = 0, coloi mErr = 1;
	//-------------------------------------------
	byte mErr = 0;

	//==================================================

	if (mErr == 0) UpdateStatus(1);
	if (mErr == 1) UpdateStatus(2);
	UpdateData(FALSE);
}


void DlgPowerSettingParam::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

void DlgPowerSettingParam::UpdateStatus(int cn) {
	//cn = 0-> bat day chay
	//cn = 1: lay duoc tham so
	//cn = 2: thiet lap co loi

	EXTCHANELINFO_DEF* m_pExtChanel_Set, * m_pExtChanel_Get;
	m_pExtChanel_Set = &(m_pPlan->mTestCase.ExtChanel_Set);
	m_pExtChanel_Get = &(m_pPlan->mTestCase.ExtChanel_Get);
	float tmpThreshol = m_pExtChanel_Set->SignParaVerifyThreshol;
	float ftmpGet, ftmpSet;
	float MOT = 1.0;
	if (cn == 0) {
		m_BMP_HV_OUT1.SetBitmap(cBmpNM);
		m_BMP_HV_OUT2.SetBitmap(cBmpNM);
		m_BMP_HV_IN1.SetBitmap(cBmpNM);
		m_BMP_HV_IN2.SetBitmap(cBmpNM);
		m_BMP_IOEXT_1.SetBitmap(cBmpNM);
		m_BMP_IOEXT_2.SetBitmap(cBmpNM);
		m_BMP_ADC1.SetBitmap(cBmpNM);
		m_BMP_ADC2.SetBitmap(cBmpNM);
		m_BMP_DAC1.SetBitmap(cBmpNM);
		m_BMP_DAC2.SetBitmap(cBmpNM);
		m_BMP_V_Hi_LOGIC_OUT.SetBitmap(cBmpNM);
		m_BMP_V_CMP_LOGIC_IN.SetBitmap(cBmpNM);
	}
	if (cn == 2) {
		m_BMP_HV_OUT1.SetBitmap(cBmpNM);
		m_BMP_HV_OUT2.SetBitmap(cBmpNM);
		m_BMP_HV_IN1.SetBitmap(cBmpNM);
		m_BMP_HV_IN2.SetBitmap(cBmpNM);
		m_BMP_IOEXT_1.SetBitmap(cBmpNM);
		m_BMP_IOEXT_2.SetBitmap(cBmpNM);
		m_BMP_ADC1.SetBitmap(cBmpNM);
		m_BMP_ADC2.SetBitmap(cBmpNM);
		m_BMP_DAC1.SetBitmap(cBmpNM);
		m_BMP_DAC2.SetBitmap(cBmpNM);
		m_BMP_V_Hi_LOGIC_OUT.SetBitmap(cBmpNM);
		m_BMP_V_CMP_LOGIC_IN.SetBitmap(cBmpNM);

		if (m_pExtChanel_Get->HV_out1.used == 1) m_BMP_HV_OUT1.SetBitmap(cBmpERR);
		if (m_pExtChanel_Get->HV_out2.used == 1) m_BMP_HV_OUT2.SetBitmap(cBmpERR);
		if (m_pExtChanel_Get->HV_in1.used == 1) m_BMP_HV_IN1.SetBitmap(cBmpERR);
		if (m_pExtChanel_Get->HV_in2.used == 1) m_BMP_HV_IN2.SetBitmap(cBmpERR);
		if (m_pExtChanel_Get->EXT_io1.used == 1) m_BMP_IOEXT_1.SetBitmap(cBmpERR);
		if (m_pExtChanel_Get->EXT_io2.used == 1) m_BMP_IOEXT_2.SetBitmap(cBmpERR);
		if (m_pExtChanel_Get->ADC_in1.used == 1) m_BMP_ADC1.SetBitmap(cBmpERR);
		if (m_pExtChanel_Get->ADC_in2.used == 1) m_BMP_ADC2.SetBitmap(cBmpERR);
		if (m_pExtChanel_Get->DAC_out1.used == 1) m_BMP_DAC1.SetBitmap(cBmpERR);
		if (m_pExtChanel_Get->DAC_out2.used == 1) m_BMP_DAC2.SetBitmap(cBmpERR);
		m_BMP_V_Hi_LOGIC_OUT.SetBitmap(cBmpERR);
		m_BMP_V_CMP_LOGIC_IN.SetBitmap(cBmpERR);
	}
	if (cn == 1) {
		if (m_pExtChanel_Get->HV_out1.used == 1) {
			ftmpSet = m_pExtChanel_Set->HV_out1.value;
			ftmpGet = m_pExtChanel_Get->HV_out1.value;
			if ((ftmpGet < ftmpSet * (MOT - tmpThreshol)) || (ftmpGet > ftmpSet * (MOT + tmpThreshol)))
				m_BMP_HV_OUT1.SetBitmap(cBmpERR);
			else m_BMP_HV_OUT1.SetBitmap(cBmpOK);
		}
		else m_BMP_HV_OUT1.SetBitmap(cBmpNM);

		if (m_pExtChanel_Get->HV_out2.used == 1) {
			ftmpSet = m_pExtChanel_Set->HV_out2.value;
			ftmpGet = m_pExtChanel_Get->HV_out2.value;
			if ((ftmpGet < ftmpSet * (MOT - tmpThreshol)) || (ftmpGet > ftmpSet * (MOT + tmpThreshol)))
				m_BMP_HV_OUT2.SetBitmap(cBmpERR);
			else m_BMP_HV_OUT2.SetBitmap(cBmpOK);
		}
		else m_BMP_HV_OUT2.SetBitmap(cBmpNM);

		if (m_pExtChanel_Get->HV_in1.used == 1) {
			ftmpSet = m_pExtChanel_Set->HV_in1.value;
			ftmpGet = m_pExtChanel_Get->HV_in1.value;
			if ((ftmpGet < ftmpSet * (MOT - tmpThreshol)) || (ftmpGet > ftmpSet * (MOT + tmpThreshol)))
				m_BMP_HV_IN1.SetBitmap(cBmpERR);
			else m_BMP_HV_IN1.SetBitmap(cBmpOK);
		}
		else m_BMP_HV_IN1.SetBitmap(cBmpNM);

		if (m_pExtChanel_Get->HV_in2.used == 1) {
			ftmpSet = m_pExtChanel_Set->HV_in2.value;
			ftmpGet = m_pExtChanel_Get->HV_in2.value;
			if ((ftmpGet < ftmpSet * (MOT - tmpThreshol)) || (ftmpGet > ftmpSet * (MOT + tmpThreshol)))
				m_BMP_HV_IN2.SetBitmap(cBmpERR);
			else m_BMP_HV_IN2.SetBitmap(cBmpOK);
		}
		else m_BMP_HV_IN2.SetBitmap(cBmpNM);

		if (m_pExtChanel_Get->ADC_in1.used == 1) {
			ftmpSet = m_pExtChanel_Set->ADC_in1.value;
			ftmpGet = m_pExtChanel_Get->ADC_in1.value;
			if ((ftmpGet < ftmpSet * (MOT - tmpThreshol)) || (ftmpGet > ftmpSet * (MOT + tmpThreshol)))
				m_BMP_ADC1.SetBitmap(cBmpERR);
			else m_BMP_ADC1.SetBitmap(cBmpOK);
		}
		else m_BMP_ADC1.SetBitmap(cBmpNM);

		if (m_pExtChanel_Get->ADC_in2.used == 1) {
			ftmpSet = m_pExtChanel_Set->ADC_in2.value;
			ftmpGet = m_pExtChanel_Get->ADC_in2.value;
			if ((ftmpGet < ftmpSet * (MOT - tmpThreshol)) || (ftmpGet > ftmpSet * (MOT + tmpThreshol)))
				m_BMP_ADC2.SetBitmap(cBmpERR);
			else m_BMP_ADC2.SetBitmap(cBmpOK);
		}
		else m_BMP_ADC2.SetBitmap(cBmpNM);

		if (m_pExtChanel_Get->DAC_out1.used == 1) {
			ftmpSet = m_pExtChanel_Set->DAC_out1.value;
			ftmpGet = m_pExtChanel_Get->DAC_out1.value;
			if ((ftmpGet < ftmpSet * (MOT - tmpThreshol)) || (ftmpGet > ftmpSet * (MOT + tmpThreshol)))
				m_BMP_DAC1.SetBitmap(cBmpERR);
			else m_BMP_DAC1.SetBitmap(cBmpOK);
		}
		else m_BMP_DAC1.SetBitmap(cBmpNM);

		if (m_pExtChanel_Get->DAC_out2.used == 1) {
			ftmpSet = m_pExtChanel_Set->DAC_out2.value;
			ftmpGet = m_pExtChanel_Get->DAC_out2.value;
			if ((ftmpGet < ftmpSet * (MOT - tmpThreshol)) || (ftmpGet > ftmpSet * (MOT + tmpThreshol)))
				m_BMP_DAC2.SetBitmap(cBmpERR);
			else m_BMP_DAC2.SetBitmap(cBmpOK);
		}
		else m_BMP_DAC2.SetBitmap(cBmpNM);

		ftmpSet = m_pExtChanel_Set->LogicOutHi.value;
		ftmpGet = m_pExtChanel_Get->LogicOutHi.value;
		if ((ftmpGet < ftmpSet * (MOT - tmpThreshol)) || (ftmpGet > ftmpSet * (MOT + tmpThreshol)))
			m_BMP_V_Hi_LOGIC_OUT.SetBitmap(cBmpERR);
		else m_BMP_V_Hi_LOGIC_OUT.SetBitmap(cBmpOK);

		ftmpSet = m_pExtChanel_Set->LogicInComp.value;
		ftmpGet = m_pExtChanel_Get->LogicInComp.value;
		if ((ftmpGet < ftmpSet * (MOT - tmpThreshol)) || (ftmpGet > ftmpSet * (MOT + tmpThreshol)))
			m_BMP_V_CMP_LOGIC_IN.SetBitmap(cBmpERR);
		else m_BMP_V_CMP_LOGIC_IN.SetBitmap(cBmpOK);
	}
}

void DlgPowerSettingParam::UpdateDataToGUI() {
	EXTCHANELINFO_DEF* m_pExtChanel_Set;
	m_pExtChanel_Set = &(m_pPlan->mTestCase.ExtChanel_Set);

	m_V_Hi_LOGIC_OUT_name = m_pExtChanel_Set->LogicOutHi.name;
	m_V_CMP_LOGIC_IN_name = m_pExtChanel_Set->LogicInComp.name;
	m_IOEXT_1_name = m_pExtChanel_Set->EXT_io1.name;
	m_IOEXT_2_name = m_pExtChanel_Set->EXT_io2.name;

	m_DAC1_name = m_pExtChanel_Set->DAC_out1.name;
	m_DAC2_name = m_pExtChanel_Set->DAC_out2.name;
	m_ADC1_name = m_pExtChanel_Set->ADC_in1.name;
	m_ADC2_name = m_pExtChanel_Set->ADC_in2.name;

	m_HV_OUT1_name = m_pExtChanel_Set->HV_out1.name;
	m_HV_OUT2_name = m_pExtChanel_Set->HV_out2.name;
	m_HV_IN1_name = m_pExtChanel_Set->HV_in1.name;
	m_HV_IN2_name = m_pExtChanel_Set->HV_in2.name;

	m_V_Hi_LOGIC_OUT.Format(_T("%0.2f"), m_pExtChanel_Set->LogicOutHi.value);
	m_V_CMP_LOGIC_IN.Format(_T("%0.2f"), m_pExtChanel_Set->LogicInComp.value);
	m_IOEXT_1 = m_pExtChanel_Set->EXT_io1.text;
	m_IOEXT_2 = m_pExtChanel_Set->EXT_io2.text;

	m_DAC1.Format(_T("%0.2f"), m_pExtChanel_Set->DAC_out1.value);
	m_DAC2.Format(_T("%0.2f"), m_pExtChanel_Set->DAC_out2.value);

	//m_ADC1.Format(_T("%0.2f"), m_pExtChanel_Set->ADC_in1.value);
	//m_ADC2.Format(_T("%0.2f"), m_pExtChanel_Set->ADC_in2.value);
	int nSelCur = 0; 
	if (m_pExtChanel_Set->ADC_in1.value == 1) nSelCur = 0;
	else if (m_pExtChanel_Set->ADC_in1.value == 10) nSelCur = 1;
	else if (m_pExtChanel_Set->ADC_in1.value == 100) nSelCur = 2;
	else if (m_pExtChanel_Set->ADC_in1.value == 1000) nSelCur = 3;
	m_Value_ADC1_Cb.SetCurSel(nSelCur);

	nSelCur = 0;
	if (m_pExtChanel_Set->ADC_in2.value == 1) nSelCur = 0;
	else if (m_pExtChanel_Set->ADC_in2.value == 10) nSelCur = 1;
	else if (m_pExtChanel_Set->ADC_in2.value == 100) nSelCur = 2;
	else if (m_pExtChanel_Set->ADC_in2.value == 1000) nSelCur = 3;
	m_Value_ADC2_Cb.SetCurSel(nSelCur);

	m_HV_OUT1.Format(_T("%0.2f"), m_pExtChanel_Set->HV_out1.value);
	m_HV_OUT2.Format(_T("%0.2f"), m_pExtChanel_Set->HV_out2.value);
	m_HV_IN1.Format(_T("%0.2f"), m_pExtChanel_Set->HV_in1.value);
	m_HV_IN2.Format(_T("%0.2f"), m_pExtChanel_Set->HV_in2.value);

	//---------------------------------
	m_Chk_IOEXT_1.SetCheck(m_pExtChanel_Set->EXT_io1.used);
	m_Chk_IOEXT_1.UpdateData(false);
	m_Chk_IOEXT_2.SetCheck(m_pExtChanel_Set->EXT_io2.used);
	m_Chk_IOEXT_2.UpdateData(true);

	m_Chk_DAC1.SetCheck(m_pExtChanel_Set->ADC_in1.used);
	m_Chk_DAC2.SetCheck(m_pExtChanel_Set->ADC_in2.used);
	m_Chk_ADC1.SetCheck(m_pExtChanel_Set->DAC_out1.used);
	m_Chk_ADC2.SetCheck(m_pExtChanel_Set->DAC_out2.used);

	m_Chk_HV_OUT1.SetCheck(m_pExtChanel_Set->HV_out1.used);
	m_Chk_HV_OUT2.SetCheck(m_pExtChanel_Set->HV_out2.used);
	m_Chk_HV_IN1.SetCheck(m_pExtChanel_Set->HV_in1.used);
	m_Chk_HV_IN2.SetCheck(m_pExtChanel_Set->HV_in2.used);
	//----------------------------------
	m_IOEXT_1_Cb.Clear();
	m_IOEXT_1_Cb.AddString(_T("IN"));
	m_IOEXT_1_Cb.AddString(_T("OUT"));
	m_IOEXT_1_Cb.SetCurSel(m_pExtChanel_Set->EXT_io1.IN_OUT);

	m_IOEXT_2_Cb.Clear();
	m_IOEXT_2_Cb.AddString(_T("IN"));
	m_IOEXT_2_Cb.AddString(_T("OUT"));
	m_IOEXT_2_Cb.SetCurSel(m_pExtChanel_Set->EXT_io2.IN_OUT);
	//----------------------------------
	UpdateData(false);
}

int DlgPowerSettingParam::ChanelToNum(CString strTmp) {
	CString str;
	for (int i = 1; i <= m_numChanel; i++)
	{
		str.Format(_T("Kênh %d  ->  Chân %d"), i, ChanelPinArr[i]);
		if (strTmp == str) return i;
	}
	if (strTmp == _T("Kênh mở rộng 1")) return 91;
	if (strTmp == _T("Kênh mở rộng 2")) return 92;
	return 0;
}
void DlgPowerSettingParam::Init_CB_Value_ADC() {
	EXTCHANELINFO_DEF* m_pExtChanel_Set;
	m_pExtChanel_Set = &(m_pPlan->mTestCase.ExtChanel_Set);

	int nSelCur; 
	m_Value_ADC1_Cb.AddString(_T("1:1"));
	m_Value_ADC1_Cb.AddString(_T("1:10"));
	m_Value_ADC1_Cb.AddString(_T("1:100"));
	m_Value_ADC1_Cb.AddString(_T("1:1000"));
	m_Value_ADC2_Cb.AddString(_T("1:1"));
	m_Value_ADC2_Cb.AddString(_T("1:10"));
	m_Value_ADC2_Cb.AddString(_T("1:100"));
	m_Value_ADC2_Cb.AddString(_T("1:1000"));

	if (m_pExtChanel_Set->ADC_in1.value <= 1) nSelCur = 0;
	else if (m_pExtChanel_Set->ADC_in1.value <= 10) nSelCur = 1;
	else if (m_pExtChanel_Set->ADC_in1.value <= 100) nSelCur = 2;
	else nSelCur = 3;
	m_Value_ADC1_Cb.SetCurSel(nSelCur);
	
	if (m_pExtChanel_Set->ADC_in2.value <= 1) nSelCur = 0;
	else if (m_pExtChanel_Set->ADC_in2.value <= 10) nSelCur = 1;
	else if (m_pExtChanel_Set->ADC_in2.value <= 100) nSelCur = 2;
	else nSelCur = 3;
	m_Value_ADC2_Cb.SetCurSel(nSelCur);
}
void DlgPowerSettingParam::Init_CB_M1(int k) {
	int tm;

	CString str;
	int count;
	int nSelCur;
	//-------------------------------------
	if (k != 2) {
		while (m_DAC1_Cb.GetCount() > 0) m_DAC1_Cb.DeleteString(0);
		//m_DAC1_Cb.Clear();
		m_DAC1_Cb.AddString(_T("Không chọn"));
		nSelCur = 0;
		count = 0;
		for (int i = 1; i <= m_numChanel; i++)
		{
			if (ChanelSelArr1[i] == 0 || ChanelSelArr1[i] == 2) {
				ChanelSelArr1[i] = 0;
				str.Format(_T("Kênh %d  ->  Chân %d"), i, ChanelPinArr[i]);
				m_DAC1_Cb.AddString(str);
				count++;
				if (i == nSelDAC1) nSelCur = count;
			}
		}
		if (nSelCur == 0) nSelDAC1 = 0;
		ChanelSelArr1[nSelDAC1] = 2;
		m_DAC1_Cb.SetCurSel(nSelCur);
	}

	if (k != 3) {
		while (m_DAC2_Cb.GetCount() > 0) m_DAC2_Cb.DeleteString(0);
		//m_DAC2_Cb.Clear();
		m_DAC2_Cb.AddString(_T("Không chọn"));
		nSelCur = 0;
		count = 0;
		for (int i = 1; i <= m_numChanel; i++)
		{
			if (ChanelSelArr1[i] == 0 || ChanelSelArr1[i] == 3) {
				ChanelSelArr1[i] = 0;
				str.Format(_T("Kênh %d  ->  Chân %d"), i, ChanelPinArr[i]);
				m_DAC2_Cb.AddString(str);
				count++;
				if (i == nSelDAC2) nSelCur = count;
			}
		}
		if (nSelCur == 0) nSelDAC2 = 0;
		ChanelSelArr1[nSelDAC2] = 3;
		m_DAC2_Cb.SetCurSel(nSelCur);
	}
	//------------------------------------------
	if (k != 4) {
		while (m_ADC1_Cb.GetCount() > 0) m_ADC1_Cb.DeleteString(0);
		//m_ADC1_Cb.Clear();
		m_ADC1_Cb.AddString(_T("Không chọn"));
		nSelCur = 0;
		count = 0;
		for (int i = 1; i <= m_numChanel; i++)
		{
			if (ChanelSelArr1[i] == 0 || ChanelSelArr1[i] == 4) {
				ChanelSelArr1[i] = 0;
				str.Format(_T("Kênh %d  ->  Chân %d"), i, ChanelPinArr[i]);
				m_ADC1_Cb.AddString(str);
				count++;
				if (i == nSelADC1) nSelCur = count;
			}
		}
		////--------MR1= 91, MR2 = 92-----------
		//if (nSelADC2 <= m_numChanel) {
		//	m_ADC1_Cb.AddString(_T("Kênh mở rộng 1"));
		//	m_ADC1_Cb.AddString(_T("Kênh mở rộng 2"));
		//}
		//else {
		//	if (nSelADC2 == 92) m_ADC1_Cb.AddString(_T("Kênh mở rộng 1"));
		//	if (nSelADC2 == 91) m_ADC1_Cb.AddString(_T("Kênh mở rộng 2"));
		//}
		//count++;
		//if (91 == nSelADC1) nSelCur = count;
		//if (92 == nSelADC1) nSelCur = count;
		////-------------------

		if (nSelCur == 0) nSelADC1 = 0;
		if (nSelADC1 <= m_numChanel) ChanelSelArr1[nSelADC1] = 4;
		else ChanelSelArr1[m_numChanel + nSelADC1 - 90] = 4;

		m_ADC1_Cb.SetCurSel(nSelCur);
	}
	//-------------------------------------------------------------
	if (k != 5) {
		while (m_ADC2_Cb.GetCount() > 0) m_ADC2_Cb.DeleteString(0);
		//m_ADC2_Cb.Clear();
		m_ADC2_Cb.AddString(_T("Không chọn"));
		nSelCur = 0;
		count = 0;
		for (int i = 1; i <= m_numChanel; i++)
		{
			if (ChanelSelArr1[i] == 0 || ChanelSelArr1[i] == 5) {
				ChanelSelArr1[i] = 0;
				str.Format(_T("Kênh %d  ->  Chân %d"), i, ChanelPinArr[i]);
				
				m_ADC2_Cb.AddString(str);
				count++;
				if (i == nSelADC2) nSelCur = count;
			}
		}
		////--------MR1= 91, MR2 = 92-----------
		//if (nSelADC1 <= m_numChanel) {
		//	m_ADC2_Cb.AddString(_T("Kênh mở rộng 1"));
		//	m_ADC2_Cb.AddString(_T("Kênh mở rộng 2"));
		//}
		//else {
		//	if (nSelADC1 == 92) m_ADC2_Cb.AddString(_T("Kênh mở rộng 1"));
		//	if (nSelADC1 == 91) m_ADC2_Cb.AddString(_T("Kênh mở rộng 2"));
		//}
		//count++;
		//if (91 == nSelADC2) nSelCur = count;
		//if (92 == nSelADC2) nSelCur = count;
		////-------------------

		if (nSelCur == 0) nSelADC2 = 0;
		if (nSelADC2 <= m_numChanel)	ChanelSelArr1[nSelADC2] = 5;
		else ChanelSelArr1[m_numChanel + nSelADC2 - 90] = 5;
		m_ADC2_Cb.SetCurSel(nSelCur);
	}

}
void DlgPowerSettingParam::Init_CB_M2(int k) {
	int tm;

	CString str;
	int count;
	int nSelCur;
	//-------------------------------------
	if (k != 6) {
		//m_HV_IN1_Cb.Clear();
		while (m_HV_IN1_Cb.GetCount() > 0) m_HV_IN1_Cb.DeleteString(0);
		m_HV_IN1_Cb.AddString(_T("Không chọn"));
		nSelCur = 0;
		count = 0;
		for (int i = 1; i <= m_numChanel; i++)
		{
			if (ChanelSelArr2[i] == 0 || ChanelSelArr2[i] == 6) {
				ChanelSelArr2[i] = 0;
				str.Format(_T("Kênh %d  ->  Chân %d"), i, ChanelPinArr[i]);
				
				m_HV_IN1_Cb.AddString(str);
				count++;
				if (i == nSelHV1) nSelCur = count;
			}
		}
		if (nSelCur == 0) nSelHV1 = 0;
		ChanelSelArr2[nSelHV1] = 6;
		m_HV_IN1_Cb.SetCurSel(nSelCur);
	}
	//------------------------------------
	if (k != 7) {
		//m_HV_IN2_Cb.Clear();
		while (m_HV_IN2_Cb.GetCount() > 0) m_HV_IN2_Cb.DeleteString(0);
		m_HV_IN2_Cb.AddString(_T("Không chọn"));
		nSelCur = 0;
		count = 0;
		for (int i = 1; i <= m_numChanel; i++)
		{
			if (ChanelSelArr2[i] == 0 || ChanelSelArr2[i] == 7) {
				ChanelSelArr2[i] = 0;
				str.Format(_T("Kênh %d  ->  Chân %d"), i, ChanelPinArr[i]);
				
				m_HV_IN2_Cb.AddString(str);
				count++;
				if (i == nSelHV2) nSelCur = count;
			}
		}
		if (nSelCur == 0) nSelHV2 = 0;
		ChanelSelArr2[nSelHV2] = 7;
		m_HV_IN2_Cb.SetCurSel(nSelCur);
	}

}
int DlgPowerSettingParam::UpdateDataGUIToVar() {
	UpdateData(TRUE);

	int iReturn;
	float mmax, mmin;
	CString mmess;
	mmax = 12; mmin = 0;
	iReturn = m_pPlan->CheckStrToNum(m_V_Hi_LOGIC_OUT.GetBuffer(), 1, mmax, mmin, 1, 1);
	if (iReturn) {
		if (iReturn == 1) MessageBox(_T("Giá trị thiết lập điện áp mức cao logic không hợp lệ\n\rPhải là số"), _T("Thông báo"));
		if (iReturn == 2) {
			mmess.Format(_T("Giá trị thiết lập điện áp mức cao logic không hợp lệ:\n\rPhải nằm trong khoảng [%0.0f, %0.0f]"), mmin, mmax);
			MessageBox(mmess, _T("Thông báo"));
		}
		if (iReturn == 3) {
			mmess.Format(_T("Giá trị thiết lập điện áp mức cao logic không hợp lệ:\n\rPhải là số >= %0.0f"), mmin);
			MessageBox(mmess, _T("Thông báo"));
		}
		return iReturn;
	}
	iReturn = m_pPlan->CheckStrToNum(m_V_CMP_LOGIC_IN.GetBuffer(), 1, mmax, mmin, 1, 1);
	if (iReturn) {
		if (iReturn == 1) MessageBox(_T("Giá trị thiết lập điện áp ngưỡng so sánh không hợp lệ\n\rPhải là số"), _T("Thông báo"));
		if (iReturn == 2) {
			mmess.Format(_T("Giá trị thiết lập điện áp ngưỡng so sánh không hợp lệ:\n\rPhải nằm trong khoảng [%0.0f, %0.0f]"), mmin, mmax);
			MessageBox(mmess, _T("Thông báo"));
		}
		if (iReturn == 3) {
			mmess.Format(_T("Giá trị thiết lập điện áp ngưỡng so sánh không hợp lệ:\n\rPhải là số >= %0.0f"), mmin);
			MessageBox(mmess, _T("Thông báo"));
		}
		return iReturn;
	}
	//if (m_Setmode == 2) 
	{
		mmax = 80; mmin = 3;
		//if (m_Chk_HV_OUT1.GetCheck())     // TUAN COMENT
			iReturn = m_pPlan->CheckStrToNum(m_HV_OUT1.GetBuffer(), 1, mmax, mmin, 1, 1);
		if (!iReturn)
		//	if (m_Chk_HV_OUT2.GetCheck())    // TUAN COMENT
				iReturn = m_pPlan->CheckStrToNum(m_HV_OUT2.GetBuffer(), 1, mmax, mmin, 1, 1);
		if (iReturn) {
			if (iReturn == 1) MessageBox(_T("Giá trị thiết lập điện áp HV_OUT không hợp lệ\n\rPhải là số"), _T("Thông báo"));
			if (iReturn == 2) {
				mmess.Format(_T("Giá trị thiết lập điện áp HV_OUT không hợp lệ:\n\rPhải nằm trong khoảng [%0.0f, %0.0f]"), mmin, mmax);
				MessageBox(mmess, _T("Thông báo"));
			}
			if (iReturn == 3) {
				mmess.Format(_T("Giá trị thiết lập điện áp HV_OUT không hợp lệ:\n\rPhải là số >= %0.0f"), mmin);
				MessageBox(mmess, _T("Thông báo"));
			}
			return iReturn;
		}

		mmax = 300; mmin = 3;
		// if (m_Chk_HV_IN1.GetCheck())   // TUAN COMENT
			iReturn = m_pPlan->CheckStrToNum(m_HV_IN1.GetBuffer(), 1, mmax, mmin, 1, 1);
		if (!iReturn)
		// 	if (m_Chk_HV_IN2.GetCheck())   // TUAN COMENT
				iReturn = m_pPlan->CheckStrToNum(m_HV_IN2.GetBuffer(), 1, mmax, mmin, 1, 1);
		if (iReturn) {
			if (iReturn == 1) MessageBox(_T("Giá trị thiết lập điện áp HV_IN không hợp lệ\n\rPhải là số"), _T("Thông báo"));
			if (iReturn == 2) {
				mmess.Format(_T("Giá trị thiết lập điện áp HV_IN không hợp lệ:\n\rPhải nằm trong khoảng [%0.0f, %0.0f]"), mmin, mmax);
				MessageBox(mmess, _T("Thông báo"));
			}
			if (iReturn == 3) {
				mmess.Format(_T("Giá trị thiết lập điện áp HV_IN không hợp lệ:\n\rPhải là số >= %0.0f"), mmin);
				MessageBox(mmess, _T("Thông báo"));
			}
			return iReturn;
		}
	}

	//if (m_Setmode == 1) 
	{
		mmax = 300; mmin = 0;
		// if (m_Chk_ADC1.GetCheck())     // TUAN COMENT
			iReturn = m_pPlan->CheckStrToNum(m_ADC1.GetBuffer(), 1, mmax, mmin, 1, 1);
		if (!iReturn)
		// if (m_Chk_ADC2.GetCheck())    // TUAN COMENT
				iReturn = m_pPlan->CheckStrToNum(m_ADC2.GetBuffer(), 1, mmax, mmin, 1, 1);
		if (iReturn) {
			if (iReturn == 1) MessageBox(_T("Giá trị thiết lập kênh vào Highvotage không hợp lệ\n\rPhải là số"), _T("Thông báo"));
			//if (iReturn == 2) {
			//	mmess.Format(_T("Giá trị thiết lập kênh ADC không hợp lệ:\n\rPhải nằm trong khoảng [%0.0f, %0.0f]"), mmin, mmax);
			//	MessageBox(mmess, _T("Thông báo"));
			//}
			//if (iReturn == 3) {
			//	mmess.Format(_T("Giá trị thiết lập kênh ADC không hợp lệ:\n\rPhải là số >= %0.0f"), mmin);
			//	MessageBox(mmess, _T("Thông báo"));
			//}
			return iReturn;
		}
	}
	EXTCHANELINFO_DEF* m_pExtChanel_Set;
	m_pExtChanel_Set = &(m_pPlan->mTestCase.ExtChanel_Set);

	m_pExtChanel_Set->LogicInComp.name = m_V_CMP_LOGIC_IN_name;
	m_pExtChanel_Set->LogicOutHi.name = m_V_Hi_LOGIC_OUT_name;
	m_pExtChanel_Set->EXT_io1.name = m_IOEXT_1_name;
	m_pExtChanel_Set->EXT_io2.name = m_IOEXT_2_name;

	m_pExtChanel_Set->SetMode = m_Setmode;

	m_pExtChanel_Set->DAC_out1.name = m_DAC1_name;
	m_pExtChanel_Set->DAC_out2.name = m_DAC2_name;
	m_pExtChanel_Set->ADC_in1.name = m_ADC1_name;
	m_pExtChanel_Set->ADC_in2.name = m_ADC2_name;

	m_pExtChanel_Set->HV_out1.name = m_HV_OUT1_name;
	m_pExtChanel_Set->HV_out2.name = m_HV_OUT2_name;
	m_pExtChanel_Set->HV_in1.name = m_HV_IN1_name;
	m_pExtChanel_Set->HV_in2.name = m_HV_IN2_name;


	swscanf_s(m_V_Hi_LOGIC_OUT.GetBuffer(), _T("%f"), &m_pExtChanel_Set->LogicOutHi.value);
	swscanf_s(m_V_CMP_LOGIC_IN.GetBuffer(), _T("%f"), &m_pExtChanel_Set->LogicInComp.value);
	m_pExtChanel_Set->EXT_io1.text = m_IOEXT_1;
	m_pExtChanel_Set->EXT_io2.text = m_IOEXT_2;

	swscanf_s(m_HV_OUT1.GetBuffer(), _T("%f"), &m_pExtChanel_Set->HV_out1.value);
	swscanf_s(m_HV_OUT2.GetBuffer(), _T("%f"), &m_pExtChanel_Set->HV_out2.value);
	swscanf_s(m_HV_IN1.GetBuffer(), _T("%f"), &m_pExtChanel_Set->HV_in1.value);
	swscanf_s(m_HV_IN2.GetBuffer(), _T("%f"), &m_pExtChanel_Set->HV_in2.value);

	swscanf_s(m_DAC1.GetBuffer(), _T("%f"), &m_pExtChanel_Set->DAC_out1.value);
	swscanf_s(m_DAC2.GetBuffer(), _T("%f"), &m_pExtChanel_Set->DAC_out2.value);

	
	//swscanf_s(m_ADC1.GetBuffer(), _T("%f"), &m_pExtChanel_Set->ADC_in1.value);
	//swscanf_s(m_ADC2.GetBuffer(), _T("%f"), &m_pExtChanel_Set->ADC_in2.value);
	int nSelCur;
	nSelCur = m_Value_ADC1_Cb.GetCurSel();
	if (nSelCur == 0) m_pExtChanel_Set->ADC_in1.value = 1;
	else if (nSelCur == 1) m_pExtChanel_Set->ADC_in1.value = 10;
	else if (nSelCur == 2) m_pExtChanel_Set->ADC_in1.value = 100;
	else if (nSelCur == 3) m_pExtChanel_Set->ADC_in1.value = 1000;
	nSelCur = m_Value_ADC2_Cb.GetCurSel();
	if (nSelCur == 0) m_pExtChanel_Set->ADC_in2.value = 1;
	else if (nSelCur == 1) m_pExtChanel_Set->ADC_in2.value = 10;
	else if (nSelCur == 2) m_pExtChanel_Set->ADC_in2.value = 100;
	else if (nSelCur == 3) m_pExtChanel_Set->ADC_in2.value = 1000;
	//---------------------------------

	m_pExtChanel_Set->EXT_io1.used = m_Chk_IOEXT_1.GetCheck();
	m_pExtChanel_Set->EXT_io2.used = m_Chk_IOEXT_2.GetCheck();

	m_pExtChanel_Set->DAC_out1.used = m_Chk_DAC1.GetCheck();   // Anh  Đức nhầm ADC và DAC. Tuấn sửa lại: 24/11/2023
	m_pExtChanel_Set->DAC_out2.used = m_Chk_DAC2.GetCheck();
	m_pExtChanel_Set->ADC_in1.used = m_Chk_ADC1.GetCheck();
	m_pExtChanel_Set->ADC_in2.used = m_Chk_ADC2.GetCheck();

	m_pExtChanel_Set->HV_out1.used = m_Chk_HV_OUT1.GetCheck();
	m_pExtChanel_Set->HV_out2.used = m_Chk_HV_OUT2.GetCheck();
	m_pExtChanel_Set->HV_in1.used = m_Chk_HV_IN1.GetCheck();
	m_pExtChanel_Set->HV_in2.used = m_Chk_HV_IN2.GetCheck();

	//---------------------------------
	CString strTmp;

	m_pExtChanel_Set->EXT_io1.IN_OUT = m_IOEXT_1_Cb.GetCurSel();
	m_pExtChanel_Set->EXT_io2.IN_OUT = m_IOEXT_2_Cb.GetCurSel();

	//Xem lai

	m_DAC1_Cb.GetLBText(m_DAC1_Cb.GetCurSel(), strTmp);
	m_pExtChanel_Set->DAC_out1.nChanel = ChanelToNum(strTmp);
	m_DAC2_Cb.GetLBText(m_DAC2_Cb.GetCurSel(), strTmp);
	m_pExtChanel_Set->DAC_out2.nChanel = ChanelToNum(strTmp);
	m_ADC1_Cb.GetLBText(m_ADC1_Cb.GetCurSel(), strTmp);
	m_pExtChanel_Set->ADC_in1.nChanel = ChanelToNum(strTmp);
	m_ADC2_Cb.GetLBText(m_ADC2_Cb.GetCurSel(), strTmp);
	m_pExtChanel_Set->ADC_in2.nChanel = ChanelToNum(strTmp);

	//m_HV_IN1_Cb.GetLBText(m_HV_IN1_Cb.GetCurSel(), strTmp);
	//m_pExtChanel_Set->HV_in1.nChanel = ChanelToNum(strTmp);
	m_pExtChanel_Set->HV_in1.nChanel = 83;
	//m_HV_IN2_Cb.GetLBText(m_HV_IN2_Cb.GetCurSel(), strTmp);
	//m_pExtChanel_Set->HV_in2.nChanel = ChanelToNum(strTmp);
	m_pExtChanel_Set->HV_in2.nChanel = 84;
	return 0;
}

void DlgPowerSettingParam::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}

//
//void DlgPowerSettingParam::OnBnClickedBtnEdit()
//{
//	// TODO: Add your control notification handler code here
//	UpdateStatus(0);
//	// Nhập các số liệu
//}


void DlgPowerSettingParam::OnBnClickedBttnSave()
{
	// TODO: Add your control notification handler code here
	if (UpdateDataGUIToVar()) return;
	
	if (m_pPlan->Save_EXTChanel_TestCase(m_pIniReader, 0) == 1) {
		MessageBox(_T("Ghi dữ liệu thành công"), _T("Thông báo"));
	}
	else MessageBox(_T("Quá trình ghi dữ liệu bị lỗi"), _T("Thông báo"));
	
}

//void DlgPowerSettingParam::OnBnClickedBtnGetinfo()
//{
//	// TODO: Add your control notification handler code here
//	//UpdateDataToGUI();
//	//UpdateStatus(0);
//
//}


void DlgPowerSettingParam::OnCbnSelchangeComboHvIn1()
{
	// TODO: Add your control notification handler code here
	CString strTmp, str;
	int iChanel;
	UpdateData(true);
	ChanelSelArr2[nSelHV1] = 0;
	m_HV_IN1_Cb.GetLBText(m_HV_IN1_Cb.GetCurSel(), strTmp);
	iChanel = ChanelToNum(strTmp);
	ChanelSelArr2[iChanel] = 6;
	nSelHV1 = iChanel;
	//---------------------------------
	Init_CB_M2(6);
	UpdateData(false);
}


void DlgPowerSettingParam::OnCbnSelchangeComboHvIn2()
{
	// TODO: Add your control notification handler code here
	CString strTmp, str;
	int iChanel;
	UpdateData(true);
	ChanelSelArr2[nSelHV2] = 0;
	m_HV_IN2_Cb.GetLBText(m_HV_IN2_Cb.GetCurSel(), strTmp);
	iChanel = ChanelToNum(strTmp);
	ChanelSelArr2[iChanel] = 7;
	nSelHV2 = iChanel;
	//---------------------------------
	Init_CB_M2(7);
	UpdateData(false);
}


void DlgPowerSettingParam::OnCbnSelchangeComboDac1()
{
	// TODO: Add your control notification handler code here
	CString strTmp, str;
	int iChanel;
	UpdateData(true);
	ChanelSelArr1[nSelDAC1] = 0;
	m_DAC1_Cb.GetLBText(m_DAC1_Cb.GetCurSel(), strTmp);
	iChanel = ChanelToNum(strTmp);
	ChanelSelArr1[iChanel] = 2;
	nSelDAC1 = iChanel;
	//---------------------------------
	Init_CB_M1(2);
	UpdateData(false);
}


void DlgPowerSettingParam::OnCbnSelchangeComboDac2()
{
	// TODO: Add your control notification handler code here
	CString strTmp, str;
	int iChanel;
	UpdateData(true);
	ChanelSelArr1[nSelDAC2] = 0;
	m_DAC2_Cb.GetLBText(m_DAC2_Cb.GetCurSel(), strTmp);
	iChanel = ChanelToNum(strTmp);
	ChanelSelArr1[iChanel] = 3;
	nSelDAC2 = iChanel;
	//---------------------------------
	Init_CB_M1(3);
	UpdateData(false);
}

void DlgPowerSettingParam::OnCbnSelchangeComboValueADC1()
{
	// TODO: Add your control notification handler code here
}


void DlgPowerSettingParam::OnCbnSelchangeComboValueADC2()
{
	// TODO: Add your control notification handler code here
}

void DlgPowerSettingParam::OnCbnSelchangeComboAdc1()
{
	CString strTmp, str;
	int iChanel;
	UpdateData(true);

	if (nSelADC1 <= m_numChanel)	ChanelSelArr1[nSelADC1] = 0;
	else ChanelSelArr1[m_numChanel + nSelADC1 - 90] = 0;

	m_ADC1_Cb.GetLBText(m_ADC1_Cb.GetCurSel(), strTmp);
	iChanel = ChanelToNum(strTmp);
	
	if (iChanel <= m_numChanel)	ChanelSelArr1[iChanel] = 4;
	else ChanelSelArr1[m_numChanel + iChanel - 90] = 4;

	nSelADC1 = iChanel;
	//---------------------------------
	Init_CB_M1(4);
	UpdateData(false);
}


void DlgPowerSettingParam::OnCbnSelchangeComboAdc2()
{
	// TODO: Add your control notification handler code here
	CString strTmp, str;
	int iChanel;
	UpdateData(true);
	if (nSelADC2 <= m_numChanel)	ChanelSelArr1[nSelADC2] = 0;
	else ChanelSelArr1[m_numChanel + nSelADC2 - 90] = 0;

	m_ADC2_Cb.GetLBText(m_ADC2_Cb.GetCurSel(), strTmp);
	iChanel = ChanelToNum(strTmp);

	if (iChanel <= m_numChanel)	ChanelSelArr1[iChanel] = 5;
	else ChanelSelArr1[m_numChanel + iChanel - 90] = 5;
	nSelADC2 = iChanel;
	//---------------------------------
	Init_CB_M1(5);
	UpdateData(false);
}


//void DlgPowerSettingParam::OnBnClickedRadio1()
//{
//	// TODO: Add your control notification handler code here
//	m_Setmode = 1;
//
//}


//void DlgPowerSettingParam::OnBnClickedRadio2()
//{
//	// TODO: Add your control notification handler code here
//	m_Setmode = 2;
//}


void DlgPowerSettingParam::OnEnChangeEditTitle()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}



