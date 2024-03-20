#include "pch.h"
#include "TextOperationen.h"
#include "Listenoperationen.h"
#include "GrundrechenartenDlg.h"
#include <string>
#include <vector>

using namespace std;

CString CTextOperationen::ErgebnisRunden(CString l_szZwischenErgebnis)
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

bool CTextOperationen::CheckLength(CString l_szNumber)
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

bool CTextOperationen::CheckFloatNumber(CString l_szNumber)
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

int CTextOperationen::GetRundungsstelle() const
{
	return l_iRundungsstelle;
}

//CString CTextOperationen::GetStringWert(CString l_szZwischenWert)
//{
//	if (CheckFloatNumber(l_szZwischenWert))
//	{
//		l_szZwischenWert = ErgebnisRunden(l_szZwischenWert);
//	}
//
//	return l_szZwischenWert;
//}

double CTextOperationen::GetDoubleWert(CString l_szZwischenWert)
{
	this->l_dReturn = _tstof(l_szZwischenWert);
	return l_dReturn;
}

bool CTextOperationen::CheckForValidInput(CString l_szInput)
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

CString CTextOperationen::NullenAbschneiden(CString l_szZwischenErgebnis)
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

CString CTextOperationen::GetStringWert(double l_dZwischenWert)
{
	string l_szAdditionErgebnis = to_string(l_dZwischenWert);
	CString l_szZwischenWert;
	l_szZwischenWert = (CString)l_szAdditionErgebnis.c_str();
	
	if (CheckFloatNumber(l_szZwischenWert))
	{
		l_szZwischenWert = ErgebnisRunden(l_szZwischenWert);
	}

	return l_szZwischenWert;
}

vector<double> CTextOperationen::GetDoubleVector(vector<CString> l_vStringVector)
{
	vector<double> l_vDoubleVector;
	for (int i = 0; i < l_vStringVector.size(); i++) {
		//l_vDoubleVector.push_back(_tstof(l_vStringVector[i]));
		l_vDoubleVector.push_back(GetDoubleWert(l_vStringVector[i]));
	}
		

	return l_vDoubleVector;
}

vector<CString> CTextOperationen::GetStringVector(vector<double> l_vDoubleVector)
{
	vector<CString> l_vStringVector;
	for (int i = 0; i < l_vDoubleVector.size(); i++) {
		//stringVector.push_back((CString)to_string(doubleVector[i]).c_str());
		l_vStringVector.push_back(GetStringWert(l_vDoubleVector[i]));
	}

	return l_vStringVector;
}