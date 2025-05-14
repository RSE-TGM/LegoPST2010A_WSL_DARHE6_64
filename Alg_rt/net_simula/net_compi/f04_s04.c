/**********************************************************************
*
*       C Source:               f04_s04.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Mar 18 11:39:51 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: f04_s04.c-2 %  (%full_filespec: f04_s04.c-2:csrc:1 %)";
#endif
/*
   modulo f04_s04.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)f04_s04.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)f04_s04.c	5.1\t11/7/95";
/*
        Fine sezione per SCCS
*/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
#if defined UNIX
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif
#if defined VMS
#include <types.h>
#include <stat.h>
#include <file.h>
#endif
#include <limits.h>     /* definition of OPEN_MAX */
# include "sim_param.h"
# include "sim_types.h"
# include "net_compi_fun.h"
#include <sqlite3.h>


#define TRUE 1
#define FALSE 0
/* ************** Definizione variabili globali ******************** */

extern FILE *fopen(), *fp_s04;

F04  f04_;

/* Sqlite handler */
extern sqlite3 *db;

extern char path_svil[MAX_MODEL][80];

void read_f04_write_s04(varlego,k,model)

   VARLEGO *varlego;
   int k;
   MODEL model[MAX_MODEL];

   {

   /*
	parametri lego
   */
#if defined UNIX
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
	char *s;
      int i,nderiv;
      int fd;
      int flag;
      char unita[4];
      char unita64[8];
/* per lettura fortran file f04.dat record 1 */
int neqs1,npvrt,nu1,nvri;

/* per lettura fortran file f04.dat record 2 */
int issisx,nbtrix,nstx,sigla1x,sigla2x;
int *noslx; /* [N001] */

/* per lettura fortran file f04.dat record 3 */
int nosub,noblc[2],nusta,nusci,ningr,islb;

/* per lettura fortran file f04.dat record 4 */
float var[2];

/* per lettura fortran file f04.dat record 5 */
int *ips /* [M004] */, *ipvrt /* [N005] */;
float sivar[2];

/* per lettura fortran file f04.dat record 6 */
int *ipi  /*  [M005]  */;
float vari[2];
int *ipvri  /* [M001] */;

      
/* per lettura fortran file f04.dat record 7 e 8*/
int *bidone /* [N003+N004+N005] */;

int numcar;

char **cdim2(int,int);

/* Determinazione del pathname del file da aprire */

      f04_.path[0] = (char)NULL;

#if defined UNIX
      strcat(f04_.path,path_svil[k]);
      strcat(f04_.path,"proc/f04.dat");
#endif

#if defined VMS
	memcpy(f04_.path,path_svil[k],strlen(path_svil[k])-1);
	f04_.path[strlen(path_svil[k])-1]='\00';
        strcat(f04_.path,".proc]f04.dat");
#endif

/*
printf("k=%d\n",k);
printf( "Path_svil del modello:  %s\n", path_svil[k]  );
printf( "Path del modello:  %s\n", f04_.path);
*/


/*printf( "f04_ del modello:  %s\n", f04_.path);*/

      f04_.lun_path = strlen(f04_.path);

/* Lettura dei dati dal file "FORTRAN" f04 */

/*printf("lettura fortran di ");*/
#if defined VMS 
      read_f04_();
#else

/*
        allocazione dinamica struttura F04
*/
f04_.nom_bloc = (char **)cdim2(_N002,MAX_LUN_NOME_BLOCCO);
f04_.nom_sivar = (char **)cdim2(_N003,100);
f04_.nom_vari = (char **)cdim2(_N004,100);
f04_.ip = (int *)malloc(sizeof(int)*_M003);
f04_.ipvrs = (int *)malloc(sizeof(int)*_N005);
f04_.iout_sivar = (int *)malloc(sizeof(int)*_N003);
f04_.iout_vari = (int *)malloc(sizeof(int)*_N004);
f04_.ipdati = (int *)malloc(sizeof(int)*(_N002+1));

/*
	allocazione dinamica dati appoggio
*/
noslx = (int *) malloc(sizeof(int)*_N001);
ips = (int *) malloc(sizeof(int)*_M004);
ipvrt = (int *) malloc(sizeof(int)*_N005);
ipi = (int *) malloc(sizeof(int)*_M005);
ipvri = (int *) malloc(sizeof(int)*_M001);
bidone = (int *) malloc(sizeof(int)*(_N003+_N004+_N005));


/* prova lettura in C file FORTRAN */
 fd = open(f04_.path, O_RDONLY);
   if ( fd == -1 )
      perror("error opening file f04.dat\n");
 
/*
printf("apertura file f04 fd=%d\n",fd);
*/
#if defined x86_64
   read( fd, unita64, 8 );
#else
   read( fd, unita, 4 );
#endif
   flag = FALSE;

/*
printf("Lettura record numero 1 %d %d %d\n",
	&(f04_.nbl),&(f04_.neqal),&(f04_.nbl1));
*/

leggi_record_ftn( fd,sizeof(int)*10,1,flag,10,
		   &(f04_.nbl),sizeof(int),
		   &(f04_.neqal),sizeof(int),
		   &(f04_.nbl1),sizeof(int),
		   &(f04_.nvart),sizeof(int),
		   &(f04_.neqsis),sizeof(int),
		   &(neqs1),sizeof(int),
		   &(npvrt),sizeof(int),
		   &(f04_.nu),sizeof(int),
		   &(nu1),sizeof(int),
		   &(nvri),sizeof(int));

/*
printf("Lettura record numero 2\n");
*/
flag=TRUE;
leggi_record_ftn( fd,sizeof(int)*5,1,flag,5,
		   &issisx,sizeof(int),
		   &nbtrix,sizeof(int),
		   &nstx,sizeof(int),
		   &sigla1x,sizeof(int),
		   &sigla2x,sizeof(int));
/*
printf("nstx=%d\n",nstx);
*/
flag=FALSE;
leggi_record_ftn( fd,sizeof(int),nstx,flag,1,
		   noslx,sizeof(int));

/*
printf("Lettura record numero 3\n");
*/
flag=TRUE;
for(i=0;i<f04_.nbl;i++)
	{
	leggi_record_ftn( fd,sizeof(int)*7+MAX_LUN_NOME_BLOCCO,1,flag,8,
		&nosub,sizeof(int),
		&noblc[0],sizeof(int),
		&noblc[1],sizeof(int),
		&nusta,sizeof(int),
		&nusci,sizeof(int),
		&ningr,sizeof(int),
		&islb,sizeof(int),
		f04_.nom_bloc[i],MAX_LUN_NOME_BLOCCO);
		/*printf("Blocco %d -> %s\n",
			i,f04_.nom_bloc[i]);*/

	flag=FALSE;
	}

/*
printf("Lettura record numero 4\n");
*/
flag=TRUE;
leggi_record_ftn( fd,sizeof(int),f04_.nbl1,flag,1,
		f04_.ip,sizeof(int));
flag=FALSE;
for(i=0;i<f04_.nvart;i++)
	{
	leggi_record_ftn( fd,sizeof(int),2,flag,1,
		var,sizeof(int));
	leggi_record_ftn( fd,sizeof(int),1,flag,1,
     		&(f04_.ipvrs[i]),sizeof(int)); 
/*
	printf("f04_.ipvrs[%d]=%d\n",i,f04_.ipvrs[i]);
*/
	}

flag=TRUE;
leggi_record_ftn( fd,sizeof(int),neqs1,flag,1,
		ips,sizeof(int));
flag=FALSE;
for(i=0;i<f04_.neqsis;i++)
	{
	leggi_record_ftn( fd,sizeof(int),2,flag,1,
		sivar,sizeof(int));
	leggi_record_ftn( fd,sizeof(char)*100,1,flag,1,
		f04_.nom_sivar[i],sizeof(char)*100);
	leggi_record_ftn( fd,sizeof(int),1,flag,1,
     		&(f04_.iout_sivar[i]),sizeof(int)); 
/**
	printf("f04_.nom_sivar[%d]=%s\n",i,f04_.nom_sivar[i]);
**/
	}
leggi_record_ftn( fd,sizeof(int),npvrt,flag,1,
		ipvrt,sizeof(int));

/*
printf("Lettura record numero 6\n");
*/
flag=TRUE;
/*
printf("nu=%d\n",f04_.nu);
printf("nu1=%d\n",nu1);
*/
leggi_record_ftn( fd,sizeof(int),nu1,flag,1,
		ipi,sizeof(int));
flag=FALSE;
for(i=0;i<f04_.nu;i++)
	{
	leggi_record_ftn( fd,sizeof(float),2,flag,1,
		vari,sizeof(float));
/*
	printf("vari[0]=%f vari[1]=%f\n",vari[0],vari[1]);
*/
	leggi_record_ftn( fd,sizeof(char)*100,1,flag,1,
		f04_.nom_vari[i],sizeof(char)*100);
	leggi_record_ftn( fd,sizeof(int),1,flag,1,
     		&(f04_.iout_vari[i]),sizeof(int)); 
/**
	printf("f04_.nom_vari[%d]=%s\n",i,f04_.nom_vari[i]);
	printf("f04_.iout_vari[%d]=%d\n",i,f04_.iout_vari[i]);
**/
	}
leggi_record_ftn( fd,sizeof(int),nvri,flag,1,
		ipvri,sizeof(int));

/*
printf("Lettura record numero 7\n");
*/
flag=TRUE;
leggi_record_ftn( fd,sizeof(int),8,flag,1,
			&bidone[0],sizeof(int));

/*
printf("Lettura record numero 8\n");
*/
flag=TRUE;
leggi_record_ftn( fd,sizeof(int),f04_.neqsis+f04_.nu+f04_.nvart,flag,1,
			&bidone[0],sizeof(int));

/*
printf("Lettura record numero 9\n");
*/
flag=TRUE;
leggi_record_ftn( fd,sizeof(int),1,flag,1,
			&f04_.ndati,sizeof(int));
/*printf("ndati=%d nvart=%d\n",f04_.ndati,f04_.nvart);*/

flag=FALSE;
leggi_record_ftn( fd,sizeof(int),f04_.nbl1,flag,1,
			f04_.ipdati,sizeof(int));
/*
for(i=0;i<f04_.nbl1;i++)
	printf("f04_.ipdati[%d]=%d\n",i,f04_.ipdati[i]);
*/



/*printf("Chiusura file f04.dat\n");*/
close(fd);
#endif

/* calcolo del numero di equazioni differenziali */

      nderiv=f04_.neqsis-f04_.neqal;

/* controllo di consistenza sul numero delle variabili */

printf("neqsis=%d nu=%d nderiv=%d ndati=%d \n",
		f04_.neqsis,f04_.nu,nderiv,f04_.ndati);

/* si mettono i tappi alla fine delle stringhe (si potrebbero compattare) */
      for ( i=0; i<f04_.nbl; i++)
          f04_.nom_bloc[i][79] = (char)NULL;
      for ( i=0; i<f04_.neqsis; i++)
          f04_.nom_sivar[i][99] = (char)NULL;
      for ( i=0; i<f04_.nu; i++)
          f04_.nom_vari[i][99] = (char)NULL;

/* Scrittura del file S04.DAT */

      fwrite(&f04_.nbl, sizeof(int),1,fp_s04);
      fwrite(&f04_.nbl1, sizeof(int),1,fp_s04);
      fwrite(&f04_.nvart, sizeof(int),1,fp_s04);
      fwrite(&f04_.neqsis, sizeof(int),1,fp_s04);
      fwrite(&f04_.nu, sizeof(int),1,fp_s04);
      fwrite(&f04_.neqal, sizeof(int),1,fp_s04);
      fwrite(&f04_.ndati, sizeof(int),1,fp_s04);

      fwrite(*f04_.nom_bloc, sizeof(char), f04_.nbl*MAX_LUN_NOME_BLOCCO, fp_s04);

/*   MODIFICA
*/
      fwrite(f04_.ipdati,sizeof(int),f04_.nbl1,fp_s04);

      fwrite(f04_.ip,  sizeof(int), f04_.nbl1, fp_s04);


      fwrite(f04_.ipvrs, sizeof(int), f04_.nvart, fp_s04);

      for ( i=0; i<f04_.neqsis; i++)
      {
         fwrite(f04_.nom_sivar[i], sizeof(char), 100, fp_s04);
         fwrite(&f04_.iout_sivar[i], sizeof(int), 1, fp_s04);
      }

      for ( i=0; i<f04_.nu; i++)
      {
         fwrite(f04_.nom_vari[i], sizeof(char), 100, fp_s04);
         fwrite(&f04_.iout_vari[i], sizeof(int), 1, fp_s04);
      }

/*
      printf("------> %d   %d\n",sizeof(f04_.nom_bloc[0]),f04_.nbl);
      printf("------> %d   %d\n",sizeof(f04_.ip[0]),f04_.nbl1);
      printf("------> %d   %d\n\n",sizeof(f04_.ipvrs[0]),f04_.nvart);
      printf("------> %d\n",sizeof(f04_.nom_sivar[0]));
      printf("------> %d\n",sizeof(f04_.iout_sivar[0]));
*/

/* riempimento della struttura varlego */      

      varlego->neqsis = f04_.neqsis;
      varlego->nu = f04_.nu;
      varlego->nderi = nderiv;
      varlego->ndati = f04_.ndati;

      for ( i=0; i<f04_.neqsis; i++) {
          s = strtok( f04_.nom_sivar[i], " \t");
          strcpy(varlego->nom_sivar[i], s);
	}

      for ( i=0; i<f04_.nu; i++) {
          s = strtok( f04_.nom_vari[i], " \t");
          strcpy(varlego->nom_vari[i], s);
	}
#if defined UNIX
/*
        free  struttura F04
*/
cfree2(f04_.nom_bloc);
cfree2(f04_.nom_sivar);
cfree2(f04_.nom_vari);
free(f04_.ip);
free(f04_.ipvrs);
free(f04_.iout_sivar);
free(f04_.iout_vari);
free(f04_.ipdati);

/*
	free dati appoggio
*/
free(noslx);
free(ips);
free(ipvrt);
free(ipi);
free(ipvri);
free(bidone);
#endif


}
