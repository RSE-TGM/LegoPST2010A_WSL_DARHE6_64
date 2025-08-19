/**********************************************************************
*
*       C Source:               Shell1_aus.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Thu Oct  9 16:03:24 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: Shell1_aus.c-3 %  (%full_filespec: Shell1_aus.c-3:csrc:1 %)";
#endif
/*******************************************************************************
Shell1_aus.c
  Funzioni ausiliarie associate all'interfaccia application_Shell1 del
  main di Legocad

*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
/* #include "UxLib.h" */
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <libutilx.h>
#include "legomain.h"
#include "lc_errore.h"

/* Missing function declarations */
extern int esegui_comando(char *);
extern int proc_legocad_attivi();
extern void lc_errore(char *, ...);
extern void set_win_cursor(char *);
extern void aggiorna_attivi();
extern void reset_win_cursor();
extern int attiva_prog_par(char *, char *, ...);
extern int attiva_programma(char *);
extern int stato_processo(int);
extern int testa_ambiente();
extern void agg_label_ambiente();
extern void update_pulldown();
extern void uccidi_processo(int);
extern int esiste_file(char *);

extern ERR_LEVEL err_level;
char *getcwd();
char *getenv();
extern int tipo_modello; /* tipo di modello : se processo
				regolazione o mix */
extern int stato; /* stato di selezione del modello */
extern char path_user[120]; /* path name che individua l'utente legocad */
extern char path_legocad[120]; /* path_name che individua la sottodirectory
                           legocad per l'utente */
extern char path_libut[120];  /* path_name che individua la libreria dei moduli
			  di processo */
extern char path_libreg[120]; /* path_name che individua la libreria dei moduli
                             di regolazione */
extern Bool ok_path_legocad;
extern Bool ok_path_libut;
extern Bool ok_path_libreg;
extern Bool ok_libut;
extern Bool ok_libreg;
extern char path_modello[120]; /* path name del modello */
extern Bool grafica_on;
static char appoggio[120];

/*
  PID relativi alle attivita' per la
  costruzione del modello: vengono utilizzati
  per sapere se tali attivita' sono ancora attive
*/
extern pid_t pid_topology,pid_data,pid_steady,pid_transient,pid_librarian;


int test_transient()
{
printf("\n richiamato test transient");
return(esegui_comando(TEST_TRANSIENT));
}

int test_data_editor()
{
printf("\n richiamato test data editor");
return(esegui_comando(TEST_DATA_EDITING));
}

int test_steady()
{
printf("\n richiamato test stazionario");
return(esegui_comando(TEST_STEADY));
}

int test_topologia()
{
printf("\n richiamato test topologia");
return(esegui_comando(TEST_TOPOLOGY));
}

int get_comando_lg1(char *comando)
{
switch(tipo_modello)
	{
	case TIPO_PROCESSO:
	strcpy(comando,CREA_LG1_P);
	break;
	case TIPO_REGOLAZIONE:
	strcpy(comando,CREA_LG1_R);
	break;
	case TIPO_MIX:
	strcpy(comando,CREA_LG1);
	break;
	}
}
	
int get_comando_lg3(char *comando)
{
switch(tipo_modello)
	{
	case TIPO_PROCESSO:
	strcpy(comando,CREA_LG3_P);
	break;
	case TIPO_REGOLAZIONE:
	strcpy(comando,CREA_LG3_R);
	break;
	case TIPO_MIX:
	strcpy(comando,CREA_LG3);
	break;
	}
}

int get_comando_lg5sk(char *comando)
{
switch(tipo_modello)
	{
	case TIPO_PROCESSO:
	strcpy(comando,CREA_LG5SK_P);
	break;
	case TIPO_REGOLAZIONE:
	strcpy(comando,CREA_LG5SK_R);
	break;
	case TIPO_MIX:
	strcpy(comando,CREA_LG5SK);
	break;
	}
}

int esegui_crea(char *comando)
{
/*
 se vi sono processi di costruzione attivi esce direttamente
*/
if(proc_legocad_attivi())
        {
        err_level = ERROR;
        lc_errore(MODEL_IN_PROGRESS_ERR,comando);
        return 0;
        }
set_win_cursor("wait");
if(esegui_comando(comando))
        {
        err_level=ERROR;
        lc_errore(COMANDO_ERR,comando);
        }
aggiorna_attivi();
reset_win_cursor();
}

void esegui_crealg1()
{
char comando[150];
get_comando_lg1(comando);
esegui_crea(comando);
}

void esegui_crealg3()
{
char comando[150];
get_comando_lg3(comando);
esegui_crea(comando);
}

void esegui_crealg5sk()
{
char comando[150];
get_comando_lg5sk(comando);
esegui_crea(comando);
}

void attiva_topology()
{
char str_grafica_on[2];
char str_tipo_modello[2];
if(proc_legocad_attivi())
	{
	err_level == ERROR;
	lc_errore(MODEL_IN_PROGRESS_ERR,"Topology");
	}
else
	{
/* 
 Trasforma in ascii il valore boolean di grafica_on
*/
	sprintf(str_grafica_on,"%d",grafica_on);
	switch(tipo_modello)
		{
		case TIPO_PROCESSO:
		strcpy(str_tipo_modello,"P");
		break;
		case TIPO_REGOLAZIONE:
		strcpy(str_tipo_modello,"R");
		break;
		case TIPO_MIX:
		strcpy(str_tipo_modello,"P");
		break;
		}
        pid_topology=attiva_prog_par("lg1",path_modello,
				str_grafica_on,str_tipo_modello,(char *)0);
	}
}

/*
 Attivazione data editor (attivita' DATI)
*/
void attiva_data()
{
char str_grafica_on[2];
if(proc_legocad_attivi())
	lc_errore(MODEL_IN_PROGRESS_ERR,"Data editor");
else
	{
	sprintf(str_grafica_on,"%d",grafica_on);
	pid_data=attiva_prog_par("dati",path_modello,str_grafica_on,(char *)0);
	}
}

/*
 Attivazione del calcolo dello stazionario (steady-state)
*/
void attiva_steady()
{
if(proc_legocad_attivi())
	lc_errore(MODEL_IN_PROGRESS_ERR,"Steady state");
else
	pid_steady=attiva_programma("calcstaz");
}

/*
 Attivazione del calcolo del transitorio
*/
void attiva_transient()
{
if(proc_legocad_attivi())
	lc_errore(MODEL_IN_PROGRESS_ERR,"Transient");
else
	pid_transient=attiva_programma("cad_simula");
}

/*
 Attivazione librarian
*/
void attiva_librarian()
{
if(proc_legocad_attivi())
	lc_errore(MODEL_IN_PROGRESS_ERR,"Librarian");
else if(strlen(path_legocad)!=0)
	pid_librarian = attiva_prog_par("librarian",(char *)0);
}

/*
 Attivazione graphics
*/
void attiva_graphics()
{
if(stato==SCELTO && strlen(path_modello))
	{
	strcpy(appoggio,path_modello);
	strcat(appoggio,"/f22circ");
	attiva_prog_par("graphics",appoggio,(char *)0);
	}
else
	attiva_programma("graphics");
}

/*
 Attivazione tavole del vapore
*/
void attiva_tables()
{
attiva_programma("tables");
}

/*
 Attivazione documentazione automatica del modello
*/
void attiva_autodoc()
{
if(stato==SCELTO && strlen(path_modello))
	{
	strcpy(appoggio,path_modello);
	attiva_prog_par("autodoc",appoggio,(char *)0);
	}
}


int proc_legocad_attivi()
{
return((stato_processo(pid_topology) && pid_topology!=0) ||
    (stato_processo(pid_data) && pid_data!=0) ||
    (stato_processo(pid_steady) && pid_steady!=0) ||
    (stato_processo(pid_librarian) && pid_librarian!=0)||
     (stato_processo(pid_transient) && pid_transient!=0) );
}

/*
 procedura richiamata al termine di un programma richiamato con
 la routine di libreria close_prog_legocad. Viene aggiornato lo
 stato dei bottoni per lo sviluppo del modello
*/
void chiudi_prog_legocad(signal,code,scp)
int signal,code;
struct sigcontext *scp;
{
printf("\n intercettata chiusura segnale %d",signal);
testa_ambiente();
agg_label_ambiente();
update_pulldown();

if(stato == SCELTO)
	aggiorna_attivi();
}

/*
 Uccide eventuali processi gestiti da legocad
*/
void kill_proc_legocad()
{
if(stato_processo(pid_topology) && pid_topology!=0)
	uccidi_processo(pid_topology);
if(stato_processo(pid_data) && pid_data!=0)
	uccidi_processo(pid_data);
if(stato_processo(pid_steady) && pid_steady!=0)
	uccidi_processo(pid_steady);
if(stato_processo(pid_librarian) && pid_librarian!=0)
	uccidi_processo(pid_librarian);
}

/*
 verifica che il path selezionato sia accettabile per la costruzione del
 modello lego
*/
int is_path_modello(char *path)
{
return(1);
}


int testa_ambiente()
{
char *path;
char app[120];
if(path=getenv("LEGOCAD_USER"))
	{
	strcpy(path_user,path);
	strcpy(path_legocad,path_user);
	strcat(path_legocad,"/legocad");
	ok_path_legocad=esiste_file(path_legocad);

	strcpy(path_libut,path_legocad);
	strcat(path_libut,"/libut");
	ok_path_libut=esiste_file(path_libut);
	if(ok_path_libut)
		{
		app[0]=0;
		strcpy(app,path_libut);
		strcat(app,"/modulilib.a");
		ok_libut=esiste_file(app);
		}

	strcpy(path_libreg,path_legocad);
	strcat(path_libreg,"/libut_reg/libreg");
	ok_path_libreg=esiste_file(path_libreg);
	if(ok_path_libreg)
		{
		app[0]=0;
		strcpy(app,path_libreg);
		strcat(app,"/reglib.a");
		ok_libreg=esiste_file(app);
		}
	}
return(ok_libut && ok_libreg); /* l'ambiente e' corretto se torna True */	
}

void chdir_path_legocad()
{
if(ok_path_legocad)
	{
	printf("\n posizionamento in dir %s",path_legocad);
	chdir(path_legocad);
	}
}



