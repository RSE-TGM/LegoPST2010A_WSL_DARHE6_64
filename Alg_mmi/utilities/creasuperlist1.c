/*

   modulo creasuperlist1.c
   tipo 
   release 1.5
   data 7/23/96
   reserved @(#)creasuperlist1.c	1.5
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)creasuperlist1.c	1.1\t1/8/96";
/*
        Fine sezione per SCCS
*/
/*           

 * sono contenute tutte le routine necessarie per modpag.c e
 * modallpag.c
 */



#include<stdio.h>
#include<string.h>

#define DIM 2000
#define DIM_BUF 1000

extern FILE *fp,fp1;
/*
 crealistone :
 		legge dai file .list e riscrive ogni campo sul listone
*/
/************************************************************/
int crea_listone(void)
/************************************************************/
/*
Funzione che esamina il contenuto della prima linea di ogni file *.list
estrae i nomi delle var da considerare 
La seconda parte esamina tutte le linee del file e riscrive l' output corretto
su superlista.list
*/
{
char linea[DIM],output[DIM],*car,*car1;
char colonna[DIM_BUF],stringa[DIM_BUF];
char *tmppag="filetmp";
register int i;
int n_var;

char *nome_var[100];
char *p;

/*
Leggi prima linea file.list da elaborare e conta quante colonne var ci sono
memorizzandone i nomi
*/
if(fgets(linea,DIM-1,fp))	/*inserisce in linea 1a linea*/
	{
	sscanf(linea,"%s",colonna);	/*leggi 1a colonna*/
	car=colonna;
	
	car++;				/*vai oltre 1a @*/
	while(*car!='@')
		{
		car++;
		}
		car++;
		
	if(strcmp(car,"TITLE"))	/*controlla che prima colonna=TITLE*/
		return(3);
	car=linea;
	n_var=0;
	while(*car!=10)	/*Scorri la linea */
		{
		while((*car==' ')||(*car==9))
			car++;
		car+=strlen(colonna);
		
		while((*car==' ')||(*car==9))
			car++;
		
		if(*car!=10)
			{
			sscanf(car,"%s",colonna);
			car1=colonna;
			car1++;				/*vai oltre 1a @*/
			while(*car1!='#')
				{
				car1++;
				}
				car1++;
			if((nome_var[n_var]=(char *)malloc(sizeof(strlen(car1)+1)))==NULL)
				{
				return(4);
				}
			strcpy(nome_var[n_var],car1);	
			n_var+=1;
			}/*end if !nwl*/
		}
	
		
/* A questo punto ho i nomi delle variabili*/	
				
	}
else
	{
	return(3);/*errore in input*/
	}

/*
2a PARTE: 
Legge tutte le linee del file 
*/
		
while ((fgets(linea,DIM-1,fp))!=NULL) {

	car=linea;
	strcpy(colonna,"");
	sscanf(car,"%s",colonna);
	strcpy(stringa,colonna);	/*salva in stringa identificatore linea*/
	
	/*debug*/
	
	if(strlen(colonna)==0)
		{
		printf("ATTENZIONE: trovata colonna vuota o con caratt. non validi\n");
		getc(stdin);
		}
		
	for(i=0;i<n_var;i++)
		{
		car+=strlen(colonna);
		while((*car==' ')||(*car==9))
			car++;			/*inizio campo*/
			if(*car!=10)
				{
				sscanf(car,"%s",colonna); /*leggi una colonna*/
				
				if(nome_var[i][0]=='V')
					{
/*
pulisci colonna da '-'
*/					car1=colonna;
					car1++; /*ignora - valori neg.*/
					while(strlen(car1)!=0)
						{
						if(*car1=='-')
							*car1=' ';
						car1++;	
						}
/*
Costruisci output finale
*/
					strcpy(output,stringa);
					strcat(output,"$");
					strcat(output,&nome_var[i][2]);
					strcat(output,":    ");
					strcat(output,colonna);
					strcat(output,"\n");
					fputs(output,fp1);
					}
				}/*end if !nwl*/
		}/* end fori*/

	}/* end while */		

/*
Libera memoria allocata per nomi variabili da considerare 
*/
for(i=0;i<n_var;i++)
	free(nome_var[i]);

return(0);	/* Operazione conclusa positivamente */

}
/****************************************************************/

