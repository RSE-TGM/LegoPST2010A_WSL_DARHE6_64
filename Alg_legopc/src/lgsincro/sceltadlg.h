#if !defined(AFX_SCELTADLG_H__DBCD6A86_2CD5_11D5_9D60_0060B0C328CA__INCLUDED_)
#define AFX_SCELTADLG_H__DBCD6A86_2CD5_11D5_9D60_0060B0C328CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SceltaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSceltaDlg dialog

class CSceltaDlg : public CDialog
{
// Construction
public:
	void AddItemMonigraf(char *lgpert);
	void Additem();
	CSceltaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSceltaDlg)
	enum { IDD = IDD_SCELTAVAR };
	CListBox	m_desc;
	CString	m_varser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSceltaDlg)
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
	//{{AFX_MSG(CSceltaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnChangeEdit1();
	afx_msg void OnDblclkDescvar();
	afx_msg void OnAdd();
	afx_msg void OnFind();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCELTADLG_H__DBCD6A86_2CD5_11D5_9D60_0060B0C328CA__INCLUDED_)
