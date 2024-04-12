/**********************************************************************
*
*       C Source:               refresh_proc.c
*       Subsystem:              3
*       Description:
*       %created_by:    mauric %
*       %date_created:  Fri Nov 21 13:10:42 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: refresh_proc.c-2 %  (%full_filespec: refresh_proc.c-2:csrc:3 %)";
#endif
/*
   modulo refresh_proc.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)refresh_proc.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)refresh_proc.c	5.1\t11/7/95";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
#endif
#if defined VMS
# include <stdlib.h>
# include "vmsipc.h"
#endif
#include "sim_param.h"
#include "sim_types.h"
#include "libnet.h"
#include "mod_data.h"
#include <Rt/RtMemory.h>

BUF_I2 buffer_;
#if defined UNIX
/*
     parametri lego
*/
extern int _N000;
extern int _N001;
extern int _N002;
extern int _N003;
extern int _N004;
extern int _N005;
extern int _N007;
extern int _M001;
extern int _M002;
extern int _M003;
extern int _M004;
extern int _M005;
#endif

/*
    A  partire  dal numero del  modello, dal numero del blocco, dal
    path del file  f14.dat e dall'offset di inizio del vettore dati
    in SH M viene letta la lista moduli e lanciata la subroutine di
    tipo I2.
*/
int refresh_dati_shm(char *ind_shm_top, VARIABILI *variabili,
                     int numero_mod, char *path14, int numero_bl)
{
FILE *fp_dati;
char *nomeblocco;
int off_dati_bl;
int tot_variabili;
int num_dati;
int num_var;
char path_lista[FILENAME_MAX];
char *path_lista_m;
char *path_lista_s;
char nome_8f14[9];
char nome_4per_lista[5];
char *punt;
int i,ki,tip;
int lnomlist,lnomfile,lnombloc;
int dati_preced=0;
int off_dati = 0;   /* offset dei dati */
int err;
int n_bl_md;
int n_md;
char path14mom[FILENAME_MAX];
char *nome_bl8();
int stop=0;

#if defined UNIX
/*
        allocazione struttura buffer_
*/
     buffer_.bufdati = (float *)malloc(sizeof(float)*_N007);
#endif

     printf("...........................................\n");
     tot_variabili=numero_variabili(ind_shm_top);
     n_md = numero_modelli(ind_shm_top);
     n_bl_md = numero_blocchi(ind_shm_top,numero_mod);
     num_dati = numero_dati(ind_shm_top,numero_mod,numero_bl);
     num_var  = numero_var_bl(variabili,tot_variabili,numero_mod,numero_bl);
     if ( (numero_bl<=0)  || (numero_bl>n_bl_md)  ||
          (numero_mod<=0) || (numero_mod>n_md)        )
        {
        fprintf(stderr,"Uscita da refresh_dati_shm: nmod=%d n_bl=%d\n",
                        numero_mod,numero_bl);
        return(-1);
        }
/*   Cerco la lista moduli opportuna e il numero del modulo in essa   */
     tip = scelta_lista(ind_shm_top,numero_mod,numero_bl,path14,&path_lista_m,
                        &path_lista_s,nome_4per_lista,nome_8f14);
     if (tip==-1)
        {
        fprintf(stderr,"refresh_dati:il blocco non e' nelle liste moduli.\n");
        return(-1);
        }
     else
        if (tip==1)
           memcpy(path_lista,path_lista_m,strlen(path_lista_m)+1);
        else
           memcpy(path_lista,path_lista_s,strlen(path_lista_s)+1);
     free(path_lista_m);
     free(path_lista_s);
/*   Leggo lista_moduli.dat, apro il file e lancio la subroutine "I2" */
     if ( !strlen(nome_8f14) )
        {
        fprintf(stderr,"refresh_dati:manca il blocco in f14.mom.\n");
        return(-1);
        }
     printf("refresh:\n nome_8f14=%s|   nome_4per_lista=%s|\n",
             nome_8f14,nome_4per_lista);
     strcpy(path14mom,path14);
     punt = (char*)strstr(path14mom,"f14.");
     punt+= 4;
     strcpy(punt,"mom");
     lnomfile = strlen(path14);
     lnombloc = strlen(nome_8f14);
     lnomlist = strlen(path_lista);
     r_lstmod_(path_lista,&lnomlist,nome_4per_lista,&ki);
     if ( ki == 0 )
        {
        fprintf(stderr,"refresh_dati:Blocco mancante da lista_moduli/schemi\n");
        return(-1);
        }
     leggi_for_(path14mom,&lnomfile,nome_8f14,&lnombloc,&err);
     if ( err == -1 )
        {
        fprintf(stderr,"refresh_dati:errore ricerca in f14.mom.\n");
        return(-1);
        }
     buffer_.inizoff = _N007/2;
     for (i=buffer_.inizoff;i<2*buffer_.inizoff;i++)
        buffer_.bufdati[i] = -2;
     lancia_i2_(&ki,&num_var,&num_dati);
/*   Test sul lancio della routine I2 per i moduli di processo predisposti */
     printf("il primo offset scritto vale %f\n",
             buffer_.bufdati[buffer_.inizoff]);
     if ( buffer_.bufdati[buffer_.inizoff] == -2 )
        return(-2);
/*   Calcolo dell'offset all'inizio della zona dati del modello */
     for (i=1;i<numero_bl;i++)
        dati_preced+=numero_dati(ind_shm_top,numero_mod,i);
     off_dati_bl = off_dati + dati_preced;
     fp_dati=fopen("dati_var.edf","w");
     if ( fp_dati==NULL )
        exit(fprintf(stderr,"refresh_dati:errore apertura dati_var.edf "));
     i = 0;
     while ( (buffer_.bufdati[buffer_.inizoff+i] != -1.000000)&&(stop<50) )
        {
        stop++;
        i++;
        } 
     printf("off_dati_bl (solo i dati precedenti)=%d\n",off_dati_bl);
     for (i=0;i<stop;i++)
       {
       printf("**Refresh: VALORE=%20.8f     OFFSET=%f**\n",
               buffer_.bufdati[i],
               buffer_.bufdati[buffer_.inizoff+i]);
       fprintf(fp_dati,"Valore[ %2d ]= %-20.8f      Offset= %f\n",
               i,buffer_.bufdati[i],buffer_.bufdati[buffer_.inizoff+i]);
       }
     printf("stampe=%d\n",i);
     printf("...........................................\n");
     return(1);
}
