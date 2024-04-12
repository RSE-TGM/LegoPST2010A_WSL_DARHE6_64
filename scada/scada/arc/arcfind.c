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
   arcfind.c

   La routine ricerca per un dato archivio il primo campione utile
   avente la data richiesta contenuta nel messaggio di tipo S_STAB
   L'operazione di ricerca del file avviene con un lock sulla
   mail box mbox_archiv per impedire al task archivi l'eventuale
   cancellazione del file in uso. (Viene settata la locazione
   arcdes[].canc. Il reset e' gestito da arcread quando il file
   in uso non coincide con ardes[].canc e nella close.)
   
   Parametri

   mess     S_STAB *    messaggio richiesta dati
   arfile   short *     indice del file in cui sono stati trovati i
                        dati
                        (viene aggiornato dalla routine)
   arpos    long *      posizione all'interno del file
                        (viene aggiornato dalla routine)
   bcamp    ARC_DBS**   puntatore al buffer dati di archivi
                        (viene aggiornato dalla routine)
   Ritorna

   0     se ha trovato i campioni corrispondenti alla data
	1		se la data non e' accettabile (> dell'ultimo campione
         memorizzato) o l'archivio non esiste

   17 Marzo 1992  Rel. 1.0 Fc
*/
#include <osf1.h>
///#include "pscs.cfg"
#include "g2comdb.inc"
#include "diagnoan.inc"
#include "messcada.inc"
#include "allar.inc"
#include "arc.inc"

arcfind(mess,arfile,arpos,bcamp)
S_STAB* mess;
short *arfile;
long *arpos;
ARC_DBS **bcamp;
{
PARCDES *arc;
float fdata;
float data;
short irec, i;
char ini_file, pfile;
long time_1, time_2, time_ric;
short anno;
int ier;

arc=&arcdes[mess->archivio-1];
/*
   trasformo la data in floating 
*/
if(mess->anno >=2000) anno=mess->anno-2000;
else anno=mess->anno-1900;
if(!arc->hea.c_dur) 
   fdata=(float)mess->ore+(float)mess->giorno*100+(float)mess->mese*10000;
else fdata=(float)mess->giorno+(float)mess->mese*100+(float)(mess->anno-1900)*10000;
/*
   ricerco il nome del file da cui iniziare la ricerca della data
   a partire dal file attualmente in uso 
*/
ini_file=arcnome[mess->archivio-1].use;
/*
   verifico se la data richiesta > di quella attuale in tal caso
   considero la richiesta di stampa non valida
*/ 
data= dbadv[ini_file+arc->hea.p_1f];
if(fsec((double)0.,(double)mess->minuti,(double)mess->ore,
   (double)mess->giorno,(double)mess->mese,(double)mess->anno) >=
   fsec((double)0.,(double)dbadv[db_minuti],(double)dbadv[db_ora],
   (double)dbadv[db_giorno],(double)dbadv[db_mese],(double)dbadv[db_anno])) 
   return(1);

rew(mbox_archiv,0,&ier);
for(*arfile=ini_file;;)
{
   data= dbadv[(*arfile)+arc->hea.p_1f];
/*
   la data del file deve essere inferiore a quella richiesta
   Nel caso di durata 0 e' possibile a cavallo dell'anno avere
   data = 01xxyy e la fdata con 12xxyy in questo caso fdata >
   data ma la ricerca deve procedere. Si utilizza il test fdata-data
   > 100000
*/
   if(data <= fdata && ((fdata-data) < 100000)) break;  // trovato file
   
   pfile=*arfile;   
   (*arfile)--;                                             // file precedente
   if(*arfile<0) *arfile=arc->hea.n_file-1;
/*
   ho completato il ciclo la data e' inferiore alla prima
   archiviazione  oppure sono arrivato ad un file non ancora 
   utilizzato
*/
   if(*arfile==ini_file || dbadv[(*arfile)+arc->hea.p_1f] == 0.0) 
   {
      *arfile=pfile;              // recupero l'ultimo file
      break;
   }
}
arc->canc=*arfile;               // setto file occupato
tra(mbox_archiv,1);
/*
   apro il file e ricerco la posizione al suo interno
	per la ricerca del primo campione da stampare 
	Prendo in considerazione giorno ora minuti e secondi
*/
time_1=time_2=0;
time_ric=tsec(mess->secondi,mess->minuti,mess->ore,mess->giorno);
*arpos=0;
for(;;)
{
/*
	chiamo la routine per la lettura dei campioni
	se ritorna 1 ho raggiunto end of file o e' stato cancellato
*/
	irec=arcread(mess->archivio-1, arfile, bcamp, arpos);
	if(irec) break;
	time_2=tsec((*bcamp)->hea.secondi,(*bcamp)->hea.minuti,(*bcamp)->hea.ore,
               (*bcamp)->hea.giorno);
/*
	ho trovato l'inizio dei campioni da stampare e l'offset e' dato
	da arpos
*/
	if(time_2 >= time_ric && time_1 <= time_ric) break;	
	time_1=time_2;
}							 
return(irec);
}   
