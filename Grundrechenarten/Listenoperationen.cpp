#include "pch.h"
#include "Listenoperationen.h"
#include "TextOperationen.h"
#include "GrundrechenartenDlg.h"
#include "Berechnungen.h"
#include <string>
#include <vector>

using namespace std;

CTextOperationen l_cText;

vector<CString> CListenoperationen::WerteSortieren(vector<CString> l_vListenWerte)
{
	vector<double> l_vDoubleVector = l_cText.GetDoubleVector(l_vListenWerte);
	//l_vDoubleVector = SelectionSort(l_vDoubleVector);
	//l_vDoubleVector = BubbleSort(l_vDoubleVector);
	l_vDoubleVector = InsertionSort(l_vDoubleVector);
	l_vListenWerte = l_cText.GetStringVector(l_vDoubleVector);

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
		double l_dZwischenSpeicher = l_vDoubleWerte[i];
		l_vDoubleWerte[i] = l_vDoubleWerte[mini];
		l_vDoubleWerte[mini] = l_dZwischenSpeicher;
	}

	return l_vDoubleWerte;
}

vector<double> CListenoperationen::BubbleSort(vector<double> l_vDoubleVector)
{
	bool l_bTausch = false;
	for (int i = 1; i < l_vDoubleVector.size(); i++) {
		if (l_vDoubleVector[i - 1] > l_vDoubleVector[i]) {
			double l_dZwischenSpeicher = l_vDoubleVector[i - 1];
			l_vDoubleVector[i - 1] = l_vDoubleVector[i];
			l_vDoubleVector[i] = l_dZwischenSpeicher;
			l_bTausch = true;
		}
	}

	if (l_bTausch)
		return BubbleSort(l_vDoubleVector);
	else
		return l_vDoubleVector;
}

vector<double> CListenoperationen::BubbleSort2(vector<double> l_vDoubleVector)
{
	bool l_bSortiert = false;
	while (!l_bSortiert) {
		l_bSortiert = true;
		for (int i = 1; i < l_vDoubleVector.size(); i++) {
			if (l_vDoubleVector[i - 1] > l_vDoubleVector[i]) {
				l_bSortiert = false;
				double l_dZwischenSpeicher = l_vDoubleVector[i - 1];
				l_vDoubleVector[i - 1] = l_vDoubleVector[i];
				l_vDoubleVector[i] = l_dZwischenSpeicher;
			}
		}
	}
	return l_vDoubleVector;
}

vector<double> CListenoperationen::BubbleSort3(vector<double> l_vDoubleVector)
{
	bool l_bTausch = true;
	for (int i = 0; i < l_vDoubleVector.size() && l_bTausch; i++) {
		l_bTausch = false;
		for (int k = 0; k < l_vDoubleVector.size() - i - 1; k++) {
			if (l_vDoubleVector[k] > l_vDoubleVector[k + 1]) {
				double l_dZwischenSpeicher = l_vDoubleVector[k];
				l_vDoubleVector[k] = l_vDoubleVector[k + 1];
				l_vDoubleVector[k + 1] = l_dZwischenSpeicher;
				l_bTausch = true;
			}
		}
	}
	return l_vDoubleVector;
}
// TODO
vector<double> CListenoperationen::CountingSort(vector<double> l_vDoubleVector) 
{
	int l_iMin = l_vDoubleVector[0]; // Geht nur bei ganzen Zahlen
	int l_iMax = l_vDoubleVector[0];
	for (int i = 0; i < l_vDoubleVector.size(); i++) {
		if (l_iMin < l_vDoubleVector[i]) {
			l_iMin = l_vDoubleVector[i];
		}
		if (l_iMax > l_vDoubleVector[i]) {
			l_iMax = l_vDoubleVector[i];
		}
	}
	int l_iGroesseVector = l_iMax - l_iMin + 1;
	vector<int> l_vZwischenVector;
	l_vZwischenVector.resize(l_iGroesseVector);

	for (int i = 0; i < l_iGroesseVector; i++) {
		if (i == l_vDoubleVector[i] && l_vDoubleVector.size() <= l_iGroesseVector) {
			l_vZwischenVector[i]++;
		}
	}

	for (int i = 0; i < l_iGroesseVector; i++) {
		l_vZwischenVector[i + 1] = l_vZwischenVector[i + 1] + l_vZwischenVector[i];
	}

	vector<double> l_vErgebnisVector;
	l_vErgebnisVector.resize(l_vDoubleVector.size());

	for (int i = 0; i < l_iGroesseVector; i++) {
		if (l_vDoubleVector.size() < l_iGroesseVector)
			break;
		else {
			l_vErgebnisVector[l_vZwischenVector[l_vDoubleVector[l_iGroesseVector - i - 1]]] = l_vDoubleVector[l_iGroesseVector - i - 1];
			l_vZwischenVector[l_vDoubleVector[l_iGroesseVector - i - 1]]--;
		}
			
	}

	return l_vErgebnisVector;
}

vector<double> CListenoperationen::InsertionSort(vector<double> l_vDoubleVector)
{
	for (int i = 1; i < l_vDoubleVector.size(); i++) {
		for (int k = i - 1; k >= 0; k--) {
			if (l_vDoubleVector[k + 1] < l_vDoubleVector[k]) {
				double l_dZwischenSpeicher = l_vDoubleVector[k];
				l_vDoubleVector[k] = l_vDoubleVector[k + 1];
				l_vDoubleVector[k + 1] = l_dZwischenSpeicher;
			}
		}
	}
	return l_vDoubleVector;
}

vector<double> CListenoperationen::InsertionSort2(vector<double> l_vDoubleVector)
{
	for (int i = 1; i < l_vDoubleVector.size(); i++) {
		if (l_vDoubleVector[i - 1] > l_vDoubleVector[i]) {
			int x = l_vDoubleVector[i];
			int k = i;
			for (; k > 0 && l_vDoubleVector[k - 1] > x; k--) {
				l_vDoubleVector[k] = l_vDoubleVector[k - 1];
			}
			l_vDoubleVector[k] = x;
		}
	}
	return l_vDoubleVector;
}
