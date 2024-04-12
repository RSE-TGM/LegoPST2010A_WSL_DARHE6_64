/*
   modulo insvar_s.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)insvar_s.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*                                                                    *
*                 Procedura insvar_subr                              *
*                                                                    *
*	La procedura serve per inserire nel file di listing (fdlocale     *
* =fdlst) o in quello intermedio (fdlocale=fdint) le variabili locali*
* di ogni subr. Se scrivo sul file intermedio, oltre al nome e all'  *
* offset della variabile scrivo anche il nuovo nome che le e' stato  *
* attribuito.                                                        *
*                                                                    *
*********************************************************************/

#ifdef INGLESE
#define varLocSub    " Subroutine local variables         "
#define varOffTip    " Variable name    Offset   Type "
#define varOffTipNw  " Variable name    Offset   Type     New name"
#else
#define varOffTipNw  " Nome variabile   Offset   tipo     Nuovo nome"
#define varOffTip    " Nome variabile   Offset   tipo "
#define varLocSub    " Variabili locali della subroutine  "
#endif

#include <stdio.h>
#include <string.h>

#include "chascii.inc"

#include "tipi.h"

extern char c[];

#define LUNGSTR	    80
#define POS1	     3
#define POS2	    10
#define POS3        20
#define POS4	    30
#define POS5	    40
#define NUM_ARG	20
extern int contsubr;
extern char *nomi_subr[];
extern int fdlst;
extern int tvarsubr[10][NUM_ARG+1];
extern char *nvarsubr[10][NUM_ARG];
extern char *t_var[];

insvar_subr(fdlocale,righeloc)
int fdlocale;
int *righeloc;
{
int i,j,t;
char stringa[LUNGSTR],nomevar[LUNG_VAR+1];
scrivisufile(fdlocale,c,2,righeloc);
for(i=0;i<contsubr;i++) {
	j=sprintf(stringa,"%s",varLocSub);
	j+=sprintf(&stringa[j],"%s",nomi_subr[i]); /* nome subr. */
	scrivisufile(fdlocale,stringa,j+1,righeloc);
	if(fdlocale==fdlst)
		j=sprintf(stringa,"%s",varOffTip);
	else
		j=sprintf(stringa,"%s",varOffTipNw);
	scrivisufile(fdlocale,stringa,j+1,righeloc);
	for(t=0;t<(tvarsubr[i][NUM_ARG] & 15);t++) {
		sbianca(stringa,LUNGSTR-1);
		j=POS1;
		j+=sprintf(&stringa[j],"%s",nvarsubr[i][t]); /* nome
					      del t-esimo argomento */
		stringa[j]=BLANK;
		j=POS3;
		j+=sprintf(&stringa[j],"%2d",t+1);  /* offset */
		stringa[j]=BLANK;
		j=POS4-4;
		j+=sprintf(&stringa[j],"%s",t_var[tvarsubr[i][t] & 15]);
		if(fdlocale!=fdlst)  {
			stringa[j]=BLANK;    /* creo il nome con cui */
			nomevar[0]=0x23;     /* l' argomento e' stato*/
/*			nomevar[1]=i+0x30;   /* ridefinito e lo inserisco */
			sprintf(&nomevar[1],"%02d",i);		
			strcpy(&nomevar[3],nvarsubr[i][t]);
			j=POS5-4;
			j+=sprintf(&stringa[j],"%s",nomevar);
		}
		scrivisufile(fdlocale,stringa,j+1,righeloc);
	}
	scrivisufile(fdlocale," ",2,righeloc);
}
scrivisufile(fdlocale,c,2,righeloc);
}
