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
/*-> printar

        la function printar prepara le stringhe degli allarmi
        di tipo generico per una stampa di tutta una pagina
		  allarmi

   9 Giugno 1992     Rel 1.0 Fc.

   Inserita gestione per data base allarmi allocati dinamicamente.
   Corretta gestione rientri.

   15 Giugno 1995
   Inizializzazione campo szvir =-1 stampante default per tabulati
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "g1tipdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "print.inc"
#include "tipal.inc"	  

extern long  off_f[] ;     /* definiti nel main mpscs */
extern short nbyte[] ;     /* come sopra */

float vsoglia();
static union {
       S_FORAR stam ;		  /* struttura contenente il formato di stampa
			              			  normale per gli allarmi	*/
		 }	uar;

printar (nal)
S_STAR *nal ;
{
short ier ;
short tpr; 

char desc[rec_fdda] ;           /* dimens. come il piu' */
                                /* grande dei record descrittori */
short i,l ;
long tot;
char *p1 ;

tpr=tpr_archivio+(nal->peri*256);
uar.stam.hea.lung=sizeof(S_FORAR);
uar.stam.hea.szvir=-1;
/*
        inserisco ora giorno mese anno minuti e secondi
        sono i medesimi per tutti gli allarmi arrivati
*/
memset(&uar.stam.blank_1,' ',uar.stam.hea.lung-sizeof(HEA_STA));
uar.stam.new=0x0D0A ;
uar.stam.eos=0x0D0A ;                  /* fine riga    */
/*
	se il puntatore e' -1 si tratta di un messaggio fittizio
	per forzare l'intestazione
*/
if(nal->al.m.punt==-1) goto SEND;

   decnum((char*)&uar.stam.blank_1,3,-1,cunita(nal->al.m.punt,nal->al.m.ext));
   if(nal->flag!=mstar_a) memset((char*)&uar.stam.blank_1,'*',1);

decnum(uar.stam.gior,2,-1,nal->al.giorno,0.) ;					
decnum(uar.stam.ora ,2,-1,nal->al.ore,0. ) ;
decnum(uar.stam.min ,2,-1,nal->al.minuti,0. ) ;
decnum(uar.stam.sec ,2,-1,nal->al.secondi,0. ) ;
uar.stam.sep_1=' ';
uar.stam.sep_2='-' ;
uar.stam.sep_3='-' ;
/*
        leggo il record dal file descrittore
*/
tot=off_f[nal->al.m.ext]+(long)nbyte[nal->al.m.ext]*(long)nal->al.m.punt;
rbyte(fileno(fpp[fdde]),(short *)desc,tot,nbyte[nal->al.m.ext]);
/*
        copio nome punto descrizione nel buffer per la stampa
        e codifica ascii del tipo di allarme
*/
strncpy(uar.stam.nome,desc,SCD_SIGLA) ;
strncpy(uar.stam.desc,&desc[SCD_SIGLA],SCD_DESCRIZIONE_LBG);
/*
        inserisco tipo di allarme
*/
/*
   elimino eventuale bit che segnala allarme da posto periferico
*/
   nal->al.m.satt=nal->al.m.satt & 0x7F;
if(nal->al.m.ertr & 0x80)
   strncpy(uar.stam.tipo,stringhe[nal->al.m.satt+max_st],c_tipo) ;
else
   strncpy(uar.stam.tipo,stringhe[nal->al.m.sprec+max_st],c_tipo) ;

/*
        inserisco le informazioni specifiche per ogni
        tipo di punto
*/
switch (nal->al.m.ext)
{
    case g1tipaa:    /*  an acq */
    case g1tipas :   /*  an calc st */
    case g1tipac :   /*  an calc non st */
    case g1tipad :   /*  an di diagnostica*/
/*
        inserisco unita' di misura soglia di allarme e valore
*/
         strncpy(uar.stam.st_prec,&desc[SCD_SIGLA+SCD_DESCRIZIONE],c_stp) ;
         if(nal->al.m.sogl1  != 255)
                decnum(uar.stam.st_att,10,4,0,
                vsoglia(nal->al.m.punt,nal->al.m.ext,nal->al.m.sogl1)) ;
         break;
    case g1tipda:   /*  dig. acq */
    case g1tipdc:  /*  dig  calc */
    case g1tipds :  /* dig cal n s */
    case g1tipdd :  /* dig diagn  */
         if(nal->al.m.sogl1  != 255)
            strncpy(uar.stam.st_prec,
               &desc[SCD_SIGLA+SCD_DESCRIZIONE+c_stp*nal->al.m.sogl1],c_stp) ;
         break ;
    case g1tipor :          /* organi          */
         tot=nbyte[0]*nal->al.m.sogl1;
         strncpy(uar.stam.st_prec,&stat_diz[tot],lun_stato) ;
         tot=nbyte[0]*nal->al.m.sogl2 ;
         strncpy(uar.stam.st_att, &stat_diz[tot],lun_stato) ;
         break ;
    default:
	       return(0);
 }
SEND:
/*
        accodo la stringa da stampare al task gestore della 546
        in base al numero di periferica
*/
invia(tpr ,&uar.stam) ;

return(0);
}

