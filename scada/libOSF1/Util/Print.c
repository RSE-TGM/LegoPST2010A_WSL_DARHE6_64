/**********************************************************************
*
*       C Source:               Print.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Thu Jul  1 13:56:14 2004 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: Print.c-10 %  (%full_filespec: Print.c-10:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <Marte/MarteP.h>
#include <Marte/TaskMarte.h>
#include <Util/code.h>
#include <g1tipdb.inc>
#include <g2comdb.inc>
#include <comunic.inc>
#include <mesqueue.h>
#include <print.inc>
#include <diagnodi.inc>
#include <mesprocv.inc>
#include <virtinv.h>

extern short qperif_00;
extern short c_mmii;

#define LUN_TESTO	6000  // lunghezza massima del buffer di stampa

static void invia_diagno(int ,int );
static void output_coda(char * ,char * );
static void str_ascii(char *,int );
static void sistema_dollaro(char *);
static int invia_cambio_riga_xterm(char *,int *,int);
static int invia_cambio_pagina_xterm(int);

print()
{
int coda;
int i;
pthread_t self;
int printer;
QUEUE_PACKET packs;
S_FORAL *dato;
short diagno = -1;
char *riga;
char nomefile_log[FILENAME_MAX+1];
FILE *fp_log;
char comando_xterm[2000];
char *path_scada_bin;
char nome_file_tty[FILENAME_MAX+1];
char nome_coda[255];
int tipo_xterm = 0;
int tipo_queue = 0;
FILE *fp_tty=NULL;
char testo[LUN_TESTO];
int lun_testo=0;

self = pthread_self();
for (i=0;i<MAX_THREAD; i++)
                if( pthread_equal(self, PuntTcb[i].id)== 1)
                        break;
if(i == MAX_THREAD)
            return(-1);
printer = i - PRINT_00_TCB;

/*
	verifico se la stampante è locale
*/
if(fisdev[printer].remota != 0)
	{
	SetTaskState(printer+PRINT_00_TCB,INACTIVE_STATE);
	return;
	}

/*
	E' gestita la stampante su terminale (XTERM) e su coda (QUEUE)
*/
//printf("tipo stampante [%d] = %s\n",printer,fisdev[printer].remname);
if(strcmp(fisdev[printer].remname,"XTERM")==0)
	tipo_xterm = 1;
if(strncmp(fisdev[printer].remname,"QUEUE",5)==0)
	{
	char *app;

	app = strstr(fisdev[printer].remname,"_");
	if(app!=NULL)
		{
		++app;
		strcpy(nome_coda,app);
		tipo_queue = 1;
		}
	else
		{
		tipo_queue = 0;
		}
	}

if(!(tipo_queue || tipo_xterm))
	{
	SetTaskState(printer+PRINT_00_TCB,INACTIVE_STATE);
	return;
	}

coda = qperif_00 + printer;

switch (printer)
	{
	case 0:{diagno =stprn1; break;}
	case 1:{diagno =stprn2; break;}
	case 2:{diagno =stprn3; break;}
	case 3:{diagno =stprn4; break;}
	case 4:{diagno =stprn5; break;}
	case 5:{diagno =stprn6; break;}
	case 6:{diagno =stprn7; break;}
	case 7:{diagno =stprn8; break;}
	}
if(diagno == -1)
	return;

if(tipo_xterm)
  {
  if((path_scada_bin= getenv("SCADA_BIN"))==NULL)
	return;

  // costruisce il nome del file apptty
  sprintf(nome_file_tty,"apptty%d",printer);
  // se il file apptty... e' gia' presente lo elimina e si sospende
  // per 2 secondi
  if((fp_tty=fopen(nome_file_tty,"r"))!=NULL)
	{
	fclose(fp_tty);
	unlink(nome_file_tty);
	wai(36);
	}

  sprintf(comando_xterm,"/usr/bin/X11/xterm -T PRN%d -sb -sl 1000 -geometry 132x40 -iconic -e %s/UtilPrint %d &",
		printer,path_scada_bin,printer);

  system(comando_xterm);
  // attende che sia creata la stampante XTERM
  while(1)
	{
	if((fp_tty=fopen(nome_file_tty,"r"))!=NULL)
		{
		fclose(fp_tty);
		break;
		}
	wai(10);
	}
  }

// invia lo stato ON a scgev
invia_diagno(diagno,1);

/*
printf("task print [%d] coda = %d diagno = %d remota = %d name = %s\n",
		printer,coda,diagno,
		fisdev[printer].remota,fisdev[printer].remname);
printf("tipo_xterm = %d tipo_queue = %d\n",tipo_xterm,tipo_queue);
*/


packs.flg=MSG_WAIT;
packs.wto=0;
packs.amsg=(char *)malloc(9000);
packs.que=coda;

/*
	Apre il file di log della stampante
*/
/*
sprintf(nomefile_log,"Printer%d",printer);
fp_log=fopen(nomefile_log,"w");
fclose(fp_log);
*/

// azzero i buffer di stampa testo
memset(testo,0,LUN_TESTO);
lun_testo = 0;

while(1)
	{
        dequeue(&packs);
	dato=(S_FORAL *)packs.amsg;
	riga=(char*)malloc(dato->hea.lung-sizeof(HEA_STA));
	memcpy(riga,&dato->blank_1,dato->hea.lung-sizeof(HEA_STA));
/*
	fp_log=fopen(nomefile_log,"a");
	fprintf(fp_log,"%s\n",riga);
	fclose(fp_log);
*/
	for(i=0;i<dato->hea.lung-sizeof(HEA_STA);i++)
		{
		if(riga[i]==0x0c) // cambio pagina
			{
        		if(tipo_xterm)
				invia_cambio_pagina_xterm(printer);
			i++;
			continue;
			}
		if(riga[i]==0x0d) // cambio riga
			{
        		if(tipo_xterm)
			    invia_cambio_riga_xterm(testo,&lun_testo,printer);
			i++;
			continue;
			}
		testo[lun_testo]=riga[i];
		++lun_testo;
		}

        if(tipo_queue)
          {
	  str_ascii(riga,dato->hea.lung-sizeof(HEA_STA));
//printf("coda tipo queue = %d\n",tipo_queue);
	  output_coda(nome_coda,riga);
	  }
	free(riga);
	}
}


static void invia_diagno(int codice,int stato)
{
QUEUE_PACKET pack_diagno;
S_MDIA  dia;

pack_diagno.flg=MSG_WAIT;
pack_diagno.wto=0;
pack_diagno.amsg=(char*)&dia;
pack_diagno.que=c_mmii;
pack_diagno.lmsg=h_dia + sizeof(S_ALDIA);

dia.nodo = 0;
dia.indice = mdia;
dia.a[0].allarme = codice;
dia.a[0].condiz = !stato;

enqueue(&pack_diagno);
}

static void output_coda(char * coda,char * testo)
{
char comando[255];

sprintf(comando,"echo \"%s\" | lpr -h -P%s ",testo,coda);
system(comando);
}


static void str_ascii(char * riga,int lun)
{
int i;

for(i=0;i<lun-1;i++)
	if((riga[i]<32)||(riga[i]>126))
		{
		//printf("posizione %d valore %d\n",i,riga[i]);
		riga[i]=' ';
		}
riga[lun] = 0;
}

void sistema_dollaro(char *riga)
{
char *iniz;
char *app;
int diff;

app=riga;
iniz=riga;
while((app=strstr(app,"$"))!=NULL)
        {
        *app=0;
#if defined LINUX
        sprintf(riga,"%s@%s",riga,app+1);
#else
        sprintf(riga,"%s\"\\$\"%s",riga,app+1);
#endif
        app +=4;
        }
}



static int invia_cambio_riga_xterm(char *testo,int *lun,int printer)
{
char comando_xterm[1000];

testo[*lun]=0;

sistema_dollaro(testo);
sprintf(comando_xterm,"echo \"%s\" > `cat apptty%d`",
		testo,printer);
system(comando_xterm);

*lun=0;
}

static int invia_cambio_pagina_xterm(int printer)
{
char comando_xterm[1000];

sprintf(comando_xterm,"echo \"%s\" > `cat apptty%d`",
	"----------------------------------------------------------------------------------------------------------------------------------",
	printer);
system(comando_xterm);
}

