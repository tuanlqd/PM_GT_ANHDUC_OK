#pragma once
#include "afxdialogex.h"
#include "Plan.h"
#include "./GridCtrl_src/GridCtrl.h"
#include "NewCellTypes/GridCellCombo.h"


// DlgChanelSelection dialog

class DlgChanelSelection : public CDialogEx
{
	DECLARE_DYNAMIC(DlgChanelSelection)

public:
	DlgChanelSelection(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgChanelSelection();

	CGridCtrl m_Grid;
	CSize m_OldSize;
	CImageList m_ImageList;
	//CToolBar m_ToolBar;
	//CStatusBar m_StatusBar;
	unsigned int m_numChanel;

	int m_nCols, m_nRows, m_nFixCols, m_nFixRows;
	bool m_bRejectEditAttempts;
	CFont* m_font;
	CFont* m_Cellfont;
	CPlan* m_pPlan;
	CIniReader* m_pCIniReader;
	bool m_isNew;
	int m_User = 0;
	CString sTringArr_ExtrChl[4] = { _T("K_GND_M9"), _T("K_VCC_5V_M9"), _T("K_VCC_12V_M9"), _T("K_VCC_27V_M9") };
	CString m_Edit_ID_Jack;
	CString sTringArr_IDJack[9] = { _T("0-Jack mở rộng bên ngoài"),
									_T("1-J6_ГРПМ9 - 31 / 62ГC2 - В"),
									_T("2-J5_ГРПМ1 - 61ГО2 - В"),
									_T("3-J4_ГРПМ1 - 31ГО2 - В"),
									_T("4-J1_C09032646825"),
									_T("5-JA3_СНП34С - 46В - 21 - В"),
									_T("6-JA5_СНП34С - 90В - 21 - В"),
									_T("7-JA2_СНП34С - 135В - 21 - В"),
									_T("8-JA4_JA1_СНП34С - 90В_135B - 21 - В") };

	CStringArray arrSelect;
	//-- check trung power ----
	BOOL mPower1_40[9];
	BOOL mPower41_80[9];
	//-------------------------
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHANEL_SELECTION };
#endif
private:
	void GetPowerArray(CStringArray& arrStr) const;
	bool SplitString(const CString& strText,
		UINT uNumSegments,
		CStringArray& rAryStrSegments,
		TCHAR zChar) const;
	int PowerStringToNum(CString strTmp, CStringArray &arrStr);
	CString NumToPowerString(int i, CStringArray& arrStr);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_DeviceName;
	CString m_BoardName;

	virtual BOOL OnInitDialog();

	afx_msg void OnFileOpenLogic();
	afx_msg void InitPinChanelLogic();

	afx_msg void OnFileNew();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveexit();

	afx_msg void setAtrGrid(int row, int col, CString strtmp);
	afx_msg bool ValidateChanel(int curRow, int curCol, const CString& strChanel) const;
	afx_msg void OnGridEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void UpdateGridToStruct();
	afx_msg void OnExit();
	CButton m_BTN1;
	CButton m_BTN2;
	CButton m_BTN3;
	CButton m_BTN4;
	CButton m_BTN5;
	CButton m_BTN6;
	CButton m_BTN7;
	CButton m_BTN8;
	afx_msg void OnBnClickedBtnThoat();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnReset();
	
};
