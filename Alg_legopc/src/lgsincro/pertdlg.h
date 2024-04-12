#if !defined(AFX_PERTDLG_H__E71365C5_F9BD_4476_9BDD_AA9A06C85334__INCLUDED_)
#define AFX_PERTDLG_H__E71365C5_F9BD_4476_9BDD_AA9A06C85334__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PertDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPertDlg dialog

class CPertDlg : public CDialog
{
// Construction
public:
	
	void OnCancel();
	CPertDlg(CWnd* pParent = NULL);   // standard constructor

	void Newvar(bool);

// Dialog Data
	//{{AFX_DATA(CPertDlg)
	enum { IDD = IDD_PERT };
	float	m_vfinal;
	float	m_timeup;
	float	m_grad;
	float	m_newv;
	float	m_delta;
	CString	m_descinput;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPertDlg)
	public:
	virtual BOOL Create();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	CWnd* m_pParent;
	// Generated message map functions
	//{{AFX_MSG(CPertDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnImpo2();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnRadio8();
	afx_msg void OnRadio9();
	afx_msg void OnRadio10();
	afx_msg void OnRadio11();
	afx_msg void OnRadio12();
	afx_msg void OnApply();
	afx_msg void OnImpo1();
	afx_msg void OnApplyall();
	afx_msg void OnRimbtt();
	afx_msg void OnImpo3();
	afx_msg void OnCorrbtt();
	afx_msg void OnChangeTimeup();
	afx_msg void OnChangeGrad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERTDLG_H__E71365C5_F9BD_4476_9BDD_AA9A06C85334__INCLUDED_)
