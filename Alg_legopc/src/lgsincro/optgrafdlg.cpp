// OptGrafDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LgSincro.h"
#include "OptGrafDlg.h"

int prep_f22(int);

#define APRI 1
#define SCRIVI 2
#define CHIUDI 3


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptGrafDlg dialog


COptGrafDlg::COptGrafDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptGrafDlg::IDD, pParent)
{


	//{{AFX_DATA_INIT(COptGrafDlg)
	m_grafmult = 0;
	m_grafrefr = 0;
	//}}AFX_DATA_INIT
/*
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_KILL);
	((CButton*)GetDlgItem(IDC_KILLGRAF))->SetIcon(m_hIcon);
*/
}


void COptGrafDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptGrafDlg)
	DDX_Text(pDX, IDC_GRAFMULT, m_grafmult);
	DDV_MinMaxInt(pDX, m_grafmult, 0, 10000);
	DDX_Text(pDX, IDC_GRAFREFR, m_grafrefr);
	DDV_MinMaxInt(pDX, m_grafrefr, 0, 10000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptGrafDlg, CDialog)
	//{{AFX_MSG_MAP(COptGrafDlg)
	ON_BN_CLICKED(IDC_KILLGRAF, OnKillgraf)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptGrafDlg message handlers

void COptGrafDlg::OnKillgraf() 
{
	// TODO: Add your control notification handler code here

if(AfxMessageBox("Reinitializing grafics file f22...\nAre you sure?",MB_YESNO  )==IDYES)
	{

	if(prep_f22(CHIUDI)==0)
		AfxMessageBox("Impossibile chiudere il file dei grafici f22");

	if(prep_f22(APRI)==-1) AfxMessageBox("Impossibile inizializzare il file grafico");
	}
}
