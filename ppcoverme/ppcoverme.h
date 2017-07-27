
// ppcoverme.h : main header file for the ppcoverme application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CppcovermeApp:
// See ppcoverme.cpp for the implementation of this class
//

class CppcovermeApp : public CWinApp
{
public:
	CppcovermeApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CppcovermeApp theApp;
