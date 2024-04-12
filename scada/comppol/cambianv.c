/*
   modulo cambianv.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)cambianv.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*                                                                    *
*			Procedura cambianvar                                        *
*                                                                    *
*	La procedura cambia tutte le occorrenze in linea_cor della        *
* stringa nomevar con newvar, mettendo a 1 ok.                       *
*                                                                    *
*********************************************************************/
#include "osf1.h"
#include <stdio.h>
#include <string.h>
#include "tipi.h"
#include "define.inc"

extern char linea_cor[];	  

cambianvar(nomevar,newvar,ok)
char nomevar[];
char newvar[];
int *ok;
{
char *s,*t,*p;
char linea_prov[DMX_RIGA+1];
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

