// ParamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LgConcil.h"
#include "ParamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParamDlg dialog


CParamDlg::CParamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParamDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParamDlg)
	m_freq = 0.0f;
	m_perc = 0.0f;
	m_chi = 0.0f;
	//}}AFX_DATA_INIT
}


void CParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParamDlg)
	DDX_Text(pDX, IDC_FREQ, m_freq);
	DDV_MinMaxFloat(pDX, m_freq, 0.f, 10000.f);
	DDX_Text(pDX, IDC_PERC, m_perc);
	DDV_MinMaxFloat(pDX, m_perc, 0.f, 1.e+006f);
	DDX_Text(pDX, IDC_CHI, m_chi);
	DDV_MinMaxFloat(pDX, m_chi, 0.f, 1.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParamDlg, CDialog)
	//{{AFX_MSG_MAP(CParamDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamDlg message handlers
