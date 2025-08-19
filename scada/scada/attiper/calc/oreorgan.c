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
	Modulo:  OREORGAN.C

        OREORGANI
        Se la misura acquisita e' valida si resetta il bit di
        fuori attendibilita' e si aggiorna il valore della
        calcolata.
        L' unita' temporale della misura e' l' ora  quindi la
        quantita' da aggiungere alla generata e' trovata nella
        tabella "convertempo" rispetto alla riga 3 delle ore
        e alla colonna relativa alla classe di scansione.
        
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
extern int bitvalue(short *, short);
extern void bitset(short *, short, short);

extern float convertempo[4][5] ;
void oreorgani(scansione)
int scansione;
{
PUNTATORE temp;
int i,j;
short val;
short *flag;

/*
        l' unita' temporale e' l' ora !!        
if( reset[scansione][f_ora] == 1 )
    {
    dbasv[tab->addr_corrente]=0.0;
    bitset(&dbasf[tab->addr_corrente],g2an_fa,0);
    }
*/

temp=tab->corrente->r.organo ;

flag=&dbosc[temp.punt];
val=(dbosc[temp.punt] & 0x003F) ;

if(bitvalue(flag,g2or_fa) || bitvalue(flag,g2or_fs))
return;

if( val == tab->corrente->r.stato )
        dbasv[tab->addr_corrente]=dbasv[tab->addr_corrente]+
                convertempo[2][scansione];
        bitset(&dbasf[tab->addr_corrente],g2an_fa,0);

/*
printf("\ngenerata =%f",dbasv[tab->addr_corrente]);
*/
}

