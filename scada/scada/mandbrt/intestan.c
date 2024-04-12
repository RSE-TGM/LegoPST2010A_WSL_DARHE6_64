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
        la function intestan visualizza le caratteristiche
        dei punti analogici di qualsiasi tipo
        sigla descrizione unita' di misura valore
        soglie di allarme
        
        indice int in n. della misura in esame
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
#include "intestan.inc"

extern DB_HEADER h_db;

#define lun_nome 10
#define lun_descr 24
#define lun_umis  8

intestan(indice,point,ext)
short ext ;
short indice;
short  point ;
{
#define HI 0x0f	  		/* carattere ad alta intensit…	*/
#define N  0x07			/* carattere normale 				*/
#define REV 0x30			/* carattere in reverse				*/
short riga_corr;
long tot ;
short ier ;
FILE *fp;
union valin soglia1, soglia2, soglia3, soglia4 ;
char nome[lun_nome+1], descr[lun_descr+1],umis[lun_umis+1];
/*
        leggo nome descrizione unita' di misura
*/
switch (ext)
 {
        case g1tipaa:
                tot = of_fdaa+(long)point*rec_fdaa;
                soglia1=dbaaal[point].alto_sic;
                soglia2=dbaaal[point].bass_sic;
                soglia3=dbaaal[point].alto_con;
                soglia4=dbaaal[point].bass_con;
                break;
        case g1tipas:
                tot = of_fdas+(long)point*rec_fdas;
                soglia1=dbasal[point].alto_sic;
                soglia2=dbasal[point].bass_sic;
                soglia3=dbasal[point].alto_con;
                soglia4=dbasal[point].bass_con;
                break;
        case g1tipad:
                tot = of_fdad+(long)point*rec_fdad;
                soglia1=dbadal[point].alto_sic;
                soglia2=dbadal[point].bass_sic;
                soglia3=dbadal[point].alto_con;
                soglia4=dbadal[point].bass_con;
                break;
        case g1tipac:
                tot = of_fdac+(long)point*rec_fdac;
                soglia1=dbacal[point].alto_sic;
                soglia2=dbacal[point].bass_sic;
                soglia3=dbacal[point].alto_con;
                soglia4=dbacal[point].bass_con;
                break;
        case g1tipao:
                tot = of_fdao+(long)point*rec_fdao;
					 break;
 }
fp=fpp[fdde];
rbyte(fileno(fp),(short *)nome,(long)tot,lun_nome);      
rbyte(fileno(fp),(short *)descr,(long)(tot+lun_nome),lun_descr);
rbyte(fileno(fp),(short *)umis,(long)(tot+lun_nome+lun_descr),lun_umis);

nome[lun_nome]=0;
descr[lun_descr]=0;
umis[lun_umis]=0;

riga_corr=indice*num_righe+1 ;
scrxy(riga_corr,nom_pos);
printf("%s",nome);
scrxy(riga_corr,descr_pos);
printf("%s",descr);
scrxy(riga_corr,umis_pos);
printf("%s",umis);
scrxy(riga_corr,tipo_pos);
printf("%s",tipoan[ext-1]);
/*
        scrittura soglie di allarme
*/
if(ext != g1tipao)
{
	riga_corr=indice*num_righe+1+off_alls ;
	scrxy(riga_corr,sa_pos);
	printf("%s",sa_s);
	scrxy(riga_corr,sb_pos);
	printf("%s",sb_s);
	scrxy(riga_corr,ca_pos);
	printf("%s",ca_s);
	scrxy(riga_corr,cb_pos);
	printf("%s",cb_s);
/*
        se la soglia di allarme e' una misura la
        ne visualizzo la sigla
*/
 scrivi_all(soglia1,indice*num_righe+off_allv+1,sa_pos,1);
 scrivi_all(soglia2,indice*num_righe+off_allv+1,sb_pos,1);
 scrivi_all(soglia3,indice*num_righe+off_allv+1,ca_pos,1);
 scrivi_all(soglia4,indice*num_righe+off_allv+1,cb_pos,1);
}
}

