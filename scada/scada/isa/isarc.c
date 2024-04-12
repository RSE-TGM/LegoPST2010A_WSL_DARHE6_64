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
	Modulo   : 	isarc.C
	            Gestione messaggi STOP-NET per trasferimento file 
	            archivi verso PC di configurazione.
					Contiene le funzioni di gestione dei messaggi relativi
					al trasferimento di file d'archivio e lilbro giornale
					del task isa().
					Elenco messaggi:
					 					mapr  	-richiesta archivi presenti
					 					mefr  	-richiesta elenco files d'archivio
					 					mtfdr 	-richiesta trasmissione file descrittore archivio
					 					mtfar 	-richiesta trasmissione file d'archivio
										mflbgpr	-richiesta file libro giornale presenti
                              meflgr   -richiesta elenco files con lunghezza

	Creazione:  E.Locatelli  -  15.12.93  - 
   Revisione:  D.Cristiani  -  22.03.94  -
   Revisione:  M.Pentolini(+s.st)  -  30.08.95  - inserito indice connessione in tx
*/
#include <osf1.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include <string.h>
#include <stdio.h>

#include "dconf.inc"	
#include "isarc.inc"
#include "mesqueue.h"
#include "diagnoan.inc"
#include "g2comdb.inc"
#include "print.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "isa.h"

static  QUEUE_PACKET spack;
extern U_ISA_MESS messg;
extern unsigned isarx,isatx;
					   			 
/*
   Funzione di gestione del messaggio di codice "mflbgpr"
*/
void ges_mflbgpr(void)
{
short i, j;
M_FLGPS ms;

 	  	spack.flg=MSG_WAIT;
   	spack.que=isatx;
   	spack.wto=0;
      ms.conn=messg.h.ch;

		for (i=1,ms.tot_flbg=0,j=db_falco1;i<=max_n_allfile;i++,j++)
		{
         if(dbadv[j])
			   ms.tot_flbg++;
		}
		ms.mess=mflbgps;			// codice messaggio
		ms.dbfileal=dbadv[db_fileal];			// codice messaggio

      spack.lmsg=l_flbgps;
		spack.amsg=(char *)&ms;
      enqueue(&spack);
}

/*
   Funzione di gestione del messaggio di codice "mapr"
*/
void ges_mapr(void)
{
short i;
M_APS ms;

 	  	spack.flg=MSG_WAIT;
   	spack.que=isatx;
   	spack.wto=0;
      ms.conn=messg.h.ch;

		for (i=0,ms.tot_arc=0;i<n_arc;i++)
		{
			if (arcdes[i].hea.iarc==-1) continue;
			ms.arc[ms.tot_arc].num=arcdes[i].hea.iarc;
			ms.arc[ms.tot_arc].tipo=arcdes[i].hea.tipo;
			ms.tot_arc++;
		}
		ms.mess=maps;			// codice messaggio

      spack.lmsg=l_aps;
		spack.amsg=(char *)&ms;
      enqueue(&spack);
}



/*
   Funzione di gestione del messaggio di codice "meflgr"
*/
void ges_meflgr(void)
{
ARCNOME *filarc;        // puntatore ai nomi dei file dell'archivio
short i;
M_EFLGS ms;
short farcp;
char nomfile[FILENAME_MAX+1];			// nome + path file archivio


spack.flg=MSG_WAIT;
spack.que=isatx;
spack.wto=0;
ms.conn=messg.h.ch;

ms.mess=meflgs;			// codice messaggio
filarc=arcnome[messg.efr.iarc-1].arc;
for (i=0,ms.num_file=0;i<arcdes[messg.efr.iarc-1].hea.n_file;i++,filarc++)
   {
	if (filarc->nome[0]!=0)			// se nome file non nullo
	   {  
      memset(nomfile,0,FILENAME_MAX+1);
      strcpy(nomfile,arcpath);
      strcat(nomfile,"\\");
      strcat(nomfile,filarc->nome);
		strcpy(ms.arcnomi[ms.num_file].nome,filarc->nome);
      farcp=open(nomfile,O_RDONLY);
		if (farcp==-1) 
         {   
         ms.flength[ms.num_file]=-1;
   		ms.num_file++;
         continue;
         }
      ms.flength[ms.num_file]=filelength(farcp);
      close(farcp);
		ms.num_file++;
		}
   }
spack.lmsg=l_eflgs;
spack.amsg=(char *)&ms;
enqueue(&spack);

}




/*
   Funzione di gestione del messaggio di codice "mtfdr" "mtfar"
*/
void ges_mtfdr(void)
{
ARCNOME *filarc;        // puntatore ai nomi dei file dell'archivio
char nomfile[FILENAME_MAX+1];			// nome + path file archivio
short numf;					// numero file in trasmissione
long offset;
short harc;
M_TFS ms;

 	  	spack.flg=MSG_WAIT;
   	spack.que=isatx;
   	spack.wto=0;
		spack.amsg=(char *)&ms;

      ms.hea.conn=messg.h.ch;          // indice connessione
		ms.hea.mess=mtfs;                // codice messaggio
	   ms.hea.num_bl=0;						// inizializzazione numero blocco
	   ms.hea.last_bl=0;						// inizializzazione ultimo blocco
		ms.hea.err=0;				         // inizializzazione codice errore

		// nome file
		if (messg.tfr.mess==mtfdr) //file descrittore
			strcpy(nomfile,conf[RTF]);
		else 	// file d'archivio
		{
			// "loc" del file in trasmissione
			// ciclo di ricerca numero file in tabella dei nomi--> numf
			filarc=arcnome[messg.tfr.iarc-1].arc;
			for (numf=0;numf<arcdes[messg.tfr.iarc-1].hea.n_file;numf++,filarc++)
			{
				if (!strcmp(messg.tfr.arcnome.nome,filarc->nome))	break;
			}
			if (numf==arcdes[messg.tfr.iarc-1].hea.n_file) 	// nome file non trovato
				goto errore; 
			arcdes[messg.tfr.iarc-1].canc=numf;
			strcpy(nomfile,arcpath);
		}
		strcat(nomfile,"\\");
		strcat(nomfile,messg.tfr.arcnome.nome);

      spack.lmsg=l_tfs;
		
		harc=open(nomfile,O_RDONLY|O_BINARY);
		if (harc==-1) goto errore;

      offset=0L;
		while (!ms.hea.last_bl)
		{
   		ms.hea.lung_bl=rbyte(harc,ms.dati_bl,offset,l_buf);
			if (ms.hea.lung_bl < l_buf) ms.hea.last_bl=1;   // ultimo blocco
         enqueue(&spack);
			ms.hea.num_bl++;						// incremento numero blocco
        	offset+=ms.hea.lung_bl;
		}
		close(harc);
		// "unloc" del file in trasmisssione
		if (messg.tfr.mess==mtfar)		arcdes[messg.tfr.iarc-1].canc=-1;

		return;

// Gestione errori
errore:
	ms.hea.err=1;
	ms.hea.last_bl=1;
   enqueue(&spack);
	if(messg.tfr.mess==mtfar) arcdes[messg.tfr.iarc-1].canc=-1;
} 



