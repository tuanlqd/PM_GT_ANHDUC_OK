// DlgConnectToDevide.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgConnectToDevide.h"


// DlgConnectToDevide dialog

IMPLEMENT_DYNAMIC(DlgConnectToDevide, CDialog)

DlgConnectToDevide::DlgConnectToDevide(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_CONNECT, pParent)
{

}

DlgConnectToDevide::~DlgConnectToDevide()
{
}

void DlgConnectToDevide::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgConnectToDevide, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &DlgConnectToDevide::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &DlgConnectToDevide::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_VERIFY, &DlgConnectToDevide::OnBnClickedButtonVerify)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &DlgConnectToDevide::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDOK, &DlgConnectToDevide::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgConnectToDevide::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgConnectToDevide message handlers


void DlgConnectToDevide::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
}


void DlgConnectToDevide::OnBnClickedButtonEdit()
{
	// TODO: Add your control notification handler code here
}


void DlgConnectToDevide::OnBnClickedButtonVerify()
{
	// TODO: Add your control notification handler code here
}


void DlgConnectToDevide::OnBnClickedButtonRemove()
{
	// TODO: Add your control notification handler code here
}


void DlgConnectToDevide::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


void DlgConnectToDevide::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
