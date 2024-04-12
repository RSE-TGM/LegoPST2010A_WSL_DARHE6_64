/*********************************************************
 *
 * i32i5.h
 *
 * Creato:	27 Febbraio 1995
 * Modificato:	27 Febbraio 1995
 * scritto da:	Marco Bonasoro
 *
 * descrizione:
 * file header per l'applicazione i32i5, un
 * convertitore che accetta in input un file .I3, e scrive
 * automaticamente il file .I5 corrispondente.
 * Contiene la definizione di costanti e i typedefs
 *
 * incluso in:
 *   i32i5.c
 *
 *********************************************************/


#define CFGBASESLOT	3		/* posizione dell'eventuale numbase in fnum */
#define NULLFVAR	"____"		/* nome di variabile fisica non utilizzata */


typedef struct i3matVarDesc {
	char mvname[GENERICVARNAMENCH+1];
	char mvtype[MVTYPENCH+1];
	char mvcomment[COMMENTNCH];
} i3mvdesc;


typedef struct i3fportDesc {
	char fpname[FPNAMENCH+1];
	int fptype;
	char fpcomment[COMMENTNCH];
	char fvar[MAXNFISVAR][GENERICVARNAMENCH+1];
        int fnum[MAXNMATCFG][MAXNFISVAR];
} i3fpdesc;

