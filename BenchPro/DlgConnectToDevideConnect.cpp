// DlgConnectToDevideConnect.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgConnectToDevideConnect.h"
#include "mta_io_client.hpp"


// DlgConnectToDevideConnect dialog

IMPLEMENT_DYNAMIC(DlgConnectToDevideConnect, CDialogEx)

DlgConnectToDevideConnect::DlgConnectToDevideConnect(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONNECT_DEVIDECONNCET, pParent)
{

}

DlgConnectToDevideConnect::~DlgConnectToDevideConnect()
{
}

void DlgConnectToDevideConnect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_Log);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strConnect);
	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_nTimeOut);
	DDV_MinMaxUInt(pDX, m_nTimeOut, 1, 10000);
}


BEGIN_MESSAGE_MAP(DlgConnectToDevideConnect, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgConnectToDevideConnect::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgConnectToDevideConnect::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgConnectToDevideConnect message handlers


void DlgConnectToDevideConnect::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_Log = _T("Đang thực hiện kết nối xuống thiết bị ...");
	UpdateData(false);

	CT2A ascii(m_strConnect, CP_UTF8);
	int nRet = set_baseUrl(ascii.m_psz, m_nTimeOut);
	CString strPort;
	m_Log = _T("");
	m_Log += _T("\r\nset_baseUrl:\r\n") + m_strConnect;
	strPort.Format(_T("\r\nTimeout:%d"), m_nTimeOut);
	m_Log += strPort;
	m_Log += _T("\r\nReturn:");
	strPort.Format(_T("%d"), nRet);;
	m_Log += strPort;

	if (nRet == 0) m_Log += _T("\r\n-----\r\nKết nối thành công!");
	else m_Log += _T("\r\n-----\r\nKết nối có lỗi");
	UpdateData(false);

	//*pFlagConnected = 1 + nRet;
	if (nRet == 0) 
	{
		
		*pFlagConnected = 1;
	} 
	else  *pFlagConnected  = 0;
}


void DlgConnectToDevideConnect::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
