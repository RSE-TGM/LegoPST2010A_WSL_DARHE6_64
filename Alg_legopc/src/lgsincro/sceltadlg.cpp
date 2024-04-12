// SceltaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LgSincro.h"
#include "PertDlg.h"
#include "SceltaDlg.h"
#include "LgSincroDlg.h"
#include "LgShared.h"
#include "MonitorDlg.h"

extern MEMORIASHARED  *pShrMem1;
extern PERTURBAZIONE pertvar[12];

extern int numerovar;
extern int listavar[12][2];
extern int elenco [5500];
extern int nelenco;

extern CLgSincroDlg *m_prin;
//extern CSceltaDlg *m_additem;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//char appo[200];
/////////////////////////////////////////////////////////////////////////////
// CSceltaDlg dialog


CSceltaDlg::CSceltaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSceltaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSceltaDlg)
	m_varser = _T("");
	//}}AFX_DATA_INIT
	ASSERT(pParent != NULL);
	m_pParent = pParent;
}


void CSceltaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSceltaDlg)
	DDX_Control(pDX, IDC_DESCVAR, m_desc);
	DDX_Text(pDX, IDC_EDIT1, m_varser);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSceltaDlg, CDialog)
	//{{AFX_MSG_MAP(CSceltaDlg)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_LBN_DBLCLK(IDC_DESCVAR, OnDblclkDescvar)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSceltaDlg message handlers

BOOL CSceltaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int j;
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
	if(m_desc.GetCount()==0)
		for(j=0;j<pShrMem1->nuu;j++)
//			m_desc.AddString(pShrMem1->nomeuu[j]);
			m_desc.AddString(pShrMem1->descruu[j]);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSceltaDlg::Create() 
{
	return CDialog::Create(IDD_SCELTAVAR,m_pParent);
}

void CSceltaDlg::PostNcDestroy() 
{
	delete this;
}

void CSceltaDlg::OnCancel() 
{
	((CLgSincroDlg*) m_pParent)->sceldone();
	DestroyWindow();
}

void CSceltaDlg::Additem()
{
	int a;
 	extern CPertDlg *m_pert;
	if((a=m_desc.GetCurSel()) !=CB_ERR )
	{	
		switch(((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())
		{
		case 0:
			if (numerovar<12)
			{
				listavar[numerovar][0]=a;
				listavar[numerovar][1]=-1;
				++numerovar;
				if(m_pert != NULL)
					m_pert->Newvar(TRUE);
			}
			else
			{
				AfxMessageBox("Troppe variabili!");
				return;
			}
			break;
		case 1:
			if(a<pShrMem1->nuu)
			{
				elenco[nelenco]=a;
				++nelenco;
			}
			else
			{
				elenco[nelenco]=a+10000-pShrMem1->nuu;
				++nelenco;
			}
			break;
		}
	}
	else 
		return;
}

void CSceltaDlg::OnRadio1() 
{
	int j;

	m_desc.ResetContent();
	for(j=0;j<pShrMem1->nuu;j++){
//		m_desc.AddString(pShrMem1->nomeuu[j]);
//		strcpy(appo,pShrMem1->descruu[j]);
//		appo[100]='\0';
		m_desc.AddString(pShrMem1->descruu[j]);
//		m_desc.AddString( appo);
	}
	for(j=0;j<pShrMem1->nxy;j++){
//		m_desc.AddString(pShrMem1->nomexy[j]);
//		strcpy(appo,pShrMem1->descrxy[j]);
//		appo[100]='\0';
		m_desc.AddString( pShrMem1->descrxy[j]);
//		m_desc.AddString( appo);

		m_prin->ApriMon(); 
	}
}

void CSceltaDlg::OnRadio2() 
{
	int j;

	m_desc.ResetContent();
	for(j=0;j<pShrMem1->nuu;j++){
//		m_desc.AddString(pShrMem1->nomeuu[j]);
//		strcpy(appo,pShrMem1->descruu[j]);
//		appo[100]='\0';
		m_desc.AddString( pShrMem1->descruu[j] );
//		m_desc.AddString( appo );

	}
}

void CSceltaDlg::OnChangeEdit1() 
{
	UpdateData();
	m_desc.SelectString(-1,m_varser);
}

void CSceltaDlg::OnDblclkDescvar() 
{
	CSceltaDlg::Additem();
}

void CSceltaDlg::OnAdd() 
{
	CSceltaDlg::Additem();
}

void CSceltaDlg::OnFind() 
{
	CString str;
	bool contr=FALSE;

	UpdateData();
	m_varser.MakeUpper();

	for(int j=m_desc.GetCurSel()+1;;j++)
	{
		if(j==m_desc.GetCount())
		{
			j=0;
			if(contr)
				return;
			contr=true;
		}

		m_desc.GetText(j,str);
		int lungh=m_desc.GetTextLen(j);
// per la versione c++ 6 era:		if(str.Find(m_varser,0)!=-1)
		int ret=str.Find(m_varser);
		if( ret !=-1)
		{
			m_desc.SetCurSel(j);
//			sprintf(ss,"ret=%d %s %s\n",str.Find(m_varser), m_varser, str);
//			char ss[100];
//			sprintf(ss,"ret=%d m_desclungh=%d j=%d %s\n",ret,lungh,j,m_varser);
//			AfxMessageBox( ss );
			return;
		}
	}
/*
char ss[100];

int j=m_desc.GetCurSel()+1;
sprintf(ss,"%s",m_varser);
int ret=m_desc.FindString(j,ss);
sprintf(ss,"%s j=%d ret=%d\n",m_varser,j,ret);
AfxMessageBox( ss );
if( ret!=LB_ERR) m_desc.SetCurSel(ret);
*/
	
}

void CSceltaDlg::AddItemMonigraf(char *lgpert)
{
	int j;
	extern CPertDlg *m_pert;

	for(j=0;j<pShrMem1->nuu;j++)
	{					
		if(strcmp(pShrMem1->nomeuu[j],lgpert) == 0)
			{
			if (numerovar<12)
					{
				listavar[numerovar][0]=j;
				listavar[numerovar][1]=-1;
				++numerovar;
				if(m_pert != NULL)
					m_pert->Newvar(TRUE);
					}
			else
			{
				AfxMessageBox("Troppe variabili!");
				return;
			}
		break;
		}	
	}
}


