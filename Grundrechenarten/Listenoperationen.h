#pragma once

#include <vector>

using namespace std;

class CListenoperationen {
private:
	vector<double> SelectionSort(vector<double> l_vDoubleVector);
public:
	vector<CString> WerteSortieren(vector<CString> l_vStringVector);
	void WerteErsetzen(CListBox* l_pListBox, vector<CString> l_vStringVector);
};
