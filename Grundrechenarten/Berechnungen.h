#pragma once

class CBerechnungen {
private:
	CString ErgebnisRunden(CString l_szZwischenErgebnis);
	CString NullenAbschneiden(CString l_szZwischenErgebnis);
	bool CheckFloatNumber(CString l_szNumber);
	bool CheckLength(CString l_szNumber);
	double l_dReturn = 0;
	CString l_szGetRundungsstelle = _T("");
	CString l_szGetErgebniswerte = _T("");
	int l_iRundungsstelle = 0;
	int l_iLength = 0;
	int GetRundungsstelle() const;

public:
	double AdditionDurchfuehren(double *l_dWert1, double *l_dWert2);
	double SubtraktionDurchfuehren(double l_dWert1, double l_dWert2);
	double MultiplikationDurchfuehren(double l_dWert1, double l_dWert2);
	double DivisionDurchfuehren(double l_dWert1, double l_dWert2);
	CString GetStringWert(CString l_szZwischenWert);
	double GetDoubleWert(CString l_szZwischenWert);
	CString GetErgebnis(double l_dZwischenWert, CString l_szZwischenWert);
	bool CheckForValidInput(CString l_szInput);
	void ShowWarning(CWnd* l_pWnd, int l_iShowFlag);
	void EnableBerechnungButtons(CWnd* l_pWndAddition, CWnd* l_pWndSubtraktion, CWnd* l_pWndMultiplikation, CWnd* l_pWndDivision, bool l_bEnableButton);
	void EnableSchreibenButton(CWnd* l_pWndSchreiben, bool l_bEnableButton);
};
