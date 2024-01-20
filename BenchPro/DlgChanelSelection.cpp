// DlgChanelSelection.cpp : implementation file
//

#include "pch.h"
#include "BenchPro.h"
#include "afxdialogex.h"
#include "DlgChanelSelection.h"


// DlgChanelSelection dialog

IMPLEMENT_DYNAMIC(DlgChanelSelection, CDialogEx)

DlgChanelSelection::DlgChanelSelection(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CHANEL_SELECTION, pParent)
	, m_DeviceName(_T(""))
	, m_BoardName(_T(""))
	, m_Edit_ID_Jack(_T(""))
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

	m_Cellfont = new CFont;
	m_Cellfont->CreateFont(
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

DlgChanelSelection::~DlgChanelSelection()
{
	if (m_font)
		delete m_font;
	if (m_Cellfont)
		delete m_Cellfont;
	
}

void DlgChanelSelection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEVICENAME, m_DeviceName);
	DDX_Text(pDX, IDC_EDIT_BOARD_NAME, m_BoardName);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Control(pDX, IDC_BTN1, m_BTN1);
	DDX_Control(pDX, IDC_BTN2, m_BTN2);
	DDX_Control(pDX, IDC_BTN3, m_BTN3);
	DDX_Control(pDX, IDC_BTN4, m_BTN4);
	DDX_Control(pDX, IDC_BTN5, m_BTN5);
	DDX_Control(pDX, IDC_BTN6, m_BTN6);
	DDX_Control(pDX, IDC_BTN7, m_BTN7);
	DDX_Control(pDX, IDC_BTN8, m_BTN8);
	DDX_Text(pDX, IDC_EDIT_CHANEL_ID_JACK, m_Edit_ID_Jack);
}


BEGIN_MESSAGE_MAP(DlgChanelSelection, CDialogEx)
	ON_COMMAND(ID_FILE_NEW, &DlgChanelSelection::OnFileNew)
	ON_COMMAND(ID_FILE_SAVE, &DlgChanelSelection::OnFileSave)
	ON_COMMAND(ID_FILE_SAVEEXIT, &DlgChanelSelection::OnFileSaveexit)
	ON_COMMAND(ID_EXIT, &DlgChanelSelection::OnExit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	//ON_NOTIFY(GVN_SELCHANGING, IDC_GRID, OnGridEndEdit)
	//ON_NOTIFY(GVN_SELCHANGED, IDC_GRID, OnGridEndEdit)
	
	ON_BN_CLICKED(IDC_BTN_THOAT, &DlgChanelSelection::OnBnClickedBtnThoat)
	ON_BN_CLICKED(IDC_BTN_SAVE, &DlgChanelSelection::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_RESET, &DlgChanelSelection::OnBnClickedBtnReset)
END_MESSAGE_MAP()


// DlgChanelSelection message handlers
BOOL DlgChanelSelection::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization here
	m_Edit_ID_Jack = sTringArr_IDJack[m_pPlan->mTestCase.mID_Jack];
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

	POWERS_STRUCT* p_Powers;
	p_Powers = &(m_pPlan->mTestCase.mPowers);
	CString strtmp;
	OnFileOpenLogic();
	strtmp.Format(_T("%0.2f"), p_Powers->POWER[1].USet);
	m_BTN1.SetWindowTextW(_T("P1+\n\r") + strtmp + _T("V"));
	strtmp.Format(_T("%0.2f"), p_Powers->POWER[2].USet);
	m_BTN2.SetWindowTextW(_T("P2+\n\r") + strtmp + _T("V"));
	strtmp.Format(_T("%0.2f"), p_Powers->POWER[3].USet);
	m_BTN3.SetWindowTextW(_T("P3+\n\r") + strtmp + _T("V"));
	strtmp.Format(_T("%0.2f"), p_Powers->POWER[4].USet);
	m_BTN4.SetWindowTextW(_T("P4+\n\r") + strtmp + _T("V"));
	strtmp.Format(_T("%0.2f"), p_Powers->POWER[5].USet);
	m_BTN5.SetWindowTextW(_T("P5+\n\r") + strtmp + _T("V"));
	strtmp.Format(_T("%0.2f"), p_Powers->POWER[6].USet);
	m_BTN6.SetWindowTextW(_T("P1-\n\r") + strtmp + _T("V"));
	strtmp.Format(_T("%0.2f"), p_Powers->POWER[7].USet);
	m_BTN7.SetWindowTextW(_T("P2-\n\r") + strtmp + _T("V"));
	strtmp.Format(_T("%0.2f"), p_Powers->POWER[8].USet);
	m_BTN8.SetWindowTextW(_T("P3-\n\r") + strtmp + _T("V"));
	//------------------------
	CBitmap cBmpON, cBmpOFF;
	cBmpON.LoadBitmap(IDB_BITMAP_ON);
	cBmpOFF.LoadBitmap(IDB_BITMAP_OFF);

	if (p_Powers->POWER[1].ON_OFF) m_BTN1.SetBitmap(cBmpON); else m_BTN1.SetBitmap(cBmpOFF);
	if (p_Powers->POWER[2].ON_OFF) m_BTN2.SetBitmap(cBmpON); else m_BTN2.SetBitmap(cBmpOFF);
	if (p_Powers->POWER[3].ON_OFF) m_BTN3.SetBitmap(cBmpON); else m_BTN3.SetBitmap(cBmpOFF);
	if (p_Powers->POWER[4].ON_OFF) m_BTN4.SetBitmap(cBmpON); else m_BTN4.SetBitmap(cBmpOFF);
	if (p_Powers->POWER[5].ON_OFF) m_BTN5.SetBitmap(cBmpON); else m_BTN5.SetBitmap(cBmpOFF);
	if (p_Powers->POWER[6].ON_OFF) m_BTN6.SetBitmap(cBmpON); else m_BTN6.SetBitmap(cBmpOFF);
	if (p_Powers->POWER[7].ON_OFF) m_BTN7.SetBitmap(cBmpON); else m_BTN7.SetBitmap(cBmpOFF);
	if (p_Powers->POWER[8].ON_OFF) m_BTN8.SetBitmap(cBmpON); else m_BTN8.SetBitmap(cBmpOFF);
	cBmpON.DeleteObject();
	cBmpOFF.DeleteObject();

	GetPowerArray(arrSelect);
	//-------------------------------
	if (m_User) {
		CMenu* pMenu = GetMenu();
		if (pMenu) {
			CMenu* pSubMenu = pMenu->GetSubMenu(0);
			if (pSubMenu) {
				pSubMenu->EnableMenuItem(ID_FILE_NEW, true);
				pSubMenu->EnableMenuItem(ID_FILE_SAVE, true);
				pSubMenu->EnableMenuItem(ID_FILE_SAVEEXIT, true);
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
void DlgChanelSelection::OnFileNew()
{
	// TODO: Add your command handler code here
	if (m_User) {
		MessageBox(_T("Không thực thiện chức năng này"), _T("Thông báo"));
		return;
	}

	CString strMess;
	strMess.Format(_T("Chắc chắn xóa hết thiết lập chọn kênh. Tiếp tục chọn?"));
	if (AfxMessageBox(strMess, MB_OKCANCEL | MB_ICONWARNING) != 1) return;

	m_pPlan->New_ChanelGridArr();
	OnFileOpenLogic();
	UpdateData(false);
}


void DlgChanelSelection::OnFileSave()
{
	// TODO: Add your command handler code here
	if (m_User) {
		MessageBox(_T("Không thực thiện chức năng này"), _T("Thông báo"));
		return;
	}
	
	UpdateGridToStruct();

	m_pPlan->Save_TestCaseConfig(m_pCIniReader, 0);
	MessageBox(_T("Ghi dữ liệu thành công"), _T("Thông báo"));

}


void DlgChanelSelection::OnFileSaveexit()
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

void DlgChanelSelection::GetPowerArray(CStringArray& arrStr) const
{
	CString str;
	arrStr.Add(_T("Không chọn"));
	arrStr.Add(_T("P1+"));
	arrStr.Add(_T("P2+"));
	arrStr.Add(_T("P3+"));
	arrStr.Add(_T("P4+"));
	arrStr.Add(_T("P5+"));
	arrStr.Add(_T("P1-"));
	arrStr.Add(_T("P2-"));
	arrStr.Add(_T("P3-"));

	arrStr.Add(_T("GND"));
	arrStr.Add(_T("LOGIC_IN"));
	arrStr.Add(_T("LOGIC_IN_P.Up"));
	arrStr.Add(_T("LOGIC_OUT"));
	arrStr.Add(_T("CLK_OUT"));
}
int DlgChanelSelection::PowerStringToNum(CString strTmp, CStringArray &arrStr) {
	for (int i = 0; i < arrStr.GetSize(); i++)
	{
		if (strTmp == arrStr.GetAt(i)) return i;
		
	}
	return 0;
}

CString  DlgChanelSelection::NumToPowerString(int i, CStringArray & arrStr){
 return arrStr.GetAt(i);
}
bool DlgChanelSelection::SplitString(const CString& strText,
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
//-----------------------------------------------------------
void DlgChanelSelection::setAtrGrid(int row, int col, CString strtmp) {
	m_Grid.SetItemText(row, col * 3 + 1, strtmp);
	//----------------------
	if (strtmp.Find(_T("+")) != -1) {
		m_Grid.SetItemBkColour(row, col * 3 + 1, RGB(255, 217, 217));
		m_Grid.SetItemFgColour(row, col * 3 + 1, RGB(255, 0, 0));
		m_Grid.SetItemImage(row, col * 3 + 1, -1);
	}
	else if (strtmp.Find(_T("-")) != -1) {
		m_Grid.SetItemBkColour(row, col * 3 + 1, RGB(182, 241, 200));
		m_Grid.SetItemFgColour(row, col * 3 + 1, RGB(63, 72, 204));
		m_Grid.SetItemImage(row, col * 3 + 1, -1);
	}
	else if (strtmp.Find(_T("GND")) != -1) {
		m_Grid.SetItemBkColour(row, col * 3 + 1, RGB(162, 183, 213));
		m_Grid.SetItemFgColour(row, col * 3 + 1, RGB(0, 0, 0));
		m_Grid.SetItemImage(row, col * 3 + 1, 1);
	}

	else if (strtmp.Find(_T("No")) != -1) {
		m_Grid.SetItemBkColour(row, col * 3 + 1, RGB(255, 255, 255));
		m_Grid.SetItemFgColour(row, col * 3 + 1, RGB(0, 0, 0));
		m_Grid.SetItemImage(row, col * 3 + 1, -1);
	}
	else if (strtmp.Find(_T("LOGIC_IN_P.Up")) != -1) {
		m_Grid.SetItemBkColour(row, col * 3 + 1, CLR_DEFAULT);
		m_Grid.SetItemFgColour(row, col * 3 + 1, RGB(0, 0, 0));
		m_Grid.SetItemImage(row, col * 3 + 1, 11);
	}
	else if (strtmp.Find(_T("LOGIC_IN")) != -1) {
		m_Grid.SetItemBkColour(row, col * 3 + 1, CLR_DEFAULT);
		m_Grid.SetItemFgColour(row, col * 3 + 1, RGB(0, 0, 0));
		m_Grid.SetItemImage(row, col * 3 + 1, 5);
	}
	else if (strtmp.Find(_T("LOGIC_OUT")) != -1) {
		m_Grid.SetItemBkColour(row, col * 3 + 1, CLR_DEFAULT);
		m_Grid.SetItemFgColour(row, col * 3 + 1, RGB(0, 0, 0));
		m_Grid.SetItemImage(row, col * 3 + 1, 4);
	}
	else if (strtmp.Find(_T("CLK_OUT")) != -1) {
		m_Grid.SetItemBkColour(row, col * 3 + 1, CLR_DEFAULT);
		m_Grid.SetItemFgColour(row, col * 3 + 1, RGB(0, 0, 0));
		m_Grid.SetItemImage(row, col * 3 + 1, 10);
	}
	else if (strtmp.Find(_T("K_")) != -1) {
		m_Grid.SetItemBkColour(row, col * 3 + 1, RGB(237, 162, 187));
		m_Grid.SetItemFgColour(row, col * 3 + 1, RGB(255, 0, 0));
		m_Grid.SetItemImage(row, col * 3 + 1, -1);
	}
		else if (strtmp.Find(_T("K_GND")) != -1) {
		m_Grid.SetItemBkColour(row, col * 3 + 1, RGB(63, 72, 204));
		m_Grid.SetItemFgColour(row, col * 3 + 1, RGB(0, 0, 0));
		m_Grid.SetItemImage(row, col * 3 + 1, 1);
	}
	else {
		m_Grid.SetItemBkColour(row, col * 3 + 1, RGB(255, 255, 255));
		m_Grid.SetItemFgColour(row, col * 3 + 1, RGB(0, 0, 0));
		m_Grid.SetItemImage(row, col * 3 + 1, -1);
	}
}
//-----------------------------------------------------------
void DlgChanelSelection::OnFileOpenLogic()
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
			m_Grid.SetColumnCount(m_nCols * 3);
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
	GetPowerArray(arrSelect);
	bool isFont = true;
	LOGFONT lf;
	isFont = (m_font->GetLogFont(&lf) != 0);
	LOGFONT Celllf;
	bool isCellFont = true;
	isCellFont = (m_Cellfont->GetLogFont(&Celllf) != 0);

	//---------------------------------------
	//GUI
	for (int col = 0; col < m_nCols; col++) {
		m_Grid.SetItemText(0, col * 3, m_pPlan->mTestCase.mTestCaseConfig.GUIGridArr[0][col]);
		if (isFont)
			m_Grid.SetItemFont(0, col * 3, &lf);
	}
	for (int col = 0; col < m_nCols; col++) {
		m_Grid.SetItemText(0, col * 3 + 1, _T(".       Power-logic      ."));
		m_Grid.SetItemText(0, col * 3 + 2, _T(".      Tên chân     ."));
		if (isFont) {
			m_Grid.SetItemFont(0, col * 3 + 1, &lf);
			m_Grid.SetItemFont(0, col * 3 + 2, &lf);

		}
	}
	//-------------
	for (int row = 1; row < m_nRows; row++) {
		for (int col = 0; col < m_nCols; col++) {
			if (m_pPlan->mTestCase.mTestCaseConfig.PinGridArr[row][col] !=-1) {
				m_Grid.SetItemText(row, col * 3, m_pPlan->mTestCase.mTestCaseConfig.GUIGridArr[row][col]);
				m_Grid.SetItemImage(row, col * 3, 0);
				if (isFont)
					m_Grid.SetItemFont(row, col * 3, &lf);
			}
		}
	}
	//----------------------------------------
	// Data
	int iPintmp, _iChaneltmp;
	CString strtmp, strNametmp;
	
	for (int row = 1; row < m_nRows; row++)
	{
		for (int col = 0; col < m_nCols; col++)
		{
			if (m_User) m_Grid.SetItemState(row, col * 3 + 1, GVIS_READONLY);

			m_Grid.SetItemState(row, col * 3 + 2, GVIS_READONLY);
			iPintmp = m_pPlan->mTestCase.mTestCaseConfig.PinGridArr[row][col];
			
			if (iPintmp <= 0)
				m_Grid.SetItemState(row, col * 3 + 1, GVIS_READONLY);
			else if (iPintmp > 103) {

			}
			else if (iPintmp >= 100) {
				setAtrGrid(row, col, sTringArr_ExtrChl[iPintmp-100]);
			}
			else if(iPintmp >=1)
			{
				_iChaneltmp = m_pPlan->mTestCase.mTestCaseConfig.ChanelGridArr[row][col];
				if (_iChaneltmp == 0) strtmp.Format(_T("Kênh %d"), iPintmp);
				else strtmp.Format(_T("%s"), NumToPowerString(_iChaneltmp, arrSelect));

				setAtrGrid(row, col, strtmp);
				//----------------------
				if (!m_Grid.SetCellType(row, col * 3 + 1, RUNTIME_CLASS(CGridCellCombo)))
					return;
				CGridCellCombo* pCell = dynamic_cast<CGridCellCombo*>(m_Grid.GetCell(row, col * 3 + 1));
				pCell->SetStyle(CBS_DROPDOWNLIST);
				pCell->SetOptions(arrSelect);
				if (isCellFont)
					pCell->SetFont(&Celllf);
			}
			//-----------------------
			strNametmp.Format(_T("%s"), m_pPlan->mTestCase.mTestCaseConfig.PinNameGridArr[row][col]);
			if (iPintmp < 0) {
				m_Grid.SetItemText(row, col * 3 + 2, _T(""));
			}
			else {
				m_Grid.SetItemText(row, col * 3 + 2, strNametmp);
			}
			if (isCellFont)
				m_Grid.SetItemFont(row, col * 3 + 2, &Celllf);

		}
	}
	m_Grid.AutoSize();
	m_Grid.SetCallbackFunc(NULL, 0);
	m_Grid.AllowReorderColumn(FALSE); // implemented now only if m_bCallback	
	m_Grid.Refresh();
}
//-----------------------------------------------------
void DlgChanelSelection::UpdateGridToStruct() {
	// Update Struct
	UpdateData(TRUE);
	if (m_pPlan == NULL)
		return;
	//-------------------------------
	// Update ChanelGridArr[256][100]; 


	int nRows, nCols;
	nRows = m_pPlan->mTestCase.mTestCaseConfig.ArrRows;
	nCols = m_pPlan->mTestCase.mTestCaseConfig.ArrCols;
	CString strTmp;
	int itmp;
	for (int row = 1; row < nRows; row++)
	{
		for (int col = 0; col < nCols; col++)
		{
			strTmp = m_Grid.GetItemText(row, col * 3 + 1);
			if (strTmp.IsEmpty()) itmp = 0;
			else
				itmp = PowerStringToNum(strTmp, arrSelect);
			m_pPlan->mTestCase.mTestCaseConfig.ChanelGridArr[row][col] = itmp;
		}
	}
	//----------------------------
	// Update 3- ChanelConfigArr
	//----------------------------
	int _nChanels = m_pPlan->mTestCase.mTestCaseConfig.nChanels;

	for (int i = 1; i <= _nChanels; i++) {
		m_pPlan->mTestCase.mTestCaseConfig.ChanelGridConfigArr[i] = 0;
		m_pPlan->mTestCase.mTestCaseConfig.ChanelConfigArr[i] = 0;
		m_pPlan->mTestCase.mTestCaseConfig.ChanelPUPConfigArr[i] = 0;
	}

	int _iChanel;
	int _valueTmp;

	for (int col = 0; col < nCols; col++)
	{
		for (int row = 1; row < nRows; row++)
		{
			_iChanel = m_pPlan->mTestCase.mTestCaseConfig.PinGridArr[row][col];
			if ((_iChanel > 0) && (_iChanel <= 84)) {
				_valueTmp = m_pPlan->mTestCase.mTestCaseConfig.ChanelGridArr[row][col];
				m_pPlan->mTestCase.mTestCaseConfig.ChanelGridConfigArr[_iChanel] = _valueTmp;
				m_pPlan->mTestCase.mTestCaseConfig.ChanelConfigArr[_iChanel] = _valueTmp;
				if (_valueTmp == 11) m_pPlan->mTestCase.mTestCaseConfig.ChanelPUPConfigArr[_iChanel] = 1;
				if (_valueTmp >= 11) m_pPlan->mTestCase.mTestCaseConfig.ChanelConfigArr[_iChanel] --;
			}
		}
	}

}

void DlgChanelSelection::OnExit()
{
	// TODO: Add your command handler code here
	CDialogEx::OnOK();
}
bool DlgChanelSelection::ValidateChanel(int curRow, int curCol, const CString& strChanel) const
{
	for (int row = 1; row <= m_nRows; row++)
	{
		for (int col = 0; col < m_nCols; col++)
		{
			if (row == curRow && col == curCol)
				continue;
			if (m_Grid.GetItemText(row, col) == strChanel)
				return false;
		}
	}
	return true;
}
// GVN_ENDLABELEDIT
void DlgChanelSelection::OnGridEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;
	//Trace(_T("End Edit on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	TESTCASE_CONFIG* p_TestCaseConfig;
	p_TestCaseConfig = &m_pPlan->mTestCase.mTestCaseConfig;

	if (m_Grid.GetItemState(pItem->iRow, pItem->iColumn) & GVIS_READONLY)
	{
		*pResult = -1;
		return;
	}

	int nRows = p_TestCaseConfig->ArrRows;
	int nCols = p_TestCaseConfig->ArrCols;
	int nCount = 0;
	int itmp = p_TestCaseConfig->PinGridArr[pItem->iRow][(pItem->iColumn-1)/3];
	//-------------------
	//CString strMess1;
	//strMess1.Format(_T("row %d; colum %d"), pItem->iRow, pItem->iColumn);
	//MessageBox(strMess1, _T("Mess"));
	//-------------------
	//-------------------
	CString m_strTmp;
	CString strMess = _T("Các chân sau sẽ thay đổi thuộc tính: ");
	int m_iPin = 0;

	for (int col = 0; col < nCols; col++)
	{	
		for (int row = 1; row < nRows; row++)
		{
			if (p_TestCaseConfig->PinGridArr[row][col] >=0) {
				m_iPin++;
				if (p_TestCaseConfig->PinGridArr[row][col] == itmp) {
					m_strTmp.Format(_T(" %d;"), m_iPin);
					strMess = strMess + m_strTmp;
					nCount++;
				}
			}
		}
	}
	strMess = strMess + _T(" Tiếp tục chọn?");

	CString strText = m_Grid.GetItemText(pItem->iRow, pItem->iColumn);
	if (nCount == 1) {
		setAtrGrid(pItem->iRow, (pItem->iColumn-1)/3, strText);
	}

	if (nCount > 1) {
		if (AfxMessageBox(strMess, MB_OKCANCEL | MB_ICONWARNING) == 1) {
			for (int col = 0; col < nCols; col++) {
				for (int row = 1; row < nRows; row++) {
					if (p_TestCaseConfig->PinGridArr[row][col] == itmp) {
						setAtrGrid(row, col, strText);
					}
				}
			}
		}
		else{
			for (int col = 0; col < nCols; col++) {
				for (int row = 1; row < nRows; row++) {
					if (p_TestCaseConfig->PinGridArr[row][col] == itmp) {
						if ((col*3+1 != pItem->iColumn) || (row != pItem->iRow)) {
							m_Grid.SetItemText(pItem->iRow, pItem->iColumn, m_Grid.GetItemText(row, col * 3 + 1));
							col = nCols;
							row = nRows;
						}
					}
				}
			}
		}
	}
	//m_Grid.SetCallbackFunc(NULL, 0);
	//m_Grid.AllowReorderColumn(FALSE); 
	m_Grid.Refresh();
	m_Grid.SetFocusCell(pItem->iRow, pItem->iColumn);
	//m_Grid.nLButtonUp(UINT nFlags, CPoint point)
	//----------kiểm tra 1-40, 41-80---------------------------
	 LOGFONT Celllf;
	bool isCellFont = true;
	isCellFont = (m_Cellfont->GetLogFont(&Celllf) != 0);
	//-----------Lay gia trị hiện thoi------------------
	//int nRows, nCols;
	nRows = p_TestCaseConfig->ArrRows;
	nCols = p_TestCaseConfig->ArrCols;
	//int itmp;
	CString strTmp;
	for (int row = 1; row < nRows; row++)
	{
		for (int col = 0; col < nCols; col++)
		{
			strTmp = m_Grid.GetItemText(row, col * 3 + 1);
			if (strTmp.IsEmpty()) itmp = 0;
			else
				itmp = PowerStringToNum(strTmp, arrSelect);
			p_TestCaseConfig->PreChanelGridArr[row][col] = p_TestCaseConfig->ChanelGridArr[row][col];
			p_TestCaseConfig->ChanelGridArr[row][col] = itmp;
		}
	}
	//-------------------------------
	//--- Check ---------------------
	//-------------------------------
	for (int i = 1; i <= 8; i++) {
		mPower1_40[i] = false;
		mPower41_80[i] = false;
	}
	//-------------------------------
	int mvalue;
	for (int row = 1; row < nRows; row++)
	{
		for (int col = 0; col < nCols; col++)
		{
			mvalue = p_TestCaseConfig->ChanelGridArr[row][col];
			if (mvalue >= 1 && mvalue <= 8)
				if (p_TestCaseConfig->PinGridArr[row][col] <= 40) mPower1_40[mvalue] = true;
				else mPower41_80[mvalue] = true;
		}
	}
	int s_Power1_40 = 0, s_Power41_80 = 0;
	for (int i = 1; i <= 8; i++) {
		if(mPower1_40[i]) s_Power1_40++;
		if(mPower41_80[i]) s_Power41_80++;
	}
	if (s_Power1_40 > 4 || s_Power41_80 > 4) {
		if (s_Power1_40 > 4)
			MessageBox( _T("Từ kênh 1->40 chỉ được thiết lập tối đa 4 loại nguồn"), _T("Thông báo"));
		if (s_Power41_80 > 4)
			MessageBox(_T("Từ kênh 41->80 chỉ được thiết lập tối đa 4 loại nguồn"), _T("Thông báo"));
		//--------- Pre grid ---------------------
		for (int row = 1; row < nRows; row++)
		{
			for (int col = 0; col < nCols; col++)
			{
				p_TestCaseConfig->ChanelGridArr[row][col] = p_TestCaseConfig->PreChanelGridArr[row][col];
			}
		}
		//----------------------------------------
		// Data
		int iPintmp, _iChaneltmp;
		CString strtmp, strNametmp;
		for (int row = 1; row < m_nRows; row++)
		{
			for (int col = 0; col < m_nCols; col++)
			{
				//if (m_User) m_Grid.SetItemState(row, col * 3 + 1, GVIS_READONLY);

				//m_Grid.SetItemState(row, col * 3 + 2, GVIS_READONLY);
				iPintmp = m_pPlan->mTestCase.mTestCaseConfig.PinGridArr[row][col];

				if (iPintmp <= 0)
					m_Grid.SetItemState(row, col * 3 + 1, GVIS_READONLY);
				else if (iPintmp >= 1)
				{
					_iChaneltmp = m_pPlan->mTestCase.mTestCaseConfig.ChanelGridArr[row][col];
					if (_iChaneltmp == 0) strtmp.Format(_T("Kênh %d"), iPintmp);
					else strtmp.Format(_T("%s"), NumToPowerString(_iChaneltmp, arrSelect));

					setAtrGrid(row, col, strtmp);
					//----------------------
					if (!m_Grid.SetCellType(row, col * 3 + 1, RUNTIME_CLASS(CGridCellCombo)))
						return;
					CGridCellCombo* pCell = dynamic_cast<CGridCellCombo*>(m_Grid.GetCell(row, col * 3 + 1));
					pCell->SetStyle(CBS_DROPDOWNLIST);
					pCell->SetOptions(arrSelect);
					if (isCellFont)
						pCell->SetFont(&Celllf);
				}
				//-----------------------
				//strNametmp.Format(_T("%s"), m_pPlan->mTestCase.mTestCaseConfig.PinNameGridArr[row][col]);
				//if (iPintmp < 0) {
				//	m_Grid.SetItemText(row, col * 3 + 2, _T(""));
				//}
				//else {
				//	m_Grid.SetItemText(row, col * 3 + 2, strNametmp);
				//}
				//if (isCellFont)
				//	m_Grid.SetItemFont(row, col * 3 + 2, &Celllf);

			}
		}
		m_Grid.Refresh();
		m_Grid.SetFocusCell(pItem->iRow, pItem->iColumn);
		//-----------------------------------------
	}
	//----------------------------------------------------------
	//--------------------------------------
	//UpdateGridToStruct();
	*pResult = (m_bRejectEditAttempts) ? -1 : 0;
}


void DlgChanelSelection::OnBnClickedBtnThoat()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void DlgChanelSelection::OnBnClickedBtnSave()
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


void DlgChanelSelection::OnBnClickedBtnReset()
{
	// TODO: Add your control notification handler code here
	OnFileNew();
}
