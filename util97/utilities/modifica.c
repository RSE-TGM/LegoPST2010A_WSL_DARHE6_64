/*
   modulo modifica.c
   tipo 
   release 1.1
   data 1/8/96
   reserved @(#)modifica.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)modifica.c	1.1\t1/8/96";
/*
        Fine sezione per SCCS
*/
/*             modifica.c     F.Lodigiani

 * sono contenute tutte le routine necessarie per modpag.c e
 * modallpag.c
 */



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define DIM 200

int found[DIM];
/*
 cambia : sostituisce nel file .pag la risorsa relativa alla
 parola chiave passata come parametro e ritorna un intero che indica
 se l' operazione � riuscita o il tipo di errore
*/
/************************************************************/
int cambia(pagina,findword,numword,newstring,operaz,posiz)
/************************************************************/

char *pagina;       /* path name completo della pagina 
                       da modificare  */
char **findword;    /* array di nomi chiave da cercare  */
int  numword;       /* numero di parole-chiave */
char *newstring;    /* nuova stringa da inserire in sostituzione */
int  operaz;        /* tipo di operazione:
			0 - sostituzione globale
			1 - sostituzione parziale partendo da
			    posiz (prossimo parametro) per una lunghezza
			    pari a strlen(newstring) */
		                                     
int posiz;          /* posizione da cui iniziare la sostituzione */

{
char linea[DIM],stringa[DIM],*car,*car1;
char comando[50],paginabak[50];
char *tmppag="filetmp.bac";



/*lung=intera linea ,lungchiave=lunghezza della chiave    */
/*lungnewstring=lunghezza della nuova stringa             */
/*spaziolavoro=lunghezza dell'insieme chiave-nuova stringa*/ 

int i,set;


FILE *fp,*fp1;

/*
 apri in lettura file da convertire
*/
set=0;
if((fp=fopen(pagina,"r"))==NULL)
	{
	printf("\n\t File da convertire non trovato\n");
	return(2);	/*errore di tipo 1 */
 	}			    

/*apri file temporaneo (copia modificata)*/

if((fp1=fopen(tmppag,"w"))==NULL)
	{
	printf("\n\tImpossibile aprire file temporaneo\n");
	return(3);	/*errore di tipo 2*/
	}

/*aggiunge i : alla fine della keyword*/


/*Legge tutte le stringhe del file */
		
while ((fgets(linea,DIM-1,fp))!=NULL) {


	for(i=0;i<numword;i++){

/*Verifica se trova una parola delle parole chiave */
/*la parola chiave deve essere preceduta da * o da . */

		car=strstr(linea,findword[i]);

/*Se la stringa trovata verifica che sia il nome di una risorsa */
		
		if(car &&(*(car+strlen(findword[i]))==':')&&( ((*(car-1))=='.')||((*(car-1))=='*') )){

	/*Parola chiave trovata*/		

		found[i]=1;
		
	
		 /*Vai alla fine della parola chiave */	
			set=1;		

		 	while((*car)!=':'){
		 		car++;
		 		}
		 		car++;

	/* punta all' inizio del valore daella risorsa da modificare */
	/*salta i caratteri tab o blank */

		 	while(((*car)==9)||((*car)==' ')){
		 		car++;
		 		}	
 			 		

	/* Inizia operazione di modifica*/

			if(operaz){
			
			/* inizia sostituz. parziale: punta a 1� car da sostituire */

			/* se #posizioni > #caratteri risorsa -> errore */

				if(strlen(car)<=posiz){
					
					return(4);
					}	/*errore*/
				car+=posiz;
				car1=car;	/* punto al 1� car da cambiare */

			/* Se il n� di caratteri da sost.< n� caratteri newstring
			copia direttamente la nuova stringa*/	
			
				if(strlen(car)<strlen(newstring)){
					strcpy(car,newstring);
					strcat(linea," \n");
					}

			/*altrimenti inserisce la stringa */		

				else{						
					car+=strlen(newstring);
					strcpy(stringa,car);
					strcpy(car1,newstring);
					strcat(linea,stringa);
					} /* end else*/
				} /*end if(operaz)*/
			else{	

		/*Inizia sostituzione totale */			 	

			 	strcpy(car,newstring);
			 	strcat(linea," \n");
				} /*end else*/
				
		 	} /*end for*/
		 	
		} /*end  if*/
	
	/* Inserisci la stringa nel file temporaneo */
	
	fputs(linea,fp1);


	}/* end while */		
/*Chiude i file aperti*/

fclose(fp);
fclose(fp1);

/*
Controlla che le parole chiave siano state tutte trovate 
*/

for(i=0;i<numword;i++)
	{
	if(found[i]==0)
		{
		set=5;
		
		}
	}	
	
/*Copia file temporaneo sul file da convertire ed elimina file temporaneo */
strcpy(paginabak,pagina);



car=paginabak;		/*Backup file originale.pag */
#ifndef VMS
while((*car)!='.')
	car++;
#else
while(!((*car=='.')&&(*(car+1)=='p')&&(*(car+2)=='a')&&(*(car+3)=='g')&&(*(car+4)==0)))
        car++;
#endif
strcpy(car,".bak");


#ifndef VMS	
sprintf(comando,"cp %s %s",pagina,paginabak);
#else
sprintf(comando,"copy %s %s",pagina,paginabak);
#endif
system(comando);

#ifndef VMS
/*
copia file temporaneo sul file modificato.pag
*/	

sprintf(comando,"cp %s %s",tmppag,pagina);
#else
sprintf(comando,"copy %s %s",tmppag,pagina);
#endif
system(comando);


#ifndef VMS
if(unlink(tmppag)==-1){
	printf("\n Impossibile eliminare file temporaneo\n");
	exit(1);
	}
#else
sprintf(comando,"delete %s;* ",tmppag);
system(comando);
#endif
return(set);	/* Operazione conclusa positivamente */

}
/****************************************************************/

