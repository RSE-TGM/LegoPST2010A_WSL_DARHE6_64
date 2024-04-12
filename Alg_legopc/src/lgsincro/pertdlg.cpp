// PertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LgSincro.h"
#include "PertDlg.h"
#include "SceltaDlg.h"
#include "LgSincroDlg.h"
#include "LgShared.h"
#include "MonitorDlg.h"

extern int pertattive;
extern MEMORIASHARED *pShrMem1;
extern PERTURBAZIONE pertvar[100];
extern bool apply;
int listavar[12][2];
int numerovar;
int varattiva;
int listapert;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPertDlg dialog


CPertDlg::CPertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPertDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPertDlg)
	m_vfinal = 0.0f;
	m_timeup = 0.0f;
	m_grad = 0.0f;
	m_newv = 0.0f;
	m_delta = 0.0f;
	m_descinput = _T("");
	//}}AFX_DATA_INIT
	ASSERT(pParent != NULL);
	m_pParent = pParent;
	
}


void CPertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPertDlg)
	DDX_Text(pDX, IDC_VFINAL, m_vfinal);
	DDX_Text(pDX, IDC_TIMEUP, m_timeup);
	DDX_Text(pDX, IDC_GRAD, m_grad);
	DDX_Text(pDX, IDC_NEWV, m_newv);
	DDX_Text(pDX, IDC_DELTAV, m_delta);
	DDX_Text(pDX, IDC_DESC, m_descinput);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPertDlg, CDialog)
	//{{AFX_MSG_MAP(CPertDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_IMPO2, OnImpo2)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	ON_BN_CLICKED(IDC_RADIO9, OnRadio9)
	ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
	ON_BN_CLICKED(IDC_RADIO11, OnRadio11)
	ON_BN_CLICKED(IDC_RADIO12, OnRadio12)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_BN_CLICKED(IDC_IMPO1, OnImpo1)
	ON_BN_CLICKED(IDC_APPLYALL, OnApplyall)
	ON_BN_CLICKED(IDC_RIMBTT, OnRimbtt)
	ON_BN_CLICKED(IDC_IMPO3, OnImpo3)
	ON_BN_CLICKED(IDC_CORRBTT, OnCorrbtt)
	ON_EN_CHANGE(IDC_TIMEUP, OnChangeTimeup)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_GRAD, OnChangeGrad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPertDlg message handlers

BOOL CPertDlg::OnInitDialog() 
{
 	CDialog::OnInitDialog();
	CPertDlg::Newvar(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	             // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPertDlg::Create() 
	{
	return CDialog::Create(IDD_PERT,m_pParent);
	
	}

void CPertDlg::Newvar(bool visu) 
{
	CString stringa;
   	int a;
	int b;
	for(int j=0;j<numerovar;j++)
	{
		GetDlgItem(IDC_RADIO1+j)->SetWindowText(pShrMem1->nomeuu[listavar[j][0]]);
		stringa.Format("%f",((pShrMem1->uu[listavar[j][0]])*(pShrMem1->cnuu[listavar[j][0]])));
		GetDlgItem(IDC_EDIT1+j)->SetWindowText(stringa);
		if((b=listavar[j][1])!=-1)
		{
			if(pertvar[b].tipo==1)
				stringa="N.V.";
			else
				if(pertvar[b].tipo==2)
					stringa="Sc.";
				else
					stringa="Rm.";
			GetDlgItem(IDC_EDIT13+j)->SetWindowText(stringa);
			}
		else
			GetDlgItem(IDC_EDIT13+j)->SetWindowText("");
	}
	
	a=listavar[varattiva][1];
	if(varattiva<numerovar)
	{
		GetDlgItem(IDC_RIMBTT)->EnableWindow();
		if (a==-1)
		{
			m_newv=0;
			m_delta=0;
			m_vfinal=0;
			m_timeup=0;
			m_grad=0;
			GetDlgItem(IDC_IMPO1)->EnableWindow();
			GetDlgItem(IDC_IMPO2)->EnableWindow();
			GetDlgItem(IDC_IMPO3)->EnableWindow();
			GetDlgItem(IDC_CORRBTT)->EnableWindow(FALSE);
			GetDlgItem(IDC_APPLY)->EnableWindow(FALSE);
			GetDlgItem(IDC_APPLYALL)->EnableWindow(FALSE);
			GetDlgItem(IDC_NEWV)->EnableWindow();
			GetDlgItem(IDC_DELTAV)->EnableWindow();
			GetDlgItem(IDC_VFINAL)->EnableWindow();
			GetDlgItem(IDC_TIMEUP)->EnableWindow();
			GetDlgItem(IDC_GRAD)->EnableWindow();
		}
		else
		{
			GetDlgItem(IDC_IMPO1)->EnableWindow(FALSE);
			GetDlgItem(IDC_IMPO2)->EnableWindow(FALSE);
			GetDlgItem(IDC_IMPO3)->EnableWindow(FALSE);
			GetDlgItem(IDC_CORRBTT)->EnableWindow();
			GetDlgItem(IDC_APPLY)->EnableWindow();
			GetDlgItem(IDC_APPLYALL)->EnableWindow();

			switch(pertvar[a].tipo)
			{
			case 1:
				m_newv=(pertvar[a].endval)*(pShrMem1->cnuu[listavar[varattiva][0]]);
				m_delta=0;
				m_vfinal=0;
				m_timeup=0;
				m_grad=0;
				GetDlgItem(IDC_NEWV)->EnableWindow();
				GetDlgItem(IDC_DELTAV)->EnableWindow(FALSE);
				GetDlgItem(IDC_VFINAL)->EnableWindow(FALSE);
				GetDlgItem(IDC_TIMEUP)->EnableWindow(FALSE);
				GetDlgItem(IDC_GRAD)->EnableWindow(FALSE);
				break;
			case 2:
				m_newv=0;
				m_delta=(pertvar[a].endval)*(pShrMem1->cnuu[listavar[varattiva][0]]);
				m_vfinal=0;
				m_timeup=0;
				m_grad=0;
				GetDlgItem(IDC_NEWV)->EnableWindow(FALSE);
				GetDlgItem(IDC_DELTAV)->EnableWindow();
				GetDlgItem(IDC_VFINAL)->EnableWindow(FALSE);
				GetDlgItem(IDC_TIMEUP)->EnableWindow(FALSE);
				GetDlgItem(IDC_GRAD)->EnableWindow(FALSE);
				break;
			case 3:
				m_newv=0;
				m_delta=0;
				m_vfinal=(pertvar[a].endval)*(pShrMem1->cnuu[listavar[varattiva][0]]);
				m_timeup=pertvar[a].time;
				m_grad=(pertvar[a].grad)*(pShrMem1->cnuu[listavar[varattiva][0]]);
				GetDlgItem(IDC_NEWV)->EnableWindow(FALSE);
				GetDlgItem(IDC_DELTAV)->EnableWindow(FALSE);
				GetDlgItem(IDC_VFINAL)->EnableWindow();
				GetDlgItem(IDC_TIMEUP)->EnableWindow();
				GetDlgItem(IDC_GRAD)->EnableWindow();
				if(listavar[varattiva][1]<pertattive)
				{
					GetDlgItem(IDC_RIMBTT)->EnableWindow(FALSE);
					GetDlgItem(IDC_APPLY)->EnableWindow(FALSE);
					GetDlgItem(IDC_APPLYALL)->EnableWindow(FALSE);
				}
				break;
			}
		}
		if(visu)
			UpdateData(FALSE);
	}
	else
	{
		GetDlgItem(IDC_RIMBTT)->EnableWindow(FALSE);
		GetDlgItem(IDC_IMPO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_IMPO2)->EnableWindow(FALSE);
		GetDlgItem(IDC_IMPO3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CORRBTT)->EnableWindow(FALSE);
		GetDlgItem(IDC_APPLY)->EnableWindow(FALSE);
		GetDlgItem(IDC_APPLYALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_NEWV)->EnableWindow(FALSE);
		GetDlgItem(IDC_DELTAV)->EnableWindow(FALSE);
		GetDlgItem(IDC_VFINAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_TIMEUP)->EnableWindow(FALSE);
		GetDlgItem(IDC_GRAD)->EnableWindow(FALSE);
	}
}

void CPertDlg::OnClose() 
{
	CDialog::OnClose();
	KillTimer(1);
}

void CPertDlg::OnRadio1() 
{
	varattiva=0;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnRadio2() 
{
	varattiva=1;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnRadio3() 
{
	varattiva=2;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnRadio4() 
{
	varattiva=3;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnRadio5() 
{
	varattiva=4;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnRadio6() 
{
	varattiva=5;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnRadio7() 
{
	varattiva=6;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnRadio8() 
{
	varattiva=7;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnRadio9() 
{
	varattiva=8;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnRadio10() 
{
	varattiva=9;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnRadio11() 
{
	varattiva=10;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnRadio12() 
{
	varattiva=11;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnImpo1() 
{
	UpdateData(TRUE);
	pertvar[listapert].nvar=listavar[varattiva][0];
	pertvar[listapert].tipo=1;
	pertvar[listapert].endval=(m_newv/(pShrMem1->cnuu[listavar[varattiva][0]]));
	pertvar[listapert].nlist=varattiva;
	listavar[varattiva][1]=listapert;
	UpdateData(FALSE);
	listapert++;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnImpo2() 
{
	UpdateData(TRUE);
	pertvar[listapert].nvar=listavar[varattiva][0];
	pertvar[listapert].tipo=2;
	pertvar[listapert].endval=(m_delta/(pShrMem1->cnuu[listavar[varattiva][0]]));
	pertvar[listapert].nlist=varattiva;
	listavar[varattiva][1]=listapert;
	UpdateData(FALSE);
	listapert++;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnImpo3() 
{
	UpdateData(TRUE);
	if(m_grad==0)
	{
		if(m_timeup==0)
		{
			AfxMessageBox("CPertDlg::OnImpo3: Manca un dato!");
			return;
		}
		m_grad=(m_vfinal-(pShrMem1->uu[listavar[varattiva][0]])*(pShrMem1->cnuu[listavar[varattiva][0]]))/m_timeup;		
	}
	else
		if(m_timeup==0)
		{
			m_timeup=(m_vfinal-(pShrMem1->uu[listavar[varattiva][0]])*(pShrMem1->cnuu[listavar[varattiva][0]]))/m_grad;
			if(m_timeup<0)
			{
				m_timeup=m_timeup*(-1);
				m_grad=m_grad*(-1);
			}
		}
		else
			m_grad=(m_vfinal-(pShrMem1->uu[listavar[varattiva][0]])*(pShrMem1->cnuu[listavar[varattiva][0]]))/m_timeup;	

// Guag dic-2004			
//			m_vfinal=(pShrMem1->uu[listavar[varattiva][0]])*(pShrMem1->cnuu[listavar[varattiva][0]])+m_grad*m_timeup;

	pertvar[listapert].nvar=listavar[varattiva][0];
	pertvar[listapert].tipo=3;
	pertvar[listapert].endval=(m_vfinal/(pShrMem1->cnuu[listavar[varattiva][0]]));
	pertvar[listapert].grad=(m_grad/(pShrMem1->cnuu[listavar[varattiva][0]]));
	pertvar[listapert].time=m_timeup;
	pertvar[listapert].nlist=varattiva;
	listavar[varattiva][1]=listapert;
	UpdateData(FALSE);
	listapert++;
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::OnApply() 
{
	PERTURBAZIONE temp;
	int a=listavar[varattiva][1];
	if (a==-1)
		return;
	temp=pertvar[pertattive];
	pertvar[pertattive]=pertvar[a];
	pertvar[a]=temp;
	listavar[varattiva][1]=pertattive;
	listavar[pertvar[a].nlist][1]=a;
	++pertattive;
}

void CPertDlg::OnApplyall() 
{
	pertattive=listapert;
}

void CPertDlg::OnRimbtt() 
{
	CString s;
	int a=varattiva;
	if(listavar[a][1] !=-1)
	{
		for(int k=listavar[a][1];k<(listapert-1);k++)
		{
			pertvar[k]=pertvar[k+1];
			--listavar[pertvar[k].nlist][1];
		}
		pertvar[k].nvar=0;
		pertvar[k].tipo=0;
		pertvar[k].endval=0;
		pertvar[k].time=0;
		pertvar[k].grad=0;
		pertvar[k].nlist=0;
		--listapert;
	}
	for (a;a<(numerovar-1);a++)
	{
		listavar[a][0]=listavar[a+1][0];
		listavar[a][1]=listavar[a+1][1];
		if(listavar[a][1] !=-1)
			--(pertvar[listavar[a][1]].nlist);
	}
	listavar[a][0]=0;
	listavar[a][1]=-1;
	--numerovar;
	GetDlgItem(IDC_RADIO1+a)->SetWindowText("");
	GetDlgItem(IDC_EDIT1+a)->SetWindowText("");
	GetDlgItem(IDC_EDIT13+a)->SetWindowText("");
	CPertDlg::Newvar(TRUE);
}

void CPertDlg::PostNcDestroy() 
{
	delete this;
}

void CPertDlg::OnCancel()
{
	((CLgSincroDlg*) m_pParent)->pertdone();
	DestroyWindow();
}

void CPertDlg::OnCorrbtt() 
{
	GetDlgItem(IDC_IMPO1)->EnableWindow();
	GetDlgItem(IDC_IMPO2)->EnableWindow();
	GetDlgItem(IDC_IMPO3)->EnableWindow();
	GetDlgItem(IDC_CORRBTT)->EnableWindow(FALSE);
	GetDlgItem(IDC_APPLY)->EnableWindow(FALSE);
	GetDlgItem(IDC_APPLYALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_NEWV)->EnableWindow();
	GetDlgItem(IDC_DELTAV)->EnableWindow();
	GetDlgItem(IDC_VFINAL)->EnableWindow();
	GetDlgItem(IDC_TIMEUP)->EnableWindow();
	GetDlgItem(IDC_GRAD)->EnableWindow();

	if((pertvar[listavar[varattiva][1]].tipo==3)&&(listavar[varattiva][1]<pertattive))
	{
		m_timeup=pertvar[listavar[varattiva][1]].time;
		UpdateData(FALSE);
		--pertattive;
	}

	for(int k=listavar[varattiva][1];k<(listapert-1);k++)
	{
		pertvar[k]=pertvar[k+1];
		--listavar[pertvar[k].nlist][1];
	}
	pertvar[k].nvar=0;
	pertvar[k].tipo=0;
	pertvar[k].endval=0;
	pertvar[k].time=0;
	pertvar[k].grad=0;
	pertvar[k].nlist=0;
	--listapert;
	listavar[varattiva][1]=-1;
}





void CPertDlg::OnChangeTimeup() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
//m_grad=0;		
}

void CPertDlg::OnChangeGrad() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
//m_timeup=0;
}
