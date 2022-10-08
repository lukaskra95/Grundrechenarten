#include "pch.h"
#include "Berechnungen.h"
#include <string>
#include "GrundrechenartenDlg.h"

using namespace std;

enum Status {
	POSITIV,
	NEGATIV
};

Status l_eStatus;

int CBerechnungen::GetRundungsstelle() const
{
	return l_iRundungsstelle;
}

double CBerechnungen::AdditionDurchfuehren(double *l_dWert1, double *l_dWert2)
{
	if (l_dWert1 >= 0)
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
	unique_ptr<double> l_pWert1;
	l_pWert1 = make_unique<double>(l_dWert1);
	unique_ptr<double> l_pWert2;
	l_pWert2 = make_unique<double>(l_dWert2);
	//l_dReturn = l_dWert1 - l_dWert2;
	l_dReturn = *l_pWert1 - *l_pWert2;
	return l_dReturn;
}

double CBerechnungen::MultiplikationDurchfuehren(double l_dWert1, double l_dWert2)
{
	shared_ptr<double> l_pWert1;
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
	if (l_dWert2 == 0)
	{
		throw InvalidParameter();
	}

	l_dReturn = l_dWert1 / l_dWert2;
	return l_dReturn;
}

CString CBerechnungen::ErgebnisRunden(CString l_szZwischenErgebnis)
{
	l_szGetRundungsstelle = l_szZwischenErgebnis;
	l_szGetErgebniswerte = l_szZwischenErgebnis;
	l_szGetRundungsstelle.Delete(0, 6);
	l_szGetRundungsstelle.Delete(1, l_szGetRundungsstelle.GetLength() - 1);
	l_iRundungsstelle = _tstof(l_szGetRundungsstelle);
	l_szZwischenErgebnis.Delete(6, l_szZwischenErgebnis.GetLength() - 6);

	if (l_iRundungsstelle == 0)
	{
		l_szZwischenErgebnis = NullenAbschneiden(l_szZwischenErgebnis);
	}
	else if (l_iRundungsstelle > 0 && l_iRundungsstelle <= 4)
	{
		l_szZwischenErgebnis.Delete(6, l_szZwischenErgebnis.GetLength() - 6);
	}
	else if (l_iRundungsstelle > 4 && l_iRundungsstelle <= 9)
	{
		l_szZwischenErgebnis.SetAt(5, l_szGetErgebniswerte[5] + 1);
	}
	else
	{

	}

	return l_szZwischenErgebnis;
}

CString CBerechnungen::NullenAbschneiden(CString l_szZwischenErgebnis)
{
	l_iLength = l_szZwischenErgebnis.GetLength();
	for (int i = l_iLength - 1; i > 0; i--)
	{
		if (l_szZwischenErgebnis[i] == L'0')
		{
			l_szZwischenErgebnis.Delete(i);
		}
		else if (l_szZwischenErgebnis[i] == L'.')
		{
			l_szZwischenErgebnis.Delete(i);
			break;
		}
		else
		{
			break;
		}
	}

	return l_szZwischenErgebnis;
}

bool CBerechnungen::CheckFloatNumber(CString l_szNumber)
{
	if (l_szNumber.Find(_T(".")) == -1)
	{
		return false;
	}
	else
	{
		bool l_bLength = CheckLength(l_szNumber);
		return l_bLength;
	}

	return false;
}

bool CBerechnungen::CheckLength(CString l_szNumber)
{
	l_iLength = l_szNumber.GetLength();
	if (l_iLength > 5)
	{
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

CString CBerechnungen::GetStringWert(CString l_szZwischenWert)
{
	if (CheckFloatNumber(l_szZwischenWert))
	{
		l_szZwischenWert = ErgebnisRunden(l_szZwischenWert);
	}

	return l_szZwischenWert;
}

double CBerechnungen::GetDoubleWert(CString l_szZwischenWert)
{
	this->l_dReturn = _tstof(l_szZwischenWert);
	return l_dReturn;
}

CString CBerechnungen::GetErgebnis(double l_dZwischenWert, CString l_szZwischenWert)
{
	std::string l_szAdditionErgebnis = std::to_string(l_dZwischenWert);
	l_szZwischenWert = l_szAdditionErgebnis.c_str();
	l_szZwischenWert = NullenAbschneiden(l_szZwischenWert);

	return l_szZwischenWert;
}

bool CBerechnungen::CheckForValidInput(CString l_szInput)
{
	bool l_bValidInput = false;
	int l_iFindDots = 0;
	//if (l_szInput.IsEmpty())
	//{
		//return false;
		//l_pWndText->ShowWindow(SW_SHOW);
		//l_pWndAddition->EnableWindow(FALSE);
		//l_pWndSubtraktion->EnableWindow(FALSE);
		//l_pWndMultiplikation->EnableWindow(FALSE);
		//l_pWndDivision->EnableWindow(FALSE);
	//}

	for (int i = 0; i < l_szInput.GetLength(); i++)
	{
		if (isdigit(l_szInput[i]))
		{
			l_bValidInput = true;
			//l_pWndText->ShowWindow(SW_HIDE);
			//l_pWndAddition->EnableWindow(TRUE);
			//l_pWndSubtraktion->EnableWindow(TRUE);
			//l_pWndMultiplikation->EnableWindow(TRUE);
			//l_pWndDivision->EnableWindow(TRUE);
		}
		else
		{
			//l_pWndText->ShowWindow(SW_SHOW);
			//l_pWndAddition->EnableWindow(FALSE);
			//l_pWndSubtraktion->EnableWindow(FALSE);
			//l_pWndMultiplikation->EnableWindow(FALSE);
			//l_pWndDivision->EnableWindow(FALSE);
			l_bValidInput = false;
			if (l_szInput.GetAt(i) == L'.')
			{
				l_iFindDots++;
				if (l_iFindDots < 2)
					continue;
			}

			if (l_szInput.GetAt(i) == L'-')
			{
				if (i == 0)
					continue;
			}
			//return false;
			return l_bValidInput;
		}	
	}
	//return true;
	//l_bValidInput = true;
	return l_bValidInput;
}

void CBerechnungen::ShowWarning(CWnd * l_pWnd, int l_iShowFlag)
{
	l_pWnd->ShowWindow(l_iShowFlag);
}

void CBerechnungen::EnableBerechnungButtons(CWnd * l_pWndAddition, CWnd * l_pWndSubtraktion, CWnd * l_pWndMultiplikation, CWnd * l_pWndDivision, bool l_bEnableButton)
{
	l_pWndAddition->EnableWindow(l_bEnableButton);
	l_pWndSubtraktion->EnableWindow(l_bEnableButton);
	l_pWndMultiplikation->EnableWindow(l_bEnableButton);
	l_pWndDivision->EnableWindow(l_bEnableButton);
}

void CBerechnungen::EnableSchreibenButton(CWnd * l_pWndSchreiben, bool l_bEnableButton)
{
	l_pWndSchreiben->EnableWindow(l_bEnableButton);
}
