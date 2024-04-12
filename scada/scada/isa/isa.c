/**********************************************************************
*
*       C Source:               isa.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Dec 16 15:42:08 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: isa.c-5 %  (%full_filespec: isa.c-5:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   Isa.c
      20 Ottobre 1994 Corretta gestione scrittura organi e digitali

        3 Novembre 1994
        Inserimento controllo dell'arrivo di almeno un messaggio al minuto
        (vedi anche attiper) per ogni connessione ISA attiva
        Se cio' non avviene viene alzato il flag di FA relativo al digitale
        di diagnostica della connessione

      30 Novembre 1994
      Aggiunta gestione messaggi verso rete SAMP.
      Giugno 1995        
      Agginuto messaggi per Enel SCC - aggiornamento dati per stringhe
*/


#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

#if !defined OSF1_40 && !defined LINUX
#pragma pack(1)
#endif

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "diagnodi.inc"
#include "comunic.inc"
#include "mesprocv.inc"

#include "mesqueue.h"
#include "netmsg.h"
#include "isarc.inc"
#include "messcada.inc"
#include "dconf.inc"
#include "isa.h"


#define fnomi 0     

extern FILE *fpp[];       /* tabella dei files pointer  */
extern char release_slave[];
extern unsigned short isarx,isatx;

U_ISA_MESS messg;

static  QUEUE_PACKET rpack,spack;

#if NCHAN_ISA != 4
 #error "Errore Numero Utenti ISA"
#else
 extern unsigned short cisa_samp1,cisa_samp2,cisa_samp3,cisa_samp4;
 static *tabcode[NCHAN_ISA] = {&cisa_samp1,&cisa_samp2,&cisa_samp3,&cisa_samp4};
 /* tabella andamento trasferimento per msputfile */
 static struct _TABPUTF { 
    char nomefile[14];
    short h;    /* handle file locale */
    long  total;    /* lunghezza totale (byte) */
    long  ricev;    /* ricevuti (byte) */
    short err;      /* errore se > 0 */
 } tabputf[NCHAN_ISA] = 
    {-1,0L,0L,0,  -1,0L,0L,0,  -1,0L,0L,0,  -1,0L,0L,0,};  
#endif
/*
   puntatori aree per memorizzazione per dati aggiornati da isa
*/
char * isaAC;
char * isaDC;   



/****************************************************************************/
/* Gestione messaggio MSGSSAMP                                              */
/*   Trasmette il messaggio contenuto nel frame al nodo SAMP indicato.      */
/*   N.B. In questa routine viene trasformato l'indice dell'utente ISA      */
/*        che ha trasmesso il messaggio nell'equivalente indice di coda     */
/*        per la risposta del nodo SAMP.                                    */
/****************************************************************************/
void msgssamp(void)
{

if(messg.h.ch >= NCHAN_ISA) return;// Se utente non valido ignora il messaggio

/* Trasforma il codice Ethernet dell'utente ISA nell'indice della coda di */
/* collegamento ISA -> SAMP. */

messg.ssamp.info.appl_Eth = *tabcode[messg.ssamp.h.ch];

/* Invia il messaggio MI_STR da accodare al gestore driver di SAMP. */

invstring(messg.ssamp.info.nodo_samp,          // Nodo SAMP di destinazione
          rpack.lmsg,                          // Lunghezza del pacchetto
          (unsigned char *) &messg);           // Indirizzo del pacchetto

}


/****************************************************************************/
/* Gestione messaggio MSGRSTRI                                              */
/*   Verifica se vi sono stringhe pendenti per il richiedente. In caso      */
/*   affermativo trasmette il contenuto della coda. In caso negativo        */
/*   trasmette un messaggio vuoto.                                          */
/****************************************************************************/
void msgrstri(void)
{
QUEUE_PACKET strpack;


if(messg.h.ch >= NCHAN_ISA) return;// Se utente non valido ignora il messaggio

/* Prepara il pacchetto di scodamento dalla coda riservata all'utente ISA. */

strpack.flg  = MSG_NOWAIT;        // Interroga la coda senza attendere messaggi
strpack.amsg = (char *) &messg.rgetm.hs;
strpack.que  = *tabcode[messg.rgetm.h.ch]; // Indice coda dell'utente ISA

/* Che abbia o meno trovato qualcosa nella coda, accoda un messaggio di */
/* risposta all'utente ISA contenente l'header SAMP. */

if(dequeue(&strpack)) strpack.lmsg = sizeof(HEADSAMP); // Se non scoda nulla!
spack.lmsg = sizeof(HEADISA) + strpack.lmsg; // lunghezza messaggio SAMP
enqueue(&spack);
}

/****************************************************************************/
/* Gestione messaggio MSGETMSG                                              */
/*   Verifica se vi sono stringhe pendenti per il richiedente. In caso      */
/*   affermativo trasmette il contenuto della coda. In caso negativo        */
/*   trasmette un messaggio vuoto.                                          */
/****************************************************************************/
void msgrmesg(void)
{
QUEUE_PACKET strpack;


if(messg.h.ch >= NCHAN_ISA) return;// Se utente non valido ignora il messaggio

/* Prepara il pacchetto di scodamento dalla coda riservata all'utente ISA. */

strpack.flg  = MSG_NOWAIT;        // Interroga la coda senza attendere messaggi
strpack.amsg = (char *) &messg.brgetmsg.buffer;
strpack.que  = *tabcode[messg.bsgetmsg.h.ch]; // Indice coda dell'utente ISA

messg.bsgetmsg.h.cod = MRGETMSG;

/* Che abbia o meno trovato qualcosa nella coda, accoda un messaggio di */
/* risposta all'utente ISA contenente l'header SAMP. */

if(dequeue(&strpack)) 
    strpack.lmsg = 2; // Se non scoda nulla! c'e' la lunghezza
messg.brgetmsg.len = strpack.lmsg;  /* lunghezza buffer per utente */  
spack.lmsg = sizeof(HEADISA) + strpack.lmsg+sizeof(short); 
enqueue(&spack);
}

/* gestione messaggio SCNVSD
   converte le stringhe delle sigle in puntatori in DB */

mscnvsd()
    {
    PUNDB *point=messg.brcnvsd.token;
    char *psigle=messg.bscnvsd.sigle;
    char sigla[12];
    short i;
   long  displ;
    short posiz,punt,ext;

    messg.brcnvsd.h.cod=MRCNVSD;
    for(i=0;i<messg.brcnvsd.npunti;i++)
        {
        memset(sigla,'\0',12);
        strncpy(sigla,psigle,10);
       if(ricerca(sigla,&punt,&ext,&displ,&posiz,fpp[fnomi]))   punt=ext=-1;
        point->p = punt;
        point->e = ext;
        point++;
        psigle +=10;
        }
    spack.lmsg=sizeof(HEADISA) + 2 + messg.brcnvsd.npunti * 4;
   enqueue(&spack);
    }

/* messaggio SGETSD
   invia i dati secondo i puntatori passati */

msgetsd()
    {
    short i=messg.brgetsd.npunti -1;
    register ind;
    PUNDB * p= &messg.bsgetsd.token[i];
    VDB * v= &messg.brgetsd.val[i];

    messg.brgetsd.h.cod=MRGETSD;

    for(;i>=0;i--,p--,v--)
        {
        ind=p->p;
        switch(p->e)
            {
          case g1tipaa :
                v->m.v=dbaav[ind];
                v->m.flag=dbaaf[ind];
                break;
          case g1tipas :
                v->m.v=dbasv[ind];
                v->m.flag=dbasf[ind];
                break;
          case g1tipac :
                v->m.v=dbacv[ind];
                v->m.flag=dbacf[ind];
                break;
          case g1tipad :
                v->m.v=dbadv[ind];
                v->m.flag=dbadf[ind];
                break;
           case g1tipda :
               v->d =dbda[ind];
                v->w[1]=v->w[2]=-1;
                break;
           case g1tipds :
               v->d =dbds[ind];
                v->w[1]=v->w[2]=-1;
                break;
           case g1tipdc :
               v->d =dbdc[ind];
                v->w[1]=v->w[2]=-1;
                break;
           case g1tipdd :
               v->d =dbdd[ind];
                v->w[1]=v->w[2]=-1;
                break;
           case g1tipor :
               v->d =dbosc[ind];
                v->w[1]=v->w[2]=-1;
                break;
            default:
                v->w[0]=v->w[1]=v->w[2]=-1;
                break;
            }
        }
    spack.lmsg=sizeof(HEADISA) + 2 + messg.brgetsd.npunti * sizeof(VDB);
   enqueue(&spack);
    }

/* messaggio SGETSTR
   invia i dati stringhe secondo puntatori passati */

msgetstr()
    {
    short i=messg.brgetstr.npunti -1;
    register ind;
    PUNDB * p= &messg.bsgetsd.token[i];
    VDBSTR * v= &messg.brgetstr.val[i];

    messg.brgetstr.h.cod=MRGETSTR;

    for(;i>=0;i--,p--,v--)
        {
        ind=p->p;
        switch(p->e)
            {
          case g1tipst :
                v->flag=0;
                memcpy(v->w,&dbstv[ind*g0lunst],g0lunst);
                break;
           default:
                v->flag=-1;
                memset(v->w,-1,g0lunst);
            }
        }
    spack.lmsg=sizeof(HEADISA) + 2 + messg.brgetsd.npunti * sizeof(VDBSTR);
   enqueue(&spack);
    }

/* messaggio LSFILE invia l' elenco dei file */

mlsfile()
{
struct find_t c_file;
char   *p = messg.brlsfile.b;
char   *fine = p + LENGBUF;
char   path[FILENAME_MAX+1];


messg.brlsfile.h.cod = MRLSFILE;
sprintf(path,"%s\\%s",conf[RTF],messg.bslsfile.lista);
*p = 0;
if(!_dos_findfirst(path,_A_NORMAL,&c_file))
   {
   do
      {
      strcpy(p,c_file.name);
      p = p + strlen(c_file.name) + 1;
      if(p >= fine)
         {
         *p++ = 0;
         messg.brlsfile.flgcontinue = 1;
         spack.lmsg = p - (char *) &messg;
         enqueue(&spack);
         p = messg.brlsfile.b;
         }
      } 
   while(!_dos_findnext(&c_file));
   }
*p++ = 0;
messg.brlsfile.flgcontinue = 0;
spack.lmsg = p - (char *) &messg;
enqueue(&spack);
}

msgetfile()
{
char  path[64];
long  offs,total;
short len;
short h;


messg.brgetfile.h.cod = MRGETFILE;
sprintf(path,"%s\\%s",conf[RTF],messg.bsgetfile.file);
if((h = open(path,O_RDONLY | O_BINARY)) == -1)
   {
   messg.brgetfile.total  = total = 0;
   messg.brgetfile.offset = offs  = 0;
   }
else
   {
   messg.brgetfile.offset = offs  = 0L;
   messg.brgetfile.total  = total = lseek(h,0L,SEEK_END);
   lseek(h,0L,SEEK_SET);
   }

while(1)
   {
   if((total - offs) > LENGBUF) len = LENGBUF;
   else                         len = total - offs;
   if(len <= 0) break;

   messg.brgetfile.len = len;
   read(h,messg.brgetfile.b,messg.brgetfile.len);
   spack.lmsg = sizeof(SGETFILE) + len;
   enqueue(&spack);
   offs = offs + len;
   messg.brgetfile.offset = offs;
   }

   if(h != -1) close(h);
 }

msputfile(struct _TABPUTF *pTabPutF)
{
    char  path[64];
    long  offs,total;
    short len;
    short h = pTabPutF->h;
    short modo;

    if (messg.bsputfile.modo == 2) {
        modo = O_TRUNC | O_WRONLY |O_BINARY;
    }
    else {
        modo = O_CREAT | O_EXCL | O_WRONLY | O_BINARY;
    }        
                
    inizio:
    if (h==-1) {    /* file non aperto */
        sprintf(path,"%s\\%s",conf[RTF],messg.bsputfile.file);
        strcpy(pTabPutF->nomefile,messg.bsputfile.file);
        if((h = open(path,modo,S_IREAD | S_IWRITE)) == -1) {
           h = -2;
           pTabPutF->err = 1;
        }
        else
           pTabPutF->err = 0;
        pTabPutF->total = messg.bsputfile.total;
        pTabPutF->ricev = 0;
    }
    else if (h >= 0) {  /* file gia' aperto */
        if (strcmp(messg.bsputfile.file,pTabPutF->nomefile)) { /* nome diverso */
           close(h);
           h=-1;
           goto inizio;
        }
    }       
        
    pTabPutF->ricev+=messg.bsputfile.len;
    if (h >= 0) {    
        len = write(h,messg.bsputfile.b,messg.bsputfile.len);
        if (len != messg.bsputfile.len) {
           pTabPutF->err++; /* inc numero di errori */
        }
    }    
    if(pTabPutF->ricev >= pTabPutF->total) {    /* fine trasf */
       messg.brputfile.h.cod = MRPUTFILE; 
       messg.brputfile.ret = pTabPutF->err;
       spack.lmsg = sizeof(SPUTFILE);
       enqueue(&spack);
       close(h);
       h=-1;
    }
                
    pTabPutF->h = h;    
}

msgetcnf()
    {
    messg.brgetcnf.h.cod=MRGETCNF;
    memcpy(&messg.brgetcnf.hdb,&h_db,sizeof(h_db));
    spack.lmsg=sizeof(RGETCNF);
   enqueue(&spack);
    }



/* messaggio SWRDB
   scrive i dati secondo i puntatori passati */

mswrdb()
    {
    short i,err;
    WRDB *w;
    S_MCSP m;
   QUEUE_PACKET vpack;
    

    vpack.que = c_mmii;
    vpack.flg = MSG_WAIT;
    vpack.wto = 0;
    vpack.amsg = (char *)  &m;
    vpack.lmsg=sizeof(S_MCSP);
    m.indice=mcsp;
    m.zona=0;
    m.video=1;
    strcpy(m.pag,"$MODI   ");
    m.point[0]=0;


    messg.brwrdb.h.cod = MRWRSD;

    for(i=0;i<messg.bswrdb.npunti;i++)
        {
        err=0;
        w= &messg.bswrdb.w[i];
        switch(w->p.e)
            {
          case g1tipac :
            *(isaAC+w->p.p)|=1 << messg.h.ch;  // memorizzo aggiornamento da connessione ISA
          case g1tipaa :
          case g1tipas :
          case g1tipad :
          case g1tipao :
                switch(w->op)
                    {
                    case ISA_MVAF:
                    case ISA_MVAL:
                    case ISA_MFORZ:
                    case ISA_MFSCA:
                    case ISA_MISCA:
                        m.tipo=m_analogico;
                        m.funz=w->op;
                        m.dat.f=w->f;
                        m.dat.s[2]=w->flag;
                        break;
                    case ISA_MLL:
                    case ISA_ML:
                    case ISA_MHH:
                    case ISA_MH:
                        m.tipo=w->op;
                        m.funz=ISA_MVAL;
                        m.dat.f=w->f;
                        m.dat.s[2]=w->flag;
                        break;
                    default:
                        err=1;
                    }
                break;
           case g1tipdc :
               *(isaDC+w->p.p)|=1 << messg.h.ch;     // memorizzo aggiornamento da connessione ISA
           case g1tipda :
           case g1tipds :
           case g1tipdd :
           case g1tipdo :
                switch(w->op)
                    {
                    case ISA_MVAF:
                    case ISA_MVAL:
                    case ISA_MFORZ:
                    case ISA_MFSCA:
                    case ISA_MISCA:
                        m.tipo=m_digitale;
                        m.funz=w->op;
                        if(w->f) m.dat.c[0]=1;  // stato 0 o 1
                        else m.dat.c[0]=0;
 //                     m.dat.c[0]=*((char *) &w->f);
                        m.dat.c[0]=m.dat.c[0]+ (w->flag & 0x00FE);  // flag
                        break;
                    default:
                        err=1;
                    }
                break;
           case g1tipor :
                switch(w->op)
                    {
                    case ISA_MFORZ:
                    case ISA_MFSCA:
                    case ISA_MISCA:
                        m.tipo=m_organo;
                        m.funz=w->op;
                        m.dat.c[0]=0;
                        m.dat.c[1]=w->f;
                        break;
                    default:
                        err=1;
                    }
                break;
            }
        if(!err)
            {
            m.point[0]=1;       // non invio risposta
            m.point[1]=w->p.e;
            m.point[2]=w->p.p;
            enqueue(&vpack);
            }
        }

    spack.lmsg=sizeof(HEADISA) + 2 + messg.brwrdb.npunti * sizeof(WRDB);
   enqueue(&spack);
    }

/* messaggio SWRDBSTR
   scrive i dati secondo i puntatori passati solo per stringhe*/

mswrdbstr()
    {
    short i,err;
    WRDBSTR *w;
    S_MCSP m;
   QUEUE_PACKET vpack;
    

    vpack.que = c_mmii;
    vpack.flg = MSG_WAIT;
    vpack.wto = 0;
    vpack.amsg = (char *)  &m;
    vpack.lmsg=sizeof(S_MCSP);
    m.indice=mcsp;
    m.zona=0;
    m.video=1;
    strcpy(m.pag,"$MODI   ");
    m.point[0]=0;


    messg.brwrdb.h.cod = MRWRSTR;

    for(i=0;i<messg.bswrdbstr.npunti;i++)
        {
        err=0;
        w= &messg.bswrdbstr.w[i];
        switch(w->p.e)
            {
            case g1tipst:        // solo stringhe
                switch(w->op)
                    {
                    case ISA_MVAF:
                    case ISA_MVAL:
                    case ISA_MFORZ:
                    case ISA_MFSCA:
                    case ISA_MISCA:
                        m.tipo=m_stringa;
                        m.funz=w->op;
                  		memcpy(m.dat.c,w->str,g0lunst);
                        break;
                    default:
                        err=1;
                    }
           break;
           default:
               err=1;
           break;
            }
        if(!err)
            {
            m.point[0]=1;       // non invio risposta
            m.point[1]=w->p.e;
            m.point[2]=w->p.p;
            enqueue(&vpack);
            }
        }

    spack.lmsg=sizeof(HEADISA) + 2 ;
   enqueue(&spack);
    }


msgetinf()
    {
    short i=messg.brgetinf.npunti -1;
    register ind;
    PUNDB * p= &messg.bsgetsd.token[i];
    STINF * v= &messg.brgetinf.stinf[i];

    messg.brgetsd.h.cod=MRGETINF;

    for(;i>=0;i--,p--,v--)
        {
        isadescr(v,p->e,p->p);
        }
    spack.lmsg=sizeof(HEADISA) + 2 + messg.brgetinf.npunti * sizeof(STINF);
   enqueue(&spack);
    }


_isa()
    {
    short app;
    short i;
    short point;

   isalloc();
   for(i = 0; i < NCHAN_ISA; i++)
        bitset(&dbdd[stnod01+i],g2di_sl,1);     // stato connessione off line
    isadia(-1,-1);

   rpack.flg=MSG_WAIT;
   rpack.amsg=(char *) &messg;
   rpack.que=isarx;
   rpack.wto=0;
   spack.flg=MSG_WAIT;
   spack.amsg=(char *) &messg;
   spack.que=isatx;
   spack.wto=0;

   while(1)
      {
      dequeue(&rpack);
        if(messg.h.cod!=STATOPORTA) isadia(messg.h.ch,1);
        switch( messg.h.cod)
            {
           case STATOSIS:                           // richiesta stato sistema
           case STATOSISES:                          // richiesta stato sistema
              if(!sys_master) messg.ssys.mess=NO_STATOSIS;      // sono slave
              else  messg.ssys.mess=STATOSIS;
              /* messg.ssys.nodo=0; sst eliminato, c'e' l'indice della porta */
              messg.ssys.status=0;
              messg.ssys.rete=0;
              spack.lmsg=sizeof(messg.ssys);


           if(SYS_DUALE)
              {
                  point=stwdb;
                  if(bitvalue(&dbdd[sysab],g2di_sl))
                     {
                       messg.ssys.status=MASK_IDEN;         // sistema B
                       point=stwda;                     // duale A
                     }
                  if(bitvalue(&dbdd[master],g2di_sl)) messg.ssys.status=messg.ssys.status | MASK_MASTER;
                  if(bitvalue(&dbdd[point],g2di_sl)) messg.ssys.status=messg.ssys.status | MASK_WDDUALE;
                  if(messg.h.cod==STATOSIS)
                     memcpy(messg.ssys.rel_duale,release_slave,4);
                  else
                  {
                     memcpy(messg.ssys.rel_duale,release_slave,2);
            	      memcpy(&messg.ssys.rel_duale[2],&release_slave[3],2);
                  }
               }
            else
               {
                  messg.ssys.status=MASK_MASTER;                // singolo A Master
                  memset(messg.ssys.rel_duale,0,4);
               }
              if(messg.h.cod==STATOSIS)
                  memcpy(messg.ssys.rel_propria,h_db.release,4);
              else
              {
                  memcpy(messg.ssys.rel_propria,h_db.release,2);
                  memcpy(&messg.ssys.rel_propria[2],&h_db.release[3],2);
               }
              messg.ssys.n_video=num_video;
              memcpy(messg.ssys.stvideo,0,num_video*2);
              enqueue(&spack);
              break;

         case MSGSSAMP:                  // "Stringa per nodo SAMP"
            msgssamp();
            break;
         case MSGRSTRI:                  // "Richiesta Stringhe Pendenti da SAMP"
            msgrstri();
            break;
         case MSGETMSG:                  // "Richiesta messaggi pendenti per SCC Enel"
            msgrmesg();
            break;
            case MSCNVSD:
                mscnvsd();
                break;
            case MSGETSD:
                msgetsd();
                break;
            case MSGETSTR:       // richiesta dati solo stringhe
                msgetstr();
                break;
            case MSLSFILE:
            case MSLSFILX:      /* non trattato in questa versione */
                mlsfile();
                break;
            case MSGETFILE:
            case MSGETFILX:     /* non trattato in questa versione */
                msgetfile();
                break;
            case MSPUTFILE:
                if(messg.h.ch < NCHAN_ISA) // Se utente valido 
                   msputfile(&tabputf[messg.h.ch]);
                break;
            case MSGETCNF:
                msgetcnf();
                break;
            case MSWRSD:
                mswrdb();
                break;
            case MSWRSTR:         // scrittura valori stringhe
                mswrdbstr();
                break;
            case MSGETINF:
                msgetinf();
                break;
            case STATOPORTA:
            diagnet(stnod01,&messg,&app);
                if(bitvalue(&dbdd[stnod01+app],g2di_sl)) isadia(app,-1);    // off line
                else isadia(app,1);                                                 // on line
                break;
        case CL_FLG*256+mflbgpr:        // richiesta file libro giornale presenti
            ges_mflbgpr();
            break;
        case CL_FLG*256+mapr:         // richiesta archivi presenti
            ges_mapr();
            break;
        case CL_FLG*256+mefr:         // richiesta elenco file singolo archivio
            ges_meflgr();
            break;
        case CL_FLG*256+mtfdr: case CL_FLG*256+mtfar:       // richiesta trasmissione file (descrittore/archivio)
            ges_mtfdr();
            break;
            default:
                printf("\n ISA: Messaggio Sconosciuto %d ",messg.h.cod);
                break;
            }
        }
    }
