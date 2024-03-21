
// GrundrechenartenDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "Grundrechenarten.h"
#include "GrundrechenartenDlg.h"
#include "afxdialogex.h"
#include "Berechnungen.h"
#include <stdexcept>
#include "FileOperationen.h"
#include "Listenoperationen.h"
#include "TextOperationen.h"
#include "DlgOperationen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

// Implementierung
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGrundrechenartenDlg-Dialogfeld



CGrundrechenartenDlg::CGrundrechenartenDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRUNDRECHENARTEN_DIALOG, pParent)
	, m_szEingabewertOben(_T("0"))
	, m_szEingabewertUnten(_T("0"))
	, m_szErgebnis(_T(""))
	, m_szPfadEinlesenSchreiben(_T("C:\\Users\\lukas\\Desktop\\DateienGrundrechenarten\\")) // Wie wird benutzerdefinierter Pfad angezeigt?
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGrundrechenartenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EINGABE_OBEN, m_szEingabewertOben);
	DDX_Text(pDX, IDC_EDIT_EINGABE_UNTEN, m_szEingabewertUnten);
	DDX_Text(pDX, IDC_EDIT_ERGEBNIS, m_szErgebnis);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_PFADEINLESENSCHREIBEN, m_szPfadEinlesenSchreiben);
	DDX_Control(pDX, IDC_LIST_ZAHLENWERTE, m_liste);
}

BEGIN_MESSAGE_MAP(CGrundrechenartenDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADDIEREN, &CGrundrechenartenDlg::OnClickedButtonAddieren)
	ON_BN_CLICKED(IDC_BUTTON_SUBTRAHIEREN, &CGrundrechenartenDlg::OnClickedButtonSubtrahieren)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLIZIEREN, &CGrundrechenartenDlg::OnBnClickedButtonMultiplizieren)
	ON_BN_CLICKED(IDC_BUTTON_DIVIDIEREN, &CGrundrechenartenDlg::OnBnClickedButtonDividieren)
	ON_EN_CHANGE(IDC_EDIT_EINGABE_OBEN, &CGrundrechenartenDlg::OnChangeEditEingabeOben)
	ON_EN_CHANGE(IDC_EDIT_EINGABE_UNTEN, &CGrundrechenartenDlg::OnChangeEditEingabeUnten)
	ON_BN_CLICKED(IDC_BUTTON_DATEIEINLESEN_OBEN, &CGrundrechenartenDlg::OnClickedButtonDateieinlesenOben)
	ON_BN_CLICKED(IDC_BUTTON_DATEIEINLESEN_UNTEN, &CGrundrechenartenDlg::OnClickedButtonDateieinlesenUnten)
	ON_BN_CLICKED(IDC_BUTTON_SCHREIBEN_OBEN, &CGrundrechenartenDlg::OnClickedButtonSchreibenOben)
	ON_BN_CLICKED(IDC_BUTTON_SCHREIBEN_UNTEN, &CGrundrechenartenDlg::OnClickedButtonSchreibenUnten)
	ON_BN_CLICKED(IDC_BUTTON_SPEICHERN, &CGrundrechenartenDlg::OnBnClickedButtonSpeichern)
	ON_BN_CLICKED(IDC_BUTTON_SORTIEREN, &CGrundrechenartenDlg::OnBnClickedButtonSortieren)
END_MESSAGE_MAP()


CBerechnungen l_cBerechnungen; // TODO: Warum geht nicht Header?
CListenoperationen l_cListe;
CDlgOperationen l_cDlg;
CTextOperationen l_cText2;
CFileOperationen l_cFile;

// CGrundrechenartenDlg-Meldungshandler

BOOL CGrundrechenartenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen

	//GetDlgItem(IDC_STATIC_WARNUNG_OBEN)->ShowWindow(SW_HIDE);
	
	l_cDlg.ChangeVisibilityText(GetDlgItem(IDC_STATIC_WARNUNG_OBEN), SW_HIDE);
	l_cDlg.ChangeVisibilityText(GetDlgItem(IDC_STATIC_WARNUNG_UNTEN), SW_HIDE);
	//GetDlgItem(IDC_STATIC_WARNUNG_UNTEN)->ShowWindow(SW_HIDE);

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

void CGrundrechenartenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CGrundrechenartenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CGrundrechenartenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGrundrechenartenDlg::OnClickedButtonAddieren()
{
	UpdateData(TRUE);

	double l_dEingabewertOben = l_cText2.GetDoubleWert(m_szEingabewertOben);
	double l_dEingabewertUnten = l_cText2.GetDoubleWert(m_szEingabewertUnten);
	double l_dErgebnis = l_cBerechnungen.AdditionDurchfuehren(&l_dEingabewertOben, &l_dEingabewertUnten);

	m_szErgebnis = l_cText2.GetStringWert(l_dErgebnis);

	UpdateData(FALSE);
}


void CGrundrechenartenDlg::OnClickedButtonSubtrahieren()
{
	UpdateData(TRUE);

	double l_dEingabewertOben = l_cText2.GetDoubleWert(m_szEingabewertOben);
	double l_dEingabewertUnten = l_cText2.GetDoubleWert(m_szEingabewertUnten);
	double l_dErgebnis = l_cBerechnungen.SubtraktionDurchfuehren(l_dEingabewertOben, l_dEingabewertUnten);

	m_szErgebnis = l_cText2.GetStringWert(l_dErgebnis);

	UpdateData(FALSE);
}


void CGrundrechenartenDlg::OnBnClickedButtonMultiplizieren()
{
	UpdateData(TRUE);

	double l_dEingabewertOben = l_cText2.GetDoubleWert(m_szEingabewertOben);
	double l_dEingabewertUnten = l_cText2.GetDoubleWert(m_szEingabewertUnten);
	double l_dErgebnis = l_cBerechnungen.MultiplikationDurchfuehren(l_dEingabewertOben, l_dEingabewertUnten);

	m_szErgebnis = l_cText2.GetStringWert(l_dErgebnis);

	UpdateData(FALSE);
}


void CGrundrechenartenDlg::OnBnClickedButtonDividieren()
{
	UpdateData(TRUE);

	double l_dEingabewertOben = l_cText2.GetDoubleWert(m_szEingabewertOben);
	double l_dEingabewertUnten = l_cText2.GetDoubleWert(m_szEingabewertUnten);
	double l_dErgebnis = l_cBerechnungen.DivisionDurchfuehren(l_dEingabewertOben, l_dEingabewertUnten);

	m_szErgebnis = l_cText2.GetStringWert(l_dErgebnis);

	UpdateData(FALSE);
}


void CGrundrechenartenDlg::OnChangeEditEingabeOben()
{
	GetDlgItemText(IDC_EDIT_EINGABE_OBEN,m_szEingabewertOben);
	//m_pWndText = GetDlgItem(IDC_STATIC_WARNUNG_OBEN);
	//m_pWndButtonAddition = GetDlgItem(IDC_BUTTON_ADDIEREN);
	//m_pWndButtonSubtraktion = GetDlgItem(IDC_BUTTON_SUBTRAHIEREN);
	//m_pWndButtonMultiplikation = GetDlgItem(IDC_BUTTON_MULTIPLIZIEREN);
	//m_pWndButtonDivision = GetDlgItem(IDC_BUTTON_DIVIDIEREN);
	//m_pWndButtonSchreiben = GetDlgItem(IDC_BUTTON_SCHREIBEN_OBEN);
	m_bValidInputOben = l_cText2.CheckForValidInput(m_szEingabewertOben);

	if (m_bValidInputOben)
	{
		l_cDlg.ChangeVisibilityText(GetDlgItem(IDC_STATIC_WARNUNG_OBEN), SW_HIDE);
		l_cDlg.ChangeVisibilityButton(GetDlgItem(IDC_BUTTON_SCHREIBEN_OBEN), true);
	}
	else
	{
		l_cDlg.ChangeVisibilityText(GetDlgItem(IDC_STATIC_WARNUNG_OBEN), SW_SHOW);
		l_cDlg.ChangeVisibilityButton(GetDlgItem(IDC_BUTTON_SCHREIBEN_OBEN), false);
	}
		

	if(m_bValidInputOben && m_bValidInputUnten)
	{
		l_cDlg.ChangeVisibilityButtons(GetDlgItem(IDC_BUTTON_ADDIEREN), GetDlgItem(IDC_BUTTON_SUBTRAHIEREN),
			GetDlgItem(IDC_BUTTON_MULTIPLIZIEREN), GetDlgItem(IDC_BUTTON_DIVIDIEREN), true);
	}
	else
	{
		l_cDlg.ChangeVisibilityButtons(GetDlgItem(IDC_BUTTON_ADDIEREN), GetDlgItem(IDC_BUTTON_SUBTRAHIEREN),
			GetDlgItem(IDC_BUTTON_MULTIPLIZIEREN), GetDlgItem(IDC_BUTTON_DIVIDIEREN), false);
	}
}


void CGrundrechenartenDlg::OnChangeEditEingabeUnten()
{
	GetDlgItemText(IDC_EDIT_EINGABE_UNTEN,m_szEingabewertUnten);
	//m_pWndText = GetDlgItem(IDC_STATIC_WARNUNG_UNTEN);
	//m_pWndButtonAddition = GetDlgItem(IDC_BUTTON_ADDIEREN);
	//m_pWndButtonSubtraktion = GetDlgItem(IDC_BUTTON_SUBTRAHIEREN);
	//m_pWndButtonMultiplikation = GetDlgItem(IDC_BUTTON_MULTIPLIZIEREN);
	//m_pWndButtonDivision = GetDlgItem(IDC_BUTTON_DIVIDIEREN);
	//m_pWndButtonSchreiben = GetDlgItem(IDC_BUTTON_SCHREIBEN_UNTEN);
	m_bValidInputUnten = l_cText2.CheckForValidInput(m_szEingabewertUnten);

	if (m_bValidInputUnten)
	{
		l_cDlg.ChangeVisibilityText(GetDlgItem(IDC_STATIC_WARNUNG_UNTEN), SW_HIDE);
		l_cDlg.ChangeVisibilityButton(GetDlgItem(IDC_BUTTON_SCHREIBEN_UNTEN), true);
	}	
	else
	{
		l_cDlg.ChangeVisibilityText(GetDlgItem(IDC_STATIC_WARNUNG_UNTEN), SW_SHOW);
		l_cDlg.ChangeVisibilityButton(GetDlgItem(IDC_BUTTON_SCHREIBEN_UNTEN), false);
	}
		

	if (m_bValidInputOben && m_bValidInputUnten)
	{
		l_cDlg.ChangeVisibilityButtons(GetDlgItem(IDC_BUTTON_ADDIEREN), GetDlgItem(IDC_BUTTON_SUBTRAHIEREN),
			GetDlgItem(IDC_BUTTON_MULTIPLIZIEREN), GetDlgItem(IDC_BUTTON_DIVIDIEREN), true);
	}
	else
	{
		l_cDlg.ChangeVisibilityButtons(GetDlgItem(IDC_BUTTON_ADDIEREN), GetDlgItem(IDC_BUTTON_SUBTRAHIEREN),
			GetDlgItem(IDC_BUTTON_MULTIPLIZIEREN), GetDlgItem(IDC_BUTTON_DIVIDIEREN), false);
	}
}

void CGrundrechenartenDlg::OnClickedButtonDateieinlesenOben()
{
	UpdateData(TRUE);
	
	//l_szDesktopPath.LoadString(IDS_STRING_DESKTOPPATH);
	//CString l_szDateiName = _T("Bsp2");
	//l_szTxtDatei.LoadString(IDS_STRING_TXTDATEI);
	//CString l_szPath = l_szDesktopPath + _T("\\") + l_szDateiName + l_szTxtDatei;
	//CString l_szPath = m_szEinlesenOben;
	//l_cFileOperationen.l_szReadFileValue = l_cFileOperationen.ReadFileValue(l_szPath);
	//m_szEingabewertLinks = l_cFileOperationen.l_szReadFileValue;
	CString l_szReadFile = l_cFile.ReadFileValue(m_szPfadEinlesenSchreiben);
	l_cFile.SetReadFileValue(l_szReadFile);
	m_szEingabewertOben = l_cFile.GetReadFileValue();

	//SetDlgItemText(IDC_EDIT_EINGABELINKS,m_szEingabewertLinks);

	//if(m_szEingabewertRechts.IsEmpty())
	//	SetDlgItemText(IDC_EDIT_EINGABERECHTS, m_szEingabewertRechts);

	UpdateData(FALSE);
}


void CGrundrechenartenDlg::OnClickedButtonDateieinlesenUnten()
{
	UpdateData(TRUE);

	//l_szDesktopPath.LoadString(IDS_STRING_DESKTOPPATH);
	//CString l_szDateiName = _T("Bsp1");
	//l_szTxtDatei.LoadString(IDS_STRING_TXTDATEI);
	//CString l_szPath = l_szDesktopPath + _T("\\") + l_szDateiName + l_szTxtDatei;
	//l_cFileOperationen.l_szReadFileValue = l_cFileOperationen.ReadFileValue(l_szPath);
	//m_szEingabewertRechts = l_cFileOperationen.l_szReadFileValue;
	CString l_szReadFile = l_cFile.ReadFileValue(m_szPfadEinlesenSchreiben);
	l_cFile.SetReadFileValue(l_szReadFile);
	m_szEingabewertUnten = l_cFile.GetReadFileValue();

	//SetDlgItemText(IDC_EDIT_EINGABERECHTS, m_szEingabewertRechts);

	//if (m_szEingabewertLinks.IsEmpty())
	//	SetDlgItemText(IDC_EDIT_EINGABELINKS, m_szEingabewertLinks);

	UpdateData(FALSE);
}


void CGrundrechenartenDlg::OnClickedButtonSchreibenOben()
{
	UpdateData(TRUE);

	//l_szDesktopPath.LoadString(IDS_STRING_DESKTOPPATH);
	//CString l_szDateiName = _T("Schreiben_Oberer_Wert");
	//l_szTxtDatei.LoadString(IDS_STRING_TXTDATEI);
	//CString l_szPath = l_szDesktopPath + _T("\\") + l_szDateiName + l_szTxtDatei;
	l_cFile.WriteFileValue(m_szPfadEinlesenSchreiben, m_szEingabewertOben);

	UpdateData(FALSE);
}


void CGrundrechenartenDlg::OnClickedButtonSchreibenUnten()
{
	UpdateData(TRUE);

	l_szDesktopPath.LoadString(IDS_STRING_DESKTOPPATH);
	CString l_szDateiName = _T("Schreiben_Unterer_Wert");
	l_szTxtDatei.LoadString(IDS_STRING_TXTDATEI);
	CString l_szPath = l_szDesktopPath + _T("\\") + l_szDateiName + l_szTxtDatei;
	l_cFile.WriteFileValue(l_szPath, m_szEingabewertUnten);

	UpdateData(FALSE);
}

void CGrundrechenartenDlg::OnBnClickedButtonSpeichern()
{
	UpdateData(TRUE);

	l_iAddString = m_liste.AddString(m_szEingabewertOben);
	l_iAddString = m_liste.AddString(m_szEingabewertUnten);
	l_iAddString = m_liste.AddString(m_szErgebnis);
	
	l_vWerte.push_back(m_szEingabewertOben);
	l_vWerte.push_back(m_szEingabewertUnten);
	l_vWerte.push_back(m_szErgebnis);

	SetDlgItemText(IDC_EDIT_EINGABE_OBEN, _T("0"));
	SetDlgItemText(IDC_EDIT_EINGABE_UNTEN, _T("0"));
	//SetDlgItemText(IDC_EDIT_ERGEBNIS, _T("")); // TODO: Warum geht das nicht?
	m_szErgebnis = _T(""); 

	l_cDlg.SetFocus((CEdit*)GetDlgItem(IDC_EDIT_EINGABE_OBEN));
	l_cDlg.ChangeVisibilityButton(GetDlgItem(IDC_BUTTON_SORTIEREN),TRUE);
	
	UpdateData(FALSE);
}

void CGrundrechenartenDlg::OnBnClickedButtonSortieren()
{
	UpdateData(TRUE);

	l_vWerte = l_cListe.WerteSortieren(l_vWerte);
	l_cListe.WerteErsetzen(&m_liste, l_vWerte);

	SetDlgItemText(IDC_EDIT_EINGABE_OBEN, _T("0"));
	SetDlgItemText(IDC_EDIT_EINGABE_UNTEN, _T("0"));
	//SetDlgItemText(IDC_EDIT_ERGEBNIS, _T("")); // TODO: Warum geht das nicht?
	m_szErgebnis = _T("");

	l_cDlg.SetFocus((CEdit*)GetDlgItem(IDC_EDIT_EINGABE_OBEN));
	l_cDlg.ChangeVisibilityButton(GetDlgItem(IDC_BUTTON_SORTIEREN), FALSE);

	UpdateData(FALSE);
}