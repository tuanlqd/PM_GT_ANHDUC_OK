// DlgPinSettingAdd.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgPinSettingAdd.h"


// DlgPinSettingAdd dialog

IMPLEMENT_DYNAMIC(DlgPinSettingAdd, CDialogEx)

DlgPinSettingAdd::DlgPinSettingAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PIN_SETTING_ADD, pParent)
	, m_Name(_T(""))
{

}

DlgPinSettingAdd::~DlgPinSettingAdd()
{
}

void DlgPinSettingAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Control(pDX, IDC_COMBO_BOARD, m_CmbBoard);
	DDX_Control(pDX, IDC_COMBO_POWER, m_CmbPower);
}


BEGIN_MESSAGE_MAP(DlgPinSettingAdd, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &DlgPinSettingAdd::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &DlgPinSettingAdd::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgPinSettingAdd message handlers
BOOL DlgPinSettingAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	GetPowerList();
	GetBoardList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void DlgPinSettingAdd::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void DlgPinSettingAdd::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Name.IsEmpty()) MessageBox(_T("The Name is not empty"), _T("Message"));
	else {
		if (ExistName(m_Name)) MessageBox(_T("The Name is realy exist"), _T("Message"));
		else {
			int Index;
			Index = m_CmbBoard.GetCurSel();
			m_CmbBoard.GetLBText(Index, m_BoardSelect);

			Index = m_CmbPower.GetCurSel();
			m_CmbPower.GetLBText(Index, m_PowerSelect);
			//MessageBox(m_BoardSelect, m_PowerSelect);

			InitPinChanelLogic();
			CDialogEx::OnOK();
		}
	}

}
bool DlgPinSettingAdd::cmpStr(CString str1, CString str2)
{
	CString str1temp = str1;
	CString str2temp = str2;
	int nTemp1 = str1temp.GetLength();
	int nTemp2 = str2temp.GetLength();
	str1temp.MakeUpper();
	str2temp.MakeUpper();
	if (nTemp1 != nTemp2) return FALSE;

	int j;
	for (j = 0; j < nTemp1; j++)
		if (str1temp[j] != str2temp[j]) return FALSE;
	return TRUE;
}

void DlgPinSettingAdd::InitPinChanelLogic()
{
	// TODO: Add your command handler code here
	//DUKKK
	UpdateData(TRUE);
	if (m_pCIniReader == NULL)
		return;
	CString strSection, strSectionTmp, strTmp, strTmp1;
	//DUK plus CHANEL_ + m_Name Board + Power 
	strSectionTmp = _T("CHANEL_") + m_Name;
	CString strValue, strKey;
	m_pCIniReader->removeSection(strSectionTmp);
	//------------
	int nItem, numChanel;
	strSection = _T("Device list");
	strKey = _T("NumItems");
	strValue = m_pCIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &nItem);
	if (nItem <= 0) return;
	int sPlit[2] = { -1 };
	for (int i = 0; i < nItem; i++) {
		strKey.Format(_T("Item_%d"), i);
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		sPlit[0] = strValue.Find(_T(';'), 0);
		if (sPlit[0] == -1) continue;
		sPlit[1] = strValue.Find(_T(';'), sPlit[0] + 1);
		if (sPlit[1] == -1) continue;

		strTmp = strValue.Mid(0, sPlit[0]);
		if (cmpStr(strTmp, m_BoardSelect)) {
			strTmp = strValue.Mid(sPlit[0] + 1, sPlit[1] - sPlit[0] - 1);
			swscanf_s(strTmp.GetBuffer(), _T("%d"), &numChanel);
			break;
		}
	}

	strKey = _T("Number of chanel");
	strValue.Format(_T("%d"), numChanel);
	m_pCIniReader->setKey(strValue, strKey, strSectionTmp);
	//--------------------
	// [JackList::DeviceName:Board1]
	//NumItems = 2
	//	SelectItem = 1
	//	Item_0 = J1; Name J
	//	Item_1 = J2; Name J
	//--------------------
	strSection.Format(_T("JackList::DeviceName:%s"),m_BoardSelect);
	strKey = _T("NumItems");
	strValue = m_pCIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &nItem);
	if (nItem <= 0) return;

	//int numConnector = m_vecData.size();
	int numConnector = nItem;
	strKey = _T("Number of connector");
	strValue.Format(_T("%d"), numConnector);
	m_pCIniReader->setKey(strValue, strKey, strSectionTmp);
	//===========================================================
	//------------------------------
	// [PinList::DeviceName:Board1:JackName:J1]
	//NumItems = 3
	//	SelectItem = 0
	//	Item_0 = 12
	//	Item_1 = 15
	//	Item_2 = 12
	//	[PinList::DeviceName:Board1:JackName:J2]
	//NumItems = 2
	//	SelectItem = 0
	//	Item_0 = 13
	//	Item_1 = 15
	//------------------------------

	for (int i = 0; i < numConnector; i++)
	{
		strSection.Format(_T("JackList::DeviceName:%s"), m_BoardSelect);
		strKey.Format(_T("Item_%d"), i);
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		sPlit[0] = strValue.Find(_T(';'), 0);
		if (sPlit[0] == -1) continue;

		int jackRows;
		CString strJackNameTmp = strValue.Mid(0, sPlit[0]);

		strSection.Format(_T("PinList::DeviceName:%s:JackName:%s"), m_BoardSelect, strJackNameTmp);
		strKey = _T("NumItems");
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		swscanf_s(strValue.GetBuffer(), _T("%d"), &jackRows);

		
		if (jackRows <= 0) continue;
		//---------------------------
		CString strValueConnectorPLAN;
		strValueConnectorPLAN.Format(_T("%s;%d"), strJackNameTmp, jackRows);

		for (int j = 0; j < jackRows; j++) {
			strKey.Format(_T("Item_%d"), j);
			strValue = m_pCIniReader->getKeyValue(strKey, strSection);

			strValueConnectorPLAN = strValueConnectorPLAN + _T(";")+ strValue;
		}
		strValueConnectorPLAN = strValueConnectorPLAN + _T(";");
		//----------
		strSectionTmp = _T("CHANEL_") + m_Name;
		strKey.Format(_T("Connector_%d"), i);
		strValue = strValueConnectorPLAN;
		m_pCIniReader->setKey(strValue, strKey, strSectionTmp);
	}
	//------------------------------------------------
	CString arrGrid[255][100] = {_T("UD")};
	for(int i = 0; i<255; i++)
		for(int j = 0; j<100; j++) arrGrid[i][j] =  _T("UD");
	int nRows, nCols = -2, nMaxRow = 0, nMaxCol;
	//int sPlit[2] = { -1 };

	strSection = _T("CHANEL_") + m_Name;
	strKey = _T("Number of connector");
	strValue = m_pCIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &nItem);
	if (nItem <= 0) return;

	for (int i = 0; i < nItem; i++) {
		
		strKey.Format(_T("Connector_%d"), i);
		strValue = m_pCIniReader->getKeyValue(strKey, strSection);
		sPlit[0] = strValue.Find(_T(';'), 0);
		if (sPlit[0] == -1) continue;

		strTmp.Format(_T("_%c"), i + 65);
		CString JackName = strValue.Mid(0, sPlit[0]) + strTmp; //+ _A BC
		int nPinRow, nPin, nJackPin = 0;
		sPlit[1] = strValue.Find(_T(';'), sPlit[0] + 1);
		if (sPlit[1] == -1) continue;
		strTmp = strValue.Mid(sPlit[0] + 1, sPlit[1] - sPlit[0] - 1);
		swscanf_s(strTmp.GetBuffer(), _T("%d"), &nPinRow);

		for (int j = 0; j < nPinRow; j++) {
			sPlit[0] = sPlit[1];
			sPlit[1] = strValue.Find(_T(';'), sPlit[0] + 1);
			if (sPlit[1] == -1) continue;
			strTmp = strValue.Mid(sPlit[0] + 1, sPlit[1] - sPlit[0] - 1);
			
			swscanf_s(strTmp.GetBuffer(), _T("%d"), &nPin);
			nCols+=2;
			nRows = nPin;
			if (nMaxRow < nRows) nMaxRow = nRows;
			//--------------------------
			arrGrid[0][nCols] = JackName;
			arrGrid[0][nCols + 1]= _T(".         Chanel        .");

			for (int iRow = 1; iRow <= nRows; iRow++) {
				nJackPin++;
				arrGrid[iRow][nCols].Format(_T("%d"), nJackPin);
				arrGrid[iRow][nCols+1] = _T("NC");
			}
			//----------------------------

		}
	}
	nMaxCol = nCols+2;
	nMaxRow = nMaxRow + 1;
	//Save to File

	strSection = _T("CHANEL_") + m_Name;
	strKey.Format(_T("Grid"));
	strValue.Format(_T("%d;%d"), nMaxRow, nMaxCol);
	m_pCIniReader->setKey(strValue, strKey, strSection);

	for (int iRow = 0; iRow < nMaxRow; iRow++) {
		strKey.Format(_T("Row_%d"), iRow);
		strValue = _T("");
		for (int iCol = 0; iCol < nMaxCol; iCol++) {
			strValue = strValue + arrGrid[iRow][iCol] + _T(";");
		}
		m_pCIniReader->setKey(strValue, strKey, strSection);
	}

}

bool DlgPinSettingAdd::ExistName(CString Name)
{
	int nItems = (*m_ListCtrl).GetItemCount();
	if (nItems == 0) return false;

	for (int i = 0; i < nItems; i++)
	{
		CString tempItem = (*m_ListCtrl).GetItemText(i, 1);
		tempItem.MakeUpper();
		CString tempPlanName = Name;
		tempPlanName.MakeUpper();

		int nTemp = tempItem.GetLength();
		int nDeviceName = Name.GetLength();
		if (nTemp != nDeviceName) continue;

		int j;
		for (j = 0; j < nTemp; j++)
			if (tempItem[j] != tempPlanName[j])
				j = nTemp + 2;

		if (j == nTemp) return true;
	}

	return false;
}
bool DlgPinSettingAdd::GetPowerList()
{
	if (m_pCIniReader == NULL)
		return false;
	/*
	[POWERS]
	NumItems=2
	SelectItem=1
	Item_0=ChanelPower_0;DV01;PJ1S2;03892392-11dc-4379-bfcb-70a4cff45c44
	Item_1=ChanelPower_1;DV01;PJ1S2;191a535b-163d-4598-9606-15fef7f026b5
	*/
	CString strSection = _T("POWERS");
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
	int Index;
	CString strTmp;
	if (nItems >= 1)
	{
		int nSplit = -1;
		for (int i = 0; i < nItems; i++)
		{
			strKey.Format(_T("Item_%d"), i);
			strValue = m_pCIniReader->getKeyValue(strKey, strSection);
			if (strValue.IsEmpty())
				continue;

			nSplit = strValue.Find(_T(';'), 0);
			if (nSplit == -1) continue;
			
			m_CmbPower.AddString(strValue.Mid(0, nSplit));
		}
		m_CmbPower.SetCurSel(0);
	}
	return true;
}
bool DlgPinSettingAdd::GetBoardList()
{
	if (m_pCIniReader == NULL)
		return false;
	/*
	[Device list]
	NumItems=2
	SelectItem=0
	Item_0=Test1;84;5;3
	Item_1=Test2;84;5;3
	*/
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
	int Index;
	CString strTmp;
	if (nItems >= 1)
	{
		int nSplit = -1;
		for (int i = 0; i < nItems; i++)
		{
			strKey.Format(_T("Item_%d"), i);
			strValue = m_pCIniReader->getKeyValue(strKey, strSection);
			if (strValue.IsEmpty())
				continue;

			nSplit = strValue.Find(_T(';'), 0);
			if (nSplit == -1) continue;

			m_CmbBoard.AddString(strValue.Mid(0, nSplit));
		}
		m_CmbBoard.SetCurSel(0);
	}
	return true;
}

