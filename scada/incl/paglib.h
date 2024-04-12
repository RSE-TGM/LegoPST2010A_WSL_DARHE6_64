/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
	File di include relativo ai parametri e alle strutture utilizzati dai
				PAG 
 */

/* Identificativi per accedere alle risorse per i pag
 */

#define ID_RES1  0
#define ID_RES2  1
#define ID_RES3  2
#define ID_RES4  3
#define ID_RES5  4


/*
	Strutture per acccedere ai dati */

typedef struct {
			short flag;
			float v;} misan;

typedef union  {
			misan m;
			char  c[2];
			short s[3]; } MIS;

typedef long TOKEN;

/* 
	Moduli */

short WaitForTimeout(int);
short WaitForEvent(int,int,long *);
void trigpag(short);

void ModiAtti(short,short,short);      
void ModiPri(short,short);       
void PagTerm(short);       

TOKEN CnvTag(char *);        
short ReadDb(TOKEN,short *,float *);        
short WriteDbop(TOKEN,short,short,float);       
short WriteDb(TOKEN,short,float);       

short GetPagRes(short,short);
short SetPagRes(short);


#define AN_FS 0x8000
#define AN_FA 0x4000
#define AN_FZ 0x2000
#define AN_ST 0x1000
#define AN_AL 0x0400
#define AN_AU 0x0100
#define AN_RI 0x0040
#define AN_DH 0x0020
#define AN_DL 0x0010
#define AN_HS 0x0008
#define AN_LS 0x0004
#define AN_HC 0x0002
#define AN_LC 0x0001


#define DI_FS 0x8000
#define DI_FA 0x4000
#define DI_FZ 0x2000
#define DI_ST 0x1000
#define DI_IN 0x0800
#define DI_AU 0x0400
#define DI_RI 0x0200
#define DI_SL 0x0100


#define OR_FS 0x8000
#define OR_FA 0x4000
#define OR_FZ 0x2000
#define OR_ST 0x1000
#define OR_AU 0x0200
#define OR_RI 0x0100

#define MAXPAG  5
#define NUMPAG  2

#define OFFTRIGPAG 128
