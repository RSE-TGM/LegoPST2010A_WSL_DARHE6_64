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
#include <osf1.h>
#include <stdio.h>
#include <dos.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "diagnoan.inc"
#include "eqschpas.inc"
#include "stschpas.inc"
#include "comunic.inc"
#include "print.inc"
#include "switch.inc"
#include "pscserr.inc"
#define _PUBLIC 0
#include "defpub.h"
#include "cprint.inc"
/*
	cprint:	routine per la codifica dell'istruzione PRINT
			   del linguaggio POL

	in input riceve PC program counter
						 FP frame pointer
*/
extern  struct SCHEDULER *s_interp;
extern  struct SCB       *scb;

short* cprint(short *pc,short *fp)
{
short *dbs;
short ext, punt, lung, off, tipo;
long dist;
int j;

dbs=(short*)s_interp->buf_dbl;

pc++;							// in pc c'era il codice dell'istruzione print

PRINT:

switch (*pc)
{
case p_pag:             /* caso di salto pagina  */  
        ta.strprint[0]=0x0c;
		  ta.strprint[1]=0x00;
		  ta.hea.lung=sizeof(HEA_STA)+lstr_pag;
		  invia(tpr_tabulato,&ta) ;
        pc++ ;
        goto PRINT ;

case p_ret:             /* caso LF + CR */
		  ta.strprint[0]=0x0d;
		  ta.strprint[1]=0x0a;
		  ta.hea.lung=sizeof(HEA_STA)+lstr_ret;
		  invia(tpr_tabulato,&ta) ;
        pc++ ;
        goto PRINT ;

case p_stringa:         /* caso stringa */
		  pc++;					   // pc punta al numero di caratteri della stringa
        lunprint=*pc;	
		  pc++;
		  ta.hea.lung=sizeof(HEA_STA)+lunprint;
		  memcpy(ta.strprint,pc,lunprint);
		  invia(tpr_tabulato,&ta) ;
        pc=pc+(lunprint+1)/2 ;   // incremento della lunghezza della
													// della stringa
        goto PRINT ;
case p_tim1:            /* richiesta anno mese giorno */
if (INGLESE)
{
		  decnum(ta.strprint,2,-1,(short)dbadv[db_mese],0.);
		  strcpy(&ta.strprint[2]," - ");
		  decnum(&ta.strprint[5],2,-1,(short)dbadv[db_giorno],0.);
}
else
{
		  decnum(ta.strprint,2,-1,(short)dbadv[db_giorno],0.);
		  strcpy(&ta.strprint[2]," - ");
		  decnum(&ta.strprint[5],2,-1,(short)dbadv[db_mese],0.);
}
		  strcpy(&ta.strprint[7]," - ");
		  decnum(&ta.strprint[10],2,-1,(short)(dbadv[db_anno]-1900),0.);
  
		  ta.hea.lung=sizeof(HEA_STA)+lstr_tempo;
		  invia(tpr_tabulato,&ta) ;
        pc++ ;
        goto PRINT ;

case p_tim2:            /* richiesta ora minuti seco. */
   		  decnum(ta.strprint,2,-1,(short)dbadv[db_ora],0.);
	   	  strcpy(&ta.strprint[2]," - ");
		     decnum(&ta.strprint[5],2,-1,(short)dbadv[db_minuti],0.);
   		  strcpy(&ta.strprint[7]," - ");
	   	  decnum(&ta.strprint[10],2,-1,(short)dbadv[db_secondi],0.);

		  ta.hea.lung=sizeof(HEA_STA)+lstr_tempo;
		  invia(tpr_tabulato,&ta) ;
        pc++ ;
        goto PRINT ;

case p_spaces :					/* caso di spazi blank   */

		  pc++;					   // pc punta al numero di caratteri blank
        lunprint=*pc;	
		  memset(ta.strprint,0x20,lunprint);
		  ta.hea.lung=sizeof(HEA_STA)+lunprint;
		  invia(tpr_tabulato,&ta) ;
        pc++ ;
        goto PRINT ;

case p_format :
		  pc++;						// punta alla descrizione del formato
		  pform=(struct formato *)pc; 
		  pc++;
        i.s  =*pc ;      /* indirizzo variabile */
        if(i.re.indi) i.s= *(fp+(i.di.byad>>1)) ;
        u.s[0]=*(dbs+(i.re.byad>>1)) ;
        u.s[1]=*(dbs+(i.re.byad>>1)+1)  ;

//		  printf(" format tot.fraz con tot= %d   fraz=%d",pform->f.re.tot,pform->f.re.fraz);
//   	  printf(" tipo variabile= %d",pform->tipo);
//       printf(" indirizzo = %d ",(i.re.byad>>1)) ;
//        printf("\nvalore = %f ",u.f) ;
  		  
		  if(pform->tipo==treale || pform->tipo==tanalogico)
		  		{
		  		decnum(ta.strprint,pform->f.re.tot+1,pform->f.re.fraz,0,u.f);
	   		ta.hea.lung=sizeof(HEA_STA)+(pform->f.re.tot+1);
		      invia(tpr_tabulato,&ta) ;
				}
		  else if(pform->tipo==tstringa)		  // caso di tipo stringa
		  		{ 
				lunprint=pform->f.in;
				memset(ta.strprint,0x20,lunprint);
				if(diff=( pform->f.in - strlen(dbs+(i.re.byad>>1))) <=0 )
					memcpy(ta.strprint,dbs+(i.re.byad>>1),lunprint);
				else
            	strcpy(ta.strprint,(char*)dbs+(i.re.byad)) ;
				  ta.hea.lung=sizeof(HEA_STA)+lunprint;
	    		  invia(tpr_tabulato,&ta) ;
				}
		           // caso di tipo intero o organo
		  else 
		  		{
		  		decnum(ta.strprint,pform->f.in,-1,u.s[0],0.);
		      ta.hea.lung=sizeof(HEA_STA)+pform->f.in;
		      invia(tpr_tabulato,&ta) ;
		  		}
        pc++ ;
        goto PRINT ;
case p_dl:       /* stampa stato digitale o valore logico */
		  pc++;		// indirizzo variabile
        i.s  =*pc;  
        if(i.re.indi) i.s= *(fp+(i.di.byad>>1)) ;
        u.c[0]=*((char*)dbs+i.re.byad) ;
        if(u.c[0]&0x01) ta.strprint[0]='1' ;		// esamina il bit di stato
        else  ta.strprint[0]='0' ;
		  ta.hea.lung=sizeof(HEA_STA)+1;
		  invia(tpr_tabulato,&ta) ;
        pc++ ;
        goto PRINT ;

case p_cod:
        lung=SCD_SIGLA;   /* lunghezza ed offset  */
        off =po_nome;
        goto EXEC ;
case p_desc:
        lung=SCD_DESCRIZIONE ; off=po_desc ;
        goto EXEC ;
case p_umis:
        lung=pl_umis ;  off=po_umis ;
EXEC :
		  pc++;
        i.s=*pc ;
        tipo=(short)*(dbs+(i.re.byad>>1)) ;
        punt=(short)*(dbs+(i.re.byad>>1)+1) ;
		  dist=(long)nbyte[tipo]*(long)punt+(long)off_f[tipo]+(long)off; 	
        if(rbyte(fileno(fpp[fdde]),(short*)ta.strprint,dist,lung)==-1) 
		  		perror("\n Errore lettura descrittori ") ;
		  ta.hea.lung=sizeof(HEA_STA)+lung;
		  invia(tpr_tabulato,&ta) ;
		  pc++;
        goto PRINT ;
case p_org:                     /* stampo stato organo  */
		  pc++;
		  i.s=*pc;
        if(i.re.indi) i.s=*(fp+(i.di.byad>>1)) ;
/*
        lettura dalla tabella stat_diz
*/
        memcpy(ta.strprint,&stat_diz[lun_stato*(*((char*)dbs+i.re.byad))],
                lun_stato) ;
		  ta.hea.lung=sizeof(HEA_STA)+lun_stato;
		  invia(tpr_tabulato,&ta) ;
		  pc++;
        goto PRINT ;
case -1 :           /* tappo finale */
        pc++ ;
        break;
case p_sgraf:           /* recupero coefficienti */
		  pc++;
        u.s[0]=*pc ; 	// limite basso
		  pc++;	
        u.s[1]=*pc ; 	// limite basso
		  coeff_mol=100./(u.s[1]-u.s[0]);  // coefficiente moltiplicativo
		  coeff_add=-u.s[0]*coeff_mol;	  // coefficiente additivo
        pc++ ;
        goto PRINT ;
case p_graf :
		  pc++;
        numgrafv=*pc ; 	// limite basso
        off=coeff_add;
        memset(ta.strprint,' ',100) ;    /* riempio di blank */
        ta.strprint[0]=ta.strprint[99]=':';  /* limiti grafico */
        if(off >= 0) ta.strprint[off]='I'; /* zero del grafico */
//		  printf("\n numero di variabili grafiche = %d",numgrafv);
        for (j=0;j<numgrafv;j++)
		  	{
				pc++;
	         i.s=*pc ; 	
            u.s[0]=*(dbs+(i.re.byad>>1)) ;
            u.s[1]=*(dbs+(i.re.byad>>1)+1) ;
            off=u.f*coeff_mol+coeff_add ;    /* valore grafico */
            if(off<0) off=0 ;
            if(off>100) off=100 ;        /* limiti massimi */
            ta.strprint[off]=j+1+0x30 ;       /* n. mis.in ascii*/
        	}
        pc++ ;
		  ta.hea.lung=sizeof(HEA_STA)+100;
		  invia(tpr_tabulato,&ta) ;
        goto PRINT ;
default :
        pscserr(ERR_TASK,TASK_TABUL,ROU_CPRINT,*pc,SYS_CONT);
        pc++ ;
        break ;
}
return(pc);
}


