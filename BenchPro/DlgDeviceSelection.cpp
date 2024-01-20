// DlgDeviceSelection.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgDeviceSelection.h"


// DlgDeviceSelection dialog

IMPLEMENT_DYNAMIC(DlgDeviceSelection, CDialogEx)

DlgDeviceSelection::DlgDeviceSelection(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEVICE_SELECT, pParent)
{

}

DlgDeviceSelection::~DlgDeviceSelection()
{
}

void DlgDeviceSelection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEVICE_LIST, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(DlgDeviceSelection, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SELECTION, &DlgDeviceSelection::OnBnClickedBtnSelection)
	ON_BN_CLICKED(IDOK, &DlgDeviceSelection::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgDeviceSelection::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgDeviceSelection message handlersiuoiuo


void DlgDeviceSelection::OnBnClickedBtnSelection()
{
	// TODO: Add your control notification handler code here
}


void DlgDeviceSelection::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void DlgDeviceSelection::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
