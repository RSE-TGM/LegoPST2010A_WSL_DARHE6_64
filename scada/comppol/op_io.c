/*
   modulo op_io.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)op_io.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*																							* 
*                   File op_io.c													* 
*																							*
*	pag(codice)																			*
*		int codice;																		*
*																							*
*	typacc(codice)																		*
*		int codice;																		*
*																							*
*	cifreIO(M,limite)																	*
*		int *M;																			*
*		int limite;																		*
*																							*
*	coloribfb(col,M)																	*
*		int *col;																		*
*		int *M;																			*
*																							*
*	legginome(nomevar,M)																*
*		char nomevar[]; 																*
*		int *M;																			*
*																							*
*	togliblank(nomestringa,inizio) 												*
*		char nomestringa[]; 															*
*	int inizio;  																		*
*         																				*
*********************************************************************/
#include <osf1.h>
#include <stdio.h>
#include <string.h>

#include "chascii.inc"
#include "define.inc"
#include "tipi.h"


#define LUNGSTR	   100
#define POS1	     3
#define POS2	    10

extern char linea_cor[];
extern int nword_o;
extern int fdint;
extern int righeint;
extern int subrcorr;

/********************************************************************
*          							     											  *
*			Procedura pag															  *
*                                                                   *
*	Sintassi :                                                       *

		PAG [nome_el] , [nome_pag] [,video] [,posto_op] [,page_handle]
		[,((GBLx (var1:nn) [,(var2:mm) areaL (oldLink1:newLink1)	])]

		dove:

		nome_el:	   stringa o variabile stringa nome elenco
		nome_pag:   stringa o variabile stringa nome pagina
		video, posto_op, page_handle variabili locali intere
		GBLx:			GBLA, GBLI, GBLD,....
		areaL:		AN, DI, OR, ST, HS, HC, LS, LC
		var1, var2: nomi variabili data base locale
		oldLink1:   stringa ASCII nome punto data base di sistema
		newLink1:   stringa ASCII nome punto data base di sistema
			  
			
		Per la corretta definizione della pagina deve essere definito
		almeno o il nome della pagina o l'elenco, tutti gli altri
		parametri sono opzionali
*          							     											  *
*********************************************************************/

pag(codice)
int codice;
{
/*
	tabelle di definizione aree possibili per passaggio parametri o
	nel data base locale o come variabili di link

	Nel caso di puntatore targ_pag vale -1 per accettare tutti i tipi
	di puntatore
*/
#define pag_aree	14
static char *aarg_pag[]={			// nomi aree permesse
                "GBLA", "GBLI", "GBLD", "GBLO","GBLS","GBLP",
					 "AN","DI","OR","ST","LS", "LC", "HC", "HS" };
static short varg_pag[]={			// codici aree
                0x8000, 0x8001, 0x8002, 0x8003, 0x8004, 0x8005,
					 tanalogico, tdigitale, torgano, tstringa,
					 tanls, tanlc, tanhc, tanhs};
static short targ_pag[]={			// tipo argomento 1 accettato
                tanalogico, tintero, tdigitale, torgano, tstringa, -1,
					 tanalogico, tdigitale, torgano, tstringa,
					 tanalogico, tanalogico, tanalogico, tanalogico};
static char sarg_pag[]={			// parametro 2 se  0 intero se 1 stringa ascii
                0, 0, 0, 0, 0, 0,
					 1, 1, 1, 1, 1, 1, 1, 1};

int i,M=4,j;
int tipo, dim, ind;
char *p,c[2],nomevar[LUNG_VAR+1],nomevar1[LUNG_VAR+1],nomearea[LUNG_VAR+1];
short narg=1;
char stringa[200];
char type[10];
short off;
int spiazzPC;
int narea;
int pos;
char bPar;				// flag indicante l'esistenza del nome della pagina
							// o dell'elenco

bPar=0;
p=nomevar;
togliblank(linea_cor,4);

memset(stringa,' ',sizeof(stringa));
pos=POS1;
pos+=sprintf(&stringa[pos],"%4d",nword_o);  /* inserisco il PC */
stringa[pos]=BLANK;
pos=POS2;
pos+=sprintf(&stringa[pos],"%s",par_chiav[codice]);  /* inserisco PAG */
scrivisufile(fdint,stringa,pos+1,&righeint);
if( linea_cor[M-1] != BLANK  ) stampa_err(6,0,"0");
spiazzPC=1;

do						// ciclo interpretazione parametri
{
	memset(nomevar,' ',sizeof(nomevar));
	nomevar[sizeof(nomevar)-1]=0;
	memset(stringa,' ',sizeof(stringa));
	pos=POS1;
	pos+=sprintf(&stringa[pos],"%4d",nword_o);  /* inserisco il PC */
	stringa[pos]=BLANK;
	pos=POS2;

	if(!linea_cor[M])			// parametro non presente
	{
		pos+=sprintf(&stringa[pos],"%s","-1");
		spiazzPC++;
	}
	else if(linea_cor[M]==VIRGOLA)	// indicato il default
	{
			pos+=sprintf(&stringa[pos],"%s","-1");
			spiazzPC++;
	}
	else								// parametro presente
	{
		legginome(nomevar,&M);			//	leggo parametro
		if(nomevar[0] != '"' )    		// e' una stringa ? no
		{ 
			if((p=strchr(nomevar,0x20))!=NULL)	*p=0;
			tipo=cerca(testa,nomevar,&dim,&ind);
			if ( tipo == -1 )				// variabile non esistente
				stampa_err(59,1,nomevar);
			if(tipo>=16) cnome(nomevar,&tipo,&M);
			controlla(nomevar,&M,tipo);

			if(tipo!=7 && narg <=2)			         // verifico se di tipo stringa
				stampa_err(12,1,nomevar);
			if(narg<=2) bPar=1;
			if(tipo!=tintero && narg > 2)			   // verifico se di tipo intero
				stampa_err(12,1,nomevar);
			if((p=strchr(nomevar,0))!=NULL)
			*p=0x20;
			strcpy(type,"$0000");
			spiazzPC+=2;
		}
		else									// nome elenco stringa 
		{
			if((p=strchr(&nomevar[1],'"'))==NULL) stampa_err(6,0,"0");
			else
			{
				*p=' ';
				off=(p-(&nomevar[0])) & 0xFFFE;		// lunghezza stringa pari o dispari
				nomevar[off+1]='"';
				sprintf(type,"$%04x",off);
				spiazzPC=spiazzPC+off/2+1;
				if(narg<=2) bPar=1;
				if(narg > 2) stampa_err(12,1,nomevar); // non puo' essere una stringa
			}
		}
		pos+=sprintf(&stringa[pos],"%s %s",type,nomevar); 		 // inserisco parametro
	}
	if(linea_cor[M]==',') M++;						 // elimino separatore ';'
	narg++;
	scrivisufile(fdint,stringa,pos+1,&righeint);
}
while(narg<=5);			// elenco pagina video postoop handle
if(!bPar) stampa_err(56,0,"");

if(linea_cor[M]!='(' && linea_cor[M]) stampa_err(6,0,"0");  // errore sintassi
if(linea_cor[M])				// altri parametri
{
	M++;

	while (linea_cor[M]=='(' || linea_cor[M]==' ' || linea_cor[M]!=')')		// esistono parametri
	{
//
//	ciclo interpretazione AREA (PAR1:PAR2,.....,PARn:PARm),
//
		memset(nomearea,0,sizeof(nomearea));
		memset(nomevar,0,sizeof(nomevar));
		memset(nomevar1,0,sizeof(nomevar1));
		j=M;
		legginome(nomearea,&j);			//	area
		for(i=0;i<strlen(nomearea);i++,M++)
			if(nomearea[i]=='(') {nomearea[i]=0;  break;}
//
//		verifico se nome area e' accettabile
//
		for(narea=0;narea<pag_aree;narea++)
		{
			if(!strcmp(nomearea,aarg_pag[narea])) break;
		}
		if(narea==pag_aree) {stampa_err(6,1,nomearea); narea=0;}
		while(linea_cor[M]==',' || linea_cor[M]=='(')
		{
			M++;
			if(!linea_cor[M])
			{
				if(new_lico()==-1) break;			// lettura riga successiva test eof
				M=0;  
				togliblank(linea_cor,M);
			}
			j=M;
			legginome(nomevar,&j);			//	argomento 1  sep : 
			for(i=0;i<strlen(nomevar);i++,M++)
			  if(nomevar[i]==':') {nomevar[i]=0; break;}
 			memset(stringa,' ',sizeof(stringa));
	 		pos=POS1;
 			pos+=sprintf(&stringa[pos],"%4d",nword_o);  /* inserisco il PC */
 			stringa[pos]=BLANK;
	 		pos=POS2;
 			pos+=sprintf(&stringa[pos],"$%04x",varg_pag[narea]);
 			spiazzPC++;
			if(!sarg_pag[narea])				// verifico variabile esistente: caso GBL
			{
				tipo=cerca(testa,nomevar,&dim,&ind);
		 		if (tipo==-1)	stampa_err(59,1,nomevar);
				if(tipo>=16) cnome(nomevar,&tipo,&M);
			 	controlla(nomevar,&M,tipo);
				if(targ_pag[narea]==-1)
				{
					if(tipo!=tpuntan && tipo!=tpuntdi	  // controllo puntatori
					&& tipo!=tpuntor && tipo!=tpuntst && tipo != tpuntcom
					) stampa_err(60,1,nomevar1);
				}
				else if(tipo!=targ_pag[narea]) stampa_err(60,1,nomevar);
				pos+=sprintf(&stringa[pos]," %s",nomevar);
				spiazzPC++;
			}
			else					// verifico variabile esistente caso: LINK
			{
				if((ind=declink(nomevar,targ_pag[narea]))==-1) stampa_err(60,1,nomevar);
				pos+=sprintf(&stringa[pos]," $%04x",ind);
				spiazzPC++;
			}
			M++;
			j=M;
			legginome(nomevar1,&j);			//	argomento 2	 sep , o )
			for(i=0;i<strlen(nomevar1);i++,M++)
				if(nomevar1[i]==')'|| nomevar1[i]==' ') {nomevar1[i]=0;  break;}
			if(!sarg_pag[narea])				// verifico intero accettabile: caso GBL
			{
				if(sscanf(nomevar1,"%d",&tipo)!=1 || tipo<1 || tipo>NUM_TIPWR_MAX)
						stampa_err(39,1,nomevar1);          // valore non accettabile
				pos+=sprintf(&stringa[pos]," $%04x",tipo-1);
				spiazzPC++;
			}
			else									// nome variabile link qualsiasi: caso LINK new name
			{										// oppure puntatore ind DBS
				tipo=cerca(testa,nomevar1,&dim,&ind);
		 		if (tipo!=-1)					// variabile definita 
				{									// verifico se puntatore
					if(tipo>=16) cnome(nomevar1,&tipo,&M);
				 	controlla(nomevar1,&M,tipo);
					if(tipo!=tpuntan && tipo!=tpuntdi	  // controllo puntatori
					&& tipo!=tpuntor && tipo!=tpuntst && tipo != tpuntcom
					)
					{			// non e' puntatore lo considero stringa link
						if((ind=declink(nomevar1,targ_pag[narea]))==-1) stampa_err(60,1,nomevar1);
						pos+=sprintf(&stringa[pos]," $%04x",ind);
						spiazzPC++;
					}
					else
					{
						pos+=sprintf(&stringa[pos]," -1");
						scrivisufile(fdint,stringa,pos+1,&righeint);
						spiazzPC++;
	 					pos=POS1;
		 				pos+=sprintf(&stringa[pos],"%4d",nword_o);  /* inserisco il PC */
 						stringa[pos]=BLANK;
				 		pos=POS2;
						pos+=sprintf(&stringa[pos],"%s",nomevar1);
						spiazzPC++;
					}
				}
				else				// nome diretto nuovo Link
				{
					if((ind=declink(nomevar1,targ_pag[narea]))==-1) stampa_err(60,1,nomevar1);
					pos+=sprintf(&stringa[pos]," $%04x",ind);
					spiazzPC++;
				}
			}
			if(!strlen(nomevar1) || !strlen(nomevar))	stampa_err(6,0,"0");  // errore sintassi
			scrivisufile(fdint,stringa,pos+1,&righeint);
		}
		M++;
		if(!linea_cor[M])
		{
			if(new_lico()==-1) break;			// lettura riga successiva test eof
			M=0;  
			togliblank(linea_cor,M);
		}
		if(M>strlen(linea_cor))
		{
			stampa_err(6,0,"0");  // errore sintassi
			break;
		}
	}
}
/*
	inserisco tappo fine argomenti
*/
memset(stringa,' ',sizeof(stringa));
pos=POS1;
pos+=sprintf(&stringa[pos],"%4d",nword_o);  /* inserisco il PC */
stringa[pos]=BLANK;
pos=POS2;
pos+=sprintf(&stringa[pos],"-1");
spiazzPC++;
scrivisufile(fdint,stringa,pos+1,&righeint);
nword_o=nword_o+spiazzPC;
}

/*********************************************************************
*
*			Procedura typacc
*	Esegue controlli e decodifica per le istruzioni  ACCEPT e TYPE
*
*********************************************************************/

typacc(codice)
int codice;
{
int temp,nuovariga,x,y,j,i,M,s=0,mm,nn=-1,dim,ind,tipo;
int zoom=0x30,aus=0,color,colO=19,colI,spiazzPC=0,sem;
static char tabzoom[]={0,16,1,17,33,18,34,51};
unsigned int xx;
char stringa[LUNGSTR],nomevar[LUNG_VAR+1];

togliblank(linea_cor,0);	// pulisce la linea di codice dai blank

if(codice==99) 			  // si posiziona all'inizio della stringa
	M=7;
else
	M=5;

sbianca(stringa,LUNGSTR);    // riempie di blank la stringa.
j=POS1;
j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC */
stringa[j]=BLANK;
j=POS2;
j+=sprintf(&stringa[j],"%s",par_chiav[codice]);  /* inserisco TYPE o ACCEPT */
stringa[j++]=BLANK;
if(linea_cor[M-1]!=APTONDA)
	stampa_err(6,0,"0");    /* errore di sintassi */
if(codice==99) {				/* se caso ACCEPT verifico la presenza del TIMEOUT */
	sem=legginvar(nomevar,codice,&M,2);
	if(sem!=-1)   {
		tipo=cerca(testa,nomevar,&dim,&ind);
		if(tipo==-1) {  /* variabile di timeout non presente oppure errata */
			j+=sprintf(&stringa[j],"%s","-1");
			M=7;
		}
		else {
			if(tipo>=16)
				cnome(nomevar,&tipo,&M);
			controlla(nomevar,&M,4);
			j+=sprintf(&stringa[j],"%s",nomevar);
			M++;
		}
	}
	else  {
		j+=sprintf(&stringa[j],"%s","-1");
		M=7;
	}
}
stringa[j++]=BLANK;
do {
	sscanf(&linea_cor[M++],"%2s",nomevar);  /* leggo la riga o la colonna */
	if(nomevar[1]==VIRGOLA)
		nomevar[1]=0x00;   /* numero di una sola cifra, non incremento M  */
	else
		M++; /* numero di due cifre, devo aumentare M per posizionarmi sulla virgola */
	if(isintero(nomevar)==1) {
		if(!((x=atoi(nomevar))>=0 && x<=39+40*s))
			stampa_err(39,1,nomevar);  /* fuori range */
	}
	else
		stampa_err(17,1,nomevar);          /* non intero */
	 if(s==0)           /* ho letto la riga */
		y=256*x;    /* e la memorizzo nel byte superiore */
	else                /* ho letto la colonna */
		y+=x;       /* e la memorizzo nel byte inferiore */
	if(linea_cor[M++]!=VIRGOLA)
		stampa_err(6,0,"0");   /* errore di sintassi */
}
while((++s)<2);   /* quando esco sono posizionato sul primo carattere di STAT O */
j+=sprintf(&stringa[j],"%s","$");  /* inserisco nella stringa riga-colonna */
j+=sprintf(&stringa[j],"%04x",y);
stringa[j++]=BLANK;
j+=sprintf(&stringa[j],"%2d",-1); /* inserisco la word vuota */
stringa[j++]=BLANK;
if(linea_cor[M]!=PIU)
	coloribfb(&colO,&M);  /* fine STAT O, sono posizionato sul separatore "+" */
if(linea_cor[M++]!=PIU)       /* controlli sintattici */
	stampa_err(6,0,"0");
if(linea_cor[M++]!=VIRGOLA)
	stampa_err(6,0,"0");
coloribfb(&colI,&M); /* fine STAT I */
if(colI==19)
	colI=colO;    /* assegno i valori di STAT I per default uguali a  STAT O */
color=colO+colI*256; /* assegno al byte alto STAT O e a quello basso STAT I */
j+=sprintf(&stringa[j],"%s","$");     /* inserisco i colori di I/O */
j+=sprintf(&stringa[j],"%04x",color);
if(linea_cor[M]=='Z') {			/* valore di zoom */
	zoom=linea_cor[++M];
	if(zoom<'0' || zoom >'8')
		stampa_err(52,0,"0");
	if(linea_cor[++M]!=VIRGOLA)
		stampa_err(6,0,"0");
	M++;
}
stringa[j++]=BLANK;
stringa[j++]=0x24;
j+=sprintf(&stringa[j],"%02x",tabzoom[zoom-'0']);
scrivisufile(fdint,stringa,j+1,&righeint);
/* sono posizionato sul primo argomento */
spiazzPC=5; /* comincio a calcolare il codice prodotto dall' istruzione */
	    /* per ora considero :
	       Cod.istr - x,y - word vuota - STAT O/I - zoom */
if(codice==99)
	spiazzPC++;		/* caso ACCEPT : considero la variabile di timeout */
while(linea_cor[M]!=CHTONDA) {
 nuovariga=0;
	if(linea_cor[M]==VIRGOLETTE) { /* caso stringa da stampare */
		sbianca(stringa,15);
		j=POS1;
		j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC, */
		stringa[j++]=BLANK;
		j=POS2+6;
		stringa[j++]=linea_cor[M++]; /* le virgolette iniziali, */
		for(i=0;i<81 && linea_cor[M]!=VIRGOLETTE && linea_cor[M]!=0x00;i++)
			stringa[j++]=linea_cor[M++];  /* la stringa da scrivere */
		if((i%2)==1)  {   /* se il numero di caratteri e' dispari */
			stringa[j++]=BLANK; /* aggiungo un BLANK alla fine */
			i++;      /* ed incremento il numero di caratteri */
			aus=-1;
		}
		stringa[j++]=VIRGOLETTE;   /* virgolette finali */
		stringa[j]=0x00;
		if(linea_cor[M]==0x00)   {
			stampa_err(1,0,"0");  /* errore di sintassi */
			nuovariga=1;
		}
		spiazzPC+=(i/2)+1;  /* codice prodotto :
			numero caratteri stringa / 2 = word occupate dalla stringa,
			1 = word contenente lunghezza stringa */
		sprintf(&stringa[POS2],"%s","$");
		temp=sprintf(&stringa[POS2+1],"%04x",i+aus); /* lunghezza stringa */
		aus=0;
		stringa[temp+POS2+1]=BLANK;
		scrivisufile(fdint,stringa,j+1,&righeint);
	}
	else
		if(linea_cor[M]==0x00)
			nuovariga=1; 		/*  fine riga */
		else {
 /* caso variabile da leggere (codice=99) o scrivere (codice=100) */
			mm=cifreIO(&M,80);  /* lunghezza i/o */
			if(!((linea_cor[M]==PUNTO && codice==100) ||
 		    (linea_cor[M]==APQUADRA && codice==99)))
				stampa_err(6,0,"0");   /* sintassi */
			if(codice==100)  {
				M++;
				if((nn=cifreIO(&M,-1))>mm-2)  /* n. decimali */
					stampa_err(39,0,"0"); /* fuori range */
				if(linea_cor[M]!=APQUADRA)
					stampa_err(6,0,"0");
			}
			M++;   /* salto la "[" */
			legginvar(nomevar,codice,&M,2);  /* leggo nome var */
			for(i=0;nomevar[i]!=0x00;i++)
				if(nomevar[i]==CHQUADRA) {
					nomevar[i]=0x00;  /* tolgo "[" */
					M--;   /* mi posiziono su "]" o ")" */
					break;
 			}
			if(linea_cor[M]==CHTONDA)
				M--;  /* mi posiziono su "]" */
			tipo=cerca(testa,nomevar,&dim,&ind);
			if(tipo>=16)
				cnome(nomevar,&tipo,&M);
			controlla(nomevar,&M,tipo);
			if(tipo==7 && mm>dim)
				mm=dim;
			if(linea_cor[M]!=CHQUADRA)   {
				stampa_err(6,0,"0");
				if(linea_cor[M]==0x00)
					nuovariga=1;
			}
/* controllo tipi ed argomenti ed inserisco nel file intermedio */
			sbianca(stringa,LUNGSTR-1);
			j=POS1;
			j+=sprintf(&stringa[j],"%4d",nword_o);
			stringa[j]=BLANK;
			j=POS2;
			spiazzPC+=2; /* 1 word di formato, 1 word per indirizzo var */
			if(codice==100) {   /* caso type */
				if(!(tipo==0 || tipo==3)) {
/* caso non analogico e non reale */	if(nn>0)
/* n. cifre decimali deve essere 0 */		stampa_err(44,0,"0");
/* metto -1 a significare che non ci */	nn=15;
/* devono essere cifre decimali, per non confondere con quando ne sono
  ammesse e non le voglio  visualizzare */
				}
				if(tipo!=7 && mm>16)
					stampa_err(39,0,"0");
				if(tipo!=7)
					mm=(mm*16+nn)+(tipo+1)*256;
/* byte alto : semi-byte sup.=cifre i/o, semi-byte inf.=cifre decimali
   byte basso : tipo */
				else
/* byte alto cifre i/o, byte basso 8 	*/  mm+=256*8;
			}
			else {              /* caso accept */
	/* byte alto : cifre i/o   ;   byte basso : tipo */
				if(tipo==7)
					mm=mm+(tipo+1)*256;
				else {
					switch(tipo) {
					case 0 :
						tipo=3;
					break;
					case 1 :
						tipo=5;
					break;
					case 2 :
						tipo=4;
					break;
					}
					mm=mm+tipo*256;
				}
			}
			j+=sprintf(&stringa[j],"%s","$");
			j+=sprintf(&stringa[j],"%04x",mm);
			stringa[j++]=BLANK;
			j+=sprintf(&stringa[j],"%5s",nomevar);
			scrivisufile(fdint,stringa,j+1,&righeint);
		}
	if(nuovariga==1) {
		while((i=new_lico())==0)
			;
		if(i==-1)
			return(-1);
		M=0;
		togliblank(linea_cor,M);
	}
	else   {
		if(!(linea_cor[++M]==VIRGOLA || linea_cor[M]==CHTONDA))
			stampa_err(6,0,"0");
		if(linea_cor[M]==VIRGOLA)
			M++;
	}
}    /* fine while */

/* inserisco il tappo finale (-1) */
spiazzPC++;
sbianca(stringa,15);
j=POS1;
j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC */
stringa[j]=BLANK;
j=POS2;
j+=sprintf(&stringa[j],"%2d",-1); /* inserisco la word vuota */
scrivisufile(fdint,stringa,j+1,&righeint);

nword_o+=spiazzPC;  /* aggiorno il PC */
return(1);
}


/*********************************************************************
*          							     *
*			Procedura cifre
*          							     *
*********************************************************************/

cifreIO(M,limite)
int *M;
int limite;    /* se -1 non controllo lim. sup. */
{
int mm=-1;
char nomevar[4];
sscanf(&linea_cor[(*M)++],"%2s",nomevar);
if(!(nomevar[1]>=0x30 && nomevar[1]<=0x39))
	nomevar[1]=0x00; /* solo una cifra */
else
	(*M)++; /* numero di due cifre */
if((isintero(nomevar))==1)  {
	if((mm=atoi(nomevar))<0) {
		stampa_err(39,1,nomevar);
		return(-1);
	}
	if(limite>=0 && mm>limite) {
		mm=-1;
		stampa_err(39,1,nomevar);
	}
}
else
	stampa_err(17,1,nomevar);
return(mm);
}

/*********************************************************************
*          							     *
*			Procedura colorbfb
*          							     *
*********************************************************************/

coloribfb(col,M)
int *col;
int *M;
{
int i,ciclo=0,bg=0,colf=7,colb=0,blk=0;
char nomevar[4];
while(ciclo<2) {
	sscanf(&linea_cor[*M],"%2s",nomevar);
	if((strcmp(nomevar,"BG"))==0) {  /* trovo BG */
		if(bg==1)
			stampa_err(41,1,"BG");
		bg=1;
		if((i=iscolor(M,1))!=-1)
			colb=i;  /* memorizzo l' indice del colore */
	}
	else
		if((strcmp(nomevar,"FG"))==0) {  /* trovo FG */
			if((i=iscolor(M,1))!=-1)
				colf=i;  /* memorizzo indice colore */
			ciclo++;         /* esco dal ciclo */
		}
		else
			break;
	if(linea_cor[(*M)++]!=VIRGOLA)
 	stampa_err(6,0,"0");
} /* fine while */
sscanf(&linea_cor[*M],"%3s",nomevar);
if((strcmp(nomevar,"BLK"))==0) {         /* trovo BLK */
	if((i=ison_off(M))!=-1)
		blk=i;                   /* ON = 1, OFF = 0 */
	if(linea_cor[(*M)++]!=VIRGOLA)
		stampa_err(6,0,"0");
}

/* colore :  bit da 0 a 2 il foreground, bit 3 blink,
	     bit da 4 a 6 il background, bit 7 inutilizzato */
*col=colb*16+blk*8+colf;
/**
*col=64*blk+8*colb+colf;
**/
}

/*********************************************************************
*          							     *
*			Procedura legginome
*          							     *
*********************************************************************/

legginome(nomevar,M)
char nomevar[];
int *M;
{
int i;
for(i=0;linea_cor[*M]!=VIRGOLA && linea_cor[*M]!=0x00 &&
    ((subrcorr==-1 && i<EF_LUNGVAR) || (subrcorr!=-1 && i<LUNG_VAR));(*M)++)
	nomevar[i++]=linea_cor[*M];
while(i<10)
	nomevar[i++]=BLANK;
while(!(linea_cor[*M]==VIRGOLA || linea_cor[*M]==0x00))
	*M++;
}

/*********************************************************************
*          			                                    			 
*			Procedura togliblank
* Elimina tutti i blank presenti all'interno della stringa esclusi         					 
* quelli compresi tra " e ".         					 
*          					 
*********************************************************************/

togliblank(nomestringa,inizio)
char nomestringa[];
int inizio;
{
int j,s,t,sem=0;
for(j=inizio;nomestringa[j]!=0x00;j++)   {
	if(nomestringa[j]==VIRGOLETTE)
		sem=!sem;
	if(nomestringa[j]==BLANK && sem==0) {
		for(s=j,t=j+1;nomestringa[t]!=0x00;s++,t++)		// compattamento
			nomestringa[s]=nomestringa[t];
	nomestringa[s]=0x00;
	}
}
}
