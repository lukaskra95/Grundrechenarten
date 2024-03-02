#include "FileOperationen.h"
#include <stdio.h>
#include <string>
#include "pch.h"
#include "Grundrechenarten.h"
#include <fstream>
#include <iostream>

#define CHARVALUE_SIZE 512
#define WCHARVALUE_SIZE 2048

using namespace std;

FILE* CFileOperationen::OpenFile(CString l_szPath)
{
	l_szMode.LoadString(IDS_STRING_READWRITEMODE);
	FILE* l_pOpenFile = _wfopen(l_szPath, l_szMode);
	return l_pOpenFile;
}

int CFileOperationen::CloseFile(FILE* l_pFile)
{
	int l_iCloseFile = fclose(l_pFile);
	return l_iCloseFile;
}

int CFileOperationen::ReadFile(CString l_szPath,char *l_cBuffer)
{
	FILE * l_pOpenFile = OpenFile(l_szPath);
	size_t l_iReadFile = fread(l_cBuffer, sizeof(char), 1000, l_pOpenFile);
	CloseFile(l_pOpenFile);

	return l_iReadFile;
}

CString CFileOperationen::CharToCString(char l_cChar)
{
	int l_iCountChars = MultiByteToWideChar(CP_UTF8, 0, &l_cChar, sizeof(char), NULL, 0);
	wchar_t* l_szConvertedValue = new wchar_t[l_iCountChars];
	MultiByteToWideChar(CP_UTF8, 0, &l_cChar, sizeof(char), l_szConvertedValue, l_iCountChars);
	CString l_szNewValue = l_szConvertedValue;
	delete[] l_szConvertedValue;

	return l_szNewValue;
}

CString CFileOperationen::ReadFileValue(CString l_szPath)
{
	std::ifstream myFile;
	myFile.open(l_szPath);
	string l_szInhalt; // Annahme, Datei hat nur eine Zeile
	getline(myFile, l_szInhalt);
	myFile.close();
	
	CString l_szNeuerInhalt = l_szInhalt.c_str();

	return l_szNeuerInhalt;
}

//CString CFileOperationen::ReadFileValue(CString l_szPath)
//{
//	char l_szBuffer[CHARVALUE_SIZE];
//	WCHAR	l_szBufferUTF16[WCHARVALUE_SIZE];
//
//	char* l_pBuffer = &l_szBuffer[0];
//	WCHAR*	l_pBufferUTF16 = &l_szBufferUTF16[0];
//
//	l_szMode.LoadString(IDS_STRING_READWRITEMODE);
//	l_pFileObject = _wfopen(l_szPath, _T("rb"));
//	if(!l_pFileObject)
//		return _T("");
//
//	//ZeroMemory(l_pBuffer, CHARVALUE_SIZE);
//	//ZeroMemory(l_pBufferUTF16, WCHARVALUE_SIZE);
//	CString l_szFileValue;
//	while(0 < fread(l_pBuffer, sizeof(l_pBuffer), 1000, l_pFileObject))
//	{
//		int l_iMultiByteToWideChar = MultiByteToWideChar(CP_UTF8, 0, l_pBuffer, CHARVALUE_SIZE, l_pBufferUTF16, 0);
//		MultiByteToWideChar(CP_UTF8, 0, l_pBuffer, CHARVALUE_SIZE, l_pBufferUTF16, l_iMultiByteToWideChar);
//
//		l_szFileValue = l_pBufferUTF16;
//
//		//ZeroMemory(l_pBuffer, CHARVALUE_SIZE);
//		//ZeroMemory(l_pBufferUTF16, WCHARVALUE_SIZE);
//	}
//	fflush(l_pFileObject);
//	fclose(l_pFileObject);
//
//	return l_szFileValue;
//}

CString CFileOperationen::ReadFileValue2(CString l_szPath) // Funktioniert noch nicht
{
	int l_iCharSize = 4;
	char* l_pNewChar = new char[l_iCharSize];
	CString l_szReadFileValue;

	l_szMode.LoadString(IDS_STRING_READWRITEMODE);
	l_pFileObject = _wfopen(l_szPath, l_szMode);
	//int l_iOpenFile = _tfopen_s(&l_pFileObject, _T("Bsp2"), l_szMode);

	//BYTE* l_eBOM = new BYTE[2];

	enum { BOM_KEINE, BOM_UTF8, BOM_UTF16 } l_eBOM = BOM_KEINE;

	if (l_eBOM == 0xEF && l_eBOM == 0xBB && l_eBOM == 0xBF)
	{
		l_eBOM = BOM_UTF8;
	}
	else if (l_eBOM == 0xFE && l_eBOM == 0xFF)
	{
		l_eBOM = BOM_UTF16;
	}
	else
	{

	}

	if (true/*l_eBOM == BOM_UTF8*/)
	{
		size_t test = fread(l_pNewChar, sizeof(l_pNewChar), 1000, l_pFileObject);
		while (true)
		{
			
			int l_iSize = MultiByteToWideChar(CP_UTF8, 0, l_pNewChar, l_iCharSize, NULL, 0);
			wchar_t* l_pNewWChar = new wchar_t[l_iSize];

			int l_iMulitByteToWideChar = MultiByteToWideChar(CP_UTF8, 0, l_pNewChar, l_iCharSize, l_pNewWChar, l_iSize);

			l_szReadFileValue = l_pNewWChar;
			//delete[] l_pNewChar;
			delete[] l_pNewWChar;

			int l_iSuccess = FilePointerVerschieben(l_pFileObject);
			if (l_iSuccess != 0)
				break;
		}

	}
	else if (l_eBOM == BOM_UTF16)
	{

	}

	return l_szReadFileValue;
}

void CFileOperationen::WriteFileValue(CString l_szPath, CString l_szWriteValue)
{
	std::ofstream myFile;
	myFile.open(l_szPath);

	//CStringA test = l_szWriteValue;
	//const char* writeValue = (CStringA) l_szWriteValue;

	size_t l_sLength = strlen((CStringA)l_szWriteValue);
	
	myFile.write((CStringA)l_szWriteValue, l_sLength);

	myFile.close();
}

void CFileOperationen::WriteFileValue2(CString l_szPath, CString l_szWriteValue) // Funktioniert, aber noch nicht perfekt
{
	l_szMode.LoadString(IDS_STRING_WRITEMODE);
	l_pFileObject = _wfopen(l_szPath, l_szMode);

	fwrite(l_szWriteValue, sizeof(wchar_t), l_szWriteValue.GetLength(), l_pFileObject);

	fflush(l_pFileObject);
	fclose(l_pFileObject);
}

void CFileOperationen::SetReadFileValue(CString l_szFileValue)
{
	l_szReadFileValue = l_szFileValue;
}

CString CFileOperationen::GetReadFileValue()
{
	return l_szReadFileValue;;
}

void CFileOperationen::ReturnToBeginning(FILE * l_pFile)
{
	fseek(l_pFile, 0, SEEK_SET);
}

int CFileOperationen::FilePointerVerschieben(FILE * l_pFile)
{
	int l_iSuccess = fseek(l_pFile, 0, SEEK_CUR);
	return l_iSuccess;
}