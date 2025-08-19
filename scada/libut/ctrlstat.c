/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	la function ctrlstato verifica se lo stato in chiaro e' presente nel
	file dizionario e se e' ammissibile per il tipo di organo

	stato		char * stato da controllare
	tab		S_FSTATO * puntatore alla tabella del tipo di organo
					ammissibile
	fp			file pointer file dizionario

	ritorna
				-1		stato non presente nel dizionario
				-2		stato non ammissibile per il tipo di organo
				indice dello stato se e' ammissibile
*/
#include <stdio.h>

#include "fileop.inc"

extern int exstati(char *, char *);

int ctrlstato(stato,tab,diz)
char *stato;
char *diz;
S_FSTATO *tab ;
{

short indice ;
short i;

indice=exstati(stato,diz) ;
if(indice==-1) return(-1) ;
for(i=0;i<num_stati;i++)
{
			if(tab->vet_stati[i] == -1) break ;
			if(tab->vet_stati[i] == indice) return(indice) ;
}
return(-2) ;
}
