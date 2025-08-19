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
/*************************************************************
	Modulo: OPERAZ.C
        Viene eseguita una delle quattro operazioni
        tra due misure oppure tra una misura e una costante.
  
        Non viene eseguita alcuna operazione nel caso in cui
        almeno una delle contribuenti al calcolo si trovi
        fuori scansione oppure fuori attendibilita'. Inoltre
        nel caso della divisione, l' operazione viene eseguita
        se il divisore e' diverso da zero. In tali casi viene
        settato il bit di fuori attendibilita'; altrimenti si
        procede al calcolo e si resetta il bit di F.A.
        
        Non vengono passati parametri alla routine.
  
	Creazione :  Antecedente 01.05.92

	Revisioni :  18.05.92  -  GM Furlan
	             Calcoli in doppia precisione

*************************************************************/

#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "calas.inc"

// External function declarations
extern int bitvalue(short *, short);
extern void bitset(short *, short, short);

void operaz()
{
PUNTATORE temp[2];
int i,j;
double result, val[2];
short *flag[2], contr, freq;


if((tab->corrente->o.c_m.misura.ext & 0xFF00) == 0xFF00)
	{            /* e' una misura!!! */
   j=2;
   temp[0]=tab->corrente->o.misura;
   temp[1].punt=tab->corrente->o.c_m.misura.punt;
   temp[1].ext=tab->corrente->o.c_m.misura.ext & 0x00FF;
  }
else
  {
  j=1;
  temp[0]=tab->corrente->o.misura;
  val[1]=tab->corrente->o.c_m.cost;
  }

for(i=0;i<j;i++)
  {
  switch(temp[i].ext)
    {
    case g1tipaa:
  	  flag[i]=&dbaaf[temp[i].punt];
     val[i]=dbaav[temp[i].punt];
     break;
    case g1tipac:
     flag[i]=&dbacf[temp[i].punt];
     val[i]=dbacv[temp[i].punt];
     break;
    case g1tipas:
     flag[i]=&dbasf[temp[i].punt];
     val[i]=dbasv[temp[i].punt];
     break;
    case g1tipad:
     flag[i]=&dbadf[temp[i].punt];
     val[i]=dbadv[temp[i].punt];
     break;
    } 

   if(bitvalue(flag[i],g2an_fa) || bitvalue(flag[i],g2an_fs))
        tab->corrente->o.cont_err++;
  }  /* end for */

 result=dbasv[tab->addr_corrente];      // inizializzazione di result

 if( !tab->corrente->o.cont_err)
  {
    switch(tab->corrente->o.oper)
    {
        case 1:
                /* somma */
                result=val[0]+val[1];
                break;
        case 2:
                /* sottrazione */
                result=val[0]-val[1];
                break;
        case 3:
                /* moltiplicazione */
                result=val[0]*val[1];
                break;
        case 4:
                /* divisione */
                if(val[1] != 0)
                  result=val[0]/val[1];
                break;
     }   /* end switch */


 dbasv[tab->addr_corrente]=result;
 bitset(&dbasf[tab->addr_corrente],g2an_fa,0);
}
else
 {
  bitset(&dbasf[tab->addr_corrente],g2an_fa,1);
 }  /* end if */
 
tab->corrente->o.cont_err=0;

/*
printf("\ngenerata =%f",dbasv[tab->addr_corrente]);
printf("\nval[0] =%f",val[0]);
printf("\nval[1] =%f\n",val[1]);
*/
}


