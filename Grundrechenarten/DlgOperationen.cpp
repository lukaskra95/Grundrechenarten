#include "pch.h"
#include "DlgOperationen.h"
#include <string>
#include "GrundrechenartenDlg.h"

void CDlgOperationen::ShowWarning(CWnd * l_pWnd, int l_iShowFlag)
{
	l_pWnd->ShowWindow(l_iShowFlag);
}

void CDlgOperationen::ChangeVisibilityButtons(CWnd * l_pWndAddition, CWnd * l_pWndSubtraktion, CWnd * l_pWndMultiplikation, CWnd * l_pWndDivision, bool l_bEnableButton)
{
	l_pWndAddition->EnableWindow(l_bEnableButton);
	l_pWndSubtraktion->EnableWindow(l_bEnableButton);
	l_pWndMultiplikation->EnableWindow(l_bEnableButton);
	l_pWndDivision->EnableWindow(l_bEnableButton);
}

//void CDlgOperationen::EnableSchreibenButton(CWnd * l_pWndSchreiben, bool l_bEnableButton)
//{
//	l_pWndSchreiben->EnableWindow(l_bEnableButton);
//}

void CDlgOperationen::ChangeVisibilityButton(CWnd * l_pButton, bool l_bFlag)
{
	l_pButton->EnableWindow(l_bFlag);
}

void CDlgOperationen::SetFocus(CEdit * l_pText)
{
	l_pText->SetFocus();
	l_pText->SetSel(0, -1, 0);
}
