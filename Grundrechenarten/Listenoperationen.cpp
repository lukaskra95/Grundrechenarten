#include "pch.h"
#include "Listenoperationen.h"
#include "TextOperationen.h"
#include "GrundrechenartenDlg.h"
#include "Berechnungen.h"
#include <string>
#include <vector>

using namespace std;

CTextOperationen l_cTextOperationen2;

vector<CString> CListenoperationen::WerteSortieren(vector<CString> l_vListenWerte)
{
	vector<double> l_vDoubleVector = l_cTextOperationen2.GetDoubleVector(l_vListenWerte);
	l_vDoubleVector = SelectionSort(l_vDoubleVector);
	l_vListenWerte = l_cTextOperationen2.GetStringVector(l_vDoubleVector);

	return l_vListenWerte;
}

void CListenoperationen::WerteErsetzen(CListBox* l_pListBox, vector<CString> l_vListenWerte)
{
	for (int i = 0; i < (*l_pListBox).GetCount(); i++) {
		(*l_pListBox).DeleteString(0);
		(*l_pListBox).AddString(l_vListenWerte[i]);
	}
}

vector<double> CListenoperationen::SelectionSort(vector<double> l_vDoubleWerte)
{
	for (int i = 0; i < l_vDoubleWerte.size(); i++) {
		int mini = i;
		for (int k = i + 1; k < l_vDoubleWerte.size(); k++) {
			if (l_vDoubleWerte[mini] > l_vDoubleWerte[k]) {
				mini = k;
			}
		}
		int l_iZwischenSpeicher = l_vDoubleWerte[i];
		l_vDoubleWerte[i] = l_vDoubleWerte[mini];
		l_vDoubleWerte[mini] = l_iZwischenSpeicher;
	}

	return l_vDoubleWerte;
}