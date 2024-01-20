// DlgPinSetting.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgPinSetting.h"
#include "DlgPinSettingEdit.h"
#include "DlgPinSettingAdd.h"



// DlgPinSetting dialog

IMPLEMENT_DYNAMIC(DlgPinSetting, CDialogEx)

DlgPinSetting::DlgPinSetting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PIN_SETTING, pParent)
{
	m_pCIniReader = NULL;
}

DlgPinSetting::~DlgPinSetting()
{
}

void DlgPinSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CTRL, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(DlgPinSetting, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &DlgPinSetting::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDOK, &DlgPinSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgPinSetting::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &DlgPinSetting::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &DlgPinSetting::OnBnClickedButtonRemove)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CTRL, &DlgPinSetting::OnNMDblclkListCtrl)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CTRL, &DlgPinSetting::OnNMClickListCtrl)
	ON_BN_CLICKED(IDC_BUTTON_SETPIN_CHANEL, &DlgPinSetting::OnBnClickedButtonSetpinChanel)
END_MESSAGE_MAP()


// DlgPinSetting message handlers

BOOL DlgPinSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	HIMAGELIST hList = ImageList_Create(16, 16, ILC_COLOR4, 2, 1);
	m_cImageListNormal.Attach(hList);
	CBitmap cBmp;
	cBmp.LoadBitmap(IDB_BITMAP_SELECT);
	m_cImageListNormal.Add(&cBmp, RGB(0, 0, 0));
	cBmp.DeleteObject();
	m_ListCtrl.SetImageList(&m_cImageListNormal, LVSIL_SMALL);
	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	// TODO:  Add extra initialization here
	m_ListCtrl.InsertColumn(0, _T("Default"), LVCFMT_LEFT, 50);
	m_ListCtrl.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 150);
	m_ListCtrl.InsertColumn(2, _T("Device"), LVCFMT_LEFT, 150);
	m_ListCtrl.InsertColumn(3, _T("Power"), LVCFMT_LEFT, 150);
	Restore();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void DlgPinSetting::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	DlgPinSettingAdd mDlgPinSettingAdd;
	mDlgPinSettingAdd.m_pCIniReader = this->m_pCIniReader;
	mDlgPinSettingAdd.m_Name.Format(_T("Plan%d"), m_ListCtrl.GetItemCount() +1);
	mDlgPinSettingAdd.m_ListCtrl = &m_ListCtrl;

	if (mDlgPinSettingAdd.DoModal() == IDOK)
	{
		int Index = m_ListCtrl.InsertItem(LVIF_IMAGE, m_ListCtrl.GetItemCount(), _T(""), 0, 0, 0, NULL);
		m_ListCtrl.SetItemText(Index, 1, mDlgPinSettingAdd.m_Name);
		m_ListCtrl.SetItemText(Index, 2, mDlgPinSettingAdd.m_BoardSelect);
		m_ListCtrl.SetItemText(Index, 3, mDlgPinSettingAdd.m_PowerSelect);

		m_ListCtrl.SetItemState(-1, 0, LVIS_SELECTED);
		m_ListCtrl.SetItemState(Index, LVIS_SELECTED, LVIS_SELECTED);
		m_ListCtrl.SetFocus();

		Save();
	}

}

void DlgPinSetting::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Save();
	CDialogEx::OnOK();
}


void DlgPinSetting::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void DlgPinSetting::OnBnClickedButtonEdit()
{
	// TODO: Add your control notification handler code here
	//int nSelCount = m_ListCtrl.GetSelectedCount();
	//if (nSelCount)
	//{
	//	CString str;
	//	// Create and int array to store the indexes and initialze 
	//	// with the indexes of selected items
	//	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
	//	while (pos)
	//	{
	//		int nSelected = m_ListCtrl.GetNextSelectedItem(pos);
	//		DlgPinSettingEdit mDlgPinSettingEdit;

	//		mDlgPinSettingEdit.m_Name = m_ListCtrl.GetItemText(nSelected, 1);
	//		mDlgPinSettingEdit.m_Board = m_ListCtrl.GetItemText(nSelected, 2);
	//		mDlgPinSettingEdit.m_Power = m_ListCtrl.GetItemText(nSelected, 3);
	//		mDlgPinSettingEdit.m_pCIniReader = this->m_pCIniReader;
	//		mDlgPinSettingEdit.DoModal();
	//	}
	//} 
}


void DlgPinSetting::OnBnClickedButtonRemove()
{
	// TODO: Add your control notification handler code here
	//DUK - Delete all section
	int nSelCount = m_ListCtrl.GetSelectedCount();
	if (nSelCount)
	{
		POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
		while (pos)
		{
			int nSelected = m_ListCtrl.GetNextSelectedItem(pos);
			if (m_pCIniReader)
			{
				CString strSection;
				strSection = _T("CHANEL_") + m_ListCtrl.GetItemText(nSelected, 1);
				m_pCIniReader->removeSection(strSection);
			}
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
	}
}


void DlgPinSetting::OnNMDblclkListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
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

bool DlgPinSetting::Save()
{
	if (m_pCIniReader == NULL)
		return false;
	CString strSection = _T("PLANS");
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
		strValue = m_ListCtrl.GetItemText(i, 1) + _T(";") + m_ListCtrl.GetItemText(i, 2) + _T(";") + m_ListCtrl.GetItemText(i, 3);
		m_pCIniReader->setKey(strValue, strKey, strSection);
	}
	return true;
}
bool DlgPinSetting::Restore()
{
	if (m_pCIniReader == NULL)
		return false;
	CString strSection = _T("PLANS");

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

		int Index = m_ListCtrl.InsertItem(LVIF_IMAGE, m_ListCtrl.GetItemCount(), _T(""), 0, 0, 0, NULL);
		m_ListCtrl.SetItemText(Index, 1, strValue.Mid(0, nSplit[0]));

		m_ListCtrl.SetItemText(Index, 2, strValue.Mid(nSplit[0] + 1, nSplit[1] - nSplit[0] - 1));
		m_ListCtrl.SetItemText(Index, 3, strValue.Mid(nSplit[1] + 1, strValue.GetLength() - nSplit[1] - 1));
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

void DlgPinSetting::OnNMClickListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
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


void DlgPinSetting::OnBnClickedButtonSetpinChanel()
{
	// TODO: Add your control notification handler code here
	//int nSelCount = m_ListCtrl.GetSelectedCount();
	//if (nSelCount)
	//{
	//	CString str;
	//	// Create and int array to store the indexes and initialze 
	//	// with the indexes of selected items
	//	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
	//	while (pos)
	//	{
	//		int nSelected = m_ListCtrl.GetNextSelectedItem(pos);
	//		DlgPinSettingEdit mDlgPinSettingEdit;

	//		mDlgPinSettingEdit.m_Name = m_ListCtrl.GetItemText(nSelected, 1);
	//		mDlgPinSettingEdit.m_Board = m_ListCtrl.GetItemText(nSelected, 2);
	//		mDlgPinSettingEdit.m_Power = m_ListCtrl.GetItemText(nSelected, 3);
	//		mDlgPinSettingEdit.m_pCIniReader = this->m_pCIniReader;
	//		mDlgPinSettingEdit.DoModal();
	//	}
	//}
}
