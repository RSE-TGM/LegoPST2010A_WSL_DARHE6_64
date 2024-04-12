/**********************************************************************
*
*       C Header:               ttipal.inc
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug  1 11:11:02 2003 %
*
**********************************************************************/
/* ->TTIPAL.INC
 * 	Definisce le tabelle utilizzate per la stampa allarmi.
 */
/*
        definizione dei tipi di allarme analogici
*/

#include "defpub.h"
#include <all_1.h>

pub unsigned char all_an[4]={sic_al,sic_ba,con_al,con_ba} ; /* all. analogici */
pub unsigned char all_ac[8]={gr_var,range_al,range_ba,ch_fser,giun_fred,0,0,0};
//pub char *stringhe[]     = {    
pub char stringhe[][8]    = {    
                            "VAR.DIG.",   /* 0 */
                            "DIAG.SIS",   /* 1 */
                            "MOD.STR.",	  /* 2 */
			    "        ",   /* 3 */
                            "R.SIC.AL",   /* 4 */
                            "R.SIC.BA",   /* 5 */
                            "R.CON.AL",   /* 6 */
                            "R.CON.BA",   /* 7 */
                            "NON FORZ",   /* 8 */
                            "ATTENDIB",   /* 9 */
                            "IN SCAN.",   /* 10 */
                            "R.GR.VAR",   /* 11 */
                            "IN RANGE",   /* 12 */
                            "IN RANGE",   /* 13 */
                            "CH. SERV",   /* 14 */
                            "G. FRED.",   /* 15 */
                            "        ",   /* 16 */
                            "COMANDO ",   /* 17 */
                            "        ",	  /* 18 */
			    "        ",   /* 19 */
                            "VAR.SPON",   /* 20 */
                            "COM.FALL",   /* 21 */
                            "PRO.FALL",   /* 22 */
                            "COM.STOP",   /* 23 */
                            "COM. PAS",   /* 24 */
                            "MOD. HS ",   /* 25 */       
                            "MOD. HC ",   /* 26 */       
                            "MOD. LS ",   /* 27 */       
                            "MOD. LC ",   /* 28 */       
#if defined ALARM_SIGNAL
                            "SIGNAL A",   /* 29 */       
                            "SIGNAL B",   /* 30 */       
                            "SIGNAL C",   /* 31 */       
                            "SIGNAL D",   /* 32 */       
                            "SIGNAL E",   /* 33 */       
                            "SIGNAL F",   /* 34 */       
                            "SIGNAL G",   /* 35 */       
                            "SIGNAL H",   /* 36 */       
                            "SIGNAL I",   /* 37 */       
                            "SIGNAL J",   /* 38 */       
                            "SIGNAL K",   /* 39 */       
                            "SIGNAL L",   /* 40 */       
                            "SIGNAL M",   /* 41 */       
                            "SIGNAL N",   /* 42 */       
                            "SIGNAL O",   /* 43 */       
                            "SIGNAL P",   /* 44 */       
                            "SIGNAL Q",   /* 45 */       
                            "SIGNAL R",   /* 46 */       
                            "SIGNAL S",   /* 47 */       
                            "SIGNAL T",   /* 48 */       
                            "SIGNAL U",   /* 49 */       
                            "SIGNAL V",   /* 50 */       
                            "SIGNAL W",   /* 51 */       
                            "SIGNAL X",   /* 52 */       
                            "SIGNAL Y",   /* 53 */       
                            "SIGNAL Z",   /* 54 */       
#endif
                            "VAR.DIG.",   /*  0 */
                            "DIAG.SIS",   /*  1 */
                            "MOD.STR.",	  /* 2 */
			    "        ",     /* 3 */
                            "F.SIC.AL",   /* 4  */
                            "F.SIC.BA",   /* 5  */
                            "F.CON.AL",   /* 6  */
                            "F.CON.BA",   /* 7  */
                            "FORZATO ",   /* 8  */
                            "NON ATT.",   /* 9  */
                            "FUORI SC",   /* 10 */
                            "GR. VAR.",   /* 11 */
                            "F.RAN.AL",   /* 12 */
                            "F.RAN.BA",   /* 13 */
                            "CAN.F.SR",   /* 14 */
                            "NO G. FR",   /* 15 */
                            "        ",   /* 16 */
                            "COMANDO ",   /* 17 */
                            "        ",	  /* 18 */
			    "        ",   /* 19 */
                            "VAR.SPON",   /* 20 */
                            "COM.FALL",   /* 21 */
                            "PRO.FALL",   /* 22 */
                            "COM.STOP",   /* 23 */
                            "COM. PAS",   /* 24 */
                            "MOD. HS ",   /* 25 */       
                            "MOD. HC ",   /* 26 */       
                            "MOD. LS ",   /* 27 */       
                            "MOD. LC ",   /* 28 */       
#if defined ALARM_SIGNAL
                            "SIGNAL A",   /* 29 */       
                            "SIGNAL B",   /* 30 */       
                            "SIGNAL C",   /* 31 */       
                            "SIGNAL D",   /* 32 */       
                            "SIGNAL E",   /* 33 */       
                            "SIGNAL F",   /* 34 */       
                            "SIGNAL G",   /* 35 */       
                            "SIGNAL H",   /* 36 */       
                            "SIGNAL I",   /* 37 */       
                            "SIGNAL J",   /* 38 */       
                            "SIGNAL K",   /* 39 */       
                            "SIGNAL L",   /* 40 */       
                            "SIGNAL M",   /* 41 */       
                            "SIGNAL N",   /* 42 */       
                            "SIGNAL O",   /* 43 */       
                            "SIGNAL P",   /* 44 */       
                            "SIGNAL Q",   /* 45 */       
                            "SIGNAL R",   /* 46 */       
                            "SIGNAL S",   /* 47 */       
                            "SIGNAL T",   /* 48 */       
                            "SIGNAL U",   /* 49 */       
                            "SIGNAL V",   /* 50 */       
                            "SIGNAL W",   /* 51 */       
                            "SIGNAL X",   /* 52 */       
                            "SIGNAL Y",   /* 53 */       
                            "SIGNAL Z",   /* 54 */       
#endif
                                } ;

unsigned char color[max_st][max_trat] = {
/*
	tipi di trattamento
2	  3         4         5        6          7         8

*/
red,	  red,	    red,      red,     red,	  red,	    red,    //  "VAR.DIG."   	allarme digitale 
white,    white,    white,    white,   white,  	  white,    white,  //  "DIAG.SIS",	allarme diagnostica
green,	  green,    green,    green,   green,	  green,    green,  //  "MOD.ST.",       modifica stringa
0,	  0,	    0,	      0,       0,	  0,	    0,	    //  "  ", 
red,      red,      red,      red,     red,    	  red,      red,    //  "F.SIC.AL",	sicurezza alta
red,      red,      red,      red,     red,    	  red,      red,    //  "F.SIC.BA",	sicurezza bassa
yellow,   yellow,   yellow,   yellow,  yellow, 	  yellow,   yellow, //  "F.CON.AL",	conduzione alta
yellow,   yellow,   yellow,   yellow,  yellow, 	  yellow,   yellow, //  "F.CON.BA",	conduzione bassa
0,        0,        0,        0,       0,   	  0,        0,       //  "FORZATO ",
magenta,  magenta,  magenta,  magenta, magenta,	  magenta,  magenta,//	"NON ATT.",	punto non attendibile
0,	  0,        0,        0,       0,   	  0,        0,	    //  "F. SCAN.",	punto fuori scansione
0,	  0,        0,        0,       0,   	  0,        0,      //  "GR.  VAR",	grande variazione
0,	  0,	    0,        0,       0,         0,   	    0,      // "F.RAN.AL",	fuori range alto
0,	  0,	    0,        0,       0,         0,   	    0,	    //  "F.RAN.BA",	fuori range basso
0,  	  0,	    0,        0,       0,         0,   	    0,      //  "CAN.F.SR",	canale fuori servizio
0,	  0,	    0,        0,       0,         0,   	    0,      //  "NO G. FR",	giunto freddo ko
green,    green,    green,    green,   green,  	  green,    green,  //  "   ",		misura normale
0,	  0,        0,        0,       0,   	  0,        0,      //  "COMANDO ",	invio comando
0,0,      0,0,      0,0,      0,0,     0,0,    	  0,0,      0,0,    //  " "," ",   
green,	  green,    green,    green,   green,	  green,    green,  //  "VAR.SPON",	organo variato
green,	  green,    green,    green,   green,	  green,    green,  //  "COM.FALL",	comando fallito
green,	  green,    green,    green,   green,	  green,    green,   //  "PRO.FALL",	protezione fallita
0,	  0,        0,        0,       0,   	  0,        0,	    //  "COM STOP",	comando
0,	  0,        0,        0,       0,   	  0,        0,      //  "COM PAS",	comando da pas
0,	  0,        0,        0,       0,   	  0,        0,      //  "MOD ALL",	modifica soglie allarmi
0,	  0,        0,        0,       0,   	  0,        0,      //  "MOD ALL",	modifica soglie allarmi
0,	  0,        0,        0,       0,   	  0,        0,      //  "MOD ALL",	modifica soglie allarmi
0,	  0,        0,        0,       0,   	  0,        0       //  "MOD ALL",	modifica soglie allarmi
#if defined ALARM_SIGNAL
,
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL A"   	segnale A
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL B"   	segnale B
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL C"   	segnale C
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL D"   	segnale D
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL E"   	segnale E
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL F"   	segnale F
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL G"   	segnale G
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL H"   	segnale H
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL I"   	segnale I
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL J"   	segnale J
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL K"   	segnale K
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL L"   	segnale L
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL M"   	segnale M
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL N"   	segnale N
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL O"   	segnale O
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL P"   	segnale P
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL Q"   	segnale Q
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL R"   	segnale R
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL S"   	segnale S
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL T"   	segnale T
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL U"   	segnale U
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL V"   	segnale V
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL W"   	segnale W
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL X"   	segnale X
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL Y"   	segnale Y
red,	  red,	    red,      red,     red,	  red,	    red,    //  "SIGNAL Z"   	segnale Z
#endif
		};
/*
	buffer priorita' stringhe allarmi
*/
char pri_all[max_st]={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0,	 
		       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	0
#if defined ALARM_SIGNAL
	,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
#endif
			};

#include <all_16.h>
