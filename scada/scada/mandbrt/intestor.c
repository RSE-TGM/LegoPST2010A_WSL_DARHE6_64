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
        la function intestor visualizza le caratteristiche
        dei punti organi
        sigla descrizione
        tipo dell'organo e descrizione del tipo di organo
        
        point  short in puntatore in data base della misura
*/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "tabelle.inc"
#include "dconf.inc"
#include "ansiscr.h"
#include "ctasti.inc"
#include "intestor.inc"

#define lun_nome 10
#define lun_descr 24
#define lun_tipo 10

extern DB_HEADER h_db;

intestor(indice,point)
short  point ;
short indice ;
{
#define REV 0x20			/* carattere in reverse				*/
short riga_corr;
long tot ;
short ier ;
FILE *fp;
char nome[lun_nome+1], descr[lun_descr+1],stipo[lun_tipo+1];
#define offset  4               /* bytes in cui inizia il nome */
                                /* nella scheda punto          */
/*
        leggo nome descrizione
*/
tot=of_fdor+(long)point*rec_fdor;

fp=fpp[fdde];
rbyte(fileno(fp),(short*)nome,(long)tot,lun_nome);      
rbyte(fileno(fp),(short*)descr,(long)(tot+lun_nome),lun_descr);
rbyte(fileno(fp),(short*)stipo,(long)(tot+lun_nome+lun_descr),lun_tipo);
nome[lun_nome]=0;
descr[lun_descr]=0;
stipo[lun_tipo]=0;

riga_corr=indice*num_righe+1 ;
scrxy(riga_corr,nom_pos);
printf("%s",nome);
scrxy(riga_corr,descr_pos);
printf("%s",descr);
scrxy(riga_corr,tipo_pos);
printf("%s",org);

/*
        scrittura tipo organo e descrizione tipo organo
*/
riga_corr=indice*num_righe+1+off_tipor ;
scrxy(riga_corr,tiporg_pos);
printf("%s",stipo);
}

