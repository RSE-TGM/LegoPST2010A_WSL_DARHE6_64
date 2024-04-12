// LgSincro.h : main header file for the LGSINCRO application
//

#if !defined(AFX_LGSINCRO_H__68175234_1F7A_11D5_8C78_00805F13C0A9__INCLUDED_)
#define AFX_LGSINCRO_H__68175234_1F7A_11D5_8C78_00805F13C0A9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLgSincroApp:
// See LgSincro.cpp for the implementation of this class
//

class CLgSincroApp : public CWinApp
{
public:
	CLgSincroApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLgSincroApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL


// Implementation

	//{{AFX_MSG(CLgSincroApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LGSINCRO_H__68175234_1F7A_11D5_8C78_00805F13C0A9__INCLUDED_)

