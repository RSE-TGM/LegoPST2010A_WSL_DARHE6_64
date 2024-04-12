/*
   modulo chgtask.c
   tipo 
   release 1.1
   data 1/8/96
   reserved @(#)chgtask.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)chgtask.c	1.1\t1/8/96";
/*
        Fine sezione per SCCS
*/
/*                 chgtask.c    F.Lodigiani

 *programma di utilita' che consente di cambiare i nomi delle variabili dei
 *task di regolazione presenti nei file....... 
 */
 


#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define DIM 200
#define LUNG_VAR 60
 
/* CAMBIO TAG */


extern int converti(FILE *,FILE *,FILE *);

main (argc,argv)
int argc;
char *argv[];

/*
*argv[1]=path+nome del file vecchio da convertire
*argv[2]=path+nome del file in cui ci sono le path con i nuvi nomi delle task di 
*regolazione
*/
{ 

FILE *fp,*fp1,*fp2;
int risultato;	/*risultato della conversione */
char comando[LUNG_VAR]; /*linea di comando */
char pathname[LUNG_VAR];/*pathname+nome del file da convertire */
char pathnamebak[LUNG_VAR];/*pathname+nome del backup*/

/*controllo di argc ed help */
if(argc<3)
	{
	printf("Programma per la conversione dei nomi dei task \n");
	printf("di regolazione e delle relative variabili\n");
	printf("Linea dicomando: chgtask <path+file_name(source)> <path+file_name(r_pathname)>\n");
	getc(stdin);
	exit(1);
	}

/*
apertura del file da modificare
*/


strcpy(pathname,argv[1]);
	
if((fp=fopen(argv[1],"r"))==NULL)
	{
	printf("Impossibile aprire file da convertire \n");
	exit(1);
	}
	
/*
Apertura file con le path delle var dei task di regolazione 
*/

if((fp1=fopen(argv[2],"r"))==NULL)
	{
	printf("Impossibile aprire file con elenco task regolazione \n");
	exit(1);
	}
	
if((fp2=fopen(strcat(argv[1],".fab"),"w"))==NULL)
	{
	printf("Impossibile aprire file convertito");
	exit(1);
	}
/*
invoca la routine di conversione
*/	

risultato=converti(fp,fp1,fp2);

/*
debugging	
*/

/* 
Chiusura di tutti i files
*/
fclose(fp);	
fclose(fp1);	
fclose(fp2);

/*crea copia di backup*/
strcpy(pathnamebak,pathname);	
sprintf(comando,"cp %s %s",pathname,strcat(pathnamebak,".bak"));

system(comando);
/*copia file temporaneo su sorgente*/
sprintf(comando,"cp %s %s",argv[1],pathname);

system(comando);

if(unlink(argv[1])==-1){
	printf("\n Impossibile eliminare file temporaneo\n");
	exit(1);
	}
	
printf("Conversione effettuata positivamente\n");
getc(stdin);	
}/*end main*/
