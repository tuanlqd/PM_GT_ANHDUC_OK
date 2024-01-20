// DlgCreateCase.cpp : implementation fileOnBnClickedButton2
//
#include <afx.h>
#include <iostream>
#include "CSpreadSheet.h"
#include <afxdb.h>
#include <afxdisp.h>  // Đảm bảo bạn đã bao gồm thư viện này

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgCreateCase.h"
#include "DlgDeviceJack.h"

//using namespace std;
// DlgCreateCase dialog

IMPLEMENT_DYNAMIC(DlgCreateCase, CDialogEx)

DlgCreateCase::DlgCreateCase(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CREATE_TESTCASE, pParent)
	, m_DeviceName(_T(""))
	, m_BoardName(_T(""))
	, m_TestName(_T(""))
	, m_TestCaseInfo(_T("Open testcase"))
	
{

}

DlgCreateCase::~DlgCreateCase()
{
}

void DlgCreateCase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEVICE_NAME, m_DeviceName);
	DDX_Text(pDX, IDC_EDIT_BOARD_NAME, m_BoardName);
	DDX_Control(pDX, IDC_STATIC_DEVICE_NAME, m_BMP_DEVICE_NAME);
	DDX_Control(pDX, IDC_STATIC_BOARD_NAME, m_BMP_BOARD_NAME);
    DDX_Text(pDX, IDC_TESTCASE_INFO, m_TestCaseInfo);
	DDX_Text(pDX, IDC_EDIT_TEST_I, m_TestName);
}


BEGIN_MESSAGE_MAP(DlgCreateCase, CDialogEx)
	ON_BN_CLICKED(IDC_OPEN_TESTCASE, &DlgCreateCase::OnBnClickedOpenTestcase)
	ON_BN_CLICKED(IDOK, &DlgCreateCase::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_EDIT_TESTCASE, &DlgCreateCase::OnBnClickedBtnEditTestcase)
	ON_BN_CLICKED(IDC_BTN_SAVE, &DlgCreateCase::OnBnClickedBtnSave)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// DlgCreateCase message handlers

BOOL DlgCreateCase::OnInitDialog()
{	
	//CDialogEx::OnInitDialog();
	CDialog::OnInitDialog();
	m_pCIniReader->setINIFileName(_T(""));
	CString strSection;
	CString strValue, strKey;
	int mlength = 5;
	if (m_pCIniReader != NULL) {
		strSection = _T("DEFINE_STRINGFORM");
		strKey = _T("OpenTestCase_s_SubTitle");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_SubTitle = strValue;
		strKey = _T("OpenTestCase_s_MainTitle");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_MainTitle = strValue;
		strKey = _T("OpenTestCase_s_TenDai");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_TenDai = strValue;
		strKey = _T("OpenTestCase_s_TenBomach");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_TenBomach = strValue;
		strKey = _T("OpenTestCase_s_BaiKT");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_BaiKT = strValue;
		strKey = _T("OpenTestCase_s_OpenfileCauHinh");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_OpenfileCauHinh = strValue;
		strKey = _T("OpenTestCase_s_TLChanJack");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_TLChanJack = strValue;
		strKey = _T("OpenTestCase_s_GhiCauHinh");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_GhiCauHinh = strValue;
		
		strKey = _T("OpenTestCase_s_Thoat");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.GetLength() >= mlength) s_Thoat = strValue;
	}
	CEdit* pEditCtrl;
	CButton* pButtonCtrl;
	this->SetWindowTextW(s_SubTitle);
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_MAIN_TITLE_ONPENTESTCASE);
	pEditCtrl->SetFont(m_bfont);
	pEditCtrl->SetWindowTextW(s_MainTitle);
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_TENDAI);
	pEditCtrl->SetFont(m_sfont);
	pEditCtrl->SetWindowTextW(s_TenDai);
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_TENBOMACH);
	pEditCtrl->SetFont(m_sfont);
	pEditCtrl->SetWindowTextW(s_TenBomach);
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_TENBAIKT);
	pEditCtrl->SetFont(m_sfont);
	pEditCtrl->SetWindowTextW(s_BaiKT);
	pEditCtrl = (CEdit*)GetDlgItem(IDC_TESTCASE_INFO);
	pEditCtrl->SetFont(m_sfont);
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_DEVICE_NAME);
	pEditCtrl->SetFont(m_sfont);
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_BOARD_NAME);
	pEditCtrl->SetFont(m_sfont);
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_TEST_I);
	pEditCtrl->SetFont(m_sfont);

	pButtonCtrl = (CButton*)GetDlgItem(IDC_OPEN_TESTCASE);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_OpenfileCauHinh);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_EDIT_TESTCASE);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_TLChanJack);
	pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_SAVE);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_GhiCauHinh);
	pButtonCtrl = (CButton*)GetDlgItem(IDOK);
	pButtonCtrl->SetFont(m_sfont);
	pButtonCtrl->SetWindowTextW(s_Thoat);
	
	
	m_DeviceName = m_pPlan->mTestCase.mPathInfo.DeviceName;
	m_BoardName = m_pPlan->mTestCase.mPathInfo.BoardName;
	m_TestName = m_pPlan->mTestCase.mPathInfo.TestName;
	UpdateData(false);
	//----------------------------
	if (m_pPlan->mTestCase.mJackInfo.nJacks != 0) {
		UpdatedataToGUI();
		//LoadDeviceBoardPic();
		PATHINFO_DEF* m_pPathInfo;
		m_pPathInfo = &m_pPlan->mTestCase.mPathInfo;
		CImage image;
		HRESULT result;
		//-----------------------------------------

		CString mPicDevicePathName = m_pPathInfo->DevicePicPath + _T("\\") + m_pPathInfo->DevicePicName;
		CString mPicBoardPathName = m_pPathInfo->BoardPath + _T("\\") + m_pPathInfo->BoardPicName;
		CString mPicBoardTestName = m_pPathInfo->TestPicPath + _T("\\") + m_pPathInfo->TestPicName;

		//----------------------------------------
		
		result = image.Load(mPicDevicePathName);
		if (SUCCEEDED(result))
		{

			CRect rect;
			GetDlgItem(IDC_STATIC_DEVICE_NAME)->GetClientRect(&rect);
			CDC* pDC = GetDlgItem(IDC_STATIC_DEVICE_NAME)->GetDC();
			image.Draw(pDC->m_hDC, rect);
		}
		//------------------------------------------
		result = image.Load(mPicBoardPathName);
		if (SUCCEEDED(result))
		{
			CRect rect;
			GetDlgItem(IDC_STATIC_BOARD_NAME)->GetClientRect(&rect);
			CDC* pDC = GetDlgItem(IDC_STATIC_BOARD_NAME)->GetDC();
			image.Draw(pDC->m_hDC, rect);
		}

		LoadDeviceBoardInfor();
		if(m_pPlan->OrderRun>0) LoadSometingInGUI(); //refress DUKKKK
		// this->UpdateWindow();

		UpdateData(false);
	}
	//-------------------------
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void DlgCreateCase::UpdatedataToGUI() {
	m_DeviceName = m_pPlan->mTestCase.mPathInfo.DeviceName;
	m_BoardName = m_pPlan->mTestCase.mPathInfo.BoardName;
	m_TestName = m_pPlan->mTestCase.mPathInfo.TestName;
	UpdateData(false);
}
void DlgCreateCase::UpdateGUITodata() {

}

//==========================================================


void DlgCreateCase::ReadExcelData()
{
	//AfxBeginThread([](LPVOID) -> UINT {
	//	CDatabase database;
	//	CString excelFile = _T("D:\\abc.xlsx");

	//	// Đặt tên DSN (Data Source Name)
	//	CString dsn = _T("ExcelDSN");

	//	CString connectString = _T("ODBC;DSN=") + dsn + _T(";Driver={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=") + excelFile;

	//	if (!database.OpenEx(connectString))
	//	{
	//		AfxMessageBox(_T("Không thể mở tệp Excel."));
	//		return 1;
	//	}

	//	AfxMessageBox(_T("Mở tệp Excel. OK"));

	//	CString strSQL = _T("SELECT * FROM [Sheet1$]"); // Sheet1 là tên của sheet trong Excel

	//	CRecordset recordset(&database);
	//	if (recordset.Open(CRecordset::snapshot, strSQL))
	//	{
	//		while (!recordset.IsEOF())
	//		{
	//			CString fieldValue;
	//			recordset.GetFieldValue(_T("Column1"), fieldValue); // Thay "Column1" bằng tên cột thực tế trong tệp Excel
	//			// Xử lý dữ liệu ở đây, ví dụ: đưa fieldValue vào danh sách, mảng, ...
	//			recordset.MoveNext();
	//		}
	//		recordset.Close();
	//	}

	//	database.Close();

	//	return 0;
	//	}, nullptr);
}
//
////----------------------------------------
//#include "CExcel.h"  // Đảm bảo đường dẫn đúng đến thư viện CExcel
//
//void ReadExcelFile(const CString& filePath)
//{
//	CExcel excel;
//	excel.Open(filePath, CExcel::xlNormal);  // Mở file Excel
//
//	if (excel.GetCount() > 0)  // Kiểm tra xem file đã được mở thành công hay chưa
//	{
//		CWorksheet* pSheet = excel.GetSheet(1);  // Lấy sheet đầu tiên (worksheet)
//		if (pSheet)
//		{
//			int rowCount = pSheet->GetRowCount();
//			int colCount = pSheet->GetColCount();
//
//			for (int row = 1; row <= rowCount; ++row)
//			{
//				for (int col = 1; col <= colCount; ++col)
//				{
//					CString cellValue = pSheet->GetCellString(row, col);
//					// Ở đây, bạn có thể làm gì đó với giá trị cellValue
//				}
//			}
//		}
//		else
//		{
//			AfxMessageBox(_T("Không thể lấy thông tin sheet."));
//		}
//
//		excel.Close();
//	}
//	else
//	{
//		AfxMessageBox(_T("Không thể mở file Excel."));
//	}
//}
//
//int main()
//{
//	AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0); // Khởi tạo MFC
//
//	CString filePath = _T("duong_dan_den_file.xlsx");  // Đặt đường dẫn tới file Excel của bạn ở đây
//	ReadExcelFile(filePath);
//
//	return 0;
//}

//----------------------------------------


void DlgCreateCase::ReadExcelFile(const CString& filePath)
{
	//CoInitialize(NULL);  // Khởi tạo COM

	//// Tạo đối tượng Excel
	//_Application excelApp;
	//excelApp.CreateDispatch(_T("Excel.Application"));

	//// Mở workbook
	//_Workbook workbook = excelApp.Workbooks.Open(filePath);
	//_Worksheet worksheet = workbook.GetActiveSheet();

	//// Lấy số dòng và cột tối đa
	//long rowCount = worksheet.GetRows()->GetCount();
	//long colCount = worksheet.GetColumns()->GetCount();

	//// Đọc dữ liệu từ mỗi ô và làm gì đó với nó
	//for (long row = 1; row <= rowCount; ++row)
	//{
	//	for (long col = 1; col <= colCount; ++col)
	//	{
	//		_Range cell = worksheet.GetCells()->GetItem(COleVariant(row), COleVariant(col));
	//		CString cellValue = cell.GetValue();
	//		// Ở đây, bạn có thể làm gì đó với giá trị cellValue
	//	}
	//}

	//// Đóng workbook và thoát ứng dụng Excel
	//workbook.Close(VARIANT_FALSE);
	//excelApp.Quit();

	//CoUninitialize();  // Giải phóng COM
}
//
//int main()
//{
//	AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0); // Khởi tạo MFC
//
//	CString filePath = _T("duong_dan_den_file.xlsx");  // Đặt đường dẫn tới file Excel của bạn ở đây
//	ReadExcelFile(filePath);
//
//	return 0;
//}
//------------------------------------------
void DlgCreateCase::LoadSometingInGUI() {
	UpdatedataToGUI();
	//---------------------------------------
	//LoadDeviceBoardPic();
	PATHINFO_DEF* m_pPathInfo;
	m_pPathInfo = &m_pPlan->mTestCase.mPathInfo;
	CImage image;
	HRESULT result;
	//-----------------------------------------

	CString mPicDevicePathName = m_pPathInfo->DevicePicPath + _T("\\") + m_pPathInfo->DevicePicName;
	CString mPicBoardPathName = m_pPathInfo->BoardPath + _T("\\") + m_pPathInfo->BoardPicName;
	CString mPicCirTestName = m_pPathInfo->TestPicPath + _T("\\") + m_pPathInfo->TestPicName;

	result = image.Load(mPicDevicePathName);
	if (SUCCEEDED(result))
	{
		CRect rect;
		GetDlgItem(IDC_STATIC_DEVICE_NAME)->GetClientRect(&rect);
		CDC* pDC = GetDlgItem(IDC_STATIC_DEVICE_NAME)->GetDC();
		image.Draw(pDC->m_hDC, rect);
	}
	//------------------------------------------
	result = image.Load(mPicBoardPathName);
	if (SUCCEEDED(result))
	{
		CRect rect;
		GetDlgItem(IDC_STATIC_BOARD_NAME)->GetClientRect(&rect);
		CDC* pDC = GetDlgItem(IDC_STATIC_BOARD_NAME)->GetDC();
		image.Draw(pDC->m_hDC, rect);
	}
	////------------------------------------------
	//result = image.Load(mPicCirTestName);
	//if (SUCCEEDED(result))
	//{
	//	CRect rect;
	//	GetDlgItem(IDC_STATIC_MACH_PIC)->GetClientRect(&rect);
	//	CDC* pDC = GetDlgItem(IDC_STATIC_MACH_PIC)->GetDC();
	//	image.Draw(pDC->m_hDC, rect);
	//}
	LoadDeviceBoardInfor();
	UpdateData(false);
}
//------------------------------------------
void DlgCreateCase::OnBnClickedOpenTestcase()
{
	//=============================================================
	 //TODO: Add your control notification handler code here
	TCHAR szFilters[] = _T("data Files (*.cfg)|*.ini|All Files (*.*)|*.*||");
	CFileDialog fileDlg(TRUE, _T("cfg"), _T("*.cfg"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	if (m_pPlan->CountRunAdmin == 1) {
		CString defaulPath = m_pPlan->mTestCase.mPathInfo.DatabasePath;
		m_pPlan->CountRunAdmin++;
		fileDlg.m_ofn.lpstrInitialDir = defaulPath;
	}

	if (fileDlg.DoModal() == IDOK)
	{
		CString pathName = fileDlg.GetPathName();
		CString tmpStr;
		tmpStr.Format(_T("%s"), pathName);

		m_pCIniReader->setTestCaseFileName(tmpStr);
		m_pPlan->LoadTestCase(m_pCIniReader);
		m_pPlan->mTestCase.mPathInfo.FullPath = tmpStr;
		m_pPlan->OrderRun = 1;
		m_pPlan->InitMFCPath();

		//==================================================================
		LoadSometingInGUI();
		//=============================================================
		//========== CHECK file ========================================
		if (m_pPlan->Check_MapPinArr()) {
			MessageBox(_T("Trong dữ liệu thiết lập sai chân - kênh"), _T("Cảnh báo"));
			m_pPlan->New_PinGrid_GridHeader_GUIGridArr();
			m_pPlan->New_ChanelGridArr();
		}
		else {
			//if (m_pPlan->Check_ChanelSelectArr()) MessageBox(_T("Thiết lập sai lựa chọn kênh"), _T("Cảnh báo"));
			//if( m_pPlan->Check_ChanelConfigArr()) MessageBox(_T("Thiết lập sai thuộc tính kênh"), _T("Cảnh báo"));

			if (m_pPlan->Check_ChanelSelectArr()|| m_pPlan->Check_ChanelConfigArr()) {
				MessageBox(_T("Thiết lập sai lựa chọn/ thuộc tính kênh"), _T("Cảnh báo"));
				m_pPlan->Init_PinGrid_GridHeader_GUIGridArr();
				m_pPlan->New_ChanelGridArr();
			}
			else 
			{
				m_pPlan->Init_PinGrid_GridHeader_GUIGridArr();
				m_pPlan->Init_ChanelGridArr();
			}
		}
		//---------------------------
		CFile file;
		unsigned char bom[2];
		if (file.Open(tmpStr, CFile::modeRead)) {
			file.Read(bom, sizeof(bom));
			file.Close();
		}

		//if ((bom[0] != 255) || (bom[1] != 254)) 
		{
			CString pathName = m_pPlan->mTestCase.mPathInfo.FullPath;
			if (IsFileExists(pathName))	CFile::Remove(pathName);

			CFile file;
			if (file.Open(tmpStr, CFile::modeCreate | CFile::modeWrite)) {
				unsigned char utf16LEBOM[2] = { 0xFF, 0xFE };
				file.Write(utf16LEBOM, sizeof(utf16LEBOM));
				file.Close();
			}
			m_pPlan->SaveTestCase(m_pCIniReader, 0);
		}
		//---------------------------
			CWnd* pwnd = GetDlgItem(IDC_BTN_EDIT_TESTCASE);
			if (pwnd)
				pwnd->EnableWindow(true);
			pwnd = GetDlgItem(IDC_BTN_SAVE);
			if (pwnd)
				pwnd->EnableWindow(true);
			UpdateData(false);
		//-------------------------------
	}

}
//======================================

void DlgCreateCase::LoadDeviceBoardInfor() {
	JACK_INFO _JackInfo;
	std::vector<JACK_DEF> _JACKS;
	JACK_DEF _Jack;
	JACK_ROW_DEF _JackRow;
	PATHINFO_DEF _PathInfo;
	int _nJacks;
	int _pinSum = 0;
	CString strtmp;
	if (m_pPlan == NULL) return;
	m_TestCaseInfo = _T("\rThông tin bảng mạch:\r\n");
	_PathInfo = m_pPlan->mTestCase.mPathInfo;
	strtmp.Format(_T("Tên đài: %s \r\n"), _PathInfo.DeviceName);
	m_TestCaseInfo += strtmp;
	strtmp.Format(_T("Tên bảng mạch: %s \r\n"), _PathInfo.BoardName);
	m_TestCaseInfo += strtmp;

	_JackInfo = m_pPlan->mTestCase.mJackInfo;
	_JACKS = _JackInfo.mJACKS;
	_nJacks = _JACKS.size();
	strtmp.Format(_T("Số jack trên bảng mạch: %d \r\n"), _nJacks);
	m_TestCaseInfo += strtmp;

	strtmp.Format(_T("Vị trí Jack cắm:\r\n     %s \r\n"), sTringArr_IDJack[m_pPlan->mTestCase.mID_Jack]);
	m_TestCaseInfo += strtmp;


	for (int i = 0; i < _nJacks; i++) {
		_Jack = _JACKS.at(i);
		strtmp.Format(_T("Jack: %d \r\n"), i+1);
		m_TestCaseInfo += strtmp;
		strtmp.Format(_T("   Ký hiệu jắc: %s \r\n"), _Jack.JackSign, _Jack.JackName);
		m_TestCaseInfo += strtmp;
		strtmp.Format(_T("   Số hàng trong jắc: %d\r\n"), _Jack.nJackRows);
		m_TestCaseInfo += strtmp;
		for (int j = 0; j < _Jack.nJackRows; j++) {
			strtmp.Format(_T("   Hàng %s: %d chân\r\n"), _Jack.mJACK_ROW.at(j).JackRowSign, _Jack.mJACK_ROW.at(j).Pins);
			m_TestCaseInfo += strtmp;
			_pinSum += _Jack.mJACK_ROW.at(j).Pins;
		}
	}
	m_pPlan->mTestCase.mPins_Of_Board = _pinSum;
	strtmp.Format(_T("Tổng số chân: %d"),_pinSum);
	m_TestCaseInfo += strtmp;

	UpdateData(false);
}
void DlgCreateCase::LoadDeviceBoardPic() {
	PATHINFO_DEF* m_pPathInfo;
	m_pPathInfo = &m_pPlan->mTestCase.mPathInfo;
	CImage image;
	HRESULT result;
	//-----------------------------------------

	CString mPicDevicePathName = m_pPathInfo->DevicePicPath + _T("\\") + m_pPathInfo->DevicePicName;
	CString mPicBoardPathName = m_pPathInfo->BoardPath + _T("\\") + m_pPathInfo->BoardPicName;
	CString mPicBoardTestName = m_pPathInfo->TestPicPath + _T("\\") + m_pPathInfo->TestPicName;
	
	//----------------------------------------
	//result = image.Load(L"D:\\sodoketnoi.jpg");
	result = image.Load(mPicDevicePathName);
	if (SUCCEEDED(result))
	{

		CRect rect;
		GetDlgItem(IDC_STATIC_DEVICE_NAME)->GetClientRect(&rect);
		CDC* pDC = GetDlgItem(IDC_STATIC_DEVICE_NAME)->GetDC();
		image.Draw(pDC->m_hDC, rect);
	}
	//------------------------------------------
	result = image.Load(mPicBoardPathName);
	if (SUCCEEDED(result))
	{
		CRect rect;
		GetDlgItem(IDC_STATIC_BOARD_NAME)->GetClientRect(&rect);
		CDC* pDC = GetDlgItem(IDC_STATIC_BOARD_NAME)->GetDC();
		image.Draw(pDC->m_hDC, rect);
	}
	////------------------------------------------
}


void DlgCreateCase::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void DlgCreateCase::OnBnClickedBtnEditTestcase()
{
	// TODO: Add your control notification handler code here
	if (m_pPlan->OrderRun < 0) {
		MessageBox(_T("Cần phải mở hoặc tạo mới bài test trước khi thực hiện chức năng này!"), _T("Thông báo"));
		return;
	}
	DlgDeviceJack mDlgDeviceJack;
	mDlgDeviceJack.m_pPlan = this->m_pPlan;
	mDlgDeviceJack.DoModal();
	
	if (m_pPlan->Fix_nJack_nPin_nJacRow() != 0) {
		MessageBox(_T("Cấu trúc chân có sự thay đổi cấu trúc. Đã chỉnh lại xong"), _T("Thông báo"));
	}
	//---------------------------
	if (m_pPlan->Check_MapPinArr()) {
		MessageBox(_T("Trong dữ liệu thiết lập sai chân - kênh"), _T("Cảnh báo"));
		m_pPlan->New_PinGrid_GridHeader_GUIGridArr();
		m_pPlan->New_ChanelGridArr();
	}
	else {
		if (m_pPlan->Check_ChanelSelectArr()) MessageBox(_T("Thiết lập sai"), _T("Cảnh báo"));
		if (m_pPlan->Check_ChanelConfigArr()) MessageBox(_T("Thiết lập sai"), _T("Cảnh báo"));

		if (m_pPlan->Check_ChanelSelectArr() || m_pPlan->Check_ChanelConfigArr()) {
			MessageBox(_T("Thiết lập sai thuộc tính kênh"), _T("Cảnh báo"));
			m_pPlan->Init_PinGrid_GridHeader_GUIGridArr();
			m_pPlan->New_ChanelGridArr();
		}
		else
		{
			m_pPlan->Init_PinGrid_GridHeader_GUIGridArr();
			m_pPlan->Init_ChanelGridArr();
		}
	}
	//------------------------------------------
	LoadDeviceBoardInfor();

	//------------------------------
	// 
	// DUKK Nen kiem tra co sai khác thì moi NEW
	int isChanged = m_pPlan->CheckEditTestCaseChanged();
	if (isChanged) {
		// Fix changed
		m_pPlan->New_PinGrid_GridHeader_GUIGridArr();
		m_pPlan->New_ChanelGridArr();
	}
}
BOOL DlgCreateCase::IsFileExists(const CString& filePath) {
	CFileStatus fileStatus;
	return CFile::GetStatus(filePath, fileStatus);
}
//----------------------------------
void DlgCreateCase::OnBnClickedBtnSave()
{
	// TODO: Add your control notification handler code here
	if (m_pPlan->OrderRun < 0) {
		MessageBox(_T("Cần phải mở hoặc tạo mới bài test trước khi thực hiện chức năng này!"), _T("Thông báo"));
		return;
	}

	UpdateData(true);
	UpdateGUITodata();

	CString pathName = m_pPlan->mTestCase.mPathInfo.FullPath;
	if (IsFileExists(pathName))	CFile::Remove(pathName);
	CFile file;
	if (file.Open(pathName, CFile::modeCreate | CFile::modeWrite)) {
		unsigned char utf16LEBOM[2] = { 0xFF, 0xFE };
		file.Write(utf16LEBOM, sizeof(utf16LEBOM));
		file.Close();
	}

	CString tmpStr;
	tmpStr.Format(_T("%s"), pathName);
	m_pCIniReader->setTestCaseFileName(tmpStr);

	if(m_pPlan->SaveTestCase(m_pCIniReader, 0) == 1)
		MessageBox(_T("Ghi dữ liệu thành công!"), _T("Thông báo"));
	else
		MessageBox(_T("Ghi dữ liệu không thành công!"), _T("Thông báo"));

}
