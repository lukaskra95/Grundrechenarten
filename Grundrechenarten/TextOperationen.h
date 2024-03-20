#pragma once

#include <vector>

using namespace std;

class CTextOperationen {
private:
	CString ErgebnisRunden(CString l_szZwischenErgebnis);
	int l_iLength = 0;
	bool CheckLength(CString l_szNumber);
	bool CheckFloatNumber(CString l_szNumber);
	double l_dReturn = 0;
	CString NullenAbschneiden(CString l_szZwischenErgebnis);
	CString l_szGetRundungsstelle = _T("");
	CString l_szGetErgebniswerte = _T("");
	int l_iRundungsstelle = 0;
	int GetRundungsstelle() const;
public:
	CString GetStringWert(double l_dZwischenWert);
	double GetDoubleWert(CString l_szZwischenWert);
	bool CheckForValidInput(CString l_szInput);
	//CString GetErgebnis(double l_dZwischenWert);
	vector<double> GetDoubleVector(vector<CString> l_vStringVector);
	vector<CString> GetStringVector(vector<double> l_vDoubleVector);
};