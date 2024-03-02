#pragma once

#include "afx.h"

class CFileOperationen {
private:
	FILE* OpenFile(CString l_szPath);
	int CloseFile(FILE* l_pFile);
	CString l_szMode;
	CString l_szReadFileValue;
	FILE* l_pFileObject;
public:
	int ReadFile(CString l_szPath, char *l_cBuffer);
	CString CharToCString(char l_cChar); // unvollständig
	CString ReadFileValue(CString l_szPath);
	CString ReadFileValue2(CString l_szPath); // unvollständig
	void WriteFileValue(CString l_szPath, CString l_szWriteValue);
	void WriteFileValue2(CString l_szPath, CString l_szWriteValue); // leicht fehlerbehaftet
	void SetReadFileValue(CString l_szFileValue);
	CString GetReadFileValue();
	void ReturnToBeginning(FILE* l_pFile);
	int FilePointerVerschieben(FILE* l_pFile);
};
