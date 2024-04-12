// WNDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LgConcil.h"
#include "WNDlg.h"
#include "LgConcilDlg.h"
#include "wn_externals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWNDlg dialog


CWNDlg::CWNDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWNDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWNDlg)
	//}}AFX_DATA_INIT

	ASSERT (pParent != NULL);
	m_pParent = pParent;
}


void CWNDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWNDlg)
	DDX_Control(pDX, IDC_WN_OFFSET, m_offset);
	DDX_Control(pDX, IDC_WN_BAND, m_band);
	DDX_Control(pDX, IDC_SENSWN, m_senswn);
	//}}AFX_DATA_MAP
}

BOOL CWNDlg::Create()
{
 	return CDialog::Create(IDD_WN,m_pParent);
}


BEGIN_MESSAGE_MAP(CWNDlg, CDialog)
	//{{AFX_MSG_MAP(CWNDlg)
	ON_BN_CLICKED(IDC_WNAPPL, OnWnappl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWNDlg message handlers

void CWNDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	((CLgConcilDlg *) m_pParent)->WNDone();

	CDialog::OnCancel();
}

CFont   fntWNCourier; //variabili globali comuni alle funzioni che seguono
char s[200];

void CWNDlg::OnOK() 
{
	// TODO: Add extra validation here

	UpdSensWN();

	((CLgConcilDlg *) m_pParent)->WNDone();	

	CDialog::OnOK();
}

BOOL CWNDlg::OnInitDialog() 
{

 	CRect	rcLBox;
	static BOOL  ExistsFont = FALSE;

	CDialog::OnInitDialog();

 	m_senswn.GetWindowRect(rcLBox);

	if (! ExistsFont) {
		fntWNCourier.CreateFont( rcLBox.Height()/12, 0, 0, 0, 0, 0, 0, 0,
 								 0, 0, 0, 0, 0, "Courier" );
		ExistsFont = TRUE;
	}

 	this->m_senswn.SetFont(&fntWNCourier);

	for (int i=0; i<pShrMem1->SensNum;i++) {
		memcpy(s,pShrMem1->SenVarName[i],8);
		sprintf(s+8,"      %5.2f        %6.2f",
 				SensBand[i],SensOffset[i]);
 		m_senswn.AddString(s);
	}
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWNDlg::OnWnappl() 
{
	// TODO: Add your control notification handler code here
	UpdSensWN();
}

void CWNDlg::UpdSensWN()
{
	CString str;
	int  nSel = m_senswn.GetCurSel();
	
	if(nSel != LB_ERR)
	{
		m_band.GetWindowText(str);
		sscanf(str,"%f",&SensBand[nSel]);
		m_offset.GetWindowText(str);
		sscanf(str,"%f",&SensOffset[nSel]);
		memcpy(s,pShrMem1->SenVarName[nSel],8);
 		sprintf(s+8,"      %5.2f        %6.2f",
  				SensBand[nSel],SensOffset[nSel]);
		m_senswn.DeleteString(nSel);
		m_senswn.InsertString(nSel,s);
	}

}

