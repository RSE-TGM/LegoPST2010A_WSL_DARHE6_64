/**********************************************************************
*
*       C Source:               allsel.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr  1 15:21:49 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: allselASD.c-4 %  (%full_filespec: allselASD.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   allselASD.c

   La routine esegue la selezione delle zone di impianto inserite
   nel messaggio msen con stringa $MINIASD
	Il messaggio e' cosi' formato:
		  
	word 0		= -2	argomento intero
	word 1		n. data base allarmi da 1 a 6
   word 2      = -2  argomento intero
        word 3      Tipo di allarmi da filtrare 
	word 4      = -2  argomento intero
	word 5		= 0 richiesta pagina allarmi miniASD
			= 1 richiesta riconosc. singolo allarme
	word 6		= -2  argomento intero
	word 7		prima gerarchia allarme selezionata (0-512)
	word 8		= -2 argomento intero
	word 9		seconda gerarchia allarme selezionata  (0-512)
	......
	......
	word 14         = -2 agomento intero
	word 15         = filtro
SOLO PER RICONOSCIMENTO:
	word 17		= punt allarme da riconoscere
	word 19		= ext allarme da riconoscere
	word 21		= ertr allarme da riconoscere
	word 23		= giorno allarme da riconoscere
	word 25		= ore allarme da riconoscere
	word 27		= minuti allarme da riconoscere
	word 29		= secondi allarme da riconoscere
        

   Parametri

   mess  short *     messaggio di selezione zone
	video	short			n. del video che ha richiesto la visualizzazione
							della pagina allarmi

   Ritorno

   0     short    visualizzare pagina allarmi
   -1    short    parametri non corretti richiesta non soddisfatta


*/

#include <stdio.h>
#include "g2comdb.inc"
#include "messcada.inc"
#include "allar.inc"
#include "video.inc"
#include "mesprocv.inc"

// External function declarations
extern void bitset(short* buffer, short indice, short bit);



/*
N.B.
l 'argomento arg1 nella strttura sel_zon corrisponde ad tipo_arg_2 
nella struttura S_SEND_ALLARMI_ZONE di client+_s.h
*/

struct  sel_ger 
{
   short arg1;
   short dbs;
   short arg2;
   short tipo;
   short arg3;
   short pric;
   short arg4;
   short zona;
   } ;
			
int allselASD(mess,video)
struct sel_ger *mess;
short video;
{
S_DBS_ALL *all;
S_DBS_ALV *alv, *ali;
short *arg;
short mask[2], i;

/*
	verifico n. data base richiesto se compreso fra 1 e max_dbsall
	e se e' stato definita nel file fdesal.rtf
*/
if(mess->dbs<1 || mess->dbs>max_dbsall) return(-1);
all=&bDbsAll[mess->dbs-1];
if(!all->def) return(-1);

alv=&bDbsAlv[video-1];
/*
	resetto le maschere precedentemente selezionate ed inserisco
	le nuove specificate nel messaggio
*/
arg=&mess->arg4;
if(*arg==-1)
{
#ifdef DEBUGYES
printf("zone no variaz.\n");
#endif
}
else
{
   i=0;
   mask[0]=0;           // inizializzazione zone selezionate
   mask[1]=0;
   /*
   2 casi : richiesta allarmi "mpalminiASD" e riconoscimento
   */
   if(mess->pric==mpalminiASD)
      for(;(*arg)!=-1;)
      {
/*
		esamino la gerarchia che e' arrivata 
*/	
#ifdef DEBUGYES
	   printf("valore di arg=%d\n",*arg);
#endif
/*
Inserisco la gerarchia nel campo della struttura video
*/
           if(*arg != -2 && i < n_gerarchie )
              {
              
              /*
              Setto maskera per vedere se esistono altre pagine allarmi 
              aperte sulla stessa gerarchia.(In teleperm primo liv.gerarchia=
              zona impianto).
              */
              if(i==0)  bitset(mask,*arg,1);
              alv->par_miniASD.gerarchia[i]=(unsigned char) *arg;
#ifdef DEBUGYES
              printf("valore di gerarchia=%d\n",alv->par_miniASD.gerarchia[i]);
#endif
              i++;
              }
            else if(*arg != -2)  /* inserisco tipo di filtro */
              {
              alv->par_miniASD.filtro=*arg;
#ifdef DEBUGYES
              printf("allselASD:Valore del filtro =%d \n",alv->par_miniASD.filtro);
#endif
              }
   	   arg++; 
      } /* end for */
   else if(mess->pric==mricsminiASD)
      for(;(*arg)!=-1;)
      {
           /*
           Esamino la gerarchia che e' arrivata 
           */	
#ifdef DEBUGYES
	   printf("valore di argx ric=%d\n",*arg);
#endif
           /*
           Inserisco la gerarchia nel campo della struttura video
           */
           if(*arg != -2 && i < n_gerarchie )
              {
              /*
              Setto maskera per vedere se esistono altre pagine allarmi 
              aperte sulla stessa gerarchia
              */
              if(i==0)  bitset(mask,*arg,1);
              alv->par_miniASD.gerarchia[i]=(unsigned char) *arg;
#ifdef DEBUGYES
              printf("valore di gerarchiaxric[%d]=%d\n",i,alv->par_miniASD.gerarchia[i]);
#endif
              i++;
              }
            else if(*arg != -2 && i== n_gerarchie)  /* inserisco tipo di filtro */
              {
              alv->par_miniASD.filtro=*arg;
#ifdef DEBUGYES
              printf("allselASD:Valore del filtro =%d \n",alv->par_miniASD.filtro);
#endif
              i++;
              }
            else if(*arg != -2 && i== n_gerarchie+1)
              {
              alv->par_miniASD.punt=*arg;
#ifdef DEBUGYES
              printf("allselASD:Valore del punt=%d \n",alv->par_miniASD.punt);
#endif
              i++;
              }
            else if(*arg != -2 && i== n_gerarchie+2)
              {
              alv->par_miniASD.ext=(char)(*arg);
#ifdef DEBUGYES
              printf("allselASD:Valore di ext =%d \n",alv->par_miniASD.ext);
#endif
              i++;
              }
            else if(*arg != -2 && i== n_gerarchie+3)
              {
              alv->par_miniASD.ertr=(unsigned char)(*arg);
#ifdef DEBUGYES
              printf("allselASD:Valore di ertr =%d \n",alv->par_miniASD.ertr);
#endif
              i++;
              }
/******
            else if(*arg != -2 && i== n_gerarchie+4)
              {
              alv->par_miniASD.giorno=(unsigned char)(*arg);
#ifdef DEBUGYES
              printf("allselASD:Valore di giorno =%d \n",alv->par_miniASD.giorno);
#endif
              i++;
              }
******/
            else if(*arg != -2 && i== n_gerarchie+4)
              {
              alv->par_miniASD.ore=(unsigned char)(*arg);
#ifdef DEBUGYES
              printf("allselASD:Valore di ore =%d \n",alv->par_miniASD.ore);
#endif
              i++;
              }
            else if(*arg != -2 && i== n_gerarchie+5)
              {
              alv->par_miniASD.minuti=(unsigned char)(*arg);
#ifdef DEBUGYES
              printf("allselASD:Valore di minuti =%d \n",alv->par_miniASD.minuti);
#endif
              i++;
              }
            else if(*arg != -2 && i== n_gerarchie+6)
              {
              alv->par_miniASD.secondi=(unsigned char)(*arg);
#ifdef DEBUGYES
              printf("allselASD:Valore di secondi =%d \n",alv->par_miniASD.secondi);
#endif
              i++;
              }

   	   arg++; 
     
       } /* end for */
}
/*
   verifico che la pagina allarmi non sia gia' presente su altri
   video con lo stesso tipo di selezione

N.B. Verificare se occorre fare controllo su altre miniASD

*/
ali=&bDbsAlv[0];
for(i=0;i<num_video;i++,ali++)
{
   if(i == (video-1)) continue;
   if(tstv[i].tsv[zonai].v_tipo != p_al && tstv[i].tsv[zonai].v_tipo != p_ar) continue;
   if((ali->pal) == mess->dbs-1 && 
      ((ali->mask1 & mask[0]) || (ali->mask2 & mask[1])))
         { 
#ifdef DEBUGYES
         printf("Trovata altra pag allarmi con zona aperta su video=%d\n",i);
#endif
         return(-1);
         }
}
alv->par_miniASD.db=(mess->dbs)-1;             // data base selezionato
alv->par_miniASD.tipo_operazione=mess->pric;    /* tipo di operazione */
alv->par_miniASD.tipo=mess->tipo;    /* tipo di filtraggio */
#ifdef DEBUGYES
printf("mess->tipo=%d\n",mess->tipo);
#endif
/*
Occorre a questo punto testare la operazione richiesta 
Se la operazione e' di ric. singolo occorre leggere i parametri
dell 'allarme da riconoscere ed inserirli nella strttura algv
*/
alv->par_miniASD.lock=1;
#ifdef DEBUGYES
printf("mess->pric=%d\n",mess->pric);
#endif
return(mess->pric);
}




