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
   allsric.c

   La routine esegue il riconoscimento degli allarmi relativi alle
   TAG inserite nel messaggio $RICSIN oppure associate all'intera
   pagina.
   Verifica che le TAG esistano e che il data base segnalato non
   sia visualizzato su nessun video.

	Il messaggio e' cosi' formato:
		  
	word 0		= -2	argomento intero
	word 1		n. data base allarmi da 1 a 6
   word 2      = -2  argomento intero
   word 3      non utilizzato
	word 4      = lunghezza prima stringa 
	word 5		= prima stringa
	......
	word n		= lunghezza ennesima stringa
	word n+1		= ennesima stringa
   ......
	word n+m		= -1 tappo fine messaggio


   Parametri

   mess  short *     messaggio di riconoscimento allarmi
	video	short			n. del video che ha richiesto il riconoscimento
                     (a partire da zero)
   zona  short       n. della zona che ha richiesto il riconoscimento
                     (a partire da zero)

   Ritorno

   nessuno

      6 Aprile 1995
         Corretta gestione tappo puntatori link da esaminare

*/

#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "video.inc"

struct  ric_all {
								short arg1;
							   short dbs;
                        short arg2;
                        short spare;
								short lung;
								short tag;
							} ;
			
allsric(mess,video,zona)
struct ric_all *mess;
short video, zona;
{
S_DBS_ALL *all;
S_DBS_ALV *alv;
short *arg;
short i;
S_VIDEO *pVideo;
long blocco;         // per ricerca su Fnomi 
short  posiz;
char nome[SCD_SIGLA];
short nTag;
#define max_tag   20
S_PUNT punt[max_tag], *p;
short tipo;
/*
	verifico n. data base richiesto se compreso fra 1 e max_dbsall
	e se e' stato definita nel file fdesal.rtf
*/
if(mess->dbs<1 || mess->dbs>max_dbsall) return;
all=&bDbsAll[mess->dbs-1];
if(!all->def) return;
/*
   verifico che il data base non sia visualizzato su nessun video
*/
pVideo=&tstv[0];
for(i=0;i<max_video;i++,pVideo++)
{
   if((pVideo->tsv[zonai].v_tipo == p_al || pVideo->tsv[zonai].v_tipo == p_ar)
      && (bDbsAlv[i].pal==(mess->dbs-1))) return;
}
/*
   tag specificate o riconoscimento degli allarmi dell'intera pagina ?
*/
arg=&mess->lung;
if((*arg)==-1)      // intera pagina
{
   allpag(mess->dbs-1, &gdav[video][zona*max_mis_zone]);
}
else
{
   p=&punt[0];
   for(nTag=0;(*arg)!=-1;)
   {
      memset(nome,0,sizeof(nome));
      memcpy(nome,arg+1,*arg);
      if(!ricerca(nome,&p->point,&tipo,&blocco,&posiz,fpp[fnomi]))
      {
         p->tipo=tipo;
         nTag++;
         p++;
         if(nTag==(max_tag-1))
         {
            p->tipo=-1;        // terminatore lista
            allpag(mess->dbs-1, punt);
            p=&punt[0];
            nTag=0;
         }
      }
      arg=arg+((*arg)-1)/2+2;
   }
   p->tipo=-1;        // terminatore lista
   p->point=-1;        // terminatore lista
   if(punt[0].tipo!=-1)
      allpag(mess->dbs-1, punt);
}
return;
}


