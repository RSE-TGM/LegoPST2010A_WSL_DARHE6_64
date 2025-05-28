#define N000 160
#define N001 N000*10
#define N002 N000*25 
#define N003 N000*50
#define N004 N000*25 
#define N005 N000*100 
#define N006 100
#define N007 N000*500
#define N008 40 
#define NR00 12 
#define NP00 10

#define M003 N002+1 
#define M004 N003+1
#define M005 N004+1
#define M001 N005-N003
#define M002 M001-N004

#define M006 N003*NR00
#define M007 2*M006
#define M008 5*N003
#define M009 8*N003
#define M010 N004+N003
#define MP01 NP00+1
#define MP02 NP00*200

extern struct c0lg5a {
		float XY[N003];
		float UU[N004];
		float XYU[N005];
		float DATI[N007];
		float CNXYU[N005];
		float TOLL[N003];
		float DATPER[MP02];
		int NOSL[N001];
		int NOSUB[N002];
		int NOBLC[N002][2];
		int NUSTA[N002];
		int NUSCI[N002];
		int NINGR[N002];
		int ISLB[N002];
		int IP[M003];
		int IPVRS[N005];
		int IPS[M004];
		int IPVRT[N005];
		int IPI[M005];
		int IPVRI[M001];
		int IPDATI[M003];
		int IPLOT[N003];
		int ISTMP[N003];
		int IVPER[NP00];
		int ITPER[NP00];
		int IPPER[MP01];
} _CC0LG5A;

extern struct integr {
		float TSTOP;
		float TEMPO;
		float DTINT;
		int   NPAS;
		float CDT;
		float ALFADT;
} _CINTEGR;


extern struct parint {
		int   ITITOL;
		float TFIN;
		float TSTEP;
		float FATOLL;
		int   INTERR;
		float TINTER;
} _CPARINT;

extern struct inpar1 {
		int   NBL;
		int   NEQAL;
		int   NEQSIS;
		int   NU;
		int   NST;
		int   NVART;
		int   NPVRT;
		int   NVRI;
		int   NDATI;
} _CINPAR1;

extern struct c0lg5d {
		char VAR[8][N005];
		char SIVAR[8][N003];
		char VARI[8][N004];
		char VARSYS[8][N003];
} _CC0LG5D;

extern struct serbido {
		int   NX2;
		int   NX3;
		int   NX4;
		int   NX8;
		int   MX7;
		int   MX10;
		int   IGRAD;
		int   IVAI;
		float CNXY[N003];
		float CNUU[N004];
		float XYOUT[M010];
		char  SYOUT[8][M010];
		int   ICDTR;
		float CDTN;
		float PX[N003];
		int   IQNMX;

} _CSERBIDO;

extern struct serdesc {
		char  NMSIVA[100][N003];
		char  NMVARI[100][N004];
		
} _CSERDESC;

#define LUNGCURDIRBUF 100
#define DIMCONTROL 50

#define MAXUSC 40
#define MAXING 40

#define MAXRIGA 100
#define MAXTOK 20

#define TIPOXY 1
#define TIPOUU 2

#define APRI 0
#define LEGGI 1
#define CLOSE 2



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

char *fileDati="\\simul.dat";
static char modelPath[LUNGCURDIRBUF];
static char nomefile[LUNGCURDIRBUF];
float tstep;


char EVEC[20]="eveC";
char EVES[20]="eveS";
char EVESINIT[20]="eveSINIT";

#define RESTART pShrMem1->control[2]
