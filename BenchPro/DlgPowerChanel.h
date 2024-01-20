#pragma once
#include "afxdialogex.h"
//#include "./GridCtrl_src/GridCtrl.h"
#include "INI.h"
#include <vector>
#include <map>

// DlgPowerChanel dialog

class DlgPowerChanel : public CDialogEx
{
	DECLARE_DYNAMIC(DlgPowerChanel)
private:
	struct DevideData
	{
		CString Name;
		unsigned int numChanels;
		unsigned int numPowerP, numPowerN;
	};
	struct PowerData
	{
		CString Name;
		double Volts[16];
		double Amp[16];
	};
	struct ConnectorData
	{
		CString portName;
		int numPosition;
		int numRows;
	};
	struct RouterData
	{
		CString portName;
		CString chanelName;
		CString powerName;
	};
public:
	DlgPowerChanel(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgPowerChanel();

	//CGridCtrl m_Grid;
	CString m_Name;
	CComboBox m_ComboBoxDevide;
	CComboBox m_ComboBoxPower;
	CIniReader* m_pCIniReader;
	std::vector<DevideData> m_vecDevide;
	std::vector<PowerData> m_vecPower;
	std::vector<ConnectorData> m_vecConnector;
	std::map<CString, RouterData> m_mapRouter;

	CSize m_OldSize;
	CImageList m_ImageList;
	CToolBar m_ToolBar;
	CStatusBar m_StatusBar;
	int m_nCols, m_nRows, m_nFixCols, m_nFixRows;
	bool m_bRejectEditAttempts;
	CFont* m_font;
	bool m_isNew;
	unsigned int m_numChanel;
	CStringArray m_arrPower;
	CString m_GUID;
	CString m_Devide, m_Power;
	bool m_ModeEdit;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POWER_CHANEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	//virtual BOOL OnInitDialog();
private:
	bool GetDevide();
	bool GetPower();
	void CreateStatusBar();
	bool ValidateChanel(int curRow, int curCol, const CString& strChanel) const;
	bool SplitString(const CString& strText,
		UINT uNumSegments,
		CStringArray& rAryStrSegments,
		TCHAR zChar) const;
	unsigned int SetEditPower(const CString& strPower);
	void GetChanels(const CString& strNameDevide, std::map<CString, CString>& mapChanels) const;
//public:
//	afx_msg void OnCbnSelchangeComboDevide();
//	afx_msg void OnCbnSelchangeComboPower();
//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnGridDblClick(NMHDR* pNotifyStruct, LRESULT* pResult);
//	afx_msg void OnGridClick(NMHDR* pNotifyStruct, LRESULT* pResult);
//	afx_msg void OnGridRClick(NMHDR* pNotifyStruct, LRESULT* pResult);
//	afx_msg void OnGridStartEdit(NMHDR* pNotifyStruct, LRESULT* pResult);
//	afx_msg void OnGridEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult);
//	afx_msg void OnGridStartSelChange(NMHDR* pNotifyStruct, LRESULT* pResult);
//	afx_msg void OnGridEndSelChange(NMHDR* pNotifyStruct, LRESULT* pResult);
//	afx_msg void OnGridBeginDrag(NMHDR* pNotifyStruct, LRESULT* pResult);
//	afx_msg void OnEditPw1p();
//	afx_msg void OnEditPw2p();
//	afx_msg void OnEditPw3p();
//	afx_msg void OnEditPw4p();
//	afx_msg void OnEditPw5p();
//	afx_msg void OnEditPw6p();
//	afx_msg void OnEditPw7p();
//	afx_msg void OnEditPw8p();
//	afx_msg void OnEditPw9p();
//	afx_msg void OnEditPw10p();
//	afx_msg void OnEditPw1n();
//	afx_msg void OnEditPw2n();
//	afx_msg void OnEditPw3n();
//	afx_msg void OnEditPw4n();
//	afx_msg void OnEditPw5n();
//	afx_msg void OnEditPw6n();
//	afx_msg void OnPowersupllyGnd();
//	afx_msg void OnPowersupllyNoconnect();
//	afx_msg void OnFileSaveLogic();
//	afx_msg void OnFileOpenLogic();
//	afx_msg void OnFileSaveExit();
};
