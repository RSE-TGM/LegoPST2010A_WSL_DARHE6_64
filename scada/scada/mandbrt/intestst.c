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
        la function intestst visualizza le caratteristiche
        dei punti stringa
        sigla descrizione          
        indice int in n. della misura in esame
        point  short in puntatore in data base della misura
*/
#include <stdio.h>

#include "ansiscr.h"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "dconf.inc"
#include "ansiscr.h"
#include "ctasti.inc"

extern DB_HEADER h_db;

#include "tabelle.inc"
#define lun_nome 10
#define lun_descr 24

intestst(indice,point,ext)
short ext ;
short indice;
short  point ;
{
short riga_corr;
long tot ;
short ier ;
FILE *fp;
char nome[lun_nome+1], descr[lun_descr+1];
/*
        leggo nome descrizione 
*/
tot = of_fdst+(long)point*rec_fdst;
fp=fpp[fdde];
rbyte(fileno(fp),(short *)nome,(long)tot,lun_nome);      
rbyte(fileno(fp),(short *)descr,(long)(tot+lun_nome),lun_descr);
nome[lun_nome]=0;
descr[lun_descr]=0;

riga_corr=indice*num_righe+1 ;
scrxy(riga_corr,nom_pos);
printf("%s",nome);
scrxy(riga_corr,descr_pos);
printf("%s",descr);
scrxy(riga_corr,tipo_pos);
printf("STRINGA    ");
}


