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
   Modulo contenente le routine esportate verso i pag e 
   il corpo del task di gestione del pag.
   I moduli contenuti sono:
      PagInitDos     - inizializzazione sotto DOS
      PagInitMarte   - inizializzazione sotto MARTE
      Pag1..5        - Entry dei task Pag
      PagComune      - Corpo comune del task

      ModiAtti       - imposta la modalita' di attivazione del pag
      ModiPri        - modifica la priorita' del Pag

      WaitForTimeout - attesa di scatto timeout
      WaitForEvent   - attesa di scatto timeout o evento

      CnvTag         - converte una tag in puntatore
      ReadDb         - legge da DataBase
      WriteDb        - scrive nel data base
      WriteOpDb      - scrive nel data base
      GetDbVer       - legge la versione corrente del data base

*/


#include <stdio.h>
#include <string.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "trapas.inc"
#include "dconf.inc"
#include "comunic.inc"
#include "mesprocv.inc"
#include "tipal.inc"				
#include "messcada.inc"
#include "mesqueue.h"

#include "paglib.h"

/* Function prototypes */
extern void pri(int tcb, int priority);
extern int tra(int mbox, int signal);
extern int ricerca(char *sigla, short *punt, short *ext, long *displ, short *posiz, FILE *fp);
extern int bitvalue(short *buffer, short bit);
extern void bitset(short *buffer, short bit, short value);
extern void verifall(short punt, short tipo);

void PagInitDos();    
void PagInitMarte();  
void Pag1();       
void Pag2();       
void Pag3();       
void Pag4();       
void Pag5();       
void PagComune(int);     


int tas(int);
int syn(int,short,short);
int ter();
int rew(int,int,int *);
int wai(short);

extern short inv_slave;


extern int pag1_tcb;
extern int pag2_tcb;
extern int pag3_tcb;
extern int pag4_tcb;
extern int pag5_tcb;

extern int mbox_pag1;
extern int mbox_pag2;
extern int mbox_pag3;
extern int mbox_pag4;
extern int mbox_pag5;

extern int mbox_pagres1;
extern int mbox_pagres2;
extern int mbox_pagres3;
extern int mbox_pagres4;
extern int mbox_pagres5;

static int * pagres[5]={&mbox_pagres1,&mbox_pagres2,&mbox_pagres3,
							   &mbox_pagres4,&mbox_pagres5};

// struttura descrittore PAG


typedef struct {
                int Tcb;
                int Mbox;
                short mode;
                short stat;
                short periodo;
                short priorita;
                char nomedll[20];
                void (* init)(short);
                void (* corpo)(); } PAG_DEF;


PAG_DEF  PagSt[MAXPAG];
static char *nomed="PAGx.DLL";

// Modi previsti

#define PG_TER 0x0
#define PG_TAS 0x1
#define PG_SYN 0x2

// Stati previsti

#define PG_ATTI   0x80
#define PG_DIS    0x0

// Stati previsti

#define PG_LOW    200
#define PG_HIGH   150


/* Modulo di inizializzazione sotto DOS
   Inizializza i descrittori con le routine di inizializzazione Marte
   e del corpo del task.
   Nella versione finale esegue l' aggancio alle DLL.....
   */

// provvisori
void   PagIniDos1();
void   PagIniDos2();
/*
void   PagIniDos3();
void   PagIniDos4();
void   PagIniDos5();
*/
void   PagIniMarte1(short);  
void   PagIniMarte2(short);  
/*
void   PagIniMarte3(short);  
void   PagIniMarte4(short);  
void   PagIniMarte5(short);  
*/
void   PagCorpo1();  
void   PagCorpo2();  
/*
void   PagCorpo3();  
void   PagCorpo4();  
void   PagCorpo5();  
*/

void PagInitDos()
   {
   int i;
   char nome[20];
      PagSt[0].init= PagIniMarte1;
      PagSt[0].corpo= PagCorpo1;
      PagSt[1].init= PagIniMarte2;
      PagSt[1].corpo= PagCorpo2;
/*
      PagSt[2].init= PagIniMarte3;
      PagSt[2].corpo= PagCorpo3;
      PagSt[3].init= PagIniMarte4;
      PagSt[3].corpo= PagCorpo4;
      PagSt[4].init= PagIniMarte5;
      PagSt[4].corpo= PagCorpo5;
*/
   PagIniDos1();
   PagIniDos2();
/*
   PagIniDos3();
   PagIniDos4();
   PagIniDos5();
*/
   }


/* Modulo di inizializzazione sotto Marte
   Completo l' inizializzazione dei campi con gli oggetti marte
   Eseguo i moduli di inizializzazione marte
   Attivo i Task Pag con la modalita' pervista
   */


extern int wtcbc;          // tcb running
static short fase;

void PagInitMarte()
   {
   int i;

   PagSt[0].Tcb=pag1_tcb;
   PagSt[0].Mbox=mbox_pag1;
   PagSt[1].Tcb=pag2_tcb;
   PagSt[1].Mbox=mbox_pag2;
   PagSt[2].Tcb=pag3_tcb;
   PagSt[2].Mbox=mbox_pag3;
   PagSt[3].Tcb=pag4_tcb;
   PagSt[3].Mbox=mbox_pag4;
   PagSt[4].Tcb=pag5_tcb;
   PagSt[4].Mbox=mbox_pag5;
   for (fase = 0;fase <NUMPAG;fase++)
      {
      PagSt[fase].priorita=PG_LOW;
      PagSt[fase].mode=PG_TAS;
      PagSt[fase].stat=PG_ATTI;
      PagSt[fase].init(fase);
      }
   fase = -1;
   for (i=0;i<NUMPAG;i++)
      {
      if(PagSt[i].mode == PG_TAS)
         tas(PagSt[i].Tcb);
      else if(PagSt[i].mode==PG_SYN)
         syn(PagSt[i].Tcb,PagSt[i].periodo,PagSt[i].periodo);
      }
   }


/* Task Pag
   Chiamo il corpo del task
   Termino secondo la modalita' prevista
   */


void Pag1()
   {
   PagComune(0);
   return;
   }
void Pag2()
   {
   PagComune(1);
   return;
   }
void Pag3()
   {
   PagComune(2);
   return;
   }
void Pag4()
   {
   PagComune(3);
   return;
   }
void Pag5()
   {
   PagComune(4);
   return;
   }

void PagComune(int ind)
   {
   while(PagSt[ind].stat==PG_ATTI)
      {
      PagSt[ind].corpo();
      if(PagSt[ind].mode==PG_SYN)
         ter();
      }
   ter();
   }

/*
Moduli richiamabili dal PAG per la modifica dei parametri

*/

void ModiAtti(short ind,short modo,short periodo)
   {
   if(ind >= 0 && ind < MAXPAG)
      {
      if(modo == PG_TAS)
         PagSt[ind].mode=modo;
      else if(modo==PG_SYN)
         {
         PagSt[ind].mode=modo;
         PagSt[ind].periodo=periodo;
         }
      }
   }


void ModiPri(short ind,short priorita)
   {
   if(ind >= 0 && ind < MAXPAG)
      {
      if(priorita == PG_LOW && PagSt[ind].priorita==PG_HIGH)
         {
         PagSt[ind].priorita=priorita;
         pri(PagSt[ind].Tcb,priorita+ind);
         }
      else if(priorita == PG_HIGH && PagSt[ind].priorita==PG_LOW)
         {
         PagSt[ind].priorita=priorita;
         pri(PagSt[ind].Tcb,priorita+ind);
         }
      }
   }


void PagTerm(short ind)
   {
   PagSt[ind].stat=PG_DIS;
   }

/* Moduli per interagire con gli eventi  */



short WaitForTimeout(int wto)
   {
   wai(wto);
   return 0;
   }

short WaitForEvent(int wto ,int nevent ,TOKEN * pdb)
   {
   int i,ier;
   int ind;
   TOKEN * ap;
   union { TOKEN p;
           short w[2]; } pd; 
   S_TRIGGER_PAS *p;
   unsigned char vtrig;
//
// cerco chi sono
//
   for(ind=0;ind<MAXPAG;ind++)
      {
      if(wtcbc == PagSt[ind].Tcb)
         break;
      }
   if(ind==MAXPAG)   return -1;
   vtrig= ind +OFFTRIGPAG;      //  pas 128 ...133
   rew(PagSt[ind].Mbox,-1,&i);       // pulisco mbox
   for(i =0,ap=pdb;i< nevent;i++,ap++)
      {
      pd.p=*ap;
      switch(pd.w[1])
         {
         case g1tipaa :
            p=&pasaa[pd.w[0]];
            break;
         case g1tipas :
            p=&pasas[pd.w[0]];
            break;
         case g1tipac :
            p=&pasac[pd.w[0]];
            break;
         case g1tipad :
            p=&pasad[pd.w[0]];
            break;
         case g1tipda :
            p=&pasda[pd.w[0]];
            break;
         case g1tipdc :
            p=&pasdc[pd.w[0]];
            break;
         case g1tipds :
            p=&pasds[pd.w[0]];
            break;
         case g1tipdd :
            p=&pasdd[pd.w[0]];
            break;
         case g1tipor :
            p=&pasor[pd.w[0]];
            break;
         default:
            p = NULL;
         }
      if(p != NULL)
         {
         p->pas=vtrig;
         p->seq=0;
         }
      }

   ier=rew(PagSt[ind].Mbox,wto,&i);

   for(i=0,ap=pdb;i<nevent;i++,ap++)
      {
      pd.p=*ap;
      switch(pd.w[1])
         {
         case g1tipaa :
            p=&pasaa[pd.w[0]];
            break;
         case g1tipas :
            p=&pasas[pd.w[0]];
            break;
         case g1tipac :
            p=&pasac[pd.w[0]];
            break;
         case g1tipad :
            p=&pasad[pd.w[0]];
            break;
         case g1tipda :
            p=&pasda[pd.w[0]];
            break;
         case g1tipdc :
            p=&pasdc[pd.w[0]];
            break;
         case g1tipds :
            p=&pasds[pd.w[0]];
            break;
         case g1tipdd :
            p=&pasdd[pd.w[0]];
            break;
         case g1tipor :
            p=&pasor[pd.w[0]];
            break;
         default:
            p = NULL;
         }
      if((p != NULL) && (p->pas == vtrig))
         {
         p->pas = (unsigned char) -1;
         p->seq = (unsigned char) -1;
         }
      }
   return ier;
   }


/* Routine utilizzata da trigger per sbloccare un pag */

void trigpag(short ipag)
   {
   if (ipag < MAXPAG)
      {
      tra(PagSt[ipag].Mbox,1);
      }
   }


#define fnomi 0		
extern FILE *fpp[];	      /* tabella dei files pointer  */


TOKEN CnvTag(char *tag)        
   {
   union { TOKEN p;
           short w[2]; } pd; 
	char sigla[12];
	short i;
   long  displ;
	short posiz;
	memset(sigla,'\0',12);
	strncpy(sigla,tag,10);
   if(ricerca(sigla,&pd.w[0],&pd.w[1],&displ,&posiz,fpp[fnomi]))
      return -1;
   else
      return pd.p;
   }



extern DB_HEADER h_db;				// header data base

short ReadDb(TOKEN pdb ,short *f,float * v)
   {
   union { TOKEN p;
           short w[2]; } pd; 
   short error=0;
   short ind;

   pd.p=pdb; 
   ind=pd.w[0];
   switch(pd.w[1])
      {
      case g1tipaa :
         if (pd.w[0] < h_db.dimaa)
            {
      		*v=dbaav[ind];
	   		*f=dbaaf[ind];
            }
         else
            error=1;
			break;
      case g1tipas :
         if (pd.w[0] < h_db.dimas)
            {
				*v=dbasv[ind];
				*f=dbasf[ind];
            }
         else
            error=1;
			break;
      case g1tipac :
         if (pd.w[0] < h_db.dimac)
            {
				*v=dbacv[ind];
				*f=dbacf[ind];
            }
         else
            error=1;
			break;
      case g1tipad :
         if (pd.w[0] < h_db.dimad)
            {
				*v=dbadv[ind];
				*f=dbadf[ind];
            }
         else
            error=1;
			break;
      case g1tipda :
         if (pd.w[0] < h_db.dimda)
			   *f =dbda[ind];
         else
            error=1;
			break;
      case g1tipds :
         if (pd.w[0] < h_db.dimds)
			   *f =dbds[ind];
         else
            error=1;
			break;
      case g1tipdc :
         if (pd.w[0] < h_db.dimdc)
			   *f =dbdc[ind];
         else
            error=1;
			break;
      case g1tipdd :
         if (pd.w[0] < h_db.dimdd)
			   *f =dbdd[ind];
         else
            error=1;
			break;
      case g1tipor :
         if (pd.w[0] < h_db.dimor)
			   *f =dbosc[ind];
         else
            error=1;
			break;
      default:
            error=1;
				break;
		}
   if(error)
      return -1;
   else
      return 0;
   }


short WriteDbOp(TOKEN pdb ,short op,short f, float v)       
	{
	short i,err;
	S_MCSP m;
   QUEUE_PACKET vpack;
   union { long p;
           short w[2]; } pd; 
	

	vpack.que = c_mmii;
	vpack.flg = MSG_WAIT;
	vpack.wto = 0;
	vpack.amsg = (char *)  &m;
	vpack.lmsg=sizeof(S_MCSP);
	m.indice=mcsp;
	m.zona=0;
	m.video=0;
	strcpy(m.pag,"$MODI   ");
	m.point[0]=0;

	err=0;
   pd.p=pdb;

	switch(pd.w[1])
   	{
	   case g1tipaa :
	   case g1tipas :
	   case g1tipac :
	   case g1tipad :
	   case g1tipao :
		   switch(op)
   			{
				case f_mvaf:
				case f_mval:
				case f_forz:
				case f_fsca:
				case f_isca:
	   			m.tipo=m_analogico;
					m.funz=op;
					m.dat.f=v;
					m.dat.s[2]=f;
					break;
				case m_anls	:
				case m_anlc	:
				case m_anhc	:
				case m_anhs	:
					m.tipo=op;
					m.funz=f_mval;
					m.dat.f=v;
					m.dat.s[2]=f;
					break;
				default:
					err=1;
				}
			break;
	   case g1tipda :
	   case g1tipds :
	   case g1tipdc :
	   case g1tipdd :
	   case g1tipdo :
			switch(op)
				{
				case f_mvaf:
				case f_mval:
				case f_forz:
				case f_fsca:
				case f_isca:
					m.tipo=m_digitale;
					m.funz=op;
					m.dat.s[0]= f;
					break;
				default:
					err=1;
				}
			break;
	   case g1tipor :
			switch(op)
				{
				case f_mvaf:
				case f_mval:
				case f_forz:
				case f_fsca:
				case f_isca:
					m.tipo=m_organo;
					m.funz=op;
					m.dat.s[0]=f;
					break;
				default:
					err=1;
				}
			break;
      default:
         break;
		}
	if(!err)
		{
		m.point[0]=1;		// non invio risposta
		m.point[1]=pd.w[1];
		m.point[2]=pd.w[0];
		enqueue(&vpack);
      return 0;
		}
   else
      return 1;
	}



short WriteDb(long pdb , short flag, float v)       
   {
   union { long p;
           short w[2]; } pd; 

   short f1 ;
   S_MALLA mess ;
   S_TRATG messd ;  /* struttura accodamento allarmi al task asinct */ 
   QUEUE_PACKET pack;
   short trat;
   short *pf;
   short st_attendi,st_logico,st_st,st_au;

   pd.p=pdb;
   switch (pd.w[1])
      {
      case g1tipac:
         if(pd.w[0] < 0 || pd.w[0] >=h_db.dimac) 
            { 
//            pscserr(ERR_TASK,TASK_ACQUI,ROU_SETAA,pd.w[0],SYS_CONT);
            return -1;
            }
         if(dbacu[pd.w[0]]==-1) return -1;			// punto non installato
/*
	il valore viene inserito in data base solo se il
	punto non e` fuori scansione o forzato
*/
         pf=&dbacf[pd.w[0]];

         if(((*pf) & mask_afs) || ((*pf) & mask_afz))
            return -1 ;
//
// assegno il valore e....
         dbacv[pd.w[0]]=v ;
// i flag AU e ST
         *pf &= ~(AN_ST |AN_AU);
         f1 = flag & (AN_ST | AN_AU);
         *pf |= f1;
// controllo FA
         if( flag & AN_FA)
            flag=1;             // isolo FA
         else
            flag=0;
         if ( flag != bitvalue(pf,g2an_fa))
            {
      	   bitset(pf,g2an_fa,flag);
            mess.sogl1=(unsigned char) -1 ;
            mess.sogl2=0 ;
            mess.punt=pd.w[0] ;
         	trat=((dbacal[pd.w[0]].tr_bdm & M_LSEVA)>>6) + (dbacal[pd.w[0]].tr_bdm>>12);  
	         if(flag)
               { mess.ertr=(trat | 0x80); mess.satt=non_att; mess.sprec=mis_norm ; }
         	else
               { mess.ertr=trat ; mess.satt=mis_norm ; mess.sprec=non_att; }

            pack.que=c_visall;
            pack.amsg=(char*)&mess;
            pack.lmsg=sizeof(S_MALLA);
            pack.flg=MSG_WAIT;
            pack.wto=0;
            mess.ext=g1tipac;
            enqueue(&pack) ;
            }
         verifall(pd.w[0],g1tipac) ;
         break;
      case g1tipdc:
         if(pd.w[0] < 0 || pd.w[0] >=h_db.dimdc) 
            { 
//            pscserr(ERR_TASK,TASK_ACQUI,ROU_SETAA,pd.w[0],SYS_CONT);
            return -1;
            }
         if(dbdcu[pd.w[0]]==-1) return -1;			// punto non installato

         pf= & dbdc[pd.w[0]];

         st_logico= (flag & DI_SL) ?1:0;
         st_attendi= (flag & DI_FA) ?1:0;
         st_au= (flag & DI_AU) ? 1:0;
         st_st= (flag & DI_ST) ? 1:0;
/*
	aggiorno comunque flag fisici
*/
         bitset(pf,g2di_afa,st_attendi);
         bitset(pf,g2di_asl,st_logico) ;

         if(bitvalue(pf,g2di_fs) || bitvalue(pf,g2di_fz)) return -1;


         pack.que=c_digor;
         pack.flg=MSG_WAIT;
         pack.wto=0;
         pack.amsg=(char*)&messd;
         pack.lmsg=sizeof(S_TRATG);

/*
	verifico se si e' avuta una variazione di stato
	se il punto non e` forzato o fuori scansione aggiorno
	il data base di sistema tenendo  
	ed accodo il punto al task tratg per le
	inibizioni le calcolate e l`emissione dell`eventuale
	allarme
*/

         messd.ext= g1tipdc ;
         messd.indice= pd.w[0] ;

         if(st_logico != bitvalue(pf,g2di_sl))
            {
            inv_slave=1;
		      messd.stato= st_logico;
        		bitset(pf,g2di_sl,st_logico) ;
            messd.mess= macdi ;                     /* preparo messfer da accodare */
            enqueue(&pack); 
            }
         if(st_attendi != bitvalue(pf,g2di_fa))
            {
            inv_slave=1;
  		      bitset(pf,g2di_fa,st_attendi);
            messd.mess= mfadi ;                     /* preparo messaggio da accodare */
        		messd.stato= st_attendi;
            enqueue(&pack); 
            }
	      bitset(pf,g2di_au,st_au);
	      bitset(pf,g2di_st,st_st);
         break;
      default:
         return -1;
      }
   return 0;
   }

/*
	Routine per accedere alle risorse riservate ai pag.
	Le risorse sono mailbox utilizzate unicamente come semafori.
	Ricordare di inserire durante la fase di inizializzazione 
	la risorsa nella mailbox.
 */

short GetPagRes(short id,short to)
	{
	int appo;

	if(id > ID_RES5 || id < ID_RES1)
		return (short) -1;
	return rew(*pagres[id],to,&appo);
	}
	 

// Esegue la tra sulla mail box risorsa. Ritorna 1 se la
// mailbox e' occupata.

short SetPagRes(short id)
	{
	if(id > ID_RES5 || id < ID_RES1)
		return (short) -1;
	return (tra(* pagres[id], -1) ? 1 : 0);
	}
	
