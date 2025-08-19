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
	Modulo:  OREMISUR.C
		
        OREMISURE
        Determina il numero di minuti in cui una misura 
        viene trovata sopra una certa soglia definita
        nel descrittore. Tale soglia puo' essere un valore
        floating oppure una misura di riferimento.
        Se la misura acquisita e' valida si resetta il bit di
        fuori attendibilita' anche se il valore non supera la
        soglia.
        L'unita' temporale della misura e' il minuto quindi la
        quantita' da aggiungere alla generata e' trovata nella
        tabella "convertempo" rispetto alla riga 1 dei minuti
        e alla colonna relativa alla classe di scansione.
        Questa misura viene resettata alla mezzanotte.
        
        Alla routine e' passato il parametro "scansione" che
        viene utilizzato come indice nella tabella convertempo
        ed indica la classe di scansione della calcolata.
  
        Nel file di include <converti.inc> vi e' la inizializza-
        zione della tabella "convertempo".
  
	Creazione :  Antecedente 01.05.92

	Revisioni :  18.05.92  -  GM Furlan
	             Calcoli in doppia precisione

*************************************************************/

#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "calas.inc"

// External function declarations
extern void bitset(short *, short, short);
extern int bitvalue(short *, short);

extern float convertempo[4][5] ;
void oremisure(scansione)
int scansione;
{
PUNTATORE temp[2];
int i,j;
double val[2];
short *flag[2], contr, freq;

if( reset[scansione][f_gio] == 1 )
    {
        dbasv[tab->addr_corrente]=0.0;
        bitset(&dbasf[tab->addr_corrente],g2an_fa,0);
    }

temp[0]=tab->corrente->h.misura;
if((tab->corrente->h.v_s.soglia.ext & 0xFF00) == 0xFF00)
  {            /* e' una misura!!! */
        j=2;
        temp[1].punt=tab->corrente->h.v_s.soglia.punt;
        temp[1].ext=tab->corrente->h.v_s.soglia.ext & 0x00FF;
  }
else
  {
        j=1;
        val[1]=tab->corrente->h.v_s.val ;
  }

for(i=0;i<j;i++)
  {
   switch(temp[i].ext)
    {
        case g1tipaa:
                flag[i]=&dbaaf[temp[i].punt];
                val[i]= dbaav[temp[i].punt];
                break;
        case g1tipac:
                flag[i]=&dbacf[temp[i].punt];
                val[i]= dbacv[temp[i].punt];
                break;
        case g1tipas:
                flag[i]=&dbasf[temp[i].punt];
                val[i]= dbasv[temp[i].punt];
                break;
        case g1tipad:
                flag[i]=&dbadf[temp[i].punt];
                val[i]= dbadv[temp[i].punt];
                break;
    }   /*end switch */

   if(bitvalue(flag[i],g2an_fa) || bitvalue(flag[i],g2an_fs))
        /*bitset(&dbasf[tab->addr_corrente],g2an_fa,1);*/
        return;
  }  /* end for */

if(val[0] > val[1])
        dbasv[tab->addr_corrente]=dbasv[tab->addr_corrente]+
                convertempo[1][scansione];
        bitset(&dbasf[tab->addr_corrente],g2an_fa,0);
 
/*
printf("\ngenerata =%f",dbasv[tab->addr_corrente]);
printf("\nval[0] =%f",val[0]);
printf("\nval[1] =%f\n",val[1]);
*/
}

