#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "viewshr.h"
#include "sked.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <Rt/RtDbPunti.h>
#include <Rt/RtErrore.h>
#include <Rt/RtMemory.h>
#include <sqlite3.h>


#define MAXCAR 256
#define MAXVAR 2500
#define MAXINPUT 10

// TIPO DI PARAMETRO LETTO DAL FILE VIEW
enum {OTHER = 0, IN, OUT, PERTURB, STEADY, DT, MODE, LOGMODE,
      SSMODE, DTWAIT, DTREAD, DTPERT, DTLOG, DTAVERAGE};

// VALORI DI MODE LOGMODE e SSMODE
enum {APPEND = 1, NEW = 2, YES = 1, NO = 0};

struct point_list 
{
    char variable[MAXCAR];
    int ind_var;
    int type;
    double a;    // FATTORI DI CONVERSIONE valore_finale = a*valore + b
    double b;
} point_list;
    
struct gest_shmem
{
    int tot_variabili;         
    VARIABILI *variabili;      
    char *ind_sh_top;          
    int id_sh; 
    RtDbPuntiOggetto dbpunti;
    RtErroreOggetto errore;
    float  puntonow;           
};
    
struct DBpoint
{
    long   ltime;
    double val[MAXINPUT];
};

static char nomevar[10];
int indir, stato1, num_var1;
float valore, tempo1;
struct gest_shmem shmem1;
struct point_list lista[MAXVAR];
time_t t_last_modification;

sqlite3 *db;


// PROTOTIPI 
float interpola(int i, long iltime, long ltimeCurr, struct DBpoint *DBvalori); 
int decodeLine(char *stringaO, char *c1, char *c2, char *c3, char *c4);
long readfile(FILE *fp, int numinput, struct DBpoint **DBvalori);
int getItem(char *stringa, char *campo, int len, int *pointer);
long time2sec(char *stringa);
long date2sec(char *stringa);
int viewshr();

                
// MAIN
int main (int argc, char **argv)
{
    long numvaloriPert, numvaloriIn, ltimeCurr, ltimeCurr0, ltimeCurrPw, ltimeCurrPp, ltimeCurrPr, 
	ltimeCurrPa, ltimeCurrPl, il, iltime, jciclo;
    static char c1[MAXCAR], c2[MAXCAR],  c3[MAXCAR], c4[MAXCAR], path_sim1[1024], key_sim1[100];
    unsigned int i, j, k, len, reset, numvar, tc, dtRead, dtPert, dtAverage, dtLog, salvataggio,
	logmode, mode, ssmode, numAverage;               
    static char key1[100], fileOut[100], fileIn[100], filePert[100], fileLog[100], comando[100];     
    int numinput, numoutput, numpert, numsteady, itimew, itimep, itimer, attendib, code;
    char stringa[100], tempo[100];
    struct DBpoint *DBpert, *DBinput;
    struct stat buff_stat;
    float valori[MAXVAR], ref_valori[MAXVAR], log_valori[MAXVAR], dtWrite;
    const struct tm *nowstruct;
    time_t nowbin, nowbinlog;               
    FILE *fp;

    reset = NO;
    itimew = 0;       // flag di inizio tempi write
    itimep = 0;       // flag di inizio tempi read perturbazioni  
    itimer = 0;       // flag di inizio tempi read
    iltime = 0;       // puntatore ad array dati di input
    ltimeCurrPw = 0L;
    ltimeCurrPp = 0L;
    ltimeCurrPr = 0L;
    ltimeCurrPa = 0L;
    ltimeCurrPl = 0L;
    t_last_modification = -1;
            
//*********************
//  VALORI DI DEFAULT
//*********************
    dtWrite = 60.;
    tc = 100;         // esecuzione ogni 0.1 sec
    dtPert = 30;      // tempo di scansione file delle perturbazioni in secondi
    dtRead = 30;      // tempo di scansione file di input in secondi
    dtAverage = 1;    // tempo di acquisizione per effettuare medie
    dtLog = 60.;      // tempo per scrittura file di log
    mode = APPEND;
    ssmode = YES;
    strcpy(fileIn, "DataServer.txt");
    strcpy(fileOut, "DataServer.DS");
    strcpy(fileLog, "DataServer.log");
    strcpy(key_sim1, "000000");
    strcpy(path_sim1, ".");

//**********************************************************
//  APERTURA FILE view PER LA LETTURA DALLA CONFIGURAZIONE
//**********************************************************
    fp = fopen("view", "r");
    if (fp == NULL)
    {  
        printf("Errore: il file view non si trova nella directory corretta");
        exit(0);
    }
    
//*************************************************************
//  MEMORIZZAZIONE DELLA CONFIGURAZIONE IN APPOSITA STRUTTURA
//*************************************************************
    i = 0;
    numpert = 0;
    numinput = 0;
    numoutput = 0;
    numsteady = 0;
    while (fgets(stringa, 100, fp)!=NULL) 
    {
        code = decodeLine(stringa, c1, c2, c3, c4);
        if (code == -1) 
        {        
            printf("Errore: formato non ammesso alla riga %s", stringa);            
            exit(0);
        }
        
        else if (code == 1) 
        {                         
            strcpy(lista[i].variable, c2);
        
            if (strcmp(c1, "in") == 0)
            {        
                lista[i].type = IN;
                lista[i].a = atof(c3);
                lista[i].b = atof(c4);                       
                numinput++;
            }
                 
            else if (strcmp(c1, "out") == 0)
            {        
                lista[i].type = OUT;
                lista[i].a = atof(c3);
                lista[i].b = atof(c4);    
                numoutput++;
            } 

            else if (strcmp(c1, "pert") == 0)
            {        
                lista[i].type = PERTURB;
                lista[i].a = atof(c3);
                lista[i].b = atof(c4);    
                numpert++;
            } 
                    

            else if (strcmp(c1, "steady") == 0)
            {        
                lista[i].type = STEADY;
		// c3 = percentuale [0..1] del valore iniziale che definisce
		// l'intervallo per la valutazione della condizione di regime
		lista[i].a = atof(c3);
		lista[i].b = atof(c4);    
                numsteady++;
            } 
                    
            else if (strcmp(c1, "dt") == 0)
                lista[i].type = DT;
            
            else if (strcmp(c1, "mode") == 0)
                lista[i].type = MODE;
                
            else if (strcmp(c1, "ssmode") == 0)
                lista[i].type = SSMODE;
                
            else if (strcmp(c1, "logmode") == 0)
                lista[i].type = LOGMODE;
                
            else if (strcmp(c1, "dtwait") == 0)
            	lista[i].type = DTWAIT;
            	
            else if (strcmp(c1, "dtpert") == 0)
            	lista[i].type = DTPERT;
            
            else if (strcmp(c1, "dtread") == 0)
            	lista[i].type = DTREAD;
            
            else if (strcmp(c1, "dtlog") == 0)
            	lista[i].type = DTLOG;
            
            else if (strcmp(c1, "dtfilt") == 0)
            	lista[i].type = DTAVERAGE;
            
            else if (strcmp(c1, "fout") == 0)
            {     
                lista[i].type = OTHER;
                strcpy(fileOut, c2); 
            } 
        
            else if (strcmp(c1, "fin") == 0)
            {     
                lista[i].type = OTHER;
                strcpy(fileIn, c2); 
            }         

            else if (strcmp(c1, "fpert") == 0)
            {     
                lista[i].type = OTHER;
                strcpy(filePert, c2); 
            }         
                                       
            else if (strcmp(c1, "flog") == 0)
            {     
                lista[i].type = OTHER;
                strcpy(fileLog, c2); 
            }         
                                       
            else if (strcmp(c1, "sim") == 0)
            {     
                lista[i].type = OTHER;
                strcpy(path_sim1, c2); 
            }   

            else if (strcmp(c1, "key") == 0)
            {     
                lista[i].type = OTHER;
                strcpy(key_sim1, c2); 
            }   
                      
            else
            {        
                printf("Errore: chiave non corretta in testa alla riga %s %s %s %s", c1, c2, c3, c4);            
                exit(0);
            }
        
            i++;
        }
    }

    numvar = i;
    fclose(fp);
     
//***********************************************
//  INIZIALIZZAZIONE AMBIENTE PRIMA SIMULAZIONE
//***********************************************
    chdir(path_sim1);        
    memcpy(key1, "SHR_USR_KEY=", 12);
    strcat(key1, key_sim1);
    putenv(key1);

    viewshr(INIZIALIZZA, nomevar, &indir, &valore, &stato1, &tempo1, &num_var1, 0, &shmem1);                                 
    viewshr(CHECK, nomevar, &indir, &valore, &stato1, &tempo1, &num_var1, 0, &shmem1);
                    
//*************************
//  SALVATAGGIO INDIRIZZI
//*************************
    chdir(path_sim1);
    putenv(key1);

    for (i=0; i<numvar; i++) 
    {    
        valori[i]  = 0.;
        log_valori[i] = 0.;
	ref_valori[i] = 0.;
        numAverage = 0;
        
        if (lista[i].type == OTHER)
        {
            lista[i].ind_var = -1;
            continue;
        }
        
        if (!viewshr(GETIND, lista[i].variable, &(lista[i].ind_var), &valore, &stato1, &tempo1, &num_var1, 0, &shmem1))                      
        {
            if (lista[i].type == DT)
            {
                dtWrite = atof(lista[i].variable);
                if (dtWrite == 0.)
                {
                    printf("Errore: valore non corretto del passo di archiviazione %s\n", lista[i].variable );
                    exit (0);
                } 
                
                lista[i].ind_var = -1;
            }
            
            else if (lista[i].type == MODE)
            {
                if (strcmp(lista[i].variable, "append") == 0)
                    mode = APPEND;
                    
                else if (strcmp(lista[i].variable, "new") == 0)
                    mode = NEW; 
                                       
                else
                {
                    printf("Errore: valore non corretto del modo di archiviazione %s\n",lista[i].variable );
                    exit (0);
                }
                
                lista[i].ind_var = -1; 
            }

            else if (lista[i].type == SSMODE)
            {
                if (strcmp(lista[i].variable, "yes") == 0)
                    ssmode = YES;
                    
                else if (strcmp(lista[i].variable, "no") == 0)
                    ssmode = NO; 
                                       
                else
                {
                    printf("Errore: valore non corretto del modo di verifica della condizione di regime %s\n",lista[i].variable );
                    exit (0);
                }
                
                lista[i].ind_var = -1; 
            }

            else if (lista[i].type == LOGMODE)
            {
                if (strcmp(lista[i].variable, "yes") == 0)
                    logmode = YES;
                    
                else if (strcmp(lista[i].variable, "no") == 0)
                    logmode = NO; 
                                       
                else
                {
                    printf("Errore: valore non corretto della modo di log %s\n",lista[i].variable );
                    exit (0);
                }
                
                lista[i].ind_var = -1; 
            }

            else if (lista[i].type == DTWAIT)
            {
              	tc = (int) (atof(lista[i].variable) * 1000);
                if (tc == 0)
                {
                    printf("Errore: valore non corretto del passo di esecuzione %s\n", lista[i].variable );
                    exit (0);
                } 
                
                lista[i].ind_var = -1;
            }            

            else if (lista[i].type == DTREAD)
            {
              	dtRead = (int) (atof(lista[i].variable));
                if (dtRead == 0)
                {
                    printf("Errore: valore non corretto del passo di lettura %s\n", lista[i].variable );
                    exit (0);
                } 
                
                lista[i].ind_var = -1;
            }
            
            else if (lista[i].type == DTPERT)
            {
              	dtPert = (int) (atof(lista[i].variable));
                if (dtPert == 0)
                {
                    printf("Errore: valore non corretto del passo di perturbazione %s\n", lista[i].variable );
                    exit (0);
                } 
                
                lista[i].ind_var = -1;
            }
            
	    else if (lista[i].type == DTAVERAGE)
            {
              	dtAverage = (int) (atof(lista[i].variable));
                if (dtAverage == 0)
                {
                    printf("Errore: valore non corretto dell'intervallo di media %s\n", lista[i].variable );
                    exit (0);
                } 
                
                lista[i].ind_var = -1;
            }
            
	    else if (lista[i].type == DTLOG)
            {
              	dtLog = (int) (atof(lista[i].variable));
                if (dtLog == 0)
                {
                    printf("Errore: valore non corretto dell'intervallo di log %s\n",
			   lista[i].variable );
                    exit (0);
                } 
                
                lista[i].ind_var = -1;
            }
            
	    else
            {                                         
                printf("variabile %s non trovata\n", lista[i].variable );
                exit (0);
            }
        }
    }

//************************************
//  LETTURA FILE DELLE PERTURBAZIONI
//************************************
    if ((fp = fopen(filePert, "r")) == NULL)
    {
        if (numpert != 0)
        {        
            printf("Errore: il file delle perturbazioni %s non esiste\n", filePert);
            exit(0);
        }
    }

    else
    {
        numvaloriPert = readfile(fp, numpert, &DBpert);
        if (numvaloriPert == -1L)
        {
            printf("Errore: controllare il formato del file delle perturbazioni %s\n", filePert);
            printf("numero variabili attese %d con il formato:\n", numpert);
            printf("dd/mm/yy    hh.mm.ss     valore(1)    valore(2)    ...    valore(%d)\n", numpert);        
            exit(0);
        }
        
        else if (numvaloriPert < 0L)
        {
            printf("Errore: controllare il file delle perturbazioni %s\n", filePert);
            printf("l'asse dei tempi non e' sequenziale alla riga %d\n",  -numvaloriPert);    
            exit(0);
        }        

        printf("numValoriPert: %d   numpert: %d\n", numvaloriPert, numpert);
        printf("time0: %ld  timeMAX: %ld\n", DBpert[0].ltime, DBpert[numvaloriPert-1].ltime);
        fclose(fp);
    }

//*********************************
//  INIZIO CICLO SINCRONIZZAZIONE
//*********************************
    jciclo=1;

    while(1) 
    {    
        i=0;
        while (stato1 == STATO_FREEZE) 
        {
            if ((stato1 == STATO_FREEZE) && (i == 0))
                printf("Simulatore in FREEZE\n");

            i=1;
            viewshr(CHECK, nomevar, &indir, &valore ,&stato1, &tempo1, &num_var1, 0, &shmem1);                  
        }
        
        printf("************INIZIO CICLO %ld ***************\n",jciclo);

//***************************
//  TRATTAZIONE DATI USCITA
//***************************
        chdir(path_sim1);        

        viewshr(CHECK, nomevar, &indir, &valore , &stato1, &tempo1, &num_var1, 0, &shmem1);
                
        if( stato1 == STATO_STOP )
        {
            printf("\n---------\n%s termina. Simulatore in STOP \n---------\n", argv[0]);
            exit (0);
        }
        
        else if(stato1 == STATO_ERRORE ) 
        {
            printf("\n---------\n%s termina. Simulatore in ERRORE \n---------\n", argv[0]);
            exit (0);
        }

        for(i=0; i<numvar; i++) 
        {  
//          dt di SCANSIONE FILE DI OUTPUT SE VARIABILE LEGO 
            if ((lista[i].type == DT) && (lista[i].ind_var != -1))
            {
                viewshr(GETVAR, lista[i].variable, &(lista[i].ind_var), &valore ,&stato1, &tempo1, &num_var1, 0, &shmem1);                     
                printf("%s=%f\n", lista[i].variable, valore);
                dtWrite = valore;
//              TEMPO DI SCANSIONE DI DEFAULT PARI A 1 MINUTO
                if (dtWrite <= 0.) dtWrite = 60.;
            } 
            
//          dt di ATTESA AD OGNI CICLO DI ESECUZIONE (dtwait) SE VARIABILE LEGO 
            if ((lista[i].type == DTWAIT) && (lista[i].ind_var != -1))
            {
                viewshr(GETVAR, lista[i].variable, &(lista[i].ind_var), &valore ,&stato1, &tempo1, &num_var1, 0, &shmem1);                     
                printf("%s=%f\n", lista[i].variable, valore);
              	tc = (int) (valore * 1000);
//              TEMPO DI ATTESA DI DEFAULT PARI A 0.1 secondi
                if (tc <= 0) tc = 100;
            }

//          dt di SCANSIONE FILE DI INPUT (dtread) SE VARIABILE LEGO 
            if ((lista[i].type == DTREAD) && (lista[i].ind_var != -1))
            {
                viewshr(GETVAR, lista[i].variable, &(lista[i].ind_var), &valore ,&stato1, &tempo1, &num_var1, 0, &shmem1);                     
                printf("%s=%f\n", lista[i].variable, valore);
              	dtRead = (int) (valore);
//              TEMPO DI SCANSIONE DI DEFAULT PARI A 30 secondi
                if (dtRead <= 0) dtRead = 30;
            } 
                        
//          dt di SCANSIONE FILE PERTURBAZIONI (dtpert) SE VARIABILE LEGO 
            if ((lista[i].type == DTPERT) && (lista[i].ind_var != -1))
            {
                viewshr(GETVAR, lista[i].variable, &(lista[i].ind_var), &valore ,&stato1, &tempo1, &num_var1, 0, &shmem1);                     
                printf("%s=%f\n", lista[i].variable, valore);
              	dtPert = (int) (valore);
//              TEMPO DI SCANSIONE DI DEFAULT PARI A 30 secondi
                if (dtPert <= 0) dtPert = 30;
            } 
                        
//          dt PER CALCOLO MEDIA DEI RISULTATI (dfilt) SE VARIABILE LEGO 
            if ((lista[i].type == DTAVERAGE) && (lista[i].ind_var != -1))
            {
                viewshr(GETVAR, lista[i].variable, &(lista[i].ind_var), &valore ,&stato1, &tempo1, &num_var1, 0, &shmem1);                     
                printf("%s=%f\n", lista[i].variable, valore);
              	dtAverage = (int) (valore);
//              TEMPO DI DEFAULT PARI A 1 secondo
                if (dtAverage <= 0) dtAverage = 1;
            } 
                        
//          dt PER LOG DELLE USCITE (dfilt) SE VARIABILE LEGO 
            if ((lista[i].type == DTLOG) && (lista[i].ind_var != -1))
            {
                viewshr(GETVAR, lista[i].variable, &(lista[i].ind_var), &valore ,&stato1, &tempo1,
			&num_var1, 0, &shmem1);                     
                printf("%s=%f\n", lista[i].variable, valore);
              	dtLog = (int) (valore);
//              TEMPO DI DEFAULT PARI A 60 secondi
                if (dtLog <= 0) dtLog = 60;
            } 
                        
//          MODO DI SCRITTURA FILE DI OUTPUT SE VARIABILE LEGO
            else if ((lista[i].type == MODE) && (lista[i].ind_var != -1))
            {
                viewshr(GETVAR, lista[i].variable, &(lista[i].ind_var), &valore, &stato1, &tempo1, &num_var1, 0, &shmem1);                         
                printf("%s=%f\n", lista[i].variable, valore);
                mode = (int) valore;
//              MODO DI SCRITTURA DI DEFAULT PARI AD append
                if ((mode < APPEND) || (mode > NEW)) mode = APPEND;
            }            

//          MODO DI VERIFICA REGIME SE VARIABILE LEGO
            else if ((lista[i].type == SSMODE) && (lista[i].ind_var != -1))
            {
                viewshr(GETVAR, lista[i].variable, &(lista[i].ind_var), &valore, &stato1, &tempo1, &num_var1, 0, &shmem1);                         
                printf("%s=%f\n", lista[i].variable, valore);
                ssmode = (int) valore;
//              MODO DI VERIFICA DI DEFAULT PARI A YES
                if ((ssmode != YES) && (ssmode != NO)) ssmode = YES;
	    }

//          MODO DI VERIFICA REGIME SE VARIABILE LEGO
	    else if ((lista[i].type == LOGMODE) && (lista[i].ind_var != -1))
	    {
		viewshr(GETVAR, lista[i].variable, &(lista[i].ind_var), &valore, &stato1, &tempo1,
			&num_var1, 0, &shmem1);                         
		printf("%s=%f\n", lista[i].variable, valore);
		logmode = (int) valore;
//              MODO DI LOG DI DEFAULT PARI A YES
		if ((logmode != YES) && (logmode != NO)) logmode = YES;
	    }            
	}             

	if (numoutput > 0)
	{  
	    viewshr(CHECK, nomevar, &indir, &valore ,&stato1, &tempo1, &num_var1, 0, &shmem1);
	    if (itimew == 0) 
	    {              
		ltimeCurr0 = (long) tempo1;
		time(&nowbin);
		nowbinlog = nowbin;
		itimew = 1;
	    }
            
	    ltimeCurr = (long) tempo1 - ltimeCurr0;
	    if ((itimew < 2) || (ltimeCurr - ltimeCurrPa >= dtAverage))
	    {
		printf("----->> aggiorno le medie\n");          
		ltimeCurrPa = ltimeCurr;
		numAverage++;           
		for(i=0; i<numvar; i++) 
		{  
		    if (lista[i].type == OUT)
		    {
			viewshr(GETVAR, lista[i].variable, &(lista[i].ind_var), &valore, &stato1, &tempo1, &num_var1, 0, &shmem1);                             
			valori[i] = valori[i] + valore;
			log_valori[i] = valore;
			printf("%s=%f\n", lista[i].variable, valore);
		    }
		}                
	    } 

	    // CONTROLLO DELLA CONDIZIONE DI REGIME
	    if (ssmode == YES && numsteady > 0)
	    {
		reset = NO;
		for(i=0; i<numvar; i++) 
		    if (lista[i].type == STEADY)
		    {
			viewshr(GETVAR, lista[i].variable, &(lista[i].ind_var), &valore,
				&stato1, &tempo1, &num_var1, 0, &shmem1);
			if (valore > ref_valori[i]*(1+lista[i].a / 2) ||
			    valore < ref_valori[i]*(1-lista[i].a / 2))
			{
				// VARIABILE NON A REGIME
			    valori[i] = valore;
			    ref_valori[i] = valore;
			    if (itimew == 2)
			    {
				printf("%s=%f - REGIME FAILED\n", lista[i].variable, valore);
				reset = YES;
			    }
			}
		    }
		// SE NON SIAMO IN STAZIONARIO ESEGUO UN RESET
		if (reset == YES)
		{
		    numAverage = 0;
		    if (ltimeCurr != 0L) nowbin = nowbin + (time_t) (ltimeCurr - ltimeCurrPw); // ???            
		    ltimeCurrPw = ltimeCurr;
		    ltimeCurrPa = ltimeCurr;
		    for (i=0; i<numvar; i++)
			if (lista[i].type == OUT) valori[i] = 0.;
		}                
	    }

//          SCRITTURA DEL LOG            
	    if ((logmode == YES) && ((itimew < 2) || (ltimeCurr - ltimeCurrPl >= dtLog)))
	    {
		printf("----->> scrivo su file di log\n");
		if (ltimeCurr != 0L) nowbinlog = nowbinlog + (time_t) dtLog;            
		ltimeCurrPl = ltimeCurr;
		// CREO UN FILE DI BACKUP
		if (itimew < 2)
		{
		    sprintf(comando, "mv %s %s.backup", fileLog, fileLog);
		    system(comando);
		}
             
		// SCRITTURA FILE DI OUTPUT
		fp = fopen(fileLog, "a");
		if (fp == NULL)
		{  
		    printf("Errore: problemi in apertura del file %s\n", fileLog);
		    exit(0);
		}
            
		nowstruct = localtime(&nowbinlog);
		strftime(tempo, 100, "20%y/%m/%d\t%T", nowstruct);
		fprintf(fp, "%s", tempo);
            
		attendib = 0;
		for (i=0; i<numvar; i++)
		    if (lista[i].type == OUT)
		    {
			fprintf(fp, "\t%.3f\t%d", log_valori[i]*lista[i].a + lista[i].b, attendib);
			log_valori[i] = 0.;
		    }
                                
		fprintf(fp, "\n");
		fclose(fp);
	    }
              
//          SCRITTURA DELL'OUTPUT
	    if ((itimew < 2) || (ltimeCurr - ltimeCurrPw >= dtWrite))
	    {
		itimew = 2;
		printf("----->> scrivo su file di output\n");
		if (ltimeCurr != 0L) nowbin = nowbin + (time_t) dtWrite;            
		ltimeCurrPw = ltimeCurr;                 
		// SCRITTURA FILE DI OUTPUT
		if (mode == APPEND)    
		{   
		    // APPEND           
		    fp = fopen(fileOut, "a");
		    if (fp == NULL)
		    {  
			printf("Errore: problemi in apertura del file %s\n", fileOut);
			exit(0);
		    }
            
		    nowstruct = localtime(&nowbin);
		    strftime(tempo, 100, "20%y/%m/%d\t%T", nowstruct);
		    fprintf(fp, "%s", tempo);
            
		    attendib = 0;
		    for (i=0; i<numvar; i++)
			if (lista[i].type == OUT)
			{                         
			    valori[i] = valori[i]/numAverage;
			    fprintf(fp, "\t%.3f\t%d", valori[i]*lista[i].a + lista[i].b, attendib);
			    valori[i] = 0.;
			}
                                
		    fprintf(fp, "\n");
		    fclose(fp);
		    numAverage = 0;
		}

		else
		{  
		    // NEW            
		    fp = fopen("output.DS", "w");
		    if (fp == NULL)
		    {  
			printf("Errore: problemi in apertura del file output.DS\n");
			exit(0);
		    }

		    nowstruct = localtime(&nowbin);
		    strftime(tempo, 100, "20%y/%m/%d\t%T", nowstruct);
		    fprintf(fp, "%s", tempo);
            
		    attendib = 0;
		    for (i=0; i<numvar; i++)
			if (lista[i].type == OUT)
			{                         
			    valori[i] = valori[i]/numAverage;
			    fprintf(fp, "\t%.3f\t%d", valori[i]*lista[i].a + lista[i].b, attendib);
			    valori[i] = 0.;
			}
		    // aggiungo una tabulazione prima del CR (ASCII DOS) e
		    // EOL per soddisfare esigenze di orema
		    fprintf(fp, "\t\r\n");
		    fclose(fp);
		    numAverage = 0;

		    sprintf(comando, "mv output.DS %s", fileOut);
		    system(comando);
		}                                       
	    }
	}
        
//*******************************************
//  TRATTAZIONE INPUT DA FILE PERTURBAZIONI
//*******************************************
	if (numpert > 0)
	{  
	    viewshr(CHECK, nomevar, &indir, &valore ,&stato1, &tempo1, &num_var1, 0, &shmem1);
	    if ((itimew == 0) && (itimep == 0)) 
	    {              
		ltimeCurr0 = (long) tempo1;
		itimep = 1;
	    }

	    ltimeCurr = (long) tempo1 - ltimeCurr0;
	    if ((itimep < 2) || (ltimeCurr - ltimeCurrPp >= dtPert))
	    { 
		itimep = 2;    
		ltimeCurrPp = ltimeCurr;                                        

		for (il=iltime; il<numvaloriPert; il++)     
		    if (ltimeCurr <= DBpert[il].ltime)
			break;

		if (il == numvaloriPert) il--;
		if (il == 0L) il++; 
		iltime = il - 1L;

		printf("----->> leggo da file perturbazioni\n");
		for (i=0, j=0; i<numvar; i++) 
		{  
		    if (lista[i].type == PERTURB)
		    {
			valori[i] = interpola(j, iltime, ltimeCurr, DBpert);
			valori[i] = valori[i]*lista[i].a + lista[i].b; 
			viewshr(PUTVAR, lista[i].variable, &(lista[i].ind_var), &valore, &stato1, &tempo1, &num_var1, valori[i], &shmem1); 
			printf("%s=%f\n",lista[i].variable, valori[i]);
			j++;
		    }
		}
	    }
	} 

//*******************************************
//  TRATTAZIONE INPUT DA FILE DI INPUT
//*******************************************
	if (numinput > 0)
	{  
	    viewshr(CHECK, nomevar, &indir, &valore ,&stato1, &tempo1, &num_var1, 0, &shmem1);
	    if ((itimew == 0) && (itimep == 0) && (itimer == 0)) 
	    {              
		ltimeCurr0 = (long) tempo1;
		itimer = 1;
	    }
            
	    ltimeCurr = (long) tempo1 - ltimeCurr0;
	    if ((itimer < 2) || (ltimeCurr - ltimeCurrPr >= dtRead))
	    { 
		itimer = 2;    
		ltimeCurrPr = ltimeCurr;                                                  

//              LETTURA FILE DI INPUT
		system("rm input.DS");
		
		sprintf(comando, "mv %s input.DS", fileIn);
		system(comando);
		if ((fp = fopen("input.DS", "r")) != NULL)
		{
		    numvaloriIn = readfile(fp, numinput, &DBinput);
		    if (numvaloriIn != 1L)
		    {
			printf("Errore: controllare il formato del file di input %s\n", fileIn);
			printf("numero variabili attese %d con il formato:\n", numinput);
			printf("dd/mm/yy    hh.mm.ss     valore(1)    valore(2)    ...    valore(%d)\n", numinput);        
			exit(0);
		    }

		    fclose(fp);

		    printf("----->> leggo da file di input\n");
		    for (i=0, j=0; i<numvar; i++) 
		    {  
			if (lista[i].type == IN)
			{
			    valori[i] = DBinput[0].val[j];
			    valori[i] = valori[i]*lista[i].a + lista[i].b; 
			    viewshr(PUTVAR, lista[i].variable, &(lista[i].ind_var), &valore, &stato1, &tempo1, &num_var1, valori[i], &shmem1); 
			    printf("%s=%f\n",lista[i].variable, valori[i]);
			    j++;
			}
		    }
		}
	    }
	}

	jciclo++;
	sospendi(tc);
    }  // FINE CICLO SINCRONIZZAZIONE
}


// READFILE
long readfile(FILE *fp, int numinput, struct DBpoint **DBvalori)
{
    char stringa[255];
    long nval, ltime, ltime0, ldate, ldate0;
    int count;

    nval  = 0L;
    count = 0;
    while (fscanf(fp, "%s", stringa) != EOF)
    {
	count++;

//      alloca la memoria e traduce la data in secondi
	if (count == 1)
	{
	    if (nval == 0L)
		*DBvalori = (struct DBpoint*) malloc(sizeof(struct DBpoint));

	    else
		*DBvalori = (struct DBpoint*) realloc(*DBvalori, (nval+1)*sizeof(struct DBpoint));
                
	    if ((ldate=date2sec(stringa)) == -1)
		return -1L;
            
	    if (nval == 0L) ldate0 = ldate;
	}

//      traduce l'ora in secondi
	else if (count == 2)
	{
	    if ((ltime=time2sec(stringa)) == -1)
		return -1L;
                
	    if (nval == 0L) ltime0 = ltime;
	    (*DBvalori)[nval].ltime = ltime - ltime0 + ldate - ldate0;
	    if (nval > 0)
		if ((*DBvalori)[nval].ltime < (*DBvalori)[nval-1].ltime)
		    return -nval;
	}
        
	else 
	    (*DBvalori)[nval].val[count - 3] = atof(stringa);
        
	if (count == numinput + 2)
	{
	    count = 0;
	    nval++;        
	}
    }

    return nval;
}



// TIME2SEC
long time2sec(char *stringa)
{
    char ore[4], minuti[4], secondi[4];
    int i, j, len, punto[2];
    
    len = strlen(stringa);
    for (i=0, j=0; i<len; i++)
	if (stringa[i] == '.' || stringa[i] == ':')
	{
	    punto[j] = i;
	    j++;
	}        
  
    if (j != 2) return -1L;

    strncpy(ore, stringa, punto[0]);
    strncpy(minuti, &stringa[punto[0] + 1], punto[1] - punto[0] - 1);
    strncpy(secondi, &stringa[punto[1] + 1], len - punto[1] - 1);
    return 3600L*(long) atoi(ore) + 60L*(long) atoi(minuti) + (long) atoi(secondi); 
}



// DATE2SEC
long date2sec(char *stringa)
{
    char giorni[4], mesi[4], anni[4];
    int i, j, len, punto[2];
    long daymonth[12] = {       0L,  2678400L,  5097600L,  7776000L, 10368000L, 13046400L, 
				15638400L, 18316800L, 20995200L, 23587200L, 26265600L, 28857600L};
    
    len = strlen(stringa);
    for (i=0, j=0; i<len; i++)
	if (stringa[i] == '/')
	{
	    punto[j] = i;
	    j++;
	}        
  
    if (j != 2) return -1L;

    strncpy(giorni, stringa, punto[0]);
    giorni[punto[0]] = '\0';
    strncpy(mesi, &stringa[punto[0] + 1], punto[1] - punto[0] - 1);
    mesi[punto[1] - punto[0] - 1] = '\0';
    strncpy(anni, &stringa[punto[1] + 1], len - punto[1] - 1);
    anni[len - punto[1] - 1] = '\0';
    return 31536000L*(long) atoi(anni) + daymonth[atoi(mesi) - 1] + 86400L*(long) (atoi(giorni) - 1); 
}



// INTERPOLA
float interpola(int i, long iltime, long ltimeCurr, struct DBpoint *DBvalori)
{
    float y1, y2, y, t1, t2, t;
    
    y1 = (float) DBvalori[iltime].val[i];
    y2 = (float) DBvalori[iltime + 1].val[i];
    t1 = (float) DBvalori[iltime].ltime;
    t2 = (float) DBvalori[iltime + 1].ltime;
    t  = (float) ltimeCurr; 
    
    if (t >= t2)
	return y2;
    else
	return y1 + (y2 - y1)*(t - t1)/(t2 - t1);
}



// DECODIFICA UNA LINEA DEL FILE DI INPUT view
int decodeLine(char *stringaO, char *c1, char *c2, char *c3, char *c4)
{  
    char stringa[255], c[255];
    int len, code, j;          

    strcpy(c1, ""); 
    strcpy(c2, ""); 
    strcpy(c3, "1."); 
    strcpy(c4, "0."); 
    
    strcpy(stringa, stringaO);
    len = strlen(stringa);
    len--;
    stringa[len] ='\0';   
    
//  ELIMINO I COMMENTI
    for (j=0; j<len; j++)   
	if (stringa[j] == '!')
	{ 
	    stringa[j] = '\0';
	    len = j;       
	    break;
	}
               
    j = 0;
    code = getItem(stringa, c, len, &j);
    if (code == 0) return 0;
    strcpy(c1, c);
     
    code = getItem(stringa, c, len, &j);
    if (code == 0) return -1;
    strcpy(c2, c);
    
    code = getItem(stringa, c, len, &j);
    if (code == 0) return 1;
    strcpy(c3, c);

    code = getItem(stringa, c, len, &j);
    if (code == 0) return 1;
    strcpy(c4, c);
    return 1;
}

  
            
// COPIA UNA SOTTOSTRINGA DI stringa IN campo
int getItem(char *stringa, char *campo, int len, int *pointer)
{ 
    int j, k;
    
    k = *pointer;
    
//  TROVO L'INIZIO STRINGA
    for (j=k; j<len; j++)   
	if ((stringa[j] != ' ') && (stringa[j] != '\t'))
	    break;
           
//  TROVO LA FINE STRINGA                
    for (k=j; k<len; k++)
	if ((stringa[k] == ' ') || (stringa[k] == '\t'))
	    break; 
                
    if (k <= j) return 0;
    
    strncpy(campo, &stringa[j], k-j);
    campo[k-j] = '\0';
    *pointer = k;
    return 1; 
}
