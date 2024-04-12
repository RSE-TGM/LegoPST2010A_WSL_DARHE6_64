// LgConcil.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LgConcil.h"
#include "LgConcilDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLgConcilApp

BEGIN_MESSAGE_MAP(CLgConcilApp, CWinApp)
	//{{AFX_MSG_MAP(CLgConcilApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLgConcilApp construction

CLgConcilApp::CLgConcilApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLgConcilApp object

CLgConcilApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLgConcilApp initialization

BOOL CLgConcilApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CLgConcilDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	return 0;
}
