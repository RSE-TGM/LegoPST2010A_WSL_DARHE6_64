#if !defined(AFX_PARAMDLG_H__5E71BF60_80F6_11D5_AE7D_0008C72BFBB6__INCLUDED_)
#define AFX_PARAMDLG_H__5E71BF60_80F6_11D5_AE7D_0008C72BFBB6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ParamDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParamDlg dialog

class CParamDlg : public CDialog
{
// Construction
public:
	CParamDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParamDlg)
	enum { IDD = IDD_PARAMETERS };
	float	m_freq;
	float	m_perc;
	float	m_chi;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CParamDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMDLG_H__5E71BF60_80F6_11D5_AE7D_0008C72BFBB6__INCLUDED_)
