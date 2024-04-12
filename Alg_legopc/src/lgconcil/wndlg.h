#if !defined(AFX_WNDLG_H__A331A7B1_8C95_11D5_AE83_0008C72BFBB6__INCLUDED_)
#define AFX_WNDLG_H__A331A7B1_8C95_11D5_AE83_0008C72BFBB6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WNDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWNDlg dialog

class CWNDlg : public CDialog
{
// Construction
public:
	CWNDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL Create();
	void UpdSensWN();

// Dialog Data
	//{{AFX_DATA(CWNDlg)
	enum { IDD = IDD_WN };
	CEdit	m_offset;
	CEdit	m_band;
	CListBox	m_senswn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWNDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd *m_pParent;

	// Generated message map functions
	//{{AFX_MSG(CWNDlg)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnWnappl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDLG_H__A331A7B1_8C95_11D5_AE83_0008C72BFBB6__INCLUDED_)
