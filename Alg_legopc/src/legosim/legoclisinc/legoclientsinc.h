#define N000 70
 
#define N003 N000*50
#define N004 N000*25 
#define N007 N000*500

#define DIMCONTROL 50
#define MAXUSC 40
#define MAXING 40
#define TIPOXY 1
#define TIPOUU 2


#define INIT 0
#define STEP 1
#define ENDLEGO 2

#define SFREEZE 0
#define SSTOP 1


#define TASK_TIMEOUT 5000

int CercaInd(int, char *);


typedef struct varTable {
			char nome[9];
			int ind;
		} VARTABLE;
	
typedef struct {
		float   xy[N003];
		float   uu[N004];
		float   dati[N007];
		float   cnxy[N003];
		float   cnuu[N004];
		int     nxy;
		int 	nuu;
		int 	ndati;
		float 	tempo;
		float 	dtint;
		char 	nomexy[N003][9];
		char 	nomeuu[N004][9];
		int     control[DIMCONTROL];
		char    descrxy[N003][100];
		char    descruu[N004][100];
} MEMORIASHARED;
static MEMORIASHARED  *pShrMem1;

VARTABLE varsc_usc[MAXUSC], varsc_ing[MAXING];
int num_usc,num_ing;	

LPVOID MapView(HANDLE);
HANDLE OpenMap(LPSTR);

static HANDLE hEveS,hEveC,hEveCSINC,hEveSINIT,hEveCSINCOK; //handle semafori server/client
DWORD retWait;

	//static float *pShrMem1 = NULL; //puntatore shared memory
static HANDLE hMem1    = NULL; //handle shared memory	
 
HANDLE 	FileToBeMapped; //nome file condiviso (essendo in memoria
							//ha un nome convenzionale)
char EVEC[20];
char EVECSINC[20];
char EVECSINCOK[20];
char EVES[20];
char EVESINIT[20];
char evesbase[]="eveS";
char evesinitbase[]="eveSINIT";
char evecbase[]="eveC";
char sharelegobase[]="SharedLego";
char simulname[]="\\simul.dat";
char tasksname[]="tasks.dat";
char startserverbase[]="lgser s";

#define RESTART pShrMem1->control[2]
