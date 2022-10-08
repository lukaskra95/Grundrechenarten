
// Grundrechenarten.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// Hauptsymbole


// CGrundrechenartenApp:
// Siehe Grundrechenarten.cpp für die Implementierung dieser Klasse
//

class CGrundrechenartenApp : public CWinApp
{
public:
	CGrundrechenartenApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CGrundrechenartenApp theApp;
