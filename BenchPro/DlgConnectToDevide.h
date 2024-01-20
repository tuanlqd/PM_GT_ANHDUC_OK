#pragma once

#include "INI.h"
#include "afxdialogex.h"


// DlgConnectToDevide dialog

class DlgConnectToDevide : public CDialogEx
{
	DECLARE_DYNAMIC(DlgConnectToDevide)

public:
	DlgConnectToDevide(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgConnectToDevide();

	bool Save();
	bool Restore();
	CIniReader* m_pCIniReader;
	CImageList	m_cImageListNormal;
	CListCtrl m_ListConnect;

	CFont* p_sfont;
	CFont* p_bfont;
	CFont* p_nfont;
	CFont* p_tfont;
	CString* pPubstrAdrressConn;
	int* pFlagConnected;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONNECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonVerify();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	afx_msg void OnLvnItemchangedListConnect(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblclkListConnect(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickListConnect(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMRClickListConnect(NMHDR* pNMHDR, LRESULT* pResult);
	CString m_Status_Connect;
};
