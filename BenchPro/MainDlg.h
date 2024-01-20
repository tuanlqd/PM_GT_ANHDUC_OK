#pragma once
#include "afxdialogex.h"

//
#include "INI.h"
#include "Plan.h"
// MainDlg dialog

class MainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MainDlg)

public:
	MainDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MainDlg();
	CString s_SubTitle = _T("Hệ thống kiểm tra bảng mạch");
	CString s_MainTitle = _T("TẠO VÀ THỬ NGHIỆM BÀI KIỂM TRA");
	CString s_KTketnoi = _T("Kiểm tra kết nối thiết bị");
	CString s_TLThongTinBoard = _T("Thiết lập thông tin bảng mạch");
	CString s_TLBaoVeNguon = _T("Thiết lập bảo vệ nguồn cho thiết bị");
	CString s_TLNguonCap = _T("Thiết lập các nguồn cấp cho bảng mạch");
	CString s_TLKetNoiChan = _T("Thiết lập kết nối chân tín hiệu");
	CString s_TLThuocTinhChan = _T("Thiết lập thuộc tính chân tín hiệu");
	CString s_TLThamsoTinHieuVaKenhMoRong = _T("Thiết lập tham số tín hiệu và kênh mở rộng");
	CString	s_TaoDLCauHinh = _T("Tạo dữ liệu cấu hình");
	CString	s_ChayKT = _T("Chạy kiểm tra");
	CString s_Thoat = _T("Thoát");
	CString s_NguoiKT = _T("Người thiết lập:");
	//-------------------------------------------
	CString bmess = _T("Cần phải mở hoặc tạo mới bài test trước khi thực hiện chức năng này!");
	CString tmess = _T("Thông báo");
	CString wmess = _T("Chú ý!");

	// Operations
	SocketTCP* SocketTh;
	SocketTCP* SocketPh;
	int *m_pFlagPhRun;
	int *m_pFlagThRun;

	int *pFlagThConnected;
	int* pFlagConnected;
	int* p_mode;
// Dialog Data
	CIniReader		 *m_pCIniReader;
	CPlan			  *m_pCPlan;

	CString m_Username;
	CFont* m_ssfont;
	CFont* m_sfont;
	CFont* m_bfont;
	CFont* m_tfont;
	CFont* m_nfont;
	CString* pPubstrAdrressConn;
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGMAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnCreatecase();
	afx_msg void OnBnClickedBtnPowersetting();
	afx_msg void OnBnClickedBtnPowerthreshol();
	afx_msg void OnBnClickedBtnExtraSetting();
	afx_msg void OnBnClickedBtnPinSetting();
	afx_msg void OnBnClickedBtnPinSelection();
	afx_msg void OnBnClickedBtnCreateDataTestcase();
	afx_msg void OnBnClickedBtnRunasuser();
	afx_msg void OnEnChangeEditVer();
};
