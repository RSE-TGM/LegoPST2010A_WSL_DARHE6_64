/*
   modulo chgtask1.c
   tipo 
   release 1.1
   data 1/8/96
   reserved @(#)chgtask1.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)chgtask1.c	1.1\t1/8/96";
/*
        Fine sezione per SCCS
*/
/*             chgtask1.c     F.Lodigiani

 * sono contenute tutte le routine necessarie per chgtask.c 
 * 
 */



#include<stdio.h>
#include<string.h>

#define DIM 200
#define LUNG_VAR 60

char var_regolazione[DIM][LUNG_VAR];
int num_task_regolazione;	/*num task di regolaz.*/


/***********************************/
 void maiuscolo(char *stringa)
/***********************************/
/*procedura che converte una stringa in maiuscolo*/
{
register int i;

for(i=0;i<strlen(stringa);i++)
	{
	stringa[i]=toupper(stringa[i]);	
	}

}
/***************************************/
int inserisci(char *regolazione,int k)
/***************************************/
/*
Inserisce nuovo nome di task di regolaz.in var_regolazione[][]
*/
{

int risultato,x;
char *car;
/*
inserire controllo per verificare che la variabile non sia già 
stata inserita
*/

strcpy(&var_regolazione[k][0],regolazione);

car=strchr(var_regolazione[k],'\n');/*elimina \n*/
strcpy(car,"");
maiuscolo(&var_regolazione[k][0]);

risultato=1;

return(risultato);
}
/**********************************/
char *converti_nome(char *stringa)
/**********************************/
/*
Converte il nome di un task di regolazione in un nuovo nome
*/
{

int i;
char *car;

for(i=0;i<num_task_regolazione;i++)
	{
/*
Se trovi un task di regolazione convertilo con il
nuovo nome
*/	
	if(car=strstr(stringa,&var_regolazione[i][0]))
			
		{
		strcpy(stringa,car);
		
		return(&var_regolazione[i][0]);
		}
	}	

return(NULL);

}
/*************************************/
void	analizza(char *stringa,char *nome_task)
/*************************************/
/*
Procedura che analizza una linea e aggiorna i nomi dei task e delle var.
*/
{

char stringhe[4][LUNG_VAR];/* stringhe per lettura task e variabili*/
char due_caratteri[2];/*2 caratteri che vengono aggiunti al nome della var*/
char *car;
register int i,t,k;/*var di conteggio*/

/*
inizializza stringhe
*/
for(i=0;i<4;i++)
	strcpy(stringhe[i],"");
sscanf(stringa,"%s %s %s %[^\n]%s",stringhe[0],stringhe[1],stringhe[2],stringhe[3]);

/*
Se il task è di regolazione cambia la var sulla 1a colonna
*/

if(nome_task!=NULL)
	{
	due_caratteri[0]=*nome_task;
	due_caratteri[1]=*(nome_task+1);

	if(strlen(stringhe[0])>6)
		{
		printf("Variabili già convertite\n");
		exit(1);		
		}
	strcat(stringhe[0],due_caratteri);
	
	}


for(i=0;i<num_task_regolazione;i++)
	{	
	
/*
Se il task è di regolazione cambia nome variabile
*/	
	if((strstr(stringhe[1],&var_regolazione[i][0]))!=NULL)
		{
		strcpy(stringhe[1],var_regolazione[i]);
		due_caratteri[0]=stringhe[1][0];
		due_caratteri[1]=stringhe[1][1];
/*
controllo per verificare se le var sono già state modificate
*/		
		if(strlen(stringhe[2])>6)/*modifica*/
			{
			printf("Variabile già modificata\n");
			exit(1);
			}
		strcat(stringhe[2],due_caratteri);
		}
	}
/*
concatena le varie stringhe
*/

k=11-strlen(stringhe[0]); /*ogni colonna=8car+3 spazi*/
for(t=0;t<k;t++)
		{
		strcat(stringhe[0]," ");/*spazi necessari*/
		}
			
for(i=1;i<4;i++)
	{
	k=11-strlen(stringhe[i]);
	for(t=0;t<k;t++)
		strcat(stringhe[i]," "); /*spazi necessari*/
	strcat(stringhe[0],stringhe[i]);	
		
	}
	
strcpy(stringa,stringhe[0]); /*copia in stringa stringhe concatenate */	
strcat(stringa,"\n");
	

}/*end analizza */


/*********************************************/
int converti(FILE *fp,FILE *fp1,FILE *fp2)
/*********************************************/
/*
procedura per convertire task e variabili associate
*/
{
int i,k,t;	/*var di conteggio */
int next_task;  /*prossima stringa letta contiene solo 1 task_name */
char *task_name;		/*puntat alla stringa di un tak di regolaz.*/
char linea[DIM],*car;
char elenco_path[DIM][LUNG_VAR];/* elenco dei path */

i=0;	/*azzera contatore campi*/
k=0;	/*azzera contatore variabili*/
t=0;	/*azzera contatore path*/

/*
Leggi il file con i path e copialo sul nuovo file
*/

while ((fgets(linea,DIM-1,fp1))!=NULL) 
	{
	
	if(i==3)	/*Se 3a linea di *** */
		{
		strcpy(&elenco_path[t++][0],linea);		
 		if(car=strstr(linea,"r_"))	/*r_ found */
			{
			car+=2;
			if(!inserisci(car,k++))
				{
				printf("Impossibile inserire nomi var\n");
				exit(1);
				} /*end if inserisci ko*/
			}/*end if trova _r*/
		
		}/*end if(i==3)*/
	
	num_task_regolazione=k;
	
	if(num_task_regolazione>200)/*controllo sul # di task*/
		{
		printf("N° di task troppo grande: programma terminato\n");
		exit(1);
		}
		
	if (*linea=='*')
		i++;
	if(i<=3)
		fputs(linea,fp2);/*copia linea su nuovo file*/
	}
	
/***************************************************/	
i=0;
k=0;
next_task=0;
/*
Legge il file sorgente:
1) dopo 4*** concatena ad OS host guest i nuovi path dei task di regolaz.
2) cambia i nomi dei task e delle variabili	
*/
while ((fgets(linea,DIM-1,fp))!=NULL) 
	{

/*
Concatena ad OS host guest i path corrispondenti
*/	
	if(i==4)
		{
		if(car=strstr(linea,"OS host guest "))
			{
			
			car+=strlen("OS host guest ");
			strcpy(car,&elenco_path[k++][0]);
			}
		}

/*
Cambia nomi dei task di regolazione e delle relative variabili di processo
*/

	if(i>=6)
		{
	
		if(next_task) /*next string:task_name */
			{
			task_name=converti_nome(linea);
			next_task=0;
			}
		
			else 
				{
		/*	printf("Linea %s -- nome task %s\n",linea,task_name);
			getc(stdin);
			exit(1);*/
				if(*linea!='*')
					analizza(linea,task_name);	
				}
		}/*end if(i==6)*/

/*
Se leggi *** allora la prossima linea conterrà un task
*/	
	if(*linea=='*')
		{
		next_task=1;
		i++;	
		}
		
		
	if(i>=4)/*da porre>=4*/
		{
		fputs(linea,fp2); /*Scrivi sul file modificato */
		}
	
	}

}/*end converti */




