// DlgDeviceProperties.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgDeviceProperties.h"
#include "DlgDeviceJack.h"


// DlgDeviceProperties dialog

IMPLEMENT_DYNAMIC(DlgDeviceProperties, CDialogEx)

DlgDeviceProperties::DlgDeviceProperties(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEVICE_PROPERTIES, pParent),
	m_DeviceName(_T("Test ...")), m_Chanel(84), m_PWP(5), m_PWN(3)
{

}

DlgDeviceProperties::~DlgDeviceProperties()
{
}

void DlgDeviceProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_DeviceName);
	DDX_Text(pDX, IDC_EDIT_CHANEL, m_Chanel);
	DDV_MinMaxUInt(pDX, m_Chanel, 1, 200);
	DDX_Text(pDX, IDC_EDIT_PWP, m_PWP);
	DDV_MinMaxUInt(pDX, m_PWP, 1, 5);
	DDX_Text(pDX, IDC_EDIT_PWN, m_PWN);
	DDV_MinMaxUInt(pDX, m_PWN, 1, 3);
}


BEGIN_MESSAGE_MAP(DlgDeviceProperties, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgDeviceProperties::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgDeviceProperties message handlers

// Truy van data
//bool DlgDeviceProperties::ExitName(CString DeviceName)
//{
//	//-----------------------
//	if (m_pCIniReader == NULL)
//		return false;
//	CString strSection = _T("Device list");
//	CString strValue, strKey;
//	int nItems = 0;
//	strKey = _T("NumItems");
//	strValue = m_pCIniReader->getKeyValue(strKey, strSection);
//	if (strValue.IsEmpty()) return false;
//
//	swscanf_s(strValue.LockBuffer(), _T("%d"), &(nItems));
//	int nSplit =  -1 ;
//
//	for (int i = 0; i < nItems; i++)
//	{
//		strKey.Format(_T("Item_%d"), i);
//		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
//		if (strValue.IsEmpty()) continue;
//
//		nSplit = strValue.Find(_T(';'), 0);
//		if (nSplit == -1) continue;
//
//		CString tempItem = strValue.Mid(0, nSplit);
//		tempItem.MakeUpper();
//		CString tempDeviceName = DeviceName;
//		tempDeviceName.MakeUpper();
//
//		int nTemp = tempItem.GetLength();
//		int nDeviceName = DeviceName.GetLength();
//		if (nTemp != nDeviceName) continue;
//
//		int j;
//		for (j = 0; j < nTemp; j++)
//			if (tempItem[j] != tempDeviceName[j])
//				j = nTemp + 2;
//
//		if(j == nTemp) return true;
//	}
//
//	return false;
//
//}

bool DlgDeviceProperties::ExistName(CString DeviceName)
{
	int nItems = (*m_ListCtrl).GetItemCount();
	if (nItems == 0) return false;

	for (int i = 0; i < nItems; i++)
	{
		CString tempItem = (*m_ListCtrl).GetItemText(i, 1);
		tempItem.MakeUpper();
		CString tempDeviceName = DeviceName;
		tempDeviceName.MakeUpper();

		int nTemp = tempItem.GetLength();
		int nDeviceName = DeviceName.GetLength();
		if (nTemp != nDeviceName) continue;

		int j;
		for (j = 0; j < nTemp; j++)
			if (tempItem[j] != tempDeviceName[j])
				j = nTemp + 2;

		if (j == nTemp) return true;
	}

	return false;
}

void DlgDeviceProperties::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	UpdateData();

	if (m_DeviceName.IsEmpty()) MessageBox(_T("Device name is not empty"), _T("Message"));
	else 
	{
		if (m_CheckNameExist && ExistName(m_DeviceName)) MessageBox(_T("Device name is realy exit"), _T("Message"));
		else
		{

			if ((!m_DeviceName.IsEmpty())
				&& (m_Chanel > 0) && (m_Chanel <= 200)
				&& (m_PWP > 0) && (m_PWP <= 5)
				&& (m_PWN > 0) && (m_PWN <= 3))
			{
				
				DlgDeviceJack mDlgDeviceJack;
				//DUKKKK
				//mDlgDeviceJack.m_pCIniReader = this->m_pCIniReader;
				CString str;
				//mDlgDeviceJack.m_DeviceName.Format(_T("%s"), this->m_DeviceName);

				if (mDlgDeviceJack.DoModal() == IDOK)
				{

				}

				CDialogEx::OnOK();
			}
		}
	}

}
