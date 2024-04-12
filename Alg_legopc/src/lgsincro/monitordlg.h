#if !defined(AFX_MONITORDLG_H__11A35CA0_C6A8_44D1_864B_C2D08FB601F3__INCLUDED_)
#define AFX_MONITORDLG_H__11A35CA0_C6A8_44D1_864B_C2D08FB601F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonitorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMonitorDlg dialog

class CMonitorDlg : public CDialog
{
// Construction
public:
	
	void StartTimer();
	BOOL Create();
	CMonitorDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CMonitorDlg)
	enum { IDD = IDD_MONITORDLG_DIALOG };
	CListBox	m_list;
	float	m_refresh;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CWnd* m_pParent;

	// Generated message map functions
	//{{AFX_MSG(CMonitorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg void OnChangeEdit1();
	afx_msg void OnRemoveMon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITORDLG_H__11A35CA0_C6A8_44D1_864B_C2D08FB601F3__INCLUDED_)
