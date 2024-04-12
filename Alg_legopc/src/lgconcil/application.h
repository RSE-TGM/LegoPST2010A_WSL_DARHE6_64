#define N000 70
#define N003 N000*50
#define N004 N000*25 
#define NXY N000*50
#define NUU N000*25
#define NUMVAR NXY+NUU
#define NUMPUNTI NUMVAR+1
#define MAXSENS 200

#define MINGRAFDT   1  // Minimum step for GRAPHICS auto-update (seconds)
#define MAXTENTAT   9  // Maximum attempts on SENSORS.DAT reading errors
#define DELAYTENT 100  // Delay (msec) between SENSORS.DAT reading attempts

float deltat = 0; // Reconciliation frequency [s]
float maxperc = 0; // Max value [p.u.] for sensors changings to be steady
float chiprob;     // Right queue probability of chi-square distribution
int upd_freq = 0;  // Timer frequency [msec]
float OldSens[MAXSENS]; // Auld sensor values for steady state control

static HANDLE hEveS, hEveC; // Server/Client Semaphores

char str[200];

char *ModelsDir;
CString ModelName;	
char *ConcilDir;
char SensorsPath[100];

BOOL  is_running = FALSE;

void AddMess(CListBox *);
CLgConcilDlg *m_dialog;
CWNDlg *m_WNDlg;
CAlarmDlg *m_AlarmDlg;
CFont   fntCourier;	
int NumSensF14 = 0;

typedef struct {
	int     control;
	float	tempo;
	float	chiprob;
	int		SensNum;
	int		AlarmNum;
	char	SenVarName[MAXSENS][8];
	char	SensDesc[MAXSENS][100];
	float	SensValue[MAXSENS];
	int		SensorsON[MAXSENS];
	int		AlarmInd[MAXSENS];
	float	AlarmVal[MAXSENS];
} MEMORIASHARED; // Shared struct

static HANDLE hMem1 = NULL; // Handle shared memory
HANDLE FileConcil; //Nome file condiviso
char MapName[20] = "SharedConcil"; //Nome area di memoria
MEMORIASHARED  *pShrMem1; //Puntatore alla shared

HANDLE CreateMap(HANDLE,LPSTR, int); //Prototipi funzioni gestione shared
LPVOID MapView(HANDLE);

float SensBand[MAXSENS]; //Vettori per gestione white noise
float SensOffset[MAXSENS];
