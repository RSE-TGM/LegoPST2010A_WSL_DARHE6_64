/**********************************************************************
*
*	C Source:		CsFunc.c
*	Instance:		1
*	Description:	
*	%created_by:	famgr %
*	%date_created:	Thu Sep 10 10:24:54 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: CsFunc.c-1 %  (%full_filespec: CsFunc.c-1:csrc:1 %)";
#endif

/******************************************************
Modulo  per contenere funzioni varie per comunicazione
fra client_server client_scada ed mmi
*******************************************************/
#include <Cs/Cs.h>
#include <sys/ipc.h>

/*
    Controlla se nella tabella delle SHM esistenti
    e' presente la SHM cercata.
*/
int cerca_shm(TAB_SHARED *tab, int id_shm)
{
char *punt;
int i;

     for(i=0;i<MAX_OPERAZIONI;i++)
        if( tab[i].id_shm==id_shm)
            break;
     if(i==MAX_OPERAZIONI)
        {
        printf("cerca_shm SHM non presente in tabella  ");
        printf("cerco id_shm=%d \n",id_shm);
        i = -1;
        }
         
 return(i);
}

/*
Funzione che invia msg di ack ad MMI dopo
aver ricevuto No di punti SIM che compongono la pagina
Parameter:
        int id_msg_client: id coda fra client ed mmi
        int id_shm: id shm appena creata
Return:
        nessuno
*/
int send_mmi_ret_ack(int id_msg_client,int id_shm)
{
MSG_NEW_PAGE_MMI_RET msg_ret;

/* Spedisco il messaggio di akwnoledge */
   msg_ret.mtype  = NEW_PAGE_MMI_RET;
   msg_ret.id_shm = id_shm ;
   msg_snd(id_msg_client,&msg_ret,sizeof(MSG_NEW_PAGE_MMI_RET)-sizeof(long),
           !IPC_NOWAIT);

}


int tab_piena(TAB_SHARED *tab)
{
char *punt;
int i=0;


     while( tab[i].id_shm!=-1 )
        {
        if(i==MAX_OPERAZIONI)
           break;
        i++;
        }
     if(i==MAX_OPERAZIONI)
        {
        printf("tab_piena!!!");
        return(-1);
        }
     else
        return(i);
}
