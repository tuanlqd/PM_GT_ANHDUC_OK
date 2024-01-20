#pragma once
#include "afxdialogex.h"
#include "INI.h"
#include "Plan.h"

// DlgTestOnBoard dialog

class DlgTestOnBoard : public CDialogEx
{
	DECLARE_DYNAMIC(DlgTestOnBoard)

public:
	DlgTestOnBoard(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgTestOnBoard();
	CString s_SubTitle = _T("Hệ thống kiểm tra bảng mạch");
	CString s_MainTitle = _T("THIẾT LẬP VÀ KIỂM TRA BẢNG MẠCH");
	CString s_KTketnoi = _T("Kiểm tra kết nối thiết bị");
	CString s_TLThanSoThietBi = _T("Thiết lập tham số thiết bị");
	CString s_TLDinhTuyenVaThamSoTinHieu = _T("Thiết lập định tuyến và tham số tín hiệu");
	CString s_NguonCap = _T("Cấp nguồn cho bảng mạch kiểm tra");
	CString s_ChayKiemTraCN = _T("Chạy kiểm tra chức năng");
	CString s_XoaDinhTuyen = _T("Xóa định tuyến");
	CString s_Thoat = _T("Thoát");
	CString s_NguoiKT = _T("Người kiểm tra:");
	//-------------------------------------------
	SocketTCP* SocketTh;
	int* pFlagThRun;

	CIniReader* m_pCIniReader;
	CPlan* m_pCPlan;
	int flagOpen;
	int *pFlagThConnected;
	int* pFlagConnected;
	int* p_mode;
	int m_User;  // User = 1, admin = 0;
	CFont* m_sfont;
	CFont* m_bfont;
	CFont* m_tfont;
	CFont* m_nfont;
	CString* pPubstrAdrressConn;

	/*int StatusConnect;*/    // TUAN; chuyen sang khai bao o plan.h
	CProgressCtrl m_ProgressCtrl;
	UINT_PTR m_timer;
	int m_nProgressValue;

	CString m_Username;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_TESTONBOARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL IsFileExists(const CString& filePath);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnPowerSetting();
	afx_msg void OnBnClickedBtnReconnect();
	afx_msg void OnBnClickedBtnPowerThreshol();
	afx_msg void OnBnClickedBtnPinselect();
	afx_msg int OpenTestCase();

	CButton m_BtnSendThanh;
	afx_msg void OnBnClickedBtnKtCn();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnResetPath();
	
	afx_msg void OnBnClickedBtnExit2();
};
