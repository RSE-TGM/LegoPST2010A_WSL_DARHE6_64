#define N000 70
#define N003 N000*50
#define N004 N000*25 
#define NXY N000*50
#define NUU N000*25
#define NDATI N000*500
#define DIMCONTROL 50
#define NUMVAR NXY+NUU
#define NUMPUNTI NUMVAR+1


#define INDACCSHM  3
#define INDPICT    4

typedef struct {
		float   xy[NXY];
		float   uu[NUU];
		float   dati[NDATI];
		float   cnxy[NXY];
		float   cnuu[NUU];
		int     nxy;
		int 	nuu;
		int 	ndati;
		float 	tempo;
		float 	dtint;
		char 	nomexy[NXY][9];
		char 	nomeuu[NUU][9];
		int     control[DIMCONTROL];
		char    descrxy[N003][100];
		char    descruu[N004][100];

} MEMORIASHARED;

typedef struct {
	int		nlist;
	int		nvar;
	int		tipo;
	float	endval;
	float	grad;
	float	time;
} PERTURBAZIONE;


/**********************************************/


char MapName[20]="SharedLego";

LPVOID MapView(HANDLE);
HANDLE OpenMap(LPSTR);
static HANDLE hMem1 = NULL;

DWORD retWait;
char np[3];
