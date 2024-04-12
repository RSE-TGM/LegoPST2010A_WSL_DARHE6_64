#if !defined(AFX_OPTGRAFDLG_H__06407DE1_79DA_11D5_99DF_00902754FDDE__INCLUDED_)
#define AFX_OPTGRAFDLG_H__06407DE1_79DA_11D5_99DF_00902754FDDE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OptGrafDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptGrafDlg dialog

class COptGrafDlg : public CDialog
{
// Construction
public:
//	CWinApp* pAppOpt;

	COptGrafDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptGrafDlg)
	enum { IDD = IDD_OPTGRAF };
	int		m_grafmult;
	int		m_grafrefr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptGrafDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptGrafDlg)
	afx_msg void OnKillgraf();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTGRAFDLG_H__06407DE1_79DA_11D5_99DF_00902754FDDE__INCLUDED_)
