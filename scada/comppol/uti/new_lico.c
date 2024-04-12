/*
   modulo new_lico.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)new_lico.c	1.1
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
#include <memory.h>

#include "defpath.inc"

#include "define.inc"
#include "chascii.inc"

extern short fdi,fdlst,fddeb;
extern short numriga;
extern short nword_o;
extern short contif;
extern short righelst;

extern char linea_cor[];

char stringacod[DMX_RILST];


/*********************************************************************
*								                                             *
*			Procedura new_lico()                                        *
*								                                             *
* La procedura legge dal file di input una riga, compatta i blank,   *
* toglie i commenti e le tabulazioni e rende in linea_cor la stringa *
* modificata e scrive la riga cosi come la trova nel file di listing *
* togliendo le tabulazioni perche' indenta il programma e scrivendo  *
* prima sul file di listing il numero di riga corrente ed il program *
* counter.							                                       *
* Ritorna -1 se e' stata trovata la fine del file di input,          *
* 1 altrimenti.  						                                    *
*								                                             *
*********************************************************************/

new_lico()

{

 short semvirg=0,loc=-1,t,i,n,j,z;
 char s[DMX_RIGA],*p,c[1];

 memset(s,0,DMX_RIGA);           // resetto il buffer s
 memset(linea_cor,0,DMX_RIGA);   // resetto il buffer linea_cor


 p=s;

 while (1) {

	i=0;

	while((n=read(fdi,c,1))!=0 && c[0]!=0x0a && c[0]!=0x0d ) {
      
   	if (n==-1) 
      {
         break;
      }
		s[i++]=c[0];
		if ( i >= (DMX_RIGA-1) ) {

		/* Linea file sorgente troppo lunga */

		stampa_err(65,0,"0");
		break;

		}

		}

	if (n==0 || n==-1)
		return(-1);

	s[i]='\0';

	for(i=0;s[i]!=0x00;i++)
		s[i]=toupper(s[i]);
	if(fdlst>0 || fddeb>0) {
/* preparo la stringa da scrivere nel file di listing con questo formato
   I campo :	numero di riga corrente del file di input
  II campo :    valore corrente del program counter
 III campo : 	riga del file di input senza tab. perche' li aggiunge
		la procedura */

		sbianca(stringacod,DMX_RILST);
		j=0;
		for(p=s,i=0;s[i]!=0x00 && s[i]<=BLANK;i++)
			p++;
		j+=sprintf(stringacod,"%04d",numriga+1);
		stringacod[j++]=BLANK;
		j+=sprintf(&stringacod[++j],"%04d",nword_o);
		stringacod[j++]=BLANK;
		for(i=0;i<contif;i++)
			j+=8;
		j+=sprintf(&stringacod[j],"%s",p);
		for(i=0;i<=j;i++)
			if(stringacod[i]==0x0a)
				stringacod[i]=BLANK;
		if(fddeb>0) {
			for(i=0;i<j;i++)
				if(stringacod[i]<BLANK)
					stringacod[i]=BLANK;
			if(j<72)
				while(j!=72)
					stringacod[j++]=BLANK;
 			stringacod[72]=0x00;
			scrivisufile(fddeb,stringacod,73,&loc);
		}
		if(fdlst>0)
			scrivisufile(fdlst,stringacod,j+1,&righelst);
	}
	for (p=s,t=0;*p!='\0' && (*p!=CAR_COMM || (*p==CAR_COMM && semvirg==1)) && *p!=CR; p++)   {
		if(*p==VIRGOLETTE)
				semvirg=!semvirg;
		if(*p!=BLANK)  {        /* se non blank  */
			if(*p!=TAB)     /* e non tab     */
				linea_cor[t++]=*p;
			else            /* se tab inserisco un blank a meno che */
				if(t!=0 && linea_cor[t-1]!=BLANK && linea_cor[t-1]!=0x2c)       /* il precedente non sia BLANK */
					linea_cor[t++]=BLANK;
		}
		else    {
			while(*++p==BLANK && semvirg==0)   /* tolgo tutti i */
				;              /*     blank     */
			if (t>0)
/* inserisco un blank a meno che il precedente non lo sia gi… 
	ed in ogni caso se si tratta di una stringa di tipo DATA    */
				if(semvirg==1 || (linea_cor[t-1]!=BLANK && linea_cor[t-1]!=0x2c))       /* il precedente non sia BLANK */
					linea_cor[t++]=BLANK;  /* ne lascio 1*/
			p--; 		                       /* come separatore */
		}
	}
	if(t==0)  /* riga vuota */
		numriga++;
	else   {
		if(linea_cor[t-1]==BLANK)
			linea_cor[t-1]='\0';
		numriga++;
		return(1);   /* riga modificata */
	}
}
}

