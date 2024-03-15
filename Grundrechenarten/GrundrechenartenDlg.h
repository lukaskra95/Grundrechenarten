
// GrundrechenartenDlg.h: Headerdatei
//

#pragma once

#include <vector>


// CGrundrechenartenDlg-Dialogfeld
class CGrundrechenartenDlg : public CDialogEx
{
// Konstruktion
public:
	CGrundrechenartenDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRUNDRECHENARTEN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
private:
	afx_msg void OnClickedButtonAddieren();
	afx_msg void OnClickedButtonSubtrahieren();
	afx_msg void OnBnClickedButtonMultiplizieren();
	afx_msg void OnBnClickedButtonDividieren();
	CString m_szEingabewertOben;
	CString m_szEingabewertUnten;
	CString m_szErgebnis;
	afx_msg void OnChangeEditEingabeOben();
	afx_msg void OnChangeEditEingabeUnten();
	CString l_szDesktopPath;
	CString l_szTxtDatei;
	bool m_bValidInputUnten = true;
	bool m_bValidInputOben = true;
	CListBox m_liste;
	int l_iAddString;
	std::vector<CString> l_vWerte;
	
public:
	afx_msg void OnClickedButtonDateieinlesenOben();
	afx_msg void OnClickedButtonDateieinlesenUnten();
	CWnd* m_pWndText;
	CWnd* m_pWndButtonAddition;
	CWnd* m_pWndButtonSubtraktion;
	CWnd* m_pWndButtonMultiplikation;
	CWnd* m_pWndButtonDivision;
	CWnd* m_pWndButtonSchreiben;
	afx_msg void OnClickedButtonSchreibenOben();
	afx_msg void OnClickedButtonSchreibenUnten();
//	CString m_szPfadEinlesenOben;
//	CString m_szPfadEinlesenUnten;
//	CString m_szPfadSchreibenOben;
//	CString m_szPfadSchreibenUnten;
	CString m_szPfadEinlesenSchreiben;
	afx_msg void OnBnClickedButtonSpeichern();
};
