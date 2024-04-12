/**********************************************************************
*
*       C Source:               gerarch.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Oct 27 15:47:35 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: gerarch.c-tmp %  (%full_filespec: gerarch.c-tmp:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

/* Calcola il numero di misure in allarme che soddisfano la
   gerarchia e la zona  caratteristiche della calcolata
   solamente se c'e' stata una variazione nel corrispondente 
   data base allarmi.                                        */
/*******************************************************************************

		Modificata da Fabio Aprile '97.

Viene presa in esame un solo tipo di calcolata (PEN$A). 
Le altre calcolate PEN$M ARC$A ecc. non sono piu' utilizzate.
Nella PEN$A viene inserita non piu' la somma degli allarmi
relativa a quella gerarchia, ma semplicemente la situazione allarmi 
di quella gerarchia.

La situazione allarmi e' cosi' rappresentata:
from LSB to MSB
		PEN
||   | N | F | M | S | T | W | A |     (Allarmi pendenti)
   7   6   5   4   3   2   1   0

		ARC		
||   | N | F | M | S | T | W | A  |    (Allarmi archiviati)
  15  14  13  12  11  10   9   8    

                RIE             
||   | N | F | M | S | T | W | A  |    (Allarmi in rientro)
  23  22  21  20  19  18  17   16   

(LSParte di un int o in questo caso di un float)
	
Per ogni PEN$A di ogni gerarchia viene consultato il database globale
degli allarmi:
per ogni allarme del database, che ha una gerarchia "figlia" di quella 
di PEN$A, si alza il bit di PEN$A, corrispondente al tipo di allarme trovato
(S,T,W,A  e ARC e PEN ).

In questa fase vengono esaminati solamente allarmi di tipo da.
*******************************************************************************/
#include <osf1.h>
#include <stdio.h>
#include <string.h>

#include "switch.inc"
#include "maxpar.inc"
#include "g2comdb.inc"
#include "g1tipdb.inc"
#include "calas.inc"
#include "messcada.inc"
#include "allar.inc"

#ifdef GERARC

extern char cAbilCalcGer[];
int kk,kkk;
gerarch()
{
#if defined ALARM_SIGNAL
char TipoAll;  // tipo di allarme segnale 0..64
#endif
short j;
short flag;		/* Flag della misura considerata per determinare FA della calcolata */
short nLevToCheck;	/* N. di livelli della gerarchia significativi cioe' != -1 */
short sDbAll;		/* Il database allarmi cui la calcolata si riferisce */
short sZona;		/* La zona cui la calcolata si riferisce */
#ifdef PROVA_GERAR
int iCont=0;		/* Contatore di appoggio dei punti che soddisfano la gerarchia */
#endif
int iCont=0;          /* Setto a 0x0 il contenitore situazione all */
int appoggio;		/* Da levare */
int numero_bit=0;      /* maschera per iCont			*/
char *pchGer;		/* Puntatore alla gerarchia da soddisfare */
struct buff_all *pall;	/* Puntatore per la scansione del database allarmi */
char *app1,*app2;
int kk;

/* Conta a partite dal byte meno significativo quanti livelli
   della gerarchia devono essere considerati, diversi da -1   */

pchGer=(char *)&tab->corrente->g.gerac;
for(nLevToCheck=0;nLevToCheck<n_gerarchie && *pchGer!=-1;pchGer++,nLevToCheck++)
    ;
	

pchGer=(char *)&tab->corrente->g.gerac;
/* Indice del data base allarmi */
sDbAll=tab->corrente->g.sDbAll-1;

/* Zona di selezione della calcolata */
sZona=tab->corrente->g.sZona;

#if defined ALARM_SIGNAL
/* prelevo il tipo di segnale allarme dalla struttura della calcolata,
   se e' presente
*/
TipoAll=tab->corrente->g.sTipoAll;
#endif

/* Scandisce tutte le misure del data base allarmi 
   se questo e' definito                           */
if(bDbsAll[sDbAll].def)
{
	pall=bDbsAll[sDbAll].pall;
	for(j=0;j<bDbsAll[sDbAll].pout;j++,pall++)
	{
	/*
	   In base al tipo di calcolata controlla che 
	   l'allarme sia in archivio o sia pendente.
	*/
#ifdef PROVACALC

	if((pall->mask & 0x8000 && tab->corrente->g.tipoc==AS_GERARCHIA_ALLPENDENTI) || 
	   (!(pall->mask & 0x8000) && tab->corrente->g.tipoc==AS_GERARCHIA_ALLARCHIVIATI))
		continue;
#endif
/*********************************************

	Nuova calcolata
Se allarme non = a PEN$A allora  non esaminare allarme

**********************************************/

	if((tab->corrente->g.tipoc==AS_GERARCHIA_ALLPENDENTI) && (TipoAll!=0) ||	(tab->corrente->g.tipoc==AS_GERARCHIA_ALLARCHIVIATI))
	   
		continue;

#if defined ALARM_SIGNAL
	/*
		se e' definito il tipo di allarme vengono
		analizzati soltanto i digitali acquisiti
	*/
	if(((TipoAll!= -1)&&(pall->m.ext!=g1tipda) ) || (pall->m.punt==-1))
		continue;
#endif
             

        /*
                 Verifico che la calcolata sia relativa 
                 ad una gerarchia
        */
	if(!nLevToCheck)
		{
		continue;
		}

		switch(pall->m.ext)
		{
			/* analogici acquisiti */
			case g1tipaa:
				flag=dbaaf[pall->m.punt];
				if((!memcmp(dbaag+pall->m.punt,pchGer,nLevToCheck) && dbaau[pall->m.punt]==sZona))
					iCont++;
				break;

			/* analogici calcolati non standard */
			case g1tipac:
				flag=dbacf[pall->m.punt];
				if((!memcmp(dbacg+pall->m.punt,pchGer,nLevToCheck) && dbacu[pall->m.punt]==sZona))
					iCont++;
				break;

			/* analogici calcolati standard */
			case g1tipas:
				flag=dbasf[pall->m.punt];
				if((!memcmp(dbasg+pall->m.punt,pchGer,nLevToCheck) && dbasu[pall->m.punt]==sZona))
					iCont++;
				break;

			/* analogici di diagnostica */
			case g1tipad:
				flag=dbadf[pall->m.punt];
				if((!memcmp(dbadg+pall->m.punt,pchGer,nLevToCheck) && dbadu[pall->m.punt]==sZona))
					iCont++;
				break;

			/* analogici di uscita */
			case g1tipao:
				flag=dbaof[pall->m.punt];
				if(!memcmp(dbaog+pall->m.punt,pchGer,nLevToCheck) && dbaou[pall->m.punt]==sZona)
					iCont++;
				break;

			/* digitali  acquisiti */
			case g1tipda:
				flag=dbda[pall->m.punt];
/*
Controllo che il numero di gerarchie da considerare sia signifiactivo
*/
/*
Vado a considerare tutti gli allarmi di una certa gerarchia indipendentemente
dalla zona a cui appartiene la calcolata
*/
/*
Vecchio codice:
				if((!memcmp(dbdag+pall->m.punt,pchGer,nLevToCheck) && dbdau[pall->m.punt]==sZona))
*/
				if((!memcmp(dbdag+pall->m.punt,pchGer,
					nLevToCheck) ))
				  {
/*
In base al tipo di allarme attivo il bit opportuno.
Modifiche by Fabio per Teleperm.
*/

				  switch(GetAlarmValue(pall->m.punt))
					{
					case ALL_A:
					numero_bit=0;	
					break;

					case ALL_W:
					numero_bit=1;
                                	break;

					case ALL_T:
					numero_bit=2;
                                	break;

					case ALL_S:
					numero_bit=3;
                                	break;
				
					case ALL_M:
					numero_bit=4;
                                	break;

					case ALL_F:
					numero_bit=5;
                                	break;

					default:
                	                break;
					}

/* Traslo di 4 il No del bit da settare a seconda del tipo di allarme */

			   if(pall->mask & 0x8000) /* all di tipo ARC */
				 {
				 numero_bit =numero_bit+PACK_DIMENSION;	
				 }
			    else if(!(pall->m.ertr & 0x80)) 
				{
				numero_bit = numero_bit+PRIE_DIMENSION;
				}
/*
Setto il bit corrispondente alla situazione allarmi trovata
*/
			   bitset_int(&iCont,numero_bit,1);	

			}  /* end if punto digitale acquisito */
			break;

			/* digitali  calcolati standard */
			case g1tipds:
				flag=dbds[pall->m.punt];
				if((!memcmp(dbdsg+pall->m.punt,pchGer,nLevToCheck) && dbdsu[pall->m.punt]==sZona))
					iCont++;
				break;

			/* digitali  calcolati non standard */
			case g1tipdc:
				flag=dbdc[pall->m.punt];
				if((!memcmp(dbdcg+pall->m.punt,pchGer,nLevToCheck) && dbdcu[pall->m.punt]==sZona))
					iCont++;
				break;

			/* digitali  di diagnostica */
			case g1tipdd:
				flag=dbdd[pall->m.punt];
				if(!memcmp(dbddg+pall->m.punt,pchGer,nLevToCheck) && dbddu[pall->m.punt]==sZona)
					iCont++;
				break;

			/* digitali  di uscita */
			case g1tipdo:
				flag=dbdo[pall->m.punt];
				if((!memcmp(dbdog+pall->m.punt,pchGer,nLevToCheck) && dbdou[pall->m.punt]==sZona))
					iCont++;
				break;

			/* organi */
			case g1tipor:
				flag=dbosc[pall->m.punt];
				if((!memcmp(dbog+pall->m.punt,pchGer,nLevToCheck) && dbou[pall->m.punt]==sZona))
					iCont++;
				break;

			/* stringhe */
			case g1tipst:
				flag=0;
				if((!memcmp(dbstg+pall->m.punt,pchGer,nLevToCheck) && dbstu[pall->m.punt]==sZona))
					iCont++;
				break;
			default:
				fprintf(stderr,"[gerarch.c] tipo punto sconosciuto.\n");
		} /* end switch */ 
			

		/* Controlla che il punto non sia ne fuori attendibilita'
		   ne fuori scansione 					  */
		if(bitvalue(&flag,g2an_fa) || bitvalue(&flag,g2an_fs))
                        {
			tab->corrente->g.cont_err++;
                        }

	}  /* end for */
}
else
	return;

/* Aggiorna valore e flag della calcolata */
/*
printf("****************************\n");
printf("Valore finale di iCont=%d\n",iCont);
*/
if(!tab->corrente->g.cont_err)
{
/*
printf("\n tipoc=%d\n",tab->corrente->g.tipoc);
printf("\n addr_corrente=%d\n",tab->addr_corrente);
printf("****************************\n");
*/
/*
Inserisco in dbasv[tab->addr_corrente] le word con i bit settati a 1
quando e' stato rilevato per questa gerarchia almeno un allarme nell' elenco generale allarmi
*/ 

	dbasv[tab->addr_corrente]=(float)iCont;
/*
appoggio=(int)dbasv[tab->addr_corrente];
printf("gerarc.c: appoggio=%x\n",appoggio);
*/
	bitset(&dbasf[tab->addr_corrente],g2an_fa,0);
}
else
        {
	bitset(&dbasf[tab->addr_corrente],g2an_fa,1);
        }

tab->corrente->g.cont_err=0;
}
#endif

