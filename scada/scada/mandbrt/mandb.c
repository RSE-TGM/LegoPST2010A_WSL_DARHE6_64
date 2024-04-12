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
        il main mandb visualizza i dati delle misure
        in data base di qualsiasi tipo chiamando le
        opportune routines
*/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "ansiscr.h"
#include "ctasti.inc"

#define _PUBLIC 0

#include "mandb.inc"
#include "tabelle.inc"

mandb() 
{
#define TIM_OUT	20				/* valore del time out che determina la 
											frequenza di refresh dei valori
											visualizzati			*/
short point;
short ext ;
long blocco;
short posiz ;
short mess ;
short com=1,i;
short ier, letti ;
short indice ,j ;
short t_out;
char *p1,*p2;
short time_out=5 ;
#define lun_nome 10
union nom  { char c[lun_nome+1];
            short s[lun_nome/2];} nome ;
short vetchar[3];       /* tabella caratteristiche linea */
short savechar  ;        /* salvo vecchia configurazione  */
short indir ;
short riscrivi ;
/*
        intestazione. 
*/
clrscr();
/*
        preparo pagina video in cui inserire i 4
        punti del data base di sistema
*/
riscrivi=0 ;
scrxy(21,1);
printf("%s",istruzione) ;
/*
        inizializzo tabella
*/
for(i=0;i<num_punti;i++)
    {
    vispun.punt[i]=-1;
    vispun.ext[i]=255;
    n_elem[i]=0;
    }

for(i=1,indice=0;i<num_righe*num_punti;i=i+num_righe,indice++)
	{       
RIPROVA :
   scrxy(i,1);
	deleol() ;
   nome_punto[0]=indice+1+48;
	printf("%s",nome_punto);
/*
        chiedo il nome del punto e definisco il tipo
*/
    nome.c[0]=0;
    letti=rdpb(15,i,&nome.c[0],lun_nome,0);
    if(letti==0 || letti==-1)
     	{
	   scrxy(i,1);
		deleol() ;
     	goto VISUAL;
     	}
    else
     	{       
/*
     verifico che sia installato
*/
		while(letti<lun_nome) nome.c[letti++]=0; 
      ier=ricerca(&nome.s[0],&point,&ext,&blocco,&posiz,fpp[fnomi]);
      if(ier)     goto RIPROVA ;					
      vispun.punt[indice]=point ;
      vispun.ext[indice]=ext;
      switch (vispun.ext[indice])
         {
         case g1tipaa:  case g1tipac: case g1tipas:
         case g1tipad :  case g1tipao :  /* analogico  */
           intestan(indice,point,ext);					 
           break;
         case g1tipda:  case g1tipdc: case g1tipds:
         case g1tipdd :  case g1tipdo :  /* digitale   */
           intestdi(indice,point,ext) ;			 
           break ;
         case g1tipor :
           intestor(indice,point) ;						 
           break ;
			case g1tipst  :
			  intestst(indice,point);
		  	  break;
         }
      }
	}
/*
	Visualizza valori e flag del punto prescelto.
*/
VISUAL :
if(vispun.punt[0]==-1)  return(0);     /* nessuna misura inserita : termina */
for(j=0;j<num_punti;j++)
   {
   switch (vispun.ext[j])
     {
        case g1tipaa:  case g1tipac: case g1tipas:  case g1tipad:
        case g1tipao :
           aggiornan(j);       /* analogici */
           break;
        case g1tipda:  case g1tipdc: case g1tipds:  case g1tipdd:
        case g1tipdo :
           aggiorndi(j);       /* digitali  */
           break ;
   	  case g1tipor :
            aggiornor(j) ;     
            break ;
		  case g1tipst :
			   aggiornst(j) ;
	    }
  }
/*
	Pulisce la parte bassa dello schermo e chiede se si vuole la modifica
	di uno dei punti visualizzati o l'uscita dal mandb.
 */
if(!riscrivi)
	{
   scrxy(21,1);
	deleol() ;
   scrxy(22,1);
	deleol() ;
   scrxy(23,1);
	deleol() ;
   scrxy(21,1);
   printf("%s",operazioni);
	}
riscrivi=1 ;
/*
	attesa con time out alla mailbox di comunicazione con fine:
	fine attende che venga premuto un tasto ed invia il corrispondente
	codice ascii a mandb. Se il tasto non viene premuto entro il time out
	mandb prosegue con la visualizzazione dei valori e flag dei punti
	richiesti.
*/
t_out=getkey_wait(TIM_OUT,&mess,&ier);	
if(t_out) goto VISUAL;	/* se Š scattato il time out va a VISUAL */
if(mess==ESC) return(0);  /* escape --> uscita */
riscrivi=0 ;
nome.c[0]=0 ;
NON_ACCET :
/*
	Richiede quale misura si vuole modificare.
*/
do
	{    
   scrxy(22,1);
	deleol() ;
   scrxy(22,1);
	printf("%s",quale_misura);
   letti=rdpb(36,22,nome.c,1,0);
   }
while( nome.c[0]>'4' || nome.c[0]<'1');
if(vispun.punt[nome.c[0]-49]==-1)
   {
   nome.c[0]=0;
   goto NON_ACCET;
   }
scrxy(22,1);
/*
	richiama l'opportuna routine di modifica punto a seconda del tipo del
	punto specificato.
*/
switch(vispun.ext[nome.c[0]-49])
        {
/*              analogici               */
        case g1tipaa:  case g1tipas: case g1tipac: case g1tipad: case g1tipao:
          modfan(vispun.ext[nome.c[0]-49],vispun.punt[nome.c[0]-49]);	 
          break;
/*              digitali                */
        case g1tipda:  case g1tipdc: case g1tipds:  case g1tipdd: case g1tipdo:
          modfdi(vispun.ext[nome.c[0]-49],vispun.punt[nome.c[0]-49]) ;	 
          break ;
/*					 organi						 */
        case g1tipor:
          modfor(vispun.punt[nome.c[0]-49]) ;	  
          break ;
/*					 stringhe						 */
        case g1tipst:
          modfst(vispun.punt[nome.c[0]-49]) ;	  
          break ;
        }
goto VISUAL ;
}


