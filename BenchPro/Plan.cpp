#include "pch.h"
#include "Plan.h"
#include "INI.h"
#include "mta_io_client.hpp"
#include <stdio.h>
#include "afxdialogex.h"


//-------------------------------------------------------

int my_uart_send_data(char* data_write, uint32_t numb_byte_to_sent, char* data_read, uint32_t max_byte_to_receive, uint32_t timeout_ms, uint32_t Num_tries)
{
	uint32_t cnt = Num_tries;
	int ret = -1;
	while (cnt > 0)
	{
		ret = uart_sent_data(data_write, numb_byte_to_sent, data_read, max_byte_to_receive, timeout_ms);
		if (ret != -1) break;
		else cnt--;
		Sleep(1000);
	}

	//AfxMessageBox(_T("Mess"));
	return ret;
}


//---------------------------------------------------
uint16_t CPlan::convert_FloatTo16bit(float F_num, float factor_Num)
/*
 * return = (uint16_t) F_num/ factor_Num
 * factor_Num: = 0.1,   0.01, ..   0.001
 */
{
	float temp, fnum_temp = F_num;
	uint16_t Bin_N = 0;
	if (fnum_temp < 0) fnum_temp = -1.0 * fnum_temp;
	else  fnum_temp = 1.0 * fnum_temp;

	temp = fnum_temp / factor_Num;
	if (temp > 65535.0) temp = 65535.0;
	else;
	Bin_N = (uint16_t)temp;
	return Bin_N;
}

//---------------------------------------------------

void CPlan::convert_16bitToFoat(uint16_t Data, float factor_Num, float sign_f, float* float_Num)
// factor_Num: = 0.1,   0.01, ..   0.001
{
	float temp = 0.0;
	temp = (float)Data * factor_Num;
	temp = temp * sign_f;
	*float_Num = temp;
}
//---------------------------------------------------
void CPlan::PackageSerial(byte srcAddr, byte desAddr, byte Cmd, int subCmd, int versionFw, byte lenData, char* pData, byte* PkgData) {

	//MessageBox(_T(" 1sdfds"), _T(" sdfds"));
	//Header
	PkgData[0] = srcAddr;
	PkgData[1] = desAddr;

	PkgData[2] = Cmd;
	PkgData[3] = (subCmd & 0x0000ff00) >> 8;
	PkgData[4] = subCmd & 0x00ff;

	PkgData[5] = (versionFw & 0x0000ff00) >> 8;
	PkgData[6] = versionFw & 0x00ff;

	PkgData[7] = lenData;

	//Body
	for (int i = 0; i < lenData; i++)
		PkgData[8 + i] = pData[i];

}

int CPlan::SetUp8Power(POWERS_STRUCT m_8Power, char* pData_receiv, int* plenData_receiv) { //Max lenData_receiv = SIZE_MAX_BUFF_RX_SERIAL


	int m_nRet;
	int lenth_payload = 24;
	char mchar[64];   // 8 nguon ,moi nguon 3 tham so
	byte PkgData[SIZE_MAX_BUFF_RX_SERIAL];
	int32_t data16bit;
	//----------------
	POWER_STRUCT mPowers[9];
	for (int i = 1; i <= 8; i++) mPowers[i] = m_8Power.POWER[i];

	//---------------

	for (int i = 1; i <= 8; i++) {
		// nguon 1
		if (mPowers[i].ON_OFF != 0) mchar[(i - 1) * 3 + 0] = 0x01;
		else mchar[(i - 1) * 3 + 0] = 0x00;

		data16bit = convert_FloatTo16bit(mPowers[i].USet, FACTOR_SCALER_0P001);
		mchar[(i - 1) * 3 + 1] = (data16bit & 0xFF00) >> 8;
		mchar[(i - 1) * 3 + 2] = data16bit & 0x00FF;
	}
	//-------------------------
	//CString tmpsrt;
	//tmpsrt.Format(_T("%ld"), data16bit);
	//MessageBox(tmpsrt, tmpsrt);
	//-------------------------
	//-------------------------
	//CString tmpsrt;
	//tmpsrt.Format(_T("%d   %d   %d"), mchar[0], mchar[1], mchar[2]);
	//MessageBox(tmpsrt, tmpsrt);
	//-------------------------


	// send to M3_0
	// dong goi goi tin
	PackageSerial(ADDR_PC, ADDR_M3_0, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	m_nRet = my_uart_send_data((char*)PkgData, lenth_payload + LENGTH_HEADER, pData_receiv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	if (m_nRet == -1)
	{
		AfxMessageBox(_T("LỖI: Thiết lập nguồn M3_0 không thành công"));
		*plenData_receiv = 0;
		return -1;
	}
	else
	{
		//MessageBox(_T("Success!"), _T("Mess"));
		*plenData_receiv = m_nRet;
	}


	//	MessageBox(_T("Delay!"), _T("Mess"));
	//// send to M3_1: cau hinh nguon cho 3 board nhu nhau
	//// dong goi goi tin

		// Chu neu co phai  delay 500ms 
	Sleep(200);

	PackageSerial(ADDR_PC, ADDR_M3_1, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	m_nRet = my_uart_send_data((char*)PkgData, lenth_payload + LENGTH_HEADER, pData_receiv, SIZE_MAX_BUFF_RX_SERIAL,3000, 3);

	if (m_nRet == -1)
	{
		AfxMessageBox(_T("LỖI: Thiết lập nguồn M3_1 không thành công"));
		*plenData_receiv = 0;
		return -1;
	}
	else
	{
		//MessageBox(_T("Success!"), _T("Mess"));
		*plenData_receiv = m_nRet;

	}

	Sleep(2000);   // delay cho board xu ly xong
	return 0;
}


void CPlan::ExtrackPackage_Get_8PWR_Info(BYTE ADDR_M3_x)
{
	int m_nRet;
	int32_t lenth_payload;
	char mchar[64];   // 8 nguon ,moi nguon 3 tham so
	byte PkgData[256];
	int32_t data16bit;
	char Data_receiv[SIZE_MAX_BUFF_RX_SERIAL];
	int lenData_receiv;


	for (int i = 1; i <= 8; i++) {
		mTestCase.mPowers.POWER[i].Status = 0;
		mTestCase.mPowers.POWER[i].IGet = 0;
		mTestCase.mPowers.POWER[i].UGet = 0;
	}


	// doc nguon
	POWER_STRUCT Power_i[9];
	float fVtemp, fItemp;
	float bitSign; // 1: so duong, -1: so am


	// #################################################################################

	if ((ADDR_M3_x == ADDR_M3_0) || (ADDR_M3_x == ADDR_M3_1))
	{

		// lay  thong tin cua Bo nguon M3_0 de hien thi thong tin doc ve cho nguoi dung
		// send to M3_0
		// dong goi goi tin
		lenth_payload = 0;
		PackageSerial(ADDR_PC, ADDR_M3_x, CMD_READ_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
		m_nRet = my_uart_send_data((char*)PkgData, lenth_payload + LENGTH_HEADER, (char*)Data_receiv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

		if (m_nRet == -1)
		{
			AfxMessageBox(_T("LỖI: Đọc giá trị nguồn M3_[%d] không thành công"), ADDR_M3_x - ADDR_M3_0);
			lenData_receiv = 0;
			return;
		}
		else
		{
			//MessageBox(_T("Success!"), _T("Mess"));	
			lenData_receiv = m_nRet;
		}
		//=====================================
		// xu ly goi tin nhan ve
		//RECEI_POWERS_PACK * mReceiPowerPk;
		// 6 byte data for Power x 8 powers
		//-----------------------
		// struct RECEI_POWERS_PACK
		//{
		//	//Header: 0-7 byte
		//	//Power: 6 byte
		//	//		1: ON/OFF: 1 byte (ON =1, OFF = 0;
		//	//		
		//	byte ONOFF;  // 1,0
		//	byte ERR_OK; //0,1
		//	byte Vh;
		//	byte Vl;
		//	byte Ih;
		//	byte Il;

		//};
		//-----------------------

		// Check Header:
		// Addr_Mx
		// Addr_PC
		// Read_Param // CMR Lệnh
		// Mã tham số // sub CMD
		// Version FW = Version SW.
		//------------------------
		for (int i = 1; i <= 8; i++) {
			Power_i[i] = mTestCase.mPowers.POWER[i];
		}

		for (int i = 1; i <= 8; i++) {		// chi so nguon
			if (i <= 5) bitSign = 1;		// nguon duong
			else bitSign = -1;				// nguon am

			byte ONOFF = (Data_receiv[8 + (i - 1) * 6 + 0]);
			byte ERR_OK = (Data_receiv[8 + (i - 1) * 6 + 1]);
			byte Vh = (Data_receiv[8 + (i - 1) * 6 + 2]);
			byte Vl = (Data_receiv[8 + (i - 1) * 6 + 3]);
			byte Ih = (Data_receiv[8 + (i - 1) * 6 + 4]);
			byte Il = (Data_receiv[8 + (i - 1) * 6 + 5]);

			Power_i[i].Status = ERR_OK;
			if (Power_i[i].ON_OFF == 0)  Power_i[i].Status = 0;
			if (Power_i[i].ON_OFF != ONOFF)  Power_i[i].Status = 0;

			if (Power_i[i].Status)
			{
				data16bit = Vh * 256 + Vl;
				convert_16bitToFoat(data16bit, FACTOR_SCALER_0P001, bitSign, &fVtemp);
				data16bit = Ih * 256 + Il;
				convert_16bitToFoat(data16bit, FACTOR_SCALER_0P001, 1, &fItemp);  //bitSign = dong luon duong

				Power_i[i].IGet = (float)fItemp;
				Power_i[i].UGet = (float)fVtemp;
			}
			else
			{
				Power_i[i].IGet = 0.0;
				Power_i[i].UGet = 0.0;

			}

		}
		//--------------- up date nguoc lai tham so --------------
		for (int i = 1; i <= 8; i++)
		{
			//mTestCase.mPowers.POWER[i] = Pwr_M3_0[i];
			if (ADDR_M3_x == ADDR_M3_0)
				Pwr_M3_0[i] = Power_i[i];
			else if (ADDR_M3_x == ADDR_M3_1)
				Pwr_M3_1[i] = Power_i[i];
		}
	}
}



//----------------------------------------------
//int CPlan::CheckEditInt(CString str, int min, int max) {
//	int number = 0;
//	f
//	if (AfxStringToInt(str, number))
//	{
//		MessageBox(_T("Đây là một số."), _T("Thông báo"), MB_ICONINFORMATION);
//	}
//		else
//		{
//			MessageBox(_T("Đây không phải là số."), _T("Thông báo"), MB_ICONWARNING);
//			}
//}
//----------------------------------------------
int CPlan::Load_PhiFileConfigPath(CIniReader* m_pCIniReader) {
	CString strSection;
	CString strValue, strKey;

	if (m_pCIniReader == NULL) return -1;

	strSection = _T("FILEPATH");
	strKey = _T("datarootpath");
	strValue = m_pCIniReader->getKeyValue(strKey, strSection);
	mTestCase.mPathInfo.PhiFileConfigPath = strValue + _T("\\FilePath\\FilePath.txt");

	strKey = _T("datanamefolder");
	strValue = m_pCIniReader->getKeyValue(strKey, strSection);
	mTestCase.mPathInfo.datanamefolder = strValue;
	return 1;
}
//----------------------------------------------
int CPlan::Load_UserName_UserPath(CIniReader* m_pIniReader) {
	
	CString strSection;
	CString strValue, strKey;

	if (m_pIniReader == NULL) return -1;

	strSection = _T("FILEPATH");
	strKey = _T("filepath");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	mTestCase.mPathInfo.PhiPath = strValue;

	strKey = _T("username");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	mTestCase.mPathInfo.Usermane = strValue;

return 1;
}
//----------------------------------------------
int CPlan::Load_AdminName(CIniReader* m_pIniReader) {

	CString strSection;
	CString strValue, strKey;

	if (m_pIniReader == NULL) return -1;
	strSection = "FILEPATH";
	strKey = _T("admin");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	mTestCase.mPathInfo.Usermane = strValue;

	return 1;
}
//----------------------------------------------
int CPlan::Load_Define_TestCase(CIniReader* m_pIniReader)
{
	return 1;
	CString strSection;
	CString strValue, strKey;
	if (m_pIniReader == NULL) return -1;
	//-------------------------------------------------
	strSection = _T("DEFINE");
	strKey = _T("POWER_P1");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.POWER_P1));

	strKey = _T("POWER_P2");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.POWER_P2));

	strKey = _T("POWER_P3");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.POWER_P3));

	strKey = _T("POWER_P4");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.POWER_P4));

	strKey = _T("POWER_P5");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.POWER_P5));

	strKey = _T("POWER_N6");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.POWER_N6));

	strKey = _T("POWER_N7");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.POWER_N7));

	strKey = _T("POWER_N8");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.POWER_N8));
	//--------------------------
	strKey = _T("GND");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.GND));

	strKey = _T("LOGIC_IN");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.LOGIC_IN));

	strKey = _T("LOGIC_IN_PUP");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.LOGIC_IN_PUP));

	strKey = _T("LOGIC_OUT");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.LOGIC_OUT));

	strKey = _T("CLOCK_OUT");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.CLOCK_OUT));
	//----------------------------------------------
	strKey = _T("ADC1");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.ADC1));

	strKey = _T("ADC2");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.ADC2));

	strKey = _T("DAC1");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.DAC1));

	strKey = _T("DAC2");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.DAC2));

	strKey = _T("HIVOLTAGE_OUT1");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.HIVOLTAGE_OUT1));

	strKey = _T("HIVOLTAGE_OUT2");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.HIVOLTAGE_OUT2));

	strKey = _T("HIVOLTAGE_IN1");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.HIVOLTAGE_IN1));

	strKey = _T("HIVOLTAGE_IN2");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.HIVOLTAGE_IN2));

	strKey = _T("EX_OUT1");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.EX_OUT1));

	strKey = _T("EX_OUT2");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.EX_OUT2));

	strKey = _T("EX_IN1");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.EX_IN1));

	strKey = _T("EX_IN2");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.EX_IN2));

	strKey = _T("SYS_1");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.SYS_1));

	strKey = _T("SYS_2");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mConfigDef.SYS_2));

	return 1;
}
//----------------------------------------------
int CPlan::Load_PathInfo_TestCase(CIniReader* m_pIniReader) {
	return 1;
	CString strSection;
	CString strValue, strKey;

	if (m_pIniReader == NULL) return -1;

	strSection = _T("PATHINFO");
	strKey = _T("DevicePath");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	mTestCase.mPathInfo.DevicePath = strValue;

	//strKey = _T("DeviceFolderName");
	//strValue = m_pIniReader->getKeyValue(strKey, strSection);
	//mTestCase.mPathInfo.DeviceFolderName = strValue;

	//strKey = _T("BoardFolderName");
	//strValue = m_pIniReader->getKeyValue(strKey, strSection);
	//mTestCase.mPathInfo.BoardFolderName = strValue;

	//strKey = _T("BoardName");
	//strValue = m_pIniReader->getKeyValue(strKey, strSection);
	//mTestCase.mPathInfo.BoardName = strValue;

	//strKey = _T("DevicePicName");
	//strValue = m_pIniReader->getKeyValue(strKey, strSection);
	//mTestCase.mPathInfo.DevicePicName = strValue;


	//strKey = _T("BoardPicName");
	//strValue = m_pIniReader->getKeyValue(strKey, strSection);
	//mTestCase.mPathInfo.BoardPicName = strValue;
	return 1;
}
//----------------------------------------------------
int CPlan::Load_JackInfo_TestCase(CIniReader* m_pIniReader) {
	CString strSection;
	CString strValue, strKey;

	if (m_pIniReader == NULL) return -1;
	//---------------------------------------
	JACK_ROW_DEF _JackRow;
	JACK_DEF _Jack;
	std::vector<JACK_DEF> _JACKS;

	int sPlit0, sPlit1;
	CString Strtmp;
	//--------------------------------------
	strSection = _T("JACKSINFO");
	int _nJacks, _nRows, _nPins, _nSumPin = 0;
	CString _JackSign, _JackName;

	strKey = _T("ID_Jack");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(mTestCase.mID_Jack));

	strKey = _T("NumItems");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(_nJacks));
	mTestCase.mJackInfo.nJacks = _nJacks;

	for (int i = 0; i < _nJacks; i++) {
		strKey.Format(_T("Item_%d"), i);
		strValue = m_pIniReader->getKeyValue(strKey, strSection);
		//------------------------------------------
		int iiRow, iicount = 0, iiflag = 0;
		sPlit0 = 0;
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		sPlit0 = sPlit1 + 1;
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		sPlit0 = sPlit1 + 1;
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
		swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(iiRow));
		while (sPlit1 > 0) {
			sPlit0 = sPlit1 + 1;
			sPlit1 = strValue.Find(_T(';'), sPlit0);
			iicount++;
		}
		if (iicount == iiRow + 1) iiflag = 1;
		//------------------------------------------
		sPlit0 = 0;
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		_JackSign = strValue.Mid(sPlit0, sPlit1 - sPlit0);

		if (iiflag) {
			sPlit0 = sPlit1 + 1;
			sPlit1 = strValue.Find(_T(';'), sPlit0);
			_JackName = strValue.Mid(sPlit0, sPlit1 - sPlit0);
		}
		else _JackName = _T("");

		sPlit0 = sPlit1 + 1;
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
		swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_nRows));
		_Jack.mJACK_ROW.clear();
		for (int j = 0; j < _nRows; j++)
		{
			sPlit0 = sPlit1 + 1;
			sPlit1 = strValue.Find(_T(';'), sPlit0);
			Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
			swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_nPins));

			_JackRow.JackRowSign.Format(_T("%s_%c"), _JackSign, j + 65);
			_JackRow.Pins = _nPins;
			_nSumPin += _nPins;
			_Jack.mJACK_ROW.push_back(_JackRow);
		}
		_Jack.JackName = _JackName;
		_Jack.JackSign = _JackSign;
		_Jack.nJackRows = _nRows;
		_JACKS.push_back(_Jack);
	}
	mTestCase.mJackInfo.mJACKS = _JACKS;
	mTestCase.mTestCaseConfig.nPins = _nSumPin;

	return 1;
}
//-----------------------------------------------------
int CPlan::Load_TestCaseConfig(CIniReader* m_pIniReader) {
	CString strSection;
	CString strValue, strKey;
	int sPlit0, sPlit1;
	CString Strtmp;
	if (m_pIniReader == NULL) return -1;
	//--------------------------------------
	strSection = _T("TESTCASECONFIG");
	TESTCASE_CONFIG* _pTestCaseConfig;
	_pTestCaseConfig = &(mTestCase.mTestCaseConfig);

	strKey = _T("nChanel");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(_pTestCaseConfig->nChanels));

	//------ reset -----
	byte tmpPins = 256;
	for (byte i = 0; i <= tmpPins; i++)
	{
		_pTestCaseConfig->mPinsConf[i].iChanel = 0;
	}
	//-----------------
	int _ni = 1;
	int _nArr = 1;
	while (_nArr * 10 < _pTestCaseConfig->nPins) {
		strKey.Format(_T("MapPinArr%d"), _nArr);
		strValue = m_pIniReader->getKeyValue(strKey, strSection);

		sPlit0 = 0;
		for (int i = (_nArr - 1) * 10 + 1; i <= _nArr * 10; i++)
		{
			sPlit1 = strValue.Find(_T(';'), sPlit0);
			Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
			swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pTestCaseConfig->mPinsConf[_ni].iChanel));
			_ni++;
			sPlit0 = sPlit1 + 1;
		}
		_nArr++;
	}
	strKey.Format(_T("MapPinArr%d"), _nArr);
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	sPlit0 = 0;
	for (int i = (_nArr - 1) * 10 + 1; i <= _pTestCaseConfig->nPins; i++)
	{
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
		swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pTestCaseConfig->mPinsConf[i].iChanel));
		sPlit0 = sPlit1 + 1;
	}
	//======================================
	//------ reset -----
	tmpPins = 256;
	for (byte i = 0; i <= tmpPins; i++)
	{
		_pTestCaseConfig->mPinsConf[i].mPinName = _T("");
	}
	//-----------------
	_ni = 1;
	_nArr = 1;
	while (_nArr * 10 < _pTestCaseConfig->nPins) {
		strKey.Format(_T("PinNameArr%d"), _nArr);
		strValue = m_pIniReader->getKeyValue(strKey, strSection);

		sPlit0 = 0;
		for (int i = (_nArr - 1) * 10 + 1; i <= _nArr * 10; i++)
		{
			sPlit1 = strValue.Find(_T(';'), sPlit0);
			Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
			_pTestCaseConfig->mPinsConf[_ni].mPinName = Strtmp;
			_ni++;
			sPlit0 = sPlit1 + 1;
		}
		_nArr++;
	}
	strKey.Format(_T("PinNameArr%d"), _nArr);
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	sPlit0 = 0;
	for (int i = (_nArr - 1) * 10 + 1; i <= _pTestCaseConfig->nPins; i++)
	{
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
		_pTestCaseConfig->mPinsConf[i].mPinName = Strtmp;
		sPlit0 = sPlit1 + 1;
	}

	//======================================
	//------ reset -----------------------
	byte tmpChanels = 85;
	for (byte i = 0; i <= tmpChanels; i++)
	{
		_pTestCaseConfig->ChanelSelectArr[i] = 0;
	}

	//---------------------------
	_ni = 1;
	_nArr = 1;
	while (_nArr * 10 < _pTestCaseConfig->nChanels) {
		strKey.Format(_T("ChanelSelectArr%d"), _nArr);
		strValue = m_pIniReader->getKeyValue(strKey, strSection);

		sPlit0 = 0;
		for (int i = (_nArr - 1) * 10 + 1; i <= _nArr * 10; i++)
		{
			sPlit1 = strValue.Find(_T(';'), sPlit0);
			Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
			swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pTestCaseConfig->ChanelSelectArr[_ni]));
			_ni++;
			sPlit0 = sPlit1 + 1;
		}
		_nArr++;
	}
	strKey.Format(_T("ChanelSelectArr%d"), _nArr);
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	sPlit0 = 0;
	for (int i = (_nArr - 1) * 10 + 1; i <= _pTestCaseConfig->nChanels; i++)
	{
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
		swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pTestCaseConfig->ChanelSelectArr[i]));
		sPlit0 = sPlit1 + 1;
	}
	//---------------------------
	//------ reset --------------
	tmpChanels = 85; //DUK   MAX_CHANELS;
	for (byte i = 0; i <= tmpChanels; i++)
	{
		_pTestCaseConfig->ChanelPUPConfigArr[i] = 0;
	}
	//---------------------------
	_ni = 1;
	_nArr = 1;
	while (_nArr * 10 < _pTestCaseConfig->nChanels) {
		strKey.Format(_T("ChanelPUPConfigArr%d"), _nArr);
		strValue = m_pIniReader->getKeyValue(strKey, strSection);

		sPlit0 = 0;
		for (int i = (_nArr - 1) * 10 + 1; i <= _nArr * 10; i++)
		{
			sPlit1 = strValue.Find(_T(';'), sPlit0);
			Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
			swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pTestCaseConfig->ChanelPUPConfigArr[_ni]));
			_ni++;
			sPlit0 = sPlit1 + 1;
		}
		_nArr++;
	}
	strKey.Format(_T("ChanelPUPConfigArr%d"), _nArr);
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	sPlit0 = 0;
	for (int i = (_nArr - 1) * 10 + 1; i <= _pTestCaseConfig->nChanels; i++)
	{
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
		swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pTestCaseConfig->ChanelPUPConfigArr[i]));
		sPlit0 = sPlit1 + 1;
	}
	//---------------------------
	//------ reset --------------
	tmpChanels = 85; //DUK   MAX_CHANELS;
	for (byte i = 0; i <= tmpChanels; i++)
	{
		_pTestCaseConfig->ChanelConfigArr[i] = 0;
	}
	//---------------------------
	_ni = 1;
	_nArr = 1;
	while (_nArr * 10 < _pTestCaseConfig->nChanels) {
		strKey.Format(_T("ChanelConfigArr%d"), _nArr);
		strValue = m_pIniReader->getKeyValue(strKey, strSection);

		sPlit0 = 0;
		for (int i = (_nArr - 1) * 10 + 1; i <= _nArr * 10; i++)
		{
			sPlit1 = strValue.Find(_T(';'), sPlit0);
			Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
			swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pTestCaseConfig->ChanelConfigArr[_ni]));
			_ni++;
			sPlit0 = sPlit1 + 1;
		}
		_nArr++;
	}
	strKey.Format(_T("ChanelConfigArr%d"), _nArr);
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	sPlit0 = 0;
	for (int i = (_nArr - 1) * 10 + 1; i <= _pTestCaseConfig->nChanels; i++)
	{
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
		swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pTestCaseConfig->ChanelConfigArr[i]));
		sPlit0 = sPlit1 + 1;
	}
	//----------------------------
	//init ChanelGridConfigArr1[]
	//---------------------------
	for (byte i = 0; i <= tmpChanels; i++)
	{
		_pTestCaseConfig->ChanelGridConfigArr[i] = _pTestCaseConfig->ChanelConfigArr[i];
		if (_pTestCaseConfig->ChanelGridConfigArr[i] > BUS_PROPERTY_LOGIC_IN) _pTestCaseConfig->ChanelGridConfigArr[i]++;
		_pTestCaseConfig->ChanelGridConfigArr[i] += _pTestCaseConfig->ChanelPUPConfigArr[i];
	}
	//---------------------------
	return 1;
}
//---------------------------------------------
int CPlan::Load_8PowerParam_TestCase(CIniReader* m_pIniReader) {
	CString strSection;
	CString strValue, strKey;
	int sPlit0, sPlit1;
	CString Strtmp;
	if (m_pIniReader == NULL) return -1;
	//--------------------------------------
	strSection = _T("CONFIG_8_POWERS");
	POWERS_STRUCT* _pPowers;
	_pPowers = &(mTestCase.mPowers);

	//strKey = _T("PowerVerifyThreshol");
	//strValue = m_pIniReader->getKeyValue(strKey, strSection);
	//swscanf_s(strValue.GetBuffer(), _T("%f"), &(_pPowers->PowerVerifyThreshol));

	for (int i = 1; i <= 8; i++) {

		strKey.Format(_T("POWER_P%d"), i);
		strValue = m_pIniReader->getKeyValue(strKey, strSection);

		sPlit0 = 0;
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
		swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pPowers->POWER[i].ON_OFF));

		sPlit0 = sPlit1 + 1;
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
		swscanf_s(Strtmp.GetBuffer(), _T("%f"), &(_pPowers->POWER[i].USet));

		sPlit0 = sPlit1 + 1;
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
		swscanf_s(Strtmp.GetBuffer(), _T("%f"), &(_pPowers->POWER[i].ImaxSet));

		sPlit0 = sPlit1 + 1;
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
		_pPowers->POWER[i].UGet = 0;

		sPlit0 = sPlit1 + 1;
		sPlit1 = strValue.Find(_T(';'), sPlit0);
		Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
		_pPowers->POWER[i].IGet = 0;
	}
	return 1;
}

//------------------------------------------------
int CPlan::Load_EXTChanel_TestCase(CIniReader* m_pIniReader) {
	CString strSection;
	CString strValue, strKey;
	int sPlit0, sPlit1;
	CString Strtmp;
	if (m_pIniReader == NULL) return -1;
	//--------------------------------------
	strSection = _T("EXTCHANEL");
	EXTCHANELINFO_DEF * _pExtChanel_Set;
	_pExtChanel_Set = &(mTestCase.ExtChanel_Set);

	strKey = _T("SignParaVerifyThreshol");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(_pExtChanel_Set->SignParaVerifyThreshol));
	//------------------------------
	strKey = _T("SetMode");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%d"), &(_pExtChanel_Set->SetMode));
	//------------------------------
	strKey = _T("HV_out1");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	
	sPlit0 = 0;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->HV_out1.used));
	
	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%f"), &(_pExtChanel_Set->HV_out1.value));
	
	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	_pExtChanel_Set->HV_out1.name = Strtmp;
	
	//------------------------------
	strKey = _T("HV_out2");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);

	sPlit0 = 0;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->HV_out2.used));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%f"), &(_pExtChanel_Set->HV_out2.value));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	_pExtChanel_Set->HV_out2.name = Strtmp;
	
	//------------------------------
	strKey = _T("HV_in1");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);

	sPlit0 = 0;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->HV_in1.used));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%f"), &(_pExtChanel_Set->HV_in1.value));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	_pExtChanel_Set->HV_in1.name = Strtmp;
	
	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->HV_in1.nChanel));
	_pExtChanel_Set->HV_in1.nChanel = 83;
	//------------------------------
	strKey = _T("HV_in2");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);

	sPlit0 = 0;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->HV_in2.used));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%f"), &(_pExtChanel_Set->HV_in2.value));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	_pExtChanel_Set->HV_in2.name = Strtmp;
	
	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->HV_in2.nChanel));
	_pExtChanel_Set->HV_in2.nChanel = 84;
	//------------------------------
	strKey = _T("EXT_io1");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);

	sPlit0 = 0;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->EXT_io1.used));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	_pExtChanel_Set->EXT_io1.name = Strtmp;
	
	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	_pExtChanel_Set->EXT_io1.text = Strtmp;

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->EXT_io1.IN_OUT));
	//------------------------------
	strKey = _T("EXT_io2");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);

	sPlit0 = 0;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->EXT_io2.used));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	_pExtChanel_Set->EXT_io2.name = Strtmp;
	
	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	_pExtChanel_Set->EXT_io2.text = Strtmp;

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->EXT_io2.IN_OUT));

	//------------------------------
	strKey = _T("ADC_in1");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);

	sPlit0 = 0;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->ADC_in1.used));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	_pExtChanel_Set->ADC_in1.name = Strtmp;
	
	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%f"), &(_pExtChanel_Set->ADC_in1.value));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->ADC_in1.nChanel));
	//------------------------------
	strKey = _T("ADC_in2");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);

	sPlit0 = 0;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->ADC_in2.used));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	_pExtChanel_Set->ADC_in2.name = Strtmp;

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%f"), &(_pExtChanel_Set->ADC_in2.value));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->ADC_in2.nChanel));
	//------------------------------
	strKey = _T("DAC_out1");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);

	sPlit0 = 0;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->DAC_out1.used));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	_pExtChanel_Set->DAC_out1.name = Strtmp;

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%f"), &(_pExtChanel_Set->DAC_out1.value));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->DAC_out1.nChanel));
	//------------------------------
	strKey = _T("DAC_out2");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);

	sPlit0 = 0;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->DAC_out2.used));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	_pExtChanel_Set->DAC_out2.name = Strtmp;

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%f"), &(_pExtChanel_Set->DAC_out2.value));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%d"), &(_pExtChanel_Set->DAC_out2.nChanel));
	//------------------------------
	strKey = _T("LOGIC_IN_V_COMPARE");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	sPlit0 = 0;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%f"), &(_pExtChanel_Set->LogicInComp.value));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	_pExtChanel_Set->LogicInComp.name = Strtmp;
	
	strKey = _T("LOGIC_OUT_V_HI");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	sPlit0 = 0;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	swscanf_s(Strtmp.GetBuffer(), _T("%f"), &(_pExtChanel_Set->LogicOutHi.value));

	sPlit0 = sPlit1 + 1;
	sPlit1 = strValue.Find(_T(";"), sPlit0);
	Strtmp = strValue.Mid(sPlit0, sPlit1 - sPlit0);
	_pExtChanel_Set->LogicOutHi.name = Strtmp;

	return 1;
}
//------------------------------------------------------
int CPlan::Load_MODE_TestCase(CIniReader* m_pIniReader){
	CString strSection;
	CString strValue, strKey;
	int sPlit0, sPlit1;
	CString Strtmp;
	if (m_pIniReader == NULL) return -1;
	//-------------------------------------------
	strSection = _T("MODE");
	strKey = _T("SYNC_MODE");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(mTestCase.mMode.SYNC_MODE));

	strKey = _T("F_SAMPLE");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(mTestCase.mMode.F_SAMPLE));

	return 1;
}
//----------------------------------------------
int CPlan::Load_SUPPLY_TestCase(CIniReader* m_pIniReader) {
	CString strSection;
	CString strValue, strKey;
	int sPlit0, sPlit1;
	CString Strtmp;
	if (m_pIniReader == NULL) return -1;
	//--------------------------------------
	strSection = _T("SUPPLY");
	SUPPLY* _pSupply_Set;
	_pSupply_Set = &(mTestCase.mSupply_Set);

	strKey = _T("Imax_3v3");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(_pSupply_Set->Imax_3v3));


	strKey = _T("Imax_5v");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(_pSupply_Set->Imax_5v));

	strKey = _T("Imax_12v");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(_pSupply_Set->Imax_12v));

	strKey = _T("Imax_12v_N");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(_pSupply_Set->Imax_12v_N));

	strKey = _T("Imax_12v_CPU");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(_pSupply_Set->Imax_12v_CPU));

	strKey = _T("Imax_12v_ROLE");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(_pSupply_Set->Imax_12v_ROLE));


	strKey = _T("Imax_30v");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(_pSupply_Set->Imax_30v));

	strKey = _T("U12v_UP");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(_pSupply_Set->U12v_UP));

	strKey = _T("U12v_DOWN");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(_pSupply_Set->U12v_DOWN));

	strKey = _T("U30v_UP");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(_pSupply_Set->U30v_UP));

	strKey = _T("U30v_DOWN");
	strValue = m_pIniReader->getKeyValue(strKey, strSection);
	swscanf_s(strValue.GetBuffer(), _T("%f"), &(_pSupply_Set->U30v_DOWN));

	return 1;
}
//---------------------------------------------------------------
int CPlan::LoadTestCase(CIniReader* m_pIniReader)
{
	int mResult;
	mResult = Load_Define_TestCase(m_pIniReader);
	if (mResult == -1) return mResult;
	mResult = Load_PathInfo_TestCase(m_pIniReader);
	if (mResult == -1) return mResult;
	mResult = Load_JackInfo_TestCase(m_pIniReader);
	if (mResult == -1) return mResult;
	mResult = Load_TestCaseConfig(m_pIniReader);
	if (mResult == -1) return mResult;
	mResult = Load_8PowerParam_TestCase(m_pIniReader);
	if (mResult == -1) return mResult;
	mResult = Load_EXTChanel_TestCase(m_pIniReader);
	if (mResult == -1) return mResult;
	mResult = Load_MODE_TestCase(m_pIniReader);
	if (mResult == -1) return mResult;
	mResult = Load_SUPPLY_TestCase(m_pIniReader);
	return mResult;
}
//===============================================================================

//byte GridHeaderRowsArr[256];
//CString GUIGridArr[256][100];
//int PinGridArr[256][100]; // -1: Ko dung; 0: No connect; 1..84 : chanel 
//int ChanelGridArr[256][100]; // 0: Ko dung; 1-23: atribute chanel
//-----------------------------------------------------------------------
int CPlan::CheckStrToNum(CString s_Num, int ChkMaxMin, float max, float min, int ChkAmDuong, int sign) {
		CString Num;
		float epsilon = 0.001;
		int flag = 0;
		float _Num = 0;
		int start = 0;
		if (s_Num[0] == '-') start = 1;
		for (int i = start; i < s_Num.GetLength(); i++) {
			if (s_Num[i] == '.') {
				if (flag == 0) flag = 1;
				else return 1;
			}
			else if (s_Num[i] > '9' || s_Num[i] < '0') return 1;
		}
		swscanf_s(s_Num, _T("%f"), &_Num);
		if (ChkMaxMin && ((_Num > max+ epsilon) || (_Num < min - epsilon))) return 2;
		if (ChkAmDuong && _Num * sign < 0) return 3;
		return 0;
	}

//===============================================================================
void CPlan::Init_PinGrid_GridHeader_GUIGridArr() {
	JACK_INFO _JackInfo;
	JACK_DEF _Jack;
	JACK_ROW_DEF _JackRows;

	int nRows, nCols = -1;
	int nMaxRow = 0, nMaxCol = 0;
	int n_Jacks, n_JackRows;
	int nJackPin = 0;

	int _nPin = 0;
	CString strSignTmp;

	TESTCASE_CONFIG	*_pTestCaseConfig;
	_pTestCaseConfig = &(mTestCase.mTestCaseConfig);

	for (int i = 0; i < 255; i++)
		for (int j = 0; j < 100; j++) {
			_pTestCaseConfig->PinGridArr[i][j] = -1;
			_pTestCaseConfig->PinNameGridArr[i][j] = _T("");
		}

	_JackInfo = mTestCase.mJackInfo;
	n_Jacks = _JackInfo.mJACKS.size();
	for (int i = 0; i < n_Jacks; i++) {
		nJackPin = 0;
		_Jack = _JackInfo.mJACKS.at(i);
		n_JackRows = _Jack.mJACK_ROW.size();
		for (int j = 0; j < n_JackRows; j++) {
			_JackRows = _Jack.mJACK_ROW.at(j);
			nRows = _JackRows.Pins;
			if (nMaxRow < nRows) nMaxRow = nRows;
			nCols += 1;
			_pTestCaseConfig->GridHeaderRowsArr[nCols] = nRows;
			//--------------------------
			_JackRows.JackRowSign.Format(_T("%s_%c"), _Jack.JackSign, j + 65);
			_pTestCaseConfig->GUIGridArr[0][nCols] = _JackRows.JackRowSign;
			for (int iRow = 1; iRow <= nRows; iRow++) {
				nJackPin++;
				_pTestCaseConfig->GUIGridArr[iRow][nCols].Format(_T("%d"), nJackPin);
				_pTestCaseConfig->PinGridArr[iRow][nCols] = 0;
				strSignTmp = _JackRows.JackRowSign + _pTestCaseConfig->GUIGridArr[iRow][nCols];
				_nPin++;
				_pTestCaseConfig->mPinsConf[_nPin].mPinSign = strSignTmp;
			}
			//----------------------------
		}
	}
	nMaxCol = nCols + 1;
	nMaxRow = nMaxRow + 1;
	_pTestCaseConfig->ArrCols = nMaxCol;
	_pTestCaseConfig->ArrRows = nMaxRow;

	//--------------------------
	_nPin = 1;
	for (int col = 0; col < nMaxCol; col++)
		for (int row = 1; row <= _pTestCaseConfig->GridHeaderRowsArr[col]; row++) {
			_pTestCaseConfig->PinGridArr[row][col] = _pTestCaseConfig->mPinsConf[_nPin].iChanel;
			_pTestCaseConfig->PinNameGridArr[row][col] = _pTestCaseConfig->mPinsConf[_nPin].mPinName;
			_nPin++;
		}
}
//-----------------------------------------
void CPlan::Init_ChanelGridArr() {
	TESTCASE_CONFIG* _pTestCaseConfig;
	_pTestCaseConfig = &mTestCase.mTestCaseConfig;
	int nMaxCol = _pTestCaseConfig->ArrCols;

	for (int i = 0; i < 255; i++)
		for (int j = 0; j < 100; j++) {
			_pTestCaseConfig->ChanelGridArr[i][j] = 0;
		}
	int _chanelTmp;
	for (int col = 0; col < nMaxCol; col++)
		for (int row = 1; row <= _pTestCaseConfig->GridHeaderRowsArr[col]; row++) {
			_chanelTmp = _pTestCaseConfig->PinGridArr[row][col];
			if (_chanelTmp > 0)
				_pTestCaseConfig->ChanelGridArr[row][col] = _pTestCaseConfig->ChanelGridConfigArr[_chanelTmp];
		}
}
//------------------------------------------
void CPlan::New_PinGrid_GridHeader_GUIGridArr() {
	JACK_INFO _JackInfo;
	JACK_DEF _Jack;
	JACK_ROW_DEF _JackRows;

	int nRows, nCols = -1;
	int nMaxRow = 0, nMaxCol = 0;
	int n_Jacks, n_JackRows;
	int nJackPin = 0;

	int _nPin = 0;
	CString strSignTmp;

	TESTCASE_CONFIG* _pTestCaseConfig;
	_pTestCaseConfig = &mTestCase.mTestCaseConfig;
	for (int i = 0; i < 255; i++)
		for (int j = 0; j < 100; j++) {
			_pTestCaseConfig->PinGridArr[i][j] = -1;
			_pTestCaseConfig->PinNameGridArr[i][j] = _T("");
		}

	_JackInfo = mTestCase.mJackInfo;
	n_Jacks = _JackInfo.mJACKS.size();
	for (int i = 0; i < n_Jacks; i++) {
		_Jack = _JackInfo.mJACKS.at(i);
		n_JackRows = _Jack.mJACK_ROW.size();
		for (int j = 0; j < n_JackRows; j++) {
			_JackRows = _Jack.mJACK_ROW.at(j);
			nRows = _JackRows.Pins;
			if (nMaxRow < nRows) nMaxRow = nRows;
			nCols += 1;
			_pTestCaseConfig->GridHeaderRowsArr[nCols] = nRows;
			//--------------------------
			_JackRows.JackRowSign.Format(_T("%s_%c"), _Jack.JackSign, j + 65);
			_pTestCaseConfig->GUIGridArr[0][nCols] = _JackRows.JackRowSign;
			for (int iRow = 1; iRow <= nRows; iRow++) {
				nJackPin++;
				_pTestCaseConfig->GUIGridArr[iRow][nCols].Format(_T("%d"), nJackPin);
				_pTestCaseConfig->PinGridArr[iRow][nCols] = 0;
				strSignTmp = _JackRows.JackRowSign + _pTestCaseConfig->GUIGridArr[iRow][nCols];
				_nPin++;
				_pTestCaseConfig->mPinsConf[_nPin].mPinSign = strSignTmp;
			}
			//----------------------------
		}
	}
	nMaxCol = nCols + 1;
	nMaxRow = nMaxRow + 1;
	_pTestCaseConfig->ArrCols = nMaxCol;
	_pTestCaseConfig->ArrRows = nMaxRow;

	//--------------------------
}
//-----------------------------------------
void CPlan::New_ChanelGridArr() {
	TESTCASE_CONFIG* _pTestCaseConfig;
	_pTestCaseConfig = &mTestCase.mTestCaseConfig;
	int nMaxCol = _pTestCaseConfig->ArrCols;

	for (int i = 0; i < 255; i++)
		for (int j = 0; j < 100; j++) {
			_pTestCaseConfig->ChanelGridArr[i][j] = -1;
		}
	int _chanelTmp;
	for (int col = 0; col < nMaxCol; col++)
		for (int row = 1; row <= _pTestCaseConfig->GridHeaderRowsArr[col]; row++) {
			_pTestCaseConfig->ChanelGridArr[row][col] = 0;
		}
}
//===============================================================================
// return 
//	0->OK; 
//	1-> nJack
//	2-> nPin
//  4-> MapPinArr err, range > nchanel or range < 0 
//  3 ->  1 + 2
//  7 -> 1 + 2 + 4
int CPlan::Check_MapPinArr() { 
	int Err = 0;
	JACK_INFO _JackInfo;
	JACK_ROW_DEF _JackRow;
	JACK_DEF _Jack;
	std::vector<JACK_DEF> _JACKS;

	int n_Jack;
	int n_Jack_Row;
	int nPinSum = 0;

	_JackInfo = mTestCase.mJackInfo;
	_JACKS = _JackInfo.mJACKS;

	n_Jack = _JACKS.size();
	if (n_Jack != _JackInfo.nJacks) {
		Err = 1;
		_JackInfo.nJacks = n_Jack;
	}

	for (int i = 0; i < n_Jack; i++) {
		_Jack = _JACKS.at(i);
		n_Jack_Row = _Jack.mJACK_ROW.size();
		if (n_Jack_Row != _Jack.nJackRows) {
			_Jack.nJackRows = n_Jack_Row;
			_JACKS.at(i) = _Jack;
		}
		for (int j = 0; j < n_Jack_Row; j++) {
			_JackRow = _Jack.mJACK_ROW.at(j);
			nPinSum += _JackRow.Pins;
		}
	}
	_JackInfo.mJACKS = _JACKS;
	//-------------------------
	mTestCase.mJackInfo= _JackInfo;
	if (mTestCase.mTestCaseConfig.nPins != nPinSum) {
		Err+=2;
		mTestCase.mTestCaseConfig.nPins = nPinSum;
	}
	//-----------------------
	int _nChanelTmp = mTestCase.mTestCaseConfig.nChanels;
	for (int i = 1; i <= nPinSum; i++) {
		if (mTestCase.mTestCaseConfig.mPinsConf[i].iChanel > _nChanelTmp) {
			if (mTestCase.mTestCaseConfig.mPinsConf[i].iChanel < 100 || mTestCase.mTestCaseConfig.mPinsConf[i].iChanel > 103) {
				Err += 4;
				return Err;
			}
		}
		if (mTestCase.mTestCaseConfig.mPinsConf[i].iChanel <  0) {
			Err+=4;
			return Err;
		}
	}
	return Err;
}
////----------------------------------
//byte MapPinArr[256];		// max 250	: 1..255
//byte ChanelSelectArr[85];	// max 84	: 1..84 : value 0,1
//byte ChanelConfigArr[85];	// max 84	: 1..84 : value 1-23
int CPlan::Check_ChanelSelectArr() { // return 0->OK; 1 -> ERR
	TESTCASE_CONFIG* _pTestCaseConfig;
	_pTestCaseConfig = &mTestCase.mTestCaseConfig;
	byte ChanelSelectArrTmp[85];
	int _chanelTmp = _pTestCaseConfig->nChanels;
	int _nPinTmp = _pTestCaseConfig->nPins;
	int _valueTmp;
	for (int i = 1; i <= _chanelTmp; i++) ChanelSelectArrTmp[i] = 0;
	for (int i = 1; i <= _nPinTmp; i++) {
		_valueTmp = _pTestCaseConfig->mPinsConf[i].iChanel;
		if ((_valueTmp > 0)&&(_valueTmp<=_chanelTmp)) {
			ChanelSelectArrTmp[_valueTmp] = 1;
		}
	}
	for (int i = 1; i <= _chanelTmp; i++)
		if (ChanelSelectArrTmp[i] != _pTestCaseConfig->ChanelSelectArr[i]) 
			return 1;
	return 0;
}
//---------------------------------
int CPlan::Check_ChanelConfigArr() { // return 0->OK; 1 -> ERR
	TESTCASE_CONFIG* _pTestCaseConfig;
	_pTestCaseConfig = &mTestCase.mTestCaseConfig;

	int n_ThuocTinh = 13; //DUKKK
	int _chanelTmp = _pTestCaseConfig->nChanels;
	for (int i = 1; i <= _chanelTmp; i++) {
		if (_pTestCaseConfig->ChanelSelectArr[i] + _pTestCaseConfig->ChanelGridConfigArr[i] != 0) {
			if (_pTestCaseConfig->ChanelSelectArr[i] == 0)	return 1;
			if ((_pTestCaseConfig->ChanelGridConfigArr[i] > n_ThuocTinh) || (_pTestCaseConfig->ChanelGridConfigArr[i] < 0)) return 1;
		}
		if (_pTestCaseConfig->ChanelPUPConfigArr[i] == 1 && _pTestCaseConfig->ChanelConfigArr[i] != 10) return 1;
	}
	return 0;
}
//===============================================================================
//Fix nJack, nPin, nJacRow when EDIT
int CPlan::Fix_nJack_nPin_nJacRow() {  // return 0->OK, !0-> ERR
	int Err = 0;
	JACK_INFO _JackInfo;
	JACK_ROW_DEF _JackRow;
	JACK_DEF _Jack;
	std::vector<JACK_DEF> _JACKS;
	
	int n_Jack;
	int n_Jack_Row;
	int nPinSum = 0;
	_JackInfo = mTestCase.mJackInfo;
	_JACKS = _JackInfo.mJACKS;
	
	n_Jack = _JACKS.size();
	if (n_Jack != _JackInfo.nJacks) {
		Err ++;
		_JackInfo.nJacks = n_Jack;
	}

	for (int i = 0; i < n_Jack; i++) {
		_Jack = _JACKS.at(i);
		n_Jack_Row = _Jack.mJACK_ROW.size();
		if (n_Jack_Row != _Jack.nJackRows) {
			Err++;
			_Jack.nJackRows = n_Jack_Row;
			_JACKS.at(i) = _Jack;
		}
		for (int j = 0; j < n_Jack_Row; j++) {
			_JackRow = _Jack.mJACK_ROW.at(j);
			nPinSum += _JackRow.Pins;
		}
	}
	_JackInfo.mJACKS = _JACKS;
	mTestCase.mJackInfo = _JackInfo;
	if (mTestCase.mTestCaseConfig.nPins != nPinSum) {
		Err++;
		mTestCase.mTestCaseConfig.nPins = nPinSum;
	}
	return 0;
}
//===============================================================================
int CPlan::SaveTestCase(CIniReader* m_pIniReader, int comment)
{
	Save_Define_TestCase(m_pIniReader, comment);
	Save_PathInfo_TestCase(m_pIniReader, comment);
	Save_JackInfo_TestCase(m_pIniReader, comment);
	Save_8PowerParam_TestCase(m_pIniReader, comment);
	Save_TestCaseConfig(m_pIniReader, comment);
	Save_EXTChanel_TestCase(m_pIniReader, comment);
	Save_MODE_TestCase(m_pIniReader, comment);
	Save_SUPPLY_TestCase(m_pIniReader, comment);
	return 1;
}
//===============================================================================
int CPlan::Save_Define_TestCase(CIniReader* m_pIniReader, int comment)
{
	CString strSection;
	CString strValue, strValue1, strKey, strKey1;
	if (m_pIniReader == NULL) return -1;
	//---------------------------------------
	strSection = _T("DEFINE");
	m_pIniReader->removeSection(strSection);

	strKey = _T("POWER_P1");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.POWER_P1);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("POWER_P2");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.POWER_P2);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("POWER_P3");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.POWER_P3);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("POWER_P4");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.POWER_P4);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("POWER_P5");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.POWER_P5);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("POWER_N6");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.POWER_N6);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("POWER_N7");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.POWER_N7);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("POWER_N8");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.POWER_N8);
	m_pIniReader->setKey(strValue, strKey, strSection);

	//-------------------
	if(comment)	
		m_pIniReader->setKey(_T("-"), _T("1-"), strSection);
	//-------------------

	strKey = _T("GND");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.GND);
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("LOGIC_IN");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.LOGIC_IN);
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("LOGIC_OUT");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.LOGIC_OUT);
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("CLOCK_OUT");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.CLOCK_OUT);
	m_pIniReader->setKey(strValue, strKey, strSection);
	//-------------------
	if (comment)
		m_pIniReader->setKey(_T("-"), _T("2-"), strSection);

	strKey = _T("ADC1");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.ADC1);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("ADC2");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.ADC2);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("DAC1");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.DAC1);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("DAC2");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.DAC2);
	m_pIniReader->setKey(strValue, strKey, strSection);

	//-------------------
	if (comment)
		m_pIniReader->setKey(_T("-"), _T("3-"), strSection);
	strKey = _T("HIVOLTAGE_IN1");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.HIVOLTAGE_IN1);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("HIVOLTAGE_IN2");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.HIVOLTAGE_IN2);
	m_pIniReader->setKey(strValue, strKey, strSection);


	//-------------------
	if (comment)
		m_pIniReader->setKey(_T("-"), _T("4-"), strSection);

	strKey = _T("HIVOLTAGE_OUT1");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.HIVOLTAGE_OUT1);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("HIVOLTAGE_OUT2");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.HIVOLTAGE_OUT2);
	m_pIniReader->setKey(strValue, strKey, strSection);


	//-------------------
	if (comment)
		m_pIniReader->setKey(_T("-"), _T("5-"), strSection);
	strKey = _T("EX_IN1");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.EX_IN1);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("EX_OUT1");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.EX_OUT1);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("EX_IN2");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.EX_IN2);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("EX_OUT2");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.EX_OUT2);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("SYS_1");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.SYS_1);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("SYS_2");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.SYS_2);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("LOGIC_IN_PUP");
	strValue.Format(_T("%d"), mTestCase.mConfigDef.LOGIC_IN_PUP);
	m_pIniReader->setKey(strValue, strKey, strSection);
	//-------------------
	if (comment)
		m_pIniReader->setKey(_T("-"), _T("61--------------------"), strSection);
	return 1;
}
//===============================================================================
int CPlan::Save_PathInfo_TestCase(CIniReader* m_pIniReader, int comment)
{
	return 1;
	CString strSection;
	CString strValue, strValue1, strKey, strKey1;
	if (m_pIniReader == NULL) return -1;

	strSection = _T("PATHINFO");
	m_pIniReader->removeSection(strSection);
	strKey = _T("DevicePath");
	strValue = mTestCase.mPathInfo.DevicePath;
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("FullPath");
	strValue = mTestCase.mPathInfo.FullPath;
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("DeviceName");
	strValue = mTestCase.mPathInfo.DeviceName;
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("BoardName");
	strValue = mTestCase.mPathInfo.BoardName;
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("DevicePicName");
	strValue = mTestCase.mPathInfo.DevicePicName;
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("BoardPicName");
	strValue = mTestCase.mPathInfo.BoardPicName;
	m_pIniReader->setKey(strValue, strKey, strSection);

	return 1;
}
//-----------------------------------------------
int CPlan::Save_JackInfo_TestCase(CIniReader* m_pIniReader, int comment){
	CString strSection;
	CString strValue, strValue1, strKey, strKey1;
	if (m_pIniReader == NULL) return -1;
	//-------------------
	JACK_ROW_DEF _JackRow;
	JACK_DEF _Jack;
	std::vector<JACK_DEF> _JACKS;
	int _nJacks, _nRows, _nPins;
	int sPlit0, sPlit1;
	CString Strtmp;
	//--------------------------------------
	strSection = _T("JACKSINFO");
	m_pIniReader->removeSection(strSection);

	strKey = _T("ID_Jack");
	strValue.Format(_T("%d"), mTestCase.mID_Jack);
	m_pIniReader->setKey(strValue, strKey, strSection);

	_JACKS = mTestCase.mJackInfo.mJACKS;
	_nJacks = _JACKS.size();
	strKey = _T("NumItems");
	strValue.Format(_T("%d"), _nJacks);
	m_pIniReader->setKey(strValue, strKey, strSection);

	for (int i = 0; i < _nJacks; i++) {
		strKey.Format(_T("Item_%d"), i);
		_Jack = _JACKS.at(i);
		strValue = _Jack.JackSign + _T(";") + _Jack.JackName;
		_nRows = _Jack.nJackRows;
		Strtmp.Format(_T("; %d; "), _nRows);
		strValue = strValue + Strtmp;
		for (int j = 0; j < _nRows; j++)
		{
			_JackRow = _Jack.mJACK_ROW.at(j);
			_nPins = _JackRow.Pins;
			Strtmp.Format(_T(" %d;"), _nPins);
			strValue = strValue + Strtmp;
		}
		m_pIniReader->setKey(strValue, strKey, strSection);
	}

	//-------------------
	if (comment)
		m_pIniReader->setKey(_T("-"), _T("6--------------------"), strSection);
	return 1;
}
//===============================================================================
int CPlan::Save_TestCaseConfig(CIniReader* m_pIniReader, int comment)
{
	CString strSection;
	CString strValue, strValue1, strKey, strKey1;
	if (m_pIniReader == NULL) return -1;

	strSection = _T("TESTCASECONFIG");
	m_pIniReader->removeSection(strSection);
	TESTCASE_CONFIG* _pTestCaseConfig;
	_pTestCaseConfig = &(mTestCase.mTestCaseConfig);

	strKey = _T("nChanel");
	strValue.Format(_T("%d;	// max = 84"), _pTestCaseConfig->nChanels);
	m_pIniReader->setKey(strValue, strKey, strSection);

	//-------------------
	if (comment)
	m_pIniReader->setKey(_T("-"), _T("7-"), strSection);

	CString tmp;
	//====================================
	int _ni = 1;
	int _nArr = 1;
	while (_nArr * 10 < _pTestCaseConfig->nPins) {
		strValue = _T("");
		strKey.Format(_T("MapPinArr%d"), _nArr);
		for (int i = (_nArr - 1) * 10 + 1; i <= _nArr * 10; i++)
		{
			tmp.Format(_T("%d;"), mTestCase.mTestCaseConfig.mPinsConf[_ni].iChanel);
			strValue = strValue + tmp;
			_ni++;
		}
		m_pIniReader->setKey(strValue, strKey, strSection);
		_nArr++;
	}
	strKey.Format(_T("MapPinArr%d"), _nArr);
	strValue = _T("");
	for (int i = (_nArr - 1) * 10 + 1; i <= _pTestCaseConfig->nPins; i++)
	{
		tmp.Format(_T("%d;"), mTestCase.mTestCaseConfig.mPinsConf[_ni].iChanel);
		strValue = strValue + tmp;
		_ni++;
	}
	m_pIniReader->setKey(strValue, strKey, strSection);
	
	//-------------------
	if (comment)
		m_pIniReader->setKey(_T("-"), _T("71-"), strSection);
	//====================================
	_ni = 1;
	_nArr = 1;
	while (_nArr * 10 < _pTestCaseConfig->nPins) {
		strValue = _T("");
		strKey.Format(_T("PinNameArr%d"), _nArr);
		for (int i = (_nArr - 1) * 10 + 1; i <= _nArr * 10; i++)
		{
			tmp.Format(_T("%s;"), mTestCase.mTestCaseConfig.mPinsConf[_ni].mPinName);
			strValue = strValue + tmp;
			_ni++;
		}
		m_pIniReader->setKey(strValue, strKey, strSection);
		_nArr++;
	}
	strKey.Format(_T("PinNameArr%d"), _nArr);
	strValue = _T("");
	for (int i = (_nArr - 1) * 10 + 1; i <= _pTestCaseConfig->nPins; i++)
	{
		tmp.Format(_T("%s;"), mTestCase.mTestCaseConfig.mPinsConf[_ni].mPinName); 
		strValue = strValue + tmp;
		_ni++;
	}
	m_pIniReader->setKey(strValue, strKey, strSection);
	//-------------------------------------------
	if (comment)
		m_pIniReader->setKey(_T("-"), _T("8-"), strSection);

	_ni = 1;
	_nArr = 1;
	while (_nArr * 10 < _pTestCaseConfig->nChanels) {
		strValue = _T("");
		strKey.Format(_T("ChanelSelectArr%d"), _nArr);
		for (int i = (_nArr - 1) * 10 + 1; i <= _nArr * 10; i++)
		{
			tmp.Format(_T("%d;"), mTestCase.mTestCaseConfig.ChanelSelectArr[_ni]);
			strValue = strValue + tmp;
			_ni++;
		}
		m_pIniReader->setKey(strValue, strKey, strSection);
		_nArr++;
	}
	strKey.Format(_T("ChanelSelectArr%d"), _nArr);
	strValue = _T("");
	for (int i = (_nArr - 1) * 10 + 1; i <= _pTestCaseConfig->nChanels; i++)
	{
		tmp.Format(_T("%d;"), mTestCase.mTestCaseConfig.ChanelSelectArr[i]);
		strValue = strValue + tmp;
	}
	m_pIniReader->setKey(strValue, strKey, strSection);

	//-------------------------------------------
	if (comment){
		m_pIniReader->setKey(_T("-"), _T("9-"), strSection);

		strKey1 = _T("Comment____3");
		m_pIniReader->setKey(_T("       ...	[1-12] ...."), strKey1, strSection);

		strKey1 = _T("Comment_----__21");
		m_pIniReader->setKey(strValue1, strKey1, strSection);
	}
	//-------------------------------------
	_ni = 1;
	_nArr = 1;
	while (_nArr * 10 < _pTestCaseConfig->nChanels) {
		strValue = _T("");
		strKey.Format(_T("ChanelConfigArr%d"), _nArr);
		for (int i = (_nArr - 1) * 10 + 1; i <= _nArr * 10; i++)
		{
			tmp.Format(_T("%d;"), mTestCase.mTestCaseConfig.ChanelConfigArr[_ni]);
			strValue = strValue + tmp;
			_ni++;
		}
		m_pIniReader->setKey(strValue, strKey, strSection);
		_nArr++;
	}
	strKey.Format(_T("ChanelConfigArr%d"), _nArr);
	strValue = _T("");
	for (int i = (_nArr - 1) * 10 + 1; i <= _pTestCaseConfig->nChanels; i++)
	{
		tmp.Format(_T("%d;"), mTestCase.mTestCaseConfig.ChanelConfigArr[i]);
		strValue = strValue + tmp;
	}
	m_pIniReader->setKey(strValue, strKey, strSection);

	//-------------------------------------------
	_ni = 1;
	_nArr = 1;
	while (_nArr * 10 < _pTestCaseConfig->nChanels) {
		strValue = _T("");
		strKey.Format(_T("ChanelPUPConfigArr%d"), _nArr);
		for (int i = (_nArr - 1) * 10 + 1; i <= _nArr * 10; i++)
		{
			tmp.Format(_T("%d;"), mTestCase.mTestCaseConfig.ChanelPUPConfigArr[_ni]);
			strValue = strValue + tmp;
			_ni++;
		}
		m_pIniReader->setKey(strValue, strKey, strSection);
		_nArr++;
	}
	strKey.Format(_T("ChanelPUPConfigArr%d"), _nArr);
	strValue = _T("");
	for (int i = (_nArr - 1) * 10 + 1; i <= _pTestCaseConfig->nChanels; i++)
	{
		tmp.Format(_T("%d;"), mTestCase.mTestCaseConfig.ChanelPUPConfigArr[i]);
		strValue = strValue + tmp;
	}
	m_pIniReader->setKey(strValue, strKey, strSection);

	//-------------------------------------------
	if (comment) 
		m_pIniReader->setKey(_T("-"), _T("10-------------------"), strSection);
	return 1;
}
//===============================================================================
int CPlan::Save_8PowerParam_TestCase(CIniReader* m_pIniReader, int comment)
{
	CString strSection;
	CString strValue, strValue1, strKey, strKey1;
	if (m_pIniReader == NULL) return -1;

	strSection = _T("CONFIG_8_POWERS");
	m_pIniReader->removeSection(strSection);

	//strKey = _T("PowerVerifyThreshol");
	//strValue.Format(_T("%f"), mTestCase.mPowers.PowerVerifyThreshol);
	//m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("Comment4");
	strValue = _T("        ON_OFF    	USet(V);    	ImaxSet(A);	       UGet ? ;	     IGet ?");
	m_pIniReader->setKey(strValue, strKey, strSection);

	for (int i = 1; i <= 8; i++) {
		strKey.Format(_T("POWER_P%d"), i);
		strValue.Format(_T("%5d;%15.6f;%15.6f;%15.6f;%15.6f;"),
			mTestCase.mPowers.POWER[i].ON_OFF,
			mTestCase.mPowers.POWER[i].USet,
			mTestCase.mPowers.POWER[i].ImaxSet,
			mTestCase.mPowers.POWER[i].UGet,
			mTestCase.mPowers.POWER[i].IGet);
		m_pIniReader->setKey(strValue, strKey, strSection);
	}
	return 1;
}
//-----------------------------------------------------------------
int CPlan::Save_EXTChanel_TestCase(CIniReader* m_pIniReader, int comment){
	CString strSection;
	CString strValue, strValue1, strKey, strKey1;
	if (m_pIniReader == NULL) return -1;
	//----------------------------

	EXTCHANELINFO_DEF* m_pExtChanel_Set;
	m_pExtChanel_Set = &mTestCase.ExtChanel_Set;
	HIVOLTAGE_OUT* m_pHV_out1, * m_pHV_out2;
	HIVOLTAGE_IN* m_pHV_in1, * m_pHV_in2;

	EXT_IO * m_pEXT_io1, * m_pEXT_io2;

	ADC_DAC_STRUCT* m_pADC_in1, * m_pADC_in2;
	ADC_DAC_STRUCT* m_pDAC_out1, * m_pDAC_out2;

	m_pHV_out1 = &(m_pExtChanel_Set->HV_out1);
	m_pHV_out2 = &(m_pExtChanel_Set->HV_out2);
	m_pHV_in1 = &(m_pExtChanel_Set->HV_in1);
	m_pHV_in2 = &(m_pExtChanel_Set->HV_in2);
	m_pEXT_io1 = &(m_pExtChanel_Set->EXT_io1);
	m_pEXT_io2 = &(m_pExtChanel_Set->EXT_io2);
	m_pADC_in1 = &(m_pExtChanel_Set->ADC_in1);
	m_pADC_in2 = &(m_pExtChanel_Set->ADC_in2);
	m_pDAC_out1 = &(m_pExtChanel_Set->DAC_out1);
	m_pDAC_out2 = &(m_pExtChanel_Set->DAC_out2);
	//---------------------------------------
	strSection = _T("EXTCHANEL");
	m_pIniReader->removeSection(strSection);

	if (comment) {
		m_pIniReader->setKey(_T("V_Compare"), _T("Comment5"), strSection);
	}

	strKey = _T("SignParaVerifyThreshol");
	strValue.Format(_T("%f"), m_pExtChanel_Set->SignParaVerifyThreshol);
	m_pIniReader->setKey(strValue, strKey, strSection);
	//----------------------------
	
	strKey = _T("SetMode");
	strValue.Format(_T("%d"), m_pExtChanel_Set->SetMode);
	m_pIniReader->setKey(strValue, strKey, strSection);
	//------------------------------
	if (comment) {
		m_pIniReader->setKey(_T("-"), _T("15-"), strSection);
		m_pIniReader->setKey(_T("Value[0.0, .., 80.0]"), _T("Comment9"), strSection);
	}

	strKey = _T("HV_out1");
	strValue.Format(_T("%d;%f;%s;"), m_pHV_out1->used, m_pHV_out1->value, m_pHV_out1->name);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("HV_out2");
	strValue.Format(_T("%d;%f;%s;"), m_pHV_out2->used, m_pHV_out2->value, m_pHV_out2->name);
	m_pIniReader->setKey(strValue, strKey, strSection);
	//----------------------------
	if (comment) {
		m_pIniReader->setKey(_T("-"), _T("16-"), strSection);
		m_pIniReader->setKey(_T("U_scale: value-> 1, 10, 100, 1000 (1 trong 4 gt)"), _T("Comment10"), strSection);
	}

	strKey = _T("HV_in1");
	strValue.Format(_T("%d;%f;%s;%d;"), m_pHV_in1->used, m_pHV_in1->value, m_pHV_in1->name, m_pHV_in1->nChanel);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("HV_in2");
	strValue.Format(_T("%d;%f;%s;%d;"), m_pHV_in2->used, m_pHV_in2->value, m_pHV_in2->name, m_pHV_in2->nChanel);
	m_pIniReader->setKey(strValue, strKey, strSection);

	//----------------------------------------
	strKey = _T("EXT_io1");
	strValue.Format(_T("%d;%s;%s;%d;"), m_pEXT_io1->used, m_pEXT_io1->name, m_pEXT_io1->text, m_pEXT_io1->IN_OUT);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("EXT_io2");
	strValue.Format(_T("%d;%s;%s;%d;"), m_pEXT_io2->used, m_pEXT_io2->name, m_pEXT_io2->text, m_pEXT_io2->IN_OUT);
	m_pIniReader->setKey(strValue, strKey, strSection);

	//----------------------------------------
	if (comment) {
		m_pIniReader->setKey(_T("-"), _T("13-"), strSection);
		m_pIniReader->setKey(_T("U_scale: value-> 1, 10, 100, 1000 (1 trong 4 gt)"), _T("Comment7"), strSection);
	}

	strKey = _T("ADC_in1");
	strValue.Format(_T("%d;%s;%f;%d;"), m_pADC_in1->used, m_pADC_in1->name, m_pADC_in1->value, m_pADC_in1->nChanel);
	m_pIniReader->setKey(strValue, strKey, strSection);
	strKey = _T("ADC_in2");
	strValue.Format(_T("%d;%s;%f;%d;"), m_pADC_in2->used, m_pADC_in2->name, m_pADC_in2->value, m_pADC_in2->nChanel);
	m_pIniReader->setKey(strValue, strKey, strSection);

	//----------------------------
	if (comment) {
		m_pIniReader->setKey(_T("-"), _T("14-"), strSection);
		m_pIniReader->setKey(_T("V_offset : value->[0.0, .., 2.0]"), _T("Comment8"), strSection);
	}

	strKey = _T("DAC_out1");
	strValue.Format(_T("%d;%s;%f;%d;"), m_pDAC_out1->used, m_pDAC_out1->name, m_pDAC_out1->value, m_pDAC_out1->nChanel);
	m_pIniReader->setKey(strValue, strKey, strSection);

	//----------------------------
	strKey = _T("DAC_out2");
	strValue.Format(_T("%d;%s;%f;%d;"), m_pDAC_out2->used, m_pDAC_out2->name, m_pDAC_out2->value, m_pDAC_out2->nChanel);
	m_pIniReader->setKey(strValue, strKey, strSection);

	//----------------------------
	strKey = _T("LOGIC_IN_V_COMPARE");
	strValue.Format(_T("%f;%s;"), m_pExtChanel_Set->LogicInComp.value, m_pExtChanel_Set->LogicInComp.name);
	m_pIniReader->setKey(strValue, strKey, strSection);

	if (comment) {
		m_pIniReader->setKey(_T("-"), _T("12-"), strSection);
		m_pIniReader->setKey(_T("V_Hi_Logic Volt(Logic 1->Muc cao)"), _T("Comment6"), strSection);
	}

	strKey = _T("LOGIC_OUT_V_HI");
	strValue.Format(_T("%f;%s;"), m_pExtChanel_Set->LogicOutHi.value, m_pExtChanel_Set->LogicOutHi.name);
	m_pIniReader->setKey(strValue, strKey, strSection);

	//----------------------------
	if (comment) {
		m_pIniReader->setKey(_T("-"), _T("181-"), strSection);
		m_pIniReader->setKey(_T("-"), _T("191-------------------"), strSection);
	}
	return 1;
}
//-------------------------------------------------------
int CPlan::Save_MODE_TestCase(CIniReader * m_pIniReader, int comment) {
	CString strSection;
	CString strValue, strValue1, strKey, strKey1;
	if (m_pIniReader == NULL) return -1;
	//----------------------------
	strSection = _T("MODE");
	m_pIniReader->removeSection(strSection);

	//----------------------------
	if (comment)
		m_pIniReader->setKey(_T("value: 0->internal; 1->external"), _T("Comment112"), strSection);

	strKey = _T("SYNC_MODE");
	strValue.Format(_T("%f"), mTestCase.mMode.SYNC_MODE);
	m_pIniReader->setKey(strValue, strKey, strSection);

	//----------------------------
	if (comment)
		m_pIniReader->setKey(_T("value: 0..30 x 10^6 (Tan so mau: Hz)"), _T("Comment111"), strSection);

	strKey = _T("F_SAMPLE");
	strValue.Format(_T("%f"), mTestCase.mMode.F_SAMPLE);
	m_pIniReader->setKey(strValue, strKey, strSection);

	//----------------------------
	if (comment) {
		m_pIniReader->setKey(_T("-"), _T("18-"), strSection);
		m_pIniReader->setKey(_T("-"), _T("19-------------------"), strSection);
	}
	//------------------------
	return 1;
}
//--------------------------------------------------------
int CPlan::Save_SUPPLY_TestCase(CIniReader* m_pIniReader, int comment){
	CString strSection;
	CString strValue, strValue1, strKey, strKey1;
	if (m_pIniReader == NULL) return -1;
	//----------------------------
	strSection = _T("SUPPLY");
	m_pIniReader->removeSection(strSection);

	//----------------------------
	if (comment) {
		m_pIniReader->setKey(_T("Nguon cap khong dam bao / khi hoat dong nguon chap, tang do ngot"), _T("Comment12"), strSection);
		m_pIniReader->setKey(_T("Han che nguoi dung thiet lap, phai co tinh nang cho admin"), _T("Comment13"), strSection);
		m_pIniReader->setKey(_T("nguong max  // Imax_12v_N (Negative) -> Dong cho nguon am"), _T("Comment14"), strSection);
		m_pIniReader->setKey(_T("Dong cho nguon"), _T("Comment15"), strSection);
		m_pIniReader->setKey(_T("Voltage"), _T("Comment16"), strSection);
	}
	//---------------------
	//strKey = _T("PowerSafeVerifyThreshol");
	//strValue.Format(_T("%f"), mTestCase.mSupply_Set.PowerSafeVerifyThreshol);
	//m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("Imax_3v3");
	strValue.Format(_T("%f"), mTestCase.mSupply_Set.Imax_3v3);
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("Imax_5v");
	strValue.Format(_T("%f"), mTestCase.mSupply_Set.Imax_5v);
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("Imax_12v");
	strValue.Format(_T("%f"), mTestCase.mSupply_Set.Imax_12v);
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("Imax_12v_N");
	strValue.Format(_T("%f"), mTestCase.mSupply_Set.Imax_12v_N);
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("Imax_12v_CPU");
	strValue.Format(_T("%f"), mTestCase.mSupply_Set.Imax_12v_CPU);
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("Imax_12v_ROLE");
	strValue.Format(_T("%f"), mTestCase.mSupply_Set.Imax_12v_ROLE);
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("Imax_30v");
	strValue.Format(_T("%f"), mTestCase.mSupply_Set.Imax_30v);
	m_pIniReader->setKey(strValue, strKey, strSection);

	//----------------------------
	if (comment) {
		m_pIniReader->setKey(_T("-"), _T("20-"), strSection);
		m_pIniReader->setKey(_T("Nguong dien ap hoat dong xoay quanh 12v"), _T("Comment17"), strSection);
	}

	strKey = _T("U12v_UP");
	strValue.Format(_T("%f"), mTestCase.mSupply_Set.U12v_UP);
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("U12v_DOWN");
	strValue.Format(_T("%f"), mTestCase.mSupply_Set.U12v_DOWN);
	m_pIniReader->setKey(strValue, strKey, strSection);

	//----------------------------
	if (comment) {
		m_pIniReader->setKey(_T("-"), _T("21-"), strSection);
		m_pIniReader->setKey(_T("Nguong dien ap hoat dong xoay quanh 30v"), _T("Comment18"), strSection);
	}

	strKey = _T("U30v_UP");
	strValue.Format(_T("%f"), mTestCase.mSupply_Set.U30v_UP);
	m_pIniReader->setKey(strValue, strKey, strSection);

	strKey = _T("U30v_DOWN");
	strValue.Format(_T("%f"), mTestCase.mSupply_Set.U30v_DOWN);
	m_pIniReader->setKey(strValue, strKey, strSection);

	return 1;
}
//----------------------------
int CPlan::CheckEditTestCaseChanged() {
	//DUKKKKK
	return 0;
}

void CPlan::InitMFCPath() {
	//DUKKK 
	PATHINFO_DEF * _pPathInfo;
	
	_pPathInfo = &mTestCase.mPathInfo;
	CString strTmp = _pPathInfo->FullPath;

	int sPlit[51] = { 0 };
	int n = 0, index;
	bool flag = true;
	sPlit[0] = 0;
	while (n < 50 && flag) {
		index = strTmp.Find(_T("\\"), sPlit[n] + 2);
		if (index > 0) {
			n++;
			sPlit[n] = index;
		}
		else flag = false;
	}
	if (n >= 5) {
		_pPathInfo->mloadInfor = 1;

		_pPathInfo->RootPath = strTmp.Mid(sPlit[0], sPlit[n - 4]);
		_pPathInfo->DeviceID = strTmp.Mid(sPlit[n - 4] + 1, sPlit[n - 3] - sPlit[n - 4] - 1);
		_pPathInfo->BoardID = strTmp.Mid(sPlit[n - 3] + 1, sPlit[n - 2] - sPlit[n - 3] - 1);
		_pPathInfo->TestID = strTmp.Mid(sPlit[n - 2] + 1, sPlit[n - 1] - sPlit[n - 2] - 1);
	}
	//--- fix  -------------
	_pPathInfo->DevicePicName = _pPathInfo->DeviceID + _T(".jpg");   //"Kacta-2E2.jpg"

	// load tư excel -----------------
	_pPathInfo->DeviceName = _pPathInfo->DeviceID; // _T("ĐÀI RA-ĐA KACTA-2E2");   // Dọc từ Excel
	_pPathInfo->BoardName = _pPathInfo->BoardID;// _T("Điều khiển B2AП78");		// Dọc từ Excel
	_pPathInfo->TestName = _pPathInfo->TestID;// _T("Kiểm tra nguồn");
	//---- tự tính -----------------------------
	_pPathInfo->DevicePath = _pPathInfo->RootPath;
	_pPathInfo->DevicePicPath = _pPathInfo->DevicePath + _T("\\Radar_Fig");

	_pPathInfo->BoardPath = _pPathInfo->DevicePath + _T("\\") + _pPathInfo->DeviceID + _T("\\") + _pPathInfo->BoardID;
	_pPathInfo->TestPicPath = _pPathInfo->BoardPath + _T("\\") + _pPathInfo->TestID;
	_pPathInfo->TestPath = strTmp.Mid(sPlit[0], sPlit[n]);

}
void CPlan::InitJavaPath(CString mPath) {
	//DUKKK 
	PATHINFO_DEF* _pPathInfo;

	//CString FullPath = mTestCase.mPathInfo.FullPath;// _T("D:\\CSDL\\daixyz\\Boardxyz\\BaiKT_So2\\CosoduLieu\\Config.dat");
	//mPath = _T("D:/CSDL_20230705/Kolchuga/CДA/BaiKT_So3/BaiKT.xlsx");
	_pPathInfo = &mTestCase.mPathInfo;

	CString tmpStr = _T("");
	for (int i = 0; i <= mPath.GetLength(); i++) {
		if (mPath[i] == '/') tmpStr += _T("\\");
		else tmpStr += mPath[i];
	}

	//m_pCPlan->mTestCase.mPathInfo.FullPath = tmpStr;

	//_pPathInfo->FullPath;

	int sPlit[10] = { 0 };
	int n = 0, index;
	bool flag = true;
	sPlit[0] = 0;
	while (n < 10 && flag) {
		index = tmpStr.Find(_T("\\"), sPlit[n] + 2);
		if (index > 0) {
			n++;
			sPlit[n] = index;
		}
		else flag = false;
	}
	CString tmpStr1;
	if (n >= 4) {
		tmpStr1 = tmpStr.Mid(sPlit[0], sPlit[n]);
	}
	tmpStr1 = tmpStr1 + _T("\\") + _pPathInfo->datanamefolder + _T("\\Config.cfg");
	_pPathInfo->FullPath = tmpStr1;
}

float CPlan::getSupplyValue(int k) {
	POWERS_STRUCT* _pPowers;
	EXTCHANELINFO_DEF* _pExtChanel;
	_pPowers = &(mTestCase.mPowers);
	_pExtChanel = &(mTestCase.ExtChanel_Set);
	float value;

	if (k > 0 && k <= 8) {
		if (!_pPowers->POWER[k].ON_OFF) value = 0;
		value = _pPowers->POWER[k].USet;
	}
	
	switch (k) {
	case 0: value = 0;
		break;
	case 9:value = 0;
		break;
	case 10:
		value = _pExtChanel->LogicInComp.value;
		break;
	case 11:
		value = _pExtChanel->LogicOutHi.value;
		break;
	case 12:  
		value = _pExtChanel->LogicOutHi.value;
		break;
	}
	return value;
}

int CPlan::InitChanelDataConf() {
	TESTCASE_CONFIG* _pTestCaseConfig;
	EXTCHANELINFO_DEF* _pExtChanel;
	_pExtChanel = &(mTestCase.ExtChanel_Set);
	_pTestCaseConfig = &(mTestCase.mTestCaseConfig);

	int iPin, nPins;
	int iChanel, nChanels;
	//reset
	nPins = _pTestCaseConfig->nPins;
	nChanels = _pTestCaseConfig->nChanels;
	
	//reset
	for (int i = 1; i <= 88; i++) {
		_pTestCaseConfig->mChanelsConf[i].iPin = 0;
		_pTestCaseConfig->mChanelsConf[i].Attri = 0;

		_pTestCaseConfig->mChanelsDataConf[i].iPinName = _T("");
		_pTestCaseConfig->mChanelsDataConf[i].iPinSign = _T("");
		_pTestCaseConfig->mChanelsDataConf[i].Attri = 0;
		_pTestCaseConfig->mChanelsDataConf[i].value = 0;
	}
	CString strr1;
	for (iPin = 1; iPin <= nPins; iPin++) {
		iChanel = _pTestCaseConfig->mPinsConf[iPin].iChanel;
		strr1.Format(_T("%d"), iChanel);
				
		_pTestCaseConfig->mChanelsConf[iChanel].iPin = iPin;
		_pTestCaseConfig->mChanelsConf[iChanel].Attri = _pTestCaseConfig->ChanelConfigArr[iChanel];
	}
	//----------------------------
	nChanels = 80;
	int nAttri;
	for (int i = 1; i <= nChanels; i++) {
		iPin = _pTestCaseConfig->mChanelsConf[i].iPin;
		if (iPin != 0) {
			_pTestCaseConfig->mChanelsDataConf[i].iPinSign = _pTestCaseConfig->mPinsConf[iPin].mPinSign;
			_pTestCaseConfig->mChanelsDataConf[i].iPinName = _pTestCaseConfig->mPinsConf[iPin].mPinName;
			nAttri = _pTestCaseConfig->mChanelsConf[i].Attri;
			_pTestCaseConfig->mChanelsDataConf[i].Attri = nAttri;
			_pTestCaseConfig->mChanelsDataConf[i].value = getSupplyValue(nAttri);

		}
	}
	//------------------------------
	_pTestCaseConfig->mChanelsDataConf[81].iPinSign = _T("HV_OUT_1");
	_pTestCaseConfig->mChanelsDataConf[81].iPinName = _pExtChanel->HV_out1.name;
	_pTestCaseConfig->mChanelsDataConf[81].Attri = _pExtChanel->HV_out1.used;
	_pTestCaseConfig->mChanelsDataConf[81].value = _pExtChanel->HV_out1.value;

	_pTestCaseConfig->mChanelsDataConf[82].iPinSign = _T("HV_OUT_2");
	_pTestCaseConfig->mChanelsDataConf[82].iPinName = _pExtChanel->HV_out2.name;
	_pTestCaseConfig->mChanelsDataConf[82].Attri = _pExtChanel->HV_out2.used;
	_pTestCaseConfig->mChanelsDataConf[82].value = _pExtChanel->HV_out2.value;

	//_pTestCaseConfig->mChanelsDataConf[83].iPinSign = _T("IO_EXIT_1");
	//_pTestCaseConfig->mChanelsDataConf[83].iPinName = _pExtChanel->EXT_io1.name;
	//_pTestCaseConfig->mChanelsDataConf[83].value = 5;
	//_pTestCaseConfig->mChanelsDataConf[83].Attri =  _pExtChanel->EXT_io1.used;
	_pTestCaseConfig->mChanelsDataConf[83].iPinSign = _T("HV_IN_1");
	_pTestCaseConfig->mChanelsDataConf[83].iPinName = _pExtChanel->HV_in1.name;
	_pTestCaseConfig->mChanelsDataConf[83].value = _pExtChanel->HV_in1.value;
	_pTestCaseConfig->mChanelsDataConf[83].Attri = _pExtChanel->HV_in1.used;
	

	//_pTestCaseConfig->mChanelsDataConf[84].iPinSign = _T("IO_EXIT_2");
	//_pTestCaseConfig->mChanelsDataConf[84].iPinName = _pExtChanel->EXT_io2.name;
	//_pTestCaseConfig->mChanelsDataConf[84].Attri = _pExtChanel->EXT_io2.used;
	//_pTestCaseConfig->mChanelsDataConf[84].value = 5;
	_pTestCaseConfig->mChanelsDataConf[84].iPinSign = _T("HV_IN_2");
	_pTestCaseConfig->mChanelsDataConf[84].iPinName = _pExtChanel->HV_in2.name;
	_pTestCaseConfig->mChanelsDataConf[84].value = _pExtChanel->HV_in2.value;
	_pTestCaseConfig->mChanelsDataConf[84].Attri = _pExtChanel->HV_in2.used;

	//ADC1
	_pTestCaseConfig->mChanelsDataConf[85].iPinSign.Format(_T("Kenh_%d"), _pExtChanel->ADC_in1.nChanel);
	_pTestCaseConfig->mChanelsDataConf[85].iPinName = _pExtChanel->ADC_in1.name;
	_pTestCaseConfig->mChanelsDataConf[85].Attri = _pExtChanel->ADC_in1.used;
	_pTestCaseConfig->mChanelsDataConf[85].value = _pExtChanel->ADC_in1.value;

	//ADC2
	_pTestCaseConfig->mChanelsDataConf[86].iPinSign.Format(_T("Kenh_%d"), _pExtChanel->ADC_in2.nChanel);
	_pTestCaseConfig->mChanelsDataConf[86].iPinName = _pExtChanel->ADC_in2.name;
	_pTestCaseConfig->mChanelsDataConf[86].Attri = _pExtChanel->ADC_in2.used;
	_pTestCaseConfig->mChanelsDataConf[86].value = _pExtChanel->ADC_in2.value;

	//DAC1
	_pTestCaseConfig->mChanelsDataConf[87].iPinSign.Format(_T("Kenh_%d"), _pExtChanel->DAC_out1.nChanel);
	_pTestCaseConfig->mChanelsDataConf[87].iPinName = _pExtChanel->DAC_out1.name;
	_pTestCaseConfig->mChanelsDataConf[87].Attri = _pExtChanel->DAC_out1.used;
	_pTestCaseConfig->mChanelsDataConf[87].value = _pExtChanel->DAC_out1.value;

	//DAC2
	_pTestCaseConfig->mChanelsDataConf[88].iPinSign.Format(_T("Kenh_%d"), _pExtChanel->DAC_out2.nChanel);
	_pTestCaseConfig->mChanelsDataConf[88].iPinName = _pExtChanel->DAC_out2.name;
	_pTestCaseConfig->mChanelsDataConf[88].Attri = _pExtChanel->DAC_out2.used;
	_pTestCaseConfig->mChanelsDataConf[88].value = _pExtChanel->DAC_out2.value;
	return 1;
}
CString CPlan::ChanelConfToString() {

	TESTCASE_CONFIG* _pTestCaseConfig;
	CHANELDATA_CONF* _pChanelData;
	EXTCHANELINFO_DEF* _pExtChanel;
	_pExtChanel = &(mTestCase.ExtChanel_Set);
	_pTestCaseConfig = &(mTestCase.mTestCaseConfig);

	CString str = _T(""), strtmp;

	for (int i = 1; i <= 80; i++) {
		_pChanelData = &(_pTestCaseConfig->mChanelsDataConf[i]);
		strtmp.Format(_T("sChanel_%d="), i);
		//----------------------------
		//str = str + strtmp + _pChanelData->iPinSign +_T(";")+ _pChanelData->iPinName + _T(";");
		str = str + strtmp + _pChanelData->iPinSign + _T(";");
		strtmp.Format(_T("%s"), _pChanelData->iPinName);
		str = str + strtmp  + _T(";");
		//------------------------------------
		strtmp.Format(_T("%d;"), _pChanelData->Attri);
		str = str + strtmp;
		strtmp.Format(_T("%f;"), _pChanelData->value);
		str = str + strtmp + _T("\r\n");
	}
	for (int i = 81; i <= 88; i++) {
		_pChanelData = &(_pTestCaseConfig->mChanelsDataConf[i]);
		strtmp.Format(_T("sChanel_%d="), i);
		//-------------------------
		//str = str + strtmp + _pChanelData->iPinSign + _T(";") + _pChanelData->iPinName + _T(";");
		str = str + strtmp + _pChanelData->iPinSign + _T(";");
		strtmp.Format(_T("%s"),_pChanelData->iPinName);
		str = str + strtmp + _T(";");
		//-------------------------
		switch (i) {
			case 81:
			case 82:
				if (_pChanelData->Attri == 1) strtmp = _T("ON");
				else strtmp = _T("OFF");
				break;
			case 83:
				if (_pChanelData->Attri == 0) strtmp = _T("OFF");
				else strtmp = _T("ON");
				/*{
					if (_pExtChanel->EXT_io1.IN_OUT) strtmp = _T("LOGIC_EXT_IN");
					else strtmp = _T("LOGIC_EXT_OUT");
				}*/
				break;
			case 84:
				if (_pChanelData->Attri == 0) strtmp = _T("OFF");				
				else strtmp = _T("ON");
				/*{
					if (_pExtChanel->EXT_io2.IN_OUT) strtmp = _T("LOGIC_EXT_IN");
					else strtmp = _T("LOGIC_EXT_OUT");
				}*/
				break;
			case 85:
				if (_pChanelData->Attri == 0) strtmp = _T("OFF");
				else strtmp = _T("ON");// strtmp = _T("ADC_1");
				break;
			case 86:
				if (_pChanelData->Attri == 0) strtmp = _T("OFF");
				else strtmp = _T("ON");//strtmp = _T("ADC_2");
				break;
			case 87:
				if (_pChanelData->Attri == 0) strtmp = _T("OFF");
				else strtmp = _T("ON");// strtmp = _T("DAC_1");
				break;
			case 88:
				if (_pChanelData->Attri == 0) strtmp = _T("OFF");
				else strtmp = _T("ON");// strtmp = _T("DAC_2");
				break;
		}
		str = str + strtmp;
		strtmp.Format(_T(";%f;"), _pChanelData->value);
		str = str + strtmp + _T("\r\n");
	}
	str = str + _T("ket thuc\r\n");
	return str;
}

int CPlan::ChanelConfToFileConf(CIniReader* m_pIniReader) {

	TESTCASE_CONFIG* _pTestCaseConfig;
	CHANELDATA_CONF* _pChanelData;
	EXTCHANELINFO_DEF* _pExtChanel;
	_pExtChanel = &(mTestCase.ExtChanel_Set);
	_pTestCaseConfig = &(mTestCase.mTestCaseConfig);

	CString strSection;
	CString strValue, strValue1, strKey, strKey1;
	if (m_pIniReader == NULL) return -1;
	//---------------------------------------
	strSection = _T("GUI_LOGICTEST");
	m_pIniReader->removeSection(strSection);

	CString str, strtmp;

	for (int i = 1; i <= 80; i++) {
		_pChanelData = &(_pTestCaseConfig->mChanelsDataConf[i]);
		strKey.Format(_T("sChanel_%d"), i);
		str.Format(_T("%s;%s;"),_pChanelData->iPinSign,_pChanelData->iPinName);
		strtmp.Format(_T("%d;"), _pChanelData->Attri);
		str = str + strtmp;
		strtmp.Format(_T("%f;"), _pChanelData->value);
		str = str + strtmp;
		strValue = str;
		m_pIniReader->setKey(strValue, strKey, strSection);
	}
	for (int i = 81; i <= 88; i++) {
		_pChanelData = &(_pTestCaseConfig->mChanelsDataConf[i]);
		strKey.Format(_T("sChanel_%d"), i);
		str.Format(_T("%s;%s;"),_pChanelData->iPinSign, _pChanelData->iPinName);
		switch (i) {
		case 81:
		case 82:
			if (_pChanelData->Attri == 1) strtmp = _T("ON");
			else strtmp = _T("OFF");
			break;
		case 83:
			if (_pChanelData->Attri == 0) strtmp = _T("OFF");
			else strtmp = _T("ON");
			/*{
				if (_pExtChanel->EXT_io1.IN_OUT) strtmp = _T("LOGIC_EXT_IN");
				else strtmp = _T("LOGIC_EXT_OUT");
			}*/
			break;
		case 84:
			if (_pChanelData->Attri == 0) strtmp = _T("OFF");
			else strtmp = _T("ON");
			/*{
				if (_pExtChanel->EXT_io2.IN_OUT) strtmp = _T("LOGIC_EXT_IN");
				else strtmp = _T("LOGIC_EXT_OUT");
			}*/
			break;
		case 85:
			if (_pChanelData->Attri == 0) strtmp = _T("OFF");
			else strtmp = _T("ON");// strtmp = _T("ADC_1");
			break;
		case 86:
			if (_pChanelData->Attri == 0) strtmp = _T("OFF");
			else strtmp = _T("ON");// strtmp = _T("ADC_2");
			break;
		case 87:
			if (_pChanelData->Attri == 0) strtmp = _T("OFF");
			else strtmp = _T("ON");// strtmp = _T("DAC_1");
			break;
		case 88:
			if (_pChanelData->Attri == 0) strtmp = _T("OFF");
			else strtmp = _T("ON");// strtmp = _T("DAC_2");
			break;
		}
		str = str + strtmp;
		strtmp.Format(_T(";%f;"), _pChanelData->value);
		str = str + strtmp;
		strValue = str;
		m_pIniReader->setKey(strValue, strKey, strSection);
	}
	//-------Thêm 89-128 trống dữ liệu--------
	for (int i = 89; i <= 128; i++) {
		strKey.Format(_T("sChanel_%d"), i);
		strValue = _T(";;0;0.000000;");
		m_pIniReader->setKey(strValue, strKey, strSection);
	}
	//----------------------------------------
	return 1;
}
//----------------------------------------------

int CPlan::SetFullProgress() {
	int nLower, nUpper;
	p_ProgressCtrl->GetRange(nLower, nUpper);
	p_ProgressCtrl->SetPos(nUpper);
	return 1;
}
int CPlan::ResetProgress() {
	p_ProgressCtrl->SetPos(0);
	return 1;
}
int CPlan::SetPhanTramProgress(int PhanTramValue){
	int nLower, nUpper;
	int value;
	p_ProgressCtrl->GetRange(nLower, nUpper);
	value = nLower + (int)((nUpper - nLower) * PhanTramValue / 100);
	if (value > nUpper) value = nUpper;
	if (value < nLower) value = nLower;
	p_ProgressCtrl->SetPos(value);
	return 1;
}

int CPlan::IncreateProgress(int value) {
	int nLower, nUpper;
	p_ProgressCtrl->GetRange(nLower,nUpper);
	int currentPosition = p_ProgressCtrl->GetPos();
	if (currentPosition + value <= nUpper) currentPosition += value;
	else currentPosition -= 5*value;
	if (currentPosition < nLower) currentPosition = nLower;
	p_ProgressCtrl->SetPos(currentPosition);
	return 1;
}
int CPlan::IncreateProgressInMinMax(int value, int PhanTramMin, int PhanTramMax) {
	int nLower, nUpper;
	p_ProgressCtrl->GetRange(nLower, nUpper);
	int nLower100, nUpper100;
	nLower100 = nLower + (int)((nUpper - nLower) * PhanTramMin / 100);
	nUpper100 = nLower + (int)((nUpper - nLower) * PhanTramMax / 100);
	int currentPosition = p_ProgressCtrl->GetPos();

	if (currentPosition + value <= nUpper100) currentPosition += value;
	else currentPosition -= 5 * value;
	if (currentPosition < nLower100) currentPosition = nLower100;
	p_ProgressCtrl->SetPos(currentPosition);
	return 1;
}
// ##################################################################

int CPlan::ping_network_to_1_board(byte addr_board) {
	// addr_board: dia chi cua board o khe cua main
	// return : 1: OK, 0: error

	byte num_bytes_payload = 0;  // so byte payload
	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];

	byte Buff_tx[9];
	// gui dia hci Ping tới board
	// header
	Buff_tx[0] = 0x00;		 // ADDR_TX
	Buff_tx[1] = addr_board; // ADDR_RX

	Buff_tx[2] = 0x01;		// ma lenh PING
	Buff_tx[3] = 0x00;
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01;		// Ver FW: 1.0
	Buff_tx[6] = 0x00;

	Buff_tx[7] = 0x00;		// Lenth data in payload

	// payload
	Buff_tx[8] = 0x00;     //  non
	// gui cho device: 
	int len_Tx = num_bytes_payload + 8;
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL,3000, 3);

	if (nRet < 8) return 0;
	else if (addr_board == *(m_pBuffRecv + 0)) return 1;
	else return 0;

}

int CPlan::send_active_1_board(byte addr_board) {
	// addr_board: dia chi cua board o khe cua main
	// return : 1: OK, 0: error

	byte num_bytes = 1;  // so byte payload
	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];

	byte Buff_tx[9];
	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = addr_board; // ADDR_M1_0
	Buff_tx[2] = 0x09; // xac nhan boarrd cam dung vi tri
	Buff_tx[3] = 0x0D;
	Buff_tx[4] = 0x00;
	Buff_tx[5] = 0x01; // ADDR_M1_0
	Buff_tx[6] = 0x00;
	Buff_tx[7] = 0x01;

	// payload
	num_bytes = 1;  // so byte payload
	Buff_tx[8] = 0x01;  // OK
	// gui cho device: 
	int len_Tx = num_bytes + 8;
	int nRet;
	// nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL,5000);
	nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 5000, 3);
	if (nRet == -1) return 0;

	return nRet;
}


int CPlan::send_active_All_board()  // khac 0 co  error, 0-> ok
{
	int TimeDelay = 680; //ms
	int stt;
	byte addr_board;

	//----------------------------------------
	ResetProgress();
	int i_Progress = 0;
	int n_Progress = 16;
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	addr_board = 0x10;
	stt = send_active_1_board(addr_board);
	if (stt == 0) return 1;


	Sleep(TimeDelay);
	addr_board = 0x11;
	stt = send_active_1_board(addr_board);
	if (stt == 0) return 2;
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------

		//--------------------------------------
	// turn on +30V for M9, M10
	Sleep(2000);  // delay 3s cho M9 khoi dong xong
	stt = Power_Ctrl_M1_For_DUT(P_ON, ADDR_M1_0);
	Sleep(TimeDelay);
	stt = Power_Ctrl_M1_For_DUT(P_OFF, ADDR_M1_1);

	Sleep(TimeDelay);

	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------




	Sleep(TimeDelay);
	addr_board = 0x20;
	stt = send_active_1_board(addr_board);
	if (stt == 0) return 3;
	// board 4,5 khong dung
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------

	Sleep(TimeDelay);
	addr_board = 0x23;
	stt = send_active_1_board(addr_board);
	if (stt == 0) return 6;
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------

	Sleep(TimeDelay);
	addr_board = 0x30;
	stt = send_active_1_board(addr_board);
	if (stt == 0) return 7;
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------

	Sleep(TimeDelay);
	addr_board = 0x31;
	stt = send_active_1_board(addr_board);
	if (stt == 0) return 8;
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------

	Sleep(TimeDelay);
	addr_board = 0x4A;
	stt = send_active_1_board(addr_board);
	if (stt == 0) return 9;
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------

	Sleep(TimeDelay);
	addr_board = 0x4B;
	stt = send_active_1_board(addr_board);
	if (stt == 0) return 10;
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------

	Sleep(TimeDelay);
	addr_board = 0x40;
	stt = send_active_1_board(addr_board);
	if (stt == 0) return 11;
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------

	Sleep(TimeDelay);
	addr_board = 0x50;
	stt = send_active_1_board(addr_board);
	if (stt == 0) return 12;
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------

	Sleep(TimeDelay);
	addr_board = 0x51;
	stt = send_active_1_board(addr_board);
	if (stt == 0) return 13;
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------

	Sleep(TimeDelay);
	addr_board = 0x52;
	stt = send_active_1_board(addr_board);
	if (stt == 0) return 14;
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------

	Sleep(TimeDelay);
	addr_board = 0x53;
	stt = send_active_1_board(addr_board);
	if (stt == 0) return 15;
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	//======================================================
	Sleep(2500); // 2s

	addr_board = 0x90;     // active M9
	Flag_Used_M9 = 0;  // xoa, M9 chua ket noi
	stt = send_active_1_board(addr_board);
	if (stt == 0) 
	{
		if (AfxMessageBox(_T("Kích hoạt khối M9 (Khối chuyển đổi cáp nối và khối DBP) không thành công!\n\rTiếp tục thực hiện và không sử dụng M9 ?"), MB_OKCANCEL) == IDOK) 
		{
			Flag_Used_M9 = 0; // ==> thuc hien tiep va khong su dung M9
		}
		else // Neu Cancel hoac Close: ==> thoat
		{
			Flag_Used_M9 = 0;
			return 17;
		}
	}
	else Flag_Used_M9 = 1; // M9 ket noi tot
	////--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);

	Sleep(600); // 1s
	addr_board = 0xA0;     // active M10
	Flag_Used_M10 = 0;  // xoa ve mac dinh M10 chua ket noi
	stt = send_active_1_board(addr_board);

	CString temp;
	
	//--------------------------------------
	if (stt == 0) {
		if (AfxMessageBox(_T("Kích hoạt khối M10 (DBP - Khối cắm Bo mạch) không thành công!\n\rTiếp tục thực hiện và không sử dụng M10 ?"), MB_OKCANCEL) == IDOK) 
		{
			Flag_Used_M10 = 0;  // tiep tuc thuc hien ma khong dung toi M10
		}
		else 
		{ 
			// Khi chon Cancel hoac Close ==> thoat
			Flag_Used_M10 = 0;
			return 18;
		}
	}
	else Flag_Used_M10 = 1;
	
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);

	//// bat nguon cho M9
	//Sleep(TimeDelay);
	//stt = Set_ON_Off_30V_M9(1);   //1: ON, 0FF
	//if (stt < 8) return 90;
	////--------------------------------------
	//i_Progress++;
	//SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	SetFullProgress();
	return 0; // all OK
}

//
//int CPlan::Set_Thres_I(byte ID_Nguon, float giatri_Inguong) {
//
//
//}
//int CPlan::Get_Thres_I(byte ID_Nguon, float* returned_Inguong) {
//
//
//}
//// U nguong
//int CPlan::Set_Thres_U(byte ID_Nguon, float giatri_Unguong) {
//
//
//}
//int CPlan::Get_Thres_U(byte ID_Nguon, float* returned_Unguong) {
//
//
//
//}



//thiet lap dinh tuyen
int CPlan::Reset_1_paths(byte ADDR_Board)
{
	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];
	byte num_bytes = 0;  // so byte payload
	byte Buff_tx[8];
	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; 			// ADDR_PC
	Buff_tx[1] = ADDR_Board; 	// ADDR_Mi
	Buff_tx[2] = 0x0B; 			// reset matrix
	Buff_tx[3] = 0x01;
	Buff_tx[4] = 0x00;
	Buff_tx[5] = 0x01; 			// Ver FW: 1.0
	Buff_tx[6] = 0x00;
	Buff_tx[7] = 0x00;

	// payload: khong co

	// gui cho device: 
	int len_Tx = num_bytes + 8;
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv,SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;

}


// dinh tuyen
int CPlan::Reset_All_paths(void) {
	byte addr_board;
	int stt;
	int time_delay = 1000;
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	addr_board = ADDR_M1_0;
	stt = Reset_1_paths(addr_board);
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (stt < 8) return 1;

	Sleep(time_delay);
	addr_board = ADDR_M1_1;
	stt = Reset_1_paths(addr_board);
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (stt < 8) return 2;

	Sleep(time_delay);
	addr_board = ADDR_M2PS_0;
	stt = Reset_1_paths(addr_board);
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (stt < 8) return 3;

	Sleep(time_delay);
	addr_board = ADDR_M2PS_3;
	stt = Reset_1_paths(addr_board);
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (stt < 8) return 4;

	Sleep(time_delay);
	addr_board = ADDR_M3_0;
	stt = Reset_1_paths(addr_board);
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (stt < 8) return 5;
	
	Sleep(time_delay);
	addr_board = ADDR_M3_1;
	stt = Reset_1_paths(addr_board);
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (stt < 8) return 6;

	Sleep(time_delay);
	//--------------------
	addr_board = ADDR_M2SIG_0;
	stt = Reset_1_paths(addr_board);
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (stt < 8) return 7;

	Sleep(time_delay);
	addr_board = ADDR_M2SIG_1;
	stt = Reset_1_paths(addr_board);
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (stt < 8) return 8;

	Sleep(time_delay);
	addr_board = ADDR_M4_0;
	stt = Reset_1_paths(addr_board);
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (stt < 8) return 9;

	Sleep(time_delay);
	addr_board = ADDR_M5_0;
	stt = Reset_1_paths(addr_board);
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (stt < 8) return 10;

	Sleep(time_delay);
	addr_board = ADDR_M5_1;
	stt = Reset_1_paths(addr_board);
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (stt < 8) return 11;

	Sleep(time_delay);
	addr_board = ADDR_M5_2;
	stt = Reset_1_paths(addr_board);
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (stt < 8) return 12;

	Sleep(time_delay);
	addr_board = ADDR_M5_3;
	stt = Reset_1_paths(addr_board);
	//--------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (stt < 8) return 13;

	return 0;
}


int CPlan::Reset_IO_FPGA_Default(void) {
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	int nret;
	// to all inputs
	io_mask m_IO_mask_Default;
	io_mask m_IO_CLK_mask_Default;

	// set up all ipnuts
	m_IO_mask_Default.mask[0] = 0;
	m_IO_mask_Default.mask[1] = 0;
	m_IO_mask_Default.mask[2] = 0;

	// setup no CLK_output mode
	m_IO_CLK_mask_Default.mask[0] = 0;
	m_IO_CLK_mask_Default.mask[1] = 0;
	m_IO_CLK_mask_Default.mask[2] = 0;



	// thuc hien cau hinh cho FPGA. return 0: is OK
	// setup default:
	// All input, sample_unit = 10000, clk_divisor = 1 Khz, Internal clk mode,  no clk_io_output,
	nret = io_set_config(m_IO_mask_Default, (uint32_t)199999, (uint32_t)10000, (uint32_t)0, m_IO_CLK_mask_Default);
	return nret;  // 0: OK
}





int CPlan::Set_Paths_M1_i(byte ADDR_Board) { // thiet lap board M1_0 /  M1_1
	// ADDR_Board: 0x30 hoac  0x31
	// rerturn 0: error,   1: OK

	byte m_pBuffRecv[128];
	byte num_bytes = 40;  // so byte payload
	byte Buff_tx[128];
	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; 			// ADDR_PC
	if ((ADDR_Board == ADDR_M1_0) || (ADDR_Board == ADDR_M1_1))
		Buff_tx[1] = ADDR_Board; 	// ADDR_Mi
	else return 0;   // error
	Buff_tx[2] = 0x09; 			// reset matrix
	Buff_tx[3] = 0x01;			// du lieu ma tran relays
	Buff_tx[4] = 0x00;

	Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
	Buff_tx[6] = (VERSION_FW & 0x00FF);


	num_bytes = 40;  // so byte  == so dau ra: DB50 / M1_i
	Buff_tx[7] = num_bytes;			// length of payload

	byte Thuoc_tinh_Pins[40];
	int Start_id;



	if (ADDR_Board == ADDR_M1_0)  Start_id = 1;
	else if (ADDR_Board == ADDR_M1_1)  Start_id = 41;
	for (int i = 0; i < 40; i++)	//  lay 40 pin dau tien
	{
		// dang loi o day
		if ((1 <= mTestCase.mTestCaseConfig.ChanelConfigArr[Start_id + i]) && (mTestCase.mTestCaseConfig.ChanelConfigArr[Start_id + i] <= 8))
			Thuoc_tinh_Pins[i] = 0x03;  // nguon: M1
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[Start_id + i] == 0x09)  Thuoc_tinh_Pins[i] = 0x04; // GND
		else
		{
			Thuoc_tinh_Pins[i] = 0x00; // khong thuc hien chuyen mach chon nguon. mac dinh la duong tin hieu
		}
		//printf("Thuoc_tinh_Pins[%d] =  \n\r", Thuoc_tinh_Pins[i]);
	}


	// dong payload vao khung du lieu
	for (int j = 0; j < 40; j++)
		Buff_tx[8 + j] = Thuoc_tinh_Pins[j];

	// gui cho device: 
	int len_Tx = num_bytes + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;

}

int CPlan::Set_Paths_M1(void) { // thiet lap ca 2 board M1_0 va M1_1
	int nRet;
	nRet = Set_Paths_M1_i(ADDR_M1_0);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (nRet < 8) return 1;
	Sleep(1000);
	nRet = Start_Apply_Relay(ADDR_M1_0);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (nRet < 8) return 2;
	Sleep(1000);
	nRet = Set_Paths_M1_i(ADDR_M1_1);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (nRet < 8) return 3;
	Sleep(1000);
	nRet = Start_Apply_Relay(ADDR_M1_1);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	Sleep(1000);
	if (nRet < 8) return 4;
	else return 0;
}


int CPlan::Set_Paths_M2_PS_i(byte ADDR_Board) { // thiet lap  M2_0 /  M2_3
	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];
	byte num_bytes = 40;  // so byte payload
	byte Buff_tx[SIZE_MAX_BUFF_RX_SERIAL];
	// cho phep board Active
	// header
	Buff_tx[0] = ADDR_PC; 			// ADDR_PC
	if ((ADDR_Board == ADDR_M2PS_0) || (ADDR_Board == ADDR_M2PS_3))
		Buff_tx[1] = ADDR_Board; 	// ADDR_Mi
	else return 0;   // error
	Buff_tx[2] = 0x09; 			// reset matrix
	Buff_tx[3] = 0x01;			// du lieu ma tran relays
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01; 			// Ver FW: 1.0
	Buff_tx[6] = 0x00;


	num_bytes = 40;  // so byte  == so dau ra: DB50 / M1_i
	Buff_tx[7] = num_bytes;			// length of payload


	for (int j = 0; j < 40; j++)
		if (ADDR_Board == ADDR_M2PS_0)  Buff_tx[8 + j] = Data_relay_M2PS_0[j + 1];
		else if (ADDR_Board == ADDR_M2PS_3)  Buff_tx[8 + j] = Data_relay_M2PS_3[j + 1];


	int len_Tx = num_bytes + 8;
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;

}

int CPlan::Set_Paths_M2_PS(void) { // thiet lap ca 2 board o M2_0, M2_3
	int nRet;
	nRet = Set_Paths_M2_PS_i(ADDR_M2PS_0);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (nRet < 8) return 1;
	Sleep(1000);
	nRet = Start_Apply_Relay(ADDR_M2PS_0);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (nRet < 8) return 2;


	Sleep(1000);
	nRet = Set_Paths_M2_PS_i(ADDR_M2PS_3);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (nRet < 8) return 3;
	Sleep(1000);
	nRet = Start_Apply_Relay(ADDR_M2PS_3);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (nRet < 8) return 4;
	else return 0;
}


int CPlan::Set_Paths_M5_i(byte ADDR_Board) {
	// thiet lap cho 1 khoi M5

	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];
	byte num_bytes;  // so byte payload
	byte Buff_tx[SIZE_MAX_BUFF_RX_SERIAL];
	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; 			// ADDR_PC
	if ((ADDR_Board == ADDR_M5_0) || (ADDR_Board == ADDR_M5_1) || (ADDR_Board == ADDR_M5_2) || (ADDR_Board == ADDR_M5_3))
		Buff_tx[1] = ADDR_Board; 	// ADDR_Mi
	else return 0;   // error
	Buff_tx[2] = 0x09; 			// reset matrix
	Buff_tx[3] = 0x01;			// du lieu ma tran relays
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01; 			// Ver FW: 1.0
	Buff_tx[6] = 0x00;


	num_bytes = 20;  // so byte  dinh nghia thuoc tinh cho 1 khoi M5
	Buff_tx[7] = num_bytes;			// length of payload

	byte Dir_BUS[20];    // 0: open, 1: output,  2: Input,
	int Start_id;
	if (ADDR_Board == ADDR_M5_0)  Start_id = 1;
	else if (ADDR_Board == ADDR_M5_1)  Start_id = 21;
	else if (ADDR_Board == ADDR_M5_2)  Start_id = 41;
	else if (ADDR_Board == ADDR_M5_3)  Start_id = 61;
	else return 0;

	for (int i = 0; i < 20; i++)	//  lay 20 pin dau tien
	{
		if (mTestCase.mTestCaseConfig.ChanelConfigArr[Start_id + i] == BUS_PROPERTY_LOGIC_OUT)
			Dir_BUS[i] = 0x01;  // thuoc tinh FPGA OUT to DB50 (theo FW)
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[Start_id + i] == BUS_PROPERTY_CLOCK_OUT)		// khi output la CLK OUT
		{
			Dir_BUS[i] = 0x01; // thuoc tinh OUT from FPGA to DB50  (theo FW)
		}
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[Start_id + i] == BUS_PROPERTY_LOGIC_IN)		// khi INput logic khong co R pulled
		{
			Dir_BUS[i] = 0x02; // thuoc tinh IN from DB50 to FPGA  (theo FW)
		}
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[Start_id + i] == BUS_PROPERTY_LOGIC_IN_PUP)    // khi INPUT LOGIC co R Pulled
		{
			Dir_BUS[i] = 0x02; // thuoc tinh IN from DB50 to FPGA  (theo FW)
		}
		else Dir_BUS[i] = 0x00;  // khong noi M5 vao bus: OPEN
	}
	// gui cho device: 
	for (int j = 0; j < 20; j++)
		Buff_tx[8 + j] = Dir_BUS[j];
	int len_Tx = num_bytes + 8;
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;

}
int CPlan::Set_Paths_M5(void) {
	// thiet lap ca 4 board o M5_0,1,2,3
	int nRet;
	nRet = Set_Paths_M5_i(ADDR_M5_0);
	if (nRet < 8) return 1;
	Sleep(1000);
	nRet = Start_Apply_Relay(ADDR_M5_0);
	if (nRet < 8) return 3;
	Sleep(1000);

	nRet = Set_Paths_M5_i(ADDR_M5_1);
	if (nRet < 8) return 2;
	Sleep(1000);
	nRet = Start_Apply_Relay(ADDR_M5_1);
	if (nRet < 8) return 3;
	Sleep(1000);

	nRet = Set_Paths_M5_i(ADDR_M5_2);
	if (nRet < 8) return 3;
	Sleep(1000);
	nRet = Start_Apply_Relay(ADDR_M5_2);
	if (nRet < 8) return 3;
	Sleep(1000);

	nRet = Set_Paths_M5_i(ADDR_M5_3);
	if (nRet < 8) return 4;
	Sleep(1000);
	nRet = Start_Apply_Relay(ADDR_M5_3);
	if (nRet < 8) return 3;
	else return 0;

}

int CPlan::Start_Apply_Relay(byte ADDR_Board)
{
	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];
	byte num_bytes = 0;  // so byte payload
	byte Buff_tx[128];
	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; // ADDR_PC
	Buff_tx[1] = ADDR_Board; // ADDR_M1_0
	Buff_tx[2] = 0x0B; // xac nhan boarrd cam dung vi tri
	Buff_tx[3] = 0x02;

	Buff_tx[4] = 0x00;  

	Buff_tx[5] = 0x01; // ADDR_M1_0
	Buff_tx[6] = 0x00;
	Buff_tx[7] = 0x00;

	// payload: khong co

	// gui cho device: 
	int len_Tx = num_bytes + 8;
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;

}



int CPlan::Start_Apply_Relay_M9(byte ID_JACK)
{
	//return :
	//	 0: khong can thuc hien cau hinh cho M9
	//	-1: goi in nhan ve bi loi
	//  >= 8: so byte nhan duoc khi thuc hien cau hinh




	// ham update relay tu cac du lieu da gui vao mang data_jack truoc do tren board M9
	// lenh nay ra lenh bt dau thuc hien data do cho cac relay

	// ID_JACK: 1,2,3,4,5,6,7,8,9 tuong ung theo quy dinh goi tin
	// NOTE: rieng voi jack 8A,8B: do cung 1 cap jack cua connector 135 chan nen ID_JACK chi can gui 1 lenh la M9_ID_JAck_8A, dieu nay se update ca 2 jack 8A, 8B

	// ddefine ID cac jack cua M9, dung cho set up M9: truyen ID jack ma DUT cam vao
// TUAN moi them 28/9/2023
// 
// 	   khong chon jack nao: 0
//#define M9_Jack_1			1
//#define M9_Jack_2			2
//#define M9_Jack_3			3
//#define M9_Jack_4			4
//	
//#define M9_Jack_5			5
//#define M9_Jack_6			6
//#define M9_Jack_7			7
//#define M9_Jack_8A, 8B	8


//Khi ID_Jack = 9; : Cau hinh Jack khong thuoc 8 Jack co tren M9 (khong su dung M9) ==> khong gui thong tin cau hnh dinh tuyen cho M9

	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];
	byte num_bytes = 0;  // so byte payload
	byte Buff_tx[SIZE_MAX_BUFF_RX_SERIAL];  
	// jack 8 duoc tach ra thah 8A va 8B. moi jack 135 chan
	// cho phep board Active
	// header
	Buff_tx[0] = ADDR_PC; // ADDR_PC
	Buff_tx[1] = ADDR_M9; // ADDR_M1_0
	Buff_tx[2] = 0x0B; // xac nhan boarrd cam dung vi tri

	if (ID_JACK == 0) Buff_tx[3] = 0x01;    // reset board khi van cam M9 ma khong dung
	if ((1<= ID_JACK) && (ID_JACK <= 8))  Buff_tx[3]  = 0x02 ;  // apply relay
	

	Buff_tx[4] = mTestCase.mID_Jack;   // only for test M9: 0,1,2,3,4,5,6,7

	Buff_tx[5] = 0x01; // ADDR_M1_0
	Buff_tx[6] = 0x00;
	Buff_tx[7] = 0x00;


	// gui cho device: 
	int len_Tx = num_bytes + 8;
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;
	
}

int CPlan::Set_Paths_M3_i(byte ADDR_Board) { // thiet lap board M3_0 /  M3_1
	
	// ADDR_Board: 0x30 hoac  0x31
	// rerturn 0: error,   1: OK

	byte m_pBuffRecv[128];
	byte num_bytes = 8;  // so byte payload
	byte Buff_tx[128];
	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; 			// ADDR_PC
	if ((ADDR_Board == ADDR_M3_0) || (ADDR_Board == ADDR_M3_1))
		Buff_tx[1] = ADDR_Board; 	// ADDR_Mi
	else return 0;   // error
	Buff_tx[2] = 0x09; 			// reset matrix
	Buff_tx[3] = 0x01;			// du lieu ma tran relays
	Buff_tx[4] = 0x00;

	Buff_tx[5] = 0x01; 			// Ver FW: 1.0
	Buff_tx[6] = 0x00;


	num_bytes = 8;				// so byte  == so dau ra: DB50 / M1_i
	Buff_tx[7] = num_bytes;		// length of payload
	

	for (int j = 0; j < 8; j++)
		if (ADDR_Board == ADDR_M3_0)  Buff_tx[8 + j] = Data_Relay_M3_0[j];
		else if (ADDR_Board == ADDR_M3_1)  Buff_tx[8 + j] = Data_Relay_M3_1[j];

	// gui cho device: 
	int len_Tx = num_bytes + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv,SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;
}



int CPlan::Set_Paths_M3(void) {
	// thiet lap ca 4 board o M5_0,1,2,3
	int nRet;

	nRet = Set_Paths_M3_i(ADDR_M3_0);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (nRet < 8) return 3;
	Sleep(1000);
	nRet = Start_Apply_Relay(ADDR_M3_0);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (nRet < 8) return 3;
	Sleep(1000);


	nRet = Set_Paths_M3_i(ADDR_M3_1);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (nRet < 8) return 3;
	Sleep(1000);
	nRet = Start_Apply_Relay(ADDR_M3_1);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	if (nRet < 8) return 3;
	else return 0;

}

int CPlan::Set_ON_Off_30V_M9(byte ON_OFF) {
	// M1 thiet lap ON_OFF nguon cho M9
	// rerturn   nRet: OK

	byte m_pBuffRecv[128];
	byte num_bytes = 8;			// so byte payload
	byte Buff_tx[128];
	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; 			// ADDR_PC
	Buff_tx[1] = ADDR_M1_0; 	// ADDR_Mi

	Buff_tx[2] = 0x09; 			// reset matrix
	Buff_tx[3] = 0x10;			// bat tat nguon M9
	Buff_tx[4] = 0x00;

	Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
	Buff_tx[6] = (VERSION_FW & 0x00FF);

	num_bytes = 1;		// so byte  == so dau ra: DB50 / M1_i
	Buff_tx[7] = num_bytes;			// length of payload
	Buff_tx[8] = ON_OFF;


	// gui cho device: 
	int len_Tx = num_bytes + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;



}



int CPlan::Set_Freq_Vout_M5(byte ADDR_Board)   // thiet lap tham so tin hieu cho M5
{
	// thiet lap tan so va Vout logic cho m5
	// rerturn   nRet: OK

	byte m_pBuffRecv[128];
	byte num_bytes = 8;  // so byte payload
	byte Buff_tx[128];
	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; 			// ADDR_PC
	Buff_tx[1] = ADDR_Board; 	// ADDR_Mi              nen check dia chi ?????????????

	Buff_tx[2] = 0x09; 			// reset matrix
	Buff_tx[3] = 0x07;			// bat tat nguon M9
	Buff_tx[4] = 0x00;

	Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
	Buff_tx[6] = (VERSION_FW & 0x00FF);


	num_bytes = 3;		// so byte  == so dau ra: DB50 / M1_i
	Buff_tx[7] = num_bytes;			// length of payload
	Buff_tx[8] = 0x01;    // tan so cao
	Buff_tx[9] = 0x13;   // 5V
	Buff_tx[10] = 0x88;

	// gui cho device: 
	int len_Tx = num_bytes + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv,SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;



}

int CPlan::Set_Vnguong_In_M5(byte ADDR_Board)   // thiet lap tham so tin hieu cho M5
{

	// thiet lap tan so va Vout logic cho m5
	// rerturn   nRet: OK

	byte m_pBuffRecv[128];
	byte num_bytes = 8;  // so byte payload
	byte Buff_tx[128];
	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; 			// ADDR_PC
	if ((ADDR_Board == ADDR_M5_0) || (ADDR_Board == ADDR_M5_1) || (ADDR_Board == ADDR_M5_2) || (ADDR_Board == ADDR_M5_3))
		Buff_tx[1] = ADDR_Board; 	// ADDR_Mi            
	else return -1;

	Buff_tx[2] = 0x09; 			// reset matrix
	Buff_tx[3] = 0x09;			// bat tat nguon M9
	Buff_tx[4] = 0x00;

	Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
	Buff_tx[6] = (VERSION_FW & 0x00FF);


	num_bytes = 2;		// so byte  == so dau ra: DB50 / M1_i
	Buff_tx[7] = num_bytes;			// length of payload

	float Vnguong_Logic_In = mTestCase.ExtChanel_Get.LogicInComp.value;

	

	uint16_t data16bit = convert_FloatTo16bit(Vnguong_Logic_In, FACTOR_SCALER_0P001);
	Buff_tx[8] = (data16bit & 0xFF00) >> 8;
	Buff_tx[9] = data16bit & 0x00FF;

	//Buff_tx[8] = 0x01;    // 
	//Buff_tx[9] = 0x55;   // vnguong = 0.5V

	// gui cho device: 
	int len_Tx = num_bytes + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);
	return nRet;

}



int CPlan::Set_Dir_IO_M5_i(byte ADDR_Board)   // thiet lap tham so tin hieu cho M5
{

	// thiet lap tan so va Vout logic cho m5
		// rerturn   nRet: OK

	byte m_pBuffRecv[128];
	byte num_bytes = 8;  // so byte payload
	byte Buff_tx[128];
	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; 			// ADDR_PC

	if ((ADDR_Board == ADDR_M5_0) || (ADDR_Board == ADDR_M5_1) || (ADDR_Board == ADDR_M5_2) || (ADDR_Board == ADDR_M5_3))
		Buff_tx[1] = ADDR_Board; 	// ADDR_Mi 
	else return 0;    // return ve loi
	Buff_tx[2] = 0x09; 			// reset matrix
	Buff_tx[3] = 0x01;			// chieu IO cua cell M5
	Buff_tx[4] = 0x00;

	Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
	Buff_tx[6] = (VERSION_FW & 0x00FF);


	num_bytes = 20;				// so byte 

	Buff_tx[7] = num_bytes;		// length of payload

	for (int k = 0; k < 20; k++)
		Buff_tx[8 + k] = 0x00;   // xoa ve defualt: khong ket noi M5 voi bus he thong



	//..................................................................
	//// du lieu co dinh cho bo test_Kacta
	//Buff_tx[8 + 7] = 0x01;  // 2: IN, 1: OUT: BUS 28 (bat dau tu 1)
	//Buff_tx[8 + 10] = 0x01;  // 2: IN, 1: OUT: BUS 31 (bat dau tu 1)
	//Buff_tx[8 + 11] = 0x02;  // 2: IN, 1: OUT: BUS 32 (bat dau tu 1)
	//...................................................................



	// lay du lieu tu co so du lieu
	// hcieu IN/OUT logic cho M5

	byte Thuoc_tinh_Pins[20];  // 0: open,    1: OUT,    2: IN
	int Start_id;



	if (ADDR_Board == ADDR_M5_0)  Start_id = 1;
	else if (ADDR_Board == ADDR_M5_1)  Start_id = 21;
	else if (ADDR_Board == ADDR_M5_2)  Start_id = 41;
	else if (ADDR_Board == ADDR_M5_3)  Start_id = 61;

	for (int i = 0; i < 20; i++)	//  lay 40 pin dau tien
	{
		// dang loi o day
		if ((mTestCase.mTestCaseConfig.ChanelConfigArr[Start_id + i] == BUS_PROPERTY_LOGIC_IN) || (mTestCase.mTestCaseConfig.ChanelConfigArr[Start_id + i] == BUS_PROPERTY_LOGIC_IN_PUP))
			Thuoc_tinh_Pins[i] = 0x02;  //  dir input
		else if ((mTestCase.mTestCaseConfig.ChanelConfigArr[Start_id + i] == BUS_PROPERTY_LOGIC_OUT) || (mTestCase.mTestCaseConfig.ChanelConfigArr[Start_id + i] == BUS_PROPERTY_CLOCK_OUT))
			Thuoc_tinh_Pins[i] = 0x01;  //  dir Output
		else  // cac thuoc tinh khac
			Thuoc_tinh_Pins[i] = 0x00; // mac dinh la khong ket noi vao bus
	}


	// dong payload vao khung du lieu
	for (int j = 0; j < 20; j++)
		Buff_tx[8 + j] = Thuoc_tinh_Pins[j];


	// gui cho device: 
	int len_Tx = num_bytes + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;

}


int CPlan::Set_tham_so_Tin_hieu_M5(void)   // thiet lap tham so tin hieu cho M5
{
	// NOTE: Phan thet lap tan so va Vout logic high chuyen set tu Thanh
	//Set_Freq_Vout_M5(ADDR_M5_0);
	//Sleep(1000);
	//return 0: OK,   != 0 : error
	// bo sung lenh check ACK_pkg khi nhan goi tin
	Set_Vnguong_In_M5(ADDR_M5_0);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	Sleep(1000);
	Set_Dir_IO_M5_i(ADDR_M5_0);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	Sleep(1000);
	Start_Apply_Relay(ADDR_M5_0);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	Sleep(1000);


	//Set_Freq_Vout_M5(ADDR_M5_1);
	//Sleep(1000);
	Set_Vnguong_In_M5(ADDR_M5_1);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	Sleep(1000);
	Set_Dir_IO_M5_i(ADDR_M5_1);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	Sleep(1000);
	Start_Apply_Relay(ADDR_M5_1);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	Sleep(1000);



	//Set_Freq_Vout_M5(ADDR_M5_2);
	//Sleep(1000);
	Set_Vnguong_In_M5(ADDR_M5_2);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	Sleep(1000);
	Set_Dir_IO_M5_i(ADDR_M5_2);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	Sleep(1000);
	Start_Apply_Relay(ADDR_M5_2);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	Sleep(1000);



	//Set_Freq_Vout_M5(ADDR_M5_3);
	//Sleep(1000);
	Set_Vnguong_In_M5(ADDR_M5_3);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	Sleep(1000);
	Set_Dir_IO_M5_i(ADDR_M5_3);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	Sleep(1000);
	Start_Apply_Relay(ADDR_M5_3);
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//---------------------------------------
	Sleep(1000);

	return 0;
}

//-----------------------------------------------------------------


int CPlan::Process_Seting_PWR(void) {
	//----------------------------------------
	i_Progress++;
	SetPhanTramProgress(i_Progress * 100 / n_Progress);
	//-------------------------------------------

	//-----------------------------------------------------------------
	// kiem tra, va chuan bi du lieu cho thiet lap nguon cho M3 và dinh tuyen cua M2PS
	// Bước 1: tinh so loại nguồn trong mỗi nhom 40 kênh
	Sleep(10);
	// 40 kenh dau tien
	int ListPwr_A[8];    // dung cho kenh 1...40
	int ListPwr_B[8];    // dung cho kenh 41..80
	int tmpA = 0;
	int tmpB = 0;
	int tmp;


	for (int i = 0; i < 8; i++)
	{
		Data_Relay_M3_0[i] = 0x00;  // xoa ve khong noi: mac dinh
		Data_Relay_M3_1[i] = 0x00;  // xoa ve khong noi: mac dinh
	}

	for (int i = 0; i < 41; i++)
	{
		Data_relay_M2PS_0[i] = 0x00;  // xoa ve khong noi: mac dinh
		Data_relay_M2PS_3[i] = 0x00;  // xoa ve khong noi: mac dinh
	}

	for (int i = 0; i < 8; i++)
	{
		ListPwr_A[i] = 0x00;
		ListPwr_B[i] = 0x00;
	}
	for (int i = 1; i <= 40; i++)
	{
		if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 1)		 ListPwr_A[0] = 1;
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 2)  ListPwr_A[1] = 1;
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 3)  ListPwr_A[2] = 1;
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 4)  ListPwr_A[3] = 1;
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 5)  ListPwr_A[4] = 1;
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 6)  ListPwr_A[5] = 1;
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 7)  ListPwr_A[6] = 1;
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 8)  ListPwr_A[7] = 1;
		else;
	}

	for (int i = 41; i <= 80; i++)
	{
		if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 1)		 ListPwr_B[0] = 1;
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 2)  ListPwr_B[1] = 1;
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 3)  ListPwr_B[2] = 1;
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 4)  ListPwr_B[3] = 1;
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 5)  ListPwr_B[4] = 1;
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 6)  ListPwr_B[5] = 1;
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 7)  ListPwr_B[6] = 1;
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[i] == 8)  ListPwr_B[7] = 1;
		else;
	}
	int NUM_PWR_A = 0;
	int NUM_PWR_B = 0;

	for (int k = 0; k < 8; k++)
	{
		NUM_PWR_A = NUM_PWR_A + ListPwr_A[k];
		NUM_PWR_B = NUM_PWR_B + ListPwr_B[k];
	}

	if (NUM_PWR_A > 4)
	{
		printf("LOI: so loai nguon cho cac kenh 1..40 vuot qua 4 loai \n");
		return -1;
	}
	if (NUM_PWR_B > 4)
	{
		printf("LOI: so loai nguon cho cac kenh 41..80 vuot qua 4 loai \n");
		return -1;
	}

	int List_Pwr_M2PS_0[4];  // list 4 nguon tuong ung; bus nguon: 1,2,3,4 tren MAIN
	for (int j = 0; j < 4; j++)
		List_Pwr_M2PS_0[j] = 0x00;   // 0: bus  khong noi voi nguon nao
	int id = 0;
	for (int j = 0; j < 8; j++)
		if (ListPwr_A[j] == 1) { List_Pwr_M2PS_0[id] = j + 1; id++; }  // luu lai chi so cua nguon: 1,2,3,4,5,6,7,8


	// nhom B; M2PS_3
	int List_Pwr_M2PS_3[4];   // list 4 nguon tuong ung; bus nguon: 5,6,7,8 tren MAIN
	for (int j = 0; j < 4; j++)
		List_Pwr_M2PS_3[j] = 0x00;   // 0: bus  khong noi voi nguon nao
	id = 0;
	for (int j = 0; j < 8; j++)
		if (ListPwr_B[j] == 1) { List_Pwr_M2PS_3[id] = j + 1; id++; }  // luu lai chi so cua nguon: 1,2,3,4,5,6,7,8

	//for (int j = 0; j < 8; j++)
	//	if (ListPwr_B[j] == 1) { List_Pwr_M2PS_3[1] = j + 1; break; }  // luu lai chi so cua nguon: 1,2,3,4,5,6,7,8

	//for (int j = 0; j < 8; j++)
	//	if (ListPwr_B[j] == 1) { List_Pwr_M2PS_3[2] = j + 1; break; }  // luu lai chi so cua nguon: 1,2,3,4,5,6,7,8

	//for (int j = 0; j < 8; j++)
	//	if (ListPwr_B[j] == 1) { List_Pwr_M2PS_3[3] = j + 1; break; }  // luu lai chi so cua nguon: 1,2,3,4,5,6,7,8

	/// --------------------
	// thiet lap cho M2PS_0
	// danh lai chi so nguon cho thuoc tinh kenh nguon
	//byte Data_relay_M2PS_0[41];  // dung tu 1...40
	//byte Data_relay_M2PS_3[41];  // dung tu 1...40
	for (int k = 0; k < 41; k++)
	{
		Data_relay_M2PS_0[k] = 0x00;
		Data_relay_M2PS_3[k] = 0x00;
	}



	// dinh danh lai
	for (int k = 1; k < 41; k++)
		if (mTestCase.mTestCaseConfig.ChanelConfigArr[k] == List_Pwr_M2PS_0[0]) Data_relay_M2PS_0[k] = 1;    // danh lai chi so nguon thanh 1,2,3,4 moi
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[k] == List_Pwr_M2PS_0[1]) Data_relay_M2PS_0[k] = 2;    // danh lai chi so nguon thanh 1,2,3,4 
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[k] == List_Pwr_M2PS_0[2]) Data_relay_M2PS_0[k] = 3;    // danh lai chi so nguon thanh 1,2,3,4 
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[k] == List_Pwr_M2PS_0[3]) Data_relay_M2PS_0[k] = 4;    // danh lai chi so nguon thanh 1,2,3,4 
		else Data_relay_M2PS_0[k] = 0;    // khong noi voi nguon

	// data cho M3_0
	//byte Data_Relay_M3_0[8];  // dung cau hinh chuyen mach relay cho M3
	Data_Relay_M3_0[0] = List_Pwr_M2PS_0[0];
	Data_Relay_M3_0[1] = List_Pwr_M2PS_0[1];
	Data_Relay_M3_0[2] = List_Pwr_M2PS_0[2];
	Data_Relay_M3_0[3] = List_Pwr_M2PS_0[3];

	// khong dung  4 dau ra cao
	Data_Relay_M3_0[4] = 0;
	Data_Relay_M3_0[5] = 0;
	Data_Relay_M3_0[6] = 0;
	Data_Relay_M3_0[7] = 0;
	/// --------------------

	// thiet lap cho M2PS_3
	// danh lai chi so nguon cho thuoc tinh kenh nguon
	//byte Data_relay_M2PS_3[41];  // dung tu 1...40

	// dinh danh lai
	for (int k = 1; k < 41; k++)
		if (mTestCase.mTestCaseConfig.ChanelConfigArr[40 + k] == List_Pwr_M2PS_3[0]) Data_relay_M2PS_3[k] = 1;    // danh lai chi so nguon thanh 1,2,3,4 moi
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[40 + k] == List_Pwr_M2PS_3[1]) Data_relay_M2PS_3[k] = 2;    // danh lai chi so nguon thanh 1,2,3,4 
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[40 + k] == List_Pwr_M2PS_3[2]) Data_relay_M2PS_3[k] = 3;    // danh lai chi so nguon thanh 1,2,3,4 
		else if (mTestCase.mTestCaseConfig.ChanelConfigArr[40 + k] == List_Pwr_M2PS_3[3]) Data_relay_M2PS_3[k] = 4;    // danh lai chi so nguon thanh 1,2,3,4 
		else Data_relay_M2PS_3[k] = 0;    // khong noi voi nguon

	// data cho M3_1
	//byte Data_Relay_M3_1[8];  // dung cau hinh chuyen mach relay cho M3
	// khong dung  4 dau ra thap
	Data_Relay_M3_1[0] = 0;
	Data_Relay_M3_1[1] = 0;
	Data_Relay_M3_1[2] = 0;
	Data_Relay_M3_1[3] = 0;

	Data_Relay_M3_1[4] = List_Pwr_M2PS_3[0];
	Data_Relay_M3_1[5] = List_Pwr_M2PS_3[1];
	Data_Relay_M3_1[6] = List_Pwr_M2PS_3[2];
	Data_Relay_M3_1[7] = List_Pwr_M2PS_3[3];

	//AfxMessageBox(_T("Mess"));

		 //===> thuc hien cau hinh relay cho M2PS_0,3
		 // ==> thuc hien cau hinh relay cho M3_0, M3_1
	
		 //luu y: truoc khi thiet lap gia tri nguon ra cho 8 nguon: nhung nguon nao khong dung o M3_i thi nen tat bo ==> 3 board M3 cacu hinh khac nhau de hieu qua hon
		 //can sua lai fW cho board M2PS, voi truong hop data relay nhan dc la cua board : M2PS_3: chi so van la tu 1,2,3,4
	
		Sleep(1000);
	
		//CString stmp;
	
		//printf("\n in ra ket qua sau xu ly: \n\r");
		//stmp.Format(_T("Data_Relay_M3_0\r\nData_Relay_M3_0 [ ]: %d,%d,%d,%d,%d,%d, %d,%d"), Data_Relay_M3_0[0], Data_Relay_M3_0[1],Data_Relay_M3_0[2], Data_Relay_M3_0[3], Data_Relay_M3_0[4], Data_Relay_M3_0[5], Data_Relay_M3_0[6], Data_Relay_M3_0[7] );
		//AfxMessageBox(stmp);

		//MessageBox(stmp, _T("Data_Relay_M3_0"));
	
		//MessageBox(_T("Active all board!"), _T("Mess"));
		//MessageBox( _T ("stmp"), _T("Data_Relay_M3_1"));
	
		//stmp.Format(_T("\n Data_Relay_M3_1 [ ]: %d,%d,%d,%d,%d,%d, %d,%d \n\r"), Data_Relay_M3_1[0], Data_Relay_M3_1[1], Data_Relay_M3_1[2], Data_Relay_M3_1[3], Data_Relay_M3_1[4], Data_Relay_M3_1[5], Data_Relay_M3_1[6], Data_Relay_M3_1[7]);
		//MessageBox(stmp, _T("Data_Relay_M3_1"));

	return 0;
}



int CPlan::Power_Ctrl_M1_For_DUT(UINT ON_OFF_Stt, byte ADDR_Board)
{
//NOTE: dieu khien ON/ OFF nguon ra +30 tu DB50 jack cap cho DUT (M9, M10)
// ON_OFF_Stt:    P_ON: 1    P_OFF: 0
// ADDR_Board; only for Board M1_0, M1_1
// return: number bytes: >=8 : 0K,    -1: error


	byte m_pBuffRecv[128];
	byte num_bytes = 8;  // so byte payload
	byte Buff_tx[128];
	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; 			// ADDR_PC

	if ((ADDR_Board == ADDR_M1_0) || (ADDR_Board == ADDR_M1_1))
		Buff_tx[1] = ADDR_Board; 	// ADDR_Mi 
	else return -1;    // return ve loi
	Buff_tx[2] = 0x09; 			// reset matrix
	Buff_tx[3] = 0x10;			// on/ OFF +30V
	Buff_tx[4] = 0x00;

	Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
	Buff_tx[6] = (VERSION_FW & 0x00FF);


	num_bytes = 1;				// so byte 

	Buff_tx[7] = num_bytes;		// length of payload

	Buff_tx[8] = ON_OFF_Stt;     // 0: OFF, 1: ON


	// gui cho device: 
	int len_Tx = num_bytes + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;


}


int CPlan::SetUp_RPullUp_M10(void)
{
	//NOTE: cau hinh tham so cho M10
	// // data gui di 12 bytes:
	// 
	// Byte [0]   V_logic_H : factor: 0.01
	// Byte [1]   V_logic_L
	//  Byte [2..11] 10 bytes x 8 bit = 80 channel ( 0..79): bit value = 1: Pulled, 0: No pulled
	// 
	// return: number bytes: >=8 : 0K,    -1: error


	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];
	byte num_bytes = 8;  // so byte payload
	byte Buff_tx[SIZE_MAX_BUFF_RX_SERIAL];

	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; 			// ADDR_PC
	Buff_tx[1] = ADDR_M10; 		// ADDR_Mi : bo mach R Pull up
	Buff_tx[2] = 0x09; 			// reset matrix
	Buff_tx[3] = 0x01;			// thiet lap vout + trang thai Pullup or no Pull Up: trang thai relays
	Buff_tx[4] = 0x00;

	Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
	Buff_tx[6] = (VERSION_FW & 0x00FF);


	num_bytes = 12;				// so byte 12 = byte ơ0,1ư: vout, byte[2,..11]: 10x8 = 80 bit : 1: Pulled, 0: normal

	Buff_tx[7] = num_bytes;		// length of payload

	float Vout_Logic_high = mTestCase.ExtChanel_Set.LogicOutHi.value;   // dien ap muc cao logic

	uint16_t data16bit = convert_FloatTo16bit(Vout_Logic_high, FACTOR_SCALER_0P001);
	Buff_tx[8 + 0] = (data16bit & 0xFF00) >> 8;
	Buff_tx[8 + 1] = data16bit & 0x00FF;

	// 10 byte cau hinh cho 80 bit pulled up or normal
	UINT8 Bit0, Bit1, Bit2, Bit3, Bit4, Bit5, Bit6, Bit7;

	for (int i = 0; i < 10; i++)
	{
		Bit0 = mTestCase.mTestCaseConfig.ChanelPUPConfigArr[8 * i + 1 + 0];
		Bit1 = mTestCase.mTestCaseConfig.ChanelPUPConfigArr[8 * i + 1 + 1];
		Bit2 = mTestCase.mTestCaseConfig.ChanelPUPConfigArr[8 * i + 1 + 2];
		Bit3 = mTestCase.mTestCaseConfig.ChanelPUPConfigArr[8 * i + 1 + 3];
		Bit4 = mTestCase.mTestCaseConfig.ChanelPUPConfigArr[8 * i + 1 + 4];
		Bit5 = mTestCase.mTestCaseConfig.ChanelPUPConfigArr[8 * i + 1 + 5];
		Bit6 = mTestCase.mTestCaseConfig.ChanelPUPConfigArr[8 * i + 1 + 6];
		Bit7 = mTestCase.mTestCaseConfig.ChanelPUPConfigArr[8 * i + 1 + 7];
		
		Buff_tx[8 + 2 + i] = (((Bit7 & 0x01) << 7) | ((Bit6 & 0x01) << 6) | ((Bit5 & 0x01) << 5) |((Bit4 & 0x01) << 4) | ((Bit3 & 0x01) << 3) | ((Bit2 & 0x01) << 2) | ((Bit1 & 0x01) << 1) | ((Bit0 & 0x01) << 0));
	}

	//CString stmp;

	//printf("\n In du lieu cau hinh cho M10: \n\r");
	//stmp.Format(_T("data[ ]: %d,%d,%d,%d,%d,%d, %d,%d, %d, %d, %d, %d\n\r"), Buff_tx[8], Buff_tx[9], Buff_tx[10], Buff_tx[11], Buff_tx[12], Buff_tx[13], Buff_tx[14], Buff_tx[15], Buff_tx[16], Buff_tx[17], Buff_tx[18], Buff_tx[19]);
	//AfxMessageBox(stmp);

	// gui cho device: 
	int len_Tx = num_bytes + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 5);

	return nRet;
}


//int CPlan::Xuly_Maloi_ACK(UINT Length_data, byte* Data_Rx_Buff)
//{
//	UINT flag[5];
//	CString stmp;
//
//	for (int i = 0; i < 5; i++) flag[i] = 0x00;
//
//	if (Data_Rx_Buff[1] == ADDR_PC)  // noi nhan la PC
//	{
//		if ((Length_data == 9) && (Data_Rx_Buff[2] == 0x02)) // goi tin ACK
//		{
//			flag[0] = (Data_Rx_Buff[8] & 0x01);   // PC dang su dung phan mem khong dung Ver de giao tiep voi thiet bi
//			flag[1] = (Data_Rx_Buff[8] & 0x02);   // loi giao tiep UART giua M6 va cac bo mach khac
//			flag[2] = (Data_Rx_Buff[8] & 0x04);   // loi CAN, M6 gui lenh khong thanh cong xuong Mx
//			flag[3] = (Data_Rx_Buff[8] & 0x08);   // loi gia tri tham so cau hinh trong goi tin khong hop le
//			flag[4] = (Data_Rx_Buff[8] & 0x10);   // loi cau hinh tham so cho phan cung khong thanh cong
//
//			if (flag[0] != 0)
//			{
//				stmp.Format(_T("LỖI: Phiên bản phần mềm không hợp lệ. Phiên bản phù hợp là Ver: %d.%d", Data_Rx_Buff[5], Data_Rx_Buff[6]));
//				MessageBox(stmp, _T("Thông báo"));
//			}
//
//			if (flag[1] != 0)
//			{
//				MessageBox(_T("LỖI: Giao tiếp UART giữa M6 và các khối Mx không tốt"), _T("Thông báo"));
//			}
//
//
//			if (flag[2] != 0)
//			{
//				MessageBox(_T("LỖI: Giao tiếp CAN, M6 gửi lệnh xuống Mx không thành công"), _T("Thông báo"));
//			}
//
//
//			if (flag[3] != 0)
//			{
//				MessageBox(_T("LỖI: Giá trị tham số trong gói tin thiết lập không hợp lệ"), _T("Thông báo"));
//			}
//
//
//			if (flag[4] != 0)
//			{
//				MessageBox(_T("LỖI: Cấu hình tham số cho thiết bị không thành công"), _T("Thông báo"));
//			}
//		} else return -1;
//	}
//	else return -1;   //  co loi trong goi tin CAN tra ve PC
//
//	return 0;
//}

//----------------------------------------------------------------------




int CPlan::Set_Paths_M9_test_JA1(void) {

	//NOTE: cau hinh tham so cho M9
	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];
	byte num_bytes = 80 + 3;  // so byte payload
	byte Buff_tx[SIZE_MAX_BUFF_RX_SERIAL];

	byte data_JA1[137];

	// tao du lieu
	data_JA1[0] = 7;
	data_JA1[1] = 135;

	byte ID_Jack_test = M9_JA4JA1_Jack_8;

	for (int i = 0; i <= 11 ; i++)   data_JA1[i + 2] = 100;  // fix = moi dat

	for (int i = 12; i <=  39; i++)   data_JA1[i + 2] = i - 11;  // fix = moi dat

	data_JA1[40 + 2] = 0;    // fix = 0
	data_JA1[41 + 2] = 29;    // fix 
	data_JA1[42 + 2] = 103;    // fix  nguon 27V
	data_JA1[43 + 2] = 31;    // fix
	data_JA1[44 + 2] = 32;    // fix

	//  hafng B
	data_JA1[45 + 2] = 0;    // fix

	for (int j = 46; j <= 85; j ++ )  data_JA1[j + 2] = 0;    // init to default. no connect
	// edit
	data_JA1[70 + 2] = 103;    // select for test: 27V


	// byte co dinh
	data_JA1[86 + 2] = 29;    // fix 
	data_JA1[87 + 2] = 0;    // fix
	data_JA1[88 + 2] = 31;    // fix
	data_JA1[89 + 2] = 32;    // fix


	// hang C
	data_JA1[90 + 2] = 100;    // fix 
	for (int j = 91; j <= 130; j++)  data_JA1[j + 2] = 0;    // init to default. no connect

	// byte co dinh
	data_JA1[131 + 2] = 29;    // fix 
	data_JA1[132 + 2] = 0;    // fix
	data_JA1[133 + 2] = 31;    // fix
	data_JA1[134 + 2] = 32;    // fix




	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; 			// ADDR_PC
	Buff_tx[1] = ADDR_M9; 		// ADDR_Mi : bo mach R Pull up
	Buff_tx[2] = 0x09; 			//  matrix
	Buff_tx[3] = 0x01;			//
	Buff_tx[4] = 0x00;

	Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
	Buff_tx[6] = (VERSION_FW & 0x00FF);

	// .......... data cho lan 1 ................
	int soluongguilan1 = 80;
	num_bytes = soluongguilan1 + 3;
	Buff_tx[7] = num_bytes;    // gui lan 1 82 byte = 3 byte dau (ID jack, vi tri bat dau, So luong byte trong goi) + 80 byte (80 pins)

	Buff_tx[8] = ID_Jack_test;    // jack J1A  (Jack_8A)
	Buff_tx[9] = 0;    // gui lan 1: vi tri bat dau ghi
	Buff_tx[10] = soluongguilan1;  // so luong data lan 1

	for (int i = 0; i < soluongguilan1; i++)
		Buff_tx[11 + i] = data_JA1[i];

	// gui cho device: 
	int len_Tx = num_bytes + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);
	
	if (nRet <= 8)
		AfxMessageBox(_T("gui lan 1 loi"));
	else AfxMessageBox(_T("gui lan 1 : OK"));


	Sleep(3000);
// ------------- gui lan 2 ----------------
	int soluongconlai = 137 - soluongguilan1;
	num_bytes = soluongconlai + 3;
	Buff_tx[7] = num_bytes;    // gui lan 1 82 byte = 3 byte dau (ID jack, vi tri bat dau, So luong byte trong goi) + 80 byte (80 pins)

	Buff_tx[8] = 7;    // jack J1A  (Jack_8A)
	Buff_tx[9] = soluongguilan1;    // gui lan 2: vi tri bat dau ghi
	Buff_tx[10] = soluongconlai;  // so luong data lan 1

	for (int i = 0; i < soluongconlai; i++)
		Buff_tx[11 + i] = data_JA1[soluongguilan1 + i];

	// gui cho device: 
	 len_Tx = num_bytes + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	 nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	 if (nRet <= 8)
		AfxMessageBox(_T("gui lan 2 loi"));
	 else AfxMessageBox(_T("gui lan 2 : OK"));

	return nRet;

}





int CPlan::Set_Paths_M9(byte ID_jack) {

	//NOTE: cau hinh tham so cho M9
	
	CString stmp;

	
	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];
	byte num_bytes = 0;  // so byte payload
	int len_Tx;
	int nRet;
	int soluongguilan1;
	int soluongguilan2;
	byte Buff_tx[SIZE_MAX_BUFF_RX_SERIAL];

	byte data_Jack[MAX_PINS_ON_JACK];    // khai bao chung cho cac jack: 270
	for (int k = 0; k < MAX_PINS_ON_JACK; k++)   data_Jack[k] = 0;   // rreset all data

	// tao du lieu
	data_Jack[0] = ID_jack;				//  0: ko su dung Jack M9, 1: Jack1, 2; jack 2, ... 8: Jack 8A + 8B

	int Tong_so_Pins_ofBoard;
	Tong_so_Pins_ofBoard = mTestCase.mPins_Of_Board;

	// J1, ... ,J6:
	if ((1 <= ID_jack) && (ID_jack <= 6) && (Tong_so_Pins_ofBoard <= 90))   // những jack thông thường: đi thẳng: không cần cấu hình
	{

		// chuan bi data
		data_Jack[0] = ID_jack;   // ID cua Jack: 1..6
		data_Jack[1] = Tong_so_Pins_ofBoard; // so chan cua Jack 

		// data_Jack[2...] : data cau hinh cho tung chan
		for (int i = 1; i <= Tong_so_Pins_ofBoard; i++)  // 
			data_Jack[i + 1] = mTestCase.mTestCaseConfig.mPinsConf[i].iChanel;  // chi so Pin tinh tu 1
		// --------------------------------------------------------------------------------------------

		// ==> RESET ALL Jack on M9: khong dung toi cac chuyen mach cua M9
		Buff_tx[0] = ADDR_PC; 		// ADDR_PC
		Buff_tx[1] = ADDR_M9; 		// ADDR_Mi : bo mach R Pull up
		Buff_tx[2] = 0x09; 			// CMD
		Buff_tx[3] = 0x01;			// data relay
		Buff_tx[4] = 0x00;

		Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
		Buff_tx[6] = (VERSION_FW & 0x00FF);

		// gui data chi 1 lan
		soluongguilan1 = Tong_so_Pins_ofBoard + 2;   // add 2 ID, Sum_Pins in arr format for a jack
		num_bytes = soluongguilan1 + 3;   // num bytes in payload: header: ID, Start_Byte, Numbyte, data[0,1,...]
		Buff_tx[7] = num_bytes;
		// add payload
		Buff_tx[8] = ID_jack;
		Buff_tx[9] = 0;   // start from 0
		Buff_tx[10] = soluongguilan1;  // 80 byte sau tien
		for (int k = 0; k < soluongguilan1; k++)
			Buff_tx[11 + k] = data_Jack[k];

		// gui cho device: 
		len_Tx = num_bytes + 8;
		//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
		nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);
		if (nRet == -1)
		{
			stmp.Format(_T("LỖI: Gửi dữ liệu cấu hình định tuyến cho JACK thứ [%d] M9 không thành công"), ID_jack);
			AfxMessageBox(stmp);
			return -1;
		}
		return nRet;
	}
	else
	{
		//J7
		if ((ID_jack == M9_JA2_Jack_7) && (Tong_so_Pins_ofBoard == 135))
		{
			// chuan bi data
			data_Jack[0] = 7;   // ID cua Jack: jack 7
			data_Jack[1] = 135; // so chan cua Jack 7: 135 chan

			// data_Jack[2...] : data cau hinh cho tung chan
			for (int i = 1; i <= Tong_so_Pins_ofBoard; i++)  // 135
				data_Jack[i + 1] = mTestCase.mTestCaseConfig.mPinsConf[i].iChanel;  // chi so Pin tinh tu 1
			// --------------------------------------------------------------------------------------------

			// cau hinh cho jack 7: 135 chan ==> chia ra lam 2 goi tin
			Buff_tx[0] = ADDR_PC; 		// ADDR_PC
			Buff_tx[1] = ADDR_M9; 		// ADDR_Mi : bo mach R Pull up
			Buff_tx[2] = 0x09; 			//  CMD
			Buff_tx[3] = 0x01;			// reset board
			Buff_tx[4] = 0x00;

			Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
			Buff_tx[6] = (VERSION_FW & 0x00FF);

			// gui lan 1
			soluongguilan1 = 80;
			num_bytes = soluongguilan1 + 3;   // num bytes in payload: header: ID, Start_Byte, Numbyte, data[0,1,...]
			Buff_tx[7] = num_bytes;
			// add payload
			Buff_tx[8] = ID_jack;
			Buff_tx[9] = 0;   // start from 0
			Buff_tx[10] = soluongguilan1;  // 80 byte sau tien
			for (int k = 0; k < soluongguilan1; k++)
				Buff_tx[11 + k] = data_Jack[k];

			// gui cho device: 
			len_Tx = num_bytes + 8;
			//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
			nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);
			if (nRet == -1)
			{
				AfxMessageBox(_T("LỖI: Gửi dữ liệu (gói 1) cấu hình định tuyến cho M9 JACK thứ [7] không thành công"));
				return -1;
			}

			//------- gui lan 2 -----
			soluongguilan2 = Tong_so_Pins_ofBoard + 2 - soluongguilan1;   //add 2: ID, num_pins
			num_bytes = soluongguilan2 + 3;
			Buff_tx[7] = num_bytes;    // gui lan 1 82 byte = 3 byte dau (ID jack, vi tri bat dau, So luong byte trong goi) + 80 byte (80 pins)

			Buff_tx[8] = ID_jack;   // Jack 7
			Buff_tx[9] = soluongguilan1;    // gui lan 2: vi tri bat dau ghi là kets thuc cua lan 1
			Buff_tx[10] = soluongguilan2;  // so luong data lan 1

			//add data jack
			for (int i = 0; i < soluongguilan2; i++)
				Buff_tx[11 + i] = data_Jack[soluongguilan1 + i];

			// gui cho device: 
			len_Tx = num_bytes + 8;
			//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
			nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);
			if (nRet == -1)
			{
				AfxMessageBox(_T("LỖI: Gửi dữ liệu (gói 2) cấu hình định tuyến cho M9 JACK thứ [7]  không thành công, "));
				return -1;
			}
			else return nRet;

		}

		// J8A + J8B
		if ((ID_jack == M9_JA4JA1_Jack_8) && (Tong_so_Pins_ofBoard == 225))
		{
			// ------------------------------------------------------------------------------------------------
			// chuan bi data Jack 8A: JA4
			// thuc te dung 90 chan / 225 chan cua 8A + 8B
			data_Jack[0] = ID_jack;   // ID cua Jack: jack 8A
			data_Jack[1] = 135; // so chan cua Jack 8A: 135 chan

			// data_Jack[2...] : data cau hinh cho tung chan
			for (int i = 1; i <= 45 ; i++)  // 135/270
				data_Jack[i + 1] = mTestCase.mTestCaseConfig.mPinsConf[i].iChanel;  // chi so Pin tinh tu 1

			for (int i = 46; i <= 90; i++)  // 135/270
				data_Jack[i + 1] = 0x00;    // hang chan bi bo, khong dung

			for (int i = 91; i <= 135; i++)  // 135/270
				data_Jack[i + 1] = mTestCase.mTestCaseConfig.mPinsConf[i-45].iChanel;  // chi so Pin tinh tu 1
			// --------------------------------------------------------------------------------------------

			// cau hinh cho jack 7: 90 chan + 445 chan hang giua dumpmy ( 45..90) = 0x00 ==> chia ra lam 2 goi tin
			Buff_tx[0] = ADDR_PC; 		// ADDR_PC
			Buff_tx[1] = ADDR_M9; 		// ADDR_Mi : bo mach R Pull up
			Buff_tx[2] = 0x09; 			//  CMD
			Buff_tx[3] = 0x01;			// reset board
			Buff_tx[4] = 0x00;

			Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
			Buff_tx[6] = (VERSION_FW & 0x00FF);

			// gui lan 1
			soluongguilan1 = 80;
			num_bytes = soluongguilan1 + 3;   // num bytes in payload: header: ID, Start_Byte, Numbyte, data[0,1,...]
			Buff_tx[7] = num_bytes;
			// add payload
			Buff_tx[8] = ID_jack;
			Buff_tx[9] = 0;   // start from 0
			Buff_tx[10] = soluongguilan1;  // 80 byte sau tien
			for (int k = 0; k < soluongguilan1; k++)
				Buff_tx[11 + k] = data_Jack[k];

			// gui cho device: 
			len_Tx = num_bytes + 8;
			//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
			nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);
			if (nRet == -1)
			{
				AfxMessageBox(_T("LỖI: Gửi dữ liệu (gói 1) cấu hình định tuyến cho M9  JACK thứ [8A] không thành công"));
				return -1;
			}

			//------- gui lan 2 -----
			soluongguilan2 = 135 + 2 - soluongguilan1;   //add 2: ID, num_pins
			num_bytes = soluongguilan2 + 3;
			Buff_tx[7] = num_bytes;    // gui lan 1 82 byte = 3 byte dau (ID jack, vi tri bat dau, So luong byte trong goi) + 80 byte (80 pins)

			Buff_tx[8] = ID_jack;   // Jack 7
			Buff_tx[9] = soluongguilan1;    // gui lan 2: vi tri bat dau ghi là kets thuc cua lan 1
			Buff_tx[10] = soluongguilan2;  // so luong data lan 1

			//add data jack
			for (int i = 0; i < soluongguilan2; i++)
				Buff_tx[11 + i] = data_Jack[soluongguilan1 + i];

			// gui cho device: 
			len_Tx = num_bytes + 8;
			//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
			nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);
			if (nRet == -1)
			{
				AfxMessageBox(_T("LỖI: Gửi dữ liệu (gói 2) cấu hình định tuyến cho M9 JACK thứ [8A] không thành công, "));
				return -1;
			}

			Sleep(1000);
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// gui data cho jack 8B: JA1: 135 chan con lai ( 225 - 90)

			data_Jack[0] = ID_jack + 1;   // ID cua Jack: jack 8B = 8A + 1
			data_Jack[1] = 135; // so chan cua Jack 8A: 135 chan

			// data_Jack[2...] : data cau hinh cho tung chan
			for (int i = 1; i <= 135; i++)  // 135/270
				data_Jack[i + 1] = mTestCase.mTestCaseConfig.mPinsConf[90+i].iChanel;  // chi so Pin tinh tu 1, jack 8B tinh tu 136...270
			// --------------------------------------------------------------------------------------------

			// cau hinh cho jack 7: 135 chan ==> chia ra lam 2 goi tin
			Buff_tx[0] = ADDR_PC; 		// ADDR_PC
			Buff_tx[1] = ADDR_M9; 		// ADDR_Mi : bo mach R Pull up
			Buff_tx[2] = 0x09; 			//  CMD
			Buff_tx[3] = 0x01;			// reset board
			Buff_tx[4] = 0x00;

			Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
			Buff_tx[6] = (VERSION_FW & 0x00FF);

			// gui lan 1
			soluongguilan1 = 80;
			num_bytes = soluongguilan1 + 3;   // num bytes in payload: header: ID, Start_Byte, Numbyte, data[0,1,...]
			Buff_tx[7] = num_bytes;
			// add payload
			Buff_tx[8] = ID_jack + 1;
			Buff_tx[9] = 0;   // start from 0
			Buff_tx[10] = soluongguilan1;  // 80 byte sau tien
			for (int k = 0; k < soluongguilan1; k++)
				Buff_tx[11 + k] = data_Jack[k];

			// gui cho device: 
			len_Tx = num_bytes + 8;
			//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
			nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);
			if (nRet == -1)
			{
				AfxMessageBox(_T("LỖI: Gửi dữ liệu (gói 1) cấu hình định tuyến cho M9  JACK thứ [8B]  không thành công"));
				return -1;
			}

			//------- gui lan 2 -----
			soluongguilan2 = 135 + 2 - soluongguilan1;   //add 2: ID, num_pins
			num_bytes = soluongguilan2 + 3;
			Buff_tx[7] = num_bytes;    // gui lan 1 82 byte = 3 byte dau (ID jack, vi tri bat dau, So luong byte trong goi) + 80 byte (80 pins)

			Buff_tx[8] = ID_jack + 1;   // Jack 8B
			Buff_tx[9] = soluongguilan1;    // gui lan 2: vi tri bat dau ghi là kets thuc cua lan 1
			Buff_tx[10] = soluongguilan2;  // so luong data lan 1

			//add data jack
			for (int i = 0; i < soluongguilan2; i++)
				Buff_tx[11 + i] = data_Jack[soluongguilan1 + i];

			// gui cho device: 
			len_Tx = num_bytes + 8;
			//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
			nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);
			if (nRet == -1)
			{
				AfxMessageBox(_T("LỖI: Gửi dữ liệu (gói 2) cấu hình định tuyến cho M9  JACK thứ [8B] không thành công, "));
				return -1;
			}
			else return nRet;

		}   // het J8

	}   // het J7,8A,8B
	return -1;    // trả về không hợp lệ khi khong trường hợp nao đúngs
}




// cac ham thiet lap tham so bao ve nguon
int CPlan::Set_Ithres_Protect_M7A(byte ID_Ithres_Pwr_Sys) {
	// ham thiet lap gia tri nguong dong I thres bao ve cho he thong tu M7A. khi dong tieu thu qua nguong nay thi se bi ngat he thong nham bao ve chong chap chay
	// ID_Ithres_Pwr_Sys = 1...9
	// cac nguon cho LTC4245 quan nguon chung
	// 0x01 : I nguong cho nguon sys 3.3V_1 : cap cho board M7A,B vaf cac bo tu board 1...8
	// 0x02 : I nguong cho nguon sys 5V
	// 0x03 : I nguong cho nguon sys 12V
	// 0x04 : I nguong cho nguon sys -12V

	// 0x05 : I nguong cho nguon sys 3.3V_2
	// 0x06 : I nguong cho nguon sys 12V_CP
	// 0x07 : I nguong cho nguon sys 12V_RL_1
	// 0x08 : I nguong cho nguon sys 12V_RL_2
	// 0x09 : I nguong cho nguon sys 30V
	

	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];
	byte num_bytes_payload = 2;  // so byte payload
	byte Buff_tx[SIZE_MAX_BUFF_RX_SERIAL];

	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; 			// ADDR_PC
	Buff_tx[1] = ADDR_M7_A; 	// ADDR_Mi
	Buff_tx[2] = 0x05; 			// set up I nguong sys protect

	if ((ID_Ithres_Pwr_Sys <= 0x09) && (ID_Ithres_Pwr_Sys > 0x00))
		Buff_tx[3] = ID_Ithres_Pwr_Sys;			// ma nguon dang can thiet lap
	else return -1;

	Buff_tx[4] = 0x00;

	Buff_tx[5] = (VERSION_FW & 0xFF00)  >> 8;			// Ver FW: 1.0
	Buff_tx[6] = (VERSION_FW & 0x00FF);



	num_bytes_payload = 2;				
	Buff_tx[7] = num_bytes_payload;		// length of payload

	float Ithres_PwrSys = 0;// gia tri nguong dong bao ve he thong

	switch (ID_Ithres_Pwr_Sys)
	{
	case ID_I_Thres_PwrSys_3V3_1: Ithres_PwrSys  = mTestCase.mSupply_Set.Imax_3v3 /2 ; break;
	case ID_I_Thres_PwrSys_3V3_2: Ithres_PwrSys = mTestCase.mSupply_Set.Imax_3v3 /2; break;
	case ID_I_Thres_PwrSys_5V: Ithres_PwrSys = mTestCase.mSupply_Set.Imax_5v; break;
	case ID_I_Thres_PwrSys_12V: Ithres_PwrSys = mTestCase.mSupply_Set.Imax_12v ; break;

	case ID_I_Thres_PwrSys_12V_N: Ithres_PwrSys = mTestCase.mSupply_Set.Imax_12v_N; break;
	case ID_I_Thres_PwrSys_12V_CPU: Ithres_PwrSys = mTestCase.mSupply_Set.Imax_12v_CPU; break;
	case ID_I_Thres_PwrSys_12V_RL_1: Ithres_PwrSys = mTestCase.mSupply_Set.Imax_12v_ROLE / 2; break;
	case ID_I_Thres_PwrSys_12V_RL_2: Ithres_PwrSys = mTestCase.mSupply_Set.Imax_12v_ROLE / 2; break;
	case ID_I_Thres_PwrSys_30V: Ithres_PwrSys = mTestCase.mSupply_Set.Imax_30v; break;

	default: Ithres_PwrSys = 0; break;
	}

	uint16_t data16bit = 0;
	if (Ithres_PwrSys > 0.01)    // de phat hien truong hop khong co case nao thoa man
		data16bit = convert_FloatTo16bit(Ithres_PwrSys, FACTOR_SCALER_0P001);
	else return -1;

	Buff_tx[8 + 0] = (data16bit & 0xFF00) >> 8;
	Buff_tx[8 + 1] = data16bit & 0x00FF;


	// gui cho device: 
	int len_Tx = num_bytes_payload + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;
	
}	


// cac ham thiet lap tham so bao ve nguon
int CPlan::Get_Ithres_Protect_M7A(byte ID_Ithres_Pwr_Sys) {
	// ham doc gia tri nguong dong I thres bao ve cho he thong tu M7A. khi dong tieu thu qua nguong nay thi se bi ngat he thong nham bao ve chong chap chay
	// ID_Ithres_Pwr_Sys = 1...9
	// cac nguon cho LTC4245 quan nguon chung
	// 0x01 : I nguong cho nguon sys 3.3V_1 : cap cho board M7A,B vaf cac bo tu board 1...8
	// 0x02 : I nguong cho nguon sys 5V
	// 0x03 : I nguong cho nguon sys 12V
	// 0x04 : I nguong cho nguon sys -12V

	// 0x05 : I nguong cho nguon sys 3.3V_2
	// 0x06 : I nguong cho nguon sys 12V_CP
	// 0x07 : I nguong cho nguon sys 12V_RL_1
	// 0x08 : I nguong cho nguon sys 12V_RL_2
	// 0x09 : I nguong cho nguon sys 30V


	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];
	byte num_bytes_payload = 0;  // so byte payload
	byte Buff_tx[SIZE_MAX_BUFF_RX_SERIAL];

	// cho phep board Active
	// header
	Buff_tx[0] = ADDR_PC; 			// ADDR_PC
	Buff_tx[1] = ADDR_M7_A; 	// ADDR_Mi
	Buff_tx[2] = CMD_READ_THRES_I; 			// read I nguong sys protect

	if ((ID_Ithres_Pwr_Sys <= 0x09) && (ID_Ithres_Pwr_Sys > 0x00))
		Buff_tx[3] = ID_Ithres_Pwr_Sys;			// ma nguon dang can thiet lap
	else return -1;

	Buff_tx[4] = 0x00;

	Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
	Buff_tx[6] = (VERSION_FW & 0x00FF);



	num_bytes_payload = 0;
	Buff_tx[7] = num_bytes_payload;		// length of payload

	// gui cho device: 
	int len_Tx = num_bytes_payload + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	CString stmp;
	//stmp.Format(_T("Test:ID = %d :    m_pBuffRecv[8,9,10] =  %d, %d,  %d"), ID_Ithres_Pwr_Sys,  m_pBuffRecv[8],  m_pBuffRecv[9], m_pBuffRecv[10]);
	//AfxMessageBox(stmp);


	float Ithres_PwrSys = 0;// gia tri nguong dong bao ve he thong
	uint16_t data16bit = 0;

	if ((nRet < 8) || (m_pBuffRecv[2] != CMD_READ_THRES_I))
		return -1;
	else
	{
		data16bit = (m_pBuffRecv[9] << 8) + m_pBuffRecv[10];
		if (m_pBuffRecv[8] == 0)
		{
			convert_16bitToFoat(data16bit, FACTOR_SCALER_0P001, 1.0, &Ithres_PwrSys);
			//stmp.Format(_T("Test Convert: ID = %d :    Ithres_PwrSys = %.3f"), ID_Ithres_Pwr_Sys, Ithres_PwrSys);
			//AfxMessageBox(stmp);
		}
		else if (m_pBuffRecv[8] == 1) convert_16bitToFoat(data16bit, FACTOR_SCALER_0P001, -1.0, &Ithres_PwrSys);
		else return -1;

		//stmp.Format(_T("Test trước khi update: ID = %d :    Ithres_PwrSys = %.3f"), ID_Ithres_Pwr_Sys, Ithres_PwrSys );
		//AfxMessageBox(stmp);

		switch (ID_Ithres_Pwr_Sys)
		{
		case ID_I_Thres_PwrSys_3V3_1: { I_max_3v_temp_1 = Ithres_PwrSys; break;}
		case ID_I_Thres_PwrSys_3V3_2: { I_max_3v_temp_2 = Ithres_PwrSys; break;}
		case ID_I_Thres_PwrSys_5V: {mTestCase.mSupply_Get.Imax_5v = Ithres_PwrSys; break;}
		case ID_I_Thres_PwrSys_12V: {mTestCase.mSupply_Get.Imax_12v = Ithres_PwrSys; break;}

		case ID_I_Thres_PwrSys_12V_N: {mTestCase.mSupply_Get.Imax_12v_N = Ithres_PwrSys; break;}
		case ID_I_Thres_PwrSys_12V_CPU: {mTestCase.mSupply_Get.Imax_12v_CPU = Ithres_PwrSys; break;}
		case ID_I_Thres_PwrSys_12V_RL_1: { I_max_12V_Relay_temp_1 = Ithres_PwrSys; break;}
		case ID_I_Thres_PwrSys_12V_RL_2: { I_max_12V_Relay_temp_2 = Ithres_PwrSys; break;}
		case ID_I_Thres_PwrSys_30V: {mTestCase.mSupply_Get.Imax_30v = Ithres_PwrSys; break;}

		default: Ithres_PwrSys = 0; break;
		}
	}

	return 0;    // 0: OK,		 -1: ERROR
}




// cac ham thiet lap tham so bao ve nguon
int CPlan::Set_UThres_HV_Protect_M7A(byte ID_UThres_HV_Pwr_Sys) {
//	// ID nguong dien ap bao ve cho nguon cao ap: khi dien ap cao ap nho hon, hoac cao hon dien ap nay he thong de ngay va khong cho hoat dong
//#define ID_UThres_HV_Pwr_Sys_30V			1
//#define ID_UThres_HV_Pwr_Sys_12V_Relay	2


	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];
	byte num_bytes_payload = 4;  // so byte payload
	byte Buff_tx[SIZE_MAX_BUFF_RX_SERIAL];

	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; 			// ADDR_PC
	Buff_tx[1] = ADDR_M7_A; 	// ADDR_Mi
	Buff_tx[2] = 0x07; 			// set up U nguong sys protect: HV

	if ((ID_UThres_HV_Pwr_Sys >= 1) && (ID_UThres_HV_Pwr_Sys <=  2))
		Buff_tx[3] = ID_UThres_HV_Pwr_Sys;			// ma nguon dang can thiet lap
	else return -1;

	Buff_tx[4] = 0x00;

	Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
	Buff_tx[6] = (VERSION_FW & 0x00FF);



	num_bytes_payload = 4;
	Buff_tx[7] = num_bytes_payload;		// length of payload

	float Uthres_PwrSys_HV_Down = 0;	// gia tri nguong bao ve duoi
	float Uthres_PwrSys_HV_Up = 0;		// gia tri nguong bao ve tren

	switch (ID_UThres_HV_Pwr_Sys)
	{
	case ID_UThres_HV_Pwr_Sys_30V: 
	{
		Uthres_PwrSys_HV_Down = mTestCase.mSupply_Set.U30v_DOWN;
		Uthres_PwrSys_HV_Up = mTestCase.mSupply_Set.U30v_UP;
		break;
	}
	case ID_UThres_HV_Pwr_Sys_12V_Relay:
	{
		Uthres_PwrSys_HV_Down = mTestCase.mSupply_Set.U12v_DOWN;
		Uthres_PwrSys_HV_Up = mTestCase.mSupply_Set.U12v_UP;
		break;
	}

	default:  break;
	}

	uint16_t data16bit = 0;
	if ((Uthres_PwrSys_HV_Down > 0.01) && (Uthres_PwrSys_HV_Up > 0.01))    // de phat hien truong hop khong co case nao thoa man
	{
		data16bit = convert_FloatTo16bit(Uthres_PwrSys_HV_Down, FACTOR_SCALER_0P001);
		Buff_tx[8 + 0] = (data16bit & 0xFF00) >> 8;
		Buff_tx[8 + 1] = data16bit & 0x00FF;

		data16bit = convert_FloatTo16bit(Uthres_PwrSys_HV_Up, FACTOR_SCALER_0P001);
		Buff_tx[8 + 2] = (data16bit & 0xFF00) >> 8;
		Buff_tx[8 + 3] = data16bit & 0x00FF;
	}
	else return -1;

	// gui cho device: 
	int len_Tx = num_bytes_payload + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;

}




// cac ham thiet lap tham so bao ve nguon
int CPlan::Get_UThres_HV_Protect_M7A(byte ID_UThres_HV_Pwr_Sys) {
	//	// ID nguong dien ap bao ve cho nguon cao ap: khi dien ap cao ap nho hon, hoac cao hon dien ap nay he thong de ngay va khong cho hoat dong
	//#define ID_UThres_HV_Pwr_Sys_30V			1
	//#define ID_UThres_HV_Pwr_Sys_12V_Relay	2


	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];
	byte num_bytes_payload = 0;  // so byte payload
	byte Buff_tx[SIZE_MAX_BUFF_RX_SERIAL];

	// cho phep board Active
	// header
	Buff_tx[0] = ADDR_PC; 			// ADDR_PC
	Buff_tx[1] = ADDR_M7_A; 	// ADDR_Mi
	Buff_tx[2] = CMD_READ_THRES_UHV; 			// read U nguong sys protect: HV

	if ((ID_UThres_HV_Pwr_Sys == 1) || (ID_UThres_HV_Pwr_Sys == 2))
		Buff_tx[3] = ID_UThres_HV_Pwr_Sys;			// ma nguon dang can thiet lap
	else return -1;

	Buff_tx[4] = 0x00;

	Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
	Buff_tx[6] = (VERSION_FW & 0x00FF);



	num_bytes_payload = 0;
	Buff_tx[7] = num_bytes_payload;		// length of payload


	// gui cho device: 
	int len_Tx = num_bytes_payload + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	float Uthres_PwrSys = 0;// gia tri nguong dien ap bao ve he thong
	uint16_t data16bit;

	if ((nRet != 12) || (m_pBuffRecv[2] != CMD_READ_THRES_UHV))
	{
		AfxMessageBox(_T("LỖI: lỗi Đọc ngưỡng U_HV bảo vệ nguồn"));
		return -1;
	}
	else
	{
		if (ID_UThres_HV_Pwr_Sys == ID_UThres_HV_Pwr_Sys_12V_Relay)
		{
			data16bit = (m_pBuffRecv[8] << 8) + m_pBuffRecv[9];
			convert_16bitToFoat(data16bit, FACTOR_SCALER_0P001, 1.0, &mTestCase.mSupply_Get.U12v_DOWN);

			data16bit = (m_pBuffRecv[10] << 8) + m_pBuffRecv[11];
			convert_16bitToFoat(data16bit, FACTOR_SCALER_0P001, 1.0, &mTestCase.mSupply_Get.U12v_UP);
		}
		else if (ID_UThres_HV_Pwr_Sys == ID_UThres_HV_Pwr_Sys_30V)
		{
			data16bit = (m_pBuffRecv[8] << 8) + m_pBuffRecv[9];
			convert_16bitToFoat(data16bit, FACTOR_SCALER_0P001, 1.0, &mTestCase.mSupply_Get.U30v_DOWN);

			data16bit = (m_pBuffRecv[10] << 8) + m_pBuffRecv[11];
			convert_16bitToFoat(data16bit, FACTOR_SCALER_0P001, 1.0, &mTestCase.mSupply_Get.U30v_UP);
		}
	}

	return 0;    // 0: OK,   -1: error
}






// cac ham thiet lap tham so bao ve nguon
int CPlan::Get_Pwr_Info(byte ADDR_BOARD, byte *dlength, byte *data_RX) {
// nhan du lieu ve tham so nguon hien tai tren cac board


	byte m_pBuffRecv[SIZE_MAX_BUFF_RX_SERIAL];
	byte num_bytes_payload = 0;  // so byte payload
	byte Buff_tx[SIZE_MAX_BUFF_RX_SERIAL];

	// cho phep board Active
	// header
	Buff_tx[0] = 0x00; 			// ADDR_PC
	Buff_tx[1] = ADDR_BOARD; 	// ADDR_Mi
	Buff_tx[2] = 0x04; 			// read trang thai nguon cua cac board

	Buff_tx[4] = 0x00;

	Buff_tx[5] = (VERSION_FW & 0xFF00) >> 8;			// Ver FW: 1.0
	Buff_tx[6] = (VERSION_FW & 0x00FF);



	num_bytes_payload = 0;
	Buff_tx[7] = num_bytes_payload;		// length of payload


	// gui cho device: 
	int len_Tx = num_bytes_payload + 8;
	//	PackageSerial(ADDR_PC, ADDR_Board, CMD_WRITE_PARAM, SUB_CMD_PARAM_DATA_8POWERS, VERSION_FW, lenth_payload, mchar, PkgData);
	int nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);


	if (nRet < 8) { *dlength = 0;  return -1; }
	else
	{
		*dlength = nRet - 8;
		for (int i = 0; i < *dlength; i++)  data_RX[i] = m_pBuffRecv[8 + i];
	}

	return 1; // 1: 0k,  -1: loi
}













// ########################################################################################
// analog channels

void CPlan::Process_setting_Analog_Channels(void)
{
	/*
	* Ham nay xu ly tao ra co so du lieu truoc khi cau hinh. co 3 ma tran quan trong
	* I.	ma tran dinh tuyen cho M2_Sig_1[41], chi so co y nghia tu 1..40: chon 4 chan trong (1..40)  Bus_chung noi voi MAIN dau vao M4 (1..4)/8 
	*		ma tran dinh tuyen cho M2_Sig_2[41], chi so co y nghia tu 1..40: chon 4 chan trong (41..80) Bus_chung noi voi MAIN dau vao M4 (5..8)/8 
	* 
	*	M2_Sig_1[i] = {0: open,  0xA1, 0xA2, 0xA3, 0xA4}: cho cac kenh 1.. 40
	*	M2_Sig_2[i] = {0: open,  0xA5, 0xA6, 0xA7, 0xA8}: cho cac kenh 41..80
	* 
	* II. ma tran M4_CM_Arr[8] de noi 8 Bus_chung noi voi MAIN dau vao M4 (1..8)/8 voi kenh Analog chuc nang can chon
	*
	*	MODE = 1
	*	gia tri moi M4_CM_Arr[0]: 0: open, k: noi ADC 1 voi bus dau vao chung k ( k = 1..8), others = open
	*	gia tri moi M4_CM_Arr[1]: 0: open, k: noi ADC 2 voi bus dau vao chung k ( k = 1..8), others = open
	*	gia tri moi M4_CM_Arr[2]: 0: open, k: noi DAC 1 voi bus dau vao chung k ( k = 1..8), others = open
	*	gia tri moi M4_CM_Arr[3]: 0: open, k: noi DAC 1 voi bus dau vao chung k ( k = 1..8), others = open
	*	
	*	MODE = 2
	*	gia tri moi M4_CM_Arr[4]: 0: open, k: noi HV_IN 1 voi bus dau vao chung k ( k = 1..8), others = open
	*	gia tri moi M4_CM_Arr[5]: 0: open, k: noi HV_IN 1 voi bus dau vao chung k ( k = 1..8), others = open
	*	gia tri moi M4_CM_Arr[6]: 0: open, k: noi BNC 1 voi bus dau vao chung   k ( k = 1..8), others = open
	*	gia tri moi M4_CM_Arr[7]: 0: open, k: noi BNC 1 voi bus dau vao chung   k ( k = 1..8), others = open
	* 
	* 
	* III. ma tran noi bus chung cua M4 voi BUS chung cua MAIN: M4_CM_RL_CONNECT_TO_MAIN[8]
	*  M4_CM_RL_CONNECT_TO_MAIN[i] = 0: open/ 1: connect ; bus chung thu i M4 voi MAIN





		//// ................................................................................................................................
		//// Ma tran chuyen mach 8x8 cua M4
		//uint8_t M4_ADDA_CM_Arr[8];     //		 1: ket noi voi BUS 1, 2: knoi voi BUS 2, ...., 8: ket noi voi BUS 8. Tuy nhien phan bo co dinh nhu sau:
		//// vi tri:[0..7]  <==> ADC1, ADC2, DAC1. DAC2, HV1, HV2, BNC1, BNC2
		// co 2 mode: 1 thoi diem cho co 1 mode!

		// TH1: MODE = 1:  ADC,DAC
		////gia tri:
		////  0/ 4 : only for ADC_1
		////  1/ 5 : only for ADC_2
		////  2/ 6 : only for DAC_1
		////  3/ 7 : only for DAC_

		MODE = 2: kenh HV, EXT_BNC
		////gia tri:
		////  0/ 4 : only for HV_IN 1
		////  1/ 5 : only for HV_IN 2
		////  2/ 6 : only for EXT_BNC 1: dự phòng
		////  3/ 7 : only for EXT_BNC 2: dự phòng


2


		//// ma tran chuyen mach noi M4 voi Main M7
		//uint8_t M4_CM_RL_CONNECT_TO_MAIN[8];     //   1: connect,   0: unconnect

		//// ma tran danh dau cac kenh dau vao M4 da duoc su dung
		//uint8_t M4_ADDA_Arr_Used[8];   // 0: khong su dung. 1: da su dung


		//// ma tran thong tin dinh tuyen cho M2_Sig
		//uint8_t M2_SIG_RL_Data_1[41];   // 0/1/2/3/4   : tai 1 hoi diem chi c
		//uint8_t M2_SIG_RL_Data_2[41];   // 0/1/2/3/4
	*/


	// ===> sTEP 1:  RESET ALL DATA TO DEFAULT
	for (int k = 0; k < 8; k++)
	{
		M4_CM_RL_CONNECT_TO_MAIN[k] = 0;
		//M4_Arr_Used[k] = 0;  
		M4_CM_Arr[k] = 0;
	}

	for (int k = 0; k < 41; k++)
	{
		M2_SIG_RL_Data_1[k] = 0;
		M2_SIG_RL_Data_2[k] = 0;
	}


	// ===> sTEP 2: tao mang du lieu ve cau hinh cho tung chan: tong hop du lieu cau hinh tu config Pins và config cho giao dien set up analog
	byte Config_Pins_for_Analogs_Arr[81];
	for (int k = 1; k < 81; k++)
	{	
		Config_Pins_for_Analogs_Arr[k] = 0;    // xoa truoc 

		if (mTestCase.mTestCaseConfig.ChanelConfigArr[k] == 0x00)  // chua duoc thiet lap thuoc tinh
		{
			if (mTestCase.ExtChanel_Set.ADC_in1.nChanel == k) Config_Pins_for_Analogs_Arr[k] = BUS_PROPERTY_ADC1;
			else if (mTestCase.ExtChanel_Set.ADC_in2.nChanel == k) Config_Pins_for_Analogs_Arr[k] = BUS_PROPERTY_ADC2;
			else if (mTestCase.ExtChanel_Set.DAC_out1.nChanel == k) Config_Pins_for_Analogs_Arr[k] = BUS_PROPERTY_DAC1;
			else if (mTestCase.ExtChanel_Set.DAC_out2.nChanel == k) Config_Pins_for_Analogs_Arr[k] = BUS_PROPERTY_DAC2;
		
			//else if (mTestCase.ExtChanel_Set.HV_in1.nChanel == k) Config_Pins_for_Analogs_Arr[k] = BUS_PROPERTY_HIVOLTAGE_IN1;
			//else if (mTestCase.ExtChanel_Set.HV_in2.nChanel == k) Config_Pins_for_Analogs_Arr[k] = BUS_PROPERTY_HIVOLTAGE_IN2;
		}
	}



	

// ===> STEP 3:  xu ly tinh toan gia ma tran thiet lap dinh tuyen relay cho M2_SIG va M4_ADDDA_BUF
	


// ____________ 2. set up chuyen mach cho ADC/ DAC     __________________
	
	byte thuoctinh_pin_tmp = 0x00;

			for (int i = 1; i <= 80; i++)
			{
				thuoctinh_pin_tmp = Config_Pins_for_Analogs_Arr[i];
				if ((thuoctinh_pin_tmp == BUS_PROPERTY_ADC1) && (mTestCase.ExtChanel_Set.ADC_in1.used == 1))
					if (i <= 40)      // M2_SIG_0: adc1 gan voi BUS 1
					{
						M4_CM_Arr[0] = 0x01;
						M4_CM_RL_CONNECT_TO_MAIN[0] = 1;
						M2_SIG_RL_Data_1[i] = 0xA1 + 0;
					}
					else if (i > 40)   // M2_SIG_1: adc1 gan voi BUS 5 
					{
						M4_CM_Arr[0] = 0x05;
						M4_CM_RL_CONNECT_TO_MAIN[4] = 1;
						M2_SIG_RL_Data_2[i] = 0xA1 + 4;
					}
					else;

				if ((thuoctinh_pin_tmp == BUS_PROPERTY_ADC2) && (mTestCase.ExtChanel_Set.ADC_in2.used == 1)) // adc2 gan voi BUS 2
					if (i <= 40)
					{
						M4_CM_Arr[1] = 0x02;
						M4_CM_RL_CONNECT_TO_MAIN[1] = 1;
						M2_SIG_RL_Data_1[i] = 0xA1 + 1;
					}
					else if (i > 40)    // adc2 gan voi BUS 6
					{
						M4_CM_Arr[1] = 0x06;
						M4_CM_RL_CONNECT_TO_MAIN[5] = 1;
						M2_SIG_RL_Data_2[i] = 0xA1 + 5;
					}
					else;

				if ((thuoctinh_pin_tmp == BUS_PROPERTY_DAC1) && (mTestCase.ExtChanel_Set.DAC_out1.used == 1))  //DAC 1 gan voi BUS 3
					if (i <= 40)
					{
						M4_CM_Arr[2] = 0x03;
						M4_CM_RL_CONNECT_TO_MAIN[2] = 1;
						M2_SIG_RL_Data_1[i] = 0xA1 + 2;
					}
					else if (i > 40)   //DAC 1 gan voi BUS 7
					{
						M4_CM_Arr[2] = 0x07;
						M4_CM_RL_CONNECT_TO_MAIN[6] = 1;
						M2_SIG_RL_Data_2[i] = 0xA1 + 6;
					}
					else;


				if ((thuoctinh_pin_tmp == BUS_PROPERTY_DAC2) && (mTestCase.ExtChanel_Set.DAC_out2.used == 1))
					if (i <= 40) //DAC 2 gan voi BUS 4
					{
						M4_CM_Arr[3] = 0x04;
						M4_CM_RL_CONNECT_TO_MAIN[3] = 1;
						M2_SIG_RL_Data_1[i] = 0xA1 + 3;
					}
					else if (i > 40)  //DAC 2 gan voi BUS 8
					{
						M4_CM_Arr[3] = 0x08;
						M4_CM_RL_CONNECT_TO_MAIN[7] = 1;
						M2_SIG_RL_Data_2[i] = 0xA1 + 7;
					}
					else;
			}

}


int CPlan::Set_Paths_M2_SIG_i(byte ADDR_Board) { // thiet lap  M4_A /  M4_B
	byte m_pBuffRecv[1024];
	byte num_bytes = 40;  // so byte payload
	byte Buff_tx[1024];
	// cho phep board Active
	// header
	Buff_tx[0] = ADDR_PC; 			// ADDR_PC
	if ((ADDR_Board == ADDR_M2SIG_0) || (ADDR_Board == ADDR_M2SIG_1))
		Buff_tx[1] = ADDR_Board; 	// ADDR_Mi
	else return 0;   // error
	Buff_tx[2] = 0x09; 			// reset matrix
	Buff_tx[3] = 0x01;			// du lieu ma tran relays
	Buff_tx[4] = 0x00;

	Buff_tx[5] = VERSION_FW >> 8; 		// H		// Ver FW: 1.0
	Buff_tx[6] = VERSION_FW & 0x00FF;   // L


	num_bytes = 40;  // so byte  == so dau ra: DB50 / M1_i
	Buff_tx[7] = num_bytes;			// length of payload

	for (int i = 1; i <= 40; i++)
	{
		if (ADDR_Board == ADDR_M2SIG_0) Buff_tx[7 + i] = M2_SIG_RL_Data_1[i];
		else if (ADDR_Board == ADDR_M2SIG_1) Buff_tx[7 + i] = M2_SIG_RL_Data_2[i];
	}


	// send to M2_Sig
	int len_Tx = num_bytes + 8;
	int nRet = -1;
	nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;

}



// code cho M2_Sig
int CPlan::Set_Paths_M2_SIG(void)
{
	int nret;
	CString stmp;

	nret = Set_Paths_M2_SIG_i(ADDR_M2SIG_0);
	if (nret < 8)
	{
		// thong bao loi
		stmp.Format(_T("LỖI: Set_Paths_M2_SIG_i [%d] "), ADDR_M2SIG_0 - 0x4A);
		AfxMessageBox(stmp);
		return -1;
	}


	Sleep(500);
	nret = Set_Paths_M2_SIG_i(ADDR_M2SIG_1);
	if (nret < 8)
	{
		// thong bao loi
		stmp.Format(_T("LỖI: Set_Paths_M2_SIG_i [%d] "), ADDR_M2SIG_1 - 0x4A);
		AfxMessageBox(stmp);
		return -1;
	}

	Sleep(500);
	nret = Start_Apply_Relay(ADDR_M2SIG_0);
	if (nret < 8)
	{
		// thong bao loi
		stmp.Format(_T("LỖI: Start_Apply_Relay [%d] "), ADDR_M2SIG_0 - 0x4A);
		AfxMessageBox(stmp);
		return -1;
	}


	Sleep(500);
	nret = Start_Apply_Relay(ADDR_M2SIG_1);
	if (nret < 8)
	{
		// thong bao loi
		stmp.Format(_T("LỖI: Start_Apply_Relay [%d] "), ADDR_M2SIG_1 - 0x4A);
		AfxMessageBox(stmp);
		return -1;
	}



	return 1;  // 1: 0k.    -1: error
}



int CPlan::Set_Paths_M4_ADDA_BUFF(void)
{
	// cau hinh cac chuyen mach cho M4
	byte m_pBuffRecv[1024];
	byte num_bytes = 16;  // so byte payload: 8 byte chuyen mach 8x8 + 8 byte connect to main
	byte Buff_tx[1024];
	// cho phep board Active
	// header
	Buff_tx[0] = ADDR_PC; 				// ADDR_PC
	Buff_tx[1] = ADDR_M4_0; 		// ADDR_Mi
	Buff_tx[2] = 0x09; 				// set param
	Buff_tx[3] = 0x01;				// du lieu ma tran relays
	Buff_tx[4] = 0x00;

	Buff_tx[5] = VERSION_FW >> 8; 		// H		// Ver FW: 1.0
	Buff_tx[6] = VERSION_FW & 0x00FF;   // L

	num_bytes = 16;				// so byte  == 8 byte dau: thong tin ma tran 8x8   + 8 byte relays connect to main
	Buff_tx[7] = num_bytes;		// length of payload

	// add 8 first bytes for matrix 8x8
	for (int i = 0; i < 8; i++)
		Buff_tx[8 + i] = M4_CM_Arr[i];

	// add 8 second bytes for connector to Main
	for (int i = 0; i < 8; i++)
		Buff_tx[16 + i] = M4_CM_RL_CONNECT_TO_MAIN[i];

	// send to M2_Sig
	int len_Tx = num_bytes + 8;
	int nRet = -1;

	nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);
	return nRet;
}

int CPlan::Set_Param_M4_HV_Out(void)
{
	// cau hinh tham so cho 2 kenh HV_out cua M4
	byte m_pBuffRecv[1024];
	byte num_bytes = 6;  // 3 byte cho 1 kenh; ON.OFF_1  | Vout_1 | ON.OFF_2  | Vout_2
	byte Buff_tx[1024];
	float HV_Value;
	uint16_t data_16bit;
	// header
	Buff_tx[0] = 0x00; 				// ADDR_PC
	Buff_tx[1] = ADDR_M4_0; 		// ADDR_Mi

	Buff_tx[2] = 0x09; 				// set param 
	Buff_tx[3] = 0x03;				// du lieu set up tham so kenh ra HV_Out: max = 80V
	Buff_tx[4] = 0x00;

	Buff_tx[5] = VERSION_FW >> 8; 		// H		// Ver FW: 1.0
	Buff_tx[6] = VERSION_FW & 0x00FF;   // L

	num_bytes = 6;				// ON_OFF_1 , Vout_1, ON_OFF_2, Vout_2
	Buff_tx[7] = num_bytes;		// length of payload

	// set up HV_out_1
	if (mTestCase.ExtChanel_Set.HV_out1.used != 0)
	{
		Buff_tx[8] = 0x01;		// HV_Out_1 = ON
		HV_Value = mTestCase.ExtChanel_Set.HV_out1.value;
	}
	else
	{
		Buff_tx[8] = 0x00;		// HV_Out_1 = OFF
		HV_Value = 0;
	}
	data_16bit = convert_FloatTo16bit(HV_Value, FACTOR_SCALER_0P01);  // moi them define: #define FACTOR_SCALER_0P01		0.01
	Buff_tx[9] = (data_16bit >> 8) & 0x00FF;
	Buff_tx[10] = data_16bit & 0x00FF;

	// set up HV_out_2
	if (mTestCase.ExtChanel_Set.HV_out2.used != 0)
	{
		Buff_tx[11] = 0x01;		// HV_Out_2 = ON
		HV_Value = mTestCase.ExtChanel_Set.HV_out2.value;
	}
	else
	{
		Buff_tx[11] = 0x00;		// HV_Out_2 = OFF
		HV_Value = 0;
	}
	data_16bit = convert_FloatTo16bit(HV_Value, FACTOR_SCALER_0P01);  // moi them define: #define FACTOR_SCALER_0P01		0.01
	Buff_tx[12] = (data_16bit >> 8) & 0x00FF;
	Buff_tx[13] = data_16bit & 0x00FF;

	// PC send to M4
	int len_Tx = num_bytes + 8;
	int nRet = -1;
	nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);
	return nRet;
}


int CPlan::Set_Param_M4_HV_In(void)
{
	// cau hinh tham so cho 2 kenh HV_in cua M4
	byte m_pBuffRecv[1024];
	byte num_bytes = 8;  // 2 byte; 1 byte ON.OFF, Vin max, Vin_nguong, 
	float HV_Value;
	byte Buff_tx[1024];

	uint16_t data_16bit;
	// header
	Buff_tx[0] = 0x00; 				// ADDR_PC
	Buff_tx[1] = ADDR_M4_0; 		// ADDR_Mi

	Buff_tx[2] = 0x09; 				// set param
	Buff_tx[3] = 0x04;				// du lieu set up tham so kenh vao HV_In. Vin max = 300V
	Buff_tx[4] = 0x00;

	Buff_tx[5] = VERSION_FW >> 8; 		// H		// Ver FW: 1.0
	Buff_tx[6] = VERSION_FW & 0x00FF;   // L

	num_bytes = 10;				// ON_OFF_1 , Vpp_Scaler_1, Vnguong_1,      ON_OFF_2 , Vpp_Scaler_2, Vnguong_2
	Buff_tx[7] = num_bytes;		// length of payload



	float Vin_HV_High_temp;
	uint16_t data16;
	float N_temp;
	float HV_in_nguong_temp;

	// HV_in_1
	if (mTestCase.ExtChanel_Set.HV_in1.used == 1)
		Buff_tx[8 + 0] = 0x01;		// HV_In_1 = ON
	else Buff_tx[8 + 0] = 0x00;		// HV_In_1 = OFF

	Vin_HV_High_temp = mTestCase.ExtChanel_Set.HV_in1.value;
	if (Vin_HV_High_temp > 300.0) Vin_HV_High_temp = 300;
	if (Vin_HV_High_temp < 0.0) Vin_HV_High_temp = 0;

	if (mTestCase.ExtChanel_Set.HV_in1.used != 1)   // OFF
		Vin_HV_High_temp = 5.0;		// dung cho tao nguong so sanh cao, khong tao xung bởi nhiễu đưa vào

	data16 = convert_FloatTo16bit(Vin_HV_High_temp, FACTOR_SCALER_0P01);

	Buff_tx[8 + 1] = (data16 >> 8) & 0x00FF;
	Buff_tx[8 + 2] = data16 & 0x00FF;

	// tinh toan nguong
	//HV_in_nguong_temp = mTestCase.ExtChanel_Set.HV_in1.Vnguong;
	HV_in_nguong_temp = Vin_HV_High_temp / 2;        // mac dinh nguong so sanh 0/1 la 50% dien ap thiet lap max dau vao

	if (HV_in_nguong_temp > 300.0) HV_in_nguong_temp = 300;
	if (HV_in_nguong_temp < 0.0) HV_in_nguong_temp = 0;

	data16 = convert_FloatTo16bit(HV_in_nguong_temp, FACTOR_SCALER_0P01);
	Buff_tx[8 + 3] = (data16 >> 8) & 0x00FF;
	Buff_tx[8 + 4] = data16 & 0x00FF;



	// HV_in_2
	if (mTestCase.ExtChanel_Set.HV_in2.used == 1)
		Buff_tx[8 + 5] = 0x01;		// HV_In_2 = ON
	else Buff_tx[8 + 5] = 0x00;		// HV_In_2 = OFF

	Vin_HV_High_temp = mTestCase.ExtChanel_Set.HV_in2.value;
	if (Vin_HV_High_temp > 300.0) Vin_HV_High_temp = 300;
	else if (Vin_HV_High_temp < 0.0) Vin_HV_High_temp = 0;

	data16 = convert_FloatTo16bit(Vin_HV_High_temp, FACTOR_SCALER_0P01);

	Buff_tx[8 + 6] = (data16 >> 8) & 0x00FF;
	Buff_tx[8 + 7] = data16 & 0x00FF;

	// tinh toan nguong
	//HV_in_nguong_temp = mTestCase.ExtChanel_Set.HV_in2.Vnguong;
	HV_in_nguong_temp = Vin_HV_High_temp / 2.0;        // mac dinh nguong so sanh 0/1 la 50% dien ap thiet lap max dau vao

	if (HV_in_nguong_temp > 300.0) HV_in_nguong_temp = 300;
	else if (HV_in_nguong_temp < 0.0) HV_in_nguong_temp = 0;

	if (mTestCase.ExtChanel_Set.HV_in2.used != 1)   // OFF
		Vin_HV_High_temp = 5.0;		// dung cho tao nguong so sanh cao, khong tao xung bởi nhiễu đưa vào



	data16 = convert_FloatTo16bit(HV_in_nguong_temp, FACTOR_SCALER_0P01);
	Buff_tx[8 + 8] = (data16 >> 8) & 0x00FF;
	Buff_tx[8 + 9] = data16 & 0x00FF;

	// PC send to M4
	int len_Tx = num_bytes + 8;
	int nRet = -1;
	nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);
	return nRet;
}

int CPlan::Set_Param_M4_ADC_In(void) // tu Vin_max ham se tinh ra scaler va gui xuong cho tbi
{

	// cau hinh tham so cho 2 kenh ADC_in cua M4
	byte m_pBuffRecv[1024];
	byte num_bytes = 8;  // 2 byte; 1 byte ON.OFF, Vin max, Vin_nguong, 
	byte Buff_tx[1024];

	uint16_t data_16bit;
	// header
	Buff_tx[0] = 0x00; 				// ADDR_PC
	Buff_tx[1] = ADDR_M4_0; 		// ADDR_Mi

	Buff_tx[2] = 0x09; 				// set param
	Buff_tx[3] = 0x05;				// du lieu set up ADC_In. Vin max = 300V
	Buff_tx[4] = 0x00;

	Buff_tx[5] = VERSION_FW >> 8; 		// H		// Ver FW: 1.0
	Buff_tx[6] = VERSION_FW & 0x00FF;   // L

	num_bytes = 6;				// ON_OFF_1 , Vpp_max 1,      ON_OFF_2, Vpp_max_2
	Buff_tx[7] = num_bytes;		// length of payload



	float Vppin_max_temp;
	uint16_t Scaler_ADC = 0;


	// ADC1
	if (mTestCase.ExtChanel_Set.ADC_in1.used == 1)
		Buff_tx[8 + 0] = 0x01;		// ADC_1 = ON
	else Buff_tx[8 + 0] = 0x00;		// ADC_1 = OFF

	Vppin_max_temp = mTestCase.ExtChanel_Set.ADC_in1.value;
	if (Vppin_max_temp > 300.0) Vppin_max_temp = 300;
	if (Vppin_max_temp < 0.0) Vppin_max_temp = 0;


	// tinh toan ra he so chia gui xong cho M4
	//tin hieu dau vao cho ADC la Fullsale: -1 ... + 1 (V).
	// muc DC offset = 0.04 V (khi cho dau vao == GND)
	if (Vppin_max_temp <= 1.0) Scaler_ADC = 1;
	else if (Vppin_max_temp <= 10.0) Scaler_ADC = 10;
	else if (Vppin_max_temp <= 100.0) Scaler_ADC = 100;
	else Scaler_ADC = 1000;

	//data_16bit = convert_FloatTo16bit(Vppin_max_temp, FACTOR_SCALER_0P01);
	Buff_tx[8 + 1] = (Scaler_ADC >> 8) & 0x00FF;
	Buff_tx[8 + 2] = Scaler_ADC & 0x00FF;



	// ADC2
	if (mTestCase.ExtChanel_Set.ADC_in2.used == 1)
		Buff_tx[8 + 3] = 0x01;		// ADC_2 = ON
	else Buff_tx[8 + 3] = 0x00;		// ADC_2 = OFF

	Vppin_max_temp = mTestCase.ExtChanel_Set.ADC_in2.value;
	if (Vppin_max_temp > 300.0) Vppin_max_temp = 300;
	if (Vppin_max_temp < 0.0) Vppin_max_temp = 0;

	// tinh toan ra he so chia gui xong cho M4
	if (Vppin_max_temp <= 2.0) Scaler_ADC = 1;
	else if (Vppin_max_temp <= 20.0) Scaler_ADC = 10;
	else if (Vppin_max_temp <= 200.0) Scaler_ADC = 100;
	else Scaler_ADC = 1000;

	//data_16bit = convert_FloatTo16bit(Vppin_max_temp, FACTOR_SCALER_0P01);
	Buff_tx[8 + 4] = (Scaler_ADC >> 8) & 0x00FF;
	Buff_tx[8 + 5] = Scaler_ADC & 0x00FF;



	// PC send to M4
	int len_Tx = num_bytes + 8;
	int nRet = -1;
	nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	return nRet;


}





void CPlan::M4_reset_EXT_IO_Dir(void)
{
	mTestCase.ExtChanel_Set.EXT_io1.used = 0; //  dont use
	mTestCase.ExtChanel_Set.EXT_io1.IN_OUT = 0; // input

	mTestCase.ExtChanel_Set.EXT_io2.used = 0; //  dont use
	mTestCase.ExtChanel_Set.EXT_io2.IN_OUT = 0; // input
}


int CPlan::Set_DIR_EXT_IO(void)  // thiet lap chieu IN/OUT cho 2 kenh do mong rong 5V
{
	// cau hinh chieu vao ra cho 2 kenh moi rong: EXT_IO_1,2
	byte m_pBuffRecv[1024];
	byte num_bytes = 2;  //  IN: 0   OUT: 1  ( kenh 1 | Kenh 2)
	byte Buff_tx[1024];

	uint16_t data_16bit;
	// header
	Buff_tx[0] = 0x00; 				// ADDR_PC
	Buff_tx[1] = ADDR_M4_0; 		// ADDR_Mi

	Buff_tx[2] = 0x09; 				// set param 
	Buff_tx[3] = 0x06;				// chieu vao ra kenh do mo rong: EXT_IO
	Buff_tx[4] = 0x00;

	Buff_tx[5] = VERSION_FW >> 8; 		// H		// Ver FW: 1.0
	Buff_tx[6] = VERSION_FW & 0x00FF;   // L

	num_bytes = 2;				//  IN: 0   OUT: 1  ( kenh 1 | Kenh 2)
	Buff_tx[7] = num_bytes;		// length of payload

	// set up HV_out_1
	if (mTestCase.ExtChanel_Set.EXT_io1.used == 0) Buff_tx[8] = 0x00;   // dont used = input
	else
	{
		if (mTestCase.ExtChanel_Set.EXT_io1.IN_OUT == 0) //     ......... dang nham muc logic qui dinh IN/OUT. Dung: 0: in, 1:out
			Buff_tx[8]	= 0x00; // input dir on M4
		else Buff_tx[8] = 0x01; // Output dir on M4
	}

	// set up HV_out_2
	if (mTestCase.ExtChanel_Set.EXT_io2.used == 0) Buff_tx[9] = 0x00;   // dont used = input
	else
	{
		if (mTestCase.ExtChanel_Set.EXT_io2.IN_OUT == 0) //     ......... dang nham muc logic qui dinh IN/OUT. Dung: 0: in, 1:out
			Buff_tx[9] = 0x00; // input dir on M4
		else Buff_tx[9] = 0x01; // Output dir on M4
	}
	// PC send to M4
	int len_Tx = num_bytes + 8;
	int nRet = -1;
	nRet = my_uart_send_data((char*)Buff_tx, len_Tx, (char*)m_pBuffRecv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);
	return nRet;
}


int CPlan::Set_Param_M4_ADDA_BUFF(void)
{
	int nRet = -1;
	// thiet lap tham so cho 2 kenh HV_OUT
	// Vout: 3..80 V
	// ON/OFF

	nRet = Set_Paths_M4_ADDA_BUFF();
	if (nRet < 8) return -1;
	Sleep(1000);
	nRet = Start_Apply_Relay(ADDR_M4_0);
	if (nRet < 8) return -1;
	Sleep(1000);
	nRet = Set_Param_M4_HV_Out();
	if (nRet < 8) return -1;


	// thiet lap tham so cho 2 kenh HV_IN
	// V_Scaler: ==> V nam trong khoang 0...3V . Chon cac he so sau: 1 (1/1), 10 (1:10), 100 (1/100), 1000 (1/1000)
	// nguong so sanh mac dinh 50%
	// ON/OFF
	Sleep(1000);
	nRet = Set_Param_M4_HV_In();
	if (nRet < 8) return -1;

	// thiet lap tham so cho 2 kenh ADC_IN
	// Vpp_Scaler: 1 (1/1), 10 (1:10), 100 (1/100), 1000 (1/1000)
	// ON/OFF
	Sleep(1000);
	nRet = Set_Param_M4_ADC_In();
	if (nRet < 8) return -1;
	// kenh kenh DAC: khong can thiet lap: da fixed tham so tren phan cung voi Gain = 3


	// bo cac kenh mo rong: EXT_IO
	//// set huong EXT_IO_1,2
	//Sleep(1000);
	//nRet = Set_DIR_EXT_IO();
	//if (nRet < 8) return -1;


	else return 0;
}








int CPlan::SetUp_I_Thres_8Power(POWERS_STRUCT m_8Power, char* pData_receiv, int* plenData_receiv) { //Max lenData_receiv = SIZE_MAX_BUFF_RX_SERIAL


	int m_nRet;
	int lenth_payload = 16;
	char mchar[64];   // 8 nguon ,moi nguon 2 tham so: he so ti le : 0.001 doi voi dong
	byte PkgData[SIZE_MAX_BUFF_RX_SERIAL];
	int32_t data16bit;
	//----------------
	POWER_STRUCT mPowers[9];
	for (int i = 1; i <= 8; i++) mPowers[i] = m_8Power.POWER[i];

	//---------------

	for (int i = 1; i <= 8; i++) {
		// nguon 
		data16bit = convert_FloatTo16bit(mPowers[i].ImaxSet, FACTOR_SCALER_0P001);
		mchar[(i - 1) * 2 + 0] = (data16bit & 0xFF00) >> 8;
		mchar[(i - 1) * 2 + 1] = data16bit & 0x00FF;
	}
	//-------------------------
	//CString tmpsrt;
	//tmpsrt.Format(_T("%ld"), data16bit);
	//MessageBox(tmpsrt, tmpsrt);
	//-------------------------
	//-------------------------
	//CString tmpsrt;
	//tmpsrt.Format(_T("%d   %d   %d"), mchar[0], mchar[1], mchar[2]);
	//MessageBox(tmpsrt, tmpsrt);
	//-------------------------


	// send to M3_0
	// dong goi goi tin
	PackageSerial(ADDR_PC, ADDR_M3_0, CMD_WRITE_PARAM, SUB_CMD_PARAM_ITHRESH_GEN_PWR, VERSION_FW, lenth_payload, mchar, PkgData);
	m_nRet = my_uart_send_data((char*)PkgData, lenth_payload + LENGTH_HEADER, pData_receiv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	if (m_nRet == -1)
	{
		AfxMessageBox(_T("LỖI: Thiết lập ngưỡng dòng bảo vệ nguồn M3_0 không thành công"));
		*plenData_receiv = 0;
		return -1;
	}
	else
	{
		//MessageBox(_T("Success!"), _T("Mess"));
		*plenData_receiv = m_nRet;
	}

	Sleep(1000);


	PackageSerial(ADDR_PC, ADDR_M3_1, CMD_WRITE_PARAM, SUB_CMD_PARAM_ITHRESH_GEN_PWR, VERSION_FW, lenth_payload, mchar, PkgData);
	m_nRet = my_uart_send_data((char*)PkgData, lenth_payload + LENGTH_HEADER, pData_receiv, SIZE_MAX_BUFF_RX_SERIAL, 3000, 3);

	if (m_nRet == -1)
	{
		AfxMessageBox(_T("LỖI: Thiết lập ngưỡng dòng bảo vệ nguồn M3_1 không thành công"));
		*plenData_receiv = 0;
		return -1;
	}
	else
	{
		//MessageBox(_T("Success!"), _T("Mess"));
		*plenData_receiv = m_nRet;
	}

	Sleep(500);   // delay cho board xu ly xong
	return 0;     // 0: OK,  -1 : error
}

