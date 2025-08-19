/**********************************************************************
*
*       C Source:               printal.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Fri Aug  7 12:27:58 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: printal.c-3 %  (%full_filespec: printal.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*-> printal

        la function printall prepara le stringhe degli allarmi
        di tipo generico (non sequenza di eventi)

   04 Luglio 1995
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

// Function declarations
void decnum(char *str, int width, int precision, short value, float fvalue);
int rbyte(int fd, short *buffer, int offset, int count);
short cunita(short point, char ext);
void invia(int printer, void *message);

void printal (al)
S_STALL *al ;
{
short ier ;
short atipo ;
short stato ;
char *pos_sep;
int  start_canc;
char app_desc[SCD_DESCRIZIONE_LBG+1];
 
S_FORAL stam ;		  /* struttura contenente il formato di stampa
					     normale per gli allarmi							*/
S_PPAL  *nal ;

char desc[rec_fdda] ;           /* dimens. come il piu' */
                                /* grande dei record descrittori */
short i,l,efflun ;
long tot;
char *p1 ;


stam.even     = 0;              // per rendere pari il messaggio
stam.hea.lung = sizeof(S_FORAL)-2;

/* inserisco ora giorno mese anno minuti e secondi sono i medesimi per */
/* tutti gli allarmi arrivati */

if(INGLESE)
   {
	decnum(stam.gior,2,-1,al->mese,0.) ;					
	decnum(stam.mese,2,-1,al->gior,0.) ;
   }
else
   {
	decnum(stam.gior,2,-1,al->gior,0.) ;					
	decnum(stam.mese,2,-1,al->mese,0.) ;
   }
decnum(stam.anno,2,-1,al->anno,0.);
decnum(stam.ora ,2,-1,al->ora,0. ) ;
decnum(stam.min ,2,-1,al->min,0. ) ;
decnum(stam.sec ,2,-1,al->sec,0.);
//#ifdef AC_SIMULATORE
// nel caso di simulatore, data sostituita da ora DOS==>diverso separatore
//   stam.sep_1=':' ;
//   stam.sep_2=':' ;
//#else
stam.sep_1='-';
stam.sep_2='-' ;
//#endif
stam.sep_3=':' ;
stam.sep_4=':' ;
stam.blank_1=0x20202020 ;
stam.blank_2=0x20202020 ;
stam.blank_3=0x20202020 ;
stam.blank_4=0x20202020 ;
stam.blank_5=0x20202020 ;
stam.blank_6=0x20202020 ;		
stam.blank_7=0x20202020 ;
stam.blank_8=0x20202020 ;
//stam.new=0x0D0A ;
//stam.eos=0x0D0A ;              /* fine riga    */

// Modifica richiesta da Stefanini (Fax 14/11/95)
stam.new=0x0A0D ;
stam.eos=(short)0x0A0D ;              /* fine riga    */



nal=&al->al ;

/* pulisco i campi variabili */

memset(stam.st_prec,' ',c_stp ) ;
memset(stam.st_att,' ',c_sta ) ;
memset(stam.val,' ',c_val ) ;

/* leggo il record dal file descrittore */

tot=off_f[nal->ext]+(long)nbyte[nal->ext]*(long)nal->punt;
rbyte(fileno(fpp[fdde]),(short *)desc,tot,nbyte[nal->ext]);
stam.hea.szvir=cunita(nal->punt, nal->ext);
/*
printf("printal DEBUG:\ndesc = %s\n",desc);
*/
/* copio nome punto descrizione nel buffer per la stampa e codifica ascii 
/* del tipo di allarme */

strncpy(stam.nome,desc,SCD_SIGLA) ;
strncpy(stam.desc,&desc[SCD_SIGLA],SCD_DESCRIZIONE_LBG);
/*
printf("printal DEBUG: nome = %s   desc = %s\n",
       stam.nome, stam.desc);
*/
/*
   Si ripulisce la descrizione dal separatore @#K@ in poi.
*/
strncpy(app_desc,stam.desc,SCD_DESCRIZIONE_LBG);
app_desc[SCD_DESCRIZIONE_LBG] = '\0';
pos_sep=strchr(app_desc,'@');
if(pos_sep != NULL) {
   start_canc = pos_sep - app_desc;
   for(i=start_canc; i< SCD_DESCRIZIONE_LBG; i++)
      stam.desc[i] = ' ';
}

if(nal->ertr & 0x80)
   {
   atipo=1;   /* emissione */
	stato=nal->satt ;
   }
else
   {
   atipo=0;   /* rientro */
   stato=nal->sprec ;
   }

/* inserisco tipo di allarme */

memcpy(stam.tipo,stringhe[stato+atipo*max_st],c_tipo) ;
/*
printf("printal DEBUG: tipo = %s\n",stam.tipo);
*/
/* inserisco le informazioni specifiche per ogni tipo di punto */

switch (nal->ext)
   {
   case g1tipaa:    /*  an acq */
   case g1tipas :   /*  an calc st */
   case g1tipac :   /*  an calc non st */
   case g1tipad :   /*  an di diagnostica*/
   case g1tipao :   /*  an di uscita */

/* inserisco unita' di misura soglia di allarme e valore */

        strncpy(stam.st_prec,&desc[SCD_SIGLA+SCD_DESCRIZIONE],c_stp) ;


        if(nal->vrif.c[0]  != 255)
                       decnum(stam.st_att,10,4,0,nal->vrif.f) ;
        if(nal->vatt.c[0]  != 255)
                       decnum(stam.val,10,4,0,(float)min(nal->vatt.f,
                                       99999.9999)) ;
        stam.blank_8=0x20202020 ;
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
/*
printf("printal DEBUG: st_prec = %s\n",stam.st_prec);
*/
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
        accodo la stringa da stampare al task gestore della 546
		  in base alla priorita' della stringa l'allarme puo'
		  essere accodato alla stampante allarme o alla stampante
		  tabulati
*/
if(!pri_all[stato]) 	invia(tpr_allarme,&stam) ;
else	invia(tpr_allarme_2,&stam) ;

return ;
}
