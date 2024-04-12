/*
   modulo cercastr.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)cercastr.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*                                                                    *
*			Procedura cercastr                                        *
*                                                                    *
*	Date due stringhe verifica se la seconda e' contenuta nella prima
*  compresa fra separatori
*
*	Parametri
*		char *	str1
*		char *	str2
*
*	Ritorno
*		NULL	se non trovata
*		char * puntatore all'indirizzo in cui e'stata trovata la stringa
*				 str2
*                                                                    *
*********************************************************************/
#include "osf1.h"
#include <stdio.h>
#include <string.h>
#include "tipi.h"

extern char linea_cor[];	  

char * cercastr(str1, str2)
char* str1;
char* str2;
{
	char *var;

	while(var=strstr(str1,str2))
	{
//
//		verifico se il carattere precedente e' un separatore

		if(issep(*(var-1))!=-1)
		{
//
//		verifico se l'ultimo carattere e' un separatore
//
			if(issep(*(var+strlen(str2)))!=-1)
			{
				return(var);
			}
		}
		str1=var+1;
	}
	return (NULL);
}

