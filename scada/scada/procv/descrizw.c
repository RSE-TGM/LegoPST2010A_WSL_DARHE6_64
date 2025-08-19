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
   Descrizwin

		la function descriz invia la descrizione di un punto in base
		al suo tipo a MMI di tipo Window
		se il punto e' analogico invia descrizione e unita' di misura
		se e' digitale descrizione e stati
		se e' organo descrizione e tipo di organo

   Parametri
         S_MRDPWIN*  messaggio di richiesta

   Ritorno
         nessuno
*/
#include <stdio.h>
#include <string.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include "messcada.inc"
#include	"mesqueue.h"
#include "dconf.inc"

extern DB_HEADER h_db;

/* Function prototypes */
extern int ricerca(short *, short *, short *, long *, short *, FILE *);
extern int rbyte(int, char *, long, int);

int descrizwin(mes)
S_MRDPWIN* mes ;
{

S_VDESPAWIN a;	

short ext,point   ;
short posiz ;
long blocco ;
char *p1 ;
long offset;
short nbyte ;
short i,ier ;
char desc[rec_fdda];       // dimensione massima descrittore ASCII

QUEUE_PACKET spack;

memset(&a,0,sizeof(a));
/*
	se conosco il nome del punto procedo a controllare se esiste su fnomi
*/
if(mes->punto[0])
{
	p1=(char*) & mes->punto[0] ;
	for(i=0;i<SCD_SIGLA;i++,p1++) { if((*p1)==' ') (*p1)=0 ; }
   if(ricerca(mes->punto,&point,&ext,&blocco,&posiz,fpp[fnomi]))
	{   
			a.ext =m_nondef;	/*  misura non esistente */
	      a.punt=erres ; 	/* punto non esistente */
	      a.tipo=m_nondef;
	      goto RISP ;
	  }
}
/*
	conosco gia' il puntatore in db
*/
else {  point=mes->punto[2] ;  ext=mes->punto[1]; }

/*
	leggo la descrizione dai file operativi
*/
switch(ext)
{
case g1tipaa: case g1tipas: case g1tipac: case g1tipad: case g1tipao:
	if(mes->tipo!=m_analogico && mes->tipo!=-1) 
   { a.ext=m_nondef; a.punt=errtip; a.tipo=m_nondef; goto RISP ;}
   a.tipo=m_analogico;
	switch(ext) 
	{
	case g1tipaa :	 nbyte=rec_fdaa; 	offset=of_fdaa ;		break ;
	case g1tipas :	 nbyte=rec_fdas;	offset=of_fdas ;		break ;
	case g1tipac :	 nbyte=rec_fdac;	offset=of_fdac ;		break ;
	case g1tipad :	 nbyte=rec_fdad;	offset=of_fdad ;		break ;
	case g1tipao :	 nbyte=rec_fdao;	offset=of_fdao ;		break ;
	}
	break ;
case g1tipda: case g1tipds: case g1tipdc: case g1tipdd:  case g1tipdo:
	if(mes->tipo!= m_digitale && mes->tipo !=-1) 
   { a.ext=m_nondef; a.punt=errtip;  a.tipo=m_nondef;  goto RISP  ;}
   if(ext==g1tipdo) a.tipo=m_dout;
   else a.tipo=m_digitale;
	switch(ext)
	{
	case g1tipda :	 nbyte=rec_fdda; 	offset=of_fdda ;		break ;
	case g1tipds :	 nbyte=rec_fdds;	offset=of_fdds ;		break ;
	case g1tipdc :	 nbyte=rec_fddc;	offset=of_fddc ;		break ;
	case g1tipdd :	 nbyte=rec_fddd;	offset=of_fddd ;		break ;
	case g1tipdo :	 nbyte=rec_fddo;	offset=of_fddo ;		break ;
	}
	break;
case g1tipor:
	if(mes->tipo!= m_organo && mes->tipo!=-1) 
   { a.ext=m_nondef; a.punt=errtip; a.tipo=m_nondef; goto RISP  ;}
   a.tipo=m_organo;
	nbyte=rec_fdor ;	  offset=of_fdor ;
	break;
case g1tipst:
   if(mes->tipo!=m_stringa && mes->tipo!=-1)
   { a.ext=m_nondef; a.punt=errtip;  a.tipo=m_nondef;  goto RISP  ;}
   a.tipo=m_stringa;
   nbyte=rec_fdst;   offset=of_fdst;
   break;
default:
	a.tipo=m_nondef;
   a.ext=m_nondef; a.punt=errtip;
	goto RISP;
}
rbyte(fileno(fpp[fdde]),(char*)desc,offset+nbyte*point,nbyte) ;
if(a.tipo==m_analogico || a.tipo==m_organo)
{
   //memcpy(a.nome,desc,SCD_SIGLA+SCD_DESCRIZIONE+winlu_mi);
   memcpy(a.nome,desc,nbyte);
}
else if(a.tipo==m_digitale)
{
   memcpy(a.nome,desc,SCD_SIGLA+SCD_DESCRIZIONE+winlu_st);
   memcpy(a.stato,&desc[SCD_SIGLA+SCD_DESCRIZIONE+winlu_st],winlu_st);
}
else  memcpy(a.nome,desc,SCD_SIGLA+SCD_DESCRIZIONE);     // stringa

a.punt=point;
a.ext=ext;

RISP :
/*
   ricopio i puntatori al data base locale dove MMI deve copiare
   le informazioni
*/
a.dblpunt=mes->dblpunt;	
a.dbltipo=mes->dbltipo;	
a.dbltag=mes->dbltag;		
a.dbldesc=mes->dbldesc;	
a.dblunita=mes->dblunita;
a.dblstat=mes->dblstat;

a.spare1=0 ;
a.indice=vdesp ;
a.zona= mes->zona ; 	a.video=mes->video ;
a.nodo=a.video-1;
memcpy(&a.pag[0],&mes->pag[0],10);
/*
	invio al micro
*/
spack.que= c_mmio;
spack.flg = MSG_WAIT;
spack.wto = 0;
spack.lmsg=sizeof(S_VDESPAWIN) ;
spack.amsg=(char *) & a;

enqueue(&spack);

return(0);
}

