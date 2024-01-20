// CInputDialog.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "CInputDialog.h"


// CInputDialog dialog

IMPLEMENT_DYNAMIC(CInputDialog, CDialogEx)

CInputDialog::CInputDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIAG_PASSWORD, pParent)
	, m_Edit_Password(_T(""))
{

}

CInputDialog::~CInputDialog()
{
}

void CInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_Edit_Password);
}


BEGIN_MESSAGE_MAP(CInputDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInputDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CInputDialog message handlers


void CInputDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_Edit_Password == _T("admin")) 
		CDialogEx::OnOK();
	else CDialogEx::OnCancel();
}


void CInputDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
