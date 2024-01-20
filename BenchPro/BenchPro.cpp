
// BenchPro.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "BenchPro.h"
#include "MainFrm.h"

#include "DlgTestOnBoard.h"
#include "MainDlg.h"

#include "BenchProDoc.h"
#include "BenchProView.h"
#include "mta_io_client.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CString PubstrAdrressConn;
//-----------------------
int mFlagConnected = ERR;
int mFlagPhConnected = ERR;
int mFlagThConnected = ERR;

int mFlagPhRun = WEIT_PH;
int mFlagThRun = WEIT_TH;

//int mkillThread = 0;

//SocketTCP* SocketTh;
//SocketTCP* SocketPh;

//===============================================
MSG_Queue* rec_mqTh = new MSG_Queue();
MSG_Queue* send_mqTh = new MSG_Queue();
UINT __cdecl threadProcPrintTh(LPVOID input);
UINT __cdecl threadProcTh(LPVOID socket);
//--------------------------------------------------
char* str_receiTh;

//--------------------------------------------------
void GUI_InterfaceTh(MSG_Queue* rec_mq, MSG_Queue* send_mq)
{
	//cout << "reading msgqeueu" << endl;
	while (1) {
		Sleep(1000);
		//cout << "here" << endl;
		if (!rec_mq->isEmty()) {
			mFlagThConnected = 1;
			//cout << "your message begin" << endl;
			//AfxMessageBox(_T("this is the socketsssssss"));
			str_receiTh = rec_mq->readMsg();
			string str(str_receiTh);
			//CString Cstr1,  Cstr(str_recei);
			//fxMessageBox(str);
			if (str.find("Thanh") != -1) {
				send_mq->addMsg("aDuc");
			}
			if (str.find("guilai") != -1) {
				//AfxMessageBox(_T("Thanh XONG"));
				mFlagThRun = 2;
			}
			if (str.find("nhanxong") != -1) {
				//AfxMessageBox(_T("Thanh XONG"));
				mFlagThRun = 3;
			}
			if (str.find("chayxong") != -1) {
				//AfxMessageBox(_T("Thanh XONG"));
				mFlagThRun = 0;
			}
			//cout << "your message end" << endl;
		}

		////Send
		//cout << "please input a message" << endl;
		//char* s = new char[20];
		//fgets(s, 20, stdin);
		//send_mq->addMsg(s);
		////Do Program
	}
	//cout << "reading msgqeueu end" << endl;
}
UINT __cdecl threadProcPrintTh(LPVOID input)
{
	// convert it to the correct data type. It's common to pass entire structures this way.

	// TODO: Add your worker code...
	//MessageBox(0, _T("Inside thread Th!"), 0, 0);
	GUI_InterfaceTh(rec_mqTh, send_mqTh);
	return 0;
}

UINT __cdecl threadProcTh(LPVOID socket)
{
	// convert it to the correct data type. It's common to pass entire structures this way.

	// TODO: Add your worker code...
	//MessageBox(0, "Inside thread!", 0, 0);
	SocketTCP* mySocket = (SocketTCP*)socket;
	mySocket->TCP_send_receive();

	mySocket->closeConnection();

	// avoid memory leak.
	delete mySocket;
	return 0;
}

//========================================
MSG_Queue* rec_mqPh = new MSG_Queue();
MSG_Queue* send_mqPh = new MSG_Queue();
UINT __cdecl threadProcPrintPh(LPVOID input);
UINT __cdecl threadProcPh(LPVOID socket);
//------------------------------------------

char* str_receiPh;

//----------
void GUI_InterfacePh(MSG_Queue* rec_mq, MSG_Queue* send_mq)
{
	//AfxMessageBox(_T("GUI_InterfacePh"));
	while (1) {
		//if (mkillThread == 1) return;
		//AfxMessageBox(_T("Loop GUI_InterfacePh"));
		//----------------------------------------------
		//------- Kiểm tra kết nối -----------------------
		CString str1 = PubstrAdrressConn;
		CT2A ascii(str1, CP_UTF8);
		int nRet = set_baseUrl(ascii.m_psz, 2000);
		CString strPort;

		if (nRet == 0)  strPort = _T("Kết nối thành công!!!");
		else strPort = _T("LỖI: Lỗi kết nối");

		if (nRet == 0) mFlagConnected = OK;
		else  mFlagConnected = ERR;
		//----------------------------------------------
		Sleep(1000);
		if (!rec_mq->isEmty()) {

			str_receiPh = rec_mq->readMsg();
			string str(str_receiPh);
			//--------------------------------------------------
			//Phi say:hello-> DUC say:aDuc; 
			//Phi say:status->status 0/1; 
			//Phi say:run admin 123456 -> Duc chay xong -> DUC say:run admin done;
			//Phi say:run user; -> phi tao file duong dan co dinh -> Duc chay xong -> DUC say:run user done; 
			//--------------------------------------------------

			if (str.find("hello") != -1) {
				//AfxMessageBox(_T("Phi say Hello"));
				mFlagPhRun = REQUETNAME_PH;
			}
			if (str.find("status") != -1) {
				//AfxMessageBox(_T("Phi say reconnet"));
				mFlagPhRun = RECONET_PH;
			}

			if (str.find("run admin") != -1) {
				//AfxMessageBox(_T("Phi say admin"));
				mFlagPhRun = RUN_AS_ADMIN_PH;
			}
			if (str.find("run user") != -1) {
				//AfxMessageBox(_T("Phi say user"));
				mFlagPhRun = RUN_AS_USER_PH;
			}
			if (str.find("quit aDuc") != -1) {
				//AfxMessageBox(_T("Phi say user"));
				mFlagPhRun = QUITPRO_PH;
				return;
			}
		}
	}
}
UINT __cdecl threadProcPrintPh(LPVOID input)
{
	// convert it to the correct data type. It's common to pass entire structures this way.

	// TODO: Add your worker code...
	//MessageBox(0, _T("threadProcPrintPh"), 0, 0);

	GUI_InterfacePh(rec_mqPh, send_mqPh);
	//MessageBox(0, _T("End threadProcPrintPh"), 0, 0);
	return 0;
}

UINT __cdecl threadProcPh(LPVOID socket)
{
	// convert it to the correct data type. It's common to pass entire structures this way.

	// TODO: Add your worker code...
	//MessageBox(0, "Inside thread!", 0, 0);
	//AfxMessageBox(_T("threadProcPh"));
	SocketTCP* mySocket = (SocketTCP*)socket;
	//mySocket->pkillThread = &mkillThread;
	mySocket->TCP_send_receive();

	//AfxMessageBox(_T("End threadProcPh"));

	mySocket->closeConnection();

	// avoid memory leak.
	delete mySocket;
	return 0;
}

//------------------------------
// CBenchProApp
//================================================

BEGIN_MESSAGE_MAP(CBenchProApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CBenchProApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CBenchProApp construction

CBenchProApp::CBenchProApp() noexcept
{
	m_bHiColorIcons = TRUE;
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("BenchPro.AppID.NoVersion"));
	m_ssfont = new CFont;
	m_ssfont->CreateFont(
		16,                       // nHeight
		0,                        // nWidth
		0,                        // nEscapement
		0,                        // nOrientation
		5,						  // nWeight  FW_BOLD,
		FALSE,                    // bItalic
		FALSE,                    // bUnderline
		0,                        // cStrikeOut
		ANSI_CHARSET,             // nCharSet
		OUT_DEFAULT_PRECIS,       // nOutPrecision
		CLIP_DEFAULT_PRECIS,      // nClipPrecision
		DEFAULT_QUALITY,          // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		_T("Arial"));            // lpszFacename
	m_sfont = new CFont;
	m_sfont->CreateFont(
		20,                       // nHeight
		0,                        // nWidth
		0,                        // nEscapement
		0,                        // nOrientation
		0,                  // nWeight  FW_BOLD,
		FALSE,                    // bItalic
		FALSE,                    // bUnderline
		0,                        // cStrikeOut
		ANSI_CHARSET,             // nCharSet
		OUT_DEFAULT_PRECIS,       // nOutPrecision
		CLIP_DEFAULT_PRECIS,      // nClipPrecision
		DEFAULT_QUALITY,          // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		_T("Arial"));            // lpszFacename
	m_bfont = new CFont;
	m_bfont->CreateFont(
		32,                       // nHeight
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
	m_tfont = new CFont;
	m_tfont->CreateFont(
		32,                       // nHeight
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
	m_nfont = new CFont;
	m_nfont->CreateFont(
		26,                       // nHeight
		0,                        // nWidth
		0,                        // nEscapement
		0,                        // nOrientation
		0,                  // nWeight  FW_BOLD,
		FALSE,                    // bItalic
		FALSE,                    // bUnderline
		0,                        // cStrikeOut
		ANSI_CHARSET,             // nCharSet
		OUT_DEFAULT_PRECIS,       // nOutPrecision
		CLIP_DEFAULT_PRECIS,      // nClipPrecision
		DEFAULT_QUALITY,          // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		_T("Arial"));            // lpszFacename
	// TODO: add construction code here,
	 //Place all significant initialization in InitInstance

	if (MODE == NORMAL || MODE == DEBUGNORMAL)
	{
		SocketPh = new SocketTCP(rec_mqPh, send_mqPh);
		SocketPh->pFlagPhConnected = &mFlagPhConnected;
		SocketPh->TCP_initPhi();
		SocketPh->TCP_connect();
		AfxBeginThread(threadProcPh, SocketPh);
		AfxBeginThread(threadProcPrintPh, SocketPh);
		//----------------------------------------
		SocketTh = new SocketTCP(rec_mqTh, send_mqTh);
		SocketTh->pflagThConnected = &mFlagThConnected;
		SocketTh->TCP_init();
		SocketTh->TCP_connect();
		AfxBeginThread(threadProcTh, SocketTh);
		AfxBeginThread(threadProcPrintTh, SocketTh);
		//-------------------------------
	}
}

// The one and only CBenchProApp object

CBenchProApp theApp;


// CBenchProApp initialization

BOOL CBenchProApp::InitInstance()
{
	m_CIniReaderINI.setINIFileName(_T(""));
	CString strSection;
	CString strValue, strKey;
	
	strSection = _T("FILEPATH");
	strKey = _T("datarootpath");
	strValue = m_CIniReaderINI.getKeyValue(strKey, strSection);
	int mlength = strValue.GetLength();
	if (mlength > 0) m_CPlan.mTestCase.mPathInfo.DatabasePath = strValue;

	strKey = _T("addressconn");
	strValue = m_CIniReaderINI.getKeyValue(strKey, strSection);
	mlength = strValue.GetLength();
	m_CPlan.strAdrressConn = _T("http://192.168.1.125:10001");
	if (mlength > 0) m_CPlan.strAdrressConn.Format(_T("http://%s:10001"), strValue);
	PubstrAdrressConn = m_CPlan.strAdrressConn;

	float mValue;
	strKey = _T("cPowerSafeVerifyThreshol");
	strValue = m_CIniReaderINI.getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(mValue));
	if (mValue < 0 || mValue >= 1) mValue = 0.15;
	m_CPlan.mTestCase.mSupply_Set.PowerSafeVerifyThreshol = mValue;
	strKey = _T("cPowerVerifyThreshol");
	strValue = m_CIniReaderINI.getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(mValue));
	if (mValue < 0 || mValue >= 1) mValue = 0.15;
	m_CPlan.mTestCase.mPowers.PowerVerifyThreshol = mValue;
	
	switch (MODE) {
		case NORMAL: 
			WaitPh(); 
			break;
		case DEBUGNORMAL:
			WaitPh();
			break;
		case ORIGINAL: 
			RunNormal(); 
			break;
		case DEBUGADMIN: 
			RunAsAdmin();
			break;
		case DEBUGUSER:
			RunAsUser(1);
			break;
	}
	return TRUE;
}
BOOL CBenchProApp::RunNormal() {
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBenchProDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CBenchProView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	return TRUE;
}

// Dialog Data

void CBenchProApp::RunAsUser(int mode) {

	DlgTestOnBoard mDlgTestOnBoard;
	mDlgTestOnBoard.SocketTh = SocketTh;
	mDlgTestOnBoard.pFlagThRun = &mFlagThRun;
	mDlgTestOnBoard.m_pCIniReader = &m_CIniReader;
	mDlgTestOnBoard.m_pCPlan = &m_CPlan;
	mDlgTestOnBoard.pFlagThConnected = &mFlagThConnected;
	mDlgTestOnBoard.pFlagConnected = &mFlagConnected;
	mDlgTestOnBoard.m_User = mode;
	mDlgTestOnBoard.p_mode = &MODE;
	mDlgTestOnBoard.m_sfont = this->m_sfont;
	mDlgTestOnBoard.m_bfont = this->m_bfont;
	mDlgTestOnBoard.m_tfont = this->m_tfont;
	mDlgTestOnBoard.pPubstrAdrressConn = &PubstrAdrressConn;
	mDlgTestOnBoard.DoModal();

}
void CBenchProApp::RunAsAdmin() {
	MainDlg mMainDlg;
	mMainDlg.SocketTh = SocketTh;
	mMainDlg.m_pFlagThRun = &mFlagThRun;
	mMainDlg.m_pCIniReader = &m_CIniReader;
	mMainDlg.pFlagThConnected = &mFlagThConnected;
	mMainDlg.pFlagConnected = &mFlagConnected;
	mMainDlg.m_pCPlan = &m_CPlan;
	mMainDlg.p_mode = &MODE;
	mMainDlg.m_ssfont = this->m_ssfont;
	mMainDlg.m_sfont = this->m_sfont;
	mMainDlg.m_bfont = this->m_bfont;
	mMainDlg.m_tfont = this->m_tfont;
	mMainDlg.pPubstrAdrressConn = &PubstrAdrressConn;
	mMainDlg.DoModal();
}
void CBenchProApp::WaitPh() {

	int flagDontSend = 0;
	int mCount = 0;
	while (1) {
		//AfxMessageBox(_T("Loop WaitPh"));
		//if (!mFlagPhConnected) {
		//	mCount++;
		//	if (mCount > 5) {
		//		//mCount = 0;
		//		//Sleep(1000);
		//		//AfxMessageBox(_T("re Connect"));
		//		//mkillThread = 1;
		//		//SocketPh->TCP_shutdown();
		//	//	SocketPh->TCP_initPhi();
		//	//	SocketPh->TCP_connect();
		//	//	AfxBeginThread(threadProcPh, SocketPh);
		//	}
		//}
		Sleep(1000);

		switch (mFlagPhRun) {
		case WEIT_PH:
			break;
		case RUN_AS_ADMIN_PH:
			mFlagPhRun = WEIT_PH;
			RunAsAdmin();
			if (mFlagPhConnected) {
				SocketPh->TCP_send("run admin done\n");
			}
			else {
				flagDontSend = RUN_AS_ADMIN_PH;
			}
			break;
		case RUN_AS_USER_PH:
			mFlagPhRun = WEIT_PH;
			RunAsUser(1);
			if (mFlagPhConnected) {
				SocketPh->TCP_send("run user done\n");
			}
			else {
				flagDontSend = RUN_AS_USER_PH;
			}
			
			break;
		case REQUETNAME_PH:
			mFlagPhRun = WEIT_PH;
			break;
			if (mFlagPhConnected) {
				SocketPh->TCP_send("aDuc\n");
			}
			else {
				flagDontSend = REQUETNAME_PH;
			}
			
			break;
		case RECONET_PH:
			mFlagPhRun = WEIT_PH;
			if (mFlagPhConnected) {
				if(mFlagConnected) 	SocketPh->TCP_send("status 1\n");
				else SocketPh->TCP_send("status 0\n");
			}
			break;
		case QUITPRO_PH:
			mFlagPhRun = WEIT_PH;

			if (mFlagThConnected) {
				SocketTh->TCP_send("quit\n");
				SocketTh->TCP_shutdown();
			}
			if (mFlagPhConnected) {
				SocketPh->TCP_shutdown();
			}
			
			return;
			break;
		}
		//---------------------------
		// --- xu ly mat ket noi Phi, ct tự thoat
		if (!mFlagPhConnected) {
			if (mFlagThConnected) {
					SocketTh->TCP_send("quit\n");
					SocketTh->TCP_shutdown();
			}
			SocketPh->TCP_shutdown();
			return;
		}
		//---------------------------------------
	}
}
BOOL CBenchProApp::InitInstance1()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	//CWinAppEx::InitInstance();

 	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	 //AfxInitRichEdit2() is required to use RichEdit control
	 AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBenchProDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CBenchProView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

int CBenchProApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CBenchProApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnConnecttodevide();
	afx_msg void OnDevidesetting();
	afx_msg void OnFileSaveExit();
	afx_msg void OnPowersettingSignparam();
	afx_msg void OnPinSettingEditFileNew();
	afx_msg void OnTestOnboard();
	afx_msg void OnAppExit();
	afx_msg void OnPinSettingEditFileSave();
	afx_msg void OnCbnSelchangeCmbIdJack();
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_CONNECTTODEVIDE, &CAboutDlg::OnConnecttodevide)
	ON_COMMAND(ID_DEVIDESETTING, &CAboutDlg::OnDevidesetting)
	ON_COMMAND(ID_POWERSETTING_SIGNPARAM, &CAboutDlg::OnPowersettingSignparam)
	ON_COMMAND(ID_PIN_SETTING_EDIT_FILE_NEW, &CAboutDlg::OnPinSettingEditFileNew)
	ON_COMMAND(ID_TEST_ONBOARD, &CAboutDlg::OnTestOnboard)
	ON_COMMAND(ID_APP_EXIT, &CAboutDlg::OnAppExit)
	ON_COMMAND(ID_PIN_SETTING_EDIT_FILE_SAVE, &CAboutDlg::OnPinSettingEditFileSave)
	ON_CBN_SELCHANGE(IDC_CMB_ID_JACK, &CAboutDlg::OnCbnSelchangeCmbIdJack)
END_MESSAGE_MAP()

// App command to run the dialog
void CBenchProApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CBenchProApp customization load/save methods

void CBenchProApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	//GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CBenchProApp::LoadCustomState()
{
}

void CBenchProApp::SaveCustomState()
{
}

// CBenchProApp message handlers


void CAboutDlg::OnConnecttodevide()
{
	// TODO: Add your command handler code here
	
}


void CAboutDlg::OnDevidesetting()
{
	// TODO: Add your command handler code here
}


void CAboutDlg::OnPowersettingSignparam()
{
	// TODO: Add your command handler code here
}


void CAboutDlg::OnPinSettingEditFileNew()
{
	// TODO: Add your command handler code here
}


void CAboutDlg::OnTestOnboard()
{
	// TODO: Add your command handler code here
}


void CAboutDlg::OnAppExit()
{
	// TODO: Add your command handler code here
}


void CAboutDlg::OnPinSettingEditFileSave()
{
	// TODO: Add your command handler code here
}


void CAboutDlg::OnCbnSelchangeCmbIdJack()
{
	// TODO: Add your control notification handler code here
}
