/*
   modulo locmem.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)locmem.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*          							                                       *
*			   File LOCMEM.C                                            *
*  	       							                                    *
*	 		PROCEDURE CONTENUTE			                                 *
*  	       							                                    *
*	var()                                                             *
*          							                                       *
*	struct variabili *inserisci(albero,nvar,tvar,h)                   *
*			struct variabili *albero;                                   *
*			char nvar[];                                                *
*			int tvar;                                                   *
*			int *h;                                                     *
*          							                                       *
*	insDB(albero,ind)        				                              *
*			struct variabili *albero;                                   *
*			int ind;                                                    *
*			int s;                                                      *
*			int *spiazz;                                                *
*          							                                       *
*	inscostanti(albero,ind)                                           *
*			struct variabili *albero;                                   *
*			int ind;                                                    *
*          							                                       *
*	cost()                                                            *
*          							                                       *
*	letturadb()                                                       *
*          							                                       *
*	cercaread(albero,nomev,valv,indice)                               *
*			struct variabili *albero;                                   *
*			char nomev[],valv[];                                        *
*			int indice;                                                 *
*          							                                       *
*	dammitipo(prov,s)                                                 *
*			char prov[];                                                *
*			int s;                                                      *
*          							                                       *
*	damminomi(nomev,valv,nuovariga,M)                                 *
*			char nomev[],valv[];                                        *
*			int *nuovariga,*M;                                          *
*          							                                       *
*********************************************************************/

#ifdef INGLESE
#define tooManyVar      "TOO MANY VARIABLES, CAN'T GO ON"
#define variable        "VARIABLE : %s "
#define press           "PRESS ANY KEY TO EXIT"
#define varLink         "LINK VARIABLE : %s"
#else
#define varLink         "VARIABILE DI LINK DA INTRODURRE : %s "
#define press           "PREMERE UN TASTO PER TERMINARE"
#define variable        "VARIABILE DA INTRODURRE : %s "
#define tooManyVar      "UTILIZZATE TROPPE VARIABILI, IMPOSSIBILE PROSEGUIRE"
#endif

#include <osf1.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "chascii.inc"

#include "tipi.h"

#include "define.inc"

extern char linea_cor[];
extern int numriga;
extern int fdlst;
extern int INDDB;
extern int cont_gruppi;
int hh;
struct variabili *inserisci();
int n_byte[NUM_TIPVAR]={6,1,2,4,2,2,1,1,2,4,4,4,4,2,4,4};

/*********************************************************************
*          							                                       *
*			   Procedura var                                            *
*          							                                       *
* La procedura e' chiamata dal main e inserisce le variabili definite*
* tramite "define" nel data base, utilizzando un albero bilanciato   *
* e, controllando che le sintassi sia rispettata, considera solo le  *
* prime 8 lettere di ogni variabile ed inserisce solo quelle che non *
* siano gia' state definite finche' non si superi il numero massimo  *
* di variabili consentite.					                              *
* Per ogni errore viene incrementeta la variabile "errori". 	      *
* Il programma prende ed esamina una riga alla volta presa dal file  *
* di input tramite la procedura "new_lico" finche' non trova una riga*
* che non inizia con "DEFINE".					                        *
* Prima di tornare il controllo al main risolve gli indirizzi delle  *
* variabili nel DB chiamando la procedura insDB passandogli il tipo  *
* delle variabili secondo l' ordine prestabilito.		               *
*          							                                       *
*********************************************************************/

var()

{

  int M,s,n,i,status,ins;
  int numerovar=0,p,dim=0,vet,j;
  int flvirg,flerr1,flsignum;
  char t[7],prov[3];
  char nomevar[LUNG_VAR+1],etic[7];
  char deflocal[100];
  short cd;					// tipo di variabile

  testa=NULL;
  hh=0;

  while(1) {

	  while((n=new_lico())==0)
			;

	 if(n==-1)
		return(-1);  /* trovata la fine del file sorgente */

	 cd=0;

 	 if(!strncmp(linea_cor,"LDEFINE",7))			// variabile di tipo DEFINE LOCALE
	 {
		sscanf(linea_cor,"%s",deflocal);
		deflocal[7]='Š';
		cd=decgrp(&deflocal[7]) << 4;
		strcpy(linea_cor,"DEFINE");
		strcat(linea_cor,&linea_cor[strlen(deflocal)]);
	 }
	 else deflocal[0]=0;

/* Carico da linea_cor la stringa ASCII che definisce l'istruzione */

	 for(i=0;i<7 && linea_cor[i]>=0x41 && linea_cor[i]<=0x5a;i++)
			t[i]=linea_cor[i];  /* leggo l'istruzione */

	 t[i]='\0';
 	 if((strcmp(t,"DEFINE"))!=0)
		return;    /* se non e' una DEFINE torno al main */
	 else
 	 {

      /* Trovata istruzione DEFINE */

		i=dammitipo(prov,7); /* testo il tipo della DEFINE */

		if(i==-1)
			stampa_err(2,1,prov);  /* tipo non consentito */

		else {

		/* Istruzione DEFINE di tipo consentito */

		if(!(linea_cor[9]==APTONDA || linea_cor[10]==APTONDA))
				stampa_err(6,0,"0");  /* errore di sintassi */

			else {

			/* Il carattere n. 10 o n. 11 risulta essere APTONDA */

				if(linea_cor[9]==APTONDA && linea_cor[10]!=BLANK)
					M=10;
				else
					M=11;

       /* Ciclo di scansione della lista delle variabili */

		 while(linea_cor[M]!=CHTONDA && linea_cor[M]!=0x00) {

			/* Ciclo di compattamento caratteri BLANK */

		   while(linea_cor[M]==BLANK)
			 M++;

         vet=0;     // resetto il flag di variabile vettoriale
         flvirg=0;  // resetto il flag presenza separatore virgola
         flsignum=1;  // setto flag sigla variabile formata da numeri

			/* Ciclo interno di estrazione sigla completa di dimensioni */

			for(s=0;linea_cor[M]!=CHTONDA &&
			linea_cor[M]!=BLANK && linea_cor[M]!=VIRGOLA &&
			linea_cor[M]!=0x00 && s<LUNG_VAR &&
				(s<(EF_LUNGVAR-1) || vet ) ;M++)  {

					if(linea_cor[M+1]==APTONDA) vet=1; // 10 caratteri + (
					if(linea_cor[M]==APTONDA) {

					   if( s == 0 ) {

						  /* Nome variabile vettoriale costituito da 0 char */

                    stampa_err(6,0,"0");  /* Errore di sintassi */
						  vet = -1;

						   }

						else {

							if ( flsignum == 1 ) {

								nomevar[s] = 0x00;

                    		stampa_err(73,1,nomevar);  /* nome variabile non accettabile */

							}

	              	  vet=1;                   /* variabile vettoriale */

							}

						}

					if ( !( (linea_cor[M] >= 0x30) && (linea_cor[M] <= 0x39) ) ) {

						flsignum = 0;  // resetto flag flsignum

						}

               nomevar[s++]=linea_cor[M];  /* carico nomevar       */	

				}

				/* Verifico la presenza di errori di sintassi */

				if ( (s==0) && (linea_cor[M]==VIRGOLA) ) {

				/* Un nome di variabile con 0 char precede una virgola */

              stampa_err(6,0,"0");  /* Errore di sintassi */
				  break;

				}

				if ( (vet==1) && ( linea_cor[M]!=CHTONDA) ) {

				/* Manca la parentesi chiusa in una variabile vettoriale */

              stampa_err(6,0,"0");  /* Errore di sintassi */
				  break;

				}

				else {

				if ( (vet==0) &&
				  ((linea_cor[M]!=CHTONDA) && (linea_cor[M]!=VIRGOLA) &&
				   (linea_cor[M]!=BLANK)) ) {

				/* Manca o la parentesi chiusa o la virgola di termine */

              stampa_err(6,0,"0");  /* Errore di sintassi */
				  break;

				  }


				}

         	if(vet && linea_cor[M]==CHTONDA) /* se variabile vettoriale     */
					nomevar[s++]=linea_cor[M++];  /* inserisco in nomevar la ")" */		

				nomevar[s]='\0';

				if(linea_cor[M]==0x00) {
              stampa_err(6,0,"0");  /* Errore di sintassi */
					break;
				}

				flerr1 = 0;

				while(linea_cor[M]!=CHTONDA && linea_cor[M]!=VIRGOLA && linea_cor[M]!=0x00) {
                  if(linea_cor[M]!=BLANK) {				       
						flerr1 = 1;
                  stampa_err(6,0,"0");  /* Errore di sintassi */
						break;
						}
						M++;
				}

				if( flerr1 == 1) 
				  break;

				if(linea_cor[M]==0x00) {
              stampa_err(6,0,"0"); /* Errore di sintassi */
					break;
				}

               /* Verifico se la variabile risulta di tipo vettoriale */

               if(vet) { 

					/* Posizionamento sul numero di componenti */

                   for(p=0;nomevar[p]!=APTONDA;p++) 
      	              	;

						/* Carico in etic la dimensione della variabile */

						for(vet=0,p++;nomevar[p]!=CHTONDA && vet<7;vet++,p++)
							etic[vet]=nomevar[p];

						etic[vet]=0x00;

						/* Verifico se la dimensione vettoriale risulta intera */

						if((isintero(etic))==-1)
                      stampa_err(17,1,etic);

						/* Tolgo in nomevar la parte contenente la dimensione */

                  for(vet=0;nomevar[vet]!=APTONDA;vet++)
							;

						nomevar[vet]='\0';

						/* Converto in intero la dimensione della variabile */

                  dim=atoi(etic);

                  /* Controllo i vincoli imposti alla dimensione :

						tipo 3 = RE ( 1 - 256 )
						tipo 4 = IN ( 1 - 256 )
						tipo 5 = LG ( 1 - 256 )
						tipo 7 = LG ( 1 -  80 )	  */


                  if(dim>0 && dim<=256 &&
						  (i==3 || i==4 || i==5 || (i==7 && dim<=80))) {

							if(i==7)

							/* Se la variabile e' di tipo stringa incremento la
							   dimensione di uno per il NULL di terminazione */

								dim++;

							/* I primi 4 bit di dim contengono il tipo variabile */

							dim=i+16*dim;

						}
						else {

						/* Dimensionamento non corretto */

							vet=-1;
 							stampa_err(8,1,nomevar);

						}

					}
					else {

					/* Variabile dichiarata non di tipo vettoriale */

                  if(i==7) 

						/* Variabile di tipo stringa di tipo non vettoriale */

 							stampa_err(8,1,nomevar);

						else

                     dim=i;

					}

					if( (vet!=-1) && ( tstnomvar(nomevar)==1 ) ) {

					/* N. B. vet = -1 significa condizione di errore */

						if(deflocal[0])
						{
							strcat(nomevar,&deflocal[7]);
						}
						if(i!=8)

					   testa=inserisci(testa,nomevar,dim,&hh,"0",cd+2,0);

						else

						/* Caso di variabile di tipo gruppo */

                  testa=inserisci(testa,nomevar,4,&hh,"0",cd+3,1);
					}

				   if( (linea_cor[M]==VIRGOLA) && 
					    (linea_cor[M+1]==CHTONDA) ) {
					flvirg = 1;

					}

				   if( (linea_cor[M]!=CHTONDA) )
					     M++;

				}

			   if(flvirg == 1) {

            stampa_err(6,0,"0");  /* Errore di sintassi */

			   }

			}  /* While scansione lista variabili */
		}	   /* Tipo variabile consentito */
		} 	   /* Istruzione DEFINE riconosciuta */
	}        /* fine while (1) */
}


/*********************************************************************
*          							                                       *
* 		   Procedura inserisci(A,B,C,D)                                *
*   			                         		                           *
* Inserisce la variabile passatagli in C nell' albero, ed            *
* eventualmente lo ribilancia.                			               *
* Una cosa importante e' poter distinguere tra i diversi tipi        *
* di variabile. Per fare cio' si considera il campo codicevar:       *
*				                                                         *
*  codicevar 1 -> variabile di LINK                                  *
*  codicevar 2 -> variabile di DEFINE                                *
*  codicevar 3 -> variabile di DATA                                  *
*  codicevar 4 -> variabile istr. CASE                               *
*  codicevar 5 -> variabile istr. SUBROUTINE                         *
*          							                                       *
*********************************************************************/

struct variabili *inserisci(albero,nvar,tvar,h,val,cd,sem)
struct variabili *albero;
char   nvar[];
int tvar,*h;
char val[];
int cd;
int sem;
{

int s,r;
char bufnomvar[LUNG_VAR];
struct variabili *p1,*p2;

p1=p2=testa;
if(albero==NULL)  {     /* Inserimento nuova variabile */
	*h=1;
	if((albero=(struct variabili *)malloc(sizeof(struct variabili)))==NULL) {
		curxy(22,1);
		printf(tooManyVar);
		curxy(23,1);
		printf(variable, nvar);
		printf(press);
		getc(stdin);
		exit(0);
	}

	memset(bufnomvar,0x00,LUNG_VAR);
	strcpy(bufnomvar,nvar);
	memcpy(albero->nome,bufnomvar,LUNG_VAR);


	albero->tipo=tvar;
	albero->codicevar = cd;
	if(cd> 0xF)
	{
		cd=cd & 0x000F;
		albero->indirizzo=0x8000;			// indirizzamento locale
	}
	else
		albero->indirizzo=0;
	if(sem>=16)  {
		s=((sem -1) -((sem-1) & 15))/16;
		albero->indirizzo=s+16384;
	}
	if((sem & 15)==1)  {
		itoa(cont_gruppi,val,10);
		cont_gruppi++;
	}
	if(cd==3 || cd==4 || cd==5)  {
		albero->valcost=malloc(1+strlen(val));
		strcpy(albero->valcost,val);
	}
	else
		albero->valcost=malloc(5);
	albero->nriga_input=numriga;
	albero->flag=(sem & 15);
	albero->bal=0;
	albero->left=NULL;
	albero->right=NULL;
}
else
	if((r=strcmp(nvar,albero->nome))<0)  {
		albero->left=inserisci(albero->left,nvar,tvar,h,val,cd,sem);
		if (*h)
		switch (albero->bal)  {
		case  1  :  albero->bal=0;
			    *h=0;
			    break;
		case  0  :  albero->bal=-1;
			    break;
		case -1  :  p1=albero->left;    /* bilanciamento */
			    if(p1->bal==-1)  {  /* rotazione LL  */
				albero->left=p1->right;
				p1->right=albero;
				albero->bal=0;
				albero=p1;
			    }
			    else  {             /* rotazione LR */
				p2=p1->right;
				p1->right=p2->left;
				p2->left=p1;
				albero->left=p2->right;
				p2->right=albero;
				if(p2->bal==-1)
					albero->bal=1;
				else
					albero->bal=0;
				if(p2->bal==1)
					p1->bal=-1;
				else
					p1->bal=0;
				albero=p2;
		           }
			   albero->bal=0;
 			   *h=0;
			   break;
		}
	}
	else
		if((r=strcmp(nvar,albero->nome))>0)  {
	albero->right=inserisci(albero->right,nvar,tvar,h,val,cd,sem);
			if(*h)
			switch(albero->bal)  {
			case  -1  :  albero->bal=0;
				     *h=0;
 			     break;
			case   0  :  albero->bal=1;
 			     break;
			case   1  :  p1=albero->right; /*Bilanciamento*/
				     if(p1->bal==1)  { /* Rot. RR */
					albero->right=p1->left;
					p1->left=albero;
					albero->bal=0;
					albero=p1;
 			     }
 			   	     else  {          /* Rot. RL */
					p2=p1->left;
					p1->left=p2->right;
					p2->right=p1;
					albero->right=p2->left;
					p2->left=albero;
					if(p2->bal==1)
						albero->bal=-1;
					else
						albero->bal=0;
					if(p2->bal==-1)
						p1->bal=1;
					else
						p1->bal=0;
	     			        albero=p2;
	 			     }
	 			     albero->bal=0;
				     *h=0;
				     break;
			}
		}
		else  {
			if((cd!=4) && (cd!=5))
				stampa_err(5,1,nvar);
			*h=0;
		}
return(albero);
}

/*********************************************************************
*          							                                       *
*			Procedura insDB				                                 *
*   			                         		                           *
* Determina l' indirizzo della variabile passata attraverso il suo   *
* tipo con l' ordine imposto dal chiamante. Cerca per ogni nodo se   *
* il tipo della variabile coincide col tipo passato e se appartine   *
* alla classe di variabili corretta ( LINK, DEFINE o DATA ) se si    *
* assegna all'indirizzo della struttura l'indirizzo corrente del D.B.*
* (INDDB), ed incrementa quest' ultimo a seconda del tipo e della    *
* dimensione della variabile; se no continua la ricerca fino alla    *
* fine dell' albero.						                                 *
*          							                                       *
*********************************************************************/

int*  GetIndGrp(int indice, int s, int flag);
insDB(albero,ind,s,indb)
struct variabili *albero;
int ind;
int s;
int *indb;				// indirizzo nel data base locale generale
{
int dim,i;
int *spiazz;

if(albero!=NULL)  {

	spiazz=indb;							// variabile globale
	if(ind==(albero->tipo & 15) &&
	(int)(albero->codicevar & 0x000F) == ( s + 1 ) )
	{
		if(s)				// define e data locali ?
		{
			if(albero->indirizzo & 0x8000)		// variabile locale
				spiazz=GetIndGrp((albero->codicevar & 0xFFF0) >> 4, s, albero->flag);
		}
		dim=(albero->tipo - ind) /16;
		albero->indirizzo+=*spiazz;
		if(dim==0)
			(*spiazz)+=n_byte[ind];
		else
			if(ind==5) {   /* caso logici */
				i=dim/16;
				if(dim%16!=0)
					i++;
				(*spiazz)+=2*i;
			}
			else
				for(i=0;i<dim;i++)
					(*spiazz)+=n_byte[ind];
	}
	insDB(albero->left,ind,s,indb);
	insDB(albero->right,ind,s,indb);
}
}


/*********************************************************************
*          							                                       *
*			Procedura inscostanti			                              *
*          							                                       *
*	Per ogni costante, definita cioe' con DATA, ne  cambia lo         *
* indirizzo precedentemente determinato in maniera provvisoria,      *
* sommandogli il valore ind passato alla procedura e calcolato nel   *
* main, che serve ad alloccare le costanti alla fine del DB.         *
*          							                                       *
*********************************************************************/

inscostanti(albero,ind,tipo)
struct variabili *albero;
int ind;
int tipo;
{
int dim,i;

if(albero!=NULL)  {

	if( (int)(albero->codicevar) == ( tipo ) ) {

		if(ind>=INDDB)
			albero->indirizzo+=ind;
		else
			stampa_err(1,0,"0");
	}
	inscostanti(albero->left,ind,tipo);
	inscostanti(albero->right,ind,tipo);
}
}

/*********************************************************************
*                                                                    *
*			Procedura cost			                                       *
*          							                                       *
* La procedura viene chiamata per inserire nell' albero delle        *
* variabili anche le costanti definite con l' apposita istruzione    *
* DATA. Essa cerca in linea_cor la parola chiave DATA, e finche' non *
* trova una riga in cui non e' presente, cerca il tipo, il nome e    *
* il valore di ogni costante presente nella riga e la inserisce nell'*
* albero. Per ogni costante controlla che il tipo sia tra quelli     *
* ammissibili, che la costante non sia gia' stata definita ( sia con *
* DATA che con DEFINE ) e che il valore sia corretto. Per le stringhe*
* inserisce col solito modo anche la dimensione nel campo "tipo".    *
*          							                                       *
*********************************************************************/

cost()

{

char t[7],prov[3],nomevar[LUNG_VAR+1],valore[81];
int n,ok,valint,vallog,i,M,nuovariga,indice=-1;
int savindice,vir,prec,esponente,punto;
char deflocal[100];
short cd;

while(1) {
	 cd=0;
 	 if(!strncmp(linea_cor,"LDATA",5))			// variabile di tipo DEFINE LOCALE
	 {
		sscanf(linea_cor,"%s",deflocal);
		deflocal[5]='Š';
		cd=decgrp(&deflocal[5]) << 4;
		strcpy(linea_cor,"DATA");
		strcat(linea_cor,&linea_cor[strlen(deflocal)]);
	 }
	 else deflocal[0]=0;

	 for(i=0;i<7 && linea_cor[i]>=0x41 && linea_cor[i]<=0x5a;i++)
			t[i]=linea_cor[i];
	 t[i]='\0';
 	 if((strcmp(t,"DATA"))!=0)
		return(1);
	indice=dammitipo(prov,5);
	if(!(indice==3 || indice==4 || indice==5 || indice==7 ||	indice==9 || 
	     indice==10 || indice==11 || indice==12 || indice == 14 || indice==15))
		stampa_err(2,1,prov); /* tipo costante non ammesso */
	else {
		if(!(linea_cor[7]==APTONDA || linea_cor[8]==APTONDA))
			stampa_err(6,0,"0");
		else {
			for(M=7;linea_cor[M]==APTONDA ||
				linea_cor[M]==BLANK; M++)
					;
			nuovariga=0;
			while(nuovariga==0) {
				ok=damminomi(nomevar,valore,&nuovariga,&M);
				if( (ok==1) && ( tstnomvar(nomevar)==1 ) )
				if(deflocal[0])
				{
					strcat(nomevar,&deflocal[5]);
				}
				switch(indice) {
				case 3 :  /* reali */
					if((ok=isreale(valore))==1)
						testa=inserisci(testa,nomevar,indice,&hh,valore,cd+3,0);
					else
/* la costante reale non */
/* e' inizializzata bene */			stampa_err(7,1,nomevar);
				break;
				case 4 : /* interi */
					if((ok=isintero(valore))==1) {
						valint=atoi(valore);
						testa=inserisci(testa,nomevar,indice,&hh,valore,cd+3,0);
					}
					else
/* la costante intera non */
/* e' inizializzata bene  */			stampa_err(7,1,nomevar);
					break;
	 	 		case 5 : /* logici */
		if((valore[0]==0x30 || valore[0]==0x31) && valore[1]==0x00)
				testa=inserisci(testa,nomevar,indice,&hh,valore,cd+3,0);
			else
				 /* errata inizializzazione */
				stampa_err(7,1,nomevar);
			break;
				case 7 : /* stringhe */
				if((ok=isstringa(valore,nomevar,&i))==1) {
					valore[i]=0x00;
					for(i=0;valore[i]!=0x00;i++)
						valore[i]=valore[i+1];
					savindice=indice;
					indice=indice+16*i;
					testa=inserisci(testa,nomevar,indice,&hh,valore,cd+3,0);
					indice=savindice;
					if(linea_cor[M]==BLANK)
						M++;
					if(linea_cor[M]==VIRGOLA)
						;
					else
						if(linea_cor[M]==CHTONDA)
							nuovariga=1;
						else {
							nuovariga=1;
/* la costante e' definita, manca il sep.*/	stampa_err(7,1,nomevar);
						}
				}
				break;
				case  9 :									/* puntatori*/
				case 10 :
				case 11 :
				case 12 :
				case 14 :
				case 15 :
					for(i=0;valore[i]!=0x00;i++)
						if(valore[i]==0x00)
							break;
					if(i<=10)
						testa=inserisci(testa,nomevar,indice,&hh,valore,cd+3,0);
					else
/* var. di DBS troppo lunga */			stampa_err(7,1,valore);
				break;
				} /* chiudo lo switch */
				M++;
				if(linea_cor[M]==BLANK)
					M++;
			} /* chiudo while interno */
		} /* chiudo else di stampa_err(6,0,"0") */
	}  /* chiudo else di stampa_err(2,1,prov) */
	while((n=new_lico())==0)
		;
	if(n==-1)
		return(-1);
}  /* fine while esterno */
}  /* fine procedura */

/*********************************************************************
*          							                                       *
*			Procedura letturadb			                                 *
*          							                                       *
*	La procedura viene chiamata per risolvere le istruzioni di        *
* LINK incontrate nella fase di definizione. Essa considera una riga *
* alla volta finche' non ne trova una in cui non vi e' LINK. Per ogni*
* riga legge il tipo della variabile e lo controlla, legge il nome   *
* della variabile nel DBL e controlla che ci sia e che sia del tipo  *
* specificato, legge il nome della variabile di DBS e la inserisce   *
* nell' albero con la procedura cercaread.  			                  *
*          							                                       *
*********************************************************************/

letturadb()
{
char t[7],prov[3],nomevar[LUNG_VAR+1],valore[81];
int ok,i,M,n,indice,nuovariga;

while(1) {
	 for(i=0;i<7 && linea_cor[i]>=0x41 && linea_cor[i]<=0x5a;i++)
			t[i]=linea_cor[i];
	 t[i]='\0';
 	 if((strcmp(t,"LINK"))!=0)
		return(1);

	 indice = ctrtpgen(2,prov,5,NUM_TIPLK,tipistlk);  /* leggo il tipo */

	if( indice==-1 )

		stampa_err(2,1,prov); /* tipo non ammesso */

	else {

		/* Tipo di istruzione LINK ammessa */

		if(!(linea_cor[7]==APTONDA || linea_cor[8]==APTONDA))
			stampa_err(6,0,"0");
		else {
			for(M=7;linea_cor[M]==APTONDA ||
				linea_cor[M]==BLANK; M++)
					;
			nuovariga=0;
			while(nuovariga==0) {
				ok=damminomi(nomevar,valore,&nuovariga,&M);
				if(ok==1) {
					n=cercaread(testa,nomevar,valore,indice);
					if(n==-1 || n==-2) {
						if (n==-1)
/* variabile non definita o di tipo errato */		stampa_err(4,1,nomevar);
						else
/* variabile definita come costante  */			stampa_err(9,1,nomevar);
					}
				}
				M++;
				if(linea_cor[M]==BLANK)
					M++;
			} /* chiudo while interno */
		} /* chiudo else di stampa_err(6,0,"0") */
	} /* chiudo else di stampa_err(2,1,prov) */
	while((n=new_lico())==0)
		;
	if(n==-1)
		return(-1);
} /* fine while esterno */
}

/*********************************************************************
*          							     *
*			Procedura cercaread 			     *
*          							     *
*	La procedura cerca nell' albero la variabile specificata da  *
* nomev e del tipo indicato da indice, se la trova scrive nel campo  *
* valcost dell' albero il contenuto di valore ( rappresenta la var.  *
* di DBS da cui leggere il valore ), altrimenti rende -1 se non la   *
* trova (puo' anche esserci ma essere di tipo diverso da quello      *
* specificato) oppure -2 se e' gia' definita come DATA.		     *
*          							     *
*********************************************************************/

cercaread(albero,nomev,valv,indice)
struct variabili *albero;
char nomev[],valv[];
int indice;
{
int n;
if(albero==NULL)
	return(-1);
if((strcmp(nomev,albero->nome))==0) {
	n=albero->tipo & 15;
	if( n == tipvarlk[indice] ) {
		if( albero->codicevar != 2 ) 
			return(-2);

		albero->codicevar = 1;
		albero->codicelk  = codistlk[indice];

		if((albero->valcost=realloc(albero->valcost,35))==NULL)  {
			curxy(22,1);
			printf(tooManyVar);
			curxy(23,1);
			printf(varLink, albero->nome);
			printf(press);
			getc(stdin);
			exit(0);
		}
		strcpy(albero->valcost,valv);
		return(n);
	}
	else
		return(-2);
}
else
	if((strcmp(nomev,albero->nome))<0)
		n=cercaread(albero->left,nomev,valv,indice);
	else
		n=cercaread(albero->right,nomev,valv,indice);
}


/*********************************************************************
*          							                                       *
*			Procedura dammitipo			                                 *
* La procedura legge da linea_cor il tipo di una variabile o         *
* costante, lo confronta con i tipi possibili e, se lo trova rende   *
* il numero relativo, altrimenti -1.				                     *
*          							                                       *
*********************************************************************/

dammitipo(prov,s)

char prov[];  /* vettore caricato con i caratteri di tipo variabile  */
int s;		  /* indice in linea_cor di inizio dei caratteri di tipo */

{

int i,indice;

prov[0]=linea_cor[s++];   /* Carico primo carattere */
prov[1]=linea_cor[s++];   /* carico secondo carattere */
prov[2]=0x00;

if(!(linea_cor[s]==BLANK || linea_cor[s]==APTONDA))
	prov[1]='\0';

indice=-1;

for(i=0;i<NUM_TIPVAR;i++)
	if((strcmp(prov,tipovar[i]))==0) {
		indice=i;   /* tipo trovato */
		break;
	}

return(indice);

}


/*********************************************************************
*          							     *
*			Procedura damminomi			     *
*          							     *
* 	La procedura legge da linea_cor il nome di una variabile o   *
* costante (caratteri di fine stringa sono ":"," ", fine riga o il   *
* raggiungimento di otto lettere) e lo mette in nomev, il valore     *
* stessa variabile e lo mette in valv controllando che non ci siano  *
* errori di sintassi.						     *
*          							     *
*********************************************************************/

damminomi(nomev,valv,nuovariga,M)
char nomev[],valv[];
int *nuovariga,*M;
{
int i,ok=1,vir;
for(i=0;linea_cor[*M]!=BLANK &&
linea_cor[*M]!=DUE_PUNTI && 
linea_cor[*M]!=0x00 && i<(EF_LUNGVAR-1);(*M)++)
		nomev[i++]=linea_cor[*M];
nomev[i]=0x00;
if(strrchr(nomev,'.')) stampa_err (58,1,nomev);
if(linea_cor[*M]==0x00) {
	ok=0;
	*nuovariga=1;
	stampa_err(6,0,"0");
}
else {
	while(linea_cor[*M]!=DUE_PUNTI && linea_cor[*M]!=0x00)
	{
		stampa_err(6,0,"0");		// nome variabile troppo lunga
		*nuovariga=1;
		return(0);
	 	(*M)++;
	}
	if(linea_cor[*M]==0x00) {
		ok=0;
		stampa_err(6,0,"0");
		*nuovariga=1;
	}
	else {
		(*M)++;
		if(linea_cor[*M]==BLANK)
			(*M)++;
		vir=0;
		for(i=0; linea_cor[*M]!=0x00 && i<80 &&
		((vir==0 && (linea_cor[*M]!=VIRGOLA &&
		linea_cor[*M]!=BLANK && linea_cor[*M]!=CHTONDA)) ||
		(vir==1 && linea_cor[*M]!=VIRGOLETTE));(*M)++) {
			if(linea_cor[*M]==VIRGOLETTE)
				vir=1;
			valv[i++]=linea_cor[*M];
		}
		if(linea_cor[*M]==BLANK)
		 	(*M)++;
		if(vir==1 && linea_cor[*M]==VIRGOLETTE)  {
			valv[i++]=VIRGOLETTE;
			(*M)++;
			if(linea_cor[*M]==BLANK)
			 	(*M)++;
		}
		valv[i]=0x00;
		if(linea_cor[*M]==CHTONDA)
			*nuovariga=1;
		if(linea_cor[*M]==0x00) {
			ok=0;
			stampa_err(6,0,"0");
			*nuovariga=1;
		}
		if(linea_cor[*M]!=VIRGOLA && (*nuovariga)!=1) {
			ok=0;
			stampa_err(6,0,"0"); /* non trovo la virgola e non e' */
		}
	} /* chiudo else di stampa_err(7,0,"0") */
} /* chiudo else di stampa_err(7,0,"0") */
return(ok);
}

