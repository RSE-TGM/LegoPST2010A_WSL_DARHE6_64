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
/*-> printalt

   La funzione prepara le stringhe allarmi per libro giornale
   nel formato caratteristico per le linee telefoniche 

   Parametri

   mess     *STALT
            se il tempo ha valore -1 si tratta di un allarme 
            normale

   Ritorno

   nessuno

   3 Dicembre 1992
   15 Giugno 1995
      Inserimento, per gestione stampanti virtuali libro giornale,
      inserimento nel messaggio da inviare per Invia, l'indicazione
      della zona di impianto del punto
*/

#include <osf1.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "print.inc"
#include "tipal.inc"	  
#include "mesqueue.h"

extern long  off_f[] ;     /* definiti nel main mpscs */
extern short nbyte[] ;     /* come sopra */

printalt (al)
S_STALLT *al ;
{
short ier ;
short atipo ;
short stato ;
 
typedef struct s_foral  {
			 HEA_STA hea;
          char gior[c_data] ;
          char sep_1;
          char mese[c_data];
          char sep_2;
          char anno[c_data] ;
          char blank_2 ;
          char ora[c_data];
          char sep_3 ;
          char min[c_data];
          char sep_4;
          char sec[c_data];
          char blank_3[3];
          char dd[c_data];
          char bb_0;
          char mes[c_data];
          char bb_1;
          char hh[c_data];
          char bb_2;
          char mm[c_data];
          char bb_3;
          char ss[c_data];
          short bb_5;
          char nome[SCD_SIGLA];
          char blank_4;
          char desc[SCD_DESCRIZIONE_LBG];
          char blank_5 ;
          char tipo[c_tipo];
          char blank_6;
          char st_prec[c_stp] ;
          char blank_7;
          char st_att[c_sta];
          char blank_8;
          char val[c_val] ;
          short  new ;
          char eos ;
		    char even;
     } S_FORALT ;
S_FORALT  stam ;		  /* struttura contenente il formato di stampa
					     normale per gli allarmi							*/
S_PPAL  *nal ;

char desc[rec_fdda] ;           /* dimens. come il piu' */
                                /* grande dei record descrittori */
short i,l ;
long tot;
char *p1 ;

stam.hea.lung=sizeof(S_FORALT);
memset((char*)&stam.gior,' ',sizeof(S_FORALT)-sizeof(HEASCA));
stam.even=0;						// per rendere pari il messaggio
/*
        inserisco ora giorno mese anno minuti e secondi
        sono i medesimi per tutti gli allarmi arrivati
*/
decnum(stam.gior,2,-1,al->m.gior,0.) ;					
decnum(stam.mese,2,-1,al->m.mese,0.) ;
decnum(stam.anno,2,-1,al->m.anno,0.);
decnum(stam.ora ,2,-1,al->m.ora,0. ) ;
decnum(stam.min ,2,-1,al->m.min,0. ) ;
decnum(stam.sec ,2,-1,al->m.sec,0.);
if(al->t.dd!=-1)                 // ora rilevazione dato
{
   decnum(stam.mes,2,-1,al->t.mese,0.) ;					
   stam.bb_0='-';
   decnum(stam.dd,2,-1,al->t.dd,0.) ;					
   decnum(stam.hh,2,-1,al->t.hh,0.) ;
   stam.bb_2=':';
   decnum(stam.mm,2,-1,al->t.mm,0.) ;
   stam.bb_3=':';
   decnum(stam.ss,2,-1,al->t.ss,0.);
}
stam.sep_1='-';
stam.sep_2='-' ;
stam.sep_3=':' ;
stam.sep_4=':' ;
stam.new=0x0D0A ;
stam.eos=0x0D0A ;              /* fine riga    */

nal=&al->m.al ;
/*
        leggo il record dal file descrittore
*/
tot=off_f[nal->ext]+(long)nbyte[nal->ext]*(long)nal->punt;
rbyte(fileno(fpp[fdde]),desc,tot,nbyte[nal->ext]);
stam.hea.szvir=cunita(nal->punt, nal->ext);
/*
        copio nome punto descrizione nel buffer per la stampa
        e codifica ascii del tipo di allarme
*/
strncpy(stam.nome,desc,SCD_SIGLA) ;
strncpy(stam.desc,&desc[SCD_SIGLA],SCD_DESCRIZIONE_LBG);
if(nal->ertr & 0x80)
{	atipo=1;   /* emissione */
	stato=nal->satt & 0x7F ;}
else
{	atipo=0;   /* rientro */
   stato=nal->sprec ;}
/*
        inserisco tipo di allarme
*/
memcpy(stam.tipo,stringhe[stato+atipo*max_st],c_tipo) ;
/*
        inserisco le informazioni specifiche per ogni
        tipo di punto
*/
switch (nal->ext)
{
    case g1tipaa:    /*  an acq */
    case g1tipas :   /*  an calc st */
    case g1tipac :   /*  an calc non st */
    case g1tipad :   /*  an di diagnostica*/
    case g1tipao :   /*  an di uscita */
/*
        inserisco unita' di misura soglia di allarme e valore
*/
         strncpy(stam.st_prec,&desc[SCD_SIGLA+SCD_DESCRIZIONE],c_stp) ;
         if(nal->vrif.c[0]  != 255)
                        decnum(stam.st_att,10,4,0,nal->vrif.f) ;
         if(nal->vatt.c[0]  != 255)
                        decnum(stam.val,10,4,0,(float)min(nal->vatt.f,
                                        99999.9999)) ;
         stam.blank_8=0x20 ;
         break;
    case g1tipda:   /*  dig. acq */
    case g1tipdc:  /*  dig  calc */
    case g1tipds :  /* dig cal n s */
    case g1tipdd :  /* dig diagn  */
    case g1tipdo:   /* dig uscita */
         if(nal->vrif.c[0] != 255)    /* stato allarme */
         {
                atipo=nal->vrif.c[0] ;
                strncpy(stam.st_prec,&desc[SCD_SIGLA+SCD_DESCRIZIONE+atipo
                                *c_stp],c_stp) ;
          }
         break ;
    case g1tipor :          /* organi          */
        if(nal->vrif.c[0] != 255)
        {
                tot=nbyte[0]*nal->vrif.c[0];
                strncpy(stam.st_prec,&stat_diz[tot],lun_stato) ;
         }
         if(nal->vatt.c[0] != 255)
         {
                tot=nbyte[0]*nal->vatt.c[0] ;
                strncpy(stam.st_att, &stat_diz[tot],lun_stato) ;
          }
          break ;
    case g1tipst:
          strncpy(stam.st_prec,nal->vrif.c,g0lunst-1) ;
	       break;
 }
/*
        chiamo la routine invia per la scelta della stampante
        virtuale da utilizzare
*/
invia(tpr_allarme,&stam) ;

return(0) ;
}
