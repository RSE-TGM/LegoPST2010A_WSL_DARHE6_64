// LgConcilDlg.h : header file
//

#if !defined(AFX_LGCONCILDLG_H__EC79A756_7C41_11D5_AE76_0008C72BFBB6__INCLUDED_)
#define AFX_LGCONCILDLG_H__EC79A756_7C41_11D5_AE76_0008C72BFBB6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CLgConcilDlg dialog

class CLgConcilDlg : public CDialog
{
// Construction
public:
	CLgConcilDlg(CWnd* pParent = NULL);	// standard constructor
	CWinApp* pApp;
	void ReadSens(FILE *fd,BOOL init);
	void WNDone();
	void AlarmDone();

// Dialog Data
	//{{AFX_DATA(CLgConcilDlg)
	enum { IDD = IDD_LGCONCIL_DIALOG };
	CButton	m_alarm_but;
	CButton	m_wn;
	CButton	m_model;
	CButton	m_param;
	CButton	m_freeze;
	CEdit	m_nome_modulo;
	CListBox m_log;
	CButton	m_quit;
	CButton	m_init;
	CButton	m_stop;
	CButton	m_graph;
	CButton	m_pert;
	CButton	m_run;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLgConcilDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLgConcilDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInit();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnButtonModel();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnParameters();
	afx_msg void OnGraph();
	afx_msg void OnFreeze();
	afx_msg void OnInfo();
	afx_msg void OnPert();
	virtual void OnCancel();
	afx_msg void OnWn();
	afx_msg void OnAlarmBut();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LGCONCILDLG_H__EC79A756_7C41_11D5_AE76_0008C72BFBB6__INCLUDED_)
