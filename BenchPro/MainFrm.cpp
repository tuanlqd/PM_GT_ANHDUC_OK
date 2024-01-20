
// MainFrm.cpp : implementation of the CMainFrame class

#include <iostream>

#include "pch.h"
#include "framework.h"
#include "BenchPro.h"
#include "DlgConnectToDevide.h"
#include "DlgDevideSetting.h"
#include "DlgDeviceSelection.h"
#include "MainFrm.h"
#include "DlgPinSetting.h"
#include "DlgPlanFileConfig.h"

#include "DlgPowerSetting.h"
#include "DlgPowerSettingThreshold.h"
#include "DlgPowerSettingParam.h"

#include "DlgCreateCase.h"
#include "DlgPinSettingEdit.h"
#include "DlgChanelSelection.h"

#include "DlgTestOnBoard.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)

	ON_COMMAND(ID_TOOLS_CONNECTTODEVIDE, &CMainFrame::OnToolsConnectToDevide)
	ON_COMMAND(ID_TOOLS_POWERSELECTION, &CMainFrame::OnToolsPowerSelection)
	ON_COMMAND(ID_TOOLS_CHANELSETTING, &CMainFrame::OnToolsChanelSetting)
	ON_COMMAND(ID_TOOLS_LOGICTEST, &CMainFrame::OnToolsLogicTest)
	ON_COMMAND(ID_TOOLS_PINSETTING, &CMainFrame::OnToolsPinsetting)
	ON_COMMAND(ID_NEW_PLANCONFIGFILE, &CMainFrame::OnDataUpdate)
	ON_COMMAND(ID_DATA_BACKUP, &CMainFrame::OnDataBackup)
	ON_COMMAND(ID_DATA_TEST, &CMainFrame::OnDataTest)
	ON_COMMAND(ID_POWERSETTING_POWERSSETTING, &CMainFrame::OnPowersettingPowerssetting)
	ON_COMMAND(ID_POWERSETTING_POWERSSAFE, &CMainFrame::OnPowersettingPowerssafe)
	ON_COMMAND(ID_POWERSETTING_SIGNPARAM, &CMainFrame::OnPowersettingSignparam)
	ON_COMMAND(ID_TOOLS_LOAD_TESTCASE, &CMainFrame::OnToolsLoadTestcase)
	ON_COMMAND(ID_TestConnectSystem, &CMainFrame::OnTestconnectsystem)
	ON_COMMAND(ID_TEST_ONBOARD, &CMainFrame::OnTestOnboard)
	ON_COMMAND(ID_APP_EXIT, &CMainFrame::OnAppExit)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	// TODO: add member initialization code here
 	
}
CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// Allow user-defined toolbars operations:
	InitUserToolbars(nullptr, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Enable toolbar and docking window menu replacement
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// enable quick (Alt+drag) toolbar customization
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == nullptr)
	{
		// load user-defined toolbar images
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// enable menu personalization (most-recently used commands)
	// TODO: define your own basic commands, ensuring that each pulldown menu has at least one basic command.
	CList<UINT, UINT> lstBasicCommands;
	//DUK
	//lstBasicCommands.AddTail(ID_FILE_NEW);
	//lstBasicCommands.AddTail(ID_FILE_OPEN);
	//lstBasicCommands.AddTail(ID_FILE_SAVE);
	//lstBasicCommands.AddTail(ID_FILE_PRINT);
	//lstBasicCommands.AddTail(ID_APP_EXIT);
	//lstBasicCommands.AddTail(ID_EDIT_CUT);
	//lstBasicCommands.AddTail(ID_EDIT_PASTE);
	//lstBasicCommands.AddTail(ID_EDIT_UNDO);
	//lstBasicCommands.AddTail(ID_APP_ABOUT);
	//lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	//lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);
	m_CIniReader.setINIFileName(_T("Config.ini"));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	return lres;
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
	// base class does the real work
	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	// enable customization button for all user toolbars
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != nullptr)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
			//pUserToolbar->EnableCustomizeButton(FALSE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}
	return TRUE;
}


void CMainFrame::OnToolsConnectToDevide()
{
	// TODO: Add your command handler code here
	// DUKKK Delete late

	DlgConnectToDevide mDlgConnectToDevide;
	mDlgConnectToDevide.m_pCIniReader = &m_CIniReader;

	/* CString strIp;
	 int portDev,portLocal;
	 GetIPConfig(strIp, portDev, portLocal);*/
	if (mDlgConnectToDevide.DoModal() == IDOK)
	{
		//connect
	}
}

void CMainFrame::OnToolsPowerSelection()
{
	MessageBox(_T("PowerSelection"), _T("Message"));

}
void CMainFrame::OnToolsChanelSetting()
{
	if (m_CPlan.OrderRun < 0) {
		MessageBox(bmess, tmess);
		return;
	}
	DlgChanelSelection mDlgChanelSelection;
	mDlgChanelSelection.m_pPlan = &m_CPlan;
	mDlgChanelSelection.m_pCIniReader = &m_CIniReader;
	mDlgChanelSelection.m_DeviceName = m_CPlan.mTestCase.mPathInfo.DeviceName;
	mDlgChanelSelection.m_BoardName = m_CPlan.mTestCase.mPathInfo.BoardName;
	mDlgChanelSelection.DoModal();
}
void CMainFrame::OnToolsLogicTest()
{
	//MessageBox(_T("Cần phải mở hoặc tạo mới bài test trước khi thực hiện chức năng này!"), _T("Thông báo"));
}


void CMainFrame::OnToolsPinsetting()
{
	// TODO: Add your command handler code here
	if (m_CPlan.OrderRun < 0) {
		MessageBox(bmess, tmess);
		return;
	}
	DlgPinSettingEdit mDlgPinSettingEdit;
	mDlgPinSettingEdit.m_pPlan = &m_CPlan;
	mDlgPinSettingEdit.m_pCIniReader = &m_CIniReader;
	mDlgPinSettingEdit.m_DeviceName = m_CPlan.mTestCase.mPathInfo.DeviceName;
	mDlgPinSettingEdit.m_BoardName = m_CPlan.mTestCase.mPathInfo.BoardName;
	mDlgPinSettingEdit.DoModal();
}

void CMainFrame::OnDataUpdate()
{
	// TODO: Add your command handler code here
	DlgPlanFileConfig mDlgPlanFileConfig;
	mDlgPlanFileConfig.m_pcFigCIniReader = &m_CIniReader;
	mDlgPlanFileConfig.m_pPlan = &m_CPlan;
	mDlgPlanFileConfig.DoModal();
}


void CMainFrame::OnDataBackup()
{
	// TODO: Add your command handler code here
	DlgPlanFileConfig mDlgPlanFileConfig;
	mDlgPlanFileConfig.m_pcFigCIniReader = &m_CIniReader;
	mDlgPlanFileConfig.m_pPlan = &m_CPlan;
	mDlgPlanFileConfig.DoModal();
}


void CMainFrame::OnDataTest()
{
	// TODO: Add your command handler code here
	//pszINIFilePath, _T("\\") + strINIFile
	//ShellExecute(0, "open", strAppPath, strFilePath, NULL, SW_MAXIMIZE);
	//ShellExecute(NULL, _T("open"), _T("D:\\GIT\\MFCTest.GPIO.ADDA.Model\\x64\\Release\\MFCTest.GPIO.ADDA.Model.exe"), _T("MFCTest.GPIO.ADDA.Model.exe"), NULL, 3);
	ShellExecute(NULL, _T("open"), _T("D:\\BenchPro\\MFCTest.GPIO.ADDA.Model.exe"), _T("MFCTest.GPIO.ADDA.Model.exe"), NULL, 3);
}


void CMainFrame::OnPowersettingPowerssetting()
{
	// TODO: Add your command handler code here
	if (m_CPlan.OrderRun < 0) {
		MessageBox(bmess, tmess);
		return;
	}

	DlgPowerSetting mDlgPowerSetting;
	mDlgPowerSetting.m_pcFigCIniReader = &m_CIniReader;
	mDlgPowerSetting.m_pPlan = &m_CPlan;
	mDlgPowerSetting.DoModal();
	
}


void CMainFrame::OnPowersettingPowerssafe()
{
	// TODO: Add your command handler code here
	if (m_CPlan.OrderRun < 0) {
		MessageBox(bmess, tmess);
		return;
	}
	DlgPowerSettingThreshold mDlgPowerSettingThreshold;
	mDlgPowerSettingThreshold.m_pcFigCIniReader = &m_CIniReader;
	mDlgPowerSettingThreshold.m_pPlan = &m_CPlan;
	mDlgPowerSettingThreshold.DoModal();
}


void CMainFrame::OnPowersettingSignparam()
{
	// TODO: Add your command handler code here
	if (m_CPlan.OrderRun < 0) {
		MessageBox(bmess, tmess);
		return;
	}
	DlgPowerSettingParam mDlgPowerSettingParam;
	mDlgPowerSettingParam.m_pIniReader = &m_CIniReader;
	mDlgPowerSettingParam.m_pPlan = &m_CPlan;
	mDlgPowerSettingParam.DoModal();
}


void CMainFrame::OnToolsLoadTestcase()
{
	// TODO: Add your command handler code here
	
	DlgCreateCase mDlgCreateCase;
	mDlgCreateCase.m_pPlan = &m_CPlan;
	mDlgCreateCase.m_pCIniReader = &m_CIniReader;

	mDlgCreateCase.DoModal();
}


void CMainFrame::OnTestconnectsystem()
{
	// TODO: Add your command handler code here
	// //---------------------------

	DlgConnectToDevide mDlgConnectToDevide;
	mDlgConnectToDevide.m_pCIniReader = &m_CIniReader;

	/* CString strIp;
	 int portDev,portLocal;
	 GetIPConfig(strIp, portDev, portLocal);*/
	mDlgConnectToDevide.DoModal();
}


void CMainFrame::OnTestOnboard()
{
	// TODO: Add your command handler code here
	DlgTestOnBoard mDlgTestOnBoard;
	mDlgTestOnBoard.m_pCPlan = &m_CPlan;
	mDlgTestOnBoard.m_pCIniReader = &m_CIniReader;
	mDlgTestOnBoard.SocketTh = SocketTh;
	mDlgTestOnBoard.DoModal();

}


void CMainFrame::OnAppExit()
{
	// TODO: Add your command handler code here
	//SocketPh->TCP_shutdown();
	//SocketTh->TCP_shutdown();
	
}
