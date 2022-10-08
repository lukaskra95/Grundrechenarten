
// GrundrechenartenDlg.h: Headerdatei
//

#pragma once


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
	CString m_szEingabewertLinks;
	CString m_szEingabewertRechts;
	CString m_szErgebnis;
	afx_msg void OnChangeEditEingabelinks();
	afx_msg void OnChangeEditEingabeRechts();
	CString l_szDesktopPath;
	CString l_szTxtDatei;
	bool m_bValidInputRight = true;
	bool m_bValidInputLeft = true;
public:
	afx_msg void OnClickedButtonDateieinlesenLinks();
	afx_msg void OnClickedButtonDateieinlesenRechts();
	CWnd* m_pWndText;
	CWnd* m_pWndButtonAddition;
	CWnd* m_pWndButtonSubtraktion;
	CWnd* m_pWndButtonMultiplikation;
	CWnd* m_pWndButtonDivision;
	CWnd* m_pWndButtonSchreiben;
	afx_msg void OnClickedButtonSchreibenlinks();
	afx_msg void OnClickedButtonSchreibenrechts();
};
