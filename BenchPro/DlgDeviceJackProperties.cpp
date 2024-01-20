// DlgDeviceJackProperties.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgDeviceJackProperties.h"
#include "DlgDeviceJackPropertiesEdit.h"

// DlgDeviceJackProperties dialog

IMPLEMENT_DYNAMIC(DlgDeviceJackProperties, CDialogEx)

DlgDeviceJackProperties::DlgDeviceJackProperties(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEVICE_JACK_PROPERTIES, pParent)
	, m_JackName(_T(""))
	, m_Jack_Sign(_T(""))
{

}

DlgDeviceJackProperties::~DlgDeviceJackProperties()
{
}

void DlgDeviceJackProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_JACK_NAME, m_JackName);
	DDX_Control(pDX, IDC_LIST_CTRL, m_ListCtrl);
	DDX_Text(pDX, IDC_EDIT_JACK_SIGN, m_Jack_Sign);
}


BEGIN_MESSAGE_MAP(DlgDeviceJackProperties, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &DlgDeviceJackProperties::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &DlgDeviceJackProperties::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &DlgDeviceJackProperties::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDOK, &DlgDeviceJackProperties::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgDeviceJackProperties::OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CTRL, &DlgDeviceJackProperties::OnNMClickListCtrl)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CTRL, &DlgDeviceJackProperties::OnNMDblclkListCtrl)
END_MESSAGE_MAP()

// DlgDeviceJackProperties message handlers
BOOL DlgDeviceJackProperties::OnInitDialog()
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
	// TODO:  Add extra initialization here
	m_ListCtrl.InsertColumn(0, _T("Chọn"), LVCFMT_LEFT, 50);
	m_ListCtrl.InsertColumn(1, _T("Số chân"), LVCFMT_LEFT, 200);

	InitListCtrlData();
	m_JackName = m_Jack.JackName;
	m_Jack_Sign = m_Jack.JackSign;
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void DlgDeviceJackProperties::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	JACK_ROW_DEF _JackRow;
	DlgDeviceJackPropertiesEdit mDlgDeviceJackPropertiesEdit;

	if (mDlgDeviceJackPropertiesEdit.DoModal() == IDOK)
	{

		CString Str;
		int intTmp;
		Str.Format(_T("%s"), mDlgDeviceJackPropertiesEdit.m_nPinPerRow);
		swscanf_s(Str.GetBuffer(), _T("%d"), &(intTmp));
		_JackRow.Pins = intTmp;

		_JackRow.JackRowSign.Format(_T("%s_%c"), m_Jack.JackSign, m_Jack.mJACK_ROW.size() + 65);
		m_Jack.mJACK_ROW.push_back(_JackRow);
		m_Jack.nJackRows++;

		int Index = m_ListCtrl.InsertItem(LVIF_IMAGE, m_ListCtrl.GetItemCount(), _T(""), 0, 0, 0, NULL);
		m_ListCtrl.SetItem(Index, 1, LVIF_TEXT, Str, 0, 0, 0, NULL);

		m_ListCtrl.SetItemState(-1, 0, LVIS_SELECTED);
		m_ListCtrl.SetItemState(Index, LVIS_SELECTED, LVIS_SELECTED);
		m_ListCtrl.SetFocus();
	}
}

void DlgDeviceJackProperties::OnBnClickedButtonEdit()
{
	// TODO: Add your control notification handler code here
	JACK_ROW_DEF _JackRow;
	int intTmp;
	int nSelCount = m_ListCtrl.GetSelectedCount();
	if (nSelCount)
	{
		CString strValue, str;
		// Create and int array to store the indexes and initialze 
		// with the indexes of selected items
		POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
		while (pos)
		{
			int nSelected = m_ListCtrl.GetNextSelectedItem(pos);
			DlgDeviceJackPropertiesEdit mDlgDeviceJackPropertiesEdit;
			strValue = m_ListCtrl.GetItemText(nSelected, 1);
			mDlgDeviceJackPropertiesEdit.m_nPinPerRow.Format(_T("%s"), strValue);
			if (mDlgDeviceJackPropertiesEdit.DoModal() == IDOK)
			{
				str.Format(_T("%s"), mDlgDeviceJackPropertiesEdit.m_nPinPerRow);
				m_ListCtrl.SetItemText(nSelected, 1, str);
				m_ListCtrl.SetFocus();

				_JackRow = m_Jack.mJACK_ROW.at(nSelected);
				swscanf_s(str.GetBuffer(), _T("%d"), &(intTmp));
				_JackRow.Pins = intTmp;
				m_Jack.mJACK_ROW.at(nSelected) = _JackRow;
			}
		}

	}
}

void DlgDeviceJackProperties::OnBnClickedButtonRemove()
{
	// TODO: Add your control notification handler code here
	if (AfxMessageBox(_T("Chắc chắn xóa"), MB_OKCANCEL | MB_ICONWARNING) == IDCANCEL) return;
	JACK_ROW_DEF _JackRow;
	std::vector<JACK_ROW_DEF> _Jacks;
	int intTmp;

	int nSelCount = m_ListCtrl.GetSelectedCount();
	if (nSelCount)
	{
		POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
		while (pos)
		{
			int nSelected = m_ListCtrl.GetNextSelectedItem(pos);
			m_ListCtrl.DeleteItem(nSelected);
			m_ListCtrl.UpdateData();
			//-----------------------
			int nItem = m_Jack.mJACK_ROW.size();
			for (int i = nItem - 1; i >= 0; i--) {
				_JackRow = m_Jack.mJACK_ROW.at(i);
				if (i != nSelected) _Jacks.push_back(_JackRow);
			}
			m_Jack.mJACK_ROW.clear();
			m_Jack.nJackRows = 0;
			nItem -= 1;
			for (int i = nItem - 1; i >= 0; i--) {
				_JackRow = _Jacks.at(i);
				_JackRow.JackRowSign.Format(_T("%s_%c"), m_Jack.JackSign, nItem - 1 - i + 65);
				m_Jack.mJACK_ROW.push_back(_JackRow);
				m_Jack.nJackRows++;
			}
		}
	}
}


void DlgDeviceJackProperties::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void DlgDeviceJackProperties::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void DlgDeviceJackProperties::OnNMClickListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
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

void DlgDeviceJackProperties::OnNMDblclkListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
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

bool DlgDeviceJackProperties::InitListCtrlData()
{
	JACK_ROW_DEF _JackRow;
	int nItems = m_Jack.nJackRows;
	int nSelected = 0;
	int Index;
	CString strtmp;
	LVITEM lvi;
	for (int i = 0; i < nItems; i++)
	{
		_JackRow = m_Jack.mJACK_ROW.at(i);
		//_JackRow.JackRowSign;
		strtmp.Format(_T("%d"),_JackRow.Pins);
		int Index = m_ListCtrl.InsertItem(LVIF_IMAGE, m_ListCtrl.GetItemCount(), _T(""), 0, 0, 0, NULL);
		m_ListCtrl.SetItemText(Index, 1, strtmp);
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