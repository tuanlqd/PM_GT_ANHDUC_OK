// DlgPowerSetting.cpp : implementation file
//

#include <stdio.h>
#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgPowerSetting.h"
#include "mta_io_client.hpp"



// DlgPowerSetting dialog

IMPLEMENT_DYNAMIC(DlgPowerSetting, CDialogEx)

DlgPowerSetting::DlgPowerSetting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_POWER_SETTING, pParent)
	//, m_UsetP1(0)
	, m_UsetP2(_T(""))
	, m_UsetP6(_T(""))
	, m_UsetP5(_T(""))
	, m_UsetP4(_T(""))
	, m_UsetP3(_T(""))
	, m_UsetP7(_T(""))
	, m_UsetP8(_T(""))
	, m_UgetP1(_T(""))
	, m_UgetP2(_T(""))
	, m_UgetP3(_T(""))
	, m_UgetP4(_T(""))
	, m_UgetP5(_T(""))
	, m_UgetP6(_T(""))
	, m_UgetP7(_T(""))
	, m_UgetP8(_T(""))
	, m_ImaxSetP1(_T(""))
	, m_Iget_P1(_T(""))
	, m_Iget_P2(_T(""))
	, m_Iget_P3(_T(""))
	, m_Iget_P4(_T(""))
	, m_Iget_P5(_T(""))
	, m_Iget_P6(_T(""))
	, m_Iget_P7(_T(""))
	, m_Iget_P8(_T(""))
	, m_ImaxSetP2(_T(""))
	, m_ImaxSetP3(_T(""))
	, m_ImaxSetP4(_T(""))
	, m_ImaxSetP5(_T(""))
	, m_ImaxSetP6(_T(""))
	, m_ImaxSetP7(_T(""))
	, m_ImaxSetP8(_T(""))
{

}

DlgPowerSetting::~DlgPowerSetting()
{
}

void DlgPowerSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_P1_ON_OFF, mBtnP1_OnOFF);
	DDX_Control(pDX, IDC_BTN_P2_ON_OFF, mBtnP2_OnOFF);
	DDX_Control(pDX, IDC_BTN_P3_ON_OFF, mBtnP3_OnOFF);
	DDX_Control(pDX, IDC_BTN_P4_ON_OFF, mBtnP4_OnOFF);
	DDX_Control(pDX, IDC_BTN_P5_ON_OFF, mBtnP5_OnOFF);
	DDX_Control(pDX, IDC_BTN_P6_ON_OFF, mBtnP6_OnOFF);
	DDX_Control(pDX, IDC_BTN_P7_ON_OFF, mBtnP7_OnOFF);
	DDX_Control(pDX, IDC_BTN_P8_ON_OFF, mBtnP8_OnOFF);

	DDX_Text(pDX, IDC_EDIT_USET_P1, m_UsetP1);
	DDX_Text(pDX, IDC_EDIT_USET_P2, m_UsetP2);
	DDX_Text(pDX, IDC_EDIT_USET_P3, m_UsetP3);
	DDX_Text(pDX, IDC_EDIT_USET_P4, m_UsetP4);
	DDX_Text(pDX, IDC_EDIT_USET_P5, m_UsetP5);
	DDX_Text(pDX, IDC_EDIT_USET_P6, m_UsetP6);
	DDX_Text(pDX, IDC_EDIT_USET_P7, m_UsetP7);
	DDX_Text(pDX, IDC_EDIT_USET_P8, m_UsetP8);

	DDX_Text(pDX, IDC_EDIT_UGET1, m_UgetP1);
	DDX_Text(pDX, IDC_EDIT_UGET2, m_UgetP2);
	DDX_Text(pDX, IDC_EDIT_UGET3, m_UgetP3);
	DDX_Text(pDX, IDC_EDIT_UGET4, m_UgetP4);
	DDX_Text(pDX, IDC_EDIT_UGET5, m_UgetP5);
	DDX_Text(pDX, IDC_EDIT_UGET6, m_UgetP6);
	DDX_Text(pDX, IDC_EDIT_UGET7, m_UgetP7);
	DDX_Text(pDX, IDC_EDIT_UGET8, m_UgetP8);

	DDX_Text(pDX, IDC_EDIT_IGET1, m_Iget_P1);
	DDX_Text(pDX, IDC_EDIT_IGET2, m_Iget_P2);
	DDX_Text(pDX, IDC_EDIT_IGET3, m_Iget_P3);
	DDX_Text(pDX, IDC_EDIT_IGET4, m_Iget_P4);
	DDX_Text(pDX, IDC_EDIT_IGET5, m_Iget_P5);
	DDX_Text(pDX, IDC_EDIT_IGET6, m_Iget_P6);
	DDX_Text(pDX, IDC_EDIT_IGET7, m_Iget_P7);
	DDX_Text(pDX, IDC_EDIT_IGET8, m_Iget_P8);

	DDX_Text(pDX, IDC_EDIT_IMAXSET1, m_ImaxSetP1);
	DDX_Text(pDX, IDC_EDIT_IMAXSET2, m_ImaxSetP2);
	DDX_Text(pDX, IDC_EDIT_IMAXSET2, m_ImaxSetP2);
	DDX_Text(pDX, IDC_EDIT_IMAXSET3, m_ImaxSetP3);
	DDX_Text(pDX, IDC_EDIT_IMAXSET4, m_ImaxSetP4);
	DDX_Text(pDX, IDC_EDIT_IMAXSET5, m_ImaxSetP5);
	DDX_Text(pDX, IDC_EDIT_IMAXSET6, m_ImaxSetP6);
	DDX_Text(pDX, IDC_EDIT_IMAXSET7, m_ImaxSetP7);
	DDX_Text(pDX, IDC_EDIT_IMAXSET8, m_ImaxSetP8);
	//DDX_Control(pDX, IDC_BTN_UGET1, m_BTN_UGET1);
	//DDX_Control(pDX, IDC_BTN_UGET2, m_BTN_UGET2);
	//DDX_Control(pDX, IDC_BTN_UGET3, m_BTN_UGET3);
	//DDX_Control(pDX, IDC_BTN_UGET4, m_BTN_UGET4);
	//DDX_Control(pDX, IDC_BTN_UGET5, m_BTN_UGET5);
	//DDX_Control(pDX, IDC_BTN_UGET6, m_BTN_UGET6);
	//DDX_Control(pDX, IDC_BTN_UGET7, m_BTN_UGET7);
	//DDX_Control(pDX, IDC_BTN_UGET8, m_BTN_UGET8);
	//DDX_Control(pDX, IDC_BTN_IGET1, m_BTN_IGET1);
	//DDX_Control(pDX, IDC_BTN_IGET2, m_BTN_IGET2);
	//DDX_Control(pDX, IDC_BTN_IGET3, m_BTN_IGET3);
	//DDX_Control(pDX, IDC_BTN_IGET4, m_BTN_IGET4);
	//DDX_Control(pDX, IDC_BTN_IGET5, m_BTN_IGET5);
	//DDX_Control(pDX, IDC_BTN_IGET6, m_BTN_IGET6);
	//DDX_Control(pDX, IDC_BTN_IGET7, m_BTN_IGET7);
	//DDX_Control(pDX, IDC_BTN_IGET8, m_BTN_IGET8);
	DDX_Control(pDX, IDC_BMP_UGET1, m_BMP_UGET1);
	DDX_Control(pDX, IDC_BMP_UGET2, m_BMP_UGET2);
	DDX_Control(pDX, IDC_BMP_UGET3, m_BMP_UGET3);
	DDX_Control(pDX, IDC_BMP_UGET4, m_BMP_UGET4);
	DDX_Control(pDX, IDC_BMP_UGET5, m_BMP_UGET5);
	DDX_Control(pDX, IDC_BMP_UGET6, m_BMP_UGET6);
	DDX_Control(pDX, IDC_BMP_UGET7, m_BMP_UGET7);
	DDX_Control(pDX, IDC_BMP_UGET8, m_BMP_UGET8);
	DDX_Control(pDX, IDC_BMP_IGET1, m_BMP_IGET1);
	DDX_Control(pDX, IDC_BMP_IGET2, m_BMP_IGET2);
	DDX_Control(pDX, IDC_BMP_IGET3, m_BMP_IGET3);
	DDX_Control(pDX, IDC_BMP_IGET4, m_BMP_IGET4);
	DDX_Control(pDX, IDC_BMP_IGET5, m_BMP_IGET5);
	DDX_Control(pDX, IDC_BMP_IGET6, m_BMP_IGET6);
	DDX_Control(pDX, IDC_BMP_IGET7, m_BMP_IGET7);
	DDX_Control(pDX, IDC_BMP_IGET8, m_BMP_IGET8);

	DDX_Control(pDX, IDC_BMP_UGET1, m_BMP_UGET1);
}


BEGIN_MESSAGE_MAP(DlgPowerSetting, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_P1_ON_OFF, &DlgPowerSetting::OnBnClickedBtnP1OnOff)
	ON_BN_CLICKED(IDC_BTN_P2_ON_OFF, &DlgPowerSetting::OnBnClickedBtnP2OnOff)
	ON_BN_CLICKED(IDC_BTN_P3_ON_OFF, &DlgPowerSetting::OnBnClickedBtnP3OnOff)
	ON_BN_CLICKED(IDC_BTN_P4_ON_OFF, &DlgPowerSetting::OnBnClickedBtnP4OnOff)
	ON_BN_CLICKED(IDC_BTN_P5_ON_OFF, &DlgPowerSetting::OnBnClickedBtnP5OnOff)
	ON_BN_CLICKED(IDC_BTN_P6_ON_OFF, &DlgPowerSetting::OnBnClickedBtnP6OnOff)
	ON_BN_CLICKED(IDC_BTN_P7_ON_OFF, &DlgPowerSetting::OnBnClickedBtnP7OnOff)
	ON_BN_CLICKED(IDC_BTN_P8_ON_OFF, &DlgPowerSetting::OnBnClickedBtnP8OnOff)
	ON_BN_CLICKED(IDC_BUTTON_SET, &DlgPowerSetting::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_GET, &DlgPowerSetting::OnBnClickedButtonGet)
	//ON_BN_CLICKED(IDC_BUTTON_ENABLE_BOARD, &DlgPowerSetting::OnBnClickedButtonEnableBoard)
	ON_BN_CLICKED(IDOK, &DlgPowerSetting::OnBnClickedOk)
	//ON_BN_CLICKED(IDC_BUTTON_SET_PATH, &DlgPowerSetting::OnBnClickedButtonSetPath)
	//ON_BN_CLICKED(IDC_BUTTON_RESET_PATH, &DlgPowerSetting::OnBnClickedButtonResetPath)
	ON_BN_CLICKED(IDC_SAVE, &DlgPowerSetting::OnBnClickedSave)
	ON_BN_CLICKED(ID_READ_PWR_M3_VALUE, &DlgPowerSetting::OnBnClickedReadPwrM3Value)
END_MESSAGE_MAP()


// DlgPowerSetting message handlers
BOOL DlgPowerSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitBtnOnOff();
	UpdateDataToGUI();
	UpdateData(false);

	if (m_User) {
		CWnd* pwnd;
		//CEdit* pEditCtrl;
		//CFont* cfont = new CFont()
		//
		//// .............  tuan code them. chinh size of text ........
		//pEditCtrl = (CEdit*)GetDlgItem(IDC_STATIC);
		//pEditCtrl->SetFont(new CFont("Segoe UI", 0, 14));
		////pEditCtrl->SetWindowTextW(s_MainTitle);
		////..........................................................
		pwnd = GetDlgItem(IDC_EDIT_USET_P1);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_USET_P2);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_USET_P3);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_USET_P4);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_USET_P5);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_USET_P6);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_USET_P7);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_USET_P8);
		if (pwnd) pwnd->EnableWindow(false);

		pwnd = GetDlgItem(IDC_EDIT_IMAXSET1);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_IMAXSET2);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_IMAXSET3);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_IMAXSET4);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_IMAXSET5);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_IMAXSET6);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_IMAXSET7);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_EDIT_IMAXSET8);
		if (pwnd) pwnd->EnableWindow(false);
		//------------------
		pwnd = GetDlgItem(IDC_BUTTON_SET);
		if (pwnd) pwnd->EnableWindow(true);
		
		pwnd = GetDlgItem(ID_READ_PWR_M3_VALUE);   // TUAN THEM NUT NAY
		if (pwnd) pwnd->EnableWindow(true);

		pwnd = GetDlgItem(IDC_BUTTON_GET);
		if (pwnd) pwnd->EnableWindow(false);
		//pwnd = GetDlgItem(IDC_BUTTON_ENABLE_BOARD);
		//if (pwnd) pwnd->EnableWindow(false);
		//pwnd = GetDlgItem(IDC_BUTTON_SET_PATH);
		//if (pwnd) pwnd->EnableWindow(false);
		//pwnd = GetDlgItem(IDC_BUTTON_RESET_PATH);
		//if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_SAVE);
		if (pwnd) pwnd->EnableWindow(false);
		//----------------------------
		pwnd = GetDlgItem(IDC_BTN_P1_ON_OFF);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_BTN_P2_ON_OFF);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_BTN_P3_ON_OFF);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_BTN_P4_ON_OFF);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_BTN_P5_ON_OFF);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_BTN_P6_ON_OFF);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_BTN_P7_ON_OFF);
		if (pwnd) pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_BTN_P8_ON_OFF);
		if (pwnd) pwnd->EnableWindow(false);
	}
	if (GETDATABASE) {
		CWnd* pwnd = GetDlgItem(IDC_BUTTON_SET);
		if (pwnd)
			pwnd->EnableWindow(false);

		pwnd = GetDlgItem(ID_READ_PWR_M3_VALUE);
		if (pwnd)
			pwnd->EnableWindow(false);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void DlgPowerSetting::OnBnClickedBtnP1OnOff()
{
	// TODO: Add your control notification handler code here
	CBitmap cBmp;
	if (m_pPlan->mTestCase.mPowers.POWER[1].ON_OFF == 1) {
		m_pPlan->mTestCase.mPowers.POWER[1].ON_OFF = 0;
		cBmp.LoadBitmap(IDB_BITMAP_OFF);
	}
	else {
		m_pPlan->mTestCase.mPowers.POWER[1].ON_OFF = 1;
		cBmp.LoadBitmap(IDB_BITMAP_ON);
	}
	mBtnP1_OnOFF.SetBitmap(cBmp);
	cBmp.DeleteObject();
}


void DlgPowerSetting::OnBnClickedBtnP2OnOff()
{
	// TODO: Add your control notification handler code here
	CBitmap cBmp;
	if (m_pPlan->mTestCase.mPowers.POWER[2].ON_OFF == 1) {
		m_pPlan->mTestCase.mPowers.POWER[2].ON_OFF = 0;
		cBmp.LoadBitmap(IDB_BITMAP_OFF);
	}
	else {
		m_pPlan->mTestCase.mPowers.POWER[2].ON_OFF = 1;
		cBmp.LoadBitmap(IDB_BITMAP_ON);
	}
	mBtnP2_OnOFF.SetBitmap(cBmp);
	cBmp.DeleteObject();
}


void DlgPowerSetting::OnBnClickedBtnP3OnOff()
{
	// TODO: Add your control notification handler code here
	CBitmap cBmp;
	if (m_pPlan->mTestCase.mPowers.POWER[3].ON_OFF == 1) {
		m_pPlan->mTestCase.mPowers.POWER[3].ON_OFF = 0;
		cBmp.LoadBitmap(IDB_BITMAP_OFF);
	}
	else {
		m_pPlan->mTestCase.mPowers.POWER[3].ON_OFF = 1;
		cBmp.LoadBitmap(IDB_BITMAP_ON);
	}
	mBtnP3_OnOFF.SetBitmap(cBmp);
	cBmp.DeleteObject();
}


void DlgPowerSetting::OnBnClickedBtnP4OnOff()
{
	// TODO: Add your control notification handler code here
	CBitmap cBmp;
	if (m_pPlan->mTestCase.mPowers.POWER[4].ON_OFF == 1) {
		m_pPlan->mTestCase.mPowers.POWER[4].ON_OFF = 0;
		cBmp.LoadBitmap(IDB_BITMAP_OFF);
	}
	else {
		m_pPlan->mTestCase.mPowers.POWER[4].ON_OFF = 1;
		cBmp.LoadBitmap(IDB_BITMAP_ON);
	}
	mBtnP4_OnOFF.SetBitmap(cBmp);
	cBmp.DeleteObject();
}


void DlgPowerSetting::OnBnClickedBtnP5OnOff()
{
	// TODO: Add your control notification handler code here
	CBitmap cBmp;
	if (m_pPlan->mTestCase.mPowers.POWER[5].ON_OFF == 1) {
		m_pPlan->mTestCase.mPowers.POWER[5].ON_OFF = 0;
		cBmp.LoadBitmap(IDB_BITMAP_OFF);
	}
	else {
		m_pPlan->mTestCase.mPowers.POWER[5].ON_OFF = 1;
		cBmp.LoadBitmap(IDB_BITMAP_ON);
	}
	mBtnP5_OnOFF.SetBitmap(cBmp);
	cBmp.DeleteObject();
}


void DlgPowerSetting::OnBnClickedBtnP6OnOff()
{
	// TODO: Add your control notification handler code here
	CBitmap cBmp;
	if (m_pPlan->mTestCase.mPowers.POWER[6].ON_OFF == 1) {
		m_pPlan->mTestCase.mPowers.POWER[6].ON_OFF = 0;
		cBmp.LoadBitmap(IDB_BITMAP_OFF);
	}
	else {
		m_pPlan->mTestCase.mPowers.POWER[6].ON_OFF = 1;
		cBmp.LoadBitmap(IDB_BITMAP_ON);
	}
	mBtnP6_OnOFF.SetBitmap(cBmp);
	cBmp.DeleteObject();
}


void DlgPowerSetting::OnBnClickedBtnP7OnOff()
{
	// TODO: Add your control notification handler code here
	CBitmap cBmp;
	if (m_pPlan->mTestCase.mPowers.POWER[7].ON_OFF == 1) {
		m_pPlan->mTestCase.mPowers.POWER[7].ON_OFF = 0;
		cBmp.LoadBitmap(IDB_BITMAP_OFF);
	}
	else {
		m_pPlan->mTestCase.mPowers.POWER[7].ON_OFF = 1;
		cBmp.LoadBitmap(IDB_BITMAP_ON);
	}
	mBtnP7_OnOFF.SetBitmap(cBmp);
	cBmp.DeleteObject();
}


void DlgPowerSetting::OnBnClickedBtnP8OnOff()
{
	// TODO: Add your control notification handler code here
	CBitmap cBmp;
	if (m_pPlan->mTestCase.mPowers.POWER[8].ON_OFF == 1) {
		m_pPlan->mTestCase.mPowers.POWER[8].ON_OFF = 0;
		cBmp.LoadBitmap(IDB_BITMAP_OFF);
	}
	else {
		m_pPlan->mTestCase.mPowers.POWER[8].ON_OFF = 1;
		cBmp.LoadBitmap(IDB_BITMAP_ON);
	}
	mBtnP8_OnOFF.SetBitmap(cBmp);
	cBmp.DeleteObject();
}

void DlgPowerSetting::InitBtnOnOff() {

	CBitmap cBmpON, cBmpOFF;
	cBmpON.LoadBitmap(IDB_BITMAP_ON);
	cBmpOFF.LoadBitmap(IDB_BITMAP_OFF);

	if (m_pPlan->mTestCase.mPowers.POWER[1].ON_OFF == 1) mBtnP1_OnOFF.SetBitmap(cBmpON);
	else mBtnP1_OnOFF.SetBitmap(cBmpOFF);

	if (m_pPlan->mTestCase.mPowers.POWER[2].ON_OFF == 1) mBtnP2_OnOFF.SetBitmap(cBmpON);
	else mBtnP2_OnOFF.SetBitmap(cBmpOFF);

	if (m_pPlan->mTestCase.mPowers.POWER[3].ON_OFF == 1) mBtnP3_OnOFF.SetBitmap(cBmpON);
	else mBtnP3_OnOFF.SetBitmap(cBmpOFF);

	if (m_pPlan->mTestCase.mPowers.POWER[4].ON_OFF == 1) mBtnP4_OnOFF.SetBitmap(cBmpON);
	else mBtnP4_OnOFF.SetBitmap(cBmpOFF);

	if (m_pPlan->mTestCase.mPowers.POWER[5].ON_OFF == 1) mBtnP5_OnOFF.SetBitmap(cBmpON);
	else mBtnP5_OnOFF.SetBitmap(cBmpOFF);

	if (m_pPlan->mTestCase.mPowers.POWER[6].ON_OFF == 1) mBtnP6_OnOFF.SetBitmap(cBmpON);
	else mBtnP6_OnOFF.SetBitmap(cBmpOFF);

	if (m_pPlan->mTestCase.mPowers.POWER[7].ON_OFF == 1) mBtnP7_OnOFF.SetBitmap(cBmpON);
	else mBtnP7_OnOFF.SetBitmap(cBmpOFF);

	if (m_pPlan->mTestCase.mPowers.POWER[8].ON_OFF == 1) mBtnP8_OnOFF.SetBitmap(cBmpON);
	else mBtnP8_OnOFF.SetBitmap(cBmpOFF); 

	cBmpON.DeleteObject();
	cBmpOFF.DeleteObject();
}
void DlgPowerSetting::UpdateStatus() {
	POWER_STRUCT* p_Power;
	CBitmap cBmpOK, cBmpERR, * cBmpTemp, * cBmpTempI;
	cBmpOK.LoadBitmap(IDB_BITMAP_ON);
	cBmpERR.LoadBitmap(IDB_BITMAP_OFF);
	p_Power = m_pPlan->mTestCase.mPowers.POWER;

	float tmpThreshol = m_pPlan->mTestCase.mPowers.PowerVerifyThreshol;
	float MOT = 1.0;



	for (int i = 1; i <= 5; i++) {   // 5 nguon Duong

		p_Power[i].StatusI = 0;
		p_Power[i].StatusU = 0;

		if (!p_Power[i].ON_OFF)
		{
			p_Power[i].StatusU = 0;
			p_Power[i].StatusI = 0;
		}
	
		if (p_Power[i].UGet < 0)
		{
			p_Power[i].StatusU = 0;
			p_Power[i].StatusI = 0;
		}

		if (p_Power[i].IGet < 0)
		{
			p_Power[i].StatusU = 0;
			p_Power[i].StatusI = 0;
		}

		if (p_Power[i].Status && p_Power[i].ON_OFF) 
		{
			if ((p_Power[i].UGet < p_Power[i].USet * (MOT - tmpThreshol)) || (p_Power[i].UGet > p_Power[i].USet * (MOT + tmpThreshol))) 
				p_Power[i].StatusU = 0;
			else p_Power[i].StatusU = 1;

			if ((p_Power[i].IGet < 0) || (p_Power[i].IGet > p_Power[i].ImaxSet))
				p_Power[i].StatusI = 0;
			else p_Power[i].StatusI = 1;
		}
		else {
			p_Power[i].StatusU = 0;
			p_Power[i].StatusI = 0;
		}
	}
	for (int i = 6; i <= 8; i++) {     // 3 nguon Am
		if (!p_Power[i].ON_OFF)
		{
			p_Power[i].StatusU = 0;
			p_Power[i].StatusI = 0;
		}

		if (p_Power[i].UGet > 0)
		{
			p_Power[i].StatusU = 0;
			p_Power[i].StatusI = 0;
		}

		if (p_Power[i].IGet < 0)
		{
			p_Power[i].StatusU = 0;
			p_Power[i].StatusI = 0;
		}


		if (p_Power[i].Status && p_Power[i].ON_OFF)
		{
			if ((p_Power[i].UGet < p_Power[i].USet * (MOT + tmpThreshol)) || (p_Power[i].UGet > p_Power[i].USet * (MOT - tmpThreshol)))
				p_Power[i].StatusU = 0;
			else p_Power[i].StatusU = 1;

			if ((p_Power[i].IGet < 0) || (p_Power[i].IGet > p_Power[i].ImaxSet))
				p_Power[i].StatusI = 0;
			else p_Power[i].StatusI = 1;
		}
		else {
			p_Power[i].StatusU = 0;
			p_Power[i].StatusI = 0;
		}
	}

	for (int i = 1; i <= 8; i++) {
		if (p_Power[i].StatusU) cBmpTemp = &cBmpOK;
		else cBmpTemp = &cBmpERR;
		if (p_Power[i].StatusI) cBmpTempI = &cBmpOK;
		else cBmpTempI = &cBmpERR;

		switch (i)
		{
		case 1: {m_BMP_UGET1.SetBitmap(*cBmpTemp); m_BMP_IGET1.SetBitmap(*cBmpTempI); break;}
		case 2: {m_BMP_UGET2.SetBitmap(*cBmpTemp); m_BMP_IGET2.SetBitmap(*cBmpTempI); break;}
		case 3: {m_BMP_UGET3.SetBitmap(*cBmpTemp); m_BMP_IGET3.SetBitmap(*cBmpTempI); break;}
		case 4: {m_BMP_UGET4.SetBitmap(*cBmpTemp); m_BMP_IGET4.SetBitmap(*cBmpTempI); break;}
		case 5: {m_BMP_UGET5.SetBitmap(*cBmpTemp); m_BMP_IGET5.SetBitmap(*cBmpTempI); break;}
		case 6: {m_BMP_UGET6.SetBitmap(*cBmpTemp); m_BMP_IGET6.SetBitmap(*cBmpTempI); break;}
		case 7: {m_BMP_UGET7.SetBitmap(*cBmpTemp); m_BMP_IGET7.SetBitmap(*cBmpTempI); break;}
		case 8: {m_BMP_UGET8.SetBitmap(*cBmpTemp); m_BMP_IGET8.SetBitmap(*cBmpTempI); break;}
		default:break;
		}
	}
	//----------------------------
	cBmpOK.DeleteObject();
	cBmpERR.DeleteObject();
	//------------------------------------
	
	m_status = 1;
	for (int i = 1; i <= 8; i++) 
		if (p_Power[i].ON_OFF && !p_Power[i].Status) m_status = 0;
}

void DlgPowerSetting::UpdateDataToGUI() {
	//----------------------
	int i = 1;
	m_UsetP1.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].USet);
	m_ImaxSetP1.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].ImaxSet);
	m_UgetP1.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].UGet);
	m_Iget_P1.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].IGet);
	//--------------------
	i = 2;
	m_UsetP2.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].USet);
	m_ImaxSetP2.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].ImaxSet);
	m_UgetP2.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].UGet);
	m_Iget_P2.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].IGet);
	//--------------------
	i = 3;
	m_UsetP3.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].USet);
	m_ImaxSetP3.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].ImaxSet);
	m_UgetP3.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].UGet);
	m_Iget_P3.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].IGet);
	//--------------------
	i = 4;
	m_UsetP4.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].USet);
	m_ImaxSetP4.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].ImaxSet);
	m_UgetP4.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].UGet);
	m_Iget_P4.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].IGet);
	//--------------------	
	i = 5;
	m_UsetP5.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].USet);
	m_ImaxSetP5.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].ImaxSet);
	m_UgetP5.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].UGet);
	m_Iget_P5.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].IGet);
	//--------------------	
	i = 6;
	m_UsetP6.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].USet);
	m_ImaxSetP6.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].ImaxSet);
	m_UgetP6.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].UGet);
	m_Iget_P6.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].IGet);
	//--------------------
	i = 7;
	m_UsetP7.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].USet);
	m_ImaxSetP7.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].ImaxSet);
	m_UgetP7.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].UGet);
	m_Iget_P7.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].IGet);
	//--------------------
	i = 8;
	m_UsetP8.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].USet);
	m_ImaxSetP8.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].ImaxSet);
	m_UgetP8.Format(_T("%0.2f"), m_pPlan->mTestCase.mPowers.POWER[i].UGet);
	m_Iget_P8.Format(_T("%0.3f"), m_pPlan->mTestCase.mPowers.POWER[i].IGet);
	//--------------------

	if (m_pPlan->mTestCase.mPowers.POWER[1].Status == 0) { m_UgetP1 = _T("NA"); m_Iget_P1 = _T("NA"); }
	if (m_pPlan->mTestCase.mPowers.POWER[2].Status == 0) { m_UgetP2 = _T("NA"); m_Iget_P2 = _T("NA"); }
	if (m_pPlan->mTestCase.mPowers.POWER[3].Status == 0) { m_UgetP3 = _T("NA"); m_Iget_P3 = _T("NA"); }
	if (m_pPlan->mTestCase.mPowers.POWER[4].Status == 0) { m_UgetP4 = _T("NA"); m_Iget_P4 = _T("NA"); }
	if (m_pPlan->mTestCase.mPowers.POWER[5].Status == 0) { m_UgetP5 = _T("NA"); m_Iget_P5 = _T("NA"); }
	if (m_pPlan->mTestCase.mPowers.POWER[6].Status == 0) { m_UgetP6 = _T("NA"); m_Iget_P6 = _T("NA"); }
	if (m_pPlan->mTestCase.mPowers.POWER[7].Status == 0) { m_UgetP7 = _T("NA"); m_Iget_P7 = _T("NA"); }
	if (m_pPlan->mTestCase.mPowers.POWER[8].Status == 0) { m_UgetP8 = _T("NA"); m_Iget_P8 = _T("NA"); }

}

int DlgPowerSetting::UpdateDataGUIToVar() {
	UpdateData(TRUE);
	int iReturn = 0;
	float mmax, mmin;
	CString mmess;
	mmax = 27; mmin = 3.3;

	if(m_pPlan->mTestCase.mPowers.POWER[1].ON_OFF) 
		iReturn = m_pPlan->CheckStrToNum(m_UsetP1.GetBuffer(), 1, mmax, mmin, 1, 1);
	if(!iReturn) 
		if (m_pPlan->mTestCase.mPowers.POWER[2].ON_OFF)
			iReturn = m_pPlan->CheckStrToNum(m_UsetP2.GetBuffer(), 1, mmax, mmin, 1, 1);
	if (!iReturn) 
		if (m_pPlan->mTestCase.mPowers.POWER[3].ON_OFF)
			iReturn = m_pPlan->CheckStrToNum(m_UsetP3.GetBuffer(), 1, mmax, mmin, 1, 1);
	if (!iReturn) 
		if (m_pPlan->mTestCase.mPowers.POWER[4].ON_OFF)
			iReturn = m_pPlan->CheckStrToNum(m_UsetP4.GetBuffer(), 1, mmax, mmin, 1, 1);
	if (!iReturn) 
		if (m_pPlan->mTestCase.mPowers.POWER[5].ON_OFF)
			iReturn = m_pPlan->CheckStrToNum(m_UsetP5.GetBuffer(), 1, mmax, mmin, 1, 1);
	if (iReturn) {
		if(iReturn == 1) MessageBox(_T("Giá trị thiết lập điện áp không hợp lệ\n\rPhải là số"), _T("Thông báo"));
		if (iReturn == 2) {
			mmess.Format(_T("Giá trị thiết lập nguồn dương không hợp lệ:\n\rPhải nằm trong khoảng [%0.0f, %0.0f]"), mmin, mmax);
			MessageBox(mmess, _T("Thông báo"));
		}
		if (iReturn == 3) {
			mmess.Format(_T("Giá trị thiết lập nguồn dương không hợp lệ:\n\rPhải là số >= %f"), mmin);
			MessageBox(mmess, _T("Thông báo"));
		}
		return iReturn;
	}

	mmax = -3.3; mmin = -27;
	if (m_pPlan->mTestCase.mPowers.POWER[6].ON_OFF)
		iReturn = m_pPlan->CheckStrToNum(m_UsetP6.GetBuffer(), 1, mmax, mmin, 1, -1);
	if (!iReturn) 
		if (m_pPlan->mTestCase.mPowers.POWER[7].ON_OFF)
			iReturn = m_pPlan->CheckStrToNum(m_UsetP7.GetBuffer(), 1, mmax, mmin, 1, -1);
	if (!iReturn) 
		if (m_pPlan->mTestCase.mPowers.POWER[8].ON_OFF)
			iReturn = m_pPlan->CheckStrToNum(m_UsetP8.GetBuffer(), 1, mmax, mmin, 1, -1);
	if (iReturn) {
		if (iReturn == 1) MessageBox(_T("Giá trị thiết lập không hợp lệ\n\rPhải là số"), _T("Thông báo"));
		if (iReturn == 2) {
			mmess.Format(_T("Giá trị thiết lập nguồn âm không hợp lệ:\n\rPhải nằm trong khoảng [%0.0f, %0.0f]"), mmin, mmax);
			MessageBox(mmess, _T("Thông báo"));
		}
		if (iReturn == 3) {
			mmess.Format(_T("Giá trị thiết lập nguồn âm không hợp lệ : \n\rPhải là số <= %f"), mmax);
			MessageBox(mmess, _T("Thông báo"));
		}
		return iReturn;
	}
	mmax = 8; mmin = 0;
	if (m_pPlan->mTestCase.mPowers.POWER[1].ON_OFF)
		iReturn = m_pPlan->CheckStrToNum(m_ImaxSetP1.GetBuffer(), 1, mmax, mmin, 1, 1);
	if (!iReturn) 
		if (m_pPlan->mTestCase.mPowers.POWER[2].ON_OFF)
			iReturn = m_pPlan->CheckStrToNum(m_ImaxSetP2.GetBuffer(), 1, mmax, mmin, 1, 1);
	if (!iReturn) 
		if (m_pPlan->mTestCase.mPowers.POWER[3].ON_OFF)
			iReturn = m_pPlan->CheckStrToNum(m_ImaxSetP3.GetBuffer(), 1, mmax, mmin, 1, 1);
	if (!iReturn) 
		if (m_pPlan->mTestCase.mPowers.POWER[4].ON_OFF)
			iReturn = m_pPlan->CheckStrToNum(m_ImaxSetP4.GetBuffer(), 1, mmax, mmin, 1, 1);
	if (!iReturn) 
		if (m_pPlan->mTestCase.mPowers.POWER[5].ON_OFF)
			iReturn = m_pPlan->CheckStrToNum(m_ImaxSetP5.GetBuffer(), 1, mmax, mmin, 1, 1);
	if (!iReturn) 
		if (m_pPlan->mTestCase.mPowers.POWER[6].ON_OFF)
			iReturn = m_pPlan->CheckStrToNum(m_ImaxSetP6.GetBuffer(), 1, mmax, mmin, 1, 1);
	if (!iReturn) 
		if (m_pPlan->mTestCase.mPowers.POWER[7].ON_OFF)
			iReturn = m_pPlan->CheckStrToNum(m_ImaxSetP7.GetBuffer(), 1, mmax, mmin, 1, 1);
	if (!iReturn) 
		if (m_pPlan->mTestCase.mPowers.POWER[8].ON_OFF)
			iReturn = m_pPlan->CheckStrToNum(m_ImaxSetP8.GetBuffer(), 1, mmax, mmin, 1, 1);
	
	if (iReturn) {
		if (iReturn == 1) MessageBox(_T("Giá trị thiết lập dòng không hợp lệ\n\rPhải là số"), _T("Thông báo"));
		if (iReturn == 2) {
			mmess.Format(_T("Giá trị thiết lập dòng điện không hợp lệ:\n\rPhải nằm trong khoảng [%0.0f, %0.0f]"), mmin, mmax);
			MessageBox(mmess, _T("Thông báo"));
		}
		if (iReturn == 3) {
			mmess.Format(_T("Giá trị thiết lập dòng điện không hợp lệ : \n\rPhải là số <= %f"), mmax);
			MessageBox(mmess, _T("Thông báo"));
		}
		return iReturn;
	}
	//--------------------------
	swscanf_s(m_UsetP1.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[1].USet);
	swscanf_s(m_UsetP2.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[2].USet);
	swscanf_s(m_UsetP3.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[3].USet);
	swscanf_s(m_UsetP4.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[4].USet);
	swscanf_s(m_UsetP5.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[5].USet);
	swscanf_s(m_UsetP6.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[6].USet);
	swscanf_s(m_UsetP7.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[7].USet);
	swscanf_s(m_UsetP8.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[8].USet);

	swscanf_s(m_ImaxSetP1.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[1].ImaxSet);
	swscanf_s(m_ImaxSetP2.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[2].ImaxSet);
	swscanf_s(m_ImaxSetP3.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[3].ImaxSet);
	swscanf_s(m_ImaxSetP4.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[4].ImaxSet);
	swscanf_s(m_ImaxSetP5.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[5].ImaxSet);
	swscanf_s(m_ImaxSetP6.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[6].ImaxSet);
	swscanf_s(m_ImaxSetP7.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[7].ImaxSet);
	swscanf_s(m_ImaxSetP8.GetBuffer(), _T("%f"), &m_pPlan->mTestCase.mPowers.POWER[8].ImaxSet);
	return 0;
}

void DlgPowerSetting::OnBnClickedButtonSet()
{
	// TODO: Add your control notification handler code here
	char RecArr[256];
	int lenRecArr;

	UpdateData(true);
	if (UpdateDataGUIToVar()) return;

	// thiet lap nguong bao ve nguon
	m_status = m_pPlan->SetUp_I_Thres_8Power(m_pPlan->mTestCase.mPowers, RecArr, &lenRecArr);
	Sleep(500);

	// set up gia tri nguon tao ra
	m_status = m_pPlan->SetUp8Power(m_pPlan->mTestCase.mPowers, RecArr, &lenRecArr);
	//Sleep(3000);  // ms

	// chuyen phan do sang nut moi

	//// TUAN moi THEM:24_08_2023
	//// doc du lieu nguon len PC
	Sleep(1000); // ms
	//Sleep(600);  // ms
	//m_pPlan->ExtrackPackage_Get_8PWR_Info(ADDR_M3_0);
	//Sleep(300);  // ms
	//m_pPlan->ExtrackPackage_Get_8PWR_Info(ADDR_M3_0);   //doc them lan 2 cho dam bao hien thi dc gia tri doc ve
	//Sleep(300);  // ms
	//m_pPlan->ExtrackPackage_Get_8PWR_Info(ADDR_M3_1);
	//Sleep(300);  // ms
	//m_pPlan->ExtrackPackage_Get_8PWR_Info(ADDR_M3_1);

	//for (int i = 0; i <= 8; i++)
	//{
	//	m_pPlan->mTestCase.mPowers.POWER[i] = m_pPlan->Pwr_M3_0[i];  // lay cac thong tin khac. hai khoi giong nhau
	//	m_pPlan->mTestCase.mPowers.POWER[i].IGet = m_pPlan->Pwr_M3_0[i].IGet + m_pPlan->Pwr_M3_0[i].IGet;  // cap nhat dong cua ca hai khoi
	//}
	UpdateDataToGUI();
	InitBtnOnOff();
	UpdateData(false);
	//UpdateStatus();

	MessageBox(_T("Đã thiết lập điện áp nguồn xong! Hãy bấm 'Đọc giá trị nguồn' để cập nhật giá trị."), _T("Thông báo"));

}


void DlgPowerSetting::OnBnClickedButtonGet()
{
	// TODO: Add your control notification handler code here
	Sleep(100);  // ms
	m_pPlan->ExtrackPackage_Get_8PWR_Info(ADDR_M3_0);
	Sleep(500);  // ms
	m_pPlan->ExtrackPackage_Get_8PWR_Info(ADDR_M3_1);

	for (int i = 0; i <= 8; i++)
	{
		m_pPlan->mTestCase.mPowers.POWER[i] = m_pPlan->Pwr_M3_0[i];  // lay cac thong tin khac. hai khoi giong nhau
		m_pPlan->mTestCase.mPowers.POWER[i].IGet = m_pPlan->Pwr_M3_0[i].IGet + m_pPlan->Pwr_M3_0[i].IGet;  // cap nhat dong cua ca hai khoi
	}
	UpdateDataToGUI();
	InitBtnOnOff();
	UpdateData(false);
	UpdateStatus();

}

void DlgPowerSetting::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
}

//void DlgPowerSetting::OnBnClickedButtonEnableBoard()
//{
//	//// send m_pBuffSend
//	//// Kiem tra Nhan ve 
//	////      1. nRet >=8 ->OK 
//	////      2. m_pBuffRecv[8] = 0x00
//	//// 
//	//// Function kich hoat board
//	//// TODO: Add your control notification handler code here
//	//int m_lenBuffSend = 9;
//	//byte m_pBuffSend[]		= { 0x00,0x30,0x09,0x0D,0x00, 0x01,0x00,0x01,0x06 }; // send
//	//byte m_pBuffRecv_Ret[]	= { 0x30,0x00,0x09,0x0D,0x00, 0x01,0x00,0x01,0x00 }; // mong muon result receive
//	//byte m_pBuffRecv[1024];														 // 	
//
//	////int nRet = uart_sent_data((char*)m_pBuffSend + m_HeaderFile.sendStart, m_HeaderFile.sendEnd - m_HeaderFile.sendStart, (char*)m_pBuffRecv, 1024);
//	//int flag = 1;
//	//int nRet = uart_sent_data((char*)m_pBuffSend, m_lenBuffSend, (char*)m_pBuffRecv, 1024);
//	//if (nRet >=8) {
//
//	//	MessageBox(_T("1 - Successful !"), _T("Mess"));
//	//	//Sleep(500);
//	//}
//	//else
//	//{
//	//	MessageBox(_T("1 - Fail receiv"), _T("Mess"));
//	//	/*for (int i = 0; i < nRet; i++) {
//	//		if (m_pBuffRecv[i] != m_pBuffRecv_Ret[i]) {
//	//			flag = 0;
//	//			
//	//			break;
//	//		}
//	//	}*/
//	//}
//}
void DlgPowerSetting::OnBnClickedButtonEnableBoard()
{
	CString stmp;
	int n = m_pPlan->send_active_All_board();

	if (n == 0) MessageBox(_T("Active all board!"), _T("Mess"));
	else {
		stmp.Format(_T("Board number %d is error"), n);
		MessageBox(stmp, _T("Mess"));
	}
}
//// ##################################################################
////=========== Dinh tuyen =====================================
//int DlgPowerSetting::send_active_1_board(byte addr_board) {
//	byte num_bytes = 1;  // so byte payload
//	byte m_pBuffRecv[1024];
//
//	byte Buff_tx[9];
//	// cho phep board Active
//	// header
//	Buff_tx[0] = 0x00; // ADDR_PC
//	Buff_tx[1] = addr_board; // ADDR_M1_0
//	Buff_tx[2] = 0x09; // xac nhan boarrd cam dung vi tri
//	Buff_tx[3] = 0x0D;
//	Buff_tx[4] = 0x00;
//	Buff_tx[5] = 0x01; // ADDR_M1_0
//	Buff_tx[6] = 0x00;
//	Buff_tx[7] = 0x01;
//
//	// payload
//	Buff_tx[8] = 0x01;  // OK
//	// gui cho device: 
//	int len_Tx = num_bytes + 8;
//	int nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);
//
//	//MessageBox(_T("OKKK"), _T("Mess"));
//	//for (int i = 0; i < 10000; i++)
//	//{
//	//	int j = i;
//	//}
//
//	return nRet;
//}
//
//int DlgPowerSetting::send_active_All_board()  // khac 0 co  error, 0-> ok
//{
//	int TimeDelay = 1000; //ms
//	int stt;
//	byte addr_board;
//	addr_board = 0x10;
//	stt = send_active_1_board(addr_board);
//	if (stt < 8) return 1;
//
//	Sleep(TimeDelay);
//	addr_board = 0x11;
//	stt = send_active_1_board(addr_board);
//	if (stt < 8) return 2;
//
//	Sleep(TimeDelay);
//	addr_board = 0x20;
//	stt = send_active_1_board(addr_board);
//	if (stt < 8) return 3;
//
//	Sleep(TimeDelay);
//	addr_board = 0x23;
//	stt = send_active_1_board(addr_board);
//	if (stt < 8) return 4;
//
//	Sleep(TimeDelay);
//	addr_board = 0x30;
//	stt = send_active_1_board(addr_board);
//	if (stt < 8) return 5;
//
//	Sleep(TimeDelay);
//	addr_board = 0x31;
//	stt = send_active_1_board(addr_board);
//	if (stt < 8) return 6;
//
//	Sleep(TimeDelay);
//	addr_board = 0x40;
//	stt = send_active_1_board(addr_board);
//	if (stt < 8) return 7;
//
//	Sleep(TimeDelay);
//	addr_board = 0x4A;
//	stt = send_active_1_board(addr_board);
//	if (stt < 8) return 8;
//
//	Sleep(TimeDelay);
//	addr_board = 0x4B;
//	stt = send_active_1_board(addr_board);
//	if (stt < 8) return 9;
//
//	Sleep(TimeDelay);
//	addr_board = 0x50;
//	stt = send_active_1_board(addr_board);
//	if (stt < 8) return 10;
//
//	Sleep(TimeDelay);
//	addr_board = 0x51;
//	stt = send_active_1_board(addr_board);
//	if (stt < 8) return 11;
//
//	Sleep(TimeDelay);
//	addr_board = 0x52;
//	stt = send_active_1_board(addr_board);
//	if (stt < 8) return 12;
//
//	Sleep(TimeDelay);
//	addr_board = 0x53;
//	stt = send_active_1_board(addr_board);
//	if (stt < 8) return 13;
//
//	Sleep(TimeDelay);
//
//	return 0; // all OK
//}

// ##################################################################

int DlgPowerSetting::apply_relay(byte addr_board)
{
	byte m_pBuffRecv[1024];
	byte num_bytes = 0;  // so byte payload
	byte Buff_tx[8];
	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0
	Buff_tx[2] = 0x0B; // xac nhan boarrd cam dung vi tri
	Buff_tx[3] = 0x02;
	Buff_tx[4] = 0x00;
	Buff_tx[5] = 0x01; // ADDR_M1_0
	Buff_tx[6] = 0x00;
	Buff_tx[7] = 0x00;

	// payload: khong co

	// gui cho device: 
	int len_Tx = num_bytes + 8;
	int nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);

	return nRet;

}
// ###################################################################################

int DlgPowerSetting::set_paths()
{
	int stt;
	int ShortTime = 500, LongTime = 1000;

	int len_Tx;
	byte m_pBuffRecv[1024];
	int nRet;

	int MAX_SIZE_BUFF = 256;
	byte addr_board;
	byte num_bytes;
	byte Buff_tx[1024];


	// lenh 1: M1_0
	// 1 - P1
	// 2 - p2
	// 3 - p3
	// 4 - p4
	addr_board = 0x10;
	num_bytes = 40;
	// tao data: default
	for (int i = 0; i < MAX_SIZE_BUFF; i++)
		Buff_tx[i] = 0x00;


	// set up
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0

	Buff_tx[2] = 0x09;  // cmd
	Buff_tx[3] = 0x01;
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01;  // ver
	Buff_tx[6] = 0x00;

	Buff_tx[7] = num_bytes;

	Buff_tx[8] = 0x03;  //data
	Buff_tx[9] = 0x03;
	Buff_tx[10] = 0x03;
	Buff_tx[11] = 0x03;


	// gui cho device: len_Tx = num_bytes + 8;
	len_Tx = num_bytes + 8;
	nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);
	if (nRet < 8) return 101;

	Sleep(ShortTime);
	stt = apply_relay(addr_board);
	if (stt < 8) return 1;
	Sleep(LongTime);
	//..................................

	// lenh 1: M1_1
	// 1 - P1
	// 2 - p2
	// 3 - p3
	// 4 - p4
	addr_board = 0x11;
	num_bytes = 40;
	// tao data: default
	for (int i = 0; i < MAX_SIZE_BUFF; i++)
		Buff_tx[i] = 0x00;


	// set up
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0

	Buff_tx[2] = 0x09;  // cmd
	Buff_tx[3] = 0x01;
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01;  // ver
	Buff_tx[6] = 0x00;

	Buff_tx[7] = num_bytes;

	Buff_tx[8] = 0x03;  //data
	Buff_tx[9] = 0x03;
	Buff_tx[10] = 0x03;
	Buff_tx[11] = 0x03;


	// send to device
	len_Tx = num_bytes + 8;
	nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);
	if (nRet < 8) return 102;

	Sleep(ShortTime);
	stt = apply_relay(addr_board);
	if (stt < 8) return 2;
	Sleep(LongTime);
	//..................................	

	// lenh 1: M2_0
	// 1 - P1
	// 2 - p2
	// 3 - p3
	// 4 - p4
	addr_board = 0x20;
	num_bytes = 40;
	// tao data: default
	for (int i = 0; i < MAX_SIZE_BUFF; i++)
		Buff_tx[i] = 0x00;


	// set up
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0

	Buff_tx[2] = 0x09;  // cmd
	Buff_tx[3] = 0x01;
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01;  // ver
	Buff_tx[6] = 0x00;

	Buff_tx[7] = num_bytes;

	Buff_tx[8] = 0x01;  //data
	Buff_tx[9] = 0x02;
	Buff_tx[10] = 0x03;
	Buff_tx[11] = 0x04;
	// con lai  = 0


// send to device
	len_Tx = num_bytes + 8;
	nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);
	if (nRet < 8) return 103;

	Sleep(ShortTime);
	stt = apply_relay(addr_board);
	if (stt < 8) return 3;
	Sleep(LongTime);
	//..................................	
		// lenh 1: M2_3
	// 1 - P1
	// 2 - p2
	// 3 - p3
	// 4 - p4
	addr_board = 0x23;
	num_bytes = 40;
	// tao data: default
	for (int i = 0; i < MAX_SIZE_BUFF; i++)
		Buff_tx[i] = 0x00;


	// set up
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0

	Buff_tx[2] = 0x09;  // cmd
	Buff_tx[3] = 0x01;
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01;  // ver
	Buff_tx[6] = 0x00;

	Buff_tx[7] = num_bytes;

	Buff_tx[8] = 0x05;  //data
	Buff_tx[9] = 0x06;
	Buff_tx[10] = 0x07;
	Buff_tx[11] = 0x08;
	// com lai bang 0


// send to device
	len_Tx = num_bytes + 8;
	nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);
	if (nRet < 8) return 104;

	Sleep(ShortTime);
	stt = apply_relay(addr_board);
	if (stt < 8) return 4;
	Sleep(LongTime);
	//..................................

	// lenh 1: M3_0
	// 1 - P1
	// 2 - p2
	// 3 - p3
	// 4 - p4
	addr_board = 0x30;
	num_bytes = 8;
	// tao data: default
	for (int i = 0; i < MAX_SIZE_BUFF; i++)
		Buff_tx[i] = 0x00;


	// set up
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0

	Buff_tx[2] = 0x09;  // cmd
	Buff_tx[3] = 0x01;
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01;  // ver
	Buff_tx[6] = 0x00;

	Buff_tx[7] = num_bytes;

	Buff_tx[8] = 0x01;  //data
	Buff_tx[9] = 0x02;
	Buff_tx[10] = 0x03;
	Buff_tx[11] = 0x04;
	// com lai bang 0


// send to device
	len_Tx = num_bytes + 8;
	nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);
	if (nRet < 8) return 105;

	Sleep(ShortTime);
	stt = apply_relay(addr_board);
	if (stt < 8) return 5;
	Sleep(LongTime);
	//..................................

			// lenh 1: M3_1
	// 1 - P1
	// 2 - p2
	// 3 - p3
	// 4 - p4
	addr_board = 0x31;
	num_bytes = 8;
	// tao data: default
	for (int i = 0; i < MAX_SIZE_BUFF; i++)
		Buff_tx[i] = 0x00;


	// set up
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0

	Buff_tx[2] = 0x09;  // cmd
	Buff_tx[3] = 0x01;
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01;  // ver
	Buff_tx[6] = 0x00;

	Buff_tx[7] = num_bytes;

	Buff_tx[8] = 0x00;  //data
	Buff_tx[9] = 0x00;
	Buff_tx[10] = 0x00;
	Buff_tx[11] = 0x00;

	Buff_tx[12] = 0x05;  //data
	Buff_tx[13] = 0x06;
	Buff_tx[14] = 0x07;
	Buff_tx[15] = 0x08;
	// com lai bang 0


// send to device
	len_Tx = num_bytes + 8;
	nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);
	if (nRet < 8) return 106;

	Sleep(ShortTime);
	stt = apply_relay(addr_board);
	if (stt < 8) return 6;
	Sleep(LongTime);
	//..................................
}
//=========== Dinh tuyen =====================================
//============================================================
int DlgPowerSetting::Reset_paths()
{
	int stt;
	int ShortTime = 500, LongTime = 1000;

	int len_Tx;
	byte m_pBuffRecv[1024];
	int nRet;

	int MAX_SIZE_BUFF = 256;
	byte addr_board;
	byte num_bytes;
	byte Buff_tx[1024];


	// lenh 1: M1_0
	// 1 - P1
	// 2 - p2
	// 3 - p3
	// 4 - p4
	addr_board = 0x10;
	num_bytes = 40;
	// tao data: default
	for (int i = 0; i < MAX_SIZE_BUFF; i++)
		Buff_tx[i] = 0x00;


	// set up
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0

	Buff_tx[2] = 0x09;  // cmd
	Buff_tx[3] = 0x01;
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01;  // ver
	Buff_tx[6] = 0x00;

	Buff_tx[7] = num_bytes;

	//Buff_tx[8] = 0x03;  //data
	//Buff_tx[9] = 0x03;
	//Buff_tx[10] = 0x03;
	//Buff_tx[11] = 0x03;


	// gui cho device: len_Tx = num_bytes + 8;
	len_Tx = num_bytes + 8;
	nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);
	if (nRet < 8) return 101;

	Sleep(ShortTime);
	stt = apply_relay(addr_board);
	if (stt < 8) return 1;
	Sleep(LongTime);
	//..................................

	// lenh 1: M1_1
	// 1 - P1
	// 2 - p2
	// 3 - p3
	// 4 - p4
	addr_board = 0x11;
	num_bytes = 40;
	// tao data: default
	for (int i = 0; i < MAX_SIZE_BUFF; i++)
		Buff_tx[i] = 0x00;


	// set up
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0

	Buff_tx[2] = 0x09;  // cmd
	Buff_tx[3] = 0x01;
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01;  // ver
	Buff_tx[6] = 0x00;

	Buff_tx[7] = num_bytes;

	//Buff_tx[8] = 0x03;  //data
	//Buff_tx[9] = 0x03;
	//Buff_tx[10] = 0x03;
	//Buff_tx[11] = 0x03;


	// send to device
	len_Tx = num_bytes + 8;
	nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);
	if (nRet < 8) return 102;

	Sleep(ShortTime);
	stt = apply_relay(addr_board);
	if (stt < 8) return 2;
	Sleep(LongTime);
	//..................................	

	// lenh 1: M2_0
	// 1 - P1
	// 2 - p2
	// 3 - p3
	// 4 - p4
	addr_board = 0x20;
	num_bytes = 40;
	// tao data: default
	for (int i = 0; i < MAX_SIZE_BUFF; i++)
		Buff_tx[i] = 0x00;


	// set up
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0

	Buff_tx[2] = 0x09;  // cmd
	Buff_tx[3] = 0x01;
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01;  // ver
	Buff_tx[6] = 0x00;

	Buff_tx[7] = num_bytes;

	//Buff_tx[8] = 0x01;  //data
	//Buff_tx[9] = 0x02;
	//Buff_tx[10] = 0x03;
	//Buff_tx[11] = 0x04;
	// con lai  = 0


// send to device
	len_Tx = num_bytes + 8;
	nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);
	if (nRet < 8) return 103;

	Sleep(ShortTime);
	stt = apply_relay(addr_board);
	if (stt < 8) return 3;
	Sleep(LongTime);
	//..................................	
		// lenh 1: M2_3
	// 1 - P1
	// 2 - p2
	// 3 - p3
	// 4 - p4
	addr_board = 0x23;
	num_bytes = 40;
	// tao data: default
	for (int i = 0; i < MAX_SIZE_BUFF; i++)
		Buff_tx[i] = 0x00;


	// set up
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0

	Buff_tx[2] = 0x09;  // cmd
	Buff_tx[3] = 0x01;
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01;  // ver
	Buff_tx[6] = 0x00;

	Buff_tx[7] = num_bytes;

	//Buff_tx[8] = 0x05;  //data
	//Buff_tx[9] = 0x06;
	//Buff_tx[10] = 0x07;
	//Buff_tx[11] = 0x08;
	//// com lai bang 0


// send to device
	len_Tx = num_bytes + 8;
	nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);
	if (nRet < 8) return 104;

	Sleep(ShortTime);
	stt = apply_relay(addr_board);
	if (stt < 8) return 4;
	Sleep(LongTime);
	//..................................

	// lenh 1: M3_0
	// 1 - P1
	// 2 - p2
	// 3 - p3
	// 4 - p4
	addr_board = 0x30;
	num_bytes = 8;
	// tao data: default
	for (int i = 0; i < MAX_SIZE_BUFF; i++)
		Buff_tx[i] = 0x00;


	// set up
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0

	Buff_tx[2] = 0x09;  // cmd
	Buff_tx[3] = 0x01;
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01;  // ver
	Buff_tx[6] = 0x00;

	Buff_tx[7] = num_bytes;

	//Buff_tx[8] = 0x01;  //data
	//Buff_tx[9] = 0x02;
	//Buff_tx[10] = 0x03;
	//Buff_tx[11] = 0x04;
	//// com lai bang 0


// send to device
	len_Tx = num_bytes + 8;
	nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);
	if (nRet < 8) return 105;

	Sleep(ShortTime);
	stt = apply_relay(addr_board);
	if (stt < 8) return 5;
	Sleep(LongTime);
	//..................................

			// lenh 1: M3_1
	// 1 - P1
	// 2 - p2
	// 3 - p3
	// 4 - p4
	addr_board = 0x31;
	num_bytes = 8;
	// tao data: default
	for (int i = 0; i < MAX_SIZE_BUFF; i++)
		Buff_tx[i] = 0x00;


	// set up
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0

	Buff_tx[2] = 0x09;  // cmd
	Buff_tx[3] = 0x01;
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01;  // ver
	Buff_tx[6] = 0x00;

	Buff_tx[7] = num_bytes;

	//Buff_tx[8] = 0x00;  //data
	//Buff_tx[9] = 0x00;
	//Buff_tx[10] = 0x00;
	//Buff_tx[11] = 0x00;

	//Buff_tx[12] = 0x05;  //data
	//Buff_tx[13] = 0x06;
	//Buff_tx[14] = 0x07;
	//Buff_tx[15] = 0x08;
	//// com lai bang 0


// send to device
	len_Tx = num_bytes + 8;
	nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);
	if (nRet < 8) return 106;

	Sleep(ShortTime);
	stt = apply_relay(addr_board);
	if (stt < 8) return 6;
	Sleep(LongTime);
	//..................................
}
//=========== Dinh tuyen =====================================
void DlgPowerSetting::OnBnClickedButtonSetPath()
{
	// TODO: Add your control notification handler code here
	CString stmp;
	int n = set_paths();
	if (n == 0) MessageBox(_T("Set all path is successfull!"), _T("Mess"));
	else {
		stmp.Format(_T("Path number %d is error"), n);
		MessageBox(stmp, _T("Mess"));
	}

}


void DlgPowerSetting::OnBnClickedButtonResetPath()
{
	// TODO: Add your control notification handler code here
	//Reset_paths();
	CString stmp;
	int n = Reset_all_paths();
	if (n == 0) MessageBox(_T("Reseted all board!"), _T("Mess"));
	else {
		stmp.Format(_T("Reset Board number %d is error"), n);
		MessageBox(stmp, _T("Mess"));
	}

}

int DlgPowerSetting::Reset_all_paths() {
	byte addr_board;
	int stt;

	addr_board = ADDR_M1_0;
	stt = Reset_1_paths(addr_board);
	if (stt < 8) return 1;
	Sleep(300);

	addr_board = ADDR_M1_1;
	stt = Reset_1_paths(addr_board);
	if (stt < 8) return 2;
	Sleep(300);

	addr_board = ADDR_M2PS_0;
	stt = Reset_1_paths(addr_board);
	if (stt < 8) return 3;
	Sleep(300);

	addr_board = ADDR_M2PS_3;
	stt = Reset_1_paths(addr_board);
	if (stt < 8) return 4;
	Sleep(300);

	addr_board = ADDR_M3_0;
	stt = Reset_1_paths(addr_board);
	if (stt < 8) return 5;
	Sleep(300);

	addr_board = ADDR_M3_1;
	stt = Reset_1_paths(addr_board);
	if (stt < 8) return 6;
	Sleep(300);

	//--------------------
	addr_board = ADDR_M2SIG_0;
	stt = Reset_1_paths(addr_board);
	if (stt < 8) return 7;
	Sleep(300);

	addr_board = ADDR_M2SIG_1;
	stt = Reset_1_paths(addr_board);
	if (stt < 8) return 8;
	Sleep(300);
	//--------------------------
	addr_board = ADDR_M5_0;
	stt = Reset_1_paths(addr_board);
	if (stt < 8) return 9;
	Sleep(300);

	addr_board = ADDR_M5_1;
	stt = Reset_1_paths(addr_board);
	if (stt < 8) return 10;
	Sleep(300);

	addr_board = ADDR_M5_2;
	stt = Reset_1_paths(addr_board);
	if (stt < 8) return 11;
	Sleep(300);

	addr_board = ADDR_M5_3;
	stt = Reset_1_paths(addr_board);
	if (stt < 8) return 12;
	Sleep(300);

	return 0;
}

int DlgPowerSetting::Reset_1_paths(byte addr_board)
{
	byte m_pBuffRecv[1024];
	byte num_bytes = 0;  // so byte payload
	byte Buff_tx[8];
	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0
	Buff_tx[2] = 0x0B; // xac nhan boarrd cam dung vi tri
	Buff_tx[3] = 0x01;
	Buff_tx[4] = 0x00;
	Buff_tx[5] = 0x01; // ADDR_M1_0
	Buff_tx[6] = 0x00;
	Buff_tx[7] = 0x00;

	// payload: khong co

	// gui cho device: 
	int len_Tx = num_bytes + 8;
	int nRet = uart_sent_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, 1024);

	return nRet;

}

void DlgPowerSetting::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (UpdateDataGUIToVar()) return;
	if (m_pPlan->Save_8PowerParam_TestCase(m_pcFigCIniReader, 0) == 1)
		MessageBox(_T("Lưu thông tin thành công"), _T("Thông báo"));
	else MessageBox(_T("Qua trình lưu xảy ra lỗi"), _T("Thông báo"));
}




void DlgPowerSetting::OnBnClickedReadPwrM3Value()
{
	// TODO: Add your control notification handler code here
	Sleep(100);  // ms
	m_pPlan->ExtrackPackage_Get_8PWR_Info(ADDR_M3_0);
	Sleep(500);  // ms
	m_pPlan->ExtrackPackage_Get_8PWR_Info(ADDR_M3_1);

	for (int i = 0; i <= 8; i++)
	{
		m_pPlan->mTestCase.mPowers.POWER[i] = m_pPlan->Pwr_M3_0[i];  // lay cac thong tin khac. hai khoi giong nhau
		m_pPlan->mTestCase.mPowers.POWER[i].UGet = (m_pPlan->Pwr_M3_0[i].UGet + m_pPlan->Pwr_M3_1[i].UGet) / 2;  // lay cac thong tin khac. hai khoi giong nhau
		m_pPlan->mTestCase.mPowers.POWER[i].IGet = m_pPlan->Pwr_M3_0[i].IGet + m_pPlan->Pwr_M3_1[i].IGet;  // cap nhat dong cua ca hai khoi: M3_0 + M3_1
	}
	UpdateDataToGUI();
	InitBtnOnOff();
	UpdateData(false);
	UpdateStatus();

}
