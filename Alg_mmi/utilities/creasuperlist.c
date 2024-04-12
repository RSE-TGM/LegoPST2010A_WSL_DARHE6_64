/*
   modulo creasuperlist.c
   tipo 
   release 1.3
   data 3/1/96
   reserved @(#)creasuperlist.c	1.3
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)creasuperlist.c	1.1\t1/8/96";
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


extern int crea_listone(void);


#define DIM 2000        /*dimensione max della linea da leggere da file*/
#define NEWL 100
#define MAXARG 5
#define MAXLIST 100
/* CAMBIO TAG */
/* char *wordkeymodify[]={"varName1:","varName2:","varName3:","varName4:",
		       "varInputCambioColore1:","varInputCambioColore2:",
		       "varInputCambioColore3:","varInputCambioColore4:"
		       };
*/
char wordkeymodify;                         /*var per nome record da modificare */
char newrecord[NEWL];                             /*var che contiene la nuova stringa */
char pathnomelist[80];

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

char linea[NEWL];
char pathname[NEWL];

if (argc<2) {
 
  printf("\n \t\tSintassi di creasuperlist:\n");
  printf("creasuperlist <file elenco *.list> (<pathname+namesuperlista>)\n");
  getc(stdin);
  printf("\n <file elenco *.list>: file contenente i *.list da considerare ");
  printf("\n <pathname+namesuperlista>: path+nome della superlista ");
  getc(stdin);

  }

else
  {


	if(argc==3)
		{
		strcpy(pathname,argv[2]);
		
		}
	else if(argc==2)
		strcpy(pathname,"superlista.list");
		
	else if(argc>3)
		{
		printf("errore: troppi parametri in input\n");
		exit(5);
		}		

	if((fp1=fopen(pathname,"w"))==NULL)
			{
			printf("\n\t File in input non trovato\n");
			exit(2);	/*errore di tipo 2 */
 			}	
 /* 
 Ciclo di elaborazione per ogni filelist passato come argomento
 */
	
	if((fp2=fopen(argv[1],"r"))==NULL)
			{
			printf("\n\t File con i win*.list nom trovato\n");
			exit(2);	/*errore di tipo 2 */
 			}
 	
 	
 	strcpy(pathnomelist,"");	
	for(i=0;fgets(linea,NEWL-1,fp2);i++)
		{
		sscanf(linea,"%s",pathnomelist);    
		printf("Sto esaminando pathnomelist %s\n",pathnomelist);  	
		
		if((fp=fopen(pathnomelist,"r"))==NULL)
			{
			printf("\n\t File %s in input non trovato\n",pathnomelist);
			return(2);	/*errore di tipo 2 */
 			}			    

/*
Elaborazioni 
*/
		risultato=crea_listone();
		fclose(fp);	/*chiudo file in lettura*/
		}


fclose(fp1);


/*Valutazione degli errori */
 
 	   switch(risultato){
   		case 0:
   		printf("\n\t Operazione conclusa positivamente\n ");
   		getc(stdin);
   		break;
   		
   		case 1:
   		printf("\n\t \n");
   		break;
   		
   		case 2:
 		printf("\n\t Impossibile trovare il file sorgente \n");  		
 		getc(stdin);
   		break;
   		
   		case 3:
		printf("Errore nella lettura del file in input\n");
   		getc(stdin);
   		break;
   		
   		case 4:
   		printf("\n\t Troppe nomi di variabili \n");
   		getc(stdin);
   		break;
   		
   			
   		default:
   		break;
   			
   		} 	/* end switch */
  } 	/*end if ... else*/
} 	/* end main */









