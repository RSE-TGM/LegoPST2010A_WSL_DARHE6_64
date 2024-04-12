#include <stdio.h>
#include <string.h>
#include <windows.h>

#define N000 70
#define N005 N000*100
#define MAXSENS 200

HANDLE OpenMap(LPSTR); //prototipi funzioni gestione shared
LPVOID MapView(HANDLE);

static HANDLE hEveS, hEveC; //handle per semafori
static HANDLE hMem1; //handle per shared
static HANDLE hf22; //handle per f22

typedef struct {
	int     control;
	float	tempo;
	float	chiprob;
	int	SensNum;
	int	AlarmNum;
	char	SenVarName[MAXSENS][8];
	char	SensDesc[MAXSENS][100];
	float	SensValue[MAXSENS];
	int	SensorsON[MAXSENS];
	int	AlarmInd[MAXSENS];
	float	AlarmVal[MAXSENS];
} MEMORIASHARED; //Struttura shared
static MEMORIASHARED  *pShrMem1; //Puntatore alla shared

char MapName[20] = "SharedConcil"; //Nome area di memoria

extern struct cfor1 {
	int     nxy;
	int 	nuu;
	char 	nomexy[8][N005];
	char 	nomeuu[8][N005];
} _CCFOR1; //struttura di collegamento C-FORTRAN

extern struct cfor2 {
	float 	TEMPO;
	int     nxy;
	int 	nuu;
	float   xy[N005];
	float   uu[N005];
} _CCFOR2; //struttura di collegamento C-FORTRAN

extern struct cfor3 {
	float   cnxy[N005];
	float   cnuu[N005];
} _CCFOR3; //struttura di collegamento C-FORTRAN

extern struct cdesc {
	char    descrxy[100][N005];
	char    descruu[100][N005];
} _CDESC; //struttura di collegamento C-FORTRAN

extern struct csens {
	int	SENSNUM;
	int	NOTAVAIL;
	float	SENSVALUE[MAXSENS];
	int	SENSORSON[MAXSENS];
} _CSENS; //struttura di collegamento C-FORTRAN

extern struct calarm {
	int	ALARMNUM;
	int	ALARMIND[MAXSENS];
	float	ALARMVAL[MAXSENS];
} _CALARM; //struttura di collegamento C-FORTRAN

extern struct chisquare {
	int	ngdl;
	float	xchi;
	int	iwzero;
} _CCHISQUARE; //struttura di collegamento C-FORTRAN
	
double poz(double z); //Prototipi funzioni calcolo chi-square
double pochisq(double x, int df);
double critchi(double p, int df);

BOOL   DoVerif;        //flag esecuzione test chi-square
char   s[200];         //Stringa per utilizzi vari

