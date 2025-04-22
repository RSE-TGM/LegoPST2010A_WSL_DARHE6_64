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
static char SccsID[] = "@(#)testata.c	5.1\t11/10/95";
/*
   modulo testata.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)testata.c	5.1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "versione_processi.h"

//char   *getenv ();

int numero_processi = (sizeof nomi_processi / sizeof nomi_processi[0]);
NOMI_PROCESSI Nome_del_processo;

void testata (nome,sccs_versione)
char     nome[50];
char     sccs_versione[80];
{
char   *debug;
FILE   * txt;
char    nome_file[30];
int     k,i;
int     indice_versione;

/* 
	riconoscimento nome processo
*/

    for (k = 0; k < numero_processi; k++)
	if (!strncmp (nome, nomi_processi[k].nome, strlen (nome)))
	    break;
    indice_versione = k;

/*
	riconoscimento versione e data
*/
    nomi_processi[indice_versione].versione[0]=0;
    nomi_processi[indice_versione].data[0]=0;
    if(sccs_versione[0]=='@')       
	{
	for(k=0;sccs_versione[k]!='\t';k++);
	k++;
	for(i=0;sccs_versione[k]!='\t';
		nomi_processi[indice_versione].versione[i++]=sccs_versione[k++]);
	nomi_processi[indice_versione].versione[i]='\00';
	k++;
	for(i=0;sccs_versione[k]!='\00';
		nomi_processi[indice_versione].data[i++]=sccs_versione[k++]);
	nomi_processi[indice_versione].data[i]='\00';
	}

     /* copia per procedure about */
     memcpy(&Nome_del_processo,&nomi_processi[indice_versione],
		sizeof(NOMI_PROCESSI));


/* 
	lettura variabile DEBUG

	DEBUG == YES   =====>   output -> file
*/

    debug = getenv ("DEBUG");
    if (debug == NULL)
    {
	debug = (char *) malloc (3 * sizeof (char));
	strcpy (debug, "NO");
    }


    if (strncmp (debug, "YES", 3) == 0)
    {
/* 
	output su terminale
*/
	printf ("\n");
	printf ("*********************************************************\n");
	printf ("Processo: %s\n", nomi_processi[indice_versione].nome);
	printf ("Versione: %s\n", nomi_processi[indice_versione].versione);
#if defined PIACENZA
	printf("Applicazione sviluppata per: DPTSAP Piacenza\n");
#endif
#if defined ENEL_CRA
	printf("Applicazione sviluppata per: ENEL C.R.A. Milano\n");
#endif
	printf ("Data: %s\n", nomi_processi[indice_versione].data);
	printf ("Output: terminale\n");
#if defined F22_APPEND
	printf ("Gestione f22: apertura in append mode\n");
#endif
#if defined LASTSNAP
	printf ("Gestione snapshot: registrazione automatica al termine della simulazione \n");
#endif
#if defined BANCO_ISTRUTTORE
	printf ("Interfacciamento Banco Istruttore: abilitato\n");
#endif
#if defined BANCO_MANOVRA
	printf ("Interfacciamento Banco Manovra: abilitato\n");
#endif
#if defined SCADA
	printf ("Interfacciamento Scada: abilitato\n");
#endif
#if defined BACKTRACK
	printf ("Gestione Backtrack: abilitata\n");
#endif
#if defined SAVEPERT
	printf ("Registrazione Perturbazioni: abilitata\n");
#endif
#if defined REPLAY
	printf ("Gestione REPLAY: abilitata\n");
#endif
#if defined MFFR
	printf ("Gestione Malfunzioni e Funzioni Remote: abilitata\n");
#endif
	printf ("*********************************************************\n");

    }
    else
    {
/* 
	output su file
*/
	sprintf (nome_file, "%s.out", nomi_processi[indice_versione].nome);
	printf ("\n");
	printf ("*********************************************************\n");
	printf ("Processo: %s\n", nomi_processi[indice_versione].nome);
	printf ("Versione: %s\n", nomi_processi[indice_versione].versione);
#if defined PIACENZA
	printf("Applicazione sviluppata per: DPTSAP Piacenza\n");
#endif
#if defined ENEL_CRA
	printf("Applicazione sviluppata per: ENEL C.R.A. Milano\n");
#endif
	printf ("Data: %s\n", nomi_processi[indice_versione].data);
	printf ("Output: file %s\n", nome_file);
#if defined F22_APPEND
	printf ("Gestione f22: apertura in append mode\n");
#endif
#if defined LASTSNAP
	printf ("Gestione snapshot: registrazione automatica al termine della simulazione \n");
#endif
#if defined BANCO_ISTRUTTORE
	printf ("Interfacciamento Banco Istruttore: abilitato\n");
#endif
#if defined BANCO_MANOVRA
	printf ("Interfacciamento Banco Manovra: abilitato\n");
#endif
#if defined SCADA
	printf ("Interfacciamento Scada: abilitato\n");
#endif
#if defined BACKTRACK
	printf ("Gestione Backtrack: abilitata\n");
#endif
#if defined SAVEPERT
	printf ("Registrazione Perturbazioni: abilitata\n");
#endif
#if defined REPLAY
	printf ("Gestione REPLAY: abilitata\n");
#endif
#if defined MFFR
	printf ("Gestione Malfunzioni e Funzioni Remote: abilitata\n");
#endif
	printf ("*********************************************************\n");
	fclose (stdout);
	txt = fopen (nome_file, "w");
	printf ("*********************************************************\n");
	printf ("Processo: %s\n", nomi_processi[indice_versione].nome);
	printf ("Versione: %s\n", nomi_processi[indice_versione].versione);
#if defined PIACENZA
	printf("Applicazione sviluppata per: DPTSAP Piacenza\n");
#endif
#if defined ENEL_CRA
	printf("Applicazione sviluppata per: ENEL C.R.A. Milano\n");
#endif
	printf ("Data: %s\n", nomi_processi[indice_versione].data);
	printf ("Output: file %s\n", nome_file);
#if defined F22_APPEND
	printf ("Gestione f22: apertura in append mode\n");
#endif
#if defined LASTSNAP
	printf ("Gestione snapshot: registrazione automatica al termine della simulazione \n");
#endif
#if defined BANCO_ISTRUTTORE
	printf ("Interfacciamento Banco Istruttore: abilitato\n");
#endif
#if defined BANCO_MANOVRA
	printf ("Interfacciamento Banco Manovra: abilitato\n");
#endif
#if defined SCADA
	printf ("Interfacciamento Scada: abilitato\n");
#endif
#if defined BACKTRACK
	printf ("Gestione Backtrack: abilitata\n");
#endif
#if defined SAVEPERT
	printf ("Registrazione Perturbazioni: abilitata\n");
#endif
#if defined REPLAY
	printf ("Gestione REPLAY: abilitata\n");
#endif
#if defined MFFR
	printf ("Gestione Malfunzioni e Funzioni Remote: abilitata\n");
#endif
	printf ("*********************************************************\n");
    }
}
