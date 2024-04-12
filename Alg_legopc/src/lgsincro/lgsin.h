char EVEC[20]="eveC";
//GUAG! 
   char EVECSINC[20]="eveC";
   char EVECSINCOK[20]="eveC";
char EVES[20]="eveS";
char EVESINIT[20]="eveSINIT";
char MapName[20]="SharedLego";

LPVOID MapView(HANDLE);
HANDLE OpenMap(LPSTR);
static HANDLE hEveS,hEveC,hEveSINIT,hMem1 = NULL;
//GUAG!
    static HANDLE hEveCSINC;
	static HANDLE hEveCSINCOK;
	bool sincok=FALSE;
	bool sinclocale=FALSE;
DWORD retWait;
DWORD retWaittask;

UINT timesinc(LPVOID);
void perturb();
void snapshot();
void readshot();
void snap14();
void formatta_float( double , char * );
int prep_f22(int);

double punti[NUMPUNTI];
CString stringa;
DWORD startTime;
CString nomesnap;
bool apply;
char locpath[100];
char stopath[100];
float velocita;
float ritardo;
char stato;
char snap;
int pertattive;
int GrafMult=1;
int GrafRefr=1;


#define SFREEZE 0
#define SSTOP 1
#define SRUN 2
#define SSTEP 3
#define MAXS 4

#define APRI 1
#define SCRIVI 2
#define CHIUDI 3

#define NOCONFERMA 1
#define TASK_TIMEOUT 5000

bool  flag_pert_graf=TRUE;

HANDLE lanciaproc (char *);
HANDLE draw2grHD = NULL, selectHD = NULL;

