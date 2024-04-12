#if !defined(AFX_NOMESNAP_H__68DA288C_A916_4C67_A25D_89C77DA44767__INCLUDED_)
#define AFX_NOMESNAP_H__68DA288C_A916_4C67_A25D_89C77DA44767__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NomeSnap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NomeSnap dialog

class NomeSnap : public CDialog
{
// Construction
public:
	NomeSnap(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(NomeSnap)
	enum { IDD = IDD_NOMESNAP_DIALOG };
	CListBox	m_snaplist;
	CString	m_nomesnap;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NomeSnap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(NomeSnap)
	virtual BOOL OnInitDialog();
	afx_msg void OnLoad();
	afx_msg void OnSave();
	afx_msg void OnSelchangeList1();
	afx_msg void OnChangeEdit1();
	afx_msg void OnErase();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOMESNAP_H__68DA288C_A916_4C67_A25D_89C77DA44767__INCLUDED_)
