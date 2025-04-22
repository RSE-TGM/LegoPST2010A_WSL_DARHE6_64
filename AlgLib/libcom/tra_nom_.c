/**********************************************************************
*
*       C Source:               tra_nom_.c
*       Subsystem:              3
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Oct 21 11:53:29 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: tra_nom_.c-2 %  (%full_filespec: tra_nom_.c-2:csrc:3 %)";
#endif

#include <stdio.h>
#include <string.h>

/*
   modulo tra_nom_.c
   tipo 
   release 5.2
   data 1/3/96
   reserved @(#)tra_nom_.c	5.2
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)tra_nom_.c	5.2\t1/3/96";
/*
        Fine sezione per SCCS
*/
/*
 * tra_nom_log_s.c
 *   traduce un nome logico  
 */
#ifdef VMS
#include unixlib
#include stdio
#include ssdef
#include lnmdef
#include descrip
#include "libcom.h"

#elif defined AIX || defined OSF1 || defined SCO_UNIX || defined LINUX
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "libcom.h"
extern S_NOME_LOGICO *ease_lnm; /* puntatore all'area shared utilizzata come
                            tabella dei nomi logici per EASE */

#endif

#ifdef VMS
typedef struct itmlst{
 short buflen;
 short code;
 char *bufadr;
 char *retlenadr;
 int end_list;} ITMLIST;


int tra_nom_log_s(valore_nome,lun_valore,nome,tabella)
char *valore_nome;
int lun_valore; /* lunghezza disponibile */
char *nome;
char *tabella;
{
int lun_ritorno;
ITMLIST item_list;
int iosb[2];
int pid;
struct dsc$descriptor_s name_desc;
struct dsc$descriptor_s tabella_desc;
int status;
int state,state_len;

item_list.end_list=0;
item_list.buflen=lun_valore;
item_list.code=LNM$_STRING;
item_list.bufadr=valore_nome;
item_list.retlenadr=(&lun_ritorno);

name_desc.dsc$b_class=DSC$K_CLASS_S;
name_desc.dsc$b_dtype=DSC$K_DTYPE_T;
name_desc.dsc$a_pointer=nome;
name_desc.dsc$w_length=strlen(nome);

tabella_desc.dsc$b_class=DSC$K_CLASS_S;
tabella_desc.dsc$b_dtype=DSC$K_DTYPE_T;
tabella_desc.dsc$a_pointer=tabella;
tabella_desc.dsc$w_length=strlen(tabella);

status=sys$trnlnm(0,&tabella_desc,&name_desc,0,&item_list);
if(status!=SS$_NORMAL)
	{
	LIB$SIGNAL(status);
	return(1);
	}
valore_nome[*(item_list.retlenadr)]=0;
return(0);
}

#elif defined AIX || defined OSF1 || defined SCO_UNIX || defined LINUX
int tra_nom_log_s(valore_nome,lun_valore,nome,tabella)
char *valore_nome;
int lun_valore; /* lunghezza disponibile */
char *nome;
char *tabella;
{
int i;
if(strcmp(tabella,"EASE$LNM")!=0)
	{ fprintf(stderr,"\ntra_nom_log_s: tabella nomi non esistente");
	  return(-1);
	}
/*
 Ricerca il nome logico richiesto nella tabella
 */
for(i=0;i<NUM_NOM_LOG;i++)
	{
	if(strcmp(nome,ease_lnm[i].nome)==0)
		{   /* nome trovato */
		strcpy(valore_nome,ease_lnm[i].valore);
		return(0);
		}
	}
fprintf(stderr,"\ntra_nom_log_s: nome logico non trovato");
return(-1);
}

#endif


#if defined VMS
/*
   Chiamata da un main fortran restituisce il nome
   logico in una variabile
*/
typedef struct stringades {
               unsigned short lunghezza;
               unsigned char  tipo;
               unsigned char  classe;
                        char  *stringa;
             } STRINGADES;


int tra_nom_log_for(STRINGADES *val_nome, int *lun_val, 
                    STRINGADES *nome_for,STRINGADES *tab)
{
int lun_ritorno;
ITMLIST item_list;
int iosb[2];
int pid;
struct dsc$descriptor_s name_desc;
struct dsc$descriptor_s tabella_desc;
int status;
int state,state_len;

char *valore_nome;
int lun_valore;
char *nome;
char *tabella;


/*
   printf("valore_nome=%s\n",val_nome->stringa);
   printf("nome=%s\n",nome_for->stringa);
   printf("tabella=%s\n",tab->stringa);
*/

/* Assegnamento puntatori e variabili locali */
   valore_nome = val_nome->stringa;
   nome        = nome_for->stringa;
   tabella     = tab->stringa;
   lun_valore = *lun_val;

   item_list.end_list=0;
   item_list.buflen=lun_valore;
   item_list.code=LNM$_STRING;
   item_list.bufadr=valore_nome;
   item_list.retlenadr=(&lun_ritorno);

   name_desc.dsc$b_class=DSC$K_CLASS_S;
   name_desc.dsc$b_dtype=DSC$K_DTYPE_T;
   name_desc.dsc$a_pointer=nome;
   name_desc.dsc$w_length=strlen(nome);

   tabella_desc.dsc$b_class=DSC$K_CLASS_S;
   tabella_desc.dsc$b_dtype=DSC$K_DTYPE_T;
   tabella_desc.dsc$a_pointer=tabella;
   tabella_desc.dsc$w_length=strlen(tabella);

   status=sys$trnlnm(0,&tabella_desc,&name_desc,0,&item_list);
/*
   printf("Dopo sys$trnlnm con in=%d\n",*(item_list.retlenadr));
   printf("Dopo sys$trnlnm con in=%s\n",valore_nome);
*/
   if(status!=SS$_NORMAL)
        {
        LIB$SIGNAL(status);
        return(1);
        }

/* Uscite */
   valore_nome[*(item_list.retlenadr)]=0;
   (*lun_val) = *(item_list.retlenadr);

   return(0);
}
#endif



