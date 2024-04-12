/*
   modulo chgvar1.c
   tipo 
   release 1.3
   data 3/1/96
   reserved @(#)chgvar1.c	1.3 
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)chgvar1.c	1.1\t1/8/96";
/*
        Fine sezione per SCCS
*/
/*           

 * sono contenute tutte le routine necessarie per modpag.c e
 * modallpag.c
 */



#include<stdio.h>
#include<string.h>

#define DIM 20000
#define DIM_BUF 600

extern FILE *fp,*fp1,*fp2;	/*fp1 superlista, fp error_chgvar, fp2 debug */
char risultato[DIM_BUF];
/*
 cerca_valore :
 		
cerca in superlista.list la variabile con identif passato a *car
restituisce il valore della variabile(UAvalore), 
se trovata, altrimenti restituisce NULL 		
*/
/*********************/
char *cerca_valore(char *car)
/*********************/
{
static char linea1[DIM];
char *car1;

/*
legge da superlista.list e cerca di trovare la variabile
*/
rewind(fp1);
while ((fgets(linea1,DIM-1,fp1))!=NULL)
	{
	if(car1=strstr(linea1,car+strlen("UA@#B@")))
		{
		while((*car1!=':'))
			car1++;
		car1++;
		while((*car1)==' ')
			car1++;
			
		strcpy(risultato,car1); /*header*/
	/*	strcat(risultato,car1);*/  /*inserito valore var*/	
		car1=strchr(risultato,10); 
		*car1=0;	/*elimino \n*/
		
		return(risultato); /*non necessario: risultato globale*/
		}	
	}
	
return(NULL);	/*var not found*/	

}
/************************************************************/
int crea_nuova_lista(void)
/************************************************************/
/*
Funzione che esamina il contenuto della prima linea di ogni file *.list
estrae i nomi delle var da considerare 
La seconda parte esamina tutte le linee del file e riscrive l' output corretto
su superlista.list
*/
{
char linea[DIM],output[DIM],*car,*car1,*car2;
char token[DIM_BUF],stringa[DIM_BUF];
char *tmppag="filetmp";
register int i;
int n_var;
int errore=0;


		
while ((fgets(linea,DIM-1,stdin))!=NULL) {
	
	
	car=linea;
	car1=car;
	while(*car!=10)
		{
		if(car1=strstr(car,"@#B@"))
			{
/*
Acquisisci il token contenente i parametri per identificare la variabile			
*/
			sscanf(car1,"%s",token);
			
			if(car2=cerca_valore(token))
				{
				car=car1+strlen(token);     /*fine della var*/
/*
salva in stringa resto di linea 
*/			
				strcpy(stringa,car); 
/*
 sostituisce a ID var il suo valore 
*/	 
				strcpy(car1,car2);  
				strcat(linea,stringa);

				car=car1+strlen(car2);

				}	
			else
				{
	/*var not found->messaggio*/			
				errore=1;
				fprintf(fp,"variabile not found=%s\n",token);
				
				car+=strlen(token);
				fprintf(fp,"Alla linea %s\n",linea);
				}	
			}
		car++;			
		}/*end if !nwl*/
	
	fputs(linea,stdout);	/*aggiorna il nuovo file*/
	}/* end while */		

/*
Libera memoria allocata per nomi variabili da considerare 
*/


return(errore);	/* Operazione conclusa positivamente */

}
/****************************************************************/

