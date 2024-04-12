/*
   modulo taskslav.c
   tipo 
   release 1.1
   data 12/1/95
   reserved @(#)taskslav.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
Task per la gestione della linea connessa al server slave. Tale comportamento
e' presente solo su CLIENT e consiste nel filtrare il messaggio di codice
"mmaster". Se il task riceve un messaggio con quel valore provvede a
commutare i campi faddr delle strutture di connessione e a forzare una
ripartenza della comunicazione. Il task forza anche l' indirizzo del
master sulla connessione relativa ad hardcopy. 

In questa versione sono previste le prime 2 porte (0 e 1) verso gli scada
e la terza (2) verso hardcopy. */

#include <pctcp/types.h>
#include <pctcp/pctcp.h>
#include "netstr.h"
#include "mesqueue.h"

#include "switch.inc"

#define PORTMASTER 0
#define PORTSLAVE  PORTMASTER +1
#define PORTHC     PORTMASTER +2

extern DESCCON _Conn[];
extern SERCLIDEF _SerCliDef[];
extern char stato_host_1;					// stato collegamento scada master

static int bufmes[1050];

taskslav()
	{
	QUEUE_PACKET spack;
   QUEUE_PACKET rpack;
 	in_name appo;
	char prev_stato_host, app_stato_host;
	unsigned short netmes[3];

	DESCCON *master=&_Conn[_SerCliDef[PORTMASTER].base];
	DESCCON *slave=&_Conn[_SerCliDef[PORTSLAVE].base];
	DESCCON *hc=&_Conn[_SerCliDef[PORTHC].base];

   spack.flg=MSG_WAIT;			// preparo per messaggio MODOFF
   spack.wto=0;
   spack.amsg=(char *)netmes;
   spack.lmsg=6;

   rpack.que=_SerCliDef[PORTSLAVE].chrx;
   rpack.flg=MSG_WAIT;
   rpack.wto=10;					// ciclo scansione stato comunicazione
   rpack.amsg=(char *)bufmes;
	prev_stato_host=1;			// off line

	netmes[0]=0xffff;				// buffer messaggio per gestione le connessioni
	netmes[2]=0;

// Se sistema funziona come slave disabilito la connessione verso lo slave
// onde evitare tentativi inutili

   if (! SYS_DUALE)        // duale non abilitato
      {
		netmes[1]=MODDISAB;				// disabilito slave
		spack.que=_SerCliDef[PORTSLAVE].chtx;
		enqueue(&spack);
      }

   while(1)
      {
      if(dequeue(&rpack))
			{
/*
	variazione stato comunicazione con host
	se off line disabilito e riabilito connessioni sia master che slave
	se on line disabilito connessione con slave
*/
					scd();
					app_stato_host=stato_host_1;
					sce();
					if(app_stato_host && app_stato_host != prev_stato_host)
					{
						netmes[1]=MODDISAB;				// disabilito connessione
						spack.que=_SerCliDef[PORTMASTER].chtx;
						enqueue(&spack);
						spack.que=_SerCliDef[PORTSLAVE].chtx;
						enqueue(&spack);
						wai(20);								// attesa
						netmes[1]=MODABIL;				// riabilito connessione
						spack.que=_SerCliDef[PORTMASTER].chtx;
						enqueue(&spack);
						spack.que=_SerCliDef[PORTSLAVE].chtx;
						enqueue(&spack);
					}
					if(!app_stato_host && app_stato_host != prev_stato_host)
					{
							netmes[1]=MODDISAB;				// disabilito slave
							spack.que=_SerCliDef[PORTSLAVE].chtx;
							enqueue(&spack);
					}
					prev_stato_host=app_stato_host;
			}
	  	   else if( bufmes[1] == MMASTER)			// messaggio sono master ?
			{
			appo=slave->a.fhost;				// se si sposto address fhost
			slave->a.fhost=master->a.fhost;
			master->a.fhost=appo;
			hc->a.fhost=appo;
			netmes[1]=MODOFF;
			spack.que=_SerCliDef[PORTMASTER].chtx;
			enqueue(&spack);
			spack.que=_SerCliDef[PORTSLAVE].chtx;
			enqueue(&spack);
// setto off (se gia' non lo e' ) la porta verso l' hardcopy
			spack.que=_SerCliDef[PORTHC].chtx;
			enqueue(&spack);
			}
		}
	}
