// DlgDeviceJack.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgDeviceJack.h"
#include "DlgDeviceJackName.h"
#include "DlgDeviceJackProperties.h"


// DlgDeviceJack dialog

IMPLEMENT_DYNAMIC(DlgDeviceJack, CDialogEx)

DlgDeviceJack::DlgDeviceJack(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEVICE_JACK, pParent)
	, m_BoardName(_T(""))
{

}

DlgDeviceJack::~DlgDeviceJack()
{
}

void DlgDeviceJack::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CRTL, m_ListCtrl);
	DDX_Text(pDX, IDC_EDIT_NAME, m_BoardName);
	DDX_Control(pDX, IDC_CMB_ID_JACK, m_CB_ID_Jack);
}


BEGIN_MESSAGE_MAP(DlgDeviceJack, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &DlgDeviceJack::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &DlgDeviceJack::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &DlgDeviceJack::OnBnClickedButtonRemove)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CRTL, &DlgDeviceJack::OnLvnItemchangedListCrtl)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CRTL, &DlgDeviceJack::OnNMClickListCrtl)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CRTL, &DlgDeviceJack::OnNMRClickListCrtl)
	ON_BN_CLICKED(IDOK, &DlgDeviceJack::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgDeviceJack::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_SUA, &DlgDeviceJack::OnBnClickedBtnSua)
	ON_CBN_SELCHANGE(IDC_CMB_ID_JACK, &DlgDeviceJack::OnCbnSelchangeCmbIdJack)
END_MESSAGE_MAP()


BOOL DlgDeviceJack::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_BoardName = m_pPlan->mTestCase.mPathInfo.BoardName;
	//-----------------------------
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
	m_ListCtrl.InsertColumn(1, _T("Ký hiệu jắc"), LVCFMT_LEFT, 200);
	m_ListCtrl.InsertColumn(2, _T("Tên jắc"), LVCFMT_LEFT, 200);

	InitListCtrlData();
	Init_CB();
	UpdateData(false);
	//---------------------
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
// DlgDeviceJack message handlers

void DlgDeviceJack::Init_CB() {
	CString str;
	int nSelCur = m_pPlan->mTestCase.mID_Jack;
	
	while (m_CB_ID_Jack.GetCount() > 0) m_CB_ID_Jack.DeleteString(0);
	m_CB_ID_Jack.AddString(_T("Không chọn"));
	m_CB_ID_Jack.AddString(_T("1-J6_ГРПМ9 - 31 / 62ГC2 - В"));
	m_CB_ID_Jack.AddString(_T("2-J5_ГРПМ1 - 61ГО2 - В"));
	m_CB_ID_Jack.AddString(_T("3-J4_ГРПМ1 - 31ГО2 - В"));
	m_CB_ID_Jack.AddString(_T("4-J1_C09032646825"));
	m_CB_ID_Jack.AddString(_T("5-JA3_СНП34С - 46В - 21 - В"));
	m_CB_ID_Jack.AddString(_T("6-JA5_СНП34С - 90В - 21 - В"));
	m_CB_ID_Jack.AddString(_T("7-JA2_СНП34С - 135В - 21 - В"));
	m_CB_ID_Jack.AddString(_T("8-JA4_JA1_СНП34С - 90В_135B - 21 - В"));
	m_CB_ID_Jack.SetCurSel(nSelCur);
}
void DlgDeviceJack::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	JACK_DEF _Jack;
	JACK_ROW_DEF _JackRow;
	DlgDeviceJackName mDlgDeviceJackName;
	int nItems = m_ListCtrl.GetItemCount();
	if (nItems == 0) {
		mDlgDeviceJackName.m_JackName = "";
		mDlgDeviceJackName.m_Symbol = "J1"; 
	}
	else {
		CString str = m_ListCtrl.GetItemText(nItems - 1, 1);
		CString str1 = str.Mid(0, str.GetLength()-1);
		mDlgDeviceJackName.m_Symbol.Format(_T("%s%d"), str1, nItems + 1);
		mDlgDeviceJackName.m_JackName = _T("");
	}

	mDlgDeviceJackName.m_BoardName = m_BoardName;
	mDlgDeviceJackName.CheckName = 0;
	mDlgDeviceJackName.m_pPlan = this->m_pPlan;
	mDlgDeviceJackName.m_ListCtrl = &m_ListCtrl;

	if (mDlgDeviceJackName.DoModal() == IDOK)
	{
		CString JackNameStr, JacSymbolStr;
		JackNameStr.Format(_T("%s"), mDlgDeviceJackName.m_JackName);
		JacSymbolStr.Format(_T("%s"), mDlgDeviceJackName.m_Symbol);
		int Index = m_ListCtrl.InsertItem(LVIF_IMAGE, m_ListCtrl.GetItemCount(), _T(""), 0, 0, 0, NULL);
		m_ListCtrl.SetItem(Index, 1, LVIF_TEXT, JacSymbolStr, 0, 0, 0, NULL);
		m_ListCtrl.SetItem(Index, 2, LVIF_TEXT, JackNameStr, 0, 0, 0, NULL);
		m_ListCtrl.SetItemState(-1, 0, LVIS_SELECTED);
		m_ListCtrl.SetItemState(Index, LVIS_SELECTED, LVIS_SELECTED);
		m_ListCtrl.SetFocus();

		//--------------------
		_Jack.JackName = JackNameStr;
		_Jack.JackSign = JacSymbolStr;
		_Jack.nJackRows = 1;
		_JackRow.JackRowSign.Format(_T("%s_%c"), JacSymbolStr, _Jack.mJACK_ROW.size()+65);
		_JackRow.Pins = 1;
		_Jack.mJACK_ROW.push_back(_JackRow);
		m_pPlan->mTestCase.mJackInfo.mJACKS.push_back(_Jack);
		m_pPlan->mTestCase.mJackInfo.nJacks++;
		//--------------------
	}
}

void DlgDeviceJack::OnBnClickedButtonEdit()
{
	// TODO: Add your control notification handler code here
	JACK_DEF _Jack, _JackTmp;
	std::vector<JACK_DEF> _JACKS;
	int nSelCount = m_ListCtrl.GetSelectedCount();
	if (nSelCount)
	{
		CString str;
		POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
		while (pos)
		{
			int nSelected = m_ListCtrl.GetNextSelectedItem(pos);
			_Jack = m_pPlan->mTestCase.mJackInfo.mJACKS.at(nSelected);
			DlgDeviceJackProperties mDlgDeviceJackProperties;
			mDlgDeviceJackProperties.m_Jack = _Jack;
			if(mDlgDeviceJackProperties.DoModal()== IDOK){
				_Jack = mDlgDeviceJackProperties.m_Jack;
				m_pPlan->mTestCase.mJackInfo.mJACKS.at(nSelected) = _Jack;
			}
		}
		m_ListCtrl.SetFocus();
	}
}

void DlgDeviceJack::OnBnClickedButtonRemove()
{
	// TODO: Add your control notification handler code here
	if (AfxMessageBox(_T("Chắc chắn xóa"), MB_OKCANCEL | MB_ICONWARNING) == IDCANCEL) return;
	JACK_DEF _Jack;
	std::vector<JACK_DEF> _JACKS;
	int _nJacks;

	int nSelCount = m_ListCtrl.GetSelectedCount();

	if (nSelCount)
	{
		POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
		while (pos)
		{
			int nSelected = m_ListCtrl.GetNextSelectedItem(pos);
			m_ListCtrl.DeleteItem(nSelected);
			m_ListCtrl.UpdateData();
			//--------------------
			_JACKS = m_pPlan->mTestCase.mJackInfo.mJACKS;
			m_pPlan->mTestCase.mJackInfo.mJACKS.clear();
			_nJacks = _JACKS.size();
			for (int i = 0; i < _nJacks; i++) {
				if (i != nSelected) {
					_Jack = _JACKS.at(i);
					m_pPlan->mTestCase.mJackInfo.mJACKS.push_back(_Jack);
				}
			}
			m_pPlan->mTestCase.mJackInfo.nJacks = m_pPlan->mTestCase.mJackInfo.mJACKS.size();
			_JACKS.clear();
			//--------------------
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


void DlgDeviceJack::OnLvnItemchangedListCrtl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void DlgDeviceJack::OnNMClickListCrtl(NMHDR* pNMHDR, LRESULT* pResult)
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


void DlgDeviceJack::OnNMRClickListCrtl(NMHDR* pNMHDR, LRESULT* pResult)
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

//=======================================================
//=======================================================
bool DlgDeviceJack::InitListCtrlData()
{
	JACK_ROW_DEF _JackRow;
	JACK_DEF _Jack;
	std::vector<JACK_DEF> _JACKS;
	int _nJacks, _nRows, _nPins;
	CString _JackSign;
	CString _JackName;

	_JACKS = m_pPlan->mTestCase.mJackInfo.mJACKS;
	_nJacks = _JACKS.size();

	int nItems = _nJacks;
	
	int nSelected = 0;
	int Index;
	LVITEM lvi;
	for (int i = 0; i < nItems; i++)
	{
		_Jack = _JACKS.at(i);
		_JackSign = _Jack.JackSign;
		_JackName = _Jack.JackName;
			
		Index = m_ListCtrl.InsertItem(LVIF_IMAGE, m_ListCtrl.GetItemCount(), _T(""), 0, 0, 0, NULL);
		m_ListCtrl.SetItemText(Index, 1, _JackSign);
		m_ListCtrl.SetItemText(Index, 2, _JackName);
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

void DlgDeviceJack::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void DlgDeviceJack::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void DlgDeviceJack::OnBnClickedBtnSua()
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	JACK_DEF _Jack, _JackTmp;
	std::vector<JACK_DEF> _JACKS;
	int nSelCount = m_ListCtrl.GetSelectedCount();
	if (nSelCount)
	{
		CString str;
		POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
		while (pos)
		{
			int nSelected = m_ListCtrl.GetNextSelectedItem(pos);
			_Jack = m_pPlan->mTestCase.mJackInfo.mJACKS.at(nSelected);

			DlgDeviceJackName mDlgDeviceJackName;
			mDlgDeviceJackName.m_JackName = _Jack.JackName;
			mDlgDeviceJackName.m_Symbol = _Jack.JackSign;
			mDlgDeviceJackName.CheckName = 1;
			mDlgDeviceJackName.m_pPlan = this->m_pPlan;
			mDlgDeviceJackName.m_ListCtrl = &m_ListCtrl;

			if (mDlgDeviceJackName.DoModal() == IDOK)
			{
				_Jack.JackName = mDlgDeviceJackName.m_JackName;
				_Jack.JackSign = mDlgDeviceJackName.m_Symbol;
				m_pPlan->mTestCase.mJackInfo.mJACKS.at(nSelected) = _Jack;

				//int Index = m_ListCtrl.InsertItem(LVIF_IMAGE, m_ListCtrl.GetItemCount(), _T(""), 0, 0, 0, NULL);
				m_ListCtrl.SetItem(nSelected, 1, LVIF_TEXT, _Jack.JackSign, 0, 0, 0, NULL);
				m_ListCtrl.SetItem(nSelected, 2, LVIF_TEXT, _Jack.JackName, 0, 0, 0, NULL);
				m_ListCtrl.SetItemState(-1, 0, LVIS_SELECTED);
				m_ListCtrl.SetItemState(nSelected, LVIS_SELECTED, LVIS_SELECTED);
				m_ListCtrl.SetFocus();

			}
		}
		m_ListCtrl.SetFocus();
	}
}


void DlgDeviceJack::OnCbnSelchangeCmbIdJack()
{
	// TODO: Add your control notification handler code here
	m_pPlan->mTestCase.mID_Jack = m_CB_ID_Jack.GetCurSel();
}
