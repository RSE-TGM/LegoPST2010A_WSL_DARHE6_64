/**********************************************************************
*
*       C Source:               ns_funcother.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Mon Jan 12 12:13:23 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: ns_funcother.c-3 %  (%full_filespec: ns_funcother.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)ns_funcother.c	1.9\t2/5/96";
/*
   modulo ns_funcother.c
   tipo 
   release 1.9
   data 2/5/96
   reserved @(#)ns_funcother.c	1.9
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
#include "sim_param.h"
#include "sim_types.h"
#include "sim_ipc.h"
#include "comandi.h"
#include "sked.h"
#include "f22_circ.h"
#include "grsf22.h"
#include "ns_macro.h"
#include <Rt/RtDbPunti.h>
#include <Rt/RtMemory.h>




/* 
   Prototyping funzioni contenute nel file
*/
   Boolean nsRemove(char * );
   Boolean nsCopy(char * , char * );
   static int ComparaCampioni3(SCIRC_DATI *,SCIRC_DATI *);





Boolean nsCopy(char * file_1, char * file_2)
{
char comando[500];
/*
        system non supportata
*/
if(system(NULL)==0)
        return(False);

#if defined VMS
        sprintf(comando,"copy/nolog %s %s",file_1,file_2);
#else
        sprintf(comando,"cp %s %s",file_1,file_2);
#endif

        system(comando);
return(True);
}





Boolean nsRemove(char * file)
{
char comando[500];
/*
        system non supportata
*/
if(system(NULL)==0)
        return(False);

#if defined VMS
        sprintf(comando,"delete/nolog %s;*",file);
#else
        sprintf(comando,"rm %s",file);
#endif

        system(comando);
return(True);
}




/*
    19/1/96
*/
int FinestraEstesaFunzionante(PUNT_FILE_F22 punt,F22CIRC_HD header,
                float *tempo, SCIRC_SEL_DATI **dati,
                float ti, float tf)
{
int intstampa=1000;
int campione;
int size_campione = (header.num_var_graf ) *sizeof(float) + sizeof(F22CIRC_T);
int offset;
int camp;
div_t divis;
int conta=0;
float tempo_prec=-9;
float primo_tempo,ultimo_tempo;

float *valori;
F22CIRC_T t_22;




valori = (float*)malloc(sizeof(float)*header.num_var_graf);

printf("FinestraEstesaFunzionante t > %f sizeof(F22CIRC_T) = %d   \n",
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
while(1)
        {
        offset=(campione-1) * size_campione;
        sposta(punt.fp,offset);
        leggi(&t_22,sizeof(F22CIRC_T),1,punt.fp);
        leggi(valori,sizeof(float),header.num_var_graf,punt.fp);

        conta++;
        /*StampaTempi(conta,campione,camp,t_22.tempo);*/
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

        /*
         * calcolo campione successivo
         */
        if(campione == header.p_iniz)
                break;
        -- campione;
        if(campione == 0)
                campione = header.num_campioni;
if( tempo_prec==t_22.tempo )
    printf("   tempo_prec==t_22.tempo=%f campione=%d\n",t_22.tempo,campione);
tempo_prec = t_22.tempo;
        }

free(valori);

if(camp>0)
        {
        qsort(*dati,camp,sizeof(SCIRC_SEL_DATI),ComparaCampioni3);
        *tempo = (*dati)[camp-1].tempo.tempo;
        ultimo_tempo = *tempo;
        primo_tempo = (*dati)[0].tempo.tempo;

        printf("Primo  tempo %f ultimo tempo=%f\n",primo_tempo,ultimo_tempo);

        printf("Ultimo tempo leggo = %f\n",*tempo);

        }

tf=85000.0;
ti=84000.0;
ConfrontaFinestre(ultimo_tempo,primo_tempo,tf,ti);
/*
return(0);
        riempie l'ultimo campione  (tappo)
*/
++camp;
*dati = (SCIRC_SEL_DATI *) realloc(*dati, sizeof(SCIRC_SEL_DATI) * camp);
(*dati)[camp -1].tempo.tempo = -1;

}





static int ComparaCampioni3(SCIRC_DATI *p1,SCIRC_DATI *p2)
{

if(p1->tempo.tempo > p2->tempo.tempo)
        return(1);

if(p1->tempo.tempo < p2->tempo.tempo)
        return(-1);

return(0);
}
/* Fine File */
