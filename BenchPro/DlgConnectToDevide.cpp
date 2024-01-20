// DlgConnectToDevide.cpp : implementation file
//

#include "afxwin.h"
#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgConnectToDevide.h"
#include "DlgConnectToDevideAdd.h"
#include "DlgConnectToDevideConnect.h"
#include "mta_io_client.hpp"

// DlgConnectToDevide dialog

IMPLEMENT_DYNAMIC(DlgConnectToDevide, CDialogEx)

DlgConnectToDevide::DlgConnectToDevide(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONNECT, pParent)
	, m_Status_Connect(_T(""))
{
	m_pCIniReader = NULL;
}

DlgConnectToDevide::~DlgConnectToDevide()
{
}

void DlgConnectToDevide::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CONNECT, m_ListConnect);
	DDX_Text(pDX, IDC_EDIT_STATUS_CONNECT, m_Status_Connect);
}


BEGIN_MESSAGE_MAP(DlgConnectToDevide, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &DlgConnectToDevide::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &DlgConnectToDevide::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_VERIFY, &DlgConnectToDevide::OnBnClickedButtonVerify)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &DlgConnectToDevide::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDOK, &DlgConnectToDevide::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgConnectToDevide::OnBnClickedCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CONNECT, &DlgConnectToDevide::OnLvnItemchangedListConnect)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CONNECT, &DlgConnectToDevide::OnNMDblclkListConnect)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CONNECT, &DlgConnectToDevide::OnNMClickListConnect)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CONNECT, &DlgConnectToDevide::OnNMRClickListConnect)
END_MESSAGE_MAP()


// DlgConnectToDevide message handlers


BOOL DlgConnectToDevide::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HIMAGELIST hList = ImageList_Create(16, 16, ILC_COLOR4, 2, 1);
	m_cImageListNormal.Attach(hList);
	CBitmap cBmp;
	cBmp.LoadBitmap(IDB_BITMAP_SELECT);
	m_cImageListNormal.Add(&cBmp, RGB(0, 0, 0));
	cBmp.DeleteObject();

	m_ListConnect.SetImageList(&m_cImageListNormal, LVSIL_SMALL);


	m_ListConnect.SetExtendedStyle(m_ListConnect.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	//// TODO:  Add extra initialization here
	m_ListConnect.InsertColumn(0, _T("Chọn"), LVCFMT_LEFT, 50);
	m_ListConnect.InsertColumn(1, _T("Địa chỉ kết nối"), LVCFMT_LEFT, 200);
	m_ListConnect.InsertColumn(2, _T("Cổng thiết bị"), LVCFMT_LEFT, 90);
	m_ListConnect.InsertColumn(3, _T("Cổng máy kết nối"), LVCFMT_LEFT, 90);
	Restore();

	CEdit* pEditCtrl;
	pEditCtrl = (CEdit*)GetDlgItem(IDC_EDIT_STATUS_CONNECT);
	pEditCtrl->SetFont(p_nfont);

	return TRUE;  // return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}
void DlgConnectToDevide::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	DlgConnectToDevideAdd mDlgConnectToDevideAdd;
	if (mDlgConnectToDevideAdd.DoModal() == IDOK)
	{
		CString devideStr;
		devideStr.Format(_T("%d.%d.%d.%d"), mDlgConnectToDevideAdd.m_FieldIPDevide[0], mDlgConnectToDevideAdd.m_FieldIPDevide[1], mDlgConnectToDevideAdd.m_FieldIPDevide[2], mDlgConnectToDevideAdd.m_FieldIPDevide[3]);

		int Index = m_ListConnect.InsertItem(LVIF_IMAGE, m_ListConnect.GetItemCount(), _T(""), 0, 0, 0, NULL);
		m_ListConnect.SetItem(Index, 1, LVIF_TEXT, devideStr, 0, 0, 0, NULL);

		devideStr.Format(_T("%d"), mDlgConnectToDevideAdd.m_DevidePort);
		m_ListConnect.SetItem(Index, 2, LVIF_TEXT, devideStr, 0, 0, 0, NULL);

		devideStr.Format(_T("%d"), mDlgConnectToDevideAdd.m_LocalPort);
		m_ListConnect.SetItem(Index, 3, LVIF_TEXT, devideStr, 0, 0, 0, NULL);

		//devideStr.Format(_T("%s"), mDlgConnectToDevideAdd.m_DevideName);
		//m_ListConnect.SetItem(Index, 0, LVIF_TEXT, devideStr, 0, 0, 0, NULL);

		m_ListConnect.SetItemState(-1, 0, LVIS_SELECTED);
		m_ListConnect.SetItemState(Index, LVIS_SELECTED, LVIS_SELECTED);
		m_ListConnect.SetFocus();

		Save();
	}
}


void DlgConnectToDevide::OnBnClickedButtonEdit()
{
	// TODO: Add your control notification handler code here
	int nSelCount = m_ListConnect.GetSelectedCount();
	if (nSelCount)
	{
		CString str;
		// Create and int array to store the indexes and initialze 
		// with the indexes of selected items
		POSITION pos = m_ListConnect.GetFirstSelectedItemPosition();
		while (pos)
		{
			int nSelected = m_ListConnect.GetNextSelectedItem(pos);
			DlgConnectToDevideAdd mDlgConnectToDevideAdd;
			// Do something with item nSelected
			//str = m_ListConnect.GetItemText(nSelected, 0);
			//swscanf_s(str.LockBuffer(), _T("%s"), &(mDlgConnectToDevideAdd.m_DevideName));

			str = m_ListConnect.GetItemText(nSelected, 1);
			swscanf_s(str.LockBuffer(), _T("%d.%d.%d.%d"), &(mDlgConnectToDevideAdd.m_FieldIPDevide[0]), &(mDlgConnectToDevideAdd.m_FieldIPDevide[1]), &(mDlgConnectToDevideAdd.m_FieldIPDevide[2]), &(mDlgConnectToDevideAdd.m_FieldIPDevide[3]));
			
			str = m_ListConnect.GetItemText(nSelected, 2);
			swscanf_s(str.LockBuffer(), _T("%d"), &(mDlgConnectToDevideAdd.m_DevidePort));

			str = m_ListConnect.GetItemText(nSelected, 3);
			swscanf_s(str.LockBuffer(), _T("%d"), &(mDlgConnectToDevideAdd.m_LocalPort));
			
			//mDlgConnectToDevideAdd.SetIPAdress();
			if (mDlgConnectToDevideAdd.DoModal() == IDOK)
			{
				str.Format(_T("%d.%d.%d.%d"), mDlgConnectToDevideAdd.m_FieldIPDevide[0], mDlgConnectToDevideAdd.m_FieldIPDevide[1], mDlgConnectToDevideAdd.m_FieldIPDevide[2], mDlgConnectToDevideAdd.m_FieldIPDevide[3]);
				m_ListConnect.SetItemText(nSelected, 1, str);
				str.Format(_T("%d"), mDlgConnectToDevideAdd.m_DevidePort);
				m_ListConnect.SetItemText(nSelected, 2, str);
				str.Format(_T("%d"), mDlgConnectToDevideAdd.m_LocalPort);
				m_ListConnect.SetItemText(nSelected, 3, str);
				m_ListConnect.SetFocus();

			}
		}
		Save();
	}
}


void DlgConnectToDevide::OnBnClickedButtonVerify()
{
	// TODO: Add your control notification handler code here
	int nSelCount = m_ListConnect.GetSelectedCount();
	if (nSelCount)
	{
		CString str, str1;
		// Create and int array to store the indexes and initialze 
		// with the indexes of selected items
		int nSelected = -1;
		POSITION pos = m_ListConnect.GetFirstSelectedItemPosition();
		while (pos)
		{
			//DlgConnectToDevideConnect  mDlgConnectToDevideConnect;
			int nSelected = m_ListConnect.GetNextSelectedItem(pos);
			str = m_ListConnect.GetItemText(nSelected, 1);
			str1.Format(_T("http://%s:10001"),str);
			//mDlgConnectToDevideConnect.m_strConnect = str1;
			//mDlgConnectToDevideConnect.m_nTimeOut = 2000;
			//mDlgConnectToDevideConnect.pFlagConnected = pFlagConnected;
			//if (mDlgConnectToDevideConnect.DoModal() == IDOK)
			//{

			//}
			//----------------------------------------------
			CT2A ascii(str1, CP_UTF8);
			int nRet = set_baseUrl(ascii.m_psz, 2000);
			CString strPort;
						
			if (nRet == 0) {
				*pPubstrAdrressConn = str1;
				strPort = _T("Hệ thống sẵn sàng!");
			}
			else strPort = _T("Kết nối không thành công");
			m_Status_Connect = strPort;
			UpdateData(false);

			//*pFlagConnected = 1 + nRet;
			if (nRet == 0)
			{
				*pFlagConnected = OK;
			}
			else  *pFlagConnected = ERR;
			//----------------------------------------------
		}
		
	}
}


void DlgConnectToDevide::OnBnClickedButtonRemove()
{
	// TODO: Add your control notification handler code here
	int nSelCount = m_ListConnect.GetSelectedCount();
	if (nSelCount)
	{
		POSITION pos = m_ListConnect.GetFirstSelectedItemPosition();
		while (pos)
		{
			int nSelected = m_ListConnect.GetNextSelectedItem(pos);
			m_ListConnect.DeleteItem(nSelected);
			m_ListConnect.UpdateData();
			nSelected = m_ListConnect.GetItemCount();
			if (nSelected > 0)
			{
				m_ListConnect.SetItemState(-1, 0, LVIS_SELECTED);
				m_ListConnect.SetItemState(nSelected - 1, LVIS_SELECTED, LVIS_SELECTED);
				m_ListConnect.SetFocus();
			}
		}
		Save();
	}
}


void DlgConnectToDevide::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	Save();
	CDialogEx::OnOK();
}


void DlgConnectToDevide::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

bool DlgConnectToDevide::Save()
{
	if (m_pCIniReader == NULL)
		return false;
	CString strSection = _T("Address connect");
	CString strValue, strKey;
	m_pCIniReader->removeSection(strSection);
	int nItems = m_ListConnect.GetItemCount();
	strValue.Format(_T("%d"), nItems);
	strKey = _T("NumItems");
	m_pCIniReader->setKey(strValue, strKey, strSection);

	int nSelected = 0;
	LVITEM lvItem = { 0 };
	lvItem.mask = LVIF_IMAGE;
	lvItem.iSubItem = 0;         // column index
	for (int i = 0; i < m_ListConnect.GetItemCount(); i++)
	{
		lvItem.iItem = i;        // item index 
		m_ListConnect.GetItem(&lvItem);
		if (lvItem.iImage == 1)
		{
			nSelected = i;
			break;
		}
	}
	strKey = _T("SelectItem");
	strValue.Format(_T("%d"), nSelected);
	m_pCIniReader->setKey(strValue, strKey, strSection);

	for (int i = 0; i < nItems; i++)
	{
		strKey.Format(_T("Item_%d"), i);
		strValue = m_ListConnect.GetItemText(i, 1) + _T(";") + m_ListConnect.GetItemText(i, 2) + _T(";") + m_ListConnect.GetItemText(i, 3);
		m_pCIniReader->setKey(strValue, strKey, strSection);
	}
	return true;
}
bool DlgConnectToDevide::Restore()
{
	if (m_pCIniReader == NULL)
		return false;
	CString strSection = _T("Address connect");
	CString strValue, strKey;
	int nItems = 0;
	strKey = _T("NumItems");
	strValue = m_pCIniReader->getKeyValue(strKey, strSection);
	if (strValue.IsEmpty())
		return false;
	if (swscanf_s(strValue.LockBuffer(), _T("%d"), &(nItems)) != 1)
		return false;
	int nSelected = -1;
	strKey = _T("SelectItem");
	strValue = m_pCIniReader->getKeyValue(strKey, strSection);
	if (strValue.IsEmpty())
		return false;
	if (swscanf_s(strValue.LockBuffer(), _T("%d"), &(nSelected)) != 1)
		return false;
	int nSplit[2] = { -1 };
	int Index;
	LVITEM lvi;
	for (int i = 0; i < nItems; i++)
	{
		strKey.Format(_T("Item_%d"), i);
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.IsEmpty())
			continue;
		nSplit[0] = strValue.Find(_T(';'), 0);
		if (nSplit[0] != -1)
			nSplit[1] = strValue.Find(_T(';'), nSplit[0] + 1);
		else
			continue;
		if (nSplit[1] == -1)
			continue;
		int Index = m_ListConnect.InsertItem(LVIF_IMAGE, m_ListConnect.GetItemCount(), _T(""), 0, 0, 0, NULL);
		m_ListConnect.SetItemText(Index, 1, strValue.Mid(0, nSplit[0]));

		m_ListConnect.SetItemText(Index, 2, strValue.Mid(nSplit[0] + 1, nSplit[1] - nSplit[0] - 1));
		m_ListConnect.SetItemText(Index, 3, strValue.Mid(nSplit[1] + 1, strValue.GetLength() - nSplit[1] - 1));
	}

	if (m_ListConnect.GetItemCount() > 0 && nSelected != -1)
	{
		m_ListConnect.SetItemState(-1, 0, LVIS_SELECTED);
		m_ListConnect.SetItemState(nSelected, LVIS_SELECTED, LVIS_SELECTED);

		LVITEM lvItem = { 0 };
		lvItem.mask = LVIF_IMAGE;
		lvItem.iSubItem = 0;         // column index
		lvItem.iItem = nSelected;        // item index 
		m_ListConnect.GetItem(&lvItem);
		lvItem.iImage = 1;
		m_ListConnect.SetItem(&lvItem);

		m_ListConnect.SetFocus();
	}
	return true;
}


void DlgConnectToDevide::OnLvnItemchangedListConnect(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void DlgConnectToDevide::OnNMDblclkListConnect(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE pitem = (LPNMITEMACTIVATE)pNMHDR;

	int row = pitem->iItem;
	int column = pitem->iSubItem;

	LVITEM lvItem = { 0 };
	lvItem.mask = LVIF_IMAGE;
	lvItem.iSubItem = 0;         // column index
	for (int i = 0; i < m_ListConnect.GetItemCount(); i++)
	{
		lvItem.iItem = i;        // item index 
		m_ListConnect.GetItem(&lvItem);
		if (i == row)
			lvItem.iImage = 1;
		else
			lvItem.iImage = 0;
		m_ListConnect.SetItem(&lvItem);
	}
	*pResult = 0;
}


void DlgConnectToDevide::OnNMClickListConnect(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE pitem = (LPNMITEMACTIVATE)pNMHDR;

	int row = pitem->iItem;
	int column = pitem->iSubItem;

	LVITEM lvItem = { 0 };
	lvItem.mask = LVIF_IMAGE;
	lvItem.iSubItem = 0;         // column index
	for (int i = 0; i < m_ListConnect.GetItemCount(); i++)
	{
		lvItem.iItem = i;        // item index 
		m_ListConnect.GetItem(&lvItem);
		if (i == row)
			lvItem.iImage = 1;
		else
			lvItem.iImage = 0;
		m_ListConnect.SetItem(&lvItem);
	}
	*pResult = 0;
}




void DlgConnectToDevide::OnNMRClickListConnect(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE pitem = (LPNMITEMACTIVATE)pNMHDR;

	int row = pitem->iItem;
	int column = pitem->iSubItem;

	LVITEM lvItem = { 0 };
	lvItem.mask = LVIF_IMAGE;
	lvItem.iSubItem = 0;         // column index
	for (int i = 0; i < m_ListConnect.GetItemCount(); i++)
	{
		lvItem.iItem = i;        // item index 
		m_ListConnect.GetItem(&lvItem);
		if (i == row)
			lvItem.iImage = 1;
		else
			lvItem.iImage = 0;
		m_ListConnect.SetItem(&lvItem);
	}
	*pResult = 0;
}
