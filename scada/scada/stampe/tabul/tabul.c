/**********************************************************************
*
*       C Source:               tabul.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Dec 16 12:08:02 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: tabul.c-5 %  (%full_filespec: tabul.c-5:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*	->TABUL
 *      task di stampa tabulati:
 *      - inizializza i parametri per l'interprete (puntatori a codice,
 *        data base locale, stack presenti nel descrittore S_INTERP).
 *        N.B. L'inizializzazione � stata effettuata direttamente nelle
 *        dichiarazioni per risparmiare tempo (utilizzando variabili
 *        static in modo che l'inizializzazione avvenga prima che il
 *        programma venga eseguito).
 *      - ciclicamente:
 *          . scoda il messaggio dalla coda c_tabul 
 *          . cerca il nome del tabulato sul dizionario (se non trovato 
 *            torna a inizio ciclo): in caso di richiesta da operatore
 *            invia il messaggio di tabulato non esistente o di tabulato
 *            in stampa
 *          . legge il programma di stampa e i dati dal file FTAB.RTF
 *          . se il tabulato ha la 'testa' la legge e chiama l'interprete
 *          . se il tabulato ha il 'corpo' lo esegue n_cicli volte
 *				  eseguendo la raccolta dati da data base
 *          . se il tabulato ha la 'coda' la legge e chiama l'interprete
 */
#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"		 // N.B. fileop � incluso in comunic
#include "messcada.inc"
#include "allar.inc"
#include "tabulati.inc"
#include "print.inc"
#include "eqschpas.inc"
#include "stschpas.inc"
#include "trapas.inc"
#include "dconf.inc"
#include "fileop_names.h"
#include "mesqueue.h"
#include "diagnoan.inc"
#include "diagnodi.inc"
#include "mesprocv.inc"
#include "cprint.inc"

// External function declarations
extern void arcind(short *, int, char *, int);
extern void bitset(short *, short, short);
extern void stfile(char *, short *, int, short);
extern int wildric(char *, short *, short *, char, FILE *);
extern void arctab(void *);
extern void invia(short, void *);
extern int trasfile(char *, short *);
extern char *itoa(int, char *, int);
extern void testlbg(int);
extern void arctrend(void *);
extern int rbyte(int, short *, long, int);
extern void racdbs(HEAD_DATAB *, char *);
extern void interfc(struct SCB *, struct SCHEDULER *);
extern void wai(int);

/*
   il buffer viene utilizzato anche in fase di visualizzazione dei trend
   storici (non variarne le dimensioni !!!)
*/
char buftab[l_htab+l_datab];  // buffer che conterr� l'header del tabulato
								      // e la parte dati 

S_HCOD phcod;									  // header sezione programma

struct SCHEDULER da_tab;
struct SCHEDULER *s_interp=&da_tab;
struct SCB *scb;

void _tabulati()      // nome preceduto da underscore per non confonderlo
                      // con la define #TABULATI TAB_SI  
{
short point;
short ext;
char wildstr[SCD_SIGLA+1];
char bStart;

S_HTAB *phtab=(S_HTAB *)&buftab[0];		  // punta all'header del file FTAB.RTF
HEAD_DATAB *hdat=(HEAD_DATAB *)&buftab[off_dat];  // punta all'header della zona dati 
S_DIZTAB *pdiz;
short mbox;

long disp;
int i,j,ier ;
char filename[30];
short itab;             /* indice tabulato      */
struct s_fine	{	HEA_STA hea;
				short   fi; } fine ;
				
QUEUE_PACKET queuer;    // coda per RECIVE
QUEUE_PACKET packs;  // canale per SEND utilizzato forzamento 
						  // --> accoda ad scgev

union u_mess {S_STAB s ;				// messaggio scodato dalla coda c_tabul
		 		  S_MCSP mcp ;				/* modifica stato punto 		*/
				  S_VISARC v;
				  S_SFILE f;				// stampa file generico
			    } mess;
/*
printf("_TABULATI: [1]  ENTRATO!!!\n");
*/
// inizializzazione offset di inizio dati e codice :

da_tab.off_buf_dbl=da_tab.buf_dbl;       // data base locale del tabulato
da_tab.off_inizio_codice=(char *)da_tab.buf_pr;  // codice del tabulato

arcind(s_interp->buf_pr,l_codtab,&buftab[0],sizeof(buftab));

fine.fi=0x0D0A ;			   // buffer fine tabulato
fine.hea.lung=sizeof(fine);

packs.flg=MSG_WAIT;
packs.wto=0;
packs.que = c_mmii;
packs.amsg=(char*) & mess;
packs.lmsg=sizeof(S_MCSP);


queuer.que=c_tabul;
queuer.wto=-1;
queuer.amsg=(char*) & mess;

/*
	la scb inizia alla fine del codice
	inizializzo i campi end_stk e begin_stk
*/
scb=(struct SCB *)&s_interp->buf_pr[l_codtab/2];
scb->end_stk=l_codtab+sizeof(struct SCB)-2;
scb->begin_stk=scb->end_stk-sizeof(scb->seq_stk);

/* DEBUG
printf("_TABULATI: sizeof(SCB)=%d sizeof(scb->seq_stk)=%d scb->end_stk=%d scb->begin_stk=%d\n",
       sizeof(struct SCB), sizeof(scb->seq_stk), scb->end_stk, scb->begin_stk);
*/

for(;;)
{
/*
        scoda il messaggio dalla coda c_tabul
*/
   bitset(&dbdd[lockarc],g2di_asl,0);      // lock interno libero
	if(dequeue(&queuer))                        // coda vuota ?
   {
      queuer.wto=0;                           // time out infinito
      queuer.flg=MSG_WAIT;
      bitset(&dbdd[lockarc],g2di_sl,0);      // lock con scgev libero
      continue;
   }

   queuer.wto=-1;                           // senza attesa
   queuer.flg=MSG_NOWAIT;
   bitset(&dbdd[lockarc],g2di_asl,1);      // lock interno occupato
	switch(mess.s.mess)
	{
	case msfile:
			stfile(mess.f.nome, s_interp->buf_pr, l_codtab, mess.f.richiesta); 
	break;
	case mcsp :	 /* modifica stato punto con wild characters */
/*
	copia la stringa con wild characters su una stringa di appoggio
*/
		wildstr[SCD_SIGLA]=0;
		memcpy(wildstr,mess.mcp.point,SCD_SIGLA);
	   for(i=0;i<SCD_SIGLA;i++) if( wildstr[i] == ' ') wildstr[i]=0 ;
		bStart=1;
/*
	ricerca in fnomi
*/
		i=0;
		while(wildric(wildstr,&point,&ext,bStart,fpp[fnomi])==0)
			{
 	      mess.mcp.point[0]=1;
     		mess.mcp.point[1]=ext;
 	      mess.mcp.point[2]=point;
			enqueue(&packs);
			bStart=0;
			}

/*
	Invia alla STOP il messaggio di fine scansione nomi
*/
      mess.mcp.point[0]=2;
		enqueue(&packs);
		break;

	case	mstabarc:
/*
	tabulato da archivio chiama la routine	 che gestisce la stampa
	del tabulato relatvo all'archivio.
*/
	arctab(&mess);
	invia(tpr_reset,&mess);
	break;
   case mtrasfarc: 
/*
	richiesta di trasferimento di archivio su dischetto
*/
#if !defined  OSF1 && !defined LINUX
	arcflop(&mess,s_interp->buf_pr); 
#else
	trasfile(mess.f.nome,NULL);
#endif
	break;
   case mtrasfpol: 
/*
	Esamina se � una richiesta di trasferimento di un file POL su dischetto
*/
		strcpy(filename,"FPOL");
		itoa(mess.s.archivio,filename+strlen(filename),10);
		strcat(filename,".VAR");
		trasfile(filename,s_interp->buf_pr); 
	 break;
   case mtrasfall: 
/*
	Esamina se � una richiesta di trasferimento di un file FILBGn su dischetto
*/
		strcpy(filename,FILBG0);
		filename[strlen(filename)-1]=filename[strlen(filename)-1]+mess.s.archivio;
		strcat(filename,RTFEXT);
/*
	se la copia e' riuscita setto il bit fz in dbs
	inoltre se il file copiato e' quello successivo a quello
	in uso devo far rientrare l'eventuale allarme di disponi-
	bilita' files libro giornale esaurita
*/
		if(!trasfile(filename,s_interp->buf_pr))
		{
			bitset(&dbadf[mess.s.archivio+db_falco1-1],g2an_fz,1);
			testlbg(n_allfile);
		}
	 break;
    case mvisarc: 
/*
	richiesta di visualizzazione di archivio
*/
    arctrend(&mess);
	 break;
 	 case mstab:              
/*
        ciclo di ricerca nel file dizionario del nome del
        tabulato
*/
	itab=0;
	pdiz=diztab;
	while(itab < n_tabu && memcmp(mess.s.nome,pdiz->nome,l_nomtab))
		{
	   itab++;
		pdiz++;
		}
/*
	caso di tabulato non trovato.
*/
	if(itab==n_tabu) 	break;  // torna all'inizio del ciclo for(;;)
/*
	caso di tabulato esistente
   leggo la parte dati nel buffer puntatato da s_interp->buf_dbl
*/
   fine.hea.szvir=mess.s.richiesta;    // imposto la stampante da utilizzare
   ta.hea.szvir=mess.s.richiesta;

	disp=itab;
	disp*=rec_ftab;
	ier=rbyte(fileno(fpp[ftab]),(short*)&buftab[0],disp,l_htab+l_datab);
/*
	copia i DATA in fondo al DBL.
*/
	memset((char*)s_interp->buf_dbl,0,2048);
	memcpy(&s_interp->buf_dbl[l_datab-(hdat->l_data)],
		&buftab[off_dat+l_datab-(hdat->l_data)],hdat->l_data);
/*
	leggo header codice parte programma
*/
	ier=rbyte(fileno(fpp[ftab]),(short*)&phcod,disp+off_cod,l_hcod);
/*
	leggo parte programma
*/
	ier=rbyte(fileno(fpp[ftab]),(short*)s_interp->buf_pr,disp+off_cod+l_hcod,
		l_codtab-l_hcod);
/*
        verifico se il tabulato ha una testa
*/
	if(phcod.entryI!=-1)		// se ENTRY INIT � diversa da -1 esiste testa
		{
	     racdbs(hdat,s_interp->buf_dbl);		// raccolta da data base di sistema
		  scb->st_seq=SEQATTI;
		  scb->f_init_stack=1;	// inizializzazione stack ed esecuzione
		  scb->ind_cod=phcod.entryI*2;
        interfc(scb,s_interp) ;
		}
/*
        verifico se il tabulato ha un corpo
*/
//printf("\n ripetizione corpo cicli %d con frquenza %d",phtab->cicli,phtab->arc_frq);
	if(phcod.entry0!=-1)
		{
		for(j=0;j<phtab->cicli;j++)   
			{
//printf("\n ciclo n. %d:",j);
	      racdbs(hdat,s_interp->buf_dbl);		// raccolta da data base di sistema
		  	scb->st_seq=SEQATTI;
		  	scb->f_init_stack=1;	// inizializzazione stack ed esecuzione
		  	scb->ind_cod=phcod.entry0*2;
		   interfc(scb,s_interp);
/*
        in caso di di prelievo dati da data base				 
        se non � l'ultimo ciclo ripeto il corpo dopo un'attesa
		  pari alla frequenza specificata nel descrittore
*/
         if(phtab->tip_dat==DATBAS && j<(phtab->cicli-1))
        	wai(phtab->arc_frq * 1090 );		 // 1000*60 / 55
			}
		}
/*
        verifico se il tabulato ha una coda
*/
	if(phcod.entryT != -1)
		{
		  scb->st_seq=SEQATTI;
		  scb->f_init_stack=1;	// inizializzazione stack ed esecuzione
		  scb->ind_cod=phcod.entryT*2;
        interfc(scb,s_interp) ;
		}
 	invia(tpr_tabulato,& fine);
 	invia(tpr_reset,& fine);
	break;
	}
}
/*
printf("_TABULATI: USCITO!!!\n");
*/
}


