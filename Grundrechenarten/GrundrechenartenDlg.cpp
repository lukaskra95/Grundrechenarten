
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGrundrechenartenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EINGABE_OBEN, m_szEingabewertOben);
	DDX_Text(pDX, IDC_EDIT_EINGABE_UNTEN, m_szEingabewertUnten);
	DDX_Text(pDX, IDC_EDIT_ERGEBNIS, m_szErgebnis);
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
END_MESSAGE_MAP()


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

	m_pWndText = GetDlgItem(IDC_STATIC_WARNUNG_OBEN);
	m_pWndText->ShowWindow(SW_HIDE);

	m_pWndText = GetDlgItem(IDC_STATIC_WARNUNG_UNTEN);
	m_pWndText->ShowWindow(SW_HIDE);

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

CBerechnungen l_cBerechnungen;

void CGrundrechenartenDlg::OnClickedButtonAddieren()
{
	UpdateData(TRUE);

	m_szEingabewertOben = l_cBerechnungen.GetStringWert(m_szEingabewertOben);
	m_szEingabewertUnten = l_cBerechnungen.GetStringWert(m_szEingabewertUnten);

	double l_dEingabewertOben = l_cBerechnungen.GetDoubleWert(m_szEingabewertOben);
	double l_dEingabewertUnten = l_cBerechnungen.GetDoubleWert(m_szEingabewertUnten);
	double l_dErgebnis = l_cBerechnungen.AdditionDurchfuehren(&l_dEingabewertOben, &l_dEingabewertUnten);

	m_szErgebnis = l_cBerechnungen.GetErgebnis(l_dErgebnis, m_szErgebnis);

	UpdateData(FALSE);
}


void CGrundrechenartenDlg::OnClickedButtonSubtrahieren()
{
	UpdateData(TRUE);

	m_szEingabewertOben = l_cBerechnungen.GetStringWert(m_szEingabewertOben);
	m_szEingabewertUnten = l_cBerechnungen.GetStringWert(m_szEingabewertUnten);

	double l_dEingabewertOben = l_cBerechnungen.GetDoubleWert(m_szEingabewertOben);
	double l_dEingabewertUnten = l_cBerechnungen.GetDoubleWert(m_szEingabewertUnten);
	double l_dErgebnis = l_cBerechnungen.SubtraktionDurchfuehren(l_dEingabewertOben, l_dEingabewertUnten);

	m_szErgebnis = l_cBerechnungen.GetErgebnis(l_dErgebnis, m_szErgebnis);

	UpdateData(FALSE);
}


void CGrundrechenartenDlg::OnBnClickedButtonMultiplizieren()
{
	UpdateData(TRUE);

	m_szEingabewertOben = l_cBerechnungen.GetStringWert(m_szEingabewertOben);
	m_szEingabewertUnten = l_cBerechnungen.GetStringWert(m_szEingabewertUnten);

	double l_dEingabewertOben = l_cBerechnungen.GetDoubleWert(m_szEingabewertOben);
	double l_dEingabewertUnten = l_cBerechnungen.GetDoubleWert(m_szEingabewertUnten);
	double l_dErgebnis = l_cBerechnungen.MultiplikationDurchfuehren(l_dEingabewertOben, l_dEingabewertUnten);

	m_szErgebnis = l_cBerechnungen.GetErgebnis(l_dErgebnis, m_szErgebnis);

	UpdateData(FALSE);
}


void CGrundrechenartenDlg::OnBnClickedButtonDividieren()
{
	UpdateData(TRUE);

	m_szEingabewertOben = l_cBerechnungen.GetStringWert(m_szEingabewertOben);
	m_szEingabewertUnten = l_cBerechnungen.GetStringWert(m_szEingabewertUnten);

	double l_dEingabewertOben = l_cBerechnungen.GetDoubleWert(m_szEingabewertOben);
	double l_dEingabewertUnten = l_cBerechnungen.GetDoubleWert(m_szEingabewertUnten);
	double l_dErgebnis = l_cBerechnungen.DivisionDurchfuehren(l_dEingabewertOben, l_dEingabewertUnten);

	m_szErgebnis = l_cBerechnungen.GetErgebnis(l_dErgebnis, m_szErgebnis);

	UpdateData(FALSE);
}


void CGrundrechenartenDlg::OnChangeEditEingabeOben()
{
	GetDlgItemText(IDC_EDIT_EINGABE_OBEN,m_szEingabewertOben);
	m_pWndText = GetDlgItem(IDC_STATIC_WARNUNG_OBEN);
	m_pWndButtonAddition = GetDlgItem(IDC_BUTTON_ADDIEREN);
	m_pWndButtonSubtraktion = GetDlgItem(IDC_BUTTON_SUBTRAHIEREN);
	m_pWndButtonMultiplikation = GetDlgItem(IDC_BUTTON_MULTIPLIZIEREN);
	m_pWndButtonDivision = GetDlgItem(IDC_BUTTON_DIVIDIEREN);
	m_pWndButtonSchreiben = GetDlgItem(IDC_BUTTON_SCHREIBEN_OBEN);
	m_bValidInputOben = l_cBerechnungen.CheckForValidInput(m_szEingabewertOben);

	if (m_bValidInputOben)
	{
		l_cBerechnungen.ShowWarning(m_pWndText, SW_HIDE);
		l_cBerechnungen.EnableSchreibenButton(m_pWndButtonSchreiben, true);
	}
	else
	{
		l_cBerechnungen.ShowWarning(m_pWndText, SW_SHOW);
		l_cBerechnungen.EnableSchreibenButton(m_pWndButtonSchreiben, false);
	}
		

	if(m_bValidInputOben && m_bValidInputUnten)
	{
		l_cBerechnungen.EnableBerechnungButtons(m_pWndButtonAddition, m_pWndButtonSubtraktion, m_pWndButtonMultiplikation, m_pWndButtonDivision, true);
	}
	else
	{
		l_cBerechnungen.EnableBerechnungButtons(m_pWndButtonAddition, m_pWndButtonSubtraktion, m_pWndButtonMultiplikation, m_pWndButtonDivision, false);
	}
}


void CGrundrechenartenDlg::OnChangeEditEingabeUnten()
{
	GetDlgItemText(IDC_EDIT_EINGABE_UNTEN,m_szEingabewertUnten);
	m_pWndText = GetDlgItem(IDC_STATIC_WARNUNG_UNTEN);
	m_pWndButtonAddition = GetDlgItem(IDC_BUTTON_ADDIEREN);
	m_pWndButtonSubtraktion = GetDlgItem(IDC_BUTTON_SUBTRAHIEREN);
	m_pWndButtonMultiplikation = GetDlgItem(IDC_BUTTON_MULTIPLIZIEREN);
	m_pWndButtonDivision = GetDlgItem(IDC_BUTTON_DIVIDIEREN);
	m_pWndButtonSchreiben = GetDlgItem(IDC_BUTTON_SCHREIBEN_UNTEN);
	m_bValidInputUnten = l_cBerechnungen.CheckForValidInput(m_szEingabewertUnten);

	if (m_bValidInputUnten)
	{
		l_cBerechnungen.ShowWarning(m_pWndText, SW_HIDE);
		l_cBerechnungen.EnableSchreibenButton(m_pWndButtonSchreiben, true);
	}	
	else
	{
		l_cBerechnungen.ShowWarning(m_pWndText, SW_SHOW);
		l_cBerechnungen.EnableSchreibenButton(m_pWndButtonSchreiben, false);
	}
		

	if (m_bValidInputOben && m_bValidInputUnten)
	{
		l_cBerechnungen.EnableBerechnungButtons(m_pWndButtonAddition, m_pWndButtonSubtraktion, m_pWndButtonMultiplikation, m_pWndButtonDivision, true);
	}
	else
	{
		l_cBerechnungen.EnableBerechnungButtons(m_pWndButtonAddition, m_pWndButtonSubtraktion, m_pWndButtonMultiplikation, m_pWndButtonDivision, false);
	}
}

CFileOperationen l_cFileOperationen;
void CGrundrechenartenDlg::OnClickedButtonDateieinlesenOben()
{
	UpdateData(TRUE);
	
	l_szDesktopPath.LoadString(IDS_STRING_DESKTOPPATH);
	CString l_szDateiName = _T("Bsp2");
	l_szTxtDatei.LoadString(IDS_STRING_TXTDATEI);
	CString l_szPath = l_szDesktopPath + _T("\\") + l_szDateiName + l_szTxtDatei;
	//l_cFileOperationen.l_szReadFileValue = l_cFileOperationen.ReadFileValue(l_szPath);
	//m_szEingabewertLinks = l_cFileOperationen.l_szReadFileValue;
	CString l_szReadFile = l_cFileOperationen.ReadFileValue(l_szPath);
	l_cFileOperationen.SetReadFileValue(l_szReadFile);
	m_szEingabewertOben = l_cFileOperationen.GetReadFileValue();

	//SetDlgItemText(IDC_EDIT_EINGABELINKS,m_szEingabewertLinks);

	//if(m_szEingabewertRechts.IsEmpty())
	//	SetDlgItemText(IDC_EDIT_EINGABERECHTS, m_szEingabewertRechts);

	UpdateData(FALSE);
}


void CGrundrechenartenDlg::OnClickedButtonDateieinlesenUnten()
{
	UpdateData(TRUE);

	l_szDesktopPath.LoadString(IDS_STRING_DESKTOPPATH);
	CString l_szDateiName = _T("Bsp1");
	l_szTxtDatei.LoadString(IDS_STRING_TXTDATEI);
	CString l_szPath = l_szDesktopPath + _T("\\") + l_szDateiName + l_szTxtDatei;
	//l_cFileOperationen.l_szReadFileValue = l_cFileOperationen.ReadFileValue(l_szPath);
	//m_szEingabewertRechts = l_cFileOperationen.l_szReadFileValue;
	CString l_szReadFile = l_cFileOperationen.ReadFileValue(l_szPath);
	l_cFileOperationen.SetReadFileValue(l_szReadFile);
	m_szEingabewertUnten = l_cFileOperationen.GetReadFileValue();

	//SetDlgItemText(IDC_EDIT_EINGABERECHTS, m_szEingabewertRechts);

	//if (m_szEingabewertLinks.IsEmpty())
	//	SetDlgItemText(IDC_EDIT_EINGABELINKS, m_szEingabewertLinks);

	UpdateData(FALSE);
}


void CGrundrechenartenDlg::OnClickedButtonSchreibenOben()
{
	UpdateData(TRUE);

	l_szDesktopPath.LoadString(IDS_STRING_DESKTOPPATH);
	CString l_szDateiName = _T("Schreiben_Oberer_Wert");
	l_szTxtDatei.LoadString(IDS_STRING_TXTDATEI);
	CString l_szPath = l_szDesktopPath + _T("\\") + l_szDateiName + l_szTxtDatei;
	l_cFileOperationen.WriteFileValue(l_szPath, m_szEingabewertOben);

	UpdateData(FALSE);
}


void CGrundrechenartenDlg::OnClickedButtonSchreibenUnten()
{
	UpdateData(TRUE);

	l_szDesktopPath.LoadString(IDS_STRING_DESKTOPPATH);
	CString l_szDateiName = _T("Schreiben_Unterer_Wert");
	l_szTxtDatei.LoadString(IDS_STRING_TXTDATEI);
	CString l_szPath = l_szDesktopPath + _T("\\") + l_szDateiName + l_szTxtDatei;
	l_cFileOperationen.WriteFileValue(l_szPath, m_szEingabewertUnten);

	UpdateData(FALSE);
}