// MonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LgSincro.h"
#include "LgShared.h"
#include "MonitorDlg.h"
#include "LgSincroDlg.h"
#include "PertDlg.h"
#include "SceltaDlg.h"

extern MEMORIASHARED  *pShrMem1;

extern CSceltaDlg *m_additem;
extern CMonitorDlg *m_monigraf;

int elenco [5500];
int nelenco;

int ref_monitor; // tempo di refresh var. di monitor
int ref_monitorgraf=500; // tempo di refresh var. di inter. con modalità grafica
int shot=0;//Variabile per controllare il numero di lanci della finestra
CString linea;

CEdit m_log;
#ifdef _DEBUG
#define new DEBUG_NEW

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitorDlg dialog


CMonitorDlg::CMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMonitorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMonitorDlg)
	m_refresh = 0.0f;
	//}}AFX_DATA_INIT
	ASSERT(pParent != NULL);
	m_pParent = pParent;
}

void CMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMonitorDlg)
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_refresh);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMonitorDlg, CDialog)
	//{{AFX_MSG_MAP(CMonitorDlg)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, OnRemoveMon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitorDlg message handlers

BOOL CMonitorDlg::Create()
{
	return CDialog::Create(IDD_MONITORDLG_DIALOG,m_pParent);

}

BOOL CMonitorDlg::OnInitDialog() 
{
    SetTimer (1, 1000, NULL);
	CDialog::OnInitDialog();

	m_list.SetColumnWidth(200);
	SetTimer( 1,1000,NULL );
	m_refresh=1;
	ref_monitor=1000;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMonitorDlg::OnTimer(UINT nIDEvent) 
{
 if (nIDEvent==1)	
	{
	KillTimer(1);
	int index=m_list.GetCurSel( );
	m_list.ResetContent( );
	for(int j=0;j<nelenco;j++)
		{
		if(elenco[j]<10000)
			linea.Format("%s	%f   %s",pShrMem1->nomeuu[elenco[j]],
			    (pShrMem1->uu[elenco[j]])*(pShrMem1->cnuu[elenco[j]]),
				pShrMem1->descruu[elenco[j]]+29);
		else
			linea.Format("%s	%f   %s",pShrMem1->nomexy[elenco[j]-10000],
			    (pShrMem1->xy[elenco[j]-10000])*(pShrMem1->cnxy[elenco[j]-10000]),
				pShrMem1->descrxy[elenco[j]-10000]+29);

		m_list.AddString(linea);
		}
	if(index != LB_ERR) m_list.SetCurSel( index );
	SetTimer( 1,ref_monitor,NULL );
	}
  else
		{	
		KillTimer (2);
/*		char *lgpert;
		char *flpert;
		flpert = getenv("LG_FLPERT");
		lgpert = getenv("LG_PERT");
		//flpert = "1";
		//AfxMessageBox(lgpert);
*/
		if(pShrMem1->control[INDACCSHM] == 1 )
			{
			 
			 m_additem->AddItemMonigraf(pShrMem1->nomeuu[NUU-1]);
			 pShrMem1->control[INDACCSHM] = 0;
			  SetTimer( 2,ref_monitorgraf,NULL );
			}
            else
			   SetTimer( 2,ref_monitorgraf,NULL );
		}
}

void CMonitorDlg::OnCancel() 
{
    ((CLgSincroDlg*) m_pParent)->monidone();
	DestroyWindow();
            
}

void CMonitorDlg::OnChangeEdit1() 
{
	UpdateData();
	if(m_refresh>0)
	{
		ref_monitor=(int)(m_refresh*1000);
	    KillTimer(1);	
		SetTimer( 1,ref_monitor,NULL );
	}
}

void CMonitorDlg::OnRemoveMon() 
{
	int index=m_list.GetCurSel( );
    if( index == LB_ERR) return;
	m_list.DeleteString( index );
	for(int j=index; j< nelenco; j++)
		elenco[j]=elenco[j+1];
	--nelenco;
}

void CMonitorDlg::StartTimer()
{  
    if(shot==0){
	m_monigraf=new CMonitorDlg(this);
	m_monigraf->Create();
	shot=1;
	}
	m_monigraf->ShowWindow(SW_HIDE);
	m_monigraf->SetTimer(2,ref_monitorgraf,NULL);
}


