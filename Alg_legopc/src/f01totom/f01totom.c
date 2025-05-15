/*
 * F01TOTOM - Conversione dei file F01 in TOM
	uso:		f01totom							--> viene letto il file f01,dat
				f01totom -a						    --> viene letto il file f01,dat in modo non  interattivo ( deve esistere f01totom.inp)
				f01totom <file di tipo f01>			--> viene letto il file in input
				f01totom -a <file di tipo f01>		--> viene letto il file in input in modo non  interattivo ( deve esistere f01totom.inp)

 * Il programma legge un file f01.dat e lo traduce nel formato topologico "tom"
 * di LegoPC. Durante la fase di conversione interattivamente � richiesta la scelta di istanze di moduli Lego
 * che ammettono configurazioni diverse. La scelta � salvata in un file "f01totom.inp" che viene
 * riletto nei successivi run del programma e che pu� essere eventualmente modificato 
 * in maniera non interettiva per scegliere altre impostazioni.
 * Durante la fase interattiva di richiesta della configurazione del blocco da utilizzare,
 * se si inposta '-a' viene utilizzato il file f01totom.inp
 * 
	input:	f01.dat
			f01totom.inp
			macroblocks.dat

	output	f01totom.tom
			f01totom.inp

 */
#include <stdlib.h>

#include <stdio.h>
//#include <windows.h>
#include "f01totom.h"
#include <malloc.h>
#include <glob.h>
#include <string.h>
#include <libgen.h>
#include <ctype.h>

int leggi_i5(char *,HEADF01 *, int);
void scrivi_tom(HEADF01 *);
void conv_minuscolo( char *, char *);
void cercai5(HEADF01 *,int, char *);
int  nomi_defi5(int,HEADF01 *);
int  leggi_macroblocks(HEADF01 *);

int	pos_automatiche=0;


// WIN32_FIND_DATA lpFindFileData[1];

char filei5scelto[MAXL];
char filf01totom[MAXL];

int alldef=0 , nodefile=0;


void essit(char *mesg)

{
  printf(mesg);
  exit(-1);
}


int main( int argc, char *argv[ ] )
{
	FILE	*fpf01;
	int		i, curblo, ik, ii, iii, okconn, okconnusc, noing, nousc, kk, trovato;

          glob_t lpFindFileData;


	HEADF01  *f01r;
    char bloconn0[5],bloconn1[5];
	char buff[MAXL],filf01[MAXL];
    char *I5PATH, *LIBRPATH;
	int retfind;
	char lpFileName[100];
	
	char *nomelibr[MAXBLO];
	int numlibr, modtrovato,non_presenti, lista_non_presenti[MAXBLO];
	int remblo;
	int ret, ferma, lunbuff;


	f01r=(HEADF01 *)malloc(sizeof(HEADF01));

	strcpy(filf01,"f01.dat");
	strcpy(filf01totom,"f01totom.tom");
/*
	if ((argc == 2) && (strcmp(argv[1],"-h")!= 0) ) {
	essit("Uso:	f01totom [-a] <nome file input (f01.dat)>\nOppure	f01totom [-a] <nome file input (f01.dat)> <nome file input (f01totom.tom)>\nOppure	f01totom [-a]\n");
	}
*/
	if (argc == 2) {
		if(strcmp(argv[1],"-a")== 0) {alldef=1;}
		else if (strcmp(argv[1],"-h")== 0) essit("Uso:	f01totom [-a] <nome file input (f01.dat)>\nOppure	f01totom [-a] <nome file input (f01.dat)> <nome file input (f01totom.tom)>\nOppure	f01totom [-a]\n");
		else strcpy(filf01,argv[1]);
	}
	if (argc == 3) {
		if(strcmp(argv[1],"-a")== 0) {alldef=1; strcpy(filf01,argv[2]);}
		else {strcpy(filf01,argv[1]);strcpy(filf01totom,argv[2]);}
	}

	if (argc == 4) {
		if(strcmp(argv[1],"-a")== 0) {alldef=1; strcpy(filf01,argv[2]);strcpy(filf01totom,argv[3]); }
		else {essit("Uso:	f01totom [-a] <nome file input (f01.dat)>\nOppure	f01totom [-a] <nome file input (f01.dat)> <nome file input (f01totom.tom)>\nOppure	f01totom [-a]\n");}
	}

	if (argc > 4) essit("Uso:	f01totom [-a] <nome file input (f01.dat)>\nOppure	f01totom [-a] <nome file input (f01.dat)> <nome file input (f01totom.tom)>\nOppure	f01totom [-a]\n");


	if((fpf01=fopen(filf01,"r"))==NULL) {
// il file non esiste errore
			essit("f01totom - ERR1-Impossibile aprire il file f01.dat\n");
//	AfxMessageBox("Impossibile creare il file snapshotBIN.dat");
	}

/* */
/* Lettura del file f01.dat e caricamento della struttura f01r */
/* */
printf( "\n-------------------------------\nFASE 1 - Lettura del file f01.dat\n-------------------------------\n");
    curblo=0;
	fgets(buff,MAXL,fpf01);  // ****
	fgets(buff,MAXL,fpf01);
    while (strncmp(buff, "****",4) != 0) {

		f01r->totblo=curblo+1;
		strncpy(f01r->nomemod[curblo],buff,4);
		f01r->nomemod[curblo][4]='\0';
		strncpy(f01r->nomeblo[curblo],buff+18,4);
		f01r->nomeblo[curblo][4]='\0';
		strcpy(f01r->descrblo[curblo],buff+33);

        fgets(buff,MAXL,fpf01);
		curblo=curblo+1;
	}
	fgets(f01r->nomemodello,9,fpf01);
// leggo i blocchi
	fgets(buff,MAXL,fpf01);  // ****
	fgets(buff,MAXL,fpf01);


for (curblo=0;curblo<f01r->totblo;curblo++) {
    if (( f01r->blo[curblo]=(BLOF01 *)malloc(sizeof(BLOF01))) == NULL)
		essit("f01totom - malloc failed in f01r->blo allocation\n");


	fgets(buff,MAXL,fpf01);

	strcpy(f01r->blo[curblo]->firstline,buff);

	fgets(buff,MAXL,fpf01);
	i=0;
    while (strncmp(buff, "****",4) != 0) {
		if ( buff[17] == '#'){
			strncpy(f01r->blo[curblo]->varblo[i],buff+18,4);
			f01r->blo[curblo]->varblo[i][4]='\0';

			f01r->blo[curblo]->tipo[i]=CO;

			strncpy(f01r->blo[curblo]->varconn[i],buff,4);
			f01r->blo[curblo]->varconn[i][4]='\0';

			strncpy(f01r->blo[curblo]->bloconn[i],buff+4,4);
			f01r->blo[curblo]->bloconn[i][4]='\0';

			strncpy(f01r->blo[curblo]->modconn[i],buff+51,4);
			f01r->blo[curblo]->modconn[i][4]='\0';

		}
		else if ( buff[13] == 'S'){  // variabile tipo US
			strncpy(f01r->blo[curblo]->varblo[i],buff,4);
			f01r->blo[curblo]->varblo[i][4]='\0';

			f01r->blo[curblo]->tipo[i]=US;
		}
		else if ( buff[13] == 'A'){  // variabile tipo UA
			strncpy(f01r->blo[curblo]->varblo[i],buff,4);
			f01r->blo[curblo]->varblo[i][4]='\0';

			f01r->blo[curblo]->tipo[i]=UA;
		}
		else if ( buff[13] == 'N'){  // variabile tipo IN
			strncpy(f01r->blo[curblo]->varblo[i],buff,4);
			f01r->blo[curblo]->varblo[i][4]='\0';

			f01r->blo[curblo]->tipo[i]=ING;
		}
	fgets(buff,MAXL,fpf01);
	i++;
	}
	f01r->blo[curblo]->numvar=i;

	fgets(buff,MAXL,fpf01);  // **** ed eventualmente >>>>
	fgets(buff,MAXL,fpf01);

}
	fclose(fpf01);

//stampe di prova
	for (i=0;i<f01r->totblo;i++)
		printf("%s-%s-%s\n",f01r->nomemod[i], f01r->nomeblo[i],f01r->descrblo[i]);
// fine stampe di prova
	pos_automatiche=0;
    if (leggi_macroblocks(f01r) == 0) pos_automatiche=1;
/* */
/* Ricerca delle librerie dei moduli di Legopc installate */
/* */
printf( "\n-------------------------------\nFASE 2 - Ricerca delle istanze esistenti\n-------------------------------\n");
	LIBRPATH = (char *)getenv("LG_LIBRARIES");

	I5PATH = (char *)getenv("LG_FILESI5");

	strcpy(lpFileName,"");
	strcat(lpFileName,LIBRPATH);
//	strcat(lpFileName,"\\*");
	strcat(lpFileName,"/*");

          lpFindFileData.gl_offs = 0;
          retfind=glob(lpFileName, GLOB_DOOFFS, NULL, &lpFindFileData);

//	retfind= FindFirstFile(  lpFileName,lpFindFileData); // pointer to name of file to search for
	numlibr=( int)lpFindFileData.gl_pathc;
	for (i=0; i<numlibr; i++){
		nomelibr[i]= (char *)malloc(strlen(lpFindFileData.gl_pathv[i]));
		strcpy(nomelibr[i],basename( lpFindFileData.gl_pathv[i]));
		printf("-----%s\n",nomelibr[i]);
        }

/*	while ( FindNextFile( retfind,lpFindFileData) )
		if(strcmp(lpFindFileData->cFileName,"..") ) {
			numlibr++;
			nomelibr[numlibr-1]= (char *)malloc(strlen(lpFindFileData->cFileName));
			strcpy(nomelibr[numlibr-1],lpFindFileData->cFileName);
			printf("-----%s\n",lpFindFileData->cFileName);
		}
*/

// cerco la libreria di appartenenza del modulo
	non_presenti=0;
	for (curblo=0;curblo<f01r->totblo;curblo ++){
		modtrovato=0;
		for (i=0;i<numlibr;i++) {
		strcpy(lpFileName,LIBRPATH);
			strcat(lpFileName,"/");
			strcat(lpFileName,nomelibr[i]);
			strcat(lpFileName,"/");
			conv_minuscolo(f01r->nomemod[curblo],buff);
			strcat(lpFileName, buff);
			strcat(lpFileName,"*.*");
          retfind=glob(lpFileName, GLOB_DOOFFS, NULL, &lpFindFileData);

			if( retfind == 0 ) {// modulo trovato
				printf("Ok---> %s nella libreria %s\n",f01r->nomemod[curblo],nomelibr[i]);
				strcpy(f01r->nomelibr[curblo],nomelibr[i]);
				modtrovato=1;
				break;
			}

		}
		if( modtrovato == 0) {
			lista_non_presenti[non_presenti]=curblo;
			non_presenti++;
			printf("NON Trovato!---> %s %s\n",lpFileName,f01r->nomemod[curblo]);

		}
	}
	if(non_presenti >0){
			printf("\n\n\n");
			for(i=0; i< non_presenti; i++) {
				ii=lista_non_presenti[i];
				printf("f01totom - Modulo: %s non presente in libreria - blocco %s\n",f01r->nomemod[ii],f01r->nomeblo[ii]);
			}
			essit("Fine del programma\n");
	}

/* */
/* Ricerca dei file i5 delle librerie */
/* */
printf( "\n-------------------------------\nFASE 3 - Ricerca nei file i5 e scelta delle istanze\n-------------------------------\n");

//  eventuale lettura ( se esistente) del file f01totom.inp dei defaults i5 e caricamentoi nella struttura f01r
		if( nomi_defi5(LEGGI, f01r) == 0) nodefile=1;
		ferma=0;
// ricerca dei file i5
		for (curblo=0;curblo<f01r->totblo;curblo ++) {
			strcpy(lpFileName,I5PATH);
			strcat(lpFileName,"/");
			conv_minuscolo(f01r->nomemod[curblo], buff);

			cercai5(f01r,curblo,lpFileName);
			strcat(lpFileName,filei5scelto);
			strcpy(f01r->nomei5[curblo],filei5scelto);
			ret=leggi_i5(lpFileName,f01r, curblo);
// provvisorio ... ignoro gli errori in lettura degli i5
//			if(ret==1) ferma=1;

// Ricerca della libreria che contiene l'istanza del modulo scelto (le istanze possono essere messe in libreie diverse un es. e il modulo nodo
		        for (i=0;i<numlibr;i++) {
		           strcpy(lpFileName,LIBRPATH);
			   strcat(lpFileName,"/");
			   strcat(lpFileName,nomelibr[i]);
			   strcat(lpFileName,"/");
			   conv_minuscolo(filei5scelto,buff);
			   lunbuff=(int)strlen(buff);
			   buff[lunbuff-3]='\0';
			   strcat(buff,"*");

			   strcat(lpFileName, buff);
//			   strcat(lpFileName,"*.*");
//	printf("Ilfilei5 da cercare � %s \n",lpFileName);

			   retfind=glob(lpFileName, GLOB_DOOFFS, NULL, &lpFindFileData);

			   if( retfind == 0 ) {// modulo trovato
	printf("Ilfilei5 scelto %s � nella libreria %s\n",f01r->nomei5[curblo],nomelibr[i]);
				strcpy(f01r->nomelibr[curblo],nomelibr[i]);
				modtrovato=1;
				break;
			   }

			}

		}
// salvo i nomi di default degli i5
		nomi_defi5(SCRIVI, f01r);
		if(ferma==1) essit ("f01totom fermo per errori\n");
/* */
/* Ricerca delle connessioni tra i blocchi */
/* */
printf( "\n-------------------------------\nFASE 4 - Ricerca connessioni tra i blocchi\n-------------------------------\n");

		for (curblo=0;curblo<f01r->totblo;curblo++) {  // per ogni blocco ...

			for (i=0; i< f01r->porte[curblo]->numporte; i++){// per ogni porta
				strcpy(bloconn0,"____");
				strcpy(bloconn1,"");

				okconn=-1;
				noing=1;
				for ( ik=0; ik< f01r->porte[curblo]->porta[i]->num; ik++) { // per ogni var della porta

					if( (f01r->porte[curblo]->porta[i]->tipo[ik] == ING ) ||
					    (f01r->porte[curblo]->porta[i]->tipo[ik] == CO))	{ // e' un ingresso
						noing=0;
						okconn=0;
						for ( ii=0; ii< f01r->blo[curblo]->numvar; ii++){ // per ogni variabile del blocco corrente
							if( strcmp(f01r->blo[curblo]->varblo[ii], f01r->porte[curblo]->porta[i]->nome[ik]) == 0) {
								if( f01r->blo[curblo]->tipo[ii] == CO) {
									okconn=1;
									strcpy(bloconn1,f01r->blo[curblo]->bloconn[ii]);
									break;
								} else {
									okconn=0;
									goto esci;
								}
							}

						}
						if (okconn == -1) essit ("f01totom - ERR2-f01ttom - variabile della porta non trovata");
						if (strcmp(bloconn0,"____") == 0)   strcpy(bloconn0,bloconn1);

						if (strcmp(bloconn1,bloconn0) == 0) {
							okconn=1;
							break;
//							continue;
						}
						else {
							okconn=0;
							goto esci;
						}

					}

				}
                okconnusc=-1;
				nousc=1;
				if (noing != 1) strcpy(bloconn0,bloconn1);
//				if( okconn== 1 )
				for ( ik=0; ik< f01r->porte[curblo]->porta[i]->num; ik++) { // per ogni var della porta

					if((f01r->porte[curblo]->porta[i]->tipo[ik] == US) ||
							(f01r->porte[curblo]->porta[i]->tipo[ik] == UA)) {  // � un uscita
						nousc=0;
						okconnusc=0;
						for (remblo=0;remblo<f01r->totblo;remblo++) {
							if( remblo == curblo) continue;
							for (iii=0;iii<f01r->blo[remblo]->numvar;iii++) { // per ogni variabile del blocco remoto
								if( (strcmp(f01r->blo[remblo]->varconn[iii], f01r->porte[curblo]->porta[i]->nome[ik]) == 0) &&
									(strcmp(f01r->blo[remblo]->bloconn[iii], f01r->nomeblo[curblo]) == 0) ) {
									strcpy(bloconn1,f01r->nomeblo[remblo]);
									if (strcmp(bloconn0,"____") == 0)   strcpy(bloconn0,bloconn1);
									break;

								}
							}

							if (strcmp(bloconn1,bloconn0) == 0) {
								okconnusc=1;
								break;
							}

						}
						if (okconnusc==1 ) continue;
						if ( noing != 1) goto esci;
					}
				}
		esci:   strcpy(f01r->porte[curblo]->porta[i]->bloconn,"____"); // porta free
				f01r->porte[curblo]->porta[i]->ibloconn=-1;
				if(((nousc == 1) && ( okconn == 1)) ||
				   ((noing == 1) && ( okconnusc == 1)) ||
				   ((okconn == 1) && ( okconnusc==1)) )	{
						strcpy(f01r->porte[curblo]->porta[i]->bloconn,bloconn1);
						for (remblo=0;remblo<f01r->totblo;remblo++) {
							if (strncmp( f01r->nomeblo[remblo], bloconn1, 4) == 0) {
								f01r->porte[curblo]->porta[i]->ibloconn=remblo;
								break;
							}
						}
				}

		}

	}

// cerco i nomi delle porte del blocco connesso con un'altro ...
		for (curblo=0;curblo<f01r->totblo;curblo++) {  // per ogni blocco ...
			for (i=0; i< f01r->porte[curblo]->numporte; i++){// per ogni porta
				remblo=f01r->porte[curblo]->porta[i]->ibloconn; // blocco connesso alla porta i del blocoo curblo
				if (remblo<0) continue;
				for (kk=0;kk<f01r->porte[remblo]->numporte; kk++) { // per ogni porta del blocco remoto
					if( f01r->porte[remblo]->porta[kk]->okport == 1) continue;
					if( strcmp(f01r->porte[remblo]->porta[kk]->bloconn,f01r->nomeblo[curblo]) == 0) { // trovato

						trovato=-1;
						ik=0;
						if((f01r->porte[curblo]->porta[i]->tipo[ik] == US) ||
							(f01r->porte[curblo]->porta[i]->tipo[ik] == UA)) {  // � un uscita
							for (iii=0;iii<f01r->blo[remblo]->numvar;iii++) { // per ogni variabile del blocco remoto
								if( strcmp(f01r->blo[remblo]->varconn[iii],f01r->porte[curblo]->porta[i]->nome[ik]) == 0) {
									break; // trovato: la variabile � iii
								}
							}

							for ( ii=0;ii<f01r->porte[remblo]->porta[kk]->num; ii++) { // per ogni var della porta remota
								if( strcmp(f01r->porte[remblo]->porta[kk]->nome[ii],f01r->blo[remblo]->varblo[iii]) == 0) {
									trovato=kk;
									break; // trovato: la porta � kk
								}
							}

						}
						ik=0;
						if((f01r->porte[curblo]->porta[i]->tipo[ik] == ING) ||
							(f01r->porte[curblo]->porta[i]->tipo[ik] == CO)) {  // � un uscita

							for (iii=0;iii<f01r->blo[curblo]->numvar; iii++) { // per ogni variabile del blocco corrente
								if( strcmp(f01r->blo[curblo]->varconn[iii],f01r->porte[remblo]->porta[kk]->nome[ik]) == 0) {
									break; // trovato: la variabile � iii
								}
							}

							for ( ii=0;ii<f01r->porte[remblo]->porta[kk]->num; ii++) { // per ogni var della porta remota
								if( strcmp(f01r->porte[remblo]->porta[kk]->nome[ii],f01r->blo[curblo]->varblo[iii]) == 0) {
									trovato=kk;
									break; // trovato: la porta � kk
								}
							}

						}

						trovato=kk;
						if(trovato != -1) strcpy(f01r->porte[curblo]->porta[i]->idbloconn,f01r->porte[remblo]->idporta[trovato]);
						f01r->porte[remblo]->porta[trovato]->okport=1;
						break;


					}
				}
			}
		}


/* */
/* scrittura del file tom */
/* */
printf( "\n-------------------------------\nFASE 5 - Scrittura del file tom\n-------------------------------\n");

	scrivi_tom(f01r);

// fine
	printf( "\n\n-->f01totom terminato, Il file tom � %s\n", filf01totom);

//free della memoria allocata
	free(f01r);
	return(0);
}


int leggi_i5(char *lpFileName,HEADF01 *f01r, int curblo)
{
/* */
/* Lettura del file i5 in esame e caricamento dei dati in f01r */
/* */

	FILE*fpi5;
	char buff[MAXL];
	int i,ii,  numporte,numconf, ik;
	char seps[]   = " ,\t\n";
	char *token;

	int trovato, ferma, dimporte;

	if((fpi5=fopen(lpFileName,"r"))==NULL) {
	// il file non esiste errore
		    printf("lpFileName = %s\n",lpFileName);
			essit("f01totom - Impossibile aprire il file i5\n");
	}
	fgets(buff,MAXL,fpi5);  // nome modulo
	fgets(buff,MAXL,fpi5);  // blank
	fgets(buff,MAXL,fpi5);  // nome modulo + descr
//        dimporte=sizeof(PORTA)*MAXPORTE+sizeof(PORTE);
        dimporte=sizeof(PORTE);

	f01r->porte[curblo]=( PORTE *)(malloc( dimporte));

	fgets(buff,MAXL,fpi5);  // numero porte
		sscanf(buff,"%d",&numporte);
		f01r->porte[curblo]->numporte=numporte;


	fgets(buff,MAXL,fpi5);  // numero configurazioni
		sscanf(buff,"%d",&numconf);
	fgets(buff,MAXL,fpi5);  // blank
    for (i=0;i<numporte;i++) {
		fgets(buff,MAXL,fpi5);   // id della porta
		while (buff[0] != 't') fgets(buff,MAXL,fpi5);
		sscanf(buff,"%s",f01r->porte[curblo]->idporta[i]);
		fgets(buff,MAXL,fpi5); // nomi delle variabili della porta
//printf( "idporta[%d]=%s buff=%s\n", i,f01r->porte[curblo]->idporta[i], buff );

		ik=0;
//		f01r->porte[curblo]->porta[i]=( PORTA *)(malloc(sizeof(PORTA)));
		f01r->porte[curblo]->porta[i]=( PORTA *)(malloc(sizeof(PORTA)+1));
		token = strtok( buff, seps ); /* Establish string and get the first token: */
		while( token != NULL )
		{
			if( (strcmp(token, "____") ==0) || (strcmp(token, "XXXX")==0)) {
				token = strtok( NULL, seps );/* Get next token: */
			} else {
//printf( "token %d- %s\n", ik, token);
				strcpy(	f01r->porte[curblo]->porta[i]->nome[ik],token);
				ik++;
				token = strtok( NULL, seps );/* Get next token: */
			}

		}
		f01r->porte[curblo]->porta[i]->num=ik;
//printf( "numero %d\n", ik, f01r->porte[curblo]->porta[i]->num);
		fgets(buff,MAXL,fpi5); // tipo delle variabili della porta


	}
ferma=0;
    for (i=0;i<numporte;i++) {
		for (ik=0;ik<f01r->porte[curblo]->porta[i]->num;ik++) {
			trovato=0;
			for (ii=0;ii<f01r->blo[curblo]->numvar;ii++) {
				if (strncmp(f01r->porte[curblo]->porta[i]->nome[ik],f01r->blo[curblo]->varblo[ii],4) == 0) { // trovato
					trovato=1;
					break;
				}
			}
			if(trovato==0) {
				printf(
					"f01totom - ERR3-f01totom - attenzione variabile della porta %s in i5 diversa da variabile del blocco %s \n",
					f01r->porte[curblo]->porta[i]->nome[ik],
					f01r->nomeblo[curblo]);
				ferma=1;
//				essit( buff );

			}
			f01r->porte[curblo]->porta[i]->tipo[ik]=f01r->blo[curblo]->tipo[ii];
		}
	}
//if(ferma ==1 ) return(1);
return( ferma );
}


void scrivi_tom(HEADF01 *f01r)
{
	FILE *fptom;
	char buff[100];
	int curblo, i;
	int posx=0,posy=100,step=100,dimx=1200, dimy=800;

	if((fptom=fopen(filf01totom,"w"))==NULL) {
		essit( "f01totom - Errore nella creazione dle file tom\n");
	}

	fputs("# this file created with LEGOPHI rel. 0.2\n", fptom);
	if( pos_automatiche==1) {
			sprintf(buff,"%d %d\n",dimx,dimy); // dimensioni tavolozza
			fputs(buff, fptom);
		} else {
			sprintf(buff,"%d %d\n",dimx,dimy + dimy*(f01r->totpag-1)); // dimensioni tavolozza
			fputs(buff, fptom);

		}

// lettura del file macroblocks se c'�
	pos_automatiche=0;
	if (leggi_macroblocks(f01r) == 0) pos_automatiche=1;

// scrittura prima parte del file
	for (curblo=0;curblo<f01r->totblo;curblo++) {  // per ogni blocco ...
		strcpy(buff,f01r->nomei5[curblo]);
		buff[6]='\0';
		fputs(buff, fptom);
		fputs("\n", fptom);
		fputs("n\n", fptom);
		fputs(f01r->nomeblo[curblo], fptom);
		fputs("\n", fptom);
// calcolo posizione delle icone
		if( pos_automatiche==1) { // le icone vengono posizionate una in fila all'altra
			posx=posx+step;
			if(posx>=dimx)		posx=step, posy=posy+step;
			if(posy>=dimy-step) posy=dimy-step;
		} else {	// le icone vengono posizionate in base alla posizione nell'eventuale file macroblocks
			posx=f01r->blo[curblo]->posx;
			posy=f01r->blo[curblo]->posy + dimy*(f01r->blo[curblo]->pag-1);
		}

		sprintf(buff,"%d%s %d%s\n",posx, ".0", posy, ".0");
		fputs(buff, fptom);
		
		fputs(f01r->nomelibr[curblo], fptom);
		fputs("\n", fptom);	
	}
	fputs("****\n", fptom);

// scrittura seconda parte del file
	for (curblo=0;curblo<f01r->totblo;curblo++) {  // per ogni blocco ...
		strcpy(buff,f01r->nomei5[curblo]);
		buff[6]='\0';
		fputs(buff, fptom);
		fputs("\n", fptom);
		fputs(f01r->nomeblo[curblo], fptom);
		fputs("\n", fptom);
		for (i=0;i<f01r->porte[curblo]->numporte; i++ ) { // per ogni porta ...
			sprintf(buff,"por%s\n",f01r->porte[curblo]->idporta[i]); // nome della porta
			fputs(buff, fptom);
			if(strcmp(f01r->porte[curblo]->porta[i]->bloconn,"____") != 0) // porta occupata 
				sprintf(buff,"busy por%s %s\n",f01r->porte[curblo]->porta[i]->idbloconn,f01r->porte[curblo]->porta[i]->bloconn);
			else sprintf(buff,"free\n");
			fputs(buff, fptom);
		}
	fputs("++++\n", fptom);
	}

	fputs("****\n", fptom);
	fclose(fptom);
}
void conv_minuscolo( char *msg, char *buff)
{
    char *p;
	strcpy(buff, msg);
	for( p = buff; p < buff + strlen( buff ); p++,buff++)
   {
      if( isupper( *p ) )
         *buff=tolower( *p );
      else
         *buff=*p;
   }

}

void cercai5(HEADF01 *f01r,int curblo, char *path)
{

/* */
/* Ricerca del file i5 correlato al blocco ed eventuale scelta tra le varie alternative */
/* */

	int retfind;
	char nomefile[100], buff[MAXL];
	char nomi[MAXFILEI5][12];
	int conta, scelta, i;

          glob_t lpFindFileData;


	strcpy(nomefile,path);
	conv_minuscolo(f01r->nomemod[curblo],buff);
	strcat(nomefile,buff);
	strcat(nomefile,"*.i5");
	printf("\ncercaI5 - %s\n",nomefile);
	i=0;

          lpFindFileData.gl_offs = 0;




	if( (retfind=glob(nomefile, GLOB_DOOFFS, NULL, &lpFindFileData)) == 0) {// pointer to name of file to search for
           conta=lpFindFileData.gl_pathc;
	   for (i=0;i<conta;i++) {
	        strcpy(nomi[i],( char *)basename(lpFindFileData.gl_pathv[i]));
		printf("Trovato----> %s\n",( char *)lpFindFileData.gl_pathv[i]);
		}
	}

	if( retfind==GLOB_NOMATCH ) {
		sprintf(buff,"f01totom - file  %s NON Trovato!\n",nomefile);
		essit(buff);
	}

/*	while (FindNextFile( retfind,lpFindFileData) != 0)  {
		i++;
		strcpy(nomi[i],lpFindFileData->cFileName);
		printf("Trovata altra configurazione----> %s\n",lpFindFileData->cFileName);
	}
	conta=++i;
*/

// dialogo di scelta
	scelta=0;
//	alldef=0;
	strcpy(filei5scelto,f01r->nomei5[curblo]);
	if(nodefile==1) strcpy(filei5scelto,nomi[0]);
	if(alldef==1 ) return;
    if (conta != 1) {
		printf("Il modulo %s ( blocco %s) ha %d possibili configurazioni\n",f01r->nomei5[curblo],f01r->nomeblo[curblo], conta);
		for (i=0;i<conta;i++) printf("%d - %s\n",i,nomi[i]);
		printf ("seleziona[%s]?=",f01r->nomei5[curblo]);

//		if( gets(buff) == NULL) scelta=-1;
		if( fgets(buff, MAXL,stdin) == NULL) scelta=-1;
		scelta=atoi(buff);
		if( buff[0]=='a') alldef=1, scelta=-1;
	}
    if(scelta>=0) strcpy(filei5scelto,nomi[scelta]);


}
int nomi_defi5(int mode,HEADF01 *f01r){
/* */
/* Lettura o Scrittura del file f01totom.inp che contiene la scelta degli i5 usata nel precedente run*/
/* */

	FILE *fpdefi5;
	char buff[MAXL], dum1[5],dum2[5];
	int curblo;


	if( mode == LEGGI) {
		for (curblo=0;curblo< f01r->totblo; curblo++) strcpy(f01r->nomei5[curblo],"");
		if((fpdefi5=fopen("f01totom.inp","r")) == NULL) return(0);
// leggo il file e carico f0ir
		for (curblo=0;curblo< f01r->totblo; curblo++){
			fgets(buff,MAXL,fpdefi5);
			sscanf(buff,"%s %s %s",dum1,dum2,f01r->nomei5[curblo]);
		}
		fclose(fpdefi5);
		return(1);	
	}
// scrivo il file	
	if((fpdefi5=fopen("f01totom.inp","w")) == NULL) 
		essit("f01totom - errore in aperura del file f01totom.inp" );
		for (curblo=0;curblo< f01r->totblo; curblo++){
			fprintf(fpdefi5,"%s %s %s\n",f01r->nomemod[curblo],f01r->nomeblo[curblo],f01r->nomei5[curblo]);  
		}
		fclose(fpdefi5);
		return(1);
}

int leggi_macroblocks( HEADF01 *f01r ){
/* */
/* Lettura o Scrittura del file macroblockz.dat per determinare la posizione delle icone */
/* */

	FILE *fpmacro;
	char buff[MAXL], indic[2],nometot[9], dum3[5],dum4[3], postx[5],posty[5], buff9[9];
	int i, curblo, lun, pagcur, trovato;

//		for (curblo=0;curblo< f01r->totblo; curblo++) strcpy(f01r->blo[curblo].posx=;
	f01r->totpag=1;	
	if((fpmacro=fopen("macroblocks.dat","r")) == NULL) return(0); // il file non c'�
// leggo il file macroblocks e carico f0ir con posx posy e pag
		
		for (i=0;i<5;i++) fgets(buff,MAXL,fpmacro);

		pagcur=0;
	while( !feof( fpmacro ) ) {
		fgets(buff,MAXL,fpmacro);
		sscanf(buff,"%s %s %s %s %s %s",indic,nometot,dum3,dum4, postx, posty);
		lun=strlen(nometot);
		if(lun < 8) {
				strcpy(buff9,"        ");
				strncpy(buff9,nometot,lun);
				strcpy(nometot,buff9);
		}
		if( indic[0] == '0' ) pagcur++;
trovato=0;
		while ( indic[0] == '0' ) {
			lun=strlen(nometot);
			if(lun < 8) {
				strcpy(buff9,"        ");
				strncpy(buff9,nometot,lun);
				strcpy(nometot,buff9);
			}		

			for (curblo=0;curblo< f01r->totblo; curblo++) {
				strcpy(buff9,f01r->nomemod[curblo]);
				strcat(buff9,f01r->nomeblo[curblo]);
				if( strcmp(buff9,nometot) == 0) {
					f01r->blo[curblo]->posx=atoi(postx);
					f01r->blo[curblo]->posy=atoi(posty);
					f01r->blo[curblo]->pag=pagcur;
		    trovato=1;
printf("%i %i %s --> x=%i y=%i postx=%s posty=%s\n",pagcur,curblo, f01r->nomeblo[curblo], f01r->blo[curblo]->posx,f01r->blo[curblo]->posy, postx, posty );

					break;
				}
			}
if( trovato == 0 ) printf("Non trovato %i %s %s\n",curblo, buff9, 	f01r->nomeblo[curblo]);

			fgets(buff,MAXL,fpmacro);
			sscanf(buff,"%s %s %s %s %s %s",indic,nometot,dum3,dum4, postx, posty);
		}
		while ( (strncmp(buff,"****",4) != 0) && !feof(fpmacro) ) fgets(buff,MAXL,fpmacro);
        fgets(buff,MAXL,fpmacro);
		if(feof( fpmacro ) ) break; 
		fgets(buff,MAXL,fpmacro);
	}
      
		f01r->totpag=f01r->totpag+pagcur;

		fclose(fpmacro);
		return(1);
}
