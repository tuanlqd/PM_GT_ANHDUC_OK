// DlgConnectToDevideAdd.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgConnectToDevideAdd.h"


// DlgConnectToDevideAdd dialog

IMPLEMENT_DYNAMIC(DlgConnectToDevideAdd, CDialogEx)

DlgConnectToDevideAdd::DlgConnectToDevideAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONNECT_ADD, pParent)
	, m_DevideName(_T("Devide ..")), m_DevidePort(33004), m_LocalPort(33001)
{
	m_FieldIPDevide[0] = 192;
	m_FieldIPDevide[1] = 168;
	m_FieldIPDevide[2] = 1;
	m_FieldIPDevide[3] = 125;

}

DlgConnectToDevideAdd::~DlgConnectToDevideAdd()
{
}

void DlgConnectToDevideAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEVIDE_NAME, m_DevideName);
	DDX_Control(pDX, IDC_IPADDRESS_DEVIDE, m_IPDevide);
	DDX_Text(pDX, IDC_EDIT_DEVIDE_PORT, m_DevidePort);
	DDV_MinMaxUInt(pDX, m_DevidePort, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_LOCAL_PORT, m_LocalPort);
	DDV_MinMaxUInt(pDX, m_LocalPort, 1, 65535);
}


BEGIN_MESSAGE_MAP(DlgConnectToDevideAdd, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgConnectToDevideAdd::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgConnectToDevideAdd::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgConnectToDevideAdd message handlers


void DlgConnectToDevideAdd::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	this->UpdateData();
	if (m_DevideName.IsEmpty() || m_IPDevide.IsBlank() || m_DevidePort == 0 || m_LocalPort == 0)
		this->OnCancel();
	m_IPDevide.GetAddress(m_FieldIPDevide[0], m_FieldIPDevide[1], m_FieldIPDevide[2], m_FieldIPDevide[3]);
	CDialogEx::OnOK();
}


void DlgConnectToDevideAdd::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

BOOL DlgConnectToDevideAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_IPDevide.SetAddress(m_FieldIPDevide[0], m_FieldIPDevide[1], m_FieldIPDevide[2], m_FieldIPDevide[3]);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}