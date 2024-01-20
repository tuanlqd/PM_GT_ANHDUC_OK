
// MainFrm.h : interface of the CMainFrame class
//
#include "INI.h"
#include "Plan.h"
#pragma once

class CMainFrame : public CFrameWndEx
{
protected: // create from serialization only
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CString bmess = _T("Cần phải mở hoặc tạo mới bài test trước khi thực hiện chức năng này!");
	CString tmess = _T("Thông báo");
	CString wmess = _T("Chú ý!");
// Operations
	SocketTCP* SocketTh;
	SocketTCP* SocketPh;
	int m_pFlagPhRun;
	int m_PFlagThRun;
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = nullptr, CCreateContext* pContext = nullptr);

// Implementation
public:
	virtual ~CMainFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

	CIniReader		  m_CIniReader;
	CPlan			  m_CPlan;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnToolsConnectToDevide();
	afx_msg void OnToolsLoadTestCase();
	afx_msg void OnToolsPowerSetting();
	afx_msg void OnToolsPowerSelection();
	afx_msg void OnToolsChanelSetting();
	afx_msg void OnToolsLogicTest();

	afx_msg void OnToolsPinsetting();
	afx_msg void OnDataUpdate();
	afx_msg void OnDataBackup();
	afx_msg void OnDataTest();
	afx_msg void OnPowersettingPowerssetting();
	afx_msg void OnPowersettingPowerssafe();
	afx_msg void OnPowersettingSignparam();
	afx_msg void OnToolsLoadTestcase();
	afx_msg void OnTestconnectsystem();
	afx_msg void OnTestOnboard();

	afx_msg void OnAppExit();
};


