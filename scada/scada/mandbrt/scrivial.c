/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
        la function scriviall scrive il nome della misura
        che e' limite di allarme ed il suo valore
        oppure il valore dell'allarme se e' fisso

        allarme float informazioni sull'allarme da esaminare
        riga  int   riga su cui posizionarsi
        colonna int colonna in cui posizionarsi
        scrnome  int =0 scrivere anche il nome della
                           misura che e' soglia di allarme

        tutti gli argomenti sono in input
*/
#include <stdio.h>
#include <stdlib.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "dconf.inc"
#include "ansiscr.h"
#include "ctasti.inc"

extern DB_HEADER h_db;
union all { float f;
            unsigned char  c[4];
            short s[2];};

scrivi_all(allarme,riga,colonna,scrnome)
union all allarme;
short riga,colonna,scrnome ;
{
#define lun_nome 10
char nome[lun_nome+1] ;
long disp;
char chval[50];	  /* stringa contenente la conversione in char del valore */
short tot,ier ;

FILE *fp ;
float valore ;
if(allarme.c[0]==254) return(0);  /* non c'e' allarme */
if(allarme.c[0]==255)             /* allarme variabile */
	{
        switch(allarme.c[1])    /*      selezione del file su cui */
        {                       /*      leggere il nome del punto */
        case g1tipaa :
                valore=dbaav[allarme.s[1]];
                disp=(long)allarme.s[1]*rec_fdaa+of_fdaa;       break;
        case g1tipas :
                valore=dbasv[allarme.s[1]];
                disp=(long)allarme.s[1]*rec_fdaa+of_fdas;       break;
        case g1tipac:
                valore=dbacv[allarme.s[1]];
                disp=(long)allarme.s[1]*rec_fdac+of_fdac;       break;
        case g1tipad :
                valore=dbadv[allarme.s[1]];
                disp=(long)allarme.s[1]*rec_fdad+of_fdad;       break;
        }
        if(scrnome)             /* non e' ancora noto  */
        {                       /* il nome della misura */
		  rbyte(fileno(fpp[fdde]),(short*)nome,disp,lun_nome );
        nome[lun_nome]=0 ;
		  scrxy(riga,colonna);
		  printf("%s",nome);
        }
}
else valore=allarme.f ;         /* allarme valore floating */
/*
        scrivo il valore floating dell'allarme
*/
colonna=colonna+11;
scrxy(riga,colonna);
printf("%#8.2f",valore);
return(0);
}


				 
