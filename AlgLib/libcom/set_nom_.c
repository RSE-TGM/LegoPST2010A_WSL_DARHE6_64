/**********************************************************************
*
*       C Source:               set_nom_.c
*       Subsystem:              3
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Oct 21 11:54:19 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: set_nom_.c-2 %  (%full_filespec: set_nom_.c-2:csrc:3 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)set_nom_.c	5.2\t1/3/96";
/*
   modulo set_nom_.c
   tipo 
   release 5.2
   data 1/3/96
   reserved @(#)set_nom_.c	5.2
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
#include <string.h>
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
/******
 ATTENZIONE !!!!
   la parte in VMS per il settaggio nome logico non e' ancora
   stata implementata   !!!!
   Di seguito e' riportata la routine per la traduzione 
*********/

int set_nom_log_s(valore_nome,lun_valore,nome,tabella)
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

status=sys$crelnm(0,&tabella_desc,&name_desc,0,&item_list);
if((status!=SS$_NORMAL)||(status!=SS$_SUPERSEDE))
	{
	LIB$SIGNAL(status);
	return(1);
	}
valore_nome[*(item_list.retlenadr)]=0;
return(0);
}

#elif defined AIX || defined OSF1 || defined SCO_UNIX || defined LINUX
int set_nom_log_s(valore_nome,lun_valore,nome,tabella)
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
		strcpy(ease_lnm[i].valore,valore_nome);
		return(0);
		}
	}
/* Il nome non e' gia' presente in tabella; lo inserisco
   nella prima posizione libera
 */
for(i=0;i<NUM_NOM_LOG;i++)
        {
        if(ease_lnm[i].nome[0]==0)
                {   /* posizione libera trovata */
                strcpy(ease_lnm[i].valore,valore_nome);
		strcpy(ease_lnm[i].nome,nome);
                return(0);
                }
        }
fprintf(stderr,"\nset_nom_log_s: tabella nomi logici piena");
return(-1);
}

#endif





