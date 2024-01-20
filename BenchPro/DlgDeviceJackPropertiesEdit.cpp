// DlgDeviceJackPropertiesEdit.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgDeviceJackPropertiesEdit.h"


// DlgDeviceJackPropertiesEdit dialog

IMPLEMENT_DYNAMIC(DlgDeviceJackPropertiesEdit, CDialogEx)

DlgDeviceJackPropertiesEdit::DlgDeviceJackPropertiesEdit(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEVICE_JACK_PROPERTIES_EDIT, pParent)
	, m_nPinPerRow(_T("1"))
{

}

DlgDeviceJackPropertiesEdit::~DlgDeviceJackPropertiesEdit()
{
}

void DlgDeviceJackPropertiesEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NPIN, m_nPinPerRow);
}


BEGIN_MESSAGE_MAP(DlgDeviceJackPropertiesEdit, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgDeviceJackPropertiesEdit::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgDeviceJackPropertiesEdit::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgDeviceJackPropertiesEdit message handlers


void DlgDeviceJackPropertiesEdit::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void DlgDeviceJackPropertiesEdit::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
