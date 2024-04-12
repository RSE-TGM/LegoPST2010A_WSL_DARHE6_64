/*
   modulo util.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)util.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*
*             File util.c
*
*	cambianvar(nomevar,newvar,ok)                    
*		char nomevar[];                               
*		char newvar[];                                
*		int *ok;                                     
*	cnome(nomevar,tipo,M)                           
*		char nomevar[];                             
*		int *tipo;                                  
*		int *M;                                     
*	insvar_subr(fdlocale,righeloc)                 
*		int fdlocale;                              
*		int *righeloc;                             
*          							 
*********************************************************************/

#ifdef INGLESE
#define SubLocVar    " Subroutine local variables         "
#define nomOffTip    " Name variable    Offset   Type "
#define nomOffTipNw  " Variable name    Offset   Type     New name  "
#else
#define nomOffTipNw  " Nome variabile   Offset   tipo     Nuovo nome"
#define nomOffTip    " Nome variabile   Offset   Tipo "
#define SubLocVar    " Variabili locali della subroutine  "
#endif

#include <osf1.h>
#include <stdio.h>
#include <string.h>

#include "chascii.inc"

#include "tipi.h"

#define LUNGSTR	    80
#define POS1	     3
#define POS2	    10
#define POS3        20
#define POS4	    30
#define POS5	    40
#define NUM_ARG	20

extern char linea_cor[];	  /*
extern char c[];
extern int fdi,numriga;
extern int nword_o;
extern int errori;
extern int indmenu[];
extern int subrcorr;
extern int tvarsubr[10][NUM_ARG+1];
extern int hh;
extern int fdlst;
extern int contsubr;
extern int righelst;
extern char *nvarsubr[10][NUM_ARG];
extern char *nomi_subr[];
extern char *t_var[];
extern struct variabili *inserisci();
*/

/*********************************************************************
*          							     *
*			Procedura cambianvar                         *
*          							     *
*	La procedura cambia tutte le occorrenze in linea_cor della   *
* stringa nomevar con newvar, mettendo a 1 ok.                       *
*          							     *
*********************************************************************/

cambianvar(nomevar,newvar,ok)
char nomevar[];
char newvar[];
int *ok;
{
char *s,*t,*p;
char linea_prov[200];
int i,sem;
s=linea_prov;
p=t=linea_cor;
*ok=0;
while(t!=NULL) {
	if((t=strstr(p,nomevar))==NULL)
		break;
	for(;p!=t;s++,p++)
		*s=*p; /* copio nella stringa aus. il pezzo scandito */
	t--;
	sem=issep(*t); /* guardo se il carattere precedente e' un separatore */
	t++;
	for(i=0;*t==nomevar[i] && i<EF_LUNGVAR;i++)
		t++;   /* mi posiziono all fine della stringa trovata
			  per vedere se la parola e' finita o meno */
	if(sem==1 && ((sem=issep(*t))==1)) {
		*s=newvar[0]; /* ho trovato una occorrenza di nomevar */
	 	s++;          /* ed allora inserisco nella stringa    */
		*s=newvar[1]; /* ausiliaria i primi tre campi del     */
	 	s++;          /* nuovo nome */
		*s=newvar[2]; 
	 	s++;          
	}
	strcpy(s,p);
	s+=i;    /* posiziono s alla fine della variabile cambiata */
	p=t;     /* mi riporto nella condizione iniziale */
	*ok=1;
}
sprintf(linea_cor,"%s",linea_prov);
}

/*********************************************************************
*          							     *
*			Procedura issep                              *
*          							     *
*	La procedura rende 1 se il carattere passato e' un separatore*
* compreso tra quelli elencati sotto, -1 altrimenti.                 *
*          							     *
*********************************************************************/

issep(c)
char c;
{
switch(c) {
	case   BLANK :
	case APTONDA :
	case CHTONDA :
	case VIRGOLA :
	case    0x5b :     /* aperta quadra */
	case    0x5d :     /* chiusa quadra */
	case    0x3a :     /* due punti */
	case    0x00 :     /* fine stringa */
	case    0x2e :	    /* punto */
		return(1);
	default :
		return(-1);
}
}

/*********************************************************************
*          							     *
*			Procedura cnome                              *
*          							     *
* 	Cambia il nome passato in nomevar mettendo come primo carat= *
* tere #, come secondo in numero della subtroutine corrente e poi vi *
* copia il vecchio nome. Inoltre incrementa M di due, cioe' dei 2    *
* caratteri aggiunti alla riga e fa considerare al tipo della var.   *
* solo i primi 4 bit.					             *
*          							     *
*********************************************************************/

cnome(nomevar,tipo,M)
char nomevar[];
int *tipo;
int *M;
{
char ausvar[LUNG_VAR+1];
if(*tipo!=-1)
	*tipo &=15;
(*M)+=2;
ausvar[0]=0x23;
/*  ausvar[1]=subrcorr+0x30; */
sprintf(&ausvar[1],"%02d",subrcorr);
(*M)++;
strcpy(&ausvar[3],nomevar);
strcpy(nomevar,ausvar);
}

/*********************************************************************
*          							     *
*			Procedura insvar_subr                        *
*          							     *
*	La procedura serve per inserire nel file di listing (fdlocale*
* =fdlst) o in quello intermedio (fdlocale=fdint) le variabili locali*
* di ogni subr. Se scrivo sul file intermedio, oltre al nome e all'  *
* offset della variabile scrivo anche il nuovo nome che le e' stato  *
* attribuito.                                                        *
*          							     *
*********************************************************************/

insvar_subr(fdlocale,righeloc)
int fdlocale;
int *righeloc;
{
int i,j,t;
char stringa[LUNGSTR],nomevar[LUNG_VAR+1];
scrivisufile(fdlocale,c,2,righeloc);
for(i=0;i<contsubr;i++) {
	j=sprintf(stringa,"%s",SubLocVar);
	j+=sprintf(&stringa[j],"%s",nomi_subr[i]); /* nome subr. */
	scrivisufile(fdlocale,stringa,j+1,righeloc);
	if(fdlocale==fdlst)
		j=sprintf(stringa,"%s",nomOffTip);
	else
		j=sprintf(stringa,"%s",nomOffTipNw);
	scrivisufile(fdlocale,stringa,j+1,righeloc);
	for(t=0;t<(tvarsubr[i][NUM_ARG] & 15);t++) {
		sbianca(stringa,LUNGSTR-1);
		j=POS1;
		j+=sprintf(&stringa[j],"%s",nvarsubr[i][t]); /* nome
					      del t-esimo argomento */
		stringa[j]=BLANK;
		j=POS3;
		j+=sprintf(&stringa[j],"%2d",t+1);  /* offset */
		stringa[j]=BLANK;
		j=POS4-4;
		j+=sprintf(&stringa[j],"%s",t_var[tvarsubr[i][t] & 15]);
		if(fdlocale!=fdlst)  {
			stringa[j]=BLANK;    /* creo il nome con cui */
			nomevar[0]=0x23;     /* l' argomento e' stato*/
/*			nomevar[1]=i+0x30;   /* ridefinito e lo inserisco */
			sprintf(&nomevar[1],"%02d",i);		
			strcpy(&nomevar[3],nvarsubr[i][t]);
			j=POS5-4;
			j+=sprintf(&stringa[j],"%s",nomevar);
		}
		scrivisufile(fdlocale,stringa,j+1,righeloc);
	}
	scrivisufile(fdlocale," ",2,righeloc);
}
scrivisufile(fdlocale,c,2,righeloc);
}
