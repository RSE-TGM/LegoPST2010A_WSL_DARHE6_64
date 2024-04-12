// AlarmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LgConcil.h"
#include "AlarmDlg.h"
#include "LgConcilDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg dialog


CAlarmDlg::CAlarmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmDlg)
	m_hold = FALSE;
	//}}AFX_DATA_INIT

	ASSERT (pParent != NULL);
	m_pParent = pParent;
}

BOOL CAlarmDlg::Create()
{
 	return CDialog::Create(IDD_ALARM,m_pParent);
}

void CAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmDlg)
	DDX_Control(pDX, IDC_ALARM, m_Alarm_lbx);
	DDX_Check(pDX, IDC_HOLD, m_hold);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarmDlg, CDialog)
	//{{AFX_MSG_MAP(CAlarmDlg)
	ON_BN_CLICKED(IDC_HOLD, OnHold)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg message handlers

void CAlarmDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	((CLgConcilDlg *) m_pParent)->AlarmDone();
	
	CDialog::OnCancel();
}

void CAlarmDlg::OnHold() 
{
	// TODO: Add your control notification handler code here
	m_hold = (m_hold ? FALSE : TRUE);
}
