#pragma once
#include "afxdialogex.h"


// DlgDeviceJackPropertiesEdit dialog

class DlgDeviceJackPropertiesEdit : public CDialogEx
{
	DECLARE_DYNAMIC(DlgDeviceJackPropertiesEdit)

public:
	DlgDeviceJackPropertiesEdit(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgDeviceJackPropertiesEdit();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEVICE_JACK_PROPERTIES_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_nPinPerRow;
};
