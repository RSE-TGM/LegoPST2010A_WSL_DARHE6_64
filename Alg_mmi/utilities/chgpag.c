/*
   modulo chgpag.c
   tipo 
   release 1.1
   data 1/8/96
   reserved @(#)chgpag.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)chgpag.c	1.1\t1/8/96";
/*
        Fine sezione per SCCS
*/
/*                 chgpag.c    S.Balistreri

 *programma di utilita' che consente di duplicare pagine del gruppo 3 e generar
 *le del gruppo 4 cambiando nel file.pag le relative tag.Inoltre e' possibile
 *cambiare i colori delle varie soglie
 */
 


#include<stdio.h>
#include<string.h>
#include <stdlib.h>


extern int cambia(char *,char **,int ,char *,int,int);
extern int found[];

#define DIM 200        /*dimensione max della linea da leggere da file*/
#define NEWL 30
#define MAXARG 5

/* CAMBIO TAG */
/* char *wordkeymodify[]={"varName1:","varName2:","varName3:","varName4:",
		       "varInputCambioColore1:","varInputCambioColore2:",
		       "varInputCambioColore3:","varInputCambioColore4:"
		       };
*/
char wordkeymodify;                         /*var per nome record da modificare */
char newrecord[NEWL];                             /*var che contiene la nuova stringa */
char pathnomepagina[80],salvapagina[80];    /*in salvapagina .bak */

FILE *fp,*fp1,*fp2;


main (argc,argv)
int argc;
char **argv;
{ 

int ritm1=0;
int ritm2=0;
int numrecord=0;         /*numero record che voglio modificare */
int risultato=0;
int i;


if (argc<2) {
#ifndef VMS 
  printf("\n \t\tSintassi di chgpag:\n");
  printf("chgpag <page_name> <newstringa> <operation(0,1)> <position> <keyname>..<>");
  getc(stdin);
  printf("\n <page_name>: path nome del file da convertire ");
  printf("\n <newstringa>: stringa da sostituire");
  printf("\n <operation(0,1)>: 0=sostituzione completa");
  printf("\n                 : 1=sostituzione parziale");
  printf("\n <position>: posizione iniziale per la sostituzione se operation=1");
  printf("\n <keyname>: elenco di una o più parole chiave");
#else
  printf("\n \t\tSintassi di chgpag:\n");
  printf("chgpag <page_name> <newstringa> <operation(0,1)> <position> ");
  printf("<keyname>");
  getc(stdin);
  printf("\n <page_name>: path nome del file da convertire ");
  printf("\n <newstringa>: stringa da sostituire");
  printf("\n <operation(0,1)>: 0=sostituzione completa");
  printf("\n                 : 1=sostituzione parziale");
  printf("\n <position>: posizione iniziale per la sostituzione se ");
  printf(" operation=1");
  printf("\n <keyname>: elenco di una o piu' parole chiave,fra apici se"); 
  printf(" con lettere maiuscole");
#endif
  getc(stdin);

  }
else if(argc<MAXARG){
	
 	printf("\t ATTENZIONE linea di comando errata\n");
 	exit(1);
 	}
else
  {

   /* in argv[1] ho path + nome della pagina 
    * in argv[2] ho nuova stringa
    * in argv[3] ho numero tipo operazione
    * in argv[4] ho posizione (considerata nel caso di operazione n.1)
    * in argv[5] inizio elenco nomi chive da modificare
    */

   /* costruisco il path completo con il nome della pagina e ".pag"*/

   strcpy(pathnomepagina,argv[1]);    
  


 		
   strcpy(newrecord,argv[2]); 	
   ritm1=atoi(argv[3]);
   ritm2=atoi(argv[4]);
   if(ritm1>=2){
   	printf("Opzione selezionata diversa da 0 od 1: conversione abortita\n");
   	exit(1);
   	}
   numrecord=argc-MAXARG;
   
/*Azzera tabella parole chiave da trovare */
   
   for(i=0;i<numrecord;i++)
	found[i]=0; 

/*Chiama la routine di sostituzione*/

risultato=cambia(pathnomepagina,&argv[5],numrecord,newrecord,ritm1,ritm2);

/*Valutazione degli errori */
 
 	   switch(risultato){
   		case 0:
   		printf("\n\t Nessuna parola chiave non trovata\n ");
   		getc(stdin);
   		break;
   		
   		case 1:
   		printf("\n\t Operazione conclusa positivamente\n");
   		break;
   		
   		case 2:
 		printf("\n\t Impossibile trovare il file sorgente \n");  		
 		getc(stdin);
   		break;
   		
   		case 3:
   		printf("\n\t Impossibile aprire il file temporaneo \n");
   		getc(stdin);
   		break;
   		
   		case 4:
   		printf("\n\t Valore di posizione troppo grande \n");
   		getc(stdin);
   		break;
   		
   		case 5:
   		for(i=0;i<numrecord;i++){
			if(found[i]==0){
				printf("Risorsa %s non trovata \n",argv[5+i]);
				getc(stdin);
   				}
   			}	
   		break;	
   			
   		default:
   		break;
   			
   		} 	/* end switch */
  } 	/*end if ... else*/
} 	/* end main */









