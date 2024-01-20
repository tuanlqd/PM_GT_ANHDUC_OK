// DlgDevideSetting.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgDevideSetting.h"
#include "DlgDeviceProperties.h"


// DlgDevideSetting dialog

IMPLEMENT_DYNAMIC(DlgDevideSetting, CDialogEx)

DlgDevideSetting::DlgDevideSetting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEVIDE_SETTING, pParent)
{

}

DlgDevideSetting::~DlgDevideSetting()
{
}

void DlgDevideSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEVIDE_LIST_CTRL, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(DlgDevideSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgDevideSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgDevideSetting::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &DlgDevideSetting::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &DlgDevideSetting::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &DlgDevideSetting::OnBnClickedButtonRemove)
	ON_NOTIFY(NM_CLICK, IDC_DEVIDE_LIST_CTRL, &DlgDevideSetting::OnNMClickDevideListCtrl)
	ON_NOTIFY(NM_RCLICK, IDC_DEVIDE_LIST_CTRL, &DlgDevideSetting::OnNMRClickDevideListCtrl)
END_MESSAGE_MAP()


// DlgDevideSetting message handlers
BOOL DlgDevideSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HIMAGELIST hList = ImageList_Create(16, 16, ILC_COLOR4, 2, 1);
	m_cImageListNormal.Attach(hList);
	CBitmap cBmp;
	cBmp.LoadBitmap(IDB_BITMAP_SELECT);
	m_cImageListNormal.Add(&cBmp, RGB(0, 0, 0));
	cBmp.DeleteObject();

	m_ListCtrl.SetImageList(&m_cImageListNormal, LVSIL_SMALL);


	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	//// TODO:  Add extra initialization here
	m_ListCtrl.InsertColumn(0, _T("Select"), LVCFMT_LEFT, 50);
	m_ListCtrl.InsertColumn(1, _T("Devide name"), LVCFMT_LEFT, 200);
	m_ListCtrl.InsertColumn(2, _T("nChanel"), LVCFMT_LEFT, 100);
	m_ListCtrl.InsertColumn(3, _T("nPositive"), LVCFMT_LEFT, 100);
	m_ListCtrl.InsertColumn(4, _T("nNegative"), LVCFMT_LEFT, 100);
	Restore();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void DlgDevideSetting::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	Save();
	CDialogEx::OnOK();
}


void DlgDevideSetting::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void DlgDevideSetting::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	DlgDeviceProperties mDlgDeviceProperties;
	mDlgDeviceProperties.m_pCIniReader = m_pCIniReader;
	mDlgDeviceProperties.m_ListCtrl = &(this->m_ListCtrl);
	mDlgDeviceProperties.m_CheckNameExist = 1;
	if (mDlgDeviceProperties.DoModal() == IDOK)
	{

		CString devideStr;
		devideStr.Format(_T("%s"), mDlgDeviceProperties.m_DeviceName);

		int Index = m_ListCtrl.InsertItem(LVIF_IMAGE, m_ListCtrl.GetItemCount(), _T(""), 0, 0, 0, NULL);
		m_ListCtrl.SetItem(Index, 1, LVIF_TEXT, devideStr, 0, 0, 0, NULL);

		devideStr.Format(_T("%d"), mDlgDeviceProperties.m_Chanel);
		m_ListCtrl.SetItem(Index, 2, LVIF_TEXT, devideStr, 0, 0, 0, NULL);

		devideStr.Format(_T("%d"), mDlgDeviceProperties.m_PWP);
		m_ListCtrl.SetItem(Index, 3, LVIF_TEXT, devideStr, 0, 0, 0, NULL);

		devideStr.Format(_T("%d"), mDlgDeviceProperties.m_PWN);
		m_ListCtrl.SetItem(Index, 4, LVIF_TEXT, devideStr, 0, 0, 0, NULL);

		m_ListCtrl.SetItemState(-1, 0, LVIS_SELECTED);
		m_ListCtrl.SetItemState(Index, LVIS_SELECTED, LVIS_SELECTED);
		m_ListCtrl.SetFocus();

		Save();
	}
}


void DlgDevideSetting::OnBnClickedButtonEdit()
{
	// TODO: Add your control notification handler code here
	int nSelCount = m_ListCtrl.GetSelectedCount();
	if (nSelCount)
	{
		CString str;
		// Create and int array to store the indexes and initialze 
		// with the indexes of selected items
		POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
		while (pos)
		{
			int nSelected = m_ListCtrl.GetNextSelectedItem(pos);
			DlgDeviceProperties mDlgDeviceProperties;
			// Do something with item nSelected
			
			//DUK- disable name, do not change DeviceName
			//mDlgDeviceProperties.m_Name

			mDlgDeviceProperties.m_DeviceName = m_ListCtrl.GetItemText(nSelected, 1);
			
			str = m_ListCtrl.GetItemText(nSelected, 2);
			swscanf_s(str.LockBuffer(), _T("%d"), &(mDlgDeviceProperties.m_Chanel));
			
			str = m_ListCtrl.GetItemText(nSelected, 3);
			swscanf_s(str.LockBuffer(), _T("%d"), &(mDlgDeviceProperties.m_PWP));
			str = m_ListCtrl.GetItemText(nSelected, 4);
			swscanf_s(str.LockBuffer(), _T("%d"), &(mDlgDeviceProperties.m_PWN));

			mDlgDeviceProperties.m_pCIniReader = m_pCIniReader;
			mDlgDeviceProperties.m_ListCtrl = &(this->m_ListCtrl);
			mDlgDeviceProperties.m_CheckNameExist = 0;
			if (mDlgDeviceProperties.DoModal() == IDOK)
			{
				m_ListCtrl.SetItemText(nSelected, 1, mDlgDeviceProperties.m_DeviceName);
				str.Format(_T("%d"), mDlgDeviceProperties.m_Chanel);
				m_ListCtrl.SetItemText(nSelected, 2, str);
				str.Format(_T("%d"), mDlgDeviceProperties.m_PWP);
				m_ListCtrl.SetItemText(nSelected, 3, str);
				str.Format(_T("%d"), mDlgDeviceProperties.m_PWN);
				m_ListCtrl.SetItemText(nSelected, 4, str);
				m_ListCtrl.SetFocus();
			}
		}
		Save();
	}
}


void DlgDevideSetting::OnBnClickedButtonRemove()
{
	// TODO: Add your control notification handler code here
	int nSelCount = m_ListCtrl.GetSelectedCount();
	if (nSelCount)
	{
		POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
		while (pos)
		{
			int nSelected = m_ListCtrl.GetNextSelectedItem(pos);
			m_ListCtrl.DeleteItem(nSelected);
			m_ListCtrl.UpdateData();
			nSelected = m_ListCtrl.GetItemCount();
			if (nSelected > 0)
			{
				m_ListCtrl.SetItemState(-1, 0, LVIS_SELECTED);
				m_ListCtrl.SetItemState(nSelected - 1, LVIS_SELECTED, LVIS_SELECTED);
				m_ListCtrl.SetFocus();
			}
		}
		Save();
	}
}
bool DlgDevideSetting::Save()
{
	if (m_pCIniReader == NULL)
		return false;
	CString strSection = _T("Device list");
	CString strValue, strKey;
	m_pCIniReader->removeSection(strSection);
	int nItems = m_ListCtrl.GetItemCount();
	strValue.Format(_T("%d"), nItems);
	strKey = _T("NumItems");
	m_pCIniReader->setKey(strValue, strKey, strSection);

	int nSelected = 0;
	LVITEM lvItem = { 0 };
	lvItem.mask = LVIF_IMAGE;
	lvItem.iSubItem = 0;         // column index
	for (int i = 0; i < m_ListCtrl.GetItemCount(); i++)
	{
		lvItem.iItem = i;        // item index 
		m_ListCtrl.GetItem(&lvItem);
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
		strValue = m_ListCtrl.GetItemText(i, 1) + _T(";") + m_ListCtrl.GetItemText(i, 2) + _T(";") + m_ListCtrl.GetItemText(i, 3) + _T(";") + m_ListCtrl.GetItemText(i, 4);
		m_pCIniReader->setKey(strValue, strKey, strSection);
	}
	return true;
}
bool DlgDevideSetting::Restore()
{
	if (m_pCIniReader == NULL)
		return false;
	CString strSection = _T("Device list");
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

	int nSplit[3] = { -1 };
	int Index;
	LVITEM lvi;
	for (int i = 0; i < nItems; i++)
	{
		strKey.Format(_T("Item_%d"), i);
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		if (strValue.IsEmpty())
			continue;
		nSplit[0] = strValue.Find(_T(';'), 0);
		
		if (nSplit[0] == -1) continue;
		
		nSplit[1] = strValue.Find(_T(';'), nSplit[0] + 1);
		if (nSplit[1] == -1) continue;

		nSplit[2] = strValue.Find(_T(';'), nSplit[1] + 1);
		if (nSplit[2] == -1) continue;

		int Index = m_ListCtrl.InsertItem(LVIF_IMAGE, m_ListCtrl.GetItemCount(), _T(""), 0, 0, 0, NULL);
		m_ListCtrl.SetItemText(Index, 1, strValue.Mid(0, nSplit[0]));
		m_ListCtrl.SetItemText(Index, 2, strValue.Mid(nSplit[0] + 1, nSplit[1] - nSplit[0] - 1));
		m_ListCtrl.SetItemText(Index, 3, strValue.Mid(nSplit[1] + 1, nSplit[2] - nSplit[1] - 1));
		m_ListCtrl.SetItemText(Index, 4, strValue.Mid(nSplit[2] + 1, strValue.GetLength() - nSplit[2] - 1));
	}

	if (m_ListCtrl.GetItemCount() > 0 && nSelected != -1)
	{
		m_ListCtrl.SetItemState(-1, 0, LVIS_SELECTED);
		m_ListCtrl.SetItemState(nSelected, LVIS_SELECTED, LVIS_SELECTED);

		LVITEM lvItem = { 0 };
		lvItem.mask = LVIF_IMAGE;
		lvItem.iSubItem = 0;         // column index
		lvItem.iItem = nSelected;        // item index 
		m_ListCtrl.GetItem(&lvItem);
		lvItem.iImage = 1;
		m_ListCtrl.SetItem(&lvItem);

		m_ListCtrl.SetFocus();
	}
	return true;
}

void DlgDevideSetting::OnNMClickDevideListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE pitem = (LPNMITEMACTIVATE)pNMHDR;

	int row = pitem->iItem;
	int column = pitem->iSubItem;

	LVITEM lvItem = { 0 };
	lvItem.mask = LVIF_IMAGE;
	lvItem.iSubItem = 0;         // column index
	for (int i = 0; i < m_ListCtrl.GetItemCount(); i++)
	{
		lvItem.iItem = i;        // item index 
		m_ListCtrl.GetItem(&lvItem);
		if (i == row)
			lvItem.iImage = 1;
		else
			lvItem.iImage = 0;
		m_ListCtrl.SetItem(&lvItem);
	}
	*pResult = 0;
}


void DlgDevideSetting::OnNMRClickDevideListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE pitem = (LPNMITEMACTIVATE)pNMHDR;

	int row = pitem->iItem;
	int column = pitem->iSubItem;

	LVITEM lvItem = { 0 };
	lvItem.mask = LVIF_IMAGE;
	lvItem.iSubItem = 0;         // column index
	for (int i = 0; i < m_ListCtrl.GetItemCount(); i++)
	{
		lvItem.iItem = i;        // item index 
		m_ListCtrl.GetItem(&lvItem);
		if (i == row)
			lvItem.iImage = 1;
		else
			lvItem.iImage = 0;
		m_ListCtrl.SetItem(&lvItem);
	}
	*pResult = 0;
}
