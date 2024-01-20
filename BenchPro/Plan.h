#include "INI.h"
#include "vector"
#include "afxdialogex.h"

#pragma once

//CString VerSW = _T("Ver: 1.0.1");

#define  ADDR_PC   		0x00
#define  ADDR_M1_0   	0x10
#define  ADDR_M1_1   	0x11
#define  ADDR_M2PS_0   	0x20
#define  ADDR_M2PS_3   	0x23
#define  ADDR_M3_0   	0x30
#define  ADDR_M3_1   	0x31
#define  ADDR_M4_0   	0x40
#define  ADDR_M2SIG_0   0x4A
#define  ADDR_M2SIG_1   0x4B
#define  ADDR_M5_0   0x50
#define  ADDR_M5_1   0x51
#define  ADDR_M5_2   0x52
#define  ADDR_M5_3   0x53
#define  ADDR_M6_0   0x60
#define  ADDR_M7_A   0x7A
#define  ADDR_M7_B   0x7B
#define  ADDR_M9	 0x90
#define  ADDR_M10	 0xA0

//cac ma lenh : Sub_I_1      Byte[2]
#define  CMD_PING			0x01
#define  CMD_ACK			0x02
#define  CMD_READ_STT		0x03
#define  CMD_READ_PWR_INF   0x04
#define  CMD_WRITE_THRES_I  0x05
#define  CMD_READ_THRES_I   0x06
#define  CMD_WRITE_THRES_UHV	0x07
#define  CMD_READ_THRES_UHV		0x08
#define  CMD_WRITE_PARAM	0x09
#define  CMD_READ_PARAM		0x0A
#define  CMD_WRITE_RUN_CMD  0x0B


// cac sub lenh: byte [3]
#define  SUB_CMD_IMAX_3V3_1			0x0100
#define  SUB_CMD_IMAX_5V			0x0200
#define  SUB_CMD_IMAX_12V			0x0300
#define  SUB_CMD_IMAX_12V_N			0x0400
#define  SUB_CMD_IMAX_3V3_2			0x0500
#define  SUB_CMD_IMAX_12V_CPU		0x0600
#define  SUB_CMD_IMAX_12V_RELAY_1   0x0700
#define  SUB_CMD_IMAX_12V_RELAY_2   0x0800
#define  SUB_CMD_IMAX_30V			0x0900


#define  SUB_CMD_U12V_HV_UP_DOWN	0x0100
#define  SUB_CMD_U30V_HV_UP_DOWN	0x0200

#define  SUB_CMD_PARAM_DATA_RELAYS		0x0100
#define  SUB_CMD_PARAM_DATA_8POWERS		0x0200
#define  SUB_CMD_PARAM_DATA_HV_OUT		0x0300
#define  SUB_CMD_PARAM_SCALER_HV_IN		0x0400
#define  SUB_CMD_PARAM_SCALER_ADC		0x0500
#define  SUB_CMD_PARAM_VOFFSET_DAC		0x0600
#define  SUB_CMD_PARAM_FSAMPLE_VHI_LOGIC_OUT	0x0700
#define  SUB_CMD_PARAM_U_COMPARE_LOGIC_IN		0x0900
#define  SUB_CMD_PARAM_SYNC_MODE				0x0B00
#define  SUB_CMD_PARAM_CTRL_MODE_PIN			0x0C00
#define  SUB_CMD_PARAM_CONFIRM_CORRECT_BOARD	0x0D00
#define  SUB_CMD_PARAM_CTRL_PWR_ON_BOARD		0x0E00
#define  SUB_CMD_PARAM_ON_OFF_HV_SUPPLY			0x0F00
#define  SUB_CMD_PARAM_ON_OFF_30V_M9			0x1000
#define  SUB_CMD_PARAM_ITHRESH_GEN_PWR			0x1100

#define  SUB_CMD_RUN_RESET_BOARD				0x0100
#define  SUB_CMD_PARAM_RUN_APPLY_RELAY			0x0200



#define  BUS_PROPERTY_POWER1	   	1
#define  BUS_PROPERTY_POWER2	   	2
#define  BUS_PROPERTY_POWER3	   	3
#define  BUS_PROPERTY_POWER4	   	4
#define  BUS_PROPERTY_POWER5	   	5
#define  BUS_PROPERTY_POWER6	   	6
#define  BUS_PROPERTY_POWER7	   	7
#define  BUS_PROPERTY_POWER8	   	8

#define  BUS_PROPERTY_GND	    	9
#define  BUS_PROPERTY_LOGIC_IN	    10
#define  BUS_PROPERTY_LOGIC_OUT	    11

#define BUS_PROPERTY_CLOCK_OUT		12  //26

#define  BUS_PROPERTY_ADC1	   	13		//12
#define  BUS_PROPERTY_ADC2	   	14		//13
#define  BUS_PROPERTY_DAC1	   	15		//14
#define  BUS_PROPERTY_DAC2	   	16		//15



#define  BUS_PROPERTY_HIVOLTAGE_IN1	   	17	//18
#define  BUS_PROPERTY_HIVOLTAGE_IN2	   	18	//19

#define  BUS_PROPERTY_HIVOLTAGE_OUT1	19	//	   	16	
#define  BUS_PROPERTY_HIVOLTAGE_OUT2	20	//   	17

#define  BUS_PROPERTY_EX_IN1		   	21	//22
#define  BUS_PROPERTY_EX_OUT1		   	22	//20

#define  BUS_PROPERTY_EX_IN2		   	23	//23
#define  BUS_PROPERTY_EX_OUT2		   	24	//21

//----------------------------------------
#define  BUS_PROPERTY_SYS_1		   		26	//24
#define  BUS_PROPERTY_SYS_2		   		27	//25

#define  BUS_PROPERTY_LOGIC_IN_PUP		28

//----------------------------------

#define P_ON				1
#define P_OFF				0

//----------------------------------

#define VERSION_FW				0x0100   // Version FW 1.0

#define FACTOR_SCALER_0P001		0.001
#define FACTOR_SCALER_0P01		0.01
#define FACTOR_SCALER_0P1		0.1

#define LENGTH_HEADER			8
#define SIZE_MAX_BUFF_RX_SERIAL	1024

//--------------------------------------------
#define VERSION_SW				0x0100   // Version SW 1.0

//-------------------------
#define MAX_PINS	255		//max 250
#define MAX_CHANELS 84



// ddefine ID cac jack cua M9, dung cho set up M9: truyen ID jack ma DUT cam vao
// TUAN moi them 28/9/2023

#define M9_dont_used			0
#define NumPins_M9_J6_Jack_1	0
 
#define M9_J6_Jack_1			1
#define NumPins_M9_J6_Jack_1	62

#define M9_J5_Jack_2			2
#define NumPins_M9_J5_Jack_2	61

#define M9_J4_Jack_3			3
#define NumPins_M9_J4_Jack_3	31

#define M9_J1_Jack_4			4
#define NumPins_M9_J1_Jack_4	64

#define M9_JA3_Jack_5			5
#define NumPins_M9_JA3_Jack_5	45

#define M9_JA5_Jack_6			6
#define NumPins_M9_JA5_Jack_6	80

#define M9_JA2_Jack_7			7
#define NumPins_M9_JA2_Jack_7	135

#define M9_JA4JA1_Jack_8		8
#define NumPins_M9_JA1JA1_Jack_8	 225         // them 45 data cho JA4: (hang giua:  pin 45 ... 90) = 0x00, khi dong goi gui cho M9 dia chi ID = 8,


// define cac id cua nguong he thong, dungcho thiet lap nguong dong bao ve
#define ID_I_Thres_PwrSys_3V3_1		1          // dong = 1/2 gia tri cua co so du lieu tren giao dien
#define ID_I_Thres_PwrSys_5V		2
#define ID_I_Thres_PwrSys_12V		3
#define ID_I_Thres_PwrSys_12V_N		4
#define ID_I_Thres_PwrSys_3V3_2		5			// dong = 1/2 gia tri cua co so du lieu tren giao dien
#define ID_I_Thres_PwrSys_12V_CPU	6
#define ID_I_Thres_PwrSys_12V_RL_1	7			// dong = 1/2 gia tri cua co so du lieu tren giao dien 12V_RL
#define ID_I_Thres_PwrSys_12V_RL_2	8			// dong = 1/2 gia tri cua co so du lieu tren giao dien 12V_RL
#define ID_I_Thres_PwrSys_30V		9

// ID nguong dien ap bao ve cho nguon cao ap: khi dien ap cao ap nho hon, hoac cao hon dien ap nay he thong de ngay va khong cho hoat dong
#define ID_UThres_HV_Pwr_Sys_30V		1
#define ID_UThres_HV_Pwr_Sys_12V_Relay	2


#define MAX_PINS_ON_JACK 270    // so chan lon nhat tren 1 jack cua M9: 135 x 2


struct PACKAGE_SERIAL {
	// header
	byte srcAddr;
	byte desAddr;
	byte Cmd;
	int subCmd;
	int versionFw;
	byte lenData;

	// payload
	char* pData;
};
//----------------------------------
struct JACK_ROW_DEF {
	CString JackRowSign = _T("J1");
	int Pins = 20;                  //update when edit
};
struct JACK_DEF {
	CString JackSign;
	CString JackName;
	int nJackRows = 2;              //update when edit
	std::vector<JACK_ROW_DEF> mJACK_ROW;
};
struct JACK_INFO {
	int nJacks = 2;                  //update when edit
	std::vector<JACK_DEF> mJACKS;
};
// struct Board
struct PATHINFO_DEF {
	int mloadInfor = 0;
	CString Usermane = _T("");
	CString admin = _T("");
	CString datanamefolder = _T("Cosodulieu");
	CString PhiFileConfigPath = _T("D:\\FilePath\\FilePath.txt");
	CString PhiPath = _T("D:\\CSDL_20230705\\Kacta-2E2\\B2AП78\\BaiKT_So1\\xyz.abc");
	CString FullPath = _T("D:\\CSDL_20230705\\Kacta-2E2\\B2AП78\\BaiKT_So1\\Cosodulieu\\Config.cfg");
	CString RootPath = _T("D:\\CSDL_20230705");
	CString DatabasePath = _T("D:\\CSDL_20230705");
	CString DeviceID = _T("Kacta-2E2");
	CString BoardID = _T("B2AП78");
	CString TestID = _T("BaiKT_So1");
	
	//--- fix  -------------
	CString DevicePicName = DeviceID +  _T(".jpg");   //"Kacta-2E2.jpg"
	CString BoardPicName = _T("Anhbomach.jpg");
	CString TestPicName = _T("Fig.jpg");

	// load tư excel -----------------
	CString DeviceName = _T("ĐÀI RA-ĐA KACTA-2E2");   // Dọc từ Excel
	CString BoardName = _T("Điều khiển B2AП78");		// Dọc từ Excel
	CString TestName = _T("Kiểm tra nguồn");
	//---- tự tính -----------------------------
	CString DevicePath = RootPath;
	CString DevicePicPath = DevicePath + _T("\\Radar_Fig");
		
	CString BoardPath = DevicePath + _T("\\") + DeviceID + _T("\\") + BoardID;
	CString TestPicPath = BoardPath + _T("\\") + TestID;
	CString TestPath = TestPicPath + _T("\\") + datanamefolder;  // Config.dat + data.dat	
	
};
//----------------------------------
struct CONFIG_DEFINE
{
	unsigned int POWER_P1 = BUS_PROPERTY_POWER1;
	unsigned int POWER_P2 = BUS_PROPERTY_POWER2;
	unsigned int POWER_P3 = BUS_PROPERTY_POWER3;
	unsigned int POWER_P4 = BUS_PROPERTY_POWER4;
	unsigned int POWER_P5 = BUS_PROPERTY_POWER5;
	unsigned int POWER_N6 = BUS_PROPERTY_POWER6;
	unsigned int POWER_N7 = BUS_PROPERTY_POWER7;
	unsigned int POWER_N8 = BUS_PROPERTY_POWER8;

	unsigned int GND = BUS_PROPERTY_GND;
	unsigned int LOGIC_IN =  BUS_PROPERTY_LOGIC_IN;
	unsigned int LOGIC_IN_PUP = BUS_PROPERTY_LOGIC_IN_PUP;
	unsigned int LOGIC_OUT = BUS_PROPERTY_LOGIC_OUT;

	unsigned int CLOCK_OUT = BUS_PROPERTY_CLOCK_OUT;
	//---------------------------
	unsigned int ADC1 = BUS_PROPERTY_ADC1;
	unsigned int ADC2 = BUS_PROPERTY_ADC2;
	unsigned int DAC1 = BUS_PROPERTY_DAC1;
	unsigned int DAC2 = BUS_PROPERTY_DAC2;

	unsigned int HIVOLTAGE_OUT1 = BUS_PROPERTY_HIVOLTAGE_OUT1;
	unsigned int HIVOLTAGE_OUT2 = BUS_PROPERTY_HIVOLTAGE_OUT2;

	unsigned int HIVOLTAGE_IN1 = BUS_PROPERTY_HIVOLTAGE_IN1;
	unsigned int HIVOLTAGE_IN2 = BUS_PROPERTY_HIVOLTAGE_IN2;

	unsigned int EX_OUT1 = BUS_PROPERTY_EX_OUT1;
	unsigned int EX_OUT2 = BUS_PROPERTY_EX_OUT2;
	unsigned int EX_IN1 = BUS_PROPERTY_EX_IN1;
	unsigned int EX_IN2 = BUS_PROPERTY_EX_IN2;

	unsigned int SYS_1 = BUS_PROPERTY_SYS_1;
	unsigned int SYS_2 = BUS_PROPERTY_SYS_2;
};

struct PIN_CONF {
	CString mPinSign;   // ky hieu
	CString mPinName;  // max 15 ky tự
	int iChanel;      // pin gan voi kenh ?: 0 ...84 + 100, 101,102,103
};

struct CHANEL_CONF {
	int iPin;
	int Attri;
};
struct CHANELDATA_CONF {
	CString iPinSign;
	CString iPinName;
	int Attri;
	float value;
};
struct TESTCASE_CONFIG
{
	byte nPins = 10;		//max 250 Update when edit
	byte nChanels = 84;	    // max 84
	//-----------------
	int ArrRows;
	int ArrCols;

	byte GridHeaderRowsArr[256];
	CString GUIGridArr[256][100];
	CString PinNameGridArr[256][100];
	int PinGridArr[256][100]; // -1: Ko dung; 0: No connect; 1..84 : chanel 
	int ChanelGridArr[256][100]; // 0: Ko dung; 1-23: atribute chanel
	int PreChanelGridArr[256][100]; // 0: Ko dung; 1-23: atribute chanel
	CHANEL_CONF		mChanelsConf[90];
	CHANELDATA_CONF mChanelsDataConf[90];
	byte ChanelGridConfigArr[85];	// max 84	: 1..84 : value 1-23 ++1
	//-----------------
	PIN_CONF mPinsConf[271];	// tuan thay doi tu 256  ==> 271; ..270 pin	
	byte ChanelSelectArr[85];	// max 84	: 1..84 : value 0,1
	
	byte ChanelConfigArr[85];	// max 84	: 1..84 : value 1-23
	byte ChanelPUPConfigArr[85];	// 0, 1
};
struct POWER_STRUCT
{
	byte ON_OFF;     // 0: OFF,   1: ON
	float USet;
	float ImaxSet = 2;
	float UGet;
	float IGet;
	byte Status = 1; //1->OK, khac -> err : nhan duoc tu trang thai tra ve tu Device
	byte StatusU = 1;
	byte StatusI = 1;
};
struct POWERS_STRUCT
{
	float   PowerVerifyThreshol = (float)0.1; //0.1
	POWER_STRUCT POWER[9];
};
//=====================================================
struct HIVOLTAGE_OUT {
	int used = 0;	// 0 -> Not use; 1 -> use
	float value;
	CString name;
};
struct HIVOLTAGE_IN {
	int used = 0;	// 0 -> Not use; 1 -> use
	float value;
	CString name;
	int nChanel;
};
struct EXT_IO{
	int used = 0;	// 0 -> Not use; 1 -> use
	CString name;
	CString text;
	int IN_OUT;		// IN->0, OUT-> 1  TUAN moi quy uoc lai
};

struct ADC_DAC_STRUCT {
	int used = 0;	// 0 -> Not use; 1 -> use
	CString name;
	float value;
	int nChanel;
};
struct LOGIC_IN_V_COMPARE {//Comment = V_Compare
	CString name;
	float	value = 0.5;
};
struct LOGIC_OUT_V_HI {//Comment = V_Hi_Logic Volt(Logic 1->Muc cao)
	CString name;
	float value = 5.0;		
};


//-----------------------------------------------------
struct EXTCHANELINFO_DEF
{
	float   SignParaVerifyThreshol = (float)0.05; // 0.05;
	byte SetMode = 1;								// mode che do tin hieu mo rong:   1: ADC DAC channels   2: HV channels, 
	LOGIC_IN_V_COMPARE LogicInComp;			//Comment = V_Compare
	LOGIC_OUT_V_HI LogicOutHi;		//Comment = V_Hi_Logic Volt(Logic 1->Muc cao)
	EXT_IO EXT_io1, EXT_io2;

	ADC_DAC_STRUCT ADC_in1, ADC_in2;
	ADC_DAC_STRUCT DAC_out1, DAC_out2;

	//Comment = Value[0.0, .., 80.0]
	HIVOLTAGE_OUT HV_out1, HV_out2;
	//Comment = U_scale: value-> 1, 10, 100, 1000 (1 trong 4 gt)
	HIVOLTAGE_IN HV_in1, HV_in2;


};
//------------------------------------------------------
struct MODE
{
	//Comment = value: 0->internal; 1->external
	float	SYNC_MODE = 0;

	//Comment = value: 0..30 x 10 ^ 6 (Tan so mau : Hz)
	float	F_SAMPLE = 1000;
};
struct SUPPLY
{
	//Comment = Nguon cap khong dam bao / khi hoat dong nguon chap/chay, tang do ngot
	//Comment = Han che nguoi dung thiet lap, phai co tinh nang cho admin
	//Comment = nguong max  // Imax_12v_N (Negative) -> Dong cho nguon am
	//Comment = Dong cho nguon
	//Comment = Voltage
	float   PowerSafeVerifyThreshol = (float)0.05; // 0.05;

	float	Imax_3v3 = 3.0;
	float	Imax_5v = 2.0;
	float	Imax_12v = 3.0;
	float	Imax_12v_N = 2.0;
	float	Imax_12v_CPU = 3.0;
	float	Imax_12v_ROLE = 8.0;
	float	Imax_30v = 8.0;

	//Comment = Nguong dien ap hoat dong xoay quanh 12v
	float	U12v_UP = 14;
	float	U12v_DOWN = 10;

	//Comment = Nguong dien ap hoat dong xoay quanh 30v
	float	U30v_UP = 34;
	float	U30v_DOWN = 28;
};
struct TESTCASE
{
	CONFIG_DEFINE	mConfigDef;
	PATHINFO_DEF	mPathInfo;
	JACK_INFO		mJackInfo;
	POWERS_STRUCT	mPowers;
	SUPPLY			mSupply_Set, mSupply_Get;
	
	TESTCASE_CONFIG	mTestCaseConfig;
	
	EXTCHANELINFO_DEF	ExtChanel_Set, ExtChanel_Get;

	MODE			mMode;				
	byte			mID_Jack = 0;
	int				mPins_Of_Board; // Tong so pin cua mot board
};
//------------------------------------
class CPlan
{
public:
	TESTCASE mTestCase;
	int OrderRun = -1;
	int CountRunAdmin = 1;
	CString strAdrressConn;
	//int mFlagThanhRUN = 1;

	int i_Progress = 0;
	int n_Progress = 14;

	CProgressCtrl * p_ProgressCtrl;

public:
	uint16_t convert_FloatTo16bit(float F_num, float factor_Num);
	void convert_16bitToFoat(uint16_t Data, float factor_Num, float sign_f, float* float_Num);

	void PackageSerial(byte srcAddr, byte desAddr, byte Cmd, int subCmd, int versionFw, byte lenData, char* pData, byte* PkgData);
	int SetUp8Power(POWERS_STRUCT m_8Power, char* pData_receiv, int* plenData_receiv); //Max lenData_receiv = 1024
	void ExtrackPackage_Get_8PWR_Info(BYTE ADDR_M3_x);

	

	//======================================
	int CheckEditInt(CString str, int min, int max);
	int Fix_nJack_nPin_nJacRow();
	//---------------------
	void Init_PinGrid_GridHeader_GUIGridArr();
	void Init_ChanelGridArr();
	//---------------------
	void New_PinGrid_GridHeader_GUIGridArr();
	void New_ChanelGridArr();
	//----------------------
	int Check_MapPinArr();
	int Check_ChanelSelectArr();
	int Check_ChanelConfigArr();
	//----------------------
	int CheckEditTestCaseChanged();
	//======================================
	void InitMFCPath();
	void InitJavaPath(CString);
	float getSupplyValue(int);
	int InitChanelDataConf();
	CString ChanelConfToString();
	int ChanelConfToFileConf(CIniReader* m_pIniReader);

	//----------------------
	int Load_PhiFileConfigPath(CIniReader* m_pCIniReader);
	int Load_UserName_UserPath(CIniReader* m_pIniReader);
	int Load_AdminName(CIniReader* m_pIniReader);

	int LoadTestCase(CIniReader* m_pIniReader);
	int SaveTestCase(CIniReader* m_pIniReader, int comment);

	int Save_Define_TestCase(CIniReader* m_pIniReader, int comment);
	int Save_PathInfo_TestCase(CIniReader* m_pIniReader, int comment);
	int Save_JackInfo_TestCase(CIniReader* m_pIniReader, int comment);
	int Save_TestCaseConfig(CIniReader* m_pIniReader, int comment);
	int Save_8PowerParam_TestCase(CIniReader* m_pIniReader, int comment);
	int Save_EXTChanel_TestCase(CIniReader* m_pIniReader, int comment);
	int Save_MODE_TestCase(CIniReader* m_pIniReader, int comment);
	int Save_SUPPLY_TestCase(CIniReader* m_pIniReader, int comment);
	
	int Load_Define_TestCase(CIniReader* m_pIniReader);
	int Load_PathInfo_TestCase(CIniReader* m_pIniReader);
	int Load_JackInfo_TestCase(CIniReader* m_pIniReader);
	int Load_TestCaseConfig(CIniReader* m_pIniReader);
	int Load_8PowerParam_TestCase(CIniReader* m_pIniReader);
	int Load_EXTChanel_TestCase(CIniReader* m_pIniReader);
	int Load_MODE_TestCase(CIniReader* m_pIniReader);
	int Load_SUPPLY_TestCase(CIniReader* m_pIniReader);

	int CheckStrToNum(CString s_Num, int ChkMaxMin, float max, float min, int ChkAmDuong, int sign);
	//--------------------------------------
	int ResetProgress();
	int SetFullProgress();
	int IncreateProgress(int value);
	int IncreateProgressInMinMax(int value, int PhanTramMin, int PhanTramMax);
	int SetPhanTramProgress(int PhanTramValue);

	//------------------- Tuan viet ----------------------
	int ping_network_to_1_board(byte addr_board);
	int send_active_1_board(byte addr_board);
	int send_active_All_board();  // khac 0 co  error, 0-> ok

	// thiet lap cac gia tri bao ve he thong: I nguong, U nguong
	// I nguong
	int Set_Thres_I(byte ID_Nguon, float giatri_Inguong);
	int Get_Thres_I(byte ID_Nguon, float* returned_Inguong);
	// U nguong
	int Set_Thres_U(byte ID_Nguon, float giatri_Unguong);
	int Get_Thres_U(byte ID_Nguon, float* returned_Unguong);

	// dinh tuyen
	int Reset_1_paths(byte ADDR_Board);
	int Reset_All_paths(void);
	int Reset_IO_FPGA_Default(void);  // to all inputs
	int Set_Paths_M9(byte ID_jack);
	int Set_Paths_M1_i(byte ADDR_Board); // thiet lap board M1_0 /  M1_1
	int Set_Paths_M1(void);  // thiet lap ca 2 board M1_0 va M1_1

	int Set_Paths_M2_PS_i(byte ADDR_Board); // thiet lap  M2_0 /  M2_3
	int Set_Paths_M2_PS(void); // thiet lap ca 2 board o M2_0, M2_3

	int Set_Paths_M5_i(byte ADDR_Board);  // thiet lap cho 1 khoi M5
	int Set_Paths_M5(void); // thiet lap ca 2 board o M5_0,1,2,3


	int Start_Apply_Relay(byte ADDR_Board);  // bat dau cho phep thuc thi cau hinh relay
	int Set_Paths_M3(void);
	int Set_Paths_M3_i(byte ADDR_Board);

	int Set_ON_Off_30V_M9(byte ON_OFF);    // thiet lap ON_OFF nguon cho M9


	int Set_Freq_Vout_M5(byte ADDR_Board);
	int Set_Vnguong_In_M5(byte ADDR_Board);

	int Set_Dir_IO_M5_i(byte ADDR_Board);
	//int Set_Dir_IO_M5_0_20(void);
	//int Set_Dir_IO_M5_21_40(void);
	//int Set_Dir_IO_M5_41_60(void);
	//int Set_Dir_IO_M5_61_80(void);

	int Set_tham_so_Tin_hieu_M5(void);   // thiet lap tham so tin hieu cho M5

	int Process_Seting_PWR(void);
	//......................................................
	// bien toan cuc cua TUAN
	byte Data_Relay_M3_0[8];  // dung cau hinh chuyen mach relay cho M3_0
	byte Data_Relay_M3_1[8];  // dung cau hinh chuyen mach relay cho M3_1

	byte Data_relay_M2PS_0[41];  // dung tu 1...40
	byte Data_relay_M2PS_3[41];  // dung tu 1...40

	int Power_Ctrl_M1_For_DUT(UINT ON_OFF_Stt, byte ADDR_Board);    // dieu khien ON OFF nguon +30V qua DB50. Chu y: khi ON/OFF la ON oFF cho nguon M9, M10
	int SetUp_RPullUp_M10(void);
	//int Xuly_Maloi_ACK(UINT Length_data, byte* Data_Rx_Buff);
	//......................................................

	int Flag_Used_M9 = 1;   // mac dinh la co su dung khoi M9. Khi active board phat hine khong co  M9.10 ket noi , neu chon bo qua loi nay thi co nay set ve 0
	int Flag_Used_M10 = 1;   // mac dinh la co su dung khoi M10
	
	//byte  M9_ID_jack = 0;
	//byte M9_NumPin_Jack[9] = {NumPins_M9_J6_Jack_1, NumPins_M9_J5_Jack_2, NumPins_M9_J4_Jack_3, NumPins_M9_J1_Jack_4, NumPins_M9_JA3_Jack_5, NumPins_M9_JA5_Jack_6, NumPins_M9_JA2_Jack_7, NumPins_M9_JA1_Jack_8A, NumPins_M9_JA4_Jack_8B};
	int RUN_TEST_M9(void);    // test M9
	int Start_Apply_Relay_M9(byte ID_JACK);
	int Set_Paths_M9_test_JA1(void);
	int Set_Ithres_Protect_M7A(byte ID_Ithres_Pwr_Sys);
	int Get_Ithres_Protect_M7A(byte ID_Ithres_Pwr_Sys);

	int Set_UThres_HV_Protect_M7A(byte ID_UThres_HV_Pwr_Sys);
	int Get_UThres_HV_Protect_M7A(byte ID_UThres_HV_Pwr_Sys);
	int Get_Pwr_Info(byte ADDR_BOARD, byte *dlength, byte* data_RX);

	int dinh_tuyen_Flag = 0;    // co xac dinh he thong da duoc xoa dinh dinh tuyen chua, truoc khi thoat: 1: dang duoc dinh tuyen, 0: dinh tuyen dc reset ve default
	int CAN_Network_Flag_Connected = 0;    // cờ báo trạng thái mạng CAN:     == int StatusConnect;   // cờ báo trạng thái mạng CAN
	

	int Set_Paths_M2_SIG_i(byte ADDR_Board);
	int Set_Paths_M2_SIG(void);



	/// code for M4, M2Sig
	// Ma tran chuyen mach 8x8 cua M4
	uint8_t M4_CM_Arr[8];     
/* 
	0: KO KET NOI		 
	1: ket noi voi BUS 1;    
	2: knoi voi BUS 2, ....,
	....
	8: ket noi voi BUS 8.
*/

	// vi tri:[0..7]  <==> ADC1, ADC2, DAC1. DAC2, HV1, HV2, BNC1, BNC2
	//gia tri:
	//  0/ 4 : chi ADC_1
	//  1/ 5 : chi ADC_2
	// 	2/ 6 : chi DAC_1
	//  3/ 7 : chi DAC_2
	// cac vi tri thua con lai se dung cho cho HV_IN_1,2: chua xly

	// ma tran chuyen mach noi M4 voi Main M7
	uint8_t M4_CM_RL_CONNECT_TO_MAIN[8];     //   1: connect,   0: unconnect

	// ma tran danh dau cac kenh dau vao M4 da duoc su dung
	//uint8_t M4_Arr_Used[8];   // 0/1


	// ma tran thong tin dinh tuyen cho M2_Sig
	uint8_t M2_SIG_RL_Data_1[41];   // 0/1/2/3/4   : tai 1 hoi diem chi c
	uint8_t M2_SIG_RL_Data_2[41];   // 0/1/2/3/4

	void Process_setting_Analog_Channels(void);  // ham tinh toan cac ma tran dinh tuyen cho cac kenh analog: M2_Sig, M4
	int Set_Paths_M4_ADDA_BUFF(void);  // cau hinh cho khoi dem tin hieu ADDA_M4


	int HV_In_1_Scaler;			// he so chia dien ap dau vao
	int HV_In_2_Scaler;			// he so chia dien ap dau vao

	int HV_ADC_In_1_Scaler;			// he so chia dien ap dau vao
	int HV_ADC_in_2_Scaler;			// he so chia dien ap dau vao

	int Set_Param_M4_HV_Out(void);
	int Set_Param_M4_HV_In(void);
	int Set_Param_M4_ADC_In(void);  // tu Vin_max ham se tinh ra scaler va gui xuong cho tbi
	void M4_reset_EXT_IO_Dir(void);
	int Set_DIR_EXT_IO(void);   // thiet lap chieu IN/OUT cho 2 kenh do mong rong 5V
	int Set_Param_M4_ADDA_BUFF(void);  // thiet lap tham so cho M4



	// moi them
	float I_hientai_3v3_1 = 0, I_hientai_3v3_2 = 0;   // gia tri dòng hiện tại cua  hai nguon 3v3
	float I_hientai_12v_Relay_1 = 0, I_hientai_12v_Relay_2 = 0;   // gia tri dòng hiện tại cua  hai nguon 12V
	float I_max_3v_temp_1 = 0, I_max_3v_temp_2 = 0;
	float I_max_12V_Relay_temp_1 = 0, I_max_12V_Relay_temp_2 = 0;

	float I_hientai_3v3 = 0;
	float I_hientai_5v = 0;
	float I_hientai_12v = 0;
	float I_hientai_12v_N = 0;

	float I_hientai_12v_Relay = 0;
	float I_hientai_12v_CPU = 0;
	float I_hientai_30v = 0;

	POWER_STRUCT Pwr_M3_0[9];
	POWER_STRUCT Pwr_M3_1[9];

	int SetUp_I_Thres_8Power(POWERS_STRUCT m_8Power, char* pData_receiv, int* plenData_receiv); //Max lenData_receiv = 1024

	// khai bao them mang phu de luu trang thai truoc khi Reset all path, tat nguon, HV, AD
	int Temp_8PWR_on_off_save_stt[9];   // luu tam trang thai nguon ON/OFF truoc khi reset path
	int Tem_ADDA_HV_on_off_save_stt[9];    // luu tam trang thai cac kenh analog, HV. ON/OFF truoc khi reset path

};

