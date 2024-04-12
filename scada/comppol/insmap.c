/*
   modulo insmap.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)insmap.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <osf1.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

#include "chascii.inc"

#include "tipi.h"

#include "define.inc"

/*********************************************************************
*          							                                       *
*			Procedura insmap                                            *
*          							                                       *
* La procedura serve per inserire nel file .map i dati richie=       *
* sti. Per le specifiche di ogni campo vedere allegato sul file .map *
*          							                                       *
*********************************************************************/

extern char nome_var_map[];

extern int aggind[];

extern int fdmap;

extern int stop_link;


insmap(albero,ind,numero,s)

struct variabili *albero;
int ind;       // indice tipo di variabile
int *numero;   // contatore di inserimento nel file codice.map
int s;         // switch di selezione funzione

{

int i,dim;
int icodlink;

char bl=' ';
float x;

if(albero!=NULL)  {

/* Struttura ad albero delle variabili non vuota */

	if(ind==(albero->tipo & 15) &&
	(int)(albero->codicevar) == ( (s & 3) + 1 ) ) {

	/* Variabile del tipo specificato dal parametro ind e in funzione 
	   dello switch s appartenente alle seguenti classi :

		s = 0 variabili di LINK
		s = 1 variabili di DEFINE 
		s = 2 costanti di tipo DATA
		s = 3 costanti introdotte dal compilatore (istruzione CASE) */

		sbianca(nome_var_map,LUNG_VAR_LINK_DBS);

		if(albero->indirizzo & 0x8000)		// variabile locale all'oggetto
		{
			
		}
		else if(s==0 || s==1) {

			/* variabili tipo LINK oppure tipo DEFINE */

			(*numero)++;   /* incremento il contatore */

			if(s==0 && stop_link==0)  {

				/* LINK con le sigle del data base di sistema */

				sprintf(nome_var_map,"%s",albero->valcost);

				/* completo con BLANK la sigla del data base di sistema */

				for(i=0;i<LUNG_VAR_LINK_DBS;i++)
					if(nome_var_map[i]==0x00)
						nome_var_map[i]=BLANK;
				nome_var_map[i]=0x00;

				/* scrittura sul file CODICE.MAP */

				write(fdmap,nome_var_map,LUNG_VAR_LINK_DBS);

			}

			else	  {

				sprintf(nome_var_map,"%s",albero->nome);

				for(i=0;i<EF_LUNGVAR-1;i++)
					if(nome_var_map[i]==0x00)
						nome_var_map[i]=BLANK;
				nome_var_map[i]=0x00;

				write(fdmap,nome_var_map,EF_LUNGVAR-1);

			}

			icodlink = (int) (albero->codicelk);

			if ( stop_link == 0 ) {

				write(fdmap,&icodlink,2);

				}

			else {

				write(fdmap,&ind,2);

			}

			i=albero->indirizzo;
			i+=2048*aggind[ind];
			write(fdmap,&i,2);

		}

		else {

			if((s==6 && albero->flag==1) ||
	 		   ((s==3 || s==2) && albero->flag==0)) {
				(*numero)++;
				sprintf(nome_var_map,"%s",albero->nome);
				for(i=0;i<EF_LUNGVAR-1;i++)
					if(nome_var_map[i]==0x00)
						nome_var_map[i]=BLANK;
			nome_var_map[i]=0x00;
				write(fdmap,nome_var_map,EF_LUNGVAR-1);
				if(ind==7)
					write(fdmap,&albero->tipo,2);
				else
					write(fdmap,&ind,2);
			i=albero->indirizzo;
			i+=2048*aggind[ind];
			write(fdmap,&i,2);
				switch(ind) {
				case 3 :
					x=atof(albero->valcost);
					write(fdmap,&x,4);
				break;
				case 4 :
					i=atoi(albero->valcost);
					write(fdmap,&i,2);
				break;
				case 5 :
					write(fdmap,albero->valcost,1);
					break;
				case 9 :
				case 10 :
				case 11:
				case 12:
				case 14:
				case 15:
					dim=strlen(albero->valcost);
 					if(dim>LUNG_VAR_LINK_DBS)
						dim=LUNG_VAR_LINK_DBS;
					write(fdmap,albero->valcost,dim);
					for(i=dim;i<LUNG_VAR_LINK_DBS;i++)
						write(fdmap,&bl,1);
				break;
				default :
					dim=(albero->tipo-ind)/16;
					write(fdmap,albero->valcost,dim);
					break;
				}
			}
	 	}   /* fine else */

	}

	/* Chiamata ricorsiva di inserimento nel file .map */

	insmap(albero->left,ind,numero,s);
	insmap(albero->right,ind,numero,s);

}

}


