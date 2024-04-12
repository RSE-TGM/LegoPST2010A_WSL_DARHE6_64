#include "stdafx.h"
#include "windows.h"
#include "mmsystem.h"
#include "LgSincro.h"
#include "PertDlg.h"
#include "SceltaDlg.h"
#include "MonitorDlg.h"
#include "LgSincroDlg.h"
#include "OptGrafDlg.h"
#include "LgShared.h"
#include "Lgsin.h"
#include "NomeSnap.h"
#include "NomeSnap.h"
#include <winreg.h>



CSceltaDlg *m_scel, *m_additem;
CPertDlg *m_pert;
CMonitorDlg *m_moni;
CFileDialog *m_openf;
CLgSincroDlg *m_prin;
CMonitorDlg *m_monigraf;

CString command;
char np[3];
int Conta=0;
char comando[200];
char comando2[200];
int graftcl=1;

bool gostep=FALSE;
bool waitevec, waitevecsincok,escifreeze=FALSE;	
				
char  *flpert, *pert;
char ss[200] ;	
char buffer[200];

MEMORIASHARED  *pShrMem1;
PERTURBAZIONE pertvar[100];

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLgSincroDlg dialog

CLgSincroDlg::CLgSincroDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLgSincroDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLgSincroDlg)
	m_pint = 0.0f;
	m_speed = 0.0f;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_scel = NULL;
	m_pert = NULL;
	m_moni = NULL;
	m_monigraf = NULL;
	m_prin = this;
//	iiqq = CWnd::m_hWnd;
}

void CLgSincroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLgSincroDlg)
	DDX_Control(pDX, IDC_STOP, m_stop);
	DDX_Control(pDX, IDC_LOG, m_log);
	DDX_Text(pDX, IDC_PINT, m_pint);
	DDV_MinMaxFloat(pDX, m_pint, 0.f, 10.f);
	DDX_Text(pDX, IDC_SPEED, m_speed);
	DDV_MinMaxFloat(pDX, m_speed, 0.f, 1.e+008f);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLgSincroDlg, CDialog)
	//{{AFX_MSG_MAP(CLgSincroDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_FREEZE, OnFreeze)
	ON_BN_CLICKED(IDC_STEP, OnStep)
	ON_BN_CLICKED(IDC_MAXS, OnMaxs)
	ON_BN_CLICKED(IDC_PERT, OnPert)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_EN_CHANGE(IDC_SPEED, OnChangeSpeed)
	ON_EN_CHANGE(IDC_PINT, OnChangePint)
	ON_COMMAND(ID_CONTROLS_START, OnControlsStart)
	ON_COMMAND(ID_CONTROLS_FREEZE, OnControlsFreeze)
	ON_COMMAND(ID_CONTROLS_STEP, OnControlsStep)
	ON_COMMAND(ID_CONTROLS_STOP, OnControlsStop)
	ON_COMMAND(ID_CONTROLS_RUN, OnControlsRun)
	ON_COMMAND(ID_OPTIONS_TIME_HHMMSS, OnOptionsTimeHhmmss)
	ON_COMMAND(ID_OPTIONS_TIME_ONLYSEC, OnOptionsTimeOnlysec)
	ON_COMMAND(ID_OPTIONS_SPEED_MAX, OnOptionsSpeedMax)
	ON_BN_CLICKED(IDC_SNAP, OnSnap)
	ON_COMMAND(ID_FUNCTIONS_PERTURBATION, OnFunctionsPerturbation)
	ON_COMMAND(ID_FUNCTIONS_SNAPSHOT, OnRecordingSnapshot)
	ON_BN_CLICKED(IDC_GRAF, OnGraf)
	ON_COMMAND(ID_FUNCTIONS_GRAPHICS, OnFunctionsGraphics)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_OPTGRAF, OnOptgraf)
	ON_COMMAND(ID_INFOABOUT, OnInfoabout)
	ON_COMMAND(ID_GRAPHICS_MOD, OnGraphicsMod)
	ON_BN_CLICKED(IDC_SF14, OnSf14)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLgSincroDlg message handlers

BOOL CLgSincroDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

m_log.ReplaceSel("LgSincro initialization.	", FALSE );

	pApp=AfxGetApp();
	if (pApp!=0)
	{
		((CButton*)GetDlgItem(IDC_PLAY))->SetIcon(pApp->LoadIcon(IDI_START));
		((CButton*)GetDlgItem(IDC_FREEZE))->SetIcon(pApp->LoadIcon(IDI_FREEZE));
		((CButton*)GetDlgItem(IDC_STEP))->SetIcon(pApp->LoadIcon(IDI_STEP));
		((CButton*)GetDlgItem(IDC_STOP))->SetIcon(pApp->LoadIcon(IDI_STOP));
		((CButton*)GetDlgItem(IDC_PERT))->SetIcon(pApp->LoadIcon(IDI_PERT));
		((CButton*)GetDlgItem(IDC_SNAP))->SetIcon(pApp->LoadIcon(IDI_SNAP));
		((CButton*)GetDlgItem(IDC_GRAF))->SetIcon(pApp->LoadIcon(IDI_GRAF));
		((CStatic*)GetDlgItem(IDC_STATUS))->SetIcon(pApp->LoadIcon(IDI_LSTOP));
//		((CButton*)GetDlgItem(IDC_PICT))->SetIcon(pApp->LoadIcon(IDI_PICT));//Aggiunto
		((CButton*)GetDlgItem(IDC_SF14))->SetIcon(pApp->LoadIcon(IDI_SF14));//Aggiunto
	    ((CButton*)GetDlgItem(IDC_APPLY))->SetIcon(pApp->LoadIcon(IDI_UPDRED));
	}
	GetDlgItem(IDC_APPLY)->EnableWindow(FALSE);

	timeBeginPeriod(1);
	orologio=FALSE;

// init opzioni 
//CLgSincroDlg::leggi_file_opzioni();

//  ---
	pMainMenu=GetMenu();

	if( orologio ) pMainMenu->CheckMenuRadioItem(ID_OPTIONS_TIME_HHMMSS,ID_OPTIONS_TIME_ONLYSEC,ID_OPTIONS_TIME_HHMMSS,MF_BYCOMMAND);
       else pMainMenu->CheckMenuRadioItem(ID_OPTIONS_TIME_HHMMSS,ID_OPTIONS_TIME_ONLYSEC,ID_OPTIONS_TIME_ONLYSEC,MF_BYCOMMAND);

    if(flag_pert_graf) pMainMenu->CheckMenuItem(ID_GRAPHICS_MOD,MF_CHECKED);
       else pMainMenu->CheckMenuItem(ID_GRAPHICS_MOD,MF_UNCHECKED);
/*
	char *simvar;
    simvar = getenv( "LG_SINCSIMUL" );
sprintf(buffer,"LG_SINCSIMUL=%s\n",simvar);
m_log.ReplaceSel(buffer,FALSE);
	
	sincok=FALSE;
	if( simvar != NULL ){
			if (strncmp(simvar,"YES",3)==0){
				_putenv( "LG_SINCSIMUL=NO" );
				sincok=TRUE;
			}
	} 

sprintf(buffer,"simvar=%s sincok=%d TRUE=%d\n",simvar,sincok,TRUE);
m_log.ReplaceSel(buffer,FALSE);
*/	

	if(sincok) 	m_log.ReplaceSel("Modo Simulink Attivo         ",FALSE);
	if(sincok) OnPlay();
	m_log.ReplaceSel( "Fine inizializzazione.		", FALSE );	
	
	return TRUE;   // return TRUE  unless you set the focus to a control
	}

void CLgSincroDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLgSincroDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLgSincroDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLgSincroDlg::OnPlay() 
{
GetDlgItem(IDC_FREEZE)->EnableWindow(FALSE);  // disabilito freeze
	m_log.ReplaceSel( "Inizio sequenza play.	", FALSE );

	if(stopath[0]==NULL)
		CLgSincroDlg::OnFileOpen();

	strcat(EVES,np);
	strcat(EVESINIT,np);
	strcat(EVEC,np);
//GUAG!
	strcpy(EVECSINC,EVEC);
	strcat(EVECSINC,"SINC");
	strcpy(EVECSINCOK,EVECSINC);
	strcat(EVECSINC,"OK");

	strcat(MapName,np);

m_log.ReplaceSel( "Lancio lgser.		", FALSE );
	SetCurrentDirectory(stopath);
	command.Format("lgser.exe s %s",np);
	if((WinExec(command,SW_SHOWMINIMIZED))>31)
m_log.ReplaceSel( "lgser lanciato.		", FALSE );
	else
	{
		AfxMessageBox("lgser.exe not found!");
		return;
	}

m_log.ReplaceSel( "Attesa init lgser.	", FALSE );
	while ((hEveSINIT = OpenEvent( EVENT_ALL_ACCESS  ,TRUE,EVESINIT) ) == NULL);
		retWait = WaitForSingleObject(  hEveSINIT,INFINITE); 		

	if( (hMem1=OpenMap( (LPSTR) MapName)) == NULL) 
	{
		AfxMessageBox("Shared memory assente!");
		return;
	}
	pShrMem1 = (MEMORIASHARED *) MapView(hMem1);

m_log.ReplaceSel( "Inizializzazione pulsanti	", FALSE );
	GetDlgItem(IDC_PLAY)->EnableWindow(FALSE);
	pMainMenu->EnableMenuItem(ID_CONTROLS_START,MF_GRAYED);
//	GetDlgItem(IDC_FREEZE)->EnableWindow(TRUE);
	pMainMenu->EnableMenuItem(ID_CONTROLS_RUN,MF_ENABLED);
	if(!sincok) GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
	pMainMenu->EnableMenuItem(ID_CONTROLS_STOP,MF_ENABLED);
	GetDlgItem(IDC_STEP)->EnableWindow(FALSE);
	pMainMenu->EnableMenuItem(ID_CONTROLS_STEP,MF_GRAYED);
	((CStatic*)GetDlgItem(IDC_STATUS))->SetIcon(pApp->LoadIcon(IDI_LFRZE));
	((CButton*)GetDlgItem(IDC_FREEZE))->SetCheck(1);
	GetDlgItem(IDC_GRAF)->EnableWindow(TRUE);
	GetDlgItem(IDC_PERT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SF14)->EnableWindow(TRUE);//Aggiunto
	GetDlgItem(IDC_SNAP)->EnableWindow(FALSE); //Provvisorio: vale TRUE se funziona SNAP
	pMainMenu->EnableMenuItem(ID_FUNCTIONS_SNAPSHOT,MF_ENABLED); // Scommentare se funziona SNAP
	pMainMenu->EnableMenuItem(ID_FUNCTIONS_PERTURBATION,MF_ENABLED);
	if(!sincok) GetDlgItem(IDC_PINT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPEED)->EnableWindow(TRUE);
	GetDlgItem(IDC_APPLY)->EnableWindow(FALSE);
	pMainMenu->EnableMenuItem(ID_OPTIONS_TIME_HHMMSS,MF_ENABLED);
	pMainMenu->EnableMenuItem(ID_OPTIONS_TIME_ONLYSEC,MF_ENABLED);
	pMainMenu->EnableMenuItem(ID_FILE_OPEN,MF_GRAYED);
    
m_log.ReplaceSel( "Iniz. parametri controllo.	", FALSE );
	m_speed=1;
	m_pint=pShrMem1->dtint;
	UpdateData(FALSE);
	velocita=1;
	ritardo=0;
	snap=0;
	pertattive=0;
	stato=SFREEZE;
	if(prep_f22(APRI)==-1)
		AfxMessageBox("Impossibile creare file grafico");

m_log.ReplaceSel( "Inizio tread timesinc.		", FALSE );
	AfxBeginThread (timesinc,0);

m_log.ReplaceSel( "Fine sequenza play.	", FALSE );
m_log.ReplaceSel( "Rilascia Freeze per partire.", FALSE );

	CLgSincroDlg::OnFreeze();
GetDlgItem(IDC_FREEZE)->EnableWindow(TRUE);  // abilito freeze
}

UINT timesinc(LPVOID )
{ 
	float delta;
	ritardo=0;
	startTime=timeGetTime();
	m_prin->refresh();
	hEveS = OpenEvent( EVENT_ALL_ACCESS  ,TRUE,EVES); 
	hEveC = OpenEvent( EVENT_ALL_ACCESS  ,TRUE,EVEC);
	hEveCSINC = CreateEvent( NULL ,TRUE,TRUE,EVECSINC);
//	hEveCSINC = OpenEvent( EVENT_ALL_ACCESS  ,TRUE,EVECSINC);
	hEveCSINCOK = CreateEvent( NULL ,TRUE,TRUE,EVECSINCOK);
//sprintf(buffer,"timesinc: sincok=%d\n",sincok);
//m_prin->stampalog( buffer );
//m_prin->m_log.ReplaceSel( buffer, FALSE);
if(sincok) escifreeze=FALSE;
	while(pShrMem1->control[1] < 0.1)
	{
		waitevec=TRUE;
// Guag 27/01/05 introdotto tempo di timeout
		retWaittask = WaitForSingleObject(  hEveC,INFINITE);
//tolto provvisorio		retWaittask = WaitForSingleObject(  hEveC,TASK_TIMEOUT);
					if((retWaittask == WAIT_TIMEOUT) && (stato!=SFREEZE)) {
                        m_prin->m_log.ReplaceSel( "TASK ABORTED 1--------       ", FALSE );
						m_prin->refresh();
                        pShrMem1->control[2]=SSTOP;
						m_prin->ferma();
					}

//----------
		waitevec=FALSE;
//sprintf(buffer,"timesinc: Dopo Wait hEveC sincok=%d, escifreeze=%d gostep=%d, stato=%d\n",sincok,escifreeze,gostep);
//m_prin->m_log.ReplaceSel( buffer, FALSE);
//GUAG!
//		if(sincok && ( !gostep)) {
//		if(sincok && !escifreeze && !gostep) {
//		if(sincok && !escifreeze ) {
		if(sincok ) {
					ResetEvent(hEveCSINCOK);
					waitevecsincok=TRUE;					
					SetEvent(hEveCSINC);
// Guag 27/01/05 introdotto tempo di timeout
					retWait = WaitForSingleObject(  hEveCSINCOK,INFINITE);
//tolto	provvisorio				retWait = WaitForSingleObject(  hEveCSINCOK,TASK_TIMEOUT);
					if((retWait == WAIT_TIMEOUT) && (stato!=SFREEZE)) {
                        m_prin->m_log.ReplaceSel( "Simulink hang up       ", FALSE );					
//					    waitevecsincok=FALSE;	
//						m_prin->ferma();
					}
//----------
//m_prin->m_log.ReplaceSel( "Dopo Wait hEveCSINCOK", FALSE);
					waitevecsincok=FALSE;	
					if(pShrMem1->control[2]==SSTOP) m_prin->ferma();
		}
		if(stato==SFREEZE )
		{
			if(snap)
			{
			if(snap==1) snapshot();
			else readshot();
			}
//			escifreeze=FALSE;
			ResetEvent(hEveC);
            startTime= 0;
			m_prin->refresh();
		}
		else if (stato==SRUN || stato==MAXS || stato==SSTEP)
		{
			
			if( startTime > 0) delta=(pShrMem1->dtint*1000)/velocita-(timeGetTime()-startTime);
			else delta = 0;   // se startTime = 0 provengo dallo stato di freeze
			
			if(escifreeze || stato==SSTEP) {
				delta = 0;
				escifreeze=FALSE;
			}
			
			if ((delta>0)&&(stato==SRUN))
				Sleep((DWORD)(delta));

			if((ritardo-=delta)<0) 
				ritardo=0;
			startTime=timeGetTime();
			if(prep_f22(SCRIVI)==-1)
				AfxMessageBox("Impossibile scrivere file uscite!");
			
			if(pertattive)
				perturb();
			
			if(snap)
			{
				if(snap==1)
					snapshot();
				else
					readshot();
			}
			m_prin->refresh();
			ResetEvent(hEveC);
//			SetEvent(hEveS);
			if(stato==SRUN || stato==MAXS) SetEvent(hEveS);
			else if (gostep ) {
//				SetEvent(hEveS);
				gostep=FALSE;
				startTime= 0;
			}
		}
/*		else if (stato==SSTEP)
		{
			if(snap)
			{
			if(snap==1) snapshot();
			else readshot();
			}
			ResetEvent(hEveC);
			if(gostep) SetEvent(hEveS);	
            startTime= 0;	
		}
*/
	}
	//m_stop->SetState( TRUE );
	CloseHandle(hEveS);
	CloseHandle(hEveSINIT);
	CloseHandle(hEveC);
		CloseHandle(hEveCSINC);
		CloseHandle(hEveCSINCOK);
	CloseHandle(hMem1);

	return(0);	
}

LPVOID MapView(HANDLE hMap)
{
   LPVOID MappedPointer;

   MappedPointer= MapViewOfFile(hMap,
                                FILE_MAP_WRITE | FILE_MAP_READ,
                                0, 0, 0);
   if (MappedPointer == NULL)
   {
      AfxMessageBox("MapViewOfFile failed!");
		return(NULL);
   }
   else
      return(MappedPointer);
}

HANDLE OpenMap( LPSTR MapName)
{
   HANDLE hAMap;

   hAMap= OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
                          TRUE,
                          MapName);

   if (hAMap == NULL)
   {
      AfxMessageBox("OpenFileMapping failed!");
      return(NULL);
   }
   else
      return(hAMap);
}

void CLgSincroDlg::OnStop() 
{
	CLgSincroDlg::OnButtonStop(0);
}

void CLgSincroDlg::OnFreeze() 
{
	if(((CButton*)GetDlgItem(IDC_FREEZE))->GetCheck())
	{
		stato=SFREEZE;
		pShrMem1->control[2] = SFREEZE;
		pMainMenu->EnableMenuItem(ID_CONTROLS_RUN,MF_ENABLED);
		pMainMenu->EnableMenuItem(ID_CONTROLS_FREEZE,MF_GRAYED);
		GetDlgItem(IDC_STEP)->EnableWindow(TRUE);
		pMainMenu->EnableMenuItem(ID_CONTROLS_STEP,MF_ENABLED);
		((CStatic*)GetDlgItem(IDC_STATUS))->SetIcon(pApp->LoadIcon(IDI_LFRZE));
		GetDlgItem(IDC_MAXS)->EnableWindow(FALSE);
		pMainMenu->EnableMenuItem(ID_OPTIONS_SPEED_MAX,MF_GRAYED);
	}
	else
	{
		if(((CButton*)GetDlgItem(IDC_MAXS))->GetCheck()){
			stato=MAXS;
			pShrMem1->control[2] = MAXS;
		}
		else{
			stato=SRUN;
			pShrMem1->control[2] = SRUN;
		}
		pMainMenu->EnableMenuItem(ID_CONTROLS_RUN,MF_GRAYED);
		pMainMenu->EnableMenuItem(ID_CONTROLS_FREEZE,MF_ENABLED);
		GetDlgItem(IDC_STEP)->EnableWindow(FALSE);
		pMainMenu->EnableMenuItem(ID_CONTROLS_STEP,MF_GRAYED);
		((CStatic*)GetDlgItem(IDC_STATUS))->SetIcon(pApp->LoadIcon(IDI_LRUN));
		GetDlgItem(IDC_MAXS)->EnableWindow(TRUE);
		pMainMenu->EnableMenuItem(ID_OPTIONS_SPEED_MAX,MF_ENABLED);
		escifreeze=TRUE;
//		SetEvent(hEveC);
SetEvent(hEveS);
	}
}

void CLgSincroDlg::OnStep() 
{
//	if(waitevecsincok) return;
	stato=SSTEP;
	gostep=TRUE;
//	SetEvent(hEveC);
SetEvent(hEveS);
}

void CLgSincroDlg::OnMaxs() 
{
	
	if(((CButton*)GetDlgItem(IDC_MAXS))->GetCheck())
	{
		stato=MAXS;
		pShrMem1->control[2] = MAXS;
		GetDlgItem(IDC_SPEED)->EnableWindow(FALSE);
		pMainMenu->CheckMenuItem(ID_OPTIONS_SPEED_MAX,MF_CHECKED);
	}
	else
	{
		stato=SRUN;
		pShrMem1->control[2] = SRUN;
		GetDlgItem(IDC_SPEED)->EnableWindow(TRUE);
		pMainMenu->CheckMenuItem(ID_OPTIONS_SPEED_MAX,MF_UNCHECKED);
	}
}

void CLgSincroDlg::OnPert() 
{	
    if(!flag_pert_graf)
	{

	  if (m_scel == NULL)
		{
     	m_scel=new CSceltaDlg(this);
		m_scel->Create();
		}
	  else
	  {
		m_scel->SetActiveWindow();

	  }
	}
  

	if (flag_pert_graf) start_pert_scan();
	if (m_pert == NULL)
	{
		m_pert=new CPertDlg(this);
		m_pert->Create();
	}
	else
		m_pert->SetActiveWindow();
/*
	if (m_moni == NULL)
	{
		m_moni=new CMonitorDlg(this);
		m_moni->Create();
	}
	else
		m_moni->SetActiveWindow();
*/
}

void CLgSincroDlg::start_pert_scan()
{ 
//	OnSf14();
//   pMainMenu->CheckMenuItem(ID_GRAPHICS_MOD,MF_CHECKED);
//   flag_pert_graf=TRUE;
	char *path1;
	char *path2;
	UINT uExitCode =0;

	path1= getenv ("LG_TIX");

//	path2= getenv ("TIX_LIBRARY");
//	sprintf(ss,"%s/../win/"LAST_TIX" %s/select.tcl",path2,path1);
	path2= getenv ("TIX_BIN_EXE_NAME");
	sprintf(ss,"%s %s/select.tcl",path2,path1);

//	command.Format(ss);
//	WinExec(command,SW_SHOWNORMAL);
	if( selectHD != NULL )  TerminateProcess(  selectHD,  uExitCode ); 
 

	selectHD=lanciaproc(ss);


	m_monigraf->StartTimer();
}

void CLgSincroDlg::OnClose() 
{
	UINT uExitCode =0;

	if(AfxMessageBox("Quitting...\nAre you sure?",MB_YESNO  )==IDYES)
	{
		if(!(GetDlgItem(IDC_PLAY)->IsWindowEnabled()))
		{
//AfxMessageBox("Eseguo SSTOP");
			pShrMem1->control[1]=SSTOP;
			stato=SSTOP;
			pShrMem1->control[2] = SSTOP;
			pertattive=0;
		}
if( selectHD != NULL )  TerminateProcess(  selectHD,  uExitCode ); 
if( draw2grHD != NULL )  TerminateProcess(  draw2grHD,  uExitCode ); 
		CloseHandle(selectHD);
		CloseHandle(draw2grHD);


//AfxMessageBox("Eseguo setevent");
		SetEvent(hEveS);
		SetEvent(hEveC);
		CloseHandle(hMem1);

		timeEndPeriod(1);
//AfxMessageBox("distruggo window");
		CDialog::DestroyWindow();
	}
}

void CLgSincroDlg::OnApply() 
{
	CString val;
	UpdateData(TRUE);
	pShrMem1->dtint=m_pint;
	velocita=m_speed;
	GetDlgItem(IDC_APPLY)->EnableWindow(FALSE);
}

void CLgSincroDlg::OnChangeSpeed() 
{
	GetDlgItem(IDC_APPLY)->EnableWindow(TRUE);
}

void CLgSincroDlg::OnChangePint() 
{
	GetDlgItem(IDC_APPLY)->EnableWindow(TRUE);
//	((CButton*)GetDlgItem(IDC_APPLY))->SetIcon(pApp->LoadIcon(IDI_UPDRED));
}

void perturb ()
{
	extern int listapert;
	extern int listavar [12][2];
	extern CPertDlg *m_pert;
	
	int k;
	for (int j=0;j<pertattive;)
	{
		if(pertvar[j].tipo==3)
			if((pertvar[j].time -= pShrMem1->dtint)>0)
			{
				pShrMem1->uu[pertvar[j].nvar]+=(pertvar[j].grad)*(pShrMem1->dtint);
				j++;
				continue;
			}
		if(pertvar[j].tipo==2)
			pShrMem1->uu[pertvar[j].nvar]+=pertvar[j].endval;
		else
			pShrMem1->uu[pertvar[j].nvar]=pertvar[j].endval;
		listavar[pertvar[j].nlist][1]=-1;
		for(k=j;k<(listapert-1);k++)
		{
			pertvar[k]=pertvar[k+1];
			--listavar[pertvar[k].nlist][1];
		}
		pertvar[k].nvar=0;
		pertvar[k].tipo=0;
		pertvar[k].endval=0;
		pertvar[k].time=0;
		pertvar[k].grad=0;
		--listapert;
		--pertattive;
	}
	if(m_pert!=NULL)
		m_pert->Newvar(FALSE);
	return ;
}

void CLgSincroDlg::OnControlsStart() 
{
	CLgSincroDlg::OnPlay();
}

void CLgSincroDlg::OnControlsFreeze() 
{
	((CButton*)GetDlgItem(IDC_FREEZE))->SetCheck(1);
	CLgSincroDlg::OnFreeze();
}

void CLgSincroDlg::OnControlsStep() 
{
	CLgSincroDlg::OnStep();	
}

void CLgSincroDlg::OnControlsStop() 
{
	CLgSincroDlg::OnButtonStop(0);
}

void CLgSincroDlg::OnControlsRun() 
{
	((CButton*)GetDlgItem(IDC_FREEZE))->SetCheck(0);
	CLgSincroDlg::OnFreeze();
}

void CLgSincroDlg::OnOptionsTimeHhmmss() 
{
	orologio=TRUE;
	pMainMenu->CheckMenuRadioItem(ID_OPTIONS_TIME_HHMMSS,ID_OPTIONS_TIME_ONLYSEC,ID_OPTIONS_TIME_HHMMSS,MF_BYCOMMAND);
	CLgSincroDlg::refresh();
	CLgSincroDlg::scrivi_file_opzioni();
}

void CLgSincroDlg::OnOptionsTimeOnlysec() 
{
	orologio=FALSE;
	pMainMenu->CheckMenuRadioItem(ID_OPTIONS_TIME_HHMMSS,ID_OPTIONS_TIME_ONLYSEC,ID_OPTIONS_TIME_ONLYSEC,MF_BYCOMMAND);
	CLgSincroDlg::refresh();
	CLgSincroDlg::scrivi_file_opzioni();
}

void CLgSincroDlg::OnOptionsSpeedMax() 
{
	if(((CButton*)GetDlgItem(IDC_MAXS))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_MAXS))->SetCheck(0);
		pMainMenu->CheckMenuItem(ID_OPTIONS_SPEED_MAX,MF_UNCHECKED);
		CLgSincroDlg::OnMaxs();
	}
	else
	{
		((CButton*)GetDlgItem(IDC_MAXS))->SetCheck(1);
		pMainMenu->CheckMenuItem(ID_OPTIONS_SPEED_MAX,MF_CHECKED);
		CLgSincroDlg::OnMaxs();
	}
}

void CLgSincroDlg::OnSnap() 
{

	NomeSnap dlg;
	dlg.DoModal();
}

void snapshot()
{
	FILE *record;

	SetCurrentDirectory(locpath);
	if((record=fopen("snapshot.dat","a+"))==NULL)
	{
		AfxMessageBox("Impossibile creare il file snapshot.dat");
		snap=0;
		return;
	}
	fprintf(record,"^ %s\n",nomesnap);
	fprintf(record,"%6d %6d %6d",pShrMem1->nuu,pShrMem1->nxy,pShrMem1->ndati);
	fprintf(record,"\ntempo:\n* %f sec.\npasso int.#%d:\n* %f sec.",pShrMem1->tempo,pShrMem1->control[0],pShrMem1->dtint);
	fprintf(record,"\nSerie ingressi:\n*");
	for(int j=0;j<pShrMem1->nuu;j++)
	{
		fprintf(record,"\n%6d %s %13g",j,pShrMem1->nomeuu[j],(pShrMem1->uu[j])*(pShrMem1->cnuu[j]));
	}
	fprintf(record,"\nSerie uscite:\n*");
	for(int k=0;k<pShrMem1->nxy;k++)
	{
		fprintf(record,"\n%6d %s %13g",k,pShrMem1->nomexy[k],(pShrMem1->xy[k])*(pShrMem1->cnxy[k]));
	}
	fprintf(record,"\nSerie dati:\n*");
	for(int l=0;l<pShrMem1->ndati;l++)
	{
		fprintf(record,"\n%6d %13g",l,pShrMem1->dati[l]);
	}
    fprintf(record,"\n");
	fclose(record);
    snap14();
/*	in sviluppo ...  scritttura file di snapshot binario

    if((record=fopen("snapshotBIN.dat","a+"))==NULL)
	{
		AfxMessageBox("Impossibile creare il file snapshotBIN.dat");
		snap=0;
		return;
	}
	int numwritten;
	numwritten = fwrite( nomesnap, sizeof( nomesnap ),1, record );
    numwritten = fwrite( pShrMem1->tempo, sizeof( float ),1, record );
    numwritten = fwrite( pShrMem1->dtint, sizeof( float ),1, record );
// scrittura ingressi
    numwritten = fwrite( pShrMem1->nuu, sizeof( float ),1, record );
    numwritten = fwrite( pShrMem1->uu, sizeof( float ),pShrMem1->nuu, record );
// scrittura uscite
    numwritten = fwrite( pShrMem1->nxy, sizeof( int ),1, record );
    numwritten = fwrite( pShrMem1->xy, sizeof( float ),pShrMem1->nxy, record );
// scrittura dati
    numwritten = fwrite( pShrMem1->ndati, sizeof( int ),1, record );
    numwritten = fwrite( pShrMem1->dati, sizeof( float ),pShrMem1->ndati, record );
	fclose(record);	 	
*/
    snap=0;
}
void snap14()
{
	FILE *sn_f14, *sn_snap;
	char f14snapname[30], line[82], buff[21];
	int i=0;
	if((sn_f14=fopen("f14.dat","r"))==NULL)
	{
		AfxMessageBox("Impossibile aprire il file f14.dat");
		return;
	}   
    strcpy(f14snapname,"f14snap_");
	strcat(f14snapname,nomesnap);
	strcat(f14snapname,".dat");


	if((sn_snap=fopen(f14snapname,"w+"))==NULL)
	{
		AfxMessageBox("Impossibile creare il file f14snap.dat");
		return;
	}    
//leggo e scrivo 4 linee
	for(i=0;i<4;i++) {
	  if( fgets( line, 82, sn_f14 ) == NULL) 
		  AfxMessageBox("Impossibile leggere f14.dat");
      else{
         if( fputs(line, sn_snap ) > 0) AfxMessageBox("Impossibile scriver il file f14snap");
	  }
	}
	
	
//leggo e scrivo le uscite	
	for(i=0;i<pShrMem1->nxy;i++) {
		if( fgets( line, 82, sn_f14 ) == NULL) 
		  AfxMessageBox("Impossibile leggere f14.dat");
		else{
			formatta_float((double)(pShrMem1->xy[i])*(pShrMem1->cnxy[i]),buff);
			memcpy(line+14,buff,10);
		    if( fputs(line, sn_snap ) > 0) AfxMessageBox("Impossibile scriver il file f14snap");

		}
	}

//leggo e scrivo una linea
	  if( fgets( line, 82, sn_f14 ) == NULL) 
		  AfxMessageBox("Impossibile leggere f14.dat");
      else{
         if( fputs(line, sn_snap ) > 0) AfxMessageBox("Impossibile scriver il file f14snap");
	  }

//leggo e scrivo gli ingressi	
	for(i=0;i<pShrMem1->nuu;i++) {
		if( fgets( line, 82, sn_f14 ) == NULL) 
		  AfxMessageBox("Impossibile leggere f14.dat");
		else{
			formatta_float((double)(pShrMem1->uu[i])*(pShrMem1->cnuu[i]),buff);
			memcpy(line+14,buff,10);
		    if( fputs(line, sn_snap ) > 0) AfxMessageBox("Impossibile scriver il file f14snap");

		}
	}

//Leggo e scrivo il resto del file

	while(fgets( line, 82, sn_f14 ) != NULL) fputs(line, sn_snap );



fclose(sn_f14);
fclose(sn_snap);
}

	
void formatta_float( double numero, char *buff)
{
	int espon_num;
	char espon_ch[4];

	if(numero > 0) sprintf(buff,"%-#10.5g",numero);
	else sprintf(buff,"%-#10.4g",numero);
	
			
	if(buff[6] !='e') return;

	memcpy(espon_ch,buff+8,3);
	sscanf(espon_ch,"%d",&espon_num);
	if(espon_num <=99) {
			memcpy(buff+8,espon_ch+1,2);
			memcpy(buff+10,"\0",1);
			return;
	}
	else {
			if(numero > 0){
					sprintf(buff,"%-#10.4g",numero);
			}
			else {
					sprintf(buff,"%-#10.3g",numero);
	
			}
	}
	


}	

void readshot ()
{
	FILE *record;
	CString key="";
	int j,k;
	float ddqq=0;
    char ccqq[8];

	SetCurrentDirectory(locpath);
	if((record=fopen("snapshot.dat","r"))==NULL)
	{
		AfxMessageBox("Impossibile accedere al file snapshot.dat");
		snap=0;
		return;
	}

	rewind(record);
	while(key!=nomesnap)
	{
		while(key!="^")
			fscanf(record,"%s",key);
		fscanf(record,"%s",key);
	}
	while(key!="*")
		fscanf(record,"%s",key);
	fscanf(record,"%f",ddqq); // era &(pShrMem1->tempo)); tempo di simulazione
	key="";
	while(key!="*")
		fscanf(record,"%s",key);
	fscanf(record,"%f",ddqq); // era &(pShrMem1->dtint)); tempo di integrazione
	key="";
	while(key!="*")
		fscanf(record,"%s",key);
	for(j=0;j<pShrMem1->nuu;j++)
	{
		fscanf(record,"%d",&k);
		if(j==k)
		{
			fscanf(record,"%s",ccqq); //era &(pShrMem1->nomeuu[j])); nome della variabile di ingresso
			fscanf(record,"%f",ddqq);// era &(pShrMem1->uu[j]));
            pShrMem1->uu[j]=ddqq/pShrMem1->cnuu[j]; // nello snap è denormalizzato
		}
	}
	key="";
	while(key!="*")
		fscanf(record,"%s",key);
	for(j=0;j<pShrMem1->nxy;j++)
	{
		fscanf(record,"%d",&k);
		if(j==k)
		{
			fscanf(record,"%s",ccqq);// era &(pShrMem1->nomexy[j]));
			fscanf(record,"%f",ddqq);// era &(pShrMem1->xy[j]));
            pShrMem1->xy[j]=ddqq/pShrMem1->cnxy[j]; // nello snap è denormalizzato
		}
	}
	key="";
	while(key!="*")
		fscanf(record,"%s",key);
	for(j=0;j<pShrMem1->ndati;j++)
	{
		fscanf(record,"%d",&k);
		if(j==k)
		{
			fscanf(record,"%f",&(pShrMem1->dati[j]));
		}
	}
	fclose(record);
	snap=0;
	if(m_pert!=NULL)
		m_pert->Newvar(FALSE);
}

void CLgSincroDlg::OnFunctionsPerturbation() 
{
	CLgSincroDlg::OnPert();
}

void CLgSincroDlg::OnRecordingSnapshot() 
{
	CLgSincroDlg::OnSnap();
}

void CLgSincroDlg::sceldone()
{
	ASSERT(m_scel != NULL);
	m_scel = NULL;
}

void CLgSincroDlg::pertdone()
{
	ASSERT(m_pert != NULL);
	m_pert = NULL;

}

void CLgSincroDlg::monidone()
{
	ASSERT(m_moni != NULL);
	m_moni = NULL;
}

int prep_f22(int param)
{
	static char nomef22[100];
	static char titolo[100]={"titolazzo"}, str[80];
	static char nomef22tmp[]={"\\lgsincro_temp.f22"};
	static int nVAR=pShrMem1->nuu+pShrMem1->nxy;
	int  j,k;
	unsigned long bWrite;
	static HANDLE hf22;
//	static int Conta=0;

	switch (param)
	{
	case APRI:
		strcpy(nomef22,locpath);
		strcat(nomef22,nomef22tmp);

		hf22 = CreateFile(nomef22, GENERIC_READ | GENERIC_WRITE, 
			   	      FILE_SHARE_READ, 
					  (LPSECURITY_ATTRIBUTES) NULL, CREATE_ALWAYS,
				      FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);
   
		if (hf22 == INVALID_HANDLE_VALUE)
			return(-1);
		WriteFile(hf22, titolo, 80, &bWrite, (LPOVERLAPPED) NULL);
		WriteFile(hf22, &nVAR, sizeof(int), &bWrite, (LPOVERLAPPED) NULL);

		for(j=0;j<pShrMem1->nxy;j++)
		{
			strcpy(str,pShrMem1->nomexy[j]);
			strcat(str,"\t");
			strncat(str,pShrMem1->descrxy[j]+8,65);
			WriteFile(hf22, str, 80, &bWrite, (LPOVERLAPPED) NULL);
		}
		for(k=0;k<pShrMem1->nuu;k++)
		{
			strcpy(str,pShrMem1->nomeuu[k]);
			strcat(str,"\t");
			strncat(str,pShrMem1->descruu[k]+8,65);
			WriteFile(hf22, str, 80, &bWrite, (LPOVERLAPPED) NULL);
		}
//		CloseHandle(hf22);
		return (0);


	case CHIUDI:
//		CloseHandle(hf22);
		return (CloseHandle(hf22));

	case SCRIVI:
		Conta++;
		if( Conta >= GrafMult) {
			if (hf22 == INVALID_HANDLE_VALUE)
				return(-1);

			SetFilePointer(hf22, 0, (PLONG) NULL, FILE_END);

			punti[0]=(double)pShrMem1->tempo;
			for(j=0;j<pShrMem1->nxy;j++)
				punti[j+1]=(double)(pShrMem1->xy[j]*pShrMem1->cnxy[j]);
			for(k=0;k<pShrMem1->nuu;k++,j++)
				punti[j+1]=(double)(pShrMem1->uu[k]*pShrMem1->cnuu[k]);

			WriteFile(hf22, punti, (nVAR + 1)*sizeof(double), &bWrite, (LPOVERLAPPED) NULL);
//			CloseHandle(hf22);
			Conta=0;
		}
		return (0);
	}
	return (-1);
}

void CLgSincroDlg::OnGraf() 
{
  char *grafvar;
  char *path1;
  char *path2;
  UINT uExitCode =0;
  grafvar = getenv( "LG_GRAF" );

  if(flag_pert_graf) graftcl=1;
  else graftcl=0;

  if( graftcl == 0) {
    /* Get the value of the environment variable. */
	sprintf(comando,"%s\\grafics.exe -R=%d -FILE=%s\\lgsincro_temp.f22",grafvar,GrafRefr,locpath);
	if(!(WinExec(comando,SW_SHOWNORMAL)>31))
		AfxMessageBox("grafics.exe not found!");
  } else {
	path1= getenv ("LG_TIX");
//	path2= getenv ("TIX_LIBRARY");
	path2= getenv ("TIX_BIN_EXE_NAME");

//	sprintf(comando,"-R=%d -FILE=%s\\lgsincro_temp.f22",GrafRefr,locpath);
	sprintf(comando,"%s\\lgsincro_temp.f22 %d ",locpath,GrafRefr);

//	sprintf(ss,"%s/../win/"LAST_TIX" %s/draw2gr.tcl %s",path2,path1,comando);
	sprintf(ss,"%s %s/draw2gr.tcl %s",path2,path1,comando);

//  AfxMessageBox( ss );

//    command.Format(ss);
//	WinExec(command,SW_SHOWNORMAL);
	if( draw2grHD != NULL )  TerminateProcess(  draw2grHD,  uExitCode ); 
 

	draw2grHD=lanciaproc(ss);

  }

}

void CLgSincroDlg::OnFunctionsGraphics() 
{
	CLgSincroDlg::OnGraf();	
}


void CLgSincroDlg::OnFileOpen() 
{
	FILE * fpp;
	char *simvar;

m_log.ReplaceSel("Ricerca file tasks.dat ...	", FALSE );

    /* Get the value of the LIB environment variable. */
//DA FARE: se in locale /LOC allora non leggo il file tasks.dat e lancio la simulazione
	if(!sincok) {
		if(!sinclocale) {
				simvar = getenv( "LG_SIMULATORS" );
			    SetCurrentDirectory(simvar);
		}
	}
	while ((fpp=fopen("tasks.dat","r"))==NULL)
	{
		m_openf=new CFileDialog(TRUE,"dat","tasks*.dat");
		if((m_openf->DoModal())==IDCANCEL)
			return;
	}

	GetCurrentDirectory(100,locpath);
	SetWindowText(locpath);

m_log.ReplaceSel("Lettura file.		", FALSE );
	fscanf(fpp,"%[^\n]s",stopath);
//	fscanf(fpp,"%s",np);
// GUAG   Metto a 1 l'istanza della shared memory 
	strcpy(np,"1");
	fclose(fpp);
m_log.ReplaceSel("File caricato.		", FALSE );
     
CLgSincroDlg::leggi_file_opzioni();

}


void CLgSincroDlg::refresh()
{
	if(orologio)
		stringa.Format("%ih %im %.2fs",(int)(pShrMem1->tempo/3600),(int)(pShrMem1->tempo/60)%60,(pShrMem1->tempo)-((int)(pShrMem1->tempo/60))*60);
	else
		stringa.Format("%.2f sec",pShrMem1->tempo);
	GetDlgItem(IDC_SIMTIME)->SetWindowText(stringa);
	stringa.Format("%.2f s",ritardo/1000);
	GetDlgItem(IDC_DELAY)->SetWindowText(stringa);
//	if(pShrMem1->control[1]==SSTOP) m_stop.SetState( TRUE );
//	if(pShrMem1->control[1]==SSTOP) OnClose();
//	if(pShrMem1->control[1]==SSTOP) OnStop();
}

void CLgSincroDlg::ferma()
{

	m_prin->CLgSincroDlg::OnButtonStop( NOCONFERMA);

	
//	m_prin->CLgSincroDlg::OnClose();
//	char buffer[300];
//	sprintf(buffer,"CWnd::m_hWnd =%d ",CWnd::m_hWnd );
//    AfxMessageBox( buffer);
//	::DestroyWindow( iiqq );
//		CLgSincroDlg::iiqq->DestroyWindow();

/*	Se si desidera chiudere il programma ....
//AfxMessageBox("ferma: Eseguo SSTOP");
			pShrMem1->control[1]=SSTOP;
			stato=SSTOP;
			pShrMem1->control[2] = SSTOP;
			pertattive=0;

//AfxMessageBox("ferma: Eseguo setevent");
		SetEvent(hEveS);
		SetEvent(hEveC);
		CloseHandle(hMem1);

		timeEndPeriod(1);
//AfxMessageBox("ferma: distruggo window");
		DestroyWindow();  // destroy non funziona se chiamato dal Thread! 
		::exit(0); 
*/
}
void CLgSincroDlg::OnFileExit() 
{
	OnClose();
}

void CLgSincroDlg::OnOptgraf() 
{
	COptGrafDlg  Dlg;
	Dlg.m_grafmult = GrafMult;
	Dlg.m_grafrefr = GrafRefr;
// char stri[100];

	if(Dlg.DoModal() == IDOK )
	{
	   GrafMult = Dlg.m_grafmult;
	   GrafRefr = Dlg.m_grafrefr;
//	   sprintf(stri,"GrafMult=%d  GrafRefr=%f",GrafMult,GrafRefr);
//  AfxMessageBox( stri );

// scrittura opzioni nel file 
	   CLgSincroDlg::scrivi_file_opzioni();
	}
	
}
void CLgSincroDlg::ApriMon() 
{
	if (m_moni == NULL)
	{
		m_moni=new CMonitorDlg(this);
		m_moni->Create();
	}
	else
		m_moni->SetActiveWindow();
}

void CLgSincroDlg::OnInfoabout() 
{
	// TODO: Add your command handler code here
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
}

void CLgSincroDlg::OnButtonStop(int conf) 
{
	if(conf == 0){
  	if(AfxMessageBox("Stop simulation? Beware: all variables will be re-initialized.",MB_YESNO  )==IDNO)
  					return;
	}
	
		pShrMem1->control[1]=SSTOP;
		pShrMem1->control[2] = SSTOP;
		SetEvent(hEveS);
		SetEvent(hEveC);
		CloseHandle(hMem1);

		GetDlgItem(IDC_PLAY)->EnableWindow(TRUE);
		pMainMenu->EnableMenuItem(ID_CONTROLS_START,MF_ENABLED);
		GetDlgItem(IDC_FREEZE)->EnableWindow(FALSE);
		pMainMenu->EnableMenuItem(ID_CONTROLS_RUN,MF_GRAYED);
		pMainMenu->EnableMenuItem(ID_CONTROLS_FREEZE,MF_GRAYED);
		((CButton*)GetDlgItem(IDC_FREEZE))->SetCheck(0);
		GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
		pMainMenu->EnableMenuItem(ID_CONTROLS_STOP,MF_GRAYED);
		GetDlgItem(IDC_STEP)->EnableWindow(FALSE);
		pMainMenu->EnableMenuItem(ID_CONTROLS_STEP,MF_GRAYED);
		((CStatic*)GetDlgItem(IDC_STATUS))->SetIcon(pApp->LoadIcon(IDI_LSTOP));
		GetDlgItem(IDC_MAXS)->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_MAXS))->SetCheck(0);
		pMainMenu->EnableMenuItem(ID_OPTIONS_SPEED_MAX,MF_GRAYED);
		GetDlgItem(IDC_GRAF)->EnableWindow(FALSE);
		GetDlgItem(IDC_PERT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SNAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_SF14)->EnableWindow(FALSE);
		pMainMenu->EnableMenuItem(ID_FUNCTIONS_SNAPSHOT,MF_GRAYED);
		pMainMenu->EnableMenuItem(ID_FUNCTIONS_PERTURBATION,MF_GRAYED);
		pMainMenu->EnableMenuItem(ID_FILE_OPEN,MF_ENABLED);
		GetDlgItem(IDC_PINT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_APPLY)->EnableWindow(FALSE);

	if(prep_f22(CHIUDI)==0)
		AfxMessageBox("Impossibile chiudere il file dei grafici f22");
        strcpy(EVEC,"eveC\0"); 
		strcpy(EVES,"eveS\0");
		strcpy(EVESINIT,"eveSINIT\0");
		strcpy(MapName,"SharedLego\0");
}

void CLgSincroDlg::OnGraphicsMod() 
{
 if(pMainMenu->GetMenuState( ID_GRAPHICS_MOD, MF_BYCOMMAND) == MF_CHECKED)
			{
		 (pMainMenu->CheckMenuItem(ID_GRAPHICS_MOD,MF_UNCHECKED));
	     flag_pert_graf=FALSE;
			}   
     else 
		{ 
		 (pMainMenu->CheckMenuItem(ID_GRAPHICS_MOD,MF_CHECKED));
		 flag_pert_graf=TRUE;
		}
}

void CLgSincroDlg::OnSf14() 
{

	CLgSincroDlg::OnSnap();
/*
   pMainMenu->CheckMenuItem(ID_GRAPHICS_MOD,MF_CHECKED);
   flag_pert_graf=TRUE;
		char *path1;
		char *path2;
	    path1= getenv ("LG_TIX");
	    path2= getenv ("TIX_LIBRARY");
	    sprintf(ss,"%s/../win/"LAST_TIX" %s/select.tcl",path2,path1);
		command.Format(ss);
		WinExec(command,SW_SHOWNORMAL);
*/
}


int CLgSincroDlg::setregistro( char *subkeyname,char *valore )
{

 //
 // Scrive nella chiave di registro HKEY_CURRENT_USER\Software\LegoPc\LgSincro
 //
 
 HKEY hkResult;
 
 if ( (RegCreateKey( HKEY_CURRENT_USER, (LPCTSTR)"Software\\LegoPc\\LgSincro",  &hkResult)) != ERROR_SUCCESS)
//       printf("Fallita la creazione della chiave\n");
        return(1);
        
 if (RegSetValue( hkResult, (LPCTSTR)subkeyname, REG_SZ, (LPTSTR)valore, strlen(valore)) != ERROR_SUCCESS)
         return(2);
//       printf("Scrittura fallita\n");
         
 if ( RegCloseKey( hkResult ) != ERROR_SUCCESS) 
     return(3);
// printf("Fallita chiusura chiave di registro\n");

return(0);
}

int CLgSincroDlg::getregistro( char *subkeyname, char * valore, LONG * lunvalore)
{
 //
 // Legge dalla chiave di registro HKEY_CURRENT_USER\Software\LegoPc\LgSincro
 //

     HKEY hkResult;
//     *lunvalore=(LONG)sizeof(valore);
  if ( (RegOpenKey( HKEY_CURRENT_USER, (LPCTSTR)"Software\\LegoPc\\LgSincro",  &hkResult)) != ERROR_SUCCESS)
        return(1);
//       printf("Fallita la apertura della chiave\n");

 if (RegQueryValue( hkResult, (LPCTSTR)subkeyname, (LPTSTR)valore, lunvalore) != ERROR_SUCCESS)
       return(2);
//        printf("Lettura fallita\n");
        
  if ( RegCloseKey( hkResult ) != ERROR_SUCCESS) 
       return(3);
//  printf("Fallita chiusura chiave di registro\n"); 

return(0);
}

HANDLE lanciaproc (char *comando)
{
			
	    STARTUPINFO Si;
		PROCESS_INFORMATION Pi;
//		char buff1[300];
		
	    Si.cb = sizeof(STARTUPINFO); 
		Si.lpReserved = NULL; 
		Si.lpTitle = NULL; 
		Si.lpDesktop = ""; 
		Si.dwX = 0L; 
		Si.dwY = 0L; 
		Si.dwXSize = 0L; 
		Si.dwYSize = 0L; 
		Si.dwFlags = 0; 
		Si.wShowWindow = SW_SHOW; 
		Si.lpReserved2 = NULL; 
		Si.cbReserved2 = 0; 
// sprintf(buff1, "lanciaproc:   %s \n",comando);	
// MessageBox( NULL, buff1, "attenzione", MB_OK|MB_ICONINFORMATION );
		if( !CreateProcess( NULL,(LPTSTR)comando, NULL,NULL,FALSE,DETACHED_PROCESS , 
	   	NULL,NULL,&Si,&Pi))
	   	{	
MessageBox( NULL, "create proc di draw2gr.tcl o select.tcl FALLITA", "attenzione", MB_OK|MB_ICONINFORMATION );
			return (NULL);
		} 
		else
		{ 
//sprintf(buff1, "process:   %d  thread: %d    dwProcessId: %d\n",Pi.hProcess,Pi.hThread, Pi.dwProcessId);
//MessageBox( NULL, buff1, "attenzione", MB_OK|MB_ICONINFORMATION );
//		  lgsinhandle=Pi.hProcess;
//		  CloseHandle(Pi.hProcess);
//		  CloseHandle(Si.hProcess);
		}
return ( Pi.hProcess );
}

int CLgSincroDlg::leggi_file_opzioni()
{
FILE *fpopt;
char bufin[10];
	while ((fpopt=fopen("lgsincro_opt.dat","r"))==NULL)
	{
// non c'e file di opzioni
//AfxMessageBox( "errore apertura file lgsincro_opt.dat" );

		return (1);
	}

//	fscanf(fpopt,"Orologio: %[^\n]s",orologio);
//
//char ss1[100];
//sprintf(ss1,"orologio %d\n",orologio);
//AfxMessageBox( ss1 );

	fscanf(fpopt,"Orologio: %s",bufin);
	if (strncmp(bufin,"TRUE",4)==0) orologio = TRUE;
	else orologio = FALSE;


	pMainMenu=GetMenu();
	if( orologio ) pMainMenu->CheckMenuRadioItem(ID_OPTIONS_TIME_HHMMSS,ID_OPTIONS_TIME_ONLYSEC,ID_OPTIONS_TIME_HHMMSS,MF_BYCOMMAND);
       else pMainMenu->CheckMenuRadioItem(ID_OPTIONS_TIME_HHMMSS,ID_OPTIONS_TIME_ONLYSEC,ID_OPTIONS_TIME_ONLYSEC,MF_BYCOMMAND);

	fscanf(fpopt,"\nGrafMult: %d",&GrafMult);
	fscanf(fpopt,"\nGrafRefr: %d",&GrafRefr);

	fclose(fpopt);

	return (0);

}


int CLgSincroDlg::scrivi_file_opzioni()
{
FILE *fpopt;
	while ((fpopt=fopen("lgsincro_opt.dat","w"))==NULL)
	{
// errore scrittura file di opzioni
			return (1);
	}

//	fscanf(fpopt,"Orologio: %[^\n]s",orologio);
//
	if (orologio) fprintf(fpopt,"Orologio: %s\n","TRUE");
	else fprintf(fpopt,"Orologio: %s\n","FALSE");

	fprintf(fpopt,"GrafMult: %d\n",GrafMult);
	fprintf(fpopt,"GrafRefr: %d\n",GrafRefr);
	fclose(fpopt);

	return (0);

}

