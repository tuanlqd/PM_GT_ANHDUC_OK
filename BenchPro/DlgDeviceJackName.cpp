// DlgDeviceJackName.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgDeviceJackName.h"
#include "DlgDeviceJackProperties.h"


// DlgDeviceJackName dialog

IMPLEMENT_DYNAMIC(DlgDeviceJackName, CDialogEx)

DlgDeviceJackName::DlgDeviceJackName(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEVICE_JACK_NAME, pParent)
	, m_Symbol(_T(""))
	, m_JackName(_T(""))
	//, m_Jack_ID(_T(""))
{

}

DlgDeviceJackName::~DlgDeviceJackName()
{
}

void DlgDeviceJackName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SYMBOL, m_Symbol);
	DDX_Text(pDX, IDC_EDIT_JACK_NAME, m_JackName);
	//DDX_Text(pDX, IDC_EDIT_ID_JACK, m_Jack_ID);
}


BEGIN_MESSAGE_MAP(DlgDeviceJackName, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgDeviceJackName::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgDeviceJackName::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgDeviceJackName message handlers
BOOL DlgDeviceJackName::OnInitDialog() {
	m_Symbol_old = m_Symbol;
	UpdateData(FALSE);
return TRUE;  // return TRUE unless you set the focus to a control
// EXCEPTION: OCX Property Pages should return FALSE
}
void DlgDeviceJackName::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_Symbol.IsEmpty()) MessageBox(_T("Ký hiệu Jắc không được để trống"), _T("Thông báo"));
	else if (ExistName(m_Symbol)) MessageBox(_T("Ký hiệu jắc đã tồn tại, cần thay đổi"), _T("Thông báo"));
	else
	{
		if (!m_Symbol.IsEmpty())
		{
			CDialogEx::OnOK();
		}
	}

}


void DlgDeviceJackName::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

bool DlgDeviceJackName::ExistName(CString JackName)
{
	
	if(CheckName && (m_Symbol == m_Symbol_old)) return false;
	int nItems = (*m_ListCtrl).GetItemCount();
	if (nItems == 0) return false;

	for (int i = 0; i < nItems; i++)
	{
		CString tempItem = (*m_ListCtrl).GetItemText(i, 1);
		tempItem.MakeUpper();
		CString tempDeviceName = JackName;
		tempDeviceName.MakeUpper();

		int nTemp = tempItem.GetLength();
		int nDeviceName = JackName.GetLength();
		if (nTemp != nDeviceName) continue;

		int j;
		for (j = 0; j < nTemp; j++)
			if (tempItem[j] != tempDeviceName[j])
				j = nTemp + 2;

		if (j == nTemp) return true;
	}

	return false;
}