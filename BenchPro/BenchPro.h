
// BenchPro.h : main header file for the BenchPro application
//
#pragma once
#include "INI.h"
#include "Plan.h"

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#define WEIT_PH				0
#define RECONET_PH			1
#define RUN_AS_ADMIN_PH		2
#define RUN_AS_USER_PH		3
#define REQUETNAME_PH		4
#define QUITPRO_PH			5

#define WEIT_TH				0
#define RUN_AS_ADMIN_TH		2
#define RUN_AS_USER_TH		3
#define REQUETNAME_TH		4
#define QUITPRO_TH			5

#define DEBUGADMIN			1
#define NORMAL				2
#define ORIGINAL			3
#define DEBUGUSER			4
#define DEBUGNORMAL			5
#define GETDATABASE			0   //0 -> normal; 1- colect data

#define OK	1
#define ERR	0

#define ADMIN				1
#define USER				2

#include "resource.h"       // main symbols

//-----------------------
//for tcp connection 
#include <thread>
#include"MSG_Qeueu.h"
#include"TcpSocket.h"


// CBenchProApp:
// See BenchPro.cpp for the implementation of this class
//


class CBenchProApp : public CWinAppEx
{
public:
	CBenchProApp() noexcept;

protected:
// Overrides
public:
	//----------------------------
	int MODE = NORMAL;
	//int MODE = DEBUGNORMAL; 
	//int MODE = DEBUGADMIN;
	//int MODE = DEBUGUSER;
	//----------------------------

	virtual BOOL InitInstance();
	virtual BOOL InitInstance1();
	virtual int ExitInstance();

	SocketTCP* SocketTh;
	SocketTCP* SocketPh;

	CFont* m_ssfont;
	CFont* m_sfont;
	CFont* m_bfont;
	CFont* m_tfont;
	CFont* m_nfont;
	CIniReader		  m_CIniReader;
	CIniReader		  m_CIniReaderINI;
	CPlan			  m_CPlan;

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	afx_msg void RunAsUser(int);
	afx_msg void RunAsAdmin();
	BOOL RunNormal();
	afx_msg void WaitPh();


};

extern CBenchProApp theApp;
