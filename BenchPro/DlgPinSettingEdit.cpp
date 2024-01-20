// DlgPinSettingEdit.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgPinSettingEdit.h"

// DlgPinSettingEdit dialog

IMPLEMENT_DYNAMIC(DlgPinSettingEdit, CDialogEx)

DlgPinSettingEdit::DlgPinSettingEdit(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PIN_SETTING_EDIT, pParent)
	, m_DeviceName(_T(""))
	, m_BoardName(_T(""))
	, m_TestName(_T(""))
	, m_Edit_Jack_ID(_T(""))
{
	m_isNew = true;
	m_OldSize = CSize(-1, -1);
	m_numChanel = 100;
	m_bRejectEditAttempts = false;
	m_font = new CFont;
	m_font->CreateFont(
		18,                       // nHeight
		0,                        // nWidth
		0,                        // nEscapement
		0,                        // nOrientation
		FW_BOLD,                // nWeight
		FALSE,                    // bItalic
		FALSE,                    // bUnderline
		0,                        // cStrikeOut
		ANSI_CHARSET,             // nCharSet
		OUT_DEFAULT_PRECIS,       // nOutPrecision
		CLIP_DEFAULT_PRECIS,      // nClipPrecision
		DEFAULT_QUALITY,          // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		_T("Arial"));            // lpszFacename
}

DlgPinSettingEdit::~DlgPinSettingEdit()
{
	if (m_font)
		delete m_font;
}

void DlgPinSettingEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_DeviceName);
	DDX_Text(pDX, IDC_EDIT_BOARD, m_BoardName);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Text(pDX, IDC_EDIT_TEST, m_TestName);
	DDX_Text(pDX, IDC_EDIT_IDJACK, m_Edit_Jack_ID);
}


BEGIN_MESSAGE_MAP(DlgPinSettingEdit, CDialogEx)
	ON_COMMAND(ID_PIN_SETTING_EDIT_FILE_NEW, &DlgPinSettingEdit::OnPinSettingEditFileNew)
	ON_COMMAND(ID_PIN_SETTING_EDIT_FILE_OPEN, &DlgPinSettingEdit::OnPinSettingEditFileOpen)
	ON_COMMAND(ID_PIN_SETTING_EDIT_FILE_SAVE, &DlgPinSettingEdit::OnPinSettingEditFileSave)
	ON_COMMAND(ID_PIN_SETTING_EDIT_FILE_SAVE_EXIT, &DlgPinSettingEdit::OnPinSettingEditFileSaveExit)
	ON_COMMAND(ID_FILE_EXIT, &DlgPinSettingEdit::OnFileExit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	ON_BN_CLICKED(IDC_BTN_SAVE, &DlgPinSettingEdit::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_EXIT, &DlgPinSettingEdit::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_RESET, &DlgPinSettingEdit::OnBnClickedBtnReset)
END_MESSAGE_MAP()


// DlgPinSettingEdit message handlers

BOOL DlgPinSettingEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_Edit_Jack_ID = sTringArr_IDJack[m_pPlan->mTestCase.mID_Jack];
	UpdateData(FALSE);
	CBitmap bmp;
	if (!bmp.LoadBitmap(IDB_IMAGES))
	{
		ASSERT(FALSE);
		return FALSE;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK | ILC_COLOR24;
	//nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_ImageList.Create(32, bmpObj.bmHeight, nFlags, 0, 0);
	m_ImageList.Add(&bmp, RGB(255, 255, 255));

	m_Grid.SetImageList(&m_ImageList);

	CRect rect;
	GetClientRect(rect);
	m_OldSize = CSize(rect.Width(), rect.Height());


	m_Grid.EnableDragAndDrop(FALSE);
	m_Grid.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));

	OnFileOpenLogic();

	if (m_User) {
		CMenu* pMenu = GetMenu();
		if (pMenu) {
			CMenu* pSubMenu = pMenu->GetSubMenu(0);
			if (pSubMenu) {
				pSubMenu->EnableMenuItem(ID_PIN_SETTING_EDIT_FILE_NEW, true);
				pSubMenu->EnableMenuItem(ID_PIN_SETTING_EDIT_FILE_SAVE, true);
				pSubMenu->EnableMenuItem(ID_PIN_SETTING_EDIT_FILE_SAVE_EXIT, true);
			}
		}

		CButton* pButtonCtrl;
		pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_RESET);
		pButtonCtrl->EnableWindow(false);
		pButtonCtrl = (CButton*)GetDlgItem(IDC_BTN_SAVE);
		pButtonCtrl->EnableWindow(false);

	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void DlgPinSettingEdit::OnPinSettingEditFileNew()
{
	// TODO: Add your command handler code here
	if (m_User) {
		MessageBox(_T("Không thực thiện chức năng này"), _T("Thông báo"));
		return;
	}
	CString strMess;
	strMess.Format(_T("Chắc chắn xóa hết thiết lập chân. Tiếp tục chọn?"));
	if (AfxMessageBox(strMess, MB_OKCANCEL | MB_ICONWARNING) != 1) return;

	m_pPlan->New_PinGrid_GridHeader_GUIGridArr();
	OnFileOpenLogic();
	UpdateData(false);
}


void DlgPinSettingEdit::OnPinSettingEditFileOpen()
{
	// TODO: Add your command handler code here
}


void DlgPinSettingEdit::OnPinSettingEditFileSave()
{
	// TODO: Add your command handler code here
	if (m_User) {
		MessageBox(_T("Không thực thiện chức năng này"), _T("Thông báo"));
		return;
	}
	UpdateGridToStruct();
	
	m_pPlan->Save_TestCaseConfig(m_pCIniReader,0);
}


void DlgPinSettingEdit::OnPinSettingEditFileSaveExit()
{
	// TODO: Add your command handler code here
	if (m_User) {
		MessageBox(_T("Không thực thiện chức năng này"), _T("Thông báo"));
		return;
	}

	UpdateGridToStruct();
	
	m_pPlan->Save_TestCaseConfig(m_pCIniReader, 0);
	CDialogEx::OnOK();
}
void DlgPinSettingEdit::GetArrayChanel(CStringArray& arrStr) const
{
	CString str;
	arrStr.Add(_T("Không chọn"));
	for (int i = 1; i <= m_numChanel; i++)
	{
		str.Format(_T("Kênh %d"), i);
		arrStr.Add(str);
	}
	for (int i = 0; i < 4; i++) arrStr.Add(sTringArr_ExtrChl[i]);
}
int DlgPinSettingEdit::ChanelToNum(CString strTmp) {
	if (strTmp == _T("Không chọn")) return 0;
	CString str;
	for (int i = 1; i <= m_numChanel; i++)
	{
		str.Format(_T("Kênh %d"), i);
		if (strTmp == str) return i;
		for(int ii = 0; ii <4; ii++ )
			if (strTmp == sTringArr_ExtrChl[ii]) return ii+100;

	}
	return 0;  
}
bool DlgPinSettingEdit::SplitString(const CString& strText,
	UINT uNumSegments,
	CStringArray& rAryStrSegments,
	TCHAR zChar) const
{
	bool    bOK = true;
	CString strSegment;
	UINT    uSegment, uCount = 0;
	int     iStartIndex, iFindIndex;

	rAryStrSegments.RemoveAll();

	if (uNumSegments == (UINT)-1)
	{
		// we must work out how many segments their are
		iStartIndex = 0;
		iFindIndex = strText.Find(zChar, iStartIndex);
		while (iFindIndex != -1)
		{
			uCount++;
			iStartIndex = iFindIndex + 1;
			iFindIndex = strText.Find(zChar, iStartIndex);
		}
		uNumSegments = uCount + 1;      
	}

	uSegment = 1;
	iStartIndex = 0;
	while (uSegment <= uNumSegments)
	{
		if (uSegment < uNumSegments)
		{
			iFindIndex = strText.Find(zChar, iStartIndex);
			if (iFindIndex == -1)
			{
				// oops, incorrect number of zChar in this string
				bOK = FALSE;
				break;
			}

			strSegment = strText.Mid(iStartIndex, iFindIndex - iStartIndex);
			iStartIndex = iFindIndex + 1;
		}
		else
		{
			// no more zChar should exist now
			iFindIndex = strText.Find(zChar, iStartIndex);
			if (iFindIndex != -1)
			{
				// oops - more zChar exist
				bOK = false;
				break;
			}

			strSegment = strText.Mid(iStartIndex);
		}

		// Handle empty strings
		if (strSegment.IsEmpty())
			strSegment = _T("");

		rAryStrSegments.Add(strSegment);
		uSegment++;
	}

	return bOK;
}

void DlgPinSettingEdit::OnFileOpenLogic()
{
	// TODO: Add your command handler code here
	if (m_pPlan == NULL)
		return;

	m_numChanel = m_pPlan->mTestCase.mTestCaseConfig.nChanels;

	m_nRows = m_pPlan->mTestCase.mTestCaseConfig.ArrRows;
	m_nCols = m_pPlan->mTestCase.mTestCaseConfig.ArrCols;
	
	//---------------------
	m_nFixRows = 1;
	m_nFixCols = 0;
	m_Grid.DeleteAllItems();
	TRY{
			m_Grid.SetRowCount(m_nRows);
			m_Grid.SetColumnCount(m_nCols*3);
			m_Grid.SetFixedRowCount(m_nFixRows);
			m_Grid.SetFixedColumnCount(m_nFixCols);
	}
		CATCH(CMemoryException, e)
	{
		e->ReportError();
		return;
	}
	END_CATCH
	//---------------

	CStringArray arrSelect;
	GetArrayChanel(arrSelect);
	bool isFont = true;
	LOGFONT lf;
	isFont = (m_font->GetLogFont(&lf) != 0);
	//---------------------------------------
	//GUI
	for (int col = 0; col < m_nCols; col++) {
		m_Grid.SetItemText(0, col*3, m_pPlan->mTestCase.mTestCaseConfig.GUIGridArr[0][col]);
		if (isFont)
			m_Grid.SetItemFont(0, col*3, &lf);
	}
	for (int col = 0; col < m_nCols; col++) {
		m_Grid.SetItemText(0, col * 3 + 1, _T(".       Kênh       ."));
		m_Grid.SetItemText(0, col * 3 + 2, _T(".     Tên chân     ."));
		if (isFont)
		{
			m_Grid.SetItemFont(0, col * 3 + 1, &lf);
			m_Grid.SetItemFont(0, col * 3 + 2, &lf);
		}
	}
	for (int row = 1; row < m_nRows; row++) {
		for (int col = 0; col < m_nCols; col++) {
			if (m_pPlan->mTestCase.mTestCaseConfig.PinGridArr[row][col] != -1) {
				m_Grid.SetItemText(row, col * 3, m_pPlan->mTestCase.mTestCaseConfig.GUIGridArr[row][col]);
				m_Grid.SetItemImage(row, col * 3, 0);
				if (isFont)
					m_Grid.SetItemFont(row, col * 3, &lf);
			}
		}
	}
	//----------------------------------------
	// Data
	int itmp;
	CString strtmp, strNametmp;
	for (int row = 1; row < m_nRows; row++)
	{
		for (int col = 0; col < m_nCols; col++)
		{
			if(m_User) m_Grid.SetItemState(row, col * 3 + 1, GVIS_READONLY);

			itmp = m_pPlan->mTestCase.mTestCaseConfig.PinGridArr[row][col];
			strNametmp.Format(_T("%s"), m_pPlan->mTestCase.mTestCaseConfig.PinNameGridArr[row][col]);
			if (itmp == -1) {
				m_Grid.SetItemState(row, col * 3 + 1, GVIS_READONLY);
				m_Grid.SetItemState(row, col * 3 + 2, GVIS_READONLY);
			}
			else
			{
				if (itmp == 0) {
					m_Grid.SetItemText(row, col * 3 + 1, _T(""));
				}
				else {
					strtmp.Format(_T("Kênh %d"), itmp);
					if (itmp >= 100 && itmp <= 103) strtmp = sTringArr_ExtrChl[itmp - 100];
					m_Grid.SetItemText(row, col * 3 + 1, strtmp);
				}
				m_Grid.SetItemText(row, col * 3 + 2, strNametmp);
				
				if (!m_Grid.SetCellType(row, col * 3 + 1, RUNTIME_CLASS(CGridCellCombo)))
					return;
				CGridCellCombo* pCell = dynamic_cast<CGridCellCombo*>(m_Grid.GetCell(row, col * 3 + 1));
				pCell->SetStyle(CBS_DROPDOWNLIST);
				pCell->SetOptions(arrSelect);
				if (isFont)
					pCell->SetFont(&lf);
				if (isFont)
					m_Grid.SetItemFont(row, col * 3+2, &lf);
			
			}
		}
	}
	m_Grid.AutoSize();
	m_Grid.SetCallbackFunc(NULL, 0);
	m_Grid.AllowReorderColumn(FALSE); // implemented now only if m_bCallback	
	m_Grid.Refresh();
}
void DlgPinSettingEdit::UpdateGridToStruct() {
	// Update Struct
	UpdateData(TRUE);
	if (m_pPlan == NULL)
		return;
	//-------------------------------
	TESTCASE_CONFIG* _pTestCaseConfig;
	_pTestCaseConfig = &m_pPlan->mTestCase.mTestCaseConfig;
	// Update PinGridArr
	//CString arrGrid[255][100];
	int nRows, nCols;
	nRows = m_Grid.GetRowCount();
	nCols = m_Grid.GetColumnCount();
	nCols = nCols / 3;
	_pTestCaseConfig->ArrRows = m_nRows;
	_pTestCaseConfig->ArrCols = m_nCols;
	CString strTmp, strNameTmp;
	int itmp;
	for (int row = 1; row < nRows; row++)
	{
		for (int col = 0; col < nCols; col++)
		{
			strTmp = m_Grid.GetItemText(row, col * 3 + 1);
			strNameTmp = m_Grid.GetItemText(row, col * 3 + 2);
			if (strTmp.IsEmpty())
			{
				if (m_Grid.GetItemState(row, col * 3 + 1) & GVIS_READONLY)
					itmp = -1;
				else
					itmp = 0;
			}
			else
				itmp = ChanelToNum(strTmp);
			_pTestCaseConfig->PinGridArr[row][col] = itmp;
			_pTestCaseConfig->PinNameGridArr[row][col] = strNameTmp;
		}
	}
	//--------------------------
	// Update 1-MapPinArr
	//--------------------------
	int _nPin = 0;
	CString strSignTmp;
	for (int col = 0; col < nCols; col++)
	{
		for (int row = 1; row < nRows; row++)
		{
			itmp = _pTestCaseConfig->PinGridArr[row][col];
			strNameTmp = _pTestCaseConfig->PinNameGridArr[row][col];
			if (itmp != -1) {
				_nPin++;
				_pTestCaseConfig->mPinsConf[_nPin].iChanel = itmp;
				_pTestCaseConfig->mPinsConf[_nPin].mPinName = strNameTmp;
			}
		}
	}
	//--------------------------
	// Update 2- ChanelSelectArr
	//--------------------------
	int _nChanels = m_pPlan->mTestCase.mTestCaseConfig.nChanels;
	_nPin = m_pPlan->mTestCase.mTestCaseConfig.nPins;
	int _valueTmp;
	for (int i = 1; i <= _nChanels; i++)
		_pTestCaseConfig->ChanelSelectArr[i] = 0;
	for (int i = 1; i <= _nPin; i++) {
		_valueTmp = _pTestCaseConfig->mPinsConf[i].iChanel;
		if (_valueTmp != 0)
			_pTestCaseConfig->ChanelSelectArr[_valueTmp] = 1;
	}
	//----------------------
	// Update  ChanelGridArr[256][100];
	for (int row = 1; row < nRows; row++)
	{
		for (int col = 0; col < nCols; col++)
		{
			itmp = _pTestCaseConfig->PinGridArr[row][col];
			if (itmp > 0) {
				if (_pTestCaseConfig->ChanelGridArr[row][col] <= 0) {
					int m_value = 0;
					for (int row_tmp = 1; row_tmp < nRows; row_tmp++) {
						for (int col_tmp = 0; col_tmp < nCols; col_tmp++) {
							if (_pTestCaseConfig->PinGridArr[row_tmp][col_tmp] == itmp) {
								if (_pTestCaseConfig->ChanelGridArr[row_tmp][col_tmp] > 0) {
									m_value = _pTestCaseConfig->ChanelGridArr[row_tmp][col_tmp];
									row_tmp = nRows;
									col_tmp = nCols;
								}
							}
						}
					}
					_pTestCaseConfig->ChanelGridArr[row][col] = m_value;
				}
			}
			else
				m_pPlan->mTestCase.mTestCaseConfig.ChanelGridArr[row][col] = -1;
		}
	}
	//----------------------
}

void DlgPinSettingEdit::OnFileExit()
{
	// TODO: Add your command handler code here
	CDialogEx::OnOK();
}
bool DlgPinSettingEdit::ValidateChanel(int curRow, int curCol, const CString& strChanel) const
{
	for (int row = 1; row <= m_nRows; row++)
	{
		for (int col = 0; col < m_nCols; col++)
		{
			if (row == curRow && (col *3 + 1) == curCol)
				continue;
			if (m_Grid.GetItemText(row, col*3+1) == strChanel)
				return false;
		}
	}
	return true;
}
// GVN_ENDLABELEDIT
void DlgPinSettingEdit::OnGridEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;
	//Trace(_T("End Edit on row %d, col %d\n"), pItem->iRow, pItem->iColumn);

	if (m_Grid.GetItemState(pItem->iRow, pItem->iColumn) & GVIS_READONLY)
	{
		*pResult = -1;
		return;
	}
	CString strText = m_Grid.GetItemText(pItem->iRow, pItem->iColumn);
	//CString Mess;
	//Mess.Format(_T("Row %d, col %d"), pItem->iRow, pItem->iColumn);
	//MessageBox(Mess, _T(""));
	if ((pItem->iColumn - 2) % 3 == 0) {
		*pResult = 0;
		return;
	}

	if (strText.Find(_T("Không chọn")) != -1)
	{
		m_Grid.SetItemText(pItem->iRow, pItem->iColumn, _T(""));
		m_Grid.SetItemBkColour(pItem->iRow, pItem->iColumn, CLR_DEFAULT);
		m_Grid.SetItemFgColour(pItem->iRow, pItem->iColumn, RGB(0, 0, 0));
		//m_Grid.SetItemImage(pItem->iRow, pItem->iColumn, -1);
	}
	else if (strText.Find(_T("Kênh")) != -1)
	{
		if (!ValidateChanel(pItem->iRow, pItem->iColumn, strText))
		{
			CString strMess;
			strMess.Format(_T("Kênh đã được lựa chọn. Tiếp tục chọn?"));
			if (AfxMessageBox(strMess, MB_OKCANCEL | MB_ICONWARNING) != 1) {
				m_Grid.SetItemText(pItem->iRow, pItem->iColumn, _T(""));
				//m_Grid.SetItemImage(pItem->iRow, pItem->iColumn, -1);
			}
			else {
				//m_Grid.SetItemBkColour(pItem->iRow, pItem->iColumn, RGB(255, 217, 217));
				m_Grid.SetItemBkColour(pItem->iRow, pItem->iColumn, CLR_DEFAULT);
				m_Grid.SetItemFgColour(pItem->iRow, pItem->iColumn, RGB(0, 0, 0));
				//m_Grid.SetItemImage(pItem->iRow, pItem->iColumn, -1);
			}
		}		
	}
	else if (strText.Find(_T("K_")) == -1)
	{
		//m_Grid.SetItemText(pItem->iRow, pItem->iColumn, _T(""));
		*pResult = -1;
		return;
	}
	*pResult = (m_bRejectEditAttempts) ? -1 : 0;
	return;
}


void DlgPinSettingEdit::OnBnClickedBtnSave()
{
	// TODO: Add your control notification handler code here
	if (m_User) {
		MessageBox(_T("Không thực thiện chức năng này"), _T("Thông báo"));
		return;
	}
	UpdateGridToStruct();
	
	m_pPlan->Save_TestCaseConfig(m_pCIniReader, 0);
	MessageBox(_T("Ghi dữ liệu thành công"), _T("Thông báo"));
}


void DlgPinSettingEdit::OnBnClickedBtnExit()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void DlgPinSettingEdit::OnBnClickedBtnReset()
{
	// TODO: Add your control notification handler code here
	OnPinSettingEditFileNew();
}
