/**********************************************************************
*
*       C Source:               timeor.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Dec 16 14:15:18 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: timeor.c-3 %  (%full_filespec: timeor.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
/*
        la function timeor.c verifica se ci sono
        organi con timer inseriti
        -  li decrementa
        -  se sono arrivati a zero considera i seguenti
           casi :
           1.  settato il flag IT di variazione spontanea
               se lo stato attuale e' diverso da quello
               precedente emette l'allarme di variazione
               spontanea
           2.  settato il flag TA di protezione
               se lo stato attuale non e' uguale allo
               stato atteso emmette l'allarme di protezione
               fallita
           3.  settato il flag TC di comando
               se lo stato attuale non e' uguale allo
               stato attesa emette l'allarme di comando
               fallito
           aggiorna lo stato precedente con quello attuale
           se lo stato e' inibente provvede ad eseguire le
           inibizioni
*/

#include "comunic.inc"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "organi.inc"
#include "mesqueue.h"
#include "tipal.inc"
#include "messcada.inc"

/* Function prototypes */
extern void scd(void);
extern void sce(void);
extern void inibiz(short, short, short, short);

void timeor(inizio,fine)
short inizio, fine;       /* inizio e fine loop   */
{
#define st_trans 0
#define st_incon 1

short i,j,k ;
#if defined OSF1 || defined LINUX
int *ipoint ;           /* puntatore a int dei timer  */
#else
long *ipoint ;           /* puntatore a long dei timer  */
#endif
char *cpoint ;          /* puntatore a char dei timer */
struct punto_inibito *inib ;

char stato1,stato2 ;
short stato ;
short indice ;

S_DESORG *des ;
S_MALLA mess;
QUEUE_PACKET pack;
char flag;

pack.que = c_visall;
pack.flg = MSG_WAIT;
pack.wto = 0;
pack.amsg = (char *)  &mess;
pack.lmsg=sizeof(S_MALLA);

mess.ext=g1tipor;
ipoint=(int *)&dbto[inizio*4] ;               // esamino 4 organi alla volta
for (i=inizio ;i<fine ;i++,ipoint++)
{
/*
        controllo i timer degli organi 4 alla volta
        devono essere diversi da zero
*/
        if(*ipoint)
        {
/*
        passo ad esaminare i 4 elementi della word
*/
                cpoint=(char *) ipoint ;
                for(j=0;j<4;j++,cpoint++)
                {
                        if(*cpoint)
                        {
									scd();					 /* il decremento non deve essere interrotto */
                           *cpoint=(*cpoint)-1 ; /* decremento */
									sce();
									if(!(*cpoint))
                           {
/*
        timer scattato inizio l'esame dei vari flag
        in indice calcolo il puntatore dell'organo
*/
                                indice=i*4+j ;
                                des=&dbode[indice] ;
/*
        se scattato il timer lo stato dell'organo e' trans
        viene forzato ad incong.
*/
                                if((dbosc[indice] & 0x00FF)==
                                        st_trans)
                                dbosc[indice]=
                                (dbosc[indice] & 0xFF00)+st_incon;
										  mess.punt=indice;	
										  flag=dboft[indice] & (mask_ta | mask_tc) ;
										  if( (dboft[indice] & mask_ta) == mask_ta)
                                {
/*
        caso : protezione fallita
*/
                                stato1=(dbosc[indice] & 0x00FF) ;
                                stato2=dbosa[indice] ;
                                mess.ertr=(des->trat | 0x80) ;
                                if(stato1 != stato2)
										  {	
												mess.sogl1=stato1; mess.sogl2=stato2;
												mess.sprec=mis_norm; mess.satt=prot_fall;
												enqueue(&pack);
										  }
										  }
		                           if( (dboft[indice] & mask_tc) == mask_tc)
											{
/*
        caso : comando fallito o no 
*/
                                stato1=(dbosc[indice] & 0x00FF) ;
                                stato2=dbosa[indice] ;
                                mess.ertr=(des->trat | 0x80) ;
                                if(stato1 != stato2)
										  {												 
												mess.sogl1=stato1; mess.sogl2=stato2;
												mess.sprec=mis_norm; mess.satt=com_fall;
                                    enqueue(&pack);
										  }
										  }
                                if(( dboft[indice] & mask_it) == mask_it)
										  {	
/*
        caso : variazione spontanea
*/
                                stato1=(dbosc[indice] & 0x00FF) ;
                                stato2=dbosp[indice] ;
                                mess.ertr=(des->trat | 0x80) ;
                                if(stato1 != stato2 && stato2)
                                {
												mess.sogl1=stato1; mess.sogl2=stato2;
												mess.sprec=mis_norm; mess.satt=var_org;
                          			   if(!flag) enqueue(&pack);
                                }
      	                       if(des->stinib != -1 )
  		                          {
/*
        per ogni misura inibita chiamo la function
        inibiz in base allo stato dell`organo
*/
                                     if(stato1==des->stinib) stato=2;
                                     else   stato=4 ;
                                     inib= &des->pinib[0] ;
                                     for(k=0;k<or_inib;k++,inib++)
                                     {
                                            if(inib->ext==-1)break ;
                                            inibiz(inib->ext,inib->punt,
                                                  inib->tipin,stato) ;
                                      }
                               	}
										 }
/*
        resetto tabella dei flag
        pongo stato precedente = stato attuale
*/
                                dboft[indice]=0 ;
                                dbosp[indice]=stato1 ;
                              }
                        }
                }
        }
}
}
