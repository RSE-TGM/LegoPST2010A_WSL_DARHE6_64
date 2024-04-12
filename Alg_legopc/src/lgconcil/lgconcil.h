// LgConcil.h : main header file for the LGCONCIL application
//

#if !defined(AFX_LGCONCIL_H__EC79A754_7C41_11D5_AE76_0008C72BFBB6__INCLUDED_)
#define AFX_LGCONCIL_H__EC79A754_7C41_11D5_AE76_0008C72BFBB6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLgConcilApp:
// See LgConcil.cpp for the implementation of this class
//

class CLgConcilApp : public CWinApp
{
public:
	CLgConcilApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLgConcilApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLgConcilApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LGCONCIL_H__EC79A754_7C41_11D5_AE76_0008C72BFBB6__INCLUDED_)
