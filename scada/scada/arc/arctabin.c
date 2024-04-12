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
   arctabini.c

   La funzione arctabini prepara le intestazioni per la stampa
   dei tabulati di archivio

   Parametri

   p_des    PARCDES *      puntatore al descrittore dell'archivio
   mess     short          tipo dell'intestazione richiesta
   pagina   short          n. della pagine
   misini   short          n. misura iniziale
   mistot   short          n. totale misure da trattare
   str      char *         stringa di cui eseguire l'output in caso
                           di mistot=0

   Ritorno

   nessuno

   23 Marzo 1992     Rel. 1.0    Fc
*/

#include <osf1.h>   
#include <stdio.h>
#include <string.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "diagnoan.inc"
#include "arc.inc"
#include "print.inc"
#include "arctab.inc"
#include "switch.inc"

extern char *arc_number;
extern char *arc_stampato;
extern short nbyte[];
extern long off_f[];

arctabin(p_des,mess,pagina,misini,mistot,str)
PARCDES *p_des;
short mess, pagina, misini, mistot;
char *str;
{
short anno;
PUNTDBS *point;
short i;
long tot;

switch (mess)
{
/*
   richiesta inizializzazione buffer intestazione header
*/
case minit:
   memset(&intarc_1,' ',sizeof(INARC_1));
   memset(&intarc_2,' ',sizeof(INARC_2));
   intarc_1.hea.lung=sizeof(INARC_1);
   intarc_1.hea.szvir=-1;
   intarc_2.hea.lung=sizeof(INARC_2);
   intarc_2.hea.szvir=-1;
   if(dbadv[db_anno]>=2000) anno=dbadv[db_anno]-2000;
   else anno=dbadv[db_anno]-1900;
if (INGLESE)
{
   decnum(intarc_1.data,2,-1,(short)dbadv[db_mese],0.);
   intarc_1.data[2]='/';	
   decnum(&intarc_1.data[3],2,-1,(short)dbadv[db_giorno],0.);
}
else
{
   decnum(intarc_1.data,2,-1,(short)dbadv[db_giorno],0.);
   intarc_1.data[2]='/';	
   decnum(&intarc_1.data[3],2,-1,(short)dbadv[db_mese],0.);
}
   intarc_1.data[5]='/';	
   decnum(&intarc_1.data[6],2,-1,anno,0.);
   memcpy(intarc_1.page,"PAG.",4) ;
   intarc_1.new= 0x0D0A ;
   intarc_1.eos= 0x0D0A ;   
   memcpy(intarc_2.titolo,arc_number,11);
   decnum(intarc_2.indice,2,-1,p_des->hea.iarc,0.);
   memcpy(intarc_2.titolo_2,arc_stampato,14);
   decnum(intarc_2.ora,2,-1,(short)dbadv[db_ora],0.);
   intarc_2.ora[2]=':';	
   decnum(&intarc_2.ora[3],2,-1,(short)dbadv[db_minuti],0.);
   intarc_2.ora[5]=':';	
   decnum(&intarc_2.ora[6],2,-1,(short)dbadv[db_secondi],0.);
   intarc_2.new= 0x0D0A ;
   intarc_2.eos= 0 ;
   arcontrol.hea.lung=sizeof(arcontrol);
   arcontrol.hea.szvir=-1;
   rtag.hea.lung=sizeof(RIGTAG);
   rtag.hea.szvir=-1;
   rval.hea.lung=sizeof(RIGVAL);
   rval.hea.szvir=-1;
break;
/*
   richiesta lettura descrizioni misure inserite in archivio e
   stampa prima parte archivio
*/ 
case msigle:
	arcontrol.val=0x0C00;
   invia(tpr_tabulato,&arcontrol);
   arcontrol.val=0x0D0A;
	decnum(intarc_1.num,4,-1,pagina,0.);
	invia(tpr_tabulato,&intarc_1);
   if(mistot)
   {
   	invia(tpr_tabulato,&intarc_2);	 
   	invia(tpr_tabulato,&arcontrol);
      point=p_des->mis+misini;
   	memset(rtag.blank1,' ',sizeof(RIGTAG)-sizeof(HEA_STA));
      for(i=0;i<mistot;i++,point++)
   	{  
         if((misini+i)==p_des->hea.n_mis) break;
      	memset(&righeint[i],' ',sizeof(RIGAINT));
         righeint[i].hea.lung=sizeof(RIGAINT);
         righeint[i].hea.szvir=-1;
   	   righeint[i].new=0x0D0A;
      	decnum(righeint[i].progr,2,-1,misini+i+1,0.);    // numero progressivo misura
         tot=off_f[point->ext]+(long)point->punt*nbyte[point->ext];
	   	rbyte(fileno(fpp[fdde]),(short *)righeint[i].nome,(long)tot,SCD_SIGLA);      
   		rbyte(fileno(fpp[fdde]),(short *)righeint[i].descr,(long)(tot+SCD_SIGLA),SCD_DESCRIZIONE);	
      	switch (point->ext)
 		   {
      	case g1tipaa:	case g1tipas: 	case g1tipac:  case g1tipad: 
   	       rbyte(fileno(fpp[fdde]),(short *)righeint[i].umis,(long)(tot+SCD_SIGLA+SCD_DESCRIZIONE),SCD_UNIMIS); // per analogici	
         break;
         case g1tipda:  case g1tipds:  case g1tipdc:  case g1tipdd:
             rbyte(fileno(fpp[fdde]),(short*)righeint[i].umis,tot+SCD_SIGLA+SCD_DESCRIZIONE,SCD_STATO); 
         break;
         }
/*
   inserisco i nomi delle misure anche nel buffer per la stampa dell'intesta-
   zione dei valori (prima riga con i nomi associati alle colonne)
*/
		   memcpy(rtag.nome[i],righeint[i].nome,SCD_SIGLA);
      	invia(tpr_tabulato,&righeint[i]);
	   }
   	invia(tpr_tabulato,&arcontrol);
	   invia(tpr_tabulato,&arcontrol);
   }
   else invia(tpr_tabulato,str);
	invia(tpr_tabulato,&arcontrol);
	invia(tpr_tabulato,&arcontrol);
break;   
}
return(0);
}



