/*
   modulo opstring.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)opstring.c	1.1
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

extern char linea_cor[];

/*********************************************************************
*								                                             *
*			Procedura opstring 			                                 *
*								                                             *
*								                                             *
*  STLENG  c. o. = 131                                               *
*  STNCAT  c. o. = 132                                               *
*								                                             *
*********************************************************************/

opstring(codice)
int codice;
{
char nomevar[LUNG_VAR+1];
int M,i,ciclo=0,tipo[3],dim[3],ind[3];
int sem,flgciclo;
int cicloleggi;

tipo[0]=-2;

M=7;

/*
	Test per determinare il numero di operandi
*/

if( codice == 131 ) {

	/* Operazione con tre operandi */

	ciclo = 0;
	flgciclo = 0;
	cicloleggi = ciclo;

	while ( flgciclo == 0 )  	// ciclo di lettura argomenti

		{

		sem=legginvar(nomevar,codice,&M,cicloleggi);

		if(sem==-1) 	 // se errore in lettura forza l'uscita dal ciclo
			{
			flgciclo=1;
			tipo[0]=-2;
			}

		else  			 // lettura corretta
			{

			if ( ciclo <= 2 ) {

				tipo[ciclo]=cerca(testa,nomevar,&dim[ciclo],&ind[ciclo]);

				if(tipo[ciclo]>=16)
					cnome(nomevar,&tipo[ciclo],&M);

				controlla(nomevar,&M,tipo[ciclo]);
				ciclo++;
				M++;

				if (ciclo == 3 ) {

					cicloleggi = 2;

					}

				else {

					cicloleggi = ciclo;

					}

				}

			else {

				/* Superato numero di argomenti previsti */

					if ( strlen(nomevar) != 0 ) {

						flgciclo = 1;

						stampa_err(11,1,par_chiav[codice]);

					}

					else {

						flgciclo = 1;

					}

				}

	 		}
		}

	M=0;

	if (codice == 131) {

		/* Operazioni su stringhe con tre argomenti : STNCAT */

		if( (tipo[0]==7) &&
	   	 (tipo[1]==4) &&
	   	 (tipo[2]==7) )
				M=1;

	}

	if(M)
		intfile(codice);
	else
		if(tipo[0]!=-2)
			stampa_err(12,1,par_chiav[codice]);

}  /* fine caso di operazioni con tre argomenti */

else {

	/* caso di operazione con due operandi */

	ciclo = 0;
	flgciclo = 0;
	cicloleggi = ciclo;

	while ( flgciclo == 0 )  {

		sem=legginvar(nomevar,codice,&M,cicloleggi+1);

		if(sem==-1)  {
			flgciclo=1;
			tipo[0]=-2;
		}

		else  {

			if ( ciclo <= 1 ) {

				tipo[ciclo]=cerca(testa,nomevar,&dim[ciclo],&ind[ciclo]);

				if(tipo[ciclo]>=16)
					cnome(nomevar,&tipo[ciclo],&M);

				controlla(nomevar,&M,tipo[ciclo]);
				ciclo++;
				M++;

				if (ciclo == 2 ) {

					cicloleggi = 1;

					}

				else {

					cicloleggi = ciclo;

					}

				}

			else {

				/* Superato numero di argomenti previsti */

					if ( strlen(nomevar) != 0 ) {

						flgciclo = 1;

						stampa_err(11,1,par_chiav[codice]);

					}

					else {

						flgciclo = 1;

					}

				}

	 		}
		}

	M=0;

	if ( codice == 130 ) {

		if((tipo[0]==7 ) &&
		   (tipo[1]==4 ))
			M=1;
	}

	if(M)
		intfile(codice);
	else
		if(tipo[0]!=-2)
			stampa_err(12,1,par_chiav[codice]);

	}  /* fine caso di operazioni con due argomenti */

}

