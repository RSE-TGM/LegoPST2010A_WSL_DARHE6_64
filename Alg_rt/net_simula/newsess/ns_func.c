/**********************************************************************
*
*       C Source:               ns_func.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue May 25 14:33:42 2004 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: ns_func.c-10 %  (%full_filespec: ns_func.c-10:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)ns_func.c	1.16\t2/5/96";
/*
   modulo ns_func.c
   tipo 
   release 1.16
   data 2/5/96
   reserved @(#)ns_func.c	1.16
*/
#include <stdio.h>
#include <errno.h>
#include <string.h>

#if defined UNIX
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#endif
#if defined VMS
#include"vmsipc.h"
#include <unixio.h>
#include <file.h>
#endif
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <Rt/RtDbPunti.h>
#include <Rt/RtMemory.h>

#include "sim_param.h"
#include "sim_types.h"
#include "sim_ipc.h"
#include "comandi.h"
#include "sked.h"
#include "f22_circ.h"
#include "grsf22.h"
#include "ns_macro.h"
//#include "libutilx.h"


#define MAXRIGA 85
#define F01 "f01.dat"


/* 
   Prototyping funzioni contenute nel file
*/
   int EstrazioneRecorder(PUNT_FILE_F22);
   int NomiBlocchi();
   int FinestreTemporali(PUNT_FILE_F22, F22CIRC_HD header,
                         float ti, float tf);
   int EstrazioneF22(PUNT_FILE_F22, PUNT_FILE_F22, F22CIRC_HD,
                      float , float , int );
   int TrovaPuntatori(PUNT_FILE_F22 ,F22CIRC_HD, int, float, float, 
                      int *, int *);
   int ScriviNuoviF22(PUNT_FILE_F22, PUNT_FILE_F22, F22CIRC_HD,
                      int, int);
   int ConfrontaFinestre(float , float , float , float );
   int StampaTempi(int ,int , int, float);
   int OutErr(int, int, char *);
   char *getpul (char *, int , FILE *p);
   int f22_leggi_camp(PUNT_FILE_F22 ,F22CIRC_HD ,
                      float *tempo, SCIRC_SEL_DATI **,
                      int , int , int , int );
   static int ComparaCampioni(SCIRC_DATI *,SCIRC_DATI *);

   //static int legge_riga(FILE *, char *);
   static int legge_riga(char  [], int *);
   static void separa_str( char [], int , int , STRIN_ST []);

/* 
   Prototyping funzioni esterne
*/
   extern Boolean nsRemove(char * );
   extern Boolean nsCopy(char * , char * );


/* 
   Variabili globali
*/
   int intstampa=1200;
   int riga_s01;
   FILE *fp_s01;
   int nmodelli;       /*  Numero dei modelli del simulatore */
   char **modelli;     /*  Nomi dei modelli (task) */
   BLOCCHI *blocchi;   /*  Blocchi di ogni modello */
  

/* 
   Variabili globali esterne
*/
   extern int totale_variabili;
   extern char *nome_file_f22;
   extern float tem_i,tem_f;
   extern char *dir_archive;
   extern char *f22_ascii;
   extern FILE *f22_ascii_id;
   extern int num_var_eff;
   extern F22CIRC_VAR *var_eff;
   extern int *selezione;




/*
    Produce a partire dal file f22circn.hd il 
    file recorder.edf corrispondente consultando i
    file f01.dat delle task i cui pathname vengono
    estratti da S01.
*/
int EstrazioneRecorder(PUNT_FILE_F22 file)
{
FILE *fp_rcd;
char nomefile[FILENAME_MAX];
int i,j,k,n;
int inserimenti=0;


/*  Legge i nomi dei blocchi della task */
    NomiBlocchi();  /*  togliere le exit e mettere fprintf */
/*
    for(i=0;i<nmodelli;i++)
       {
       printf("\n    MODELLO=%s   blocchi=%d\n",
              blocchi[i].modello,blocchi[i].nblock);
       for(j=0;j<blocchi[i].nblock;j++)
           printf("       BLOCCO %d = %s\n",
                  j,blocchi[i].blocchi[j]);
       }
*/

/*  Scrittura File */
    strcpy(nomefile, "./");
    strcat(nomefile, dir_archive);
    strcat(nomefile, "/");
    strcat(nomefile, NAME_RECORDN);
    if (!(fp_rcd = fopen(nomefile, "w")))
       exit(fprintf(stderr,"Non esiste il file %s",nomefile));
    fprintf(fp_rcd, "****\n");
    fprintf(fp_rcd, "NOME MODELLO\n");
    fprintf(fp_rcd, "****\n");
    fprintf(fp_rcd, "NOME SELEZIONE\n");
    fprintf(fp_rcd, "AUTORE SELEZIONE\n");
    fprintf(fp_rcd, "VERSIONE SELEZIONE\n");
    fprintf(fp_rcd, "****\n");


/*
*/
    inserimenti=0;
    for(i=0;i<nmodelli;i++)
       {
       fprintf(fp_rcd,"MODELLO %s\n",blocchi[i].modello);
           {
/*         Le variabili vengono inserite se appartengono al modello i-esimo */
           n=0;
           while(1)
              {
              for(j=0;j<blocchi[i].nblock;j++)
                 {
                 /*printf("           %s  n=%d\n",var_eff[n].nomevar,n);*/
                 if ( strstr(var_eff[n].descvar,blocchi[i].blocchi[j])!=0 )
                    {
                    /*printf("           %s  n=%d\n",var_eff[n].nomevar,n);*/
                    fprintf(fp_rcd,"%s\n",var_eff[n].nomevar);
                    inserimenti++;
                    break;
                    }
                 else
                    {
                    if ( n==num_var_eff )
                       break;
                    }
                 }
              n++;
              if ( n==num_var_eff )
                 break;
              }/* Fine scansione della lista delle variabili grafiche */
           }
       fprintf(fp_rcd,"****\n");
       }/* Fine ciclo su tutti i modelli */
    fclose(fp_rcd);
    fprintf(stderr,"\n    Prodotto recordern.edf contenente %d variabili\n",
            inserimenti);

/*  Liberazione strutture */
    XtFree((char*)var_eff);
    for(i=0; i<nmodelli; i++) 
       cfree2(blocchi[i].blocchi);
    XtFree((char*)blocchi);
}





/*
    Legge da S01 i path degli f14 dei modelli allo scopo di leggere
    poi nei relativi file f01.dat i nomi dei blocchi dei modelli.
    SE SI TRATTA DI UNA TASK NON LEGO SARA' DA GESTIRE.
*/
int NomiBlocchi()
{
int i,j,k;
char riga[300];
int lun;
int nstr;
char **path_svil;
char nomefile[FILENAME_MAX];
STRIN_ST strin [10];
FILE *fp_f01;
int nbl;
int separatori;


/*
    Inizializzazione della struttura STRIN_ST
*/
    for(i=0; i<10; i++)
       strin[i].stringa = NULL;

/*  
    Lettura S01 per lettura path della macchina di sviluppo
*/
    if (!(fp_s01 = fopen( "S01", "r")))
         exit(fprintf(stderr,"Non esiste il file S01.DAT"));
    riga_s01 = 0;

/*  Lettura prima riga di S01 */
    legge_riga( riga, &lun);
    if (strncmp( riga, "****", 4))
        exit( fprintf(stderr,"La prima riga di S01 deve essere ****"));

/*  Lettura seconda riga di S01.DAT (NOME MACRO_MODELLO) */
    legge_riga( riga, &lun);

/*  Lettura terza riga di S01.DAT */
    legge_riga( riga, &lun);
    if (strncmp(riga, "****", 4))
        exit(fprintf(stderr,
                     "Linea dopo nome del MACRO-modello diversa da ****"));

/*  Lettura dei NOMI dei modelli */
    modelli = (char **)cdim2(MAX_MODEL,9);
    nmodelli = 0;
    do 
        {
        legge_riga( riga, &lun);
        if (! strncmp( riga, "****", 4))
           break;
        separa_str( riga, lun, nstr=2, strin);
        if (strin[0].lun_stringa > 8)
            exit( fprintf(stderr,"Nome di modello piu` lungo di 8 caratteri"));

        strcpy(modelli[nmodelli],strin[0].stringa);
        nmodelli++;
        if ( nmodelli==MAX_MODEL )
           exit(fprintf(stderr,"Numero modelli supera MAX_MODEL"));
        } 
    while (1);


/* Lettura dei path della macchina di sviluppo */
   path_svil = (char **)cdim2(nmodelli,100);
   for (i=0; i<nmodelli; i++) 
      {
      legge_riga(riga,&lun);
      separa_str( riga, lun, nstr=2, strin);
      strcpy(path_svil[i], strin[0].stringa);
      }

   fclose(fp_s01);

/* 
   Ciclo di lettura da f01.dat dei nomi dei blocchi di ogni modello 
*/
   blocchi = (BLOCCHI*)calloc(nmodelli,sizeof(BLOCCHI));
   for (i=0; i<nmodelli; i++) 
       {
       strcpy(blocchi[i].modello,modelli[i]);
       strcpy(nomefile,path_svil[i]);
       strcat(nomefile,F01);
       if (!(fp_f01 = fopen(nomefile, "r")))
             exit(fprintf(stderr,"Non esiste il file %s",nomefile));
 
/*     Lettura dei blocchi */
       getpul (riga, 100, fp_f01);  
       nbl=0;
       while (getpul (riga, 100, fp_f01))
         {
         if (!strncmp (riga, "****", 4))
            break;
         else
            nbl++;
         }  /* Fine ciclo while */
       blocchi[i].nblock  = nbl;
       blocchi[i].blocchi = (char**)cdim2(nbl,100);

       while (getpul (riga, 100, fp_f01))
         if (!strncmp (riga, "****", 4))
            break;

       for(j=0;j<nbl;j++)
          {
          getpul (riga, 100, fp_f01);  
          strncpy(blocchi[i].blocchi[j],riga,8);
          separatori=0;
          while (getpul (riga, 100, fp_f01))
              {
              if (!strncmp (riga, "****", 4))
                   separatori++;
              if( separatori==2)
                   break;
              }  /* Fine ciclo while */
          }
       fclose(fp_f01);
       }    /* Fine ciclo for */

/* Libero le strutture */
   cfree2(path_svil);
   cfree2(modelli);
   for(i=0;i<10;i++) {
      if(strin[i].stringa!=NULL)
         free(strin[i].stringa);
   }
}





/* 
    Legge nel file dei dati di input il primo e l'ultimo valore 
    e valuta le sovrapposizioni della finestra temporale richiesta
    con la finestra temporale su file.
    Ritorna il risultato del confronto tramite le define seguenti:
        FIN_ESTESA            
        FIN_INCLUSA          
        FIN_PARZ_INCLUSA_DX 
        FIN_PARZ_INCLUSA_SX
        FIN_ESTERNA       

*/
int FinestreTemporali(PUNT_FILE_F22 punt, F22CIRC_HD header,
                      float ti, float tf)
{
int campione;
int size_campione = (header.num_var_graf ) *sizeof(float) + sizeof(F22CIRC_T);
int offheader     = sizeof(HEADER_REGISTRAZIONI) + sizeof(F22CIRC_HD) +
                    sizeof(F22CIRC_VAR) * header.num_var_graf;
int offset;
int camp;
int conta=0;
float primo_tempo,ultimo_tempo;
int ret;
float *valori;
F22CIRC_T t_22;



    if(header.p_fine == header.p_iniz)
        {
        printf("Esco perche' header.p_fine == header.p_iniz\n");
        return(-1);
        }

    valori = (float*)malloc(sizeof(float)*header.num_var_graf);

    camp = 0;
/*  Leggo l'ultimo valore */
    campione=header.p_fine;
    offset=offheader + (campione-1) * size_campione;
    sposta(punt.fp,offset);
    leggi(&t_22,sizeof(F22CIRC_T),1,punt.fp);
    leggi(valori,sizeof(float),header.num_var_graf,punt.fp);
    ultimo_tempo = t_22.tempo;

/*  Leggo il primo valore */
    campione=header.p_iniz;
    offset=offheader + (campione-1) * size_campione;
    sposta(punt.fp,offset);
    leggi(&t_22,sizeof(F22CIRC_T),1,punt.fp);
    leggi(valori,sizeof(float),header.num_var_graf,punt.fp);
    primo_tempo = t_22.tempo;

    free(valori);

    printf("\n    FinestreTemporali  Primo tempo %f   ultimo tempo=%f\n",
           primo_tempo,ultimo_tempo);

    ret = ConfrontaFinestre(ultimo_tempo,primo_tempo,tf,ti);
    return(ret);
}





/*
    In base a caso, definito dal confronto delle finestre temporali
    in input ed output definisce il tipo di estrazione del nuovo file
    che deve essere effettuata.
*/
int EstrazioneF22(PUNT_FILE_F22 file, PUNT_FILE_F22 file_new,
                   F22CIRC_HD header,
                   float ti, float tf, int caso)
{
int piniz,pfine;
int ret;



switch(caso)
    {
    case FIN_ESTESA:
         {
         fprintf(stderr,
           "  La finestra temporale richiesta include interamente quella  del file.\n  Tutti i campioni presenti verranno trasferiti.\n");
         piniz=header.p_iniz;
         pfine=header.p_fine;
         ret = ScriviNuoviF22(file,file_new,header,piniz,pfine);
         break;
         }
    case FIN_INCLUSA:
         {
         TrovaPuntatori(file,header,caso,ti,tf,&piniz,&pfine);
         ret = ScriviNuoviF22(file,file_new,header,piniz,pfine);
         break;
         }
    case FIN_PARZ_INCLUSA_DX:
         {
         fprintf(stderr,
           "    Finestra temporale richiesta solo parzialmente inclusa nel file.\n    Si otterra' una estrazione parziale.\n");
         TrovaPuntatori(file,header,caso,ti,tf,&piniz,&pfine);
         ret = ScriviNuoviF22(file,file_new,header,piniz,pfine);
         break;
         }
    case FIN_PARZ_INCLUSA_SX:
         {
         fprintf(stderr,
           "    Finestra temporale richiesta solo parzialmente inclusa nel file.\n    Si otterra' una estrazione parziale.\n");
         TrovaPuntatori(file,header,caso,ti,tf,&piniz,&pfine);
         ret = ScriviNuoviF22(file,file_new,header,piniz,pfine);
         break;
         }
    case FIN_ESTERNA:
         {
         fprintf(stderr,
           "    Finestra temporale richiesta esterna a quella del file.\n");
         fprintf(stderr,
           "    Il file f22circn.dat conterra' solo la parte di header\n");
         piniz=1;
         pfine=1;
         ret = ScriviNuoviF22(file,file_new,header,piniz,pfine);
         break;
         }
    default:
         {
         printf(" -1\n");
         break;
         }
    }
return(ret);
}





/*
    Trova nel file dei dati di input i puntatori p_i, p_f ai tempi
    ti, tf che definiscono la finestra di input.
*/
int TrovaPuntatori(PUNT_FILE_F22 punt,F22CIRC_HD header, int caso,
                   float ti, float tf, int *p_i, int *p_f)
{
int campione;
int size_campione = (header.num_var_graf ) *sizeof(float) + sizeof(F22CIRC_T);
int offheader     = sizeof(HEADER_REGISTRAZIONI) + sizeof(F22CIRC_HD) +
                    sizeof(F22CIRC_VAR) * header.num_var_graf;
int offset;
int camp=0;
int conta=0;
float tempo_prec=-1;
float primo_tempo=-1,ultimo_tempo=-1;
float *valori;
F22CIRC_T t_22;
int trovato_ti=0,trovato_tf=0;
int ret=-9;


     intstampa = 10000;
     printf("\n    TrovaPuntatori  caso=%d ti=%f  tf=%f\n",caso,ti,tf);
     
     valori = (float*)malloc(sizeof(float)*header.num_var_graf);
 
     campione=header.p_fine;
 
     conta=0;
     while(1)
        {
        if( conta==header.num_campioni )
            {
            ret = -1;
            printf("Non ho trovato i tempi cercati\n");
            break;
            }

        offset=offheader + (campione-1) * size_campione;
        sposta(punt.fp,offset);
        leggi(&t_22,sizeof(F22CIRC_T),1,punt.fp);
        leggi(valori,sizeof(float),header.num_var_graf,punt.fp);

        conta++;

        StampaTempi(conta,campione,camp,t_22.tempo);

        switch (caso)
           {
           case FIN_PARZ_INCLUSA_DX:
                {
                if( (trovato_tf==0) && (campione==header.p_fine) )
                   {
                   *p_f = header.p_fine;
                   trovato_tf = 1;
                   ultimo_tempo = t_22.tempo;
                   /*printf("trovato_tf t22=%f p_u=%d\n",t_22.tempo,*p_f);*/
                   }
                if( (t_22.tempo <= ti) && (trovato_ti==0) )
                   {
                   *p_i = campione;
                   trovato_ti = 1;
                   primo_tempo = t_22.tempo;
                   /*printf("trovato_ti t22=%f p_i=%d\n",primo_tempo,*p_i);*/
                   }
                break;
                }
           case FIN_PARZ_INCLUSA_SX:
                {
                if( (t_22.tempo <= tf) && (trovato_tf==0) )
                   {
                   *p_f = campione+1;
                   trovato_tf = 1;
                   ultimo_tempo = tempo_prec;
                   /*printf("trovato_tf t22=%f p_u=%d %f\n",ultimo_tempo,*p_f);*/
                   }
                if( (trovato_ti==0) && (campione==header.p_iniz) )
                   {
                   *p_i = header.p_iniz;
                   trovato_ti = 1;
                   primo_tempo = t_22.tempo;
                   /*printf("trovato_ti t22=%f p_i=%d\n",primo_tempo,*p_i);*/
                   }
                break;
                }
           case FIN_INCLUSA:
                {
                if( (t_22.tempo <= tf) && (trovato_tf==0) )
                   {
                   *p_f = campione+1;
                   trovato_tf = 1;
                   ultimo_tempo = tempo_prec;
                   /*printf("trovato_tf t22=%f p_u=%d\n",ultimo_tempo,*p_f);*/
                   }
                if( (t_22.tempo < ti) && (trovato_ti==0) )
                   {
                   *p_i = campione;
                   trovato_ti = 1;
                   primo_tempo = t_22.tempo;
                   /*printf("trovato_ti t22=%f p_i=%d\n",primo_tempo,*p_i);*/
                   }
                break;
                }
           case 99:
                {
                break;
                }
           }   /*  Fine switch */



        if( (trovato_tf==1) && (trovato_ti==1) )
           {
           ret = 1;
           break;
           }

        ++camp;

/*      Campione successivo */
        if(campione == header.p_iniz)
                {
                printf("Non ho trovato i tempi cercati, campione==p_iniz\n");
                printf("campione=%d conta=%d\n",campione,conta);
                break;
                }
        -- campione;
        if(campione == 0)
                campione = header.num_campioni;
/*
        if( tempo_prec==t_22.tempo )
           printf("    TrovaPuntatori tempo_prec==t_22.tempo=%f campione=%d\n",
                  t_22.tempo,campione);
*/
        tempo_prec = t_22.tempo;
        }

     free(valori);
     printf("    Puntatori: p_i=%d (ti=%f)   p_f=%d (tf=%f)\n\n",
            *p_i,primo_tempo,*p_f,ultimo_tempo);
     intstampa = 1200;
     return(ret);
}





/*
    Legge dal file i campioni compresi tra niniz e nfine e li
    scrive nel nuovo file dei dati completandolo con campioni nulli.
    Aggiorna il file degli header.
*/
int ScriviNuoviF22(PUNT_FILE_F22 punt, PUNT_FILE_F22 punt_new, 
                   F22CIRC_HD header,
                   int niniz, int nfine)
{
int campione;
int size_campione = (header.num_var_graf ) *sizeof(float) + sizeof(F22CIRC_T);
int offheader     = sizeof(HEADER_REGISTRAZIONI) + sizeof(F22CIRC_HD) +
                    sizeof(F22CIRC_VAR) * header.num_var_graf;
int offset;
int scritture=0;
float tempo_prec=-9;
float *valori;
F22CIRC_T t_22;
F22CIRC_T tzero;
F22CIRC_HD header_new;
HEADER_REGISTRAZIONI hdreg_new;
int finedati=0;
int numzeri;
int i,kkk;
int ret1,ret2,ret3;


     if(header.p_fine == header.p_iniz)
        {
        printf("Esco perche' header.p_fine == header.p_iniz\n");
        return(-1);
        }

     printf("    ScriviNuoviF22 a partire da niniz=%d  nfine=%d\n",
            niniz,nfine);

/*   Inizializzazioni */
     valori = (float*)malloc(sizeof(float)*header.num_var_graf);
     campione=niniz;
     scritture=0;
     sposta(punt_new.fp,0);
     sposta(punt.fp,0);
/*
     Lettura dell'header (HEADER_REGISTRAZIONI) del file f22circ corrente. 
*/
     leggi(&hdreg_new,sizeof(HEADER_REGISTRAZIONI),1,punt.fp);
     memcpy(&header_new,&header,sizeof(F22CIRC_HD));
/*
     Scrittura degli header del file f22circn.dat e delle variabili
     presenti nel file di partenza
*/    
     scrivi(&hdreg_new,sizeof(HEADER_REGISTRAZIONI),1,punt_new.fp); 
     scrivi(&header_new,sizeof(F22CIRC_HD),1,punt_new.fp);
     scrivi(var_eff,sizeof(F22CIRC_VAR),num_var_eff,punt_new.fp); 
     fluscia(punt_new.fp);
/*
     Si controlla se ci sono campioni nell'intervallo selezionato
*/
     if(niniz!=nfine) {
/*
     Posizionamento sul primo campione del file f22circ.dat
*/
        sposta(punt.fp,offheader);
/*
     Ciclo di letture dei valori di interesse e loro scrittura
     nel nuovo file.
*/
        header_new.p_iniz = 1;
        while(1)
           {
/*      Leggo i valori a partire dal primo di interesse */
           offset=offheader + (campione-1) * size_campione;
           sposta(punt.fp,offset);
           ret1 = leggi(&t_22,sizeof(F22CIRC_T),1,punt.fp);
           ret2 = leggi(valori,sizeof(float),header.num_var_graf,punt.fp);
           ret3 = OutErr(ret1,ret2,LETTURA);
           if( ret3 < 0 )
              return(ret3);
/*
Sezione aggiunta per creare un file ASCII contenente
il valore dei punti registrati nel file f22circ.dat
*/
           fprintf(f22_ascii_id,"%f;",t_22.tempo);
           for (kkk=0;kkk<num_var_eff;kkk++)
           {
           if(selezione[kkk]==1)
             {
             fprintf(f22_ascii_id,"%f;",valori[kkk]);
             }

           }
           fprintf(f22_ascii_id,"\n");
/*
Fine Sezione aggiunta per creare un file ASCII contenente
il valore dei punti registarti nel file f22circ.dat
*/
/*      Scrivo i valori nel nuovo file */
           ret1 = scrivi(&t_22,sizeof(F22CIRC_T),1,punt_new.fp);
           ret2 = scrivi(valori,sizeof(float),num_var_eff,punt_new.fp);
           ret3 = OutErr(ret1,ret2,SCRITTURA);
           if( ret3 < 0 )
              return(ret3);
           fluscia(punt_new.fp);

           scritture++;

/*      Sezione per stampe di output */
        /*StampaTempi(scritture,campione,nfine,t_22.tempo);*/
           if( campione==niniz )
              printf("		Primo  tempo  estratto=%f\n",t_22.tempo);
           if( campione==nfine )
              printf("		Ultimo tempo  estratto=%f\n",t_22.tempo);

/*      Test uscita ciclo */
           if(campione == nfine)
              {
              finedati = 1;
              break;
              }

/*      Aggiornamento puntatori */
           campione++;
           if(campione == header.num_campioni)
                campione = 1;
        
/*      Questa parte potra' essere eliminata */
           if( tempo_prec==t_22.tempo )
               ret3 = OutErr((int)tempo_prec,(int)t_22.tempo,LETTURATMP);
           tempo_prec = t_22.tempo;
           }   /*  Fine ciclo while */
/*
        Aggiornamento nell'header del file f22circn.dat di: 
        header_new.p_fine = scritture, num_campioni=scritture,
        num_var_graf = num_var_eff.
*/ 
           header_new.p_fine=scritture;
           header_new.num_campioni=scritture;
           header_new.num_var_graf=num_var_eff;
        }
        else {
/*
   Aggiornamento dell'header nel caso in cui non ci sono campioni
*/
           header_new.p_iniz=1;
           header_new.p_fine=1;
           header_new.num_campioni=0;
           header_new.num_var_graf=num_var_eff;
        }

printf("ScriviNuoviF22: p_iniz_new = %d\tp_fine_new = %d\n",
       header_new.p_iniz, header_new.p_fine);

        sposta(punt_new.fp,sizeof(HEADER_REGISTRAZIONI));
        scrivi(&header_new,sizeof(F22CIRC_HD),1,punt_new.fp);
        fluscia(punt_new.fp);

        free(valori);
return(1);
}





/*
    Confronta la finestra temporale del file (tf1--tf2) con quella
    richiesta (t1--t2) riconoscendo tra le diverse possibili situazioni.
    Ritorna la define relativa al caso riconosciuto.
*/
int ConfrontaFinestre(float tf2 , float tf1, float t2, float t1)
{

    printf("    ConfrontaFinestre --->\n    tf2=%f  t2=%f   tf1=%f  t1=%f\n",
            tf2,t2 ,tf1,t1);

/*  Finestra richiesta piu' estesa */
    if( (tf2<=t2) && (tf1>=t1) )
       {
       printf("    FIN_ESTESA\n\n");
       return(FIN_ESTESA);
       }

/*  Finestra richiesta completamente inclusa */
    if( (tf2>=t2) && (tf1<=t1) )
       {
       printf("    FIN_INCLUSA\n\n");
       return(FIN_INCLUSA);
       }

/*  Finestra richiesta parzialmente inclusa (esce a destra) */
    if ( (tf2>=t1) && (tf2<=t2) && (tf1<=t1) )
       {
       printf("    FIN_PARZ_INCLUSA_DX\n\n");
       return(FIN_PARZ_INCLUSA_DX);
       }

/*  Finestra richiesta parzialmente inclusa (esce a sinistra) */
    if ( (tf1>=t1) && (tf1<=t2) && (tf2>=t2) )
       {
       printf("    FIN_PARZ_INCLUSA_SX\n\n");
       return(FIN_PARZ_INCLUSA_SX);
       }

/*  Finestra richiesta non compresa */
    if( (tf2<t1) || (tf1>t2) )
       {
       printf("    FIN_ESTERNA\n\n");
       return(FIN_ESTERNA);
       }

    printf("    Caso default\n\n");
    return(-1);
}





/*
     Esegue una stampa ad intervalli regolari di intstampa
*/
int  StampaTempi(int contatore,int num_campione, int camp, float tempo)
{
div_t divis;

        divis = div(contatore,intstampa);
        if (divis.rem == 0)
              printf("    %d)   tempo=%f campione=%d 3par=%d\n",
                      contatore,tempo,num_campione,camp);
}





/*
      Stampa messaggi d'errore per le fasi di lettura 
      e scrittura del file nella funzione ScriviNuoviF22.
*/
int   OutErr(int ret1, int ret2, char * rd_o_wr)
{
static int prima_stampa=1;

        if(!strcmp(rd_o_wr,LETTURATMP))
           {
           if( prima_stampa==1 )
               {
               fprintf(stderr,"    ATTENZIONE : Nel file ci sono campioni ");
               fprintf(stderr,"col medesimo tempo.\n");
               fprintf(stderr,"    Tali valori sono riproposti nel nuovo file.\n");
               prima_stampa=0;
               }
           return(-1);
           }
        if ( (ret1 <=0) || (ret2<=0) )
           {
           fprintf(stderr,
               "   Errore %s nuovi file: ret1=%d ret2=%d\n",rd_o_wr,ret1,ret2);
           return(-1);
           }
        else
           return(0);
}





/*
*/
int legge_riga(char riga [MAXRIGA], int *lun)
{
int c, k;

    riga_s01++;
    for (k=0; k<MAXRIGA; k++)
      riga[k] = (char)NULL;

    for (k=0; (c = fgetc(fp_s01)) != '\n'; k++) 
        {
        if (c == EOF) 
            {
            fprintf(stderr, 
             "ATTENZIONE end_of_file inatteso del file S01\n");
            exit( 1);
            }
        if (k == MAXRIGA-1) 
            {
            fprintf(stderr, 
             "ATTENZIONE riga %d supera %d caratteri.\n", riga_s01, MAXRIGA);
            exit( 1);
            }
        riga[k]=c;
        }
    riga[k]=(char)NULL;

    if (k == 0)
       {
       fprintf(stderr,
        "ATTENZIONE nel file S01 la riga %d e' vuota\n", riga_s01);
       exit( 1);
       }
    if (riga[0] == ' ') 
       {
       fprintf(stderr, 
        "ATTENZIONE nel file S01 la riga %d inizia con blank\n", riga_s01);
       fprintf(stderr, "L'elaborazione continua!\n");
       }
    *lun = k;
}





/*
*/
void separa_str( char riga[], int lun, int nstr, STRIN_ST strin[])
{
char *s;
int i;


for (s=riga, i=0; i<nstr; i++) 
    {
    s = strtok( s, " \t");
    if(s == (char*)NULL)
         {
         strin[i].stringa=(char*)realloc(strin[i].stringa,3);
         sprintf(strin[i].stringa," ");
         strin[i].lun_stringa = strlen(strin[i].stringa);
         }
    else
         {
         strin[i].lun_stringa = ( s ? strlen( s) : 0 );
         strin[i].stringa=(char*)realloc(strin[i].stringa,
                                         (strin[i].lun_stringa + 1));
         strcpy(strin[i].stringa, s);
         }
    s = (char*)NULL;
    }
}





/*
     Legge una riga da f01.dat
*/
char *getpul (char *str, int n, FILE *fp)
{
char *ptr;
if (! fgets (str, n, fp))
   return NULL;
ptr = str + strlen(str) - 1;
for ( ; ptr >= str && (unsigned)*ptr <= 32; )
   *(ptr--) = '\0';
return (str);
}





/*
    Funzione presa pari pari dalla libreria libsim (f22_func.c)
*/
int f22_leggi_camp(PUNT_FILE_F22 punt,F22CIRC_HD header,
                float *tempo, SCIRC_SEL_DATI **dati,
                int p1, int p2, int p3, int p4)
{
int campione;
int size_campione = (header.num_var_graf ) *sizeof(float) + sizeof(F22CIRC_T);
int offheader     = sizeof(HEADER_REGISTRAZIONI) + sizeof(F22CIRC_HD) +
                   sizeof(F22CIRC_VAR) * header.num_var_graf;
int offset;
int camp;
static F22CIRC_HD header_save;
static int p1_save = -1;
static int p2_save = -1;
static int p3_save = -1;
static int p4_save = -1;
div_t divis;
int conta=0;
float tempo_prec=-9;

float *valori;
F22CIRC_T t_22;

valori = (float*)malloc(sizeof(float)*header.num_var_graf);

printf("f22_leggi_camp t > %f sizeof(F22CIRC_T) = %d   \n",
                *tempo,sizeof(F22CIRC_T));


/*
        annullo i puntatori
*/
*dati = NULL;
camp = 0;


campione=header.p_fine;

if(header.p_fine == header.p_iniz)
        {
        printf("Esco perche' header.p_fine == header.p_iniz\n");
        return(1);
        }

conta=0;

printf("f22_leggi_camp: p_iniz_new = %d p_fine_new = %d\n",
        header.p_iniz, header.p_fine);

while(1)
        {
        offset=offheader + (campione-1) * size_campione;
        sposta(punt.fp,offset);
        leggi(&t_22,sizeof(F22CIRC_T),1,punt.fp);
        leggi(valori,sizeof(float),header.num_var_graf,punt.fp);

        conta++;

printf("f22_leggi_camp: conta = %d tempo = %lf\n", conta,t_22.tempo);

        divis = div(conta, intstampa);
        if ( (divis.rem == 0)||(conta==0 ) )
              printf("%d)   tempo=%f\n",conta,t_22.tempo,campione);

        if(t_22.tempo <= *tempo)
                {
                printf("  Esco per il break \n");
                break;
                }
        /*
                sistema i valori nei vettori
        */
        ++camp;
        *dati = (SCIRC_SEL_DATI *)
                realloc(*dati, sizeof(SCIRC_SEL_DATI) * camp);
        (*dati)[camp-1].tempo.tempo = t_22.tempo;
        if(p1>=0)
         (*dati)[camp -1].mis[0] = valori[ p1];
        else
         (*dati)[camp -1].mis[0]= 0;
        if(p2>=0)
         (*dati)[camp -1].mis[1] = valori[ p2];
        else
         (*dati)[camp -1].mis[1] = 0;
        if(p3>=0)
         (*dati)[camp -1].mis[2] = valori[ p3];
        else
         (*dati)[camp -1].mis[2] = 0;
        if(p4>=0)
         (*dati)[camp -1].mis[3] = valori[ p4];
        else
         (*dati)[camp -1].mis[3] = 0;

        /*
         * calcolo campione successivo
         */
        if(campione == header.p_iniz)
                break;
        -- campione;
        if(campione == 0)
                campione = header.num_campioni;
if( tempo_prec==t_22.tempo )
    printf("    tempo_prec==t_22.tempo=%f campione=%d\n",t_22.tempo,campione);
tempo_prec = t_22.tempo;
        }

free(valori);

if(camp>0)
        {
        qsort(*dati,camp,sizeof(SCIRC_SEL_DATI),(__compar_fn_t)ComparaCampioni);
        *tempo = (*dati)[camp-1].tempo.tempo;

        printf("Ultimo tempo leggo = %f\n",*tempo);

        }

/*
        riempie l'ultimo campione  (tappo)
*/
++camp;
*dati = (SCIRC_SEL_DATI *) realloc(*dati, sizeof(SCIRC_SEL_DATI) * camp);
(*dati)[camp -1].tempo.tempo = -1;

return(1);
}





/*
    Usata per fare una qsort fra i tempi della struttura SCIRC_DATI
*/
static int ComparaCampioni(SCIRC_DATI *p1,SCIRC_DATI *p2)
{

if(p1->tempo.tempo > p2->tempo.tempo)
        return(1);

if(p1->tempo.tempo < p2->tempo.tempo)
        return(-1);

return(0);
}
/* Fine File */
