/*
   modulo chgvar.c
   tipo 
   release 1.3
   data 3/1/96
   reserved @(#)chgvar.c	1.3
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)chgvar.c	1.1\t1/8/96";
/*
        Fine sezione per SCCS
*/
/*                
 *programma di utilita' che consente di duplicare pagine del gruppo 3 e generar
 *le del gruppo 4 cambiando nel file.pag le relative tag.Inoltre e' possibile
 *cambiare i colori delle varie soglie
 */
 


#include<stdio.h>
#include<string.h>
#include <stdlib.h>


extern int crea_nuova_lista(void);


#define DIM 200        /*dimensione max della linea da leggere da file*/
#define NEWL 30
#define MAXARG 5



char newrecord[NEWL];                             /*var che contiene la nuova stringa */
char pathnomelist[80],salvapagina[80];    /*in salvapagina .bak */

FILE *fp,*fp1,*fp2;


main (argc,argv)
int argc;
char **argv;
{ 

int ritm1=0;
int ritm2=0;
int numrecord=0;         /*numero record che voglio modificare */
int risultato=0;
register unsigned int i;

char pathname[100];
  

/* in argv[n] ho path + nome dell' nesimo file lista in input 
Apro file superlista

*/
 if((fp=fopen("error_chgvar.msg","w"))==NULL)
			{
			
			exit(3);	/*errore di tipo 3 */
 			}				
	if(argc==2)
		{
		strcpy(pathname,argv[1]);
		
		}
	else if(argc==1)
		strcpy(pathname,"superlista.list");
	else if(argc>2)
		{
		fprintf(fp,"errore: troppi parametri\n");
		exit(5);
		}		
	if((fp1=fopen(pathname,"r"))==NULL)
			{
			fprintf(fp,"\n\t File in input superlista.list non trovato\n");
			exit(2);	/*errore di tipo 2 */
 			}	
 /* 
 Apertura di file per debug
 */
/*		if((fp=fopen("fabio.pag","r"))==NULL)
			{
			printf("\n\t File in input non trovato\n");
			exit(2);	
 			}	

		if((fp2=fopen("fabio.fin","w"))==NULL)
			{
			printf("\n\t File in input non trovato\n");
			exit(2);
 			}	*/


/*
Elaborazioni 
*/

		risultato=crea_nuova_lista();

fclose(fp);	/*chiudo file in lettura*/
fclose(fp1);
/*fclose(fp2);*/

/*Valutazione degli errori */
 
	switch(risultato){
		case 0:
   		fprintf(fp,"\n\t Operazione conclusa positivamente\n ");
   		getc(stdin);
   		break;
   		
   		case 1:
   		printf("\n\t \n");
                exit(1);
   		break;
 
   			
   		default:
   		break;
   			
   		} 	/* end switch */
	exit(0);  
} 	/* end main */





