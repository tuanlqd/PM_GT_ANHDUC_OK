// MainDlg.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "MainDlg.h"

#include "DlgConnectToDevide.h"
#include "DlgPinSettingEdit.h"
#include "DlgChanelSelection.h"
#include "DlgPowerSetting.h"
#include "DlgPowerSettingThreshold.h"
#include "DlgPowerSettingParam.h"
#include "DlgCreateCase.h"
#include "DlgTestOnBoard.h"

#define OK	1
#define ERR	0

// MainDlg dialog

IMPLEMENT_DYNAMIC(MainDlg, CDialogEx)

MainDlg::MainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLGMAIN, pParent)
{
	//char* str_receiPhTmp = "D:\\CSDL_20230705\\Kolchuga\\ƂCДA\\BaiKT_So2"; // for test
}

MainDlg::~MainDlg()
{
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_Username);
}


BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &MainDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_Connect, &MainDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_CREATECASE, &MainDlg::OnBnClickedBtnCreatecase)
	ON_BN_CLICKED(IDC_BTN_POWERSETTING, &MainDlg::OnBnClickedBtnPowersetting)
	ON_BN_CLICKED(IDC_BTN_POWERTHRESHOL, &MainDlg::OnBnClickedBtnPowerthreshol)
	ON_BN_CLICKED(IDC_BTN_EXTRA_SETTING, &MainDlg::OnBnClickedBtnExtraSetting)
	ON_BN_CLICKED(IDC_BTN_PIN_SETTING, &MainDlg::OnBnClickedBtnPinSetting)
	ON_BN_CLICKED(IDC_BTN_PIN_SELECTION, &MainDlg::OnBnClickedBtnPinSelection)
	ON_BN_CLICKED(IDC_BTN_CREATE_DATA_TESTCASE, &MainDlg::OnBnClickedBtnCreateDataTestcase)
	ON_BN_CLICKED(IDC_BTN_RUNASUSER, &MainDlg::OnBnClickedBtnRunasuser)
//	ON_EN_CHANGE(IDC_EDIT_VER, &MainDlg::OnEnChangeEditVer)
END_MESSAGE_MAP()


// MainDlg message handlers

// DlgTestOnBoard message handlers
BOOL MainDlg::OnInitDialog()
{
	m_pCIniReader->setINIFileName(_T(""));
	CString strSection;
	CString strValue, strKey;
	int mlength = 5;
	if (m_pCIniReader != NULL) {
		strSection = _T("DEFINE_STRINGFORM");
		strKey = _T("admin_s_SubTitle");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_SubTitle = strValue;
		strKey = _T("admin_s_MainTitle");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength()>= mlength) s_MainTitle = strValue;
		strKey = _T("admin_s_KTketnoi");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_KTketnoi = strValue;
		strKey = _T("admin_s_TLThongTinBoard");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_TLThongTinBoard = strValue;
		strKey = _T("admin_s_TLBaoVeNguon");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_TLBaoVeNguon = strValue;
		strKey = _T("admin_s_TLNguonCap");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_TLNguonCap = strValue;
		strKey = _T("admin_s_TLKetNoiChan");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_TLKetNoiChan = strValue;
		strKey = _T("admin_s_TLThuocTinhChan");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_TLThuocTinhChan = strValue;
		strKey = _T("admin_s_TLThamsoTinHieuVaKenhMoRong");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_TLThamsoTinHieuVaKenhMoRong = strValue;
		strKey = _T("admin_s_TaoDLCauHinh");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_TaoDLCauHinh = strValue;
		strKey = _T("admin_s_ChayKT");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_ChayKT = strValue;
		strKey = _T("admin_s_Thoat");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_Thoat = strValue;
		strKey = _T("admin_s_NguoiKT");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_NguoiKT = strValue;



	}
	//===========================================

	CEdit* pEditCtrl;
	CButton* pButtonCtrl;
	this->SetWindowTextW(s_SubTitle);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_Connect);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_KTketnoi);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_CREATECASE);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_TLThongTinBoard);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_POWERTHRESHOL);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_TLBaoVeNguon);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_POWERSETTING);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_TLNguonCap);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_PIN_SELECTION);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_TLKetNoiChan);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_PIN_SETTING);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_TLThuocTinhChan);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_EXTRA_SETTING);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_TLThamsoTinHieuVaKenhMoRong);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_CREATE_DATA_TESTCASE);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_TaoDLCauHinh);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_RUNASUSER);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_ChayKT);
	pButtonCtrl = (CButton*)GetDlgItem(IDOK);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_Thoat);

	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_MAIN_TITLE);
	pEditCtrl->SetFont(m_bfont);
	pEditCtrl->SetWindowTextW(s_MainTitle);
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_USERNAME);
	pEditCtrl->SetFont(m_sfont);

	m_pCIniReader->setINIFileName(_T(""));
	m_pCPlan->Load_PhiFileConfigPath(m_pCIniReader);
	m_pCIniReader->setTestCaseFileName(m_pCPlan->mTestCase.mPathInfo.PhiFileConfigPath);  // PATH  Phi
	m_pCPlan->Load_AdminName(m_pCIniReader);
	m_Username = s_NguoiKT + m_pCPlan->mTestCase.mPathInfo.Usermane;
	UpdateData(FALSE);
	this->BringWindowToTop();
	//---------------------------
	if (GETDATABASE) {
		CWnd* pwnd = GetDlgItem(IDC_BTN_Connect);
		if (pwnd)
			pwnd->EnableWindow(false);
		pwnd = GetDlgItem(IDC_BTN_CREATECASE);
		if (pwnd)
			pwnd->EnableWindow(true);
		pwnd = GetDlgItem(IDC_BTN_RUNASUSER);
		if (pwnd)
			pwnd->EnableWindow(false);
		
	}
	return TRUE;
}

void MainDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void MainDlg::OnBnClickedBtnConnect()
{
	//// TODO: Add your control notification handler code here

	m_pCIniReader->setINIFileName(_T(""));
	DlgConnectToDevide mDlgConnectToDevide;
	mDlgConnectToDevide.m_pCIniReader = m_pCIniReader;
	mDlgConnectToDevide.pFlagConnected = pFlagConnected;
	mDlgConnectToDevide.p_sfont = m_sfont;
	mDlgConnectToDevide.p_bfont = m_bfont;
	mDlgConnectToDevide.p_tfont = m_tfont;
	mDlgConnectToDevide.p_nfont = m_nfont;
	mDlgConnectToDevide.pPubstrAdrressConn = pPubstrAdrressConn;
	if (mDlgConnectToDevide.DoModal() == IDOK)
	{
		//connect
	}
	m_pCIniReader->setTestCaseFileName(m_pCPlan->mTestCase.mPathInfo.FullPath);
	//=======================================
	int nRet = 0;
	//if (*pFlagConnected == 1) {
	//	MessageBox(_T("Trạng thái đang kết nối"), _T("Thông báo"));
	//}
	//else {
	//	MessageBox(_T("Trạng thái đang có lỗi"), _T("Thông báo"));
	//}
	//------------------------
	//if (*pFlagConnected == OK) MessageBox(_T("OK"), _T("Mess"));
	//else MessageBox(_T("not OK"), _T("Mess"));
	
	//if (*pFlagConnected == OK||*p_mode == DEBUGADMIN) {
	//	CWnd* pwnd = GetDlgItem(IDC_BTN_CREATECASE);
	//	if (pwnd)
	//		pwnd->EnableWindow(true);
	//}
	////=======================================
	//if (*p_mode == DEBUGNORMAL) {
	//	CWnd* pwnd = GetDlgItem(IDC_BTN_CREATECASE);
	//	if (pwnd)
	//		pwnd->EnableWindow(true);
	//}
	CWnd* pwnd = GetDlgItem(IDC_BTN_CREATECASE);
	if (pwnd)
		pwnd->EnableWindow(true);
}


void MainDlg::OnBnClickedBtnCreatecase()
{
	// TODO: Add your control notification handler code here
	DlgCreateCase mDlgCreateCase;
	mDlgCreateCase.m_pPlan = m_pCPlan;
	mDlgCreateCase.m_pCIniReader = m_pCIniReader;
	mDlgCreateCase.m_sfont = this->m_sfont;
	mDlgCreateCase.m_bfont = this->m_bfont;
	mDlgCreateCase.m_tfont = this->m_tfont;
	mDlgCreateCase.DoModal();

	if (m_pCPlan->OrderRun >= 0) {
		CWnd* pwnd = GetDlgItem(IDC_BTN_POWERSETTING);
		if (pwnd)
			pwnd->EnableWindow(true);
		pwnd = GetDlgItem(IDC_BTN_POWERTHRESHOL);
		if (pwnd)
			pwnd->EnableWindow(true);
		pwnd = GetDlgItem(IDC_BTN_PIN_SETTING);
		if (pwnd)
			pwnd->EnableWindow(true);
		pwnd = GetDlgItem(IDC_BTN_PIN_SELECTION);
		if (pwnd)
			pwnd->EnableWindow(true);
		pwnd = GetDlgItem(IDC_BTN_EXTRA_SETTING);
		if (pwnd)
			pwnd->EnableWindow(true);
		//---------------------------------
		pwnd = GetDlgItem(IDC_BTN_CREATE_DATA_TESTCASE);
		if (pwnd)
			pwnd->EnableWindow(true);
		//---------------------------------

	}
		
}


void MainDlg::OnBnClickedBtnPowersetting()
{
	// TODO: Add your control notification handler code here
	if (m_pCPlan->OrderRun < 0) {
		MessageBox(bmess, tmess);
		return;
	}

	DlgPowerSetting mDlgPowerSetting;
	mDlgPowerSetting.m_pcFigCIniReader = m_pCIniReader;
	mDlgPowerSetting.m_pPlan = m_pCPlan;
	mDlgPowerSetting.DoModal();
}


void MainDlg::OnBnClickedBtnPowerthreshol()
{
	// TODO: Add your control notification handler code here
	if (m_pCPlan->OrderRun < 0) {
		MessageBox(bmess, tmess);
		return;
	}
	DlgPowerSettingThreshold mDlgPowerSettingThreshold;
	mDlgPowerSettingThreshold.m_pcFigCIniReader = m_pCIniReader;
	mDlgPowerSettingThreshold.m_pPlan = m_pCPlan;
	mDlgPowerSettingThreshold.m_tfont = m_tfont;
	mDlgPowerSettingThreshold.DoModal();
}


void MainDlg::OnBnClickedBtnExtraSetting()
{
	// TODO: Add your control notification handler code here
	if (m_pCPlan->OrderRun < 0) {
		MessageBox(bmess, tmess);
		return;
	}
	DlgPowerSettingParam mDlgPowerSettingParam;
	mDlgPowerSettingParam.m_sfont = m_sfont;
	mDlgPowerSettingParam.m_bfont = m_bfont;
	mDlgPowerSettingParam.m_tfont = m_tfont;
	mDlgPowerSettingParam.m_pIniReader = m_pCIniReader;
	mDlgPowerSettingParam.m_pPlan = m_pCPlan;
	mDlgPowerSettingParam.DoModal();
}


void MainDlg::OnBnClickedBtnPinSetting()
{
	// TODO: Add your control notification handler code here
	if (m_pCPlan->OrderRun < 0) {
		MessageBox(bmess, tmess);
		return;
	}
	DlgChanelSelection mDlgChanelSelection;
	mDlgChanelSelection.m_pPlan = m_pCPlan;
	mDlgChanelSelection.m_pCIniReader = m_pCIniReader;
	mDlgChanelSelection.m_DeviceName = m_pCPlan->mTestCase.mPathInfo.DeviceName;
	mDlgChanelSelection.m_BoardName = m_pCPlan->mTestCase.mPathInfo.BoardName;
	mDlgChanelSelection.DoModal();
}


void MainDlg::OnBnClickedBtnPinSelection()
{
	// TODO: Add your control notification handler code here

	if (m_pCPlan->OrderRun < 0) {
		MessageBox(bmess, tmess);
		return;
	}
	DlgPinSettingEdit mDlgPinSettingEdit;
	mDlgPinSettingEdit.m_pPlan = m_pCPlan;
	mDlgPinSettingEdit.m_pCIniReader = m_pCIniReader;
	mDlgPinSettingEdit.m_DeviceName = m_pCPlan->mTestCase.mPathInfo.DeviceName;
	mDlgPinSettingEdit.m_BoardName = m_pCPlan->mTestCase.mPathInfo.BoardName;
	mDlgPinSettingEdit.DoModal();
}

BOOL IsFileExists(const CString& filePath) {
	CFileStatus fileStatus;
	return CFile::GetStatus(filePath, fileStatus);
}
void MainDlg::OnBnClickedBtnCreateDataTestcase()
{
	// TODO: Add your control notification handler code here

	//========================================================
	// write to string
	// m_pCPlan->InitChanelDataConf();
	//CString dataStr = m_pPlan->ChanelConfToString();
	//CT2A ascii(dataStr);
	//MessageBox(_T("Chuyen Thanh chay"), _T("thong tbao"));
	//int comment = 0;
	//mySocket->TCP_send("sendbuf\n");
	//mySocket->TCP_send(ascii);

	//mFlagThanhRun = 1;
	//CString stmstr;
	//while (bflag) {
	//	//stmstr.Format(_T("thanh dang chay %d"), mFlagThanhRun);
	//	//MessageBox(stmstr, _T("thong bao"));
	//	Sleep(10);
	//	switch (mFlagThanhRun) {
	//		case 1:
	//			mySocket->TCP_send(ascii);
	//			//stmstr.Format(_T("thanh dang chay %d"), mFlagThanhRun);
	//			//MessageBox(stmstr, _T("thong bao"));
	//			//return;
	//			break;
	//		case 2:
	//			bflag = false;
	//			return;
	//			break;
	//		case 0: 
	//			bflag = false;
	//			return;
	//			break;
	//	}
	//}
	//========================================================
	//========================================================
	//Write: save as exit open file
	//----------------------------------------------------
	//TCHAR szFilters[] = _T("data Files (*.dat)|*.ini|All Files (*.*)|*.*||");
	//CFileDialog fileDlg(TRUE, _T("dat"), _T("*.dat"),
	//	OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, szFilters);
	//CString pathName;
	//if (fileDlg.DoModal() == IDOK)
	//{
	//	pathName = fileDlg.GetPathName();
	//  if(IsFileExists(namePath))	CFile::Remove(namePath);
	// 
	//	CString tmpStr;
	//	tmpStr.Format(_T("%s"), pathName);
	//	m_pCIniReader->setTestCaseFileName(tmpStr);

	//	m_pCPlan->InitChanelDataConf();
	//	if (m_pCPlan->ChanelConfToFileConf(m_pCIniReader) == 1)
	//		MessageBox(_T("Ghi dữ liệu thành công!"), _T("Thông báo"));
	//	else
	//		MessageBox(_T("Ghi dữ liệu không thành công!"), _T("Thông báo"));
	//	//----------
	//	pathName = m_pCPlan->mTestCase.mPathInfo.FullPath;
	//	tmpStr.Format(_T("%s"), pathName);
	//	m_pCIniReader->setTestCaseFileName(tmpStr);
	//}
	////======================================================
	//========================================================
	//Write to file fix path Cosodulieu\data.dat
	//---------------------------------------------
	CString namePath;
	namePath = m_pCPlan->mTestCase.mPathInfo.TestPath + _T("\\data.dat");
	//-----------------------------
	if(IsFileExists(namePath))	CFile::Remove(namePath);

	CString tmpStr;
	tmpStr.Format(_T("%s"), namePath);
	m_pCIniReader->setTestCaseFileName(tmpStr);
	////--------------------------------------------
	CFile file;
	if (file.Open(tmpStr, CFile::modeCreate | CFile::modeWrite)) {
		unsigned char utf16LEBOM[2] = { 0xFF, 0xFE };
		file.Write(utf16LEBOM, sizeof(utf16LEBOM));
		file.Close();
	}
	
	
	m_pCPlan->InitChanelDataConf();
	m_pCPlan->ChanelConfToFileConf(m_pCIniReader);
	//-------------------------------------------------------------
	if (IsFileExists(namePath))	
		MessageBox(_T("Tạo dữ liệu thành công!"), _T("Thông báo"));
	else
		MessageBox(_T("LỖI: Lỗi tạo dữ liệu\r\nXem lại đường dẫn:\r\n") + namePath, _T("Thông báo"));
	//------------------------------------------
	namePath = m_pCPlan->mTestCase.mPathInfo.FullPath;
	tmpStr.Format(_T("%s"), namePath);
	m_pCIniReader->setTestCaseFileName(tmpStr);

	////============================================
	// send filepath to Thanh
	// ------------------------------------
	////CString dataStr = _T("aDuc");
	////CT2A ascii(dataStr);
	//CT2A pathfilenameThanh(pathName);
	//AfxMessageBox(_T("Thong bao Thanh chay"));
	////SocketTh->TCP_send("thanhchay\n\r");
	////SocketTh->TCP_send(pathfilenameThanh);
	//*m_pFlagThRun = 1;
	//while (1) {
	//	Sleep(50);
	//	if (*m_pFlagThRun == 1) {
	//		return;
	//	}
	//}
	//------------------------------------------
	//=============================================
}

void MainDlg::OnBnClickedBtnRunasuser()
{
	// TODO: Add your control notification handler code here

	DlgTestOnBoard mDlgTestOnBoard;
	mDlgTestOnBoard.SocketTh = SocketTh;
	mDlgTestOnBoard.pFlagThRun = m_pFlagThRun;
	mDlgTestOnBoard.m_pCIniReader = m_pCIniReader;
	mDlgTestOnBoard.m_pCPlan= m_pCPlan;
	mDlgTestOnBoard.pFlagConnected = pFlagConnected;
	mDlgTestOnBoard.pFlagThConnected = pFlagThConnected;
	mDlgTestOnBoard.p_mode = p_mode;
	mDlgTestOnBoard.m_sfont = this->m_sfont;
	mDlgTestOnBoard.m_bfont = this->m_bfont;
	mDlgTestOnBoard.m_tfont = this->m_tfont;
	mDlgTestOnBoard.s_NguoiKT = this->s_NguoiKT;
	mDlgTestOnBoard.m_Username = this->m_Username;
	mDlgTestOnBoard.m_User = 0;
	mDlgTestOnBoard.pPubstrAdrressConn = pPubstrAdrressConn;
	this->ShowWindow(SW_HIDE);
	mDlgTestOnBoard.DoModal();
	this->ShowWindow(SW_SHOW);
	this->BringWindowToTop();
}



