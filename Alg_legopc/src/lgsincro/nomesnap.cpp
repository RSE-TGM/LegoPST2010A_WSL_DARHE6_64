// NomeSnap.cpp : implementation file
//

#include "stdafx.h"
#include "LgSincro.h"
#include "NomeSnap.h"

extern char locpath[100];
extern CString nomesnap;
extern char snap;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NomeSnap dialog


NomeSnap::NomeSnap(CWnd* pParent /*=NULL*/)
	: CDialog(NomeSnap::IDD, pParent)
{
	//{{AFX_DATA_INIT(NomeSnap)
	m_nomesnap = _T("");
	//}}AFX_DATA_INIT
}


void NomeSnap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(NomeSnap)
	DDX_Control(pDX, IDC_LIST1, m_snaplist);
	DDX_Text(pDX, IDC_EDIT1, m_nomesnap);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(NomeSnap, CDialog)
	//{{AFX_MSG_MAP(NomeSnap)
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(IDC_ERASE, OnErase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NomeSnap message handlers

BOOL NomeSnap::OnInitDialog() 
{
	
	CDialog::OnInitDialog();

	FILE *record;
	char * key="";

	SetCurrentDirectory(locpath);
	if((record=fopen("snapshot.dat","r"))==NULL)
		return TRUE;
	rewind(record);
//char ss1[100];
//sprintf(ss1,"OnInitDialog 1\n");
//AfxMessageBox( ss1 );
	while(fscanf(record,"%s",key) != EOF)
		if(!strcmp(key,"^"))
		{
			fscanf(record,"%s",key);
			m_snaplist.AddString((CString)key);
		}
    fclose(record);
	if(m_snaplist.GetCount()!=0)
	{
//Provvisorio... disabilito le due funzionalità in quanto errate
//		GetDlgItem(IDC_LOAD)->EnableWindow();
//		GetDlgItem(IDC_ERASE)->EnableWindow(); 
	}
    m_nomesnap.Empty();
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void NomeSnap::OnLoad() 
{
	UpdateData();
	if((nomesnap=m_nomesnap)!="" && (m_snaplist.FindString(-1,m_nomesnap)!=LB_ERR ))
	{
		snap=2;
		CDialog::OnOK();
	}
}

void NomeSnap::OnSave() 
{
	UpdateData();
	if((nomesnap=m_nomesnap)!="" && (m_snaplist.FindString(-1,m_nomesnap)==LB_ERR ))
	{
		snap=1;
		CDialog::OnOK();
	}
}

void NomeSnap::OnSelchangeList1() 
{
	m_snaplist.GetText(m_snaplist.GetCurSel(),m_nomesnap);
	UpdateData(FALSE);	
}

void NomeSnap::OnChangeEdit1() 
{
	UpdateData();
	m_snaplist.SelectString(-1,m_nomesnap);
}

void NomeSnap::OnErase() 
{
	FILE *record;
	CString key;

	SetCurrentDirectory(locpath);
	if((record=fopen("snapshot.dat","r+"))==NULL)
	{
		AfxMessageBox("Impossibile accedere al file snapshot.dat");
		return;
	}

	rewind(record);
	while(key!=m_nomesnap)
	{
		while(key!="^")
			fscanf(record,"%s",key);
		fscanf(record,"%s",key);
	}

	fseek(record,-(2+m_nomesnap.GetLength()),SEEK_CUR);
	fprintf(record,"          \n");
	
	rewind(record);
	m_snaplist.ResetContent();
	while(fscanf(record,"%s",key) != EOF)
		if(key=="^")
		{
			fscanf(record,"%s",key);
			m_snaplist.AddString(key);
		}
	fclose(record);

	if(m_snaplist.GetCount()==0)
	{
		GetDlgItem(IDC_LOAD)->EnableWindow(FALSE);
		GetDlgItem(IDC_ERASE)->EnableWindow(FALSE);
	}

}

void NomeSnap::OnCancel() 
{
	// TODO: Add extra cleanup here
	DestroyWindow();
	CDialog::OnCancel();
//delete this;
}

void NomeSnap::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
//	CDialog::PostNcDestroy();
//	delete  this;
}
