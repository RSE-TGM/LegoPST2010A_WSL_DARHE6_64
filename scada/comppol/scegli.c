/*
   modulo scegli.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)scegli.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*								                                             *
*			    File SCEGLI.C			                                    *
*								                                             *
*			PROCEDURE CONTENUTE			                                 *
*								                                             *
*	scegli(ln)		ove  :	int ln;			                           *
*								                                             *
*********************************************************************/

#include <osf1.h>
#include <stdio.h>

#include "chascii.inc"

#include "tipi.h"

#define maxlung_istr	12

extern char linea_cor[];
extern char *private[];
extern int istruzioni;
extern int fdlst;
extern int contif;
extern int contcase;
extern int contloop;

extern short flgjump;
extern short flgloop;
extern short flgreploop;


extern struct symb_list *ins_symb();
extern int contrari[];
extern int contsubr;
extern int inentry;
extern int finesubr;
extern int nword_o;

extern int indcpl;  // indirizzo di compilazione
extern int tbicpl[NUM_ISTR][3];  // tabella filtro primario   compilazione
extern int tbicps[NU_ISTRS][3];  // tabella filtro secondario compilazione

int oksubr=0;

/*********************************************************************
*								                                             *
*			  Procedura scegli			                                 *
*								                                             *
* Questa procedura prende una riga dal file di input (tramite la     *
* procedura new_lico()) ,se la chiamata lo esige ("ln"=1), cerca     *
* l' istruzione presente nella riga e chiama la procedura relativa.  *
* Se non esiste alcuna istruzione nella riga incrementa "errori".    *
* Continua questo loop finche' new_lico() non ritorna EOF, al che il *
* controllo ritorna al main(). 					                        *
*								                                             *
*								                                             *
*********************************************************************/

scegli(ln)

int ln;
/* ln = 0 ==> analisi della riga contenuta in linea_cor       */
/* ln = 1 ==> caricamento dal file sorgente di una nuova riga */

{
// utilizzati da MOVR MOVA SCALG ROTG
short argi[2]={tintero, tintero};  
short argri[3]={treale, tintero, tintero};

short retproc,retscegli;

int n=0,j=0,trovato=0,indice,i,ris;
int ier,indshift;
char istruz[maxlung_istr],nomevar[maxlung_istr];
char stringacod[60];


if (ln)								 // caricamento di una nuova linea di codice
	while((n=new_lico())==0)
		;

if(n==-1)
	return(-4);  /* trovata la fine del file sorgente */

/* Carico da linea_cor il codice mnemonico dell'istruzione */

for(n=0;n<maxlung_istr-1 && (( linea_cor[n]>=0x41 && linea_cor[n]<=0x5a) ||
                             ( linea_cor[n]>=0x30 && linea_cor[n]<=0x39) ||
                               linea_cor[n]==UNDSCORE); n++)
	istruz[n]=linea_cor[n];

istruz[n]='\0';

trovato=0;  // resetto il flag di nome istruzione riconosciuto

/* Ciclo di ricerca dell'istruzione tra le parole chiave ammesse */

for(indice=1;indice<NUM_ISTR;indice++)
	if( (strcmp(istruz,par_chiav[indice])==0) &&
	    (tbicpl[indice][indcpl]==1) ) {

		/* Nome istruzione riconosciuto e compatibile con l'indirizzo */
		/* di compilazione selezionato */

		trovato=1;
		break;
	}

if(trovato) {

   /* Nome istruzione trovato tra le parole chiave */

	if (istruzioni >= MAXISTR ) {

	   /* Superato il numero massimo di istruzioni consentite */

		stampa_err(57,0,"0");
		return(-1);

	}

  	if(inentry==1 || finesubr==0) {

	/* Ho incontrato una istruzione ENTRY o sono in una SUBROUTINE */

		if(indice==29 && inentry==1)

		/* Dopo una ENTRY incontro una istruzione TERM */

			inentry=0;  // resetto il flag di ENTRY in corso

	}

	else

		if(indice==29)

      /* Incontrata una TERM senza ENTRY relativa */
         stampa_err(10,1,istruz);

		else {

      /* istruzione non tra ENTRY e TERM */
         stampa_err(46,1,istruz);
		 	return(1);
		}

	istruzioni++;
	oksubr=0;

	/* Switch in funzione dell'indice parola chiave riconosciuta */

	switch(indice) {

	case  1  :  /* istruzioni senza operandi */
	case  27 :
	case  28 :
	case  29 :
	case  50 :
	case  51 :
	case  59 :
	case  61 :		// RICHIAMA
	case  92 :
	case 116 :    // SUCCESSIVO
	case 115 :    // PRECEDENTE

/* inserisce la parola chiave relativa all'istruzione nella simbol table
	strutturata ad albero                                                */

		inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);

		istrnoar();

/* scrive l'istruzione sul file intermedio                              */ 

 	 	intfile(indice);
		if(indice==29)		  // ha trovato una term.
			oksubr=1;
              break;

	case  2  :   /* serie istruzioni tipo IF */
	case  3  :
	case  4  :
	case  5  :
	case  6  :
	case  7  :
	case  8  :
	case  9  :
	case  10 :
	case  11 :
	case  12 :
	case  13 :
	case  14 :
	case  15 :
		strcpy(nomevar,par_chiav[contrari[indice-2]]);
		nomevar[0]=linea_cor[0]=0x42; /* inserisco B */
   	nomevar[1]=linea_cor[1]=0x52; /* inserisco R */
		inizio=ins_symb(inizio,nomevar,contrari[indice-2],-1,-1,-1,2);

/*	 passa il controllo a procif() (contenuta nel file se.c) che risolve
	 le eventuali nidificazioni degli if e le istruzioni interne ai blocchi
	 subordinati ad essi, richiamando a sua volta la presente routine scegli */

			ier = procif(indice);
			
			if ( ier == -2 ) {
		
			/* Manca istruzione ENDIF */

			return(-3);

			}

	 	break;

	case  118 :	 /* istruzione IFNES */

		strcpy(nomevar,par_chiav[119]);
		nomevar[0]=linea_cor[0]=0x42; /* inserisco B */
   	nomevar[1]=linea_cor[1]=0x52; /* inserisco R */
		inizio=ins_symb(inizio,nomevar,119,-1,-1,-1,2);

			ier = procif(indice);
			
			if ( ier == -2 ) {
		
			/* Manca istruzione ENDIF */

			return(-3);

			}

	 	break;

	case  119 :	 /* istruzione IFEQS */

		strcpy(nomevar,par_chiav[118]);
		nomevar[0]=linea_cor[0]=0x42; /* inserisco B */
   	nomevar[1]=linea_cor[1]=0x52; /* inserisco R */
		inizio=ins_symb(inizio,nomevar,118,-1,-1,-1,2);

			ier = procif(indice);
			
			if ( ier == -2 ) {
		
			/* Manca istruzione ENDIF */

			return(-3);

			}

	 	break;

	case  16 :  /* istruzione GOSUB */

		inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
		procgosub();
	 	break;

	case  17 :   /* operazioni logiche */
	case  18 :
	case  19 :
	case  20 :
	case  21 :
	case  22 :
	case  23 :  /* OR  */
	case  24 :  /* ORN */
	case  25 :
	case  26 :
	case  129 : /* XOR */

		if ( indice != 129 ) {

      inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);

		}

		else {

		/* indice = 129 istruzione XOR */

		indshift = indice + 1;

      inizio=ins_symb(inizio,par_chiav[indice],indshift,-1,-1,-1,2);

		}

	 	logica(indice);

	 	break;

	case  30 :	  // outg
	case  33 :    // inv
	case  34 :    // vision
	case  35 :    // visioff
	case  37 :    // tsel
	case 127 :    // outgv

		if ( indice != 127 ) {

      inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);

		}

		else {

		/* indice = 127 istruzione OUTGV */

		indshift = indice + 1;

      inizio=ins_symb(inizio,par_chiav[indice],indshift,-1,-1,-1,2);

		}

		gruppi(indice);
		break;

	case  31 :  /* istruzione PAG  */

      inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
		pag(indice);
		break;

	case  32 :  /* istruzione STAT */

      inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
	 	stat(indice);
		break;

	case  36 :  /* istruzione RET */

 		if(finesubr!=0 ) {
			stampa_err(13,1,istruz); /* trovo RET senza subr. */
	           	return;
		}
	 	oksubr=2;
 		fastringa(private[6],1,"0");
      inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
	 	intfile(indice);
	 	break;

	case  38 :  // CLRPAGE 
	case  60 :	// SALVA
	case  99 :	// HCPY

      inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
		oppag(indice);
		break;

	case  39 :  /* istruzione SEND */

      inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
		send(indice);
		break;

	case  40 :   /* operazioni sullo stack */
	case  41 :
	case  42 :
	case  43 :
	case  44 :
	case  45 :
	case  46 :
	case  47 :
	case  48 :
	case  49 :

      inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
		procstack(indice);
	 	break;

	case  52 :    /* operazioni di assegnamento */
	case  53 :
	case  54 :
	case  55 :
	case  56 :
	case  57 :
	case 105 :
	case 106 :

		inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
	 	assegna(indice);
 		break;

	case  58 :	  /* ACTIV */

      inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
 		attivo(indice);
		break;

	case  62 :    // READ
	case  63 :	  // WRITE
	case 100 :    // RWRITE

      inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
		rdwr(indice);
	 	break;

	case  64 :    // operazioni algebriche
	case  65 :
	case  66 :
	case  67 :
	case  68 :
	case  69 :
	case  70 :
	case  71 :
	case  72 :
	case  73 :
	case  74 :
	case  75 :
	case  76 :
	case  77 :
	case  78 :
	case  79 :
	case  80 :
	case  81 :
	case  82 :
	case  83 :
	case  84 :
	case 107 :	  // elevaz. a potenza
	case 108 :	  // funz. trigonometriche
	case 109 :
	case 110 :
	case 111 :
	case 128 :

		if ( indice != 128 ) {

      inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);

		}

		else {

		/* indice = 128 istruzione SUMS */

		indshift = indice + 1;

      inizio=ins_symb(inizio,par_chiav[indice],indshift,-1,-1,-1,2);

		}

 		aritmetic(indice);

		break;

	case  93 :	  // LSEL
	case  94 :	  // LACT

		inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
		loadm_g(indice);
	 	break;

	case  96 :	  // LEDON
	case  97 :	  // LEDOFF
	case 117 :	  // LEDBLK
	case 98  :	  // KEY	

		inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
 		led(indice);
 		break;

	case 95 :		  /* PRINT   */

		inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
	 	if((i=ctrprint(indice))==-1)
 			return(-1);
 		break;

	case 112 : /* MOVA spostamento gruppi assoluto */
	case 113 : /* MOVR spostamento relativo oggetto*/
		
		inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
		movgr(indice,2,argi);			// 2 argomenti di tipo intero
		break;

	case 114 : /* SCALG ridimensionamento oggetto  */
		inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
		movgr(indice,2,argri);			// 2 argomenti uno reale e uno intero
		break;

	case 104 : /* ROTG rotazione oggetto			  */
		inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
		movgr(indice,3,argri);			// 3 argomenti 1 di tipo reale e 2 interi
		break;

	case 132 : /* SETWIND */

		indshift = indice + 1;
      inizio=ins_symb(inizio,par_chiav[indice],indshift,-1,-1,-1,2);
	 	oplstarg(indice);
		break;

	case 120 :  // istruzione EXECBL blocco di calcolo

		inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
		execblc(indice);
		break;

	case 121 :  // istruzione WAIT time out trigger

		inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
		ctrwait(indice);
		break;

	case 122 :  // istruzione STOP sequenza di un P.A.S.

		inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
		ctrstop(indice,1);
		break;

	case 123 :  // istruzione START sequenza di un P.A.S.

		inizio=ins_symb(inizio,par_chiav[indice],indice,-1,-1,-1,2);
		ctrstop(indice,0);
		break;

	case 124 :  // istruzione FREAD di lettura da file disco

		indshift = indice + 1;

		inizio=ins_symb(inizio,par_chiav[indice],indshift,-1,-1,-1,2);
		ctrfrewr(indice,0);
		break;

	case 125 :  // istruzione FWRITE di scrittura su file disco

		indshift = indice + 1;

		inizio=ins_symb(inizio,par_chiav[indice],indshift,-1,-1,-1,2);
		ctrfrewr(indice,1);
		break;


	case 126 :  // istruzione FDELETE di cancellazione file su disco

		indshift = indice + 1;

		inizio=ins_symb(inizio,par_chiav[indice],indshift,-1,-1,-1,2);
		ctrfrewr(indice,1);
		break;

	case 130 :  // istruzione STLENG
	case 131 :  // istruzione STNCAT

		indshift = indice + 1;

		inizio=ins_symb(inizio,par_chiav[indice],indshift,-1,-1,-1,2);
		oplstarg(indice);
		break;

	case 101 :  // istruzioni READ_K WRITE_K READ_C WRITE_C
	case 102 :
	case 103 :

			stampa_err(0,1,istruz);
			break;

	}  /* fine switch */

	return(1);

} /* fine if (trovato) */

else {

/* Nome istruzione non trovata nel vettore delle parole chiave */

	indice=-1;

/* Ciclo di ricerca nel vettore secondo set di parole chiave */

for(i = 0; i < NU_ISTRS; i++)

	if( (strcmp(istruz,altre_istr[i]) ) == 0 && 
	    (tbicps[i][indcpl] == 1) ) {

		indice=i;
		break;

	}

/* Verifico se l'istruzione corrente coincide con una dichiarazione */
/* SUBROUTINE oppure con la parola chiave ENDS                      */

	if( !(indice==8 || indice==10) )
		oksubr=0;  // non e' SUBROUTINE neppure ENDS


  if(inentry==0 && finesubr!=0 && (!(indice==9 || indice==8 || indice==11)))

  /* Istruzione non compresa tra ENTRY e TERM */	

    stampa_err(46,1,istruz);

/* Switch di selezione in funzione del valore di indice */

	switch(indice)  {

	case   0 :   /* ELSE */

			if( (contloop==0 && contcase==0) && (flgjump==0) ) {

				flgjump = 1;
				inizio=ins_symb(inizio,"JUMP",0,-1,-1,-1,2);

			}

			procelse(1);
			break;

	case   1 :   /* ENDIF */

			procendif();
			break;

	case   2 :   /* Istruzione DATA nel posto errato */

			stampa_err(0,1,istruz);
			break;

	case   3 :   /* MOVP */

		   inizio=ins_symb(inizio,"MOVP",53,-1,-1,-1,2);
	 	  	assegna(-1);
			break;

	case   4 :   /* CASE */

			if(contcase==0)  {
				inizio=ins_symb(inizio,"CASE",8,-1,-1,-1,2);
				inizio=ins_symb(inizio,"JUMP",0,-1,-1,-1,2);
				indice=8;
				strcpy(nomevar,par_chiav[indice]);
				nomevar[0]=0x42; /* B */
				nomevar[1]=0x52; /* R */
				inizio=ins_symb(inizio,nomevar,indice,-1,-1,-1,2);
			}

			ier = proccase();
			
			if ( ier == -2 ) {
		
			/* Manca istruzione ENDCASE */

			return(-3);

			}

			break;

	case   5 :   /* BEGIN */

			procbegin();
			break;

	case   6 :   /* ENDCASE */

			procfcase();
			break;

	case   7 :   /* BREAK */

/**
		if(contif==1 && contcase==1)
**/
			procelse(0);
			break;

	case   8 :   /* SUBROUTINE */

			if(oksubr==1) {
				inizio=ins_symb(inizio,"SUBROUTINE",-1,-1,-1,-1,2);
				retproc = procsub();
			}
			else
				stampa_err(14,1,istruz); /* istr. prec non e' TERM o ENDS */
			break;

	case   9 :   /* ENTRY */

			if(oksubr!=0) {
         /* gia' definito delle subr. */ stampa_err(0,1,istruz);
				break;
			}
			if(inentry==1)
         /* ENTRY nidificata */		stampa_err(10,1,istruz);
			else {
				procentry();
			}
			break;

	case  10 :   /* ENDS */

			if(oksubr==2)
				oksubr=1;
			else
         /* trovo ENDS senza RET prima */stampa_err(15,1,istruz);
	 		if(finesubr!=0 )
         /* trovo ENDS senza subr. */	stampa_err(13,1,istruz);
			else
				finesubr=1;
			break;

	case  11 :   /* END */

			if(inentry==1)
				stampa_err(10,1,istruz);  /* MANCA TERM */
			return(-3);

   case  12 :   /* LOOP */

			if ( flgloop == 0 ) {

			/* Prima istruzione LOOP incontrata nel sorgente */

				flgloop = 1;

				inizio=ins_symb(inizio,"LOOP",( COISLOOP ),-1,-1,-1,2);
				inizio=ins_symb(inizio,"JUMP",0,-1,-1,-1,2);


			}

			ier = procloop(indice);
			
			if ( ier == -2 ) {
		
			/* Manca istruzione ENDLOOP */

			return(-3);

			}

	      break;

   case  13 :   /* BREAKLOOP */

			prbrloop();

	      break;


   case  14 :   /* ENDLOOP */

	      prfloop();

	      break;


   case  15 :   /* REPLOOP */

			if ( flgreploop == 0 ) {

			/* Prima istruzione REPLOOP incontrata nel sorgente */

				flgreploop = 1;

				inizio=ins_symb(inizio,"REPLOOP",( COISRLOOP ),-1,-1,-1,2);
				inizio=ins_symb(inizio,"JUMP",0,-1,-1,-1,2);


			}

			ier = procloop(indice);
			
			if ( ier == -2 ) {
		
			/* Manca istruzione ENDLOOP */

			return(-3);

			}

	      break;


	default  :

			stampa_err(0,1,istruz);
			break;

	}  /* fine switch */

	retscegli = 1;

	if ( (retproc == -3) || (retproc == -4) ) {

	retscegli = retproc;

	}

	return(retscegli);

}

}
