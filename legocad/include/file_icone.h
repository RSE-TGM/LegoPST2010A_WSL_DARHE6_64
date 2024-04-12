/**********************************************************************
*
*       C Header:               file_icone.h
*       Subsystem:              1
*       Description:
*       %created_by:    lorenzo %
*       %date_created:  Thu Aug 29 13:48:30 1996 %
*
**********************************************************************/
/* file_icone.h */
/* fecero Buffo e Calleri il 26/4 anno solare 1993 D.C. */

/* nomi di files utilizzati */
#define FILE_DATI_LIBUT  	"lista_moduli.dat"
#define FILE_DATI_LIBUTREG  	"lista_schemi.dat"
#define FILE_DATI_LIBREG  	"lista_moduli_reg.dat"
#define FILE_ICONE_MODP   	"icon_list.dat"
#define FILE_ICONE_STD    	"icon_std.dat"
#define FILE_SIMBOLI   	  	"symbol.dat"
#define BMAP_STD_MODP     	"std_modp.bmp"
#define BMAP_STD_MODNP    	"std_modnp.bmp"

#define DEFAULT_FOREGROUND	1
#define DEFAULT_BACKGROUND	0
#define DEFAULT_WIDTH	90
#define DEFAULT_HEIGHT	70
#define DEFAULT_SYMBOL_WIDTH	10
#define DEFAULT_SYMBOL_HEIGHT	10

#define BUFFER_SIZE	512
#define DIM_BUFFER	100

#define MAX_ICON_X_PMODULE	10
#define MAX_SYMBOL		99

/* tipi di moduli standard (processo e schema) */
#define MODULE_PROCESS	0
#define MODULE_SCHEME	1

/* codici di ritorno delle funzioni */
#define	RETURN_OK	0
#define RETURN_ERROR	-1

#ifdef VMS

#define PATH_LIBUT_UTE		"legocad.libut"
#define PATH_LIBUTREG_UTE	"legocad.libut_reg"
#define PATH_LIBREG_UTE		"legocad.libut_reg.libreg"
#define PATH_LIBGRAF_UTE	"legocad.libut"
#define PATH_LIBUT_STD		"sorgmodu.processo"
#define PATH_LIBUTREG_STD	"sorgmodu.regola"
#define PATH_LIBREG_STD		"sorgmodu.regola"
#define PATH_LIBGRAF_STD	"sorgmodu.lib_graf"

#else

#define PATH_LIBGRAF_STD	"sorgmodu/lib_graf"
#define PATH_LIBUT_STD		"sorgmodu/processo"
#define PATH_LIBUTREG_STD	"new_regola"
#define PATH_LIBREG_STD		"new_regola"
#define PATH_LIBGRAF_UTE	"legocad/libut"
#define PATH_LIBUT_UTE		"legocad/libut"
#define PATH_LIBUTREG_UTE	"legocad/libut_reg"
#define PATH_LIBREG_UTE		"legocad/libut_reg/libreg"

#endif

#define CREA_FALSE	0
#define CREA_TRUE	1

/* Flag che indica se si utilizza la libreria utente o standard */
/* NON CAMBIARE TALI VALORI PERCHE' SONO UTILIZZATI COME INDICI IN LIBRARIAN */
#define LIB_UTENTE	0
#define LIB_STANDARD	1

typedef struct {
                 char nome_file[14];
                 int  colore_fg, colore_bg;
                 int  base, altezza;
                 int  esiste;
               } BitmapFileRec;

typedef struct {
                 char nome_modulo[5];
                 char descr_modulo[51];
                 int num_icone;
                 BitmapFileRec bmap_record[10];
               } IconFileRec;

typedef struct {
                 int tipo_modulo;          /* icona standard di processo */
				           /* e di schema */
                 int num_icone;
                 BitmapFileRec bmap_record;
               } IconStdRec;

typedef struct {
                 char nome_modulo[5];
                 char descr_modulo[51];
               } SchemeFileRec;

typedef struct {
                 int num_simboli;
                 BitmapFileRec bmap_record[99];
               } SymbolFileRec;


/* Prototipi di funzioni */
#ifdef _NO_PROTO

FILE *apri_file_icoproc();
FILE *apri_file_icoscheme();
int scrivi_empty_record_file_ico();
FILE *apri_file_std();
int scrivi_record_file_ico();
int leggi_record_file_ico();
long cerca_modulo_proc();
int leggi_file_regola();
long cerca_modulo_regola();
int scrivi_file_std_ico();
long leggi_file_std_ico();
FILE *apri_file_symb();
int scrivi_file_simboli();
int leggi_file_simboli();
int recupera_dim_icona();
int prima_icona_disponibile();
int aggiungi_record_file_ico();
int cancella_record_file_ico();

#else

FILE *apri_file_icoproc(char, char);
FILE *apri_file_icoscheme(char);
int scrivi_empty_record_file_ico(FILE *, IconFileRec *);
int aggiungi_record_file_ico(char *, char, IconFileRec *);
int cancella_record_file_ico(char *, char);
FILE *apri_file_std(char, char);
int scrivi_record_file_ico(FILE *, IconFileRec *);
int leggi_record_file_ico(FILE *, IconFileRec *);
long cerca_modulo_proc(FILE *, IconFileRec *, char *);
int leggi_file_regola(FILE *, SchemeFileRec *);
long cerca_modulo_regola(FILE *, SchemeFileRec *, char *);
int scrivi_file_std_ico(FILE *, IconStdRec *);
long leggi_file_std_ico(FILE *, IconStdRec *, int);
FILE *apri_file_symb(SymbolFileRec *, char, char);
int scrivi_file_simboli(FILE *, BitmapFileRec *);
int leggi_file_simboli(FILE *, BitmapFileRec *);
int recupera_dim_icona(char *, int, int *, int *, char);
int prima_icona_disponibile(char *, int *, int *, char);

#endif

/* fine file_icone.h */
