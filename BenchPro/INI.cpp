// IniFile.cpp: implementation of the CIniReader class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
//#include "Readini.h"
#include "INI.h"
#include <afxcoll.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



// Used to retrieve a value give the section and key
CString CIniReader::getKeyValue(const CString& strKey,const CString& strSection) const
{
	TCHAR ac_Result[255];
	// Get the info from the .ini file	
	if(GetPrivateProfileString((LPCTSTR)strSection,(LPCTSTR)strKey,_T(""),ac_Result, 255, (LPCTSTR)m_strFileName)>0)
		return CString(ac_Result);
	return CString(_T(""));
}

// Used to add or set a key value pair to a section
long CIniReader::setKey(const CString& strValue, const CString& strKey,const CString& strSection) const
{
	return WritePrivateProfileString (strSection, strKey,strValue, m_strFileName);
}

// Used to find out if a given section exists
BOOL CIniReader::sectionExists(const CString& strSection) const
{
	TCHAR ac_Result[100];	
	CString csAux;
	// Get the info from the .ini file	
	return (GetPrivateProfileString((LPCTSTR)strSection,NULL,_T(""),ac_Result, 90, (LPCTSTR)m_strFileName)>0);
}
BOOL CIniReader::removeSection(const CString& strSection) const
{
	 return (WritePrivateProfileString((LPCTSTR)strSection,NULL,NULL, (LPCTSTR)m_strFileName)>0);
}


// Used to retrieve all of the  section names in the ini file
CStringList* CIniReader::getSectionNames()  //returns collection of section names
{
	TCHAR ac_Result[2000];
	m_sectionList->RemoveAll();
	
	m_lRetValue = GetPrivateProfileSectionNames(ac_Result,2000,(LPCTSTR)m_strFileName);
	
	CString strSectionName;
	for(int i=0; i<m_lRetValue; i++)
	{
		if(ac_Result[i] != _T('\0')) {
			strSectionName = strSectionName + ac_Result[i];
		} else {
			if(strSectionName != _T("")) {
				m_sectionList->InsertAfter(m_sectionList->GetTailPosition(),strSectionName);
			}
			strSectionName = _T("");
		}
	}

	return m_sectionList;
}

// Used to retrieve all key/value pairs of a given section.  
CStringList* CIniReader::getSectionData(const CString& strSection)  
{
	TCHAR ac_Result[2000];  //change size depending on needs
	m_sectionDataList->RemoveAll();
	m_lRetValue = GetPrivateProfileSection((LPCTSTR)strSection, ac_Result, 2000, (LPCTSTR)m_strFileName);

	CString strSectionData;
	for(int i=0; i<m_lRetValue; i++)
	{
		if(ac_Result[i] != _T('\0')) {
			strSectionData = strSectionData + ac_Result[i];
		} else {
			if(strSectionData != _T("")) {
				m_sectionDataList->InsertAfter(m_sectionDataList->GetTailPosition(),strSectionData);
			}
			strSectionData = _T("");
		}
	}

	return m_sectionDataList;
}

void CIniReader::setINIFileName(const CString& strINIFile)
{
	m_strFileName = strINIFile;
	TCHAR pszINIFilePath[MAX_PATH];
	::GetModuleFileName(NULL, pszINIFilePath, MAX_PATH);
	::PathRemoveFileSpec(pszINIFilePath);
	if(m_strFileName.IsEmpty())
		::StrCat(pszINIFilePath, _T("\\Config.ini"));
	else
		::StrCat(pszINIFilePath, _T("\\")+ strINIFile);
	m_strFileName = pszINIFilePath;

	//LPTSTR pszSectionB = _T("[Config PLAN]");
	LPTSTR pszSectionB = _T("[StringTable]"); // section name with bracket 
	LPTSTR pszSection = _T("StringTable"); // section name without bracket
	LPTSTR pszKey = _T("String");
	LPTSTR pszValue=_T("Value");
	if(!::PathFileExists(pszINIFilePath))
	{
		// UTF16-LE BOM(FFFE)
		WORD wBOM = 0xFEFF;
		DWORD NumberOfBytesWritten;
		HANDLE hFile = ::CreateFile(pszINIFilePath, GENERIC_WRITE, 0, 
					   NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		::WriteFile(hFile, &wBOM, sizeof(WORD), &NumberOfBytesWritten, NULL);
		//::WriteFile(hFile, pszSectionB, (_tcslen(pszSectionB)+1)*(sizeof(TCHAR)), 
					//&NumberOfBytesWritten, NULL);
		::CloseHandle(hFile);
	}
	//setKey(pszValue,pszKey,pszSection);
	//removeSection(_T("Test01"));

	//WritePrivateProfileString(pszSection, pszKey, _T("+12B Сборос аварии"), pszINIFilePath);
}
int CIniReader::setTestCaseFileName(const CString& strTestCaseFile)
{
	m_strFileName = strTestCaseFile;

	LPTSTR pszSectionB = _T("[TEST CASE INFO]");
	//LPTSTR pszSectionB = _T("[StringTable]"); // section name with bracket 
	//LPTSTR pszSection = _T("StringTable"); // section name without bracket
	LPTSTR pszKey = _T("String");
	LPTSTR pszValue = _T("Value");
	if (!::PathFileExists(m_strFileName))
	{
		// UTF16-LE BOM(FFFE)
		WORD wBOM = 0xFEFF;
		DWORD NumberOfBytesWritten;
		HANDLE hFile = ::CreateFile(m_strFileName, GENERIC_WRITE, 0,
			NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		::WriteFile(hFile, &wBOM, sizeof(WORD), &NumberOfBytesWritten, NULL);
		//::WriteFile(hFile, pszSectionB, (_tcslen(pszSectionB) + 1) * (sizeof(TCHAR)),
		//	&NumberOfBytesWritten, NULL);
		::CloseHandle(hFile);
		return 0;
	}
	return 1;
}

/*
// Used to retrieve all of the  section names in the ini file
int CIniFile::GetSectionNames( CStringList* plistSectionNames )
{
	int nSize = 1000;
	long lRetValue = 0;
	TCHAR* pacReturnData = NULL;
	plistSectionNames->RemoveAll();

	do
	{
		delete [] pacReturnData;
		nSize *= 2;

		pacReturnData = new TCHAR[nSize];

		lRetValue = GetPrivateProfileSectionNames(pacReturnData, nSize, (LPCTSTR)m_strINiFileName);
	}
	while(lRetValue>=(nSize-2));

	TCHAR* pKey = pacReturnData;
	while( *pKey )
	{
		CString strData(pKey);

		if(!strData.IsEmpty())
			plistSectionNames->InsertAfter(plistSectionNames->GetTailPosition(), strData);

		// get next INi entry
		pKey += strlen( pKey ) + 1;
	}

	delete [] pacReturnData;
	return plistSectionNames->GetCount();
}

// Used to retrieve all key/value pairs of a given section.  
int CIniFile::GetSectionData( CString strSection, CStringList* plistSectionData )
{
	int nSize = 1000;
	long lRetValue = 0;
	TCHAR* pacReturnData = NULL;
	plistSectionData->RemoveAll();

	do
	{
		delete [] pacReturnData;
		nSize *= 2;

		pacReturnData = new TCHAR[nSize];
		lRetValue = GetPrivateProfileSection((LPCTSTR)strSection, pacReturnData, nSize, (LPCTSTR)m_strINiFileName);
	}
	while(lRetValue>=(nSize-2));

	TCHAR* pKey = pacReturnData;
	while( *pKey )
	{
		CString strData(pKey);

		if(!strData.IsEmpty())
			plistSectionData->InsertAfter(plistSectionData->GetTailPosition(), strData);

		// get next INi entry
		pKey += strlen( pKey ) + 1;
	}

	delete [] pacReturnData;

	return plistSectionData->GetCount();
}
*/