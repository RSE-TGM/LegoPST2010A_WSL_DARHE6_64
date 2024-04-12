/*
   modulo data_tip.h
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)data_tip.h	1.1
*/
/********************************************************************
*			   File DATA_TIPI.H 				                             *
*            							                                   *
*	Contiene tutte le inizializzazioni                               *
********************************************************************/

/* Opzioni di attivazione compilatore POL */

char *stropcmp[NMXOPCMP] ={
"/I","/LS","/LO","/ST","/DEB","/FL" };

/* Vettore flag di utilizzo opzioni di attivazione compilatore */

short utiopcmp[NMXOPCMP] ={
-1,-1,-1,-1,-1,-1 };

/* Parole chiave primo set istruzioni linguaggio */

char *par_chiav[NUM_ISTR] ={
"",          "NOP",   	   "IFAN",         "IFAZ",	        "IFLTI",
"IFLEI",     "IFGTI",	   "IFGEI",        "IFNEI",        "IFEQI",
"IFLTF",     "IFLEF",      "IFGTF",        "IFGEF",        "IFNEF",
"IFEQF",     "GOSUB",      "LOAD",         "LOADN",        "STO",
"STON",      "SET",        "CLR",          "OR",           "ORN",
"AND",       "ANDN",       "SETA",         "CLRA",         "TERM",
"OUTG",      "PAG",        "STAT",         "INV",          "VISION",
"VISIOFF",   "RET",        "TSEL",         "CLRPAGE",      "SEND",
"PUSHI",     "PUSHF",      "IPUSHI",       "IPUSHF",       "POPI",
"POPF",      "LOADI",      "LOADF",        "STOI",         "STOF",
"FIX",       "FLOAT",      "MOVI",         "MOVF",         "IMOVI",
"IMOVF",     "MFIX",       "MFLOAT",       "ACTIV",        "DACT",
"SALVA",     "RICHIAMA",   "READ",         "WRITE",        "MULF",
"MULI",      "DIVF",       "DIVI",         "SUMF",         "SUMI",
"SUBF",      "SUBI",       "CLRF",         "CLRI",         "ABSF",
"ABSI",      "NEGF",       "NEGI",         "SQRT",         "LOG",
"EXP",       "LN",         "EXP10",        "SIN",          "COS",
"",           "",           "",		       "",      	     "",
"",          "",	         "DSEL",  	   "LSEL",          "LACT",
"PRINT",     "LEDON",	   "LEDOFF",	   "KEY",	        "HCPY",
"RWRITE",  	 "",	   		"",	   		"",        		  "ROTG",
"MOVS",	    "IMOVS",	   "POTF",        "TAN",	        "ARCSIN",
"ARCCOS",    "ARCTAN",	   "MOVA",	      "MOVR",	        "SCALG",
"PRECEDENTE","SUCCESSIVO", "LEDBLK",		"IFNES",			  "IFEQS",
"EXECBL",    "WAIT",       "STOP",        "START",         "FREAD",
"FWRITE",    "FDELETE",    "OUTGV",       "SUMS",          "XOR",
"STLENG",    "STNCAT",     "SETWIND"
	         	   };

/* Vettore nomi secondo set istruzioni linguaggio */

char *altre_istr[NU_ISTRS]= {

"ELSE","ENDIF","DATA","MOVP","CASE","BEGIN","ENDCASE","BREAK",
"SUBROUTINE","ENTRY","ENDS","END","LOOP","BREAKLOOP","ENDLOOP",
"REPLOOP"
			};

/* Sigle di individuazione dei tipi di variabile ammessi */

char *tipovar[NUM_TIPVAR] = {
   "AN", "DI", "OR", "RE", "IN", "LG", "DO", "ST", "GR",
   "PA", "PD", "PO", "PC", "PB", "PI", "PS"
			    };

short lnbyvar[NUM_TIPVAR]={6,1,2,4,2,1,4,0,0,4,4,4,4,0,0,4};

int aggind[NUM_TIPVAR]={0,0,2,3,1,0,0,4,0,3,3,3,3,0,0,3};


/* Vettore contenente i tipi ammessi per l'istruzione LINK */

char *tipistlk[NUM_TIPLK] = {
   "AN", "DI", "OR", "ST", "LS", "LC", "HC", "HS","IN" };
char *tipistlkp[NUM_TIPLK] = {
   "AN", "DI", "OR", "RE", "IN", "LG", "--", "--","--",  };     /* PIOMBINO */

/* Vettore contenente per ciascun tipo ammesso il relativo tipo variabile */

short tipvarlk[NUM_TIPLK]={0,1,2,7,0,0,0,0,4};
short tipvarlkp[NUM_TIPLK]={0,1,2,3,4,5,0,0,0}; /* PIOMBINO */

/* Vettore contenente per ciascun tipo ammesso il relativo codice */

short codistlk[NUM_TIPLK]={0,1,2,7,19,20,21,22,4};
short codistlkp[NUM_TIPLK]={0,1,2,3,4,5,0,0,0};    /* PIOMBINO */

/* Vettore contenente i tipi ammessi per l'istruzione READ */

char *tipistrd[NUM_TIPRD] = {
   "AN", "OR", "DI", "ST", "IN", "LS", "LC", "HC", "HS" };
char *tipistrdp[NUM_TIPRD] = {
     "AN", "OR", "DI", "RE", "IN", "LG", "--", "--", "--" }; /* PIOMBINO */

/* Vettore contenente per ciascun tipo ammesso il relativo codice */

short codistrd[NUM_TIPRD]={0,1,2,8,5,19,20,21,22};
short codistrdp[NUM_TIPRD]={0,1,2,3,4, 5, 0, 0, 0};     /* PIOMBINO  */

/* Vettore contenente per ciascun tipo di istruzione READ ammessa 
   il tipo ammesso per la variabile destinazione nel DBL          */

short tvdblrd[NUM_TIPRD]={0,2,1,7,4,0,0,0,0};
short tvdblrdp[NUM_TIPRD]={0,2,1,3,4,5,0,0,0};  /* PIOMBINO */

/* Vettore contenente per ciascun tipo di istruzione READ ammessa 
   il tipo ammesso per la variabile sorgente nel DBS              */

short tvdbsrd[NUM_TIPRD]={9,11,10,15,14,9,9,9,9};
short tvdbsrdp[NUM_TIPRD]={9,11,10,9,14,10,0,0,0};      /* PIOMBINO     */

/* Vettore contenente i tipi ammessi per l'istruzione WRITE */

char *tipistwr[NUM_TIPWR] = {"AN", "OR", "DI", "ST", "RE", "IN", "LG", "DO",
   "LS", "LC", "HC", "HS" };

char *tipistwrp[NUM_TIPWR] = {"AN", "OR", "DI", "DO", "RE", "IN", "LG", "--",
     "--", "--", "--", "--" };    /* PIOMBINO */

/* Vettore contenente per ciascun tipo ammesso il relativo codice */

short codistwr[NUM_TIPWR]={0,1,2,8,4,5,6,7,19,20,21,22};
short codistwrp[NUM_TIPWR]={0,1,2,7,4,5,6,0,0,0,0,0}; /* PIOMBINO */

/* Vettore contenente per ciascun tipo di istruzione WRITE ammessa 
   il tipo ammesso per la variabile sorgente nel DBL              */

short tvdblwr[NUM_TIPWR]={0,2,1,7,3,4,5,6,0,0,0,0};
short tvdblwrp[NUM_TIPWR]={0,2,1,6,3,4,5,0,0,0,0,0};  /* PIOMBINMO */

/* Vettore contenente per ciascun tipo di istruzione WRITE ammessa 
   il tipo ammesso per la variabile destinazione nel DBS          */

short tvdbswr[NUM_TIPWR]={9,11,10,15,9,14,10,12,9,9,9,9};
short tvdbswrp[NUM_TIPWR]={9,11,10,12,9,14,10,0,0,0,0,0}; /* PIOMBINO */

/* Tabella costituita da 3 colonne individuate dagli indici 0,1,2 */
/* corrispondenti agli indirizzi di compilazione ammessi e da un  */
/* numero di righe pari a NUM_ISTR                                */

/* Indirizzi di compilazione ammessi :                            */
/* - 0 indirizzo compilazione pagine video                        */
/* - 1 indirizzo compilazione tabulati                            */
/* - 2 indirizzo compilazione programmi applicativi               */

/* Gli elementi della tabella tbicpl assumono il significato :    */

/* tbicpl[i][indcpl] = 1                                          */

/* Istruzione individuata dall'indice i nel vettore delle parole  */
/* chiavi riconosciuta per l'indirizzo di compilazione indcpl     */


/* tbicpl[i][indcpl] = -1                                         */

/* Istruzione individuata dall'indice i nel vettore delle parole  */
/* chiavi non riconosciuta per l'indirizzo di compilazione indcpl */

int tbicpl[NUM_ISTR][3] = {
 1, 1, 1,   // 0			    
 1, 1, 1,	// 1			 NOP
 1, 1, 1,	// 2			 IFAN
 1, 1, 1,	// 3			 IFAZ
 1, 1, 1,	// 4			 IFLTI
 1, 1, 1,	// 5			 IFLEI
 1, 1, 1,	// 6			 IFGTI
 1, 1, 1,	// 7			 IFGEI
 1, 1, 1,	// 8			 IFNEI
 1, 1, 1,	// 9			 IFEQI
 1, 1, 1,	// 10        IFLTF
 1, 1, 1,	// 11			 IFLEF
 1, 1, 1,	// 12			 IFGTF
 1, 1, 1,	// 13			 IFGEF
 1, 1, 1,	// 14			 IFNEF
 1, 1, 1,	// 15			 IFEQF
 1, 1, 1,	// 16			 GOSUB
 1, 1, 1,	// 17			 LOAD
 1, 1, 1,	// 18			 LOADN
 1, 1, 1,	// 19			 STO
 1, 1, 1,	// 20			 STON
 1, 1, 1,	// 21			 SET
 1, 1, 1,	// 22			 CLR
 1, 1, 1,	// 23			 OR
 1, 1, 1,	// 24			 ORN
 1, 1, 1,	// 25			 AND
 1, 1, 1,	// 26			 ANDN
 1, 1, 1,	// 27			 SETA
 1, 1, 1,	// 28			 CLRA
 1, 1, 1,	// 29			 TERM
 1,-1,-1,	// 30			 OUTG
 1,-1,-1,	// 31			 PAG
 1,-1,-1,	// 32			 STAT
 1,-1,-1,	// 33			 INV
 1,-1,-1,	// 34			 VISION
 1,-1,-1,	// 35			 VISIOFF
 1, 1, 1,	// 36			 RET
 1,-1,-1,	// 37			 TSEL
 1,-1,-1,	// 38			 CLRPAG
 1,-1, 1,	// 39			 SEND 
 1, 1, 1,	// 40			 PUSHI
 1, 1, 1,	// 41			 PUSHF
 1, 1, 1,	// 42			 IPUSHI
 1, 1, 1,	// 43
 1, 1, 1,	// 44
 1, 1, 1,	// 45
 1, 1, 1,	// 46
 1, 1, 1,	// 47
 1, 1, 1,	// 48
 1, 1, 1,	// 49
 1, 1, 1,	// 50
 1, 1, 1,	// 51
 1, 1, 1,	// 52
 1, 1, 1,	// 53
 1, 1, 1,	// 54
 1, 1, 1,	// 55
 1, 1, 1,	// 56
 1, 1, 1,	// 57
 1,-1,-1,	// 58			 ACTIV
 1,-1,-1,	// 59			 DACT
 1,-1,-1,	// 60			 SALVA
 1,-1,-1,	// 61			 RICHIAMA
 1, 1, 1,	// 62
 1, 1, 1,	// 63
 1, 1, 1,	// 64
 1, 1, 1,	// 65
 1, 1, 1,	// 66
 1, 1, 1,	// 67
 1, 1, 1,	// 68
 1, 1, 1,	// 69
 1, 1, 1,	// 70
 1, 1, 1,	// 71
 1, 1, 1,	// 72
 1, 1, 1,	// 73
 1, 1, 1,	// 74
 1, 1, 1,	// 75
 1, 1, 1,	// 76
 1, 1, 1,	// 77
 1, 1, 1,	// 78
 1, 1, 1,	// 79
 1, 1, 1,	// 80
 1, 1, 1,	// 81
 1, 1, 1,	// 82
 1, 1, 1,	// 83
 1, 1, 1,	// 84
 1, 1, 1,	// 85
 1, 1, 1,	// 86
 1, 1, 1,	// 87
 1, 1, 1,	// 88
 1, 1, 1,	// 89
 1, 1, 1,	// 90
 1, 1, 1,	// 91
 1,-1,-1,	// 92			 DSEL
 1,-1,-1,	// 93			 LSEL
 1,-1,-1,	// 94			 LACT
-1, 1,-1,	// 95			 PRINT
 1,-1,-1,	// 96			 LEDON
 1,-1,-1,	// 97			 LEDOFF
 1,-1,-1,	// 98			 KEY
 1,-1,-1,	// 99			 HCPY
 1,-1,-1,	// 100		 RWRITE
 1, 1, 1,	// 101		 
 1, 1, 1,	// 102		 
 1, 1, 1,	// 103		 
 1, -1, -1,	// 104		 ROTG
 1, 1, 1,	// 105
 1, 1, 1,	// 106
 1, 1, 1,	// 107
 1, 1, 1,	// 108
 1, 1, 1,	// 109
 1, 1, 1,	// 110
 1, 1, 1,	// 111
 1,-1,-1,	// 112		 MOVA
 1,-1,-1,	// 113		 MOVR
 1,-1,-1,	// 114		 SCALG
 1, 1, 1,	// 115
 1,-1,-1,	// 116		 NCURS
 1,-1,-1,	// 117		 LEDBLK
 1, 1, 1,	// 118       IFNES
 1, 1, 1,	// 119		 IFEQS
-1,-1, 1,   // 120		 EXECBL
-1,-1, 1,   // 121		 WAIT
-1,-1, 1,   // 122		 STOP
-1,-1, 1,   // 123		 START
 1, 1, 1,   // 124		 FREAD
 1,-1, 1,   // 125		 FWRITE
 1,-1, 1,   // 126		 FDELETE
 1,-1,-1,   // 127		 OUTGV
 1, 1, 1,   // 128		 SUMS
 1, 1, 1,   // 129		 XOR
 1, 1, 1,   // 130		 STLENG
 1, 1, 1,   // 131		 STNCAT
 1,-1,-1    // 132		 SETWIND
        };

/* Tabella costituita da 3 colonne individuate dagli indici 0,1,2 */
/* corrispondenti agli indirizzi di compilazione ammessi e da un  */
/* numero di righe pari a NU_ISTRS                                */

/* Indirizzi di compilazione ammessi :                            */
/* - 0 indirizzo compilazione pagine video                        */
/* - 1 indirizzo compilazione tabulati                            */
/* - 2 indirizzo compilazione programmi applicativi               */

/* Gli elementi della tabella tbicps assumono il significato :    */

/* tbicps[i][indcpl] = 1                                          */

/* Istruzione individuata dall'indice i nel vettore altre_istr    */
/* riconosciuta per l'indirizzo di compilazione indcpl            */


/* tbicps[i][indcpl] = -1                                         */

/* Istruzione individuata dall'indice i nel vettore altre_istr    */
/* non riconosciuta per l'indirizzo di compilazione indcpl        */

int tbicps[NU_ISTRS][3] = {
 1, 1, 1,   // 0
 1, 1, 1,	// 1
 1, 1, 1,	// 2
 1, 1, 1,	// 3
 1, 1, 1,	// 4
 1, 1, 1,	// 5
 1, 1, 1,	// 6
 1, 1, 1,	// 7
 1, 1, 1,	// 8
 1, 1, 1,	// 9
 1, 1, 1,	// 10
 1, 1, 1,	// 11
-1,-1, 1,	// 12  LOOP
 1,-1, 1,   // 13  BREAKLOOP
 1,-1, 1,   // 14  ENDLOOP
 1,-1, 1    // 15  REPLOOP
        };

/* Vettore parallelo a par_chiav con il seguente significato */

int wordpar_ch[NUM_ISTR]= {
  2,  	     1,     	     2,	 	     2,		    4,
  4,          4,             4,		     4,		    4,
  4,          4,             4,		     4,		    4,
  4,          2,             2,          2,         2,
  2,          2,             2,          2,         2,
  2,          2,             1,          1,         1,
  2,         13,             4,          2,         2,
  2,          1,             2,          2,        15,
  2,          2,             2,          3,         2,
  2,          2,             2,          2,         2,
  1,          1,             3,          3,         3,
  4,          3,             3,          2,         1,
  2,          1,             4,          4,         4,
  4,          4,             4,		     4,		    4,
  4,          4,             2,		     2,		    3,
  3,          3,             3,          3,         3,
  3,          3,             3,          3,         3,
  2,	        1,     	     1,	        1,         1,
  1,	        1,     	     1,	 	     2,		    2,
  0,	        2,	           2,  	     2,  	    2,
  4,	        4,             4,	 	     4,		    4,
  3,	        0,	           4, 	        3,		    3,
  3,	        3,     	     4,		     5,         5,
  1,	        1,             2,          4,		    4,
  2,          0,             0,          0,         0,
  0,          0,             2,          4,         2,
  3,          4,             5  };

char *estensioni[MAX_EST]= {
  "FS","FA","FZ","ST","AU","RI",
  "DS","DC","HS","LS","HC","LC",
  "IN","AL","S2","S3","D0","O2","S1",
  "B0","B1","B2","B3","B4","B5","B6","B7",
  "B8","B9","BA","BB","BC","BD","BE","BF"
		};

int val_est[MAX_EST][5]= {
		15,     7,  	 7,   -1,	 -1,  /* "FS" */
		14,     6,	    6,   -1,	 -1,  /* "FA" */
 		13,	  5,	    5,   -1,	 -1,  /* "FZ" */
		12,	  4,	    4,   -1,	 -1,  /* "ST" */
		 8,	  2,	    1,   -1,	 -1,  /* "AU" */
		 6,	  1,	    0,   -1,	 -1,  /* "RI" */
		 5,    -1,     -1,   -1,	 -1,  /* "DS" */
		 4,    -1,     -1,   -1,	 -1,  /* "DC" */
		 3,    -1,     -1,   -1,	 -1,  /* "HS" */
		 2,    -1,     -1,   -1,	 -1,  /* "LS" */
		 1,    -1,     -1,   -1,	 -1,  /* "HC" */
		 0,    -1,     -1,   -1,	 -1,  /* "LC" */
		-1,     3,      3,   -1,	 -1,  /* "IN" */
		10,    -1,     -1,   -1,	 -1,  /* "AL" */
		 9,    -1,     -1,   -1,	 -1,  /* "S2" */
		 7,    -1,     -1,   -1,	 -1,  /* "S3" */
		-1,     0,     -1,   -1,	 -1,  /* "D0" */
		-1,    -1,      2,   -1,	 -1,  /* "O2" */
		11,    -1,     -1,   -1,	 -1,  /* "S1" */
		-1,    -1,     -1,   -1,	 0,  // B0
		-1,    -1,     -1,   -1,	 1,  // B1
		-1,    -1,     -1,   -1,	 2,  // B2
		-1,    -1,     -1,   -1,	 3,  // B3
		-1,    -1,     -1,   -1,	 4,  // B4
		-1,    -1,     -1,   -1,	 5,  // B5
		-1,    -1,     -1,   -1,	 6,  // B6
		-1,    -1,     -1,   -1,	 7,  // B7
		-1,    -1,     -1,   -1,	 8,  // B8
		-1,    -1,     -1,   -1,	 9,  // B9
		-1,    -1,     -1,   -1,	10,  // BA
		-1,    -1,     -1,   -1,	11,  // BB
		-1,    -1,     -1,   -1,	12,  // BC
		-1,    -1,     -1,   -1,	13,  // BD
		-1,    -1,     -1,   -1,	14,  // BE
		-1,    -1,     -1,   -1,   15	  // BF
		};			 
