#include "pch.h"
#include "Berechnungen.h"
#include <string>
#include "GrundrechenartenDlg.h"
#include "TextOperationen.h"

using namespace std;

enum Status {
	POSITIV,
	NEGATIV
};

Status l_eStatus; // Zum Testen

double CBerechnungen::AdditionDurchfuehren(double *l_dWert1, double *l_dWert2)
{
	if (l_dWert1 >= 0) // Kann das sinnvoll verwendet werden?
	{
		l_eStatus = Status::POSITIV;
	}
	else
	{
		l_eStatus = Status::NEGATIV;
	}

	l_dReturn = *l_dWert1 + *l_dWert2;
	return l_dReturn;
}

double CBerechnungen::SubtraktionDurchfuehren(double l_dWert1, double l_dWert2)
{
	unique_ptr<double> l_pWert1; // Pointer testen
	l_pWert1 = make_unique<double>(l_dWert1);
	unique_ptr<double> l_pWert2;
	l_pWert2 = make_unique<double>(l_dWert2);
	//l_dReturn = l_dWert1 - l_dWert2;
	l_dReturn = *l_pWert1 - *l_pWert2;
	return l_dReturn;
}

double CBerechnungen::MultiplikationDurchfuehren(double l_dWert1, double l_dWert2)
{
	shared_ptr<double> l_pWert1; // Pointer testen
	l_pWert1 = make_shared<double>(l_dWert1);
	shared_ptr<double> l_pWert2;
	l_pWert2 = make_shared<double>(l_dWert2);
	//l_dReturn = l_dWert1 * l_dWert2;
	l_dReturn = *l_pWert1 * *l_pWert2;
	return l_dReturn;
}

class InvalidParameter{};

double CBerechnungen::DivisionDurchfuehren(double l_dWert1, double l_dWert2)
{
	if (l_dWert2 == 0) // Division durch 0 abfangen
	{
		throw InvalidParameter();
	}

	l_dReturn = l_dWert1 / l_dWert2;
	return l_dReturn;
}