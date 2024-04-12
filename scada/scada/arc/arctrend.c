/**********************************************************************
*
*       C Source:               arctrend.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Fri Dec 13 15:13:56 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: arctrend.c-4 %  (%full_filespec: arctrend.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   arctrend.c

   La funzione gestisce il messaggio S_VISARC inviato da scgev al
   task tabul per inviare ad mmi i dati relativi ai trend storici.
   Le operazioni si svolgono in due fasi: nella prima viene invia-
   to il messaggio S_VPRGR con descrizione e unita' di misura (o 
   per i digitali stato 0 e stato 1), nella seconda fasi vengono 
   inviati i dati relativi al trend mediante il messaggio S_VDSGR.
   Prima della preparazione di un messaggio viene controllato che
   il trend non sia stato cancellato dal video. 
   I buffer utilizzati per la preparazione dei messaggi sono quelli
   definiti dai parametri inseriti nella struttura acrsort. (vedi
   routine arcind.c).(campo .indir per le operazioni di I/O, .vids
   per i messaggi)

   Parametri 

   mess  S_VISARC*   indirizzo del messaggio di richiesta trend

   Ritorno

   nessuno

   30 Marzo 1992  Rel. 1.0    Fc
   03 Gennaio 1995 Rel. 2.0   Fc
      Modificata trdata per test data e ora con durata inferiore al
      giorno in caso di dati a cavallo di due anni
*/
#include <osf1.h>
#include <stdio.h>
#include <string.h>

#include "mesqueue.h"
#include "comunic.inc"
#include "arc.inc"
#include "arcvis.inc"
#include "g2comdb.inc"
#include "video.inc"
#include "diagnoan.inc"
#include "tag.h"

#if defined (LINUX)
#define min(x,y) ((x)<(y) ? (x) : (y))
#endif

extern short nbyte[];
extern long off_f[];

char winFlagArc;           // flag per abilitare nella routine arctrend l'attesa dell'ack
char winStopArc;           // =1 procedere all'invio del messaggio dati =0 attendere messaggio vdsgrack

arctrend(mess)
S_VISARC *mess;
{
QUEUE_PACKET pack;
S_VPRGR *desc;             // messaggio descrizioni
S_VDSGR *dati;             // messaggio dati
PARCDES *arc;              // puntatore all'archivio corrente
short arfile;
long arpos;
ARC_DBS *bcamp;            // puntatore ad un record di dati
short  i, posmis, max_camp;
long initemp, attemp;      // tempo iniziale e tempo attuale di archiviazione
char *indice;               // puntatore all'indice delle misure in archivio
PUNTDBS point;
QMISDES *misdes;           // puntatore al descrittore della misura
long tot;
char stop;
QCAMP *camp;               // puntatore al pacchetto di inserimento messaggio
DATDBS *dbs;               // puntatore al valore di una singola misura
double odata, fdata;
short *v_tipo;             // indirizzo tabella video con il codice del
                           // trend
int ier;

v_tipo=&tstv[mess->hea.video-1].tsv[mess->hea.zona-1].v_tipo;
if(*v_tipo != mess->hea.codtrend) return(0);

desc=(S_VPRGR*) arcsort.vis;
/*
   inizializzo packet per invio messaggi a mmi
   con attesa infinita
*/
pack.que=c_mmio;
pack.flg=MSG_WAIT;
pack.wto=0;
pack.amsg=(char *) desc;
/*
   inizializzo header messaggio di invio descrizione
*/
memcpy(desc,mess,sizeof(H_MTREND));
desc->hea.indice=vprgr;
desc->hea.nodo=mess->hea.video-1;
pack.lmsg=l_vprgr+sizeof(QMISDES)*mess->hea.n_mis;

stop=0;                          // flag di continua inviare messaggio
arc=&arcdes[mess->archivio-1];
/*
   inserisco la durata dell'archivio in secondi
   il minimo intervallo di campionamento
*/
switch(arc->hea.c_dur)
{
case 0:
   desc->durata=28800.;    break;      // 8 ore
case 1:
   desc->durata=86400.;    break;      // 1 giorno
case 2:
   desc->durata=604800.;   break;      // 7 giorni
case 3:
   desc->durata=2678400.;  break;      // 1 mese
default:
   desc->durata=0.;        break;
}
desc->interv=(float) arc->hea.freqN;
/*
   ricerco il file contenente i campioni piu' antichi
   se la data e' 0.0 non ho ancora utilizzato tutti i
   file. Il file piu' antico e' il n. 0
   Il file scelto deve avere una data non inferiore alla
   data odierna meno il periodo dell'archivio.
   
*/
rew(mbox_archiv,0,&ier);
arfile=arcnome[mess->archivio-1].use;
odata=dbadv[arfile+arc->hea.p_1f];        // data file attualmente in uso
trdata(arc->hea.c_dur,&odata);            // tradotta in secondi
odata=odata+desc->durata;                 // + la durata del file attuale
desc->durata=desc->durata*arc->hea.n_file;
odata=odata-desc->durata;                 // - il periodo di archiviazione complessivo
if(odata<0) odata=-odata;

arfile++; 

for(i=0;i<arc->hea.n_file;i++)				// fino al massimo n. di file
{
   if(arfile>=arc->hea.n_file) arfile=0;
   fdata= dbadv[arfile+arc->hea.p_1f]; 
   if(arfile == arcnome[mess->archivio-1].use) break;
	if(fdata != 0.0)
	{
	   trdata(arc->hea.c_dur,&fdata);
   	if(fdata >= odata) break;               // all'interno del periodo ?
	}
   arfile++; 
}
arc->canc=arfile;                          // setto file occupato
tra(mbox_archiv,1);
/*
   leggo il primo campione e memorizzo il tempo iniziale di archiviazione
   ( se non esiste pongo a 0 giorno, mese, anno e  ora iniziale
*/
arpos=0;
stop=arcread(mess->archivio-1, &arfile, &bcamp, &arpos);
if(stop)
{
   desc->t_iniz=0.;
   desc->giorno=desc->mese=desc->anno=0;
}
else
{
   desc->giorno=bcamp->hea.giorno;   
   desc->mese=bcamp->hea.mese;   
   if(bcamp->hea.anno>=2000)
      desc->anno=bcamp->hea.anno-2000;
   else
      desc->anno=bcamp->hea.anno-1900;
   desc->t_iniz=(float)bcamp->hea.secondi+
         (float)bcamp->hea.minuti*FMIN+(float)bcamp->hea.ore*FORA;   
   arcsec(bcamp,&initemp);
}
/*
   estrazione delle descrizioni, unita' di misura e stato 0 e stato 1
   Se una misura non e' in archivio la sua descrizione e' posta a '*'
   e non si prosegue nell'invio dei dati
*/
indice=&mess->point[0];
misdes=desc->md;
memset(misdes,'*',sizeof(QMISDES)*max_sigqua);
for(i=0;i<mess->hea.n_mis;i++,indice++,misdes++)
{
   if((*indice)!=-1)           // misura esistente
   {
      point=arc->mis[*indice];
      tot=off_f[point.ext]+(long)point.punt*nbyte[point.ext]+SCD_SIGLA;
	   rbyte(fileno(fpp[fdde]),(short *)misdes,(long)tot,
            nbyte[point.ext]-SCD_SIGLA);      
   }
   else stop=1;
}
enqueue(&pack);
/*
   se o non ho campioni o almeno una misura non esiste non invio 
   altri messaggi e chiudo il file di I/O
*/
if(stop || (*v_tipo != mess->hea.codtrend)) 
{
   arfile=-1;
   arcread(mess->archivio-1, &arfile, &bcamp, &arpos);
   return(0);
}
winStopArc=1;          // procedere al primo invio
/*
   ciclo di invio dati   calcolando quanti campioni al massimo puo'
   contenere un messaggio (max_camp)
	In caso di coda piena attendo fino a 1 secondo
*/
dati=(S_VDSGR*)arcsort.vis;
dati->hea.indice=vdsgr;
dati->flag=2;                    // flag primo pacchetto
dati->n_camp=0;
camp=&dati->b;
if(winFlagArc)       // per MMI Win
   max_camp=min(num_qcamp,(l_maxgrWin-l_vdsgr)/(l_ftemp+sizeof(DATDBS)*mess->hea.n_mis));
else
   max_camp=min(num_qcamp,(l_maxgr-l_vdsgr)/(l_ftemp+sizeof(DATDBS)*mess->hea.n_mis));

pack.flg=MSG_NOWAIT;			
for(;;)
{
/*
   ciclo di inserimento dati di ciascuna misura  definita
*/
   arcsec(bcamp,&attemp);
   camp->temp=attemp-initemp;
   dbs=& camp->val;
   memset(dbs,-1,sizeof(DATDBS)*mess->hea.n_mis);     // inizializzo
   indice=&mess->point[0];
   dati->n_camp++;
   for(i=0;i<mess->hea.n_mis;i++,indice++,dbs++)
   {
      if(bcamp->hea.n_misvel && arc->hea.t_mem==M_Par) 
      {
            posmis=arcpar(bcamp,*indice);
            if(posmis==-1) continue;               // non esiste (arch. parziale)
       }
       else posmis=*indice;
       memcpy(dbs,bcamp->dbs+posmis,sizeof(DATDBS));  // copio campione
       if(dbs->d.imis==-1) continue;

       if(dbs->d.dtipo==-1) dbs->d.dtipo=-2;          // correggo codifica digitale
   }
   if(*v_tipo != mess->hea.codtrend) break;
   stop=arcread(mess->archivio-1, &arfile, &bcamp, &arpos);
   if(stop || dati->n_camp>=max_camp)
   {
      if(stop) dati->flag=dati->flag+1;               // flag fine invio dati
      pack.lmsg=l_vdsgr+dati->n_camp*(l_ftemp+mess->hea.n_mis*sizeof(DATDBS));
      if(winFlagArc)       // per MMI Win attendo Ack
      {
         while((*v_tipo == mess->hea.codtrend) && (!winStopArc))
         {
            wai(1);
         }
#if defined OSF1 || defined LINUX
         winStopArc=1;
#else
         winStopArc=0;
#endif
      }
      while(enqueue(&pack))
		{ 
#if defined OSF1 || defined LINUX
		wai(1);
#else
		wai(15);
#endif
		}
      dati->flag=0;                                   // flag pacchetto intermedio
      if(stop) break;   
      camp=&dati->b;
      dati->n_camp=0;
   }
   else camp=(QCAMP*)((char*)camp+mess->hea.n_mis*sizeof(DATDBS)+l_ftemp);                                          // nuovo pacchetto
}
arfile=-1;
arcread(mess->archivio-1, &arfile, &bcamp, &arpos);
return(0);
}
/*
   trdata

   funzione per la trasformazione della data nel formato
   aammgg o mmggoo in secondi

   Parametri

   tipo  char     tipo di archivio =0 formato data mmggoo
                                   >0 formato data aammgg
   data *double   data da trasformare 

   Ritorno

   data  *double  data nel nuovo formato

   1 Aprile 1992  Rel 1.0  Fc
*/
trdata(tipo,data)
short tipo;
double *data;
{
short anno, mese, giorno, ora;
extern double fsec_double();

if(!tipo)
{
   mese=(*data)/10000;
   ora=(*data)-mese*10000;
   giorno=ora/100;
   ora=ora-giorno*100;
   mese--;
   giorno--;
   if(mese>dbadv[db_mese]) 
	anno=dbadv[db_anno]-1900-1;//test per il caso fra due anni
   else 
	anno=dbadv[db_anno]-1900;
}
else
{
   ora=0;
   anno=(*data)/10000;
   giorno=(*data)-anno*10000;
   mese=giorno/100;
   giorno=giorno-mese*100;
   mese--;
   giorno--;
}
*data=fsec_double(0.0,0.0,(double)ora,(double)giorno,(double)mese,(double)anno);
return(0);
}
