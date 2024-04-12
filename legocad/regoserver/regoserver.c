/**********************************************************************
*
*       C Source:               regoserver.c
*       Subsystem:              1
*       Description:
*       %created_by:    stefania %
*       %date_created:  Wed Sep 11 14:42:07 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: regoserver.c,2 %  (%full_filespec: 1,csrc,regoserver.c,2 %)";
#endif

/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)regoserver.c	1.2\t3/31/95";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
char buff[1024];
char buf4[4];
char buf80[80];
char iblock1[7];
float dati[50];
/*
 regoserver
 Richiama le routines lego per la generazione delle liste delle variabili e dei  dati.
		regoserver N D
 dove N e' l'indice del modulo LEGO in lista_moduli_reg.dat genera la lista dei
 dati per il modulo N-esimo.
		regoserver N DT
 dove N e' l'indice del modulo LEGO in lista_moduli_reg.dat genera la lista dei
 dati per il modulo N-esimo.+ totale num dati
		regoserver N V
 genera la lista delle variabili per il modulo N-esimo.
*/
main(argc,argv)
int     argc;
char    *argv[];
{
int ifun,ier;
int id = 0;
int iblock2=11;
int num_modulo;
if(argc < 2)
	{
	printf("\n errore: chiamata corretta= regoserver N (numero modulo)");
	exit(1);
	}
num_modulo=atoi(argv[1]);
if(argc > 2 )
	{
	if(strcmp(argv[2],"d")==0 || strcmp(argv[2],"D")==0)
		{
		strcpy(iblock1,"XXXXYY");
                ifun = 1;  /* scrittura dati su file 14 */
		modrdat_(&num_modulo,&ifun,iblock1,&iblock2,dati,&id,&ier);
		}
         if(strcmp(argv[2],"dt")==0 || strcmp(argv[2],"DT")==0)
                {
                strcpy(iblock1,"XXXXYY");
                ifun = 2; /*lettura dati da file 14 */
                modrdat_(&num_modulo,&ifun,iblock1,&iblock2,dati,&id,&ier);
                printf("totdati=%d\n",id);
                }
	 else if (strcmp(argv[2],"v")==0 || strcmp(argv[2],"V")==0)
		{
		modrvar_(&num_modulo,buf4,buf80);
		}
	}
else
	{
	modrvar_(&num_modulo,buf4,buf80);
	}
exit(2);
}
