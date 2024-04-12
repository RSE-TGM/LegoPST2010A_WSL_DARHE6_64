/**********************************************************************
*
*       C Source:               interpol.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Jun 17 17:51:42 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: interpol.c-3 %  (%full_filespec: interpol.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*	->INTERP.C
        la function interp procede all'esecuzione delle
        istruzione dell linguaggio P.O.L.

        viene passata in input la struttura che fornisce
        i puntatori al database locale, al codice e allo
        stack insieme al frame pointer e stack pointer
*/

#include <osf1.h>
#include <math.h>
#include <stdio.h>
#include <malloc.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "fileop.inc"
#include "comunic.inc"
#include "opcode.inc"
#include "interpol.inc"
#include "diagnoan.inc"
#include "pscserr.inc"
#include "print.inc"
#include "dconf.inc"
#include "fio.h"
#include "tag.h"
#include "cprint.inc"


union u_indirizzi IndDir(S_INTERP* s, union u_indirizzi ind, long *fp, short** dbs, char** dbc);
void BuildFPOLName(char *str,short n);

interp(s)
S_INTERP *s ;
{
union u_indirizzi  i,i2,i3 ;    /* indirizzi */
short pa ;
long dist,*fp ;
short vint1,vint2 ;
short *pint,*pint2,*pint3 ;
char *p1,*pcha,*pcha2,*pcha3,*pch;
int lung,punt,j,tipo,off;
short indbit,*stk;              /* indice bit e puntatore short per lo stack */
short disp;

union u_val {   float   f;
                long    l ;
                short   s[2];
                char    c[6] ;
            } u ,u2,u3 ;

short *dbs;
char *dbc;
char str[FILENAME_MAX+1];
FILE *file;

/* Inizializzazioni frame pointer stack pointer e pseudo accumulatore */
pa=0;   
fp=s->stk ;

for(;;)
{

/* primo svincolo per risolvere gli indirizzi ed estrarre
   dal data base i valori necessari                       */
switch (*(s->pc))
{
case c_ifgei: case c_ifgti: case c_iflei: /* 2 variabili */
case c_ifeqi: case c_ifnei: case c_iflti: /* intere od organi */
case c_ifeqs: case c_ifnes:               /* o stringhe           */

        /* prima variabile */
        i.s  =*(s->pc+2) ; /* indirizzo variabile */
        i=IndDir(s, i, fp, &dbs, &dbc);
        if(i.re.biad==b_organo) vint1=*(dbc+i.re.byad) ;
        else vint1=*(dbs+(i.re.byad>>1)) ;
	pcha=dbc+i.re.byad;
        
	/* seconda variabile */
        i.s  =*(s->pc+3) ; /* indirizzo variabile */
        i=IndDir(s, i, fp, &dbs, &dbc);
        if(i.re.biad==b_organo) vint2=*(dbc+i.re.byad) ;
        else vint2=*(dbs+(i.re.byad>>1)) ;
	pcha2=dbc+i.re.byad;
        break ;

case c_ifgef: case c_ifgtf: case c_iflef: /* 2 variabili */
case c_ifeqf: case c_ifnef: case c_ifltf: /* floating o reali */

        /* prima variabile */
        i.s  =*(s->pc+2) ;      /* indirizzo variabile */
        i=IndDir(s, i, fp, &dbs, &dbc) ;
        u.s[0]=*(dbs+(i.re.byad>>1)) ;
        u.s[1]=*(dbs+(i.re.byad>>1)+1) ;

	/* seconda variabile */
        i.s  =*(s->pc+3) ;      /* indirizzo variabile */
        i=IndDir(s, i, fp, &dbs, &dbc) ;
        u2.s[0]=*(dbs+(i.re.byad>>1)) ;
        u2.s[1]=*(dbs+(i.re.byad>>1)+1) ;
        break ;

case c_load:  case c_loadn: case c_sto:   case c_ston:
case c_set :  case c_clr  : case c_or :   case c_orn :
case c_and :  case c_andn : case c_seta:  case c_clra:
case c_xor :

        i.s=*(s->pc+1) ;        /* indirizzo variabile  */
        if(i.re.indi) {indbit=15+i.dd.biad ;
                       i.s=*(fp-(i.dd.byad>>1))+i.dd.disp ;
                      }
        else    indbit=15+i.re.biad ;
        pcha  = s->dbc+i.re.byad ;
        u.c[0]=*pcha ;
        break ;

case c_muli:  case c_divi:  case c_sumi:  case c_subi:  case c_sums:
case c_mulf:  case c_divf:  case c_sumf:  case c_subf:
case c_potf:  case c_stncat:

        i3.s  =*(s->pc+3) ;     /* indirizzo variabile 3 arg.*/
        i3=IndDir(s, i3, fp, &dbs, &dbc) ;
        pint3=dbs+(i3.re.byad>>1) ;
	pcha3=dbc+i3.re.byad;

case c_mfix:  case c_mfloat:    /* recupero secondo argomento   */
case c_absf:  case c_absi  :  case c_negf :  case c_negi :
case c_sqrt:  case c_log   :  case c_exp :   case c_ln :
case c_exp10: case c_sin :    case c_cos :
case c_movi:  case c_movf: case c_movs:
case c_arctan:  case c_arccos:  case c_arcsin:  case c_tan:
case c_stleng:

        i2.s  =*(s->pc+2) ;     /* indirizzo variabile 2 arg  */
        i2= IndDir(s, i2, fp, &dbs, &dbc) ;
        pint2=dbs+(i2.re.byad>>1) ;
        pcha2=dbc+i2.re.byad;

case c_pushi: case c_stoi: case c_popi: case c_loadi: case c_imovi:
case c_clri: case c_ipusha: case c_pushf: case c_stof: case c_popf:
case c_loadf: case c_imovf: case c_clrf: case c_fdelete:
case c_imovs:

        /* in questi casi serve solo trovare l'indirizzo in dbl
        recupero primo argomento                                */
        i.s  =*(s->pc+1) ; /* indirizzo variabile */
        i=IndDir(s, i, fp, &dbs, &dbc) ;
        pint=dbs+(i.re.byad>>1) ;
        pcha=dbc+i.re.byad ;
        break ;
}

switch (*(s->pc))
{
case c_jump:
//printf("[interpol.c] c_jump\n");
        s->pc=s->inc+*(s->pc+1) ;
	break;
case c_nop:
//printf("[interpol.c] c_nop\n");
        s->pc=s->pc+c_nop ;
	break;
case c_ifaz:
//printf("[interpol.c]  c_nop\n");
        if(!pa) s->pc=s->pc+l_ifaz ;
        else    s->pc=s->inc+(*(s->pc+1)) ;
	break;
case c_ifan:
//printf("[interpol.c]  c_ifan\n");
        if(pa) s->pc=s->pc+l_ifan ;
        else   s->pc=s->inc+(*(s->pc+1)) ;
	break;
case c_ifgei:
//printf("[interpol.c]  c_ifgei\n");
        if(vint1 >= vint2) s->pc=s->pc+l_ifgei ;
        else               s->pc=s->inc+(*(s->pc+1)) ;
	break;
case c_ifgti:
//printf("[interpol.c]  c_ifgti\n");
        if(vint1 >  vint2) s->pc=s->pc+l_ifgti ;
        else               s->pc=s->inc+(*(s->pc+1)) ;
	break;
case c_iflei:
//printf("[interpol.c]  c_iflei\n");
        if(vint1 <= vint2) s->pc=s->pc+l_iflei ;
        else               s->pc=s->inc+(*(s->pc+1)) ;
	break;
case c_iflti:
//printf("[interpol.c]  c_iflti\n");
        if(vint1 <  vint2) s->pc=s->pc+l_iflti ;
        else               s->pc=s->inc+(*(s->pc+1)) ;
	break;
case c_ifeqi:
//printf("[interpol.c]  c_ifeqi\n");
        if(vint1 == vint2) s->pc=s->pc+l_ifeqi ;
        else               s->pc=s->inc+(*(s->pc+1)) ;
	break;
case c_ifnei:
//printf("[interpol.c]  c_ifnei\n");
        if(vint1 != vint2) s->pc=s->pc+l_ifnei ;
        else               s->pc=s->inc+(*(s->pc+1)) ;
	break;
case c_ifgef:
//printf("[interpol.c]  c_ifgef\n");
        if(u.f  >= u2.f ) s->pc=s->pc+l_ifgef ;
        else               s->pc=s->inc+(*(s->pc+1)) ;
	break;
case c_ifgtf:
//printf("[interpol.c]  c_ifgtf\n");
        if(u.f  >  u2.f ) s->pc=s->pc+l_ifgtf ;
        else               s->pc=s->inc+(*(s->pc+1)) ;
	break;
case c_iflef:
//printf("[interpol.c]  c_iflef\n");
        if(u.f  <= u2.f ) s->pc=s->pc+l_iflef ;
        else               s->pc=s->inc+(*(s->pc+1)) ;
	break;
case c_ifltf:
//printf("[interpol.c]  c_ifltf\n");
        if(u.f  <  u2.f ) s->pc=s->pc+l_ifltf ;
        else               s->pc=s->inc+(*(s->pc+1)) ;
	break;
case c_ifeqf:
//printf("[interpol.c]  c_ifeqf\n");
        if(u.f  == u2.f ) s->pc=s->pc+l_ifeqf ;
        else               s->pc=s->inc+(*(s->pc+1)) ;
	break;
case c_ifeqs:
//printf("[interpol.c]  c_ifeqs\n");
        if(!strcmp(pcha,pcha2)) s->pc=s->pc+l_ifeqs;
        else               s->pc=s->inc+(*(s->pc+1));
        break;
case c_ifnes:
//printf("[interpol.c]  c_ifnes\n");
        if(strcmp(pcha,pcha2)) s->pc=s->pc+l_ifnes;
        else               s->pc=s->inc+(*(s->pc+1));
        break;
case c_ifnef:
//printf("[interpol.c]  c_ifnef\n");
        if(u.f  != u2.f ) s->pc=s->pc+l_ifnef ;
        else               s->pc=s->inc+(*(s->pc+1)) ;
	break;
case c_gosub:
//printf("[interpol.c]  c_gosub %x\n",*(s->pc+2));
        *(s->stk)=(long)(s->pc+2) ;     /* salvo indirizzo di ritorno nello stack */
        if(s->stk < s->sfine) s->stk++; 
        else
	{
		printf("[gosub] *** stack overflow *** ");
		return;
	}
        s->pc=s->inc+*(s->pc+1);  	/* indirizzo subroutine */
	break;
case c_load :
//printf("[interpol.c]  c_load\n");
        pa=bitvalue(u.s,indbit) ;
        s->pc=s->pc+l_load ;
	break;
case c_loadn :
//printf("[interpol.c]  c_loadn\n");
        pa= ! bitvalue(u.s,indbit) ;
        s->pc=s->pc+l_loadn ;
	break;
case c_sto:
//printf("[interpol.c]  c_sto\n");
        bitset(u.s,indbit,pa) ;
        s->pc=s->pc+l_sto ;
        *pcha=u.c[0] ;
	break;
case c_ston:
//printf("[interpol.c]  c_ston\n");
        bitset(u.s,indbit,!pa) ;
        s->pc=s->pc+l_ston ;
        *pcha=u.c[0] ;
	break;
case c_set:
//printf("[interpol.c]  c_set\n");
        bitset(u.s,indbit,1) ;
        s->pc=s->pc+l_set ;
        *pcha=u.c[0] ;
	break;
case c_clr :
//printf("[interpol.c]  c_clr\n");
        bitset(u.s,indbit,0) ;
        s->pc=s->pc+l_clr ;
        *pcha=u.c[0] ;
	break;
case c_or :
//printf("[interpol.c]  c_or\n");
        pa= pa | bitvalue(u.s,indbit) ;
        s->pc=s->pc+l_or ;
	break;
case c_orn :
//printf("[interpol.c]  c_orn\n");
        pa= pa | (!bitvalue(u.s,indbit)) ;
        s->pc=s->pc+l_orn ;
	break;
case c_and:
//printf("[interpol.c]  c_and\n");
        pa= pa & bitvalue(u.s,indbit) ;
        s->pc=s->pc+l_or ;
	break;
case c_andn:
//printf("[interpol.c]  c_andn\n");
        pa= pa & (!bitvalue(u.s,indbit)) ;
        s->pc=s->pc+l_orn ;
	break;
case c_seta :
//printf("[interpol.c]  c_seta\n");
        pa=1 ;
        s->pc=s->pc+l_seta ;
	break;
case c_clra :
//printf("[interpol.c]  c_clra\n");
        pa=0 ;
        s->pc=s->pc+l_clra ;
	break;
case c_xor:
//printf("[interpol.c]  c_xor\n");
        pa= pa ^ bitvalue(u.s,indbit) ;
        s->pc=s->pc+l_xor ;
	break;
case c_term :
//printf("[interpol.c]  c_term\n");
        s->pc=s->pc+l_term ;
        return ;
case c_ret  :                   /* riprendo dallo stack l'indi */
        s->stk-- ;              /* rizzo di ritorno            */
        s->pc=(short *)(*(s->stk)) ;
//printf("[interpol.c]  c_ret pc=%x\n",*(s->pc));
	break;
case c_pushi :                  /* inserisco in stack intero */
//printf("[interpol.c]  c_pushi\n");
        *(s->stk)=*pint ;       /* prelevato da dbl          */
        if(s->stk < s->sfine) s->stk++ ;
        else
	{
		printf("[pushi] *** stack overflow *** ");
		return;
	}
        s->pc=s->pc+l_pushi ;
	break;
case c_pushf :
//printf("[interpol.c]  c_pushf\n");
        stk=(short *)s->stk ;			/* da word a hword */
        *stk = *pint; *(stk+1)=*(pint+1);  	/* inserisco float */
        if(s->stk < s->sfine) s->stk++ ;  	/* prelevato da dbl */
        else
	{
		printf("[pushf] *** stack overflow *** ");
		return;
	}
        s->pc=s->pc+l_pushf ;
	break;
case c_ipushi :
//printf("[interpol.c]  c_ipushi\n");
        *(s->stk)=*(s->pc+1) ;  		/* inserisco valore immediato */
        if(s->stk < s->sfine) s->stk++ ;
        else
	{
		printf("[ipushi] *** stack overflow *** ");
		return;
	}
        s->pc=s->pc+l_ipushi ;
	break;
case c_ipushf :                 		/* inserisco float immediato */
//printf("[interpol.c]  c_ipushf\n");
        stk=(short *)s->stk ;    		/* da word a hword */
        *stk = *(s->pc+1) ; *(stk+1) =  *(s->pc+2) ;
        if(s->stk < s->sfine) s->stk++ ;
        else
	{
		printf("[ipushf] *** stack overflow *** ");
		return;
	}
        s->pc=s->pc+l_ipushf ;
	break;
case c_popi :                   		/* prelevo dallo stack  val. intero */
//printf("[interpol.c]  c_popi\n");
        if(s->stk > s->siniz) s->stk-- ;
        else
	{
		printf("[popi] *** stack underflow *** ");
		return;
	}
        *pint=*(s->stk) ;
        s->pc=s->pc+l_popi ;
	break;
case c_popf :                   		/* prelevo dallo stack val. float */
//printf("[interpol.c]  c_popf\n");
        if(s->stk > s->siniz) s->stk-- ;
        else
	{
		printf("[popf] *** stack underflow *** ");
		return;
	}
        stk=(short *)s->stk ;            	/* da word a hword */
        *pint = *stk ;  *(pint+1)=*(stk+1) ;
        s->pc=s->pc+l_popf ;
	break;
case c_loadi :                  	/* prelevo intero senza toccare stk */
//printf("[interpol.c]  c_loadi\n");
        *pint=*(s->stk-1) ;
        s->pc=s->pc+l_loadi ;
	break;
case c_loadf :                  	/* prelevo float senza toccare stk */
//printf("[interpol.c]  c_loadf\n");
        stk=(short *)(s->stk-1) ;       /* da word a hword */
        *(pint)=*(stk) ;
        *(pint+1)= *(stk+1) ;
        s->pc=s->pc+l_loadf ;
	break;
case c_stoi :
//printf("[interpol.c]  c_stoi\n");
        *(s->stk-1)=*pint ;     	/* inserisco intero senza mod. stk */
        s->pc=s->pc+l_stoi ;
	break;
case c_stof :                   	/* inserisco float senza mod. stk */
//printf("[interpol.c]  c_stof\n");
        stk=(short *)(s->stk-1) ;       /* da word a hword */
        *stk =*pint ;   *(stk+1)=*(pint+1) ;
        s->pc=s->pc+l_stof ;
	break;
case c_fix :                    	/* da reale a intero */
//printf("[interpol.c]  c_fix\n");
        u.l=*(s->stk-1) ;  *(s->stk-1)=u.f    ;
        s->pc=s->pc+l_fix ;
	break;

/* Istruzioni READ e WRITE non ancora implementate non sono usate per i tabulati
case c_read :
//printf("[interpol.c]  c_read\n");
#include <read.c>
       	s->pc=s->pc+l_read ;
	break;
case c_write :
//printf("[interpol.c]  c_write\n");
#include <write.c>
      	s->pc=s->pc+l_write ;
	break;
*/
case c_float :                  		/* da intero a reale */
//printf("[interpol.c]  c_float\n");
        u.f=*(s->stk-1) ;       
	*(s->stk-1)=u.l ;
        s->pc=s->pc+l_float ;
	break;
case c_movi :                   		/* possono essere organi o interi */
//printf("[interpol.c]  c_movi\n");
        if(i.re.biad==b_organo) u.s[0]=*pcha ;
        else                  u.s[0]=*pint ;
        if(i2.re.biad==b_organo) *pcha2=u.s[0] ;
        else                  *pint2=u.s[0] ;
        s->pc=s->pc+l_imovi ;
	break;
case c_movf :
//printf("[interpol.c]  c_movf\n");
        *pint2=*pint ;  *(pint2+1)=*(pint+1) ; 	/* valore */
        if(i.re.biad==b_analogico && i2.re.biad==b_analogico)
            *(pint2+2)=*(pint+2) ;              /* flags        */
        s->pc=s->pc+l_movf ;
	break;
case c_imovf :                  		/* copio reale  in dbl  float */
//printf("[interpol.c]  c_imovf\n");
        *pint=*(s->pc+2) ;      *(pint+1)=*(s->pc+3) ;
        s->pc=s->pc+l_imovf ;
	break;
case c_imovi :
//printf("[interpol.c]  c_imovi\n");
        if(i.re.biad==b_organo) *pcha=*(s->pc+2) ;      /* org*/
        else   *pint =*(s->pc+2) ;                      /* intero */
        s->pc=s->pc+l_imovi ;
	break;
case c_imovs :
//printf("[interpol.c]  c_imovs\n");
        if((pcha+(*(s->pc+2))) < dbc+n_tdbl)              /* controllo limiti     */
        	strncpy(pcha,(char*)(s->pc+3),*(s->pc+2)); /* copia di una stringa */
        s->pc=s->pc+3+(*(s->pc+2))/2;                      /* da byte a word       */
        break;
case c_stleng :
//printf("[interpol.c]  c_stleng\n");
        (*pint2)=strlen(pcha);
        s->pc=s->pc+l_stleng;
        break;
case c_stncat:
//printf("[interpol.c]  c_stncat\n");
        if(pcha3+(*pint2)+strlen(pcha) < dbc+n_tdbl)   /* controllo limiti */
        	strncat(pcha3, pcha, *(pint2));
        s->pc=s->pc+l_stncat;
        break;
case c_mfix :
//printf("[interpol.c]  c_mfix\n");
        u.s[0]=*pint ;		/* copio valore float */
        u.s[1]=*(pint+1);
        u.s[0]=u.f+0.5;		/* approx. intero piu' vicino */
        *pint2 =u.s[0];		/* scritt. in dbl */
	s->pc+=l_mfix;
	break;
case c_mfloat:
//printf("[interpol.c]  c_mfloat\n");
        u.s[0]=*pint ;          /* copio valore intero */
        u.f=u.s[0] ;            /* trasformo in float  */
        *pint2=u.s[0] ; *(pint2+1)=u.s[1] ;
        s->pc=s->pc+l_mfloat ;
	break;
case c_mulf :
//printf("[interpol.c]  c_mulf\n");
        u.s[0]=*pint ;  u.s[1]=*(pint+1) ;
        u2.s[0]=*pint2; u2.s[1]=*(pint2+1) ;
        u3.f=u.f * u2.f ;
        *pint3 = u3.s[0] ; *(pint3+1)= u3.s[1] ;
        s->pc=s->pc+l_mulf ;
	break;
case c_muli :
//printf("[interpol.c]  c_muli\n");
        *pint3 = *pint * (*pint2) ;
        s->pc=s->pc+l_muli ;
	break;
case c_divf :
//printf("[interpol.c]  c_divf\n");
        u.s[0]=*pint ;  u.s[1]=*(pint+1) ;
        u2.s[0]=*pint2; u2.s[1]=*(pint2+1) ;
        u3.f=u.f / u2.f ;
        *pint3 = u3.s[0] ; *(pint3+1)= u3.s[1] ;
        s->pc=s->pc+l_divf;
	break;
case c_divi :
//printf("[interpol.c]  c_divi a/b a=%d b=%d\n",*pint,*pint2);
        *pint3 = *pint / (*pint2) ;
        s->pc=s->pc+l_divi ;
	break;
case c_sumf :
//printf("[interpol.c]  c_sumf\n");
        u.s[0]=*pint ;  u.s[1]=*(pint+1) ;
        u2.s[0]=*pint2; u2.s[1]=*(pint2+1) ;
        u3.f=u.f + u2.f ;
        *pint3 = u3.s[0] ; *(pint3+1)= u3.s[1] ;
        s->pc=s->pc+l_sumf;
	break;
case c_sumi :
//printf("[interpol.c]  c_sumi\n");
        *pint3 = *pint + (*pint2);
        s->pc=s->pc+l_sumi ;
	break;
case c_sums :
//printf("[interpol.c]  c_sums\n");
	strcpy(str,pcha);
	strcat(str,pcha2);
        if((pcha3+ strlen(str)) < dbc+n_tdbl)
        	strcpy(pcha3,str);
        s->pc=s->pc+l_sums;
        break;
case c_subf :
//printf("[interpol.c]  c_subf\n");
        u.s[0]=*pint ;  u.s[1]=*(pint+1) ;
        u2.s[0]=*pint2; u2.s[1]=*(pint2+1) ;
        u3.f=u.f - u2.f ;
        *pint3 = u3.s[0] ; *(pint3+1)= u3.s[1] ;
        s->pc=s->pc+l_subf;
	break;
case c_subi :
//printf("[interpol.c]  c_subi\n");
        *pint3 = *pint - (*pint2) ;
        s->pc=s->pc+l_subi ;
	break;
case c_clrf :
//printf("[interpol.c]  c_clrf\n");
        *pint=0 ;  *(pint+1)=0 ;
        s->pc=s->pc+l_clrf ;
	break;
case c_clri :
//printf("[interpol.c]  c_clri\n");
        *pint=0 ;
        s->pc=s->pc+l_clri ;
	break;
case c_absf :
//printf("[interpol.c]  c_absf\n");
        u.s[0]=*pint;   u.s[1]=*(pint+1) ;
        u.f= fabs(u.f) ;
        *pint2=u.s[0]; *(pint2+1)=u.s[1] ;
        s->pc=s->pc+l_absf ;
	break;
case c_absi :
//printf("[interpol.c]  c_absi\n");
        *pint2=abs(*pint) ;
        s->pc=s->pc+l_absi ;
	break;
case c_negf :
//printf("[interpol.c]  c_negf\n");
        u.s[0]=*pint;   u.s[1]=*(pint+1) ;
        u.f= - u.f  ;
        *pint2=u.s[0];  *(pint2+1)=u.s[1] ;
        s->pc=s->pc+l_negf ;
	break;
case c_negi :
//printf("[interpol.c]  c_negi\n");
        *pint2=- (*pint) ;
        s->pc=s->pc+l_negi ;
	break;
case c_sqrt :
//printf("[interpol.c]  c_sqrt\n");
        u.s[0]=*pint;   u.s[1]=*(pint+1) ;
        u.f= sqrt(u.f) ;
        *pint2=u.s[0];  *(pint2+1)=u.s[1] ;
        s->pc=s->pc+l_sqrt ;
	break;
case c_log  :
//printf("[interpol.c]  c_log\n");
        u.s[0]=*pint;   u.s[1]=*(pint+1) ;
        u.f= log10(u.f) ;
        *pint2=u.s[0];  *(pint2+1)=u.s[1] ;
        s->pc=s->pc+l_log ;
	break;
case c_exp  :
//printf("[interpol.c]  c_exp\n");
        u.s[0]=*pint;   u.s[1]=*(pint+1) ;
        u.f= exp(u.f) ;
        *pint2=u.s[0];  *(pint2+1)=u.s[1] ;
        s->pc=s->pc+l_exp  ;
	break;
case c_ln   :
//printf("[interpol.c]  c_ln\n");
        u.s[0]=*pint;   u.s[1]=*(pint+1) ;
        u.f= log(u.f) ;
        *pint2=u.s[0];  *(pint2+1)=u.s[1] ;
        s->pc=s->pc+l_ln   ;
	break;
case c_exp10:
//printf("[interpol.c]  c_exp10\n");
        u.s[0]=*pint;   u.s[1]=*(pint+1) ;
        u.f= pow(10.0,u.f) ;
        *pint2=u.s[0];  *(pint2+1)=u.s[1] ;
        s->pc=s->pc+l_exp10;
	break;
case c_sin  :
//printf("[interpol.c]  c_sin\n");
        u.s[0]=*pint;   u.s[1]=*(pint+1) ;
        u.f= sin(u.f) ;
        *pint2=u.s[0];  *(pint2+1)=u.s[1] ;
        s->pc=s->pc+l_sin  ;
	break;
case c_cos  :
//printf("[interpol.c]  c_cos\n");
        u.s[0]=*pint;   u.s[1]=*(pint+1) ;
        u.f= cos(u.f) ;
        *pint2=u.s[0];  *(pint2+1)=u.s[1] ;
        s->pc=s->pc+l_cos ;
	break;
case c_ipusha :
//printf("[interpol.c]  c_ipusha\n");
// Inizio NUOVO
        i.s  =*(s->pc+1) ; /* indirizzo variabile */
	disp=i.di.disp;
        if(i.re.indi)
        {
        	long  *fp1;
                fp1=(long*)*(fp);
                i.s=(short)(*(fp1-(i.di.byad>>1)));
                if(i.re.biad==b_reale) i.re.byad=i.re.byad+disp*4;	// vettori reali sommo displacement
                else i.re.byad=i.re.byad+disp*2;			// vettori interi o organi
	}
// Fine NUOVO
        *(s->stk)=i.s ;      		/* inserisco indirizzo nello stack */
        if(s->stk < s->sfine) s->stk++ ;
        else
	{
		printf("[ipusha] *** stack overflow *** ");
		return;
	}
        s->pc=s->pc+l_ipusha ;
	break;
case c_push_sp :
//printf("[interpol.c]  c_push_sp\n");
        *(s->stk)=(long)s->stk ;      	/* salvo stack pointer */
        if(s->stk < s->sfine) s->stk++ ;
        else
	{
		printf("[push_sp] *** stack overflow *** ");
		return;
	}
        s->pc=s->pc+l_push_sp ;
	break;
case c_push_fp :
//printf("[interpol.c]  c_push_fp\n");
        *(s->stk)=(long)fp ;          
        if(s->stk < s->sfine) s->stk++ ;
        else
	{
		printf("[push_fp] *** stack overflow *** ");
		return;
	}
        s->pc=s->pc+l_push_fp ;
	break;
case c_pop_sp :
//printf("[interpol.c]  c_pop_sp\n");
        s->stk-- ; s->stk=(long *) *(s->stk) ;
        s->pc=s->pc+l_pop_sp ;
	break;
case c_pop_fp :
//printf("[interpol.c]  c_pop_fp\n");
        fp=(long *) *(s->stk) ;
        s->pc=s->pc+l_pop_fp ;
	break;
case c_sp_fp :
//printf("[interpol.c]  c_sp_fp\n");
        fp=s->stk-1;            /* lo stack parte da zero */
        s->pc=s->pc+l_sp_fp ;
	break;
case c_fp_sp :                  /* lo stack parte da zero */
//printf("[interpol.c]  c_fp_sp\n");
        s->stk=fp+1 ;
        s->pc=s->pc+l_fp_sp ;
	break;
case c_print :
//printf("[interpol.c]  c_print\n");
        s->pc++ ;
#include "decpr.c"
	break;
case c_potf :
//printf("[interpol.c]  c_potf\n");
        u.s[0]=*pint ;  u.s[1]=*(pint+1) ;
        u2.s[0]=*pint2;  u2.s[1]=*(pint2+1) ;
        u3.f=pow(u.f,u2.f) ;
        *pint3=u3.s[0] ; u3.s[1]=*(pint3+1) ;
        s->pc=s->pc+l_potf ;
	break;
case c_tan  :
//printf("[interpol.c]  c_tan\n");
        u.s[0]=*pint;   u.s[1]=*(pint+1) ;
        u.f= tan(u.f) ;
        *pint2=u.s[0];  *(pint2+1)=u.s[1] ;
        s->pc=s->pc+l_tan ;
	break;
case c_arcsin :
//printf("[interpol.c]  c_arcsin\n");
        u.s[0]=*pint;   u.s[1]=*(pint+1) ;
        u.f= asin(u.f) ;
        *pint2=u.s[0];  *(pint2+1)=u.s[1] ;
        s->pc=s->pc+l_arcsin ;
	break;
case c_arccos :
//printf("[interpol.c]  c_arccos\n");
        u.s[0]=*pint;   u.s[1]=*(pint+1) ;
        u.f= acos(u.f) ;
        *pint2=u.s[0];    *(pint2+1)=u.s[1] ;
        s->pc=s->pc+l_arccos ;
	break;
case c_arctan :
//printf("[interpol.c]  c_arctan\n");
        u.s[0]=*pint;   u.s[1]=*(pint+1) ;
        u.f= atan(u.f) ;
        *pint2=u.s[0];  *(pint2+1)=u.s[1] ;
        s->pc=s->pc+l_arctan ;
	break;
case c_fread:
//printf("[interpol.c]  c_fread\n");
	/* N. del file */
	i.s  =*(s->pc+1);
        i=IndDir(s,i,fp,&dbs,&dbc);
        pcha=dbc+i.re.byad;
	pint=dbs+(i.re.byad>>1);
        s->pc+=4;

	/* Indice del record da leggere */
	i2.s  =*(s->pc);     
        i2=IndDir(s,i2,fp,&dbs,&dbc);
        pcha2=dbc+i2.re.byad;
	pint2=dbs+(i2.re.byad>>1);
        s->pc+=2;

	/* Apre il file e legge il record opportuno */
	BuildFPOLName(str,*pint);
	file=fopen(str,"r");
	if(!file)
	{
		printf("[fread] impossibile aprire il file %s\n",str);
		return;
	}
	pch=p1=(char*)malloc(LRECFIO);
	memset(p1,-1,LRECFIO);
	fseek(file,((long)LRECFIO * *pint2),SEEK_SET);
	fread(p1,LRECFIO,1,file);

	/* Assegnazione dei valori alle variabili */
	for(;*(++s->pc)!=-1 && pch<p1+LRECFIO-2;)
        {
        	i3.s  =*(s->pc);
        	i3=IndDir(s,i3,fp,&dbs,&dbc) ;
        	pcha3=dbc+i3.re.byad;
		
		/* Esegue la copia solo se il tipo del dato e' plausibile */
		if(*pch!=-1)
			memcpy(pcha3,pch+2,*(pch+1));

		pch+=(2+*(pch+1));
        	s->pc+=2;
        }

	/* Libera le risorse */
	fclose(file);
	free(p1);

	s->pc++;
	break;
case c_fwrite:
//printf("[interpol.c]  c_fwrite\n");
	/* N. del file */
	i.s  =*(s->pc+1);
        i=IndDir(s,i,fp,&dbs,&dbc);
        pcha=dbc+i.re.byad;
	pint=dbs+(i.re.byad>>1);
        s->pc+=4;

	/* Indice del record da leggere */
	i2.s  =*(s->pc);     
        i2=IndDir(s,i2,fp,&dbs,&dbc);
        pcha2=dbc+i2.re.byad;
	pint2=dbs+(i2.re.byad>>1);
        s->pc+=2;

	/* Apre il file e legge il record opportuno */
	BuildFPOLName(str,*pint);
	file=fopen(str,"r");
	if(!file)
	{
		printf("[fwrite] impossibile aprire il file %s\n",str);
		return;
	}
	pch=p1=(char*)malloc(LRECFIO);
	memset(p1,-1,LRECFIO);
	fseek(file,((long)LRECFIO * *pint2),SEEK_SET);

	/* Compone il record per il file */
	for(;*(++s->pc)!=-1 && pch<p1+LRECFIO-2;)
        {
        	i3.s  =*(s->pc);
        	i3=IndDir(s,i3,fp,&dbs,&dbc) ;
        	pcha3=dbc+i3.re.byad;
		
		*(pch++)=*(s->pc+1);
                *(pch++)=*(s->pc+2);

		if(*(s->pc+1)==FIO_STRING)
		{
			strcpy(pch,pcha3);
			pch+=strlen(pcha3)+1;
		}
		else
		{
			memcpy(pch,pcha3,*(s->pc+2));
			pch+=*(s->pc+2);
		}

        	s->pc+=2;
        }
	
	/* Inserisce il checksum e scrive il record */
	p1[LRECFIO-1]=_fchks(p1,LRECFIO-1);
	fwrite(p1,LRECFIO,1,file);

	/* Libera le risorse */
	fclose(file);
	free(p1);

	s->pc++;
	break;
case c_fdelete:
//printf("[interpol.c]  c_fdelete\n");
	BuildFPOLName(str,*pint);
	remove(str);
	s->pc+=l_fdelete;
	break;
case c_movs:
//printf("[interpol.c]  c_movs\n");
        strcpy(pcha2,pcha);
        s->pc=s->pc+l_movs;
        break;
default :
        printf("interpol.c: istruzione sconosciuta  ") ;
        return ;
}
}
}

/********************************************************************************************
*
*       IndDir()
*       Trasforma  un indirizzo da indiretto a diretto
*   
*       Parametri
*                       frame pointer
*                       indirizzo da tradurre
* 
*       Ritorno
*                       indirizzo tradotto
**********************************************************************************************/
union u_indirizzi IndDir(S_INTERP* s, union u_indirizzi ind, long* fp, short** dbs, char** dbc)
{
        short disp;

        if(ind.re.indi)
        {
                disp=ind.di.disp;
        	ind.s=(short)(*(fp-(ind.di.byad>>1)));

		/* vettori reali sommo displacement */
        	if(ind.re.biad==b_reale) 
			ind.re.byad+=disp*4;  
        	else 
			ind.re.byad+=disp*2;
        }

       	*dbs=s->dbs;
        *dbc=s->dbc;

	return(ind);
}

/* Costruisce il nome del file POL FPOLxxxx.VAR 
   usato da pagine, PAS e tabulati .             */
void BuildFPOLName(char *str,short n)
{
	memset(str,0,FILENAME_MAX+1);
        strcpy(str,conf[RTF]);
        sprintf(str+strlen(str),"/fpol%hd.var",n);
}

