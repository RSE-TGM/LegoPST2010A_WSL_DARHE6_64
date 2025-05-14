/**********************************************************************
*
*       C Source:               co_n04_s.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Wed Apr  8 16:42:19 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: co_n04_s.c-2 %  (%full_filespec: co_n04_s.c-2:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)co_n04_s.c	5.4\t3/4/96";
/*
   modulo co_n04_s.c
   tipo 
   release 5.4
   data 3/4/96
   reserved @(#)co_n04_s.c	5.4
*/
/*    SUBROUTINE READ_S01_WRITE_S04(VARLEGO,K,MODEL)
  conversione f-c	1991-05-22	Autore	C.Lusso (CISE)
*/
	/* rimuovere se inserita in compi.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sim_param.h"
#include "sim_types.h"
typedef struct strin_st {
  char *stringa;
  int lun_stringa;
  } STRIN_ST;

#include "net_compi_fun.h"
void separa_str( char riga[], int lun, int nstr, STRIN_ST strin[]);

extern FILE *fp_n04;
extern int riga_n04;
extern FILE *fp_s04;

char **cdim2(int,int);

void read_n04_write_s04(varlego,k,model)
 VARLEGO *varlego;
 int k;
 MODEL model[MAX_MODEL];
{
 char file[95], riga[80];
 int lun, nstr, ibl, nbl, nbl1, nvart, neqsis, nu, i, nderiv, ndati,neqal;
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

 char **nom_bloc; /* [N002][80] */
 int *ip; /* [M003] */
 int *ipvrs; /* [N005]  */
 char **nom_sivar; /* [N003] [100] */
 int *iout_sivar; /*  [N003] */
 char **nom_vari; /*  [N004] [100] */
 int *iout_vari; /*   [N004] */
#else
 char nom_bloc[N002][80];
 int ip[M003];
 int ipvrs[N005];
 char nom_sivar[N003][100];
 int iout_sivar[N003];
 char nom_vari[N004][100];
 int iout_vari[N004];
#endif
 STRIN_ST strin [10];

#if defined UNIX
/*
	allocazione vettori
*/
nom_bloc = (char **)cdim2(_N002,80);
nom_sivar = (char **)cdim2(_N003,100);
nom_vari = (char **)cdim2(_N004,100);
ip = (int *)malloc(_M003*sizeof(int));
ipvrs = (int *)malloc(_N005*sizeof(int));
iout_sivar = (int *)malloc(_N003*sizeof(int));
iout_vari = (int *)malloc(_N004*sizeof(int));
#endif

/* Inizializzazione della struttura STRIN_ST */
     for(i=0; i<10; i++)
        strin[i].stringa = NULL;


printf("Modello %d-esimo, non lego. \n",k);

/* Determinazione del pathname del file da aprire */

      file[0] = (char)NULL;

#if defined OSF1 || UNIX
      strcat(file,model[k].path);
      strcat(file,"proc/n04.dat");
#endif

#if defined VMS
        memcpy(file,model[k].path,strlen(model[k].path)-1);
        file[strlen(model[k].path)-1]='\00';
        strcat(file,".proc]n04.dat");
#endif
 

 fp_n04 = fopen( file, "r");
 if (! fp_n04) {
   perror( file);
   exit( -1);
   }
 riga_n04 = 0;

 legge_riga_n04( riga, &lun);
 separa_str( riga, lun, nstr=1, strin);
 if (strcmp( model[k].name, strin[0].stringa)) {
   fprintf( stderr,
    "nome modello inatteso su file N04.\n");
   exit( -1);
   }


 legge_riga_n04( riga, &lun);
 if (sscanf( riga, "%d", &nbl) != 1) {
   fprintf(stderr, "ATTENZIONE riga %d, errore nbl\n", riga_n04);
   exit(1);
   }

/*	scandisce i blocchi */
 nvart = neqsis = nu = 0;
 ip[0] = 1;
 for (ibl = 0; ibl < nbl; ibl++) {
   int neqsis_bl, nu_bl;

/* I vettori dei puntatori vengono inizializzati in ordine di 
   apparizione, per ciascun blocco: prima le neqsis_bl var
   di uscita (valori positivi) e poi le nu_bl var di ingresso
   (valori negativi) a partire dall'indice 1 o -1 (alla Fortran) */

   legge_riga_n04( riga, &lun);
   strcpy( nom_bloc[ibl], riga);

   legge_riga_n04( riga, &lun);
   if (sscanf( riga, "%d", &neqsis_bl) != 1) {
     fprintf(stderr, "ATTENZIONE riga %d, errore neqsis, blocco %d\n", riga_n04, ibl + 1);
     exit(1);
     }

   for (i=0; i<neqsis_bl; i++) {
     legge_riga_n04( riga, &lun);
     strcpy( nom_sivar[neqsis+i], riga);
     separa_str( riga, lun, nstr=1, strin);
     strcpy( varlego->nom_sivar[neqsis+i], strin[0].stringa);
     ipvrs[nvart++] = neqsis+i+1;
     /* ipvrs e' costruito progressivamente */
     }

   legge_riga_n04( riga, &lun);
   if (sscanf( riga, "%d", &nu_bl) != 1) {
     fprintf(stderr, "ATTENZIONE riga %d, errore nu, blocco %d\n", riga_n04, ibl + 1);
     exit(1);
     }

   for (i=0; i<nu_bl; i++) {
     legge_riga_n04( riga, &lun);
     strcpy( nom_vari[nu+i], riga);
     separa_str( riga, lun, nstr=1, strin);
     strcpy( varlego->nom_vari[nu+i], strin[0].stringa);
     ipvrs[nvart++] = -(nu+i+1);
     /* ipvrs e' costruito progressivamente */
     }

   legge_riga_n04( riga, &lun);
   if (strncmp( riga, "****", 4)) {
     fprintf( stderr,
     "ATTENZIONE riga %d, il blocco deve terminare con 4 asterischi\n", riga_n04);
     exit(  -1);
     }

   neqsis += neqsis_bl;
   nu += nu_bl;
   ip[ibl+1] = ip[ibl] + neqsis_bl + nu_bl;
   }

 varlego->neqsis = neqsis;
 varlego->nu = nu;

 legge_riga_n04( riga, &lun);
 if (sscanf( riga, "%d", &nderiv) != 1) {
   fprintf(stderr, "ATTENZIONE riga %d, errore nderiv\n", riga_n04);
   exit(1);
   }
printf("letto nderiv = %d\n",nderiv);

 varlego->nderi = nderiv;

 legge_riga_n04( riga, &lun);
 if (sscanf( riga, "%d", &ndati) != 1) {
   fprintf(stderr, "ATTENZIONE riga %d, errore ndati\n", riga_n04);
   exit(1);
   }
printf("letto ndati = %d riga = [%s]\n",ndati,riga);

 varlego->ndati = ndati;

fclose(fp_n04);

 for (i=0; i<neqsis; i++)
  iout_sivar[i] = (nom_sivar[i][9] == '*') ? 1 : 0;

 for (i=0; i<nu; i++)
  iout_vari[i] = (nom_vari[i][9] == '*') ? 1 : 0;

/* Preparazione dei dati del modello NON LEGO per uniformarlo
   allo standard dello skedulatore */
/* Si assimila una task non lego ad un solo modulo con numero
   totale di variabili pari alla somma degli ingressi e delle
   uscite */
 nbl1 = nbl + 1;
 nvart = nu + neqsis;

 neqal = neqsis - nderiv;

/* scrittura dei dati di tutti i modelli NON LEGO sul file S04.DAT
*/
printf("nbl = %d nvart = %d neqsis = %d nu = %d ndati = %d\n",
	nbl,nvart,neqsis,nu,ndati);

 fwrite( &nbl, sizeof( int), 1, fp_s04);
 fwrite( &nbl1, sizeof( int), 1, fp_s04);
 fwrite( &nvart, sizeof( int), 1, fp_s04);
 fwrite( &neqsis, sizeof( int), 1, fp_s04);
 fwrite( &nu, sizeof( int), 1, fp_s04);
 fwrite( &neqal, sizeof( int), 1, fp_s04);
 fwrite( &ndati, sizeof( int), 1, fp_s04);

 fwrite(nom_bloc[0], sizeof(char), nbl*MAX_LUN_NOME_BLOCCO, fp_s04);

/*
	modifica per la gestione dei dati:
		e' necessario sostituire alla scrittura seguente
		la scrittura del vettore ipdati (vedi file fs4_s04.c )
*/
 fwrite(ip,  sizeof(int), nbl1, fp_s04);


 fwrite(ip,  sizeof(int), nbl1, fp_s04);

 fwrite(ipvrs, sizeof(int), nvart, fp_s04);

 for (i=0; i<neqsis; i++) {
  fwrite( nom_sivar[i], sizeof(char), 100, fp_s04);
  fwrite( &iout_sivar[i], sizeof( int), 1, fp_s04);
 }
 for (i=0; i<nu; i++) {
  fwrite( nom_vari[i], sizeof( char), 100, fp_s04);
  fwrite( &iout_vari[i], sizeof( int), 1, fp_s04);
 }

#if defined UNIX
/*
	libero i vettori 
*/
cfree2(nom_bloc);
cfree2(nom_sivar);
cfree2(nom_vari);
free(ip);
free(ipvrs);
free(iout_sivar);
free(iout_vari);
#endif
for(i=0; i<10; i++) {
    if(strin[i].stringa != NULL)
       free(strin[i].stringa);
}

} /* FINE "co_read_n04_write_s04()" */
