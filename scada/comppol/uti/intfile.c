/*
   modulo intfile.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)intfile.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <malloc.h>

#include "defpath.inc"

#include "chascii.inc"
#include "tipi.h"


#define LUNGSTR1	  110
#define POS1	       3
#define POS2         10

extern short nword_o;
extern short fdint;
extern short righeint;


extern char linea_cor[];

/*********************************************************************
*								                                             *
*			 Procedura intfile                                          *
*								                                             *
*  Inserisce nel file intermedio l'istruzione presente in linea_cor, *
*  inserendo prima di essa il numero di word di output, ed           *
*  incrementando il contatore di word della quantita' relativa.      *
*								                                             *
*********************************************************************/

intfile(codice)

short codice;

{

char intlinea[LUNGSTR1];
short i,s;

sbianca(intlinea,LUNGSTR1-1);
i=POS1;
i+=sprintf(&intlinea[i],"%4d",nword_o);
intlinea[i]=BLANK;
nword_o+=wordpar_ch[codice];
i=POS2;
s=strlen(linea_cor);
if(s+i>=LUNGSTR1-1)
	s=LUNGSTR1-2-i;
memcpy(&intlinea[i],linea_cor,s);
i+=s;
intlinea[i++]=0;
/*  i+=sprintf(&intlinea[i],"%s",linea_cor); */
scrivisufile(fdint,intlinea,i+1,&righeint);

}

