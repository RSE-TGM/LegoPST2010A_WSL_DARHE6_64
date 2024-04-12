// LgSincroDlg.h : header file
//

#if !defined(AFX_LGSINCRODLG_H__68175236_1F7A_11D5_8C78_00805F13C0A9__INCLUDED_)
#define AFX_LGSINCRODLG_H__68175236_1F7A_11D5_8C78_00805F13C0A9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CLgSincroDlg dialog

class CLgSincroDlg : public CDialog
{
// Construction
public:
	int getregistro( char *subkeyname, char *valore, LONG *lunvalore);
	int setregistro( char *subkeyname, char *valore );
    int leggi_file_opzioni();
    int scrivi_file_opzioni();
	CLgSincroDlg(CWnd* pParent = NULL);	// standard constructor
	void OnButtonStop(int conf);
	CMenu *pMainMenu;
	CWinApp* pApp;
    
	void monidone();
	void pertdone();
	void sceldone();
	void refresh();
    void ferma();
    void start_pert_scan();

	bool orologio;
	void ApriMon();
// Dialog Data
	//{{AFX_DATA(CLgSincroDlg)
	enum { IDD = IDD_LGSINCRO_DIALOG };
	CButton	m_stop;
	CEdit	m_log;
	float	m_pint;
	float	m_speed;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLgSincroDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
    
	// Generated message map functions
	//{{AFX_MSG(CLgSincroDlg)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnFreeze();
	afx_msg void OnStep();
	afx_msg void OnMaxs();
	afx_msg void OnPert();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnApply();
	afx_msg void OnChangeSpeed();
	afx_msg void OnChangePint();
	afx_msg void OnControlsStart();
	afx_msg void OnControlsFreeze();
	afx_msg void OnControlsStep();
	afx_msg void OnControlsStop();
	afx_msg void OnControlsRun();
	afx_msg void OnOptionsTimeHhmmss();
	afx_msg void OnOptionsTimeOnlysec();
	afx_msg void OnOptionsSpeedMax();
	afx_msg void OnSnap();
	afx_msg void OnFunctionsPerturbation();
	afx_msg void OnRecordingSnapshot();
	afx_msg void OnGraf();
	afx_msg void OnFunctionsGraphics();
	afx_msg void OnFileOpen();
	afx_msg void OnFileExit();
	afx_msg void OnOptgraf();
	afx_msg void OnInfoabout();
	afx_msg void OnGraphicsMod();
	afx_msg void OnSf14();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LGSINCRODLG_H__68175236_1F7A_11D5_8C78_00805F13C0A9__INCLUDED_)
