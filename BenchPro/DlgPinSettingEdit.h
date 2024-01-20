#pragma once
#include "afxdialogex.h"
#include "Plan.h"
#include "./GridCtrl_src/GridCtrl.h"
#include "NewCellTypes/GridCellCombo.h"

// DlgPinSettingEdit dialog

//struct DesignPortData
//{
//	CString portName;
//	int numPosition;
//	int numRows;
//};

class DlgPinSettingEdit : public CDialogEx
{
	DECLARE_DYNAMIC(DlgPinSettingEdit)

public:
	DlgPinSettingEdit(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgPinSettingEdit();

	CGridCtrl m_Grid;
	CSize m_OldSize;
	CImageList m_ImageList;
	CToolBar m_ToolBar;
	CStatusBar m_StatusBar;
	unsigned int m_numChanel;

	//std::vector<DesignPortData>	m_vecData;  //DUK
	int m_nCols, m_nRows, m_nFixCols, m_nFixRows;
	bool m_bRejectEditAttempts;
	CFont* m_font;
	CIniReader* m_pCIniReader;
	CPlan* m_pPlan;
	bool m_isNew;

	int m_User = 0;

	CString sTringArr_ExtrChl[4]= { _T("K_GND_M9"), _T("K_VCC_5V_M9"), _T("K_VCC_12V_M9"), _T("K_VCC_27V_M9") };
	CString m_Edit_Jack_ID;
	CString sTringArr_IDJack[9] = { _T("0-Jack mở rộng bên ngoài"),
									_T("1-J6_ГРПМ9 - 31 / 62ГC2 - В"),
									_T("2-J5_ГРПМ1 - 61ГО2 - В"),
									_T("3-J4_ГРПМ1 - 31ГО2 - В"),
									_T("4-J1_C09032646825"),
									_T("5-JA3_СНП34С - 46В - 21 - В"),
									_T("6-JA5_СНП34С - 90В - 21 - В"),
									_T("7-JA2_СНП34С - 135В - 21 - В"),
									_T("8-JA4_JA1_СНП34С - 90В_135B - 21 - В")};
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PIN_SETTING_EDIT };
#endif
private:
	void GetArrayChanel(CStringArray& arrStr) const;
	bool SplitString(const CString& strText,
		UINT uNumSegments,
		CStringArray& rAryStrSegments,
		TCHAR zChar) const;
	int ChanelToNum(CString strTmp);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_DeviceName;
	CString m_BoardName;
	
	virtual BOOL OnInitDialog();

	afx_msg void OnPinSettingEditFileNew();
	afx_msg void OnPinSettingEditFileOpen();
	afx_msg void OnPinSettingEditFileSave();
	afx_msg void OnPinSettingEditFileSaveExit();

	afx_msg void OnFileOpenLogic();
	afx_msg void InitPinChanelLogic();

	afx_msg bool ValidateChanel(int curRow, int curCol, const CString& strChanel) const;
	afx_msg void OnGridEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void UpdateGridToStruct();
	afx_msg void OnFileExit();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnExit();
	CString m_TestName;
	afx_msg void OnBnClickedBtnReset();
	
};
