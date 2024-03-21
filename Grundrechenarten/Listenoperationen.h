#pragma once

#include <vector>

using namespace std;

class CListenoperationen {
private:
	vector<double> SelectionSort(vector<double> l_vDoubleVector);
	vector<double> BubbleSort(vector<double> l_vDoubleVector);
	vector<double> BubbleSort2(vector<double> l_vDoubleVector);
	vector<double> BubbleSort3(vector<double> l_vDoubleVector);
	vector<double> CountingSort(vector<double> l_vDoubleVector);
	vector<double> InsertionSort(vector<double> l_vDoubleVector);
	vector<double> InsertionSort2(vector<double> l_vDoubleVector);
public:
	vector<CString> WerteSortieren(vector<CString> l_vStringVector);
	void WerteErsetzen(CListBox* l_pListBox, vector<CString> l_vStringVector);
};
