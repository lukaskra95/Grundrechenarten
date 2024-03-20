#pragma once

class CDlgOperationen {
private:

public:
	void ShowWarning(CWnd* l_pWnd, int l_iShowFlag);
	void ChangeVisibilityButtons(CWnd* l_pWndAddition, CWnd* l_pWndSubtraktion, CWnd* l_pWndMultiplikation, CWnd* l_pWndDivision, bool l_bEnableButton);
	void EnableSchreibenButton(CWnd* l_pWndSchreiben, bool l_bEnableButton);
	void ChangeVisibilityButton(CWnd* l_pButton, bool l_bFlag);
	void SetFocus(CEdit* l_pText);
};