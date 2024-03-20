#pragma once

class CBerechnungen {
private:
	double l_dReturn;
public:
	double AdditionDurchfuehren(double *l_dWert1, double *l_dWert2);
	double SubtraktionDurchfuehren(double l_dWert1, double l_dWert2);
	double MultiplikationDurchfuehren(double l_dWert1, double l_dWert2);
	double DivisionDurchfuehren(double l_dWert1, double l_dWert2);
};
