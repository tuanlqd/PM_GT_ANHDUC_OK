#pragma once
#include "afxdialogex.h"
#include "INI.h"


// DlgDeviceProperties dialog

class DlgDeviceProperties : public CDialogEx
{
	DECLARE_DYNAMIC(DlgDeviceProperties)

public:
	DlgDeviceProperties(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgDeviceProperties();

	CIniReader *m_pCIniReader;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEVICE_PROPERTIES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl *m_ListCtrl;
	unsigned int m_CheckNameExist;

	CString m_DeviceName;
	unsigned int m_Chanel;
	unsigned int m_PWP;
	unsigned int m_PWN;
	afx_msg void OnBnClickedOk();
	bool ExistName(CString DeviceName);
};
