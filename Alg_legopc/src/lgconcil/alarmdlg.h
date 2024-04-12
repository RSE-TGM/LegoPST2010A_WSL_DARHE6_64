#if !defined(AFX_ALARMDLG_H__E5215BF0_E3F2_11D5_AEF2_0008C72BFBB6__INCLUDED_)
#define AFX_ALARMDLG_H__E5215BF0_E3F2_11D5_AEF2_0008C72BFBB6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AlarmDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg dialog

class CAlarmDlg : public CDialog
{
// Construction
public:
	CAlarmDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL Create();
// Dialog Data
	//{{AFX_DATA(CAlarmDlg)
	enum { IDD = IDD_ALARM };
	CListBox	m_Alarm_lbx;
	BOOL	m_hold;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd *m_pParent;
	// Generated message map functions
	//{{AFX_MSG(CAlarmDlg)
	virtual void OnCancel();
	afx_msg void OnHold();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMDLG_H__E5215BF0_E3F2_11D5_AEF2_0008C72BFBB6__INCLUDED_)


