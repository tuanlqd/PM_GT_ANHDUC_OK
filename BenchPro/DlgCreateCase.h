#pragma once
#include "afxdialogex.h"
#include "INI.h"
#include "Plan.h"


// DlgCreateCase dialog

class DlgCreateCase : public CDialogEx
{
	DECLARE_DYNAMIC(DlgCreateCase)

public:
	DlgCreateCase(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgCreateCase();

	CIniReader*		  m_pCIniReader;
	CPlan*			  m_pPlan;
	CFont* m_sfont;
	CFont* m_bfont;
	CFont* m_tfont;
	//int m_flagEdit = 0;
	// 	
	CString sTringArr_IDJack[9] = { _T("0-Jack mở rộng bên ngoài"),
									_T("1-J6_ГРПМ9 - 31 / 62ГC2 - В"),
									_T("2-J5_ГРПМ1 - 61ГО2 - В"),
									_T("3-J4_ГРПМ1 - 31ГО2 - В"),
									_T("4-J1_C09032646825"),
									_T("5-JA3_СНП34С - 46В - 21 - В"),
									_T("6-JA5_СНП34С - 90В - 21 - В"),
									_T("7-JA2_СНП34С - 135В - 21 - В"),
									_T("8-JA4_JA1_СНП34С - 90В_135B - 21 - В")};
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CREATE_TESTCASE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString s_SubTitle = _T("Hệ thống kiểm tra bảng mạch");
	CString s_MainTitle = _T("THIẾT LẬP THÔNG TIN CẤU HÌNH CHÂN CHO BẢNG MẠCH");
	CString s_TenDai = _T("Tên đài");
	CString s_TenBomach = _T("Tên bảng mạch");
	CString s_BaiKT = _T("Bài kiểm tra");
	CString s_OpenfileCauHinh = _T("Mở file thiết lập bảng mạch");
	CString s_TLChanJack = _T("Thiết lập chân, jắc bảng mạch");
	CString s_GhiCauHinh = _T("Ghi cấu hình");
	CString s_Thoat = _T("Thoát");
	CString m_DeviceName;
	CString m_BoardName;
	CString m_TestName;
	
	CString m_TestCaseInfo;

	CStatic m_BMP_DEVICE_NAME;
	CStatic m_BMP_BOARD_NAME;

	afx_msg BOOL OnInitDialog();

	afx_msg void OnBnClickedOpenTestcase();
	afx_msg void OnBnClickedOk();

	afx_msg void UpdatedataToGUI();
	afx_msg void UpdateGUITodata();
	afx_msg void LoadSometingInGUI();

	afx_msg void LoadDeviceBoardPic();
	afx_msg void LoadDeviceBoardInfor();
	afx_msg void OnBnClickedBtnEditTestcase();

	afx_msg void OnBnClickedBtnSave();
	afx_msg void ReadExcelData();
	afx_msg BOOL IsFileExists(const CString& filePath);
	afx_msg void ReadExcelFile(const CString& filePath);
	
};
