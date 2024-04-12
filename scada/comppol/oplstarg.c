/*
   modulo oplstarg.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)oplstarg.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <osf1.h>
#include <stdio.h>
#include <string.h>

#include "tipi.h"
#include "chascii.inc"

extern char linea_cor[];

/*********************************************************************
*								                                             *
*			Procedura oplstarg 			                                 *
*								                                             *
*								                                             *
*  MOVG    c. o. = 112                                               *
*  ROTG    c. o. = 113                                               *
*  SCALG   c. o. = 114                                               *
*  STLENG  c. o. = 131                                               *
*  STNCAT  c. o. = 132                                               *
*  SETWIND c. o. = 133                                               *
*								                                             *
*********************************************************************/

oplstarg(codice)

int codice;

{

char nomevar[LUNG_VAR+1];
int M,i,ciclo=0,tipo[10],dim[10],ind[10];
int tipoamm[10];
int sem,flgciclo;
int numoper;
int j;

tipo[0]=-2;

switch (codice) {

	case 112 : /* MOVG */

		numoper = 3;
		tipoamm[0] = 4;
		tipoamm[1] = 4;
		tipoamm[2] = 4;
		M=5;

	break;

	case 113 : /* ROTG */

		numoper = 4;
		tipoamm[0] = 4;
		tipoamm[1] = 4;
		tipoamm[2] = 3;
		tipoamm[3] = 4;
		M=5;

	break;

	case 114 : /* SCALG */

		numoper = 4;
		tipoamm[0] = 4;
		tipoamm[1] = 4;
		tipoamm[2] = 3;
		tipoamm[3] = 4;
		M=6;

	break;

	case 130 : /* STLENG */

		numoper = 2;
		tipoamm[0] = 7;
		tipoamm[1] = 4;
		M=7;

	break;

	case 131 : /* STNCAT */

		numoper = 3;
		tipoamm[0] = 7;
		tipoamm[1] = 4;
		tipoamm[2] = 7;
		M=7;

	break;

	case 132 : /* SETWIND () */

		numoper = 4;
		tipoamm[0] = 4;
		tipoamm[1] = 4;
		tipoamm[2] = 4;
		tipoamm[3] = 4;
		M=8;
		if(linea_cor[M]!='(') stampa_err(6,0,"");
		else linea_cor[M]=' ';
		if(linea_cor[strlen(linea_cor)-1]!=')') stampa_err(6,0,"");
		else linea_cor[strlen(linea_cor)-1]=0;
		M++;
	break;

}

	ciclo = 0;
	flgciclo = 0;

	while ( flgciclo == 0 )  	// ciclo di lettura argomenti

		{

		sem = getnovar(nomevar,&M);

		if( sem==-1 ) { 

			if( (ciclo <= (numoper-1)) ) { 

				/* numero caratteri letti nullo */

				flgciclo=1;
				tipo[0]=-2;

				stampa_err(6,1,par_chiav[codice]);
				stampa_err(11,1,par_chiav[codice]);

				}

			else {

				if ( linea_cor[M-1] == VIRGOLA ) {

					flgciclo=1;

					stampa_err(6,1,par_chiav[codice]);

					}

				else

					{

					/* termino il ciclo di scansione della lista */

					flgciclo=1;

					}
				}
			}

		else  			 // lettura corretta
			{

			if ( ciclo <= (numoper-1) ) {

				tipo[ciclo]=cerca(testa,nomevar,&dim[ciclo],&ind[ciclo]);

				if(tipo[ciclo]>=16)
					cnome(nomevar,&tipo[ciclo],&M);

				controlla(nomevar,&M,tipo[ciclo]);
				ciclo++;
				M++;

				}

			else {

				/* Superato numero di argomenti previsti */

					if ( strlen(nomevar) != 0 ) {

						flgciclo = 1;
						tipo[0]=-2;

						stampa_err(6,1,par_chiav[codice]);
						stampa_err(11,1,par_chiav[codice]);

					}

					else {

						flgciclo = 1;

					}

				}

	 		}
		}

	M=1;

	for ( j = 0; j < numoper; j++ ) {

		if( tipo[j] != tipoamm[j] ) {

			M = 0;

		}

	}

	if(M)
		intfile(codice);
	else
		if(tipo[0]!=-2)
			stampa_err(12,1,par_chiav[codice]);

}

