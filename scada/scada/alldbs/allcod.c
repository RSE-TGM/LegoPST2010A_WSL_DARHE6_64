/**********************************************************************
*
*       C Source:               allcod.c
*       Subsystem:              1
*       Description:
*       %created_by:    carlo %
*       %date_created:  Thu Mar  2 11:58:04 2006 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: allcod.c-6_deb1.1.2 %  (%full_filespec: allcod.c-6_deb1.1.2:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*

   Allcod.c

   Prepara la stringa allarmi a partire da un elemnto del data base allarmi

   Parametri

   flag  short    =1 visualizzare allarmi da riconoscere (Vdeal)
                  =0 visualizzare allarmi in archivio (Vdeal)
                  =2 aggiornamento parziale (Vpaal)
      		      =3 visualizzare allarmi da riconoscere 
                     (ricopiatura senza clear) (Vdeal)
                  =4 movimento in pagina allarmi di 8 allarmi alla volta

   S_STRALL       *str  buffer in cui inserire la codifica

   struct buff_all * all   pacchetto allarmi da decodificare

   Ritorno

      nessuno
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "pscserr.inc"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include "messcada.inc"
#include	"mesqueue.h"
#include "allar.inc"
#include "diagnodi.inc"
#include "tipal.inc"

// External function declarations
extern int rbyte(int, char *, long, int);
extern void pscserr(int, int, int, int, int);
extern int IsAlarmSignal(short);
extern int GetAlarmValue(short);
extern void decnum(char *, short, short, short, float);


int allcod (flag, str, all)
short flag;
S_STRALL *str;
struct buff_all *all;
{
short stato;
short ier;
long tot ;
char desc[rec_fdda] ;  			/* buffer per leggere dai file descrittori */
short trat,ind_colore;
char valore[16];	// stringa di appoggio del valore corrente della misura analogica

/*
        dimensione record file descrittori e offset relativi 
		 (sono inizializzati e definiti nel main )
*/
extern long  off_f[] ;     	/* definiti nel main mpscs */
extern short nbyte[] ;     	/* come sopra */

short ptipo,pdata ;
short atipo;

float vsoglia() ;

/*
Puntatori per elaborazione descrizione
Eliminazione kks con |
*/
char *kks;
int jj,ii;

/*      
        recupero tipo di punto e puntatore
*/
pdata=all->m.punt ;
ptipo=(short)all->m.ext ;
str->lun=sizeof(S_STRALL) ;
memset(str->desc,' ',sizeof(str->desc));
/*
        leggo dal file descrittore le caratteristiche del punto
        posizionandomi con fseek
*/
tot=off_f[ptipo]+(long)nbyte[ptipo]*(long)pdata;
if(rbyte(fileno(fpp[fdde]),(char*)desc,tot,nbyte[ptipo])==-1)
            pscserr(ERR_IO,TASK_ALLARMI,ROU_ALLDEC,pdata,SYS_CONT);
/*
        copio nome punto descrizione nel buffer allarmi
        e codifica ascii del tipo di allarme
*/
strncpy(&str->desc[0],desc,SCD_SIGLA) ;
strncpy(&str->desc[SCD_SIGLA+1],&desc[SCD_SIGLA],SCD_DESCRIZIONE_ALL);
/*
printf("Descr all 1afase==%.*s\n",26+SCD_SIGLA+SCD_DESCRIZIONE_ALL,str->desc);
*/
/*
Inserisco elaborazione per evitare di inserire nella descr dello
allarme il KKS.
*/

for(ii=0;ii<2;ii++)
   {
   kks=strstr(str->desc,KKSCODE);
   if(kks)
       {
       for(jj=0;jj<strlen(KKSCODE)-1;jj++)
          {
          *kks++=' ';
          }
       *kks=SEPARATORCODE;
       }
   }
/*
printf("Descr dopo modifica==%.*s\n",26+SCD_SIGLA+SCD_DESCRIZIONE_ALL,str->desc);
*/
trat=all->m.ertr & M_TRALL;
ind_colore=( (all->m.ertr & M_SEALL) >> 4);
if(all->m.ertr & 0x80 )              // emissione
{
   atipo=EMISSIONE;  stato=all->m.satt & 0x7F; str->emission=atipo;
}
else                                // rientro
{
   atipo=RIENTRO;  stato=all->m.sprec ;   str->emission=atipo;
}
if(all->mask& 0x8000) /* all di tipo ARC */
	{
	str->emission=RICONOSCIUTO;          /* stato di archiviazione */
	} 
#if defined ALARM_SIGNAL
if(ptipo == g1tipda)    /*  dig. acq */
	if(IsAlarmSignal(pdata))
		{
		stato = GetAlarmValue(pdata) + max_st_no_sig;
		atipo = !atipo;
		}
#endif
/*
Modifiche per visualizzazione Teleperm
*/
/*******
strncpy(&str->desc[SCD_SIGLA+SCD_DESCRIZIONE_ALL+2],
			stringhe[stato+atipo*max_st],8) ;
********/
/*
printf("Descr all 2afase==%.*s\n",26+SCD_SIGLA+SCD_DESCRIZIONE_ALL,str->desc);
*/
/*
        inserisco asterisco colori e ora
*/
str->spare=0;
str->pont=0;		
str->aster='*' ;
#if defined ALARM_SIGNAL
/*
	i digitali di tipo segnale inviano al posto dell'asterisco il
	carattere corrispondente al segnale allarme
*/
if(ptipo == g1tipda)    /*  dig. acq */
	if(IsAlarmSignal(pdata))
		str->aster=GetAlarmValue(pdata)+'A';
#endif

// CARLO 03/02/06
switch (ptipo)
{
   case g1tipaa:   /*  an acq */
   case g1tipas :   /*  an calc st */
   case g1tipac :   /*  an calc non st */
   case g1tipad :   /*  an di diagnostica*/
      printf("\n\n **** DEBUG CARLO: all->m.sogl1=%x\n\n",all->m.sogl1);
      if(all->m.sogl1 != 255)
      {
         // msogl1  0 o 1 superate hs o ls
         //         2 o 3 superate hc o lc
         if( all->m.sogl1==0 || all->m.sogl1 ==1 )
            str->aster='A';
         else
            str->aster='W';
      }
   break;
}

if(all->m.satt & 0x80)
{
   str->colorast=color[all->m.sprec][ind_colore]<<4 ;
   if(flag) str->colorast=str->colorast+8 ;		   // pag. all. blink
   str->colorstr=color[all->m.satt & 0x7F][ind_colore]<<4;
}
else
{
   str->colorast=color[all->m.sprec][ind_colore] ;
   if(flag) str->colorast=str->colorast+8 ;		   // pag. all. blink
   str->colorstr=color[all->m.satt][ind_colore];
#if defined ALARM_SIGNAL
if(ptipo == g1tipda)    /*  dig. acq */
	if(IsAlarmSignal(pdata))
		{
		char sprec = all->m.sprec;
		char satt = all->m.satt;

		if(satt==var_dig)
			satt = GetAlarmValue(pdata) + max_st_no_sig;	
		if(sprec==var_dig)
			sprec = GetAlarmValue(pdata) + max_st_no_sig;	

   		str->colorast=color[sprec][ind_colore] ;
   		if(flag) str->colorast=str->colorast+8 ;		
   		str->colorstr=color[satt][ind_colore];
		}
#endif
}
if(SEC_FORMAT)
{
#ifdef FABIO
printf("SEC_FORMAT:ore=%d\n",all->ore);
printf("SEC_FORMAT:minuti=%d\n",all->minuti);
printf("SEC_FORMAT:secondi=%d\n",all->secondi);
#endif
decnum(&str->data[0],2,-2,all->ore,0.) ;
str->data[2]=':';
decnum(&str->data[3],2,-2,all->minuti,0.) ;
str->data[5]=':';
decnum(&str->data[6],2,-2,all->secondi,0.);
str->data[8]=' ';
}
else
{
#ifdef FABIO
printf(":giorno=%d\n",all->giorno);
printf("SEC_FORMAT:minuti=%d\n",all->minuti);
printf("SEC_FORMAT:secondi=%d\n",all->secondi);
#endif
decnum(&str->data[0],2,-1,all->giorno,0.) ;
str->data[2]=' ';
decnum(&str->data[3],2,-1,all->ore,0.) ;
str->data[5]='-';
decnum(&str->data[6],2,-1,all->minuti,0.);
str->data[8]=' ';
}
/*
        inserisco le informazioni specifiche per ogni
        tipo di punto
*/
switch (ptipo)
{
   case g1tipaa:   /*  an acq */
   case g1tipas :   /*  an calc st */
   case g1tipac :   /*  an calc non st */
   case g1tipad :   /*  an di diagnostica*/
   case g1tipao :  /*  an di uscita */
      str->p.point=pdata;  /* puntatore ed estensione*/
      str->p.ext=(char)ptipo ;

     // stato allarme (p.es BASSO/ALTO/BAS.MO/ALT.MO)
     // recuperato dal vettore stringhe (fdesal.rtf)
      if(all->m.sogl1 != 255)
      {
	   /* CARLO 2/Marzo/2006 
              introduco stato allarme in chiaro 
	   */
	   strncpy(&str->desc[2+SCD_SIGLA+SCD_DESCRIZIONE_ALL],
			stringhe[stato+atipo*max_st],8) ;

      }
      // unità di misura
      strncpy(&str->desc[11+SCD_SIGLA+SCD_DESCRIZIONE_ALL],
			&desc[SCD_SIGLA+SCD_DESCRIZIONE],6);

      // valore della soglia superata
      if(all->m.sogl1 != 255)
      {

// limite di soglia
            decnum(&str->desc[18+SCD_SIGLA+SCD_DESCRIZIONE_ALL],
			8,2,0,vsoglia(pdata,ptipo,all->m.sogl1)) ;

	    // valore corrente misura
            // decnum(&str->desc[18+SCD_SIGLA+SCD_DESCRIZIONE_ALL],
            //			8,2,0,dbaav[all->m.punt]) ;

      }
      break;
   case g1tipda:   /*  dig. acq */
   case g1tipdc:  /*  dig  calc */
   case g1tipds :  /* dig cal n s */
   case g1tipdd :  /* dig diagn  */
      /**
      str->p.point=-2 ;
      str->p.ext=-2 ;
      **/
      /*
      ATTENZIONE !!!
      */
      /*
      Cambiamento per teleperm
      */
      str->p.point=pdata;  /* puntatore ed estensione*/
      str->p.ext=(char)ptipo ;
      str->p.tipo=all->m.ertr;
      if(all->m.sogl1 != 255)
      {
         atipo=all->m.sogl1 ;    /* stoto 0 stato 1 */
/*
Modifiche per visualizzazione Teleperm
*/
/********
         strncpy(&str->desc[11+SCD_SIGLA+SCD_DESCRIZIONE_ALL],
			&desc[SCD_SIGLA+SCD_DESCRIZIONE+atipo*8],8) ;
********/
/*
printf("Descr all atipo=%d 3afase==%.*s\n",atipo,26+SCD_SIGLA+SCD_DESCRIZIONE_ALL,str->desc);
*/
      }
      break ;
   case g1tipor :          /* organi          */
      str->p.point=-2;
      str->p.ext=-2 ;
      if(all->m.sogl1 != 255)
      {
         tot=nbyte[0]*all->m.sogl1 ;
         strncpy(&str->desc[11+SCD_SIGLA+SCD_DESCRIZIONE_ALL],
			&stat_diz[tot],lun_stato) ;
      }
      if(all->m.sogl2 != 255)
      {
         tot=nbyte[0]*all->m.sogl2 ;
         strncpy(&str->desc[18+SCD_SIGLA+SCD_DESCRIZIONE_ALL],
			&stat_diz[tot],lun_stato);
      }
      break ;
   case g1tipst :          /* stringhe          */
      str->p.point=-2;
      str->p.ext=-2 ;
      strncpy(&str->desc[11+SCD_SIGLA+SCD_DESCRIZIONE_ALL],
		&dbstv[pdata*g0lunst],g0lunst) ;
      break;
}
return(0) ;
}
