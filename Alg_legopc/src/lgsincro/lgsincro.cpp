// LgSincro.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LgSincro.h"
#include "PertDlg.h"
#include "SceltaDlg.h"
#include "LgSincroDlg.h"

extern bool sincok;
extern bool sinclocale;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CLgSincroApp

BEGIN_MESSAGE_MAP(CLgSincroApp, CWinApp)
	//{{AFX_MSG_MAP(CLgSincroApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLgSincroApp construction

CLgSincroApp::CLgSincroApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLgSincroApp object

CLgSincroApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLgSincroApp initialization

BOOL CLgSincroApp::InitInstance()
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
//CCommandLineInfo::ParseParam
/* LPCTSTR lpszParam;
BOOL bFlag=false;
BOOL bLast=false;

	CCommandLineInfo::ParseParam(  lpszParam,  bFlag,  bLast );

if (m_lpCmdLine[0] == '\0')
   {
      // Create a new (empty) document.
      OnFileNew();
   }
*/
	CLgSincroDlg dlg;
	m_pMainWnd = &dlg;

/* controllo parametri di lancio di lgsincro */
// AfxMessageBox( m_lpCmdLine );
 if(strcmp(m_lpCmdLine,"/SINC") == 0) sincok=TRUE;
 if(strcmp(m_lpCmdLine,"/LOC") == 0) sinclocale=TRUE;

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.


	return FALSE;
}
