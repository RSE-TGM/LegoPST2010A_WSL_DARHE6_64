// LgConcilDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LgConcil.h"
#include "LgConcilDlg.h"
#include "WNDlg.h"
#include "AlarmDlg.h"
#include "ParamDlg.h"

#include <direct.h>
#include "application.h"

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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLgConcilDlg dialog

CLgConcilDlg::CLgConcilDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLgConcilDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLgConcilDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon   = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_WNDlg   = NULL;
	m_AlarmDlg= NULL;
}

void CLgConcilDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLgConcilDlg)
	DDX_Control(pDX, IDC_ALARM_BUT, m_alarm_but);
	DDX_Control(pDX, IDC_WN, m_wn);
	DDX_Control(pDX, IDC_MODEL, m_model);
	DDX_Control(pDX, IDC_PARAMETERS, m_param);
	DDX_Control(pDX, IDC_FREEZE, m_freeze);
	DDX_Control(pDX, IDC_NOME_MODULO, m_nome_modulo);
 	DDX_Control(pDX, IDC_LOG, m_log);
	DDX_Control(pDX, IDCANCEL, m_quit);
	DDX_Control(pDX, IDC_INIT, m_init);
	DDX_Control(pDX, IDC_STOP, m_stop);
	DDX_Control(pDX, IDC_GRAPH, m_graph);
	DDX_Control(pDX, IDC_PERT, m_pert);
	DDX_Control(pDX, IDC_RUN, m_run);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLgConcilDlg, CDialog)
	//{{AFX_MSG_MAP(CLgConcilDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INIT, OnInit)
	ON_BN_CLICKED(IDC_RUN, OnStart)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_MODEL, OnButtonModel)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PARAMETERS, OnParameters)
	ON_BN_CLICKED(IDC_GRAPH, OnGraph)
	ON_BN_CLICKED(IDC_FREEZE, OnFreeze)
	ON_BN_CLICKED(IDC_INFO, OnInfo)
	ON_BN_CLICKED(IDC_PERT, OnPert)
	ON_BN_CLICKED(IDC_WN, OnWn)
	ON_BN_CLICKED(IDC_ALARM_BUT, OnAlarmBut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLgConcilDlg message handlers

BOOL CLgConcilDlg::OnInitDialog()
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

	pApp=AfxGetApp();
	if (pApp != 0)
	{
		((CButton*)GetDlgItem(IDC_INIT))->SetIcon(pApp->LoadIcon(IDI_INIT));
		((CButton*)GetDlgItem(IDC_RUN))->SetIcon(pApp->LoadIcon(IDI_RUN));
		((CButton*)GetDlgItem(IDC_FREEZE))->SetIcon(pApp->LoadIcon(IDI_FREEZE));
		((CButton*)GetDlgItem(IDC_STOP))->SetIcon(pApp->LoadIcon(IDI_STOP));
		((CButton*)GetDlgItem(IDC_PERT))->SetIcon(pApp->LoadIcon(IDI_PERT));
		((CButton*)GetDlgItem(IDC_WN))->SetIcon(pApp->LoadIcon(IDI_WN));
		((CButton*)GetDlgItem(IDC_GRAPH))->SetIcon(pApp->LoadIcon(IDI_GRAPH));
		((CButton*)GetDlgItem(IDC_ALARM_BUT))->SetIcon(pApp->LoadIcon(IDI_ALARM));
		((CButton*)GetDlgItem(IDCANCEL))->SetIcon(pApp->LoadIcon(IDI_QUIT));

	}
	
	// TODO: Add extra initialization here

	m_nome_modulo.SetWindowText("NONE");
	m_dialog = this;
	ConcilDir = getenv( "LG_CONCIL" );

	fntCourier.CreateFont( 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, "Courier" );

	m_dialog->m_log.SetFont(&fntCourier);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLgConcilDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLgConcilDlg::OnPaint() 
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
HCURSOR CLgConcilDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLgConcilDlg::OnInit() 
{
	DWORD retWait;
	CString text;
	FILE *fd;

    m_log.AddString("Compiling application ..."); //Compilazione server
	sprintf(str,"%s\\compile 2>temp.dat",ConcilDir);
 	system(str);
	AddMess(&(m_dialog->m_log));

	hEveS = CreateEvent( NULL ,TRUE,TRUE,"EVES"); //Creazione semafori client/server
	hEveC = CreateEvent( NULL ,TRUE,FALSE,"EVEC"); 

	FileConcil = (HANDLE) 0xFFFFFFFF; //Inizializzazione shared
	hMem1=CreateMap( FileConcil, (LPSTR) MapName, sizeof(MEMORIASHARED));
	pShrMem1 = (MEMORIASHARED *) MapView(hMem1);
	pShrMem1->tempo = 0.0;
	pShrMem1->control=0; //flag di terminazione

	srand((unsigned)time(NULL)); //seeding del generatore di numeri casuali (per white noise)

	m_dialog->m_log.AddString("Initializing ...");

	NumSensF14 = 0;
	if((fd = fopen("f14.dat","r")) == NULL) // Legge descrizioni sensori
		AfxMessageBox("File f14.dat doesn't exist!");
	else 
	{
		BOOL go = TRUE;
		for (int i=0;i<4;i++) fgets(str,100,fd);
		while (go) {
			fgets(str,100,fd);
			if (! _strnicmp(str+43,"*$",2)) { 
				strcpy(pShrMem1->SensDesc[NumSensF14],str+45);
				strncpy(pShrMem1->SenVarName[NumSensF14++],str+4,8);
			} else if (! _strnicmp(str,"*LG*DATI",8))
				go = FALSE;
		}
		fclose(fd);
	}
	
	if (deltat == 0) //se non è una ri-inizializzazione
	{
		if((fd = fopen("settings.dat","r")) == NULL)
			AfxMessageBox("File settings.dat doesn't exist!");
		else 
		{
			fscanf(fd,"%s\n",SensorsPath);
			if (SensorsPath[strlen(SensorsPath)-1] != '\\')
				strcat (SensorsPath, "\\");
			fscanf(fd,"%f\n",&deltat);
			upd_freq = (int) (deltat*1000.);
			fscanf(fd,"%f\n",&maxperc);
			fscanf(fd,"%f\n",&chiprob);
			fclose(fd);
			pShrMem1->chiprob=chiprob;
		}
	}

	strcpy(str,SensorsPath);
	strcat(str,"sensors.dat");
	if((fd = fopen(str,"r")) == NULL) // Legge valori sensori
		AfxMessageBox("File sensors.dat doesn't exist!");
	else 
	{
		ReadSens(fd,TRUE);
		fclose(fd);
		if(pShrMem1->SensNum != NumSensF14) {
			sprintf(str,"There are %d sensors in f14.dat and %d in sensors.dat!",
					NumSensF14,	pShrMem1->SensNum);	
			AfxMessageBox(str);
		}
		for(int i=0;i<pShrMem1->SensNum;i++)
			OldSens[i] = pShrMem1->SensValue[i]; // Inizializza vettore controllo stazionarietà
	}
	
	for (int i=0; i < pShrMem1->SensNum; i++) // Inizializza vettori gestione white noise
	{
		SensBand[i]=0;
		SensOffset[i]=0;
	}

	WinExec("proc\\LgCSer",SW_SHOWMINIMIZED); // lancia LEGO_WGS in automatico
//	AfxMessageBox("Run manually server, please!"); // richiede lancio manuale LgCSer

 	retWait = WaitForSingleObject(hEveC,INFINITE); //Aspetta fine calcoli server
	AddMess(&(m_dialog->m_log));

	m_param.EnableWindow(TRUE);
	m_run.EnableWindow(TRUE);
	m_model.EnableWindow(FALSE);
	m_init.EnableWindow(FALSE);
	m_stop.EnableWindow(TRUE);	
	m_pert.EnableWindow(FALSE);
	m_wn.EnableWindow(FALSE);
	m_graph.EnableWindow(FALSE);
	m_alarm_but.EnableWindow(FALSE);
	m_quit.EnableWindow(FALSE);
}

void CLgConcilDlg::OnStart() 
{

	m_dialog->SetTimer(1,upd_freq,NULL);
	is_running = TRUE;

	m_freeze.EnableWindow(TRUE);
	m_stop.EnableWindow(TRUE);	
	m_pert.EnableWindow(TRUE);
	m_wn.EnableWindow(TRUE);
	m_graph.EnableWindow(TRUE);	
	m_init.EnableWindow(FALSE);
	m_run.EnableWindow(FALSE);
	m_alarm_but.EnableWindow(TRUE);
	m_quit.EnableWindow(FALSE);
}

void CLgConcilDlg::OnStop() 
{
	int i;
	FILE *fp;
	char buff[200];

	m_dialog->KillTimer(1);
	is_running = FALSE;
	pShrMem1->control=1; // comando terminazione server
	SetEvent(hEveS); // sblocca il server affinche' termini

	Sleep(500);
	CloseHandle(hEveS);
	CloseHandle(hEveC);
	CloseHandle(hMem1);

	m_model.EnableWindow(TRUE);
	m_init.EnableWindow(TRUE);
	m_quit.EnableWindow(TRUE);
	m_run.EnableWindow(FALSE);
	m_freeze.EnableWindow(FALSE);	
	m_stop.EnableWindow(FALSE);	
	m_pert.EnableWindow(FALSE);	
	m_wn.EnableWindow(FALSE);
	m_graph.EnableWindow(FALSE);
	m_alarm_but.EnableWindow(FALSE);

	if (fp = fopen("eventlog.txt","w")) {
		for (i = 0; i< m_log.GetCount(); i++) {
			m_log.GetText(i,buff);
			fprintf(fp, "%s\n", buff);
		}
		fclose (fp);
	}
	m_log.ResetContent();

}

void CLgConcilDlg::OnButtonModel() 
{
	// TODO: Add your control notification handler code here

	CString s;
	m_nome_modulo.GetWindowText(s);

	ModelsDir = getenv( "LG_MODELS" );
    _chdir(ModelsDir);
	CFileDialog *m_f14;
	m_f14=new CFileDialog(TRUE,"tom","*.tom");
	if (m_f14->DoModal() == IDOK) {
		ModelName = m_f14->GetPathName();
		ModelName=ModelName.Left(ModelName.ReverseFind('\\'));
	    _chdir(ModelName);
		FILE *fd;
		if((fd=fopen("settings.dat","r")) != NULL)
			fclose(fd);
		else {
			sprintf(str,"copy %s\\settings.dat",ConcilDir);
			system(str);
		}
		if((fd=fopen("precond.for","r")) != NULL)
			fclose(fd);
		else {
			sprintf(str,"copy %s\\precond.for",ConcilDir);
			system(str);
		}
		ModelName=ModelName.Right(ModelName.GetLength()-ModelName.ReverseFind('\\')-1);

		m_nome_modulo.SetWindowText(ModelName);
		m_log.AddString("Reconciliation model has been set");
		m_init.EnableWindow(TRUE);
		m_quit.EnableWindow(TRUE);
		m_run.EnableWindow(FALSE);
		m_stop.EnableWindow(FALSE);	
		m_pert.EnableWindow(FALSE);	
		m_wn.EnableWindow(FALSE);
		m_graph.EnableWindow(FALSE);
		m_alarm_but.EnableWindow(FALSE);
	} else {
		m_nome_modulo.SetWindowText(s);
	}
	
}

void AddMess(CListBox *list) 
{
	FILE *fp;

	fp = fopen("temp.dat","r");
 	while (fgets(str,90,fp) != NULL) {
		list->AddString(str);
	}
	list->SetTopIndex((list->GetCount())-1);
	fclose(fp);
}

void CLgConcilDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	DWORD retWait;
	FILE *fd;
	float VarPu;
	int i;
	BOOL SensorsExists;
	int continua=0;

	retWait = WaitForSingleObject(hEveC,INFINITE); //Aspetta fine calcoli T-1

	pShrMem1->tempo += deltat; //incremento passo di tempo
	pShrMem1->chiprob=chiprob; //probabilità coda destra chi-square

    strcpy(str,SensorsPath);
	strcat(str,"sensors.dat");

	while (continua >= 0)
	{
		if((fd = fopen(str,"r")) == NULL) // Legge valori sensori
		{
			continua++;
			if (continua >= MAXTENTAT) {
				SensorsExists = FALSE;
				m_dialog->m_log.AddString("File sensors.dat doesn't exist!");
				m_dialog->m_log.SetTopIndex((m_dialog->m_log.GetCount())-1);
				return;	// skip di ogni altra operazione
			}
		} else {
			SensorsExists = TRUE;
			ReadSens(fd,FALSE);
			fclose(fd);
			if (pShrMem1->SensNum == NumSensF14)
				continua = -1;
			else {
				continua++;
				if (continua >= MAXTENTAT) {
					sprintf(str,"T = %8.2f num. %d sensors data found (%d expected)",
						pShrMem1->tempo, pShrMem1->SensNum, NumSensF14);
					m_dialog->m_log.AddString(str);
					m_dialog->m_log.SetTopIndex((m_dialog->m_log.GetCount())-1);
					return;	// skip di ogni altra operazione
				}
			}
		}
		if (continua >= 0)
			Sleep(DELAYTENT);
	}
	if (maxperc > 0) // Si richiede controllo di stazionarietà
	{ 
		float MaxVarPu= 0; 
		for (i=0;i<pShrMem1->SensNum;i++) {
			if (pShrMem1->SensorsON[i] != 0) {          //se sensore disponibile
			   VarPu = (pShrMem1->SensValue[i] - OldSens[i])/(pShrMem1->SensValue[i]);
			   if (VarPu < 0) VarPu = -VarPu; //prende il valore assoluto
			   MaxVarPu=max(MaxVarPu,VarPu);
			}
		}

		if (MaxVarPu < maxperc) {
			ResetEvent(hEveC);
			SetEvent(hEveS);
			retWait = WaitForSingleObject(hEveC,INFINITE); //Aspetta fine calcoli server
			AddMess(&(m_dialog->m_log));
		} else {
			sprintf(str,"T = %8.2f system state was not steady",pShrMem1->tempo);
			m_dialog->m_log.AddString(str);
			m_dialog->m_log.SetTopIndex((m_dialog->m_log.GetCount())-1);
		}
	} else {
		ResetEvent(hEveC);
		SetEvent(hEveS);
		retWait = WaitForSingleObject(hEveC,INFINITE); //Aspetta fine calcoli server
		AddMess(&(m_dialog->m_log));
	}
	

	for (i=0;i<pShrMem1->SensNum;i++) 
		OldSens[i]  = pShrMem1->SensValue[i];

	if (m_AlarmDlg != NULL && m_AlarmDlg->m_hold != TRUE) {
		m_AlarmDlg->m_Alarm_lbx.ResetContent();
		if (pShrMem1->AlarmNum >0) {
			for (i=0;i<pShrMem1->AlarmNum;i++) {
				m_AlarmDlg->m_Alarm_lbx.SetFont(&fntCourier);
				int index = pShrMem1->AlarmInd[i];
				memcpy(str,pShrMem1->SenVarName[index],8);
				sprintf(str+8,"         %f",pShrMem1->AlarmVal[i]);
 				m_AlarmDlg->m_Alarm_lbx.InsertString(-1,str);
			}
		}
	}
}

HANDLE CreateMap(HANDLE FileToBeMapped, LPSTR MapName, int dimshared)
{
   HANDLE MapHandle;

   MapHandle= CreateFileMapping(FileToBeMapped,
                                NULL,
                                PAGE_READWRITE,
                                0,
                                dimshared,
                                MapName);

   if (MapHandle == NULL)
   {
      fprintf(stderr,"CreateFileMapping\n");
      return(NULL);
   }
   else
      return(MapHandle);
}


LPVOID MapView(HANDLE hMap)
{
   LPVOID MappedPointer;

   MappedPointer= MapViewOfFile(hMap,
                                FILE_MAP_WRITE | FILE_MAP_READ,
                                0, 0, 0);
   if (MappedPointer == NULL)
   {
      fprintf(stderr,"MapViewOfFile\n");
      return(NULL);
   }
   else
      return(MappedPointer);
}

void CLgConcilDlg::OnParameters() 
{
	// TODO: Add your control notification handler code here
	CParamDlg dlg;

	dlg.m_freq = deltat;
	dlg.m_perc = maxperc;
	dlg.m_chi  = chiprob;

	if (dlg.DoModal() == IDOK) {
		maxperc=dlg.m_perc;
		chiprob=dlg.m_chi;
		deltat = dlg.m_freq;
		upd_freq = (int) (deltat*1000);
		KillTimer(1);
		if (is_running) m_dialog->SetTimer(1,upd_freq,NULL);
	}
}

void CLgConcilDlg::OnGraph() 
{
	// TODO: Add your control notification handler code here
	char *grafvar;
	int dtgraf = (int) (deltat + 0.5);

	/* check the graphic visualization time */
	dtgraf = (dtgraf > MINGRAFDT) ? dtgraf : MINGRAFDT;

    /* Get the value of the environment variable. */
    grafvar = getenv( "LG_GRAF" );

	sprintf(str,"%s\\grafics.exe -R=%d -FILE=lgconcil.f22",grafvar,dtgraf);

	if(!(WinExec(str,SW_SHOWNORMAL)>31))
		AfxMessageBox("grafics.exe not found!");	
}

void CLgConcilDlg::OnFreeze() 
{
	// TODO: Add your control notification handler code here
	m_dialog->KillTimer(1);	
	is_running = FALSE;
	m_run.EnableWindow(TRUE);
	m_freeze.EnableWindow(FALSE);
}

void CLgConcilDlg::OnInfo() 
{
	CAboutDlg dlg;

	dlg.DoModal();
}

void CLgConcilDlg::OnPert() 
{
	// TODO: Add your control notification handler code here
    sprintf(str,"notepad %s%s",SensorsPath,"sensors.dat");
	WinExec(str,SW_SHOWNORMAL);	
}

void CLgConcilDlg::OnCancel() 
{
	// TODO: Add extra cleanup here

	FILE *fd1, *fd2;
	CString s;

	m_nome_modulo.GetWindowText(s);

	if (s != "NONE") { //se è stato scelto un modello
		if ((fd1 = fopen("settings.dat","r")) == NULL) { // Salva valori preferenze utente
			AfxMessageBox("File settings.dat doesn't exist!");
		} else if ((fd2 = fopen("temp.dat","w")) == NULL) {
			AfxMessageBox("Impossible to write temporary file!");
		} else {
			fprintf(fd2,"%s\n",SensorsPath);
			fprintf(fd2,"%g\n",deltat);
			fprintf(fd2,"%g\n",maxperc);
			fprintf(fd2,"%g\n",chiprob);
			fgets(str,100,fd1);
			fgets(str,100,fd1);
			fgets(str,100,fd1);
			fgets(str,100,fd1);
 			while (fgets(str,100,fd1) != NULL)
				fputs(str,fd2);
			fclose(fd1);
			fclose(fd2);
			fd1 = fopen("settings.dat","w");
			fd2 = fopen("temp.dat","r");
 			while (fgets(str,100,fd2) != NULL)
				fputs(str,fd1);
			fclose(fd1);
			fclose(fd2);
		}
	}

	CDialog::OnCancel();
}

void CLgConcilDlg::OnWn() 
{
	// TODO: Add your control notification handler code here
	if (m_WNDlg == NULL)
	{
		m_WNDlg=new CWNDlg(this);

		BOOL result = m_WNDlg->Create();
 		if (result == 0) AfxMessageBox("Unable to create white noise dialog");
	}
	else
		m_WNDlg->SetActiveWindow();	
}

void CLgConcilDlg::ReadSens(FILE *fd,BOOL init)
{
		int i = 0;
		int SensorON;
		char riga[80];
		float temp, temp2, halfband, scarto;

		while (fgets(riga, 80, fd)) {
			int NumberOfItems = sscanf(riga,"%f %d",&temp,&SensorON);
			if (NumberOfItems == 1) SensorON = 1;
			if(NumberOfItems == 1 || (NumberOfItems == 2 && SensorON != 0)) { 
														//sensore disponibile
				if (! init) { 
					temp2 = temp;
					if (SensBand[i] != 0) {
						halfband = temp*SensBand[i]/100; //calcolo semibanda
						scarto = (2*halfband/RAND_MAX) * rand()-halfband; 
						temp += scarto;     // Aggiunta valore pseudocasuale
					}
					if (SensOffset[i] != 0) 
						temp += temp2 * SensOffset[i]/100;  // Aggiunta offset
				}

				pShrMem1->SensValue[i] = temp;

			}

			pShrMem1->SensorsON[i++] = (SensorON == 0) ? 0 : 1;
		}
		pShrMem1->SensNum = i;
}

void CLgConcilDlg::WNDone()
{
	ASSERT(m_WNDlg != NULL);
	m_WNDlg = NULL;
}

void CLgConcilDlg::AlarmDone()
{
	ASSERT(m_AlarmDlg != NULL);
	m_AlarmDlg = NULL;
}

void CLgConcilDlg::OnAlarmBut() 
{
	// TODO: Add your control notification handler code here
	if (m_AlarmDlg == NULL)
	{
		m_AlarmDlg=new CAlarmDlg(this);

		BOOL result = m_AlarmDlg->Create();
 		if (result == 0) AfxMessageBox("Unable to create alarm dialog");
	}
	else
		m_AlarmDlg->SetActiveWindow();		
}