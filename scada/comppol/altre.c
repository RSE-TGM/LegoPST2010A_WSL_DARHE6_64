/*
   modulo altre.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)altre.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*          							     *
*			File altre.c                                 *
*          							     *
*	rdwr(codice)                                                 *
*		int codice;                                          *
*	led(codice)                                                  *
*		int codice;                                          *
*	oppag(codice)                                                *
*		int codice;                                          *
*	proc_key(codice)                                                  *
*		int codice                                           *
*	stat(codice)                                                 *
		int codice;                                          *
*	iszona(nomevar)                                              *
*		char nomevar[];                                      *
*	iscolor(M)                                                   *
*		int *M;                                              *
*          							     *
*********************************************************************/

#include <osf1.h>
#include <stdio.h>
#include <string.h>

#include "chascii.inc"

#include "tipi.h"
#include "data_tip.h"

#define  LUNGSTR	60
#define  POS1		 3
#define  POS2		10
#define VAL_MAX_AN_RW 60

extern char linea_cor[];
extern char *par_chiav[];
extern int nword_o;
extern int righeint;
extern int fdint;
extern int wordpar_ch[];

char *zona[]={ "S","I","W",};
char *color[]={"B","R","G","Y","L","M","C","W"};

/***********************************************************************
*          							                                         *
*			Procedura rdwr                                                *
*          							                                         *
* La procedura viene chiamata per risolvere le istruzioni di           *
* write e di read dinamiche. La prima variabile (chiamiamola var)      *
* puo' essere tra i seguenti tipi :                                    *
*      analogico-reale,	     digitale-logico,     organo-intero,       *
*      digital_output        stringa											  *
*  mentre la seconda (la chiameremo sigla) :                           *
*  puntatore_analogico,    puntatore_digitale,    puntatore_organo     *
*  puntatore_intero , puntatore_comando (PC)		  punt_stringa (PS)    *
*	Sono inoltre consentite solo le seguenti combianzioni:       		  *
*	  var = analogico && sigla = puntatore_analogico,            		  *
*	  var = reale     && sigla = puntatore_analogico,            		  *
*	  var = organo    && sigla = puntatore_organo                		  *
*	  var = intero    && sigla = puntatore_organo                       *
*	  var = intero    && sigla = puntatore_intero                       *
*	  var = logico    && sigla = puntatore_digitale,                    *
*	  var = digitale  && sigla = puntatore_digitale,             		  *
*	  var = digit_out && sigla = puntatore_comando,                     *
*
*  Sono ammesse anche operazioni su data base globali al posto operatore
*  GBC, al video operatore GBK e alla pagina video GBL. In questo caso
*  il tipo viene inserito con il bit piu' significativo a 1 (0x8000)
*          		                                                        *
************************************************************************/

rdwr(codice)

int codice;

{

int j,nuovariga=0,M,i,r,dim,ind,tipo,tipo_aus=-1,valore,new_code=-1;
char stringa[LUNGSTR],nomevar[LUNG_VAR+1],valvar[81],tip_rw[3];


static char *tipo_rw_aus[]={
                           "GBLA", "GBLI", "GBLD", "GBLO","GBLS","GBLP",
                           "GBKA", "GBKI", "GBKD", "GBKO","GBKS","GBKP",
                           "GBCA", "GBCI", "GBCD", "GBCO","GBCS","GBCP",
                           };
short ntipiop;
char *ptipiop;
short icodop;
short itvdbl;
short itvdbs;
char  berr;

/* Distinguo tra tipo di istruzione READ oppure WRITE */

if(codice==62) {

	/* Istruzione READ */

	ntipiop = NUM_TIPRD;

	ptipiop = (char *)&(tipistrd[0]);

	M=5;

}

else if(codice==63)
{

	/* Istruzione WRITE */

	ntipiop = NUM_TIPWR;

	ptipiop = (char *)&(tipistwr[0]);

	M=6;

}
else			// RWRITE
{
	ntipiop = NUM_TIPRD;
	ptipiop = (char *)&(tipistrd[0]);
	M=7;
}

togliblank(linea_cor,M);

tipo=-1;

/* verifica del tipo di READ/WRITE */

tipo = ctrtpgen (2,tip_rw,M,ntipiop,ptipiop);
if(tip_rw[0]=='G')                           // data base globale ?
{						 									// estraggo l'intera stringa 4 caratteri
   tipo = ctrtpgen (4,tip_rw,M,ntipiop,ptipiop);
}
if(tipo==-1)
{
	if(codice!=62 && codice!=63) stampa_err(6,0,"");	// errore sintassi non accettabile per RWRITE
	else
	{
	/* considero se si tratta del tipo Global data Base GBL, GBK, GBC */
		tipo_aus = -1;
		for(i=0;i<NUM_TIPWR_EXT;i++)
			if(strcmp(tip_rw,tipo_rw_aus[i])==0)
			{
				tipo_aus=i;
				break;
			}
	}
}

if( !( (tipo!=-1) || (tipo_aus!=-1) ) ) {

	/* Errore tipo di READ/WRITE non previsto */

	stampa_err(12,0,"0");

	return(0);

}

/* Tipo di istruzione READ/WRITE riconosciuto */

while(linea_cor[M]!=APTONDA && linea_cor[M]!=0x00)
	M++;

if(linea_cor[M]==0x00) {
	stampa_err(6,0,"0"); /* manca la "(", errore di sintassi */
	return(0);
}

M++;

sbianca(stringa,LUNGSTR-1);

while(nuovariga==0) {

	/* nomevar <-- sigla in DBL */
	/* valvar  <-- sigla in DBS */

	damminomi(nomevar,valvar,&nuovariga,&M);

	i=cerca(testa,nomevar,&dim,&ind);

	if(i>=16)
		cnome(nomevar,&i,&M);

	/* i <-- indica il tipo variabile nel DBL */

	if(tipo_aus!=-1) {

		/* caso READ/WRITE particolare  */
      berr=0;                 // nessun errore
      switch(tipo_aus)
      {
      case 0: case 6: case 12:               // analogici o reali
         if(i!=tanalogico && i!=treale) berr=1;
      break;
      case 1: case 7: case 13:               // interi
         if(i!=tintero) berr=1;
      break;
      case 2: case 8: case 14:               // digitali o logici
         if(i!=tlogico && i!=tdigitale) berr=1;
      break;
      case 3: case 9: case 15:               // organi
         if(i!=torgano) berr=1;
      break;
      case 4: case 10: case 16:               // stringhe
         if(i!=tstringa) berr=1;
      break;
      case 5: case 11: case 17:               // puntatori
         if(i!=tpuntan && i!=tpuntdi && i!=tpuntor
            && i!=tpuntcom && i!=tpuntst) berr=1;
      break;
      }
      if(berr) 
      {
	      stampa_err(12,0,"0");
         return(0);
      }

		/* test sul campo numerico intero di offset */

		if(isintero(valvar)!=1) {
			stampa_err(17,1,valvar);           /* valore fuori range */
			return(0);
		}
		valore=atoi(valvar);

		/* test sul range dei valori accettati per il campo offset */

		if(valore <=0 || valore >NUM_TIPWR_MAX) {
			stampa_err(39,1,valvar);           /* valore fuori range */
			return(0);
		}

      valore=(valore-1);
      icodop=tipo_aus+0x8000;
		new_code=codice;
	}

	else {

		/* caso READ/WRITE normale ( AN OR .. ) */

		r=cerca(testa,valvar,&dim,&ind);
		if(r>=16)
			cnome(valvar,&r,&M);

		if ( codice != 63 ) {

			/* istruzione READ o RWRITE */

			icodop = codistrd[tipo];
			itvdbl = tvdblrd[tipo];
			itvdbs = tvdbsrd[tipo];

		}

		else {

			/* istruzione WRITE */

			icodop = codistwr[tipo];
			itvdbl = tvdblwr[tipo];
			itvdbs = tvdbswr[tipo];

		}

		if ( !( ( i == itvdbl ) && ( r == itvdbs ) ) ) {

			stampa_err(12,0,"0"); /* tipi incongruenti per l'operz. */
			return(0);

		}

		new_code=codice;

	}

	/* new_code contiene il codice operativo corretto nel caso KA CA KD CD */

	/* preparo linea per il file intermedio */

	j=POS1; /* inserisco sul file intermedio rispettivamente */
	j+=sprintf(&stringa[j],"%4d",nword_o);   /* il P.C. */
	nword_o+=wordpar_ch[new_code];           /* e lo incremento */
	stringa[j]=BLANK;
	j=POS2;
	j+=sprintf(&stringa[j],"%s",par_chiav[new_code]);  /* parola chiave */
	stringa[j++]=BLANK;
	j+=sprintf(&stringa[j],"%d",icodop);             /* tipo primo argomento */
	stringa[j++]=BLANK;
	j+=sprintf(&stringa[j],"%s",nomevar);            /* nome primo argomento */
	stringa[j++]=BLANK;
	if(tipo_aus==-1)
		j+=sprintf(&stringa[j],"%s",valvar);    /* nome secondo argomento */
	else	{
		stringa[j++]='$';
		j+=sprintf(&stringa[j],"%x",valore);    /* nome secondo argomento */
	}

	scrivisufile(fdint,stringa,j+1,&righeint);

	if(linea_cor[++M]==BLANK)
		M++;

}

}

/*********************************************************************
*          							     *
*			Procedura led                                *
*          							     *
*	La procedura viene chiamata per trattare le istruzioni       *
* "LEDON", "LEDOFF" e "LEDBLK". Si controlla che l' argomento sia un intero    *
* compreso tra 1 e 256 compresi. Se lo e' si inserisce la riga nel   *
* file intermedio, altrimenti errore.                                *
*          					             *
*********************************************************************/

led(codice)
int codice;
{
int time_out=0,key=0,ok,i,M,sem=0;
char nomevar[9];
switch (codice) {   /* mi serve per sapere dove cominciare a leggere */
case  96 :           /* caso ledon  */
case  97 :           /* caso ledoff */
   M=codice-90;
   break;
case  98 :           /* caso key */
    M=4;
   break;			 
case 117 :			 /* caso ledblk */
 	M=7;
 	break;
case 123 :			 /* case SETTO */
 	M=6;
 	time_out=1;
 	break;
default:
	stampa_err(6,0,"");		// non previsto
	break;
}
i=sscanf(&linea_cor[M],"%8s",nomevar);   /* leggo l' argomento */
if((ok=isintero(nomevar))==1 && (i=atoi(nomevar))>=1 && (time_out==1 || i<=256))
	sem=1;         /* se appartiene al range setto sem a 1 */
if(sem)   /* se istruzione corretta */
	if(key==0) {   /* se sto compilando istruzione led */
		if(time_out==0)
			sprintf(&linea_cor[M],"%3d",i-1);  /* decremento codice tasto */
									/* cosi' il codice tasto passa da 1-256 a 0-255 */
		else
			sprintf(&linea_cor[M],"%3d",i);   /* inserisco time_out */
		intfile(codice);
  	}
	else           /* sto compilando istruzione key */
		return(i-1);   /* ritorno codice tasto -1 */
else {
	if(ok==1)
		stampa_err(39,1,nomevar);  /* fuori range */
	else
		stampa_err(17,1,nomevar);  /* non intero */
}
if(key==1)
	return(-1);
}

/*********************************************************************
	Decodifica l'istruzione CLRPAGE, Salva e hcpy
	Accetta un argomento intero contenente handle della pagina

*********************************************************************/

oppag(codice)
int codice;
{
int i,j,M,ok=0;
char nomevar[LUNG_VAR+1];
short ciclo;
char stringa[200];

if(codice==38)	M=8;				// clrpage
else if(codice==99) M=5;		// hcpy
else	M=6;							// salva

if(linea_cor[M]=='(') stampa_err(6,0,"");			// errore di sintassi

legginvar(nomevar,codice,&M,2);
if(!strlen(nomevar))
{
	linea_cor[M-1]=BLANK;  /*  tolgo il fine stringa */
	sprintf(&linea_cor[M],"%d",-1);
}
else
{
   i=cerca(testa,nomevar,&ciclo,&ciclo);
  	if(i>=16)
   	cnome(nomevar,&i,&M);
   strcpy(&stringa[j+1],nomevar);
  	controlla(nomevar,&M,i);
   if(i!=4) {    			  /* controllo che sia un intero */
	   stampa_err(29,1,nomevar); /* non e' un intero */
  	return(0);
	}
}
intfile(codice);
}

/*********************************************************************
*          							     *
*			Procedura key                                *
*          							     *
*	La procedura controlla che il primo argomento dell' istruzio=*
* ne "KEY" sia una zona o un tasto (nel tal caso la zona manca ). Se *
* e' una zona verifica che il secondo sia un tasto.                  *
*          							     *
*********************************************************************/

proc_key(codice)
int codice;
{
char nomevar[9];
int i,M,spiazz=0,cod_zona=-1,cod_tasto;
for(i=0,M=4;linea_cor[M]!=BLANK && linea_cor[M]!=0x00 &&
 	    linea_cor[M]!=VIRGOLA;M++)
	nomevar[i++]=linea_cor[M];
nomevar[i]=0x00;
while(linea_cor[M]==BLANK) {
	spiazz=1;  /* il secondo argomento e' separato anche dal blank */
	M++;
}
if(linea_cor[M]==0x00) {  /* senza specifica zona */
	spiazz=2;
	cod_tasto=led(codice+spiazz);  /* controllo che sia un indice di tasto corretto */
}
else {                    /* con specifica di zona */
	if(linea_cor[M]!=VIRGOLA)
		stampa_err(6,0,"0");  /* errore di sintassi */
	else {
		if((cod_zona=iszona(nomevar))!=-1)    /* controllo se zona corretta */
			cod_tasto=led(codice+spiazz);  /* verifico se tasto */
		else {  /* zona non ammissibile */
 		 cod_zona=-2;
			 stampa_err(40,1,nomevar);
		}
	}
}
if(cod_tasto!=-1 && cod_zona!=-2) {
	i=4;
	i+=sprintf(&linea_cor[i],"%3d",cod_tasto); /* inserisco codice tasto (0-255) */
	linea_cor[i++]=BLANK;
	i+=sprintf(&linea_cor[i],"%2d",cod_zona);  /* inserisco codice zona */
	intfile(codice);
}
}

/*********************************************************************
*          							     *
*			Procedura stat                               *
*
*   La procedura decodifica gli argomenti dell'istruzione stat cosi'
*   composta:
*   
*   STAT GRUPPO (FG, BG, BLK, SEL, ...,..,..,..)
*
*   GRUPPO opzionale (-1 se non definito)       word
*   FG,BG  opzionali (0xFFFF se non definiti)   word
*   BLK,SEL opzionali (0xFFFF se non definiti)  word
*
*********************************************************************/

stat(codice)
int codice;
{
int M=5;
char nomevar[LUNG_VAR+1];
char stringa[LUNGSTR];           // stringa scrittura codice
char *pch;                      // puntatore al token
short spiazzPC;
unsigned char  blink, sel, Bg, Fg;
short j,i,ciclo;
short n_arg;

memset(stringa,' ',sizeof(stringa));

j=POS1;
j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC */
stringa[j]=BLANK;
j=POS2;
j+=sprintf(&stringa[j],"%s",par_chiav[codice]);  /* inserisco SEND */
stringa[j]=BLANK;
spiazzPC=2;                // codice + gruppo
//
// recupero indice gruppo se esistente
//
pch=&linea_cor[M];
if(*pch=='(')        // nome gruppo non esistente
{
   strcpy(&stringa[j]," -1");
}
else                 // nome gruppo esistente
{
   legginvar(nomevar,codice,&M,2);
   i=cerca(testa,nomevar,&ciclo,&ciclo);
   if(i>=16)
	   cnome(nomevar,&i,&M);
   strcpy(&stringa[j+1],nomevar);
   controlla(nomevar,&M,i);
   if(i!=4) {    			  /* controllo che sia un intero */
	   stampa_err(29,1,nomevar); /* non e' un intero */
   	return(0);
   }
   pch=pch+strlen(nomevar)+1;        // escludo nome gruppo dalla ricerca
}
scrivisufile(fdint,stringa,0,&righeint);
memset(stringa,' ',sizeof(stringa));
j=POS1;
j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC */
stringa[j++]=BLANK;
j=POS2;
//
//    Ricerca sezioni Foreground, Background, Blink, Sel
//    separati da virgole
//
n_arg=0;
for(;;)
{
   pch++;
   if((*pch)==0) break;      // fine scansione argomenti
   
   n_arg++;
   while((*pch)==' ') pch++;
   if(*pch==',')  Fg=-1;
   else
   {
      pch=strtok(pch,",");          // foreground
      Fg=CercaCol(pch);
      pch=pch+strlen(pch);
   }
   pch++;
   if((*pch)==0) break;      // fine scansione argomenti
   n_arg++;
   if(*pch==',')  Bg=-1;            // background
   else
   {
      pch=strtok(pch,",");  
      Bg=CercaCol(pch);
      pch=pch+strlen(pch);
   }
   pch++;
   if((*pch)==0) break;      // fine scansione argomenti
   n_arg++;
   if(*pch==',')  blink=-1;            // blink
   else
   {
      pch=strtok(pch,",");  
      if(!strcmp(pch,"ON")) blink=1;
      else if(!strcmp(pch,"OFF")) blink=0;
      else stampa_err(42,0,pch);
      pch=pch+strlen(pch);
   }
   pch++;
   if((*pch)==0) break;      // fine scansione argomenti
   n_arg++;
   if(*pch==',' || *pch==')')  sel=-1;            // sel
   else
   {
      pch=strtok(pch,",)");  
      if(!strcmp(pch,"ON")) sel=1;
      else if(!strcmp(pch,"OFF")) sel=0;
      else stampa_err(42,0,pch);
      pch=pch+strlen(pch);
   }
   sprintf(&stringa[j],"$%04x $%04x",Fg*256+Bg,blink*256+sel);
	scrivisufile(fdint,stringa,0,&righeint);
   spiazzPC=spiazzPC+2;
}
if(n_arg % 4) stampa_err(6,0,"0");
nword_o+=spiazzPC;  /* aggiorno il PC */
}

/*********************************************************************
*          							     *
*			Procedura iszona                             *
*          							     *
*	La procedura rende -1 se il nome passato in nomevar non e'   *
* una zona, il numero corrispondente alla zona viceversa.            *
*          							     *
*********************************************************************/

iszona(nomevar)
char nomevar[];
{
int i;
for(i=0;i<3;i++)
	if((strcmp(nomevar,zona[i]))==0)
		return(i+1);  /* zona  corretta */
return(-1);  		    /* zona non corretta */
}

/*********************************************************************
*          							     *
*			Procedura iscolor                            *
*          							     *
* 	La procedura legge un carattere dalla linea corrente e       *
* verifica se e' un simbolo di colore corretto. Se lo e' rende l'    *
* offset rispetto al vettore dei colori se il secondo argometo e'    *
* diverso da zero o il codice ASCII della sigla del colore se uguale *
* a zero. In caso contrario rende -1.                                *
*          							     *
*********************************************************************/

iscolor(M,sem)
int *M;
int sem;
{
int i;
char c[2];
(*M)+=2;
if(linea_cor[(*M)++]!=0x3d) {
	stampa_err(6,0,"0");
	return(-1);
}
sscanf(&linea_cor[(*M)++],"%1s",c);
for(i=0;i<8;i++)
	if((strcmp(c,color[i]))==0)
		if(sem==0)
			return(c[0]); /* colore corretto rendo codice ASCII della sigla colore */
		else
			return(i);    /* colore  corretto rendo l' indice */
stampa_err(42,1,c);         /* visualizzo errore */
return(-1);  		    /* colore non corretto rendo -1 */
}

/*********************************************************************
*          							     *
*			Procedura ison_off                           *
*          							     *
*	La procedura legge prima due caratteri dalla linea corrente  *
* e se la stringa cosi' letta e' ON rende 1, altrimenti, sempre dalla*
* stessa posizione di prima ne legge tre e verifica se la stringa e' *
* OFF. In questo caso rende 0, altrimenti segnala errore e rende -1. *
*          							     *
*********************************************************************/

ison_off(M)
int *M;
{
char c[4];
(*M)+=3;
if(linea_cor[(*M)++]!=0x3d) {  /* mi aspetto il carattere "=" */
	stampa_err(6,0,"0");   /* se non lo trovo errore */
	return(-1);
}
sscanf(&linea_cor[*M],"%2s",c);
if((strcmp(c,"ON"))==0)  {    /* trovo ON e rendo 1 */
	(*M)+=2;
	return(1);
}
sscanf(&linea_cor[*M],"%3s",c);
if((strcmp(c,"OFF"))==0)  {   /* trovo OFF e rendo 0 */
	(*M)+=3;
	return(0);
}
stampa_err(42,1,c);           /* ne ON ne OFF segnalo errore */
return(-1);                   /* e rendo -1 */
}
